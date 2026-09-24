# Subsystem: kernel

## headers/kernel/console_in.h
- Layer: utility
- Doc: Docstring: console_in.h -- boundary of the console input device
- Language: h
- Symbols:
  - `Consumers` (function, line 7) `* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into kernel/shell.c. */ #include "kernel.h" /** Docstring: Blocking read from PS/2 or COM1 w`
  - `console_peek` (function, line 17) `int console_peek(void);`
  - `console_raw_try` (function, line 21) `int console_raw_try(void);`
  - `console_raw_get` (function, line 22) `int console_raw_get(void);`
  - `console_job_try` (function, line 25) `int console_job_try(void);`
  - `console_job_get` (function, line 26) `int console_job_get(void);`
  - `console_ungetc` (function, line 30) `void console_ungetc(unsigned char c);`
  - `console_stdin_push` (function, line 37) `int console_stdin_push(const char *data, unsigned long len);`
  - `console_stdin_clear` (function, line 38) `void console_stdin_clear(void);`
  - `console_stdin_active` (function, line 39) `int console_stdin_active(void);`
  - `CONSOLE_IN_H` (macro, line 2) `#define CONSOLE_IN_H`
- Depends on: `headers/kernel.h`
- Imported by: `headers/shell.h`, `kernel/console_in.c`, `kernel/shell.c`

## headers/kernel/vga_cursor.h
- Layer: utility
- Doc: Docstring: vga_cursor.h -- boundary of the pointer sprite layer
- Language: h
- Symbols:
  - `cursor_over` (function, line 16) `int cursor_over(int x0, int y0, int w, int h);`
  - `cursor_place` (function, line 19) `void cursor_place(int mx, int my);`
  - `cursor_move` (function, line 22) `void cursor_move(int mx, int my);`
  - `cursor_erase` (function, line 25) `void cursor_erase(void);`
  - `cursor_invalidate` (function, line 28) `void cursor_invalidate(void);`
  - `cursor_note_repaint` (function, line 31) `void cursor_note_repaint(int x0, int y0, int w, int h);`
  - `VGA_CURSOR_H` (macro, line 2) `#define VGA_CURSOR_H`
  - `CURSOR_W` (macro, line 12) `#define CURSOR_W`
  - `CURSOR_H` (macro, line 13) `#define CURSOR_H`
- Depends on: `headers/kernel.h`
- Imported by: `kernel/vga_cursor.c`, `kernel/vga_fb.c`
