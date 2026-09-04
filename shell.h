#ifndef SHELL_H
#define SHELL_H

/* shell.h -- shared shell constants and the line reader/parser reused by
 * the built-in editor (kernel/editor.c).  The shell's public entry points
 * (shell_init, shell_run, shell_exec_builtin, shell_run_any,
 * shell_queue_launch, shell_take_redirect) are declared in kernel.h, the
 * single source of the shell API. */

#include "kernel.h"

#define CMD_BUF_SZ 256
#define MAX_ARGS   16

/* Read one line into buf with arrow-key editing; used by the built-in
 * editor to edit file text. */
void shell_readline_buf(char *buf, int size);

/* Tokenize `line` into up to `max_args` argv entries; returns argc. */
int shell_parse(char *line, char **argv, int max_args);

/* Execute a shell script: read `path` line by line, skip blanks and `#`
 * comments, parse each line and dispatch it through the normal builtin/
 * program path.  Returns 0 on success, 1 on file error. */
int shell_cmd_sh(int argc, char **argv);

#endif