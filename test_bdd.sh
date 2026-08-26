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
BOOT_WAIT="${BOOT_WAIT:-1}"
IMAGE="$HERE/os.img"
LOG="$HERE/test_bdd.log"
KEEP_LOG="${KEEP_LOG:-0}"
FAIL_FAST="${FAIL_FAST:-0}"

PASS=0
FAIL=0
FAILED_NAMES=""
SCENARIO=""

cleanup_stale_qemu() {
    # pkill -x matches against the process name, which the kernel truncates
    # to 15 chars (qemu-system-x86), so -x never matches a real qemu and a
    # stale guest would survive holding the image lock. Match the command
    # line instead; at this point no qemu of ours is running, so the only
    # matches are stale ones.
    pkill -9 -f "$QEMU" 2>/dev/null || true
    sleep 0.5
}

# scenario <name> <script of shell commands>
scenario() {
    SCENARIO="$1"
    local cmds="$2"
    echo "--- $SCENARIO"
    cleanup_stale_qemu
    {
        sleep "$BOOT_WAIT"
        printf '%s\n' "$cmds"
    } | timeout "$TMO" "$QEMU" \
        -drive "file=$IMAGE,format=raw,if=ide" -m "$MEM" \
        -nic user,model=rtl8139 \
        -display none -serial stdio -no-reboot > "$LOG" 2>&1
    if [ $? -eq 124 ]; then
        echo "    NOTE: timed out (guest did not power off)"
    fi
}

