# Ring-3 apps: vedit, file, paint, themes, Lua, MicroPython, Lisp, Nuklear, Quake 2, doomedit

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### Mini IDE (`vedit`, ring 3, Nuklear)
`bin/vedit` is the fullscreen visual editor, deliberately a user-space
program, never kernel code: the kernel image ends ~1 KB below
`USER_LOAD_BASE`, so a 14 KB in-kernel visual editor overflowed the user
window and killed the boot (measured `_kernel_end 0x403220`). The editor
lives in `progs/vedit/vedit.c`, is built on the host like the piano and
the node editor (static ELF, shared `nuklear_minios.c` platform layer),
and ships on MiniFS (`vedit.elf` plus the bare-name alias, source
beside it). Commands: `vedit [file]` (the file is optional; the
default buffer is `untitled`), plus the headless proofs
`vedit --selftest`, `vedit --selftest-build` and
`vedit --selftest-leak`. The full key guide lives in
`progs/vedit/README.md`.

- Interaction: arrow-key navigation with in-place typing (no line
  numbers to name), Enter splits with auto-indent, Tab inserts a stop,
  Backspace/Delete erase and join, Home/End/PgUp/PgDn jump, `^O`/`^S`
  save, `^N` save-as, `^W` find (wraps once), `^G` goto line, `^R`
  build/run by extension, `^L` link (prompts `elf|cvm`), `^X`
  save+quit, Esc or `^Q` quit without saving, `^D` dumps the buffer with ANSI
  highlight to the console (serial fallback and BDD hook; moved from
  `^L` so the linker owns `^L`). uemacs adoption (buffers, region,
  search, windows, macros, shell, in the same file, every bound in
  `VEDIT_*`): 8 buffers (`M-x find-file/view-file/insert-file`,
  `select-buffer`, `next-buffer`, `kill-buffer`, `list-buffers`, Buf
  button, recent-file history), mark/region (`^@`, `M-w` copy, `M-k`
  kill, 8-deep kill ring, `^K` kill line, `^Y` yank), word ops (`M-f`/
  `M-b`, `M-c`/`M-l`/`M-u` case), `^T` transpose, `^]` goto fence,
  `^U` universal arg (repeat motions/kills/inserts, digits accumulate),
  `^A`/`^E` bol/eol, `M-s`/`M-r` incremental search (type to narrow,
  Backspace to widen, Enter keeps, ESC restores), `M-n` hunt,
  `M-%` query-replace (`y/n/!/q`), `M-x replace-string`, magic
  search (`M-x search-forward-magic`: `. * ^ $ [class]`, host-pinned),
  `M-q` fill paragraph to 72 columns (`VEDIT_FILL_COL`), stacked 2-pane
  split (`M-2`/`M-1`/`M-o`),
  keyboard macros (`M-( M-) M-e`, depth-guarded), `M-x` named commands
  (46, `help` lists keys on the console), `bind-to-key` plus
  `/etc/vedit.rc` + `./vedit.rc` startup (`bind <key> <cmd>`, bare
  commands), `M-!` shell capture into `*shell*`, `M-#` filter region
  (or the whole buffer when no region is set) through a program,
  `M-x grep` (magic) into `*grep*` with `next-error`,
  read-only toggle, overwrite toggle, `~` backup on save with
  changed-on-disk armed-force, stat-backed mtime guard, status row
  (`name [Lang] B1/8 Ln 12/300(4%) Col 5` plus the `RO OVR REC MRK
  SEL META ARG` flags and a trailing message). Clipboard Phase 2 is
  wired: mouse drag selects into syscalls 249/250 (4 KB, fail closed,
  inverted highlight, `SEL` flag), `M-v`/`M-x paste` pastes, `M-W`/
  `M-x copy-to-clipboard` copies the emacs region, and the shell
  `clip` builtin shares the same 4 KB slot; `--selftest-build` proves
  the wire live (set/get roundtrip plus the
  oversize/undersize refusals). Save/Find/Name/Run/Link/
  Buf/M-x/Done are also clickable buttons (labels `^O Save`, `^W Find`,
  `^N Name`, `^R Run`, `^L Link`, `Buf`, `M-x`, `^X Done`); the wheel scrolls by moving the cursor (the old
  code moved only the viewport offset, which the cursor-follow pass
   snapped straight back, so wheeling long files did nothing). A
   4096-line / 255-char heap buffer (1 MB pool, so real sources like
   `freedom.c` at 1236 lines open whole)
   with the same fail-closed rules as `edit`: full lines, overflowing
   joins and full buffers refuse whole, and a truncated load refuses
   to save and to build. There is no undo stack (uemacs never had
   one). The frame loop polls instead of blocking on a
   key (8 ms pacing like the node editor) so wheel and mouse drain every
  frame; the ESC `[` decoder is a cross-frame state machine with a
   1000 ms timeout, degrading to a bare Esc instead of hanging. A
   scripted quit must therefore not carry a trailing newline: the decoder
   would read it as the second byte of a sequence and turn the quit into
   a Meta key (the BDD scenario quits with `^Q` for that reason).
- Key prefixes: `^X` is Control+key; `M-x` is ESC then the key
  within one second (`VEDIT_ESC_MS` 1000), and the status row shows
  `META` while that prefix is armed, so a lone ESC quits only after
  the same one-second pause. Holding Alt just types the letter (the
  PS/2 driver folds Ctrl+letter into a control code only, and nothing
  else, in `drivers/kbd.c`), and physical Ctrl+Space arrives as a
  plain space, so `M-SP` (ESC, Space) is the reliable set mark. If
  no key responds at all, the terminal owns the keyboard: focus the
  graphics window (Alt-Tab or its taskbar button) and try again.
- Build/run (`^R`, `^L`, single-file contract in `progs/vedit/vedit.c`):
  `^R` saves then routes by extension through `SYS_SPAWN` (215) so the
  IDE survives the child: `.c`/`.h` compile with
  `objects/minigcc.o <file>` redirected to `asm/<base>.s`, `.s` links
  with `objects/ld.o -f elf -o bin/<base>.elf`, signs with `sign` and
  runs the result
  (same as `^L` answering `elf`, without prompting), `.lua` runs
  with `lua <file>`, `.py` runs with `micropython <file>`, `.lisp` runs
  with `lisp <file>`; the routing
  lives in `vedit_run_kind` (mirrored by `t_run_kind` in
  `tests/test_vedit_build.c`, so drift fails `make test-vedit`). `^L`
  prompts `link elf/cvm: ` and links `asm/<base>.s` with
  `objects/ld.o -f <fmt> -o bin/<base>.elf|cvm/<base>.cvm`, signs an
  ELF with `sign`, then runs
  the freshly linked artifact (`cvm.o` for a `.cvm`, the ELF directly)
  so its output lands on the console without leaving the IDE. A
  redirect whose commit fails is loud, never a silent drop: the spawn
  layer reports `SPAWN: redirect to <path> failed` on the live console
  and the IDE names the missing log file. Every
  build drops `SYS_VGA_MODE` first so the desktop terminal stays
  ordered and the toolchain log lands on the console, then resumes the
  IDE and reports the exit code in the status row. `mrun` stays the
  shell-level multitask path (`mrun vedit.elf &` tiles the IDE beside
  the terminal with Super+Tab); in-IDE builds use synchronous `SPAWN`
  because `mrun` is a shell builtin, not a syscall. All bounds, keys,
  tools, directories and formats live in the centralized `VEDIT_*`
  config. The tool and artifact paths are root-anchored (`/objects/`*,
  `/asm/`, `/bin/`, `/cvm/`), never host paths, so editing a file in a
  subdirectory (`cd src`) still resolves the toolchain and outputs at
  the system root instead of under the cwd.
