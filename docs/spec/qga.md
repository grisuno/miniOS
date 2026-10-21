# QEMU guest agent channel (COM2)

A guest-agent style channel on the second serial port, for a host tool to
drive the running system without the interactive console.

### UART contract (`headers/qga.h`)

The channel is the second ISA serial port: base `0x2F8`, IRQ 3, 115200
baud (divisor `0x01`), 8 data bits, no parity, one stop bit (LCR `0x03`),
FIFO control `0xC7` (FIFO enabled, cleared, 14-byte threshold) and modem
control `0x0B` (IRQs off, RTS/DSR set). The register offsets are a named
mirror of COM1: THR/RBR/DLL `0x00`, IER/DLM `0x01`, FCR `0x02`, MCR `0x04`,
LCR `0x03`, LSR `0x05`.

### Framing and bounds (`qga.c`)

One JSON request per line. A request line must fit `QGA_LINE_MAX` (512,
NUL included): an overlong line is discarded fail-closed and never
truncated into a command (`qga.c:465-469`). Replies are capped at
`QGA_RESP_MAX` (2048 bytes) and the cap is enforced while the response is
built, not when it is sent (`qga.c:180-195`).

`guest-file-read` answers with base64, so a read is bounded at
`QGA_FILE_READ_MAX` (1024 raw bytes), which keeps the encoded answer
comfortably inside `QGA_RESP_MAX`.

### Request shape (`headers/qga.h`, `qga.c`)

A request is `{"execute": "...", "arguments": {...}}`, flattened into a
key/value pair table so `arguments.id` is one key. The table is bounded at
`QGA_MAX_PAIRS` (16) with `QGA_KEY_MAX` (32) and `QGA_STR_MAX` (256)
characters per string, and `QGA_MAX_DEPTH` (2) bounds nested objects inside
`arguments` (depth 0 is the arguments object itself); deeper nesting is
rejected. Open guest files live in a table of `QGA_FILE_MAX` (8) handles,
indexed by the integer handle the protocol expects.

A malformed request is answered with a `GenericError`; an unknown command
with `CommandNotFound` (`qga.c:440-441`, `qga.c:457-458`).

### Commands (`qga.c`)

`guest-info` lists the supported set: `guest-file-close`,
`guest-file-open`, `guest-file-read`, `guest-exec`,
`guest-get-host-name`, `guest-get-osinfo`, `guest-get-time`,
`guest-info`, `guest-ping`, `guest-shutdown`, `guest-sync` and
`guest-sync-delimited` (`qga.c:260-275`). `guest-exec` queues a shell
command line and answers `{"return":{"pid":0}}`; the command runs at the
shell's next loop top and its output goes to the console, where the `>`
redirect still captures it (`qga.c:303-314`). `guest-sync-delimited` asks
for the `0xFF` marker byte that precedes the answer (`qga.c:182`,
`qga.c:461`).

### Host side (`tools/qga_client.py`, `tools/qga_test.sh`)

`tools/qga_client.py` speaks the protocol from the host: it connects to
the agent socket, sends one JSON request per line and prints the JSON
reply. The socket path defaults to `/tmp/minios-ga.sock` and is overridden
with `--sock` or the `MINIOS_GA_SOCK` environment variable. The framing is
the one QEMU's own `guest-agent-command` uses, so the same client drives
both. Usage: `qga_client.py guest-ping`,
`qga_client.py guest-exec '{"path":"..."}'`,
`qga_client.py guest-file-read '{"handle":0,"count":100}'`.

`tools/qga_test.sh` is the single-boot smoke test: it boots `os.img` once
with the agent socket as a QEMU chardev, waits for the shell prompt and
asserts the replies for `guest-ping`, `guest-info`, `guest-get-time`,
`guest-exec`, `guest-file-open`, `guest-file-read` (base64 content and the
exact byte count), an unknown command and a raw malformed request.

### Host wiring

The host side is a QEMU chardev socket mapped to COM2:

```
-chardev socket,path=/tmp/minios-ga.sock,server=on,wait=off,id=ga0 \
-device isa-serial,chardev=ga0,iobase=0x2F8,irq=3
```

### Build status

The channel source is `qga.c` with the contract in `headers/qga.h`, but
the current `Makefile` has no rule for it and `kernel.elf` carries no
`qga` symbol, so the kernel does not answer on COM2 yet: `qga_init` and
`qga_poll` have no call site. Wiring it means linking the object and
calling `qga_init` at boot and `qga_poll` from the shell's idle input
loop, which is where the agent expects to be polled (`qga.c:444-445`).

