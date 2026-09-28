"""Check spinlock call-site discipline across kernel C sources.

Rules, derived from the headers/spinlock.h contract:
  S1  No orphaned acquire or release: a function using spin_lock must
      reach a spin_unlock on some path (and vice versa); same for the
      irqsave/irqrestore pair. Early-return style (one acquire, many
      releases) is idiomatic here, so exact counts are not enforced.
      Functions using spin_trylock follow the conditional-unlock idiom
      and are exempt from pairing.
  S2  No plain spin_lock inside interrupt context: isr_dispatch and any
      function whose name carries isr/irq may only use the irqsave form,
      because spin_unlock re-enables interrupts unconditionally.

Usage: python3 tools/check_spin_discipline.py [dir ...]
Exit 1 with a diagnostic on the first violation, else prints ok.
"""

import os
import re
import sys


class Config:
    roots = ("kernel", "drivers", "fs", "net")
    suffix = ".c"
    handoff = frozenset(("fs_take", "fs_drop"))
    isr_name = re.compile(r"isr|irq", re.IGNORECASE)
    plain_acq = re.compile(r"(?<![\w])spin_lock\s*\(")
    plain_rel = re.compile(r"(?<![\w])spin_unlock\s*\(")
    save_acq = re.compile(r"(?<![\w])spin_lock_irqsave\s*\(")
    save_rel = re.compile(r"(?<![\w])spin_unlock_irqrestore\s*\(")
    keep_rel = re.compile(r"(?<![\w])spin_unlock_keep_irq\s*\(")
    try_acq = re.compile(r"(?<![\w])spin_trylock\s*\(")
    func_head = re.compile(
        r"^([A-Za-z_][\w\s\*]*?)\b([A-Za-z_]\w*)\s*\([^;]*\)\s*\{?\s*$")


def iter_functions(path):
    """Yield (name, first_line, body_lines) with a brace-depth split."""
    lines = open(path).read().splitlines()
    i = 0
    n = len(lines)
    while i < n:
        m = Config.func_head.match(lines[i])
        if m and "(" in lines[i] and not lines[i].strip().startswith("if"):
            name = m.group(2)
            start = i
            depth = 0
            j = i
            opened = False
            while j < n:
                depth += lines[j].count("{") - lines[j].count("}")
                if "{" in lines[j]:
                    opened = True
                if opened and depth <= 0:
                    break
                j += 1
            yield name, start + 1, lines[start:j + 1]
            i = j + 1
        else:
            i += 1


def check_file(path):
    """Return a list of violation strings for one translation unit."""
    bad = []
    for name, line, body in iter_functions(path):
        if name in Config.handoff:
            continue
        text = "\n".join(body)
        acq = len(Config.plain_acq.findall(text))
        rel = len(Config.plain_rel.findall(text))
        sacq = len(Config.save_acq.findall(text))
        srel = len(Config.save_rel.findall(text))
        keep = len(Config.keep_rel.findall(text))
        uses_try = bool(Config.try_acq.search(text))
        if not uses_try:
            if acq and not rel and not keep:
                bad.append("%s:%d: %s: spin_lock without spin_unlock"
                           % (path, line, name))
            if rel and not acq:
                bad.append("%s:%d: %s: spin_unlock without spin_lock"
                           % (path, line, name))
            if sacq and not srel and not keep:
                bad.append("%s:%d: %s: irqsave without irqrestore"
                           % (path, line, name))
            if srel and not sacq:
                bad.append("%s:%d: %s: irqrestore without irqsave"
                           % (path, line, name))
        if acq and Config.isr_name.search(name):
            bad.append("%s:%d: %s: plain spin_lock in interrupt context"
                       % (path, line, name))
        if name == "isr_dispatch" and acq:
            bad.append("%s:%d: plain spin_lock inside isr_dispatch"
                       % (path, line))
    return bad


def main(argv):
    """Walk the configured roots and fail closed on any violation."""
    roots = argv[1:] or list(Config.roots)
    problems = []
    for root in roots:
        for dirpath, _dirs, files in os.walk(root):
            for fn in sorted(files):
                if fn.endswith(Config.suffix):
                    problems.extend(
                        check_file(os.path.join(dirpath, fn)))
    if problems:
        for p in problems:
            print("check_spin_discipline: %s" % p)
        return 1
    print("check_spin_discipline: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