- Highlighting: C (`.c`/`.h`, with `//` and `/* */` plus `#`
  directives; also the default for `untitled` until a name with an
  extension is given), Assembler (`.s`, AT&T x86-64: `#` and `/* */`
  comments, `.directives` in preproc ink, `%registers` in number ink,
  `label:` in string ink, mnemonics in keyword ink), MicroPython (`.py`,
  with `#` and triple-quoted strings)
  and Lua (`.lua`, with `--`, `--[[ ]]` blocks and `[[ ]]` strings);
  Lisp (`.lisp`, with `;` comments, `"` strings, numbers and the special
  forms plus MiniOS primitives in keyword ink; dashed names like
  `string-length` match on their alpha segments because the shared
  word scanner stops at `-`);
  keywords, strings, comments, numbers and directives each get an ink,
  drawn as per-token runs on the canvas with a block cursor. The `.s`
  routing is mirrored by `t_lang_of` in `tests/test_vedit_build.c`, so
  spec drift fails `make test-vedit`. The file browser opens `.lisp`
  in vedit through `etc/association` (`lisp|/vedit`).
- Plumbing: every platform fact comes from `minios_abi.h` or a
  syscall, never a literal. Keystrokes arrive through syscall 236
  `GETC_RAW` (0 polls with `-1` when idle for the bounded ESC-sequence
  wait, nonzero blocks), the same serial+PS/2 multiplexer the console
  reads but with no line buffering, echo or scrollback detour, so
  PgUp/PgDn reach the editor; the PS/2 driver reports Ctrl+letter as
  control codes and Delete as `ESC [ 3 ~`, so both consoles drive every
  key. The app owns the display through `SYS_VGA_MODE` exactly like the
  piano, the window title carries the dirty `*`, and the kernel redraws
  the desktop on exit. `vedit --selftest` renders one frame and proves
  the composite landed, mirroring the Nuklear selftest.
  `vedit --selftest-build` checks the headless build contract (untitled
  defaults to C, extension routing, base/path joins, `elf|cvm` parsing,
  `^R`/`^L`/`^D` shortcuts) and prints `vedit: build ok`; the BDD suite
  pins it and `make test-vedit` locks the same vectors on the host
  (including a `t_lang_of` mirror of `vedit_lang_of`, so spec drift fails
  the build). The scanner shares `vedit_parse_string`/`vedit_parse_number`
  (C-only quote flag)/`vedit_parse_keyword` helpers; per-language quirks
  (C `#`/`/* */`, Python triple-quote, Lua long brackets, Lisp `;`)
  stay in the caller.
- Allocation discipline: the insert path (`insert-file`, `M-!` capture)
  borrows a reusable scratch arena that grows to the largest file seen
  and resets per load, so repeated builds stop churning one
  malloc/free pair per run; buffers and the scratch free exactly once
  at exit and `kill-buffer` frees its pair. `vedit --selftest-leak`
  pins the contract headless (scratch reuse, growth, one buffer
  lifecycle, drained live set, `vedit: leak ok`), and the whole unit
  compiles with the `headers/leakcheck.h` tracker enabled.
- The kernel `edit` stays: scripted flows (the MCP `minios_write`
  editor upload, the marketplace, the BDD suite) drive it
  non-interactively, which a fullscreen program cannot serve.

### File browser (`file`, ring 3, Nuklear)
`bin/file` is the graphical file browser, a ring-3 Nuklear app built like
vedit (host gcc `-static`, MiniFS with a bare-name alias, source beside
it at `progs/file/file.c`, one file per contract with a centralized
config). Commands: `file` (GUI: navigate, open, run, preview) and
`file --selftest` (headless: assoc vectors plus a live listing).
It lists the unified filesystem (ramdisk first, MiniFS fallback)
through the DIR_LIST syscall (241, `MINIOS_SYS_DIR_LIST`), which fills a
user buffer with NUL-separated names (dirs carry `/`) and returns the
count, fail closed on bad pointers, overlong names and truncation.

- Dispatch comes from `etc/association` (plain `ext|program` lines, the
  same shape as `etc/shortcuts`): text kinds (`c h s txt py sh lua html`)
  open in `/vedit` through `SYS_SPAWN`, `o|elf|cvm` run through `shell`
  semantics (ELF/o spawned directly, cvm through `/objects/cvm.o` with
  the module as `argv[0]`), `png|internal` decodes in-app with stb_image
  and blits downscaled into the NK back-buffer after rasterize, through
  the shared `progs/minios_png.h` helpers (bounded load, scaled
  RGB-to-indexed, blit) that the pokemon side fringes also use. Preview
  sources reach `MPNG_BIG_DIM` (2048) through
  `mpng_rgb_to_idx_scaled_big`, so an 800x600 wallpaper previews while
  icons and policy art keep the 512 source bound. Unknown
  kinds report instead of running. Assoc parsing is fail closed: only
  `[a-z0-9]` exts, programs are absolute paths or `shell`/`internal`, and
  a `|` inside the program rejects the line.
- The dock carries `File|icons/file.png|file` beside a Terminal shortcut
  that now uses the custom `icons/shell.png` art; both PNGs convert from
  the `images/file.png`/`images/shell.png` sources through
  `tools/gen_desktop_pngs.py` like every other icon. The dock bar paints a
  crystal checker (`DOCK_CRYSTAL_STEP`) over the wallpaper and magnifies on
  hover (hot icon 2x to `DOCK_MAG`, neighbours 1.5x to `DOCK_NEAR`,
  bottom-aligned); the mouse tick repaints only the dock strip (wallpaper
  rect erase, no clear, no terminal re-render) once per hover change, so
  there is no fullscreen flash, and it stays out while a button is down,
  a drag is live, or a fullscreen terminal hides the dock. A click arms a
  Mac-style bounce on the clicked icon (`dock_bounce_kick` in `vga_fb.c`):
  two full parabolic hops (peaks 24/14 px over `DOCK_BOUNCE_TICKS`
  = 90 sys_ticks, 0.9 s, integer-only in `dock_bounce_height`, both hops
  starting and landing at exactly 0) painted by the same strip path.
  Flicker discipline: a repaint is an erase (wallpaper flash) plus a
  redraw, so the tick repaints only on a real change — a new bounce
  height (`dock_last_bounce_h`, exact under a held timer IRQ so no torn
  read doubles into a redundant flash) or a hover that persisted two
  consecutive ticks (a pointer on a cell edge jitters ±1 count between
  neighbours). Repaint count therefore equals the height transitions
  (58), never the idle-tick rate. The launch stays pending (`dock_pending_cmd`) until the hops
  finish and only then runs `desktop_launch`, because a synchronous launch
  in the click tick blocks the shell loop that drives the strip and zero
  bounce frames ever paint (measured: instant launch = no visible hop).
  While a user program owns the CPU the ISR tick still animates, and the
  pending launch degrades to the queued `shell_pending_cmd` path instead
  of re-entering `k_exec_user` from ISR context. Serial proof: `wm state`
  reports `wm: bounce kicks=N paints=M edges=K pending=P`, and `wm list`
  prints one `win dockN x=.. y=.. w=.. h=.. <cmd>` line per icon, so a
  headless QMP driver clicks exact coordinates (verified: dock0 click at
  its listed center gives `kicks=1 paints=89 edges=1`, mid-bounce pixels
  move 30x above the identical-frame noise floor, then `wm split` lands).
  Tiled terminals cover the dock row, so a click there is a focus change,
  never a bounce: prove the bounce in the single-terminal layout.
