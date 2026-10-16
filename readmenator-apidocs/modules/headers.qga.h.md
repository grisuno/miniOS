# `headers/qga.h`

> Source: [headers/qga.h:1](../../headers/qga.h#L1) | language `h` | coverage 72.4% | [API index](../index.md)

## Contents

- **Functions:** [`qga_init`](#qga_init), [`qga_poll`](#qga_poll)
- **Macros:** [`QGA_COM2_BASE`](#qga_com2_base), [`QGA_COM2_IRQ`](#qga_com2_irq), [`QGA_UART_THR`](#qga_uart_thr), [`QGA_UART_RBR`](#qga_uart_rbr), [`QGA_UART_DLL`](#qga_uart_dll), [`QGA_UART_DLM`](#qga_uart_dlm), [`QGA_UART_IER`](#qga_uart_ier), [`QGA_UART_FCR`](#qga_uart_fcr), [`QGA_UART_LCR`](#qga_uart_lcr), [`QGA_UART_LSR`](#qga_uart_lsr), [`QGA_UART_MCR`](#qga_uart_mcr), [`QGA_UART_LSR_TX_RDY`](#qga_uart_lsr_tx_rdy), [`QGA_UART_LSR_RX_RDY`](#qga_uart_lsr_rx_rdy), [`QGA_UART_LCR_DLAB`](#qga_uart_lcr_dlab), [`QGA_UART_LCR_8N1`](#qga_uart_lcr_8n1), [`QGA_UART_FCR_CFG`](#qga_uart_fcr_cfg), [`QGA_UART_MCR_CFG`](#qga_uart_mcr_cfg), [`QGA_BAUD_DIVISOR`](#qga_baud_divisor), [`QGA_LINE_MAX`](#qga_line_max), [`QGA_RESP_MAX`](#qga_resp_max), [`QGA_FILE_READ_MAX`](#qga_file_read_max), [`QGA_MAX_PAIRS`](#qga_max_pairs), [`QGA_KEY_MAX`](#qga_key_max), [`QGA_STR_MAX`](#qga_str_max), [`QGA_MAX_DEPTH`](#qga_max_depth), [`QGA_FILE_MAX`](#qga_file_max)

## Functions

<a id="qga_init"></a>

### `qga_init`

`function` | [headers/qga.h:48](../../headers/qga.h#L48)

```c
void qga_init(void);
```

---

<a id="qga_poll"></a>

### `qga_poll`

`function` | [headers/qga.h:49](../../headers/qga.h#L49)

```c
void qga_poll(void);
```

---

## Macros

<a id="qga_com2_base"></a>

### `QGA_COM2_BASE`

`macro` | [headers/qga.h:5](../../headers/qga.h#L5)

```c
#define QGA_COM2_BASE
```

========== QEMU guest agent channel (COM2, ISA 16550) ==========

---

<a id="qga_com2_irq"></a>

### `QGA_COM2_IRQ`

`macro` | [headers/qga.h:6](../../headers/qga.h#L6)

```c
#define QGA_COM2_IRQ
```

---

<a id="qga_uart_thr"></a>

### `QGA_UART_THR`

`macro` | [headers/qga.h:9](../../headers/qga.h#L9)

```c
#define QGA_UART_THR
```

UART registers (offsets from the COM base; named mirror of COM1).

---

<a id="qga_uart_rbr"></a>

### `QGA_UART_RBR`

`macro` | [headers/qga.h:10](../../headers/qga.h#L10)

```c
#define QGA_UART_RBR
```

transmit holding

---

<a id="qga_uart_dll"></a>

### `QGA_UART_DLL`

`macro` | [headers/qga.h:11](../../headers/qga.h#L11)

```c
#define QGA_UART_DLL
```

receive buffer (reads)

---

<a id="qga_uart_dlm"></a>

### `QGA_UART_DLM`

`macro` | [headers/qga.h:12](../../headers/qga.h#L12)

```c
#define QGA_UART_DLM
```

divisor lo (DLAB)

---

<a id="qga_uart_ier"></a>

### `QGA_UART_IER`

`macro` | [headers/qga.h:13](../../headers/qga.h#L13)

```c
#define QGA_UART_IER
```

divisor hi (DLAB)

---

<a id="qga_uart_fcr"></a>

### `QGA_UART_FCR`

`macro` | [headers/qga.h:14](../../headers/qga.h#L14)

```c
#define QGA_UART_FCR
```

interrupt enable

---

<a id="qga_uart_lcr"></a>

### `QGA_UART_LCR`

`macro` | [headers/qga.h:15](../../headers/qga.h#L15)

```c
#define QGA_UART_LCR
```

FIFO control

---

<a id="qga_uart_lsr"></a>

### `QGA_UART_LSR`

`macro` | [headers/qga.h:16](../../headers/qga.h#L16)

```c
#define QGA_UART_LSR
```

line control

---

<a id="qga_uart_mcr"></a>

### `QGA_UART_MCR`

`macro` | [headers/qga.h:17](../../headers/qga.h#L17)

```c
#define QGA_UART_MCR
```

line status

---

<a id="qga_uart_lsr_tx_rdy"></a>

### `QGA_UART_LSR_TX_RDY`

`macro` | [headers/qga.h:18](../../headers/qga.h#L18)

```c
#define QGA_UART_LSR_TX_RDY
```

modem control

---

<a id="qga_uart_lsr_rx_rdy"></a>

### `QGA_UART_LSR_RX_RDY`

`macro` | [headers/qga.h:19](../../headers/qga.h#L19)

```c
#define QGA_UART_LSR_RX_RDY
```

transmit holding register empty

---

<a id="qga_uart_lcr_dlab"></a>

### `QGA_UART_LCR_DLAB`

`macro` | [headers/qga.h:20](../../headers/qga.h#L20)

```c
#define QGA_UART_LCR_DLAB
```

receive data ready

---

<a id="qga_uart_lcr_8n1"></a>

### `QGA_UART_LCR_8N1`

`macro` | [headers/qga.h:21](../../headers/qga.h#L21)

```c
#define QGA_UART_LCR_8N1
```

divisor latch access bit

---

<a id="qga_uart_fcr_cfg"></a>

### `QGA_UART_FCR_CFG`

`macro` | [headers/qga.h:22](../../headers/qga.h#L22)

```c
#define QGA_UART_FCR_CFG
```

8 bits, no parity, one stop

---

<a id="qga_uart_mcr_cfg"></a>

### `QGA_UART_MCR_CFG`

`macro` | [headers/qga.h:23](../../headers/qga.h#L23)

```c
#define QGA_UART_MCR_CFG
```

enable FIFO, clear, 14-byte threshold

---

<a id="qga_baud_divisor"></a>

### `QGA_BAUD_DIVISOR`

`macro` | [headers/qga.h:25](../../headers/qga.h#L25)

```c
#define QGA_BAUD_DIVISOR
```

---

<a id="qga_line_max"></a>

### `QGA_LINE_MAX`

`macro` | [headers/qga.h:30](../../headers/qga.h#L30)

```c
#define QGA_LINE_MAX
```

A request line must fit QGA_LINE_MAX (including the NUL); overlong input is rejected fail-closed, never truncated into a command.

---

<a id="qga_resp_max"></a>

### `QGA_RESP_MAX`

`macro` | [headers/qga.h:31](../../headers/qga.h#L31)

```c
#define QGA_RESP_MAX
```

---

<a id="qga_file_read_max"></a>

### `QGA_FILE_READ_MAX`

`macro` | [headers/qga.h:34](../../headers/qga.h#L34)

```c
#define QGA_FILE_READ_MAX
```

guest-file-read returns base64, so a read of up to this many bytes keeps the whole response comfortably inside QGA_RESP_MAX.

---

<a id="qga_max_pairs"></a>

### `QGA_MAX_PAIRS`

`macro` | [headers/qga.h:37](../../headers/qga.h#L37)

```c
#define QGA_MAX_PAIRS
```

Flat key/value pair table: a request is `{ "execute": "...", "arguments": { ... } }`, flattened so `arguments.id` is one key.

---

<a id="qga_key_max"></a>

### `QGA_KEY_MAX`

`macro` | [headers/qga.h:38](../../headers/qga.h#L38)

```c
#define QGA_KEY_MAX
```

---

<a id="qga_str_max"></a>

### `QGA_STR_MAX`

`macro` | [headers/qga.h:39](../../headers/qga.h#L39)

```c
#define QGA_STR_MAX
```

---

<a id="qga_max_depth"></a>

### `QGA_MAX_DEPTH`

`macro` | [headers/qga.h:42](../../headers/qga.h#L42)

```c
#define QGA_MAX_DEPTH
```

Depth bound for nested objects inside [`arguments`](progs.freedomui.ps2_keymap.h.md#arguments) (0 = the arguments object itself).

Deeper nesting is rejected.

---

<a id="qga_file_max"></a>

### `QGA_FILE_MAX`

`macro` | [headers/qga.h:46](../../headers/qga.h#L46)

```c
#define QGA_FILE_MAX
```

guest-file handles: a small table of open ramdisk files indexed by the integer handle QEMU's protocol expects.

---
