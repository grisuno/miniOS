"""Verify every mutate.sh mutant anchor matches its target file.

A mutant whose sed expression matches nothing is reported BROKEN by
mutate.sh instead of killed, so a stale anchor silently weakens the
mutation gate. Ground truth is sed itself: each expression is applied
to a scratch copy of its target and a no-change result is breakage.

Usage:
    python3 tools/check_mutant_anchors.py
"""
import subprocess
import sys
import tempfile
from pathlib import Path


class Config:
    """Central configuration for the anchor check."""

    repo = Path(__file__).resolve().parent.parent
    mutate_sh = repo / "tools" / "mutate.sh"
    table_start_marker = 'MUTATIONS="'
    table_end_marker = '"'


def bash_unquote(expr):
    """Collapse the escapes bash applies inside the MUTATIONS string."""
    out = []
    i = 0
    while i < len(expr):
        ch = expr[i]
        if ch == "\\" and i + 1 < len(expr) and expr[i + 1] in '$`"\\\n':
            out.append(expr[i + 1])
            i += 2
            continue
        out.append(ch)
        i += 1
    return "".join(out)


def parse_mutations(text):
    """Extract (name, expression, target) triples from the MUTATIONS block.

    Bounds derive from the block markers, never from line numbers, so
    adding a mutant cannot silently push rows out of the checked range.
    """
    rows = []
    lines = text.splitlines()
    first = next(
        i for i, line in enumerate(lines)
        if line.strip() == Config.table_start_marker
    )
    last = next(
        i for i, line in enumerate(lines[first + 1:], start=first + 1)
        if line.strip() == Config.table_end_marker
    )
    for line in lines[first + 1:last]:
        line = line.strip()
        if not line or "|" not in line:
            continue
        name, rest = line.split("|", 1)
        expr, _, target = rest.rpartition("|")
        rows.append((name.strip(), expr.strip(), target.strip()))
    return rows


def anchor_matches(repo, target, expr):
    """Apply the sed expression to a scratch copy; True when it changes it."""
    src = repo / target
    if not src.is_file():
        return False, "missing file"
    expr = bash_unquote(expr)
    with tempfile.NamedTemporaryFile(suffix="-anchor") as tmp:
        tmp.write(src.read_bytes())
        tmp.flush()
        proc = subprocess.run(
            ["sed", "-i", expr, tmp.name], capture_output=True, text=True
        )
        if proc.returncode != 0:
            return False, "sed error: %s" % proc.stderr.strip()
        with open(tmp.name, "rb") as handle:
            changed = handle.read() != src.read_bytes()
    return changed, "no match" if not changed else "ok"


def main():
    """Entry point: report anchors that change nothing and exit nonzero."""
    rows = parse_mutations(Config.mutate_sh.read_text())
    broken = []
    for name, expr, target in rows:
        ok, reason = anchor_matches(Config.repo, target, expr)
        if not ok:
            broken.append((name, target, reason))
    if broken:
        for name, target, reason in broken:
            print("BROKEN %s (%s): %s" % (name, target, reason))
        print("%d/%d anchors broken" % (len(broken), len(rows)))
        return 1
    print("%d/%d anchors match" % (len(rows), len(rows)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
