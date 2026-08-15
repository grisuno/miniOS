#!/bin/bash
# Mutation testing for the MiniOS MCP bridge. Every mutant is injected into
# a private copy of minios_mcp.py and run against the unit and BDD suite.
# A mutant that survives (suite fully green) exposes a test gap.
#
# Mutation format: "name | sed -i expression | file"

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$HERE/.."
WORK="$(mktemp -d "${TMPDIR:-/tmp}/minios_mcp_mut.XXXXXX")" || exit 1
KEEP_WORK="${KEEP_WORK:-0}"
if [ "$KEEP_WORK" = "1" ]; then
    echo "mutation workspace: $WORK"
else
    trap 'rm -rf "$WORK"' EXIT
fi

FILE="minios_mcp.py"

# Shorter waits keep the mutation loop bounded: every failing marker wait
# costs its timeout, and a mutant that breaks the prompt would otherwise
# stall each scenario for a minute.
export MINIOS_TMO_BOOT=8000
export MINIOS_TMO_PROMPT=5000
export MINIOS_TMO_EXPECT=5000
export MINIOS_TMO_POWEROFF=8000

MUTATIONS="
boot-marker-bad | s/CFG_MARK_BOOT = \"MiniOS Kernel\"/CFG_MARK_BOOT = \"MiniOS KerneX\"/ | $FILE
prompt-shell-marker | s/CFG_PROMPT_SHELL = \"miniOS> \"/CFG_PROMPT_SHELL = \"miniOSX> \"/ | $FILE
editor-prompt-marker | s/CFG_PROMPT_EDITOR = \"edit> \"/CFG_PROMPT_EDITOR = \"edX> \"/ | $FILE
poweroff-marker | s/CFG_MARK_POWEROFF = \"powering off\"/CFG_MARK_POWEROFF = \"powering down\"/ | $FILE
editor-save-cmd | s/CFG_EDITOR_SAVE = \"x\"/CFG_EDITOR_SAVE = \"q\"/ | $FILE
editor-append-cmd | s/CFG_EDITOR_APPEND = \"a\"/CFG_EDITOR_APPEND = \"l\"/ | $FILE
send-no-newline | s/line + \"\\\\n\"/line/ | $FILE
send-wrong-marker | s/marker = CFG_PROMPT_SHELL.encode(\"latin-1\")/marker = CFG_PROMPT_EDITOR.encode(\"latin-1\")/ | $FILE
expect-cursor-zero | s/wait_for(raw, self.cursor/wait_for(raw, 0/ | $FILE
expect-always-matched | s/return {\"matched\": False, \"text\": self.log.text_from(self.cursor)}/return {\"matched\": True, \"text\": self.log.text_from(self.cursor)}/ | $FILE
path-dotdot-check | s/if \"\\.\\.\" in name:/if \"zz\" in name:/ | $FILE
write-cursor-zero | s/self.cursor = pos + len(shell)/self.cursor = 0/ | $FILE
boot-consumes-prompt | s/self.cursor = pos + len(CFG_MARK_BOOT.encode(\"latin-1\"))/self.cursor = ready + len(CFG_PROMPT_SHELL.encode(\"latin-1\"))/ | $FILE
unknown-tool-code | s/CFG_JSONRPC_INVALID_PARAMS, \"unknown tool/CFG_JSONRPC_INTERNAL_ERROR, \"unknown tool/ | $FILE
"

KILLED=0
SURVIVED=0
BROKEN=0

OLDIFS=$IFS
IFS='
'
for entry in $MUTATIONS; do
    IFS=$OLDIFS
    [ -z "$entry" ] && continue
    name="${entry%%|*}"
    name="$(echo "$name" | tr -d ' ')"
    rest="${entry#*|}"
    expr="${rest%%|*}"
    file="$(echo "${rest#*|}" | tr -d ' ')"
    [ -z "$name" ] && continue
    dir="$WORK/$name"
    mkdir -p "$dir"
    cp "$HERE/$file" "$dir/$file"
    if ! eval "sed -i '$expr' '$dir/$file'" 2>/dev/null; then
        echo "MUTANT $name: ERROR (sed failed)"
        BROKEN=$((BROKEN + 1))
        IFS='
'
        continue
    fi
    if cmp -s "$HERE/$file" "$dir/$file"; then
        echo "MUTANT $name: ERROR (expression matched nothing)"
        BROKEN=$((BROKEN + 1))
        IFS='
'
        continue
    fi
    if ! python3 -m py_compile "$dir/$file" 2>/dev/null; then
        echo "MUTANT $name: KILLED (compile failure)"
        KILLED=$((KILLED + 1))
        IFS='
'
        continue
    fi
    ( cd "$ROOT" && MINIOS_MCP="$dir/$file" python3 -m unittest mcp/test_minios_mcp.py > "$dir/suite.log" 2>&1 )
    rc=$?
    if [ "$rc" -eq 0 ]; then
        echo "MUTANT $name: SURVIVED (test gap!)"
        sed -n 's/^=== summary/    suite: summary/p' "$dir/suite.log"
        SURVIVED=$((SURVIVED + 1))
    else
        echo "MUTANT $name: KILLED"
        KILLED=$((KILLED + 1))
    fi
    IFS='
'
done
IFS=$OLDIFS

echo ""
echo "=== mutation summary: $KILLED killed, $SURVIVED survived, $BROKEN broken ==="
if [ "$BROKEN" -gt 0 ]; then
    echo "A broken mutant never reached the suite; fix its expression."
    exit 1
fi
if [ "$SURVIVED" -gt 0 ]; then
    echo "A surviving mutant means the suite does not cover that behavior."
    exit 1
fi
exit 0
