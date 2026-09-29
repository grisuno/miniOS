# VESA desktop, graphics windows, window manager, taskbar, dock and desktop effects

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

## VESA Hi-Res Desktop and Windowed DOOM

**Testing doctrine: VGA-mode work is driven with `tools/minios_gui.py`, never
headless.** A headless boot cannot observe or trigger desktop events (mouse
cursor, window drag, title-bar buttons, the return-to-desktop transition after
a ring-3 program), so a GUI bug seen by hand or assumed from code is not
reproduced. `minios_gui.py` boots QEMU with the std VGA device, a QMP socket
to inject PS/2 mouse motion, clicks and keyboard, and a pty serial console;
after each action it saves the framebuffer to a PNG via QMP `screendump`.
`gfx` / `gfx pixel x y` probe the framebuffer over serial as a text backstop.

The desktop runs at a VESA linear-framebuffer resolution (800x600x8 by
default) instead of VGA Mode 13h, and DOOM runs in a titled window at its
native 320x200 instead of stealing the whole display.

- **Boot path (stage2.S + bootdefs.h):** after the kernel image is loaded and
  before long mode kills the BIOS video services, stage 2 probes VESA BIOS
  Extensions for a linear framebuffer: 1024x768x32 first, then 1024x768x8,
  800x600x32, 800x600x8, 640x480x32, 640x480x8, then VGA
  Mode 13h as a fallback. It
  writes `{phys_base, pitch, width, height, valid, bpp}` to the fixed
  low-memory struct `VBE_INFO_ADDR` (0x7E20). In true color the kernel
  expands palette-index drawing to RGB and the wallpaper keeps full
  24-bit color (no websafe quantization); the 8-bit modes keep the
  256-entry VGA DAC path. No bare
  VBE constant appears in the assembly; every mode number, offset and
  attribute lives in `bootdefs.h`.
- **Kernel mapping (kernel.c `mm_setup_protections`):** `vga_fb_boot_config`
  loads the VBE struct into `fb_width`/`fb_height`/`fb_pitch`/`fb_phys_base`,
  and the kernel maps that physical framebuffer into the user window at the
  fixed virtual `FB_ADDR` (0x0B200000), replacing the old 0xA0000 mapping. All
  drawing addresses through `FB_ADDR` (desktop and graphics programs) work
  unchanged; pixel addressing honors `fb_pitch`.
- **Movable shell window (vga_fb.c):** the shell runs in a window (default
  72x40 cells, clamped to the framebuffer) with a title bar on top and a
  scrollbar on the window's right edge, over a desktop background with a
  bottom taskbar. Click-and-drag on the title bar moves the window with the
  mouse; F11 toggles fullscreen, F5 resets the position. Window geometry is
  independent of the framebuffer dimensions.
- **Windowed DOOM (syscall 211 + doomgeneric_minios.c):** the kernel maps a
  64 KB kernel-heap back-buffer into the user window at `DOOM_BACKBUF_ADDR`
  (0x0B000000, RW, NX). DOOM renders its 320x200 frame there and calls
  `SYS_DOOM_FRAME`; the kernel composites the buffer onto the desktop through
  the graphics view contract below (`vga_fb_blit_gfx_window`). DOOM and
  Quake 2 now start in true fullscreen (see "Graphics view contract"); with
  `mini_windowed` / `minios_windowed` on the command line, or in a headless
  `*_autoframes` run, they keep the historical titled 1:1 window, centered,
  with the shell window and desktop visible around it. When a graphics
  program exits the kernel redraws the desktop and restores the 15-color
  desktop palette.
 - **Known limitation:** an 8-bit palette mode has one global 256-color DAC, so
   while DOOM runs its 256-color palette recolor the desktop behind the window.
   The window geometry and shell remain correct; only the desktop's colors
   shift until the next `vga_fb_draw_desktop`. A 16/24-bit VBE mode would fix
   this but is out of scope.


### Taskbar with clock and volume (`vga_fb.c` + `rtc.c` + `pcspk.c`)
The bottom taskbar is the desktop's status strip, not a hint line. It shows
the current time and a speaker icon with volume control, both live, and both
wired to the same kernel state the shell's `date` and `vol` builtins expose
so the behaviour is serial-observable and BDD-testable even though the
framebuffer is not.

