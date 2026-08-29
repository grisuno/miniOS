#ifndef QGA_H
#define QGA_H

/* ========== QEMU guest agent channel (COM2, ISA 16550) ========== */
#define QGA_COM2_BASE      0x2F8
#define QGA_COM2_IRQ       3

/* UART registers (offsets from the COM base; named mirror of COM1). */
#define QGA_UART_THR       0x00   /* transmit holding */
#define QGA_UART_RBR       0x00   /* receive buffer (reads) */
#define QGA_UART_DLL       0x00   /* divisor lo (DLAB) */
#define QGA_UART_DLM       0x01   /* divisor hi (DLAB) */
#define QGA_UART_IER       0x01   /* interrupt enable */
#define QGA_UART_FCR       0x02   /* FIFO control */
#define QGA_UART_LCR       0x03   /* line control */
#define QGA_UART_LSR       0x05   /* line status */
#define QGA_UART_MCR       0x04   /* modem control */
#define QGA_UART_LSR_TX_RDY 0x20  /* transmit holding register empty */
#define QGA_UART_LSR_RX_RDY 0x01  /* receive data ready */
#define QGA_UART_LCR_DLAB   0x80  /* divisor latch access bit */
#define QGA_UART_LCR_8N1    0x03  /* 8 bits, no parity, one stop */
#define QGA_UART_FCR_CFG    0xC7  /* enable FIFO, clear, 14-byte threshold */
#define QGA_UART_MCR_CFG    0x0B  /* IRQs off, RTS/DSR set */

#define QGA_BAUD_DIVISOR    0x01  /* 115200 baud */

/* ========== Protocol bounds ========== */
/* A request line must fit QGA_LINE_MAX (including the NUL); overlong input
 * is rejected fail-closed, never truncated into a command. */
#define QGA_LINE_MAX        512
#define QGA_RESP_MAX        2048
/* guest-file-read returns base64, so a read of up to this many bytes keeps
 * the whole response comfortably inside QGA_RESP_MAX. */
#define QGA_FILE_READ_MAX   1024
/* Flat key/value pair table: a request is `{ "execute": "...",
 * "arguments": { ... } }`, flattened so `arguments.id` is one key. */
#define QGA_MAX_PAIRS       16
#define QGA_KEY_MAX         32
#define QGA_STR_MAX         256
/* Depth bound for nested objects inside `arguments` (0 = the arguments
 * object itself). Deeper nesting is rejected. */
#define QGA_MAX_DEPTH       2

/* guest-file handles: a small table of open ramdisk files indexed by the
 * integer handle QEMU's protocol expects. */
#define QGA_FILE_MAX        8

void qga_init(void);
void qga_poll(void);

#endif
