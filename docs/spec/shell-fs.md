# Shell, ramdisk names, filesystems, tracing, observability and the line editor

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### Shell
`cmd > file` redirects the command's console output into a ramdisk file
(truncating it); `cmd >> file` appends. Shell status text — exit codes and
the shell's own diagnostics — is lifted out of the capture: a redirection
captures what the command wrote, not what the shell reported about it.
This is what makes `run objects/minigcc.o p.c > asm/p.s` produce assembly a linker can
consume.

The prompt keeps a bounded command history (`SHELL_HIST_MAX` entries).
Up arrow (ESC `[` `A`, or PS/2 make code `E0 48`) recalls the newest older
command starting with the typed prefix (zsh `history-beginning-search`);
down arrow (ESC `[` `B`, `E0 50`) moves forward again, back to the live
line. An empty line matches every entry, i.e. plain chronological recall.
Right arrow at end of line accepts the suggestion outright: it completes
the line to the newest history entry starting with the prefix (a plain
cursor move there would be a no-op, so nothing is lost). The recalled text
replaces the line the user was typing, which is preserved while scrolling.
The history stores commands on submission (even unknown ones), skips
consecutive duplicates, and survives only until reboot. A bare ESC or
an incomplete escape sequence is discarded, never inserted into the
line, and the editor (`edit`) is unaffected: history is a shell-prompt
feature, not a readline library.

The prompt is a full mid-line editor, not an append-only line: the
cursor moves with Left/Right (ESC `[` `C`/`D`, PS/2 `E0 4B`/`4D`) and
Home/End (ESC `[` `H`/`F`, `E0 47`/`4F`); Delete (ESC `[` `3~`, `E0 53`)
removes the character at the cursor; backspace removes the one before it;
Ctrl+A/E jump to start/end; Ctrl+U kills to the start; Ctrl+K kills to
the end; Ctrl+W kills the word before the cursor. Inserting in the middle
of a line shifts the tail right, and a framebuffer block cursor
(`vga_fb_text_cursor`) tracks the edit position on the terminal window.
Every operation repaints the line (erase + rewrite + back the console
cursor up), so the display and the serial console agree. The escape
sequence reader (`consume_page_after_esc` + `raw_wait_seq`) polls a
bounded number of spins for the sequence's final byte, because a
serial-delivered escape arrives byte by byte: without that wait an
arrow/Home/End/Delete key arriving right after a command could be split
across reads and mis-parsed. A bare ESC that never completes a sequence
still degrades to a discarded key, never a hang.

Command resolution is a fixed order: builtin, registered program, then a
single runnable-file resolver. Every non-builtin command — whether typed
with `run` or bare — funnels through `shell_run_any`, so `run ld.o`,
bare `ld.o`, `run fib.elf`, bare `fib.elf`, `run fib.cvm` and bare
`fib.cvm` all behave identically.

The runnable-file resolver (`shell_resolve_run`) maps a bare name to a
full ramdisk path by suffix, through the toolchain directories `objects/`,
`bin/` and `cvm/` (`shell_run_dirs`, `SHELL_RUN_DIRS`):

| suffix | directory | example |
|--------|-----------|---------|
| `.cvm` | `cvm/` | `w1.cvm` |
| `.o`   | `objects/` | `ld.o`, `minigcc.o` |
| `.elf` | `bin/` | `fib.elf` |
| (none) | `bin/` | `cp`, `freedom` (command path) |

Resolution order is fail-closed and never truncates: a name with a `/` is
resolved against the cwd; a bare name is tried first against the cwd and
then through the suffix-picked directory and the remaining directories as
fallback. Every candidate must exist as a real file (`fs_is_dir` is
rejected, `ramdisk_open` must succeed) before it is run. A candidate whose
full path cannot fit `RAMDISK_FNAME_LEN` is skipped like a missing file,
never truncated.

