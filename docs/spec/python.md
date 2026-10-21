# Python on MiniOS

The Python story has two runtimes: the frozen MicroPython unix port of
`docs/spec/apps.md` and a full static CPython 3.12 with pip. This document
owns what MiniOS adds around them so Python programs can use the network,
install modules and sleep: the socket ABI surface the port leans on, the
`mip` package installer, the `select(2)`/`pselect6(2)` syscalls behind
`time.sleep`, the Linux calls CPython and pip require, and the staged plan
toward the wider ecosystem.

Hard rule: no address, socket fd encoding or poll bit is invented here.
Sockets ride `docs/spec/network.md`'s Linux socket ABI; poll bits are the
Linux values; `select` maps them through `headers/select_map.h`.

## The Python entry points

Three programs, six names, all of them MiniFS root entries: the shell
resolves a bare name against the MiniFS root before the ramdisk run
directories (`kernel/shell.c:1220`), so the names below work from any cwd.

| Command | What it is | Ships when |
|---------|------------|------------|
| `micropython`, `micropython.elf` | frozen MicroPython 1.28 unix port, static ring-3 ELF | always (`Makefile:1583`) |
| `python3`, `python3.elf` | static CPython 3.12.11, ring-3 ELF | the sibling `../cpython` checkout exists (`Makefile:982`) |
| `pip`, `pip3` | launcher images that `execv` `python3 -m pip` | same (`Makefile:984`) |

The command lines this document's evidence uses:

```
python3 -c "print('cpython-ok', 6 * 7)"
python3 /tmp/hello.py
pip --version
pip3 --version
pip install --no-index --no-deps /usr/local/lib/python3.12/packages/six-1.16.0-py2.py3-none-any.whl
pip uninstall -y six
pip show six
micropython src/test_py.py
micropython -c "import mip; raise SystemExit(mip.main())" install http://10.0.2.2:8899/pkg.py
micropython src/test_py.py wire 10.0.2.2 8899
```

The shell tokenizer knows double quotes and nothing else: no `$@`
expansion, no single quotes, no escapes (`kernel/shell.c:815`). A shell
script therefore cannot forward `pip install x` to the interpreter, which
is why `pip` is a compiled launcher and not a script.

## MicroPython variant deltas (phase 1)

`progs/micropython/variants/minios/mpconfigvariant.{h,mk}` enables, on top
of the previous minimal set (compiler, floats, `os`, `minios` module):

- **`MICROPY_PY_SOCKET`.** `socket` (client and server) over the kernel's
  Linux socket ABI (`net_sys_*`, `docs/spec/network.md`): `socket`,
  `connect`, `bind`, `listen`, `accept`, `send`/`recv`/`sendto`/`recvfrom`,
  `setsockopt`/`getsockopt`. The kernel serves the whole set
  (`kernel/syscalls.c:3395-3409`: socket 41, connect 42, accept 43,
  sendto 44, recvfrom 45, shutdown 48, bind 49, listen 50, setsockopt 54,
  getsockopt 55). `getaddrinfo` goes through static glibc's resolver,
  which reads the shipped `/etc/resolv.conf`, `/etc/hosts` and
  `/etc/nsswitch.conf` (`progs/netroot/etc`, `Makefile:1578`); that is the
  same path `progs/src/lxnet.c` pins. SSL stays off: the port carries no
  TLS engine, so `ssl` is absent and HTTPS is refused by policy (see
  `mip`).
- **`MICROPY_PY_TIME`** with `MICROPY_PY_TIME_INCLUDEFILE
  "ports/unix/modtime.c"`: `time.time`, `time.sleep`, `gmtime`,
  `localtime`, `mktime`. `time.sleep` (fractional seconds) reaches
  `select(2)` through the port's own `mp_time_sleep`
  (`ports/unix/modtime.c:46,100`), which the kernel now answers (below);
  `time.sleep_ms` is a different path and rides `nanosleep` (35) through
  `mp_hal_delay_ms`.
- **`MICROPY_PY_SELECT`** with the unix port's POSIX optimisations
  (`MICROPY_PY_SELECT_POSIX_OPTIMISATIONS`): `select.poll()` is backed by
  `poll(2)` (`extmod/modselect.c:42`), which the kernel already served,
  and `MICROPY_PY_SELECT_SELECT 0` removes `select.select` exactly like
  every other unix variant.
