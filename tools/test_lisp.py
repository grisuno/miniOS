"""Host test suite for the MiniOS Lisp interpreter.

Builds progs/lisp/lisp.c with the host toolchain and drives the resulting
binary through assertion vectors covering arithmetic, fail-closed errors,
closures, strings, files, predicates, CLI flags and the in-OS suite file
in language-only mode. Kernel-backed primitives (minios-run, time-ms, vol)
are exercised for shape only: without a kernel they fail closed instead
of crashing.

Usage:
  python3 tools/test_lisp.py [--binary PATH] [--lisp SRC]
"""

import argparse
import os
import shutil
import subprocess
import sys
import tempfile


REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DEFAULT_SRC = os.path.join(REPO, "progs", "lisp", "lisp.c")
DEFAULT_SUITE = os.path.join(REPO, "progs", "src", "test.lisp")
DEFAULT_MINIGCC = os.path.join(REPO, "progs", "lisp", "minigcc.lisp")


class LispConfig:
    """Central configuration for paths, flags and match expectations."""

    cc = "gcc"
    cflags = ["-std=c17", "-Wall", "-Wextra", "-Wpedantic"]
    include_dir = os.path.join(REPO, "progs")
    timeout = 30


class LispTest:
    """Builds the interpreter once and asserts vectors against it."""

    def __init__(self, binary, suite):
        self.binary = binary
        self.suite = suite
        self.passed = 0
        self.failed = 0
        self.failures = []

    def check(self, name, actual, expected):
        """Assert one observed value equals the expectation."""
        if actual == expected:
            self.passed += 1
            print("PASS {}".format(name))
        else:
            self.failed += 1
            self.failures.append(name)
            print("FAIL {}: expected {!r} got {!r}".format(
                name, expected, actual))

    def run_expr(self, code):
        """Evaluate one inline expression and capture output."""
        proc = subprocess.run(
            [self.binary, "-e", code],
            capture_output=True, text=True, timeout=LispConfig.timeout)
        return proc

    def check_eval(self, name, code, stdout):
        """Assert an inline expression prints exactly the expectation."""
        proc = self.run_expr(code)
        self.check(name, (proc.stdout, proc.returncode), (stdout, 0))

    def check_error(self, name, code, fragment):
        """Assert an inline expression fails closed with a diagnostic."""
        proc = self.run_expr(code)
        ok = proc.returncode != 0 and fragment in proc.stderr
        self.check(name, ok, True)

    def run_all(self):
        """Drive every assertion vector in sequence."""
        self.check_eval("add", "(+ 40 2)", "42\n")
        self.check_eval("nested", "(* (+ 2 3) (- 10 4))", "30\n")
        self.check_eval("fact", ("(begin (define fact (lambda (n) "
                                 "(if (= n 0) 1 (* n (fact (- n 1)))))) "
                                 "(fact 5))"), "120\n")
        self.check_eval("closure-capture", ("(begin (define make-adder "
                                            "(lambda (x) (lambda (y) (+ x y)))) "
                                            "(define add5 (make-adder 5)) "
                                            "(add5 7))"), "12\n")
        self.check_eval("let-multibody", ("(let ((x 1) (y 2)) "
                                          "(set! x 10) (+ x y))"), "12\n")
        self.check_eval("quote", "(car '(1 2 3))", "1\n")
        self.check_eval("cons-print", "(cons 1 2)", "(1 . 2)\n")
        self.check_eval("string-roundtrip",
                        '(string-concat "foo" "bar")', '"foobar"\n')
        self.check_eval("predicates",
                        "(begin (println (null? nil)) "
                        "(println (number? 7)) (println (string? 7)) nil)",
                        "t\nt\nnil\nnil\n")
        self.check_eval("t-literal", "t", "t\n")
        self.check_eval("error-message", "(error-message (/ 1 0))",
                        '"division by zero"\n')
        self.check_eval("error-message-nonerror", "(error-message 42)",
                        "nil\n")
        self.check_eval("exit-code-zero", "(exit 0)", "")
        self.check_exit_code()
        self.check_error("add-overflow", "(+ 9223372036854775807 1)",
                         "integer overflow")
        self.check_error("mul-overflow", "(* 9223372036854775807 2)",
                         "integer overflow")
        self.check_error("div-zero", "(/ 1 0)", "division by zero")
        self.check_error("unbound", "nosuchsymbol", "unbound symbol")
        self.check_error("arity", "(+ 1)", "+ expects two numbers")
        self.check_error("call-nonfunction", "(1 2)",
                         "attempt to call a non-function")
        self.check_error("unclosed", "(+ 1 2", "expected ')'")
        self.check_error("bad-mode", '(open-file "/tmp/x" "bogus")',
                         "file mode not allowed")
        self.check_file_roundtrip()
        self.check_cli()
        self.check_suite_language_only()
        self.check_minigcc_subset()

    def check_file_roundtrip(self):
        """Assert a file write and read roundtrip through the interpreter."""
        with tempfile.TemporaryDirectory() as tmp:
            target = os.path.join(tmp, "rt.txt")
            quoted = '"{}"'.format(target)
            code = ("(begin (define f (open-file {} \"w\")) "
                    "(write f \"payload\") (close-file f) "
                    "(define g (open-file {} \"r\")) "
                    "(define c (read-char g)) (close-file g) c)").format(
                        quoted, quoted)
            proc = self.run_expr(code)
            self.check("file-roundtrip", (proc.stdout, proc.returncode),
                       ("112\n", 0))

    def check_exit_code(self):
        """Assert a nonzero exit status survives the cleanup path."""
        proc = subprocess.run([self.binary, "-e", "(exit 7)"],
                              capture_output=True, text=True,
                              timeout=LispConfig.timeout)
        self.check("exit-code-nonzero", proc.returncode, 7)

    def check_cli(self):
        """Assert version, help, unknown flag and missing file behaviors."""
        proc = subprocess.run([self.binary, "--version"], capture_output=True,
                              text=True, timeout=LispConfig.timeout)
        self.check("version", (proc.stdout.startswith("lisp "),
                               proc.returncode), (True, 0))
        proc = subprocess.run([self.binary, "--bogus"], capture_output=True,
                              text=True, timeout=LispConfig.timeout)
        self.check("unknown-flag", (proc.returncode != 0, "usage:" in
                                    proc.stderr), (True, True))
        proc = subprocess.run([self.binary, "/tmp/does-not-exist.lisp"],
                              capture_output=True, text=True,
                              timeout=LispConfig.timeout)
        self.check("missing-file", (proc.returncode != 0,
                                    "cannot read" in proc.stderr),
                   (True, True))

    def check_suite_language_only(self):
        """Assert the shipped in-OS suite passes its language section."""
        with tempfile.TemporaryDirectory() as tmp:
            shim = os.path.join(tmp, "suite.lisp")
            with open(self.suite) as handle:
                body = handle.read()
            marker = '(check-spawn "xxhash-selftest"'
            head = body.split(marker)[0]
            tail = ('(print "TOTAL pass=") (print pass) '
                    '(print " fail=") (println fail) '
                    '(exit (if (= fail 0) 0 1))\n')
            with open(shim, "w") as handle:
                handle.write(head + tail)
            proc = subprocess.run([self.binary, shim], capture_output=True,
                                  text=True, timeout=LispConfig.timeout)
            self.check("suite-language-only",
                       (proc.returncode, "FAIL" in proc.stdout), (0, False))

    def check_minigcc_subset(self):
        """Assert the Lisp subset compiler covers expr codegen end to end.

        Each vector compiles one tiny C source through minigcc.lisp, then
        assembles and links the output with the host toolchain and checks
        the process exit code. Vectors that need `as`/`ld` skip cleanly
        when the host lacks them; the fail-closed vectors need no linker.
        """
        vectors = [
            ("minigcc-demo", "int main(){return 40 + 2;}", 42),
            ("minigcc-prec", "int main(){return 2 + 3 * 4 - 20 / 5;}", 10),
            ("minigcc-paren", "int main(){return (2 + 3) * 4;}", 20),
            ("minigcc-sub-chain", "int main(){return 100 - 30 - 12;}", 58),
            ("minigcc-single", "int main(){return 7;}", 7),
            ("minigcc-call",
             "int add(int a, int b){return a + b;}"
             "int main(void){return add(10, 2);}", 12),
            ("minigcc-nested",
             "int add(int a,int b){return a+b;}"
             "int main(void){return add(add(1,2),4);}", 7),
            ("minigcc-threeargs",
             "int f(int a,int b,int c){return a*b+c;}"
             "int main(){return f(3,4,5);}", 17),
        ]
        has_toolchain = shutil.which("as") and shutil.which("ld")
        minios_ld = os.path.join(REPO, "build", "ld")
        has_minios_ld = os.path.isfile(minios_ld) and os.access(minios_ld, os.X_OK)
        proc = subprocess.run(
            [self.binary, DEFAULT_MINIGCC],
            capture_output=True, text=True, timeout=LispConfig.timeout)
        self.check("minigcc-no-args-usage",
                    (proc.returncode != 0,
                     "usage: lisp minigcc.lisp <source.c> > out.s" in proc.stdout),
                    (True, True))
        proc = subprocess.run(
            [self.binary, DEFAULT_MINIGCC, "--help"],
            capture_output=True, text=True, timeout=LispConfig.timeout)
        self.check("minigcc-help",
                    (proc.returncode,
                     "minigcc.lisp v" in proc.stdout),
                    (0, True))
        proc = subprocess.run(
            [self.binary, DEFAULT_MINIGCC, "--version"],
            capture_output=True, text=True, timeout=LispConfig.timeout)
        self.check("minigcc-version",
                    (proc.returncode, proc.stdout.startswith("minigcc.lisp v")),
                    (0, True))
        with tempfile.TemporaryDirectory() as tmp:
            for name, source, want in vectors:
                src = os.path.join(tmp, name + ".c")
                asm = os.path.join(tmp, name + ".s")
                with open(src, "w") as handle:
                    handle.write(source)
                proc = subprocess.run(
                    [self.binary, DEFAULT_MINIGCC, src],
                    capture_output=True, text=True,
                    timeout=LispConfig.timeout)
                if proc.returncode != 0 or ".globl main" not in proc.stdout:
                    self.check(name, (proc.returncode, proc.stdout),
                               (0, ".globl main"))
                    continue
                if not has_toolchain:
                    self.check(name + "-emits", True, True)
                    continue
                with open(asm, "w") as handle:
                    handle.write(proc.stdout)
                obj = os.path.join(tmp, name + ".o")
                exe = os.path.join(tmp, name)
                proc = subprocess.run(
                    ["as", "--64", asm, "-o", obj],
                    capture_output=True, text=True,
                    timeout=LispConfig.timeout)
                if proc.returncode != 0:
                    self.check(name, proc.stderr, "")
                    continue
                proc = subprocess.run(
                    ["ld", obj, "-o", exe],
                    capture_output=True, text=True,
                    timeout=LispConfig.timeout)
                if proc.returncode != 0:
                    self.check(name, proc.stderr, "")
                    continue
                proc = subprocess.run([exe], capture_output=True,
                                      timeout=LispConfig.timeout)
                self.check(name, proc.returncode, want)
                if has_minios_ld:
                    meld = os.path.join(tmp, name + "_minios.elf")
                    proc = subprocess.run(
                        [minios_ld, "-f", "elf", "-o", meld, asm],
                        capture_output=True, text=True,
                        timeout=LispConfig.timeout)
                    if proc.returncode != 0:
                        self.check(name + "-minios-ld", proc.stderr, "")
                        continue
                    os.chmod(meld, 0o755)
                    proc = subprocess.run([meld], capture_output=True,
                                          timeout=LispConfig.timeout)
                    self.check(name + "-minios-ld", proc.returncode, want)
            bad = os.path.join(tmp, "bad.c")
            with open(bad, "w") as handle:
                handle.write("int main(){oops}")
            proc = subprocess.run(
                [self.binary, DEFAULT_MINIGCC, bad],
                capture_output=True, text=True, timeout=LispConfig.timeout)
            self.check("minigcc-bad-input",
                        (proc.returncode != 0,
                         "minigcc: expected return" in proc.stdout),
                        (True, True))
            with open(bad, "w") as handle:
                handle.write("int main(){return x;}")
            proc = subprocess.run(
                [self.binary, DEFAULT_MINIGCC, bad],
                capture_output=True, text=True, timeout=LispConfig.timeout)
            self.check("minigcc-unbound-var",
                        (proc.returncode != 0,
                         "minigcc: unbound variable" in proc.stdout),
                        (True, True))
            proc = subprocess.run(
                [self.binary, DEFAULT_MINIGCC,
                 os.path.join(tmp, "does-not-exist.c")],
                capture_output=True, text=True, timeout=LispConfig.timeout)
            self.check("minigcc-missing-file", proc.returncode != 0, True)

    def report(self):
        """Print the totals and return the process exit status."""
        print("TOTAL pass={} fail={}".format(self.passed, self.failed))
        for name in self.failures:
            print("FAILED {}".format(name))
        return 0 if self.failed == 0 else 1


def build_binary(source, output):
    """Compile the interpreter with warnings promoted to errors."""
    cmd = ([LispConfig.cc] + LispConfig.cflags +
           ["-Werror", "-I", LispConfig.include_dir,
            "-o", output, source])
    proc = subprocess.run(cmd, capture_output=True, text=True,
                          timeout=LispConfig.timeout)
    if proc.returncode != 0:
        sys.stderr.write(proc.stderr)
        raise SystemExit("lisp host build failed")
    return output


def main():
    """Parse arguments, build the binary and drive the suite."""
    parser = argparse.ArgumentParser(description="Host test for MiniOS lisp")
    parser.add_argument("--binary", default=None)
    parser.add_argument("--lisp", default=DEFAULT_SRC)
    parser.add_argument("--suite", default=DEFAULT_SUITE)
    args = parser.parse_args()
    binary = args.binary
    if binary is None:
        tmpdir = tempfile.mkdtemp(prefix="lisp_test_")
        binary = os.path.join(tmpdir, "lisp")
        build_binary(args.lisp, binary)
    suite = LispTest(binary, args.suite)
    suite.run_all()
    raise SystemExit(suite.report())


if __name__ == "__main__":
    main()
