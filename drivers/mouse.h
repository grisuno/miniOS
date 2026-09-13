#ifndef MOUSE_H
#define MOUSE_H

/** Docstring: mouse.h -- boundary of the PS/2 mouse device driver
 * (drivers/mouse.c). Owns the controller handshake, the Intellimouse
 * detect knock and the enable/disable verbs. */

#include "kernel.h"

/** Docstring: Detect the wheel mouse and enable data reporting. */
void mouse_hw_init(void);

/** Docstring: Disable mouse data reporting. */
void mouse_disable(void);

/** Docstring: Enable mouse data reporting. */
void mouse_enable(void);

#endif
