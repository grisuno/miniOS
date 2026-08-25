# shell.py -- pybash: a Python shell layer on top of MiniOS's C shell.
#
# The C shell is untouched. This is an additional capability layer that gives
# MiniOS pipelines, variables and control flow in Python, so new behaviour no
# longer requires recompiling kernel.c. The core primitive is minios.run(),
# which invokes any ramdisk program through SYS_SPAWN while preserving the
# interpreter, and minios.run(..., redirect=file) to capture a program's
# console output for composition.
#
# Usage (inside MiniOS):
#   micropython src/shell.py

import minios
import os
import sys

TMP = '/tmp/cap.txt'


def run_capture(cmd, args):
    rc = minios.run(cmd, args, redirect=TMP)
    try:
        with open(TMP) as f:
            data = f.read()
    except OSError:
        data = ''
    return rc, data


def expand(line, env):
    for k, v in env.items():
        line = line.replace('$' + k, v)
    return line


def main():
    env = {}
    print('pybash: MiniOS Python shell (variables, capture, run)')
    while True:
        sys.stdout.write('pybash> ')
        sys.stdout.flush()
        line = sys.stdin.readline()
        if not line:
            break
        line = line.rstrip('\r\n').strip()
        if not line:
            continue

        # variable assignment:  name = value
        if line.startswith('set '):
            for k in sorted(env):
                print('%s=%s' % (k, env[k]))
            continue
        if '=' in line and not line.startswith(' '):
            k, v = line.split('=', 1)
            k = k.strip()
            v = expand(v.strip(), env)
            env[k] = v
            print('%s = %s' % (k, v))
            continue

        line = expand(line, env)
        parts = line.split()
        if not parts:
            continue
        cmd = parts[0]
        args = parts[1:]

        if cmd == 'exit':
            break
        elif cmd == 'echo':
            print(' '.join(args))
        elif cmd == 'pwd':
            print(os.getcwd())
        elif cmd == 'capture':
            # capture the output of a program into a variable
            if len(args) < 2:
                print('usage: capture <var> <program> [args...]')
                continue
            var, prog, cargs = args[0], args[1], args[2:]
            rc, data = run_capture(prog, cargs)
            env[var] = data.rstrip('\n')
            print('$%s = <%d bytes, exit %d>' % (var, len(env[var]), rc))
        elif cmd == 'ifok':
            # ifok <program> [args...] then: <command>... -- run a guard
            # program; if it exits 0, run the remainder.
            sep = args.index('then')
            prog = args[:sep]
            rest = args[sep + 1:]
            rc, _ = run_capture(prog[0], prog[1:])
            if rc == 0:
                for sub in rest:
                    print('  running: %s' % sub)
                    subparts = sub.split()
                    if subparts:
                        minios.run(subparts[0], subparts[1:])
        else:
            rc = minios.run(cmd, args)
            if rc < 0:
                print('pybash: not found: %s (exit %d)' % (cmd, rc))

    print('pybash: bye')


if __name__ == '__main__':
    main()
