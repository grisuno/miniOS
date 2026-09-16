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
mutant "lisp-add-overflow-unchecked" 's/if (__builtin_add_overflow(v\[0\]->as.num, v\[1\]->as.num, &out)) {/if (0) {/'
mutant "lisp-div-zero-unchecked" 's/    if (b == 0) {/    if (0) {/'
mutant "lisp-num-format-prefix" 's/fprintf(rt->out, "%" PRId64, node->as.num);/fprintf(rt->out, "%%" PRId64, node->as.num);/'
mutant "lisp-true-unbound" 's/    env_bind(rt, env, rt->true_value, rt->true_value);/    (void)rt;/'
mutant "lisp-unbound-silent" 's/result = value ? value : make_error(rt, "unbound symbol");/result = value ? value : rt->nil;/'
mutant "lisp-error-message-nil" 's/return make_str(rt, v\[0\]->as.error ? v\[0\]->as.error : "unknown");/return rt->nil;/'
mutant "lisp-exit-code-zero" 's/        exit(status);/        exit(0);/'
lisp_mut() {
    name="$1"; expr="$2"; src="$3"; want="$4"
    cp progs/lisp/minigcc.lisp "$tmp/minigcc_mut.lisp"
    if ! sed -i "$expr" "$tmp/minigcc_mut.lisp" 2>/dev/null; then die "mutant $name: sed failed"; return; fi
    if cmp -s progs/lisp/minigcc.lisp "$tmp/minigcc_mut.lisp"; then die "mutant $name: matched nothing"; return; fi
    printf '%s' "$src" > "$tmp/mut.c"
    if ! "$tmp/lisp_mut_main" "$tmp/minigcc_mut.lisp" "$tmp/mut.c" > "$tmp/mut.s" 2>/dev/null; then
        say "KILLED $name (compile failure)"; return
    fi
    if ! as --64 "$tmp/mut.s" -o "$tmp/mut.o" 2>/dev/null; then
        say "KILLED $name (asm failure)"; return
    fi
    ld "$tmp/mut.o" -o "$tmp/mut" 2>/dev/null || { die "mutant $name: no host ld"; return; }
    code=0; "$tmp/mut" 2>/dev/null || code=$?
    if [ "$code" = "$want" ]; then die "mutant $name SURVIVED"; else say "KILLED $name"; fi
}
gcc -std=c17 -Wall -Wextra -Wpedantic -Werror -I progs -o "$tmp/lisp_mut_main" progs/lisp/lisp.c 2>/dev/null || die "mutant host lisp build failed"
lisp_mut "minigcc-sub-operand-swap" 's/subq %rax, %rcx/addq %rcx, %rax/' 'int main(){return 100 - 30 - 12;}' 58
lisp_mut "minigcc-mul-as-add" 's/imulq %rcx, %rax/addq %rcx, %rax/' 'int main(){return 2 + 3 * 4 - 20 / 5;}' 10
lisp_mut "minigcc-call-pad-dropped" 's/(println "    popq %r10")/(println "    nop")/' 'int f(int a,int b,int c){return a*b+c;}int main(){return f(3,4,5);}' 17
lisp_mut "minigcc-var-sign" 's/(- 0 (+ 16 (\* idx 8)))/(+ 16 (* idx 8))/' 'int add(int a, int b){return a + b;}int main(void){return add(10, 2);}' 12
lisp_mut "minigcc-entry-dropped" 's/(println "_start:")/(println ".Lnoentry:")/' 'int main(){return 7;}' 7
mut_usage() {
    cp progs/lisp/minigcc.lisp "$tmp/minigcc_usage_mut.lisp"
    if ! sed -i 's/usage: lisp minigcc.lisp <source.c> > out.s/usage: hidden/' "$tmp/minigcc_usage_mut.lisp" 2>/dev/null; then die "mutant minigcc-usage-dropped: sed failed"; return; fi
    if cmp -s progs/lisp/minigcc.lisp "$tmp/minigcc_usage_mut.lisp"; then die "mutant minigcc-usage-dropped: matched nothing"; return; fi
    code=0; out=$("$tmp/lisp_mut_main" "$tmp/minigcc_usage_mut.lisp" 2>/dev/null) || code=$?
    case "$out" in
        *"usage: lisp minigcc.lisp"*) die "mutant minigcc-usage-dropped SURVIVED" ;;
        *) say "KILLED minigcc-usage-dropped" ;;
    esac
    if [ "$code" = "0" ]; then die "mutant minigcc-usage-dropped SURVIVED (exit 0)"; else say "KILLED minigcc-usage-exit"; fi
}
mut_usage
if [ "$fail" -eq 0 ]; then say "lisp scoped: ok"; else say "lisp scoped: FAIL"; fi
exit "$fail"
