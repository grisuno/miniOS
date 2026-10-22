# MiniOS Cheatsheet

One-line lookups for the shell, editor, build and host tooling. Inside
the guest the prompt is `miniOS>`; in the editor it is `edit>`.
`CLAUDE.md` is the normative contract, this file is the index.

## Shell builtins

| Command | Effect |
|---------|--------|
| `help` | command summary (also printed above) |
| `ls [dir]` | list ramdisk entries under a directory (default: cwd) |
| `lsfs` | list files on the MiniFS disk filesystem |
| `cat <f> [f...]` | print files; `cat a b > c` concatenates |
| `catfs <file>` | print a file from MiniFS |
| `cd [dir]` / `pwd` | change / print working directory (`cd` alone goes to root, `cd ..` pops) |
| `mkdir <name>` | create a directory entry (parent must exist) |
| `rmdir <dir>` | remove an empty directory |
| `rm <file>` | delete a file (ramdisk first, MiniFS fallback; directories refused, use `rmdir`) |
| `mv <src> <dst>` | rename within one filesystem (existing dst, directories and cross-filesystem moves refused) |
| `fat ls <img> [dir]` / `fat cat <img> <file>` | read-only FAT32 loopback image browser (`etc/fat.img` ships one) |
| `fat ls hd0 /` / `fat cat hd0 <file>` | same driver on a real disk partition (MBR FAT32 entry first, magic scan fallback) |
| `ext4 ls <img> [dir]` / `ext4 cat <img> <file>` | read-only ext4 loopback/partition browser (`etc/ext4.img` ships one, `hd0` probes `0x83`) |
| `echo <text>` | print text |
| `edit <file>` | line editor over ramdisk/MiniFS files |
| `run <name\|file>` | run a program: `.o` at ring 0, `.elf` at ring 3, `.cvm` on the interpreter |
| `<cmd> [args]` | bare run: same as `run`, resolved by suffix (`objects/`, `bin/`, `cvm/`) |
| `load <file>` | load an ELF (`.o` relocatable or Linux executable) |
| `sh <script.sh>` | run a shell script file |
| `cmd > file` / `cmd >> file` | redirect output (truncate / append); exit codes stay on console |
| `cmd 2> file` | same capture (MiniOS merges stdout/stderr at the console) |
| `a \| b [\| c]` | pipe stdout of each stage into stdin of the next (sequential capture); bare `cat` copies stdin |
| `panic` | paint the kernel panic screen (vector/RIP/RSP/backtrace), demo without halting |
| `mount [prefix driver]` / `unmount <prefix>` / `vfstest` | list, add/drop (ramdisk/minifs/mem/fat/ext4) and prove VFS mounts; busy refuses, `/` pinned |
| `httpd [--once] <port> [root]` / `httpd --selftest` | static file server over server TCP (GET, any VFS root) / headless handshake proof |
| `clip [text\|clear]` | shared text clipboard: publish, print, empty (4096 byte cap, never truncates) |
| `vblk` | virtio-blk probe: LBA 0 boot signature + MiniFS superblock off the virtio queue |
| `nvme` | NVMe probe: LBA 0 boot signature + MiniFS superblock |
| `vnet` | virtio-net probe: MAC, link state, one TX frame through the queue |
| `usb` | xHCI controller, devices, HID state and disk counters |
| `ps` | list live processes (pid/ppid/state) |
| `jobs` / `wait` / `kill` | list / reap / terminate background jobs (`&` starts one) |
| `sleep <secs>` | yield until the wall clock advances (Ctrl+C aborts) |
| `mrun <a.elf> [...]` | run isolated ELFs concurrently (multitask) |
| `smp` | per-CPU state, dispatches, runqueue hits/steals/drops |
| `net` | NIC status (MAC, IP, counters); `net ping <ip>` sends one ICMP echo |
| `trace [on\|off\|verbose\|quiet]` | trace Linux-ABI syscalls, numeric or named+decoded (noisy slots: 204, kbd, mouse, raw keyboard) |
| `strace <cmd> [args]` | run one command with verbose syscall tracing, then restore mode |
| `ltrace <cmd> [args]` | no-PLT proxy: allocator-trap view (`brk/mmap/mprotect/open/close`) |
| `vmmap [pid]` | user-window map (text/brk/mmap + game/fb/nk/rgb/stack) + live VMA tree |
| `schedtop` | uptime, per-CPU cur, one row per thread (tgid group, T/P flag, state/nice/vruntime/ticks) |
| `irqstat` | ISR arrivals: timer/kbd/mouse/sb16 + net/sb16 queues + gfx frames |
| `bootlog` | timestamped boot phases in ms since power-on |
| `sclog <pid>` | last syscalls of a process (kernel flight recorder) |
| `gdb regs [pid]` / `gdb dump <a> <l>` / `gdb qemu` | in-OS inspector (LIVE regs for running pid; decimal/`0x` addr; 1..256 bytes) / remote-GDB hookup |
| `kstack` | kernel-stack high-water marks + canary (`kstack: ok`) |
| `date` | CMOS clock `HH:MM:SS` |
| `clock` | wall and monotonic clock, two reads (backwards check) |
| `kbd [en\|es]` | print or set the keyboard layout |
| `vol [0-100]` | print or set the PC-speaker volume (0 = mute) |
| `rlimit [as\|cpu\|nofile] [v]` | caps: address space bytes, CPU ticks, open files |
| `nice [n]` | scheduler niceness of the current process (-20..19) |
| `seccomp <deny\|allow> <n>` | deny or allow one MiniOS syscall (200..231) |
| `sb16` | Sound Blaster 16 ring health and counters |
| `perf` | guest CPU / clock / console throughput diagnostics |
| `gfx [...]` | graphics state; `gfx pixel x y`, `gfx frames` (composited frame counter) |
| `fx [on\|off]` | melt effect state (melts completed) |
| `wm [op]` | window ops: `state`, `minimize`, `maximize`, `close`, `split`, `list`, `tile`, `focus` |
| `desktop [stop\|status]` | Wayland session: tile NK apps as windows |
| `hash <file>` | XXH64 checksum of a file |
| `mem` | heap, ramdisk, MiniFS and process pressure |
| `minifetch` | system screen (logo and specs) |
| `zip <out> <f...>` / `unzip <z> [dir]` | create / extract ZIP archives (`unzip -l` lists) |
| `clear` | clear the screen |
| `poweroff` | ACPI power off (ends QEMU runs and BDD scenarios) |

