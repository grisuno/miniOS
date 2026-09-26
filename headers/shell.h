#ifndef SHELL_H
#define SHELL_H

/* shell.h -- shared shell constants and the line reader/parser reused by
 * the built-in editor (kernel/editor.c).  The shell's public entry points
 * (shell_init, shell_run, shell_exec_builtin, shell_run_any,
 * shell_queue_launch, shell_take_redirect) are declared in kernel.h, the
 * single source of the shell API. */

#include "kernel.h"
#include "kernel/console_in.h"

#define CMD_BUF_SZ 256
#define MAX_ARGS   16

/* Read one line into buf with arrow-key editing; used by the built-in
 * editor to edit file text. */
void shell_readline_buf(char *buf, int size);

/* Tokenize `line` into up to `max_args` argv entries; returns argc. */
int shell_parse(char *line, char **argv, int max_args);

/* Strict signed decimal parse for numeric shell/editor operands: an
 * optional sign followed by at least one digit, whole string consumed,
 * fail-closed on empty input, trailing garbage or overflow. Returns 1
 * and sets *out on success, 0 otherwise. Replaces katol (which stops
 * at the first non-digit and wraps on overflow) at every builtin call
 * site, so `kill 12abc` is a diagnostic instead of pid 12. */
int shell_parse_long(const char *s, long *out);

/* Bounded pid parse: strict shell_parse_long plus min_pid <= pid < MAX_PROCS.
 * Unifies the wait/kill/vmmap range checks so the bound cannot drift per
 * call site. Returns 1 and sets *out on success, 0 otherwise. */
int shell_parse_pid(const char *s, int min_pid, int *out);

/* Execute a shell script: read `path` line by line, skip blanks and `#`
 * comments, parse each line and dispatch it through the normal builtin/
 * program path.  Returns 0 on success, 1 on file error. */
int shell_cmd_sh(int argc, char **argv);

#endif