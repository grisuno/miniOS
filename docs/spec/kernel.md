# Kernel contracts: ABI layout, loaders, stacks, sanitization, spawn, isolation

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## Kernel Contracts

### Single source of truth for the memory layout (`progs/minios_abi.h`)
The user-window layout — load base, stack, brk cap, the graphics back-buffers,
the linear framebuffer and the kernel heap — is defined **once** in
`progs/minios_abi.h`, the header shared by the kernel and every ring-3 program.
The kernel derives its own constants from it (`kernel.h` -> `kernel.c`
`USER_LOAD_*`/`USER_STACK_*`/`HEAP_*`, `vga_fb.h` `FB_ADDR`/`DOOM_BACKBUF_ADDR`/
`NK_BACKBUF_ADDR`, `sched.c`), so growing the window or moving a back-buffer is
a one-line edit in one file instead of a cross-file address hunt. This is the
direct fix for the historical bug where moving an address (DOOM's back-buffer
`0x7C00000 -> 0x0B000000`, the user-window growth) left a consumer writing the
old value and silently breaking. Belt and suspenders: `_Static_assert`s in
`kernel.c` prove the kernel's values equal the ABI header, the asm-safe
`SYSCALL_*` numerics in `headers/syscall_asm.h` are asserted the same way,
and `kernel.ld` carries machine-checked `_user_win_lo/hi` mirrors plus a
link-time `ASSERT` fenced by the `check-size` gate. **Rule: never
hardcode a layout address in the kernel or a ring-3 program; put it in
`minios_abi.h`.** The scheduler's old local `MY_USER_STACK_TOP` (`0x07400000`)
is gone — it went stale when the window grew and would have stacked a scheduled
process in the middle of the heap.

### Ramdisk
The data area is sized from the image that is loaded plus a spare margin, and
grows on demand up to `RD_DATA_MAX`; it is never a fixed reservation that the
payload can silently outgrow. `ramdisk_setup_from` validates the whole image
(header, table extent, per-file offset and size, total against the maximum)
**before** publishing any entry, so a rejected image leaves the directory
untouched instead of advertising files whose data was never copied.

### ELF loaders
Relocation is fail-closed. Every relocation is bounds checked against the
section it patches; a relocation symbol index outside the symbol table, an
unsupported relocation type, or a symbol that the kernel cannot resolve
aborts the load with a diagnostic. An unapplied relocation would hand the
program a wild call target, so it is never skipped. No libc name is ever
registered with a null address. Section header arithmetic uses the
overflow-safe pattern `sh_offset > size || sh_size > size - sh_offset` to
prevent unsigned wrap from bypassing the bounds check.

### CVM modules (`.cvm`) argv contract
A CVM v2 module runs with a Linux-style argv: `run <file>.cvm [args...]`
passes the module path as `argv[0]` and the remaining words as `argv[1..]`,
so the startup code every `ld -f cvm` module carries reads `argc` and
`argv` exactly as on real hardware, and a program like
`run minigcc.cvm test.c` works without extra ceremony. The data section is
laid out so that argument passing can never corrupt module data: globals,
string blobs and extern slots precede the x86 stack region, `ld` stores the
region's offset and size in the module ABI area, and the interpreter reads
those values at run time (older modules without the stored offset fall back
to the fixed layout). `cvm_set_args` copies the argument strings into the
module heap and builds the argv pointer array in the reserved area above the
stack region; a module whose layout cannot hold the argument list is
rejected with a diagnostic, never silently corrupted.

### Integer overflow protection
`kfread` and `kfwrite` compute `size * n` before accessing the buffer.
A ring-3 program passing `size=0xFFFFFFFF, n=2` would cause the product
to wrap to `0xFFFFFFFE`, smaller than the intended allocation, bypassing
the `bytes > RD_DATA_MAX` check. Both functions now reject the call when
`n != 0 && size > ULONG_MAX / n`, returning 0 before any buffer access.
The early-return also covers `size == 0` and `n == 0`, which the old code
handled implicitly through division-by-zero or zero-length loops.

### Stack setup bounds checking
`setup_user_stack` writes argv strings downward from the stack top. Without
a bounds check, a program with many large argv entries could write below
`sbase` and corrupt kernel memory before the user window. Each iteration now
checks `l > (p - sbase)` and returns NULL on overflow. `k_exec_user` checks
the return value and refuses to enter ring 3 with a NULL stack pointer.

