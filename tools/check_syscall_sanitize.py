"""Scoped audit gate for syscall user-pointer sanitization.

Every ring-3 pointer that reaches a syscall handler as a1..a6 must pass a
SANITIZE_* macro or user_range_ok/user_str_ok check before its first
dereference. The discipline allows one delegation shape: an unchecked
pointer may flow only into a callee that sanitizes internally
(Config.delegated_callees); anything else is a fail-closed violation.

The analysis is textual and conservative: it over-reports, and Config
records each triaged outcome, so a new unsanitized dereference fails the
build instead of shipping silently.
"""

import re
import sys


class Config:
    """Centralized tunable values for the sanitize audit."""

    target_files = ("kernel/syscalls.c", "kernel/syscalls_proc.c")
    func_pattern = re.compile(
        r"^(?:static\s+)?long\s+(sys_\w+|do_\w+|ksyscall_\w+|k_syscall_\w+)\s*\("
    )
    cast_pattern = re.compile(
        r"\(\s*(?:const\s+|unsigned\s+|char\s+|int\s+|long\s+|void\s+|\*\s*)+"
        r"\*\s*\)\s*\(?\s*(a[1-6])\b"
    )
    alias_pattern = re.compile(r"(\w+)\s*=\s*\([^)]*\*[^)]*\)\s*\(?\s*(a[1-6])\b")
    scalar_pattern = re.compile(
        r"(\w+)\s*=\s*\(\s*(?:unsigned\s+long|long|unsigned|int)\s*\)"
        r"\s*\(?\s*(a[1-6])\b"
    )
    check_patterns = (
        re.compile(r"SANITIZE_\w+\(([^;]*)\)"),
        re.compile(r"user_range_ok\(([^;]*)\)"),
        re.compile(r"user_str_ok\(([^;]*)\)"),
    )
    deref_template = "(?:\\*\\s*{n}\\b|{n}\\s*\\[|{n}\\s*->)"
    delegated_callees = (
        "k_syscall_spawn",
        "do_open_path",
        "futex_wake",
        "do_waitpid",
        "do_waitpid_nb",
        "do_kill",
        "do_thread_spawn",
    )
    dereferencing_callees = (
        "futex_wait",
        "net_sys_dns",
        "net_sys_connect",
        "net_sys_sendto",
        "net_sys_recvfrom",
        "net_sys_poll",
        "do_clone",
    )
    callee_ptr_params = {
        "futex_wait": (0,),
        "net_sys_dns": (0,),
        "net_sys_connect": (1,),
        "net_sys_sendto": (1,),
        "net_sys_recvfrom": (1,),
        "net_sys_poll": (0,),
        "do_clone": (1,),
    }


def split_functions(lines):
    """Yield (name, start, body_lines) triples using brace depth."""
    funcs = []
    i = 0
    cfg = Config()
    case_pattern = re.compile(r"^\s*(case\s+\d+\s*:|default\s*:)")
    while i < len(lines):
        match = cfg.func_pattern.match(lines[i])
        if not match:
            i += 1
            continue
        name = match.group(1)
        depth = 0
        body = []
        started = False
        while i < len(lines):
            line = lines[i]
            depth += line.count("{") - line.count("}")
            if "{" in line:
                started = True
            if started:
                body.append((i + 1, line))
            i += 1
            if started and depth <= 0:
                break
        if name == "ksyscall_dispatch":
            block = []
            block_name = name + ":head"
            for lineno, line in body:
                if case_pattern.match(line):
                    if block:
                        funcs.append((block_name, block))
                    block_name = "%s:%s" % (name, line.strip())
                    block = [(lineno, line)]
                else:
                    block.append((lineno, line))
            if block:
                funcs.append((block_name, block))
        else:
            funcs.append((name, body))
    return funcs


def checked_names(body):
    """Return identifiers named inside sanitizer checks in a body."""
    names = set()
    for _, line in body:
        for pattern in Config.check_patterns:
            for args in pattern.findall(line):
                names.update(re.findall(r"[A-Za-z_]\w*", args))
    return names


def delegated_only(body, alias):
    """Decide whether an alias flows only into sanitizing callees."""
    uses = []
    for _, line in body:
        if re.search(r"\b" + re.escape(alias) + r"\b", line):
            uses.append(line)
    bare = [u for u in uses if not Config.cast_pattern.search(u)]
    if not bare:
        return True
    for line in bare:
        if re.search(r"\b" + re.escape(alias) + r"\s*(\[|->|\*)", line):
            return False
        if re.search(r"\*\s*" + re.escape(alias) + r"\b", line):
            return False
        callee = re.search(r"(\w+)\s*\([^;]*\b" + re.escape(alias) + r"\b", line)
        if callee and callee.group(1) not in Config.delegated_callees:
            if "SANITIZE" not in line and "user_" not in line:
                return False
    return True


def split_top_args(argtext):
    """Split a call argument list on top-level commas only."""
    parts = []
    depth = 0
    cur = ""
    for ch in argtext:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(cur)
            cur = ""
        else:
            cur += ch
    parts.append(cur)
    return parts


def audit_body(name, body):
    """Return violation strings for one function body."""
    violations = []
    checked = checked_names(body)
    pointers = {}
    scalars = {}
    for lineno, line in body:
        for alias, arg in Config.alias_pattern.findall(line):
            pointers.setdefault(alias, (arg, lineno))
        for alias, arg in Config.scalar_pattern.findall(line):
            if alias not in pointers:
                scalars.setdefault(alias, (arg, lineno))
    for alias, (arg, cast_line) in pointers.items():
        if alias in checked or arg in checked:
            continue
        if delegated_only(body, alias):
            continue
        violations.append(
            "%s:%d: %s (from %s) may dereference without a check"
            % (name, cast_line, alias, arg)
        )
    for alias, (arg, cast_line) in scalars.items():
        if alias in checked or arg in checked:
            continue
        for _, line in body:
            callee = re.search(r"(\w+)\s*\([^;]*\b" + re.escape(alias) + r"\b", line)
            if callee and callee.group(1) in Config.dereferencing_callees:
                violations.append(
                    "%s:%d: %s (from %s) reaches %s without a check"
                    % (name, cast_line, alias, arg, callee.group(1))
                )
                break
    reported = set(violations)
    for _, line in body:
        for callee, positions in Config.callee_ptr_params.items():
            call = re.search(r"\b" + re.escape(callee) + r"\s*\((.*)\)\s*;?\s*$", line)
            if not call:
                continue
            args = split_top_args(call.group(1))
            for pos in positions:
                if pos >= len(args):
                    continue
                ident = re.findall(r"[A-Za-z_]\w*", args[pos])
                ident = ident[-1] if ident else ""
                if ident and ident not in checked:
                    key = "%s:%s:%s" % (name, callee, ident)
                    if key not in reported:
                        reported.add(key)
                        violations.append(
                            "%s: %s (to %s) reaches without a check"
                            % (name, ident, callee)
                        )
    return violations


def audit_file(path):
    """Audit every handler in one file, return violation strings."""
    with open(path, "r") as handle:
        lines = handle.read().splitlines()
    out = []
    for name, body in split_functions(lines):
        for violation in audit_body(name, body):
            out.append(path + ":" + violation)
    return out


def main():
    """Entry point used by lint and CI."""
    cfg = Config()
    violations = []
    for path in cfg.target_files:
        violations.extend(audit_file(path))
    for violation in violations:
        print("FAIL: " + violation)
    if violations:
        return 1
    print("sanitize audit: ok (all handler pointers checked or delegated)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