- **`MICROPY_PY_ERRNO`** and **`MICROPY_STREAMS_NON_BLOCK`**: both are
  load-bearing for asyncio (see phase 2 below).
- **`MICROPY_PY_ASYNCIO`** with the asyncio package frozen from
  `$(MPY_DIR)/extmod/asyncio/manifest.py` (phase 2 below).

Threading, FFI, termios, SSL, machine and the websocket module stay
disabled by design; each one returns only with an engine that makes it
true. `MICROPY_PY_BTREE` and the three VFS filesystems are off as well
(`mpconfigvariant.mk:7,15-17`).

The variant must not define `MICROPY_PY_SOCKET` in the header while the
`.mk` sets it to 1: the port Makefile turns the `.mk` value into
`-DMICROPY_PY_SOCKET=1` (`micropython/ports/unix/Makefile:134`) and a
conflicting `#define` in `mpconfigvariant.h` would win with a warning and
turn the module back off.

## `mip` (frozen `lib/mip.py`)

A minimal pip for the frozen port: fetch one module over HTTP or HTTPS
and install it. Frozen with the port (`manifest.py`: `freeze('lib')`), so
it is always importable.

- **Contract.** `mip.install(url[, dest])` fetches
  `http(s)://host[:port]/path.py` and writes `<dest>/<module>.py`
  (default `dest` is `lib`), creating the directory and appending it to
  `sys.path`. Returns the written path. `mip.main()` is the CLI;
  MicroPython puts the code first in `sys.argv` and everything after `-c`
  next (`micropython/ports/unix/main.c:595`), so the shell form is
  `micropython -c "import mip; raise SystemExit(mip.main())" install <url> [dest]`.
  A usage error prints the same sentence and returns 2.
- **HTTPS.** An `https://` URL spawns `bin/tlsget` (the ring-3 TLS stack
  with the pinned roots from `headers/tls_roots.h`) through the `minios`
  module's `SYS_SPAWN` (215) with `-q`, so tlsget's success diagnostic
  stays out of the capture and the file holds exactly the raw HTTP
  response; the capture is `/tmp/mip_tlsget.out`. No kernel TLS number is
  involved: `tlsget` is `tlsget [-q] <host-or-ip> [path] [port]`
  (`progs/tls_u/tls_u_main.c:7,79`). `minios.run` returns the child's
  exit code (`progs/micropython/variants/minios/minios_module.c:142`),
  and a non-zero code fails the install.
- **Fail closed.** The request is `HTTP/1.0` + `Connection: close`;
  chunked responses and a Content-Length that disagrees with the body are
  refused; the response is capped at `MAX_BODY` (256 KiB) plus
  `MAX_HEAD_BYTES` (8 KiB); a socket timeout (10 s) bounds the read. A
  refused scheme, a missing host, a port outside 1..65535, a control
  character in the host or the path, a malformed status line or header,
  a body over the cap, a non-200 answer and a missing `Location` all
  raise instead of installing something.
- **Redirects.** 301/302/303/307/308 up to `MAX_REDIRECTS` (3) across
  http and https, absolute or path-absolute `Location`; a truly relative
  `Location` is refused.
- **Name safety.** The module file name is the URL's last path segment
  (query and fragment dropped) and must match
  `[A-Za-z_][A-Za-z0-9_]*\.py`; any path segment equal to `.` or `..` is
  refused. Subdirectories in the URL path are allowed but flattened: the
  installed name is always bare, so a hostile server cannot write
  outside `dest` (no traversal, no dots, no percent escapes).
- **Atomicity.** Writes go to `<dest>/<module>.py.part` and are renamed
  on success, so a failed fetch never leaves a half module on `sys.path`.
  MiniFS rename replaces a regular-file destination like Linux
  (`fs/minifs.c:1191-1204`), so a reinstall lands on the first rename; the
  drop-and-retry in `mip.install` stays as the belt-and-braces path for a
  filesystem that refuses an existing target.
- **Host behaviour.** On host CPython there is no `minios` module, so the
  https shim raises `OSError("https needs MiniOS (no TLS engine on this
  host)")`; inside the ELF on a host kernel `SYS_SPAWN` is `ENOSYS` and
  the failure names `tlsget`. The host tests cover the http path and both
  refusals.
