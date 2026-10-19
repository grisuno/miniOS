# Python on MiniOS

The Python story has one interpreter today: the frozen MicroPython unix
port of `docs/spec/apps.md`. This document owns what MiniOS adds around it
so Python programs can use the network, install modules and sleep: the
socket ABI surface the port leans on, the `mip` package installer, the
`select(2)`/`pselect6(2)` syscalls behind `select.poll()` and
`time.sleep`, and the staged plan toward the wider ecosystem.

Hard rule: no address, socket fd encoding or poll bit is invented here.
Sockets ride `docs/spec/network.md`'s Linux socket ABI; poll bits are the
Linux values; `select` maps them through `headers/select_map.h`.

## MicroPython variant deltas (phase 1)

`progs/micropython/variants/minios/mpconfigvariant.{h,mk}` enables, on top
of the previous minimal set (compiler, floats, `os`, `minios` module):

- **`MICROPY_PY_SOCKET`.** `socket` (client and server) over the kernel's
  Linux socket ABI (`net_sys_*`, `docs/spec/network.md`): `socket`,
  `connect`, `bind`, `listen`, `accept`, `send`/`recv`/`sendto`/`recvfrom`,
  `setsockopt`/`getsockopt`, `getaddrinfo` through static glibc's resolver
  (the same resolver `lxnet` pins). SSL stays off: the port carries no TLS
  engine, so `ssl` is absent and HTTPS is refused by policy (see `mip`).
- **`MICROPY_PY_TIME`** on `ports/unix/modtime.c`: `time.time`,
  `time.sleep`, `gmtime`/`localtime`/`mktime`. `sleep` goes through
  `select(2)`, now answered by the kernel (below).
- **`MICROPY_PY_SELECT`** with the unix port's POSIX optimisations
  (`select.poll()` backing on `poll(2)`, `select.select` disabled exactly
  like every other unix variant).

Threading, FFI, termios, SSL and the websocket module stay disabled by
design; each one returns only with an engine that makes it true.

The variant must not define `MICROPY_PY_SOCKET` in the header while the
`.mk` sets it to 1: the port Makefile passes `-DMICROPY_PY_SOCKET=1` and a
conflicting `#define` in `mpconfigvariant.h` would win with a warning.

## `mip` (frozen `lib/mip.py`)

A minimal pip for the frozen port: fetch one module over HTTP or HTTPS
and install it. Frozen, so it is always importable.

- **Contract.** `mip.install(url[, dest])` fetches
  `http(s)://host[:port]/path.py` and writes `<dest>/<module>.py`
  (default `dest` is `lib`), creating the directory and appending it to
  `sys.path`. Returns the written path. `mip.main()` is the CLI;
  MicroPython puts the code first in `sys.argv` and everything after `-c`
  next, so the shell form is
  `micropython -c "import mip; raise SystemExit(mip.main())" install <url> [dest]`.
- **HTTPS.** An `https://` URL spawns `bin/tlsget` (the ring-3 TLS stack
  with the pinned roots from `headers/tls_roots.h`) through the minios
  module's SYS_SPAWN with `-q` and reads the captured raw HTTP response;
  no kernel TLS number is involved. On host CPython the shim fails
  closed naming tlsget, so host tests cover http and the refusal paths.
- **Fail closed.** Chunked responses and mismatched Content-Length are
  refused; the request is `HTTP/1.0` + `Connection: close`;
  `MAX_BODY` (256 KiB) caps the download; a socket timeout bounds the
  read.
- **Redirects.** 301/302/303/307/308 up to `MAX_REDIRECTS` (3) across
  http and https, absolute or path-absolute `Location`.
- **Name safety.** The module file name is the URL's last path segment
  and must match `[A-Za-z_][A-Za-z0-9_]*\.py`; anything else (traversal,
  subdirectories, dots, percent escapes) is rejected. Writes go to
  `<dest>/<module>.py.part` and are renamed on success. MiniFS rename
  refuses an existing target where Linux overwrites, so a reinstall
  drops the old module and retries once; the `.part` file keeps the
  common path atomic.
- **Not** implemented: package metadata, dependency resolution,
  multi-file packages, checksums. Those arrive with the CPython phase.

## asyncio (phase 2)

`MICROPY_PY_ASYNCIO` with the package frozen from
`$(MPY_DIR)/extmod/asyncio/manifest.py` (the pure-Python loop over the
`_asyncio` C helper), on top of `select.poll()` and the socket ABI. Two
variant flags are load-bearing and were the actual blockers:

- `MICROPY_PY_ERRNO`: `asyncio/stream.py` imports `EINPROGRESS` from
  `errno`; without the module every `open_connection` dies at import.
- `MICROPY_STREAMS_NON_BLOCK`: makes a non-blocking `EAGAIN` read answer
  `None` (`mp_is_nonblocking_error` in `py/stream.h`); without it the
  socket read raises and every async stream dies mid-transfer.

