/*
 * sched.c  --  Process scheduler, IDT, TSS, PIC, PIT
 */
#include "kernel.h"
#include "sched.h"
#include "smp.h"
#include "sync.h"
#include "bootdefs.h"
#include "vga_fb.h"
#include "sb16.h"
#include "arch/x86/msr.h"

/* The user-window and syscall-stack constants come from kernel.h, which
 * derives them from progs/minios_abi.h (the single source of truth for the
 * kernel-ABI memory layout). Do not copy a bare address here: the historical
 * MY_USER_STACK_TOP (0x07400000) went stale when the window grew and would
 * have stacked a scheduled process in the middle of the heap. */
#define MY_SYS_KSTK_TOP   SYS_KSTK_TOP
#define MY_USER_STACK_TOP USER_STACK_TOP
#define MY_USER_LOAD_BASE USER_LOAD_BASE

proc_t procs[MAX_PROCS];
int    proc_count;
cpu_t  cpus[MAX_CPUS];
int    cpu_count = 1;
volatile uint64_t sys_ticks;
volatile int user_program_active;
volatile int sched_ready;
spinlock_t sched_lock = SPINLOCK_INIT;

extern void user_trampoline(void);

static inline unsigned long read_cr3(void) {
    unsigned long v;
    __asm__ volatile("mov %%cr3, %0" : "=r"(v));
    return v;
}

/* Layout contract with the syscall_entry asm in kernel.c, which locates
 * the current proc's kernel stack top as procs + pid * SIZE + KSTACK_OFF
 * (it cannot use C here).  If either assert fires, update the immediates
 * in that trampoline to match. */
_Static_assert(__builtin_offsetof(proc_t, kstack) == 168, "proc kstack off");
_Static_assert(sizeof(proc_t) == 248, "proc size");
/* The AP stub loads the GDT with the SMP limit; it must cover one TSS
 * descriptor (two slots) per CPU past the 5 stage-2 entries. */
_Static_assert((5 + 2 * MAX_CPUS) * 8 == GDT64_SMP_BYTES, "GDT SMP size");

/* ---- TSS (one per CPU) ----
 *
 * Every CPU that runs ring-3 code needs a private TSS: a timer tick that
 * preempts ring 3 switches to TSS.rsp0, so two CPUs sharing one TSS would
 * run their ISRs on the same stack.  The runtime GDT grows from 7 entries
 * (5 from stage 2 + 1 TSS descriptor of 2 slots) to 5 + 2*MAX_CPUS
 * entries; CPU 0 keeps selector 0x28 exactly as before.  The GDT lives at
 * 0x8000 with 4 KB reserved up to stage 2 at 0x9000, so 21 entries
 * (168 bytes) fit with room to spare. */
typedef struct __attribute__((packed)) {
    uint32_t res0;
    uint64_t rsp0, rsp1, rsp2;
    uint64_t res1;
    uint64_t ist1, ist2, ist3, ist4, ist5, ist6, ist7;
    uint64_t res2;
    uint16_t res3;
    uint16_t iopb;
} tss_t;
static tss_t the_tss[MAX_CPUS] __attribute__((aligned(16)));
/* Private ring-3 preempt stacks, one per CPU (8 KB each). */
static char tss_kstack[MAX_CPUS][8192] __attribute__((aligned(16)));
/* Per-CPU idle stacks: a park into the idle context re-enters
 * smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */
static char ap_idle_stack[MAX_CPUS][4096] __attribute__((aligned(16)));
proc_t ap_idle_proc[MAX_CPUS];
volatile unsigned long smp_dispatches[MAX_CPUS];
volatile unsigned long smp_idle_polls[MAX_CPUS];
static volatile int ser_e_reported;

/* ---- IDT ---- */
typedef struct __attribute__((packed)) {
    uint16_t off_lo; uint16_t sel; uint8_t ist; uint8_t type_attr;
    uint16_t off_mid; uint32_t off_hi; uint32_t zero;
} idt_entry_t;
static idt_entry_t idt[256] __attribute__((aligned(16)));

/* Exported IDTR for APs to load during SMP bring-up.  Filled by idt_init(). */
idtr_t bsp_idtr;

extern void *isr_stub_table[];

/* ---- Kernel stack pool ---- */
static char kstack_pool[MAX_PROCS][16*1024] __attribute__((aligned(16)));
static int kstack_used[MAX_PROCS];  /* 0 = free, 1 = in use */

static uint64_t alloc_kstack(void) {
    int i;
    for (i = 0; i < MAX_PROCS; i++) {
        if (!kstack_used[i]) {
            kstack_used[i] = 1;
            return (uint64_t)&kstack_pool[i][16*1024];
        }
    }
    return 0;
}

static void free_kstack(uint64_t top) {
    if (!top) return;
    int idx = (int)(((char *)top - (char *)kstack_pool) / (16*1024));
    if (idx >= 0 && idx < MAX_PROCS) kstack_used[idx] = 0;
}

/* ---- Trap frame (must match isr_stubs.S) ---- */
typedef struct {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip, cs, rflags, rsp, ss;
    uint64_t vector, errcode;
} trap_frame_t;

/* Parked trap frames for preempted ring-3 contexts, one slot per pid.
 * The ISR copies the preempted frame here (never onto a live stack: the
 * TSS stack is reused by the next tick and a thread's own kstack may be
 * mid-syscall), points ctx at the copy and resumes it later through
 * resume_iretq + iretq.  Dedicated slots mean parking can never clobber
 * live kernel state. */
static trap_frame_t isr_park[MAX_PROCS];

/* ---- IDT init ---- */
static void idt_set(int vec, void (*h)(void)) {
    uint64_t a = (uint64_t)h;
    idt[vec].off_lo = a & 0xFFFF;
    idt[vec].sel = GDT64_CODE_SEL;
    idt[vec].ist = 0;
    idt[vec].type_attr = 0x8E;
    idt[vec].off_mid = (a >> 16) & 0xFFFF;
    idt[vec].off_hi = (a >> 32) & 0xFFFFFFFF;
    idt[vec].zero = 0;
}

static void idt_init(void) {
    kmemset(idt, 0, sizeof(idt));
    int i;
    for (i = 0; i < 256; i++)
        if (isr_stub_table[i])
            idt_set(i, (void(*)(void))isr_stub_table[i]);
    bsp_idtr.limit = sizeof(idt) - 1;
    bsp_idtr.base = (uint64_t)&idt;
    __asm__ volatile("lidt %0" :: "m"(bsp_idtr));
}

