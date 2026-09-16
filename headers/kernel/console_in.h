#ifndef CONSOLE_IN_H
#define CONSOLE_IN_H

/** Docstring: console_in.h -- boundary of the console input device
 * (kernel/console_in.c). Owns the pushback FIFO, the serial + PS/2 raw
 * multiplexer, the blocking/peek/raw/job readers and the scrollback view.
 * Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include
 * this header instead of reaching into kernel/shell.c. */

#include "kernel.h"

/** Docstring: Blocking read from PS/2 or COM1 with PageUp/PageDown
 * scrollback detour. */
int console_getc(void);

/** Docstring: Next buffered byte without consuming it, or -1. */
int console_peek(void);

/** Docstring: Raw console multiplexer backing GETC_RAW: same sources,
 * no line buffering, echo or scrollback. try returns -1 when idle. */
int console_raw_try(void);
int console_raw_get(void);

/** Docstring: PS/2-only GETC_RAW source for background jobs. */
int console_job_try(void);
int console_job_get(void);

/** Docstring: Push one byte back into the console FIFO; the next
 * console_getc/console_peek serves it first. Drops the byte when full. */
void console_ungetc(unsigned char c);

#endif
