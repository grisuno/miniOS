#!/bin/bash
# BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over
# the serial console (COM1). Every scenario sends a script of shell commands,
# then asserts that the expected markers appear in the console log.
#
# The guest powers itself off through the ACPI port at the end of each
# scenario, which makes QEMU exit; the timeout is only a safety net for hangs.
# A stale-qemu guard prevents image-lock cascades between runs.
#
# Environment overrides: QEMU, TMO (per-scenario timeout), KEEP_LOG=1 to keep
# the console log of the last scenario for inspection.

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
QEMU="${QEMU:-qemu-system-x86_64}"
TMO="${TMO:-120}"
MEM="${MEM:-256M}"
IMAGE="$HERE/os.img"
LOG="$HERE/test_bdd.log"
KEEP_LOG="${KEEP_LOG:-0}"
FAIL_FAST="${FAIL_FAST:-0}"

PASS=0
FAIL=0
FAILED_NAMES=""
SCENARIO=""

cleanup_stale_qemu() {
    pkill -9 -x "$(basename "$QEMU")" 2>/dev/null || true
    sleep 1
}

# scenario <name> <script of shell commands>
scenario() {
    SCENARIO="$1"
    local cmds="$2"
    echo "--- $SCENARIO"
    cleanup_stale_qemu
    {
        sleep 4
        printf '%s\n' "$cmds"
        sleep 2
    } | timeout "$TMO" "$QEMU" \
        -drive "file=$IMAGE,format=raw,if=ide" -m "$MEM" \
        -display none -serial stdio -no-reboot > "$LOG" 2>&1
    if [ $? -eq 124 ]; then
        echo "    NOTE: timed out (guest did not power off)"
    fi
}

# expect <marker>
expect() {
    local what="$1"
    if grep -q -- "$what" "$LOG"; then
        echo "    PASS  $what"
        PASS=$((PASS + 1))
    else
        echo "    FAIL  $what"
        FAIL=$((FAIL + 1))
        FAILED_NAMES="$FAILED_NAMES [$SCENARIO: $what]"
        if [ "$FAIL_FAST" = "1" ]; then
            echo ""
            echo "=== summary: $PASS passed, $FAIL failed (stopped at first failure) ==="
            [ "$KEEP_LOG" = "1" ] || rm -f "$LOG"
            exit 1
        fi
    fi
}

if [ ! -f "$IMAGE" ]; then
    echo "os.img not found; run make first"
    exit 1
fi

echo "=== MiniOS BDD ==="

scenario "boot and power off" "poweroff"
expect "MiniOS Kernel"
expect "powering off"

scenario "shell help advertises the editor" "help
poweroff"
expect "edit <file>"
expect "powering off"

scenario "editor creates a file and cat reads it back" "edit hello.txt
a
hello from edit
w
x
cat hello.txt
poweroff"
expect "new file hello.txt"
expect "wrote 1 line(s) to hello.txt"
expect "hello from edit"

scenario "editor inserts a line" "edit hello.txt
a
first line
i 1
second line
w
x
cat hello.txt
poweroff"
expect "wrote 2 line(s) to hello.txt"
expect "second line"

scenario "editor deletes a line" "edit hello.txt
a
only line
a
doomed line
d 2
w
x
cat hello.txt
poweroff"
expect "wrote 1 line(s) to hello.txt"
expect "only line"

scenario "new files appear in the directory listing" "edit listed.txt
a
content
x
ls
poweroff"
expect "listed.txt"

scenario "cvm module built by ld runs on the interpreter" "run fib.cvm
poweroff"
expect "exit code: 55"

scenario "cvm module prints through the write native" "run w1.cvm
poweroff"
expect "hola cvm"

scenario "ELF produced by ld returns its exit code" "run ldhello.elf
poweroff"
expect "exit code: 42"

scenario "ELF produced by ld computes fib(10)" "run fib.elf
poweroff"
expect "exit code: 55"

scenario "native Linux static ELF runs unmodified" "run lxhello.elf
poweroff"
expect "Hello"

scenario "editor guards unsaved changes on quit" "edit guard.txt
a
work in progress
q
q!
ls
poweroff"
expect "unsaved changes"

scenario "shell redirects command output to a file" "echo redirected text > r.txt
cat r.txt
poweroff"
expect "redirected text"

scenario "redirection captures compiler output" "run minigcc.o test.c > t.s
cat t.s
poweroff"
expect ".section .text"

scenario "toolchain compiles and links a program written inside the OS" "edit p.c
a
int main(void) { return 7; }
x
run minigcc.o p.c > p.s
run ld.o -f elf -o p.elf p.s
run p.elf
poweroff"
expect "exit code: 7"

scenario "toolchain also produces a cvm module inside the OS" "edit q.c
a
int main(void) { return 21; }
x
run minigcc.o q.c > q.s
run ld.o -f cvm -o q.cvm q.s
run q.cvm
poweroff"
expect "exit code: 21"

echo ""
echo "=== summary: $PASS passed, $FAIL failed ==="
[ "$KEEP_LOG" = "1" ] || rm -f "$LOG"
if [ "$FAIL" -gt 0 ]; then
    echo "failed:$FAILED_NAMES"
    exit 1
fi
exit 0
