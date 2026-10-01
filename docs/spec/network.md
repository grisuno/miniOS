# Network stack, ring-3 TLS, freedom browsers

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### Network (rtl8139 + slirp)
The kernel owns an rtl8139 NIC under QEMU user networking (slirp) with the
standard fixed configuration: address `10.0.2.15`, netmask `255.255.255.0`,
gateway `10.0.2.2` (the host), DNS `10.0.2.3`. Every QEMU launch in the
build, the BDD suite and the MCP attaches `-nic user,model=rtl8139`.

The stack is split into two contracts: the polled NIC driver
(`net/rtl8139.{c,h}`) and the protocol stack (`net/net.c`).  The driver
owns the port I/O, PCI probe, TX descriptors, the receive ring, the NIC
MAC and the PIT-calibrated clock; the stack owns addressing, ARP/IP/
UDP/DNS/ICMP/TCP, the sockets and the demux (`net_rx_handle_frame`) that
the driver reaches through `rtl_poll`.  `rtl8139.h` is the boundary:
`rtl_send`, `rtl_poll`, `rtl_present`, `rtl_get_mac`, `rtl_iobase`,
`rtl_counters`; the shared aggregate RX drop counter (`net_rx_dropped`,
declared in `net.h`) is incremented by both sides (bad frames in the
driver, dropped fragments in the stack).

- The driver polls the NIC (no interrupt controller is configured): TX
  waits for the descriptor owner bit, RX drains the classic ring by
  comparing CAPR against CBR. QEMU forces the legacy receive ring to
  8 KB (it masks the RCR ring-size bits out of writes), so the guest
  ring is 8 KB too; a frame that straddles the ring end is copied
  wrap-aware into a scratch buffer before it reaches the stack. The MAC
  is read from the NIC IDR registers.
- Stack: Ethernet (ARP cache, broadcast requests, replies to our address),
  IPv4 (checksum verified; fragmented datagrams are dropped, fail closed),
  ICMP echo, UDP and a minimal client TCP: SYN/SYN-ACK/ACK handshake,
  stop-and-wait with retransmission timeouts (PIT-calibrated TSC clock),
  FIN teardown, fixed 536-byte MSS and a bounded window. Every accepted
  segment advances the ACK number (a stale ACK stalls real servers that
  wait for acknowledgement before sending more), an out-of-order FIN is
  never reported as EOF before the data before it has arrived, and the
  receive buffer compacts instead of dropping when it is partially
  consumed. A kernel DNS client resolves A records against `10.0.2.3`
  (UDP, retries, bounded timeout).
- Programs reach the stack two ways. ET_REL programs get the libc-style
  symbols `net_open`, `net_connect` (resolves the hostname itself),
  `net_send`, `net_recv` (0 = EOF) and `net_close`. Linux binaries get
  the socket syscalls: `socket`, `connect`, `sendto`, `recvfrom`,
  `shutdown`, `close` and a minimal `poll` (POLLIN when data is ready,
  bounded timeout otherwise) — enough for a static glibc resolver.
- The shell gets `net` (status: MAC, IP, counters) and `net ping <ip>`
  (one ICMP echo, reported as `reply from <ip>` or a timeout diagnostic).
- All constants are named in `net.h` (`NET_*`); none of the fixed
  addresses, ports or timeouts appears as a bare literal.

### virtio-net preference (T4, specified, driver not yet written)
Same shape as the virtio-blk landing: a polled legacy virtio-net driver
(`drivers/virtio_net.c`, QEMU `-device virtio-net-pci`, no MSI-X, no
interrupts, TX/RX queue pair with heap buffers as guest-physical by the
identity-map rule, MAC from the config space) behind the `net.h`
driver boundary (`vnet_send`, `vnet_poll`, `vnet_present`,
`vnet_get_mac` mirroring the `rtl_*` verbs), and `net_init` prefers it
when present (`net: backend=virtio`, else `rtl8139`), with a `vnet`
diagnostic mirroring `vblk` (probe, MAC, queue proof). The preference
is size-gate-free (NICs carry no image identity; presence decides),
and the BDD proves the fast path end to end: virtio NIC attached
beside the stock rtl8139, an HTTP fetch through the preferred device,
plus the backend marker. Pin when implemented: backend marker,
`vnet` queue proof, fetch over virtio, `vnet-*` mutants under
`MATCH="vnet "`.

