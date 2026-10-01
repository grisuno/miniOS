# Architectural abstractions, session records and the improvement plan

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## Architectural Abstractions

### VFS (Virtual File System)
A registration-based filesystem dispatch layer (implementation in kernel.c).
Filesystem drivers register a prefix and a set of operations (`vfs_ops_t`).
The VFS layer dispatches open/read/write to the registered driver based on
path prefix matching.  Four drivers are registered at boot: ramdisk
(always available), MiniFS (when the IDE disk mounts), `fat:` and
`ext4:` (per-open `imgpath:inpath` addressing, so one registration
serves every image and partition). Both disk drivers ride the shared
`fs/fsimg.c` backend (loopback file or absolute disk region, every
offset fenced). The KFILE struct carries a `vfs_file_t *vfs` pointer
for future VFS-backed dispatch; the existing direct ramdisk/MiniFS
paths remain for backward compatibility. New filesystem additions
register a prefix and implement `vfs_ops_t` without touching the
kernel core. Listings go through the `readdir` verb
(`vfs_readdir`, path-based, longest-prefix match like open, stateless
so a listing never pins an unmount): ramdisk splits flat names into
leaves and deduplicated first-level subdirs, MiniFS walks indexes
faithfully, mem: lists its flat root only, and fat:/ext4: wrap the
bounded list helpers over "img:inpath" split addressing. The shell
`fat ls`/`ext4 ls` build "drv:/img:dir" and print verbatim (dir
slashes preserved), so no builtin names a driver anymore. Pin: `vfstest`
readdir legs (mem find + subdir refusal, ramdisk root pairwise-unique,
MiniFS root plus file refusal) and `vfs-readdir-*` mutants under
`MATCH="vfs "`.

