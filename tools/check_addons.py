#!/usr/bin/env python3
"""check_addons.py -- validate the MiniOS addon marketplace index.

Loads every addons/*.yaml through the strict stdlib-only parser in
mcp/minios_addons.py (no PyYAML) and reports each addon's kind. Any
unparseable file, failed validation or installer refusal for a guest
addon fails closed with a diagnostic and a nonzero exit, so the index
can never drift from the dialect the MCP server speaks.

Usage:
  python3 tools/check_addons.py [--addons-dir DIR]

Exit status: 0 when every file validates, 1 otherwise.
"""

import argparse
import importlib.util as iu
import os
import sys


def load_parser():
    here = os.path.dirname(os.path.abspath(__file__))
    path = os.path.join(here, "..", "mcp", "minios_addons.py")
    spec = iu.spec_from_file_location("minios_addons", path)
    mod = iu.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--addons-dir", default="addons",
                    help="directory holding the addon YAML files")
    args = ap.parse_args()

    ma = load_parser()
    names = sorted(n for n in os.listdir(args.addons_dir) if n.endswith(".yaml"))
    if not names:
        print("check_addons.py: error: no addon files in %s" % args.addons_dir,
              file=sys.stderr)
        return 1
    fails = 0
    for name in names:
        path = os.path.join(args.addons_dir, name)
        try:
            with open(path, "r") as f:
                text = f.read()
            addon = ma.validate_addon(ma.parse_addon_yaml(text), name)
        except ma.AddonError as exc:
            print("check_addons.py: %s: %s" % (name, exc), file=sys.stderr)
            fails += 1
            continue
        except OSError as exc:
            print("check_addons.py: %s: cannot read: %s" % (name, exc),
                  file=sys.stderr)
            fails += 1
            continue
        print("  %-16s kind=%-9s artifact=%s"
              % (name, addon["install"].get("kind", "guest"),
                 addon["install"].get("artifact", "")))
    if fails:
        print("check_addons.py: %d invalid addon file(s)" % fails, file=sys.stderr)
        return 1
    print("check_addons.py: %d addon file(s) valid" % len(names))
    return 0


if __name__ == "__main__":
    sys.exit(main())
