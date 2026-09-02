# test.py -- in-OS test suite for MiniOS, driven by MicroPython.
#
# Tests every available binary sorted by size (smallest first).
# Graphical programs excluded: DOOM, Quake2, Nuklear, Piano, TopoGPT.
#
# Usage (inside MiniOS):
#   micropython src/test.py

import minios

PASS = 0
FAIL = 0


def check(name, cond, detail=''):
    global PASS, FAIL
    if cond:
        PASS += 1
        print('PASS %s' % name)
    else:
        FAIL += 1
        print('FAIL %s%s' % (name, (' ' + detail) if detail else ''))


def safe_run(*a, **kw):
    # SYS_SPAWN of an ET_EXEC child from inside an interpreter is a known
    # pre-existing limitation (the parent-window save cannot fit the heap), so
    # minios.run() raises OSError instead of returning an exit code.  Turn that
    # into a None so a test reports a clean FAIL rather than aborting the suite.
    try:
        return minios.run(*a, **kw)
    except OSError:
        return None


# ── Interpreter module bindings ─────────────────────────────────────

def test_module_bindings():
    check('time_ms is int', isinstance(minios.time_ms(), int))
    try:
        h, m, s = minios.rtc()
        check('rtc plausible', 0 <= h < 24 and 0 <= m < 60 and 0 <= s < 60,
              'h=%d m=%d s=%d' % (h, m, s))
    except OSError:
        check('rtc plausible', False, 'unavailable')
    try:
        w, h, p = minios.fb_info()
        check('fb_info positive', w > 0 and h > 0 and p > 0,
              'w=%d h=%d p=%d' % (w, h, p))
    except OSError:
        check('fb_info positive', False, 'unavailable')
    v = minios.vol()
    check('volume in range', 0 <= v <= 100, 'v=%d' % v)


def test_filesystem():
    path = '/tmp/pytest.txt'
    try:
        with open(path, 'w') as f:
            f.write('hello from test.py\n')
        with open(path) as f:
            data = f.read()
        check('fs write/read', data == 'hello from test.py\n', 'got=%r' % data)
    except OSError as e:
        check('fs write/read', False, str(e))


# ── ET_REL objects (run at ring 0, sorted by size) ─────────────────
# These work from the interpreter because they are ring-0 kernel
# extensions; the SYS_SPAWN parent-window issue does not apply.

def test_xxhash():
    rc = minios.run('/objects/xxhash.o')
    check('xxhash selftest', rc == 0, 'exit=%s' % str(rc))


def test_stb():
    rc = minios.run('/objects/stb.o')
    check('stb selftest', rc == 0, 'exit=%s' % str(rc))


def test_dlmalloc():
    rc = minios.run('/objects/dlmalloc.o')
    check('dlmalloc selftest', rc == 0, 'exit=%s' % str(rc))


def test_hello():
    rc = minios.run('/objects/hello.o', ['arg1', 'arg2'])
    check('hello runs', rc == 42, 'exit=%s' % str(rc))


def test_ftest():
    rc = minios.run('/objects/ftest.o', ['ftest_prog'])
    check('ftest libc surface', rc == 7, 'exit=%s' % str(rc))


def test_minigcc():
    rc = minios.run('/objects/minigcc.o', ['/src/fib.c'], redirect='/asm/_t.s')
    check('minigcc compiles', rc == 0, 'exit=%s' % str(rc))


def test_ld():
    try:
        with open('/asm/_t.s') as f:
            f.read()
    except OSError:
        check('ld links', False, 'no /asm/_t.s')
        return
    rc = minios.run('/objects/ld.o', ['-f', 'elf', '-o', '/bin/_t.elf',
                                     '/asm/_t.s'])
    check('ld links', rc == 0, 'exit=%s' % str(rc))


# test_cvm skipped: requires shell's argv[0] rewrite, not available via minios.run()


# ── Full toolchain roundtrip ────────────────────────────────────────

def test_toolchain_roundtrip():
    rc = minios.run('/objects/minigcc.o', ['/src/fib.c'], redirect='/asm/_t.s')
    if rc != 0:
        check('toolchain roundtrip', False, 'minigcc failed')
        return
    rc = minios.run('/objects/ld.o', ['-f', 'elf', '-o', '/bin/_t.elf',
                                     '/asm/_t.s'])
    if rc != 0:
        check('toolchain roundtrip', False, 'ld failed')
        return
    # ET_EXEC child from interpreter is a known limitation.
    rc = safe_run('/bin/_t.elf')
    check('toolchain roundtrip', rc == 55, 'exit=%s' % str(rc))


def test_spawn_preserves_interpreter():
    before = minios.time_ms()
    rc = minios.run('/objects/minigcc.o', ['/src/ldhello.c'],
                    redirect='/asm/_t2.s')
    after = minios.time_ms()
    check('parent survives child', rc == 0 and after >= before,
          'rc=%s before=%d after=%d' % (str(rc), before, after))


