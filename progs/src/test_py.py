# test_py.py -- in-OS Python checks for src/test_all.sh (docs/spec/python.md).
#
# Every check prints a PASS: or FAIL: marker the host runner greps. Runs
# from the ramdisk with the frozen mip module and the socket-enabled
# MicroPython build; no network is touched (mip vectors are the offline
# refusals; the live install is tests/test_mip.py on the host).

import sys
import time


def check(name, cond):
    print(('PASS: ' if cond else 'FAIL: ') + name)


try:
    import socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.close()
    check('py-socket-ok', True)
except Exception:
    check('py-socket-ok', False)

import select
p = select.poll()
p.register(0, select.POLLIN)
p.poll(0)
check('py-select-poll-ok', True)

t0 = time.time()
time.sleep(0.03)
check('py-sleep-ok', time.time() - t0 >= 0.02)

epoch = time.gmtime(0)
check('py-time-epoch-ok', epoch[0] == 1970 and epoch[1] == 1 and epoch[2] == 1)

import os
if hasattr(os, 'getuid'):
    check('py-uid-ok', os.getuid() == 0 and os.geteuid() == 0)
    check('py-listdir-ok', 'resolv.conf' in os.listdir('/etc'))
if hasattr(os, 'rmdir'):
    try:
        os.mkdir('/tmp/py_rmdir')
        os.rmdir('/tmp/py_rmdir')
        try:
            os.stat('/tmp/py_rmdir')
            _gone = False
        except OSError:
            _gone = True
        check('py-rmdir-ok', _gone)
    except OSError:
        check('py-rmdir-ok', False)

import mip

try:
    mip.split_url('https://example.com/pkg.py')
    check('py-mip-https-refused-ok', False)
except ValueError:
    check('py-mip-https-refused-ok', True)

try:
    mip.module_name('http://host/../evil.py')
    check('py-mip-traversal-refused-ok', False)
except ValueError:
    check('py-mip-traversal-refused-ok', True)

try:
    check('py-mip-name-ok', mip.module_name('http://host/pkg.py') == 'pkg.py')
except ValueError:
    check('py-mip-name-ok', False)


# asyncio over select.poll() (docs/spec/python.md): two tasks with
# different delays prove the loop schedules and awaits. The loopback TCP
# variant is not in the suite (MiniOS has no loopback route); the `wire`
# mode drives an async HTTP GET against a host fixture instead:
#   micropython src/test_py.py wire 10.0.2.2 8899
async def _asyncio_double(n, ms):
    await asyncio.sleep_ms(ms)
    return n * 2


async def _asyncio_main():
    return await asyncio.gather(_asyncio_double(3, 5), _asyncio_double(4, 15))


def _asyncio_wire_check(host, port):
    async def _one():
        reader, writer = await asyncio.open_connection(host, port)
        writer.write(b'GET /netpkg.py HTTP/1.0\r\nHost: f\r\nConnection: close\r\n\r\n')
        await writer.drain()
        data = await reader.read(16)
        writer.close()
        return data

    try:
        data = asyncio.run(_one())
        check('py-asyncio-wire-ok', data.startswith(b'HTTP/1.'))
    except Exception as exc:
        sys.print_exception(exc)
        check('py-asyncio-wire-ok', False)


try:
    import asyncio
    check('py-asyncio-ok', asyncio.run(_asyncio_main()) == [6, 8])
except Exception as _exc:
    sys.print_exception(_exc)
    check('py-asyncio-ok', False)

_argv = getattr(sys, 'argv', [])
if len(_argv) >= 4 and _argv[1] == 'wire':
    _asyncio_wire_check(_argv[2], int(_argv[3]))