- Entry icons come from `images/` (`folder.png` dirs, `files.png` text
  kinds, `image.png` `.png`, `object.png` `.o/.elf/.cvm`, unknown falls
  back to `files.png`), decoded to indexed pixels plus an alpha mask and
  drawn through the backend `NK_COMMAND_IMAGE` path; a `big icons` /
  `small icons` button toggles 32 px (2 columns) vs 16 px (4 columns) with
  one reload and no extra memory. All-or-nothing load, so the UI never
  mixes icon and text rows.
- Proof: `file --selftest` runs the assoc vectors plus a live `/`
  listing (`file: ok (N entries at /, theme dark)`, BDD-pinned), and
  `make test-file` locks the same parser vectors on the host. The
  selftest asserts a drained allocation live set (`file: leak ok`) over
  the icon/preview decode and assoc paths with the
  `headers/leakcheck.h` tracker enabled, and the browser frees the
  assoc table on GUI exit; `make test-leakcheck` locks the tracker
  plus an assoc push/clear/free cycle on the host.
- Every NK app quits the same way: ESC or Alt+F4 through the platform
  latch (`nk_quit_requested` in `nuklear_minios.c`, polled per frame)
  plus an on-canvas Quit control (file's `quit` button, paint's `quit`
  button, piano's `Quit` pad, the node editor's existing Quit; vedit
  already exits on Esc/^X).
  No window depends on the title-bar X alone.

### Paint program (`paint`, ring 3, Nuklear)
`bin/paint` is the canvas paint program, a ring-3 Nuklear app built like
the file browser (host gcc `-static`, MiniFS with a bare-name alias,
source beside it at `progs/paint/paint.c`, one file per contract with a
centralized config). The canvas is 320x200 palette indices blitted into
the NK back-buffer after rasterize (the file-preview pattern); that
back-buffer is the shared `NK_BACKBUF_ADDR` window, presented through
`SYS_NK_FRAME` (220) like every other NK app. The widget
bounds from `nk_widget` are the single source for both the blit offset
and mouse hit-testing, so no screen coordinate is hardcoded. There is no
GLFW or OpenGL anywhere: MiniOS has no GPU stack, only the 8-bit
composited back-buffer, so the desktop GLFW demo layout does not apply.
Commands: `paint` (GUI: draw, save to the default `/drawing.png`),
`paint <file>` (preloads it) and `paint --selftest`
(headless: vectors, png, file, frame). Build: `make progs/bin/paint.elf`
(or just `make` to rebuild everything).

- Layout: the white canvas cell is exactly 320 px wide (`PAINT_W`), so
  every white pixel shown is paintable; the tools, the 16 swatches and
  the size buttons live in the side panel beside the canvas, never
  above an oversized slot.
- Tools: brush, line, rect, circle, fill and eraser with sizes 1/2/4;
  a 16-swatch picker drawn from exact hybrid-palette entries (black, the
  14 saturated accents, white), so a saved PNG reloads pixel-identical
  (nearest-mapping ties resolve to an identical RGB, never a wrong
  color). Some swatches tie with the 6x6x6 cube (black and white live
  in both ranges), so the selftest asserts by RGB color, never by
  index. Shape tools rubber-band from a 64 KB backup copy taken at
  stroke start. The status row always shows tool, swatch, size and the
  last file result.
- PNG save/load is self-contained: the writer emits 8-bit truecolor PNG
  with stored-deflate blocks, CRC-32 and Adler-32 (no third-party encoder
  dependency; `stb_image_write` is not vendored), and the reader decodes
  through stb_image and nearest-maps onto the hybrid palette, top-left
  clamped with white margins. Paths go through a fail-closed gate
  (printable ASCII, bounded, `.png` suffix, no `..` traversal).
- The dock carries `Paint|icons/paint.png|paint`; the icon converts from
  the `images/paint.png` source through `tools/gen_desktop_pngs.py`
  like every other icon. `paint <file>` opens the GUI preloading that
  file; the title `Paint` matches the shortcut name for the taskbar icon.
- Proof: `paint --selftest` runs the core vectors, a 2x2 encode/decode
  roundtrip (`paint: png ok`), a save/load roundtrip through the unified
  filesystem (`paint: file ok (/paint_selftest.png)`) and one composited
  frame (`paint: frame ok (800x360)`), all BDD-pinned; `make test-paint`
  locks the mirror vectors plus the PNG byte-layout pin (192278 bytes
  for the canvas) on the host. The frame probe scans the whole
  framebuffer for a unique 4-pixel pattern instead of trusting the window
  origin report, so it holds in any video mode (an 8-bit exact check
  would fail where the origin report is stale, which the nuklear origin
  check does on a truecolor fallback boot). Present and scan retry up
  to three times with no serial output in between: a print takes
  milliseconds over serial and opens windows for the 25 Hz desktop tick
  between them.
- Interactive strokes (drag painting) have no headless proof by
  construction; the hit-testing shares the blit rect by construction, so
  a landed blit implies aligned input.

### Nuklear themes (`nuklear_theme`, all NK apps)
`progs/nuklear/nuklear_theme.c` (header `nuklear_theme.h`) is the one
theme loader every NK app links through `NUKLEAR_PLATFORM` (file,
nuklear, piano, vedit, paint): each calls `nk_theme_apply(&ctx, 0)` after
`nk_init_fixed`, which resolves `/etc/themes/current` (else `dark`),
loads `/etc/themes/<name>` over a compiled-in fallback and pushes the
32 colors via `nk_style_from_table`. A theme file is `key r g b` lines
(the key list is the `NK_THEME_KEY_LIST` X-macro shared with
`tests/test_theme.c`, so no copy can drift); shipped values sit on the
6x6x6 cube (multiples of 51) so the 8-bit backend maps them exactly
instead of nearest-neighbour. Fail closed: unknown keys skipped,
numbers clamped, overlong lines drained, bad names fall back to `dark`.
Switching is a write to `current` (`echo light > etc/themes/current`)
and a relaunch; no reboot, no rebuild. The taskbar shows the active
name left of EN/ES (bright, `TASKBAR_THEME_CH` wide, `TASKBAR_PAD`
breathing room like every other widget since the crowding fix) and a
click cycles `etc/themes/` in ramdisk order with wraparound, writing
the choice back; `wm state` reports it as `wm: theme <name>` (BDD-pinned)
so the widget is serial-observable. Proof: `file --selftest` prints
the active theme name (BDD pins `theme dark`), `make test-theme` pins
the contract plus all five shipped files (`dark light amber forest
slate`, 32 keys each, unique, palette-exact, `current` naming an
existing file). Build: `make progs/bin/nuklear.elf` (or just `make` to
rebuild everything).

