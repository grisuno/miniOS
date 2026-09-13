# MiniOS Debug Tools

The dissection toolbox: every in-OS observability builtin, the MCP bridge
that drives them from an agent, and the host harnesses that prove them.
Normative contract: `CLAUDE.md` ("Observability / dissection toolbox").
One-line index: `docs/cheatsheet.md`.

Doctrine: everything is serial-observable. State is snapshotted under the
owning lock and printed after release, so console I/O never runs with
`sche_lock`-class locks held. A tool that cannot observe something says so
on screen instead of printing a forged number.

## In-OS toolbox

| Tool | Sees | Answers |
|------|------|---------|
| `trace` | syscalls, numeric or named | what is the system doing right now? |
| `strace` | syscalls, named + decoded | how does userland ask the kernel for resources? |
| `ltrace` | allocator-trap subset | what does `malloc` trap to? (no PLT on static ELFs) |
| `vmmap` | user window + VMA tree | where do my code, heap and mappings live? |
| `mem` | heap/ramdisk/minifs/procs | what is exhausted? |
| `schedtop` | scheduler state | who owns the CPU and why? |
| `irqstat` | interrupt arrivals | is the hardware talking, is the guest keeping up? |
| `bootlog` | boot phases with ms | where did boot time go? |
| `gdb` | contexts, memory, remote hookup | what is the value RIGHT NOW? |
| `ps` / `jobs` | processes / shell children | what exists, what finished? |
| `kstack` | kernel-stack high water + canary | did a stack overflow? |
| `smp` / `sb16` / `net` / `gfx` | subsystem status | per-domain health |

### trace / strace

```
miniOS> trace verbose
syscall tracing: on (verbose)
miniOS> strace run bin/lxhello.elf
Hello from a REAL Linux ELF executable (syscall ABI)!
syscall write(1, 4202496, 54, ...) fd=1 len=54 = 54
syscall exit(1, ...) code=1 = 1
exit code: 1
strace: done (tracing restored on)
```

- `trace [on|off|verbose|quiet]`. Verbose resolves names (`syscall_name`:
  Linux table, then MiniOS window, then a data table of out-of-table
  Linux numbers) and decodes: path strings for `open/openat/access/
  unlink/readlink`, `code=` for exit, `addr=` for brk, `len=` for mmap,
  `fd/len` for read/write, `pid=` for kill/wait4.
- `SYS_TIME` (204), `SYS_KBD` (205), `SYS_MOUSE` (219), `GETC_RAW` (236)
  are never traced: pacing loops hammer them and tracing turned
  interactive programs into a crawl.
- Zero traced syscalls is itself a diagnosis: `strace minifetch` prints
  `strace: 'minifetch' is a shell builtin (ring 0): nothing to trace`
  plus the count (`done (0 syscalls, ...)`). Builtins never cross into
  ring 3, so there is nothing to trace; use `strace run bin/lxhello.elf`
  for a real dialogue.
- Each traced line is printed atomically AFTER dispatch returns: the path
  hint is snapshotted before (max 48 bytes, only after `user_str_ok`,
  else `<bad-ptr>`), the whole line prints after, so program output never
  interleaves mid-line. A program that prints without a trailing newline
  still leaves its partial line before the trace line: that is the
  program's bytes, not a corruption.

### ltrace

```
miniOS> ltrace run bin/lxhello.elf
ltrace: no PLT on static ELFs; brk/mmap/mprotect/open/close only
...
```

Honest proxy, stated on every run: static ELFs carry no PLT to hook, so
function-level tracing is impossible in-guest. It runs the `strace` path
so the traps `malloc`/`free` actually take stay visible. True per-symbol
tracing is host-GDB work (`make gdb` + `break malloc`).

### vmmap

```
miniOS> vmmap
vmmap: pid=0 (kernel) window 0x400000..0xc000000
  text 0x400000..0x403000  brk 0x403000 cap 0xb000000  mmap 0xb000000..0xbf00000
  game 0xb000000  fb 0xb200000  nk 0xb600000  stack 0xbf00000..0xc000000
  vma-live: (empty)
```

