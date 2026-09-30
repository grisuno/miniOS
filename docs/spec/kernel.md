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
