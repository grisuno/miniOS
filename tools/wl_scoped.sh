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
grep -q "wlcomp_blit_chrome" progs/wl/wl_mini.h || die "chrome blit missing"
grep -q "wl_surface_hit_zone" progs/wl/wl_mini.h || die "hit zone missing"
grep -q "wl_comp_set_minimized" progs/wl/wl_mini.h || die "minimize missing"
grep -q "wl_comp_refresh_active" progs/wl/wl_mini.h || die "active focus missing"
grep -q "wl_client_attach" progs/wl/wl_client.h || die "client lib missing"
grep -q "wl_ev_encode" progs/wl/wl_mini.h || die "ev encode missing"
grep -q "wl_ev_decode" progs/wl/wl_mini.h || die "ev decode missing"
grep -q "wl_ev_map" progs/wl/wl_mini.h || die "ev map missing"
grep -q "wl_client_box" progs/wl/wl_mbox.h || die "client box missing"
grep -q "wl_mbox_ev_name" progs/wl/wl_mbox.h || die "ev name missing"
grep -q "nk_client_probe" progs/nuklear/nuklear_minios.c || die "nk client missing"
grep -q "nk_client_poll" progs/nuklear/nuklear_minios.c || die "nk ev poll missing"
grep -q "wlserv_push_ev" progs/wl/wlcomp.c || die "ev push missing"
grep -q "wlserv_focus_box" progs/wl/wlcomp.c || die "focus box missing"
grep -q "alt_held" progs/wl/wlcomp.c || die "alt shortcut missing"
grep -q "shell_cmd_desktop" kernel/shell.c || die "desktop builtin missing"
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
grep -q "wlserv_pix" progs/wl/wlcomp.c || die "static pool missing"
grep -q "wlserv_close" progs/wl/wlcomp.c || die "close path missing"
grep -q "wlserv_gc_strays" progs/wl/wlcomp.c || die "stray gc missing"
grep -q "wl_client.h" progs/wl/wlcomp.c || die "client lib use missing"
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
grep -q "spin_wl" progs/src/spin.c || die "tiny live publisher missing"
grep -q "spin_raw_file" progs/src/spin.c || die "tiny raw publish missing"
grep -q "spin.elf" Makefile || die "spin build missing"
rm -f progs/bin/spin.elf
make progs/bin/spin.elf >build/wl_scoped_spin.log 2>&1 || die "spin guest build failed"
if grep -E "warning|error" build/wl_scoped_spin.log; then die "warnings in spin build"; fi
make progs/bin/wlcomp >build/wl_scoped_wlcomp.log 2>&1 || die "wlcomp rebuild failed"
if grep -E "warning|error" build/wl_scoped_wlcomp.log; then die "warnings in wlcomp rebuild"; fi
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
mut "chrome-active" 's/c->items\[top\]\.active = 1;/c->items[top].active = 0;/'
mut "chrome-close" 's/fb\[y \* fb_w \+ x\] = WL_CLOSE_INK;/fb[y * fb_w + x] = WLCOMP_BG;/'
mut "chrome-minimize" 's/if \(!s->mapped || s->minimized\)/if (!s->mapped)/'
mut "chrome-zone" 's/return WL_HIT_CLOSE;/return WL_HIT_TITLE;/'
mut "ev-magic" 's/if \(magic != WL_EV_MAGIC\)/if (0)/'
mut "ev-map-outside" 's/if \(fx < x0 || fy < y0 || fx >= x0 + cw || fy >= y0 + ch\)/if (0)/'
mut "ev-nsc" 's/ev->nsc > \(unsigned int\)WL_EV_SC_MAX/ev->nsc > 999/'
mutm "box-pid" 's/if \(pid < 0\)/if (0)/'
mutm "ev-name-suffix" 's/static const char suf\[\] = WL_MBOX_EV_SUFFIX;/static const char suf[] = ".xx";/'
cp build/wl_scoped_backup.h progs/wl/wl_mini.h
cp build/wl_scoped_mbox.h progs/wl/wl_mbox.h
make test-wl >build/wl_scoped_test.log 2>&1 || die "test-wl failed after restore"
if [ "$fail" -eq 0 ]; then say "wl scoped: ok"; else say "wl scoped: FAIL"; fi
exit "$fail"
