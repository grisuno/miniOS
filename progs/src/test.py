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
    check('minigcc compiles', rc == 0, 'exit=%d' % rc)
    if rc != 0:
        return
    # Link the assembly into an ELF.
    rc = minios.run('/objects/ld.o', ['-f', 'elf', '-o', '/bin/_t.elf',
                                     '/asm/_t.s'])
    check('ld links', rc == 0, 'exit=%d' % rc)
    if rc != 0:
        return
    # Execute the freshly built ELF.  fib.c's main returns fib(10) = 55.
    rc = minios.run('/bin/_t.elf')
    check('built elf runs', rc == 55, 'exit=%d' % rc)


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


def main():
    print('MiniOS in-OS test suite')
    test_module_bindings()
    test_spawn_preserves_interpreter()
    test_toolchain()
    test_filesystem()
    print('TOTAL pass=%d fail=%d' % (PASS, FAIL))
    return 1 if FAIL else 0


if __name__ == '__main__':
    import sys
    sys.exit(main())
