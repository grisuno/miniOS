# headers

*Community 5 | 9 files | cohesion 0.63*

## Definition

This community groups 9 file(s) rooted at `headers` with dominant language c (cohesion 0.63). Central symbols: `CHECK`, `PORT_IO_DEFINED`, `TLS_ALERT_LEVEL_FATAL`, `TLS_ALERT_LEVEL_WARNING`, `TLS_BN_384_WORDS`, `TLS_BN_4096_WORDS`, `TLS_BN_WORDS`, `TLS_CERT_MAX`. Core file: `net/tls_crypto.c` (78 symbols). Documented purpose: Portability shim between the MiniOS kernel and the host-side test.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/tls.h` | h | utility | 73 | yes |
| `headers/tls_port.h` | h | utility | 49 | yes |
| `headers/tls_roots.h` | h | utility | 0 | yes |
| `headers/tls_test_roots.h` | h | testing | 0 | yes |
| `net/tls.c` | c | utility | 27 | yes |
| `net/tls_crypto.c` | c | utility | 78 | yes |
| `net/tls_x509.c` | c | utility | 23 | yes |
| `progs/tls_u/tls_u_main.c` | c | utility | 5 | yes |
| `tls_test.c` | c | testing | 23 | yes |

## Key Symbols

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
- `TLS_EXT_SIGNATURE_ALGS` (macro, `headers/tls.h:43`) `#define TLS_EXT_SIGNATURE_ALGS`
- `TLS_ALERT_LEVEL_WARNING` (macro, `headers/tls.h:46`) `#define TLS_ALERT_LEVEL_WARNING`
- `TLS_ALERT_LEVEL_FATAL` (macro, `headers/tls.h:47`) `#define TLS_ALERT_LEVEL_FATAL`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 12
- Cross-boundary resolved imports (EXTRACTED): 7

## Connections

- [EXTRACTED] depends_on community 5 <-> 6 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 5 <-> 7 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.

## Risks

- [dataflow UNINIT_USE] `net/tls_crypto.c:1227` `ecdsa_verify` `gen`: `gen` may be read before initialization (declared line 1223).

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `headers/tls.h`
- `headers/tls_port.h`
- `headers/tls_roots.h`
- `headers/tls_test_roots.h`
- `net/tls.c`
- `net/tls_crypto.c`
- `net/tls_x509.c`
- `progs/tls_u/tls_u_main.c`
- `tls_test.c`
