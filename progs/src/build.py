# build.py -- self-hosted toolchain orchestrator for MiniOS.
#
# Encapsulates the edit -> minigcc -> ld -> run pipeline as a single Python
# program running inside the OS, so development no longer needs a human or an
# external host script. The toolchain objects (minigcc.o, ld.o) are ET_REL
# ring-0 extensions reached through the minios.run() SYS_SPAWN boundary, which
# preserves MicroPython so a single invocation can build every target.
#
# Usage (inside MiniOS):
#   micropython src/build.py            build every target
#   micropython src/build.py fib        build one target
#   micropython src/build.py fib cp     build several targets

import minios

# target name -> (C source, output format). Output lands in bin/<name>.elf.
# Sources are absolute so the build works from any working directory.
TARGETS = {
    'ldhello': ('/src/ldhello.c', 'elf'),
    'fib':     ('/src/fib.c',     'elf'),
    'w1':      ('/src/w1.c',      'elf'),
    'http':    ('/src/http.c',    'elf'),
    'cp':      ('/src/cp.c',      'elf'),
    'freedom': ('/src/freedom.c', 'elf'),
}


def build_one(name, src, kind):
    base = name
    asm = '/asm/' + base + '.s'
    out = '/bin/' + base + '.elf'

    # 1. C -> x86-64 AT&T assembly, capturing stdout to asm/<name>.s.
    rc = minios.run('/objects/minigcc.o', [src], redirect=asm)
    if rc != 0:
        print('build: minigcc failed on %s (exit %d)' % (src, rc))
        return rc

    # 2. Assembly -> ELF.
    rc = minios.run('/objects/ld.o', ['-f', 'elf', '-o', out, asm])
    if rc != 0:
        print('build: ld failed on %s (exit %d)' % (asm, rc))
        return rc

    print('built %s' % out)
    return 0


def main(argv):
    targets = argv[1:] if len(argv) > 1 else sorted(TARGETS)
    failed = 0
    for t in targets:
        if t not in TARGETS:
            print('build: unknown target %s' % t)
            failed = 1
            continue
        name = t
        src, kind = TARGETS[t]
        if build_one(name, src, kind) != 0:
            failed = 1
    if failed:
        print('build: FAILED')
        return 1
    print('build: OK')
    return 0


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
