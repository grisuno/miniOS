/* pip -- launcher for `python3 -m pip`, and pip3 as a copy of this image.
 *
 * The shell has no argument expansion, so a shell script cannot forward
 * `pip install x` to the interpreter. This launcher carries the MiniOS
 * process note (the shell's pid-0 exec frame cannot execve), rebuilds
 * argv as python3 -m pip <user args>, and replaces itself with the
 * static interpreter at /python3 (a MiniFS root entry, so the caller's
 * cwd does not matter). Exit 127 when execve fails, like a shell. */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "minios_abi.h"

/** Interpreter path inside the guest; cwd independent. */
#define PIP_PYTHON_PATH "/python3"
/** Python arguments that select the pip module. */
#define PIP_MODULE_FLAG "-m"
#define PIP_MODULE_NAME "pip"
/** Prefix words added in front of the caller's arguments. */
#define PIP_PREFIX_WORDS 3
/** Exit status for a failed execve. */
#define PIP_EXEC_FAILED 127

#ifdef PIP_PROCESS_NOTE
/** MiniOS process note: name, 4-byte descriptor, both 4-byte padded. */
struct pip_note {
    uint32_t namesz;
    uint32_t descsz;
    uint32_t type;
    char     name[sizeof MINIOS_NOTE_NAME];
    uint32_t desc;
};

__attribute__((section(".note.minios.process"), used, aligned(4)))
static const struct pip_note pip_process_note = {
    sizeof MINIOS_NOTE_NAME, sizeof(uint32_t), MINIOS_NOTE_PROCESS, MINIOS_NOTE_NAME, 1u
};
#endif

/** Build argv and exec the interpreter; returns only on failure. */
int main(int argc, char **argv) {
    char **args;
    int i;
    if (argc < 1) argc = 1;
    args = malloc(sizeof(char *) * (size_t)(argc + PIP_PREFIX_WORDS + 1));
    if (!args) {
        fprintf(stderr, "pip: out of memory\n");
        return PIP_EXEC_FAILED;
    }
    args[0] = (char *)PIP_PYTHON_PATH;
    args[1] = (char *)PIP_MODULE_FLAG;
    args[2] = (char *)PIP_MODULE_NAME;
    for (i = 1; i < argc; i++) args[PIP_PREFIX_WORDS + i - 1] = argv[i];
    args[PIP_PREFIX_WORDS + argc - 1] = 0;
    execv(PIP_PYTHON_PATH, args);
    fprintf(stderr, "pip: exec %s failed: %d\n", PIP_PYTHON_PATH, errno);
    free(args);
    return PIP_EXEC_FAILED;
}
