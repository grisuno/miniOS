#ifndef SHELL_H
#define SHELL_H

/* shell.h -- Shell API extracted from kernel.c (Phase 6.1).
 *
 * This header defines the public interface for the MiniOS shell.
 * The implementation lives in shell.c and links against the kernel
 * API defined in kernel.h.
 *
 * Contract:
 *   shell_init() must be called once before shell_run().
 *   shell_run() is the main loop and does not return.
 *   shell_exec_builtin() dispatches built-in commands.
 *   shell_run_any() resolves and runs a command by name.
 *   shell_queue_launch() queues a command for deferred execution.
 */

#include "kernel.h"

/* ---- Shell run directories (suffix-based command resolution) ---- */
typedef struct {
    const char *suffix;
    const char *dir;
} ShellRunDir;

/* ---- Shell initialization and main loop ---- */
void shell_init(void);
void shell_run(void);

/* ---- Command execution ---- */
void shell_exec_builtin(int argc, char **argv);
int  shell_run_any(const char *name, int argc, char **argv);

/* ---- Deferred launch (for desktop shortcuts) ---- */
void shell_queue_launch(const char *cmd);

/* ---- Completion ---- */
void shell_complete_replace(char *buf, int size, int *pos, const char *text);

/* ---- Redirect handling ---- */
int  shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);

/* ---- Command parsing ---- */
int  shell_parse(char *line, char **argv, int max_args);

#endif