### Kernel stack discipline (read before adding ANY kernel local)
Ring-3 syscalls run on per-proc 16 KB slots (`KSTACK_SZ` in
`kernel/sched.c`, 64 slots = 1 MB of `.bss`). A chain like
`write_inode -> journal_touch -> journal_save_entries` nested three 4 KB
stack frames plus the syscall frames and overflowed the slot, smashing a
return into a ring-0 `#UD` (`EXCEPTION 6, rip=0x3`, measured on
`lua -> lua -> /bin/cp` with a MiniFS write). The shell never caught it
because the shell runs on its own generous boot stack — only isolated
procs died, which is why single-level shell tests stayed green while
nested execution (file browser -> vedit -> toolchain) crashed. The
16 KB size is NOT negotiable upward: the pool already costs 1 MB of
`.bss` and `_kernel_end` sits ~47 KB below `USER_LOAD_BASE`, so doubling
the slots does not fit the image budget. Chunking was never the problem:
the block layer always moved in `MINIFS_BLOCK_SIZE` units correctly; the
bug was *where the scratch lived* (stack vs heap), not its size.

Rules, enforced by the build, not by review:

1. No kernel function holds a stack frame larger than 2 KB.
   `CFLAGS_KERN` carries `-Werror=frame-larger-than=2048`, so a violator
   fails `make` outright. The limit leaves room for ~6 nested frames
   plus ISR nesting inside one 16 KB slot.
2. Block-sized scratch is heap, fail-closed on OOM. The pattern is
   `blk_new`/`blk_free` in `fs/minifs.c` (every runtime MiniFS helper),
   heap query/reply buffers in `net/net.c` (`net_dns_resolve`,
   `net_icmp_rx`), a heap hash table in `LZ4_compress_default` (16 KB —
   OOM degrades to storing uncompressed, the existing fail-closed path),
   and heap snapshots in `schedtop_report`/`ps`/`ls`/`minifetch`.
3. Exemptions are named, scoped and boring: `minifs_mount`/`minifs_mkfs`
   keep stack scratch (boot-time only, deep stacks) via a `#pragma GCC
   diagnostic` pair each, and `shell_exec_builtin` is exempt because it
   runs only on the shell's boot stack (no syscall path reaches it; -Os
   inlines single-use helpers into its frame). Pristine upstream
   (`CFLAGS_UPSTREAM`: xxhash, stb, miniz, dlmalloc) warns at 32 KB
   instead — never rewritten for the gate; their entry points run on
   generous stacks (boot/selftest/ring-3 decode), never on proc slots.
   A new exemption needs the same proof (which generous stack, why no
   syscall path), never "it is only a little over".
4. Verify with depth, not with single-level tests: the repro is a
   two-level nested spawn doing a real MiniFS write (lua -> lua -> cp),
   plus the toolchain chain and a background writer. `kstack` reports
   high-water marks and dead canaries (`kstack: ok` is BDD-pinned), but
   it only observes — the gate above is what prevents.

Adopted strategies if pressure returns: heap kstacks per proc (192 MB
heap, frees the 1 MB `.bss` pool entirely, needs leak-proof free on
every exit path), fewer slots than procs (caps live procs), guard pages
between slots (needs 4 KB paging work in the identity map first). In
that order; none scheduled while the gate holds.

### Syscall argument sanitization (`sanitize.h`)
Every MiniOS handler takes user pointers only through the `SANITIZE_*`
macros (range, string, non-negative length, and copy-in with an explicit
count-by-size wrap check), which all fail closed with `EFAULT` (-14). The
audit that motivated them found five handlers returning `-EFAULT` (+14,
which userland reads as success) and open-coded multiplications a hostile
count could wrap past the range check; both classes are gone where the
macros apply. `SANITIZE_COPY_IN` copies into kernel memory before use, so
userland cannot mutate an array between validation and execution (no
TOCTOU). The macros name only `user_range_ok`/`user_str_ok`/`kmemcpy`/
`EFAULT` and are host-tested (`make test-sanitize`, mutation-covered);
`grep SANITIZE_` lists every sanitized entry point. `tools/check_syscall_sanitize.py`
gates the whole discipline in `make lint`: every pointer alias of a1..a6 must be
checked in its own case-block and every raw arg reaching a dereferencing callee
(`futex_wait`, `net_sys_*`, `do_clone`) must be boundary-checked; callees that
sanitize internally (`k_syscall_spawn`, `do_open_path`) stay delegated. The sweep
hardened `sys_minios_clone` (`newsp` now `EFAULT` unless 0-inherit or in-window).
Boundary rule:
sanitize at the boundary, trust internally. `writev` copies the iovec
array into kernel memory before iterating it, so userland cannot mutate
an entry between its range check and its use. Region-typed validation (heap
vs stack vs mmap) is deliberately deferred: the VMA tree tracks mmap
regions only, and futex/batch words legitimately live in any writable
region, so a single-type check would need a region-mask redesign plus
tagging at load/brk/stack setup first. Mechanism lesson, not incident:
a disabled check is a live vulnerability even when the suite is green —
`SANITIZE_COPY_IN` with its negative and wrap checks replaced by `if (0)`
segfaults the host suite instead of passing it, which is how a committed
mutant in this file was caught and reverted; never commit with a red
`make test-sanitize`.