### Page cache + file-backed mmap (T5, slices 1-2 landed)
Slice 1 landed the store: `fs/pcache.c` (256 page-aligned heap
pages, refcounts, dirty bits, FIFO eviction skipping pinned slots,
per-inode invalidation, publish-then-fill so racers never map a
half-written page, phys-proved put/ref, stats on `mem`),
host-pinned by `make test-pcache` (plus alignment and publish
vectors), pool allocated at boot, invalidate hooks live in
truncate/unlink. Dirty pages drop on invalidate until slice 3
teaches writeback, and no in-tree writer marks dirty yet.
Slice 2 landed file-backed `MAP_PRIVATE` mmap: VMA nodes carry
(ino, offset) tags, non-present faults publish privately filled
pages into the cache (fill-then-publish, so a racing faulter never
maps a half-written page; private zero/file fallbacks past EOF and
on pool exhaustion), writes break into private copies after
cow_resolve refuses, releases prove ownership through the PTE
before dropping (a private fallback never donates a ref it never
took), munmap/mremap clear PTEs precisely (VMA-only unmap would
otherwise resurrect stale pages on remap, including another
mapping's writes), fork inherits refs it proves through the parent
PTEs, teardown drops through the dying window while the sweeper
skips pool pages, and mprotect refuses write-upgrades on
cache-shared pages like CoW-shared ones. `MAP_SHARED`, ramdisk fds
and mremap-fixed moves refuse; the `pcmap` probe pins it (two
sequential sharers, one hash, one 17-page copy, plus a concurrent
no-crash run) with `mmap-file-*`/`pcache-*` mutants. Slice 3
(writeback + pressure eviction with reverse shootdown) waits for
its first writer; `ld.so` (T8) is unblocked on slices 1-2.

### Dynamic linking, minimal (T8: L1 landed, L2 as-built, L3/L4 specified)
Goal: share `.text` between processes (the RAM win), nothing more.
Functions only in v1: data stays per-binary behind the `ld` stubs
(`errno`/`stdout` keep working exactly as today), no lazy PLT, no
`dlopen`/`dlsym`, no TLS, no versioning, no C++. The toolchain
already cooperates without knowing it: miniGCC emits bare `call
extfunc` extern refs, and `ld -f elf` already writes zero-based
ET_DYN (fully RIP-relative intra-binary code, which is why the
ASLR slide works today). What is missing, in order:
L1 (`ld` repo, LANDED): `-shared` builds ET_DYN with SONAME plus
`.dynsym`/`.dynstr` over the defined global functions (no
relocations needed inside: self-contained miniGCC code is already
position-independent), proven by host `dlopen` (`dynlib: 42 5`).
L2 (`ld` repo, AS-BUILT): `-f elf -d lib.so` verifies each undefined
function against the lib's dynsym (typos stay hard link errors, the
existing contract) and emits one 16-byte eager PLT stub per import
(`jmp *GOT; 10x CC` fail-closed padding, control never falls
through) in RX after `.text`, the matching GOT in RW BSS, one
standard `R_X86_64_GLOB_DAT` row per import (sym = its `.dynsym`
index, addend 0: RELATIVE would wrongly bind the executable's own
slide), plus `.dynamic` (`DT_NEEDED`) and the import dynsym/dynstr.
Layout invariant (burned once: GOT writes ate later RELA rows and
the host died at row 22): `.rela` is placed in the data region
BEFORE the BSS-anchored GOT, never overlapping; `readelf -r`
must show disjoint ranges. Host proof: `ld-linux exe` returns
`42`/`47` through the stubs.
L3 (kernel, LANDED): a boot-global lib registry keyed by basename
(`ldso_libs[8]`: base, map span, heap copy of the file, pseudo ino,
refcount; the first loader reads and reserves, every later binder
reuses). The reserved region is `MINIOS_LDSO_BASE..END`
(0x09000000..0x0B000000, 32 MB) in `progs/minios_abi.h`, below the
graphics tail; `brk`/mmap seed at `USER_HEAP_CEIL` (= the region
base) and `munmap` refuses the range, so the heap never eats it.
Binding (`ldso_bind_into`) runs after the executable's segments land:
each `DT_NEEDED` loads through a pseudo inode (`LDSO_INO_BASE+slot`)
whose bytes are served by `ldso_pseudo_stat/read`, and every page is
published into the T5 pcache and mapped explicitly
(`mm_user_map_page`, shared read-only; private zero past EOF; data
breaks private on first write through `mm_file_break`). Explicit
mapping is deliberate: the live window is identity pre-mapped, so
demand faults never fire there, while isolated windows start empty,
and one path serves both. `R_X86_64_GLOB_DAT` rows resolve by name
in exe-then-libs-then-`ksym_resolve` order (v1 links functions only;
unresolved names stay zero and fault only if called), then RX is set
over verified text (`mm_user_set_exec`; a first-page content check
fails the bind before anything executes). The pure parser lives in
`kernel/ldso_parse.c` + `headers/ldso.h` (host-pinned by
`make test-ldso`, no kernel calls), so the loader only moves bytes
and installs mappings. Live runs release the previous run's registry
nodes first (`ldso_forget_live`: refs dropped, pages unmapped,
ranges freed) so the pcache never leaks across `run`s. Proven
in-guest: `ld -shared` + `ld -f elf -d` + `run` prints
`ld.so: dyn.so shared x1`, then `x2` on a second run (one registry
load for both) and the same for `mrun` (isolated window), exit 42;
`ldso-*` mutants under `MATCH="ldso-"` all killed.
L4 (next): `libcmini.so` (strlen/strcmp/memcpy/memset) plus two
probes built entirely in-guest (edit, minigcc, `ld -shared`,
`ld -f elf -d`, run), proving correct output and demand-shared text;
then the space win the distro wants: link programs against the one
shared libc instead of embedding the static stubs.
miniGCC needs zero changes; CVM programs naming shared symbols
keep failing to link (documented, same as errno today).
L4 toolchain pieces that LANDED (ld repo): `-shared` no longer
injects the runtime stubs, so a library may define and export names
the stubs also provide; `-f elf -d` pre-registers one placeholder
per import before the stub scan, so the colliding stub body shadows
itself and the resolver routes the call through the PLT (library
definition wins, a user definition stays local); `-runtime` prints
the built-in runtime (syscall stubs + libc fallbacks) as assembly,
each chunk behind a `.text` reset, so `ld -shared` over it yields a
49-routine `libcmini.so`. All host-pinned in the ld suite.
Measured reality (why the win is not there yet): a program linked
`-d libcmini.so` came out LARGER than the static one (8153 vs 4588
bytes) because (a) `ld` still injects all 49 stub bodies into every
binary and (b) `ld_read_lib` imports every library export, so the
exe carries 51 GOT/PLT/RELA rows it never calls. The win needs two
pruning passes: inject only the stubs the program actually
references (shrinks static binaries too) and import only the
referenced library symbols. A full shared libc that also moves the
error-setting syscall wrappers shifts `errno`/`stdout` into the
shared image (shared across processes) unless they move to a
per-process TLS slot via FSBASE; that is the open design decision
for the all-functions-in-libc version, tracked here, not shipped.

### Dynamic mounts, pipes, clipboard, fork, httpd (2026-09 session)
I implemented the user-facing half of the UNIX-way plan in one session,
one contract per feature, each with SDD spec, TDD host suite, BDD
scenarios and scoped mutants (full `mutate.sh` + `test_bdd.sh` only at
the end). What follows is what I proved and the mechanism behind each,
so the next session reuses the contracts instead of rediscovering them.

- **Pipes and `2>` (`headers/pipe.h`, `fs/kfile.c`, `kernel/syscalls.c`,
  `kernel/shell.c`, `kernel/console_in.c`, `kernel/console.c`,
  `kernel/redirect.c`). The shell runs pipelines sequentially: every
  stage runs to completion, its stdout is captured, and the capture
  becomes the next stage's stdin. Two doors each way because the two
  program kinds write differently: builtins and ET_REL children write
  `vga_putc` (caught by `redirect_begin`/`redirect_take`), ET_EXEC
  children write sys_write fd 1 (caught by a `kfd_table[1]` pipe
  override installed per stage). Two stdin doors match:
  `console_stdin_push` for the console reader and a `kfd_table[0]`
  override for sys_read fd 0; a drained pipe reports EOF (-1) instead
  of blocking on hardware. Linux pipe/dup/dup2 (22/32/33) work for
  ring-3 threads on refcounted KFILE pipe ends (empty+open is -11,
  drained+closed is 0). `2>` is an alias of `>` because MiniOS merges
  both streams at the console. `cat` with no arguments copies stdin
  when piped (still a usage diagnostic interactively). BDD asserts
  anchored output lines (unanchored expects match the command echo
  itself and prove nothing). Host suite `make test-pipe`.
