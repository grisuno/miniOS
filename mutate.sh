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
# Progress is persisted to a state file (default .mutate-state in the repo
# root, overridable with --state or MINIOS_MUTATE_STATE). A run therefore
# RESUMES where it left off: mutants already recorded are skipped, so a
# timed-out run can be picked up without re-running the finished ones. The
# state file is just a list of "name outcome" lines and can be edited by
# hand to re-target work.
#
# Usage:
#   mutate.sh                     full run, resuming from the first mutant not
#                                 yet recorded in the state file
#   mutate.sh --from NAME         force-run from the mutant NAME onward,
#                                 ignoring recorded state for those mutants
#   mutate.sh --match REGEX       only run mutants whose name matches REGEX
#   mutate.sh --limit N           run at most N mutants this invocation
#   mutate.sh --state FILE        use FILE as the progress file
#   mutate.sh --reset             clear the state file and run the full suite
#   mutate.sh --show              list every mutant with its recorded outcome
#
# The flags compose: `--match zip- --limit 3` runs the next three unrecorded
# zip mutants; `--from ps-empty --limit 5` re-runs five mutants starting at
# ps-empty regardless of recorded state.
#
# Mutation format: "name | sed -i expression | file"

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
BACKUP="$(mktemp -d "${TMPDIR:-/tmp}/minios_mut.XXXXXX")" || exit 1

FROM=""
MATCH=""
LIMIT=""
SHOW=0
RESET=0
STATE_FILE="${MINIOS_MUTATE_STATE:-$HERE/.mutate-state}"

usage() {
    sed -n '2,28p' "$0" | sed 's/^# \{0,1\}//'
    exit "${1:-0}"
}

set -- "$@"
while [ "$#" -gt 0 ]; do
    arg="$1"
    case "$arg" in
        --help|-h) usage 0 ;;
        --show)    SHOW=1; shift ;;
        --reset)   RESET=1; shift ;;
        --from)    FROM="$2"; shift 2 ;;
        --from=*)  FROM="${arg#--from=}"; shift ;;
        --match)   MATCH="$2"; shift 2 ;;
        --match=*) MATCH="${arg#--match=}"; shift ;;
        --limit)   LIMIT="$2"; shift 2 ;;
        --limit=*) LIMIT="${arg#--limit=}"; shift ;;
        --state)   STATE_FILE="$2"; shift 2 ;;
        --state=*) STATE_FILE="${arg#--state=}"; shift ;;
        *) echo "mutate.sh: unknown argument: $arg" >&2; usage 1 ;;
    esac
done

if [ -n "$LIMIT" ]; then
    case "$LIMIT" in
        ''|*[!0-9]*) echo "mutate.sh: --limit must be a positive integer" >&2; exit 1 ;;
    esac
fi

if [ "$RESET" = "1" ]; then
    rm -f "$STATE_FILE"
fi

SOURCES="kernel.c arch/x86/boot/bootdefs.h net/net.c net/tls.c net/tls_x509.c net/rtl8139.c drivers/pcspk.c drivers/rtc.c fs/zip.c fs/ramdisk.c fs/vfs.c fs/kfile.c kernel/redirect.c kernel/syscalls.c kernel/mm/paging.c kernel/shell.c kernel/editor.c vma.c"

restore_sources() {
    local f
    for f in $SOURCES; do
        [ -f "$BACKUP/$f" ] && { mkdir -p "$HERE/$(dirname "$f")"; cp "$BACKUP/$f" "$HERE/$f"; }
    done
}

cleanup() {
    restore_sources
    rm -rf "$BACKUP"
}
trap cleanup EXIT INT TERM

for f in $SOURCES; do
    mkdir -p "$BACKUP/$(dirname "$f")"
    cp "$HERE/$f" "$BACKUP/$f" || exit 1
done