- **Clock (`rtc.c`):** `rtc_read_tod` reads the CMOS RTC time-of-day through
  the named ports and registers in `rtc.c`. It waits out the update-in-progress
  flag, decodes the binary-coded-decimal fields, and **fails closed**: a
  non-BCD field, an impossible hour/minute/second, or a clock that never stops
  updating returns failure, never a plausible-but-wrong time. The taskbar
  redraws the clock when the second changes and treats a failed read as "clock
  unavailable", never a stale value. `rtc_read_date` adds the calendar side
  (CMOS 0x07-0x09, two-digit year mapped to 2000..2099, Feb 29 validated
  against the leap rule including the %400 century case) and
  `rtc_days_from_civil` converts to post-1970 days, so `gettimeofday(96)`
  and `clock_gettime(228)` report true epoch seconds (second resolution,
  usec/nsec zero). The old `gettimeofday` returned TSC milliseconds since
  boot — uptime, not an epoch — which silently broke every absolute-date
  consumer, notably the ring-3 TLS certificate window (days computed to 0,
  so no real chain ever verified in-guest). On RTC failure both syscalls
  report 0/0 and TLS fails the chain closed downstream.
- **Volume (`pcspk.c`):** a master volume 0..100, `PCSPK_VOL_DEFAULT` at boot,
  clamped on set. The PC speaker has no hardware amplitude and this kernel does
  not drive a PWM carrier, so volume is a **mute switch**: `pcspk_tone` opens
  the speaker (port 0x61 bits 0 and 1, both required for the PIT2 square wave
  to sound) only when the volume is above `PCSPK_VOL_MIN`, exactly as the
  pre-volume driver did, so a default boot is byte-for-byte compatible and a
  tone always sounds. At volume 0 the bits stay low and the speaker is silent.
  Keeping the tone path identical to the original is deliberate: it is the
  guarantee that sound never regresses.
