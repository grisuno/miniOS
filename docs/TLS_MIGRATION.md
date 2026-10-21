# TLS migration: kernel engine → userspace library

Status: complete. The kernel no longer ships the TLS engine
(`net/tls*.c` never link into the image; 203 always answers `-ENOSYS`,
201 serves Linux `time(2)` and 202 serves Linux `futex(2)`).
`tlsget`/`freedom` are the supported HTTPS path. There is no legacy
opt-in: a switchable engine preserved a trap (kernel TLS and glibc were
never compatible at 202), not a fallback.

## Why

A full TLS 1.2 + X.509 parser in ring 0 violates least privilege: any
parse bug is kernel execution. Linux/FreeBSD/macOS all keep TLS in
userspace. MiniOS follows, in phases small enough to keep every gate
green.

## How the sources are shared

`net/tls.c`, `net/tls_crypto.c`, `net/tls_x509.c` include only
`tls_port.h` + `tls.h` (both freestanding-clean). The port header
selects the environment:

| build | transport | alloc | time | entropy |
|---|---|---|---|---|
| kernel (port branch only, not built into the image) | `net_send/recv` | `kmalloc` | CMOS RTC | TSC + net counters |
| `TLS_TEST` (host suite) | POSIX test sockets | libc | `time()` | `/dev/urandom` |
| `TLS_RING3` (`tlsget`) | POSIX sockets | libc | `gettimeofday` | `/dev/urandom`, time/pid fallback |

Session slots are indexed by raw OS fd (`TLS_FD_MAX` 160 in the
`TLS_RING3` build, 16 in `TLS_TEST`, `NET_SOCKETS` in the kernel
branch): 160 covers the MiniOS socket range 100+ and host small fds.

## Phases

- [x] **1. Ring-3 client lands.** `progs/bin/tlsget` (from
  `progs/tls_u/tls_u_main.c`, static ET_EXEC on MiniFS): `tlsget
  <host> [path] [port]` does TCP + `tls_handshake` + HTTP GET over the
  shared stack. Verified on the host against `openssl s_server` (`make
  tlsget-host`, same sources, same flag).
- [x] **2. Relink freedom.** `progs/bin/freedom` builds the same
  `progs/src/freedom.c` with host gcc + glibc (`FREEDOM_RING3_LIBC`
  shim: casts miniGCC cannot parse stay behind `#ifdef`) and links the
  shared ring-3 TLS objects, so no handshake byte crosses ring 0.
  Plain-HTTP output is byte-identical to the miniGCC twin in-guest
  (7822 = 7822); a throwaway CA fails closed with the same UX. BDD
  scenarios pin http fetches, the https fail-closed message and the
  `freedom3` byte-copy alias; `bin/freedom-mini` is the miniGCC-to-ld
  twin of the same source (http only), kept as toolchain dogfood and
  pinned by its own BDD fetch scenario.
- [x] **3. Kernel engine removed for good.** There is no opt-in legacy
  build anymore: 203 always answers `-ENOSYS`, 201 serves Linux
  `time(2)` and 202 serves Linux `futex(2)` — kernel TLS and glibc
  ring-3 were never compatible at that number (`__NR_futex` collides
  with TLS_SEND; glibc aborts without a real futex), so keeping a
  switchable engine preserved a trap, not a fallback. `net/tls*.c` never
  link into the image.
- [x] **4. Delete `net/tls*.c` from the kernel image.** Default build
  unlinks `tls.o tls_crypto.o tls_x509.o` (`KERN_TLS_OBJS` empty); the
  kernel keeps only TCP/UDP/DNS sockets. `make test-tls` still compiles
  the same sources on the host, so the crypto stays covered.

## Verification

```bash
make test-tls        # shared sources unchanged: vectors + live handshakes
make tlsget-host     # ring-3 twin binary
# terminal 1: openssl s_server -accept 4433 -cert ... -www
# terminal 2: ./build/tlsget 127.0.0.1 / 4433
```

In-guest: `run tlsget 10.0.2.2 / 4443` against a host server reaches
`chain: verification failed` (throwaway CA, correct reject), and
`run tlsget example.com / 443` works where the guest has a route.

Boyscout find (2026-09): the first guest run timed out because
`net_sys_poll` read `struct pollfd` with big-endian wire readers, so
poll never reported readiness. Fixed in `net/net.c` (host-order
`kmemcpy`), with regression scenario "poll reports a connected socket
readable" (`progs/src/pollready.c`, `run bin/pollready.elf`).

Known failure mode (2026-10 audit, re-verified 2026-10-20, fixed
2026-10-21): `make test-tls` used to fail every positive scenario
(`good-rsa`, `good-ec`, `wild-good`, `chain-good`) with `freedom: tls:
chain: verification failed`, and the fixture server threads logged
`ConnectionResetError` as the client aborted the handshake. The trigger
was deterministic, not a race: the binary embedded the roots of
`headers/tls_test_roots.h` while the servers used the CA under
`build/tls_test_work`, so every chain was rejected when the two
disagreed (a fresh clone, a wiped work dir, or a header older than the
certs). The fix belongs in the build order, never in a looser
assertion: the roots header now lives in the work directory next to the
certificates (`build/tls_test_work/tls_test_roots.h`) and the Makefile
regenerates both together (`tls_test.py --gen-only --regen`), so the
binary and the servers can never disagree.