### TLS client (userspace: tlsget/freedom over net/tls*.c)
TLS 1.2 left ring 0 (`net/tls*.c` never link into the image; 201/203
always answer `-ENOSYS` and 202 serves Linux `futex(2)`). The same sources compile
unchanged with `-DTLS_RING3` into `tlsget`/`freedom`, so `https://`
works without the kernel ever touching key material. The engine spec
below describes the shared sources, not kernel code. The scope
is fixed and fail-closed: no downgrade, no fallback, no session resumption.

- Handshake: `TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256` (0xC02F) and
  `TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256` (0xC02B). ClientHello carries
  SNI (the request host), the secp256r1 (23) group only and both signature
  algorithms; every message feeds the running handshake hash, and the
  server's Finished is verified before the first application byte is
  accepted. Application data is AES-128-GCM, one record = one TLS record,
  GCM tag verified before any plaintext byte is released.
- Crypto (all constant-time where it counts, no table lookups indexed by
  secret bytes): SHA-256/384, HMAC-SHA256, the TLS 1.2 PRF, AES-128-GCM
  with a GHASH that never branches on key bits, P-256 and P-384 field
  arithmetic for ECDSA verify and P-256 ECDHE, and RSA PKCS#1 v1.5 verify
  (SHA-256 and SHA-384) up to 4096-bit moduli for the chain and the
  ServerKeyExchange signature. The Montgomery multiplier's temporaries
  are sized for 128 limbs (4096-bit keys exercise the full width; the
  host suite signs vectors with a 4096-bit key so that path is covered).
  The ECDHE private scalar is rejected unless it is a valid non-zero
  scalar, so invalid-curve attacks have nothing to land on.
- Certificate chain: X.509 DER parsed from the Certificate message (up to
  4 certs, each bounded); the leaf is verified against the presented
  chain down to an embedded root, the leaf public key must match the
  handshake signature, the hostname must match a SAN `dNSName` or the
  subject CN (exact or `*.`-single-label wildcard), and the validity
  window is checked against the CMOS RTC. Any parse error, unknown
  signature algorithm, expired chain, wrong hostname or bad signature
  aborts with `freedom: tls: <stage>: <reason>` and the session is freed.
- Embedded roots (8, DER in `tls_roots_src/`, regenerated into
  `tls_roots.h` by `mkroots.sh`; the build never trusts anything outside
  the table): ISRG Root X1/X2, DigiCert Global Root G2, GlobalSign Root
  CA R3, Google Trust Services Root R1/R4, SSL.com TLS ECC/RSA Root CA
  2022. Real roots are often presented as cross-signed copies (the
  SSL.com 2022 roots are signed by Comodo AAA, ISRG X2 by X1, GTS R1 by
  GlobalSign), so the top cert is anchored by public-key equality with an
  embedded root, or by the root's key verifying the top's signature when
  the server truncates the chain at the leaf. Key equality is safe
  because every link below the top is still signature-verified.
- Session state is heap-allocated per handshake and freed on `close`; a
  socket without TLS costs nothing. Handshake reads are deadline-bounded
  (`net_recv_timeout`), so a silent peer cannot hang the shell forever.
- Client random: the kernel has no CSPRNG; the ClientRandom mixes the TSC,
  accumulated RX bytes/frames and the retransmit counters. Documented,
  not hidden.
- Syscall surface (ld stubs, MiniOS namespace like 200 = dns): 201
  `tls_handshake(fd, host)` on an already connected TCP socket, 202
  `tls_send(fd, buf, len)` (all-or-error, no partial TLS record), 203
  `tls_recv(fd, buf, len)` (decrypted application bytes; 0 = clean EOF:
  close_notify or FIN at a record boundary, truncation is reported; alert
  records are decrypted before their level/description is read, so an
  encrypted close_notify is a clean EOF and never a bogus diagnostic).
  All three validate fd and length and return -1 with a diagnostic on
  misuse. Retired: the engine left ring 0 for good, so 201/203 always
  answer `-ENOSYS` and 202 serves Linux `futex(2)` instead (`__NR_futex`
  collides with the old TLS_SEND number; glibc's NPTL aborts without a
  real futex there). Fossil miniGCC binaries still trap all three and
  fail closed. The supported path is `tlsget`/`freedom`, which link the
  same engine in ring 3 and never trap 201-203. Multi-fetch processes
  must close through `tls_close` (frees the fd-keyed session), never raw
  `close`, or the next fetch reuses the recycled fd onto a live slot.