### Lua (`lua.elf`)
Lua 5.4 runs inside MiniOS exactly like DOOM and MicroPython: the
upstream reference interpreter is cloned as a sibling checkout and
built on the host with the ordinary gcc toolchain against the static
glibc, and the resulting `ET_EXEC` binary ships on MiniFS, where it
runs as a ring-3 process through the Linux syscall ABI. The upstream
`lua.c` main is replaced by `progs/lua/lua_main.c`, which registers
the `minios` C module (`progs/lua/minios.c`) globally before any
script runs, so the kernel services are a plain global table exactly
like `import minios` in MicroPython.

- **Source**: `LUA_DIR` (default `../lua`), `LUA_URL` and the pinned
  release tag `LUA_REF` (v5.4.7) are overridable like every toolchain
  location, and `make sources` clones it with
  `--depth 1 -b $LUA_REF`; an existing checkout is never touched
  (`docs/spec/source.md` owns that contract).
- **Build**: `gcc -static -no-pie` against the upstream library
  sources plus `progs/lua/{minios.c,lua_main.c}`, exactly the linking
  contract DOOM follows. The ELF is copied to `progs/bin/lua.elf` and
  packed into `minifs.bin` at its root together with the `lua`
  bare-name alias, so it never inflates the kernel image.
- **CLI**: `lua -e <expr>`, `lua -l minios` (the only loadable
  library, the statically linked module itself), `lua -v`/`--version`,
  `lua <script> [args]` and `lua` for the interactive REPL; the banner
  is `Lua 5.4  (MiniOS)  type 'os.exit()' to quit`, the REPL reads
  stdin from the serial console and a line starting with `=` means
  `return <expr>`. `run lua.elf`, bare `lua.elf` and bare `lua` all
  work. Scripts are opened through the unified filesystem (ramdisk
  first, MiniFS fallback).
- **Bindings** (`progs/lua/minios.c`): `minios.time_ms()` (ms since
  boot), `minios.rtc()` (hour, minute, second from the CMOS clock),
  `minios.fb_info()` (width, height, pitch), `minios.vol([v])`
  (PC-speaker volume 0..100), `minios.pal(buf)` (768-byte VGA DAC
  palette), `minios.pcspeaker(freq, ms)` (tone for `ms` milliseconds)
  and `minios.run(path[, args][, redirect])`.
- **Spawn**: `minios.run` invokes `SYS_SPAWN` (215), which runs a
  child program while preserving the Lua interpreter (user window,
  file descriptors, brk and mmap cursors), so a script orchestrates
  the toolchain from inside the OS. `args` is a table of strings (a
  non-table is an error) and `redirect` is a single output-file path
  that captures the console output; the call returns the child exit
  code, or `nil` plus `spawn failed` when the kernel refuses:

  ```
  miniOS> lua -e "minios.run('/objects/minigcc.o', {'/src/fib.c'}, '/asm/fib.s')"
  miniOS> lua -e "minios.run('/objects/ld.o', {'-f','elf','-o','/bin/fib.elf','/asm/fib.s'})"
  miniOS> lua -e "minios.run('/bin/fib.elf')"
  exit code: 0
  ```

  The kernel resolves the path against the cwd, so a bare
  `objects/minigcc.o` depends on where the shell stands; the
  root-anchored `/objects/...` form is the portable one.
- **In-OS suite**: `src/test.lua` (on the ramdisk next to
  `src/test.py` and `src/test.lisp`) exercises the `time_ms`, `rtc`,
  `fb_info`, `vol` and `run` bindings, the filesystem and the
  compression and encryption tools (the `lz4`, `lzss` and `aes`
  roundtrips through `minios.run`). It covers neither `pal` nor
  `pcspeaker`.

## MicroPython (`micropython.elf`)
MicroPython runs inside MiniOS exactly like DOOM does: the upstream project
is cloned as a sibling repository, built on the host with the ordinary gcc
toolchain against the static glibc, and the resulting `ET_EXEC` binary ships
on MiniFS, where it runs as a ring-3 process through the Linux syscall ABI.
No MicroPython source is ever compiled by miniGCC, and nothing reaches into
the MicroPython checkout for content MiniOS owns: the port lives in this
repository as an out-of-tree unix-port variant.

- **Source**: `MICROPYTHON_DIR` (default `../micropython`), overridable like
  every toolchain location; `MICROPYTHON_URL` and the pinned release tag
  `MICROPYTHON_REF` are overridable too. `make sources` clones it with
  `--depth 1 -b $MICROPYTHON_REF`; an existing checkout is never touched.
  The shallow clone is enough: the MiniOS build needs no git submodules
  (no FFI, no SSL, no berkeley-db).
- **Variant**: `progs/micropython/variants/minios/{mpconfigvariant.h,
  mpconfigvariant.mk}` is a variant of `ports/unix` selected at build time
  through the `VARIANT_DIR` mechanism, so the upstream checkout carries no
  modifications. The configuration keeps the compiler, floats, computed-goto
  (`MICROPY_OPT_COMPUTED_GOTO`), the `os`
  module, sockets, `select.poll`, `time` and the frozen `mip` installer
  (docs/spec/python.md owns that surface), and disables readline (the
  kernel console is a cooked, line-based device with its own echo),
  threading, SSL, FFI, termios, VFS layers and native emitters.
- **Build**: `make` builds `mpy-cross` and then the port with
  `LDFLAGS_EXTRA="-static -no-pie"`, exactly the linking contract DOOM
  follows; the ELF is copied to `progs/bin/micropython.elf` and packed into
  `minifs.bin` at its root together with the `micropython` bare-name alias,
  so it never inflates the kernel image (`< 3 MB` contract). `run
  micropython.elf`, bare `micropython.elf` and bare `micropython` all work;
  `micropython -c "expr"` evaluates, `micropython src/script.py` runs a file
  (opened through the unified fs: ramdisk first, MiniFS fallback), and bare
  `micropython` reads the interactive REPL from stdin (the serial
  console). The process exits
  with `exit code: N` like any other program.
 - **Kernel ABI**: the binary leans on the same glibc-static stub set DOOM
   proved (`open/openat`, `read`, `write`, `brk`, `mmap`, `fstat`, ...). The
   unix port's `realpath()` of script paths needs the cwd and directory/type
   information, so the kernel implements `getcwd` (79, returns the shell
   `fs_cwd`), `newfstatat` (262, reports `S_IFREG`/`S_IFDIR` with size from
   the unified filesystem, `ENOENT` when missing) and `readlink` (89, returns
   `EINVAL` since MiniOS has no symlinks, so glibc's `realpath()` keeps
   resolving) with the same user-pointer validation as every other dispatcher
   case. Anything else the C library probes (`statx`, signals, ioctls)
   degrades through `-ENOSYS` or existing stubs, never through kernel crashes.

 - **ELF entry registers**: `k_exec_user` zeroes `rdi`, `rsi` and `rdx` before
   the `iretq` to the program entry, exactly as Linux does at `exec`. glibc's
   `_start` reads `%rdx` as `rtld_fini`; a leftover kernel value would make
   `__libc_start_main` register that garbage address as an exit handler and
   `__run_exit_handlers` would demangle and call it on exit — the historical
   MicroPython crash (`EXCEPTION 14`). This is a hard requirement for any
   ring-3 glibc binary.