A resolved file is then classified by content and run by the matching
loader (`shell_run_elf_buf`): `ET_REL` `.o` objects run at ring 0 through
`k_run_rel`, `ET_EXEC`/`ET_DYN` binaries run as ring-3 processes through
`k_exec_user`, and `.cvm` modules run on the `objects/cvm.o` interpreter
loaded on demand (`shell_run_cvm`). Because the file is reloaded and
relocated fresh on every invocation, running a toolchain object does not
grow the registered-program table. The relocated image is freed when the
run returns (`elf_load` reports its base, `run`/`SPAWN` release it), and the
toolchain's OWN malloc arena is freed too: `ld.o` releases all five link
buffers (`ld_release` in the sibling `ld.c`: `blob_data`, `data_region`,
`code`, `pool`, `fixups`, plus counters) before every return/exit from
`main` and `elf_build`, and `minigcc.o` was already clean (source, includes,
string pool all freed on the success path). Measured `mem` before/after:
compile, `-f elf` link, `-f cvm` link and `cvm` runs are all flat after a
one-time first-touch; sibling suites stay green (`ld` 37/37, `miniGCC`
67/67) and `sh src/test_all.sh` prints 96 PASS. The exit code is reported exactly as
`run` reports it; an unresolvable name falls through to
`command not found` (bare) or `run: not found` (with `run`). `objects/`
and `cvm/` are never on the bare command path — only registered programs,
the current directory, and the suffix-driven `bin/` lookup answer a bare
name, so the command path stays root-anchored and an attacker can never
run an arbitrary `.o` as a command by name alone.

TAB completes the current word from history, builtins, registered programs
and ramdisk file names: one TAB fills the longest unambiguous prefix, a
second TAB on a unique match fills the whole name, and an ambiguous prefix
lists the candidates. Completion repaints the line in place (never a stray
newline) with the cursor at the end, so the submitted command always
matches what is on screen. On the first word the newest history commands
complete too (deduplicated first tokens, most recent first), then the
builtin names, so TAB after `minigcc` offers the most recent matching
command and TAB after `pw` offers `pwd`. A bare first word (no `/`)
completes runnable-first across the ramdisk and the MiniFS root (where the
big ELFs live under bare names): the `.elf` tier, then `.cvm`, then `.o`,
and only the highest-priority non-empty tier is kept, so `poke` offers
`pokemon.elf` instead of its icon PNG. An explicit path or an argument word
keeps every match, so navigating to data files still works: the ramdisk
half matches full names and basenames, and `shell_complete_minifs_arg`
adds the MiniFS half (the word's directory part resolves against the cwd,
entries of that MiniFS directory match the leaf prefix, directories with
a trailing `/`), so a file created under a MiniFS-only directory by a
redirect completes exactly like a ramdisk one. The completion
is bounds-checked and never writes past the command buffer.

Terminal scrollback is a 256-line logical ring (`SB_MAX_LINES` in
`vga_fb.h`): a completed line is pushed whole on `\n` and the viewport is
repainted from the ring, so old lines scroll off the top and stay reachable
through the scrollbar/mouse-wheel (`disp_off`). A push that evicts the
oldest line always fully renders: comparing row counts alone would take the
active-line-only fast path (the count is unchanged by an eviction) and
freeze the screen with only the bottom line repainting. Blank viewport rows
are explicitly cleared, never left with stale pixels.

Known limitation (pre-existing, desktop-only): console scrollback is
windowed. The text-console PageUp scrollback ring is populated from the
80x25 `VGA_BASE` layer, so it stays empty while the windowed desktop is
active (shell output renders to the framebuffer window instead). The
desktop exposes its own scrollback through the terminal window's
mouse-wheel/scrollbar (`disp_off`), which redraws the framebuffer only and
does not re-emit lines to the serial console. The BDD scenario
`page up scrolls back to the boot banner` therefore asserts the serial
text-console behaviour and is expected to fail under the windowed desktop;
this is a pre-existing gap, not a regression.

Known limitation (pre-existing, under investigation): the BDD scenario
`stb image selftest loads test.png and checks pixel` times out — the guest
never reaches `poweroff`, so the kernel hangs (or the machine resets) while
the ring-0 `stb.o` selftest runs. It fails deterministically and predates
the zip/miniz work; it is tracked separately from this feature and is not a
regression.

Known limitation (pre-existing, under investigation): `fptest` passes in
isolation but dies when run late in a churned session (after the lisp
suite or the full `test_all.sh`, and on an immediate second run): the
guest faults jumping to the user stack top (`EXCEPTION 0e`, fetch at
`0x0BFFFFxx`) or halts silently. It is independent of the spawn and
mount work — `thdemo` + `fptest` passes, and none of the changed lines
execute on fptest's path (`k_exec_user`, clone, futex, mmap, FPU) —
so it belongs to thread/proc teardown, not to this feature.