- **Not** implemented: package metadata, dependency resolution,
  multi-file packages, checksums. Those arrive with the CPython phase.

## asyncio (phase 2)

`MICROPY_PY_ASYNCIO` with the package frozen from
`$(MPY_DIR)/extmod/asyncio/manifest.py` (the pure-Python loop over the
`_asyncio` C helper), on top of `select.poll()` and the socket ABI. Two
variant flags are load-bearing and were the actual blockers:

- `MICROPY_PY_ERRNO`: `asyncio/stream.py` imports `EINPROGRESS` from
  `errno` (`extmod/asyncio/stream.py:100`); without the module every
  `open_connection` dies at import.
- `MICROPY_STREAMS_NON_BLOCK`: makes a non-blocking `EAGAIN` read answer
  `None` (`mp_is_nonblocking_error` in `py/stream.h:141`); without it the
  socket read raises and every async stream dies mid-transfer.

The loop's own delay rides `poll(2)`: `asyncio.sleep_ms` schedules a
deadline in `time.ticks_ms` and the event loop turns the remaining time
into the poll timeout (`extmod/asyncio/core.py:114`).

MiniOS has no loopback route in its net stack, so the hermetic suite
exercises the task scheduler (`asyncio.gather` + `sleep_ms`) and the
live wire proof drives an async HTTP GET against a host fixture:
`micropython src/test_py.py wire 10.0.2.2 8899`. Runs of the same frozen
binary on a host kernel prove the full loopback echo path.

## Kernel: `select(2)` (23) and `pselect6(2)` (270)

Static glibc's `select()` is implemented on top of `pselect6` on Linux
x86-64, so the legacy number 23 is only reached by a program that traps
`SYS_select` directly (`progs/src/lxsel.c` does exactly that); glibc's
`poll()` enters `poll` (7), already served. `time.sleep` is what forces
`pselect6`; the legacy `select` number is the second entry point into the
same body:

- **`select` (23).** Linux `fd_set` (1024 fds, 128 bytes), `timeval`
  timeout; Linux updates the `timeval` with the remaining time, and the
  implementation does too (with a non-zero timeout; a zero timeout polls
  once and leaves the caller's `timeval` alone). That write-back is
  visible only to a raw `SYS_select` caller: glibc copies the timeout
  into a local before entering `pselect6`.
- **`pselect6` (270).** Same sets, `timespec` timeout, not modified. The
  sigmask argument (a6) is accepted and ignored: MiniOS delivers no
  signals to ring-3 handlers, and nothing dereferences it.
- **Semantics.** Only fds below `nfds` are consulted; a bit may appear in
  several sets. Readiness classes follow Linux: read = `POLLIN|POLLERR|
  POLLHUP`, write = `POLLOUT|POLLERR`, except = `POLLPRI`. Negative set
  pointers mean "not interested". A negative `nfds`, a `nfds` above 1024
  or a negative timeout field is `-EINVAL`. Timeouts are converted to the
  poll millisecond budget rounding up (a sub-millisecond sleep still
  waits) and clamped to `SELECT_TIMEOUT_MS_MAX` (24 days, Linux's own
  ceiling class).
- **Mapping.** `headers/select_map.h` holds the pure fd_set/pollfd
  translation (count, build, result) shared by the kernel and the host
  test; the kernel wrapper copies the sets at the syscall boundary, polls
  through `net_sys_poll` with a kmalloc'd array (never stack: 1024
  entries), maps results back and copies out. `select_common` is a
  delegated callee in `tools/check_syscall_sanitize.py`: it sanitizes
  internally, so the `select`/`pselect6` wrappers may hand it raw user
  pointers.

### `newfstatat` `st_mode` offset (found by this work)

MicroPython's filesystem import (`vfs_posix` -> `mp_import_stat`) trusts
`S_ISREG`/`S_ISDIR` from `stat(2)`. `newfstatat` (262) wrote the mode at
the wrong x86-64 offset: `((unsigned int *)st)[5]` is byte 20, inside
`st_nlink`, while Linux puts `st_mode` at byte 24 (`[6]`, the offset
`fstat` already used). Every user `stat` therefore reported
`st_mode = 0`, so `import` of an installed `.py` failed "no module
named" no matter what the file contained. Fixed in all three branches
(MiniFS file, ramdisk file, directory) and pinned by `lxabi`
(`stat-minifs-file-mode`, `stat-ramdisk-file-mode`, `stat-dir-mode`,
`stat-size`) plus the `lxabi-stat-*-offset` mutants.