- **`minios` module + `SYS_SPAWN` (215)**: the variant ships a `minios` C
    module (`progs/micropython/variants/minios/minios_module.c`) exposing
    `time_ms()`, `rtc()` (hour, minute, second), `fb_info()` (width,
    height, pitch), `vol([v])` (0..100), `pal(buf)` (768-byte VGA DAC
    palette), `pcspeaker(freq, ms)` and `run(path, args=None,
    redirect=None)`; `args` must be a list or tuple of strings (max 64)
    and `redirect` is a single output-file path that captures the
    console output; `run` returns the child exit code and raises
    `OSError` on a kernel fault. `SYS_SPAWN` runs a ramdisk
    program from the interpreter while preserving it.  ET_REL children
    (`minigcc.o`, `ld.o`) run at ring 0 through `k_run_rel`; ET_EXEC/ET_DYN
    children run in a fresh isolated window via `proc_spawn_elf` (the same
    path `mrun` uses) and the caller blocks in `do_waitpid`, so the parent
    address space, FS/GS base, fd table and brk/mmap cursors are untouched.
    This drives `build.py`, `shell.py` and `test.py` on the ramdisk
    (`micropython src/build.py` chains minigcc to ld to run and builds
    every target by default, `micropython src/shell.py` is the pybash
    layer with variables, pipelines and output capture, `micropython
    src/test.py` verifies the kernel bindings and the toolchain from
    inside the machine and then runs every non-graphical binary).  The
    exec frame's kernel stack is `EXEC_KSTACK_SZ` (64 KB, `kernel/exec.c`):
    it must hold a ring-0 toolchain child's deep recursion (minigcc/ld), and
    a child that overflowed the old 32 KB stack wrote into adjacent kernel-heap
    page tables, making the parent's `pt_free_user` spin on the corruption.

## Lisp (`lisp.elf`)
Lisp runs inside MiniOS exactly like Lua does: a ring-3 `ET_EXEC` binary
built on the host with `gcc -static -no-pie` against the static glibc,
shipped on MiniFS as `lisp.elf` plus the bare-name alias, running through
the Linux syscall ABI. The difference from Lua and MicroPython is that
there is no upstream checkout: the interpreter is one self-contained
translation unit in this repository (`progs/lisp/lisp.c`), so there is no
sibling directory to clone and `LISP_DIR` does not exist.

- **Language**: int64 numbers, strings, symbols, cons cells and closures
  with lexical scope. Special forms are `quote`, `if`, `begin`, `define`,
  `set!`, `lambda` and `let`; builtins cover arithmetic, string ops,
  `car`/`cdr`/`cons`, predicates (`null?`, `number?`, `string?`),
  `error-message`, files (`open-file`, `read-char`, `write`,
  `close-file`), `exit`, and the MiniOS primitives `time-ms`, `rtc`,
  `fb-info`, `vol`, `pal`, `pcspeaker` and `minios-run` (SYS_SPAWN 215,
  same isolated-window path the other interpreters use). CLI is
  `lisp [-e expr] [script [args]]` with an interactive REPL on stdin
  (banner `Lisp 2.1 (MiniOS)`);
  `lisp src/test.lisp` runs the in-OS suite (the file is on the ramdisk
  next to `src/test.lua` and `src/test.py`). `run lisp.elf`, bare
  `lisp.elf` and bare `lisp` all work. `minios-run` takes a path, an
  argument list and a redirect file, and answers the child exit code:

  ```
  miniOS> lisp -e '(minios-run "/objects/minigcc.o" (quote ("/src/fib.c")) "/asm/_t.s")'
  0
  ```
- **Fail-closed arithmetic**: `+`, `-`, `*` use overflow-checked builtins
  and `/` guards zero and `INT64_MIN / -1`; a violation is an error
  value, never a wrap. File modes are whitelisted to read/write/append
  (`r`, `w`, `a` plus binary), allocation and input sizes are bounded by
  one config enum, and eval/print depth is capped so a cyclic structure
  prints `<depth-exceeded>` instead of recursing forever.
- **Errors are values**: a runtime fault evaluates to an error node that
  travels through argument lists and `define`/`set!`/`let` bindings like
  any value, and prints to stderr at the top level with a nonzero exit.
  It propagates through `if` conditions and `begin` sequences instead of
  branching, so tests must never assert on a bare error expression: the
  suite binds errors through `error-message` and guards with `string?`
  first (`check-error`, `check-spawn` in `progs/src/test.lisp`). An
  assertion shaped `(string-eq (error-message X) msg)` passes vacuously
  when `error-message` regresses to nil, because the resulting type error
  itself aborts the check truthy through the suite's `if`; the `string?`
  guard is what kills that mutant.
- **Build**: `make progs/bin/lisp.elf` from `progs/lisp/lisp.c` plus
  `minios_abi.h`; `make test-lisp` runs `tools/test_lisp.py` (host,
  49 vectors: arithmetic, fail-closed errors, closures, strings, files,
  predicates, CLI flags, the shipped suite in language-only mode, plus
  the minigcc subset end to end through the host `as`/`ld` and through
  the MiniOS `ld -f elf` itself, plus the minigcc usage/version CLI).
  `tools/lisp_scoped.sh` is the scoped gate (static ELF rebuild with
  zero warnings plus 7 targeted mutants, all killed, plus 7 minigcc.lisp
  codegen/CLI mutants). `mutate.sh`
  routes `progs/lisp/lisp.c` mutants to `make test-lisp`.