- **Panic screen (`headers/panic.h`, `kernel/panic.c`, `panic`
  builtin). The fault handler keeps its serial forensics first, then
  unrecoverable faults paint vector/err/RIP/RSP plus up to five
  frame-pointer returns (validated low-half + image/heap/window/low
  stacks, re-entry halts) on the framebuffer terminal, raw VGA text
  (white on red) or serial-only under a graphics mode, and halt.
  Recovering ring-3 faults and killed threads never reach the screen.
  `panic` demos it without halting. Host suite `make test-panic`.
- **Dynamic VFS mounts (`fs/vfs.c`, `mount`/`unmount`/`vfstest`).
  Mounts carry open refcounts under `vfs_lock`; `vfs_open` bumps,
  `vfs_close` drops, longest-prefix-first is now real (the contract
  always claimed it while the code did first-match, which buried
  every mount under the root). Unmount refuses busy with -EBUSY and
  the pinned root with -EINVAL; duplicates and overlong prefixes
  refuse at register. `mem:` is a volatile driver proving the
  lifecycle end to end. Append mode rebases pos from the live size in
  `vfs_write`, so a reopened append handle cannot overwrite the head.
- **Thread-aware schedtop (`kernel/sched.c`). Rows carry tgid (lowest
  live pid sharing the VMA view) and T/P (CLONE_VM flag), so ten
  `thdemo` threads read as one group with ten tick counters; per-CPU
  rows are unchanged.
- **TCP server + httpd (`net/net.c`, `headers/net.h`,
  `headers/httpd.h`, `httpd` builtin). LISTEN/SYN_RCVD states beside
  the client machine: bare SYN to a listening port allocates a child
  and answers SYN-ACK (single backlog slot, second SYN drops for the
  peer to retry), the exact ACK establishes, wrong ACKs and early
  data drop. `net_listen`/`net_accept_nb`/`net_accept` (deadline
  bounded) plus Linux bind(49)/listen(50)/accept(43) with the same
  sanitize discipline as connect. `net_test_inject_tcp` feeds
  checksummed peer segments through the production demux so
  `httpd --selftest` proves handshake, ack guard, request, 200 and
  404 with no NIC. `httpd` serves static files from any VFS root
  (GET only, traversal/overlong/version refused, every failure a
  status code). Host suite `make test-httpd`. Live hostfwd proof is
  environment-blocked here (slirp accepts but never delivers to the
  guest NIC: rx stays 0), so `--once` exists for manual
  host-curl verification with `-hostfwd`.
- **Clipboard (`kernel/clip.c`, syscalls 249/250, `headers/httpd.h`
  sibling `wl_clip_*` in `progs/wl/wl_mini.h`, `clip` builtin). One
  4 KB kernel slot: set refuses past the cap, get refuses empty and
  undersize (never a truncated paste), clear empties. ABI v10 carries
  the two numbers in the checksum (Linux owns 249/250 as
  request_key/keyctl, unused by every ring-3 program here).
  Terminal selection and vedit paste on top are Phase 2.
- **Copy-on-write fork (`kernel/mm/cow.c`, `kernel/sched.c`
  `do_fork`/`vma_ctx_copy`, `arch/x86/ctx_sw.S`
  `fork_trampoline`, `progs/src/forktest.c`). Isolated non-CLONE_VM
  processes only (legacy pid 0 and threads refuse -ENOSYS). The
  child shares present data pages read-only (512-entry phys table,
  full/OOM degrades that page to eager copy) with NX preserved; the
  first write in either window privatizes through a #PF resolve that
  runs fenced (ring-3 faults inherit IF=1, and a tick preempting the
  resolve deadlocks on `cow_lock` silently). VMA contexts deep-copy
  with pointer rebase. The child resumes at the trapped syscall
  return (`sc_rip` + parked user rsp) through `fork_trampoline`,
  which zeroes rax: `switch_to` restores every GPR from the PCB
  except rax (its own scratch), so `user_trampoline` would resume
  the child with garbage and it would take the parent branch (seen
  live as a doubled "parent waiting" wedge). `mm_copy_user_page`
  preserves the NX bit (eager clones faulted fetch as err=15
  before). `pt_free_user` releases shares first. FSBASE and the FPU
  image inherit live (the child never re-runs glibc init).
  `mrun bin/forktest.elf` proves both-direction isolation and
  reaping. `check_fork_stubs.py` now gates vfork/execve only.
- **virtio-blk (`drivers/virtio_blk.c`,
  `headers/drivers/virtio_blk.h`, `headers/drivers/pci.h`,
  `vblk` builtin). PCI config access unified from rtl8139's static
  copy into `drivers/pci.h` (host suite `make test-pci`). Legacy
  queue: 12 KB contiguous area (desc/avail/used for up to 256),
  QueueNum written (a zero default processes nothing), single
  in-flight request, bounded poll, ISR acked per completion.
  Request header and status byte are heap objects: KASLR slides
  statics out from under DMA (the signature bug of this driver:
  completions landed nowhere while the device reported success).
  `vblk` reads LBA 0 and the MiniFS superblock off the queue and
  checks both magics; the BDD slice attaches the image as a second
  virtio drive (same file twice is write-locked, so it boots a
  copy). IDE stays the default path; MiniFS-on-virtio migration is
  future work.