/* ---- PIC ---- */
static void pic_init(void) {
    /* Drain the i8042 output buffer before touching the masks.  SeaBIOS
     * probes the PS/2 mouse before our boot sector runs, and the command
     * ACKs it left behind (0xFA bytes) would otherwise enter the IRQ12
     * 4-byte phase machine below: two strays shift every later packet by
     * two, sticking the buttons (a left press reads back as bit 1) and
     * warping motion, permanently.  0xFA has bit 3 set, so the phase-0
     * guard cannot reject it; only a flush at init keeps the framing. */
    {
        int i;
        for (i = 0; i < 256; i++) {
            unsigned char st;
            __asm__ volatile("inb $0x64, %0" : "=a"(st));
            if (!(st & 0x01)) break;
            unsigned char d;
            __asm__ volatile("inb $0x60, %0" : "=a"(d));
            (void)d;
        }
    }
    outb(0x20,0x11); outb(0xA0,0x11);
    outb(0x21,0x20); outb(0xA1,0x28);
    outb(0x21,0x04); outb(0xA1,0x02);
    outb(0x21,0x01); outb(0xA1,0x01);
    /* Master: unmask IRQ0 (timer) + IRQ1 (keyboard) + IRQ2 (cascade) +
     * IRQ4 (COM1, UART IER stays 0 so it never fires) +
     * IRQ5 (Sound Blaster 16 DMA done).  In the mask register a bit set
     * means masked, so 0xC8 masks only IRQ3, IRQ6 and IRQ7.  Masking IRQ5
     * here starves the SB16 completion interrupt and leaves audio on the
     * timer watchdog alone (audible as jitter); keep it unmasked. */
    outb(0x21,0xC8);
    /* Slave: unmask IRQ12 (mouse) only. 0xEF = ~bit4. */
    outb(0xA1,0xEF);
}

/* ---- PIT channel 0: 100 Hz ---- */
static void pit_init(void) {
    outb(0x43, 0x34);
    int d = 1193182 / 100;
    outb(0x40, d & 0xFF);
    outb(0x40, (d >> 8) & 0xFF);
}

