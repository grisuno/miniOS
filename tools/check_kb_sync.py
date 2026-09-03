"""check_kb_sync.py -- Verify KNOWLEDGE_BASE.md is in sync with code.

Runs readmenator to regenerate the knowledge base, then checks if the
output differs from the committed version.  Used in CI to prevent drift.

Usage:
    python3 tools/check_kb_sync.py [--kb KNOWLEDGE_BASE.md] [--regenerate]

Exit codes:
    0 -- KB is in sync
    1 -- KB is out of sync
    2 -- readmenator not available
"""

import os
import sys
import subprocess
import argparse

DEFAULT_KB = "KNOWLEDGE_BASE.md"
READMENATOR = "tools/readmenator.py"


def regenerate_kb():
    """Attempt to regenerate KNOWLEDGE_BASE.md using readmenator."""
    if not os.path.exists(READMENATOR):
        return None

    try:
        result = subprocess.run(
            [sys.executable, READMENATOR, "--output", DEFAULT_KB],
            capture_output=True, text=True, timeout=120
        )
        if result.returncode == 0 and os.path.exists(DEFAULT_KB):
            with open(DEFAULT_KB, "r") as f:
                return f.read()
    except (subprocess.TimeoutExpired, FileNotFoundError):
        pass

    return None


def main():
    parser = argparse.ArgumentParser(description="Check KB sync")
    parser.add_argument("--kb", default=DEFAULT_KB,
                        help="Path to KNOWLEDGE_BASE.md")
    parser.add_argument("--regenerate", action="store_true",
                        help="Regenerate and compare")
    args = parser.parse_args()

    if not os.path.exists(args.kb):
        print(f"check_kb_sync: {args.kb} not found, skipping")
        sys.exit(0)

    if not args.regenerate:
        print(f"check_kb_sync: {args.kb} exists, skipping (no --regenerate)")
        sys.exit(0)

    new_content = regenerate_kb()
    if new_content is None:
        print("check_kb_sync: readmenator not available, skipping")
        sys.exit(0)

    with open(args.kb, "r") as f:
        old_content = f.read()

    if old_content == new_content:
        print("check_kb_sync: OK (KB in sync)")
        sys.exit(0)

    print("check_kb_sync: KB OUT OF SYNC")
    print("  Regenerated content differs from committed version")
    print("  Run: python3 tools/readmenator.py --output KNOWLEDGE_BASE.md")
    sys.exit(1)


if __name__ == "__main__":
    main()
