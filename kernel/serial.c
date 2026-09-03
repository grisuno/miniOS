#include "kernel.h"

/* serial.c -- COM1 16550 UART driver.
 *
 * Provides blocking serial I/O for the kernel console.  The serial port
 * mirrors all VGA output and drives the pty serial console used by the
 * MCP bridge and the BDD suite.
 *
 * Contract:
 *   serial_init must be called once before any other serial function.
 *   serial_putc blocks until the transmit buffer is empty, then sends one byte.
 *   serial_getc returns the next byte from the receive buffer, or -1 if empty.
 *   serial_available returns nonzero when at least one byte is ready.
 *   serial_puts is a convenience wrapper that sends a NUL-terminated string.
 */

#define COM1 0x3F8

void serial_init(void) {
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x01);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

static int serial_tx_ready(void) { return inb(COM1 + 5) & 0x20; }
static int serial_rx_ready(void) { return inb(COM1 + 5) & 0x01; }

void serial_putc(char c) {
    while (!serial_tx_ready());
    outb(COM1, (unsigned char)c);
}

void serial_puts(const char *s) { while (*s) serial_putc(*s++); }

int serial_available(void) { return serial_rx_ready(); }

int serial_getc(void) { return serial_rx_ready() ? (int)inb(COM1) : -1; }
