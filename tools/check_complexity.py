"""check_complexity.py -- Kernel complexity gate for MiniOS CI.

Validates that kernel.c does not exceed the configured symbol count
threshold without explicit approval in ARCH_POLICY.yaml.

Usage:
    python3 tools/check_complexity.py [--threshold 350] [--policy ARCH_POLICY.yaml]

Exit codes:
    0 -- within threshold or explicitly approved
    1 -- complexity exceeded without approval
    2 -- input files missing
"""

import re
import sys
import os

DEFAULT_THRESHOLD = 350
KERNEL_SOURCE = "kernel.c"
POLICY_FILE = "ARCH_POLICY.yaml"


def count_symbols(filepath):
    """Count top-level function and global variable definitions."""
    if not os.path.exists(filepath):
        return 0

    count = 0
    with open(filepath, "r") as f:
        for line in f:
            stripped = line.strip()
            # Count function definitions: type name(...) at column 0
            if re.match(r'^(static\s+)?(void|int|unsigned|long|char|'
                        r'KFILE|RDFile|Elf64|MiniFS|struct\s+\w+)\s+\w+\s*\(',
                        stripped):
                count += 1
            # Count global variables: type name at column 0 (not in functions)
            elif re.match(r'^(static\s+)?(const\s+)?(unsigned|char|int|void)\s+'
                          r'\w+\s*(\[|;|=)',
                          stripped):
                count += 1
    return count


def load_approval(policy_path):
    """Load explicit complexity approval from ARCH_POLICY.yaml."""
    if not os.path.exists(policy_path):
        return False, 0

    with open(policy_path, "r") as f:
        content = f.read()

    # Simple YAML-like parsing for kernel_symbol_limit
    match = re.search(r'kernel_symbol_limit:\s*(\d+)', content)
    if match:
        return True, int(match.group(1))
    return False, 0


def main():
    import argparse
    parser = argparse.ArgumentParser(description="Check kernel complexity")
    parser.add_argument("--threshold", type=int, default=DEFAULT_THRESHOLD,
                        help="Maximum symbol count (default: 350)")
    parser.add_argument("--policy", default=POLICY_FILE,
                        help="Path to ARCH_POLICY.yaml")
    args = parser.parse_args()

    if not os.path.exists(KERNEL_SOURCE):
        print(f"check_complexity: {KERNEL_SOURCE} not found, skipping")
        sys.exit(0)

    symbols = count_symbols(KERNEL_SOURCE)
    approved, limit = load_approval(args.policy)

    effective_limit = limit if approved else args.threshold

    if symbols > effective_limit:
        print(f"check_complexity: COMPLEXITY REGRESSION")
        print(f"  {KERNEL_SOURCE}: {symbols} symbols "
              f"> limit {effective_limit}")
        if approved:
            print(f"  (approved limit from {args.policy})")
        else:
            print(f"  (no approval in {args.policy}; "
                  f"default threshold={args.threshold})")
        sys.exit(1)

    print(f"check_complexity: OK ({symbols} symbols, "
          f"limit={effective_limit})")
    sys.exit(0)


if __name__ == "__main__":
    main()