- **Taskbar widgets:** the speaker icon sits in the taskbar with `-`/`+`
  buttons that call `pcspk_set_volume`; a left click on the icon toggles
  mute, and the `-`/`+`   buttons step the volume by `TASKBAR_VOL_STEP`. Left
  of the speaker an `EN`/`ES` label shows the keyboard layout and toggles it
  on click (`EN` US qwerty, `ES` Spanish qwerty with Latin-1 `ñ Ñ ¡ ¿ ´ ¨ ·
  ª º ç Ç ¬` glyphs in the framebuffer font; `^ ´ ` ¨` emit their spacing
  symbol, no composition; code characters live on Right Alt (AltGr) exactly
  like on real hardware — `AltGr+3` is `#`, `AltGr+2` `@`, `AltGr+`` `[`,
  `AltGr++` `]`, `AltGr+´` `{`, `AltGr+ç` `}`, `AltGr+º` `\`, `AltGr+1` `|`,
  `AltGr+4` `~`, `AltGr+6` `¬` — so ES is fully usable for code editing;
  only `€` is missing, it has no Latin-1 byte). Console input accepts
  printable Latin-1 (`kbd_is_printable`, 32..126 plus 160..255) in the
  prompt, the `edit` line reader and the terminal, so `ñ` travels from key
  to buffer to screen as one byte. Mouse hit-testing lives in `vga_fb_mouse_tick` beside the
  existing title-bar drag and scrollbar logic; there is no separate input
  path. The cursor tip is the sprite's top-left pixel, so a click lands where
  the arrow points; the IRQ12 phase guard also rejects first-byte overflow
  bits, so a stray init reply (`0xFA`/`0xAA`) can never shift the packet
  framing and warp the first motion after boot.
- **Tiling shortcuts (Alt = WM modifier, `kernel.c` + `vga_fb.c`):** the window
  is moved, snapped and resized from the keyboard for a tiling-WM feel. Alt is
  tracked as a modifier beside Shift and Ctrl. Alt+Enter toggles fullscreen,
  Alt+arrows snap the window to the left/right/top/bottom half of the screen,
  Alt+Home/End snap to the top-left / bottom-right quadrant, Alt+`[`/`]`
  shrink/grow width, Alt+`-`/`=` shrink/grow both dimensions, and Alt+0 resets
  the window to its default position and size. The window keeps its current
  size across redraws (resize/snap persist instead of snapping back to the
  default like the old layout engine).
- **Focus + tiling across windows (Alt-Tab, Super-Tab, `vga_fb.c` + `drivers/kbd.c`):**
  the focused window owns the keyboard; its title bar paints bright
  (`COL_TITLEBAR`) while unfocused terminals dim (`COL_SHADOW`) with a `*`
  marking the focused one. Alt+Tab cycles focus across EVERY window —
  present terminals plus the graphics window (`WM_FOCUS_GFX`), like
  Windows/Linux, never terminals-only; Super (E0 0x5B/0x5C, tracked as
  `kbd_super` beside Alt) + Tab tiles them all (one terminal fills it, two
  go left/right; with a graphics window the terminal(s) yield the right
  half — two stack vertically on the left — and a window too wide for the
  half goes right-aligned instead of centered). Super+arrows snap the
  focused window like Alt+arrows. Clicking an unfocused terminal raises it
  through the same select path, so mouse and keys agree. Click-to-focus
  follows paint order (graphics first, then terminals): the gfx window
  composites on top, so it owns overlapping clicks, and an already-focused
  target never repaints (`vga_fb_focus_id` early-outs). Mechanism, not
  incident: testing terminals first stole gfx clicks — one click focused
  the wrong window, the unfocused app read -1 from `SYS_MOUSE`, and the
  user paid three clicks per action with a full repaint flash each time.
  Every focus move emits once on the `wm_notify.h` bus at the user-intent
  site (keyboard cycle, pointer click, taskbar button, mode switch, shell
  command), never inside the mechanism, so one gesture is one event; the
  cursor-sync subscriber owns stale-cursor invalidation (the tick no
  longer clears it by hand on focus clicks) and `wm state` reports the
  last move as `wm: focus-event <old>-><new> <kbd|ptr|bar|mode|prog>`.
  The `wm` builtin
  drives the same functions (`wm focus [next|0|1|2]`, `wm tile`, `wm list`,
  `wm state` reports `focus`/`nterms`) so the BDD suite asserts them over
  serial exactly like `date`/`vol` (including a background-DOOM scenario
  that focuses, tiles, lists and closes the gfx window); real scancodes are
  covered by QMP `input-send-event` (`alt`+`tab`, `meta_l`+`tab`) against
  `display none`.
- **Second terminal (`wm split`, `vga_fb.c` + `shell.c`):** two shells share
  one execution engine — the globals every terminal function uses always
  mirror the focused window, and `tw_park`/`tw_unpark` swap the whole window
  state (geometry, logical ring, active line, cursor) between the globals and
  the per-window slot. Window 0 keeps the historical static ring; window 1's
  64 KB ring lives on the kernel heap (a static would blow the
  `USER_LOAD_BASE` `.bss` budget). The shell parks its half-typed line per
  window (`shell_focus_park/restore` over `vga_fb_park/unpark_line`, with a
  generation counter so the readline loop adopts the incoming line instead
  of dropping the first keystroke after Alt-Tab); history and cwd stay
  shared, and running a program blocks both windows (one `exec_return`).
  While split, window 0 snapshots to the heap too: its slot borrows the
  static ring, which IS the live one, so sharing it merged both windows'
  content and aliased `tw_park`'s copy (src == dst), rotting scrollback
  once `lg_head` moved. `wm close` drops the split from any focus (typing
  it in window 0 still closes window 1, never a silent no-op), adopts the
  live ring into window 0 so no output is lost, frees both heap rings and
  re-homes window 0 on the static ring; window 0 never closes (it resets
  to default like the historical X button). An empty submit (Enter /
  Ctrl+D on a blank line) clears the window's live-prompt flag, or every
  refocus stacked another `miniOS> `.
  The dock's Terminal icon runs `wm split` (`progs/etc/shortcuts`), so a
  click opens/focuses the second shell with no typing — verified over QMP
  with separated button down/up (a joint down+up can land inside one tick
  and read as no click); a repeat click just refocuses window 1.
  Icons are never relative to the shell: `desktop_launch` (`kernel/shell.c`)
  pins the cwd to `/` while the shortcut command runs and restores it
  after (a click during a running program queues through the same path),
  so `run quake2generic.elf +set basedir .` resolves `baseq2/` at the
  root no matter where the shell sits — a wrong cwd used to kill Quake
  with `Couldn't load pics/colormap.pcx`, mimicking memory exhaustion.
  `tools/test_gui_icon_cwd.py` proves it over QMP (template-matched dock
  click from a shell sitting in `/cvm`).
  Honest limits: no Alt-Tab mid-`edit` (the modal editor echoes into
  whichever window is focused), serial sees one interleaved console (use
  `wm list`'s `line` flag to tell which window holds a parked line).
- **Focus-routed input (`vga_fb_ps2_owner`, `drivers/kbd.c` +
  `kernel/syscalls.c`):** one PS/2 keyboard feeds every window, so the
  focused window owns it — a background gfx job (`run doomgeneric.elf
  mini_autoframes 3000 &`, shell stays interactive) reads `SYS_KBD` only
  while the gfx window is focused, the shell's `kbd_read` only while a
  terminal is, and neither touches the port when unfocused, so the two
  never split the scancode stream. The serial console is the shell's own
  and is never shared: `GETC_RAW` (236) serves a background job from the
  PS/2-only source (`console_job_try/get`, never serial or the shell's
  cooked queue) and `read(0)` answers `-EAGAIN` when unfocused, so a
  polling game can never steal shell bytes; foreground runs (legacy
  `run`, `mrun` fg via `shell_fg_active`) keep the full multiplexer.
  The cursor has exactly one painter per mode: the tick owns it on the
  desktop, the present path (`blit_gfx_buf` erase-then-draw) owns it
  while a graphics program runs. Sharing the save/old state between
  the 25 Hz tick and ~60 fps presents raced every frame and stranded
  stale sprites (worst on the title-bar hitboxes the tick touches), so
  in gfx mode the tick never draws or restores and only invalidates
  across real repaints. `tools/test_gui_fashion.py` proves it over QMP
  (one arrow sprite after motion, stable idle frames, ESC quits).
  Taking the display also takes focus (`wm_gfx_focus_sync` inside
  `vga_fb_set_gfx_mode`): enabling graphics mode parks the shell line
  and focuses the graphics window with stale raw bytes flushed, so a
  gfx child spawned from another gfx app (file browser opening vedit)
  owns PS/2 from its first frame instead of looking hung while its keys
  and wheel land on the shell; disabling hands the focused terminal
  back silently. Raw mode is per-app state each program asserts at
  startup (piano/node editor/file set 1, vedit sets 0 because GETC_RAW
  starves while raw diverts PS/2 to the raw queue), and the file
  browser drops to 0 around every SPAWN so no child inherits its mode.
  A legacy foreground program owns
  everything (its shell is blocked, nobody to steal from). `kbd_read`
  always translates cooked for the shell even with the global raw mode on
  (a bg raw game used to deafen shell PS/2), and focusing the gfx window
  flushes stale raw bytes. Serial bypasses routing and stays a shell
  console at every focus. `sleep <secs>` (yield loop, Ctrl+C aborts) paces
  scripts across a booting bg job. Honest limits: one interactive gfx app
  at a time (two bg games race one port); PS/2 Ctrl+C reaches `wait` only
  with a terminal focused (serial Ctrl+C always works).
- **Window controls (title-bar buttons, `vga_fb.c`):** every titled window
  (terminal, DOOM, Nuklear) carries the classic three glyph buttons at the
  right end of its title bar — minimize (`_`), maximize (open square) and
  close (`X`) — drawn and hit-tested by the shared `wm_*` helpers. A click on
  minimize hides the terminal window (the content stays in the logical ring,
  so restoring repaints it with nothing lost); maximize toggles fullscreen;
  close restores the terminal to its default geometry because the shell
  cannot be closed. For a graphics window the buttons target the composited
  DOOM/Nuklear title bar: maximize is a no-op (the window is already display-
  sized) and   close arms `wm_close_request`, which the syscall dispatcher
  honours on the child's next syscall (`exec_exit_code = 130`, `klongjmp` on
  the child's own stack — never from the ISR), so a graphics program is
  terminated cleanly from its title-bar X. A background job has no fg exec
  frame, so its close request reaps it as `do_exit(130)` instead of stealing
  the shell's `klongjmp` target. Alt+M toggles minimize and
  Alt+X/Alt+Q close the active window. Fullscreen and minimize are mutually
  exclusive: entering one clears the other.
- **WM geometry and events (`wm_geom.h`, `wm_events.h`, `vga_fb.c`):** the
  tick no longer hardcodes title height or button edges. `wm_geom.h` owns
  every rectangle (title, content, scrollbar, clamp) through
  `wm_geom_config_t` derived once from `FONT_W`/`FONT_H`/`SCROLLBAR_W`;
  `wm_events.h` owns click/release/scroll/move translation through
  `wm_event_config_t` with a stateless pure translator plus the shared
  Alt/Super combo table (`WM_COMBOS`, `WM_SC_*`, `wm_combo_lookup`) used by
  cooked and raw paths, so Alt-Tab/Super-Tab/snap/resize can never diverge
  again and AltGr never triggers a combo. Drag grabs live at
  file scope (`wm_dragging`, `wm_gdrag`) so `tw_select` resets them on
  every focus change instead of leaking a stale grab. `wm_window.h` unifies
  terminal and graphics hit-testing plus focus rotation and paint order
  (`tw_hit` delegates, `tw_select` bounds-checks); `wm_render.h` owns the
  back-to-front composition plan (wallpaper, shortcuts, taskbar, terminals,
  graphics last); `wm_tiling.h` owns terminal cell layout (split, stack
  beside graphics, fullscreen single); `wm_focus.h` owns validated focus
  transitions (`vga_fb_focus_next`/`vga_fb_focus_id` delegate id selection
  and refuse invalid targets); `wm_layout.h` owns unified placement across
  `tile`/`bsp`/`cascade`/`fibonacci`/`fullscreen` (`wm_layout_compute`,
  `wm_layout_same`, `wm_layout_fullscreen_cell`, config
  `wm_layout_config_t`, spec `docs/wm_layout_spec.md`, manifest
  `docs/wm_layout_manifest.md` via `tools/wm_layout_sync.py`). Host contract is
  `make test-wm`; mutation gate covers title height, containment edges,
  click/release confusion, paint and layer order, tiling splits (odd
  widths included), bsp/cascade/fibonacci cells, fullscreen uniformity,
  plan-equality and null/degenerate fail-closed.
- **WM inside games (raw scancodes, `drivers/kbd.c`):** DOOM/Quake/Nuklear/
  piano read raw Set-1 scancodes through `SYS_KBD` (205), bypassing the
  cooked translation where Alt-Tab lives — so the WM used to die the moment
  a game owned the keyboard. `raw_track_mods`/`wm_raw_combo` (shared core)
  intercept on both raw paths (`kbd_read`'s raw branch and
  `kbd_sys_raw_filter` for the direct-port syscall read): Alt+Tab focuses,
  Super+Tab tiles, Super+arrows/Home/End snap, Alt+Enter/M/X/Q/`[`/`]`/`-`/
  `=`/`0` act, and a swallowed Tab make swallows its break too. The table is
  the single source: `wm_combo_dispatch` in `drivers/kbd.c` serves cooked,
  raw-fill and `SYS_KBD` paths, Alt+arrows stay cooked-only by path mask.
  Clicking a graphics body focuses it (`gfx_hit` over `wm_window_contains`,
  not title-only) and wheel/scroll act only when a terminal is focused.
  `SYS_MOUSE` snapshots atomically under IRQ save and honors `ps2_owner`,
  so an unfocused reader gets `-1` instead of leaked coordinates. `ps2_owner`
  validates `0 <= pid < MAX_PROCS` and `sched.h` owns `user_program_active`.
  Both blits share `blit_gfx_buf` under `GFX_TITLE_DEFAULT`, so DOOM/Nuklear
  titles always come from `SYS_GFX_SET_TITLE`. `wm state` also reports
  `kbd drops cooked/raw`. Bare keys
  always reach the game, and Alt+arrows stay with the game (DOOM strafes
  with them); Super is never a game key, so it carries the full set raw.
  The `SYS_KBD` path holds back the `0xE0` prefix while Alt/Super is held
  (no stray prefix wedges a game's key pump) and modifiers are tracked raw,
  so nothing sticks across `kbd_reset_for_shell` (which now clears every
  modifier, not just Super/AltGr). `vga_fb_tile_all` parks a fitting gfx
  window (DOOM 320px) on the right half beside the terminal(s); a full-size
  one (Nuklear/vedit 800px) stays centered. Honest limits: legacy blocking
  `run` still blocks the shell (type in a terminal while a fg game runs
  needs `run game &` + preempt), and one keyboard feeds both a bg game and
  the shell — WM combos are consumed, the rest reaches both.
- **Minimize/restore (`wm` builtin):** while the terminal is minimized the
  window is not drawn and the taskbar shows a `[]` restore button on the far
  left. The mouse tick ignores wheel/drag/scrollbar while minimized. The `wm`
  builtin (`wm state`, `wm minimize`, `wm maximize`, `wm close`) drives the
  same functions as the buttons and shortcuts and reports state over the
  serial console, so the BDD suite asserts the WM behaviour exactly like
  `date`/`vol`/`kbd`/`gfx`.
- **Layout modes (`wm layout`, `wm_layout.h`):** `tile` keeps the legacy
  dual split exactly (odd remainder goes right, like `wm_tiling.h`);
  `bsp` splits recursively alternating axes; `cascade` offsets by config
  steps; `fibonacci` carves integer-ratio strips; `fullscreen` fills focus.
  `wm layout [tile|bsp|cascade|fibonacci|cycle]` sets it, `wm state`
  reports `wm: layout <name>`, Alt+Enter stays uniform (a terminal fills
  the grid, the graphics window goes true fullscreen), and
  `vga_fb_tile_all` skips the redraw when `wm_layout_same` proves the
  plan unchanged, which removes the drag/tile flicker without touching
  the rasterizer. The graphics window is a layout participant like any
  terminal (after the terminals, so `tile` keeps it on the right): its
  cell becomes the tiled view and the app is scaled into it. Every cell
  with a right neighbour gives back the grid column its scrollbar (or
  letterbox strip) paints into; before that every split overlapped the
  neighbour's first 8 px column.
- **Graphics view contract (`wm_gfxview.h`, `vga_fb.c` `gfx_present`):**
  the tiling WM governs every graphics app, not just terminals and vedit.
  One header-only contract (pure integer, `make test-wm`) owns where a
  back-buffer lands in three modes: *floating* (native size or the app's
  2x zoom, centered plus the drag/snap offset, titled), *tiled* (the cell
  the layout assigned, titled, content aspect-fit and centered inside it,
  scaled up or down) and *fullscreen* (the whole display, no chrome,
  content aspect-fit with black letterbox bars). The fit keeps the
  largest integer scale when it covers at least 7/8 of the exact fit, so
  DOOM runs a crisp 3x (960x600) at 1024x768 and an exact 2.5x (800x500)
  at 800x600. Every source (DOOM 320x200, the indexed and RGB 800x360
  Nuklear buffers, Pokemon, wlcomp) funnels through one present path and
  one nearest-neighbour scaler (`gfx_scale_blit`: 16.16 column stepping,
  repeated rows copied from the row just written, 8/24/32 bpp). A
  minimized graphics window keeps running and counting frames but paints
  nothing. Entry points: Alt+Enter / the title maximize button / `wm
  maximize` toggle fullscreen on the focused graphics window; `wm tile`,
  Super+Tab and `wm layout ...` tile it; the title minimize button, Alt+M
  and `wm minimize` hide it to its taskbar button (which it used to
  *close* by mistake: the minimize glyph armed the close request); the
  taskbar button, Alt+Tab and `wm focus 2` restore it; snap, Ctrl+arrows
  and a title drag float a tiled window at native size. `SYS_GFX_ZOOM`
  (242) grew two values in `minios_abi.h`: `MINIOS_GFX_ZOOM_FULLSCREEN`
  (2) and `MINIOS_GFX_ZOOM_WINDOWED` (3); an older kernel answers -EINVAL
  and the app simply stays windowed. Pointer truth follows the pixels: the
  present syscalls report the real content origin (`vga_fb_gfx_origin`)
  and `SYS_MOUSE` maps the desktop pointer through the inverse transform
  (`vga_fb_gfx_map_mouse`) when the view is scaled, so an app's `mouse -
  origin` lands on the back-buffer pixel under the arrow; 1:1 views pass
  through untouched. Over a fullscreen app the desktop never paints
  (taskbar clock, dock, terminal output, title-bar hit tests all stand
  down), a click only refocuses the app, and the arrow hides after 1.5 s
  without motion. `wm list` reports `win gfx ... view=<floating|tiled|
  fullscreen|minimized> cx= cy= cw= ch=` and `wm state` carries `wm: gfx
  view <name>`. Alt+Tab (or `wm focus`) away from a fullscreen app
  minimizes it, like any desktop does, so the keyboard never lands on a
  terminal the app still covers; Alt+Tab back restores it fullscreen
  (BDD `gfxview alt-tab`, mutant `gfxview-alttab-keeps-fullscreen`). Proof: `make test-wm` (fit,
  views, map, ease, lerp vectors), the `gfxview` BDD scenario (fullscreen
  start, maximize, tile, minimize, restore, close 130 over serial) and
  `tools/test_gui_gfxview.py` (QMP pixels: fullscreen hides the taskbar
  row, floating shows the desktop, tiled scales past 320 px); seven
  `gfxview-*` mutants die in `mutate.sh`.
- **Double-buffered desktop composition (`vga_fb.c` render target):**
  every primitive writes through `FBT`, which is the framebuffer unless a
  full desktop composition is in flight; `vga_fb_draw_desktop` composes
  wallpaper, dock, taskbar, terminals, the graphics layer and the pointer
  into a heap shadow of identical layout and presents it with one bulk
  copy, so a drag, Alt-Tab or tile never shows the cleared or half-painted
  frame that used to flash. Nested compositions (an ISR tick inside a
  syscall) draw into the same shadow and leave the present to the
  outermost owner; the shadow is allocated once and never freed; OOM
  degrades to direct drawing. The primitives that dominated every redraw
  went bulk at the same time: `vga_fb_rect` resolves its color once and
  fills whole runs, the wallpaper is cached in the framebuffer's native
  pixel format and repaints as one row copy per scanline, and bulk copies
  use `rep movsq`/`stosq` (an eighth of the iterations under TCG).
- **Animated transitions (`gfx_animate`, `wm_gfxview_ease`):** a
  graphics view change (fullscreen on/off, tile, snap, reset, minimize
  into the taskbar button, restore out of it) glides between the old and
  new frame with an ease-out cubic over 10 steps of 16 ms, paced by
  deadline against the PIT-calibrated clock. The desktop without the
  graphics layer is composed once as a background and each step scales
  the persistent source frame into the interpolated rect over it. The
  final frame is a plain redraw, so the end state is byte-identical with
  effects on or off; every failure degrades to that redraw.
- **Persistent graphics layer (`gfx_keep_*`, `vga_fb.c`):** every desktop
  redraw wipes the whole framebuffer, which used to bury any program that
  only composites on input — vedit/Nuklear sit blocked in `read` with no
  next frame coming, so Alt+Tab made the window vanish until the next
  keypress, with no way back. Every present now keeps a private copy of
  the SOURCE frame (the back-buffer bytes before scaling, sized for the
  largest source, the RGB Nuklear buffer; allocated once and never freed,
  no alloc/free races with the ISR tick, validity reset on mode-on), and
  `draw_desktop` re-composes it on top after the terminals at the current
  view. Because it is the unscaled source rather than screen pixels, the
  same frame re-renders correctly after a re-tile, a fullscreen toggle or
  mid-animation, which a screen-pixel copy could never do; the copy is
  taken right after the present reads the back-buffer, so an app drawing
  its next frame can never tear what the desktop re-shows.
- **Taskbar running-app button (`taskbar_render`, click):** while a graphics
  program owns the display the taskbar shows a small button right after the
  restore slot: the app's own 32x32 desktop icon downsampled to the 8px row
  plus its title, bright when focused. The icon resolves through
  `etc/shortcuts` (never a hardcoded list): `vga_fb_set_gfx_program`
  records the compositor — the shell's launch name for foreground runs,
  `procs[current_pid].name` attributed per frame for background jobs, so it
  is always whoever is actually on screen — and matches it against each
  shortcut's command binary (`run quake2generic.elf +set basedir .` matches
  `quake2generic.elf`); the window title against the shortcut name is the
  fallback (case-insensitive, `*` suffix ignored), text-only when nothing
  matches. This is why every app sets its title at startup (Nuklear, Piano
  and vedit call `SYS_GFX_SET_TITLE`; DOOM keeps the default): title-less
  programs all read "DOOM" and shared one icon. Clicking the button focuses
  the graphics window, which redraws it on top through the persistent layer
  — a buried app is always reachable. `wm list` reports it as
  `win gfxbtn x=.. w=.. icon|text` for the BDD pin.
- **Desktop art sources (`tools/gen_desktop_pngs.py` vs `gen_icons.py`):**
  custom art (wallpaper + per-app icons) converts from user PNGs in
  `images/`, pixel art (terminal) generates procedurally; the sets are
  disjoint by Makefile rule. Pokemon ships the `images/pokemon.png` Pikachu
  (32x32 RGBA like every icon), never the old generated pokeball. The art
  ships MiniFS-only (the 649 KB wallpaper cannot fit the ramdisk inside the
  `USER_LOAD_BASE` image budget), so `make art` regenerates it explicitly
  and both images depend on `DESKTOP_ART`: a first build after `make clean`
  never boots art-less. Missing art degrades silently by design (solid fill,
  embedded fallback icons), so a bare desktop means the files never packed,
  never a decode error.
- **GUI proof (`tools/test_gui_wm.py`):** serial `wm` commands share the
  functions but not the reality (blocking reads, frame timing), so the WM
  is also proven headless over QMP: real Alt+Tab/Super-Tab scancodes with
  vedit in the foreground, judged on pixels (vedit painted, identical after
  Alt+Tab, still painted after tile), then a background vedit whose taskbar
  button is clicked through a real relative-mouse walk, asserting serial
  `focus 2`. Serial goes over a unix socket (pipes make QEMU block-buffer
  stdout; sends are paced ~20ms for the 16-byte 16550 FIFO), stdin is held
  open (EOF exits QEMU), RAM is 1G (256M dies silently), and in practice
  QMP +y moves the cursor down.
- **Shell surface:** `date` prints `HH:MM:SS` from `rtc_read_tod` (a failed
  read prints a diagnostic); `vol [0-100]` prints the volume and, with an
  argument, sets it after strict decimal parsing and clamping; `kbd [en|es]`
  prints the keyboard layout and, with an argument, sets it (`toggle`
  switches). This is the
  TDD hook: the BDD suite asserts `date`, `vol` and `kbd` through the serial console.
- **Desktop effects, DOOM melt (`vga_fx.h`, `kernel/vga_fx.c`, `vga_fb.c`):**
  windows melt in and out like a DOOM level intro instead of flashing. The
  column logic mirrors `progs/doomgeneric/f_wipe.c` `wipe_initMelt`/
  `wipe_doMelt` (staggered per-column delays, then the new frame scrolls
  down over the old one) and lives header-only in `vga_fx.h` so `make
  test-fx` pins it on the host; the kernel owns only heap snapshots, the
  packed-pixel driver and TSC pacing. Trigger points are appear/disappear
  only: boot (`vga_fb_init` melts black into the desktop), graphics-window
  open (first composite after mode-on) and close (the redraw after
  mode-off melts the desktop over the last window rect), terminal
  minimize/restore, fullscreen on/off, `wm split` and `wm close`. Moves,
  resizes, snaps, tiles and focus changes never melt. Everything is
  heap-allocated and freed per transition (a fullscreen pair peaks at two
  800x600x4 snapshots; OOM degrades to a plain redraw), every rect clamps,
  the melt loop is frame-bounded, and the effect is synchronous, so the
  final frame is identical with it on or off and the QMP pixel suites stay
  deterministic. Pacing is by elapsed time, not by frame count: the driver
  advances as many virtual 8 ms melt frames as the clock says are due
  before each paint and waits on an absolute deadline, so a paint that runs
  slow never stretches or stutters the melt (the old loop slept a fixed
  8 ms after every paint, so the duration grew with the draw cost), and
  snapshots/restores move whole rows through `fb_read/write_row_packed`.
  A show/hide melt holds the present of the redraws in between, so the new
  frame is melted in from the shadow instead of flashing whole first. `fx` reports `fx: on melts=N` (`off` skips every
  transition; default on), `wm state` carries `wm: fx on`, and the melts
  counter is the serial proof a transition ran — a skipped melt leaves the
  same pixels behind, so the BDD suite pins `melts=1` after boot, `melts=3`
  after minimize+restore and `melts=5` after a Nuklear selftest
  (open+close), beside the `gfx frames` climb. Eight `fx-*` mutants
  (default, toggle, reporting, skipped melts, stuck/clamp column logic)
  die in `make test-fx` and the `MATCH=fx` BDD slice.
