-- test.lua -- in-OS test suite for MiniOS, driven by Lua.
--
-- The Lua counterpart of src/test.py (MicroPython): verifies the kernel
-- (the `minios` module bindings) and the self-hosted toolchain
-- (minigcc -> ld -> execute) from inside the machine, through the
-- minios.run() SYS_SPAWN boundary.
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

local function test_toolchain()
  -- Compile a known source to assembly (captured to a temp file).
  local rc = minios.run('/objects/minigcc.o', {'/src/fib.c'}, '/asm/_t.s')
  check('minigcc compiles', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  -- Link the assembly into an ELF.
  rc = minios.run('/objects/ld.o', {'-f', 'elf', '-o', '/bin/_t.elf',
                                    '/asm/_t.s'})
  check('ld links', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  -- Execute the freshly built ELF.  fib.c's main returns fib(10) = 55.
  rc = minios.run('/bin/_t.elf')
  check('built elf runs', rc == 55, string.format('exit=%d', rc))
end

local function test_spawn_preserves_interpreter()
  local before = minios.time_ms()
  local rc = minios.run('/objects/minigcc.o', {'/src/ldhello.c'}, '/asm/_t2.s')
  local after = minios.time_ms()
  check('parent survives child', rc == 0 and after >= before,
        string.format('rc=%d before=%d after=%d', rc, before, after))
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

local function test_json()
  local path = '/tmp/test.json'
  if not write_file(path, '{"a":1,"b":[2,3],"c":"hello"}\n') then
    check('json validate', false, 'write failed'); return
  end
  local rc = minios.run('/json', {path}, '/tmp/_json_out.txt')
  check('json validate', rc == 0, string.format('exit=%d', rc))
  local rc2 = minios.run('/json', {path, '.a'}, '/tmp/_json_q.txt')
  check('json query', rc2 == 0, string.format('exit=%d', rc2))
end

local function test_lzss_roundtrip()
  local payload = 'lzss roundtrip test data ' .. string.rep('x', 200) .. '\n'
  if not write_file('/tmp/_lzss_src.txt', payload) then
    check('lzss compress', false, 'write failed'); return
  end
  local rc = minios.run('/lzss', {'/tmp/_lzss_src.txt', '/tmp/_lzss_c.bin'})
  check('lzss compress', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  rc = minios.run('/unlzss', {'/tmp/_lzss_c.bin', '/tmp/_lzss_d.txt'})
  check('lzss decompress', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  local result = read_file('/tmp/_lzss_d.txt')
  check('lzss roundtrip', result == payload,
        string.format('len=%d expected=%d', #(result or ''), #payload))
end

local function test_lz4_roundtrip()
  local payload = 'lz4 roundtrip test data ' .. string.rep('y', 300) .. '\n'
  if not write_file('/tmp/_lz4_src.txt', payload) then
    check('lz4 compress', false, 'write failed'); return
  end
  local rc = minios.run('/lz4', {'/tmp/_lz4_src.txt', '/tmp/_lz4_c.bin'})
  check('lz4 compress', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  rc = minios.run('/unlz4', {'/tmp/_lz4_c.bin', '/tmp/_lz4_d.txt'})
  check('lz4 decompress', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  local result = read_file('/tmp/_lz4_d.txt')
  check('lz4 roundtrip', result == payload,
        string.format('len=%d expected=%d', #(result or ''), #payload))
end

local function test_aes_roundtrip()
  local key = '00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff'
  local nonce = '000000000000000000000000deadbeef'
  local payload = 'aes roundtrip test data ' .. string.rep('z', 150) .. '\n'
  if not write_file('/tmp/_aes_src.txt', payload) then
    check('aes encrypt', false, 'write failed'); return
  end
  local rc = minios.run('/aes', {key, nonce, '/tmp/_aes_src.txt', '/tmp/_aes_enc.bin'})
  check('aes encrypt', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  rc = minios.run('/unaes', {key, nonce, '/tmp/_aes_enc.bin', '/tmp/_aes_dec.txt'})
  check('aes decrypt', rc == 0, string.format('exit=%d', rc))
  if rc ~= 0 then return end
  local result = read_file('/tmp/_aes_dec.txt')
  check('aes roundtrip', result == payload,
        string.format('len=%d expected=%d', #(result or ''), #payload))
end

local function test_freedom()
  local rc = minios.run('/freedom', {}, '/tmp/_freedom_out.txt')
  check('freedom runs', rc == 1, string.format('exit=%d', rc))
end

print('MiniOS in-OS test suite (Lua)')
test_module_bindings()
test_spawn_preserves_interpreter()
test_toolchain()
test_filesystem()
test_json()
test_lzss_roundtrip()
test_lz4_roundtrip()
test_aes_roundtrip()
test_freedom()
print(string.format('TOTAL pass=%d fail=%d', PASS, FAIL))
os.exit(FAIL > 0 and 1 or 0)