- **minigcc.lisp subset compiler** (`progs/lisp/minigcc.lisp`, v0.3):
  a C compiler written in MiniOS Lisp, shipped on MiniFS beside `lisp.c`
  (plus the `tin.c` demo fixture) so
  `lisp minigcc.lisp tin.c > out.s` works in-OS. With no file argument,
  `-h`/`--help` or `-v`/`--version` it prints the compiler name, version
  and usage instead of compiling, exiting 1 on missing input and 0 on
  flags. It compiles one or more `int` functions in order, each shaped
  `int f(int a, ...){ return <expr>; }` with int or void params, a
  single return body, and expressions of integers, params, calls,
  `+ - * /` and parentheses (max 6 params and 6 args). Frames mirror
  `../miniGCC` (`-(16+8i)(%rbp)` param slots) with the same
  push-left/pop-rcx operand order (`rax` holds right, `rcx` holds
  left); calls follow System V (args pushed left to right, odd counts
  padded with the pad discarded into `r10`, popped into `rdi`..`r9` in
  reverse, result in `rax`, stack-neutral so nested calls work); the
  epilogue emits the same `_start` entry wrapper minigcc does, because
  without it `ld` sets the entry to `main` directly and the first `ret`
  jumps wild. Anything outside the shape is a diagnostic plus exit 1,
  never bad assembly. Host proof is 8 semantic vectors assembled,
  linked and executed plus 4 fail-closed vectors; the BDD scenarios
  link the in-OS output with `ld.o` and assert `exit code: 42` for
  `tin.c` and `exit code: 12` for the real two-function `test.c`, and
  assert the no-args run prints the usage line with exit 1. Later
  versions widen the shape toward full `minigcc.c`; the token model
  (cons cells of kind and value, no `set-cdr` so the list builds
  reversed) and the emit helpers are the stable interface for that
  growth.
- **History**: the first version printed every number with a stray `%`
  prefix (`"%%" PRId64`, the exact `-Wformat-extra-args` warning the
  user reported) and had no overflow checks; both are now pinned by
  host vectors and mutants.

## Nuklear node editor (`nuklear`)

Nuklear runs inside MiniOS exactly like DOOM and MicroPython: the upstream
single-header immediate-mode UI library is cloned as a sibling repository and
built on the host with the ordinary gcc toolchain against a static libc. The
resulting ring-3 `ET_EXEC` binary ships on MiniFS and renders through the
same kernel compositing path the DOOM window uses. The demo app is a visual
node editor: a "low-code tool for the CVM" that compiles a dataflow graph
into a `.cvm` module the interpreter runs.

- **Source**: `NUKLEAR_DIR` (default `../nuklear`), overridable like every
  toolchain location, cloned by `make sources`; `NUKLEAR_URL` is overridable
  too. The build compiles `progs/nuklear/{nuklear_minios.c,node_editor.c,
  cvm_emit.c}` with `-I$(NUKLEAR_DIR)` into `progs/bin/nuklear.elf`
  (`-static -no-pie`, the same linking contract DOOM follows), plus the
  bare-name alias `progs/bin/nuklear`, both packed into MiniFS. The node
  editor's compiler lives in this repository (`progs/nuklear/cvm_emit.c`),
  never in the Nuklear checkout.
- **Platform layer (`nuklear_minios.c`)**: the app renders Nuklear's abstract
  draw commands (`nk__begin`/`nk__next`) into an 8-bit palette-indexed
  back-buffer mapped into the user window at `NK_BACKBUF_ADDR` (0x0B600000,
  `NK_W`x`NK_H` = 800x360) and, when the kernel maps it (ABI v7,
  `NK_RGB_ADDR` 0x0B700000, probed once through the `fb_info` 4th word),
  into the RGB companion (same geometry, 3 bytes per pixel) with the
  command's true `nk_color`; it then presents indexed (`SYS_NK_FRAME`
  220 / `GFX_PRESENT` id 1) or full-color (`GFX_PRESENT` id 2,
  `MINIOS_GFX_BUF_NK_RGB`). The kernel composites it as a titled window
  on the desktop, identical to the DOOM window, leaving the shell visible.
  A software rasterizer handles the full command set (scissor, line, rect,
  circle, arc, triangle, polygon, text) with clipping and a built-in 8x8
  bitmap font. The hybrid palette keeps indices 0-14 exactly equal to the
  desktop palette (so the desktop behind the window is never recolored)
  and uses 15-255 as a UI ramp; the indexed buffer maps colours by nearest
  neighbour while the RGB buffer carries them exact. Index-owned pixels
  (canvas/preview mirrors in paint/file, `NK_COMMAND_IMAGE`) resolve
  through the exact 256-entry table (`nk_idx_to_rgb`), never a second
  nearest search. Old kernels leave the probe word zero, so the platform
  never touches the unmapped address and keeps the indexed path. Input
  comes from `SYS_MOUSE` (219, new: x, y, buttons, wheel, wheel consumed
  on read) and raw PS/2 scancodes translated to Nuklear keys and unicode.
  DOOM/Quake 2 stay indexed by nature (their assets are 256-color; the
  palette upload is already exact in true color), so the RGB path serves
  the Nuklear apps: node editor, vedit, file, paint, doomedit, piano.
- **Node editor (`node_editor.c`)**: a canvas with draggable nodes (Number,
  Add, Sub, Mul, Div, Neg, Print, Exit), pin wiring by drag, and Compile,
  which writes `cvm/nodes.cvm` to the ramdisk through the ordinary open/write
  syscalls. Running it (bare `nuklear`, or `nuklear.elf`) opens the GUI; the
  headless modes are the serial-observable surface:
  - `nuklear --selftest` renders one UI frame through the whole graphics
    pipeline and proves it end to end: it writes a marker pixel into the
    back-buffer (mirrored exact into the RGB twin when the kernel maps
    it, since the present routes there), calls the frame present, reads
    the desktop framebuffer at the reported window origin and requires
    the pixel to have landed there; on RGB kernels it additionally
    presents the unquantizable marker (123,45,67) and requires it
    byte-exact (`nuklear: rgb ok (123,45,67)`), which the 256-color path
    could never produce; it also checks that SYS_MOUSE accepts a user
    pointer and rejects a kernel pointer with `-EFAULT`. Only then does
    it print `nuklear: frame ok (800x360)` — so a mutant that drops the
    composite, the origin reporting or the mouse bounds check is killed.
  - `nuklear --demo <out.cvm>` compiles a fixed demo graph `(2+3)*4` and
    writes the module.
  - `nuklear --compile <graph.txt> <out.cvm>` parses a simple graph
    description (`num a 2`, `add b a a`, `print p b`) and compiles it.
  A compiled module is a self-contained cvm2 file the interpreter runs with
  `run cvm/demo.cvm` (prints `20`, exit 0). The compiler (`cvm_emit.c`)
  topologically sorts the graph, detects cycles and feed-an-output-node
  errors with diagnostics, computes every node value into a local slot,
  prints through the `printf` native and exits with `OP_HALT`; division by
  zero fails closed (`cvm: runtime error: division by zero`, exit 1).
  Commands: `nuklear` (GUI: drag nodes, wire pins, compile),
  `nuklear --selftest`, `nuklear --demo cvm/demo.cvm`,
  `nuklear --compile src/graph.txt cvm/out.cvm` and `run cvm/out.cvm`
  to run the compiled module.
- **Syscall surface**: the kernel adds 219 (`SYS_MOUSE`: read the desktop
  mouse state into a user int[4], resetting the wheel) and 220
  (`SYS_NK_FRAME`: composite the Nuklear back-buffer as a titled window,
  optionally returning the window content origin so the app can translate
  mouse coordinates). The `NK_W`/`NK_H`/`NK_BACKBUF_ADDR` constants live in
  `vga_fb.h`; the buffer sits at the middle of the user window, far from both
  the program heap (grows up from the load base) and its mmap zone (grows
  down from the stack base). The ld stub set grew `minios_mouse`/`nk_frame`
  beside the other MiniOS syscalls.
