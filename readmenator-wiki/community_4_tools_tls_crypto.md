# tools: tls_crypto

*Community 4 | 44 files | cohesion 0.78*

## Definition

This community groups 44 file(s) rooted at `tools` with dominant language py (cohesion 0.78). Central symbols: `AddonError`, `AddonState`, `CHECK`, `Client`, `Config`, `DG_DrawFrame`, `DG_GetKey`, `DG_GetTicksMs`. Core file: `net/tls_crypto.c` (78 symbols). Documented purpose: pure time-conversion helpers shared by the kernel clock.

## Files

### `tools` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/boot_wl.py` | py | utility | 15 | yes |
| `tools/gdb_repro.py` | py | utility | 4 | yes |
| `tools/minios_cli.py` | py | utility | 6 | yes |

### `progs/src` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/lxabi.c` | c | utility | 61 | yes |
| `progs/src/lxsel.c` | c | utility | 11 | yes |

### `headers` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/ktime.h` | h | utility | 3 | yes |
| `headers/tls.h` | h | utility | 73 | yes |

### `mcp` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `mcp/mcp_dbg_driver.py` | py | infrastructure | 6 | yes |
| `mcp/mcp_dogfood.py` | py | utility | 6 | yes |

### `net` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/tls.c` | c | utility | 27 | yes |
| `net/tls_crypto.c` | c | utility | 78 | yes |

### `progs/micropython/variants/minios/lib` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/lib/hello.py` | py | utility | 0 | yes |
| `progs/micropython/variants/minios/lib/mip.py` | py | utility | 15 | yes |

### `progs/tls_u` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_main.c` | c | utility | 5 | yes |
| `progs/tls_u/tls_u_port.c` | c | utility | 15 | yes |

### `.` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tls_test.c` | c | testing | 23 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/time.c` | c | utility | 4 | yes |

### `progs/doomgeneric` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doomgeneric_xlib.c` | c | utility | 9 | no |

### `progs/lua` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/minios.c` | c | utility | 17 | no |

### `tests` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_ktime.c` | c | testing | 2 | yes |

*... and 24 more files in this community.*


## Key Symbols

