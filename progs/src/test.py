# test.py -- in-OS test suite for MiniOS, driven by MicroPython.
#
# Runs inside the machine and verifies the kernel (minios module bindings) and
# the self-hosted toolchain (minigcc -> ld -> execute) from within, through the
# minios.run() SYS_SPAWN boundary. Complements the host-side test_bdd.sh: it
# inspects kernel state the host cannot see and needs no QEMU/serial timing.
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


def test_toolchain():
    # Compile a known source to assembly (captured to a temp file).
    rc = minios.run('/objects/minigcc.o', ['/src/fib.c'], redirect='/asm/_t.s')
    check('minigcc compiles', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    # Link the assembly into an ELF.
    rc = minios.run('/objects/ld.o', ['-f', 'elf', '-o', '/bin/_t.elf',
                                     '/asm/_t.s'])
    check('ld links', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    # Execute the freshly built ELF.  fib.c's main returns fib(10) = 55.
    # SYS_SPAWN of an ET_EXEC child from inside an interpreter is a known
    # pre-existing limitation (the parent-window save cannot fit the heap), so
    # run() returns None: report it as a FAIL but do NOT abort the suite, or
    # the lzss/lz4/aes tests below would never run.
    rc = safe_run('/bin/_t.elf')
    check('built elf runs', rc == 55, 'exit=%s' % str(rc))


def test_spawn_preserves_interpreter():
    # The parent MicroPython must survive a ring-0 child run.
    before = minios.time_ms()
    rc = minios.run('/objects/minigcc.o', ['/src/ldhello.c'], redirect='/asm/_t2.s')
    after = minios.time_ms()
    check('parent survives child', rc == 0 and after >= before,
          'rc=%d before=%d after=%d' % (rc, before, after))


def test_filesystem():
    # Unified fs: write then read back through Python's open().
    path = '/tmp/pytest.txt'
    try:
        with open(path, 'w') as f:
            f.write('hello from test.py\n')
        with open(path) as f:
            data = f.read()
        check('fs write/read', data == 'hello from test.py\n', 'got=%r' % data)
    except OSError as e:
        check('fs write/read', False, str(e))


def test_json():
    # Write a test JSON file, run json to validate and pretty-print.
    path = '/tmp/test.json'
    try:
        with open(path, 'w') as f:
            f.write('{"a":1,"b":[2,3],"c":"hello"}\n')
    except OSError as e:
        check('json validate', False, 'write: %s' % e)
        return
    rc = safe_run('/json', [path], redirect='/tmp/_json_out.txt')
    check('json validate', rc == 0, 'exit=%s' % str(rc))
    # Query a dotted path.
    rc2 = safe_run('/json', [path, '.a'], redirect='/tmp/_json_q.txt')
    check('json query', rc2 == 0, 'exit=%s' % str(rc2))


def test_lzss_roundtrip():
    # Compress then decompress, verify roundtrip.
    src = '/tmp/_lzss_src.txt'
    comp = '/tmp/_lzss_c.bin'
    decomp = '/tmp/_lzss_d.txt'
    payload = 'lzss roundtrip test data ' + 'x' * 200 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('lzss compress', False, 'write: %s' % e)
        return
    rc = safe_run('/lzss', [src, comp])
    check('lzss compress', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    rc = safe_run('/unlzss', [comp, decomp])
    check('lzss decompress', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    try:
        with open(decomp) as f:
            result = f.read()
        check('lzss roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('lzss roundtrip', False, 'read: %s' % e)


def test_lz4_roundtrip():
    src = '/tmp/_lz4_src.txt'
    comp = '/tmp/_lz4_c.bin'
    decomp = '/tmp/_lz4_d.txt'
    payload = 'lz4 roundtrip test data ' + 'y' * 300 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('lz4 compress', False, 'write: %s' % e)
        return
    rc = safe_run('/lz4', [src, comp])
    check('lz4 compress', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    rc = safe_run('/unlz4', [comp, decomp])
    check('lz4 decompress', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    try:
        with open(decomp) as f:
            result = f.read()
        check('lz4 roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('lz4 roundtrip', False, 'read: %s' % e)


def test_aes_roundtrip():
    src = '/tmp/_aes_src.txt'
    enc = '/tmp/_aes_enc.bin'
    dec = '/tmp/_aes_dec.txt'
    key = '00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff'
    nonce = '000000000000000000000000deadbeef'
    payload = 'aes roundtrip test data ' + 'z' * 150 + '\n'
    try:
        with open(src, 'w') as f:
            f.write(payload)
    except OSError as e:
        check('aes encrypt', False, 'write: %s' % e)
        return
    rc = safe_run('/aes', [key, nonce, src, enc])
    check('aes encrypt', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    rc = safe_run('/unaes', [key, nonce, enc, dec])
    check('aes decrypt', rc == 0, 'exit=%s' % str(rc))
    if rc != 0:
        return
    try:
        with open(dec) as f:
            result = f.read()
        check('aes roundtrip', result == payload,
              'len=%d expected=%d' % (len(result), len(payload)))
    except OSError as e:
        check('aes roundtrip', False, 'read: %s' % e)


def test_freedom():
    # Run freedom without arguments — should print usage and exit 1.
    rc = safe_run('/freedom', [], redirect='/tmp/_freedom_out.txt')
    check('freedom runs', rc == 1, 'exit=%s' % str(rc))


def main():
    print('MiniOS in-OS test suite')
    test_module_bindings()
    test_spawn_preserves_interpreter()
    test_toolchain()
    test_filesystem()
    test_json()
    test_lzss_roundtrip()
    test_lz4_roundtrip()
    test_aes_roundtrip()
    test_freedom()
    print('TOTAL pass=%d fail=%d' % (PASS, FAIL))
    return 1 if FAIL else 0


if __name__ == '__main__':
    import sys
    sys.exit(main())
