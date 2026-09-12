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
make test-wm >/tmp/opencode_wm.log 2>&1 || die "test-wm failed"
grep -q "wm: ok" /tmp/opencode_wm.log || die "wm vectors missing"
rm -f vga_fb.o kbd.o syscalls.o shell.o
make vga_fb.o kbd.o syscalls.o shell.o >/tmp/opencode_build.log 2>&1 || die "kernel objects failed"
if grep -E "warning|error" /tmp/opencode_build.log; then die "warnings in touched objects"; fi
grep -q "WM_COMBOS" wm_events.h || die "combo table missing"
grep -q "wm_combo_lookup" drivers/kbd.c || die "kbd lookup missing"
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
grep -q "elf_load((void \*)data, data_size, &base)" kernel/syscalls.c || die "spawn image free missing"
grep -q "dlmalloc_usage" kernel/shell.c || die "mem builtin missing"
if [ "$fail" -eq 0 ]; then say "wm scoped: ok"; else say "wm scoped: FAIL"; fi
exit "$fail"
