# MiniOS Quickstart

Build the image, boot it, write a C program inside the running system,
compile it with the on-board toolchain, run it, then verify your change
with the host test suites. Every command below runs from the repository
root on the host unless marked `miniOS>` (inside the guest).

## 1. Prerequisites

Host tools: `gcc`, binutils (`ld`, `objcopy`, `xxd`), `qemu-system-x86_64`,
`python3`, `git`. No absolute paths are assumed anywhere in the build;
every external checkout location is overridable (see `make sources-status`).

## 2. Fetch the sibling sources

```sh
make sources
```

Clones miniGCC, `ld`, cvm/cvm2, MicroPython, Nuklear and Lua next to the
repo (defaults `../miniGCC`, `../ld`, `../cvm`, `../micropython`,
`../nuklear`, `../lua`). Existing directories are never touched.

## 3. Build the image

```sh
make
```

Zero warnings is required. Produces `os.img` (boot sectors, kernel with
embedded ramdisk, MiniFS partition, swap). Rebuilding after a kernel
change is the same single command.

## 4. Boot it

```sh
make run-headless   # serial console, no GUI window
make run            # with display (TCG by default)
```

Wait for the `miniOS>` prompt. `poweroff` shuts the guest down.

## 5. Your first in-OS program

Type these at the `miniOS>` prompt. The shell resolves bare names by
suffix (`objects/` for `.o`, `bin/` for `.elf` and bare commands,
`cvm/` for `.cvm`), so `run` is optional but explicit here:

```
miniOS> edit src/p.c
edit> a
int main(void) { return 7; }
edit> x
miniOS> run objects/minigcc.o src/p.c > asm/p.s
miniOS> run objects/ld.o -f elf -o bin/p.elf asm/p.s
miniOS> run bin/p.elf
exit code: 7
```

What happened: `edit` wrote `src/p.c` to the ramdisk, miniGCC compiled C
to x86-64 assembly (redirected into `asm/p.s`), `ld` linked an `ET_EXEC`
binary, and `run` executed it as a ring-3 process. For a CVM module
instead: `run objects/ld.o -f cvm -o cvm/p.cvm asm/p.s`, then
`run cvm/p.cvm`.

Interpreters are also on board: bare `micropython` or `lua` start a REPL,
`micropython src/script.py` runs a file.

## 6. Verify your change

```sh
make test-host           # all fast host suites (sync, vma, futex, percpu_rq,
                         # batch, rcu, sanitize, tick, hal)
make test-tick test-hal  # tick listener bus + HAL port mapping only
```

For a live-boot check without hand-rolling QEMU flags:

```sh
tools/boot_run.sh "smp" "sb16" "run cvm/w1.cvm" --timeout 80
```

It boots `os.img`, runs the commands, sends `poweroff`, and returns
nonzero on hang. GUI behaviour (cursor, drag, title buttons) must be
driven with `tools/minios_gui.py`, never headless; see `README.md`
"Testing the VGA desktop".

## 7. Full gate (before a commit)

```sh
make
sh src/test_all.sh
./test_bdd.sh
./tools/test_codecs.sh
./mutate.sh
make test-tls
make test-vma
make test-futex test-percpu-rq test-batch test-rcu
make test-sanitize
make test-tick test-hal
```

## 8. Where to read next

| Document | Purpose |
|----------|---------|
| `docs/cheatsheet.md` | shell, editor, make targets, key bindings, one-line lookups |
| `README.md` | full user and subsystem reference |
| `CLAUDE.md` | engineering contract (specs, invariants, gates) |
| `KNOWLEDGE_BASE.md` | generated architecture reference (all symbols, graphs) |
| `readmenator-agent/INDEX.md` | grep-friendly file-to-purpose map for agents |
| `readmenator-agent/GOTCHAS.md` | what not to change and why |
| `docs/KB_sync.md` | blocking synchronization layer notes |

Regenerate the analysis outputs after structural changes (see the
Project Knowledge Base section at the end of `CLAUDE.md`), then sync
`docs/KNOWLEDGE_BASE.md` from the root copy so both stay identical.
