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

SOURCES="kernel.c bootdefs.h net.c tls.c tls_x509.c"

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
bin-path-prefix | s/#define SHELL_BIN_PATH     \"bin\/\"/#define SHELL_BIN_PATH     \"bix\/\"/ | kernel.c
bin-lookup-bypassed | s/ret = shell_run_from_path(argv\\[0\\], argc, argv);/ret = -1;/ | kernel.c
cwd-never-applied | s/kmemcpy(out, fs_cwd, kstrlen(fs_cwd) + 1);/kmemcpy(out, \"\", 1);/ | kernel.c
cd-always-fails | s/if (!fs_resolve(argv\\[1\\], resolved, sizeof(resolved))) {/if (1) {/ | kernel.c
rm-missing-passes | s/if (!f) { kprintf(\\\"rm: %s: no such file\\\\n\\\", argv\\[1\\]); return; }/if (0) {/ | kernel.c
rm-dir-accepted | s/if (fs_is_dir(resolved)) {/if (0) {/ | kernel.c
mkdir-dup-passes | s/if (fs_dir_exists(dirname)) {/if (0) {/ | kernel.c
mkdir-parent-bypassed | s/if (!fs_dir_exists(parent)) {/if (0) {/ | kernel.c
cd-exists-bypassed | s/if (!fs_dir_exists(target)) {/if (0) {/ | kernel.c
kfopen-dir-refusal-bypassed | s/if (fs_is_dir(resolved)) return 0;/\\/* dir bypass *\\// | kernel.c
ps-empty | s/kprintf(\\\"  %-12s  %s  %p\\\\n\\\", p->name,/if (0) kprintf(\\\"  %-12s  %s  %p\\\\n\\\", p->name,/ | kernel.c
cat-drops-second-file | s/for (fi = 1; fi < argc; fi++)/for (fi = 1; fi < 2; fi++)/ | kernel.c
append-flag-ignored | s/            \*append_mode = 1;/            \*append_mode = 0;/ | kernel.c
append-mode-acts-like-write | s/((mode\[0\] == \x27a\x27) ? 2 : 0)/((mode\[0\] == \x27a\x27) ? 1 : 0)/ | kernel.c
append-resets-pos | s/f->pos  = (f->mode == 2) ? f->rf->size : 0;/f->pos  = 0;/ | kernel.c
trace-print-gated-off | s/if (s_trace_enabled)/if (0) \&\& (s_trace_enabled)/ | kernel.c
trace-on-never-enables | s/syscall_trace_set(1)/syscall_trace_set(0)/ | kernel.c
arp-cache-never-stored | s/net_arp_cache\[free\].valid = 1;/net_arp_cache\[free\].valid = 0;/ | net.c
arp-reply-ignored | s/net_get16(frame + 20) == NET_ARP_REPLY/net_get16(frame + 20) == 0/ | net.c
tx-owner-wait-inverted | s/while (!(net_reg32((unsigned short)(NET_REG_TSD0 + slot \* 4)) \& 0x2000)) {/while (net_reg32((unsigned short)(NET_REG_TSD0 + slot \* 4)) \& 0x2000) {/ | net.c
tcp-seq-never-advances | s/if (fresh \&\& (flags/if (0) { if (fresh \&\& (flags/ | net.c
tcp-peer-ack-corrupts-ack | s/\/\* ACK: peer acks our data \*\//s->ack = ack; \/\* ACK: peer acks our data \*\// | net.c
ping-id-mismatched | s/net_put16(req + 4, net_icmp_id)/net_put16(req + 4, net_icmp_id + 1)/ | net.c
ip-csum-ignored | s/if (net_checksum(ip, 20) != 0) return;/if (0) return;/ | net.c
tcp-ack-not-advanced | s/                    s->ack = s->rx_next;/                    s->ack = s->ack;/ | net.c
rx-frame-truncated | s/    for (k = 0; k < n; k++) {/    for (k = 0; k < n - 128; k++) {/ | net.c

tls-close-notify-unrecognized | s/if (s->rec_len == 2 \&\& s->rec\[1\] == 0) {/if (s->rec_len == 2 \&\& s->rec\[1\] == 1) {/ | tls.c
tls-chain-stride | s/TLS_MEMCPY(s->chain + stored, m + pos, cl);/TLS_MEMCPY(s->chain + s->n_certs * TLS_CERT_MAX, m + pos, cl);/ | tls.c
tls-wildcard-overrun | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len; i++) {/ | tls_x509.c
tls-wildcard-short-tail | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len - 2; i++) {/ | tls_x509.c
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

    case "$file" in
        tls.c|tls_x509.c|tls_crypto.c|tls.h)
            make -C "$HERE" test-tls > "$BACKUP/suite.log" 2>&1
            ;;
        *)
            FAIL_FAST=1 "$HERE/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
    esac
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