## External commands (on MiniFS / ramdisk `bin/`)

| Command | Effect |
|---------|--------|
| `cp <src> <dst>` | copy a file |
| `lzss` / `unlzss` | Okumura LZSS compress / decompress (`-d` forces decode) |
| `lz4` / `unlz4` | LZ4 compress / decompress over syscalls 216/255 |
| `json <file> [path]` | validate + pretty-print; dotted path query (`.a.b`, `.a.3`) |
| `aes` / `unaes` | AES-256-CTR file cipher (`-d` forces decrypt) |
| `freedom <url>` | headless text browser (`--dump-css`, `--dump-dom`) |
| `micropython` / `lua` | REPL or script (`-c` / file arg); `minios` module for kernel services |
| `lisp` | Lisp interpreter (REPL or script; `lisp src/test.lisp` runs the in-OS suite) |
| `python3` / `pip` | CPython 3.12 (script or `-c`); `pip` installs wheels offline |

## Toolchain loop (inside the OS)

```
edit src/p.c
run objects/minigcc.o src/p.c > asm/p.s
run objects/ld.o -f elf -o bin/p.elf asm/p.s
run bin/p.elf
run objects/ld.o -f cvm -o cvm/p.cvm asm/p.s
run cvm/p.cvm
```

## Prompt keys

| Keys | Effect |
|------|--------|
| Up / Down | history recall by typed prefix (empty line = chronological) |
| Right at end of line | accept the suggestion |
| Left / Right, Home / End | move cursor |
| Delete / Backspace | delete at / before cursor |
| Ctrl+A / Ctrl+E | start / end of line |
| Ctrl+U / Ctrl+K | kill to start / end |
| Ctrl+W | kill word before cursor |
| TAB | complete (twice lists candidates on ambiguous prefix); argument words complete MiniFS paths too |

