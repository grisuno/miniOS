# vedit — MiniOS visual IDE

`bin/vedit` is the fullscreen visual editor and mini-IDE. It runs at
ring 3 as a static ELF (MiniFS, with the bare-name alias), renders
through the shared Nuklear platform layer, and builds/runs programs
without leaving the machine. One file implements it all:
`progs/vedit/vedit.c` (every bound lives in a `VEDIT_*` define).

Start it with `vedit [file]`.

## How to press the keys (read this first)

- `^A` means **Control+A**: hold Control, tap A, release. Same for
  `^E ^K ^Y ^T ^U ^W ^R ^O ^S ^N ^G ^L ^D ^X` and `^]` (Control plus
  the `]` key).
- `M-w` means **ESC followed by the key**: tap ESC, release, then tap
  `w` within one second. The status row shows `META` while the prefix
  is armed — if you see it, vedit is waiting for your second key, not
  ignoring you. Do NOT hold Alt — Alt+letter just types the letter. Same for `M-f M-b M-c M-l M-u M-s M-r M-n M-q M-x M-v M-W
  M-k M-o M-1 M-2 M-! M-# M-( M-) M-e` and `M-%` (ESC, then Shift+5).
- `^@` (set mark) has a friendlier alias: `M-SP`, i.e. ESC followed
  by Space. (Physical Ctrl+Space arrives as a plain space on PS/2, so
  the alias is the reliable way.)
- A lone ESC quits without saving, but only after a 1-second pause
  with no following key — that pause is your Meta window. If you tap
  ESC and hesitate too long, you land back in the shell: just reopen.
- If NO key seems to do anything (not even typing), the terminal owns
  the keyboard instead of vedit: focus the graphics window
  (`Alt-Tab`, or click its taskbar button) and try again.
- `^A` at column 1 and `^E` at end of line are silent no-ops by
  design — the cursor is already there. Test them mid-line and watch
  the `Col` field in the status row.
- `M-x help` prints the whole key list on the console at any time.

## Everyday keys

| Key | Action |
|-----|--------|
| arrows, Home/End, PgUp/PgDn | move |
| type, Enter, Tab, Backspace/Delete | edit (Enter splits with auto-indent) |
| `^O` / `^S` | save (`~` backup kept, see below) |
| `^N` | save-as (rename + save) |
| `^W` | find (wraps once) |
| `^G` | go to line |
| `^R` | save, then build/run by extension |
| `^L` | save, link `asm/<base>.s`, run the artifact |
| `^D` | dump buffer to the console with highlight |
| `^X` | save and quit |
| Esc | quit without saving |

Buttons on the top bar do the same: Save, Find, Name, Run, Link,
Buf (next buffer), M-x (command prompt), Done.

`^R` routes by extension: `.c`/`.h` compile with
`objects/minigcc.o` into `asm/<base>.s`; `.s` links with
`objects/ld.o -f elf` into `bin/<base>.elf` and runs it; `.lua`,
`.py`, `.lisp` run with their interpreters. `^L` answers `elf` or
`cvm` at the `link elf/cvm:` prompt, links, then runs the result.
Every build drops the display first so the toolchain log lands on
the console, then the IDE resumes and reports the exit code.

## Buffers (up to 8)

`M-x find-file` opens a file in a new buffer, `M-x view-file` opens
read-only, `M-x insert-file` inserts a file at dot,
`M-x select-buffer` jumps by name, `M-x next-buffer` (Buf button)
cycles, `M-x kill-buffer` closes (refuses unsaved work),
`M-x list-buffers` prints them on the console. File prompts show
the recent-file history first. Saving writes a `~` backup of the
previous on-disk version; if the file changed on disk since it was
loaded, the first save warns and the second save forces.

The status row reads
`name [Lang] B1/8 Ln 12/300(4%) Col 5 RO OVR REC MRK ARG SEL msg`:
buffer index/open count, line/total (percent), column, and flags
for read-only, overwrite, macro recording, mark, universal arg and
mouse selection.

## uemacs editing keys

| Key | Action |
|-----|--------|
| `^A` / `^E` | beginning / end of line |
| `^@` (Ctrl+Space) or `M-SP` (ESC, Space) | set mark (M-SP is the reliable one) |
| `M-w` | copy region to the kill ring |
| `M-k` | kill region |
| `^K` | kill to end of line (or the newline) |
| `^Y` | yank the kill ring head |
| `M-f` / `M-b` | word forward / back |
| `M-c` / `M-l` / `M-u` | capitalize / lower / upper word |
| `^T` | transpose characters |
| `^]` | jump to the matching fence `()[]{}` |
| `^U` (then digits) | universal argument: repeats motions, kills, inserts |
| `M-q` | refill paragraph to 72 columns |

## Search and replace

