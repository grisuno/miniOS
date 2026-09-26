# progs/src

*Community 10 | 4 files | cohesion 0.75*

## Definition

This community groups 4 file(s) rooted at `progs/src` with dominant language py (cohesion 0.75). Central symbols: `SYS_FB_INFO`, `SYS_PALETTE`, `SYS_PCSPK_INIT`, `SYS_PCSPK_TONE`, `SYS_PCSPK_VOL`, `SYS_RTC`, `SYS_SPAWN`, `SYS_TIME_MS`. Core file: `progs/src/test.py` (20 symbols). Documented purpose: frozen demo: runs at import time as a smoke test..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/minios.c` | c | utility | 17 | no |
| `progs/micropython/variants/minios/lib/hello.py` | py | utility | 0 | yes |
| `progs/src/shell.py` | py | utility | 3 | yes |
| `progs/src/test.py` | py | testing | 20 | yes |

## Key Symbols

- `msys5` (function, `progs/lua/minios.c:37`) `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` - /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, lo
- `SYS_TIME_MS` (macro, `progs/lua/minios.c:52`) `#define SYS_TIME_MS`
- `SYS_PALETTE` (macro, `progs/lua/minios.c:53`) `#define SYS_PALETTE`
- `SYS_PCSPK_INIT` (macro, `progs/lua/minios.c:54`) `#define SYS_PCSPK_INIT`
- `SYS_PCSPK_TONE` (macro, `progs/lua/minios.c:55`) `#define SYS_PCSPK_TONE`
- `SYS_RTC` (macro, `progs/lua/minios.c:56`) `#define SYS_RTC`
- `SYS_FB_INFO` (macro, `progs/lua/minios.c:57`) `#define SYS_FB_INFO`
- `SYS_PCSPK_VOL` (macro, `progs/lua/minios.c:58`) `#define SYS_PCSPK_VOL`
- `SYS_SPAWN` (macro, `progs/lua/minios.c:59`) `#define SYS_SPAWN`
- `minios_time_ms` (function, `progs/lua/minios.c:62`) `static int minios_time_ms(lua_State *L)` - } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #
- `minios_rtc` (function, `progs/lua/minios.c:68`) `static int minios_rtc(lua_State *L)` - #define SYS_PCSPK_INIT  MINIOS_SYS_PCSPK_INIT #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define
- `minios_fb_info` (function, `progs/lua/minios.c:82`) `static int minios_fb_info(lua_State *L)` - static int minios_rtc(lua_State *L) { int h, m, s; if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) <
- `minios_vol` (function, `progs/lua/minios.c:96`) `static int minios_vol(lua_State *L)` - static int minios_fb_info(lua_State *L) { int w, h, p; if (msys(SYS_FB_INFO, (long)&w, (long)&h, (lo
- `minios_pal` (function, `progs/lua/minios.c:109`) `static int minios_pal(lua_State *L)` - /* ── minios.vol([v]) -> current volume ─────────────────────────────── static int minios_vol(lua_St
- `minios_pcspeaker` (function, `progs/lua/minios.c:119`) `static int minios_pcspeaker(lua_State *L)` - return 1; } /* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── static int minio
- `minios_run` (function, `progs/lua/minios.c:136`) `static int minios_run(lua_State *L)` - ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAW
- `luaopen_minios` (function, `progs/lua/minios.c:192`) `int luaopen_minios(lua_State *L)`
- `run_capture` (function, `progs/src/shell.py:20`) `def run_capture(cmd, args)`
- `expand` (function, `progs/src/shell.py:30`) `def expand(line, env)`
- `main` (function, `progs/src/shell.py:36`) `def main()`
- `check` (function, `progs/src/test.py:15`) `def check(name, cond, detail)`
- `safe_run` (function, `progs/src/test.py:25`) `def safe_run()`
- `test_module_bindings` (function, `progs/src/test.py:38`) `def test_module_bindings()`
- `test_filesystem` (function, `progs/src/test.py:56`) `def test_filesystem()`
- `test_xxhash` (function, `progs/src/test.py:72`) `def test_xxhash()`
- `test_stb` (function, `progs/src/test.py:77`) `def test_stb()`
- `test_dlmalloc` (function, `progs/src/test.py:82`) `def test_dlmalloc()`
- `test_hello` (function, `progs/src/test.py:87`) `def test_hello()`
- `test_ftest` (function, `progs/src/test.py:92`) `def test_ftest()`
- `test_minigcc` (function, `progs/src/test.py:97`) `def test_minigcc()`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 10 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.
- [INFERRED] shares_context community 0 <-> 10 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 10 (progs/src).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `progs/lua/minios.c`)? What purpose do they serve?
- What would break if the most connected file in progs/src changed?
- Should progs/src be split, given cohesion 0.75?

## Sources

- `progs/lua/minios.c`
- `progs/micropython/variants/minios/lib/hello.py`
- `progs/src/shell.py`
- `progs/src/test.py`