## Editor commands

`h` help, `l [a [b]]` list range, `p` print, `e` edit line, `a` append,
`i` insert, `d` delete, `w` write, `x` write+quit, `q` quit (refuses with
unsaved changes), `q!` quit discarding, `g N` go to line, `n` / `b`
next / previous, `.` current line, `/ text` search, `=` status. A `*`
marks a modified buffer, `!` a truncated one (refuses to write).

## Window keys (Alt is the WM modifier)

Alt+Enter toggle fullscreen, Alt+arrows snap to half, Alt+Home/End snap
to quadrant, Alt+`[`/`]` shrink/grow width, Alt+`-`/`=` shrink/grow both,
Alt+0 reset, Alt+M minimize, Alt+X / Alt+Q close, Alt+Tab focus next,
Super+Tab tile, F11 fullscreen, F5 reset.

## Make targets (host)

Full target list (every target and its purpose): `docs/spec/build-run.md`.

| Target | Effect |
|--------|--------|
| `make` / `os.img` | build the full image (zero warnings required) |
| `make sources` | clone missing sibling repos (never touches existing dirs) |
| `make update [repo...]` | bring the newest sources: all of them, or only the named ones (`make update freedom`) |
| `make run` / `run-kvm` / `run-headless` | boot with display / KVM / serial only |
| `make debug` / `serial` | boot with the QEMU monitor on stdio / boot on the serial console |
| `make test` | behavioural suite |
| `make test-host` | all fast host suites at once |
| `make test-sync test-vma test-futex test-percpu-rq test-batch test-rcu test-sanitize test-tick test-hal` | individual host suites |
| `make test-tls` | crypto vectors + OpenSSL-driven TLS 1.2 handshakes |
| `make selfhost` | bootstrap fixed-point check (`g3.s == g4.s`) |
| `make clean` | remove every build product (snapshots `saves/` into `saves-backup/` first) |

## Host harnesses

Full toolbox guide: `docs/debug_tools.md` (in-OS tools, MCP bridge, recipes,
image-budget notes).

```sh
tools/boot_run.sh "cmd1" "cmd2" --timeout 80 --log run.log
./tools/test_bdd.sh               # full serial-console suite
./tools/test_codecs.sh              # lzss/lz4/aes roundtrips (pass=3)
./tools/mutate.sh                 # kernel/boot mutants, all must die
python3 tools/minios_gui.py send "run doomgeneric.elf" sleep 10 dump shot
```

## Layout

Ramdisk (flat, `/` is data): `objects/` ET_REL toolchain (`minigcc.o`,
`ld.o`, `cvm.o`, `stb.o`, `xxhash.o`, `dlmalloc.o`), `bin/` command path
(`cp`, `mtop`), `src/` sources and scripts, `etc/`, `docs/`. MiniFS (real
directories, persists `saves/` across rebuilds): big ELFs
(`doomgeneric.elf`, `quake2generic.elf`, `micropython.elf`,
`python3.elf` when the CPython checkout exists, `lua.elf`, `lisp.elf`,
`topogpt3.elf`, `nuklear.elf`, `piano.elf`, `paint.elf`, `vedit.elf`,
`doomedit.elf`, `file.elf`, `wlcomp.elf`, `minicraft.elf`), CVM modules
(`cvm/*.cvm`), miniGCC output (`asm/*.s`), WAD/PAK data,
`aes`/`json`/`freedom`/`lzss`/`lz4` tools.

## Syscall numbers (source of truth: `progs/minios_abi.h`)

Linux ABI `0-199`; MiniOS `200-299`: 201 Linux time, 202 Linux futex,
203 retired (-ENOSYS), 205 keyboard, 206 palette, 207 raw keyboard,
208 VGA mode, 209/210 speaker init/tone, 211 DOOM frame, 215 spawn,
216/255 LZ4 compress/decompress, 219 mouse, 220 Nuklear frame, 221/222
SB16 open/submit, 223 graphics window title, 226/227 futex wait/wake,
235 batch submit (NOP/YIELD/TIME/GETPID only), 246/247 PCM2 open/write,
249/250 clipboard set/get, 254 time.
