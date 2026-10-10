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

### IPv6 base, fail-closed (Phase 1: counted drop, no stack yet)
`NET_ETHERTYPE_IPV6` (0x86DD) frames are dropped at the top of
`net_rx_handle_frame` and counted in `net6_rx_dropped` (reported by
`net` status as `v6 <n> dropped`); no IPv6 header is parsed, no reply
is ever emitted. Rationale: QEMU slirp and real LANs deliver
multicast/broadcast v6 (router advertisements, neighbour solicitation)
that the old demux silently ignored inside the IPv4-only fallthrough;
an explicit, counted drop keeps the fail-closed posture visible
instead of silent. Full IPv6 (NDP, SLAAC/DHCPv6, TCP over v6) is
future work and reuses this counter as its RX proof. The shape is
pinned by the `net6-branch-misclassified` mutant (v6 branch folded
into the IPv4 ethertype kills every TCP scenario, so the full suite
is its gate).

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

### Full FreeDom GUI (`freedom-gui`)
`bin/freedom-gui` is the unmodified FreeDom browser (`../FreeDom`, the same
`browser_ui.c`, Cairo painter, HarfBuzz shaper, QuickJS sandbox and tab
pipeline the Linux build runs) linked as one static glibc ELF. FreeDom draws
into a Cairo ARGB32 image surface and talks to the display only through its
windowing seam `gui/platform.h` (FreeDom `spec/platform.md`); MiniOS supplies
that seam, nothing else in FreeDom changes.