| Key | Action |
|-----|--------|
| `M-s` / `M-r` | incremental search forward / reverse (type to narrow, Backspace to widen, Enter to keep, ESC to restore) |
| `M-n` | hunt: repeat the last search |
| `M-%` | query replace (`y`/space yes, `n` skip, `!` rest, `q` quit) |
| `M-x replace-string` | replace all |
| `M-x search-forward-magic` | search with `.` any, `*` repeat, `^`/`$` anchors, `[0-9]`/`[^...]` classes, `\x` literal |

## Windows, macros, commands

- `M-2` splits into two stacked panes (each with its own buffer and
  cursor), `M-o` switches pane, `M-1` back to single.
- `M-(` starts recording a keyboard macro, `M-)` stops, `M-e`
  plays it (depth-guarded, so a macro cannot recurse forever).
- `M-x` runs any of 46 named commands: `save-file`, `find-file`,
  `insert-file`, `view-file`, `list-buffers`, `select-buffer`,
  `next-buffer`, `kill-buffer`, `copy-region`, `kill-region`,
  `yank`, `kill-line`, `transpose-chars`, `goto-matching-fence`,
  `count-words`, `fill-paragraph`, `overwrite-mode`, `read-only`,
  `goto-line`, `search-forward`, `search-reverse`,
  `search-forward-magic`, `hunt-forward`, `hunt-backward`,
  `replace-string`, `query-replace`, `set-mark`,
  `exchange-point-and-mark`, `split-window`, `single-window`,
  `next-window`, `begin-macro`, `end-macro`, `execute-macro`,
  `shell-command`, `filter-buffer`, `grep`, `next-error`,
  `compile`, `link`, `help`, `describe-bindings`, `save-and-quit`,
  `quit`, `paste`, `copy-to-clipboard`. `M-x help` prints the key
  list on the console.
- `M-x bind-to-key` rebinds a key for the session: first the key
  (`^K`, `M-f`, `Up`, `PgDn`...), then the command.

## Region in 4 steps (copy / kill)

1. Move to one end of the text.
2. `M-SP` (ESC, Space) — status shows `MRK`.
3. Move to the other end (arrows, `M-f`, search — everything works).
4. `M-w` copies to the kill ring, `M-k` cuts, `M-W` copies to the
   clipboard. `^Y` pastes the kill ring back at the cursor.

Try it: type `hello world`, `^A`, `M-SP`, `M-f`, `M-f`, `M-k` —
both words vanish; `^Y` brings them back.

## Shell in 3 steps (`M-!`)

1. `M-!` — the status row asks `!: `.
2. Type a program and arguments, e.g. `/bin/cp src/a.c /tmp/b.c`,
   Enter. The display drops while it runs and the log prints on the
   console.
3. Its stdout is waiting in the `*shell*` buffer: `M-x select-buffer`,
   type `*shell*`, Enter.

Word and case keys work the same everywhere: `M-f` jumps one word
forward, `M-b` back; with the cursor inside `hello`, `M-u` makes
`HELLO`, `M-l` makes `hello`, `M-c` makes `Hello`.

## Shell, filter, grep (reference)

- `M-! program args` runs a program and loads its stdout into the
  `*shell*` buffer (e.g. `M-! /bin/cp src/a.c /tmp/b.c`).
- `M-# program` pipes the region (or the whole buffer when no mark)
  through a program that takes a file argument and replaces it with
  the output; a failing filter keeps the original.
- `M-x grep <magic-pattern>` collects matches into `*grep*` as
  `line: text`; `M-x next-error` jumps to the match under dot
  (move down and repeat to walk them).

## Clipboard (kernel syscalls 249/250, 4 KB)

Drag with the mouse in the code area: the selection highlights
inverted (`SEL` in the status row) and lands in the kernel
clipboard on release. `M-v` (or `M-x paste`) pastes it at dot;
`M-W` (or `M-x copy-to-clipboard`) copies the emacs region instead.
Oversize content is refused with a diagnostic, never truncated, and
paste into a read-only buffer is refused too. The shell `clip`
builtin shares the same slot, so both directions interoperate.

## Startup file

At startup vedit runs `/etc/vedit.rc`, then `./vedit.rc`. Lines are
`bind <key> <command>` or a bare command with an optional argument;
`#` comments and unknown lines are skipped with a console note.

```text
# open the project, use ^K for grep-style flow
bind ^G goto-line
find-file /src/main.c
```

## Worked example: fix every TODO

1. `M-x grep TODO` — matches land in `*grep*`.
2. `M-x next-error` — jump to the first hit; edit it.
3. Down arrow, `M-x next-error` again — walk the rest.
4. `^R` — build and run without leaving the IDE.
5. `M-(`, do the edit once, `M-)` — `M-e` replays it per site.

## Limits, honestly

Line length 255, 4096 lines and 1 MB per buffer (fail closed, never
truncated); 8 buffers; kill ring 8 deep; clipboard 4 KB; macros
1024 keys; no undo (uemacs never had it either). A truncated load
refuses to save and to build.