Known limitation (pre-existing, characterized 2026-09-16, same family
as `fptest` above): two heavyweight ring-3 processes running
concurrently can fault one side with `EXCEPTION 0e` (fetch at own
RODATA/text or a near-null read in glibc init, pid-attributed since
the fault line carries `pid=` plus the program name). The matrix is
deterministic about the shape: single-heavyweight runs are always
clean (paint/file/vedit/nuklear selftests, `fptest`, lua suite pass
alone and sequentially); an infinite background (Wayland server,
`doomgeneric` attract loop, micropython file churn) plus a big
foreground faults one side within seconds, with no Wayland code on
the failing path (`doomgeneric &` + `paint --selftest` faults doom
with `-14`). Mechanism, closed one layer at a time: legacy
`load_exec_elf` wrote the live window and `g_brk`/VMA with no
preemption guard (now `cli` like the isolated path), `kfd_table`
had no lock or ownership (now `fd_lock` plus `KFILE` refcounts),
`block_read` filled its shared cache line unlocked (now private
fill plus atomic install), whole `kf*` bodies and `unlink` plus
`dir_list` ran unlocked against each other (now `fs_lock`), and
dlmalloc ran with `USE_LOCKS` off despite concurrent allocators
(now on, built-in CAS spin). What remains open is narrower than it
was: image bytes verify clean at load, the initial stack verifies
healthy, yet glibc init still jumps wild under sustained overlap,
so the next audit layer is the preempt park/resume path and the
MiniFS write internals. Until that lands, run heavyweights
sequentially (each alone, as `make wl` does) and treat overlapping
big processes as the known-red configuration instead of a demo
target. The `make wl` desktop is structured exactly that way:
clients attach one by one and exit, the server is then the sole
heavyweight, and the shell stays builtin-only beside it.


### Ramdisk names
File names are at most `RAMDISK_FNAME_LEN - 1` characters. Names may
contain `/`, which is how directories are expressed (`bin/cp`, `objects/ld.o`):
the ramdisk is flat, the slash is data. `mkramdisk.py` derives each name from
the path relative to the shared parent of the packed files, so
`progs/src/cp.c` ships as `src/cp.c` and `progs/bin/cp` as `bin/cp`. A name
longer than the bound or a collision between two files is a build error,
never a silent truncation that would make a lookup miss.

### Filesystem commands
A working directory (`cwd`) and directory-aware builtins, over a merged view
of the ramdisk (flat namespace) and MiniFS (real directory-capable filesystem
on the IDE disk):

