#!/bin/bash
# test_sb16.sh — targeted BDD harness for the SB16 audio path.
#
# Boots the disk image once with the SB16 device attached (headless, null
# audio backend) and drives the shell over the serial console:
#
#   run sbtone    streams 440 Hz PCM and reports how many buffers the ring
#                 actually accepted over a 3 s guest window;
#   sb16          prints the driver's re-arm and submit/drop counters.
#
# A healthy driver must drain the 7-slot ring via the timer watchdog (the null
# backend never raises a completion IRQ), so sbtone must accept ~32 of ~33
# buffers and the counters must show poll arms > 0 and drops of 0.  This is
# the regression test for the wedge where the ring filled once and every later
# submit was refused.  Exits nonzero on any failed assertion.

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(dirname "$HERE")"
QEMU="${QEMU:-qemu-system-x86_64}"
TMO="${TMO:-90}"
IMAGE="$ROOT/os.img"
LOG="${TMPDIR:-/tmp}/test_sb16.log"
MIN_BUFFERS="${MIN_BUFFERS:-30}"

pkill -9 -f "$QEMU" 2>/dev/null || true
sleep 0.5

{
    sleep 8
    printf 'run sbtone\n'
    sleep 40
    printf 'sb16\n'
    sleep 4
    printf 'poweroff\n'
    sleep 6
} | timeout "$TMO" "$QEMU" \
    -drive "file=$IMAGE,format=raw,if=ide" -m 256M \
    -nic user,model=rtl8139 \
    -audiodev none,id=snd1 -device sb16,iobase=0x220,irq=5,dma=1,audiodev=snd1 \
    -display none -serial stdio -monitor none > "$LOG" 2>&1

fail=0
fail_msg() {
    echo "FAIL  $1"
    fail=1
}

count=$(tr -d '\r' < "$LOG" | grep -o 'sbtone: submitted [0-9]*' | grep -o '[0-9]*' | tail -1)
if [ -z "$count" ]; then
    fail_msg "sbtone produced no submission count"
elif [ "$count" -ge "$MIN_BUFFERS" ]; then
    echo "PASS  sbtone accepted $count buffers (>= $MIN_BUFFERS)"
else
    fail_msg "sbtone accepted only $count buffers (need >= $MIN_BUFFERS); ring likely wedged"
fi

if tr -d '\r' < "$LOG" | grep -q 'sb16: arms irq=[0-9]* poll=[1-9]'; then
    echo "PASS  sb16 watchdog performed poll arms"
else
    fail_msg "sb16 watchdog poll arms missing or zero (no timer-driven re-arm)"
fi

if tr -d '\r' < "$LOG" | grep -q 'sb16: .* drops=0$'; then
    echo "PASS  no PCM submits were dropped"
else
    fail_msg "some PCM submits were dropped"
fi

echo "=== sb16 target log ==="
grep -E 'sbtone:|sb16:|exit code|MiniOS Kernel|sb16:' "$LOG" | tr -d '\r'
if [ "${KEEP_LOG:-0}" = "1" ]; then
    echo "log kept at $LOG"
else
    rm -f "$LOG"
fi
exit "$fail"
