#!/bin/sh
# Docstring: Scoped WM validation for Alt-Tab and tile across all windows.
# Runs host WM unit tests, rebuilds touched kernel objects with zero
# warnings, and asserts scoped mutants die. Fails closed on first gap.
set -eu
cd "$(dirname "$0")/.."
fail=0
say() { printf '%s\n' "$1"; }
die() { say "FAIL: $1"; fail=1; }
say "== wm scoped =="
make test-wm >build/wm_scoped_test.log 2>&1 || die "test-wm failed"
grep -q "wm: ok" build/wm_scoped_test.log || die "wm vectors missing"
make test-modifiers >build/wm_scoped_mod.log 2>&1 || die "test-modifiers failed"
grep -q "modifiers: ok" build/wm_scoped_mod.log || die "modifier vectors missing"
make test-driver >build/wm_scoped_drv.log 2>&1 || die "test-driver failed"
grep -q "driver: ok" build/wm_scoped_drv.log || die "driver vectors missing"
make test-sanitize >build/wm_scoped_san.log 2>&1 || die "test-sanitize failed"
grep -q "sanitize: ok" build/wm_scoped_san.log || die "sanitize vectors missing"
make test-notify >build/wm_scoped_not.log 2>&1 || die "test-notify failed"
grep -q "notify: ok" build/wm_scoped_not.log || die "notify vectors missing"
make test-vedit >build/wm_scoped_ved.log 2>&1 || die "test-vedit failed"
grep -q "vedit build host test ok" build/wm_scoped_ved.log || die "vedit vectors missing"
python3 tools/wm_layout_sync.py --check >build/wm_scoped_sync.log 2>&1 || die "layout manifest drifted"
rm -f vga_fb.o kbd.o syscalls.o spawn.o shell.o sb16.o pcspk.o
make vga_fb.o kbd.o syscalls.o spawn.o shell.o sb16.o pcspk.o >build/wm_scoped_build.log 2>&1 || die "kernel objects failed"
if grep -E "warning|error" build/wm_scoped_build.log; then die "warnings in touched objects"; fi
grep -q "WM_COMBOS" wm_events.h || die "combo table missing"
grep -q "wm_combo_lookup_mods" drivers/kbd.c || die "kbd unified lookup missing"
grep -q "modifiers_update" drivers/kbd.c || die "kbd unified tracking missing"
grep -q "spawn_execute" kernel/syscalls.c || die "spawn dispatch missing"
grep -q "spawn_execute" kernel/spawn.c || die "spawn contract missing"
grep -q "sb16_audio_device" kernel/syscalls.c || die "audio strategy missing"
grep -q "sb160" drivers/sb16.c || die "sb16 registry missing"
grep -q "wm_notify_emit" kernel/vga_fb.c || die "focus bus emit missing"
grep -q "wm_focus_cursor_sync" kernel/vga_fb.c || die "focus subscriber missing"
grep -q "focus-event" kernel/shell.c || die "wm state event missing"
grep -q "VEDIT_LANG_ASM" progs/vedit/vedit.c || die "asm lang missing"
grep -q "vedit_kw_asm" progs/vedit/vedit.c || die "asm keywords missing"
python3 - <<'EOF' || die "gfx must own overlapping clicks before terminals"
import re
s = open("kernel/vga_fb.c").read()
m = re.search(r"static int mouse_focus_topmost.*?^}", s, re.M | re.S)
assert m, "unified click dispatcher missing"
body = m.group(0)
i = body.find("gfx_hit(")
j = body.find("tw_hit(")
assert i != -1 and j != -1 and i < j, "paint order violated in dispatcher"
EOF
grep -q "if (wm_focus == WM_FOCUS_GFX) return 0;" kernel/vga_fb.c || die "gfx refocus repaint missing"
if grep -n "code == 0x" drivers/kbd.c >/dev/null; then die "raw magics remain in kbd.c"; fi
grep -q "gfx_hit" kernel/vga_fb.c || die "gfx body hit missing"
grep -q "vga_fb_ps2_owner(current_pid)" kernel/syscalls.c || die "mouse focus gate missing"
grep -q "spin_save_irq" kernel/syscalls.c || die "mouse atomic snapshot missing"
grep -q "pid < 0 || pid >= MAX_PROCS" kernel/vga_fb.c || die "ps2 pid validation missing"
if grep -n 'text_px.*Nuklear' kernel/vga_fb.c >/dev/null; then die "hardcoded Nuklear title remains"; fi
grep -q "GFX_TITLE_DEFAULT" vga_fb.h || die "title default config missing"
grep -q "blit_gfx_buf" kernel/vga_fb.c || die "blit fusion missing"
grep -q "wm_build_render_plan" kernel/vga_fb.c || die "render plan unused in kernel"
grep -q "kbd_drop_counts" drivers/kbd.h || die "drop counters missing"
grep -q "snap\[MAX_PROCS\]" kernel/shell.c || die "ps snapshot missing"
grep -q "job_row" kernel/shell.c || die "jobs snapshot missing"
grep -q "console_job_try" shell.h || die "job ps2-only source missing"
grep -q "ps2_owner(current_pid)) return -1" kernel/syscalls.c || die "getc gate missing"
grep -q "ps2_owner(current_pid)) return -11" kernel/syscalls.c || die "read stdin gate missing"
grep -q "elf_load((void \*)data, size, &base)" kernel/shell.c || die "run image free missing"
grep -q "elf_load((void \*)data, data_size, &base)" kernel/spawn.c || die "spawn image free missing"
grep -q "dlmalloc_usage" kernel/shell.c || die "mem builtin missing"
grep -q "wm_layout_compute" kernel/vga_fb.c || die "layout engine unused in kernel"
grep -q "wm_layout_same" kernel/vga_fb.c || die "repaint skip missing"
grep -q "vga_fb_layout_set" vga_fb.h || die "layout api missing"
grep -q "wm layout" kernel/shell.c || die "layout builtin missing"
grep -q "wm_layout.h" Makefile || die "layout test deps missing"
python3 tools/wm_layout_sync.py --check >/dev/null 2>&1 || die "layout manifest drifted"
if [ "$fail" -eq 0 ]; then say "wm scoped: ok"; else say "wm scoped: FAIL"; fi
exit "$fail"
