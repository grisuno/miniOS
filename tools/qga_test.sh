#!/usr/bin/env bash
# Quick standalone smoke test for the QEMU guest agent: boots os.img once with
# the agent socket chardev, waits for the shell prompt, drives qga_client.py
# against the socket, and asserts the replies. Exits nonzero on any failure.
#
# This is the low-cost (single boot) check used during development; the full
# end-to-end coverage lives as a scenario in test_bdd.sh.
#
# Env overrides: QEMU, IMAGE, MEM, TMO, MINIOS_GA_SOCK.
set -u

HERE="$(cd "$(dirname "$0")/.." && pwd)"
QEMU="${QEMU:-qemu-system-x86_64}"
IMAGE="${IMAGE:-$HERE/os.img}"
MEM="${MEM:-256M}"
TMO="${TMO:-90}"
SOCK="${MINIOS_GA_SOCK:-/tmp/minios-ga.smoke.$$.sock}"
CON="${MINIOS_GA_CON:-/tmp/minios-ga.smoke.$$.con}"
LOG="$HERE/qga_smoke.log"
CLIENT="python3 $HERE/tools/qga_client.py --sock $SOCK"

PASS=0
FAIL=0

cleanup() {
    rm -f "$SOCK" "$CON"
    [ "${KEEP_LOG:-0}" = "1" ] || rm -f "$LOG"
}
trap cleanup EXIT

check() {
    local what="$1"
    local got="$2"
    if [ -n "$got" ]; then
        echo "    PASS  $what -> $got"
        PASS=$((PASS + 1))
    else
        echo "    FAIL  $what (no/empty reply)"
        FAIL=$((FAIL + 1))
    fi
}

expect_in() {
    local what="$1"
    local hay="$2"
    local needle="$3"
    if printf '%s' "$hay" | grep -q -- "$needle"; then
        echo "    PASS  $what"
        PASS=$((PASS + 1))
    else
        echo "    FAIL  $what (want '$needle' in '$hay')"
        FAIL=$((FAIL + 1))
    fi
}

pkill -9 -f "$QEMU" 2>/dev/null || true
sleep 0.5
rm -f "$SOCK" "$CON"
mkfifo "$CON"

echo "--- qemu guest agent smoke"
# Start QEMU first (it blocks opening the FIFO for reading), then open the
# write end; opening the FIFO write end unblocks QEMU. This is the classic
# FIFO pair ordering: the reader must open before the writer.
timeout "$TMO" "$QEMU" -drive "file=$IMAGE,format=raw,if=ide" -m "$MEM" \
    -nic user,model=rtl8139 -display none -serial stdio -no-reboot \
    -chardev socket,path="$SOCK",server=on,wait=off,id=ga0 \
    -device isa-serial,chardev=ga0,iobase=0x2F8,irq=3 \
    < "$CON" > "$LOG" 2>&1 &
QPID=$!
exec 9>"$CON"

# Wait for the shell prompt: the kernel has booted and the agent (polled only
# while the shell is idle) is answering on the socket.
for _ in $(seq 1 300); do
    tr -d '\r' < "$LOG" | grep -q "miniOS> " && break
    sleep 0.1
done
sleep 0.3

guest_ping=$($CLIENT guest-ping 2>/dev/null)
expect_in "guest-ping returns ok" "${guest_ping:-}" 'return'

guest_info=$($CLIENT guest-info 2>/dev/null)
expect_in "guest-info lists guest-exec" "${guest_info:-}" 'guest-exec'

guest_time=$($CLIENT guest-get-time 2>/dev/null)
expect_in "guest-get-time returns epoch" "${guest_time:-}" '"return":[0-9]'

guest_exec=$($CLIENT guest-exec '{"path":"echo hello-ga > /tmp/ga.txt"}' 2>/dev/null)
expect_in "guest-exec queues a command" "${guest_exec:-}" 'pid'

# Give the queued command a moment to run and write the file.
sleep 1
handle=$($CLIENT guest-file-open '{"path":"/tmp/ga.txt","mode":"r"}' 2>/dev/null)
expect_in "guest-file-open returns a handle" "${handle:-}" '"return":[0-9]'

hval=$(printf '%s' "$handle" | sed -n 's/.*"return":\([0-9]*\).*/\1/p')
if [ -n "$hval" ]; then
    read_resp=$($CLIENT guest-file-read "{\"handle\":$hval,\"count\":100}" 2>/dev/null)
    expect_in "guest-file-read returns base64 content" "${read_resp:-}" 'aGVsbG8tZ2E'
    expect_in "guest-file-read reports exact count" "${read_resp:-}" '"count":9'
    $CLIENT guest-file-close "{\"handle\":$hval}" >/dev/null 2>&1
else
    echo "    FAIL  could not parse guest-file-open handle"
    FAIL=$((FAIL + 1))
fi

# A well-formed request for an unknown command must be rejected.
bad=$($CLIENT guest-does-not-exist 2>/dev/null)
expect_in "unknown command rejected" "${bad:-}" 'CommandNotFound'

# Raw malformed bytes must be rejected fail-closed by the agent's parser.
raw_bad=$(python3 - "$SOCK" <<'PYEOF'
import socket, sys, time
s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
s.connect(sys.argv[1]); s.settimeout(3)
s.sendall(b'this is not json {\n')
out = b""
try:
    while True:
        c = s.recv(4096)
        if not c: break
        out += c
except socket.timeout:
    pass
s.close()
print(out.decode(), end="")
PYEOF
)
expect_in "malformed request rejected" "${raw_bad:-}" 'error'

# Power off through the console.
printf 'poweroff\n' >&9
wait "$QPID" 2>/dev/null
exec 9>&-

echo "=== summary: $PASS passed, $FAIL failed ==="
[ "$FAIL" -gt 0 ] && exit 1
exit 0