### Headless browser (`freedom`)
`bin/freedom` is the headless text browser: a curlfree-style engine (the
host `http.c` + `htmlfilter.c` ideas) with a FreeDom-style omnibox. It is
built from `progs/src/freedom.c` with the host toolchain linked against
the shared ring-3 TLS engine (`tlsget`/`freedom3` sources), so `https://`
works with no TLS in the kernel; `bin/freedom-mini` is the miniGCC-to-ld
twin of the same source (http only: miniGCC cannot compile the
struct-heavy TLS engine), kept as toolchain dogfood. Both talk to the
stack through the Linux socket syscalls plus the DNS
syscall; every timeout, retransmission and EOF (0 = FIN) semantics it leans
on is already implemented in the network driver, so the program owns only
HTTP semantics.

- Omnibox (FreeDom): an argument that is not a URL is a DuckDuckGo HTML
  (no-JS) search over https; `javascript:`/`data:` (any non-http scheme) is
  searched, never executed; the User-Agent is a fixed anti-fingerprinting
  identity. Secure by Default: a bare host (no scheme) is fetched as
  `https://`. Explicit `http://` stays http: the host dev loop serves the
  BDD fixtures over plain HTTP, so the upgrade FreeDom applies to
  `http://` input is not applied here (documented deviation).
- Engine (curlfree): a header phase reads the response head into a bounded
  buffer (`FREEDOM_HDR_MAX`, sized for real-world header blocks), then the
  body is read either to `Content-Length` (never waiting for the FIN past
  the announced body) or to EOF, decoding `Transfer-Encoding: chunked`
  in place. Header names match case-insensitively. On `https://` the same
  dialogue runs over the ring-3 TLS engine after `tls_handshake`; a failed
  handshake fails closed with
  `freedom: https handshake with <host> failed` (BDD-pinned against a
  plain-HTTP port), with no key material crossing ring 0.
- Redirects (curlfree + FreeDom policy): a 3xx with a `Location` is chased
  up to `FREEDOM_HOPS_MAX` hops. Absolute `http://` and `https://` targets
  are followed (https through the ring-3 TLS engine); relative targets resolve
  against the current path; any other explicit scheme in a `Location` is
  refused, fail closed.
- HTML filter (htmlfilter.c): comments are skipped, `script`/`style`
  contents are suppressed, block tags (`p`, `div`, `h1`-`h6`, `li`, `tr`)
  and `br` become newlines, entities (named and numeric, decimal and hex)
  are decoded, whitespace collapses. Filter state carries across network
  chunk boundaries, so a tag or entity split between two segments is still
  decoded.
- Remote pages are hostile data (FreeDom): every byte printed to the
  console passes a UTF-8 gate that replaces bytes outside a valid sequence
  (overlong, surrogate, out of range) with `?`.
- Headless dumps (the FreeDom agent surface MiniOS can carry, no JS):
  `freedom --dump-css <url>` prints `=== freedom css ===` then every
  stylesheet the page carries — `<style>` blocks captured in document
  order, inline `style="..."` attributes as `tag#id.class { ... }` lines
  (the declaration is normalized with a trailing `;`), and
  `<link rel=stylesheet>` targets fetched (bounded count
  `FREEDOM_CSS_MAX`, each bounded bytes) and printed with their source.
  `freedom --dump-dom <url>` prints `=== freedom dom ===` then the
  element outline: one depth-indented `tag#id.class` line per element in
  document order (bounded buffer `FREEDOM_DOM_MAX`). Dump modes suppress
  the normal filtered text. Both flags validate argv and refuse unknown
  flags with a usage diagnostic.
- Diagnostics are `freedom: ...` lines; the fetch ends with
  `freedom: <host> (<n> bytes)`.
- Build: the ld stubs grew `tls_handshake`/`tls_send`/`tls_recv` (MiniOS
  syscalls 201-203, now `-ENOSYS` on a default kernel), so the toolchain
  in `ld/ld.c` and the ramdisk binary must be rebuilt together; the
  Makefile derives `bin/freedom` (host gcc + ring-3 TLS) and
  `bin/freedom-mini` (miniGCC-to-ld, http only) from `progs/src/freedom.c`.
  Two toolchain fixes this program leans on,
  both in the sibling checkouts: ld's `strip_comment` must ignore `#`
  inside string literals (`.asciz "#"` is the id/class separator in the
  dumps), and miniGCC must index a chained subscript on a pointer array
  (`argv[1][0]`, the flag check) with a byte load after the pointer
  element was loaded.