Pid 0 / the running view reads the `g_brk` globals; any other pid reads
its saved per-proc view. The VMA walk is bounded (64-deep explicit
stack, 128 regions, then `truncated`).

### schedtop / irqstat / bootlog

```
miniOS> schedtop
schedtop: up 4s ticks 448 cpus 1
  cpu0 cur=0 dispatched=0 polls=0
  pid  ppid state nice vruntime ticks name
  0    -1   run   0    0        0     kernel
miniOS> irqstat
irqstat: timer=463 kbd=1 mouse=13 sb16=0 bad_gs=0
irqstat: net tx=0 rx=0 drop=0 sb16 sub=0 drop=0 gfx=0
miniOS> bootlog
bootlog: 6 phases (ms since power-on)
  +     1ms entry
  +     1ms heap
  +     3ms mm+fb
  +    12ms block+minifs
  +   570ms sched
  +  1970ms smp+audio-ready
```

- `timer` counts `sys_ticks` (100 Hz PIT + BSP IPI broadcast);
  `kbd`/`mouse`/`sb16` are counted at the top of their `isr_dispatch`
  arms (`isr_cnt_*`, increment-only, lock-free single words).
- Pre-`sched_init` boot marks are TSC-derived, still monotonic.

### gdb (in-OS half)

```
miniOS> gdb regs 0
gdb: pid=0 (kernel) state=2 LIVE (sampled now)
gdb: rip=0x10f9dd rsp=0x8f1c0 rflags=0x246 cr3=0x1000 kstack=0x2c7a40
gdb: gprs not shown: live gprs are clobbered by this call
miniOS> gdb dump 0x400000 16
gdb: 0x400000: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
```

- `regs [pid]`: the running pid prints LIVE-sampled `rip/rsp/rflags/cr3`
  (read without a trap via `mov`/`pushfq`/return-address); GPRs are
  refused, not forged, because the call path clobbers them. Preempted
  pids print the full parked context. `regs` on pid 0 used to print
  zeros; that was a placeholder, now it samples.
- `dump <addr> <len>`: 1..256 bytes. Operands are decimal or `0x`-hex,
  strictly validated (no signs, no trailing garbage, fail-closed on
  overflow): `gdb dump 0x400000 16` and `gdb dump 4194304 16` agree.
- `gdb qemu` prints the remote hookup. A serial RSP stub is deliberately
  out of scope: the console belongs to the shell, so a stub would fight
  the prompt for every byte. Real breakpoints/single-step:
  `make gdb`, host `target remote :1234` +
  `add-symbol-file kernel.elf 0x100000` (ring-3 ELF: base `0x400000`).

## MCP bridge (agent-driven debugging)

`mcp/minios_mcp.py` (stdlib only, one QEMU child on a pty, marker waits
capped by `timeout_ms`). The debug loop is: `minios_boot` once, then
`minios_send` / `minios_expect` / `minios_snapshot`, assert with
`minios_test`, `minios_poweroff` when done.

| Tool | Use for debugging |
|------|-------------------|
| `minios_status` | `{booted, pid, log_bytes, log_cap}`; never fails |
| `minios_boot` | spawn QEMU, wait for `miniOS> `; idempotent |
| `minios_send` | send one shell line, return output up to next prompt (`exit code: N` surfaces here) |
| `minios_expect` | wait for a marker (cursor advances past the match) |
| `minios_snapshot` | tail of the log since the cursor (peek) |
| `minios_write` / `minios_cat` | upload / print ramdisk files (`[A-Za-z0-9._/-]`, printable ASCII, editor limits enforced up front) |
| `minios_python` | run a Python snippet inside the bridge process |
| `minios_test` | send commands, assert `expect` markers present / `refute` absent; returns `{pass, failures, transcript}` |
| `minios_addons` / `minios_install` | marketplace: build inside the OS, verify exit codes, record in `var/lib/addons.txt` |
| `minios_poweroff` | clean shutdown, releases the pid file |