## CPython 3.12 and pip (phase 3)

The full interpreter runs in ring 3 unmodified: `python3.elf` is a static
x86-64 CPython 3.12.11 built from the sibling `../cpython` checkout with
`--disable-shared --without-ensurepip --disable-test-modules` and
`LDFLAGS="-static -no-pie"` (`Makefile:34-36,986-990`). Every extension
module is linked in: the sibling checkout's `Modules/Setup.local` holds
`*static*` plus the `Setup.stdlib` lines with `*shared*` removed, and
without that `zlib`, `_socket` and the hashlib backends are silently
dropped and C-extension imports fail at runtime.

Layout (all paths are build products, never host paths):

| Guest path | Content | Built by |
|------------|---------|----------|
| `/usr/local/lib/python312.zip` | the pure-Python stdlib, STORED so `zipimport` can read it without a zlib module in the guest; one MiniFS inode instead of ~600 | `tools/mkcpyzip.py` (`Makefile:1011-1013`) |
| `/usr/local/lib/python3.12/site-packages` | pip 24.3.1 unzipped from the pinned wheel, plus the generated `_sysconfigdata_*.py` that `sysconfig` imports | `Makefile:1014-1024` |
| `/usr/local/lib/python3.12/packages/six-1.16.0-py2.py3-none-any.whl` | the install demo wheel, fetched by `make sources` (offline hosts keep it in the tree) | `Makefile:1018-1021` |

`mkcpyzip.py` prunes the trees that need absent pieces (`test`,
`idlelib`, `tkinter`, `turtledemo`, `lib2to3`, `ensurepip`, `venv`) and
every `__pycache__`. The `_sysconfigdata_*.py` file is produced by the
CPython tree's own `pybuilddir.txt`/`sharedmods` step, not by
`make python`; a tree that only built `python` boots but every
`sysconfig` call dies with `ModuleNotFoundError`. `lib-dynload` is
created empty (`Makefile:1010`): with every module static there is
nothing left to load at runtime.

The kernel-side work this phase forced (all pinned by tests):

- **uid/gid family** (`getuid` 102, `getgid` 104, `geteuid` 107, `getegid`
  108): every process is root, like the shell; `-ENOSYS` made glibc answer
  `(uid_t)-1` and broke CPython's startup checks.
- **`getdents64` (217):** `os.listdir`, `os.scandir` and pip's wheel walk.
  The listing handle is `KFILE.is_dir` + `dir_off` + `dir_path`, opened by
  `kfopen_dir`. Its `ref` must start at 1: with 0 the first `kfd_put`
  freed the handle under the iterator and the process hung.
- **`select(23)` / `pselect6(270)`:** see the section above.
- **`rmdir` (84)** and **`unlinkat` (263, `AT_REMOVEDIR` selects `rmdir`):**
  pip's `shutil.rmtree` walks with dir fds and `unlinkat`, never path
  `rmdir`. Missing paths are `ENOENT`, non-directories `ENOTDIR`, non-empty
  directories and the root `ENOTEMPTY`.
- **`chmod` (90), `fchmod` (91), `umask` (95):** MiniFS modes are fixed at
  creation and nothing on the boot image is permission-checked, so the
  kernel validates the target and reports success. Refusing breaks pip's
  console-script installation, which chmods every wrapper to 0755.
- **`*at(2)` dirfd resolution** (`openat` 257, `newfstatat` 262,
  `unlinkat` 263): relative names are joined against the open directory
  fd's `dir_path`; `AT_FDCWD` (-100, normalized through `int`) passes
  through. Before this, CPython's fd-based `shutil.rmtree` resolved the
  child name against the cwd. The joined path lives in kernel memory, so
  the *at handlers call the trusted `do_open_kpath`/`unlink_kpath`/
  `rmdir_kpath` cores: re-running `SANITIZE_STR` on a kernel buffer
  answers `EFAULT`.
