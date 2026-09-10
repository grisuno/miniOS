/** Docstring: x86 port I/O hardware abstraction contract.
 *
 * Centralizes every port number, controller command and device address
 * the timer ISR path touches, so sched.c no longer carries bare port
 * literals or raw inb/outb asm. The inline accessors emit exactly the
 * same instructions as the previous open-coded sites. Under
 * HAL_IO_HOST_TEST the accessors log to stub counters instead of
 * executing privileged instructions, which makes the constant mapping
 * host-testable without hardware.
 */

#ifndef HAL_IO_H
#define HAL_IO_H

/** Docstring: Master PIC command port. */
#define HAL_PIC1_CMD 0x20
/** Docstring: Master PIC data port. */
#define HAL_PIC1_DATA 0x21
/** Docstring: Slave PIC command port. */
#define HAL_PIC2_CMD 0xA0
/** Docstring: Slave PIC data port. */
#define HAL_PIC2_DATA 0xA1
/** Docstring: PIC end-of-interrupt command byte. */
#define HAL_PIC_EOI 0x20

/** Docstring: PIT mode/command port. */
#define HAL_PIT_CMD 0x43
/** Docstring: PIT channel 0 data port. */
#define HAL_PIT_CH0 0x40

/** Docstring: PS/2 controller status port. */
#define HAL_PS2_STATUS 0x64
/** Docstring: PS/2 controller data port. */
#define HAL_PS2_DATA 0x60
/** Docstring: PS/2 status bit for mouse output buffer full. */
#define HAL_PS2_MOUSE_OBF 0x20
/** Docstring: PS/2 status bit for input buffer empty. */
#define HAL_PS2_IBF_EMPTY 0x02
/** Docstring: PS/2 status bit for output buffer full. */
#define HAL_PS2_OBF_FULL 0x01

/** Docstring: Mouse packet first-byte sync bit. */
#define HAL_MOUSE_SYNC_BIT 0x08
/** Docstring: Mouse packet first-byte overflow bits (X/Y counters wrapped). */
#define HAL_MOUSE_OVF_BITS 0xC0
/** Docstring: Mouse packet button mask. */
#define HAL_MOUSE_BUTTON_MASK 0x07
/** Docstring: Mouse packet byte count for Intellimouse mode. */
#define HAL_MOUSE_PACKET_LEN 4
/** Docstring: Mouse motion scale factor. */
#define HAL_MOUSE_SCALE 2

/** Docstring: Local APIC end-of-interrupt MMIO address. */
#define HAL_LAPIC_EOI_ADDR 0xFEE000B0UL

#ifdef HAL_IO_HOST_TEST

/** Docstring: Stub log for host tests, counts port writes. */
extern unsigned hal_io_stub_writes;
/** Docstring: Stub log for host tests, last port written. */
extern unsigned hal_io_stub_last_port;
/** Docstring: Stub log for host tests, last value written. */
extern unsigned hal_io_stub_last_val;
/** Docstring: Stub log for host tests, counts LAPIC EOI calls. */
extern unsigned hal_io_stub_lapic_eois;
/** Docstring: Canned byte returned by stub port reads. */
extern unsigned char hal_io_stub_read_val;

/** Docstring: Stub port byte write, records port and value. */
static inline void hal_outb(unsigned short port, unsigned char val) {
    hal_io_stub_writes++;
    hal_io_stub_last_port = port;
    hal_io_stub_last_val = val;
}

/** Docstring: Stub port byte read, returns the canned value. */
static inline unsigned char hal_inb(unsigned short port) {
    (void)port;
    return hal_io_stub_read_val;
}

/** Docstring: Stub port word write, records port and low byte. */
static inline void hal_outw(unsigned short port, unsigned short val) {
    hal_io_stub_writes++;
    hal_io_stub_last_port = port;
    hal_io_stub_last_val = (unsigned)(val & 0xFFU);
}

/** Docstring: Stub port word read, returns the canned value. */
static inline unsigned short hal_inw(unsigned short port) {
    (void)port;
    return (unsigned short)hal_io_stub_read_val;
}

/** Docstring: Stub LAPIC EOI, counts calls. */
static inline void hal_lapic_eoi(void) {
    hal_io_stub_lapic_eois++;
}

/** Docstring: Stub PIC EOI for an IRQ line. */
static inline void hal_pic_eoi(int irq) {
    if (irq >= 8) {
        hal_outb(HAL_PIC2_CMD, HAL_PIC_EOI);
    }
    hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI);
}

#else

/** Docstring: Emit a port byte write. */
static inline void hal_outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

/** Docstring: Emit a port byte read. */
static inline unsigned char hal_inb(unsigned short port) {
    unsigned char r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

/** Docstring: Emit a port word write. */
static inline void hal_outw(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

/** Docstring: Emit a port word read. */
static inline unsigned short hal_inw(unsigned short port) {
    unsigned short r;
    __asm__ volatile("inw %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}

/** Docstring: Acknowledge the local APIC after an IPI-driven tick. */
static inline void hal_lapic_eoi(void) {
    *(volatile unsigned *)HAL_LAPIC_EOI_ADDR = 0;
}

/** Docstring: Send end-of-interrupt for an IRQ line. */
static inline void hal_pic_eoi(int irq) {
    if (irq >= 8) {
        hal_outb(HAL_PIC2_CMD, HAL_PIC_EOI);
    }
    hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI);
}

#endif

#endif