### mprotect enforcement (`sys_linux_mprotect`, syscall 10)
The old stub returned 0 without touching a bit, so every caller believed
its pages were protected. The handler toggles RW/NX per page in the
caller's live tables (syscall entry keeps the caller CR3 loaded) with a
local invlpg each, the cow_resolve precedent, no cross-CPU shootdown
yet. Two passes under mm_lock (validate all, then apply): unaligned
base and unknown prot bits are -EINVAL, anything outside the user
window, unmapped, non-user, phys-less or CoW-shared is -ENOMEM with
nothing applied. A write to a cleared page falls through cow_resolve
into the kill path exactly like nx. Two documented deviations:
PROT_NONE stays present (denies write+exec, reads still succeed)
because the reaper only frees present data pages, and CoW-shared pages
refuse (upgrading them in place would write another window's bytes
past cow_resolve). Pin: `run bin/mprot.elf` (legs, R|X exec, faulting
write) plus `mprotect-*` mutants under `MATCH="mprotect"`.

### Anonymous memory: demand paging, `munmap`, address-space views
Static glibc reserves big anonymous regions it may never touch: a 64 MB
`PROT_NONE` region per thread malloc arena, opened up step by step with
`mprotect`, and an 8 MB thread stack. Backing them eagerly from the 192 MB
kernel heap exhausted it after a few threads (FreeDom runs many), so:

- **Reservation, not allocation.** `mmap` of an anonymous range writes
  non-present PTEs carrying `PTE_DEMAND` plus the requested protection in
  software bits the MMU ignores while the present bit is clear
  (`PTE_DEMAND_READ/WRITE/EXEC`, bits 8-11; bits 0-1 stay clear, so every
  "present" test reads them as absent). `mprotect` on a reservation rewrites
  the marker and commits nothing.
- **First touch.** The not-present fault path resolves a reservation before
  trying a file mapping (`mm_anon_fault`): a zeroed page with the reserved
  protection, from ring 3 or from a kernel copy into a user buffer.
  `PROT_NONE` and writes to read-only reservations stay faults (the thread
  stack guard page works).
- **Fresh mappings read zero.** A page still present in a reused range is a
  leftover of an earlier mapping: a copy-on-write share is dropped for a
  reservation, any other frame is zeroed in place (glibc's `calloc` skips
  clearing fresh mmap chunks, as Linux guarantees zero).
- **`munmap` (11)** removes the overlap with every mapping in the range, head,
  tail, middle or whole: survivors stay live with their file offsets, only
  the unmapped pages are released (heap frames freed, or unshared when a
  fork sibling still maps them; fixed frames of the pid-0 window stay), and
  the range returns to the free tree. Unmapping a hole is not an error; an
  unaligned base, zero length or range outside the window is `-EINVAL`.
  `mremap` releases the anonymous pages of every range it gives back.
- **fork** copies reservations into the child (`cow_copy_demand`).
- **Address-space views.** `g_brk`, `user_mmap_cur` and the VMA roots are
  global and describe one address space at a time. `mm_view_enter` runs on
  every way a task starts running (switch, timer preemption, the idle loop
  claiming a task after the running process died): a task of the address
  space already held keeps the view, any other saves it into its holder and
  loads its owner's (`mm_owner`: the non-`CLONE_VM` process sharing the
  thread's VMA context; legacy-window threads belong to pid 0). Without it
  a thread scheduled right after an unrelated process, or a parent resumed
  from idle after its child died, allocated from someone else's view and
  the next fork refused to copy the corrupted tree.
