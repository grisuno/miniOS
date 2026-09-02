#!/bin/bash
# boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the
# serial console with a list of commands, capturing the full transcript.
#
# This is the reusable harness behind the one-shot manual checks (lua in-OS
# suite, DOOM/Quake 2 autoquit render tests, toolchain compile/link/run) so a
# future run does not hand-roll a QEMU launch.  The guest powers itself off
# through the ACPI port; the timeout is only a safety net for hangs.
#
# Usage:
#   tools/boot_run.sh "cmd1" "cmd2" ... [--timeout N] [--log FILE]
#
#   - every non-option argument is a shell command sent to the guest in order
#   - --timeout N   per-run timeout in seconds (default 200)
#   - --log FILE    write the console transcript to FILE (default ./boot_run.log)
#
# Examples:
#   tools/boot_run.sh "lua src/test.lua"
#   tools/boot_run.sh "gfx frames" "run doomgeneric.elf mini_autoframes 150" \
#                     "gfx frames" --timeout 200
#   tools/boot_run.sh "gfx frames" \
#                     "run bin/quake2generic.elf +set basedir . +set minios_autoframes 400" \
#                     "gfx frames" --timeout 300

set -u
HERE="$(cd "$(dirname "$0")/.." && pwd)"
QEMU="${QEMU:-qemu-system-x86_64}"
MEM="${MEM:-1G}"
TMO=200
LOG="$HERE/boot_run.log"
CMDS=()

while [ $# -gt 0 ]; do
    case "$1" in
        --timeout) TMO="$2"; shift 2 ;;
        --log)     LOG="$2"; shift 2 ;;
        *)         CMDS+=("$1"); shift ;;
    esac
done

if [ ${#CMDS[@]} -eq 0 ]; then
    echo "usage: $0 <cmd> [cmd...] [--timeout N] [--log FILE]" >&2
    exit 1
fi

# Kill any stale guest so the image write lock is never held across runs.
pkill -9 -f "$QEMU" 2>/dev/null || true
sleep 0.5

{
    sleep 4
    printf '%s\n' "${CMDS[@]}"
    printf '%s\n' "poweroff"
} | timeout "$TMO" "$QEMU" \
    -drive "file=$HERE/os.img,format=raw,if=ide" -m "$MEM" \
    -nic user,model=rtl8139 \
    -display none -serial stdio -no-reboot > "$LOG" 2>&1

rc=$?
if [ $rc -eq 124 ]; then
    echo "NOTE: timed out after ${TMO}s (guest did not power off)" >&2
fi
echo "console transcript: $LOG"
exit $rc