- **MiniFS mount is a superblock probe, never a computed LBA.**
  `minifs_mount` tries the computed guess first and then every
  2048-aligned candidate for a magic + version + block-size hit, because
  the `KERNEL_SECTORS` fast path only ever reaches stage2: this unit
  sees the ramdisk-size fallback, which underestimates the kernel image
  and lands before the real partition (every icon, the wallpaper and
  the whole toolchain fallback silently vanished the day the kernel
  grew past the 2048-sector guess). Two companions ride with the
  probe: `block_set_base` invalidates the direct-mapped block cache
  (it is keyed by block number only, so a base change without a flush
  serves the old partition's data), and the probe reads through a
  4 KB scratch buffer, never `block_read` straight into the 48-byte
  superblock (the old code smeared 4096 bytes over the neighbouring
  `.bss` on every boot).
- **Block backend preference is virtio-first, size-gated.** `block_init`
  probes the virtio-blk queue after IDE and prefers it only when it
  carries the same image (equal sector count) or IDE is absent
  (virtio-only hardware); a foreign disk of another size never hijacks
  MiniFS, and the choice is frozen at boot (`block: backend=...`
  marker) so a late-attached disk cannot reroute a mounted filesystem.
  The queue moves at most 16 sectors per request (single head
  descriptor), so wider block reads chunk instead of refusing.
- **Directory reads distrust entry lengths.** `minifs_dir_read` skips
  entries whose name would overflow the 64-byte buffer every caller
  passes or run past the block (resolved paths cap leaves at 63, so
  nothing reachable is hidden; exact lookup still finds them). All
  six callers shared the smash before the guard landed at the choke
  point.
- `pwd` prints the cwd (`/` for root). `cd [dir]` changes it: bare `cd` goes
  to root, `cd ..` pops one level, anything else resolves against the current
  cwd. A directory is any ramdisk name ending in `/` **or** a MiniFS directory
  (checked via `minifs_resolve_path` + `MINIFS_S_IFDIR`). `cd` into a
  nonexistent directory is a diagnostic, never a silent no-op.
- `mkdir <name>` creates a directory entry: an empty file named
  `<resolved name>/`. The parent directory must already exist. Creating a
  directory that already exists is a diagnostic.
- `rm <file>` deletes a file — ramdisk first, MiniFS fallback (writes
  fall back to MiniFS via `kfopen`, so deletes must too, or a file the
  shell just created is undeletable); a missing file is a diagnostic and
  a directory name (trailing `/`) is refused, never silently removed.
- `mv <src> <dst>` renames one file within its filesystem through
  `fs_rename` (`fs/kfile.c`): ramdisk entries rename in place, MiniFS
  entries move directory slots with no data copy, all under `fs_lock`.
  Directories refuse, a missing src is a diagnostic, an existing dst
  refuses (no silent overwrite in v1) and a dst whose parent lives only
  on the other filesystem refuses instead of shadowing a MiniFS
  directory with a volatile ramdisk entry or half-moving across the
  boundary (copy+delete stays explicit). The Linux `rename` syscall (82,
  `MINIOS_SYS_RENAME`, ABI v10) serves the same function to ring-3
  programs with the same user-pointer validation as every other
  dispatcher case; `progs/src/mvrn.c` proves it headless (`mvrn: ok`,
  exit 0, plus the missing-src and kernel-pointer refusals).
- `fat ls <img> [dir]` / `fat cat <img> <file>` read a FAT32 disk
  image stored as an ordinary file (`etc/fat.img`, host-built with
  `mkfs.vfat` + mtools and packed on MiniFS). The driver
  (`fs/fat32.c`, `headers/fat32.h`) is read-only by construction:
  BPB validation, cluster-chain walking and 8.3 traversal with every
  offset bounds-checked against the image size, walks step-bounded,
  depth capped, LFN skipped, write/truncate refusing; the loopback
  backend is ramdisk-first/MiniFS-fallback with the flat-root
  basename rule, exactly like `kfopen`. File bytes flow through the
  real `fat:` VFS driver (`img:fatpath` per open, registered at boot
  and mountable via `mount X fat`), listings through `fat32_list`
  (the VFS table has no readdir verb). Proven by `make test-fat`
  (host suite over a synthetic image: units, multi-cluster reads,
  fail-closed edges) and two BDD scenarios on the reference image
  (list/read plus missing-file/bad-image refusals); the
  `fat-lfn-check-inverted` mutant dies on both.
- `fat ls hd0 ...` reads a real disk partition (primary IDE master)
  through the same parser over absolute LBA sectors: location is a
  probe, never computed (genuine MBR `0x0B`/`0x0C`/`0x1B`/`0x1C`
  entries first, each proven by a BPB read, then a 2048-aligned magic
  scan for superfloppy layouts; GPT protective degrades to the scan).
  `os.img` appends the reference image past swap so the suite
  exercises the device path end to end. Real-hardware rules ride
  along: CHS ignored, LBA28 only, primaries only, a file named `hd0`
  always wins over the device name, and every read funnels through
  the one bounds-checked choke point (a per-backend copy in the read
  loop once forgot the device and went silent; unifying it is what
  keeps   the third backend honest). The `fat-dev-never-found` mutant
  dies on the `hd0` scenario.
- `ext4 ls <img> [dir]` / `ext4 cat <img> <file>` do the same for
  ext4, read-only, over the shared image backend (`fs/fsimg.c`,
  extracted from the FAT driver so the loopback/device contract
  lives once). Served: 1K/2K/4K blocks, 32/64-bit group
  descriptors, extent trees (bounded depth, uninitialized read as
  zeros), legacy direct plus singly-indirect, linear dirs. Refused:
  htree dirs, symlinks, encrypted/inline files, double/triple
  indirect, writes; checksums unverified, journal ignored (last
  consistent state). `hd0` probes a native `0x83` partition the
  same way. Proven by `make test-ext4` (synthetic image: units,
  multi-extent and legacy-indirect reads, fail-closed set) and
  three BDD scenarios (list/read, refusals, `hd0`); the
  `ext4-magic-unchecked` and `ext4-dev-never-found` mutants die on
  the host suite and the `hd0` scenario. The fragment-then-copy
  rule (whole block in, fragment out) is load-bearing: a read
  that copies block-relative bytes for a fragment offset returns
  the wrong bytes with the right length, which only a
  content-checking cross-fragment vector catches.
- `ls [dir]` lists the entries under a directory, defaulting to the cwd,
  names relative to it. At root, both ramdisk and MiniFS entries are shown
  (merged view). In subdirectories, ramdisk entries take priority; when the
  ramdisk has none for that path, MiniFS entries are shown. Directory entries
  appear with their trailing `/`.
- `cat <file> [file...]` prints files in order; with a redirection it
  concatenates them (`cat a b > c`), which is how the MCP marketplace
  reassembles sources larger than the editor buffer. File I/O (`kfopen`)
  checks the ramdisk first, then falls back to MiniFS, so `cat asm/_t.s`
  works even though `asm/` lives only on MiniFS.
- Path resolution is one choke point: `kfopen` and the builtins resolve a
  path against the cwd (leading `/` = root, `..` pops one component) into a
  buffer of `RAMDISK_FNAME_LEN`; a name that does not fit is rejected like
  a missing file, never truncated. `kfopen` refuses directory names, so
  `edit dir/`, `cat dir/` and redirects into a directory fail cleanly.
- **Write fallback to MiniFS (`kfopen`)**: a write (`w`/`a`) goes to the
  ramdisk only when the flat namespace can host it (the parent directory entry
  exists there). When it cannot — e.g. `run objects/minigcc.o p.c > asm/_t.s`
  or a program writing `tmp/...`, neither of which has a parent on the ramdisk
  — `kfopen` falls back to MiniFS, the real directory-capable filesystem,
  auto-creating the parent chain with `minifs_mkdir_p` and creating the file
  with `minifs_create`. This is what fixed the lua and MicroPython in-OS test
  suites: before it, the "refuse to create a ramdisk file when its parent is
  missing" rule silently dropped every redirect into a non-ramdisk directory,
  so `ld` could not open the freshly compiled `_t.s`. MiniFS-backed writes
  flush through `minifs_write`, and `kfclose` calls `minifs_sync` so the block/
  inode bitmaps stay consistent across reboots. `fstat`/`access`/`unlink`
  report and operate on MiniFS-backed files too.
  A latent bug in `minifs_write` (minifs.c) surfaced when this path became
  reachable: after `minifs_inode_alloc_block` mapped a fresh block into the
  *local* inode struct, an `fs_read_inode` reload wiped that mapping (the inode
  is only persisted by the `fs_write_inode` at the end of the function), so the
  data landed in a block the on-disk inode never referenced and the file read
  back as zeros. The reload was removed; the block pointer now survives to the
  end-of-function inode write.
  The ramdisk half of the parent check is ramdisk-only on purpose: the old
  code asked `fs_dir_exists` (either filesystem) but always created on the
  ramdisk, so the second and later files under a MiniFS-only directory were
  captured by volatile ramdisk and vanished on reboot (the parent test also
  appended a second `/`, which could never match a ramdisk prefix at all).
  `saves/` is the persistent user-data directory by convention (Pokemon
  battery + savestates); rebuilding the images preserves it (see below).
- **Image rebuilds preserve `saves/`**: `make minifs.bin` and `make os.img`
  extract the live `saves/` tree out of the previous `os.img`
  (`tools/minifs_saves.py`, byte-exact, fail-closed on compressed or
  double-indirect files, which the guest write path never produces) and pack
  it back into the fresh image via `mkfs.minifs.py`, so a rebuild never wipes
  runtime saves. Only doom maps (`*.wad`, `*.txt`) and Pokemon saves
  (`*.sav`, `*.rtc`, `*.state`) persist (`PERSIST_SUFFIXES`); minicraft
  chunks regenerate in-game and are skipped with a log line, never packed. The `os.img` rule refreshes `minifs.bin` the same way because
  a kernel-only rebuild re-embeds it and would otherwise clobber the live
  partition with the stale artifact. Not even `make clean` loses saves:
  it snapshots them to `saves-backup/` first (no-op when there is nothing
  to save), and the image rules reseed from there when `os.img` has
  nothing to carry forward — so clean + rebuild restores the partida
  byte-identical. `saves-backup/` is gitignored; copy it elsewhere for
  off-machine backup.
- `ps` lists the live process table (`pid ppid state name` from `procs[]`,
  snapshot under `sched_lock` then printed after release, so console I/O
  never runs with the scheduler lock held). `jobs` lists the shell's live
  children, `wait [pid]` reaps, `kill <pid>` terminates a real target.
- `mem` reports heap use/free (dlmalloc), ramdisk use/cap/max, MiniFS free
  blocks/inodes and live process count: the first thing to read when a
  load stops loading, before blaming the game.
- `minifetch` prints the neofetch-style screen (`kernel/minifetch.c`): the
  left column renders `icons/doom.png` live as brightness ASCII (embedded
  text fallback when undecodable) and the right column lists OS/ABI,
  uptime, CPUs, procs, memory, disk, display, MAC/IP, date and toolchain,
  each fact reused from the accessor its builtin owns. BDD asserts the
  header, OS and toolchain lines over serial.
- `kstack` reports kernel-stack health: per-proc high-water marks plus the
  legacy 32 KB syscall stack, ending in `kstack: ok` (or `OVERFLOW`). Every
  pool slot is paint-filled at claim time with a canary word at its bottom
  (`sched.c`), so a stack that overruns into its neighbour's slot is
  detected instead of corrupting silently; the legacy slot paints at
  `sched_init`. BDD asserts `kstack: ok` after boot and after a threaded
  run. This is the instrument for the historical intermittent black-screen
  class (a fault with no recovery halts the machine with no serial after
  the banner): the next black screen gets a `kstack` reading first instead
  of a guess.
- The prompt stays `miniOS> `: the cwd is reported by `pwd`, so the MCP
  marker wait keeps working unchanged.

### Syscall tracing
`trace` prints the current state; `trace on` / `trace off` set it (off by
default). While tracing, every Linux-ABI syscall is reported on the console
as `syscall <n>(a1, a2, a3, ...) = <result>`, so a program's dialogue with
the kernel can be watched from outside without a debugger. Three syscalls are
never traced — `SYS_TIME` (204), `SYS_KBD` (205), `SYS_MOUSE` (219) — because
they are poll/clock reads that a pacing spin loop hammers thousands of times
a second; tracing them flooded the console and made `trace on` turn an
interactive program into a 100 ms-per-syscall crawl. All other syscalls are
traced one-to-one so a short program's full dialogue stays visible. `make gdb`
boots QEMU with the gdb stub (`-s -S`) for register-level debugging;
`gdb -ex 'target remote :1234' -ex 'add-symbol-file kernel.elf 0x100000'`
attaches to the 64-bit kernel.

### Observability / dissection toolbox (`strace`, `vmmap`, `schedtop`, `irqstat`, `bootlog`, `gdb`, `ltrace`)
Seven shell builtins answer "what is the system doing right now" without
leaving the machine; all state is snapshotted under the owning lock and
printed after release, so console I/O never runs with `sched_lock` held.

- `trace [on|off|verbose|quiet]`: `verbose` (also the `strace` default)
  prints the resolved name (`syscall_name`, Linux table then MiniOS
  window then the out-of-table Linux numbers the dispatcher answers) plus
  a decoded hint — the path string for `open/openat/access/unlink/
  readlink` (at most 48 chars, only after `user_str_ok`, else
  `<bad-ptr>`), `code=` for `exit/exit_group`, `addr=` for `brk`,
  `len=` for `mmap`, `fd/len` for `read/write`, `pid=` for
  `kill/wait4`. Numeric mode is the legacy `syscall <n>(...)` format.
- `strace <cmd> [args...]`: runs one shell command with verbose tracing
  held on, then restores the previous mode (`trace off` state included).
  Every line prints atomically after dispatch returns: the path hint is
  snapshotted before dispatch (max 48 bytes, only after `user_str_ok`),
  the whole `syscall name(...) hint = ret` line prints after, so program
  output never interleaves mid-line. A program that prints without a
  trailing newline still leaves its partial line first — its bytes, not
  a corruption. Zero traced syscalls is itself a diagnosis: the target
  never crossed into ring 3 (a shell builtin), so `strace` names it and
  suggests a ring-3 target instead of printing a bare `done`.
- `ltrace <cmd> [args...]`: honest proxy, stated up front on every run:
  static ELFs carry no PLT to hook, so true function-level tracing is
  impossible in-guest; it runs the `strace` path so the
  allocator-backed traps `malloc/free` actually take
  (`brk/mmap/munmap/mprotect/open/close`) stay visible.
- `vmmap [pid]`: the user-window map from `progs/minios_abi.h`
  (text/data, brk cur/cap, mmap cur/cap, game/fb/Nuklear reserved slots,
  1 MB stack) plus the live VMA tree walked bounded (64-deep explicit
  stack, 128 regions, then `truncated`). Pid 0 / the running view reads
  the `g_brk` globals; any other pid reads its saved per-proc view.
- `schedtop`: uptime from `sys_ticks`, per-CPU current pid plus
  `dispatched/polls`, then one row per proc (state, nice, `vruntime`,
  consumed `cpu_ticks`).
- `irqstat`: ISR arrivals per source — `timer` from `sys_ticks` (100 Hz
  PIT + BSP IPI broadcast), `kbd`/`mouse`/`sb16` counted at the top of
  their `isr_dispatch` arms (`isr_cnt_*`), `bad_gs` from the GS guard —
  plus NIC queue health (`rtl_counters`, `net_rx_dropped`), `sb16`
  submits/drops and `gfx frames`.
- `bootlog`: six timestamped phases marked in `kmain`
  (`entry/heap/mm+fb/block+minifs/sched/smp+audio-ready`) in ms since
  power-on (pre-`sched_init` marks are TSC-derived, still monotonic).
- `gdb [regs [pid] | dump <addr> <len> | qemu]`: the in-OS inspector
  half. `regs` dumps the stored context (`proc_t.ctx`, `cr3`, `kstack`);
  the running pid prints LIVE-sampled `rip/rsp/rflags/cr3` instead
  (GPRs are refused, not forged: the call path clobbers them, so only
  preempted pids show truthful GPRs). `dump` hexdumps 1..256 bytes;
  operands are decimal or `0x`-hex through `shell_parse_u64` (strict,
  fail-closed on garbage/overflow). A fault whose rip and rsp both lie
  in the kernel heap additionally prints 16 bytes at rip (`heapcode`)
  and 4 words at rsp (`heapstack`): a #GP there is usually an
  alignment fault in ring-0 code, and the opcode bytes name it without
  a debugger attached. A remote RSP stub is deliberately out
  of scope: the serial console belongs to the shell, so a stub here would
  fight the prompt for every byte; `gdb qemu` prints the `make gdb` +
   `target remote :1234` hookup for real breakpoints and single-step.

Numeric shell operands are strict at one choke point. `katol` stays lax on
purpose (it is exported to ring-0 programs as `atol`/`strtol`, and the C
library idiom stops at the first non-digit), so no builtin may use it for
argument parsing: `wait`, `kill`, `vmmap`, `nice`, `seccomp`, `rlimit` and
`sleep` parse through `shell_parse_long` (optional sign, full-string,
overflow fail-closed, shared via `shell.h`), and the editor's line numbers
(`g`, `l`, `i`) use the same function instead of a second copy. The digit
loop itself lives once in `shell_parse_mag`, behind `shell_parse_u64`
(hex-aware, inspector operands), `shell_parse_long` (signed, shell/editor
operands), `shell_parse_vol` (which only adds the 0..100 clamp) and
`shell_parse_pid` (which only adds the `min_pid <= pid < MAX_PROCS` range,
so `wait`/`kill` use min 1 and `vmmap` uses min 0 with no per-site copy).
Garbage
is always a diagnostic (`kill 12abc` is `usage: kill <pid>`, never pid 12),
and silent zeroing is gone (`rlimit as abc` no longer zeroes the cap,
`nice abc` no longer resets niceness). Pinned by BDD scenarios and the
`kill-wait`/`rlimit`/`sleep`-`garbage-accepted` mutants.

### Editor (`edit`)
A command-driven line editor over ramdisk/MiniFS files, in its own contract
`kernel/editor.c` (header `editor.h`), extracted from the shell.  The core
commands are `h l p e a i d w x q q!`; on top of them it carries a
nano-style status — `g N` go to line, `n`/`b` next/previous, `.` current,
`/ text` search, `=` status, and `l [a [b]]` range listing — and marks a
modified buffer with a `*` in the prompt and a truncated one with `!`.  Text
entry for `e`/`a`/`i` reuses the shell's arrow-key line reader
(`shell_readline_buf`, exported via `shell.h`), so editing a line has the
same mid-line cursor behaviour as the prompt.  Two invariants:
- A buffer that did not hold the whole file is marked truncated and refuses
  to be written back, because saving it would drop what was never loaded.
- `q` refuses to discard unsaved changes; `q!` discards explicitly.