### FreeDom Wayland layer (`freedom_wl`)
`bin/freedom_wl` is the Wayland-to-MiniOS intermediate layer for FreeDom,
the same role `doomgeneric_minios.c` plays for DOOM, and a complete
graphical browser in one file (`progs/src/freedom_wl.c`): the FreeDom
omnibox policy, HTTP/1.0 fetch over the socket syscalls with DNS from
syscall 200 and https through the shared ring-3 TLS engine (no key
material crosses ring 0, exactly like `bin/freedom`), redirect chasing,
chunked decoding, an HTML-to-text filter over a 100x45 layout on the
shared 8x8 font (`progs/nuklear/font8x8.c`, one copy linked by every
NK-window program through `NUKLEAR_PLATFORM`), and an input loop with
keyboard and wheel scroll. A Wayland surface becomes the Nuklear
back-buffer window (`MINIOS_NK_W`x`MINIOS_NK_H`), present routes through
`GFX_PRESENT` with `BUF_NK`, title through `GFX_SET_TITLE`, pointer through
`SYS_MOUSE`, keyboard through `SYS_KBD`. Keysyms translate from PS/2 Set 1,
dirty rects clamp to the surface, UTF-8 sanitizes fail-closed. The browser
uploads its 768-byte graphics palette through `SYS_PALETTE` before every
present (indices 0-14 match the desktop palette, the rest mirror the Nuklear
hybrid ramp), so the terminal-style page stays visible on true-color VBE modes
instead of rendering black on black through the kernel gray-ramp default.
Every tunable
lives in `FreedomWlConfig`, every address comes from `minios_abi.h`, no
absolute paths. `FREEDOM_DIR` (`../FreeDom`, fifth sibling repo) is cloned by
`make sources` and never touched when present. MiniFS grows to 768 MB
(`MINIFS_BLOCKS` 196608) for browser assets and fonts; the growth is
disk-only and moves no memory address. Proof: `make test-freedom-wl` (host),
`freedom_wl --selftest` prints `freedom_wl: frame ok (800x360)` (BDD),
`freedom_wl --once <url>` fetches and presents with `freedom_wl: <host>
(<n> bytes)` (live boot: README is 3193 bytes and `gfx frames` climbs 0 to
1; `google.com` chases to `www.google.com` over real TLS and renders whole
at 83 KB against the 256 KB body cap), five mutants (clip, https port,
title, keysym, uname) die in `mutate.sh`, plus the palette-bg mutant dies
in the host suite (`palette bg terminal`).
See ADR-0019.

### Real FreeDom browser (`freedomui`)
`bin/freedomui` is the real FreeDom engine on MiniOS, built exactly like
DOOM and Quake 2: host gcc `-static -no-pie` links the engine core
(`url`, `link_nav`, `html_parse` over Lexbor, `ui_layout`) from the
sibling `../FreeDom` checkout with the platform layer
`progs/freedomui/freedomui_minios.c`, and the ELF ships on MiniFS. Every
Wayland and Cairo call is replaced in that one file: the NK back-buffer
window is the surface, `GFX_PRESENT` with `BUF_NK` presents, `GFX_SET_TITLE`
titles, `SYS_MOUSE`/`SYS_KBD` feed input, `SYS_PALETTE` uploads the hybrid
palette before every present (same table as Nuklear, so no black window on
true-color VBE), `SYS_TIME` paces, `VGA_MODE` claims the display, and fetch
runs over the socket syscalls with DNS plus the ring-3 TLS engine. Parsing
goes through `hp_parse` with secure defaults and layout through
`ui_wrap_text`, so what renders is engine output, not a rewritten filter.
Out of scope for v1: JS, images, video, sandbox confinement, persistence.
Build is conditional (`FREEDOMUI_AVAILABLE`, sibling plus static Lexbor)
like `Q2G_AVAILABLE`. Proof: `make test-freedomui` (host, omnibox plus
Lexbor parse plus wrap), `freedomui --selftest` prints
`freedomui: frame ok (800x360)` (BDD), `freedomui --once <url>` fetches and
presents with `freedomui: <host> (<n> bytes, <m> elems)` (live boot proves
`gfx frames` climbs 0 to 1), two mutants (palette-bg, omnibox-kind) die in
`mutate.sh`.
See ADR-0021.