MiniOS has no loopback route in its net stack, so the hermetic suite
exercises the task scheduler (`asyncio.gather` + `sleep_ms`) and the
live wire proof drives an async HTTP GET against a host fixture:
`micropython src/test_py.py wire 10.0.2.2 8899`. Runs of the same frozen
binary on a host kernel prove the full loopback echo path.

## Kernel: `select(2)` (23) and `pselect6(2)` (270)

Static glibc's `select()` enters `pselect6` on x86-64; glibc's `poll()`
enters `poll` (7), already served. `time.sleep` and `select.poll()` are
what force these two new numbers:

- **`select` (23).** Linux `fd_set` (1024 fds, 128 bytes), `timeval`
  timeout; Linux updates the `timeval` with the remaining time, and the
  implementation does too.
- **`pselect6` (270).** Same sets, `timespec` timeout, not modified. The
  sigmask argument (a6) is accepted and ignored: MiniOS delivers no
  signals to ring-3 handlers, and nothing dereferences it.
- **Semantics.** Only fds below `nfds` are consulted; a bit may appear in
  several sets. Readiness classes follow Linux: read = `POLLIN|POLLERR|
  POLLHUP`, write = `POLLOUT|POLLERR`, except = `POLLPRI`. Negative set
  pointers mean "not interested". A negative timeout field or `nfds >
  1024` is `-EINVAL`. Timeouts are converted to the poll millisecond
  budget rounding up (a sub-millisecond sleep still waits) and clamped to
  `SELECT_TIMEOUT_MS_MAX` (24 days, Linux's own ceiling class).
- **Mapping.** `headers/select_map.h` holds the pure fd_set/pollfd
  translation (count, build, result) shared by the kernel and the host
  test; the kernel wrapper copies the sets at the syscall boundary, polls
  through `net_sys_poll` with a kmalloc'd array (never stack: 1024
  entries), maps results back and copies out. `select_common` is the one
  delegated callee that sanitizes internally; it is recorded in
  `tools/check_syscall_sanitize.py`.

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

## Evidence

- `tests/test_mip.py` (`make test-mip`): pure vectors for URL split,
  module-name validation, response parsing, redirects; then live installs
  through `progs/bin/micropython.elf` against a local `http.server`
  (plain, redirect, reinstall, chunked refusal, host https refusal,
  CLI).
- `tests/test_select_map.c` (`make test-select-map`): fd_set bit ops,
  build/count/result over multi-set vectors, the read/write/except
  classes and the "only requested fds" rule.
- `progs/src/lxsel.c` + the BDD scenario "lxsel probes select(2) and
  pselect6(2)": every kernel vector (nfds bound, negative timeout,
  timeout waiting, select's timeval write-back, pipe read/write
  readiness through both syscall numbers, empty-read timeout, EBADF on
  a bad fd). The `lxsel-*` mutants in `tools/mutate.sh` (nfds check,
  bad-fd detection, result mapping, timeval write-back) all die here.
- `progs/src/lxabi.c` stat-mode vectors + the `lxabi-stat-*-offset`
  mutants pin the `newfstatat` fix (docs above).
- `progs/src/test_py.py` inside `sh src/test_all.sh` (now 109 PASS):
  socket creation, `select.poll`, `time.sleep` wall-clock, `time`
  epoch, the mip refusal vectors and the asyncio scheduler run on every
  boot suite.
- Live in-OS proof (outside the hermetic suite, needs the host's
  internet): `mip.install` over https pulled `heapq.py` and
  `functools.py` from micropython-lib (`raw.githubusercontent.com`),
  then imported and used them (`heap-min: 1`, `partial: 42`);
  `micropython src/test_py.py wire 10.0.2.2 8899` completed an async
  HTTP GET through the host fixture.

## Staged path (status)

Done: phase 1 (sockets, `select.poll`/`time.sleep`, `select(2)`/
`pselect6(2)`, https through `bin/tlsget`, the `newfstatat` mode fix,
the `mip` installer) and phase 2 (asyncio with `errno` and non-blocking
streams).

1. **Loopback TCP.** The net stack has no 127.0.0.1 route, so local
   servers and hermetic async wire tests are impossible; an in-stack
   loopback shortcut would close that gap.
2. **More of the library.** `micropython-lib` packages that fit the
   single-file installer, and `ssl`-shaped helpers for packages that
   expect one.
3. **CPython.** A sibling-repo port built exactly like
   MicroPython/DOOM (`-static -no-pie`, ring-3, Linux ABI) as
   `python3.elf` plus pip from `get-pip.py` over the https path.
   Prerequisites this document does not yet satisfy: symlink syscalls
   (CPython and wheels assume them; `readlink` answers `EINVAL` today),
   `dlopen` of C extensions and dynamic linking depth, `termios`/`tty`
   for the REPL, signals beyond group-kill, and a memory budget review
   for the 140 MB user window. Until those land, CPython is a
   documented plan, not a promise.