# expect <marker>
expect() {
    local what="$1"
    if tr -d '\r' < "$LOG" | grep -q -- "$what"; then
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

# expect_count <count> <marker>: the marker must appear exactly that many
# times in the log. Used where a single occurrence would also match the
# echoed command line, so only the output can prove the behaviour.
expect_count() {
    local n="$1"
    local what="$2"
    local got
    got=$(tr -d '\r' < "$LOG" | grep -o -- "$what" | wc -l)
    if [ "$got" -eq "$n" ]; then
        echo "    PASS  $what x$n"
        PASS=$((PASS + 1))
    else
        echo "    FAIL  $what (expected x$n, found x$got)"
        FAIL=$((FAIL + 1))
        FAILED_NAMES="$FAILED_NAMES [$SCENARIO: $what x$n]"
        if [ "$FAIL_FAST" = "1" ]; then
            echo ""
            echo "=== summary: $PASS passed, $FAIL failed (stopped at first failure) ==="
            [ "$KEEP_LOG" = "1" ] || rm -f "$LOG"
            exit 1
        fi
    fi
}

# refute <marker>: the marker must NOT appear (suppressed hostile content).
refute() {
    local what="$1"
    if tr -d '\r' < "$LOG" | grep -q -- "$what"; then
        echo "    FAIL  (unexpected) $what"
        FAIL=$((FAIL + 1))
        FAILED_NAMES="$FAILED_NAMES [$SCENARIO: unexpected $what]"
        if [ "$FAIL_FAST" = "1" ]; then
            echo ""
            echo "=== summary: $PASS passed, $FAIL failed (stopped at first failure) ==="
            [ "$KEEP_LOG" = "1" ] || rm -f "$LOG"
            exit 1
        fi
    else
        echo "    PASS  (absent) $what"
        PASS=$((PASS + 1))
    fi
}

if [ ! -f "$IMAGE" ]; then
    echo "os.img not found; run make first"
    exit 1
fi

echo "=== MiniOS BDD ==="

scenario "boot and power off" "poweroff"
expect "MiniOS Kernel"
expect "isolation"
expect "powering off"

scenario "KASLR slides the kernel physical base per boot" "poweroff"
expect "kernel: physical base 0x"
refute "kernel: physical base 0x100000"

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

scenario "cvm module built by ld runs on the interpreter" "run cvm/fib.cvm
poweroff"
expect "exit code: 55"

scenario "cvm module prints through the write native" "run cvm/w1.cvm
poweroff"
expect "hola cvm"

scenario "ELF produced by ld returns its exit code" "run bin/ldhello.elf
poweroff"
expect "exit code: 42"

scenario "ELF produced by ld computes fib(10)" "run bin/fib.elf
poweroff"
expect "exit code: 55"

scenario "native Linux static ELF runs unmodified" "run bin/lxhello.elf
poweroff"
expect "Hello"

scenario "user-mode isolation drops ET_EXEC binaries to ring 3" "run bin/cpl.elf
poweroff"
expect "exit code: 3"

scenario "syscall boundary rejects kernel-space pointers" "run bin/kmem.elf
poweroff"
expect "exit code: 0"

scenario "user pages are non-executable unless the segment is executable" "run bin/nx.elf
poweroff"
expect "nx: jumping to stack"
refute "powering off"

scenario "run resolves a bare .o name from objects/" "run minigcc.o src/fib.c > asm/bare.s
run objects/ld.o -f elf -o bin/bare.elf asm/bare.s
run bin/bare.elf
poweroff"
expect "exit code: 0"
expect "exit code: 55"

scenario "a bare .o name runs directly from objects/ without run" "ld.o -f elf -o bin/bare2.elf asm/fib.s
poweroff"
expect "exit code: 0"

scenario "a bare .elf name runs directly from bin/ without run" "fib.elf
poweroff"
expect "exit code: 55"

scenario "a bare .cvm name runs directly from cvm/ without run" "w1.cvm
poweroff"
expect "hola cvm"
expect "exit code: 0"

scenario "run resolves a bare .cvm name from cvm/" "run fib.cvm
poweroff"
expect "exit code: 55"

scenario "a bare .o toolchain object drives the full compile pipeline" "minigcc.o src/fib.c > asm/direct.s
ld.o -f elf -o bin/direct.elf asm/direct.s
direct.elf
poweroff"
expect "exit code: 55"

scenario "an unresolvable bare name falls through to command not found" "nosuchfile.o
poweroff"
expect "command not found: nosuchfile.o"

scenario "run reports an unresolvable cvm module as not found" "run nosuchmod.cvm
poweroff"
expect "run: not found: nosuchmod.cvm"

scenario "TAB completes a runnable path from objects/" $'objects/ld\t\npoweroff'
expect "usage: ld"

scenario "TAB completes a bare runnable name to its full path" $'ld.\t\npoweroff'
expect "usage: ld"

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

scenario "append redirect adds instead of truncating" "cp src/fib.c log.txt
cat src/fib.c >> log.txt
cat log.txt
poweroff"
expect_count 2 "int fib"

scenario "append redirect creates a missing file" "cat src/fib.c >> fresh.txt
cat fresh.txt
poweroff"
expect "int fib"

scenario "redirection captures compiler output" "run objects/minigcc.o src/test.c > asm/t.s
cat asm/t.s
poweroff"
expect ".section .text"

scenario "toolchain compiles and links a program written inside the OS" "edit src/p.c
a
int main(void) { return 7; }
x
run objects/minigcc.o src/p.c > asm/p.s
run objects/ld.o -f elf -o bin/p.elf asm/p.s
run bin/p.elf
poweroff"
expect "exit code: 7"

scenario "toolchain also produces a cvm module inside the OS" "edit src/q.c
a
int main(void) { return 21; }
x
run objects/minigcc.o src/q.c > asm/q.s
run objects/ld.o -f cvm -o cvm/q.cvm asm/q.s
run cvm/q.cvm
poweroff"
expect "exit code: 21"

scenario "cvm module run with arguments gets a Linux-style argv and keeps its strings" "run cvm/minigcc.cvm src/test.c > asm/t2.s
cat asm/t2.s
run objects/ld.o -f cvm -o cvm/t2.cvm asm/t2.s
run cvm/t2.cvm
poweroff"
expect ".globl add"
expect "exit code: 0"
expect "exit code: 12"

scenario "self-hosted minigcc (compiled by minigcc, linked by ld) compiles inside the OS" "run bin/minigcc.elf src/test.c > asm/t.s
run objects/ld.o -f elf -o bin/t.elf asm/t.s
run bin/t.elf
poweroff"
expect "exit code: 12"

scenario "bin path runs an ELF as a plain command" "cp src/fib.c copy1.txt
cat copy1.txt
poweroff"
expect "exit code: 0"
expect "int fib"

scenario "cp reports failures through its exit code" "cp missing.txt x.txt
cp src/fib.c
poweroff"
expect "cannot open missing.txt"
expect "exit code: 1"
expect "usage: cp <src> <dst>"

scenario "bin path entries are skipped for unknown commands" "nosuchcmd
poweroff"
expect "command not found: nosuchcmd"

scenario "lzss roundtrips a repetitive text file" "edit rep.txt
a
the quick brown fox jumps over the lazy dog
a
the quick brown fox jumps over the lazy dog
a
the quick brown fox jumps over the lazy dog
x
lzss rep.txt rep.lzs
unlzss rep.lzs rep.out
cat rep.out
poweroff"
expect "wrote 3 line(s) to rep.txt"
expect "lzss: rep.txt -> rep.lzs"
expect "unlzss: rep.lzs -> rep.out"
expect "the quick brown fox jumps over the lazy dog"

scenario "lzss selection by argv0 decodes with the -d flag too" "lzss rep.txt
poweroff"
expect "usage: lzss [-d] <src> <dst>"

scenario "unlzss rejects a file without the LZS1 magic" "cp src/fib.c bad.lzs
unlzss bad.lzs out.bin
poweroff"
expect "unlzss: bad.lzs: bad magic"
expect "exit code: 1"

scenario "lzss reports failures through its exit code" "lzss missing.txt x.lzs
poweroff"
expect "lzss: cannot open missing.txt"
expect "exit code: 1"

scenario "lz4 roundtrips a repetitive text file" "edit rep4.txt
a
lz4 lz4 lz4 lz4 lz4 lz4 lz4 lz4
x
lz4 rep4.txt rep4.lz4
unlz4 rep4.lz4 rep4.out
cat rep4.out
poweroff"
expect "wrote 1 line(s) to rep4.txt"
expect "lz4: rep4.txt -> rep4.lz4"
expect "unlz4: rep4.lz4 -> rep4.out"
expect "lz4 lz4 lz4 lz4 lz4 lz4 lz4 lz4"

scenario "lz4 reports failures through its exit code" "lz4 missing.txt x.lz4
poweroff"
expect "lz4: cannot open missing.txt"
expect "exit code: 1"

scenario "unlz4 rejects a truncated header and an implausible size" "edit t.lz4
a
xx
x
edit aaaa.lz4
a
AAAA
x
unlz4 t.lz4 out.bin
unlz4 aaaa.lz4 out.bin
poweroff"
expect "unlz4: t.lz4: truncated header"
expect "unlz4: aaaa.lz4: implausible size"
expect "exit code: 1"

scenario "lz4 usage without arguments" "lz4
poweroff"
expect "usage: lz4 [-d] <src> <dst>"

scenario "shell up arrow recalls the last command" "run cvm/fib.cvm
$(printf '\033[A')
poweroff"
expect_count 2 "exit code: 55"
expect "powering off"

scenario "shell arrows scroll history and restore the live line" "run cvm/fib.cvm
run cvm/w1.cvm
$(printf '\033[A\033[B')
run cvm/fib.cvm
poweroff"
expect_count 2 "exit code: 55"
expect_count 1 "hola cvm"
expect "powering off"

scenario "repeated cvm runs do not exhaust the kernel heap" "run cvm/fib.cvm
run cvm/w1.cvm
run cvm/fib.cvm
run cvm/w1.cvm
run cvm/fib.cvm
run cvm/fib.cvm
poweroff"
expect_count 4 "exit code: 55"
expect_count 2 "hola cvm"
expect "powering off"

scenario "date prints the CMOS wall clock" "date
poweroff"
expect "[0-9][0-9]:[0-9][0-9]:[0-9][0-9]"

scenario "vol reports the default volume" "vol
poweroff"
expect "volume: 100%"

scenario "vol sets and reports the volume" "vol 40
vol
poweroff"
expect_count 2 "volume: 40%"

scenario "vol clamps above the maximum" "vol 250
vol
poweroff"
expect_count 2 "volume: 100%"

scenario "vol clamps below zero" "vol -5
vol
poweroff"
expect_count 2 "volume: 0%"

scenario "vol rejects non-numeric input" "vol abc
poweroff"
expect "usage: vol"

scenario "net reports the slirp configuration" "net
poweroff"
expect "rtl8139"
expect "10.0.2.15"

scenario "net pings the slirp gateway" "net ping 10.0.2.2
poweroff"
expect "^reply from 10.0.2.2"

http_server_start() {
    python3 -m http.server "${NET_HTTP_PORT:-8899}" --directory "$HERE/progs" \
        > /dev/null 2>&1 &
    BDD_HTTP_PID=$!
    sleep 1
}

http_server_stop() {
    [ -n "${BDD_HTTP_PID:-}" ] && kill "$BDD_HTTP_PID" 2>/dev/null || true
    BDD_HTTP_PID=""
}

http_fixture_start() {
    python3 "$HERE/test_http_server.py" "${NET_HTTP2_PORT:-8900}" \
        > /dev/null 2>&1 &
    BDD_HTTP2_PID=$!
    sleep 1
}

http_fixture_stop() {
    [ -n "${BDD_HTTP2_PID:-}" ] && kill "$BDD_HTTP2_PID" 2>/dev/null || true
    BDD_HTTP2_PID=""
}

trap 'http_server_stop; http_fixture_stop' EXIT

http_server_start
scenario "tcp stack fetches a page from the host" "run bin/http.elf 10.0.2.2 8899 /src/fib.c
poweroff"
expect "received"
expect "exit code: 0"

scenario "freedom fetches a page from the host" "run bin/freedom http://10.0.2.2:8899/README.txt
poweroff"
expect "minimal 64-bit kernel"
expect "freedom: 10.0.2.2 ("

scenario "freedom follows the directory redirect of the host server" "run bin/freedom http://10.0.2.2:8899/bin
poweroff"
expect "cp"
expect "freedom: 10.0.2.2 ("

scenario "freedom filters hostile html" "run bin/freedom http://10.0.2.2:8899/docs/hostile.html
poweroff"
expect "first block"
expect "bold & safe"
expect "<tag>"
expect "bad bytes: ?"
refute "evil"
refute "this comment must vanish"
expect "freedom: 10.0.2.2 ("

http_fixture_start
scenario "freedom decodes a chunked response" "run bin/freedom http://10.0.2.2:8900/chunked
poweroff"
expect "chunked body works"
expect "freedom: 10.0.2.2 ("

scenario "freedom follows a 302 and lands on the final page" "run bin/freedom http://10.0.2.2:8900/redirect302
poweroff"
expect "FINAL PAGE MARKER"
expect "freedom: 10.0.2.2 ("

scenario "freedom stops at Content-Length instead of waiting for EOF" "run bin/freedom http://10.0.2.2:8900/final
poweroff"
expect "FINAL PAGE MARKER"
expect "freedom: 10.0.2.2 ("

scenario "tcp ack advances so a server waiting on the ack continues" "run bin/freedom http://10.0.2.2:8900/acktest
poweroff"
expect "freedom: 10.0.2.2 (6000 bytes)"

scenario "freedom fails closed on https against a plain-http port" "run bin/freedom https://10.0.2.2:8899/README.txt
poweroff"
expect "freedom: https handshake with 10.0.2.2 failed"

scenario "freedom follows an https redirect and fails closed on plain http" "run bin/freedom http://10.0.2.2:8900/redirecthttps
poweroff"
expect "freedom: https handshake with 10.0.2.2 failed"

scenario "freedom upgrades a bare host to https" "run bin/freedom 10.0.2.2
poweroff"
expect "freedom: connect to 10.0.2.2 failed"

scenario "freedom dump-css collects styles, inline styles and linked sheets" "run bin/freedom --dump-css http://10.0.2.2:8900/styled
poweroff"
expect "=== freedom css ==="
expect "== style =="
expect "p { color: red; }"
expect "p#x.y { font-size: 12px; }"
expect "== /style.css =="
expect "body { margin: 0; }"

scenario "freedom dump-dom prints the element outline" "run bin/freedom --dump-dom http://10.0.2.2:8900/styled
poweroff"
expect "=== freedom dom ==="
expect "html"
expect "body"
expect "p#x.y"
refute "hello"
refute "color: red"

scenario "freedom refuses unknown flags" "run bin/freedom --nosuchflag http://10.0.2.2:8900/styled
poweroff"
expect "freedom: unknown flag --nosuchflag"
expect "usage: freedom"

http_server_stop
http_fixture_stop

scenario "mkdir creates a directory and cd enters it" "mkdir work
cp src/fib.c work/copy.c
cd work
pwd
edit f.txt
a
hello cwd
x
ls
cat copy.c
poweroff"
expect "hello cwd"
expect "f.txt"
expect "int fib"

scenario "cd .. pops one level and bare cd returns to root" "mkdir work
mkdir work/sub
cd work
cd sub
pwd
cd ..
pwd
cd
pwd
poweroff"
expect "work/sub/"
expect "^/$"

scenario "mkdir refuses existing directories and missing parents" "mkdir work
mkdir work
mkdir nope/child
poweroff"
expect "mkdir: work/: already exists"
expect "no such directory"

scenario "cd into a nonexistent directory is a diagnostic" "cd ghost
poweroff"
expect "cd: ghost: no such directory"

scenario "rm deletes files, refuses directories and reports missing" "mkdir work
edit doomed.txt
a
bye
x
rm doomed.txt
cat doomed.txt
rm doomed.txt
rm work
poweroff"
expect "removed doomed.txt"
expect "cat: doomed.txt: no such file"
expect "rm: doomed.txt: no such file"
expect "rm: work: is a directory"

scenario "ps lists registered programs" "load objects/hello.o
ps
poweroff"
expect "^  hello"

scenario "cat concatenates files in order through a redirect" "edit a.txt
a
first part
x
edit b.txt
a
second part
x
cat a.txt b.txt > c.txt
cat c.txt
poweroff"
expect "first part"
expect_count 2 "second part"

scenario "cat refuses directories" "mkdir work
cat work
poweroff"
expect "cat: work: no such file or is a directory"

scenario "edit refuses directories" "mkdir work
edit work/
x
poweroff"
expect "edit: work/: is a directory"

scenario "redirect into a directory fails cleanly" "mkdir work
echo x > work/
poweroff"
expect "redirect: cannot write work/"

scenario "redirect and .. resolve against the cwd" "mkdir work
cd work
echo hello > r.txt
cd
cat work/r.txt
echo hi > work/../x.txt
cat x.txt
poweroff"
expect "hello"
expect "hi"

scenario "ls lists a named directory relative to the cwd" "mkdir work
cd work
edit f.txt
a
inner
x
cd
ls work
poweroff"
expect "f.txt"

scenario "bin path is root anchored and cp args resolve against the cwd" "mkdir work
cd work
cp /src/fib.c copy1.txt
cat copy1.txt
poweroff"
expect "exit code: 0"
expect "int fib"

scenario "syscall tracing reports the program dialogue" "trace
trace on
cp src/fib.c copy_t.txt
trace off
trace
poweroff"
expect "syscall tracing: off"
expect "syscall tracing: on"
expect "syscall 2"
expect "syscall 3"

# PageUp (ESC [ 5 ~) re-renders a window over the scrollback ring to the serial
# console. The boot banner was scrolled off while the cat output streamed past,
# so after a page up it must reappear: once from the real boot, once from the
# rendered history. The page-up keys must be concatenated on one line so a
# single trailing newline exits the view (a newline between page-ups would each
# exit the view and re-enter, rendering the top each time). Page-ups beyond the
# top of the ring are a no-op, so exactly one render ever reaches the boot
# banner regardless of ring depth, and the count is exactly two. `echo done`
# proves the shell resumed, and poweroff leaves QEMU clean for the next boot.
PGUP=$'\x1b[5~'
scenario "page up scrolls back to the boot banner" "cat docs/hostile.html docs/hostile.html
${PGUP}${PGUP}${PGUP}
echo done
poweroff"
expect_count 2 "MiniOS Kernel v0.3"
expect "done"

# MicroPython: a host-built static glibc ELF on MiniFS running at ring 3
# through the Linux syscall ABI, exactly like DOOM. Bare name resolves
# through the MiniFS fallback.
scenario "micropython evaluates -c with integers and floats" "micropython -c \"print(6 * 7)\"
micropython -c \"print(1.5 * 2)\"
poweroff"
expect "42"
expect "3.0"
expect "exit code: 0"

scenario "micropython runs a script from the ramdisk" "micropython src/hello.py
poweroff"
expect "hello from python"
expect "exit code: 0"

scenario "micropython reports a syntax error and returns a failure code" "micropython -c \"def broken(:\"
poweroff"
expect "SyntaxError"
expect "exit code: 1"

scenario "micropython REPL reads lines from the console" "micropython
print(40 + 2)
exit()
poweroff"
expect "42"

echo ""
echo "=== summary: $PASS passed, $FAIL failed ==="
[ "$KEEP_LOG" = "1" ] || rm -f "$LOG"
if [ "$FAIL" -gt 0 ]; then
    echo "failed:$FAILED_NAMES"
    exit 1
fi
exit 0