Tests: `python3 -m unittest -v mcp/test_minios_mcp.py` (unit + QEMU BDD,
skips cleanly without QEMU/image); `mcp/mutate_mcp.sh` (every mutant
killed, parallel via `MUTATE_JOBS`).

## Host harnesses

```sh
tools/boot_run.sh "strace run bin/lxhello.elf" "vmmap" --timeout 90 --log run.log
./test_bdd.sh                       # full serial-console suite
./tools/test_codecs.sh              # lzss/lz4/aes roundtrips (pass=3)
./mutate.sh                         # kernel/boot mutants, all must die
python3 tools/test_gui_wm.py        # QMP pixel proof (Alt+Tab/tile/taskbar)
python3 tools/test_gui_fashion.py   # one cursor, stable frames, ESC quit
python3 tools/test_gui_icon_cwd.py  # dock launch ignores shell cwd
make gdb                            # QEMU -s -S gls; host attaches :1234
```

`tools/minios_gui.py` is mandatory for VGA-mode work: headless boots
cannot observe desktop events. `sh src/test_all.sh` (79 PASS) covers the
toolbox non-interactively (`trace-verbose`, `strace`, `ltrace`, `vmmap`,
`schedtop`, `irqstat`, `bootlog`, `gdb`, `gdb-regs`, `gdb-dump-hex`).

## Recipes

- What does `printf` do? `strace run bin/lxhello.elf`: one `write` per
  flush, `exit` with `code=`.
- Where is my memory? `vmmap <pid>`: brk cur/cap vs mmap cur/cap; a
  growing `vma-live` list with no matching `munmap` in `strace` is a leak.
- Who is slow? `schedtop` (ticks/vruntime per proc) + `irqstat` (timer
  flowing?) + `perf` (console throughput vs ktime overhead).
- Did the stack overflow? `kstack`: per-proc high water; `OVERFLOW` names
  the corpse via the canary.
- Where did boot go? `bootlog`: `smp+audio-ready` dominates (AP bring-up
  waits); `sched` marks the PIT start.
- Dead graphics program? `gfx frames` before/after + `irqstat` gfx line;
  `wm list` for the window; title-bar X arms `wm_close_request`.

## Image budget (why the ceiling is where it is)

`make check-size` (prerequisite of `kernel.bin`) fails the build when
`_kernel_end > USER_LOAD_BASE` (`0x400000`). That address is pinned by
the Linux-compat hard requirement, not by taste: `load_exec_elf`
(`kernel/loader.c`) maps `ET_EXEC` segments at their linked `p_vaddr`
with `base = 0` and rejects `dst < USER_LOAD_BASE`, and static Linux
binaries link at `0x400000`. Moving the window up would orphan every
`ET_EXEC`; the kernel cannot grow down either (boot structures, page
tables, the `0x10000` user-PT zone). So the ~3 MB `[0x100000,0x400000)`
image span is structural, and the gate forces the conversation at build
time instead of as a black screen in QEMU.

Measured cost of this toolbox (`.o` text deltas vs pre-toolbox):
`shell.o` +~3.4 KB (vmmap/strace-run/gdb/help), `sched.o` +~2.9 KB
(reports + live-regs sample), `syscalls.o` +~1.8 KB (name tables +
atomic trace print), `kernel.o` +~0.4 KB (bootlog), ramdisk +~0.3 KB
(suite markers).
Trimmed back with a data-table resolver (no `case N:` ladder, which also
keeps `check_abi_numbers.py` Rule C quiet), terse formats, and a 12-slot
bootlog. Next levers if the gate bites again: teach `shell_resolve_run`
a MiniFS fallback so bulk (e.g. `minigcc.elf`, 140 KB) can leave the
ramdisk; compress `help` text; split cold reports behind a build flag.
