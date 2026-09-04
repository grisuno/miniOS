#ifndef EDITOR_H
#define EDITOR_H

/* editor.h -- the built-in line editor contract.
 *
 * The editor owns its buffer (EditBuf) and the whole edit session; the
 * shell only dispatches the `edit` builtin to shell_cmd_edit.  Two
 * invariants are enforced here and covered by the mutation suite:
 *   1. a buffer that did not hold the whole file refuses to save;
 *   2. `q` refuses to discard unsaved changes, `q!` discards explicitly.
 */

#include "kernel.h"

void shell_cmd_edit(int argc, char **argv);

#endif