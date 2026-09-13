"""Fail-closed stub gate for unimplemented process syscalls.

fork, vfork and execve have no implementation in this kernel. A stub
that answers success lets userland believe a child exists when none
does, so all three must answer Linux ENOSYS. The check scans the
handler definitions and fails on any success return.
"""

import re
import sys


class Config:
    """Centralized tunable values for the stub gate."""

    target_file = "kernel/syscalls_proc.c"
    handlers = ("sys_linux_fork", "sys_linux_vfork", "sys_linux_execve")
    enosys_literal = "-38"
    success_pattern = re.compile(r"\breturn\s+0\s*;")


def handler_body(text, name):
    """Return the body of the named handler or empty string when absent."""
    pattern = re.compile(
        r"long\s+" + re.escape(name) + r"\([^)]*\)\s*\{(.*?)\n\}",
        re.DOTALL,
    )
    match = pattern.search(text)
    return match.group(1) if match else ""


def check_stubs(text, cfg):
    """Collect failure strings for stubs that do not fail closed."""
    failures = []
    for name in cfg.handlers:
        body = handler_body(text, name)
        if not body:
            failures.append(name + ": handler not found")
            continue
        if cfg.enosys_literal not in body:
            failures.append(name + ": missing ENOSYS answer")
        if cfg.success_pattern.search(body):
            failures.append(name + ": answers success")
    return failures


def main():
    """Entry point used by lint and CI."""
    cfg = Config()
    with open(cfg.target_file, "r") as handle:
        text = handle.read()
    failures = check_stubs(text, cfg)
    for failure in failures:
        print("FAIL: " + failure)
    if failures:
        return 1
    print("stub gate: ok (fork/vfork/execve answer ENOSYS)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