- **CVM host fix**: the JIT encodes runtime faults (division by zero, bad
  address) as a *negative* exit code because `cvm_jit_error` only stops the
  machine, so the interpreter's host must translate `cvm_exit_code < 0` back
  into `cvm: runtime error: <reason>` with exit 1 instead of leaking a
  negative status to the shell. This lives in `cvm_host.c` `cvm_main`.

## Quake 2 (quake2generic)

Quake 2 runs inside MiniOS exactly like DOOM: the upstream quake2generic
engine is cloned as a sibling checkout, built on the host with the ordinary
gcc toolchain against the static glibc, and the resulting `ET_EXEC` binary
ships on MiniFS, where it runs as a ring-3 process through the Linux syscall
ABI. The software renderer produces an 8-bit paletted framebuffer that
reuses the DOOM back-buffer infrastructure unchanged.

### Platform layer (`q2generic_minios.c`)

The platform layer lives at `progs/quake2generic/q2generic_minios.c` and
implements the quake2generic interface:

- **Video**: `SWimp_SetMode` sets `vid.buffer` to the DOOM back-buffer
  address (`DOOM_BACKBUF_ADDR`, 0x0B000000) and `vid.rowbytes` to 320.
  `SWimp_EndFrame` calls `SYS_DOOM_FRAME` (211) to composite the 320x200
  buffer onto the desktop as a titled window. The window title is set to
  "Quake 2" via `SYS_Q2G_SET_TITLE` (223) at startup.
- **Palette**: `SWimp_SetPalette` converts the engine's 256-entry RGBA
  quads (1024 bytes) to the 768-byte VGA DAC format and uploads via
  `SYS_PALETTE` (206) on the next frame.
- **Input**: PS/2 Set 1 scancodes are translated to Quake 2 keycodes
  (from `client/keys.h`) and queued through `Quake2_SendKey`. Mouse deltas
  come from `SYS_MOUSE` (219).
- **Timing**: `QG_Milliseconds` returns PIT-calibrated milliseconds via
  `SYS_TIME` (204).

### Audio

