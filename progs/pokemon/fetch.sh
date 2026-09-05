#!/bin/sh
# fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.
#
# The upstream project ships the recompiler + runtime, but no ROMs and no
# pre-generated game code (see its README). You generate a project from a
# ROM you legally own, then point the MiniOS build at it. See README.md.
#
# Usage: ./fetch.sh   (safe to re-run; never touches an existing checkout)

set -e
cd "$(dirname "$0")"

URL="https://github.com/arcanite24/gb-recompiled.git"

if [ -d upstream ]; then
    echo "upstream/ already exists, leaving it alone."
    exit 0
fi

if ! command -v git >/dev/null 2>&1; then
    echo "error: git is required to fetch $URL" >&2
    exit 1
fi

echo "Cloning $URL ..."
git clone --depth 1 "$URL" upstream
echo "Done. Next: build gbrecomp (see upstream README), generate a project"
echo "from your ROM into game/, then run the MiniOS build."
