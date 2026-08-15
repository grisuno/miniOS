#!/bin/bash
# Mutation testing for MiniOS.
#
# Each mutation is applied to the source in place, the disk image is rebuilt
# and the behavioural suite is run in fail-fast mode. A mutant that survives
# a full green suite exposes a gap that must be closed by adding a scenario,
# never by deleting the mutant.
#
# The sources are backed up before the first mutation and restored on every
# exit path, including interrupts. A mutation whose expression matches
# nothing is reported as broken rather than surviving: `sed -i` exits zero
# when it changes nothing, which would otherwise rebuild pristine sources and
# look like a test gap.
#
# Mutation format: "name | sed -i expression | file"

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
BACKUP="$(mktemp -d "${TMPDIR:-/tmp}/minios_mut.XXXXXX")" || exit 1

SOURCES="kernel.c bootdefs.h"

restore_sources() {
    local f
    for f in $SOURCES; do
        [ -f "$BACKUP/$f" ] && cp "$BACKUP/$f" "$HERE/$f"
    done
}

cleanup() {
    restore_sources
    rm -rf "$BACKUP"
}
trap cleanup EXIT INT TERM

for f in $SOURCES; do
    cp "$HERE/$f" "$BACKUP/$f" || exit 1
done

MUTATIONS="
pd-drop-page-size | s/#define PT_FLAGS_PRESENT_RW_PS    0x083/#define PT_FLAGS_PRESENT_RW_PS    0x003/ | bootdefs.h
gdt64-code-to-data | s/#define GDT64_DESC_CODE           0x00209A0000000000/#define GDT64_DESC_CODE           0x0000920000000000/ | bootdefs.h
kernel-buffer-seg | s/#define BOOT_KERNEL_BUF_SEG       0x1000/#define BOOT_KERNEL_BUF_SEG       0x1001/ | bootdefs.h
chunk-copy-length | s/#define SECTOR_DWORD_SHIFT        7/#define SECTOR_DWORD_SHIFT        6/ | bootdefs.h
ramdisk-entry-stride | s/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 8)/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 4)/ | kernel.c
redirect-captures-nothing | s/    redir_active = 1;/    redir_active = 0;/ | kernel.c
status-leaks-into-redirect | s/int was = redirect_suspend();/int was = 0;/ | kernel.c
editor-drops-unsaved | s/if (e->dirty) {/if (0) {/ | kernel.c
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
    name="$(echo "${entry%%|*}" | tr -d ' ')"
    rest="${entry#*|}"
    expr="${rest%%|*}"
    file="$(echo "${rest#*|}" | tr -d ' ')"
    [ -z "$name" ] && continue

    restore_sources
    if ! eval "sed -i '$expr' '$HERE/$file'" 2>/dev/null; then
        echo "MUTANT $name: ERROR (sed failed)"
        BROKEN=$((BROKEN + 1))
        IFS='
'
        continue
    fi
    if cmp -s "$BACKUP/$file" "$HERE/$file"; then
        echo "MUTANT $name: ERROR (expression matched nothing)"
        BROKEN=$((BROKEN + 1))
        IFS='
'
        continue
    fi

    if ! make -C "$HERE" > "$BACKUP/build.log" 2>&1; then
        echo "MUTANT $name: KILLED (build failure)"
        KILLED=$((KILLED + 1))
        IFS='
'
        continue
    fi

    FAIL_FAST=1 "$HERE/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
    if [ $? -eq 0 ]; then
        echo "MUTANT $name: SURVIVED (test gap!)"
        sed -n 's/^=== summary/    suite: summary/p' "$BACKUP/suite.log"
        SURVIVED=$((SURVIVED + 1))
    else
        echo "MUTANT $name: KILLED"
        KILLED=$((KILLED + 1))
    fi
    IFS='
'
done
IFS=$OLDIFS

restore_sources
make -C "$HERE" > "$BACKUP/build.log" 2>&1

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