- **`rename` replaces a regular-file destination**, like Linux (`fs_rename`
  refuses only directories and ramdisk targets). pip writes
  `RECORD<random>.tmp` and renames it over the wheel's `RECORD`; a
  no-overwrite `rename` fails every install with `EEXIST`.
- **`RAMDISK_FNAME_LEN` 64 -> 96** (`headers/kernel.h`): the 64-byte slot
  failed the first pip import with `ENAMETOOLONG`. The ramdisk format's
  name slot is derived from that define (`tools/mkramdisk.py` parses it),
  so packer and `RDFile` cannot drift; the earlier hardcoded 64 against a
  96-byte kernel slot misaligned every entry and the ABI gate halted with
  `manifest check failed (1)`.
- **MiniFS inode table** 2048 entries (`INODE_TABLE_BLOCKS = 64` in
  `tools/mkfs.minifs.py`): the pip + stdlib tree needs more than the old
  table.

Boot evidence (outside the hermetic suite): `pip --version` and `pip3
--version` answer `pip 24.3.1 from /usr/local/lib/python3.12/site-packages/pip
(python 3.12)`; `pip install --no-index --no-deps
/usr/local/lib/python3.12/packages/six-1.16.0-py2.py3-none-any.whl`
answers `Successfully installed six`, `pip uninstall -y six` answers
`Successfully uninstalled six-1.16.0`, and `pip show six` prints
`Name: six` / `Version: 1.16.0`; `import six` prints `1.16.0`;
`os.listdir('/etc')` matches the host view and fd-based `shutil.rmtree`
removes a nested tree. The one remaining startup warning
(`Could not find platform independent libraries <prefix>`) is cosmetic:
the frozen `getpath.py` looks for the `lib/python3.12/os.py` landmark,
which the zip layout does not have, while `sys.prefix` still resolves to
`/usr/local` and both `purelib` and the zip are found.

### `pip` and `pip3` commands

The shell does not expand `$@`, so a script cannot forward `pip install
x`. `progs/src/pip.c` builds `python3 -m pip <user args>` and `execv`s
`/python3` (a MiniFS root entry, cwd independent); it carries the
`MINIOS_NOTE_PROCESS` note so the shell runs it as a process, since the
pid-0 exec frame cannot `execve`. `bin/pip3` is a copy of the image and
`make` ships both only when the CPython checkout exists. `pip --version`,
`pip3 --version`, `pip install`, `pip uninstall -y` and `pip show` are
driven by the BDD scenario "cpython runs and pip installs a wheel by
command name".

Directory renames are part of this contract: pip's uninstall stashes a
whole `dist-info`/`__pycache__` directory with `os.rename`, so MiniFS
`rename` moves directories (replacing an empty destination directory), and
rejects moving a directory into its own subtree. `unlinkat`'s
`AT_REMOVEDIR` and the fd-based walk cover the rest of `shutil.rmtree`.

## Documented gaps

Named, not hidden:

- **No `epoll`.** `epoll_create1` (291) is not registered, so a library
  that insists on epoll gets `-ENOSYS` and a `UNIMPL SYSCALL` line on the
  console (pip itself survives). The legacy `epoll_create` (213) is
  worse: that number belongs to MiniOS's own `fb_info` syscall, which
  `tools/check_abi_numbers.py` records as a documented deviation.
- **No dynamic extension modules.** The guest has no shared libraries and
  no dynamic loader, so pip can install pure-Python wheels only; a wheel
  carrying a `.so` installs its files but the extension never imports.
- **Path length.** The name slot is `RAMDISK_FNAME_LEN` (96 bytes). A
  user path of 96 bytes or more fails the `SANITIZE_STR` bound with
  `EFAULT`; a shorter path whose resolved form (cwd prefix included) does
  not fit the slot fails with `ENAMETOOLONG` on `rename`/`mkdir`/`rmdir`/
  `unlink` and with `ENOENT` on `open`. The deepest module pip opens
  during an install is 87 bytes
  (`pip/_internal/operations/build/build_tracker.py`), under the slot,
  but the wheel still ships vendored paths of up to 98 bytes
  (`pip/_vendor/urllib3/packages/backports/weakref_finalize.py`) that do
  not fit and would fail if anything imported them.
- **No stored modes.** `chmod`/`fchmod` validate and answer success; the
  mode is not persisted, and `umask` keeps the customary value without
  changing anything on disk.