- **UEFI stub (`boot/uefi_stub.c`, `make uefi`, `uefi.img`,
  `scenario_uefi`). A freestanding PE32+ app (i386pep link, no
  gnu-efi) proving entry, ConOut+COM1, the BootServices table, a
  full memory-map read and a BlockIo LBA 0 read with the MBR
  signature. Three firmware-call facts this stub taught me, kept
  here so nobody re-learns them: calls use the MS x64 ABI
  (`__attribute__((ms_abi))`, SysV calls hang); every table struct
  carries its 24-byte header (a missing one shifts every slot by
  three and jumps at the "BOOTSERV" magic, #GP with RIP="BOOTSERV");
  `unsigned long` is 8 bytes, so hand-rolled `u32` typedefs must be
  `unsigned int` (the silent shift behind weeks of confusion
  compressed into one line). GOP is correctly reported unavailable
  on the video-less OVMF build here, not a stub failure. Kernel
  handoff (ExitBootServices + stage2 contract) is Phase 2.
- **Surveyed, not built**: USB-HID needs a full xHCI+USB stack
  (months, the real-metal blocker); E1000/AHCI reuse the PCI
  discovery virtio-blk already owns; runtime TrueType stays out
  (stb_truetype is float-heavy, kernel builds -mno-sse: fonts
  remain build-time bitmaps).

### Harness repairs found by the mutation gate (same session)
The full `mutate.sh` run is itself a test of the harness. It caught
four, all fixed and re-proven in isolation before the gate closed:

- **Unquoted eval (`tools/mutate.sh`).** Mutants were applied with
  `eval "sed -i '$expr'"`. An expression carrying a literal quote
  (vol-sign-ignored's `-`) re-quotes under eval: sed receives a
  de-quoted pattern, matches nothing, and the mutant reports BROKEN
  while the anchor checker (plain sed, no shell layer) passes. Every
  table entry is a single `s///` program, so eval bought nothing:
  the runner now calls `sed -i "$expr"` directly, the same ground
  truth the checker uses. Mechanism, not incident: never wrap a data
  substitution in eval; a checker that bypasses the shell cannot
  catch shell-layer mangling.
- **SOURCES allowlist gaps (`tools/mutate.sh`).** Six
  mutation-target files were missing from the backup/restore
  allowlist (pre-existing futex/batch/rcu/percpu/lisp, plus my own
  httpd.h): their mutants leaked, stacked, and every stacked kill
  was vacuous. The repo comment already named this failure mode;
  the allowlist now covers all 55 targets (audited
  programmatically), and the stacked verdicts were re-run isolated:
  7/7 smpscale, 7/7 lisp, 4/4 httpd, all KILLED. The same class
  recurred when `syscalls_proc.c` (split from `syscalls.c` after that
  audit) shipped a mutant row without an entry: `execve-never-replaces`
  leaked `rc = -38` into the tree and the shipped image. The anchor
  checker caught it (expression matched nothing), the line was
  restored, and `loader.c`/`exec.c` ride along as the
  execve-adjacent surface. Rule restated: a new mutant row lands its
  SOURCES entry in the same edit, and a green anchor check is required
  before any mutant run, not after.
- **File-level routing collision (`tools/mutate.sh`).** My
  `cow.c|ctx_sw.S → fork-slice` routing sent the pre-existing
  fpu-no-save to 3 unrelated fork scenarios, where it survived
  vacuously. Routing is by mutant name for that file now
  (fpu-no-save runs the fptest slice: KILLED). fpu-no-restore still
  survives the fptest slice: genuine pre-existing gap (fptest never
  diverges FPU state across threads), like paint-blit-transposed in
  the paint slice. Both are recorded SURVIVED, neither is mine.
- **Unescaped quotes in the table (`tools/mutate.sh`).**
  `MUTATIONS="..."` is plain double quotes, so a literal `"` inside
  toggles shell quoting and de-quotes the value (rlimit-as-shell-
  ignored's `"as"` became bare `as`: checker passes, runner
  errors). One line in the whole table had the bug; quotes are now
  `\"`-escaped and the mutant dies. Rule for new rows: escape every
  `"` and keep `\\[`-style BRE escapes doubled, exactly like the
  neighboring rows.

Final gate of this session: 171 KILLED, 2 SURVIVED (both pre-existing
genuine gaps above), 0 BROKEN. Full BDD on this tree: 448 passed, 15
failed; 4 failures reproduce byte-identical on a clean-HEAD baseline
image (cvm-argv exit 12, ps-hello anchor, bg-gfx focus, fx-melts
count), thdemo/fptest/pageup are the documented flaky/limited areas,
and the freedom-fetch/exit-130 remainder is fixture-timing sensitive
(each passes in isolation). Every scenario touching new code passes;
`sh src/test_all.sh` prints 96 PASS with zero FAIL.

#### Mutation anchor hygiene and the equivalent-mutant record
Every `mutate.sh` expression must match its target file, or `mutate.sh`
reports BROKEN instead of a kill and the gate silently weakens.
`tools/check_mutant_anchors.py` (in `make lint`) applies each expression
with sed itself to a scratch copy and fails closed on any no-change anchor.
A BRE metacharacter left unescaped (notably a bare `*` where a literal star
stands in the source) matches nothing. The checker derives the table bounds
from the `MUTATIONS="` markers, never from line numbers: a hardcoded range
once silently dropped the last row (and would have dropped every row added
past it). The same BRE caution applies to `test_bdd.sh` markers: `usage:
wait [pid]` matches one char of {p,i,d}, never the brackets; assert
`usage: wait` instead.

The only mutant ever removed as provably equivalent stopped
`redirect_resume` from restoring the capture: every shell status print is
the last thing a command does, so nothing observable followed the missed
resume. It was replaced by `redirect-captures-nothing` and
`status-leaks-into-redirect`, which exercise the same contract through
effects the suite can see.

### VMA (Virtual Memory Areas)
A red-black tree for mmap tracking, implemented in its own contract
`vma.c` with the single header `vma.h` (previously inlined in `loader.c`
against an unwired, divergent `vma.h`).  Replaces the former flat
`mmap_used`/`mmap_free` arrays with O(log n) insert/find/delete.  Two
trees: `vma_live_root` for active allocations, `vma_free_root` for
reclaimed regions.  A static node pool (`VMA_MAX` = 2048) backs both
trees and is reset by `vma_tree_init` on every exec; a pool that is
exhausted fails closed (returns `VMA_NIL`), never overruns.  The mmap
syscall (9) searches the free tree for reusable regions before carving
fresh space from the cursor; munmap (11) moves the freed region to the
free tree.  The SPAWN syscall saves and restores the entire VMA pool and
tree roots so child mutations do not corrupt the parent state.  mremap
(25, `sys_linux_mremap`) resizes or moves one exact live node: shrink
splits precisely, grow extends in place over free-covered pages,
otherwise `MREMAP_MAYMOVE` relocates (copy, then free old) and
`MREMAP_FIXED` relocates only onto a free-covered target; `new_size` 0
unmaps. Every failure restores the trees first, so a failed call changes
nothing. glibc's realloc needs it for large mmap'd chunks (the file
browser hits it three times decoding the wallpaper), proved headless by
`file --selftest` (`file: png ok (192x120)`), which decodes
`wall/wallpaper.png` through the same stb_image realloc path.

The tree is integer-only and free of kernel dependencies, so it is
host-tested by `tests/test_vma.c` (`make test-vma`), which asserts the
red-black invariants (root black, no double-red, equal black height,
in-order uniqueness) across insert/find/delete, pool exhaustion and full
drain.  That suite exposed and fixed a latent CLRS-conformance bug: the
two-child delete case restored the successor's color
(`y->red = y_orig_red`) instead of the deleted node's color
(`y->red = z->red`), which unbalanced black height (reproducible with
eight nodes).  Mutation coverage lives in `mutate.sh` (`vma-*` mutants,
routed to the host test, no QEMU boot).

Known growth area (pre-existing, documented): a deleted node's slot is
not recycled into the pool, so a single process is bounded to `VMA_MAX`
total tree operations before `vma_tree_init` resets the pool on the next
exec; this matches the single-address-space model and the working-set
tests the suite drives.

### Unified Audio API
A hardware-agnostic audio interface (`audio.h`, implementation in
`progs/src/audio.c`) providing tone mode (PC speaker square wave) and
PCM streaming mode (SB16 DMA).  Ring-3 programs use these wrappers instead
of raw syscalls.  The kernel dispatches to the appropriate hardware backend.

### Quake 2 Decoupling
The `SYS_Q2G_SET_TITLE` syscall is renamed to `SYS_GFX_SET_TITLE` (generic
window title).  The Q2G build is conditional: skipped when the upstream
checkout is absent (`Q2G_AVAILABLE` flag in Makefile).  The kernel contains
no Quake-2-specific logic; all Q2G coupling lives in the platform layer
(`progs/quake2generic/q2generic_minios.c`) and the Makefile.

## Security Requirements (Non-Negotiable)
- Every loader input is validated before use: ELF headers, section and
  relocation bounds, ramdisk table extents and per-file ranges.
- Size arithmetic is overflow checked before allocation.
- Failure paths report and release; no silent partial state.
- No function symbol is ever resolved to a null address.
- `size * n` in file I/O is checked for integer overflow before multiplication.
- Stack setup for user programs validates that argv writes stay within bounds.

## Unified Architectural Improvement Plan

See `ARCHITECTURE_PLAN.md` for the future-work plan and `docs/adr/` for
the decided record (ADR-0001..0013, the source of truth for *why*;
`docs/vma-complexity.md` proves the VMA bound).  This section documents the
implemented changes and the contracts they establish.

### ABI Versioning (Phase 1.1)

`progs/minios_abi.h` carries `MINIOS_ABI_VERSION` (monotonic integer) and
`MINIOS_ABI_CHECKSUM` (XOR-fold of all layout constants).  Any backwards-
incompatible change to layout constants or syscall numbers must bump the
version.  The checksum is computed at compile time from the constants
themselves, so it changes automatically when any constant changes.

Build-time drift prevention: `kernel.c` contains `_Static_assert` macros that
verify the kernel's derived constants equal the ABI header values.  Ring-3
programs include the same header, so both sides pick up changes on rebuild.

### Canonical Syscall Table (Phase 3.1)

`progs/minios_abi.h` is the single source of truth for all syscall numbers.
The table is organized as:
- 0-199: Linux ABI compatible syscalls (read, write, brk, mmap, ...)
- 200-299: MiniOS custom syscalls (networking, audio, graphics, ...)
- 300+: Reserved for future use

Linux numbers implemented late but fully: pipe/dup/dup2 (22/32/33, KFILE
pipes), accept/bind/listen (43/49/50, server TCP), rename (82, fs_rename).
ABI v10 adds rename (82, in the checksum); ABI v9 added the
clipboard pair (249/250, in the checksum); 243-245 stay reserved for
Wayland-mini and out of the checksum until the kernel answers them.

All runtime bindings (Lua `minios.c`, MicroPython `minios_module.c`, Lisp
`lisp.c`, DOOM
`doomgeneric_minios.c`, Nuklear `nuklear_minios.c`, Quake 2
`q2generic_minios.c`, OPL3 `opl3.c`, SB16 `sbtone.c`, piano `piano.c`)
must reference the `MINIOS_SYS_*` constants instead of defining their own.
Compatibility aliases (`SYS_TIME_MS`, `SYS_PALETTE`, etc.) are provided
for backward compatibility but new code should use the canonical names.

### Per-process file descriptors (`kfd_view_t`, `kernel/syscalls.c`)
`KFILE *kfd_table[KFD_MAX]` is gone. Each process owns a heap `kfd_view_t`
(32 slots, a close-on-exec bitmask, a view refcount) through `proc_t.kfd;
NULL means the static root view, which serves the shell (pid 0), AP idle
and any pid without its own and is never freed. `proc_t` grew 328 to 336
bytes (`PROC_T_SIZE`, mirrored by `SYSCALL_PROC_T_SIZE`; `kstack`/`fpu`/
`fsbase` offsets unchanged, proven by the same `_Static_assert`s), costing
512 B of `.bss` against the `check-size` gate. Every syscall (open, pipe,
dup, dup2, close, read, write, override) resolves the caller's view once
(`kfd_view_current`) and mutates slots only under `fd_lock`, so a close in
one process never drops another's handle. Threads (`do_thread_spawn`,
`do_clone` with `CLONE_FILES`) share the view with a refcount bump; fork,
`proc_create` and isolated spawn (`proc_spawn_elf`, which copies the
spawner's view so pipeline fd 0/1 overrides are inherited, then isolated)
deep-copy it with one `KFILE` ref per live entry; `waitpid_scan` releases
it at reap beside the VMA context (shared views drop one view ref, entries
close only at zero); `do_execve` keeps the view minus `O_CLOEXEC` fds
(Linux `0x80000`, armed at open, cleared at close). `spawn_backup`/
`spawn_restore` snapshot and restore the caller's own view, preserving the
ring-0 ET_REL borrow semantics. `RLIM_NOFILE` is now enforced per view
instead of best-effort. Proven by the `forktest` fd leg (pre-fork pipe,
parent closes write at once, child writes after 2000 yields, parent reads
back after the child's closes: `fork: fd ok`, exit 0) with the BDD scenario
extended and the `fd-fork-shares-view` mutant (copy replaced by share)
routed to the fork slice, where it dies.

### SMP Synchronization (Phase 1.3)

`spinlock.h` provides a lightweight xchg-based spinlock with two acquisition
modes:
- `spin_lock` / `spin_unlock`: disables interrupts on acquire, re-enables on
  release. Single-level sections only: the caller must hold no other
  interrupt-disabling lock and must not run inside an ISR. Nested or ISR
  paths must use `spin_lock_irqsave` instead, or the inner `spin_unlock`
  re-enables interrupts prematurely. Every contention loop emits `pause`,
  so a spinning core does not saturate the bus against its siblings.
- `spin_lock_irqsave` / `spin_unlock_irqrestore`: saves RFLAGS.IF before
  disabling, restores the saved state on release. Safe for nested critical
  sections where the outer lock has IF=0.

`spin_trylock` attempts acquisition without modifying interrupts.

`sched_lock` protects the shared process table (`procs[]`), `proc_count`,
and scheduler state. `smp_lock` protects the AP counter and LAPIC registers.
Per-CPU data (current PID on each core, per-CPU stacks) needs no lock.
The lock primitives are in place for when SMP scheduling is enabled; currently
APs idle in an hlt loop.

### Kernel Decomposition (Phase 1.4)

`kernel.c` is being decomposed into standalone compilation units and the
project is restructured into a Linux/BSD-style directory layout:

```
arch/x86/boot/    stage1.S, stage2.S, bootdefs.h, linker scripts
arch/x86/         isr_stubs.S, ctx_sw.S, ap_entry.S
kernel/            string.c, serial.c, sched.c, vga_fb.c, lz4_kernel.c, cvm_host.c
drivers/           ide.c, block.c, pcspk.c, sb16.c, rtc.c
fs/                minifs.c, zip.c
net/               net.c, tls.c, tls_crypto.c, tls_x509.c
third_party/       xxhash, stb, dlmalloc, miniz
```

Kernel-owned headers live in `headers/` (accessed via `-Iheaders`, with the
`arch/`/`drivers/`/`kernel/`/`net/` subpaths preserved); source files live
in subdirectories. The Makefile uses `VPATH` so make finds sources in
subdirs while `.o` files stay in the root for the link line.

Extracted so far:
- `serial.c`: COM1 16550 UART driver (init, putc, getc, available, puts)
- `string.c`: kernel string/memory functions (kstrlen, kmemcpy, katol, etc.)
- `console.c`: text console, output capture and libc name table (ADR-0011;
  `kernel.c` is now only the Mediator orchestrator + syscall trampoline)
- `driver.c`: Strategy-pattern device registry (`ide0` block, `pcspk0`
  audio, consumed by `block.c` through ops); VFS exposes the
  `file_operations`/`vnode_t` facade (ADR-0012)
- Drivers: ide, block, pcspk, sb16, rtc moved to `drivers/`
- Mouse: the PS/2 controller handshake, Intellimouse knock and
  enable/disable verbs moved from `kernel/sched.c` to `drivers/mouse.c`
  with the boundary header `drivers/mouse.h`; the IRQ12 packet phase
  machine stays in the scheduler ISR dispatch beside its consumer.
  `mouse_hw_init` performs the full OSDev init sequence, never trusting
  firmware state: disable both ports (0xAD/0xA7) before the config
  read-modify-write, publish a known-good command byte (IRQ1 + IRQ12 +
  set-2-to-set-1 translation on, both disable-port bits clear), then
  enable both ports (0xAE/0xA8) before the mouse reset/knock. Skipping
  the disable-first step corrupted the command byte on VirtualBox (whose
  BIOS leaves different strays than SeaBIOS), silencing the keyboard and
  the mouse together even with host input captured, while QEMU worked.
  The `vb` recipe pins `--mouse ps2 --keyboard ps2` so no VirtualBox
  default (USB tablet) can starve the i8042 path; input still requires a
  click to capture (no Guest Additions), Host key releases.
- Filesystem: minifs, zip moved to `fs/`
- Network: net, tls, tls_crypto, tls_x509 moved to `net/`; the rtl8139
  driver further split into its own contract `net/rtl8139.c` with the
  boundary header `net/rtl8139.h`
- Scheduler: sched.c, vga_fb.c, lz4_kernel.c, cvm_host.c moved to `kernel/`
- Cursor: the pointer sprite layer (bitmap, saved background, painted
  position) moved from `kernel/vga_fb.c` to `kernel/vga_cursor.c` with the
  boundary header `kernel/vga_cursor.h`; it draws only through the
  framebuffer primitives (`vga_fb_pixel`, `fb_read/write_packed`), and the
  compositor reaches it through place/move/erase/invalidate ops
- Syscalls: proc-leaf handlers (clone, seccomp, nice, yield, getpid/tid,
  fork/vfork/execve stubs, exit, wait4, kill) moved to
  `kernel/syscalls_proc.c` with the boundary header `syscalls_proc.h`;
  first increment of the `syscalls.c` decomposition, tables unchanged
- Memory: VMA red-black tree moved to `vma.c` (its own contract, was inline
  in loader.c against a divergent `vma.h`)
- Editor: the built-in line editor moved to `kernel/editor.c` with the
  boundary header `editor.h`; `shell_readline_buf`/`shell_parse` and the
  `CMD_BUF_SZ`/`MAX_ARGS` bounds are shared through `shell.h`
- Boot: stage1.S, stage2.S, bootdefs.h moved to `arch/x86/boot/`
- Arch: isr_stubs.S, ctx_sw.S, ap_entry.S moved to `arch/x86/`
- WM: six header-only contracts at the root (`wm_geom.h`, `wm_events.h`,
  `wm_window.h`, `wm_render.h`, `wm_tiling.h`, `wm_focus.h`, ADR-0020);
  `kernel/vga_fb.c` consumes them for hit-testing, event edges, paint
  order, tiling cells and focus transitions, host-tested by `make test-wm`
- Console input: pushback FIFO, serial + PS/2 raw multiplexer,
  blocking/peek/raw/job readers and the scrollback view moved from
  `kernel/shell.c` (2961 lines) to `kernel/console_in.c` with the boundary
  header `kernel/console_in.h`; the readline loop re-injects through the
  public `console_ungetc`. `shell.h` re-exports the boundary, so the editor,
  SPAWN waits and the GETC_RAW syscall include one header as before.

Future extractions: shell.c remainder — readline/history/completion state
and builtins (~2700 lines), loader.c (deps on static mm funcs), mm.c, and
the remaining `syscalls.c` leaves (fd table, spawn bridge, mm, net, gfx
handlers, in that risk order).

### VFS Invariant Documentation (Phase 1.4)

`kernel.h` documents explicit contracts for `vfs_ops_t`, `vfs_file_t`,
`KFILE`, and `RDFile`:
- Every field has a semantic contract (what it holds, when it is valid)
- Invariants are stated (what must be true before/after operations)
- Failure modes are documented (what happens on error)

### CVM Hardening (Phase 3.3)

The CVM interpreter already has comprehensive bytecode validation:
- Module loading: magic, version, size, all section bounds checked
- Jump targets: bounds-checked against `code_size` (OP_JMP, OP_JZ, OP_JNZ)
- Function calls: bounds-checked against `num_funcs` (OP_CALL)
- Native calls: bounds-checked against `num_module_natives` + CVM_MAX_NARGS
- Memory operations: all use `mem_valid()` for bounds checking
- Stack operations: overflow/underflow checks via vp()/vo()
No additional hardening was needed.

### Shell Extraction Plan (Phase 6.1)

`shell.h` defines the public API.  The extraction of 38 shell functions
(~2070 lines) from kernel.c to shell.c is planned as a future phase.
See `tools/extract_shell.py` for the full dependency analysis.  The
extraction requires:
- Making redirect_begin/commit/suspend/resume non-static (done)
- Making shell_run_elf_buf, shell_run_elf_file, shell_run_cvm non-static
- Making shell_run_any, shell_exec_builtin, shell_report non-static (done)
- Making console_getc non-static (done)
- Breaking circular dep: kfgetc (kernel.c) -> console_getc (shell section)
- Breaking circular dep: load_exec_elf -> redirect_suspend/resume
- Exposing fs_cwd, fs_resolve, and filesystem helpers
- Updating the Makefile to compile shell.c

The circular dependencies between console_getc, kfgetc, redirect functions,
and the ELF loader make a clean extraction non-trivial.  The cross-boundary
functions are now non-static with declarations in kernel.h, ready for
extraction when the circular deps are broken.

### Architectural Governance (Phase 2)

CI gates enforce architectural constraints:
- `tools/check_cohesion.py`: fails if any root community's cohesion drops
  below 0.25 (configurable in ARCH_POLICY.yaml)
- `tools/check_complexity.py`: fails if kernel.c exceeds 350 symbols
  without explicit approval in ARCH_POLICY.yaml
- `tools/check_surprising.py`: flags new connections of 5+ hops between
  distinct communities as coupling debt
- `tools/check_kb_sync.py`: verifies KNOWLEDGE_BASE.md is in sync with code

`.github/workflows/governance.yml` runs these gates on every push.
`.github/workflows/test.yml` runs the unified test pipeline.

### Validation Gate (updated)
```bash
make                        # zero warnings
make lint                   # cppcheck + -Wextra (ring-3) + clang-tidy curated + bash -n + abi-numbers + fork-stubs + sanitize-audit + addons, all green
sh src/test_all.sh          # one-boot comprehensive non-interactive suite (96 PASS)
./tools/test_bdd.sh          # all scenarios green (full interactive suite)
python3 tools/test_gui_wm.py  # QMP pixel proof: gfx survives Alt+Tab/tile, taskbar button refocuses
python3 tools/test_gui_icon_cwd.py  # QMP pixel proof: dock launch ignores shell cwd
python3 tools/test_gui_fashion.py  # QMP pixel proof: one cursor, stable frames, ESC quit
python3 tools/test_gui_gfxview.py  # QMP pixel proof: fullscreen DOOM, Alt+Enter, tile, minimize, close
./tools/test_codecs.sh      # lzss/lz4/aes roundtrips (pass=3)
./tools/mutate.sh            # every mutant killed
make test-tls               # host-side crypto + handshake suite
make test-vma               # host-side VMA red-black tree suite
make test-lisp              # host-side Lisp interpreter suite green
make test-wl                # host-side Wayland-mini wire suite green (ADR-0024)
make test-freedom-wl  # Wayland-to-MiniOS mapping suite green (ADR-0019)
make test-freedomui   # real FreeDom engine backend suite green (ADR-0021)
make test-futex test-percpu-rq test-batch test-rcu  # SMP scaling contracts green
make test-sanitize  # syscall sanitize-macro suite green
make test-tick test-hal  # tick bus + HAL port-mapping suites green
make test-driver test-sync  # device registry + sync/PI suites green
make test-pcm        # low-latency PCM ring suite green
make test-rtc        # RTC civil-date math suite green
make test-vedit      # vedit IDE build-contract suite green
make test-file       # file browser assoc-contract suite green
make test-paint      # paint canvas/PNG-contract suite green
make test-png        # shared ring-3 PNG helpers + pokemon side-art policy green
make test-doomedit   # doom PWAD writer + C/Python roundtrip green
make test-theme      # shared Nuklear theme suite green
make test-wm         # WM geometry + event translator suite green
make test-fx         # DOOM-melt column contract suite green
make test-pipe test-panic test-pci test-httpd  # pipe ring + panic walk + PCI + httpd wire green
make test-fat  # FAT32 loopback driver: units, multi-cluster reads, fail-closed edges green
make test-ktime test-randmix  # Phase 0 truthfulness: TSC->usec + getrandom mixer green
python3 tools/check_abi_numbers.py  # Phase 0.6: syscall numbers match Linux x86-64 (also in lint)
python3 -m unittest -v mcp/test_minios_mcp.py   # unit + QEMU BDD
mcp/mutate_mcp.sh           # every MCP mutant killed
python3 tools/check_cohesion.py KNOWLEDGE_BASE.jsonld
python3 tools/check_complexity.py --policy ARCH_POLICY.yaml
python3 tools/check_surprising.py KNOWLEDGE_BASE.jsonld
```

<!-- readmenator-agent-kb-link -->
