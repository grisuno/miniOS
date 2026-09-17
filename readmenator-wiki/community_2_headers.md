# headers

*Community 2 | 3 files | cohesion 0.40*

## Definition

This community groups 3 file(s) rooted at `headers` with dominant language c (cohesion 0.40). Central symbols: `ABI_BAD_FORMAT`, `ABI_CHECKSUM_MISMATCH`, `ABI_H`, `ABI_MANIFEST_MAX`, `ABI_MANIFEST_NAME`, `ABI_NO_MANIFEST`, `ABI_OK`, `ABI_VERSION_MISMATCH`. Core file: `headers/abi.h` (10 symbols). Documented purpose: Docstring: abi.h -- Boot-time ABI manifest gate contract..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/abi.h` | h | utility | 10 | yes |
| `kernel/abi.c` | c | utility | 3 | yes |
| `tests/test_abi.c` | c | testing | 2 | yes |

## Key Symbols

- `ABI_H` (macro, `headers/abi.h:14`) `#define ABI_H`
- `ABI_OK` (macro, `headers/abi.h:16`) `#define ABI_OK`
- `ABI_NO_MANIFEST` (macro, `headers/abi.h:17`) `#define ABI_NO_MANIFEST`
- `ABI_BAD_FORMAT` (macro, `headers/abi.h:18`) `#define ABI_BAD_FORMAT`
- `ABI_VERSION_MISMATCH` (macro, `headers/abi.h:19`) `#define ABI_VERSION_MISMATCH`
- `ABI_CHECKSUM_MISMATCH` (macro, `headers/abi.h:20`) `#define ABI_CHECKSUM_MISMATCH`
- `ABI_MANIFEST_NAME` (macro, `headers/abi.h:22`) `#define ABI_MANIFEST_NAME`
- `ABI_MANIFEST_MAX` (macro, `headers/abi.h:23`) `#define ABI_MANIFEST_MAX`
- `abi_verify` (function, `headers/abi.h:25`) `int abi_verify(const char *text, long version, unsigned long checksum);`
- `abi_check_manifest` (function, `headers/abi.h:28`) `int abi_check_manifest(void);` - ifndef ABI_HOST_TEST
- `abi_parse_num` (function, `kernel/abi.c:20`) `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)` - order, junk, overflow, missing newline) fails closed as BAD_FORMAT. Number parsing carries its own o
- `abi_verify` (function, `kernel/abi.c:38`) `int abi_verify(const char *text, long version, unsigned long checksum)` - return 0; while (p < end && *p >= '0' && *p <= '9') { unsigned digit = (unsigned)(*p - '0'); if (v >
- `abi_check_manifest` (function, `kernel/abi.c:74`) `int abi_check_manifest(void)` - p += 2; if (!abi_parse_num(&p, end, &c)) return ABI_BAD_FORMAT; if (p + 1 != end \|\| *p != '\n') retu
- `expect` (function, `tests/test_abi.c:16`) `static void expect(const char *name, const char *manifest, int want)`
- `main` (function, `tests/test_abi.c:25`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/abi.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: tests/test_abi.c imports progs/minios_abi.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 2 (headers).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.40?

## Sources

- `headers/abi.h`
- `kernel/abi.c`
- `tests/test_abi.c`
