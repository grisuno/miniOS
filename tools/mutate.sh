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

HERE="$(cd "$(dirname "$0")/.." && pwd)"
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

SOURCES="kernel.c headers/arch/x86/boot/bootdefs.h net/net.c net/tls.c net/tls_x509.c net/rtl8139.c drivers/virtio_net.c drivers/pcspk.c drivers/rtc.c fs/zip.c fs/ramdisk.c fs/vfs.c fs/kfile.c kernel/redirect.c kernel/syscalls.c kernel/mm/paging.c kernel/shell.c kernel/editor.c vma.c headers/pipe.h headers/panic.h kernel/clip.c kernel/mm/cow.c arch/x86/ctx_sw.S drivers/virtio_blk.c drivers/nvme.c drivers/block.c headers/drivers/pci.h boot/uefi_stub.c"
SOURCES="$SOURCES smp.c kernel/sched.c fs/minifs.c kernel/console.c headers/rtc.h headers/sanitize.h"
# Every file a MUTATIONS entry touches MUST be listed here: restore_sources
# backs these up before the run and restores after each mutant. A file
# missing here keeps its mutation (the fpu-no-save residue disabled
# fxsave/fxrstor in the tree for days and poisoned every later boot).
SOURCES="$SOURCES arch/x86/ctx_sw.S arch/x86/syscall_entry.S progs/minios_abi.h headers/ktime.h headers/randmix.h headers/sched.h progs/src/mthreads.h"
SOURCES="$SOURCES progs/src/freedom_wl.c progs/vedit/vedit.c"
SOURCES="$SOURCES progs/freedomui/freedomui_minios.c tests/test_freedomui.c"
SOURCES="$SOURCES progs/freedomui/ps2_keymap.c tests/test_ps2_keymap.c progs/freedomui/platform_minios.c"
# Mechanism: SOURCES is the backup/restore allowlist, not documentation.
# Every file named by the mutation table MUST appear here, or a mutant
# applied to it is never restored and leaks into the tree (and stacks
# under the next mutant, whose kill is then vacuous). This bit paint
# when progs/paint/paint.c shipped mutants without a SOURCES entry.
SOURCES="$SOURCES progs/paint/paint.c tests/test_paint.c"
SOURCES="$SOURCES drivers/pcm2.c headers/pcm2.h headers/pcm_ring.h tests/test_pcm.c progs/quake2generic/snddma_minios.c"
SOURCES="$SOURCES progs/nk_palette.h progs/wl/wl_mini.h progs/wl/wl_mbox.h progs/wl/wlcomp.c"
SOURCES="$SOURCES progs/minicraft/minicraft.c"
# Backup/restore completeness (2026-09 audit): every mutation-target
# file must appear here or its mutants leak and stack. futex/batch/
# rcu/percpu/lisp predated the allowlist and their kills were vacuous
# for a whole run; httpd.h shipped its own mutants without an entry.
SOURCES="$SOURCES kernel/futex.c kernel/percpu_rq.c kernel/batch.c kernel/rcu.c"
SOURCES="$SOURCES progs/src/lxabi.c tools/mkfs.minifs.py tools/minifs_fsck.py"
SOURCES="$SOURCES kernel/proc_sec.c kernel/seccomp_bpf.c progs/src/lxsecc.c"
SOURCES="$SOURCES progs/lisp/lisp.c headers/httpd.h"
SOURCES="$SOURCES kernel/vga_fx.c kernel/vga_fb.c headers/vga_fx.h tests/test_fx.c"
# gfxview-* rows (graphics view contract) target the header, the
# compositor and the zoom syscall; the latter two are listed above.
SOURCES="$SOURCES headers/wm_gfxview.h tests/test_wm.c"
# execve row targets syscalls_proc.c (the proc-leaf TU split from
# syscalls.c after the allowlist audits); loader.c and exec.c ride
# along as the ASLR/execve-adjacent surface for future rows. A missing
# entry leaked execve-never-replaces into the tree (rc = -38 shipped
# in os.img), caught by the anchor checker, never by review.
SOURCES="$SOURCES kernel/syscalls_proc.c kernel/loader.c kernel/exec.c kernel/ldso_parse.c"
SOURCES="$SOURCES kernel/spawn.c kernel/mm/tlb.c arch/x86/tlb_nmi.S"
# ldso-* rows target the pure dynamic-table parser (kernel/ldso_parse.c,
# host-pinned by make test-ldso) and its kernel glue (kernel/loader.c);
# the BDD dynamic scenarios are the guest kill. headers/ldso.h and
# headers/kernel.h carry the contract but no mutable logic.
SOURCES="$SOURCES headers/ldso.h headers/kernel.h"
SOURCES="$SOURCES fs/fat32.c fs/ext4.c"

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
pd-drop-page-size | s/#define PT_FLAGS_PRESENT_RW_PS    0x083/#define PT_FLAGS_PRESENT_RW_PS    0x003/ | headers/arch/x86/boot/bootdefs.h
gdt64-code-to-data | s/#define GDT64_DESC_CODE           0x00209A0000000000/#define GDT64_DESC_CODE           0x0000920000000000/ | headers/arch/x86/boot/bootdefs.h
kernel-buffer-seg | s/#define BOOT_KERNEL_BUF_SEG       0x1000/#define BOOT_KERNEL_BUF_SEG       0x1001/ | headers/arch/x86/boot/bootdefs.h
chunk-copy-length | s/#define SECTOR_DWORD_SHIFT        7/#define SECTOR_DWORD_SHIFT        6/ | headers/arch/x86/boot/bootdefs.h
ramdisk-entry-stride | s/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 16)/#define RD_ENTRY_SIZE  (RAMDISK_FNAME_LEN + 8)/ | fs/ramdisk.c
ramdisk-deflate-ignored | s/if (fflg \& RD_FLAG_DEFLATE) {/if (0) {/ | fs/ramdisk.c
redirect-captures-nothing | s/    redir_active = 1;/    redir_active = 0;/ | kernel/console.c
status-leaks-into-redirect | s/int was = redirect_suspend();/int was = 0;/ | kernel/redirect.c
editor-drops-unsaved | s/if (e->dirty) {/if (0) {/ | kernel/editor.c
bin-path-prefix | s/{ \"\",      \"bin\/\" }/{ \"\",      \"bix\/\" }/ | kernel/shell.c
bin-lookup-bypassed | s/    return ramdisk_open(resolved) ? 1 : 0;/    return 0;/ | kernel/shell.c
run-o-dir | s/{ \".o\",    \"objects\/\" }/{ \".o\",    \"objectx\/\" }/ | kernel/shell.c
run-elf-dir | s/{ \".elf\",  \"bin\/\" }/{ \".elf\",  \"bix\/\" }/ | kernel/shell.c
run-cvm-dir | s/{ \".cvm\",  \"cvm\/\" }/{ \".cvm\",  \"cvmx\/\" }/ | kernel/shell.c
cwd-never-applied | s/kmemcpy(out, fs_cwd, kstrlen(fs_cwd) + 1);/kmemcpy(out, \"\", 1);/ | fs/vfs.c
cd-always-fails | s/if (!shell_resolve_arg(\\\"cd\\\"/if (1 || !shell_resolve_arg(\\\"cd\\\"/ | kernel/shell.c
rm-missing-passes | s/kprintf(\\\"%s: %s: %s\\\\n\\\", cmd, arg, reason);/kprintf(\\\"removed %s\\\\n\\\", arg);/ | kernel/shell.c
rm-dir-accepted | s/if (fs_is_dir(resolved)) {/if (0) {/ | kernel/shell.c
mkdir-dup-passes | s/if (fs_dir_exists(dirname)) {/if (0) {/ | kernel/shell.c
mkdir-parent-bypassed | s/if (!fs_dir_exists(parent)) {/if (0) {/ | kernel/shell.c
cd-exists-bypassed | s/if (!fs_dir_exists(target)) {/if (0) {/ | kernel/shell.c
kfopen-dir-refusal-bypassed | s/if (fs_is_dir(resolved)) { kerrno = EISDIR; return 0; }/if (0) {}/ | fs/kfile.c
ps-empty | s/kprintf(\\\"  pid  ppid state name\\\\n\\\");/kprintf(\\\"  pid  ppid state name\\\\n\\\"); n = 0;/ | kernel/shell.c
cat-drops-second-file | s/for (fi = 1; fi < argc; fi++)/for (fi = 1; fi < 2; fi++)/ | kernel/shell.c
append-flag-ignored | s/            \\*append_mode = 1;/            \\*append_mode = 0;/ | kernel/redirect.c
append-mode-acts-like-write | s/((mode\\[0\\] == \\x27a\\x27) ? 2 : 0)/((mode\\[0\\] == \\x27a\\x27) ? 1 : 0)/ | fs/kfile.c
append-resets-pos | s/if (f->mode == 2) {/if (0) {/ | fs/kfile.c
trace-print-gated-off | s/int show = s_trace_enabled \&\& !trace_is_noisy(n);/int show = 0;/ | kernel/syscalls.c
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
nk-origin-not-reported | s/            vga_fb_gfx_origin(\&o\\[0\\], \&o\\[1\\]);/            o[0] = 0; o[1] = 0;/ | kernel/syscalls.c
nk-mouse-bounds-unchecked | s/    SANITIZE_RANGE(a1, 4 \\* sizeof(int));/    (void)a1;/ | kernel/syscalls.c
nk-backbuf-not-mapped | s/        buf = mm_page_aligned_alloc(NK_W \\* NK_H, \\&phys);/        buf = 0;/ | kernel/mm/paging.c

tls-close-notify-unrecognized | s/if (s->rec_len == 2 \\&\\& s->rec\\[1\\] == 0) {/if (s->rec_len == 2 \\&\\& s->rec\\[1\\] == 1) {/ | net/tls.c
tls-chain-stride | s/TLS_MEMCPY(s->chain + stored, m + pos, cl);/TLS_MEMCPY(s->chain + s->n_certs \\* TLS_CERT_MAX, m + pos, cl);/ | net/tls.c
tls-wildcard-overrun | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len; i++) {/ | net/tls_x509.c
tls-wildcard-short-tail | s/    for (i = 0; i < name_len - 1; i++) {/    for (i = 0; i < name_len - 2; i++) {/ | net/tls_x509.c

user-pages-supervisor | s/#define PT_FLAGS_USER             0x004/#define PT_FLAGS_USER             0x000/ | headers/arch/x86/boot/bootdefs.h
write-pointer-check-bypassed | s/int user_range_ok(unsigned long p, unsigned long len) {/int user_range_ok(unsigned long p, unsigned long len) { (void)p; (void)len; return 1; \\/\\* bypass \\*\\// | kernel/syscalls.c

vol-default-zero | s/static unsigned pcspk_volume = PCSPK_VOL_DEFAULT;/static unsigned pcspk_volume = 0;/ | drivers/pcspk.c
vol-sign-ignored | s/if (\*s == '-') { neg = 1; s++; }/if (*s == '-') { neg = 0; s++; }/ | kernel/shell.c
vol-garbage-accepted | s/if (!shell_parse_vol(argv\\[1\\], &v)) {/if (0) {/ | kernel/shell.c
kill-wait-garbage-accepted | s/if (!shell_parse_pid(argv\\[1\\], 1, &pid)) {/if (0) {/ | kernel/shell.c
mv-rename-silenced | s/r = fs_rename(src, dst);/r = -2;/ | kernel/shell.c
tab-minifs-arg-dropped | s/if (ncomps < 32)/if (0)/ | kernel/shell.c
execve-never-replaces | s/rc = do_execve(resolved, kargc, kargv);/rc = -38;/ | kernel/syscalls_proc.c
aslr-no-entropy | s/return t ^ (aslr_counter \* 0xBF58476D1CE4E5FUL);/return 0;/ | kernel/sched.c
fat-lfn-check-inverted | s/if (de\[11\] == 0x0F) return 0;/if (de[11] != 0x0F) return 0;/ | fs/fat32.c
fat-dev-never-found | s/fat_dev_cached = (long)base;/fat_dev_cached = -2;/ | fs/fat32.c
ext4-magic-unchecked | s/if (ext_ld16(sb + 56) != EXT4_MAGIC) return -1;/if (0) return -1;/ | fs/ext4.c
ext4-dev-never-found | s/ext_dev_cached = (long)base;/ext_dev_cached = -2;/ | fs/ext4.c
rlimit-garbage-accepted | s/if (!shell_parse_long(argv\\[2\\], &lv) || lv < 0) {/if (0) {/ | kernel/shell.c
sleep-garbage-accepted | s/if (!shell_parse_long(argv\\[1\\], &sv)) {/if (0) {/ | kernel/shell.c
rtc-always-fails | s/    return 1;/    return 0;/ | drivers/rtc.c
pcm-ring-drops-lost | s/r->drops += (unsigned long)(len - space);/r->drops += 0;/ | headers/pcm_ring.h
pcm-ring-pad-zero | s/for (j = taken; j < len; j++) dst\[j\] = 0x80;/for (j = taken; j < len; j++) dst[j] = 0x00;/ | headers/pcm_ring.h
pcm-ring-wrap-broken | s/if (r->head >= r->cap) r->head = 0;/if (r->head > r->cap) r->head = 0;/ | headers/pcm_ring.h
pcm-ring-underrun-lost | s/r->underruns++;/r->underruns += 0;/ | headers/pcm_ring.h
pcm2-open-always-busy | s/    if (pcm2_on) {/    if (1) {/ | drivers/pcm2.c
pcm2-write-always-zero | s/        chunk = len - accepted;/        chunk = 0;/ | drivers/pcm2.c
pcm2-close-no-release | s/    pcm2_release_locked();/    ;/ | drivers/pcm2.c
q2snd-init-false | s/    if (sys_pcm2_open(MINIOS_PCM2_NONBLOCK) < 0) {/    if (1) {/ | progs/quake2generic/snddma_minios.c
q2snd-rate-wrong | s/    dma.speed = Q2SND_RATE;/    dma.speed = 11025;/ | progs/quake2generic/snddma_minios.c
q2snd-submit-nopush | s/    q2_dma_push((int)horizon);/    ;/ | progs/quake2generic/snddma_minios.c

zip-traversal-allowed | s/if (clen == 2 \\&\\& start\\[0\\] == \\x27.\\x27 \\&\\& start\\[1\\] == \\x27.\\x27) return 0;/if (0) return 0;/ | fs/zip.c
zip-bad-magic-accepted | s/if (!mz_zip_reader_init_mem(\\&zip, abuf, (size_t)asize, 0)) {/if (0) {/ | fs/zip.c
zip-writer-never-finalizes | s/if (!fail \\&\\& !mz_zip_writer_finalize_archive(\\&zip)) {/if (!fail \\&\\& 0) {/ | fs/zip.c

vma-del-color-reversion | s/        y->red = z->red;/        y->red = y_orig_red;/ | vma.c
vma-pool-init-broken | s/    vma_pool_n = 0;/    vma_pool_n = VMA_MAX;/ | vma.c
vma-rotate-left-broken | s/    x->right = y->left;/    x->right = y->right;/ | vma.c
vma-find-comparison-inverted | s/        else if (base < x->base) x = x->left;/        else if (base < x->base) x = x->right;/ | vma.c
pipe-empty-eof-confused | s/    return r->wopen ? PIPE_EMPTY : 0;/    return 0;/ | headers/pipe.h
pipe-write-count-lost | s/        r->count++;/        r->count += 0;/ | headers/pipe.h
pipe-init-unbounded | s/    if (cap == 0u || cap > PIPE_CAP_MAX)/    if (cap == 0u)/ | headers/pipe.h
pipe-close-never | s/    r->wopen = 0;/    r->wopen = 1;/ | headers/pipe.h
pipe-empty-stage-accepted | s/            if (sargc == 0) {/            if (0) {/ | kernel/shell.c
panic-null-ret-continues | s/        if (ret == 0u)/        if (0)/ | headers/panic.h
panic-max-never-clamps | s/        max = PANIC_BT_MAX;/        max = 0;/ | headers/panic.h
panic-valid-unchecked | s/        if (!valid(rbp) || !valid(rbp + 8u))/        if (0)/ | headers/panic.h
vfs-first-match-wins | s/            if (plen > best_len || best < 0) {/            if (best < 0) {/ | fs/vfs.c
vfs-busy-unmount-allowed | s/                return -16;/                return 0;/ | fs/vfs.c
vfs-root-unmountable | s/    if (!prefix\[0\]) return -22;/    if (0) return -22;/ | fs/vfs.c
schedtop-threads-unlabeled | s/  pid  tgid T\/P ppid/  pid  tgid ppid/ | kernel/sched.c
httpd-traversal-accepted | s/            if (path_out\[k\] == '.' && path_out\[k + 1u\] == '.')/            if (0)/ | headers/httpd.h
httpd-length-unreported | s/Content-Length: /X-Length: / | headers/httpd.h
httpd-syn-ignored | s/        if ((seg\[13\] & 0x12) != 0x02) return;/        if ((seg[13] \& 0x12) != 0x03) return;/ | net/net.c
httpd-ack-unchecked | s/            if ((flags & 0x12) == 0x10 && ack == s->seq) {/            if ((flags \& 0x12) == 0x10) {/ | net/net.c
clip-store-dropped | s/    clip_valid = 1;/    clip_valid = 0;/ | kernel/clip.c
clip-empty-accepted | s/    if (!clip_valid || clip_len == 0u) return -1;/    if (0) return -1;/ | kernel/clip.c
fork-child-nonzero | s/        xorl    %eax, %eax/        incl    %eax/ | arch/x86/ctx_sw.S
fork-share-dropped | s/        cpt\[(va >> 12) & 0x1FF\] = phys | PT_USER_RO | flags;/        cpt[(va >> 12) \& 0x1FF] = 0;/ | kernel/mm/cow.c
fork-resolve-never | s/            resolved = cow_resolve(cur_cr3, fault_addr);/            resolved = -1;/ | kernel/sched.c
fd-fork-shares-view | s/    if (!kfd_view_copy(child, cur)) {/    kfd_view_share(child); if (0) {/ | kernel/sched.c
pci-find-first-only | s/    for (dev = 0; dev < PCI_MAX_DEV; dev++)/    for (dev = 0; dev < 1; dev++)/ | headers/drivers/pci.h
vblk-status-unchecked | s/statusp != 0/statusp == 0/ | drivers/virtio_blk.c
nvme-class-wrong | s/#define NVME_CLASS_PI 0x02u/#define NVME_CLASS_PI 0x03u/ | drivers/nvme.c
nvme-present-inverted | s/return xnv_on;/return !xnv_on;/ | drivers/nvme.c
nvme-nsid-zero | s/#define NVME_NSID 1u/#define NVME_NSID 0u/ | drivers/nvme.c
nvme-opcode-read-wrong | s/#define NVME_OPC_READ 0x02u/#define NVME_OPC_READ 0x03u/ | drivers/nvme.c
net6-branch-misclassified | s/if (etype == NET_ETHERTYPE_IPV6)/if (etype == NET_ETHERTYPE_IP)/ | net/net.c
vnet-never-preferred | s/net_use_virtio = vnet_init() ? 1 : 0;/net_use_virtio = 0;/ | net/net.c
mmap-file-off-dropped | s/mmap_tag_file(user_mmap_cur, fino, foff)/mmap_tag_file(user_mmap_cur, fino, 0)/ | kernel/syscalls.c
mmap-file-anon-fallback | s/if (!(mflags \\& (unsigned long)LINUX_MAP_ANONYMOUS)) {/if (0) {/ | kernel/syscalls.c
pcache-shared-not-ro | s/mm_user_map_page(cr3, va, (unsigned long)pg, 0, 0)/mm_user_map_page(cr3, va, (unsigned long)pg, 1, 0)/ | kernel/mm/paging.c
pcache-break-dropped | s/resolved = mm_file_break(cur_cr3, fault_addr);/resolved = -1;/ | kernel/sched.c
vnet-rx-not-writable | s/VNET_RX_SIZE, VNET_DESC_WRITE, 0u);/VNET_RX_SIZE, 0u, 0u);/ | drivers/virtio_net.c
vnet-tx-kick-wrong-queue | s/(unsigned short)VNET_Q_TX);/(unsigned short)VNET_Q_RX);/ | drivers/virtio_net.c
vfs-readdir-mem-subdir-allowed | s/if (\*path != 0) return -1;/if (0) return -1;/ | fs/vfs.c
errno-open-noent-dropped | s/kerrno = ENOENT; return 0;/kerrno = 0; return 0;/ | fs/kfile.c
errno-symbol-unregistered | s/k_register_symbol(\"errno\",    (void \*)&kerrno);/k_register_symbol(\"enoda\",    (void \*)&kerrno);/ | kernel/console.c
vfs-readdir-minifs-notdir-allowed | s/if (!(st.mode & MINIFS_S_IFDIR)) return -20;/if (0) return -20;/ | fs/vfs.c
vfs-readdir-ramdisk-dedupe-dropped | s/if (dup) continue;/if (0) continue;/ | fs/vfs.c
mprotect-write-unenforced | s/if (want_write) pte |= (unsigned long)0x002;/if (0) pte |= (unsigned long)0x002;/ | kernel/syscalls.c
mprotect-exec-unenforced | s/if (!want_exec) pte |= (unsigned long)PT_FLAGS_NX;/if (1) pte |= (unsigned long)PT_FLAGS_NX;/ | kernel/syscalls.c
mprotect-align-unchecked | s/if (base & 0xFFFUL) return -22;/if (0) return -22;/ | kernel/syscalls.c
mprotect-prot-unchecked | s/if (prot & ~(unsigned long)7) return -22;/if (0) return -22;/ | kernel/syscalls.c
blk-virtio-never-preferred | s/            block_use_virtio = 1;/            block_use_virtio = 0;/ | drivers/block.c
blk-virtio-size-gate-dropped | s/if (ide_total == 0 || vblk_total == (unsigned long)ide_total)/if (ide_total == 0 || vblk_total != (unsigned long)ide_total)/ | drivers/block.c
uefi-blk-guid-wrong | s/0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B/0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3C/ | boot/uefi_stub.c
uefi-sfs-guid-wrong | s/0x22, 0x5B, 0x4E, 0x96, 0x59, 0x64/0x22, 0x5B, 0x4E, 0x96, 0x58, 0x64/ | boot/uefi_stub.c
uefi-kernel-name-wrong | s/L\"kernel.bin\"/L\"kernel.binx\"/ | boot/uefi_stub.c
uefi-errbit-dropped | s/0x8000000000000005ULL/5/ | boot/uefi_stub.c
uefi-tramp-cs-wrong | s/0x6A, 0x08, 0xB8/0x6A, 0x10, 0xB8/ | boot/uefi_stub.c
uefi-pt-flags-nops | s/| 0x83u/| 0x03u/ | boot/uefi_stub.c
uefi-gdt-code-data | s/0x00209A0000000000ULL/0x0020920000000000ULL/ | boot/uefi_stub.c
uefi-lba-sig-ignored | s/sec\[510\] == 0x55/sec[510] != 0x55/ | boot/uefi_stub.c
uefi-mmap-unchecked | s/puts_both(\"uefi: mmap entries=\");/;/ | boot/uefi_stub.c
wl-clip-size-unbounded | s/|| n > (unsigned)WL_CLIP_MAX)/|| n > 999999u)/ | progs/wl/wl_mini.h
wl-clip-trunc-unchecked | s/    if (len < 0 || (unsigned)len < total)/    if (0)/ | progs/wl/wl_mini.h

smp-icr-shorthand-broken | s/LAPIC_ICR_ALL_EXC 0xC0000u/LAPIC_ICR_ALL_EXC 0x30000u/ | smp.c
smp-init-missing | s/LAPIC_ICR_INIT);/0);/ | smp.c
smp-sipi-vector-zero | s/SIPI_VECTOR       (AP_STUB_ADDR >> 12)/SIPI_VECTOR       0/ | smp.c
smp-ap-no-lapic-eoi | s/            hal_lapic_eoi();/            \/* mutant: no eoi *\// | kernel/sched.c
smp-bsp-ctx-switch-not-guarded | s/if (cpu->is_bsp \&\& proc_count > 1)/if (proc_count > 1)/ | kernel/sched.c
smp-gs-base-not-set | s/wrmsr(MSR_GSBASE, (unsigned long)\\&cpus\\[cpu\\]);/\\/* mutant: no gs base \\*/ | smp.c
poll-host-order | s/kmemcpy(\&events, entry + 4, 2);/events = net_get16((const unsigned char *)entry + 4);/ | net/net.c
rlimit-as-shell-ignored | s/if (kstrcmp(argv\[1\], \"as\") == 0) rp->rl_as_max = v;/if (kstrcmp(argv[1], \"as\") == 0) rp->rl_as_max = 0;/ | kernel/shell.c
lapic-cal-fallback | s/lapic_cal_valid = 1;/lapic_cal_valid = 0;/ | smp.c
ap-sse-disabled | s/^    cpu_enable_sse();$/    (void)0;/ | smp.c
idle-cr3-stale | s/ctx.cr3 = sched_idle_cr3;/ctx.cr3 = read_cr3();/ | kernel/sched.c
tlb-shootdown-skipped | s/    if (!tlb_others_on(cr3)) return;/    return;/ | kernel/mm/tlb.c
tlb-nmi-no-ack | s/        lock incl tlb_shoot_acks(%rip)/        nop/ | arch/x86/tlb_nmi.S
futex-wait-no-forget | s/    futex_forget(current_pid);/    (void)0;/ | kernel/futex.c
futex-wake-keeps-dead | s/        if (procs\[pid\].state != PROC_BLOCKED) {/        if (0) {/ | kernel/futex.c
futex-value-check-inverted | s/if (\\*(volatile int \\*)uaddr != val)/if (*(volatile int *)uaddr == val)/ | kernel/futex.c
futex-wake-count-unbounded | s/while (pid != WQ_NONE \\&\\& woken < n \\&\\& steps++ < MAX_PROCS)/while (pid != WQ_NONE \\&\\& steps++ < MAX_PROCS)/ | kernel/futex.c
futex-linux-private-unmasked | s/    cmd = op \& ~(long)(LINUX_FUTEX_PRIVATE_FLAG | LINUX_FUTEX_CLOCK_REALTIME);/    cmd = op \& ~(long)LINUX_FUTEX_CLOCK_REALTIME;/ | kernel/futex.c
futex-linux-wake-dropped | s/    if (cmd == LINUX_FUTEX_WAIT || cmd == LINUX_FUTEX_WAKE ||/    if (cmd == LINUX_FUTEX_WAIT ||/ | kernel/futex.c
rtc-epoch-day-off-by-one | s/return era \\* 146097 + doe - 719468;/return era \\* 146097 + doe - 719467;/ | headers/rtc.h
percpu-rq-full-drop-lost | s/if (rqueues\\[cpu\\].count >= RQ_DEPTH)/if (rqueues[cpu].count > RQ_DEPTH)/ | kernel/percpu_rq.c
batch-completion-off-by-one | s/\\*completed = i + 1;/\\*completed = i;/ | kernel/batch.c
rcu-grace-shortened | s/if (rcu_state.pending\\[i\\].epoch < rcu_state.epoch)/if (rcu_state.pending[i].epoch <= rcu_state.epoch)/ | kernel/rcu.c
sanitize-neg-check-dropped | s/if ((count) < 0) return EFAULT;/if (0) return EFAULT;/ | headers/sanitize.h
sanitize-wrap-check-dropped | s/if (_sz \\/ _es != _n) return EFAULT;/if (0) return EFAULT;/ | headers/sanitize.h

lisp-add-overflow-unchecked | s/if (__builtin_add_overflow(v\[0\]->as.num, v\[1\]->as.num, \&out)) {/if (0) {/ | progs/lisp/lisp.c
lisp-div-zero-unchecked | s/    if (b == 0) {/    if (0) {/ | progs/lisp/lisp.c
lisp-num-format-prefix | s/fprintf(rt->out, \"%\" PRId64, node->as.num);/fprintf(rt->out, \"%%\" PRId64, node->as.num);/ | progs/lisp/lisp.c
lisp-true-unbound | s/    env_bind(rt, env, rt->true_value, rt->true_value);/    (void)rt;/ | progs/lisp/lisp.c
lisp-unbound-silent | s/result = value ? value : make_error(rt, \"unbound symbol\");/result = value ? value : rt->nil;/ | progs/lisp/lisp.c
lisp-error-message-nil | s/return make_str(rt, v\[0\]->as.error ? v\[0\]->as.error : \"unknown\");/return rt->nil;/ | progs/lisp/lisp.c
lisp-exit-code-zero | s/        exit(status);/        exit(0);/ | progs/lisp/lisp.c

abi-flock-back-to-74 | s/#define MINIOS_SYS_FLOCK        73/#define MINIOS_SYS_FLOCK        74/ | progs/minios_abi.h
abi-fsync-claims-73 | s/#define MINIOS_SYS_FSYNC        74/#define MINIOS_SYS_FSYNC        73/ | progs/minios_abi.h
abi-statx-back-to-267 | s/#define MINIOS_SYS_STATX       332/#define MINIOS_SYS_STATX       267/ | progs/minios_abi.h
abi-robust-back-to-301 | s/#define MINIOS_SYS_SET_ROBUST_LIST 273/#define MINIOS_SYS_SET_ROBUST_LIST 301/ | progs/minios_abi.h
truth-gettid-returns-one | s/return (long)current_pid;/return 1;/ | kernel/syscalls.c
truth-getrandom-count-zero | s/return (long)cnt;/return 0;/ | kernel/syscalls.c
truth-gettimeofday-usec-zero | s/tv\\[1\\] = total % 1000000UL;/tv[1] = 0;/ | kernel/syscalls.c
fpu-no-save | s/fxsave  (%rax)/\\/* mutant: no save *\\// | arch/x86/ctx_sw.S
fpu-no-restore | s/fxrstor (%rax)/\\/* mutant: no restore *\\// | arch/x86/ctx_sw.S
fsbase-restore-corrupted | s/movq    320(%rax), %rax/movq    320(%rax), %rdx/ | arch/x86/ctx_sw.S
fpu-preempt-no-save | s/if (cur->fpu_save) fpu_save_to(cur->fpu_save);/if (0) {}/ | kernel/sched.c
fpu-mxcsr-zero | s/a\\[FPU_MXCSR_OFF\\] = (unsigned char)(FPU_MXCSR_DEFAULT & 0xFF);/a[FPU_MXCSR_OFF] = 0;/ | kernel/sched.c
fpu-cw-single | s/a\\[0\\] = 0x7F; a\\[1\\] = 0x03;/a[0] = 0; a[1] = 0;/ | kernel/sched.c
sched-imulq-stale | s/imulq \$SYSCALL_PROC_T_SIZE, %rax/imulq \$304, %rax/ | arch/x86/syscall_entry.S
sched-park-rip-zero | s/movq    8(%rbp), %rcx/movq    \$0, %rcx/ | arch/x86/ctx_sw.S
sched-park-rbp-zero | s/movq    (%rbp), %rcx/movq    \$0, %rcx/ | arch/x86/ctx_sw.S
mthreads-stack-no-adjust | s/(mthread_stacks\\[i\\] + MTHREAD_STACK_SZ) - 8;/(mthread_stacks[i] + MTHREAD_STACK_SZ);/ | progs/src/mthreads.h
ktime-us-factor | s/\\* 1000UL +/ * 100UL +/ | headers/ktime.h
randmix-constant | s/return x ^ (x >> 31);/return 0;/ | headers/randmix.h
clock-backwards | s/(w2 >= w1 \&\& m2 >= m1) ? \"monotonic\" : \"BACKWARDS\"/(w2 >= w1 \&\& m2 >= m1) ? \"BACKWARDS\" : \"monotonic\"/ | kernel/shell.c
truth-uname-fails | s/\[63\]  = { sys_linux_uname,        \"uname\" },/[63]  = { 0, \"uname\" },/ | kernel/syscalls.c
freedom-wl-clip-origin-sign | s/\*w += \*x;/\*w -= *x;/ | progs/src/freedom_wl.c
freedom-wl-https-port | s/*port = c->port_https;/*port = c->port_http;/ | progs/src/freedom_wl.c
freedom-wl-title-bound-lost | s/if (n < 0L || n > c->title_max) {/if (n < 0L) {/ | progs/src/freedom_wl.c
freedom-wl-keysym-enter-lost | s/if (make == 0x1CL) {/if (make == 0x1DL) {/ | progs/src/freedom_wl.c
freedomui-omnibox-kind-flip | s/if (kind != 0) {/if (kind != 1) {/ | progs/freedomui/freedomui_minios.c
lxabi-fork-regs-lost | s/        if (sf) ctx_from_frame(\&child->ctx, sf);/        (void)sf;/ | kernel/sched.c
lxabi-thread-tgid-lost | s/    child->tgid = cur->autoreap ? cur->tgid : current_pid;/    child->tgid = pid;/ | kernel/sched.c
lxabi-thread-settls-lost | s/    child->fsbase = (flags \& LINUX_CLONE_SETTLS) ? (uint64_t)tls : rdmsr(MSR_FSBASE);/    child->fsbase = rdmsr(MSR_FSBASE);/ | kernel/sched.c
lxabi-cleartid-lost | s/        \*(volatile int \*)(unsigned long)self->clear_child_tid = 0;/        (void)0;/ | kernel/sched.c
lxabi-kstack-free-off-by-one | s/    idx = (int)(off \/ KSTACK_SZ) - 1;/    idx = (int)(off \/ KSTACK_SZ);/ | kernel/sched.c
lxabi-reap-sc-top-lost | s/        free_kstack((uint64_t)sc_top_save\[i\]);/        (void)0;/ | kernel/sched.c
lxabi-cr0-wp-off | s/        cr0 |= (unsigned long)CR0_WP;/        cr0 |= 0UL;/ | kernel/mm/paging.c
lxabi-pipe-eof-lost | s/            if (!kpipe_empty_wopen(f)) return 0;/            if (!kpipe_empty_wopen(f)) return 1;/ | kernel/syscalls.c
lxabi-epipe-lost | s/            if (!ropen) return done > 0 ? done : -32;/            if (0) return -32;/ | kernel/syscalls.c
lxabi-pipe2-cloexec-lost | s/    int cloexec = (a2 \& LINUX_O_CLOEXEC) ? 1 : 0;/    int cloexec = 0;/ | kernel/syscalls.c
lxabi-poll-hup-lost | s/                if (!wopen) rev |= NET_POLLHUP;/                if (0) rev |= NET_POLLHUP;/ | kernel/syscalls.c
lxabi-futex-timeout-never | s/        if (left <= 0) return -110; \/\* ETIMEDOUT \*\//        if (0) return -110;/ | kernel/syscalls.c
lxabi-time-unreclaimed | s/= { sys_linux_time, /= { sys_minios_tls_retired, / | kernel/syscalls.c
lxabi-eventfd-overwrites | s/        f->efd_count += v;/        f->efd_count = v;/ | fs/kfile.c
lxabi-reader-close-lost | s/        if (!f->pipe_write \&\& f->pring) pipe_ring_close_reader(f->pring);/        (void)0;/ | fs/kfile.c
lxabi-mkfs-seal-lost | s/        self.seal_inode(ino)/        pass/ | tools/mkfs.minifs.py
futex-bitset-refused | s/        cmd == LINUX_FUTEX_WAIT_BITSET || cmd == LINUX_FUTEX_WAKE_BITSET)/        0)/ | kernel/futex.c
lxsecc-nnp-check-lost | s/    if (!strict \&\& !sec_nnp\[pid\]) return ERR_EACCES;/    if (0) return ERR_EACCES;/ | kernel/proc_sec.c
lxsecc-errno-data-lost | s/        \*ret = -(long)e;/        *ret = 0;/ | kernel/proc_sec.c
lxsecc-kill-ignored | s/        sec_kill(n, 1);/        (void)0;/ | kernel/proc_sec.c
lxsecc-rank-inverted | s/        if (r < best_rank) { best = a; best_rank = r; }/        if (r > best_rank) { best = a; best_rank = r; }/ | kernel/proc_sec.c
lxsecc-inherit-lost | s/    sec_chain\[child\] = f;/    sec_chain[child] = 0;/ | kernel/proc_sec.c
lxsecc-exe-substitution-lost | s/        kstrncpy(resolved, exe, sizeof(resolved) - 1);/        resolved[0] = 0;/ | kernel/syscalls_proc.c
lxsecc-wait4-returns-code | s/    return found;/    return code;/ | kernel/syscalls_proc.c
seccomp-bpf-final-ret-unchecked | s/    if (SBPF_CLASS(prog\[len - 1\].code) != SBPF_RET) return SBPF_ERR_INVALID;/    if (0) return SBPF_ERR_INVALID;/ | kernel/seccomp_bpf.c
seccomp-bpf-jset-swapped | s/            case SBPF_JSET: pc += (a \& src) ? in->jt : in->jf; break;/            case SBPF_JSET: pc += (a \& src) ? in->jf : in->jt; break;/ | kernel/seccomp_bpf.c
seccomp-bpf-scratch-flow-lost | s/            if (!(memvalid \& (1u << in->k))) return SBPF_ERR_INVALID;/            if (0) return SBPF_ERR_INVALID;/ | kernel/seccomp_bpf.c
lxnet-udp-deliver-lost | s/        u->count++;/        (void)0;/ | net/net.c
lxnet-nonblock-flag-lost | s/    int nonblock = (a2 \& LNX_SOCK_NONBLOCK) != 0;/    int nonblock = 0;/ | net/net.c
lxnet-cloexec-lost | s/    case LNX_F_GETFD: return \*ce ? LNX_FD_CLOEXEC : 0;/    case LNX_F_GETFD: return 0;/ | net/net.c
lxnet-refused-unreported | s/    s->so_error = LNX_ECONNREFUSED;/    s->so_error = 0;/ | net/net.c
lxnet-soerror-sticky | s/^                s->so_error = 0;/                (void)0;/ | net/net.c
lxnet-pollout-lost | s/        if (s->state == NET_TCP_ESTABLISHED \&\& !s->tx_pending) rev |= LNX_POLLOUT;/        (void)0;/ | net/net.c
lxnet-peer-name-wrong | s/        return net_store_sockaddr(addr, lenp, s->dip, s->dport);/        return net_store_sockaddr(addr, lenp, net_our_ip, s->dport);/ | net/net.c
lxnet-sendmmsg-len-lost | s/        \*(unsigned int \*)(m + NET_MMSGHDR_LEN_OFF) = (unsigned int)rc;/        (void)0;/ | net/net.c
lxnet-udp-from-lost | s/            long rc = net_store_sockaddr(from, fromlen, g->sip, g->sport);/            long rc = 0;/ | net/net.c
lxnet-inet6-wrong-errno | s/    if (a1 != LNX_AF_INET) return -LNX_EAFNOSUPPORT;/    if (a1 != LNX_AF_INET) return -LNX_EINVAL;/ | net/net.c
lxnet-socket-read-unrouted | s/        return net_sys_recvfrom(a1, a2, a3, 0, 0, 0);/        return -9;/ | kernel/syscalls.c
lxnet-socket-write-unrouted | s/    if (net_sys_is_socket(fd)) return net_sys_sendto(fd, (long)buf, cnt, 0, 0, 0);/    (void)0;/ | kernel/syscalls.c
lxnet-sockopt-unrouted | s/    \[54\]  = { sys_linux_setsockopt, .*$// | kernel/syscalls.c
lxnet-minifs-dir-merge-lost | s/^            return existing$/            pass/ | tools/mkfs.minifs.py
minifs-free-blocks-stale | s/                         count_free(self.bbitmap, self.total_blocks),/                         self.total_blocks - self.data_start,/ | tools/mkfs.minifs.py
minifs-free-inodes-stale | s/                         count_free(self.ibitmap, self.total_inodes),/                         self.total_inodes - ROOT_INODE,/ | tools/mkfs.minifs.py
minifs-fsck-counters-unchecked | s/^        self.check_counters()$/        pass/ | tools/minifs_fsck.py
lxnet-ip-recverr-refused | s/        case LNX_IP_RECVERR:/        case 0x7fe:/ | net/net.c
lxabi-group-exit-code-lost | s/            lead->exit_code = code;/            lead->exit_code = 0;/ | kernel/sched.c
lxabi-sigterm-not-fatal | s/14, 15, 24, 25,/14, 24, 25,/ | kernel/syscalls_proc.c
lxabi-relative-sleep-skipped | s/    else linux_sleep_until(ktime_us, ktime_us() + (unsigned long)us);/    else (void)us;/ | kernel/syscalls.c
lxabi-abstime-ignored | s/    if (a2 \& LINUX_TIMER_ABSTIME) linux_sleep_until(now, (unsigned long)us);/    if (a2 \& LINUX_TIMER_ABSTIME) (void)now;/ | kernel/syscalls.c
lxabi-timespec-unchecked | s/    if (sec < 0 || nsec < 0 || nsec >= LINUX_NS_PER_S) return -22;/    if (sec < 0) return -22;/ | kernel/syscalls.c
lxabi-getres-coarse | s/            ((long \*)a2)\[1\] = LINUX_NS_PER_US;/            ((long *)a2)[1] = LINUX_NS_PER_S;/ | kernel/syscalls.c
lxabi-rlimit-stack-unlimited | s/    if (res == LINUX_RLIMIT_STACK) v = MINIOS_USER_STACK_SIZE;/    if (res == LINUX_RLIMIT_STACK) v = LINUX_RLIM_INFINITY;/ | kernel/syscalls.c
lxabi-affinity-mask-empty | s/    \*(unsigned long \*)a3 = mask;/    *(unsigned long *)a3 = 0;/ | kernel/syscalls.c
lxabi-pipe-fionread-zero | s/    case LINUX_FIONREAD: \*(int \*)a3 = kfile_readable_bytes(f); r = 0; break;/    case LINUX_FIONREAD: *(int *)a3 = 0; r = 0; break;/ | kernel/syscalls.c
lxabi-pipe-claims-tty | s/    default: r = -LINUX_ENOTTY; break;/    default: r = 0; break;/ | kernel/syscalls.c
lxabi-demand-fault-refused | s/(pte \& PTE_DEMAND) \&\& (pte \& PTE_DEMAND_READ) \&\&/0 \&\&/ | kernel/mm/paging.c
lxabi-view-never-swapped | s/    if (!no || no == ho) return;/    if (1) return;/ | kernel/sched.c
lxabi-wild-jump-panics | s/^        if ((frame->cs \& 3) == 3) {$/        if (0) {/ | kernel/sched.c
lxnet-udp-fionread-zero | s/            \*(int \*)arg = u->count ? (int)u->q\[u->head\].len : 0;/            *(int *)arg = 0;/ | net/net.c
lxnet-tx-bounce-skipped | s/        kmemcpy(rtl_tx_buf\[slot\], frame, len);/        (void)frame;/ | net/rtl8139.c
vma-spare-not-recycled | s/    if (vma_spare) {/    if (0) {/ | vma.c
vma-mru-any-tree | s/            vma_mru->base == base \&\& vma_node_in_tree(root, vma_mru))/            vma_mru->base == base)/ | vma.c
ps2-caps-xor-lost | s/if (is_letter(c) \&\& s->caps_lock) upper = !upper;/if (is_letter(c) \&\& !s->caps_lock) upper = !upper;/ | progs/freedomui/ps2_keymap.c
ps2-chord-text-leak | s/if (!make || (k.mods \& (KE_MOD_CTRL | KE_MOD_ALT))) {/if (!make) {/ | progs/freedomui/ps2_keymap.c
ps2-e0-prefix-lost | s/if (byte == PS2_PREFIX_EXTENDED) { s->extended = 1;/if (byte == PS2_PREFIX_EXTENDED) { s->extended = 0;/ | progs/freedomui/ps2_keymap.c
ps2-num-lock-starts-off | s/    s->num_lock = 1;/    s->num_lock = 0;/ | progs/freedomui/ps2_keymap.c
ps2-pause-tail-short | s/#define PS2_PAUSE_TAIL      5/#define PS2_PAUSE_TAIL      4/ | progs/freedomui/ps2_keymap.c
ps2-release-keeps-mod | s/    else      s->held \&= ~bit;/    else      s->held \&= bit;/ | progs/freedomui/ps2_keymap.c
freedom-gui-frame-proof-lost | s/    if (!d->frame_reported) {/    if (0) {/ | progs/freedomui/platform_minios.c
process-note-ignored | s/        if (srcpath \&\& elf_wants_process(data, size))/        if (0 \&\& srcpath \&\& elf_wants_process(data, size))/ | kernel/shell.c
process-note-frame-exe-lost | s/        if (srcpath) proc_sec_set_exe(0, srcpath);/        (void)srcpath;/ | kernel/shell.c
process-note-type-flip | s/namesz == namesz_want \&\& type == MINIOS_NOTE_PROCESS \&\&/namesz == namesz_want \&\& type != MINIOS_NOTE_PROCESS \&\&/ | kernel/loader.c
process-note-name-flip | s/MINIOS_NOTE_NAME, namesz_want) == 0 \&\&/MINIOS_NOTE_NAME, namesz_want) != 0 \&\&/ | kernel/loader.c
gfx-cursor-follow-lost | s/^    gfx_cursor_follow_idle();/    ;/ | kernel/vga_fb.c
gfx-cursor-stale-arrow | /Lift the desktop pointer/,/cursor_erase/s/cursor_erase();/(void)0;/ | kernel/vga_fb.c
fg-wait-tick-lost | s/^            vga_fb_wait_tick();/            ;/ | kernel/spawn.c
nk-palette-bg-black | s/{15, 15, 15}, {0, 220, 0},/{0, 0, 0}, {0, 0, 0},/ | progs/nk_palette.h
spawn-nested-parent-zeroed | s/child->clone_flags = 0;/child->parent_pid = 0; child->clone_flags = 0;/ | kernel/sched.c
minicraft-ser-enter-lost | s/if (b == 13L || b == 10L)/if (0) {/ | progs/minicraft/minicraft.c
vedit-untitled-not-c | s/    return VEDIT_LANG_C;/    return VEDIT_LANG_TEXT;/ | progs/vedit/vedit.c
vedit-link-elf-rejected | s/if (e\\[k\\] == 0 \\&\\& s\\[k\\] == 0) return 1;/if (e[k] == 0 \&\& s[k] == 0) return 0;/ | progs/vedit/vedit.c
vedit-asm-dir-broken | s/#define VEDIT_DIR_ASM \"\/asm\//\#define VEDIT_DIR_ASM \"\/asx\// | progs/vedit/vedit.c
vedit-run-key-moved | s/#define VEDIT_KEY_RUN 18/#define VEDIT_KEY_RUN 19/ | progs/vedit/vedit.c
vedit-base-dot-kept | s/s = k + 1;/s = 0;/ | progs/vedit/vedit.c
paint-png-ihdr-type-dropped | s/if (paint_put_bytes(dst, cap, \\&pos, ihdr, 4) < 0) return -1;/if (0) return -1;/ | progs/paint/paint.c
paint-flood-mark-lost | s/    buf\\[y \\* w + x\\] = nc;/    buf[y * w + x] = oc;/ | progs/paint/paint.c
paint-path-traversal-accepted | s/        if (p\\[k\\] == \\x27.\\x27 \\&\\& p\\[k + 1\\] == \\x27.\\x27) return -1;/        if (p[k] == \\x27.\\x27 \&\& p[k+1] == \\x27.\\x27) return 0;/ | progs/paint/paint.c
paint-blit-transposed | s/            fb\\[dy \\* NK_W + dx\\] = paint_px\\[y \\* PAINT_W + x\\];/            fb[dy * NK_W + dx] = paint_px[x * PAINT_W + y];/ | progs/paint/paint.c
paint-test-plot-bounds-lost | s/    if (x < 0 || y < 0 || x >= w || y >= h) return -1;/    if (x < 0 || y < 0) return -1;/ | tests/test_paint.c
paint-test-flood-noop-inverted | s/    if (oc == nc) return 0;/    if (oc == nc) return 1;/ | tests/test_paint.c
paint-test-png-total-changed | s/    CHECK(total == 192278UL, \\x22png total bytes\\x22);/    CHECK(total == 192274UL, \\x22png total bytes\\x22);/ | tests/test_paint.c
fx-default-off | s/static int fx_enabled = 1;/static int fx_enabled = 0;/ | kernel/vga_fx.c
fx-on-ignored | s/    fx_enabled = on ? 1 : 0;/    fx_enabled = 0;/ | kernel/vga_fx.c
fx-state-inverted | s/    return fx_enabled;/    return !fx_enabled;/ | kernel/vga_fx.c
fx-melts-unreported | s/    fx_melts_completed++;/    fx_melts_completed += 0;/ | kernel/vga_fx.c
fx-finish-skips-melt | s/    vga_fx_melt_rect(0, 0, fb_width, fb_height, oldb, newb);/    (void)newb;/ | kernel/vga_fb.c
fx-open-never-armed | s/        fx_gfx_armed = 1;/        fx_gfx_armed = 0;/ | kernel/vga_fb.c
fx-advance-stuck | s/            cols\[i\]++;/            cols[i] += 0;/ | headers/vga_fx.h
fx-front-clamp-lost | s/    if (col_y > h) {/    if (col_y > h + 1) {/ | headers/vga_fx.h
gfxview-fullscreen-request-dropped | s/        return vga_fb_gfx_set_fullscreen(a1 == MINIOS_GFX_ZOOM_FULLSCREEN) ? -22 : 0;/        return 0;/ | kernel/syscalls.c
gfxview-tile-skips-graphics | s/                gfx_view_mode = WM_GFXVIEW_TILED;/                gfx_view_mode = gfx_view_mode;/ | kernel/vga_fb.c
gfxview-minimize-closes | s/^        vga_fb_gfx_set_hidden(1);/        wm_close_request = 1;/ | kernel/vga_fb.c
gfxview-maximize-ignores-gfx | s/        vga_fb_gfx_set_fullscreen(gfx_view_mode != WM_GFXVIEW_FULL);/        term_toggle_fullscreen();/ | kernel/vga_fb.c
gfxview-fit-integer-lost | s/        fw = k \\* (long)sw;/        fw = fw;/ | headers/wm_gfxview.h
gfxview-map-unscaled | s/    lx = ((long)(mx - v->content.x) \\* (long)sw) \\/ (long)v->content.w;/    lx = (long)(mx - v->content.x);/ | headers/wm_gfxview.h
gfxview-ease-linear | s/    r = den - (den \\* inv \\* inv \\* inv) \\/ ((long)n \\* (long)n \\* (long)n);/    r = (den * (long)t) \\/ (long)n;/ | headers/wm_gfxview.h
gfxview-alttab-keeps-fullscreen | s/^        if (wm_focus == WM_FOCUS_GFX \\&\\& gfx_covers_screen())/        if (0)/ | kernel/vga_fb.c

ldso-needed-dropped | s/info->needed_off\[info->needed_count++\] = val;/;/ | kernel/ldso_parse.c
ldso-func-symbol-skipped | s/type != LDSO_STT_FUNC && type != LDSO_STT_NOTYPE/type != LDSO_STT_NOTYPE/ | kernel/ldso_parse.c
ldso-reloc-type-inverted | s/type != LDSO_R_GLOB_DAT && type != LDSO_R_JUMP_SLOT/type == LDSO_R_GLOB_DAT || type == LDSO_R_JUMP_SLOT/ | kernel/ldso_parse.c
ldso-lib-base-dropped | s/lib->base + (unsigned long)v;/(unsigned long)v;/ | kernel/loader.c
ldso-text-not-exec | s/mm_user_set_exec(start, end, cr3);/;/ | kernel/loader.c
ldso-static-rejected | s/if (fr == 0) return 0;/if (fr == 0) return -1;/ | kernel/loader.c
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
    # Split at the LAST pipe: the sed expression itself may contain a
    # literal | (e.g. an escaped BRE alternation), while the filename
    # never does. %%/# (longest match) on the old code truncated such
    # expressions and produced garbage filenames (smp-init-missing).
    expr="${rest%|*}"
    file="${rest##*|}"; file="${file// /}"
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
    # Direct sed, never eval: an expression carrying a literal quote
    # (vol-sign-ignored's '-') re-quotes under eval, sed receives a
    # de-quoted pattern and reports "matched nothing" while the anchor
    # checker (ground truth: plain sed) passes. Every table entry is a
    # single s/// program, so eval buys nothing and breaks quoting.
    if ! sed -i "$expr" "$HERE/$file" 2>/dev/null; then
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

    # Mutants named lxabi-* break the Linux process, thread and descriptor
    # ABI that progs/src/lxabi.c probes (docs/spec/smp-sched.md): its one
    # scenario is the suite that must kill them, whatever file they touch.
    suite_key="$file"
    case "$name" in
        lxabi-*) suite_key="lxabi-probe" ;;
        lxsecc-*) suite_key="lxsecc-probe" ;;
        lxnet-*) suite_key="lxnet-probe" ;;
        minifs-*) suite_key="minifs-tools" ;;
    esac
    case "$suite_key" in
        lxabi-probe)
            MATCH="lxabi" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        lxsecc-probe)
            MATCH="lxsecc" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        lxnet-probe)
            MATCH="lxnet" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        minifs-tools)
            make -C "$HERE" test-minifs-tools > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/seccomp_bpf.c)
            make -C "$HERE" test-seccomp-bpf > "$BACKUP/suite.log" 2>&1
            ;;
        net/tls.c|net/tls_x509.c|tls_crypto.c|headers/tls.h)
            make -C "$HERE" test-tls > "$BACKUP/suite.log" 2>&1
            ;;
        vma.c)
            make -C "$HERE" test-vma > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/futex.c)
            make -C "$HERE" test-futex > "$BACKUP/suite.log" 2>&1
            ;;
        headers/rtc.h)
            make -C "$HERE" test-rtc > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/percpu_rq.c)
            make -C "$HERE" test-percpu-rq > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/batch.c)
            make -C "$HERE" test-batch > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/rcu.c)
            make -C "$HERE" test-rcu > "$BACKUP/suite.log" 2>&1
            ;;
        headers/sanitize.h)
            make -C "$HERE" test-sanitize > "$BACKUP/suite.log" 2>&1
            ;;
        headers/pipe.h)
            make -C "$HERE" test-pipe > "$BACKUP/suite.log" 2>&1
            ;;
        headers/panic.h)
            make -C "$HERE" test-panic > "$BACKUP/suite.log" 2>&1
            ;;
        headers/pcm_ring.h|tests/test_pcm.c)
            make -C "$HERE" test-pcm > "$BACKUP/suite.log" 2>&1
            ;;
        progs/lisp/lisp.c)
            make -C "$HERE" test-lisp > "$BACKUP/suite.log" 2>&1
            ;;
        headers/ktime.h)
            make -C "$HERE" test-ktime > "$BACKUP/suite.log" 2>&1
            ;;
        headers/randmix.h)
            make -C "$HERE" test-randmix > "$BACKUP/suite.log" 2>&1
            ;;
        progs/src/freedom_wl.c)
            make -C "$HERE" test-freedom-wl > "$BACKUP/suite.log" 2>&1
            ;;
        progs/freedomui/freedomui_minios.c|tests/test_freedomui.c)
            make -C "$HERE" test-freedomui > "$BACKUP/suite.log" 2>&1
            ;;
        progs/freedomui/ps2_keymap.c|tests/test_ps2_keymap.c)
            make -C "$HERE" test-freedom-gui > "$BACKUP/suite.log" 2>&1
            ;;
        progs/freedomui/platform_minios.c)
            MATCH="freedom-gui" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        progs/nk_palette.h|progs/wl/wl_mini.h|progs/wl/wl_mbox.h|progs/wl/wlcomp.c)
            make -C "$HERE" test-wl > "$BACKUP/suite.log" 2>&1
            ;;
        tests/test_paint.c)
            make -C "$HERE" test-paint > "$BACKUP/suite.log" 2>&1
            ;;
        progs/paint/paint.c)
            MATCH="paint" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/clip.c)
            MATCH="clip" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/mm/cow.c)
            MATCH="fork" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        arch/x86/ctx_sw.S)
            # One file, three contracts: fpu-no-save breaks FPU
            # save/restore (killed by the fptest slice), while the
            # fork trampoline mutant breaks child-zero return (killed
            # by the fork slice). Routing by file alone sent
            # fpu-no-save to the fork slice, where it survived
            # vacuously on 3 unrelated passes; route by name.
            # sched-park-* break the voluntary-switch park used by
            # every blocking wait, so the fork slice (forktest blocks
            # in waitpid) kills them.
            if [ "$name" = "fpu-no-save" ]; then
                MATCH="fpu" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [ "$name" = "fsbase-restore-corrupted" ]; then
                MATCH="glibc TLS" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                MATCH="fork" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        arch/x86/syscall_entry.S)
            # The entry trampoline serves every syscall: a stale stride
            # lands every thread on the wrong kstack, so the full BDD
            # suite (the old kernel.c routing for this same mutant)
            # kills it.
            FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        headers/drivers/pci.h)
            make -C "$HERE" test-pci > "$BACKUP/suite.log" 2>&1
            ;;
        drivers/virtio_blk.c)
            MATCH="virtio" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        drivers/nvme.c)
            MATCH="nvme" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        drivers/virtio_net.c)
            MATCH="vnet" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        net/net.c)
            # vnet-* rows break the virtio preference proved by the
            # vnet slice; every other net.c mutant keeps the full
            # suite (TCP/ARP/DNS ride the rtl8139 path there).
            if [[ "$name" == vnet-* ]]; then
                MATCH="vnet" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        drivers/block.c)
            MATCH="virtio" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        boot/uefi_stub.c)
            make -C "$HERE" uefi.img > "$BACKUP/suite.log" 2>&1 && \
            MATCH="uefi" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" >> "$BACKUP/suite.log" 2>&1
            ;;
        drivers/pcm2.c|headers/pcm2.h)
            # Null-backend probe slice: open/write/close plumbing only.
            # IRQ-ack and auto-init-command mutants are deliberately NOT
            # in the table: with no completion IRQ they are invisible
            # here and would survive vacuously; they are covered by live
            # runs (irq counter climbs) instead of the gate.
            MATCH="pcm2" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        progs/quake2generic/snddma_minios.c)
            # The Quake 2 sound backend is pinned by the pcm2 probe scenario
            # (SNDDMA path reaches pcm2) and the engine-init scenario
            # (sound sampling rate 22050); MATCH="quake2generic" runs both.
            MATCH="quake2generic" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        progs/minios_abi.h)
            python3 "$HERE/tools/check_abi_numbers.py" > "$BACKUP/suite.log" 2>&1
            ;;
        fs/fat32.c)
            # Host parser suite first (no boot), then the live fat
            # slice proving VFS wiring, mount table and builtin.
            make -C "$HERE" test-fat > "$BACKUP/suite.log" 2>&1 && \
            MATCH="fat " FAIL_FAST=1 "$HERE/tools/test_bdd.sh" >> "$BACKUP/suite.log" 2>&1
            ;;
        fs/ext4.c)
            # Host parser suite first (no boot), then the live ext4
            # slice proving VFS wiring, mount table and builtin.
            make -C "$HERE" test-ext4 > "$BACKUP/suite.log" 2>&1 && \
            MATCH="ext4 " FAIL_FAST=1 "$HERE/tools/test_bdd.sh" >> "$BACKUP/suite.log" 2>&1
            ;;
        headers/vga_fx.h|tests/test_fx.c)
            make -C "$HERE" test-fx > "$BACKUP/suite.log" 2>&1
            ;;
        headers/wm_gfxview.h|tests/test_wm.c)
            make -C "$HERE" test-wm > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/vga_fx.c|kernel/vga_fb.c)
            # gfxview-* rows break the graphics view contract (fullscreen,
            # tile, minimize), which only the gfxview scenario observes:
            # route them by name so they never survive vacuously on the
            # melt-counter slice.
            if [[ "$name" == gfxview-* ]]; then
                MATCH="gfxview" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == gfx-cursor-* ]]; then
                # The graphics-mode pointer (idle follow, desktop sprite
                # lifted on entry) is observable only on pixels: the
                # foreground phase of the FreeDom GUI proof judges both.
                python3 "$HERE/tools/test_gui_freedom.py" > "$BACKUP/suite.log" 2>&1
            else
            # No non-fx mutant touches these files yet, so the fx-filtered
            # BDD (3 scenarios, melts-counter pins) is the targeted suite;
            # revisit the routing if other vga_fb.c mutants ever land.
            make -C "$HERE" test-fx > "$BACKUP/suite.log" 2>&1 && \
            MATCH="fx" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" >> "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/syscalls.c)
            # MATCH must not leak into the suite: --match selects MUTANTS
            # by name, but test_bdd.sh reads the same variable as a
            # scenario filter. Leaking it skips every scenario whose name
            # lacks the string, the suite exits 0 on zero assertions, and
            # the mutant SURVIVES vacuously (this is how fpu-no-save got a
            # false SURVIVED while disabling fxsave in the tree).
            if [[ "$name" == gfxview-* ]]; then
                MATCH="gfxview" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == mprotect-* ]]; then
                MATCH="mprotect" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == mmap-file-* || "$name" == pcache-* ]]; then
                MATCH="pcache" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
            FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1 && \
            python3 "$HERE/tools/check_abi_numbers.py" >> "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/sched.c)
            # fd-fork-shares-view drops the fork-time view copy (the
            # forktest fd leg pins both directions), so the fork slice
            # kills it; every other sched.c mutant keeps the full suite.
            if [ "$name" = "fd-fork-shares-view" ]; then
                MATCH="fork" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == idle-cr3-* ]]; then
                # The smp builtin reports each idle context's tables; the
                # AP SSE scenario parks the AP after six threaded runs.
                MATCH="SSE in threads" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == pcache-* ]]; then
                MATCH="pcache" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/mm/paging.c)
            # pcache-* rows break the file-fault populate proved by
            # the pcache slice; every other paging.c mutant keeps
            # the full suite.
            if [[ "$name" == pcache-* ]]; then
                MATCH="pcache" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        fs/vfs.c)
            # vfs-readdir-* rows break listing legs pinned by the two
            # vfs scenarios (lifecycle readdir + unmount refusals), so
            # they run that slice; every other vfs.c mutant keeps the
            # full suite.
            if [[ "$name" == vfs-readdir-* ]]; then
                MATCH="vfs " FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        fs/kfile.c|kernel/console.c)
            # errno-* rows break the two errno scenarios (in-guest
            # toolchain link+run, loaded-object libc surface), so they
            # run that slice; every other mutant in these files keeps
            # the full suite.
            if [[ "$name" == errno-* ]]; then
                MATCH="errno" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/ldso_parse.c|kernel/loader.c)
            # ldso-* rows: the host parser suite first (kills the pure
            # table mutants without a boot), then the two BDD dynamic
            # scenarios (live window and isolated window) kill the
            # loader-glue mutants.
            if [[ "$name" == process-note-* ]]; then
                MATCH="process note" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == ldso-static-rejected ]]; then
                # Breaks loading of every no-dynamic image, ET_EXEC
                # included: the MiniFS lisp ELF is the kill.
                MATCH="lisp evaluates" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            elif [[ "$name" == ldso-* ]]; then
                make -C "$HERE" test-ldso > "$BACKUP/suite.log" 2>&1 && \
                MATCH="shared library" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" >> "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/shell.c)
            # process-note-* rows break the foreground process path or the
            # exec frame's /proc/self/exe; the lxproc/lxframe scenario pins
            # both. Every other shell row keeps the full suite.
            if [[ "$name" == process-note-* ]]; then
                MATCH="process note" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        smp.c)
            # ap-sse-* rows break the AP's per-CPU SSE enable: glibc
            # threads doing SSE2 on the AP (the apsse scenario) die with
            # #UD. Every other smp.c row keeps the full suite.
            if [[ "$name" == ap-sse-* ]]; then
                MATCH="SSE in threads" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            else
                FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            fi
            ;;
        kernel/mm/tlb.c|arch/x86/tlb_nmi.S)
            # TLB shootdown: the AP SSE scenario's munmap churn counts
            # tlb_shootdowns and pins tlb_timeouts=0.
            MATCH="SSE in threads" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        kernel/spawn.c)
            # The foreground process wait drives the desktop tick: without
            # it the pointer freezes over the waiting program, which the
            # foreground phase of the FreeDom GUI proof judges on pixels.
            python3 "$HERE/tools/test_gui_freedom.py" > "$BACKUP/suite.log" 2>&1
            ;;
        fs/ramdisk.c)
            # ramdisk-* rows break the boot image decoder, so anything
            # that runs a ramdisk file dies: the bare-.o scenarios load
            # objects/minigcc.o and objects/ld.o through it.
            MATCH="bare .o" FAIL_FAST=1 "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
        *)
            FAIL_FAST=1 MATCH="" "$HERE/tools/test_bdd.sh" > "$BACKUP/suite.log" 2>&1
            ;;
    esac
    if [ $? -eq 0 ]; then
        # A BDD suite that asserted nothing is not a pass (see the MATCH
        # leak above): a vacuous green must never read as a covered
        # mutant. A "0 passed" BDD summary means the run proved nothing:
        # mark BROKEN so a human looks, instead of SURVIVED so nobody
        # does. (Host suites print no summary; their exit code is already
        # the verdict, so only logs carrying a summary qualify.)
        if grep -q "=== summary" "$BACKUP/suite.log" && \
           grep -q "0 passed" "$BACKUP/suite.log"; then
            echo "MUTANT $name: BROKEN (suite asserted nothing)"
            record "$name" BROKEN
            BROKEN=$((BROKEN + 1))
        else
            echo "MUTANT $name: SURVIVED (test gap!)"
            sed -n 's/^=== summary/    suite: summary/p' "$BACKUP/suite.log"
            record "$name" SURVIVED
            SURVIVED=$((SURVIVED + 1))
        fi
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