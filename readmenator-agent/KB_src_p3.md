# Subsystem: src (page 3 of 3)
Previous: [KB_src_p2.md](KB_src_p2.md)

## progs/src/sign.c
- Doc: in-OS Ed25519 code signer for MiniOS secure boot.
- Layer: utility
- Language: c
- Symbols:
  - `sign_hexval` (function, line 89) `static unsigned int sign_hexval(char c)`
  - `sign_unhex` (function, line 100) `static void sign_unhex(char *out, char *in, int n)`
  - `sign_byte` (function, line 111) `static unsigned int sign_byte(char *p, int i)`
  - `sign_copy` (function, line 119) `static void sign_copy(char *dst, char *src, int n)`
  - `sign_strlen` (function, line 128) `static int sign_strlen(char *s)`
  - `sign_le16` (function, line 136) `static unsigned int sign_le16(char *p, int off)`
  - `sign_le32` (function, line 141) `static unsigned int sign_le32(char *p, int off)`
  - `sign_put32` (function, line 147) `static void sign_put32(char *p, int off, unsigned int v)`
  - `sign_offok` (function, line 180) `static int sign_offok(char *p, int off, int *lo)`
  - `below` (function, line 195) `* every other op below (`|`, `<<`) is low-32 exact. */
static void sign_rotr(unsigned int *lo, un...`
  - `sign_borrow2` (function, line 230) `static unsigned int sign_borrow2(unsigned int x, unsigned int y, unsigned int s)`
  - `sign_add3` (function, line 237) `static unsigned int sign_add3(unsigned int *s, unsigned int a, unsigned int b, unsigned int c)`
  - `sign_be32` (function, line 247) `static unsigned int sign_be32(char *p, int off)`
  - `sign_block` (function, line 253) `static void sign_block(void)`
  - `sign_sha_init` (function, line 387) `static void sign_sha_init(void)`
  - `sign_sha_update` (function, line 410) `static void sign_sha_update(char *data, int len)`
  - `sign_sha_final` (function, line 442) `static void sign_sha_final(char *out)`
  - `sign_feed32` (function, line 490) `static void sign_feed32(unsigned int v)`
  - `sign_key_init` (function, line 500) `static void sign_key_init(void)`
  - `fe_copy` (function, line 549) `static void fe_copy(unsigned int *r, unsigned int *a)`
  - `fe_zero` (function, line 558) `static void fe_zero(unsigned int *r)`
  - `fe_one` (function, line 567) `static void fe_one(unsigned int *r)`
  - `fe_cmov` (function, line 573) `static void fe_cmov(unsigned int *r, unsigned int *b, unsigned int flag)`
  - `fe_ge` (function, line 586) `static unsigned int fe_ge(unsigned int *a, unsigned int *b)`
  - `fe_rawsub` (function, line 601) `static void fe_rawsub(unsigned int *r, unsigned int *a, unsigned int *b)`
  - `fe_add` (function, line 617) `static void fe_add(unsigned int *r, unsigned int *a, unsigned int *b)`
  - `fe_sub` (function, line 636) `static void fe_sub(unsigned int *r, unsigned int *a, unsigned int *b)`
  - `bits` (function, line 672) `* values here always fit 32 bits (limbs below 2^16, carries and
 * products below 2^32), so the s...`
  - `fe_foldadd` (function, line 690) `static void fe_foldadd(unsigned int *row, int at, unsigned int x)`
  - `fe_mul` (function, line 696) `static void fe_mul(unsigned int *r, unsigned int *a, unsigned int *b)`
  - `fe_sq` (function, line 766) `static void fe_sq(unsigned int *r, unsigned int *a)`
  - `fe_inv` (function, line 771) `static void fe_inv(unsigned int *r, unsigned int *a)`
  - `fe_frombytes` (function, line 790) `static void fe_frombytes(unsigned int *r, char *b)`
  - `fe_tobytes` (function, line 800) `static void fe_tobytes(char *b, unsigned int *a)`
  - `fe_curved` (function, line 812) `static void fe_curved(unsigned int *d, unsigned int *d2)`
  - `ge_copy` (function, line 829) `static void ge_copy(unsigned int *r, unsigned int *a)`
  - `fe_off` (function, line 845) `static unsigned int *fe_off(unsigned int *p, int n)`
  - `ge_cmov` (function, line 850) `static void ge_cmov(unsigned int *r, unsigned int *b, unsigned int flag)`
  - `ge_add` (function, line 860) `static void ge_add(unsigned int *r, unsigned int *p, unsigned int *q, unsigned int *d2)`
  - `ge_double` (function, line 892) `static void ge_double(unsigned int *r, unsigned int *p)`
  - `ge_scalarmult` (function, line 926) `static void ge_scalarmult(unsigned int *r, unsigned int *p, char *s, unsigned int *d2)`
  - `sc_mod_l` (function, line 951) `static void sc_mod_l(unsigned int *r, unsigned int *t16)`
  - `sc_mul_add` (function, line 1013) `static void sc_mul_add(unsigned int *r, unsigned int *a, unsigned int *b, unsigned int *c)`
  - `sign_rev32` (function, line 1070) `static void sign_rev32(char *b)`
  - `sign_points_init` (function, line 1081) `static void sign_points_init(void)`
  - `sign_digest` (function, line 1112) `static void sign_digest(char *sig, char *digest)`
  - `sign_read` (function, line 1232) `static char *sign_read(char *name, int *len)`
  - `sign_write` (function, line 1260) `static int sign_write(char *name, char *data, int len)`
  - `sign_note_span` (function, line 1273) `static int sign_note_span(char *img, int off, int len, int *desc)`
  - `sign_digest_of` (function, line 1307) `static int sign_digest_of(char *img, int size, int entry, char *ph, int phnum, char *digest)`
  - `sign_patch_notes` (function, line 1356) `static int sign_patch_notes(char *img, int size, char *ph, int phnum, char *desc)`
  - `sign_append` (function, line 1393) `static int sign_append(char *name, char *img, int size, int shoff, int shnum, int shentsize,
    ...`
  - `sign_file` (function, line 1529) `static int sign_file(char *name)`
  - `sign_selftest` (function, line 1637) `static int sign_selftest(void)`
  - `main` (function, line 1657) `int main(int argc, char **argv)`
  - `printf` (function, line 28) `int printf();`
  - `strcmp` (function, line 29) `int strcmp();`
  - `fopen` (function, line 30) `void *fopen();`
  - `fclose` (function, line 31) `int fclose();`
  - `fread` (function, line 32) `int fread();`
  - `fwrite` (function, line 33) `int fwrite();`
  - `fseek` (function, line 34) `int fseek();`
  - `ftell` (function, line 35) `int ftell();`
  - `malloc` (function, line 36) `void *malloc();`
  - `free` (function, line 37) `void free();`
  - `SIGN_KEY_ID` (macro, line 39) `#define SIGN_KEY_ID`
  - `SIGN_EXIT_FAIL` (macro, line 40) `#define SIGN_EXIT_FAIL`
  - `SIGN_ET_EXEC` (macro, line 42) `#define SIGN_ET_EXEC`
  - `SIGN_ET_DYN` (macro, line 43) `#define SIGN_ET_DYN`
  - `SIGN_EM_X86_64` (macro, line 44) `#define SIGN_EM_X86_64`
  - `SIGN_PT_LOAD` (macro, line 45) `#define SIGN_PT_LOAD`
  - `SIGN_PT_NOTE` (macro, line 46) `#define SIGN_PT_NOTE`
  - `SIGN_SHT_NOTE` (macro, line 47) `#define SIGN_SHT_NOTE`
  - `SIGN_EHDR_SIZE` (macro, line 48) `#define SIGN_EHDR_SIZE`
  - `SIGN_PHDR_SIZE` (macro, line 49) `#define SIGN_PHDR_SIZE`
  - `SIGN_SHDR_SIZE` (macro, line 50) `#define SIGN_SHDR_SIZE`
  - `SIGN_NOTE_HDR` (macro, line 51) `#define SIGN_NOTE_HDR`
  - `SIGN_DESC_BYTES` (macro, line 52) `#define SIGN_DESC_BYTES`
  - `SIGN_SIG_BYTES` (macro, line 53) `#define SIGN_SIG_BYTES`
  - `SIGN_NOTE_TOTAL` (macro, line 54) `#define SIGN_NOTE_TOTAL`
  - `SIGN_NOTE_TYPE` (macro, line 55) `#define SIGN_NOTE_TYPE`
  - `SIGN_MAX_FILE` (macro, line 56) `#define SIGN_MAX_FILE`
  - `SIGN_SEEK_END` (macro, line 57) `#define SIGN_SEEK_END`

