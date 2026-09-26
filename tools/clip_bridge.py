"""Host to MiniOS clipboard bridge plan builder.

Builds the exact shell lines that carry a host text file into the guest
through the shared 4 KB clipboard slot (syscalls 249/250) or, for
multi-line input, through the kernel line editor upload path the MCP
``minios_write`` tool already drives. This module never talks to QEMU
itself: it prints a plan the operator pastes into a live serial session
or feeds to ``minios_send`` line by line, so there is no host assumption
beyond the serial console both paths already require.

Single-line printable input within the clipboard cap travels as one
``clip <text>`` line and lands ready to paste with Ctrl+V at any prompt
or in vedit. Anything else (embedded newlines, overlong lines,
non-printable bytes) travels as an editor script (``edit <dst>`` plus
one ``a <line>`` per line plus ``x``), which is the only guest path
that preserves newlines: the ``clip`` builtin joins argv with spaces.

Every bound is fail-closed. A destination outside the character
whitelist, a line the kernel readline cannot carry, or content past the
clipboard cap is refused before a single plan line is printed, never
silently truncated.
"""

import re
import sys

VALID_DST = re.compile(r"[A-Za-z0-9._/-]+")


class ClipBridgeConfig:
    """Centralized bounds for the bridge plan."""

    CLIP_MAX = 4096
    EDIT_MAX_LINES = 512
    EDIT_LINE_MAX = 128
    FNAME_MAX = 63
    PRINT_LO = 32
    PRINT_HI = 126


def valid_dst(name, cfg=ClipBridgeConfig):
    """True when name is a safe guest path."""
    if not name or len(name) > cfg.FNAME_MAX:
        return False
    if name.startswith("/"):
        return False
    if ".." in name:
        return False
    return VALID_DST.fullmatch(name) is not None


def printable_line(line, cfg=ClipBridgeConfig):
    """True when every char survives the kernel readline."""
    if len(line) > cfg.EDIT_LINE_MAX:
        return False
    return all(cfg.PRINT_LO <= ord(c) <= cfg.PRINT_HI for c in line)


def build_plan(text, dst, cfg=ClipBridgeConfig):
    """Return (ok, lines, diagnostic) for carrying text to dst."""
    if not valid_dst(dst):
        return False, [], "refused: unsafe destination '%s'" % dst
    raw_lines = text.split("\n")
    if raw_lines and raw_lines[-1] == "":
        raw_lines = raw_lines[:-1]
    if len(raw_lines) > cfg.EDIT_MAX_LINES:
        return False, [], "refused: %d lines past the %d editor cap" % (
            len(raw_lines), cfg.EDIT_MAX_LINES)
    for line in raw_lines:
        if not printable_line(line):
            return False, [], "refused: line past %d printable chars" % (
                cfg.EDIT_LINE_MAX)
    if len(raw_lines) == 1 and len(text) <= cfg.CLIP_MAX:
        return True, ["clip " + raw_lines[0]], "clipboard one-liner"
    if len(text) > cfg.CLIP_MAX and len(raw_lines) == 1:
        return False, [], "refused: %d bytes past the %d clipboard cap" % (
            len(text), cfg.CLIP_MAX)
    plan = ["edit " + dst]
    plan.extend("a " + line for line in raw_lines)
    plan.append("x")
    return True, plan, "editor upload of %d lines" % len(raw_lines)


def main(argv):
    """Entry point: clip_bridge.py <src-file> <dst-name>."""
    if len(argv) != 3:
        sys.stderr.write("usage: clip_bridge.py <src-file> <dst-name>\n")
        return 2
    try:
        with open(argv[1], "r", encoding="ascii") as handle:
            text = handle.read()
    except (OSError, UnicodeDecodeError) as exc:
        sys.stderr.write("cannot read '%s': %s\n" % (argv[1], exc))
        return 1
    ok, lines, diag = build_plan(text, argv[2])
    if not ok:
        sys.stderr.write(diag + "\n")
        return 1
    sys.stderr.write(diag + "\n")
    for line in lines:
        sys.stdout.write(line + "\n")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
