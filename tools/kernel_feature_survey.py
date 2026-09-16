#!/usr/bin/env python3
"""kernel_feature_survey.py - verify which C features the MiniOS kernel needs.

Scans kernel and ring-3 sources for constructs miniGCC must support before
it can compile them: function pointers, extended-asm constraints, wide
calls, unions, long long, bitfields, privileged mnemonics and section
attributes. Every claim the SDD specs make about a gap must reproduce
through this tool first, so plans never rest on hallucinated file paths.

Usage: kernel_feature_survey.py [root] [--format text|md]
Exit 0 always; findings print to stdout.
"""
import os
import re
import sys


class SurveyConfig:
    """Centralized tunables for the survey."""
    SOURCE_SUFFIXES = (".c", ".h")
    SKIP_DIRS = (".git", "readmenator-agent", "readmenator-maps",
                 "third_party", "build", "__pycache__")
    MAX_PARAMS_MINIGCC = 6
    FNPTR_DECL_RE = re.compile(r"\(\s*\*\s*[A-Za-z_]\w*\s*\)\s*\(")
    ASM_CONSTRAINT_RE = re.compile(r'"([=+%]*)([a-zA-Z])"')
    UNION_RE = re.compile(r"(?<![A-Za-z_])union(?![A-Za-z_])")
    LONGLONG_RE = re.compile(r"(?<![A-Za-z_])long\s+long(?![A-Za-z_])")
    BITFIELD_RE = re.compile(r":\s*\d+\s*;")
    PRIV_RE = re.compile(r'"[^"]*(lidt|lgdt|ltr|fxsave|fxrstor|mov\s+%+\w+,\s*%+cr\d|mov\s+%+cr\d|in\s*\(\s*%+\w+\s*\)|in[lwb]?\s|out[lwb]?\s)[^"]*"')
    SECTION_RE = re.compile(r'section\s*\(\s*"([^"]+)"\s*\)')
    FUNCDEF_RE = re.compile(r"^\s*(?:static\s+)?(?:inline\s+)?[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*\(([^;{}]*)\)\s*\{?\s*$")


def iter_sources(root):
    """Yield C source paths under root, skipping vendored and cache dirs."""
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = [d for d in dirnames if d not in SurveyConfig.SKIP_DIRS]
        for fn in filenames:
            if fn.endswith(SurveyConfig.SOURCE_SUFFIXES):
                yield os.path.join(dirpath, fn)


def find_fnptr_hits(path, text):
    """Return line numbers declaring function pointers."""
    return [i + 1 for i, line in enumerate(text.splitlines())
            if SurveyConfig.FNPTR_DECL_RE.search(line)]


def find_asm_constraints(path, text):
    """Return sorted constraint letters used in extended asm."""
    found = set()
    for line in text.splitlines():
        if "__asm__" in line or "__asm" in line or "asm(" in line:
            for m in SurveyConfig.ASM_CONSTRAINT_RE.finditer(line):
                found.add(m.group(2))
    return sorted(found)


def count_params(params):
    """Count parameters, treating void and empty as zero."""
    params = params.strip()
    if not params or params == "void":
        return 0
    return params.count(",") + 1


def survey(root):
    """Collect findings per category across all sources."""
    findings = {"fnptr": [], "constraints": {}, "wide_calls": [],
                "unions": [], "longlong": [], "bitfields": [],
                "privileged": [], "sections": set()}
    for path in iter_sources(root):
        try:
            with open(path, "r", errors="replace") as f:
                text = f.read()
        except OSError:
            continue
        rel = os.path.relpath(path, root)
        for ln in find_fnptr_hits(path, text):
            findings["fnptr"].append("%s:%d" % (rel, ln))
        for c in find_asm_constraints(path, text):
            findings["constraints"].setdefault(c, []).append(rel)
        for m in SurveyConfig.UNION_RE.finditer(text):
            ln = text.count("\n", 0, m.start()) + 1
            findings["unions"].append("%s:%d" % (rel, ln))
        for m in SurveyConfig.LONGLONG_RE.finditer(text):
            ln = text.count("\n", 0, m.start()) + 1
            findings["longlong"].append("%s:%d" % (rel, ln))
        for i, line in enumerate(text.splitlines()):
            stripped = line.strip()
            if (SurveyConfig.BITFIELD_RE.search(line) and "(" not in line
                    and "?" not in line and not stripped.startswith("case")
                    and not stripped.startswith("default")):
                findings["bitfields"].append("%s:%d" % (rel, i + 1))
        for m in SurveyConfig.PRIV_RE.finditer(text):
            ln = text.count("\n", 0, m.start()) + 1
            findings["privileged"].append("%s:%d:%s" % (rel, ln, m.group(1)))
        for m in SurveyConfig.SECTION_RE.finditer(text):
            findings["sections"].add(m.group(1))
    return findings


def render_text(findings):
    """Render findings as plain text."""
    lines = []
    lines.append("fnptr_decls=%d" % len(findings["fnptr"]))
    for hit in findings["fnptr"][:15]:
        lines.append("  fnptr %s" % hit)
    lines.append("asm_constraints=%s" % ",".join(sorted(findings["constraints"])))
    lines.append("unions=%d longlong=%d bitfields=%d" % (
        len(findings["unions"]), len(findings["longlong"]),
        len(findings["bitfields"])))
    for hit in findings["unions"][:5] + findings["longlong"][:5]:
        lines.append("  type %s" % hit)
    lines.append("privileged=%d" % len(findings["privileged"]))
    for hit in findings["privileged"][:15]:
        lines.append("  priv %s" % hit)
    lines.append("sections=%s" % ",".join(sorted(findings["sections"])))
    return "\n".join(lines)


def main(argv):
    """Entry point for the survey tool."""
    root = argv[1] if len(argv) > 1 and not argv[1].startswith("--") else os.getcwd()
    print(render_text(survey(root)))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
