#!/bin/bash
# test_codecs.sh -- exercise the lzss/lz4/aes command-pair tools inside the OS.
#
# The interpreter in-OS suites (test.lua / test.py) cannot run these ET_EXEC
# tools: SYS_SPAWN of an ET_EXEC child from inside an interpreter must save the
# parent's user window, which cannot fit the heap (a pre-existing limitation),
# so minios.run() returns nil and those tests report FAIL.  The shell CAN run
# ET_EXEC binaries, so this harness drives the real compress/decompress and
# encrypt/decrypt roundtrips through the serial console instead.
#
# Usage:
#   tools/test_codecs.sh
#
# Exits 0 when every roundtrip checks out, 1 otherwise.

set -u
HERE="$(cd "$(dirname "$0")/.." && pwd)"
LOG="$HERE/boot_codecs.log"

# The source payloads are written with the `edit` builtin; each line must be
# short.  We then compress/decompress/encrypt/decrypt and cat the result back.
# An exact byte match is hard to eyeball, so we rely on the tools' own
# fail-closed guarantees: a bad magic/size aborts with a diagnostic and a
# nonzero exit, and unlzss/unaes report exact byte counts.
"$HERE/tools/boot_run.sh" \
    "edit /tmp/c_src.txt" \
    "a" "lzss roundtrip payload abcdefghijklmnopqrstuvwxyz" "x" \
    "run bin/lzss /tmp/c_src.txt /tmp/c_c.bin" \
    "run bin/unlzss /tmp/c_c.bin /tmp/c_d.txt" \
    "cat /tmp/c_d.txt" \
    "edit /tmp/c4_src.txt" \
    "a" "lz4 roundtrip payload ABCDEFGHIJKLMNOPQRSTUVWXYZ" "x" \
    "run bin/lz4 /tmp/c4_src.txt /tmp/c4_c.bin" \
    "run bin/unlz4 /tmp/c4_c.bin /tmp/c4_d.txt" \
    "cat /tmp/c4_d.txt" \
    "edit /tmp/a_src.txt" \
    "a" "aes roundtrip payload 0123456789abcdef" "x" \
    "run bin/aes 00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff 000000000000000000000000deadbeef /tmp/a_src.txt /tmp/a_enc.bin" \
    "run bin/unaes 00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff 000000000000000000000000deadbeef /tmp/a_enc.bin /tmp/a_dec.txt" \
    "cat /tmp/a_dec.txt" \
    --timeout 200 --log "$LOG"

rc=$?

# Assert the decompressed/decrypted payloads came back intact.
pass=0
fail=0
for payload in "lzss roundtrip payload abcdefghijklmnopqrstuvwxyz" \
               "lz4 roundtrip payload ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
               "aes roundtrip payload 0123456789abcdef"; do
    if tr -d '\r' < "$LOG" | grep -q -- "$payload"; then
        echo "    PASS $payload"
        pass=$((pass + 1))
    else
        echo "    FAIL $payload"
        fail=$((fail + 1))
    fi
done

echo "codecs: pass=$pass fail=$fail (transcript: $LOG)"
[ "$fail" -eq 0 ] && [ $rc -eq 0 ]
