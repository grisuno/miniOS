# Subsystem: lib

## progs/micropython/variants/minios/lib/__init__.py
- Doc: MiniOS frozen library package.
- Layer: utility
- Language: py

## progs/micropython/variants/minios/lib/hello.py
- Doc: frozen demo: runs at import time as a smoke test.
- Layer: utility
- Language: py
- Depends on: `progs/lua/minios.c`

## progs/micropython/variants/minios/lib/mip.py
- Doc: MiniOS package installer (frozen module).
- Layer: utility
- Language: py
- Symbols:
  - `parse_url` (function, line 49) `def parse_url(url)`
  - `_split_authority_path` (function, line 67) `def _split_authority_path(url, rest, default_port)`
  - `split_url` (function, line 98) `def split_url(url)`
  - `split_https_url` (function, line 106) `def split_https_url(url)`
  - `module_name` (function, line 114) `def module_name(url)`
  - `_is_module_stem` (function, line 136) `def _is_module_stem(stem)`
  - `parse_response` (function, line 150) `def parse_response(data)`
  - `_status_code` (function, line 191) `def _status_code(line)`
  - `absolute_url` (function, line 202) `def absolute_url(base, location)`
  - `http_get` (function, line 222) `def http_get(host, port, path)`
  - `_unlink_quiet` (function, line 268) `def _unlink_quiet(path)`
  - `ensure_dir` (function, line 276) `def ensure_dir(path)`
  - `https_get` (function, line 298) `def https_get(host, port, path)`
  - `install` (function, line 336) `def install(url, dest)`
  - `main` (function, line 394) `def main(argv)`
- Depends on: `progs/lua/minios.c`
- Imported by: `progs/src/test_py.py`
