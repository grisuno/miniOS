#!/bin/bash
# Mutation testing for the MiniOS MCP bridge. Every mutant is injected into
# a private copy of minios_mcp.py and run against the unit and BDD suite.
# A mutant that survives (suite fully green) exposes a test gap.
#
# Suites run in parallel (one worker per core, MUTATE_JOBS to override);
# each mutant gets its own pid file and addon state so the runs stay
# independent.
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
# stall each scenario for a minute. The boot budget carries some headroom
# because several QEMU instances boot concurrently.
export MINIOS_TMO_BOOT=15000
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
registry-forgot-record | s/rebuilt.append(\"%s %s\" % (name, version))/rebuilt.append(name)/ | minios_addons.py
state-not-saved | s/state.save(addons)/pass/ | minios_addons.py
parts-not-cleaned | s/            session._cleanup_parts(parts)/            pass/ | minios_addons.py
roundtrip-check-removed | s/if body.rstrip(\\\"\\\\n\\\") != expected:/if False and body.rstrip(\\\"\\\\n\\\") != expected:/ | minios_addons.py
verify-exit-code-ignored | s/if \\\"exit_code\\\" in entry and code != entry\\[\\\"exit_code\\\"\\]:/if False:/ | minios_addons.py
build-failure-ignored | s/if code is not None and code != 0:/if code is not None and False:/ | minios_addons.py
exit-code-parsed-as-zero | s/return int(match.group(1)) if match else None/return 0 if match else None/ | minios_addons.py
split-drops-chunks | s/range(0, len(lines), ADDON_CHUNK_LINES)/range(0, 1, ADDON_CHUNK_LINES)/ | minios_addons.py
yaml-unknown-key-accepted | s/if k not in ADDON_KEYS:/if k not in ADDON_KEYS and False:/ | minios_addons.py
installer-dispatched-to-list | s/return self._addon_install(args)/return self._addons_list()/ | $FILE
"

KILLED=0
SURVIVED=0
BROKEN=0

TODO="$WORK/todo"
: > "$TODO"

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
    cp "$HERE/minios_mcp.py" "$dir/minios_mcp.py"
    cp "$HERE/minios_addons.py" "$dir/minios_addons.py"
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
    if ! python3 -m py_compile "$dir/$file" 2>/dev/null || ! python3 -m py_compile "$dir/minios_mcp.py" 2>/dev/null; then
        echo "MUTANT $name: KILLED (compile failure)"
        KILLED=$((KILLED + 1))
        IFS='
'
        continue
    fi
    echo "$dir|$name|$file" >> "$TODO"
    IFS='
'
done
IFS=$OLDIFS

# Each mutant runs the suite in its own directory with its own pid file and
# addon state, so the runs are independent and may execute in parallel. The
# worker writes the exit code; the loop below maps it onto the verdict.
run_one() {
    dir="$1"
    file="$2"
    (
        cd "$ROOT" &&
            MINIOS_MCP="$dir/$file" \
            MINIOS_PIDFILE="$dir/qemu.pid" \
            MINIOS_ADDON_STATE="$dir/state.json" \
            python3 -m unittest mcp/test_minios_mcp.py > "$dir/suite.log" 2>&1
    )
    echo $? > "$dir/rc"
}
export -f run_one
export ROOT

MAXJOBS="${MUTATE_JOBS:-4}"
cut -d'|' -f1,3 "$TODO" | xargs -r -d '\n' -P "$MAXJOBS" -n 1 \
    bash -c 'line="$1"; run_one "${line%%|*}" "${line#*|}"' _

while IFS='|' read -r dir name file; do
    [ -z "$name" ] && continue
    rc="$(cat "$dir/rc" 2>/dev/null || echo 1)"
    if [ "$rc" -eq 0 ]; then
        echo "MUTANT $name: SURVIVED (test gap!)"
        sed -n 's/^=== summary/    suite: summary/p' "$dir/suite.log"
        SURVIVED=$((SURVIVED + 1))
    else
        echo "MUTANT $name: KILLED"
        KILLED=$((KILLED + 1))
    fi
done < "$TODO"

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
