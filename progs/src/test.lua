-- test.lua -- in-OS test suite for MiniOS, driven by Lua.
--
-- Tests every available binary sorted by size (smallest first).
-- Graphical programs excluded: DOOM, Quake2, Nuklear, Piano, TopoGPT.
--
-- Usage (inside MiniOS):
--   lua src/test.lua

local PASS = 0
local FAIL = 0

local function check(name, cond, detail)
  if cond then
    PASS = PASS + 1
    print('PASS ' .. name)
  else
    FAIL = FAIL + 1
    print('FAIL ' .. name .. (detail and (' ' .. detail) or ''))
  end
end

local function write_file(path, contents)
  local f = io.open(path, 'w')
  if not f then return false end
  f:write(contents)
  f:close()
  return true
end

local function read_file(path)
  local f = io.open(path, 'r')
  if not f then return nil end
  local d = f:read('*a')
  f:close()
  return d
end

-- ── Interpreter module bindings ────────────────────────────────────

local function test_module_bindings()
  check('time_ms is int', type(minios.time_ms()) == 'number')
  local h, m, s = minios.rtc()
  check('rtc plausible', h ~= nil and h >= 0 and h < 24 and m >= 0 and m < 60
                          and s >= 0 and s < 60,
        string.format('h=%d m=%d s=%d', h, m, s))
  local w, hh, p = minios.fb_info()
  check('fb_info positive', w ~= nil and w > 0 and hh > 0 and p > 0,
        string.format('w=%d h=%d p=%d', w, hh, p))
  local v = minios.vol()
  check('volume in range', v >= 0 and v <= 100, string.format('v=%d', v))
end

local function test_filesystem()
  local f = io.open('/tmp/luatest.txt', 'w')
  if not f then check('fs write/read', false, 'open-write failed'); return end
  f:write('hello from test.lua\n')
  f:close()
  local f2 = io.open('/tmp/luatest.txt', 'r')
  if not f2 then check('fs write/read', false, 'open-read failed'); return end
  local data = f2:read('*a')
  f2:close()
  check('fs write/read', data == 'hello from test.lua\n',
        string.format('got=%q', data or ''))
end

-- ── ET_REL objects (run at ring 0, sorted by size) ────────────────
-- These work from the interpreter because they are ring-0 kernel
-- extensions; the SYS_SPAWN parent-window issue does not apply.

local function test_xxhash()
  local rc = minios.run('/objects/xxhash.o')
  check('xxhash selftest', rc == 0, string.format('exit=%s', tostring(rc)))
end

local function test_stb()
  local rc = minios.run('/objects/stb.o')
  check('stb selftest', rc == 0, string.format('exit=%s', tostring(rc)))
end

local function test_dlmalloc()
  local rc = minios.run('/objects/dlmalloc.o')
  check('dlmalloc selftest', rc == 0, string.format('exit=%s', tostring(rc)))
end

local function test_hello()
  local rc = minios.run('/objects/hello.o', {'arg1', 'arg2'})
  check('hello runs', rc == 42, string.format('exit=%s', tostring(rc)))
end

local function test_ftest()
  local rc = minios.run('/objects/ftest.o', {'ftest_prog'})
  check('ftest libc surface', rc == 7, string.format('exit=%s', tostring(rc)))
end

local function test_minigcc()
  local rc = minios.run('/objects/minigcc.o', {'/src/fib.c'}, '/asm/_t.s')
  check('minigcc compiles', rc == 0, string.format('exit=%s', tostring(rc)))
end

local function test_ld()
  -- Requires minigcc output; skip if _t.s does not exist.
  local f = io.open('/asm/_t.s', 'r')
  if not f then check('ld links', false, 'no /asm/_t.s'); return end
  f:close()
  local rc = minios.run('/objects/ld.o', {'-f', 'elf', '-o', '/bin/_t.elf',
                                          '/asm/_t.s'})
  check('ld links', rc == 0, string.format('exit=%s', tostring(rc)))
end

-- test_cvm skipped: requires shell's argv[0] rewrite, not available via minios.run()

local function test_toolchain_roundtrip()
  local rc = minios.run('/objects/minigcc.o', {'/src/fib.c'}, '/asm/_t.s')
  if rc ~= 0 then check('toolchain roundtrip', false, 'minigcc failed'); return end
  rc = minios.run('/objects/ld.o', {'-f', 'elf', '-o', '/bin/_t.elf', '/asm/_t.s'})
  if rc ~= 0 then check('toolchain roundtrip', false, 'ld failed'); return end
  -- ET_EXEC child from interpreter is a known limitation.
  rc = minios.run('/bin/_t.elf')
  check('toolchain roundtrip', rc == 55, string.format('exit=%s', tostring(rc)))
end

local function test_spawn_preserves_interpreter()
  local before = minios.time_ms()
  local rc = minios.run('/objects/minigcc.o', {'/src/ldhello.c'}, '/asm/_t2.s')
  local after = minios.time_ms()
  check('parent survives child', rc == 0 and after >= before,
        string.format('rc=%s before=%d after=%d', tostring(rc), before, after))
end

-- ── ET_EXEC tools on MiniFS (sorted by size, run via pcall) ───────
-- SYS_SPAWN of an ET_EXEC child from inside an interpreter is a known
-- pre-existing limitation (the parent-window save cannot fit the heap).
-- pcall catches the error so the suite continues.

