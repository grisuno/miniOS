# manifest.py -- frozen modules for the MiniOS MicroPython variant.
# Scripts listed here are compiled to .mpy by mpy-cross and embedded in
# the firmware binary, so they are available as frozen imports without
# touching the filesystem.

freeze('lib')