# ── ET_EXEC tools on MiniFS (sorted by size, run via safe_run) ─────
# SYS_SPAWN of an ET_EXEC child from inside an interpreter is a known
# pre-existing limitation.  safe_run() catches OSError so the suite
# reports FAIL and continues instead of aborting.

def test_bin_cp():
    rc = safe_run('/cp', ['/src/hello.c', '/tmp/_cp_test.c'])
    check('cp copies file', rc == 0, 'exit=%s' % str(rc))


def test_bin_lz4():
    src = '/tmp/_lz4_src.txt'
    comp = '/tmp/_lz4_c.bin'
    decomp = '/tmp/_lz4_d.txt'
    payload = 'lz4 test payload ' + 'A' * 200 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('lz4 roundtrip', False, 'write: %s' % e)
        return
    rc = safe_run('/lz4', [src, comp])
    if rc != 0:
        check('lz4 roundtrip', False, 'compress exit=%s' % str(rc))
        return
    rc = safe_run('/unlz4', [comp, decomp])
    if rc != 0:
        check('lz4 roundtrip', False, 'decompress exit=%s' % str(rc))
        return
    try:
        with open(decomp) as f:
            result = f.read()
        check('lz4 roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('lz4 roundtrip', False, 'read: %s' % e)


def test_bin_lzss():
    src = '/tmp/_lzss_src.txt'
    comp = '/tmp/_lzss_c.bin'
    decomp = '/tmp/_lzss_d.txt'
    payload = 'lzss test payload ' + 'B' * 200 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('lzss roundtrip', False, 'write: %s' % e)
        return
    rc = safe_run('/lzss', [src, comp])
    if rc != 0:
        check('lzss roundtrip', False, 'compress exit=%s' % str(rc))
        return
    rc = safe_run('/unlzss', [comp, decomp])
    if rc != 0:
        check('lzss roundtrip', False, 'decompress exit=%s' % str(rc))
        return
    try:
        with open(decomp) as f:
            result = f.read()
        check('lzss roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('lzss roundtrip', False, 'read: %s' % e)


def test_bin_aes():
    src = '/tmp/_aes_src.txt'
    enc = '/tmp/_aes_enc.bin'
    dec = '/tmp/_aes_dec.txt'
    key = '00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff'
    nonce = '000000000000000000000000deadbeef'
    payload = 'aes test payload ' + 'C' * 150 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('aes roundtrip', False, 'write: %s' % e)
        return
    rc = safe_run('/aes', [key, nonce, src, enc])
    if rc != 0:
        check('aes roundtrip', False, 'encrypt exit=%s' % str(rc))
        return
    rc = safe_run('/unaes', [key, nonce, enc, dec])
    if rc != 0:
        check('aes roundtrip', False, 'decrypt exit=%s' % str(rc))
        return
    try:
        with open(dec) as f:
            result = f.read()
        check('aes roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('aes roundtrip', False, 'read: %s' % e)


def test_bin_json():
    path = '/tmp/test.json'
    try:
        with open(path, 'w') as f:
            f.write('{"a":1,"b":[2,3],"c":"hello"}\n')
    except OSError as e:
        check('json validate', False, 'write: %s' % e)
        return
    rc = safe_run('/json', [path], redirect='/tmp/_json_out.txt')
    check('json validate', rc == 0, 'exit=%s' % str(rc))
    rc2 = safe_run('/json', [path, '.a'], redirect='/tmp/_json_q.txt')
    check('json query', rc2 == 0, 'exit=%s' % str(rc2))


def test_bin_freedom():
    rc = safe_run('/freedom', [], redirect='/tmp/_freedom_out.txt')
    # freedom without args prints usage and exits 1
    check('freedom runs', rc == 1, 'exit=%s' % str(rc))


# ── Run all tests (sorted by binary size, smallest first) ───────────

def main():
    print('MiniOS in-OS test suite')

    test_module_bindings()
    test_filesystem()

    # ET_REL objects: smallest to largest
    test_xxhash()         # 2176 bytes
    test_stb()            # 2240 bytes
    test_dlmalloc()       # 3472 bytes
    test_hello()          # 1784 bytes
    test_ftest()          # 2432 bytes
    test_minigcc()        # 145280 bytes
    test_ld()             # 155480 bytes

    # Toolchain roundtrip
    test_toolchain_roundtrip()
    test_spawn_preserves_interpreter()

    # ET_EXEC tools on MiniFS: smallest to largest
    test_bin_cp()         # 4580 bytes
    test_bin_lz4()        # 8676 bytes
    test_bin_lzss()       # 16868 bytes
    test_bin_aes()        # 16868 bytes
    test_bin_json()       # 16868 bytes
    test_bin_freedom()    # 45540 bytes

    print('TOTAL pass=%d fail=%d' % (PASS, FAIL))
    return 1 if FAIL else 0


if __name__ == '__main__':
    import sys
    sys.exit(main())
