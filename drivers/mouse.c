/** Docstring: PS/2 mouse device driver (drivers/mouse.c).
 *
 * Owns the controller handshake, the Intellimouse detect knock and the
 * enable/disable verbs. The IRQ12 packet phase machine stays in the
 * scheduler ISR dispatch beside the tick that consumes it; this unit only
 * talks to the controller through arch/x86/hal_io.h. */
#include "kernel.h"
#include "arch/x86/hal_io.h"
#include "drivers/mouse.h"

/* ---- PS/2 mouse hardware init ---- */
/* Every wait is deadline-bounded through port_wait_mask (see kernel.h):
 * the old bare 100k-spin polls burned ~200 ms of KVM VM-exits per wait
 * and mouse_hw_init issues dozens of them (measured 5 s of boot).
 * 100 ms is generous: a real controller answers in microseconds. */
static void mouse_wait_cmd(void) {
    port_wait_mask(HAL_PS2_STATUS, HAL_PS2_IBF_EMPTY, 0, 100);
}

static void mouse_wait_data(void) {
    port_wait_mask(HAL_PS2_STATUS, HAL_PS2_OBF_FULL, 1, 100);
}

static void mouse_write(unsigned char data) {
    mouse_wait_cmd();
    hal_outb(HAL_PS2_STATUS, HAL_PS2_CMD_WRITE_MOUSE);
    mouse_wait_cmd();
    hal_outb(HAL_PS2_DATA, data);
}

static unsigned char mouse_read(void) {
    mouse_wait_data();
    return hal_inb(HAL_PS2_DATA);
}

void mouse_hw_init(void) {
    /* Drain any stale bytes in the output buffer */
    while (hal_inb(HAL_PS2_STATUS) & HAL_PS2_OBF_FULL) hal_inb(HAL_PS2_DATA);

    /* Enable auxiliary device (mouse) */
    mouse_wait_cmd();
    hal_outb(HAL_PS2_STATUS, HAL_PS2_CMD_ENABLE_AUX);

    /* Enable IRQ12 by setting bit 1 of the PS/2 controller config byte */
    mouse_wait_cmd();
    hal_outb(HAL_PS2_STATUS, HAL_PS2_CMD_READ_CONFIG);
    mouse_wait_data();
    unsigned char config = hal_inb(HAL_PS2_DATA);
    mouse_wait_cmd();
    hal_outb(HAL_PS2_STATUS, HAL_PS2_CMD_WRITE_CONFIG);
    mouse_wait_cmd();
    hal_outb(HAL_PS2_DATA, config | HAL_PS2_CONFIG_IRQ12);

    /* Reset mouse.  A reset yields THREE reply bytes (0xFA ack, 0xAA
     * self-test, device ID); reading fewer leaves the rest pending, and
     * each stray enters the IRQ12 phase machine below: 0xAA has bit 3
     * set, so the phase-0 guard accepts it as a packet start and every
     * later packet is framed wrong (a left press reads back as bit 1,
     * motion warps), permanently. */
    mouse_write(HAL_MOUSE_CMD_RESET);
    mouse_read();
    mouse_read();
    mouse_read();

    /* Enable Intellimouse extension for scroll wheel:
     * Set sample rate to 200, 100, 80 in sequence */
    mouse_write(HAL_MOUSE_CMD_SET_RATE); mouse_read();  /* set sample rate */
    mouse_write(HAL_MOUSE_RATE_KNOCK_200); mouse_read();  /* 200 */
    mouse_write(HAL_MOUSE_CMD_SET_RATE); mouse_read();  /* set sample rate */
    mouse_write(HAL_MOUSE_RATE_KNOCK_100); mouse_read();  /* 100 */
    mouse_write(HAL_MOUSE_CMD_SET_RATE); mouse_read();  /* set sample rate */
    mouse_write(HAL_MOUSE_RATE_KNOCK_80); mouse_read();  /* 80 */
    /* Read device ID: 0x03 = Intellimouse (wheel) */
    mouse_write(HAL_MOUSE_CMD_GET_ID); mouse_read();
    unsigned char id = mouse_read();
    (void)id;

    /* Set defaults */
    mouse_write(HAL_MOUSE_CMD_DEFAULTS);
    mouse_read();

    /* Enable data reporting */
    mouse_write(HAL_MOUSE_CMD_ENABLE);
    mouse_read();
}

void mouse_disable(void) { mouse_write(HAL_MOUSE_CMD_DISABLE); mouse_read(); }
void mouse_enable(void)  { mouse_write(HAL_MOUSE_CMD_ENABLE); mouse_read(); }
