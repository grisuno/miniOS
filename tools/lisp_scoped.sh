#!/bin/sh
# Docstring: Scoped Lisp validation for the MiniOS interpreter contract.
# Builds the ring-3 static ELF with zero warnings, runs the host suite,
# and asserts each scoped mutant dies. Fails closed on first gap.
set -eu
cd "$(dirname "$0")/.."
fail=0
say() { printf '%s\n' "$1"; }
die() { say "FAIL: $1"; fail=1; }
say "== lisp scoped =="
make test-lisp >build/lisp_scoped_test.log 2>&1 || die "test-lisp failed"
grep -q "TOTAL pass=" build/lisp_scoped_test.log || die "lisp vectors missing"
if grep -q " fail=[1-9]" build/lisp_scoped_test.log; then die "host suite has failures"; fi
rm -f progs/bin/lisp.elf progs/bin/lisp
make progs/bin/lisp.elf progs/bin/lisp >build/lisp_scoped_build.log 2>&1 || die "static ELF build failed"
if grep -E "warning|error" build/lisp_scoped_build.log; then die "warnings in lisp build"; fi
test -x progs/bin/lisp || die "lisp binary missing"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT INT TERM
mutant() {
    name="$1"; expr="$2"
    cp progs/lisp/lisp.c "$tmp/lisp_mut.c"
    if ! sed -i "$expr" "$tmp/lisp_mut.c" 2>/dev/null; then die "mutant $name: sed failed"; return; fi
    if cmp -s progs/lisp/lisp.c "$tmp/lisp_mut.c"; then die "mutant $name: matched nothing"; return; fi
    if ! gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -I progs -o "$tmp/lisp_mut" "$tmp/lisp_mut.c" 2>/dev/null; then
        say "KILLED $name (build failure)"; return
    fi
    if python3 tools/test_lisp.py --binary "$tmp/lisp_mut" >"$tmp/$name.log" 2>&1; then
        die "mutant $name SURVIVED"
    else
        say "KILLED $name"
    fi
}
mutant "lisp-add-overflow-unchecked" 's/if (__builtin_add_overflow(a, b, &out)) {/if (0) {/'
mutant "lisp-div-zero-unchecked" 's/    if (b == 0) {/    if (0) {/'
mutant "lisp-num-format-prefix" 's/fprintf(rt->out, "%" PRId64, node->as.num);/fprintf(rt->out, "%%" PRId64, node->as.num);/'
mutant "lisp-true-unbound" 's/    env_bind(rt, env, rt->true_value, rt->true_value);/    (void)rt;/'
mutant "lisp-unbound-silent" 's/result = value ? value : make_error(rt, "unbound symbol");/result = value ? value : rt->nil;/'
mutant "lisp-error-message-nil" 's/return make_str(rt, value->as.error ? value->as.error : "unknown");/return rt->nil;/'
mutant "lisp-exit-code-zero" 's/        exit(status);/        exit(0);/'
if [ "$fail" -eq 0 ]; then say "lisp scoped: ok"; else say "lisp scoped: FAIL"; fi
exit "$fail"
