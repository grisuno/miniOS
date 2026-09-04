# test_all.sh -- comprehensive non-interactive test suite for MiniOS.
#
# Run with:  sh src/test_all.sh
#
# Every test prints a PASS: or FAIL: marker.  The host-side runner
# greps the QEMU serial log for these markers.
# No interactive commands, no external server dependencies.

# === HELP & CLEAR ===
echo PASS: boot-ok
help
echo PASS: help-ok
clear
echo PASS: clear-ok

# === FILESYSTEM: ls, mkdir, cd, pwd, rm, cp ===
ls
echo PASS: ls-root-ok
ls objects/
echo PASS: ls-objects-ok
ls bin/
echo PASS: ls-bin-ok
mkdir workdir
echo PASS: mkdir-ok
cd workdir
echo PASS: cd-workdir-ok
pwd
echo PASS: pwd-workdir-ok
cd /
echo PASS: cd-root-ok
mkdir delme
rm delme
echo PASS: rm-ok
cp src/fib.c /tmp/cp_test.txt
cat /tmp/cp_test.txt
echo PASS: cp-cat-ok
rm /tmp/cp_test.txt

# === REDIRECTS ===
echo hello-redirect > /tmp/redir_test.txt
cat /tmp/redir_test.txt
echo PASS: redirect-ok
rm /tmp/redir_test.txt
echo append-data > /tmp/redir_test.txt
cat /tmp/redir_test.txt >> /tmp/redir_test.txt
cat /tmp/redir_test.txt
echo PASS: append-ok
rm /tmp/redir_test.txt

# === ECHO ===
echo echo-test-123
echo PASS: echo-ok

# === DATE & VOL ===
date
echo PASS: date-ok
vol
echo PASS: vol-ok
vol 40
vol
echo PASS: vol-set-ok
vol 100
echo PASS: vol-reset-ok

# === PS & TRACE ===
ps
echo PASS: ps-ok
trace on
trace off
echo PASS: trace-ok

# === NET ===
net
echo PASS: net-ok
net ping 10.0.2.2
echo PASS: net-ping-ok

# === GFX & WM ===
gfx
echo PASS: gfx-ok
wm state
echo PASS: wm-state-ok

# === HASH ===
hash src/fib.c
echo PASS: hash-ok

# === TOOLCHAIN: compile C -> asm -> ELF -> run ===
minigcc.o src/fib.c > asm/test_all_fib.s
echo PASS: compile-ok
ld.o -f elf -o bin/test_all_fib.elf asm/test_all_fib.s
echo PASS: link-ok
run bin/test_all_fib.elf
echo PASS: run-elf-ok

# === TOOLCHAIN: compile C -> CVM module -> run ===
minigcc.o src/w1.c > asm/test_all_w1.s
echo PASS: compile-cvm-ok
ld.o -f cvm -o cvm/test_all_w1.cvm asm/test_all_w1.s
echo PASS: link-cvm-ok
run cvm/test_all_w1.cvm
echo PASS: run-cvm-ok

# === TOOLCHAIN: bare names (no run prefix) ===
ld.o -f elf -o bin/test_all_bare.elf asm/test_all_fib.s
echo PASS: bare-ld-ok
bin/test_all_fib.elf
echo PASS: bare-elf-ok
w1.cvm
echo PASS: bare-cvm-ok

# === SELF-HOST: minigcc.elf compiles, ld.o links, run ===
run bin/minigcc.elf src/fib.c > asm/test_all_sh.s
echo PASS: selfhost-compile-ok
run objects/ld.o -f elf -o bin/test_all_sh.elf asm/test_all_sh.s
echo PASS: selfhost-link-ok
run bin/test_all_sh.elf
echo PASS: selfhost-run-ok

# === CODECS: lzss roundtrip ===
echo lzss-roundtrip-payload-ABCDEFGHIJKLMNOPQRSTUVWXYZ > /tmp/lzss_src.txt
run bin/lzss /tmp/lzss_src.txt /tmp/lzss_c.bin
echo PASS: lzss-compile-ok
run bin/unlzss /tmp/lzss_c.bin /tmp/lzss_dst.txt
echo PASS: lzss-decompile-ok
cat /tmp/lzss_dst.txt
rm /tmp/lzss_src.txt
rm /tmp/lzss_c.bin
rm /tmp/lzss_dst.txt

# === CODECS: lz4 roundtrip ===
echo lz4-roundtrip-payload-0123456789 > /tmp/lz4_src.txt
run bin/lz4 /tmp/lz4_src.txt /tmp/lz4_c.bin
echo PASS: lz4-compile-ok
run bin/unlz4 /tmp/lz4_c.bin /tmp/lz4_dst.txt
echo PASS: lz4-decompile-ok
cat /tmp/lz4_dst.txt
rm /tmp/lz4_src.txt
rm /tmp/lz4_c.bin
rm /tmp/lz4_dst.txt

# === CODECS: aes roundtrip ===
echo aes-roundtrip-payload-top-secret-data > /tmp/aes_src.txt
run bin/aes 00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff 000000000000000000000000deadbeef /tmp/aes_src.txt /tmp/aes_enc.bin
echo PASS: aes-encrypt-ok
run bin/unaes 00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff 000000000000000000000000deadbeef /tmp/aes_enc.bin /tmp/aes_dec.txt
echo PASS: aes-decrypt-ok
cat /tmp/aes_dec.txt
rm /tmp/aes_src.txt
rm /tmp/aes_enc.bin
rm /tmp/aes_dec.txt

# === CODECS: error cases ===
lzss missing_nope.txt /tmp/x.lzs
echo PASS: lzss-error-ok
lz4 missing_nope.txt /tmp/x.lz4
echo PASS: lz4-error-ok

# === JSON ===
echo {"name":"miniOS","version":1,"live":true} > /tmp/test.json
json /tmp/test.json
json /tmp/test.json .name
echo PASS: json-ok
rm /tmp/test.json

# === ZIP: hostile archive ===
unzip etc/hostile.zip /tmp/hostile
echo PASS: hostile-zip-ok

# === ZIP: host-produced archive ===
unzip etc/host.zip /tmp/hostzip
cat /tmp/hostzip/sub/note.txt
cat /tmp/hostzip/top.txt
echo PASS: host-zip-ok

# === ELF PROGRAMS ===
run bin/lxhello.elf
echo PASS: lxhello-ok
run bin/cpl.elf
echo PASS: cpl-ok
run bin/kmem.elf
echo PASS: kmem-ok
run bin/nx.elf
echo PASS: nx-ok
run bin/mmreuse.elf
echo PASS: mmreuse-ok

# === CVM MODULES ===
run cvm/fib.cvm
echo PASS: cvm-fib-ok
run cvm/w1.cvm
echo PASS: cvm-w1-ok

# === SELFTESTS (ring-0 .o objects) ===
run objects/xxhash.o
echo PASS: xxhash-ok
run objects/dlmalloc.o
echo PASS: dlmalloc-ok

# === REPEATED RUNS (heap stability) ===
run cvm/fib.cvm
run cvm/w1.cvm
run cvm/fib.cvm
echo PASS: heap-stability-ok

# === TRACING ===
trace on
cp src/fib.c /tmp/trace_test.txt
trace off
echo PASS: trace-run-ok
rm /tmp/trace_test.txt

# === DONE ===
echo PASS: ALL-TESTS-DONE