## progs/src/spin.c
- Layer: utility
- Language: c
- Symbols:
  - `lx_syscall3` (function, line 11) `static long lx_syscall3(long n, long a1, long a2, long a3)`
  - `lx_strlen` (function, line 20) `static unsigned long lx_strlen(const char *s)`
  - `lx_write` (function, line 26) `static void lx_write(const char *s)`
  - `lx_write_int` (function, line 30) `static void lx_write_int(long v)`
  - `lx_atoi` (function, line 42) `static long lx_atoi(const char *s)`
  - `spin_u32` (function, line 66) `static void spin_u32(unsigned char *d, unsigned long v)`
  - `spin_hdr` (function, line 73) `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,
        unsigned long ...`
  - `spin_box_ok` (function, line 82) `static int spin_box_ok(const char *box)`
  - `spin_hex8` (function, line 95) `static void spin_hex8(unsigned int v, char *dst)`
  - `spin_write_all` (function, line 104) `static long spin_write_all(long fd, const unsigned char *buf, long len)`
  - `spin_emit` (function, line 114) `static int spin_emit(const char *box, unsigned int seq,
        const unsigned char *msg, long mlen)`
  - `spin_raw_file` (function, line 145) `static int spin_raw_file(const char *box)`
  - `spin_pixels` (function, line 169) `static void spin_pixels(long off)`
  - `spin_wl` (function, line 181) `static int spin_wl(const char *box, const char *narg)`
  - `lmain` (function, line 225) `int lmain(long argc, char **argv)`
  - `SPIN_WLW` (macro, line 56) `#define SPIN_WLW`
  - `SPIN_WLH` (macro, line 57) `#define SPIN_WLH`
  - `SPIN_WLA` (macro, line 58) `#define SPIN_WLA`
  - `SPIN_WLB` (macro, line 59) `#define SPIN_WLB`