- **No loopback route.** The net stack has no 127.0.0.1 route, so a
  local server (and any hermetic async wire test) is impossible inside
  the guest.
- **No terminal attributes.** `TCGETS` succeeds with a zeroed block
  (`isatty` is true) but no attribute is stored and no raw mode is
  entered, so the interpreter's interactive editing stays at the kernel's
  line discipline: scripts and `-c` are the usable forms.

## Evidence

- `tests/test_mip.py` (`make test-mip`): pure vectors for URL split,
  module-name validation, response parsing, redirects; then live installs
  through `progs/bin/micropython.elf` against a local `http.server`
  (plain, redirect, reinstall, chunked refusal, host https refusal,
  CLI). 32 tests, all green.
- `tests/test_select_map.c` (`make test-select-map`): fd_set bit ops,
  build/count/result over multi-set vectors, the read/write/except
  classes and the "only requested fds" rule.
- `progs/src/lxsel.c` + the BDD scenario "lxsel probes select(2) and
  pselect6(2)": every kernel vector (nfds bound, negative timeout,
  timeout waiting, select's timeval write-back, pipe read/write
  readiness through both syscall numbers, empty-read timeout, EBADF on
  a bad fd). The `lxsel-*` mutants in `tools/mutate.sh` (nfds check,
  bad-fd detection, result mapping, timeval write-back) all die here.
- `progs/src/lxabi.c` stat-mode, uid/gid, `rmdir` (empty, non-empty,
  emptied, missing), directory `rename` and `getdents64` vectors, with
  the `lxabi-stat-*-offset`, `lxabi-uid-nonzero`,
  `lxabi-rmdir-notempty-lost`, `lxabi-rmdir-emptied-size` and
  `lxabi-getdents-*` mutants.
- `progs/src/test_py.py` inside `sh src/test_all.sh` (112 PASS markers:
  103 from the script, 9 from the in-OS Python suite; the breakdown is
  `docs/spec/testing.md`): socket creation, `select.poll`, `time.sleep`
  wall-clock, `time` epoch, `os.mkdir`/`os.rmdir`, the mip refusal
  vectors, the asyncio scheduler run, plus the CPython and pip import
  markers on every boot suite. Two of the eleven Python checks
  (`py-uid-ok`, `py-listdir-ok`) are gated on `os.getuid`, which the
  guest MicroPython build does not have, so nine of them run.
- `tools/check_abi_numbers.py` (`make lint`): every syscall number this
  document names (23, 35, 41-55, 82, 84, 90, 91, 95, 102, 104, 107, 108,
  217, 257, 262, 263, 270) is resolved against the frozen Linux x86-64
  table by the dispatch site itself, so a renumber cannot drift
  unnoticed.
- Live in-OS proof (outside the hermetic suite, needs the host's
  internet): `mip.install` over https pulled `heapq.py` and
  `functools.py` from micropython-lib (`raw.githubusercontent.com`),
  then imported and used them (`heap-min: 1`, `partial: 42`);
  `micropython src/test_py.py wire 10.0.2.2 8899` completed an async
  HTTP GET through the host fixture.

## Staged path (status)

Done: phase 1 (sockets, `select.poll`/`time.sleep`, `select(2)`/
`pselect6(2)`, https through `bin/tlsget`, the `newfstatat` mode fix,
the `mip` installer), phase 2 (asyncio with `errno` and non-blocking
streams) and phase 3 (static CPython 3.12 with all modules, the stdlib
zip, pip and a working wheel install).

Next candidates, in dependency order:

1. **Loopback TCP.** The net stack has no 127.0.0.1 route, so local
   servers and hermetic async wire tests are impossible; an in-stack
   loopback shortcut would close that gap.
2. **Dynamic extension modules.** pip can install pure-Python wheels
   today; anything with a `.so` needs `dlopen`/`mmap`-exec and a loader
   path contract (MiniOS has no shared libraries).
3. **`epoll` (291).** `ENOSYS` is survivable but libraries that require
   an epoll loop (rather than falling back to poll) cannot run.
4. **REPL quality.** No terminal attributes are stored, so `python3` runs
   scripts and `-c`; interactive editing stays in `vedit`/`edit`.
