/** Docstring: Host test for arch/x86/hal_io.h (make test-hal).
 *
 * Verifies the centralized port and device constants match the Intel
 * and APIC values the ISR path relied on, and that the host stub
 * accessors route writes and EOIs to the observable stub counters
 * without executing privileged instructions.
 */

#include <stdio.h>

#define HAL_IO_HOST_TEST 1

unsigned hal_io_stub_writes;
unsigned hal_io_stub_last_port;
unsigned hal_io_stub_last_val;
unsigned hal_io_stub_lapic_eois;
unsigned char hal_io_stub_read_val;

#include "arch/x86/hal_io.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    CHECK(HAL_PIC1_CMD == 0x20, "master pic command port");
    CHECK(HAL_PIC1_DATA == 0x21, "master pic data port");
    CHECK(HAL_PIC2_CMD == 0xA0, "slave pic command port");
    CHECK(HAL_PIC2_DATA == 0xA1, "slave pic data port");
    CHECK(HAL_PIC_EOI == 0x20, "pic eoi byte");
    CHECK(HAL_PIT_CMD == 0x43, "pit command port");
    CHECK(HAL_PIT_CH0 == 0x40, "pit channel zero port");
    CHECK(HAL_PS2_STATUS == 0x64, "ps2 status port");
    CHECK(HAL_PS2_DATA == 0x60, "ps2 data port");
    CHECK(HAL_PS2_MOUSE_OBF == 0x20, "ps2 mouse obf bit");
    CHECK(HAL_MOUSE_SYNC_BIT == 0x08, "mouse sync bit");
    CHECK(HAL_MOUSE_OVF_BITS == 0xC0, "mouse overflow bits");
    CHECK(HAL_MOUSE_BUTTON_MASK == 0x07, "mouse button mask");
    CHECK(HAL_MOUSE_SCALE == 2, "mouse scale factor");
    CHECK(HAL_MOUSE_PACKET_LEN == 4, "mouse packet length");
    CHECK(HAL_PS2_CMD_WRITE_MOUSE == 0xD4, "ps2 forward-to-mouse command");
    CHECK(HAL_PS2_CMD_ENABLE_AUX == 0xA8, "ps2 enable aux command");
    CHECK(HAL_PS2_CMD_READ_CONFIG == 0x20, "ps2 read config command");
    CHECK(HAL_PS2_CMD_WRITE_CONFIG == 0x60, "ps2 write config command");
    CHECK(HAL_PS2_CONFIG_IRQ12 == 0x02, "ps2 irq12 config bit");
    CHECK(HAL_MOUSE_CMD_RESET == 0xFF, "mouse reset command");
    CHECK(HAL_MOUSE_CMD_SET_RATE == 0xF3, "mouse set rate command");
    CHECK(HAL_MOUSE_CMD_GET_ID == 0xF2, "mouse get id command");
    CHECK(HAL_MOUSE_CMD_DEFAULTS == 0xF6, "mouse defaults command");
    CHECK(HAL_MOUSE_CMD_ENABLE == 0xF4, "mouse enable command");
    CHECK(HAL_MOUSE_CMD_DISABLE == 0xF5, "mouse disable command");
    CHECK(HAL_MOUSE_RATE_KNOCK_200 == 200, "intellimouse knock first rate");
    CHECK(HAL_MOUSE_RATE_KNOCK_100 == 100, "intellimouse knock second rate");
    CHECK(HAL_MOUSE_RATE_KNOCK_80 == 80, "intellimouse knock third rate");
    CHECK(HAL_MOUSE_ID_INTELLI == 0x03, "intellimouse device id");
    CHECK(HAL_MOUSE_HW_TIMEOUT == 100000, "mouse controller wait bound");
    CHECK(HAL_LAPIC_EOI_ADDR == 0xFEE000B0UL, "lapic eoi address");
    hal_io_stub_writes = 0;
    hal_io_stub_lapic_eois = 0;
    hal_io_stub_read_val = 0xAB;
    hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI);
    CHECK(hal_io_stub_writes == 1, "stub counts port writes");
    CHECK(hal_io_stub_last_port == 0x20, "stub records port");
    CHECK(hal_io_stub_last_val == 0x20, "stub records value");
    CHECK(hal_inb(HAL_PS2_STATUS) == 0xAB, "stub read returns canned byte");
    hal_lapic_eoi();
    CHECK(hal_io_stub_lapic_eois == 1, "stub counts lapic eoi");
    hal_io_stub_writes = 0;
    hal_pic_eoi(12);
    CHECK(hal_io_stub_writes == 2, "slave irq eoies both pics");
    hal_io_stub_writes = 0;
    hal_pic_eoi(0);
    CHECK(hal_io_stub_writes == 1, "master irq eoies master only");
    if (failures == 0) {
        printf("hal_io: ok\n");
    }
    return failures != 0;
}
