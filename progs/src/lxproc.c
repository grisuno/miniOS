/** lxproc.c - foreground process-note probe (docs/spec/shell-fs.md, "Process
 * note", and progs/minios_abi.h).
 *
 * Built twice from this one file: bin/lxproc carries the MiniOS process note
 * (LXPROC_PROCESS_NOTE defined), bin/lxframe does not. Run bare in the
 * foreground, the shell executes lxframe in its pid-0 exec frame and lxproc
 * as an isolated process, and the probe reports what that gives it:
 *
 *   lxproc: exe /<path>         what readlink("/proc/self/exe") answers
 *   lxproc: fork ok             a forked child ran and was reaped (process)
 *   lxproc: fork unavailable    fork answered ENOSYS (exec frame)
 *   lxproc: fork FAIL <errno>   any other outcome
 *
 * Exit code: 0 when every line is one of the expected outcomes, 1 otherwise.
 * The BDD scenario pins which fork line each variant prints.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minios_abi.h"

/** Bytes kept from the /proc/self/exe answer. */
#define LXPROC_EXE_MAX 128
/** Exit status the forked child reports, so the reap proves it ran. */
#define LXPROC_CHILD_CODE 7
#define LXPROC_OK 0
#define LXPROC_BAD 1

#ifdef LXPROC_PROCESS_NOTE
/** MiniOS process note: name, 4-byte descriptor, both 4-byte padded. */
struct lxproc_note {
    uint32_t namesz;
    uint32_t descsz;
    uint32_t type;
    char     name[sizeof MINIOS_NOTE_NAME];
    uint32_t desc;
};

__attribute__((section(".note.minios.process"), used, aligned(4)))
static const struct lxproc_note lxproc_process_note = {
    sizeof MINIOS_NOTE_NAME, sizeof(uint32_t), MINIOS_NOTE_PROCESS, MINIOS_NOTE_NAME, 1u
};
#endif

/** Print the image path the kernel reports; 0 on success. */
static int report_exe(void) {
    char exe[LXPROC_EXE_MAX];
    ssize_t n = readlink("/proc/self/exe", exe, sizeof exe - 1);
    if (n <= 0) {
        printf("lxproc: exe FAIL %d\n", errno);
        return LXPROC_BAD;
    }
    exe[n] = '\0';
    printf("lxproc: exe %s\n", exe);
    return LXPROC_OK;
}

/** Fork a child that exits with LXPROC_CHILD_CODE and reap it; 0 when the
 * outcome is one of the two the contract allows. */
static int report_fork(void) {
    int status = 0;
    fflush(stdout);
    pid_t pid = fork();
    if (pid == 0) _exit(LXPROC_CHILD_CODE);
    if (pid < 0) {
        if (errno == ENOSYS) {
            printf("lxproc: fork unavailable\n");
            return LXPROC_OK;
        }
        printf("lxproc: fork FAIL %d\n", errno);
        return LXPROC_BAD;
    }
    while (waitpid(pid, &status, 0) < 0) {
        if (errno != EINTR) {
            printf("lxproc: fork FAIL wait %d\n", errno);
            return LXPROC_BAD;
        }
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != LXPROC_CHILD_CODE) {
        printf("lxproc: fork FAIL status %d\n", status);
        return LXPROC_BAD;
    }
    printf("lxproc: fork ok\n");
    return LXPROC_OK;
}

int main(void) {
    int bad = report_exe();
    bad |= report_fork();
    fflush(stdout);
    return bad ? LXPROC_BAD : LXPROC_OK;
}
