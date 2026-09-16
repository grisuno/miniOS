#!/usr/bin/env python3
"""test_call_align.py - verify stack alignment at call sites, both parities.

Compiles a probe with miniGCC whose callees read %rsp in their body and
report rsp & 15. A System V callee entered with a correct call sequence
sees (entry_rsp - 8 - frame) where frame is a multiple of 16, so the
reported value is always 8 regardless of arity. An inverted spill pad or
a missing align dance shows up as 0. No gcc reference is needed: the
assertion is the ABI constant itself, which makes this probe immune to
the host compiler's frame choices.

Covers 6-arg (no spill, even), 7-arg (spill, odd) and 8-arg (spill,
even) callees through direct and indirect calls.

Usage: test_call_align.py [--minigcc DIR] [--keep]
Exit 0 when every probe reports 0.
"""
import os
import subprocess
import sys
import tempfile


class AlignConfig:
    """Centralized tunables for the alignment probe."""
    MINIGCC_DIR = os.environ.get("MINIGCC_DIR", "")
    PROBE = r"""
long mod6(long a, long b, long c, long d, long e, long f) {
    long r;
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    __asm__ volatile("movq %%rsp, %0" : "=r"(r));
    return r & 15;
}
long mod7(long a, long b, long c, long d, long e, long f, long g) {
    long r;
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g;
    __asm__ volatile("movq %%rsp, %0" : "=r"(r));
    return r & 15;
}
long mod8(long a, long b, long c, long d, long e, long f, long g, long h) {
    long r;
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
    __asm__ volatile("movq %%rsp, %0" : "=r"(r));
    return r & 15;
}
#include <stdio.h>
int main(void) {
    long (*fp)(long, long, long, long, long, long, long);
    printf("%ld %ld %ld\n", mod6(1, 2, 3, 4, 5, 6), mod7(1, 2, 3, 4, 5, 6, 7),
        mod8(1, 2, 3, 4, 5, 6, 7, 8));
    fp = mod7;
    printf("%ld\n", fp(1, 2, 3, 4, 5, 6, 7));
    return 0;
}
"""
    EXPECTED = "8 8 8\n8\n"


def find_minigcc(explicit):
    """Locate the miniGCC checkout without host assumptions."""
    if explicit and os.path.isfile(os.path.join(explicit, "minigcc.c")):
        return explicit
    if AlignConfig.MINIGCC_DIR and os.path.isfile(
            os.path.join(AlignConfig.MINIGCC_DIR, "minigcc.c")):
        return AlignConfig.MINIGCC_DIR
    here = os.path.dirname(os.path.abspath(__file__))
    for cand in (os.path.join(here, "..", "miniGCC"),
                 os.path.join(here, "..", "..", "miniGCC")):
        if os.path.isfile(os.path.join(cand, "minigcc.c")):
            return os.path.normpath(cand)
    return ""


def run(argv, **kwargs):
    """Run a subprocess, returning CompletedProcess."""
    return subprocess.run(argv, capture_output=True, text=True, **kwargs)


def main(argv):
    """Build the probe with miniGCC and assert every report is eight."""
    mgcc_dir = ""
    keep = False
    args = list(argv[1:])
    while args:
        a = args.pop(0)
        if a == "--minigcc" and args:
            mgcc_dir = args.pop(0)
        elif a == "--keep":
            keep = True
    mgcc_dir = find_minigcc(mgcc_dir)
    if not mgcc_dir:
        print("test_call_align: miniGCC checkout not found (use --minigcc)")
        return 2
    work = tempfile.mkdtemp(prefix="alignprobe_")
    try:
        src = os.path.join(work, "probe.c")
        with open(src, "w") as f:
            f.write(AlignConfig.PROBE)
        mgcc = os.path.join(work, "minigcc")
        r = run(["gcc", "-std=c99", "-O2", "-o", mgcc,
                 os.path.join(mgcc_dir, "minigcc.c")])
        if r.returncode != 0:
            print("test_call_align: cannot build minigcc")
            print(r.stderr[-2000:])
            return 1
        asm_p = os.path.join(work, "probe.s")
        r = run([mgcc, src], **{})
        with open(asm_p, "w") as f:
            f.write(r.stdout)
        if r.returncode != 0 or r.stderr.strip():
            print("test_call_align: probe compile failed")
            print(r.stderr[-2000:])
            return 1
        obj_p = os.path.join(work, "probe.o")
        bin_p = os.path.join(work, "probe")
        r = run(["as", asm_p, "-o", obj_p])
        if r.returncode != 0:
            print("test_call_align: as failed")
            print(r.stderr[-2000:])
            return 1
        r = run(["gcc", "-no-pie", obj_p, "-o", bin_p])
        if r.returncode != 0:
            print("test_call_align: link failed")
            print(r.stderr[-2000:])
            return 1
        r = run([bin_p])
        if r.returncode != 0:
            print("test_call_align: probe crashed (rc=%d)" % r.returncode)
            return 1
        if r.stdout != AlignConfig.EXPECTED:
            print("test_call_align: MISALIGNED")
            print("got: %r want: %r" % (r.stdout, AlignConfig.EXPECTED))
            return 1
        print("test_call_align: PASS (6/7/8 direct + 7 indirect all rsp&15==8)")
        return 0
    finally:
        if not keep:
            import shutil
            shutil.rmtree(work, ignore_errors=True)
    return 0 if not failures else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
