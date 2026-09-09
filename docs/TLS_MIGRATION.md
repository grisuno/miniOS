# TLS migration: kernel engine → userspace library

Status: phase 1 landed. The kernel still serves syscalls 201-203 for
`freedom`; `tlsget` proves the same sources run in ring 3.

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
| kernel (default) | `net_send/recv` | `kmalloc` | CMOS RTC | TSC + net counters |
| `TLS_TEST` (host suite) | POSIX test sockets | libc | `time()` | `/dev/urandom` |
| `TLS_RING3` (`tlsget`) | POSIX sockets | libc | `gettimeofday` | `/dev/urandom`, time/pid fallback |

Session slots are indexed by raw OS fd (`TLS_FD_MAX` 160 covers the
MiniOS socket range 100+ and host small fds).

## Phases

- [x] **1. Ring-3 client lands.** `progs/tls_u/tlsget` (static ET_EXEC
  on MiniFS): `tlsget <host> [path] [port]` does TCP + `tls_handshake`
  + HTTP GET over the shared stack. Verified on the host against
  `openssl s_server` (`make tlsget-host`, same sources, same flag).
- [ ] **2. Relink freedom.** `freedom` links the ring-3 objects instead
  of trapping 201-203. No behaviour change; BDD dump scenarios cover it.
- [ ] **3. Kernel engine becomes opt-in legacy.** 201-203 stay behind
  `ENABLE_TLS=1` (already the default-off path via `MINIOS_NO_TLS`
  returning `-ENOSYS`), then are removed with the ABI bump.
- [ ] **4. Delete `net/tls*.c` from the kernel image.** The kernel keeps
  only TCP/UDP/DNS sockets.

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