- **Build.** FreeDom's own Makefile builds the binary (`make -C $(FREEDOM_DIR)
  BUILD_DIR=progs/freedomui/build ...`), so its object list and per-module
  flags stay the single source of truth. MiniOS overrides only the port
  variables: `PLATFORM_SRCS` (the three files below), `PLATFORM_CFLAGS`,
  `PLATFORM_LIBS` (empty), `PLATFORM_PREREQS` (empty), `MEDIA_OBJ` (empty), the
  library variables pointing at static archives, and `LDHARDEN` for
  `-static -no-pie`. Archives the host lacks (pixman, HarfBuzz, Cairo with
  image/PDF/FreeType/fontconfig only, libcurl over OpenSSL and zlib only) come
  from `tools/build_freedom_deps.sh` (`make freedom-deps`), pinned by version
  and SHA-256 into `progs/freedomui/deps/prefix`. The build is conditional
  (`FREEDOM_GUI_AVAILABLE`: sibling checkout plus the deps prefix) like
  `Q2G_AVAILABLE`.
- **`progs/freedomui/platform_minios.c`** implements `gui/platform.h`:
  - Surface: the NK RGB back-buffer (`MINIOS_NK_RGB_ADDR`, `MINIOS_NK_W` x
    `MINIOS_NK_H`, 3 bytes per pixel). The window paints into a heap ARGB32
    Cairo surface of exactly that size; `pf_window_present` converts it to RGB
    and presents with `GFX_PRESENT(MINIOS_GFX_BUF_NK_RGB)`. A kernel that does
    not report the RGB buffer (`SYS_FB_INFO` fourth word) fails
    `pf_display_open` with `PF_ERR_UNSUPPORTED`; the indexed buffer is never
    written. The first successful present prints `freedom: frame ok (800x360)`
    once, the proof line the BDD scenario pins.
  - Windows: one process owns one NK surface, so the most recently opened
    window is the visible one; closing it hands the surface back to the
    previous window, which receives `configure` plus `ready` and repaints.
    Every window is told `decoration(0)`: the MiniOS window manager draws the
    chrome, so FreeDom never spends rows on a client-side titlebar.
  - Lifecycle: `SYS_VGA_MODE(1)`, then the title (`GFX_SET_TITLE`, at most 31
    bytes), then `SYS_KBD_RAW(1)`; `pf_display_close` restores both.
    Fullscreen and maximize map to `GFX_ZOOM` fullscreen/windowed; minimize,
    interactive move and resize have no ring-3 call (the WM owns the chrome)
    and are ignored; cursor shapes are ignored (the WM draws the pointer).
  - Input: `SYS_KBD` raw PS/2 set 1 bytes go through `ps2_keymap`; `SYS_MOUSE`
    desktop coordinates minus the content origin `GFX_PRESENT` returned give
    surface-local pointer events, buttons bit 0/1/2 map to left/right/middle,
    and the wheel delta maps to `pointer_axis` with the content-down sign.
    PS/2 typematic repeat produces repeated make codes; a make of a key that is
    already held is delivered with `repeat = 1` only while the key handler
    asked for repeat on the press. Alt+F4 fires the window's `close` handler.
  - Wait: `pf_display_wait` polls the caller's descriptors with a zero timeout
    and the keyboard and mouse in `FREEDOM_GUI_TICK_MS` slices, yielding the CPU
    between slices, until input arrives, a descriptor is ready or the timeout
    expires.
  - Clipboard: the kernel clipboard (`CLIP_SET`/`CLIP_GET`), bounded by
    `PF_CLIPBOARD_MAX`.
- **`progs/freedomui/ps2_keymap.c`** is the pure PS/2 set 1 to keysym
  translator (US layout): `E0` extended prefix, Shift/Ctrl/Alt held state,
  Caps Lock and Num Lock toggles (Num Lock starts on), and the text a press
  produces with xkb semantics (Tab `\t`, BackSpace `\b`, Return `\r`, Escape
  `\x1b`, Delete `\x7f`; letters follow Shift XOR Caps Lock). A Ctrl or Alt
  chord produces no text. Keysym values are the X11 values FreeDom's
  `key_event` vocabulary pins; the host suite pins them to
  `xkbcommon-keysyms.h` too.
  - Process: the binary carries the MiniOS process note (minios_abi.h), so
    a foreground `freedom-gui`, a bare name or the dock icon runs it as an
    isolated process the shell waits for. In the pid-0 exec frame `fork`
    is `-ENOSYS`, OpenSSL's providers do not initialize and every fetch
    ended in "Could not start the request (out of resources)".
- **`progs/freedomui/media_unavailable.c`** replaces FreeDom's FFmpeg decoder
  entry points for a build without FFmpeg: `media_decoder_spawn` fails closed
  (`-1`, `ENOSYS`), which `video_play` already reports and unwinds, so no
  decoder process ever starts; a direct `--media-decoder` invocation answers one
  `MD_ERROR` ("media decoding is not available on MiniOS") and exits.
- **MiniFS payload**: the binary, `etc/fonts/fonts.conf` pointing fontconfig
  at `usr/share/fonts`, and the DejaVu Sans / Sans Mono faces.
- Proof: `make test-freedom-gui` (host: `ps2_keymap` vectors, keysym values,
  modifier and lock state, extended keys, text rules), BDD
  `freedom-gui presents the real FreeDom GUI and is killable` (`run
  freedom-gui &` prints `freedom: frame ok (800x360)`, `gfx frames` climbs 0
  to 1, `kill 1` reaps it), and seven mutants in `mutate.sh` (caps xor, chord
  text leak, lost E0 prefix, Num Lock default, short Pause tail, sticky
  modifier, lost frame proof) all killed by the suites. `python3
  tools/test_gui_freedom.py` is the input proof over QMP: a typed key changes
  the URL bar, Ctrl+V pastes the kernel clipboard (`clip abc`) after it and
  Ctrl+C copies the bar back (`clip` prints `xabc`), and a click on the toolbar
  menu button paints the options panel, with the pointer walked to the
  content origin `wm list` reports. Pages render once the tab worker can
  start: that needs the Linux thread, descriptor and sandbox syscalls listed
  in the FreeDom readiness plan (`clone`/`clone3`, `fcntl`, `pipe2`,
  `getdents64`, `prctl` seccomp, `/proc/self/exe`).

### Linux socket ABI (FreeDom readiness, step 6)
The full FreeDom GUI fetches through libcurl over OpenSSL (TLS 1.3, hybrid
post-quantum key exchange, FreeDom `spec/secure_fetch.md`), resolving names
with static glibc's resolver. Both speak the plain Linux socket ABI; MiniOS
answers it on top of the existing TCP stack and a new datagram socket kind.
Pinned by `progs/src/lxnet.c` against the host fixture
`tools/test_net_fixture.py` (UDP and TCP echo on one port, `10.0.2.2` through
slirp): `run bin/lxnet 10.0.2.2 <port>` prints one `lxnet: <check> ok` per
point and `lxnet: all ok`.

- **`socket` (41).** `AF_INET` with `SOCK_STREAM` or `SOCK_DGRAM` (protocol 0,
  `IPPROTO_TCP` or `IPPROTO_UDP`); `SOCK_NONBLOCK` and `SOCK_CLOEXEC` in the
  type are honoured, any other type bit is `-EINVAL`. Every other family
  (`AF_INET6`, `AF_UNIX`, `AF_NETLINK`) is `-EAFNOSUPPORT`, which glibc and
  libcurl treat as "use IPv4".
- **Datagram sockets.** A bounded queue of received datagrams per socket
  (`NET_UDP_QUEUE` entries of at most `NET_UDP_DGRAM_MAX` bytes, oldest kept,
  newest dropped when full, like a full Linux receive buffer); an ephemeral
  local port on first send. `sendto`/`send` (after `connect`) build one UDP
  datagram; `recvfrom`/`recv` return one datagram (truncated to the buffer,
  the rest discarded, like Linux) and the sender's address. `connect` fixes
  the peer and filters what is received. Empty and non-blocking is
  `-EAGAIN`; blocking waits yielding.
- **Stream sockets.** A non-blocking `connect` answers `-EINPROGRESS` and
  completes in the background; `poll` reports `POLLOUT` once established
  (`POLLERR` and `SO_ERROR = ECONNREFUSED` when refused). A blocking connect
  keeps its old behaviour. `recv` on an empty non-blocking stream is
  `-EAGAIN`; `MSG_NOSIGNAL` and `MSG_DONTWAIT` are accepted on send and recv
  (MiniOS delivers no SIGPIPE); any other flag is `-EOPNOTSUPP`.
- **`read`/`write` (0/1) and `readv`/`writev`** on a socket descriptor map to
  recv/send (OpenSSL's socket BIO uses them).
- **`setsockopt` (54) / `getsockopt` (55).** `SO_ERROR` (pending connect
  error, cleared on read), `SO_TYPE`, `SO_KEEPALIVE`, `SO_REUSEADDR`,
  `SO_RCVBUF`, `SO_SNDBUF`, `SO_RCVTIMEO`, `SO_SNDTIMEO`, `SO_LINGER`,
  `TCP_NODELAY`, `TCP_KEEPIDLE`/`TCP_KEEPINTVL`/`TCP_KEEPCNT`, and at
  `IPPROTO_IP` `IP_TOS`, `IP_TTL`, `IP_MTU_DISCOVER` and `IP_RECVERR` (glibc's
  resolver sets `IP_RECVERR` on its UDP socket and abandons the lookup when
  it is refused) are accepted and
  recorded (the stack sends every segment at once, so `TCP_NODELAY` is
  already true); unknown options are `-ENOPROTOOPT`.
- **`getsockname` (51) / `getpeername` (52)** answer the local and peer
  `sockaddr_in`; `getpeername` on an unconnected socket is `-ENOTCONN`.
- **`fcntl` on sockets.** `F_GETFL`/`F_SETFL` read and set `O_NONBLOCK`;
  `F_GETFD`/`F_SETFD` record `FD_CLOEXEC` (`SOCK_CLOEXEC` sets it too).
  Deviation: `execve` does not close marked sockets. The socket tables are
  global, not per process, so a forked child that execs (the FreeDom tab
  worker re-executing `/proc/self/exe`) would otherwise close its parent's
  live connections; the flag is reported faithfully and the descriptor
  stays usable in both.
- **`sendmsg` (46) / `sendmmsg` (307).** The iovecs of each `msghdr` are
  gathered (bounded, every range validated) and sent as one datagram or one
  stream write; `msg_name` addresses a datagram. `sendmmsg` stores each
  message's byte count in `msg_len` and returns the number sent (an error on
  the first message is returned as the error). glibc's resolver sends its
  `A` and `AAAA` queries through `sendmmsg` and treats `ENOSYS` as a failed
  lookup. `recvmsg` and `accept4` stay unimplemented: neither libcurl's
  client path nor the resolver uses them.
- **MiniFS payload.** Committed in `progs/netroot/etc`: `etc/resolv.conf` (`nameserver 10.0.2.3`, the slirp
  resolver), `etc/hosts` (`localhost`), `etc/nsswitch.conf` (`hosts: files
  dns`), and `etc/ssl/certs/ca-certificates.crt`, the Mozilla root store
  pinned by `tools/build_freedom_deps.sh` (libcurl is configured to read
  exactly that path), copied into the freedom-gui `fsroot/etc` at build
  time. `tools/mkfs.minifs.py` merges same-named directories from several
  roots into one (the two `etc` trees become one `/etc`) and rejects any
  other name collision as a build error.
- **Transmit DMA.** The RTL8139 fetches a frame by 32-bit physical address;
  only the identity-mapped heap qualifies (kernel stacks live in `.bss`,
  whose virtual address is not its physical one under KASLR), so every frame
  is copied into a per-slot heap buffer first. Before this, a send from any
  thread but pid 0 stalled and failed (`EAGAIN`), which is how glibc's
  threaded resolver inside libcurl lost every lookup. The receive ring keeps
  the datasheet's 16-byte tail (8K + 16) so the NIC never writes into the
  next heap chunk.
- **`lxnet --dial <host> <port>`** resolves through glibc and dials with
  libcurl's sequence (non-blocking connect, `poll`, `SO_ERROR`).
- **`lxtls <url>`** (built and shipped with freedom-gui) runs the same static
  libcurl, OpenSSL, CA path and resolver on their own and prints libcurl's
  verbose transcript and the exact failure; `lxtls --rand` walks OpenSSL's
  random generator stack. Inside MiniOS, as a job, it completes a TLS 1.3
  handshake with the hybrid post-quantum group `X25519MLKEM768` and an HTTP
  200 from `https://example.com`. In the pid-0 foreground window OpenSSL's
  providers do not initialize (every algorithm fetch fails); probes that
  fetch run as jobs, and `freedom-gui` carries the process note so its
  foreground run is a process (docs/spec/shell-fs.md).
- **Address-space budget.** brk and mmap share about 140 MB of the user
  window (`USER_LOAD_BASE` to `USER_HEAP_CEIL`), with the kernel heap
  identity-mapped right above the window. glibc reserves 64 MB per thread
  malloc arena and sizes thread stacks from `RLIMIT_STACK`, so the kernel
  reports the true 1 MB stack limit and the true CPU count (one arena
  budget per CPU), and the freedom-gui platform layer keeps every thread on
  the main arena (`mallopt(M_ARENA_MAX, 1)` before `main`). Without that the
  browser ran out of address space after its first fetch thread and died on
  a NULL `malloc`.
- **Live proof (needs the host's internet, outside the hermetic BDD):**
  `freedom-gui https://example.com`, in the foreground or as a job,
  resolves through the slirp resolver, negotiates TLS 1.3 and paints the
  page.
