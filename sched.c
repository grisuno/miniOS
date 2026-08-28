/*
 * sched.c  --  Process scheduler, IDT, TSS, PIC, PIT
 */
#include "kernel.h"
#include "sched.h"
#include "bootdefs.h"
#include "vga_fb.h"

/* Local copies of kernel constants (static in kernel.c) */
#define MY_SYS_KSTK_TOP   0x00088000UL
#define MY_USER_STACK_TOP 0x02000000UL
#define MY_USER_LOAD_BASE 0x00400000UL

proc_t procs[MAX_PROCS];
int    proc_count;
int    current_pid;
volatile uint64_t sys_ticks;
volatile int user_program_active;

extern void user_trampoline(void);

static inline unsigned long read_cr3(void) {
    unsigned long v;
    __asm__ volatile("mov %%cr3, %0" : "=r"(v));
    return v;
}

/* ---- TSS ---- */
typedef struct __attribute__((packed)) {
    uint32_t res0;
    uint64_t rsp0, rsp1, rsp2;
    uint64_t res1;
    uint64_t ist1, ist2, ist3, ist4, ist5, ist6, ist7;
    uint64_t res2;
    uint16_t res3;
    uint16_t iopb;
} tss_t;
static tss_t the_tss __attribute__((aligned(16)));

/* ---- IDT ---- */
typedef struct __attribute__((packed)) {
    uint16_t off_lo; uint16_t sel; uint8_t ist; uint8_t type_attr;
    uint16_t off_mid; uint32_t off_hi; uint32_t zero;
} idt_entry_t;
static idt_entry_t idt[256] __attribute__((aligned(16)));
typedef struct __attribute__((packed)) { uint16_t limit; uint64_t base; } idtr_t;

extern void *isr_stub_table[];

/* ---- Kernel stack pool ---- */
static char kstack_pool[MAX_PROCS][16*1024] __attribute__((aligned(16)));
static int kstack_idx;

static uint64_t alloc_kstack(void) {
    if (kstack_idx >= MAX_PROCS) return 0;
    return (uint64_t)&kstack_pool[kstack_idx++][16*1024];
}

/* ---- Trap frame (must match isr_stubs.S) ---- */
typedef struct {
    uint64_t rax, rbx, rcx, rdx, rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
    uint64_t rip, cs, rflags, rsp, ss;
    uint64_t vector, errcode;
} trap_frame_t;

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
    static idtr_t idtr;
    idtr.limit = sizeof(idt) - 1;
    idtr.base = (uint64_t)&idt;
    __asm__ volatile("lidt %0" :: "m"(idtr));
}