## progs/src/test.c
- Layer: testing
- Language: c
- Symbols:
  - `add` (function, line 1) `int add(int a, int b)`
  - `main` (function, line 2) `int main(void)`

## progs/src/test.lua
- Layer: testing
- Language: lua
- Symbols:
  - `check` (function, line 12)
  - `write_file` (function, line 22)
  - `read_file` (function, line 30)
  - `test_module_bindings` (function, line 40)
  - `test_filesystem` (function, line 53)
  - `test_xxhash` (function, line 70)
  - `test_stb` (function, line 75)
  - `test_dlmalloc` (function, line 80)
  - `test_hello` (function, line 85)
  - `test_ftest` (function, line 90)
  - `test_minigcc` (function, line 95)
  - `test_ld` (function, line 100)
  - `test_toolchain_roundtrip` (function, line 112)
  - `test_spawn_preserves_interpreter` (function, line 122)
  - `test_bin_cp` (function, line 135)
  - `test_bin_lz4` (function, line 141)
  - `test_bin_lzss` (function, line 158)
  - `test_bin_aes` (function, line 175)
  - `test_bin_json` (function, line 194)
  - `test_bin_freedom` (function, line 205)

## progs/src/test.py
- Doc: in-OS test suite for MiniOS, driven by MicroPython.
- Layer: testing
- Language: py
- Symbols:
  - `check` (function, line 15) `def check(name, cond, detail)`
  - `safe_run` (function, line 25) `def safe_run()`
  - `test_module_bindings` (function, line 38) `def test_module_bindings()`
  - `test_filesystem` (function, line 56) `def test_filesystem()`
  - `test_xxhash` (function, line 72) `def test_xxhash()`
  - `test_stb` (function, line 77) `def test_stb()`
  - `test_dlmalloc` (function, line 82) `def test_dlmalloc()`
  - `test_hello` (function, line 87) `def test_hello()`
  - `test_ftest` (function, line 92) `def test_ftest()`
  - `test_minigcc` (function, line 97) `def test_minigcc()`
  - `test_ld` (function, line 102) `def test_ld()`
  - `test_toolchain_roundtrip` (function, line 119) `def test_toolchain_roundtrip()`
  - `test_spawn_preserves_interpreter` (function, line 134) `def test_spawn_preserves_interpreter()`
  - `test_bin_cp` (function, line 148) `def test_bin_cp()`
  - `test_bin_lz4` (function, line 153) `def test_bin_lz4()`
  - `test_bin_lzss` (function, line 181) `def test_bin_lzss()`
  - `test_bin_aes` (function, line 209) `def test_bin_aes()`
  - `test_bin_json` (function, line 239) `def test_bin_json()`
  - `test_bin_freedom` (function, line 253) `def test_bin_freedom()`
  - `main` (function, line 261) `def main()`
- Depends on: `progs/lua/minios.c`

## progs/src/test_all.sh
- Doc: comprehensive non-interactive test suite for MiniOS.
- Layer: testing
- Language: sh

## progs/src/thdemo.c
- Doc: Producer-consumer over mthreads (roadmap Phase 1, M1).
- Layer: utility
- Language: c
- Symbols:
  - `producer` (function, line 36) `static void *producer(void *p)`
  - `consumer` (function, line 57) `static void *consumer(void *p)`
  - `main` (function, line 82) `int main(void)`
  - `threads` (function, line 3) `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...`
  - `NPROD` (macro, line 21) `#define NPROD`
  - `NCONS` (macro, line 22) `#define NCONS`
  - `PER_PROD` (macro, line 23) `#define PER_PROD`
  - `BUFSZ` (macro, line 24) `#define BUFSZ`
  - `EXPECTED_N` (macro, line 26) `#define EXPECTED_N`
  - `EXPECTED_SUM` (macro, line 27) `#define EXPECTED_SUM`
- Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`

## progs/src/w1.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 3) `int main(void)`
  - `write` (function, line 1) `int write(int fd, char *buf, int n);`

