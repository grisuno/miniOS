# Subsystem: src (page 3 of 3)
Previous: [KB_src_p2.md](KB_src_p2.md)

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