local function test_bin_cp()
  local ok, rc = pcall(minios.run, '/cp', {'/src/hello.c', '/tmp/_cp_test.c'})
  local passed = ok and rc == 0
  check('cp copies file', passed, string.format('exit=%s', tostring(rc)))
end

local function test_bin_lz4()
  if not write_file('/tmp/_lz4_src.txt', 'lz4 test payload ' .. string.rep('A', 200) .. '\n') then
    check('lz4 roundtrip', false, 'write failed'); return
  end
  local ok1, rc1 = pcall(minios.run, '/lz4', {'/tmp/_lz4_src.txt', '/tmp/_lz4_c.bin'})
  if not ok1 or rc1 ~= 0 then
    check('lz4 roundtrip', false, string.format('compress exit=%s', tostring(rc1))); return
  end
  local ok2, rc2 = pcall(minios.run, '/unlz4', {'/tmp/_lz4_c.bin', '/tmp/_lz4_d.txt'})
  if not ok2 or rc2 ~= 0 then
    check('lz4 roundtrip', false, string.format('decompress exit=%s', tostring(rc2))); return
  end
  local result = read_file('/tmp/_lz4_d.txt')
  check('lz4 roundtrip', result == 'lz4 test payload ' .. string.rep('A', 200) .. '\n',
        string.format('len=%d', #(result or '')))
end

local function test_bin_lzss()
  if not write_file('/tmp/_lzss_src.txt', 'lzss test payload ' .. string.rep('B', 200) .. '\n') then
    check('lzss roundtrip', false, 'write failed'); return
  end
  local ok1, rc1 = pcall(minios.run, '/lzss', {'/tmp/_lzss_src.txt', '/tmp/_lzss_c.bin'})
  if not ok1 or rc1 ~= 0 then
    check('lzss roundtrip', false, string.format('compress exit=%s', tostring(rc1))); return
  end
  local ok2, rc2 = pcall(minios.run, '/unlzss', {'/tmp/_lzss_c.bin', '/tmp/_lzss_d.txt'})
  if not ok2 or rc2 ~= 0 then
    check('lzss roundtrip', false, string.format('decompress exit=%s', tostring(rc2))); return
  end
  local result = read_file('/tmp/_lzss_d.txt')
  check('lzss roundtrip', result == 'lzss test payload ' .. string.rep('B', 200) .. '\n',
        string.format('len=%d', #(result or '')))
end

local function test_bin_aes()
  local key = '00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff'
  local nonce = '000000000000000000000000deadbeef'
  if not write_file('/tmp/_aes_src.txt', 'aes test payload ' .. string.rep('C', 150) .. '\n') then
    check('aes roundtrip', false, 'write failed'); return
  end
  local ok1, rc1 = pcall(minios.run, '/aes', {key, nonce, '/tmp/_aes_src.txt', '/tmp/_aes_enc.bin'})
  if not ok1 or rc1 ~= 0 then
    check('aes roundtrip', false, string.format('encrypt exit=%s', tostring(rc1))); return
  end
  local ok2, rc2 = pcall(minios.run, '/unaes', {key, nonce, '/tmp/_aes_enc.bin', '/tmp/_aes_dec.txt'})
  if not ok2 or rc2 ~= 0 then
    check('aes roundtrip', false, string.format('decrypt exit=%s', tostring(rc2))); return
  end
  local result = read_file('/tmp/_aes_dec.txt')
  check('aes roundtrip', result == 'aes test payload ' .. string.rep('C', 150) .. '\n',
        string.format('len=%d', #(result or '')))
end

local function test_bin_json()
  local path = '/tmp/test.json'
  if not write_file(path, '{"a":1,"b":[2,3],"c":"hello"}\n') then
    check('json validate', false, 'write failed'); return
  end
  local ok, rc = pcall(minios.run, '/json', {path}, '/tmp/_json_out.txt')
  check('json validate', ok and rc == 0, string.format('exit=%s', tostring(rc)))
  local ok2, rc2 = pcall(minios.run, '/json', {path, '.a'}, '/tmp/_json_q.txt')
  check('json query', ok2 and rc2 == 0, string.format('exit=%s', tostring(rc2)))
end

local function test_bin_freedom()
  local ok, rc = pcall(minios.run, '/freedom', {}, '/tmp/_freedom_out.txt')
  -- freedom without args prints usage and exits 1
  check('freedom runs', ok and rc == 1, string.format('exit=%s', tostring(rc)))
end

-- ── Run all tests (sorted by binary size, smallest first) ──────────

print('MiniOS in-OS test suite (Lua)')

test_module_bindings()
test_filesystem()

-- ET_REL objects: smallest to largest
test_xxhash()         -- 2176 bytes
test_stb()            -- 2240 bytes
test_dlmalloc()       -- 3472 bytes
test_hello()          -- 1784 bytes
test_ftest()          -- 2432 bytes
test_minigcc()        -- 145280 bytes
test_ld()             -- 155480 bytes

-- Toolchain roundtrip
test_toolchain_roundtrip()
test_spawn_preserves_interpreter()

-- ET_EXEC tools on MiniFS: smallest to largest
test_bin_cp()         -- 4580 bytes
test_bin_lz4()        -- 8676 bytes
test_bin_lzss()       -- 16868 bytes
test_bin_aes()        -- 16868 bytes
test_bin_json()       -- 16868 bytes
test_bin_freedom()    -- 45540 bytes

print(string.format('TOTAL pass=%d fail=%d', PASS, FAIL))
os.exit(FAIL > 0 and 1 or 0)
