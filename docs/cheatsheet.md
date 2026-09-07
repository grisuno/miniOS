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
| `rm <file>` | delete a ramdisk file (directories refused) |
| `echo <text>` | print text |
| `edit <file>` | line editor over ramdisk/MiniFS files |
| `run <name\|file>` | run a program: `.o` at ring 0, `.elf` at ring 3, `.cvm` on the interpreter |
| `<cmd> [args]` | bare run: same as `run`, resolved by suffix (`objects/`, `bin/`, `cvm/`) |
| `load <file>` | load an ELF (`.o` relocatable or Linux executable) |
| `sh <script.sh>` | run a shell script file |
| `cmd > file` / `cmd >> file` | redirect output (truncate / append); exit codes stay on console |
| `ps` | list registered programs |
| `smp` | per-CPU state, dispatches, runqueue hits/steals/drops |
| `net` | NIC status (MAC, IP, counters); `net ping <ip>` sends one ICMP echo |
| `trace [on\|off]` | trace Linux-ABI syscalls (time/kbd/mouse excluded) |
| `date` | CMOS clock `HH:MM:SS` |
| `vol [0-100]` | print or set the PC-speaker volume (0 = mute) |
| `sb16` | Sound Blaster 16 ring health and counters |
| `perf` | guest CPU / clock / console throughput diagnostics |
| `gfx [...]` | graphics state; `gfx pixel x y`, `gfx frames` (composited frame counter) |
| `wm [op]` | window ops: `state`, `minimize`, `maximize`, `close` |
| `hash <file>` | XXH64 checksum of a file |
| `zip <out> <f...>` / `unzip <z> [dir]` | create / extract ZIP archives (`unzip -l` lists) |
| `clear` | clear the screen |
| `poweroff` | ACPI power off (ends QEMU runs and BDD scenarios) |

## External commands (on MiniFS / ramdisk `bin/`)

| Command | Effect |
|---------|--------|
| `cp <src> <dst>` | copy a file |
| `lzss` / `unlzss` | Okumura LZSS compress / decompress (`-d` forces decode) |
| `lz4` / `unlz4` | LZ4 compress / decompress over syscalls 216/217 |
| `json <file> [path]` | validate + pretty-print; dotted path query (`.a.b`, `.a.3`) |
| `aes` / `unaes` | AES-256-CTR file cipher (`-d` forces decrypt) |
| `freedom <url>` | headless text browser (`--dump-css`, `--dump-dom`) |
| `micropython` / `lua` | REPL or script (`-c` / file arg); `minios` module for kernel services |

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
| TAB | complete (twice lists candidates on ambiguous prefix) |

## Editor commands

`h` help, `l [a [b]]` list range, `p` print, `e` edit line, `a` append,
`i` insert, `d` delete, `w` write, `x` write+quit, `q` quit (refuses with
unsaved changes), `q!` quit discarding, `g N` go to line, `n` / `b`
next / previous, `.` current line, `/ text` search, `=` status. A `*`
marks a modified buffer, `!` a truncated one (refuses to write).

## Window keys (Alt is the WM modifier)

Alt+Enter toggle fullscreen, Alt+arrows snap to half, Alt+Home/End snap
to quadrant, Alt+`[`/`]` shrink/grow width, Alt+`-`/`=` shrink/grow both,
Alt+0 reset, Alt+M minimize, Alt+X / Alt+Q close, F11 fullscreen, F5 reset.

## Make targets (host)

| Target | Effect |
|--------|--------|
| `make` / `os.img` | build the full image (zero warnings required) |
| `make sources` | clone missing sibling repos (never touches existing dirs) |
| `make run` / `run-kvm` / `run-headless` | boot with display / KVM / serial only |
| `make debug` / `serial` | boot for gdb / serial console |
| `make test` | behavioural suite |
| `make test-host` | all fast host suites at once |
| `make test-sync test-vma test-futex test-percpu-rq test-batch test-rcu test-sanitize test-tick test-hal` | individual host suites |
| `make test-tls` | crypto vectors + OpenSSL-driven TLS 1.2 handshakes |
| `make selfhost` | bootstrap fixed-point check (`g3.s == g4.s`) |
| `make clean` | remove every build product (also drops `saves/`) |

## Host harnesses

```sh
tools/boot_run.sh "cmd1" "cmd2" --timeout 80 --log run.log
./test_bdd.sh                       # full serial-console suite
./tools/test_codecs.sh              # lzss/lz4/aes roundtrips (pass=3)
./mutate.sh                         # kernel/boot mutants, all must die
python3 tools/minios_gui.py send "run doomgeneric.elf" sleep 10 dump shot
```

## Layout

Ramdisk (flat, `/` is data): `objects/` ET_REL toolchain, `bin/` Linux
ELFs + command path, `cvm/` CVM modules, `src/` C sources, `asm/`
miniGCC output, `docs/`. MiniFS (real directories, persists `saves/`
across rebuilds): big ELFs (`doomgeneric.elf`, `micropython.elf`,
`lua.elf`, `nuklear.elf`, `piano.elf`, `quake2generic.elf`), WAD/PAK
data, `aes`/`json`/`freedom`/`lzss`/`lz4` tools.

## Syscall numbers (source of truth: `progs/minios_abi.h`)

Linux ABI `0-199`; MiniOS `200-299`: 201-203 TLS handshake/send/recv,
204 time, 205 keyboard, 206 palette, 207 raw keyboard, 208 VGA mode,
209/210 speaker init/tone, 211 DOOM frame, 215 spawn, 216/217 LZ4
compress/decompress, 219 mouse, 220 Nuklear frame, 221/222 PCM
open/submit, 223 graphics window title, 226/227 futex wait/wake, 235
batch submit (NOP/YIELD/TIME/GETPID only).