static void pic_eoi(int irq) {
    if (irq >= 8) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

/* ---- TSS + GDT expansion (one descriptor per CPU) ---- */
static uint8_t tss_gdtr_buf[10] __attribute__((aligned(2)));

static void tss_write_desc(int cpu) {
    uint64_t base = (uint64_t)&the_tss[cpu];
    uint32_t limit = sizeof(the_tss[cpu]) - 1;
    uint8_t *gdt = (uint8_t *)GDT64_ADDR;

    /* TSS descriptor at GDT slot 5 + 2*cpu (16 bytes, two slots).
     * Access 0x89: Present=1, DPL=0, S=0, Type=9 (available 64-bit TSS).
     * Flags 0x00: all reserved bits zero for TSS. */
    uint64_t lo = (uint64_t)(limit & 0xFFFF)
        | (((uint64_t)(base & 0xFFFFFF)) << 16)
        | (0x89ULL << 40)
        | (((uint64_t)(limit >> 16)) << 48);
    uint64_t hi = (uint64_t)(base >> 32);
    *(uint64_t *)(gdt + (5 + 2 * cpu) * 8) = lo;
    *(uint64_t *)(gdt + (5 + 2 * cpu) * 8 + 8) = hi;
}

static void tss_init(void) {
    int cpu;
    for (cpu = 0; cpu < MAX_CPUS; cpu++) {
        kmemset(&the_tss[cpu], 0, sizeof(the_tss[cpu]));
        the_tss[cpu].rsp0 = (uint64_t)&tss_kstack[cpu][8192];
        the_tss[cpu].iopb = sizeof(the_tss[cpu]);
        tss_write_desc(cpu);
    }

    /* Pack GDTR manually: limit(16 LE) + base(64 LE) */
    uint16_t gdtr_lim = (5 + 2 * MAX_CPUS) * 8 - 1;
    uint64_t gdtr_base = GDT64_ADDR;
    tss_gdtr_buf[0] = gdtr_lim & 0xFF;
    tss_gdtr_buf[1] = (gdtr_lim >> 8) & 0xFF;
    tss_gdtr_buf[2] = gdtr_base & 0xFF;
    tss_gdtr_buf[3] = (gdtr_base >> 8) & 0xFF;
    tss_gdtr_buf[4] = (gdtr_base >> 16) & 0xFF;
    tss_gdtr_buf[5] = (gdtr_base >> 24) & 0xFF;
    tss_gdtr_buf[6] = (gdtr_base >> 32) & 0xFF;
    tss_gdtr_buf[7] = (gdtr_base >> 40) & 0xFF;
    tss_gdtr_buf[8] = (gdtr_base >> 48) & 0xFF;
    tss_gdtr_buf[9] = (gdtr_base >> 56) & 0xFF;

    __asm__ volatile("lgdt (%0)" : : "r"(tss_gdtr_buf) : "memory");
    __asm__ volatile("ltr %%ax" :: "a"((uint16_t)0x28) : "memory");
}

/* Load this AP's task register.  The BSP wrote every descriptor in
 * tss_init before the APs were woken, so the AP only points its TR at
 * its own slot; its ring-3 preempts then land on its private rsp0
 * stack instead of the BSP's. */
void tss_init_ap(int cpu) {
    uint16_t sel = TSS_SEL(cpu);
    __asm__ volatile("ltr %%ax" :: "a"(sel) : "memory");
}

/* ---- C dispatch from isr_common ---- */

/* Guards the shared g_brk/g_brk_limit/user_mmap_cur view and the VMA
 * trees against concurrent brk/mmap/munmap syscalls from threads on
 * different CPUs.  Defined in kernel/syscalls.c; always taken INSIDE
 * sched_lock (lock order: sched_lock -> mm_lock), never alone in the
 * scheduler paths. */
extern spinlock_t mm_lock;

/* Re-arm this CPU's SYSCALL swap target before entering next.
 * KGS must equal &cpus[cpu] whenever ring-3 code runs: a syscall entry
 * swaps GS with KGS, so a stale KGS hands the entry the wrong GS and
 * the cur_pid math reads garbage.  KGS goes stale whenever a GS=0
 * context (anything entered via k_exec_user) is inside a syscall
 * (entry swapped 0 in), and a context switch in that window would
 * otherwise propagate the stale value to the incoming thread. */
static inline void sched_rearm_kgs(void) {
    wrmsr(MSR_KERNEL_GS_BASE, (unsigned long)this_cpu());
}

/* Park a preempted context: the whole trap frame is copied to the
 * pid's dedicated slot and resumed later via resume_iretq + iretq.
 * This is uniform for ring 3 AND ring 0 preempts: resuming with a
 * plain iretq is correct for an interrupted ring-0 context too (the
 * kernel is compiled -mno-red-zone, and the 64-bit interrupt frame
 * always carries rsp/ss).  The older ring-0 path saved the ISR's own
 * return address as the resume point ("continue the ISR"), which
 * required the stranded ISR frame to stay intact on the interrupted
 * stack — under SMP, two CPUs can preempt the same thread at different
 * stack depths and a later resume lands on a clobbered frame. */
static void sched_save_preempt(proc_t *cur, trap_frame_t *frame,
                               int from_user) {
    (void)from_user;
    trap_frame_t *dst = &isr_park[cur->pid];
    kmemcpy(dst, frame, sizeof(trap_frame_t));
    cur->ctx.rip = (uint64_t)resume_iretq;
    cur->ctx.rsp = (uint64_t)dst;
}

/* Round-robin scan with sched_lock HELD.  Returns a claimed (PROC_RUNNING)
 * pid or -1.  vm_only restricts the pick to CLONE_VM threads, which is
 * what APs run: same CR3, no brk/mmap view switch, no TLB work. */
static int sched_next_locked(int start, int vm_only) {
    int next = start;
    int t;
    for (t = 0; t < MAX_PROCS; t++) {
        next = (next + 1) % MAX_PROCS;
        if (procs[next].state != PROC_READY) continue;
        if (vm_only && !(procs[next].clone_flags & CLONE_VM)) continue;
        procs[next].state = PROC_RUNNING;
        return next;
    }
    return -1;
}

/* Claim one READY thread for this CPU's idle loop (the AP only claims
 * CLONE_VM threads): marks it RUNNING under lock and installs it as the
 * CPU's current pid.  Returns the pid, or -1 when nothing is ready. */
static int smp_claim_thread_v(int vm_only) {
    irqflags_t flags;
    spin_lock_irqsave(&sched_lock, &flags);
    int next = sched_next_locked(this_cpu()->cur_pid, vm_only);
    if (next >= 0)
        this_cpu()->cur_pid = next;
    spin_unlock_irqrestore(&sched_lock, flags);
    return next;
}

/* AP idle loop: hlt until a CLONE_VM thread is ready, run it, repeat.
 * Entered once from smp_ap_entry on the AP stub stack; the first
 * switch_to out of here saves these registers into ap_idle_proc[cpu],
 * so every return to idle resumes this loop.
 *
 * Interrupts stay OFF from the claim through the switch: a LAPIC tick
 * landing in between would park this half-switched state over the
 * incoming thread's ctx.  Threads enter with their own rflags (IF=1);
 * a resume back to idle restores IF=0, so sti runs after every
 * switch_to return.  The hlt itself needs IF=1 to wake. */
void smp_ap_idle_loop(void) {
    /* The BSP's idle claims everything (it is the fallback runner when
     * every other context is parked); an AP claims only CLONE_VM
     * threads, which share their parent's address space and so need no
     * brk/mmap view switch and no TLB work. */
    int cpu = this_cpu()->cpu_id;
    int vm_only = !this_cpu()->is_bsp;
    for (;;) {
        __asm__ volatile("cli");
        __sync_fetch_and_add(&smp_idle_polls[cpu], 1);
        int pid = smp_claim_thread_v(vm_only);
        if (pid < 0) {
            __asm__ volatile("sti; hlt; cli");
            continue;
        }
        proc_t *next = proc_get(pid);
        if (!next) {
            __asm__ volatile("sti");
            continue;
        }
        __sync_fetch_and_add(&smp_dispatches[cpu], 1);
        sched_rearm_kgs();
        switch_to(&ap_idle_proc[cpu], next);
        __asm__ volatile("sti");
    }
}

/* AP timer preemption: time-slice the AP's current CLONE_VM thread with
 * the next READY one.  An idle AP (cur_pid -1) needs nothing: its idle
 * loop polls.  The park/unclaim discipline is the same as the BSP tick:
 * park the trap frame (complete ctx), publish READY, claim the next,
 * switch NOTRAP (load-only) so a stealing CPU always resumes a valid
 * context.  A non-VM proc can never run here by construction; if one is
 * ever observed, leave it alone (fail safe, never migrate it). */
static void sched_ap_preempt(trap_frame_t *frame) {
    proc_t *cur = proc_get(current_pid);
    if (!cur || cur->state != PROC_RUNNING) return;
    if (!(cur->clone_flags & CLONE_VM)) return;
    sched_save_preempt(cur, frame, 0);
    irqflags_t flags;
    spin_lock_irqsave(&sched_lock, &flags);
    cur->state = PROC_READY;
    int next = sched_next_locked(current_pid, 1);
    if (next < 0 || next == current_pid) {
        cur->state = PROC_RUNNING;
        spin_unlock_irqrestore(&sched_lock, flags);
        return;
    }
    current_pid = next;
    proc_t *nxt = proc_get(next);
    spin_unlock_irqrestore(&sched_lock, flags);
    if (!nxt) return;
    sched_rearm_kgs();
    switch_to_notrap(cur, nxt);
}

/* True when some AP is idle.  The BSP tick uses this to leave freshly
 * parked CLONE_VM threads unclaimed: the idle AP's next poll (IPI
 * wake) picks them up, which keeps thread execution biased to the APs
 * instead of the BSP winning every claim race. */
static int smp_any_ap_idle(void) {
    int c;
    for (c = 1; c < cpu_count && c < MAX_CPUS; c++)
        if (cpus[c].cur_pid < 0) return 1;
    return 0;
}

void isr_dispatch(int vector, trap_frame_t *frame) {
    if (vector == 32) {
        /* Atomic: the BSP's PIT and every AP's LAPIC timer all run this
         * path, so a plain increment would lose ticks under SMP. */
        __sync_fetch_and_add(&sys_ticks, 1);
        if (this_cpu()->is_bsp) {
            pic_eoi(0);
            sb16_poll();
            /* Share the tick with the APs: their per-CPU LAPIC timers
             * are not a dependable wakeup for a halted AP in QEMU, so
             * the BSP broadcasts a fixed IPI (vector 32) every tick.
             * Each AP's ISR EOIs its own LAPIC; the same vector drives
             * thread preemption and idle-loop wakeups there. */
            if (cpu_count > 1) { __sync_fetch_and_add(&smp_dbg_sent, 1); smp_ipi_broadcast(32); }
        } else {
            /* AP: LAPIC EOI (LAPIC_EOI_OFF 0x0B0, named in smp.c)
             * instead of PIC EOI; also count it for the `smp` builtin. */
            *(volatile unsigned *)0xFEE000B0UL = 0;
            __sync_fetch_and_add(&smp_dbg_ipis, 1);
        }
        if (this_cpu()->is_bsp && proc_count > 1) {
            proc_t *cur = proc_get(current_pid);
            if (cur && cur->state == PROC_RUNNING) {
                /* A preempt from ring 3 parks the whole trap frame in the
                 * pid's dedicated slot and resumes it later through
                 * resume_iretq + iretq: returning through switch_to's ret
                 * would keep executing user code at CPL 0, the shared ISR
                 * stack the frame sits on is clobbered by the next tick,
                 * and switch_to_notrap skips the save that would bury the
                 * parked state under the ISR's own registers.  A preempt
                 * from ring 0 (inside a syscall) keeps the old raw save,
                 * which resumes correctly with a plain ret. */
                int from_user = ((frame->cs & 3) == 3);
                sched_save_preempt(cur, frame, from_user);
                irqflags_t sflags, mflags;
                spin_lock_irqsave(&sched_lock, &sflags);
                cur->state = PROC_READY;
                /* VM threads: when an AP is idle, leave them unclaimed
                 * so the AP's poll picks them up (threads run on the
                 * APs; the claim race otherwise always goes to the
                 * BSP's tick ISR). */
                int next = sched_next_locked(current_pid,
                                             smp_any_ap_idle());
                if (next >= 0 && next != current_pid) {
                    proc_t *nxt = proc_get(next);
                    /* Save per-process brk/mmap from outgoing, load into incoming.
                     * CLONE_VM threads share one address space with their
                     * parent, so the globals stay untouched: switching the
                     * view per thread would let two allocators hand out the
                     * same bytes.  The swap runs under mm_lock (inside
                     * sched_lock) so a concurrent brk/mmap syscall on an
                     * AP cannot interleave it. */
                    spin_lock_irqsave(&mm_lock, &mflags);
                    if (!(cur->clone_flags & CLONE_VM))
                        cur->brk = g_brk, cur->brk_limit = g_brk_limit, cur->mmap_cur = user_mmap_cur;
                    current_pid = next;
                    nxt->state = PROC_RUNNING;
                    if (!(nxt->clone_flags & CLONE_VM))
                        g_brk = nxt->brk, g_brk_limit = nxt->brk_limit, user_mmap_cur = nxt->mmap_cur;
                    spin_unlock_irqrestore(&mm_lock, mflags);
                    spin_unlock_irqrestore(&sched_lock, sflags);
                    /* Re-arm the swap slot before abandoning this frame:
                     * a from_user switch skips the ISR exit swapgs, and a
                     * ring-0 switch may land in a KGS window left by the
                     * outgoing syscall (see sched_rearm_kgs).  Without
                     * this the next entry swapgs puts garbage under GS
                     * and the pid math faults. */
                    sched_rearm_kgs();
                    /* NOTRAP only (see sched_ap_preempt): cur's ctx is
                     * complete from the park; the save phase would let
                     * a stealing CPU resume it into the dead ISR tail. */
                    switch_to_notrap(cur, nxt);
                } else {
                    cur->state = PROC_RUNNING;
                    spin_unlock_irqrestore(&sched_lock, sflags);
                }
            }
        } else if (!this_cpu()->is_bsp && proc_count > 1) {
            /* APs time-slice CLONE_VM threads; the BSP owns everything
             * else (devices, mouse tick, non-VM processes). */
            sched_ap_preempt(frame);
        } else if (this_cpu()->is_bsp && (sys_ticks % DESKTOP_TICK_INTERVAL) == 0) {
            if (user_program_active) vga_fb_mouse_tick();
        }
        return;
    }
    if (vector == 33) { pic_eoi(1); return; }
    if (vector == 44) { /* IRQ12: PS/2 mouse */
        static int mouse_phase;
        static unsigned char mouse_packet[4];
        unsigned char status;
        __asm__ volatile("inb $0x64, %0" : "=a"(status));
        if (!(status & 0x20)) { pic_eoi(12); return; }
        unsigned char data;
        __asm__ volatile("inb $0x60, %0" : "=a"(data));
        if (mouse_phase == 0) {
            if (data & 0x08) {
                mouse_packet[0] = data;
                mouse_phase = 1;
            }
        } else if (mouse_phase == 1) {
            mouse_packet[1] = data;
            mouse_phase = 2;
        } else if (mouse_phase == 2) {
            mouse_packet[2] = data;
            mouse_phase = 3;
        } else {
            /* Byte 4: Intellimouse wheel data */
            mouse_packet[3] = data;
            mouse_phase = 0;
            mouse_state.buttons = mouse_packet[0] & 0x07;
            int dx = (int)(signed char)mouse_packet[1];
            int dy = (int)(signed char)mouse_packet[2];
            mouse_state.x += dx * 2;
            mouse_state.y -= dy * 2;
            int wheel = (int)(signed char)(mouse_packet[3] << 4) >> 4;
            mouse_state.wheel += wheel;
            mouse_state.present = 1;
        }
        pic_eoi(12);
        return;
    }
    if (vector == 37) { /* IRQ5: Sound Blaster 16 DMA buffer complete */
        sb16_irq();
        pic_eoi(5);
        return;
    }
    if (vector >= 32 && vector < 48) { pic_eoi(vector - 32); return; }
    if (vector < 32) {
        /* Serial-only dump: the exception handler must not fault.  The
         * normal kprintf path renders through the framebuffer terminal,
         * and a corrupted page table that caused the fault can also
         * fault the FB write, killing the handler before it prints. */
        unsigned long fault_addr = 0;
        if (vector == 14)
            __asm__ volatile("mov %%cr2, %0" : "=r"(fault_addr));
        {
            char h[17];
            static const char digits[] = "0123456789abcdef";
            serial_puts("EXCEPTION ");
            for (int i = 0; i < 16; i++) h[i] = '0';
            h[16] = 0;
            unsigned long v = (unsigned long)frame->vector;
            for (int i = 15; i >= 8; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
            serial_puts(h + 8);
            serial_puts(" err=");
            v = (unsigned long)frame->errcode;
            for (int i = 15; i >= 8; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
            serial_puts(h + 8);
            serial_puts(" rip=");
            v = (unsigned long)frame->rip;
            for (int i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
            serial_puts(h);
            serial_puts(" rsp=");
            v = (unsigned long)frame->rsp;
            for (int i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
            serial_puts(h);
            serial_puts(" cr2=");
            v = fault_addr;
            for (int i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
            serial_puts(h);
            serial_puts("\n");
        }
        /* Dump the PTE of the faulting address (walk CR3): a user fault
         * with a garbage PTE means the page tables were corrupted by a
         * wild kernel write, and the PTE value identifies the writer. */
        if (vector == 14 && fault_addr >= 0x400000 && fault_addr < 0xC000000) {
            unsigned long cr3v, pml4e, pdpe, pde, pte = 0;
            unsigned long *tab;
            __asm__ volatile("mov %%cr3, %0" : "=r"(cr3v));
            tab = (unsigned long *)(cr3v & ~0xFFFUL);
            pml4e = tab[(fault_addr >> 39) & 511];
            tab = (unsigned long *)(pml4e & ~0xFFFUL);
            pdpe = tab[(fault_addr >> 30) & 511];
            tab = (unsigned long *)(pdpe & ~0xFFFUL);
            pde = tab[(fault_addr >> 21) & 511];
            if (!(pde & 0x80)) {
                tab = (unsigned long *)(pde & ~0xFFFUL);
                pte = tab[(fault_addr >> 12) & 511];
            }
            char h[17];
            static const char digits[] = "0123456789abcdef";
            serial_puts("  pte walk: cr3=");
            unsigned long vals[5]; vals[0]=cr3v; vals[1]=pml4e; vals[2]=pdpe; vals[3]=pde; vals[4]=pte;
            static const char *names[5] = { " cr3=", " pml4e=", " pdpe=", " pde=", " pte=" };
            for (int k = 0; k < 5; k++) {
                serial_puts(names[k]);
                unsigned long v = vals[k];
                for (int i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
                serial_puts(h);
            }
            serial_puts("\n");
        }
        /* CPU identity and GPRs, serial-only: this_cpu() dereferences
         * GS, which may itself be the corruption (it cascades). */
        {
            char h[17];
            static const char digits[] = "0123456789abcdef";
            static const char *label[] = {
                "  gs=", " kgs=", " rax=", " rbx=", " rcx=", " rdx=",
                " rsi=", " rdi=", " rbp=", " r8=", " r9=", " r10=",
                " r11=", " r12=", " r13=", " r14=", " r15=" };
            unsigned long vals[] = {
                rdmsr(MSR_GSBASE), rdmsr(MSR_KERNEL_GS_BASE),
                frame->rax, frame->rbx, frame->rcx, frame->rdx,
                frame->rsi, frame->rdi, frame->rbp, frame->r8,
                frame->r9, frame->r10, frame->r11, frame->r12,
                frame->r13, frame->r14, frame->r15 };
            for (int k = 0; k < 17; k++) {
                serial_puts(label[k]);
                unsigned long v = vals[k];
                for (int i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
                h[16] = 0;
                serial_puts(h);
            }
            serial_puts("\n");
        }
        /* If a ring-3 user fault lands in the user window, recover:
         * pid 0 is the k_exec_user frame and longjmps back to the shell
         * with EFAULT.  A CLONE_VM thread (or any non-0 pid) must NOT
         * take that path: k_user_fault_return loads GS=&cpus[0] and
         * longjmps the shell's jmp_buf, which on an AP would make this
         * CPU believe it is the BSP (wrong per-CPU identity, two CPUs
         * running the shell context) — the thread dies through the
         * scheduler instead and its parent reaps it with waitpid. */
        if ((frame->cs & 3) == 3 &&
            frame->rip >= 0x400000 && frame->rip < 0x0C000000) {
            if (current_pid == 0) {
                serial_puts("  [recovering: ring-3 user fault, returning EFAULT]\n");
                k_user_fault_return();
                __builtin_unreachable();
            }
            serial_puts("  [thread faulted: killing]\n");
            do_exit(EFAULT);
            __builtin_unreachable();
        }
        serial_puts("  [no recovery]\n");
        for(;;) __asm__("hlt");
    }
}

/* ---- Process management ---- */

proc_t *proc_get(int pid) {
    if (pid < 0 || pid >= MAX_PROCS) return 0;
    if (procs[pid].state == PROC_FREE) return 0;
    return &procs[pid];
}

int proc_create(const char *name, int parent_pid) {
    spin_lock(&sched_lock);
    int pid;
    for (pid = 1; pid < MAX_PROCS; pid++)
        if (procs[pid].state == PROC_FREE) break;
    if (pid >= MAX_PROCS) { spin_unlock(&sched_lock); return -1; }

    proc_t *p = &procs[pid];
    kmemset(p, 0, sizeof(proc_t));
    p->pid = pid;
    p->state = PROC_READY;
    p->parent_pid = parent_pid;
    p->clone_flags = 0;
    kstrncpy(p->name, name, sizeof(p->name) - 1);

    /* Inherit brk/mmap defaults from parent */
    proc_t *parent = proc_get(parent_pid);
    if (parent) {
        p->brk = parent->brk;
        p->brk_limit = parent->brk_limit;
        p->mmap_cur = parent->mmap_cur;
    } else {
        p->brk = 0;
        p->brk_limit = USER_BRK_END;
        p->mmap_cur = USER_BRK_END;
    }

    uint64_t kstack_top = alloc_kstack();
    if (!kstack_top) { spin_unlock(&sched_lock); return -1; }
    p->kstack = kstack_top;

    /* Build iretq frame at the top of the kernel stack */
    unsigned long *frame = (unsigned long *)(kstack_top - 40);
    frame[0] = (unsigned long)MY_USER_LOAD_BASE;
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x200;
    frame[3] = MY_USER_STACK_TOP - 8;
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    p->ctx.rip = (uint64_t)user_trampoline;
    p->ctx.rsp = (uint64_t)frame;
    /* Give the new process its own page tables so it is isolated from
     * the parent and from other processes.  pt_clone_user copies the
     * kernel identity mapping and creates fresh user-window PTEs. */
    uint64_t new_cr3 = pt_clone_user(read_cr3());
    p->ctx.cr3 = new_cr3 ? new_cr3 : read_cr3();
    p->ctx.rflags = 0x200;

    if (proc_count <= pid) proc_count = pid + 1;
    spin_unlock(&sched_lock);
    return pid;
}

/* Capture "schedule() has returned" as the resume context: rip = the
 * CALLER's return address, rsp = the CALLER's stack, IF = 1.  On the
 * next claim the thread RETURNS from schedule() into its own caller
 * (yield / sleep_on / do_waitpid / do_exit) instead of replaying
 * schedule()'s tail on a foreign CPU — the tail's unlock and
 * current_pid writes must never run twice.  Frame walk: this helper's
 * rbp -> (%rbp) = schedule()'s rbp -> 8(schedule rbp) = schedule's
 * return address, 16(schedule rbp) = the caller's rsp.  Requires a
 * frame pointer (the kernel builds with -fno-omit-frame-pointer).
 * switch_save_only has just captured the live callee-saved GPRs, which
 * the caller needs; only rip/rsp/rflags are overridden. */
__attribute__((noinline))
static void sched_park_as_returned(proc_t *cur) {
    unsigned long rip, rsp, sched_rbp;
    __asm__ volatile("movq (%%rbp), %0" : "=r"(sched_rbp));
    __asm__ volatile("movq 8(%2), %0; leaq 16(%2), %1"
                     : "=&r"(rip), "=&r"(rsp) : "r"(sched_rbp));
    cur->ctx.rip = rip;
    cur->ctx.rsp = rsp;
    cur->ctx.rflags = 0x202;
}

void schedule(void) {
    cpu_t *me = this_cpu();
    int vm_only = !me->is_bsp;
    spin_lock(&sched_lock);
    int next = sched_next_locked(current_pid, vm_only);
    if (next < 0) {
        /* No work: park into this CPU's idle context.  The idle loop
         * claims again on the next tick/wake (the BSP idle claims
         * everything, an AP only CLONE_VM threads), so a woken waiter is
         * always picked up.  current_pid -1 marks the CPU idle. */
        proc_t *cur = proc_get(current_pid);
        if (!cur) {
            current_pid = -1;
            spin_unlock(&sched_lock);
            return;
        }
        int cpu = me->cpu_id;
        /* Publish only with a complete context: save under the lock
         * while the thread is still PROC_SWITCHING (never claimable),
         * then set the resume point and publish.  A BLOCKED/ZOMBIE
         * thread keeps its state (no one claims it until a wake). */
        switch_save_only(cur);
        sched_park_as_returned(cur);
        if (cur->state == PROC_SWITCHING) cur->state = PROC_READY;
        current_pid = -1;
        spin_unlock_keep_irq(&sched_lock);
        sched_rearm_kgs();
        /* The idle context is stateless: re-entry at the loop top, on
         * its private per-CPU stack.  A park that preserved the live
         * frame would resume it on whichever stack the loop happened
         * to be running (the 2 KB AP stub stack early on), where the
         * 100 Hz IPI ISRs clobber the saved frame between parks. */
        ap_idle_proc[cpu].ctx.rip = (uint64_t)smp_ap_idle_loop;
        ap_idle_proc[cpu].ctx.rsp =
            (uint64_t)&ap_idle_stack[cpu][sizeof(ap_idle_stack[0])];
        ap_idle_proc[cpu].ctx.cr3 = read_cr3();
        switch_to_notrap(cur, &ap_idle_proc[cpu]);
        return;
    }
    if (next == current_pid) {
        proc_t *k = proc_get(current_pid);
        if (k && k->state == PROC_SWITCHING) k->state = PROC_RUNNING;
        spin_unlock(&sched_lock);
        return;
    }
    proc_t *cur = proc_get(current_pid);
    proc_t *nxt = proc_get(next);
    if (!cur || !nxt) {
        if (cur && cur->state == PROC_SWITCHING) cur->state = PROC_RUNNING;
        spin_unlock(&sched_lock);
        return;
    }
    /* Save per-process brk/mmap state.  An AP only ever switches
     * between CLONE_VM threads (same address space), so it never
     * touches the shared view; the BSP swaps under mm_lock so an AP
     * brk/mmap syscall cannot interleave it. */
    irqflags_t mflags;
    spin_lock_irqsave(&mm_lock, &mflags);
    if (cur) { if (!(cur->clone_flags & CLONE_VM)) { cur->brk = g_brk; cur->brk_limit = g_brk_limit; cur->mmap_cur = user_mmap_cur; } }
    current_pid = next;
    if (!(nxt->clone_flags & CLONE_VM)) { g_brk = nxt->brk; g_brk_limit = nxt->brk_limit; user_mmap_cur = nxt->mmap_cur; }
    spin_unlock_irqrestore(&mm_lock, mflags);
    /* Capture the continuation while the thread is still PROC_SWITCHING
     * (never claimable), publish it as READY only once the ctx is
     * complete, then switch load-only: whichever CPU claims the thread
     * later resumes a valid context. */
    switch_save_only(cur);
    sched_park_as_returned(cur);
    if (cur->state == PROC_SWITCHING) cur->state = PROC_READY;
    spin_unlock_keep_irq(&sched_lock);
    sched_rearm_kgs();
    switch_to_notrap(cur, nxt);
}

void yield(void) {
    proc_t *cur = proc_get(current_pid);
    if (cur) {
        /* IF must stay off from the state transition through the save:
         * between READY (claimable) and the completed ctx save, another
         * CPU's claim would resume a stale context.  PROC_SWITCHING
         * makes the thread unclaimable; schedule() publishes it READY
         * only after the save.  schedule() re-enables on every path
         * that returns (and the resumed thread returns with IF=1). */
        __asm__ volatile("cli");
        cur->state = PROC_SWITCHING;
        schedule();
    }
}

void do_exit(int code) {
    spin_lock(&sched_lock);
    proc_t *cur = proc_get(current_pid);
    if (!cur) { spin_unlock(&sched_lock); return; }
    cur->exit_code = code;
    /* The kernel stack CANNOT be freed here: under SMP the zombie still
     * runs its exit tail (schedule's save/switch) on it, and a concurrent
     * proc_create would hand the same stack to a live thread.  The stack
     * and the page tables are freed by the reaper (do_waitpid) after the
     * zombie has switched away; procs[].exited no longer means "stack
     * freed" (it is kept for the historical waitpid check, which then
     * frees everything exactly once). */
    cur->state = PROC_ZOMBIE;
    cur->exited = 1;
    if (cur->parent_pid >= 0) {
        proc_t *parent = proc_get(cur->parent_pid);
        if (parent && parent->state == PROC_BLOCKED)
            parent->state = PROC_READY;
    }
    spin_unlock(&sched_lock);
    schedule();
}

/* do_thread_spawn(fn, stack, arg) - create a 1:1 kernel thread that shares
 * the caller's address space (CLONE_VM).  Unlike do_clone, whose child
 * frame is ambiguous, this one starts cleanly at fn(arg) on the given
 * stack:
 *
 *   child RIP = fn, child RSP = stack, child RDI = arg (SysV first arg),
 *   entered through the same user_trampoline + iretq path as proc_create.
 *
 * The caller (pthread-like user code) owns the stack: it must be allocated
 * before the call (8 KB each per the roadmap) with its TOP passed here,
 * and must stay alive until the thread is joined.  fn and stack must lie
 * in the user window (checked by the syscall wrapper).  The thread shares
 * CR3, the file table and (by the schedule() CLONE_VM rule) the live
 * brk/mmap view with its parent; the parent joins it with do_waitpid,
 * which reaps the exit code without freeing the shared page tables.
 * Returns the child PID, or -1 when no slot or stack is usable. */
long do_thread_spawn(unsigned long fn, unsigned long stack,
                     unsigned long arg) {
    proc_t *cur = proc_get(current_pid);
    if (!cur) return -1;
    if (!fn || !stack) return -1;

    spin_lock(&sched_lock);
    int pid;
    for (pid = 1; pid < MAX_PROCS; pid++)
        if (procs[pid].state == PROC_FREE) break;
    if (pid >= MAX_PROCS) { spin_unlock(&sched_lock); return -1; }

    proc_t *child = &procs[pid];
    kmemset(child, 0, sizeof(proc_t));
    child->pid = pid;
    child->state = PROC_READY;
    child->parent_pid = current_pid;
    child->clone_flags = CLONE_VM;
    child->wq_next = WQ_NONE;
    kstrncpy(child->name, cur->name, sizeof(child->name) - 1);

    uint64_t kstack_top = alloc_kstack();
    if (!kstack_top) { spin_unlock(&sched_lock); return -1; }
    child->kstack = kstack_top;

    /* Share the address space; inherit the current brk/mmap view.  The
     * live view stays in the globals while threads run (schedule() skips
     * save/load for CLONE_VM), so these copies are only the starting
     * point a future per-mm design would replace. */
    child->ctx.cr3 = cur->ctx.cr3;
    child->brk = cur->brk;
    child->brk_limit = cur->brk_limit;
    child->mmap_cur = cur->mmap_cur;

    /* iretq frame [rip, cs, rflags, rsp, ss]: start at fn(arg). */
    unsigned long *frame = (unsigned long *)(kstack_top - 40);
    frame[0] = fn;
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x202;
    frame[3] = stack;
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    child->ctx.rip = (uint64_t)user_trampoline;
    child->ctx.rsp = (uint64_t)frame;
    child->ctx.rflags = 0x200;
    child->ctx.rdi = arg;
    child->ctx.rax = 0;

    if (proc_count <= pid) proc_count = pid + 1;
    spin_unlock(&sched_lock);
    return pid;
}

/* do_clone(flags, newsp) - create a thread or process.
 * CLONE_VM: share address space (same CR3).
 * CLONE_FILES: share fd table (not yet implemented).
 * Returns child PID to parent, 0 to child. */
long do_clone(long flags, long newsp) {
    int cflags = (int)flags;
    proc_t *cur = proc_get(current_pid);
    if (!cur) return -1;

    spin_lock(&sched_lock);
    int pid;
    for (pid = 1; pid < MAX_PROCS; pid++)
        if (procs[pid].state == PROC_FREE) break;
    if (pid >= MAX_PROCS) { spin_unlock(&sched_lock); return -1; }

    proc_t *child = &procs[pid];
    kmemset(child, 0, sizeof(proc_t));
    child->pid = pid;
    child->state = PROC_READY;
    child->parent_pid = current_pid;
    child->clone_flags = cflags;
    kstrncpy(child->name, cur->name, sizeof(child->name) - 1);

    uint64_t kstack_top = alloc_kstack();
    if (!kstack_top) { spin_unlock(&sched_lock); return -1; }
    child->kstack = kstack_top;

    if (cflags & CLONE_VM) {
        child->ctx.cr3 = cur->ctx.cr3;
    } else {
        uint64_t new_cr3 = pt_clone_user(read_cr3());
        child->ctx.cr3 = new_cr3 ? new_cr3 : read_cr3();
    }

    child->brk = cur->brk;
    child->brk_limit = cur->brk_limit;
    child->mmap_cur = cur->mmap_cur;

    unsigned long *frame = (unsigned long *)(kstack_top - 40);
    frame[0] = (unsigned long)(newsp ? newsp : cur->ctx.rsp);
    frame[1] = (unsigned long)(GDT64_USER_CODE_SEL | 3);
    frame[2] = 0x202;
    frame[3] = (unsigned long)(newsp ? newsp : cur->ctx.rsp);
    frame[4] = (unsigned long)(GDT64_USER_DATA_SEL | 3);

    child->ctx.rip = (uint64_t)user_trampoline;
    child->ctx.rsp = (uint64_t)frame;
    child->ctx.rflags = 0x200;
    child->ctx.rax = 0;

    if (proc_count <= pid) proc_count = pid + 1;
    spin_unlock(&sched_lock);
    return pid;
}

int do_waitpid(int pid) {
    proc_t *cur = proc_get(current_pid);
    if (!cur) return -1;
    for (;;) {
        spin_lock(&sched_lock);
        int i;
        for (i = 0; i < MAX_PROCS; i++) {
            if (procs[i].state != PROC_FREE
                && procs[i].parent_pid == current_pid
                && procs[i].state == PROC_ZOMBIE
                && (pid == -1 || pid == procs[i].pid)) {
                int code = procs[i].exit_code;
                /* Reap owned resources exactly once.  do_exit no longer
                 * frees anything (the zombie still runs its exit tail on
                 * its stack under SMP): the reaper frees the kernel stack
                 * and the page tables here, after the zombie has parked.
                 * CLONE_VM threads share the parent's page tables; their
                 * private kernel stack is still freed here. */
                if (procs[i].ctx.cr3
                    && !(procs[i].clone_flags & CLONE_VM))
                    pt_free_user(procs[i].ctx.cr3);
                free_kstack(procs[i].kstack);
                procs[i].kstack = 0;
                procs[i].state = PROC_FREE;
                spin_unlock(&sched_lock);
                return code;
            }
        }
        spin_unlock(&sched_lock);
        cur->state = PROC_BLOCKED;
        schedule();
    }
}

int do_kill(int pid) {
    proc_t *p = proc_get(pid);
    if (!p) return -1;
    do_exit(-1);
    return 0;
}

void timer_tick(void) { __sync_fetch_and_add(&sys_ticks, 1); }

/* ---- PS/2 mouse hardware init ---- */
static void mouse_wait_cmd(void) {
    int timeout = 100000;
    while (timeout--) {
        if (!(inb(0x64) & 2)) return;
    }
}

static void mouse_wait_data(void) {
    int timeout = 100000;
    while (timeout--) {
        if (inb(0x64) & 1) return;
    }
}

static void mouse_write(unsigned char data) {
    mouse_wait_cmd();
    outb(0x64, 0xD4);
    mouse_wait_cmd();
    outb(0x60, data);
}

static unsigned char mouse_read(void) {
    mouse_wait_data();
    return inb(0x60);
}

static void mouse_hw_init(void) {
    /* Drain any stale bytes in the output buffer */
    while (inb(0x64) & 1) inb(0x60);

    /* Enable auxiliary device (mouse) */
    mouse_wait_cmd();
    outb(0x64, 0xA8);

    /* Enable IRQ12 by setting bit 1 of the PS/2 controller config byte */
    mouse_wait_cmd();
    outb(0x64, 0x20);
    mouse_wait_data();
    unsigned char config = inb(0x60);
    mouse_wait_cmd();
    outb(0x64, 0x60);
    mouse_wait_cmd();
    outb(0x60, config | 0x02);

    /* Reset mouse.  A reset yields THREE reply bytes (0xFA ack, 0xAA
     * self-test, device ID); reading fewer leaves the rest pending, and
     * each stray enters the IRQ12 phase machine below: 0xAA has bit 3
     * set, so the phase-0 guard accepts it as a packet start and every
     * later packet is framed wrong (a left press reads back as bit 1,
     * motion warps), permanently. */
    mouse_write(0xFF);
    mouse_read();
    mouse_read();
    mouse_read();

    /* Enable Intellimouse extension for scroll wheel:
     * Set sample rate to 200, 100, 80 in sequence */
    mouse_write(0xF3); mouse_read();  /* set sample rate */
    mouse_write(0xC8); mouse_read();  /* 200 */
    mouse_write(0xF3); mouse_read();  /* set sample rate */
    mouse_write(0x64); mouse_read();  /* 100 */
    mouse_write(0xF3); mouse_read();  /* set sample rate */
    mouse_write(0x50); mouse_read();  /* 80 */
    /* Read device ID: 0x03 = Intellimouse (wheel) */
    mouse_write(0xF2); mouse_read();
    unsigned char id = mouse_read();
    (void)id;

    /* Set defaults */
    mouse_write(0xF6);
    mouse_read();

    /* Enable data reporting */
    mouse_write(0xF4);
    mouse_read();
}

void mouse_disable(void) { mouse_write(0xF5); mouse_read(); }
void mouse_enable(void)  { mouse_write(0xF4); mouse_read(); }

void sched_init(void) {
    int c;
    kmemset(procs, 0, sizeof(procs));
    kmemset(cpus, 0, sizeof(cpus));
    kmemset(ap_idle_proc, 0, sizeof(ap_idle_proc));
    proc_count = 1;

    /* Per-CPU idle contexts: pid -1 marks them as never-pickable; a
     * state other than PROC_READY keeps every scan away.  The AP fills
     * in its own entry in smp_ap_entry before its first dispatch.
     * cr3 must be the kernel tables on every CPU: switch_to loads
     * next->ctx.cr3 unconditionally, so a zero would wipe the page
     * tables the first time schedule() parks a finished process.
     * rip/rsp point at a private idle stack so a park into a virgin
     * idle context re-enters the idle loop instead of jumping to 0. */
    {
        unsigned long cr3 = read_cr3();
        for (c = 0; c < MAX_CPUS; c++) {
            ap_idle_proc[c].pid = -1;
            ap_idle_proc[c].state = PROC_BLOCKED;
            ap_idle_proc[c].parent_pid = -1;
            ap_idle_proc[c].ctx.cr3 = cr3;
            ap_idle_proc[c].ctx.rip = (uint64_t)smp_ap_idle_loop;
            ap_idle_proc[c].ctx.rsp =
                (uint64_t)&ap_idle_stack[c][sizeof(ap_idle_stack[0])];
            ap_idle_proc[c].ctx.rflags = 0x202;
        }
    }

    /* Initialize BSP (cpu 0) per-CPU state */
    cpus[0].self = &cpus[0];
    cpus[0].cpu_id = BOOT_CPU;
    cpus[0].cur_pid = 0;
    cpus[0].is_bsp = 1;
    cpus[0].lapic_id = 0;
    cpus[0].syscall_kstack = SYS_KSTK_TOP;

    /* Set GS base so this_cpu() works from the BSP */
    wrmsr(MSR_GSBASE, (unsigned long)&cpus[0]);
    /* Seed the SYSCALL swap target (k_exec_user re-arms it per run;
     * the APs seed their own in smp_ap_entry). */
    wrmsr(MSR_KERNEL_GS_BASE, (unsigned long)&cpus[0]);

    procs[0].pid = 0;
    procs[0].state = PROC_RUNNING;
    procs[0].parent_pid = -1;
    kstrcpy(procs[0].name, "kernel");
    procs[0].ctx.cr3 = read_cr3();
    /* Every live proc owns a kernel stack for syscall entry (see
     * syscall_entry); k_exec_user temporarily points this one at a
     * deeper stack for the run. */
    procs[0].kstack = alloc_kstack();

    /* IDT and TSS FIRST: pic_init unmasks IRQ0/1/12, and the PIT starts
     * firing the moment pit_init runs — an IRQ delivered with the IDT
     * still zeroed (kmemset happens inside idt_init) faults through a
     * null gate.  Handlers for 32/33/44 are safe pre-mouse-init. */
    idt_init();
    tss_init();
    pic_init();
    pit_init();
    mouse_hw_init();
    __asm__ volatile("sti");
    sched_ready = 1;
}
