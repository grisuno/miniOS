# manifest.py -- frozen modules for the MiniOS MicroPython variant.
# Scripts listed here are compiled to .mpy by mpy-cross and embedded in
# the firmware binary, so they are available as frozen imports without
# touching the filesystem.

freeze('lib')

# asyncio ships as pure Python over the _asyncio C helper (extmod),
# reaching the poll(2) event loop through select.poll and sockets
# (docs/spec/python.md).
include('$(MPY_DIR)/extmod/asyncio/manifest.py')