/* ---- PIC ---- */
static void pic_init(void) {
    outb(0x20,0x11); outb(0xA0,0x11);
    outb(0x21,0x20); outb(0xA1,0x28);
    outb(0x21,0x04); outb(0xA1,0x02);
    outb(0x21,0x01); outb(0xA1,0x01);
    /* Master: unmask IRQ0 (timer) + IRQ1 (keyboard) + IRQ2 (cascade). */
    outb(0x21,0xF8);
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

/* ---- TSS + GDT expansion ---- */
static uint8_t tss_gdtr_buf[10] __attribute__((aligned(2)));

static void tss_init(void) {
    kmemset(&the_tss, 0, sizeof(the_tss));
    the_tss.rsp0 = MY_SYS_KSTK_TOP;
    the_tss.iopb = sizeof(the_tss);

    uint64_t base = (uint64_t)&the_tss;
    uint32_t limit = sizeof(the_tss) - 1;
    uint8_t *gdt = (uint8_t *)GDT64_ADDR;

    /* TSS descriptor at GDT slot 5 (offset 0x28), 16 bytes.
     * Access 0x89: Present=1, DPL=0, S=0, Type=9 (available 64-bit TSS).
     * Flags 0x00: all reserved bits zero for TSS. */
    uint64_t lo = (uint64_t)(limit & 0xFFFF)
        | (((uint64_t)(base & 0xFFFFFF)) << 16)
        | (0x89ULL << 40)
        | (((uint64_t)(limit >> 16)) << 48);
    uint64_t hi = (uint64_t)(base >> 32);
    *(uint64_t *)(gdt + 40) = lo;
    *(uint64_t *)(gdt + 48) = hi;

    /* Pack GDTR manually: limit(16 LE) + base(64 LE) */
    uint16_t gdtr_lim = 7 * 8 - 1;
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

/* ---- C dispatch from isr_common ---- */
void isr_dispatch(int vector, trap_frame_t *frame) {
    if (vector == 32) {
        sys_ticks++;
        pic_eoi(0);
        if (proc_count > 1) {
            proc_t *cur = proc_get(current_pid);
            if (cur && cur->state == PROC_RUNNING) {
                cur->ctx.rax = frame->rax;
                cur->ctx.rbx = frame->rbx;
                cur->ctx.rcx = frame->rcx;
                cur->ctx.rdx = frame->rdx;
                cur->ctx.rsi = frame->rsi;
                cur->ctx.rdi = frame->rdi;
                cur->ctx.rbp = frame->rbp;
                cur->ctx.r8  = frame->r8;
                cur->ctx.r9  = frame->r9;
                cur->ctx.r10 = frame->r10;
                cur->ctx.r11 = frame->r11;
                cur->ctx.r12 = frame->r12;
                cur->ctx.r13 = frame->r13;
                cur->ctx.r14 = frame->r14;
                cur->ctx.r15 = frame->r15;
                cur->ctx.rip = frame->rip;
                cur->ctx.rflags = frame->rflags;
                unsigned long ksp;
                __asm__ volatile("mov %%rsp, %0" : "=r"(ksp));
                cur->ctx.rsp = ksp;
                cur->state = PROC_READY;
                int next = current_pid;
                int t;
                for (t = 0; t < MAX_PROCS; t++) {
                    next = (next + 1) % MAX_PROCS;
                    if (procs[next].state == PROC_READY) break;
                }
                if (t < MAX_PROCS && next != current_pid) {
                    proc_t *nxt = proc_get(next);
                    current_pid = next;
                    nxt->state = PROC_RUNNING;
                    switch_to(cur, nxt);
                }
            }
        } else if (user_program_active && (sys_ticks % DESKTOP_TICK_INTERVAL) == 0) {
            vga_fb_mouse_tick();
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
    if (vector >= 32 && vector < 48) { pic_eoi(vector - 32); return; }
    if (vector < 32) {
        kprintf("EXCEPTION %ld err=%ld rip=%lx rsp=%lx\n",
                (long)frame->vector, (long)frame->errcode,
                (unsigned long)frame->rip, (unsigned long)frame->rsp);
        kprintf("  rax=%lx rbx=%lx rcx=%lx rdx=%lx\n",
                (unsigned long)frame->rax, (unsigned long)frame->rbx,
                (unsigned long)frame->rcx, (unsigned long)frame->rdx);
        kprintf("  rsi=%lx rdi=%lx rbp=%lx r8=%lx r9=%lx\n",
                (unsigned long)frame->rsi, (unsigned long)frame->rdi,
                (unsigned long)frame->rbp, (unsigned long)frame->r8,
                (unsigned long)frame->r9);
        kprintf("  r10=%lx r11=%lx r12=%lx r13=%lx r14=%lx r15=%lx\n",
                (unsigned long)frame->r10, (unsigned long)frame->r11,
                (unsigned long)frame->r12, (unsigned long)frame->r13,
                (unsigned long)frame->r14, (unsigned long)frame->r15);
        unsigned char *code = (unsigned char *)(unsigned long)frame->rip;
        kprintf("  [%lx]: ", (unsigned long)frame->rip);
        for (int _i = 0; _i < 16; _i++) kprintf("%02x ", code[_i]);
        kprintf("\n");
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
    int pid;
    for (pid = 1; pid < MAX_PROCS; pid++)
        if (procs[pid].state == PROC_FREE) break;
    if (pid >= MAX_PROCS) return -1;

    proc_t *p = &procs[pid];
    kmemset(p, 0, sizeof(proc_t));
    p->pid = pid;
    p->state = PROC_READY;
    p->parent_pid = parent_pid;
    kstrncpy(p->name, name, sizeof(p->name) - 1);

    uint64_t kstack_top = alloc_kstack();
    if (!kstack_top) return -1;
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
    p->ctx.cr3 = read_cr3();
    p->ctx.rflags = 0x200;

    if (proc_count <= pid) proc_count = pid + 1;
    return pid;
}

void schedule(void) {
    int next = current_pid;
    int t;
    for (t = 0; t < MAX_PROCS; t++) {
        next = (next + 1) % MAX_PROCS;
        if (procs[next].state == PROC_READY) break;
    }
    if (t >= MAX_PROCS) return;
    if (next == current_pid) return;
    proc_t *cur = proc_get(current_pid);
    proc_t *nxt = proc_get(next);
    if (!cur || !nxt) return;
    current_pid = next;
    nxt->state = PROC_RUNNING;
    switch_to(cur, nxt);
}

void yield(void) {
    proc_t *cur = proc_get(current_pid);
    if (cur) { cur->state = PROC_READY; schedule(); }
}

void do_exit(int code) {
    proc_t *cur = proc_get(current_pid);
    if (!cur) return;
    cur->exit_code = code;
    cur->state = PROC_ZOMBIE;
    if (cur->parent_pid >= 0) {
        proc_t *parent = proc_get(cur->parent_pid);
        if (parent && parent->state == PROC_BLOCKED)
            parent->state = PROC_READY;
    }
    schedule();
}

int do_waitpid(int pid) {
    proc_t *cur = proc_get(current_pid);
    if (!cur) return -1;
    for (;;) {
        int i;
        for (i = 0; i < MAX_PROCS; i++) {
            if (procs[i].state != PROC_FREE
                && procs[i].parent_pid == current_pid
                && procs[i].state == PROC_ZOMBIE) {
                int code = procs[i].exit_code;
                procs[i].state = PROC_FREE;
                return code;
            }
        }
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

void timer_tick(void) { sys_ticks++; }

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

    /* Reset mouse, drain any stale data */
    mouse_write(0xFF);
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
    kmemset(procs, 0, sizeof(procs));
    proc_count = 1;
    current_pid = 0;
    procs[0].pid = 0;
    procs[0].state = PROC_RUNNING;
    procs[0].parent_pid = -1;
    kstrcpy(procs[0].name, "kernel");
    procs[0].ctx.cr3 = read_cr3();

    pic_init();
    pit_init();
    mouse_hw_init();
    tss_init();
    idt_init();
    __asm__ volatile("sti");
}