MUTATIONS="
pd-drop-page-size | s/#define PT_FLAGS_PRESENT_RW_PS    0x083/#define PT_FLAGS_PRESENT_RW_PS    0x003/ | arch/x86/boot/bootdefs.h
gdt64-code-to-data | s/#define GDT64_DESC_CODE           0x00209A0000000000/#define GDT64_DESC_CODE           0x0000920000000000/ | arch/x86/boot/bootdefs.h
kernel-buffer-seg | s/#define BOOT_KERNEL_BUF_SEG       0x1000/#define BOOT_KERNEL_BUF_SEG       0x1001/ | arch/x86/boot/bootdefs.h
chunk-copy-length | s/#define SECTOR_DWORD_SHIFT        7/#define SECTOR_DWORD_SHIFT        6/ | arch/x86/boot/bootdefs.h
ramdisk-entry-stride | s/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 8)/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 4)/ | fs/ramdisk.c
redirect-captures-nothing | s/    redir_active = 1;/    redir_active = 0;/ | kernel.c
status-leaks-into-redirect | s/int was = redirect_suspend();/int was = 0;/ | kernel.c
editor-drops-unsaved | s/if (e->dirty) {/if (0) {/ | kernel/editor.c
bin-path-prefix | s/{ \"\",      \"bin\/\" }/{ \"\",      \"bix\/\" }/ | kernel/shell.c
bin-lookup-bypassed | s/    return ramdisk_open(resolved) ? 1 : 0;/    return 0;/ | kernel/shell.c
run-o-dir | s/{ \".o\",    \"objects\/\" }/{ \".o\",    \"objectx\/\" }/ | kernel/shell.c
run-elf-dir | s/{ \".elf\",  \"bin\/\" }/{ \".elf\",  \"bix\/\" }/ | kernel/shell.c
run-cvm-dir | s/{ \".cvm\",  \"cvm\/\" }/{ \".cvm\",  \"cvmx\/\" }/ | kernel/shell.c
cwd-never-applied | s/kmemcpy(out, fs_cwd, kstrlen(fs_cwd) + 1);/kmemcpy(out, \"\", 1);/ | fs/vfs.c
cd-always-fails | s/if (!fs_resolve(argv\\[1\\], resolved, sizeof(resolved))) {/if (1) {/ | kernel/shell.c
rm-missing-passes | s/if (!f) { kprintf(\\\"rm: %s: no such file\\\\n\\\", argv\\[1\\]); return; }/if (0) {/ | kernel/shell.c
rm-dir-accepted | s/if (fs_is_dir(resolved)) {/if (0) {/ | kernel/shell.c
mkdir-dup-passes | s/if (fs_dir_exists(dirname)) {/if (0) {/ | kernel/shell.c
mkdir-parent-bypassed | s/if (!fs_dir_exists(parent)) {/if (0) {/ | kernel/shell.c
cd-exists-bypassed | s/if (!fs_dir_exists(target)) {/if (0) {/ | kernel/shell.c
kfopen-dir-refusal-bypassed | s/if (fs_is_dir(resolved)) return 0;/\\/* dir bypass *\\// | fs/kfile.c
ps-empty | s/kprintf(\\\"  %-12s  %s  %p\\\\n\\\", p->name,/if (0) kprintf(\\\"  %-12s  %s  %p\\\\n\\\", p->name,/ | kernel/shell.c
cat-drops-second-file | s/for (fi = 1; fi < argc; fi++)/for (fi = 1; fi < 2; fi++)/ | kernel/shell.c
append-flag-ignored | s/            \\*append_mode = 1;/            \\*append_mode = 0;/ | kernel/redirect.c
append-mode-acts-like-write | s/((mode\\[0\\] == \\x27a\\x27) ? 2 : 0)/((mode\\[0\\] == \\x27a\\x27) ? 1 : 0)/ | fs/kfile.c
append-resets-pos | s/f->pos  = (f->mode == 2) ? f->rf->size : 0;/f->pos  = 0;/ | fs/kfile.c
trace-print-gated-off | s/if (s_trace_enabled)/if (0) \\&\\& (s_trace_enabled)/ | kernel/syscalls.c
trace-on-never-enables | s/syscall_trace_set(1)/syscall_trace_set(0)/ | kernel/shell.c
arp-cache-never-stored | s/net_arp_cache\\[free\\].valid = 1;/net_arp_cache\\[free\\].valid = 0;/ | net/net.c
arp-reply-ignored | s/net_get16(frame + 20) == NET_ARP_REPLY/net_get16(frame + 20) == 0/ | net/net.c
tx-owner-wait-inverted | s/while (!(rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot \\* 4)) \\& 0x2000)) {/while (rtl_reg32((unsigned short)(RTL_REG_TSD0 + slot \\* 4)) \\& 0x2000) {/ | net/rtl8139.c
tcp-seq-never-advances | s/if (fresh \\&\\& (flags/if (0) { if (fresh \\&\\& (flags/ | net/net.c
tcp-peer-ack-corrupts-ack | s/\\/\\* ACK: peer acks our data \\*\\//s->ack = ack; \\/\\* ACK: peer acks our data \\*\\// | net/net.c
ping-id-mismatched | s/net_put16(req + 4, net_icmp_id)/net_put16(req + 4, net_icmp_id + 1)/ | net/net.c
ip-csum-ignored | s/if (net_checksum(ip, 20) != 0) return;/if (0) return;/ | net/net.c
tcp-ack-not-advanced | s/                    s->ack = s->rx_next;/                    s->ack = s->ack;/ | net/net.c
rx-frame-truncated | s/    for (k = 0; k < n; k++) {/    for (k = 0; k < n - 128; k++) {/ | net/rtl8139.c

nk-frame-not-composited | s/        vga_fb_blit_nk_window();/        if (0) vga_fb_blit_nk_window();/ | kernel/syscalls.c
nk-origin-not-reported | s/            o\\[0\\] = nk_win_x;/            o\\[0\\] = 0;/ | kernel/syscalls.c
nk-mouse-bounds-unchecked | s/        if (!user_range_ok((unsigned long)a1, 4 \\* sizeof(int))) return EFAULT;/        if (0) return EFAULT;/ | kernel/syscalls.c
nk-backbuf-not-mapped | s/        unsigned char \\*buf = (unsigned char \\*)kmalloc(NK_W \\* NK_H);/        unsigned char \\*buf = 0;/ | kernel/mm/paging.c

tls-close-notify-unrecognized | s/if (s->rec_len == 2 \\&\\& s->rec\\[1\\] == 0) {/if (s->rec_len == 2 \\&\\& s->rec\\[1\\] == 1) {/ | net/tls.c
tls-chain-stride | s/TLS_MEMCPY(s->chain + stored, m + pos, cl);/TLS_MEMCPY(s->chain + s->n_certs \\* TLS_CERT_MAX, m + pos, cl);/ | net/tls.c
tls-wildcard-overrun | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len; i++) {/ | net/tls_x509.c
tls-wildcard-short-tail | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len - 2; i++) {/ | net/tls_x509.c

user-pages-supervisor | s/#define PT_FLAGS_USER             0x004/#define PT_FLAGS_USER             0x000/ | arch/x86/boot/bootdefs.h
write-pointer-check-bypassed | s/int user_range_ok(unsigned long p, unsigned long len) {/int user_range_ok(unsigned long p, unsigned long len) { (void)p; (void)len; return 1; \\/\\* bypass \\*\\// | kernel/syscalls.c

vol-default-zero | s/static unsigned pcspk_volume = PCSPK_VOL_DEFAULT;/static unsigned pcspk_volume = 0;/ | drivers/pcspk.c
vol-sign-ignored | s/v \*= sign;/v \*= 1;/ | kernel/shell.c
vol-garbage-accepted | s/if (!shell_parse_vol(argv\\[1\\], &v)) {/if (0) {/ | kernel/shell.c
rtc-always-fails | s/    return 1;/    return 0;/ | drivers/rtc.c

zip-traversal-allowed | s/if (clen == 2 \\&\\& start\\[0\\] == \\x27.\\x27 \\&\\& start\\[1\\] == \\x27.\\x27) return 0;/if (0) return 0;/ | fs/zip.c
zip-bad-magic-accepted | s/if (!mz_zip_reader_init_mem(\\&zip, abuf, (size_t)asize, 0)) {/if (0) {/ | fs/zip.c
zip-writer-never-finalizes | s/if (!fail \\&\\& !mz_zip_writer_finalize_archive(\\&zip)) {/if (!fail \\&\\& 0) {/ | fs/zip.c

vma-del-color-reversion | s/        y->red = z->red;/        y->red = y_orig_red;/ | vma.c
vma-pool-init-broken | s/    vma_pool_n = 0;/    vma_pool_n = VMA_MAX;/ | vma.c
vma-rotate-left-broken | s/    x->right = y->left;/    x->right = y->right;/ | vma.c
vma-find-comparison-inverted | s/        else if (base < x->base) x = x->left;/        else if (base < x->base) x = x->right;/ | vma.c

smp-icr-shorthand-broken | s/LAPIC_ICR_ALL_EXC 0xC0000u/LAPIC_ICR_ALL_EXC 0x30000u/ | smp.c
smp-init-missing | s/lapic_write(LAPIC_ICR_LO, LAPIC_ICR_ALL_EXC \\| LAPIC_ICR_INIT);/lapic_write(LAPIC_ICR_LO, 0);/ | smp.c
smp-sipi-vector-zero | s/SIPI_VECTOR       (AP_STUB_ADDR >> 12)/SIPI_VECTOR       0/ | smp.c
smp-ap-no-lapic-eoi | s/\\*0xFEE000B0UL = 0;/\\*0xFEE000B0UL = 0; \\/* mutant: no eoi \\*/ | kernel/sched.c
smp-bsp-ctx-switch-not-guarded | s/if (this_cpu\\(\\)->is_bsp \\&\\& proc_count > 1)/if (proc_count > 1)/ | kernel/sched.c
smp-gs-base-not-set | s/wrmsr(MSR_GSBASE, (unsigned long)\\&cpus\\[cpu\\]);/\\/* mutant: no gs base \\*/ | smp.c
"

# Parse the mutation table into parallel arrays (preserving order).
NAMES=()
EXPRS=()
FILES=()
mapfile -t LINES <<< "$MUTATIONS"
for line in "${LINES[@]}"; do
    [ -z "$line" ] && continue
    name="${line%%|*}"; name="${name// /}"
    rest="${line#*|}"
    expr="${rest%%|*}"
    file="${rest#*|}"; file="${file// /}"
    NAMES+=("$name"); EXPRS+=("$expr"); FILES+=("$file")
done

# Load recorded progress into an associative array.
declare -A STATE
if [ -f "$STATE_FILE" ]; then
    while read -r n o; do
        [ -n "$n" ] && STATE["$n"]="$o"
    done < "$STATE_FILE"
fi

record() {
    STATE["$1"]="$2"
    echo "$1 $2" >> "$STATE_FILE"
}

# Locate a mutant by name.
find_index() {
    local want="$1" i
    for i in "${!NAMES[@]}"; do
        [ "${NAMES[$i]}" = "$want" ] && { echo "$i"; return 0; }
    done
    echo -1
    return 1
}

if [ "$SHOW" = "1" ]; then
    printf '%-32s %-9s %s\n' "name" "outcome" "file"
    for i in "${!NAMES[@]}"; do
        printf '%-32s %-9s %s\n' "${NAMES[$i]}" "${STATE[${NAMES[$i]}]:-}" "${FILES[$i]}"
    done
    exit 0
fi

# Determine the starting point.
START=0
if [ -n "$FROM" ]; then
    START="$(find_index "$FROM")" || { echo "mutate.sh: --from '$FROM': no such mutant" >&2; exit 1; }
else
    while [ "$START" -lt "${#NAMES[@]}" ] && [ -n "${STATE[${NAMES[$START]}]:-}" ]; do
        START=$((START + 1))
    done
fi

KILLED=0
SURVIVED=0
BROKEN=0
RUN=0

if [ "$FROM" = "" ]; then
    if [ "$START" -lt "${#NAMES[@]}" ]; then
        echo "resuming: ${#NAMES[@]} mutants, ${START} already recorded, running from '${NAMES[$START]}'"
    else
        echo "all ${#NAMES[@]} mutants already recorded; use --from NAME or --reset to re-run"
    fi
else
    echo "running from '${NAMES[$START]}' (index ${START}) ignoring recorded state"
fi

for (( i = START; i < ${#NAMES[@]}; i++ )); do
    name="${NAMES[$i]}"; expr="${EXPRS[$i]}"; file="${FILES[$i]}"

    if [ -z "$FROM" ] && [ -n "${STATE[$name]:-}" ]; then
        continue        # already recorded: skip on a plain resume
    fi
    if [ -n "$MATCH" ] && ! [[ "$name" =~ $MATCH ]]; then
        continue
    fi
    if [ -n "$LIMIT" ] && [ "$RUN" -ge "$LIMIT" ]; then
        break
    fi
    RUN=$((RUN + 1))

    restore_sources
    if ! eval "sed -i '$expr' '$HERE/$file'" 2>/dev/null; then
        echo "MUTANT $name: ERROR (sed failed)"
        record "$name" BROKEN
        BROKEN=$((BROKEN + 1))
        continue
    fi
    if cmp -s "$BACKUP/$file" "$HERE/$file"; then
        echo "MUTANT $name: ERROR (expression matched nothing)"
        record "$name" BROKEN
        BROKEN=$((BROKEN + 1))
        continue
    fi

    if ! make -C "$HERE" > "$BACKUP/build.log" 2>&1; then
        echo "MUTANT $name: KILLED (build failure)"
        record "$name" KILLED
        KILLED=$((KILLED + 1))
        continue
    fi

    case "$file" in
        net/tls.c|net/tls_x509.c|tls_crypto.c|tls.h)
            make -C "$HERE" test-tls > "$BACKUP/suite.log" 2>&1
            ;;
        vma.c)
            make -C "$HERE" test-vma > "$BACKUP/suite.log" 2>&1
            ;;
        *)
            FAIL_FAST=1 "$HERE/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
    esac
    if [ $? -eq 0 ]; then
        echo "MUTANT $name: SURVIVED (test gap!)"
        sed -n 's/^=== summary/    suite: summary/p' "$BACKUP/suite.log"
        record "$name" SURVIVED
        SURVIVED=$((SURVIVED + 1))
    else
        echo "MUTANT $name: KILLED"
        record "$name" KILLED
        KILLED=$((KILLED + 1))
    fi
done

restore_sources
make -C "$HERE" > "$BACKUP/build.log" 2>&1

# Count how many are still unrecorded.
REMAINING=0
for i in "${!NAMES[@]}"; do
    [ -z "${STATE[${NAMES[$i]}]:-}" ] && REMAINING=$((REMAINING + 1))
done

echo ""
echo "=== this run: $KILLED killed, $SURVIVED survived, $BROKEN broken ==="
echo "=== $REMAINING of ${#NAMES[@]} mutants remain unrecorded ==="
if [ "$REMAINING" -gt 0 ]; then
    echo "    resume with: $0"
fi
if [ "$BROKEN" -gt 0 ]; then
    echo "A broken mutant never reached the suite; fix its expression."
    exit 1
fi
if [ "$SURVIVED" -gt 0 ]; then
    echo "A surviving mutant means the suite does not cover that behavior."
    exit 1
fi
if [ "$REMAINING" -gt 0 ] && [ -z "$FROM" ] && [ -z "$LIMIT" ] && [ -z "$MATCH" ]; then
    exit 0
fi
exit 0