- `KTIME_H` (macro, `headers/ktime.h:2`) `#define KTIME_H`
- `ktime_us_from_delta` (function, `headers/ktime.h:19`) `static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,`
- `wall_us_from_parts` (function, `headers/ktime.h:30`) `static inline unsigned long wall_us_from_parts(unsigned long base_sec,` - wall_us_from_parts: wall-clock microseconds from an RTC-anchored base. base_sec is the last seen RTC
- `TLS_H` (macro, `headers/tls.h:2`) `#define TLS_H`
- `TLS_CT_CCS` (macro, `headers/tls.h:7`) `#define TLS_CT_CCS`
- `TLS_CT_ALERT` (macro, `headers/tls.h:8`) `#define TLS_CT_ALERT`
- `TLS_CT_HANDSHAKE` (macro, `headers/tls.h:9`) `#define TLS_CT_HANDSHAKE`
- `TLS_CT_APPDATA` (macro, `headers/tls.h:10`) `#define TLS_CT_APPDATA`
- `TLS_REC_HEADER` (macro, `headers/tls.h:11`) `#define TLS_REC_HEADER`
- `TLS_REC_MAX` (macro, `headers/tls.h:12`) `#define TLS_REC_MAX`
- `TLS_MSG_MAX` (macro, `headers/tls.h:13`) `#define TLS_MSG_MAX`
- `TLS_PLAIN_MAX` (macro, `headers/tls.h:14`) `#define TLS_PLAIN_MAX`
- `TLS_VERSION_TLS12` (macro, `headers/tls.h:15`) `#define TLS_VERSION_TLS12`
- `TLS_VERSION_TLS10` (macro, `headers/tls.h:16`) `#define TLS_VERSION_TLS10`
- `TLS_HS_CLIENT_HELLO` (macro, `headers/tls.h:19`) `#define TLS_HS_CLIENT_HELLO`
- `TLS_HS_SERVER_HELLO` (macro, `headers/tls.h:20`) `#define TLS_HS_SERVER_HELLO`
- `TLS_HS_CERTIFICATE` (macro, `headers/tls.h:21`) `#define TLS_HS_CERTIFICATE`
- `TLS_HS_SERVER_KEY_EXCHANGE` (macro, `headers/tls.h:22`) `#define TLS_HS_SERVER_KEY_EXCHANGE`
- `TLS_HS_SERVER_HELLO_DONE` (macro, `headers/tls.h:23`) `#define TLS_HS_SERVER_HELLO_DONE`
- `TLS_HS_CLIENT_KEY_EXCHANGE` (macro, `headers/tls.h:24`) `#define TLS_HS_CLIENT_KEY_EXCHANGE`
- `TLS_HS_FINISHED` (macro, `headers/tls.h:25`) `#define TLS_HS_FINISHED`
- `TLS_CSUITE_ECDHE_RSA_AES128GCM` (macro, `headers/tls.h:28`) `#define TLS_CSUITE_ECDHE_RSA_AES128GCM`
- `TLS_CSUITE_ECDHE_ECDSA_AES128GCM` (macro, `headers/tls.h:29`) `#define TLS_CSUITE_ECDHE_ECDSA_AES128GCM`
- `TLS_SIG_RSA_PKCS1_SHA256` (macro, `headers/tls.h:32`) `#define TLS_SIG_RSA_PKCS1_SHA256`
- `TLS_SIG_ECDSA_P256_SHA256` (macro, `headers/tls.h:33`) `#define TLS_SIG_ECDSA_P256_SHA256`
- `TLS_SIG_ECDSA_P384_SHA384` (macro, `headers/tls.h:34`) `#define TLS_SIG_ECDSA_P384_SHA384`
- `TLS_GROUP_SECP256R1` (macro, `headers/tls.h:37`) `#define TLS_GROUP_SECP256R1`
- `TLS_EXT_SERVER_NAME` (macro, `headers/tls.h:40`) `#define TLS_EXT_SERVER_NAME`
- `TLS_EXT_SUPPORTED_GROUPS` (macro, `headers/tls.h:41`) `#define TLS_EXT_SUPPORTED_GROUPS`
- `TLS_EXT_EC_POINT_FORMATS` (macro, `headers/tls.h:42`) `#define TLS_EXT_EC_POINT_FORMATS`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 55
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.
- [EXTRACTED] depends_on community 4 <-> 1 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports progs/doomgeneric/doomkeys.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `mcp/mcp_dbg_driver.py` via `subprocess` (0 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `mcp/mcp_dogfood.py` via `subprocess` (0 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `mcp/minios_addons.py` via `subprocess` (0 hops)
- [taint high] `mcp/minios_addons.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_mcp.py` -> `mcp/minios_mcp.py` via `subprocess` (0 hops)
- [taint high] `mcp/minios_mcp.py` -> `mcp/minios_addons.py` via `subprocess` (1 hops)
- [taint high] `mcp/minios_mcp.py` -> `kernel/time.c` via `subprocess` (1 hops)
- [taint high] `mcp/minios_mcp.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `tools/boot_wl.py` -> `tools/boot_wl.py` via `subprocess` (0 hops)
- [taint high] `tools/boot_wl.py` -> `kernel/time.c` via `subprocess` (1 hops)

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric_xlib.c`)? What purpose do they serve?
- Is the dangerous import `subprocess` in `mcp/mcp_dbg_driver.py` still required, or can it be isolated?
- What would break if the most connected file in tools: tls_crypto changed?
- Should tools: tls_crypto be split, given cohesion 0.78?

## Sources

- `headers/ktime.h`
- `headers/tls.h`
- `headers/tls_port.h`
- `headers/tls_roots.h`
- `kernel/time.c`
- `mcp/mcp_dbg_driver.py`
- `mcp/mcp_dogfood.py`
- `mcp/minios_addons.py`
- `mcp/minios_mcp.py`
- `net/tls.c`
- `net/tls_crypto.c`
- `net/tls_x509.c`
- `progs/doomgeneric/doomgeneric_xlib.c`
- `progs/lua/minios.c`
- `progs/micropython/variants/minios/lib/hello.py`
- `progs/micropython/variants/minios/lib/mip.py`
- `progs/src/lxabi.c`
- `progs/src/lxsel.c`
- `progs/src/shell.py`
- `progs/src/test.py`
- *... and 24 more*