- **Heap budget.** The kernel heap backs every user page and page table;
  pages come from `kmalloc_page` (dlmalloc `memalign`, one page plus a chunk
  header; the old align-by-overallocation cost two pages per page) and an
  ownership bitmap marks which heap frames the page allocator owns, so only
  those are ever freed as pages. A failed allocation is reported on the
  serial line (`kheap: allocation of N bytes failed`) where it happens.
- **Copy-on-write table.** Open addressing over the frame number, 65536
  entries (heap, created on the first fork), tombstones on delete, reset
  when empty and rehashed when tombstones pile up. The old 512-entry table
  made fork copy every page past the 512th eagerly, so forking a 100 MB
  browser duplicated it before the child could exec.
- **VMA nodes** are recycled through a spare chain (deleted nodes are handed
  out again before the pool grows), and the one-entry lookup cache only
  answers for the tree that filled it (live and free trees share it; a
  free-tree delete could otherwise unlink a live node). `mmap` refuses and
  reports any range that would overlap a live mapping or the brk heap.
- **Flight recorder.** Each process keeps its last 32 syscalls (number,
  three arguments, result) with no I/O; the exception dump prints the
  faulting process's log and `sclog <pid>` prints any process's, live or
  exited. `ps` shows exit codes of finished processes.
- **Kernel stacks.** `alloc_kstack` never hands out a slot a live process
  still references (its stack or its open syscall's entry stack), and
  reports the stale reference; the exception dump lists every slot with its
  owner and high-water mark and flags a dead canary. Each `fork` failure
  names the exhausted resource.

### Spawn contract (`spawn.h` + `kernel/spawn.c`)
`k_syscall_spawn` is a ~30-line thin wrapper: validate, copy argv,
resolve, snapshot, `spawn_backup`, `spawn_execute`, release,
`spawn_restore`. The context struct carries only scalars plus VMA roots;
the pool copy lives in a file-static array because `VMA_MAX` nodes do not
fit any kernel stack. `spawn_execute` runs ET_REL through the ring-0
loader behind the `objects/` trust gate and ET_EXEC/ET_DYN through the
isolated `proc_spawn_elf` window. Backup/restore are symmetric by
construction; the `procs[0].kstack` save is unconditional because an
ET_REL child exits through `klongjmp` past the entry write-back.

An ET_REL child never runs on the caller's kernel stack: `k_run_rel`
(`kernel/exec.c`) switches to a dedicated 256 KB heap stack through
`k_run_on_stack` (`arch/x86/ctx_sw.S`) and frees it on either return
path (normal return or `kexit` longjmp, whose setjmp sits on the
caller stack with intact frames). The reasons are measured, not
assumed: a SYS_SPAWN arriving from an isolated window runs on that
process's 16 KB pool slot, and minigcc carries a 66 KB single frame
in `parse_function`, so the slot overflowed into whatever the pool
abuts -- observed as a silently lost MiniFS mount with no crash
(file browser -> vedit -> Ctrl+R killed every later MiniFS access).
OOM keeps the historical caller-stack behavior, fail-closed never
applies here because refusing the spawn would break the IDE build
key. The child entry is delivered with rsp%16==8, the de facto
convention of the legacy spawn path (which tail-calls into it) that
the sibling-built toolchain objects require: minigcc's
`parse_function` faults its SIMD spills on a normalized rsp%16==0
(proven: E=0 breaks fib.c with #GP, E=8 fixes it; all five in-tree
ET_REL objects pass the gate under E=8). A future ET_REL built for
strict SysV E=0 with its own SIMD spills would break the other way;
that conflict is resolved in the toolchain repos, never by silently
changing E here.

### Bump arenas and leak tracking (`headers/arena.h`, `headers/leakcheck.h`)
Per-keypress churn is scoped, never counted: `spawn_copy_argv` serves
the pointer vector plus every argv word from one kmalloc through a
bump arena (`spawn_free_argv` is a single kfree), so a Ctrl+R / Ctrl+L
spawn costs one heap block instead of argc+1 round trips. The redirect
capture is a persistent bump buffer by the same logic (16 KB seed,
doubling to 16 MB, length rewound on begin/commit/take/discard, block
never freed), and `redirect_take_into` / `redirect_pending` /
`redirect_discard` let the shell pipeline stage assemble its output
with one kmalloc instead of three while fixing the discarded
`redirect_take(0)` block on the oversize path. `kfwrite` keeps the
pre-grow capacity when `krealloc` fails instead of installing the null
and orphaning the old write buffer. The leak tracker is the
long-pasted `stb_leakcheck` finally wired in as `headers/leakcheck.h`
with a hosted backend (malloc/free, stdout) and a kernel backend
(kmalloc/kfree, kprintf), unknown-pointer-tolerant frees, and
`lk_live_count` baselines; the kernel never overrides its allocator
globally (permanent caches would drown the report), ring-3 file and
vedit compile with `MINIOS_LK_ENABLE` and assert a drained live set in
their selftests. Host pins: `make test-arena test-leakcheck`.

### Audio Strategy (`driver.h` + `drivers/sb16.c`)
The PCM sink joins the tone sink in the device registry: `audio_ops_t`
carries `present`/`pcm_open`/`pcm_close`/`pcm_submit` beside the tone
verbs, `sb160` registers on successful DSP probe (absent device is
fail-closed: open reports 0, submit refuses -1), and the syscall layer
dispatches through `device_find`, never by direct call. The pump and the
mixer streams stay direct: the pump runs in ISR context and the streams
are per-id mixer state, not device verbs. Host proof is `make
test-driver`, which now covers tone-only vs PCM device dispatch.

### Modifier contract (`drivers/modifiers.h`)
One `modifier_state_t` serves the cooked and raw keyboard paths through
`modifiers_update` (single consumer of every make/break edge) and
`wm_combo_lookup_mods` (single entry into the shared `WM_COMBOS` table),
host-tested by `make test-modifiers`. The old parallel tracking in
`raw_track_mods` and the cooked break/make blocks is gone; behavior is
unchanged because real hardware never E0-prefixes Shift/Ctrl/Alt.
Cursor visibility is structural: the arrow paints white over a 1-px
black outline (`COL_BLACK`), so it reads on the white paint canvas and
on dark terminals alike.

### User-mode isolation
ET_EXEC / ET_DYN binaries run at ring 3 under hardware page protection;
ET_REL objects (the toolchain) remain ring-0 kernel extensions by contract,
because they are linked against the kernel symbol table. The boot path
installs user code/data segments (`GDT64_USER_CODE_SEL` 0x20, `GDT64_USER_DATA_SEL`
0x18, DPL 3) beside the kernel segments and the kernel marks the user window
`USER_LOAD_BASE`..`USER_LOAD_END` as user-accessible (`PT_FLAGS_USER`). Every
other page — page tables, kernel image, kernel heap, VGA, MMIO — stays
supervisor, so a user binary cannot read or write kernel memory: the U/S bit
stops it in hardware. Identity mapping remains a single address space: per-
process page tables (CR3 switch) belong to the preemption track, not this one.

The user window runs on eager 4 KB page tables for the whole
`USER_LOAD_BASE`..`USER_LOAD_END` range (`mm_setup_protections`), not on the
2 MB kernel pages, so the no-execute bit works: every user page starts
NX-clear (EFER.NXE is enabled), and `load_exec_elf` clears NX only on the
pages a program's executable segments occupy. A program cannot execute from
its stack, heap, `.data` or unmapped space — a jump into a non-executable
page faults and the machine resets (no IDT), never silently running
shellcode. The kernel heap keeps its 2 MB executable pages: `.o` toolchain
programs execute from the heap at ring 0 by contract. The page tables live
in the dedicated identity-mapped zone `PT_USER_TABLES_ADDR` (`0x10000`),
below the kernel image and never in the kernel heap, so neither the ramdisk
data buffer nor kernel `.bss` growth can ever clobber them.
The BDD suite proves the isolation with `cpl.elf` (reports ring 3),
`kmem.elf` (kernel pointers rejected) and `nx.elf` (a `ret` written to the
stack faults on fetch, so `poweroff` is never reached).

### FSBASE rides every switch, pid 0 included (`arch/x86/ctx_sw.S`)
The switch saves `%fs` base into the outgoing PCB unconditionally and
restores the incoming one, with one exception left standing: the AP
idle loop (no user state to restore). The old pid-0 restore skip
assumed pid 0 never runs TLS code, but `k_exec_user` runs glibc
programs in the shared window, so every switch-back handed them the
preemptor's base: `file.elf` faulted inside malloc with wlcomp up,
deterministically, while text-mode runs (no TLS competitor) stayed
green. Fresh spawns stay safe (PCB and MSR zeroed together at exec),
fork inherits the live base, and `arch_prctl` needs no PCB write (the
outgoing save heals the slot before any switch-in can read it). Pin:
`desktop` + `run bin/file.elf --selftest` expecting `file: leak ok`,
plus the `fsbase-restore-corrupted` mutant under `MATCH="glibc TLS"`.

### errno for the miniGCC ABI (T10)
miniGCC predefines `errno` as an extern global (`libc_global_name`),
so any toolchain program naming it emits a reference the link chain
must resolve. Two worlds, like `stdout` before it: `ld -f elf` links
an `errno` cell from its stub layer (`ELF_STUBS_SRC`, sibling `ld`
repo) and its open/read/write/malloc stubs store the negated syscall
code without changing their returns, so in-guest toolchain programs
read real POSIX codes; ET_REL `.o` programs resolve the kernel
`"errno"` cell (`kerrno`, registered beside stdin) with codes set at
the KFILE boundary (ENOENT/EIO/EBADF/ENOMEM/EFBIG/ESPIPE/ENAMETOOLONG,
set-on-failure-only; glibc ELFs keep their own `%fs` errno and never
touch it). One global cell is correct today (single shared ET_REL
window, no miniGCC threads); per-thread moves with miniGCC threads,
never before. CVM stays out (its natives live in another sibling).
Pin: in-guest minigcc→ld→run probe (`errno: 2` after a failed open),
`run objects/ftest.o` (`ftest: errno=2`), plus `errno-*` mutants
under `MATCH="errno"`.

Every legacy `run` clones those tables with `pt_clone_user` and frees the
clone with `pt_free_user` on return. The graphics pass (framebuffer plus
DOOM/Nuklear/RGB slots) installs a second private PT per slot on top of
the main loop's copy: it must release the replaced table first, or every
legacy run leaks one page per graphics slot (measured 40 KB/run, heap
never returning, fragmenting the arena until big contiguous allocs fail
far from the cause — the shape of the post-minicraft "desmontado"
incident). Proven by `mem` before/after two `run bin/fib.elf` (5534K flat
after the fix, +40KB per run before); DOOM still composites 60/60 frames
after it, so the installed mappings are unchanged.

A user program is entered with `iretq` to ring 3 (CS `USER_CODE_SEL`, SS
`USER_DATA_SEL`, RPL 3) on a user stack carved from the top of the user
window (`USER_STACK_BASE`..`USER_STACK_TOP`). The program break is bounded
below that stack (`USER_BRK_END`) and anonymous `mmap` allocations are carved
from the same window, so every address a user program can obtain is a user
page. Syscalls switch to a dedicated kernel stack (`syscall_kstack`, exchanged
on entry, `SYS_KSTK_TOP`) and return with `sysretq`, so the kernel never runs
on a user stack and never touches the user red zone. The return path
discriminates on the caller RIP, never on RSP: RSP is attacker-settable
without faulting while RIP is constrained to executable mappings, so an
`RSP=0` spoof takes the `sysretq` path instead of retaining CPL0 through
`jmp *%rcx` (ring-0 ET_REL callers trap from heap code and keep the `jmp`
return). The entry range-checks the pid (`jae 98f`, fail closed with
`-EFAULT` touching no memory), so a corrupt `cur_pid` can neither index
`sc_top_save` out of bounds nor swap onto a wild kstack. The exit path
(`klongjmp` back to the shell) restores the kernel data segments and resets
the syscall kernel stack for the next program.

The syscall dispatcher is the hardened boundary. Every pointer argument is
validated to lie inside the user window before it is dereferenced (`write`,
`read`, `writev` buffers, `open` paths, `poll` fd arrays, socket `sockaddr`s
and payload buffers, `clock_gettime` timespec, DNS hostnames, TLS buffers);
string arguments must be NUL-terminated inside the window; a violating call
returns `-EFAULT`. `arch_prctl` accepts only canonical bases. Faulting user
code still resets the machine (no IDT): interrupt delivery, fault handlers
and a scheduler are the preemption track, not part of this contract.

### Linux seccomp-bpf, prctl and `/proc/self/exe` (FreeDom readiness, step 5)
The full FreeDom GUI re-execs itself as a tab worker
(`execve("/proc/self/exe", ["freedom", "--tab-worker", r, w])`) and the
worker refuses to touch content unless it can install a seccomp-bpf
allowlist (`prctl(PR_SET_NO_NEW_PRIVS)` then `prctl(PR_SET_SECCOMP,
SECCOMP_MODE_FILTER, &prog)`): fail closed. MiniOS answers that contract the
Linux way. Pinned by `progs/src/lxsecc.c` (`mrun bin/lxsecc`, one `lxsecc:
<check> ok` line per point, `lxsecc: all ok`, exit 0) and its BDD scenario,
plus `make test-seccomp-bpf` for the interpreter.

- **Classic BPF interpreter (`kernel/seccomp_bpf.c`, `headers/seccomp_bpf.h`).**
  Pure (no kernel state), host-tested. `sbpf_check` validates a program
  before it is ever run, exactly the classic rules Linux applies: 1..4096
  instructions; only the classic opcodes (`LD`/`LDX` W ABS on the 64-byte
  `seccomp_data` at 4-byte-aligned offsets, `LD`/`LDX` IMM and MEM, `ST`/`STX`
  on the 16 scratch words, every `ALU` op with K or X except a constant zero
  divisor or modulus, `JA`/`JEQ`/`JGT`/`JGE`/`JSET` with K or X, `RET` K or
  A, `TAX`/`TXA`); every jump lands inside the program, forward only; the
  last instruction is a `RET`. `sbpf_run` executes a checked program over a
  `seccomp_data` (`nr`, `arch`, `instruction_pointer`, `args[6]`) and
  returns the 32-bit action; a runtime division by a zero `X` returns
  `SECCOMP_RET_KILL_PROCESS` (fail closed), every load is in bounds by
  construction.
- **Filters.** Installed per process, inherited by `fork`, `clone` threads
  and kept across `execve`, stacked like Linux (a new filter runs in front of
  the inherited ones; every filter runs and the most restrictive action
  wins: KILL_PROCESS, KILL_THREAD, TRAP, ERRNO, USER_NOTIF, TRACE, LOG,
  ALLOW). At most `SECCOMP_FILTERS_MAX` stacked filters and
  `SBPF_MAX_INSNS` instructions each. Evaluated at the top of every syscall
  of a filtered process, before any other dispatch, with `arch =
  AUDIT_ARCH_X86_64` and the caller's rip:
  - ALLOW and LOG run the syscall;
  - ERRNO answers `-(data & 0xfff)` (capped at 4095) without running it;
  - TRACE and USER_NOTIF answer `-ENOSYS` (there is no tracer or listener);
  - KILL_THREAD kills the calling thread, KILL_PROCESS and TRAP (no signal
    delivery) kill the whole thread group as a death by SIGSYS: exit code
    `-31` in MiniOS terms, `WIFSIGNALED` with `WTERMSIG == SIGSYS` through
    `wait4`.
- **`prctl` (157).** `PR_SET_NO_NEW_PRIVS` (only `1`, unused args 0, sticky
  and inherited), `PR_GET_NO_NEW_PRIVS`, `PR_SET_DUMPABLE` (0 or 1) and
  `PR_GET_DUMPABLE` (MiniOS writes no core files, the flag is recorded),
  `PR_SET_NAME`/`PR_GET_NAME` (16 bytes, the process name `schedtop` shows),
  `PR_SET_SECCOMP` (`SECCOMP_MODE_FILTER` with a `sock_fprog`;
  `SECCOMP_MODE_STRICT` installs the read/write/exit/sigreturn filter) and
  `PR_GET_SECCOMP`. Installing a filter without no_new_privs is `-EACCES`
  (MiniOS has no capabilities to waive it). Anything else `-EINVAL`.
- **`seccomp` (317).** `SECCOMP_SET_MODE_STRICT`, `SECCOMP_SET_MODE_FILTER`
  (flags 0) and `SECCOMP_GET_ACTION_AVAIL`, same rules as the prctl path.
- **`/proc/self/exe`.** Every process records the resolved path of the image
  it runs (spawn, foreground run, `execve`), inherited by fork and clone.
  `execve` of `/proc/self/exe` runs that path; `readlink` of
  `/proc/self/exe` answers it (no NUL, truncated to the buffer like Linux).
- **Best-effort isolation answers.** `unshare` (272) and the Landlock calls
  (444-446) answer `-ENOSYS` without the UNIMPL trace: FreeDom treats both as
  defense in depth and keeps seccomp as the mandatory boundary.