Sound reaches the kernel's low-latency pcm2 engine through the MiniOS DMA
backend `progs/quake2generic/snddma_minios.c` (replaces upstream
`snddma_null.c` in `Q2G_SOUND_SRCS`). The engine (`client/snd_mix.c`
`S_TransferPaintBuffer`) mixes every sfx into one mono ring,
`dma.buffer`, and `S_Update_`/`GetSoundtime` drive painting from
`SNDDMA_GetDMAPos`. The backend maps that ring straight onto pcm2 (syscalls
246/247/248, 8-bit mono 22050 Hz single-cycle DMA; see "Low-latency path
pcm2"): `SNDDMA_Submit` pushes at most one kernel ring ahead of the play
position (`Q2SND_AHEAD` 1024 B) with NONBLOCK writes that never stall the
frame loop, and anything further painted waits in `dma.buffer` for the next
Submit — pushing the whole painted lead would cost ~200 ms per frame (the
0.2 s `s_mixahead` at 22050 Hz) and drop the game to single-digit fps.
`SNDDMA_GetDMAPos` reports a play position from
elapsed guest time clamped to what was submitted. Geometry is dictated by
the engine and must not drift: `dma.samples` must be a power of two (the
mixer indexes with `paintedtime & (dma.samples - 1)`; the backend uses
8192), `dma.channels == 1`, and `dma.speed == 22050`
because `client/snd_mem.c` resamples every loaded sfx to `dma.speed`.
The mixer runs 16-bit mono (`dma.samplebits == 16`, downconverted to 8-bit
unsigned on the way to pcm2) because upstream `S_PaintChannelFrom8` is
broken (see the MiniOS-local patch below); 16-bit silence is `0`.
Fail-closed: no SB16 (pcm2 open refuses) leaves `dma.buffer` NULL and the
game runs silently through `S_ClearBuffer`, never a crash. The engine's
`S_Init` prints `sound sampling rate: 22050` only when `SNDDMA_Init`
succeeded, and `quake2generic.elf --pcm2-probe` is the headless hook that
proves the backend reaches pcm2; `minios_sndtest <wav>` plays a real pak
sfx in-game for headless verification. The BDD suite pins the probe, the
engine init (clean `exit code: 0`), the forced-sine non-silence
(`q2snd: audio present`) and a real sfx (`minios_sndtest`), and
`q2snd-init-false` / `q2snd-rate-wrong` / `q2snd-submit-nopush` mutants die
in `tools/mutate.sh`. Do NOT route this
through the legacy SB16 ring (221/222): it is the ~650 ms game-music path
and, more importantly, auto-init DMA is forbidden on this bus (see the SB16
HAZARD note).

- **MiniOS-local patch (`snd_mix.c`, build-time copy).** Upstream
  `S_PaintChannelFrom8` indexes the 32-row `snd_scaletable` with
  `leftvol >> 11`, which is 0 for every legal volume (the original id code
  uses `>> 3`), so every 8-bit sfx mixes as pure silence while the channel
  shows full volume — the exact "game runs, mixer runs, no sound" failure.
  The upstream checkout is git-ignored and must stay pristine, so the
  Makefile generates `build/snd_mix_fixed.c` from the upstream source with
  the one-line `>> 11` to `>> 3` fix applied via `sed`, and compiles that
  instead. If the fix ever regresses, real sfx go silent (the forced sine
  still sounds, because it bypasses channels) and the `plays a real sfx`
  BDD scenario fails.

### Memory constraints

Quake 2 needs ~16-24 MB at runtime (Zone + Hunk allocations for PAK files,
BSP, models). The user window provides 184 MB (`0x400000` to `0x0C000000`),
with ~17 MB available via `brk`/`mmap` after the ELF loads. The 320x200
back-buffer (64 KB) sits in the DOOM infrastructure at `0x0B000000`, below
the 1 MB stack at the top of the user window.

### Data files

The engine requires `baseq2/pak0.pak` (shareware: ~18 MB). MiniFS supports
subdirectories, so the PAK file is packed at `baseq2/pak0.pak` in the
filesystem image. The engine searches for `basedir/baseq2/pak0.pak`; with
`+set basedir .` at launch it finds the file at the MiniFS root.

### Build

```makefile
make progs/bin/quake2generic.elf
```

The binary ships on MiniFS (not the ramdisk, same as DOOM) via
`MINIFS_Q2G_FILES`. Run inside the OS:

```
miniOS> run bin/quake2generic.elf +set basedir .
```

### Syscall surface

The kernel adds 223 (`SYS_Q2G_SET_TITLE`: copy a user string into the
graphics window title buffer so the desktop compositing shows "Quake 2"
instead of "DOOM"). All other infrastructure is reused: `SYS_DOOM_FRAME`
(211), `SYS_PALETTE` (206), `SYS_KBD` (205), `SYS_KBD_RAW` (207),
`SYS_VGA_MODE` (208), `SYS_TIME` (204), `SYS_MOUSE` (219), and the pcm2
sound path (246/247/248, via `snddma_minios.c`).

### BDD

 Five scenarios pin Quake 2: `quake2generic binary exists on minifs`
 (the ELF ships on MiniFS), `quake2generic sound path opens and releases
 pcm2` (`--pcm2-probe` prints `q2snd: pcm2 ok` and the device is released),
 `quake2generic initializes sound and exits cleanly` (a short
 `minios_autoframes` run prints `sound sampling rate: 22050` and exits 0),
 `quake2generic pushes non-silent audio` (the same run with
 `+set s_testsound 1`, which forces the engine's fixed sine into the paint
 buffer, prints `q2snd: audio present`), and `quake2generic plays a real
 sfx` (`minios_sndtest weapons/blastf1a` plays a pak blaster in-game,
 prints `q2snd: audio present`). The sine-vs-real pair tells plumbing from
 mixer: if the sine sounds but the blaster does not, the 8-bit mixer fix
 regressed; if neither sounds, the device path is broken. Every pushed byte
 passes a loudness probe (anything clearly off the `0x80` line counts)
 reported at shutdown as `q2snd: pushed N bytes (M loud)`. For manual
 checks, `+set s_testsound 1` must be audible on the host; silence there is
 a host backend (mixer/mute) problem, because the guest demonstrably streams
 loud bytes to the SB16. A full gameplay test requires the PAK file and is
 not automated in the serial-console BDD suite (same as DOOM).

## Doom map editor (`doomedit`)

`bin/doomedit` is the in-OS Doom map authoring path: a ring-3 Nuklear app
built exactly like the node editor (host gcc `-static -no-pie`, MiniFS with
a bare-name alias, one file per contract at `progs/doomedit/doomedit.c`
with a centralized config). The author paints a tile grid up to 32x20 on a
canvas beside a side panel (slots, level picker, brush combobox, raycaster
preview, all visible without scrolling in the 800x360 window), choosing
from the full thing palette below, watches a live DDA raycaster preview
in the style of the sibling
`../raycastlib` checkout (CC0, cloned by hand, reference only, never
vendored), exports a multi-sector E1M1 PWAD snapshot to `/saves`, and
boots the shipped Doom on it with `-file` without ever writing to the
immutable IWAD. Commands: `doomedit` (GUI editor), `doomedit --demo
/saves/dmap0.wad`, `doomedit --preset 8 /saves/dmap1.wad` (the bundled
levels are 0-8), `doomedit --random [seed] /saves/dmap2.wad`,
`doomedit --check /saves/dmap0.wad` (validate a snapshot) and `run
doomgeneric.elf -file /saves/dmap0.wad mini_autoframes 30` to play a
snapshot headlessly.
Build: `make progs/bin/doomedit.elf` (or just `make` to rebuild
everything).

- **PWAD writer (`tools/doom_pwad.py`)**: a single-file host tool with the
  same algorithm as the C exporter (`build`/`check`/`info` verbs). Grid
  legend `#` wall, `.` floor, `P` player, `E` exit marker, `+` door cell,
  `,` dark floor, `~` nukage pit, plus thing stamps; the exit marker
  must sit next to a wall whose shared edge becomes the S1 exit-switch
  linedef (special 11). Output is multi-sector: every same-style floor
  region and every door block is its own sector (rooms differ in light,
  floor height and flats; doors are tagged sectors with D1 open-door
  lines on both faces), while segs mirror the linedefs under one
  subsector, one root node with both children leaf, one shared-list
  blockmap and a sized REJECT bit table. One subsector needs no
  ordering, so no BSP compiler is required; a partition-searching
  builder for large maps stays an explicit later phase. Fail closed on
  ragged grids, open perimeters, missing player or exit, unreachable
  tiles, oversized dimensions and every wild cross-lump reference
  (sized REJECT, paired sidedefs, tagged door lines, unique sector
  tags). All tunables live in `DoomPwadConfig`; textures, flats and
  thing ids are verified byte-present in the shareware `Doom1.wad`.
- **Shareware `-file` gate (`progs/doomgeneric/d_main.c`)**: the shipped
  IWAD is shareware, whose startup aborts any `-file` load. The
  MiniOS-local patch relaxes that one abort into a notice; the
  registered-version lump check stays intact and the IWAD file itself is
  never opened for writing.
- **Snapshots (`saves/`)**: custom maps live only under `saves/` on MiniFS,
  which the image rules already extract and repack across rebuilds, so a
  map survives `make os.img` and `make clean` through `saves-backup/`.
  Booting without `-file` always returns to the original game; replay via
  the editor Run action (button or Ctrl+R through the scancode hook) or
  `run doomgeneric.elf -file /saves/dmapN.wad` from the shell.
- **Bundled levels and procedural maps**: the level combo offers nine
  compiled-in levels in the same one-char-per-tile grid text the editor
  saves (`Hangar of Dawn`, `Imp Gallery`, `Demon Pit`, `Crossfire Chapel`,
  `Fortress of Lead`, `Sunken Halls`, `Baron's Court`, `Gatehouse`,
  `Nukage Mills`, a few hundred bytes each), and the Random button grows
  connected rooms joined by corridors, splits them with a door-pierced
  wall divider and stains dark patches plus one nukage pool, with the
  full thing palette (demon, shotgun guy, shotgun, medikit and shells
  guaranteed), retried until the validator accepts it. Painting any
  tile (or a line/rect drag) returns the level combo to `Custom`.
  Headless:
  `doomedit --preset N out.wad` and `doomedit --random [seed] out.wad`;
  the selftest builds every preset plus a fixed-seed random map and
  `make test-doomedit` runs all nine through the Python checker.
- **Thing palette**: enemies imp/demon/zombieman/shotgun guy/spectre/baron
  plus exploding barrels; weapons shotgun/chaingun/rocket launcher/chainsaw;
  ammo shells/clip/bullet box/rockets/rocket box/shell box; health
  stimpack/medikit/soulsphere/health bonus; armor bonus/green/blue; keys
  blue/red/yellow; powerups invisibility/radiation suit/computer map/light
  amp; backpack and a decorative pillar. Every id is the engine's own
  doomednum with its sprite verified present in the shareware `Doom1.wad`:
  cacodemon, lost soul, plasma rifle, BFG, berserk, invulnerability and the
  megasphere have no sprites there and would fault the renderer once
  visible, so they are excluded (Doom has no quad damage; invisibility is
  the closest surviving powerup).
- **Dock icon**: `DoomEdit|icons/doomedit.png|doomedit` in
  `progs/etc/shortcuts`, converted from `images/doomedit.png` by
  `tools/gen_desktop_pngs.py`.
- **Proof**: `make test-doomedit` (python vectors plus the C `--demo`
  output passing the python checker, so the two writers cannot drift);
  BDD `doomedit --selftest` (frame plus build), demo export plus check in
  `saves/`, preset export plus check, and Doom boot on the snapshot with
  `exit code: 0`, plus a multi-sector preset export plus check and a Doom
  boot on the door map with `exit code: 0` (see ADR-0022, ADR-0023).
