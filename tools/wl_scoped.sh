#!/bin/sh
# Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor.
# Runs host wire, mailbox and palette tests, rebuilds the guest wlcomp
# binary with zero warnings, and asserts scoped mutants die. Fails closed.
set -eu
cd "$(dirname "$0")/.."
fail=0
say() { printf '%s\n' "$1"; }
die() { say "FAIL: $1"; fail=1; }
say "== wl scoped =="
make test-wl >build/wl_scoped_test.log 2>&1 || die "test-wl failed"
grep -q "wl: ok" build/wl_scoped_test.log || die "wl vectors missing"
make test-freedom-wl >build/wl_scoped_fwl.log 2>&1 || die "test-freedom-wl failed"
grep -q "freedom_wl: ok" build/wl_scoped_fwl.log || die "freedom_wl vectors missing"
make test-freedomui >build/wl_scoped_fui.log 2>&1 || die "test-freedomui failed"
grep -q "freedomui: ok" build/wl_scoped_fui.log || die "freedomui vectors missing"
rm -f progs/bin/wlcomp.elf progs/bin/wlcomp
make progs/bin/wlcomp >build/wl_scoped_build.log 2>&1 || die "wlcomp guest build failed"
if grep -E "warning|error" build/wl_scoped_build.log; then die "warnings in wlcomp build"; fi
grep -q "wl_comp_layout_tile" progs/wl/wl_mini.h || die "tile layout missing"
grep -q "wlcomp_blit" progs/wl/wl_mini.h || die "pixel blit missing"
grep -q "wl_attach_encode" progs/wl/wl_mini.h || die "attach wire missing"
grep -q "wl_commit_encode" progs/wl/wl_mini.h || die "commit wire missing"
grep -q "wl_scale_nearest" progs/wl/wl_mini.h || die "scaler missing"
grep -q "wl_stream_feed" progs/wl/wl_mini.h || die "stream reassembly missing"
grep -q "wl_dispatch" progs/wl/wl_mini.h || die "request dispatch missing"
grep -q "wl_iface_find" progs/wl/wl_mini.h || die "iface table missing"
grep -q "WL_SURF_MAX_W" progs/wl/wl_mini.h || die "geometry config missing"
grep -q "wl_mbox_route" progs/wl/wl_mbox.h || die "mailbox route missing"
grep -q "wl_mbox_fresh" progs/wl/wl_mbox.h || die "mailbox freshness missing"
grep -q "nk_palette_build" progs/nk_palette.h || die "shared palette missing"
grep -q "wlcomp_session" progs/wl/wlcomp.c || die "session selftest missing"
grep -q "wlcomp_server" progs/wl/wlcomp.c || die "server loop missing"
grep -q "wlserv_drain" progs/wl/wlcomp.c || die "mailbox drain missing"
grep -q "wlcomp_client" progs/wl/wlcomp.c || die "client attach missing"
grep -q "freedom_wl_surface_attach" progs/src/freedom_wl.c || die "client attach missing"
grep -q "nk_palette.h" progs/nuklear/nuklear_minios.c || die "nuklear palette share missing"
grep -q "nk_palette.h" progs/freedomui/freedomui_minios.c || die "freedomui palette share missing"
grep -q "nk_mirror_tick" progs/nuklear/nuklear_minios.c || die "nk mirror missing"
grep -q "wl_mbox.h" progs/nuklear/nuklear_minios.c || die "nk mbox include missing"
grep -q '"term"' progs/wl/wlcomp.c || die "term pattern missing"
grep -q "0025" docs/adr/0025-wayland-session.md || die "session ADR missing"
grep -q "0026" docs/adr/0026-wayland-mailbox.md || die "mailbox ADR missing"
python3 -m py_compile tools/boot_wl.py || die "boot_wl syntax broken"
grep -q "wlcomp --server" tools/boot_wl.py || die "desktop setup missing"
grep -q "^wl:" Makefile || die "make wl target missing"
cp progs/wl/wl_mini.h build/wl_scoped_backup.h
cp progs/wl/wl_mbox.h build/wl_scoped_mbox.h
mut() {
  desc="$1"; expr="$2"
  cp build/wl_scoped_backup.h progs/wl/wl_mini.h
  cp build/wl_scoped_mbox.h progs/wl/wl_mbox.h
  perl -0pi -e "$expr" progs/wl/wl_mini.h
  if make test-wl >build/wl_scoped_mut.log 2>&1; then die "mutant live: $desc"; fi
}
mutm() {
  desc="$1"; expr="$2"
  cp build/wl_scoped_backup.h progs/wl/wl_mini.h
  cp build/wl_scoped_mbox.h progs/wl/wl_mbox.h
  perl -0pi -e "$expr" progs/wl/wl_mbox.h
  if make test-wl >build/wl_scoped_mut.log 2>&1; then die "mutant live: $desc"; fi
}
mut "layout-cols" 's/rows = 1;\n        cols = 2;/rows = 1;\n        cols = 1;/'
mut "attach-pool" 's/if \(!wl_pool_id_valid\(\*pool\)\)/if (0)/'
mut "blit-border" 's/fb\[y \* fb_w \+ x\] = WLCOMP_BORDER;/fb[y * fb_w + x] = WLCOMP_BG;/'
mut "commit-id" 's/if \(!wl_surface_id_valid\(\*id\)\)/if (0)/'
mut "stream-more" 's/if \(s->len < WL_HDR_SZ\)\n        return WL_ERR_MORE;/if (s->len < WL_HDR_SZ)\n        return WL_ERR_OK;/'
mut "stream-consume" 's/s->buf\[i\] = s->buf\[i \+ n\];/s->buf[i] = 0;/'
mut "dispatch-attach-short" 's/if \(!arg \|\| alen < WL_ATTACH_SZ\)\n                return WL_ERR_BOUND;/if (0)\n                return WL_ERR_BOUND;/'
mut "dispatch-create-size" 's/wl_comp_add\(c, nid, 64, 64\)/wl_comp_add(c, nid, 0, 0)/'
mut "iface-find" 's/if \(table\[i\]\.name\[k\] == .\\0. && name\[k\] == .\\0.\)\n            return i;/if (table[i].name[k] == 0 \&\& name[k] == 0)\n            return 0;/'
mut "scale-xy-swap" 's/int sx = \(x \* sw\) \/ dw;/int sx = (y * sw) \/ dw;/'
mutm "mbox-magic" 's/if \(magic != WL_MBOX_MAGIC\)/if (0)/'
mutm "mbox-fresh" 's/if \(boxes\[slot\]\.used && seq == boxes\[slot\]\.seq_last\)/if (0)/'
mutm "route-commit-op" 's/if \(opcode == WL_OP_SURFACE_COMMIT\) \{\n            for \(i = 0; i < WL_MAX_SURFACES; i\+\+\)/if (opcode == 7) {\n            for (i = 0; i < WL_MAX_SURFACES; i++)/'
mutm "route-attach-short" 's/if \(!arg \|\| alen < WL_ATTACH_SZ\)/if (0)/'
cp build/wl_scoped_backup.h progs/wl/wl_mini.h
cp build/wl_scoped_mbox.h progs/wl/wl_mbox.h
make test-wl >build/wl_scoped_test.log 2>&1 || die "test-wl failed after restore"
if [ "$fail" -eq 0 ]; then say "wl scoped: ok"; else say "wl scoped: FAIL"; fi
exit "$fail"
