#include "kernel.h"

/* ================================================================
 *  Console output capture for shell redirection
 *
 *  The hot-path redirect_putc() lives in kernel.c (inlined into vga_putc)
 *  and accesses the state directly.  This file owns the lifecycle
 *  functions: begin, commit, suspend, resume, report.
 * ================================================================ */

void shell_report_exit(int code) {
    int was = redirect_suspend();
    kprintf("exit code: %d\n", code);
    redirect_resume(was);
}

void shell_report(const char *what, const char *detail) {
    int was = redirect_suspend();
    vga_puts(what);
    if (detail) vga_puts(detail);
    vga_putc('\n');
    redirect_resume(was);
}

int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode) {
    int i;
    *path = 0;
    *append_mode = 0;
    for (i = 0; i < *argc; i++) {
        if (argv[i][0] != '>') continue;
        if (argv[i][1] == '>') {
            *append_mode = 1;
            if (argv[i][2]) *path = argv[i] + 2;
        } else if (argv[i][1]) {
            *path = argv[i] + 1;
        }
        if (!*path) {
            if (i + 1 >= *argc) return -1;
            *path = argv[i + 1];
        }
        *argc  = i;
        argv[i] = 0;
        return 1;
    }
    return 0;
}
