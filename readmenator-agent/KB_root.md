# Subsystem: root

## ap_stub.h
- Layer: testing
- Doc: generated from ap_stub.bin - do not edit
- Language: h

## app.py
- Layer: utility
- Doc: _*_ coding: utf8 _*_
- Language: py

## audio.h
- Layer: infrastructure
- Doc: ifndef AUDIO_H define AUDIO_H  Unified audio API for MiniOS.
- Language: h
- Symbols:
  - `AUDIO_H` (macro, line 2)
  - `AUDIO_RATE_DEFAULT` (macro, line 14)
  - `AUDIO_CHANNELS_MONO` (macro, line 16)
  - `AUDIO_FORMAT_U8` (macro, line 17)
  - `AUDIO_FORMAT_S16` (macro, line 18)

## block.h
- Layer: utility
- Doc: ifndef BLOCK_H define BLOCK_H  Block device abstraction for MiniFS. Maps 4096-byte logical blocks to 512-byte IDE sector
- Language: h
- Symbols:
  - `BLOCK_H` (macro, line 2)
  - `BLOCK_SIZE` (macro, line 6)
  - `BLOCK_SHIFT` (macro, line 8)
  - `SECTORS_PER_BLOCK` (macro, line 9)

## bootloader.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 20) `void main(void)`
  - `KSECTORS` (macro, line 19)

## desktop_icons.h
- Layer: utility
- Doc: desktop_icons.h -- embedded icon pixel data for desktop shortcuts.
- Language: h
- Symbols:
  - `DESKTOP_ICONS_H` (macro, line 8)
  - `ICON_EMBEDDED_W` (macro, line 11)
  - `ICON_EMBEDDED_H` (macro, line 13)

## desktop_shortcuts.h
- Layer: utility
- Doc: desktop_shortcuts.h -- configurable desktop icon shortcuts.
- Language: h
- Symbols:
  - `desktop_shortcut` (struct, line 36)
  - `DESKTOP_SHORTCUTS_H` (macro, line 12)
  - `MAX_SHORTCUTS` (macro, line 17)
  - `SHORTCUT_NAME_LEN` (macro, line 18)
  - `SHORTCUT_CMD_LEN` (macro, line 19)
  - `SHORTCUT_PATH_LEN` (macro, line 20)
  - `ICON_W` (macro, line 23)
  - `ICON_H` (macro, line 24)
  - `ICON_PAD_X` (macro, line 25)
  - `ICON_PAD_Y` (macro, line 26)
  - `ICON_LABEL_H` (macro, line 27)
  - `ICON_PAL_BASE` (macro, line 32)
  - `ICON_PAL_SIZE` (macro, line 33)

## editor.h
- Layer: infrastructure
- Doc: ifndef EDITOR_H define EDITOR_H  editor.h -- the built-in line editor contract.
- Language: h
- Symbols:
  - `EDITOR_H` (macro, line 2)

## gen_minifs.py
- Layer: utility
- Language: py

## ide.h
- Layer: utility
- Doc: ifndef IDE_H define IDE_H  IDE/ATA PIO driver for MiniOS.
- Language: h
- Symbols:
  - `IDE_H` (macro, line 2)
  - `IDE_PRIMARY_BASE` (macro, line 9)
  - `IDE_PRIMARY_CTRL` (macro, line 10)
  - `IDE_REG_DATA` (macro, line 13)
  - `IDE_REG_ERROR` (macro, line 14)
  - `IDE_REG_SECCOUNT` (macro, line 15)
  - `IDE_REG_LBA_LO` (macro, line 16)
  - `IDE_REG_LBA_MID` (macro, line 17)
  - `IDE_REG_LBA_HI` (macro, line 18)
  - `IDE_REG_DRIVE` (macro, line 19)
  - `IDE_REG_STATUS` (macro, line 20)
  - `IDE_REG_ALTSTATUS` (macro, line 21)
  - `IDE_STATUS_ERR` (macro, line 24)
  - `IDE_STATUS_DRQ` (macro, line 25)
  - `IDE_STATUS_SRV` (macro, line 26)
  - `IDE_STATUS_DF` (macro, line 27)
  - `IDE_STATUS_RDY` (macro, line 28)
  - `IDE_STATUS_BSY` (macro, line 29)
  - `IDE_CMD_READ` (macro, line 32)
  - `IDE_CMD_WRITE` (macro, line 33)
  - `IDE_CMD_IDENTIFY` (macro, line 34)
  - `IDE_CMD_FLUSH` (macro, line 35)
  - `IDE_DRIVE_LBA` (macro, line 38)
  - `IDE_DRIVE_MASTER` (macro, line 39)
  - `IDE_DRIVE_SLAVE` (macro, line 40)
  - `IDE_TIMEOUT` (macro, line 43)
  - `IDE_SECTOR_SIZE` (macro, line 46)

## install.sh
- Layer: utility
- Language: sh

## kernel.c
- Layer: utility
- Doc: include "kernel.h" include "net.h" include "tls.h" include "bootdefs.h" include "minifs.h" include "ide.h" include "bloc
- Language: c
- Symbols:
  - `vga_get_x` (function, line 29) `int vga_get_x(void)`
  - `vga_get_y` (function, line 31) `int vga_get_y(void)`
  - `vga_set_xy` (function, line 32) `void vga_set_xy(int x, int y)`
  - `vga_get_color` (function, line 33) `char vga_get_color(void)`
  - `vga_offset` (function, line 36) `static inline unsigned vga_offset(int x, int y)`
  - `vga_clear` (function, line 38) `void vga_clear(void)`
  - `vga_set_cursor` (function, line 49) `void vga_set_cursor(int x, int y)`
  - `vga_scroll` (function, line 69) `void vga_scroll(void)`
  - `vga_newline` (function, line 88) `void vga_newline(void)`
  - `vga_cursor_enable` (function, line 99) `void vga_cursor_enable(int on)`
  - `vga_raw_space` (function, line 105) `static void vga_raw_space(void)`
  - `redir_grow` (function, line 128) `static int redir_grow(void)`
  - `redirect_active` (function, line 138) `int redirect_active(void)`
  - `redirect_putc` (function, line 140) `static int redirect_putc(char c)`
  - `redirect_suspend` (function, line 147) `int redirect_suspend(void)`
  - `redirect_resume` (function, line 153) `void redirect_resume(int was)`
  - `redirect_begin` (function, line 157) `int redirect_begin(void)`
  - `redirect_commit` (function, line 165) `int redirect_commit(const char *path, int append_mode)`
  - `vga_putc` (function, line 182) `void vga_putc(char c)`
  - `vga_puts` (function, line 220) `void vga_puts(const char *s)`
  - `syscall_init` (function, line 304) `void syscall_init(void)`
  - `register_libc_symbols` (function, line 398) `static void register_libc_symbols(void)`
  - `__attribute__` (function, line 473) `__attribute__((section(".init.text")))
void kmain(void)`
  - `XXH_STATIC_LINKING_ONLY` (macro, line 17)
  - `REDIR_INITIAL_CAP` (macro, line 119)
  - `REDIR_MAX_BYTES` (macro, line 121)
  - `USER_WIN_LO` (macro, line 253)
  - `USER_WIN_HI` (macro, line 254)
  - `STR_` (macro, line 255)
  - `STR` (macro, line 256)
  - `KSYM_MAX` (macro, line 294)

## kernel.h
- Layer: utility
- Doc: ifndef KERNEL_H define KERNEL_H  define EFAULT  (-14)  The user-window memory layout (load base, stack, brk cap, graphic
- Language: h
- Symbols:
  - `vfs_ops` (struct, line 246)
  - `vfs_file` (struct, line 255)
  - `outb` (function, line 20) `static inline void outb(unsigned short port, unsigned char val)`
  - `inb` (function, line 23) `static inline unsigned char inb(unsigned short port)`
  - `outw` (function, line 28) `static inline void outw(unsigned short port, unsigned short val)`
  - `inw` (function, line 31) `static inline unsigned short inw(unsigned short port)`
  - `KERNEL_H` (macro, line 2)
  - `EFAULT` (macro, line 3)
  - `ALIGN_UP` (macro, line 17)
  - `PORT_IO_DEFINED` (macro, line 19)
  - `VGA_BASE` (macro, line 39)
  - `VGA_COLS` (macro, line 40)
  - `VGA_ROWS` (macro, line 41)
  - `KEY_BACKSPACE` (macro, line 73)
  - `KEY_ENTER` (macro, line 74)
  - `KEY_LSHIFT` (macro, line 75)
  - `KEY_RSHIFT` (macro, line 76)
  - `KEY_CAPS` (macro, line 77)
  - `KEY_E0` (macro, line 78)
  - `KEY_UP` (macro, line 79)
  - `KEY_DOWN` (macro, line 80)
  - `KEY_PGUP` (macro, line 81)
  - `KEY_PGDN` (macro, line 82)
  - `KEY_ESC` (macro, line 83)
  - `KEY_CSI` (macro, line 84)
  - `KEY_ARR_UP` (macro, line 85)
  - `KEY_ARR_DOWN` (macro, line 86)
  - `KEY_ARR_RIGHT` (macro, line 87)
  - `KEY_ARR_LEFT` (macro, line 88)
  - `KEY_HOME_SEQ` (macro, line 89)
  - `KEY_END_SEQ` (macro, line 90)
  - `KEY_PGUP_SEQ` (macro, line 91)
  - `KEY_PGDN_SEQ` (macro, line 92)
  - `KEY_LEFT` (macro, line 93)
  - `KEY_RIGHT` (macro, line 94)
  - `KEY_LCTRL` (macro, line 95)
  - `KEY_F5` (macro, line 96)
  - `KEY_F11` (macro, line 97)
  - `KEY_TILDE` (macro, line 98)
  - `KEY_LALT` (macro, line 99)
  - `KEY_RALT` (macro, line 100)
  - `KEY_HOME` (macro, line 101)
  - `KEY_END` (macro, line 102)
  - `USER_LOAD_BASE` (macro, line 118)
  - `USER_LOAD_END` (macro, line 119)
  - `USER_STACK_SIZE` (macro, line 120)
  - `USER_STACK_TOP` (macro, line 121)
  - `USER_STACK_BASE` (macro, line 122)
  - `USER_BRK_END` (macro, line 123)
  - `SYS_KSTK_TOP` (macro, line 128)
  - `SYS_KSTK_BASE` (macro, line 129)
  - `HEAP_BASE` (macro, line 130)
  - `HEAP_SIZE` (macro, line 132)
  - `RAMDISK_MAX_FILES` (macro, line 171)
  - `RAMDISK_FNAME_LEN` (macro, line 172)
  - `RD_DATA_MAX` (macro, line 191)
  - `EOF` (macro, line 297)
  - `KSYM_MAX` (macro, line 393)
  - `KPROG_MAX` (macro, line 395)
  - `EI_NIDENT` (macro, line 466)
  - `ET_REL` (macro, line 490)
  - `ET_EXEC` (macro, line 492)
  - `ET_DYN` (macro, line 493)
  - `KFD_MAX` (macro, line 506)

## lz4_kernel.h
- Layer: utility
- Doc: ifndef LZ4_KERNEL_H define LZ4_KERNEL_H
- Language: h
- Symbols:
  - `LZ4_KERNEL_H` (macro, line 2)

## minifs.h
- Layer: utility
- Doc: ifndef MINIFS_H define MINIFS_H  MiniFS: a minimal Unix-like filesystem for MiniOS.
- Language: h
- Symbols:
  - `MINIFS_H` (macro, line 2)
  - `MINIFS_MAGIC` (macro, line 7)
  - `MINIFS_VERSION` (macro, line 9)
  - `MINIFS_BLOCK_SIZE` (macro, line 10)
  - `MINIFS_MAX_FILENAME` (macro, line 11)
  - `MINIFS_ROOT_INODE` (macro, line 12)
  - `MINIFS_INODES_PER_BLOCK` (macro, line 13)
  - `MINIFS_DIR_ENTRIES_PER_BLOCK` (macro, line 14)
  - `MINIFS_S_IFMT` (macro, line 15)
  - `MINIFS_S_IFREG` (macro, line 17)
  - `MINIFS_S_IFDIR` (macro, line 18)
  - `MINIFS_S_IFLNK` (macro, line 19)
  - `MINIFS_S_IRWXU` (macro, line 20)
  - `MINIFS_S_IRWXG` (macro, line 21)
  - `MINIFS_S_IRWXO` (macro, line 22)
  - `MINIFS_FT_FILE` (macro, line 23)
  - `MINIFS_FT_DIR` (macro, line 25)
  - `MINIFS_FT_SYMLINK` (macro, line 26)
  - `MINIFS_INODE_COMPRESSED` (macro, line 27)
  - `MINIFS_DIR_ENTRY_HDR_SIZE` (macro, line 74)
  - `MINIFS_JOURNAL_BLOCKS` (macro, line 76)
  - `MINIFS_JOURNAL_MAX_ENTRIES` (macro, line 78)
  - `MINIFS_JOP_WRITE` (macro, line 79)
  - `MINIFS_JOP_CREATE` (macro, line 80)
  - `MINIFS_JOP_DELETE` (macro, line 81)
  - `MINIFS_JOP_MKDIR` (macro, line 82)
  - `MINIFS_JOP_RMDIR` (macro, line 83)
  - `MINIFS_JOP_TRUNCATE` (macro, line 84)
  - `MINIFS_JOP_COMMIT` (macro, line 85)
  - `MINIFS_JSTATE_CLEAN` (macro, line 86)
  - `MINIFS_JSTATE_DIRTY` (macro, line 88)

## minifs_dump.py
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `mode_str` (function, line 16) `def mode_str(m)`
  - `FS` (class, line 25) `class FS`
  - `main` (method, line 105) `def main()`
  - `__init__` (method, line 26) `def __init__(self, fn)`
  - `blk` (method, line 29) `def blk(self, n)`
  - `_sb` (method, line 30) `def _sb(self)`
  - `inode` (method, line 38) `def inode(self, i)`
  - `read` (method, line 47) `def read(self, ino)`
  - `resolve` (method, line 67) `def resolve(self, path)`
  - `ls` (method, line 86) `def ls(self, ino, prefix)`

## minifs_fsck.py
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `FSCK` (class, line 16) `class FSCK`
  - `main` (method, line 97) `def main()`
  - `__init__` (method, line 17) `def __init__(self, fn)`
  - `blk` (method, line 23) `def blk(self, n)`
  - `_sb` (method, line 24) `def _sb(self)`
  - `inode` (method, line 30) `def inode(self, i)`
  - `read` (method, line 37) `def read(self, ino)`
  - `err` (method, line 52) `def err(self, msg)`
  - `mark_block` (method, line 54) `def mark_block(self, n)`
  - `scan_inode` (method, line 59) `def scan_inode(self, i)`
  - `scan_dir` (method, line 68) `def scan_dir(self, ino)`
  - `run` (method, line 82) `def run(self)`

## mkfs.minifs.py
- Layer: utility
- Language: py
- Symbols:
  - `roundup4` (function, line 22) `def roundup4(v)`
  - `div_round_up` (function, line 25) `def div_round_up(n, d)`
  - `crc16` (function, line 28) `def crc16(data)`
  - `crc32` (function, line 36) `def crc32(data)`
  - `MiniFS` (class, line 44) `class MiniFS`
  - `main` (method, line 241) `def main()`
  - `__init__` (method, line 45) `def __init__(self, total_blocks)`
  - `mark_inodes_used` (method, line 67) `def mark_inodes_used(self, start, count)`
  - `mark_blocks_used` (method, line 71) `def mark_blocks_used(self, start, count)`
  - `alloc_inode` (method, line 75) `def alloc_inode(self)`
  - `alloc_block` (method, line 81) `def alloc_block(self)`
  - `create_root` (method, line 87) `def create_root(self)`
  - `create_inode` (method, line 95) `def create_inode(self, mode)`
  - `inode_set_size` (method, line 102) `def inode_set_size(self, ino, size)`
  - `inode_set_block` (method, line 106) `def inode_set_block(self, ino, logblk, phys)`
  - `add_dir_entry` (method, line 136) `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
  - `write_file` (method, line 174) `def write_file(self, parent_ino, name, data)`
  - `write_dir` (method, line 191) `def write_dir(self, parent_ino, name)`
  - `serialize` (method, line 197) `def serialize(self)`
  - `pack_tree` (method, line 271) `def pack_tree(parent_ino, path, rel)`

## mkramdisk.py
- Layer: infrastructure
- Language: py
- Symbols:
  - `pack_name` (function, line 20) `def pack_name(path, common)`
  - `main` (function, line 30) `def main()`

## mkroots.sh
- Layer: utility
- Doc: mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Provenance of each root (2026 web PKI reality
- Language: sh

## mutate.sh
- Layer: utility
- Doc: Mutation testing for MiniOS.  Each mutation is applied to the source in place, the disk image is rebuilt and the behavio
- Language: sh
- Symbols:
  - `usage` (function, line 51)
  - `restore_sources` (function, line 87)
  - `cleanup` (function, line 94)
  - `record` (function, line 201)
  - `find_index` (function, line 207)

## net.h
- Layer: utility
- Doc: ifndef NET_H define NET_H  ========== Fixed slirp configuration (QEMU -nic user) ==========
- Language: h
- Symbols:
  - `NET_H` (macro, line 2)
  - `NET_IP_ADDR` (macro, line 5)
  - `NET_NETMASK` (macro, line 6)
  - `NET_GATEWAY` (macro, line 7)
  - `NET_DNS` (macro, line 8)
  - `NET_PCI_VENDOR` (macro, line 11)
  - `NET_PCI_DEVICE` (macro, line 12)
  - `NET_RX_BUF_LEN` (macro, line 18)
  - `NET_RX_ALIGN` (macro, line 19)
  - `NET_RCR` (macro, line 22)
  - `NET_MAX_FRAME` (macro, line 23)
  - `NET_TX_SLOTS` (macro, line 24)
  - `NET_ETH_ALEN` (macro, line 27)
  - `NET_ETHERTYPE_IP` (macro, line 28)
  - `NET_ETHERTYPE_ARP` (macro, line 29)
  - `NET_PROTO_ICMP` (macro, line 32)
  - `NET_PROTO_TCP` (macro, line 33)
  - `NET_PROTO_UDP` (macro, line 34)
  - `NET_ARP_CACHE` (macro, line 37)
  - `NET_ARP_REQUEST` (macro, line 38)
  - `NET_ARP_REPLY` (macro, line 39)
  - `NET_TCP_MSS` (macro, line 42)
  - `NET_TCP_WINDOW` (macro, line 43)
  - `NET_SOCK_RX_BUF` (macro, line 46)
  - `NET_RX_RING_SIZE` (macro, line 47)
  - `NET_SOCKETS` (macro, line 48)
  - `NET_DNS_PORT` (macro, line 49)
  - `NET_EPHEMERAL_MIN` (macro, line 50)
  - `NET_DNS_TRIES` (macro, line 51)
  - `NET_DNS_TMO_MS` (macro, line 52)
  - `NET_CONNECT_TMO_S` (macro, line 53)
  - `NET_RETRY_MS` (macro, line 54)
  - `NET_TX_MAX` (macro, line 55)
  - `NET_FD_BASE` (macro, line 58)

## pcspk.h
- Layer: utility
- Doc: ifndef PCSPK_H define PCSPK_H  define PCSPK_VOL_MIN     0 define PCSPK_VOL_MAX     100 define PCSPK_VOL_DEFAULT 100
- Language: h
- Symbols:
  - `PCSPK_H` (macro, line 2)
  - `PCSPK_VOL_MIN` (macro, line 3)
  - `PCSPK_VOL_MAX` (macro, line 5)
  - `PCSPK_VOL_DEFAULT` (macro, line 6)

## qga.c
- Layer: utility
- Doc: MiniOS QEMU guest agent (QGA).
- Language: c
- Symbols:
  - `qga_pair` (struct, line 49)
  - `qga_tx_ready` (function, line 26) `static int qga_tx_ready(void)`
  - `qga_rx_ready` (function, line 28) `static int qga_rx_ready(void)`
  - `qga_putc` (function, line 29) `static void qga_putc(char c)`
  - `qga_init` (function, line 34) `void qga_init(void)`
  - `qga_ws` (function, line 55) `static int qga_ws(char c)`
  - `qga_parse_object` (function, line 65) `static int qga_parse_object(const char **pp, struct qga_pair *out, int max,
                     ...`
  - `qga_parse_flat` (function, line 147) `static int qga_parse_flat(const char *s, struct qga_pair *out, int max)`
  - `qga_get_str` (function, line 157) `static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key)`
  - `qga_get_int` (function, line 165) `static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out)`
  - `qga_resp_reset` (function, line 183) `static void qga_resp_reset(void)`
  - `qga_resp_puts` (function, line 185) `static void qga_resp_puts(const char *s)`
  - `qga_resp_putc_enc` (function, line 193) `static void qga_resp_putc_enc(char c)`
  - `qga_resp_put_long` (function, line 201) `static void qga_resp_put_long(long v)`
  - `qga_err` (function, line 209) `static void qga_err(const char *klass, const char *desc)`
  - `qga_puts_resp` (function, line 217) `static void qga_puts_resp(void)`
  - `qga_b64_encode` (function, line 230) `static void qga_b64_encode(const unsigned char *in, int n)`
  - `qga_cmd_get_time` (function, line 280) `static void qga_cmd_get_time(void)`
  - `qga_cmd_exec` (function, line 306) `static void qga_cmd_exec(const struct qga_pair *pairs, int n)`
  - `qga_cmd_shutdown` (function, line 315) `static void qga_cmd_shutdown(const struct qga_pair *pairs, int n)`
  - `qga_file_size` (function, line 328) `static int qga_file_size(const KFILE *f)`
  - `qga_cmd_file_open` (function, line 333) `static void qga_cmd_file_open(const struct qga_pair *pairs, int n)`
  - `qga_cmd_file_read` (function, line 359) `static void qga_cmd_file_read(const struct qga_pair *pairs, int n)`
  - `qga_cmd_file_close` (function, line 383) `static void qga_cmd_file_close(const struct qga_pair *pairs, int n)`
  - `qga_dispatch` (function, line 400) `static void qga_dispatch(struct qga_pair *pairs, int n)`
  - `qga_poll` (function, line 446) `void qga_poll(void)`

## qga.h
- Layer: utility
- Doc: ifndef QGA_H define QGA_H  ========== QEMU guest agent channel (COM2, ISA 16550) ==========
- Language: h
- Symbols:
  - `QGA_H` (macro, line 2)
  - `QGA_COM2_BASE` (macro, line 5)
  - `QGA_COM2_IRQ` (macro, line 6)
  - `QGA_UART_THR` (macro, line 9)
  - `QGA_UART_RBR` (macro, line 10)
  - `QGA_UART_DLL` (macro, line 11)
  - `QGA_UART_DLM` (macro, line 12)
  - `QGA_UART_IER` (macro, line 13)
  - `QGA_UART_FCR` (macro, line 14)
  - `QGA_UART_LCR` (macro, line 15)
  - `QGA_UART_LSR` (macro, line 16)
  - `QGA_UART_MCR` (macro, line 17)
  - `QGA_UART_LSR_TX_RDY` (macro, line 18)
  - `QGA_UART_LSR_RX_RDY` (macro, line 19)
  - `QGA_UART_LCR_DLAB` (macro, line 20)
  - `QGA_UART_LCR_8N1` (macro, line 21)
  - `QGA_UART_FCR_CFG` (macro, line 22)
  - `QGA_UART_MCR_CFG` (macro, line 23)
  - `QGA_BAUD_DIVISOR` (macro, line 24)
  - `QGA_LINE_MAX` (macro, line 30)
  - `QGA_RESP_MAX` (macro, line 31)
  - `QGA_FILE_READ_MAX` (macro, line 34)
  - `QGA_MAX_PAIRS` (macro, line 37)
  - `QGA_KEY_MAX` (macro, line 38)
  - `QGA_STR_MAX` (macro, line 39)
  - `QGA_MAX_DEPTH` (macro, line 42)
  - `QGA_FILE_MAX` (macro, line 46)

## rtc.h
- Layer: utility
- Doc: ifndef RTC_H define RTC_H
- Language: h
- Symbols:
  - `RTC_H` (macro, line 2)

## sb16.h
- Layer: utility
- Doc: ifndef SB16_H define SB16_H  Sound Blaster 16 DMA audio driver contract.
- Language: h
- Symbols:
  - `SB16_H` (macro, line 2)
  - `SB16_PCM_BUF` (macro, line 31)
  - `SB16_PCM_RATE` (macro, line 33)
  - `SB16_SLOTS` (macro, line 34)
  - `SB16_RING_CAP` (macro, line 35)
  - `SB16_ARM_PERIOD_MS` (macro, line 36)
  - `SB16_STREAMS` (macro, line 42)
  - `SB16_STREAM_BUF` (macro, line 43)
  - `SB16_KB_SLOTS` (macro, line 47)
  - `SB16_KB_RING_SZ` (macro, line 48)

## sched.h
- Layer: utility
- Doc: ifndef SCHED_H define SCHED_H  include <stdint.h> include "spinlock.h"  ---- Process states ----
- Language: h
- Symbols:
  - `cpu` (struct, line 72)
  - `__attribute__` (function, line 130) `typedef struct __attribute__((packed))`
  - `SCHED_H` (macro, line 2)
  - `PROC_FREE` (macro, line 8)
  - `PROC_READY` (macro, line 9)
  - `PROC_RUNNING` (macro, line 10)
  - `PROC_BLOCKED` (macro, line 11)
  - `PROC_ZOMBIE` (macro, line 12)
  - `MAX_PROCS` (macro, line 15)
  - `PROC_KSTACK_SZ` (macro, line 16)
  - `MAX_CPUS` (macro, line 19)
  - `BOOT_CPU` (macro, line 20)
  - `CLONE_VM` (macro, line 48)
  - `CLONE_FILES` (macro, line 49)
  - `current_pid` (macro, line 103)
  - `DESKTOP_TICK_INTERVAL` (macro, line 106)

## shell.h
- Layer: utility
- Doc: ifndef SHELL_H define SHELL_H  shell.h -- shared shell constants and the line reader/parser reused by
- Language: h
- Symbols:
  - `SHELL_H` (macro, line 2)
  - `CMD_BUF_SZ` (macro, line 11)
  - `MAX_ARGS` (macro, line 13)

## smp.c
- Layer: utility
- Doc: include "kernel.h" include "bootdefs.h" include "smp.h" include "sched.h" include "ap_stub.h" include "arch/x86/msr.h"  
- Language: c
- Symbols:
  - `lapic_read` (function, line 67) `static unsigned lapic_read(unsigned off)`
  - `lapic_write` (function, line 71) `static void lapic_write(unsigned off, unsigned val)`
  - `map_lapic` (function, line 78) `static int map_lapic(void)`
  - `ap_delay` (function, line 90) `static void ap_delay(void)`
  - `ap_lapic_timer_init` (function, line 98) `static void ap_lapic_timer_init(void)`
  - `smp_ap_entry` (function, line 106) `void smp_ap_entry(void)`
  - `smp_init` (function, line 147) `void smp_init(void)`
  - `LAPIC_BASE` (macro, line 27)
  - `LAPIC_ID_OFF` (macro, line 29)
  - `LAPIC_SVR_OFF` (macro, line 30)
  - `LAPIC_ICR_HI` (macro, line 31)
  - `LAPIC_ICR_LO` (macro, line 32)
  - `LAPIC_TIMER_DIV` (macro, line 33)
  - `LAPIC_TIMER_INIT` (macro, line 34)
  - `LAPIC_TIMER_CUR` (macro, line 35)
  - `LAPIC_TIMER_VEC` (macro, line 36)
  - `LAPIC_SVR_ENABLE` (macro, line 37)
  - `LAPIC_ICR_BUSY` (macro, line 39)
  - `LAPIC_ICR_INIT` (macro, line 40)
  - `LAPIC_ICR_SIPI` (macro, line 41)
  - `LAPIC_ICR_ALL_EXC` (macro, line 42)
  - `LAPIC_ICR_LEVEL` (macro, line 43)
  - `LAPIC_ICR_TRIGGER` (macro, line 44)
  - `SIPI_VECTOR` (macro, line 45)
  - `PIT_HZ` (macro, line 49)
  - `LAPIC_TIMER_DIVIDE_16` (macro, line 52)
  - `LAPIC_TIMER_PERIODIC` (macro, line 53)
  - `LAPIC_PD_ADDR` (macro, line 61)
  - `LAPIC_PDPT_SLOT` (macro, line 62)
  - `LAPIC_PD_IDX` (macro, line 63)

## smp.h
- Layer: utility
- Doc: ifndef SMP_H define SMP_H  include "spinlock.h"  SMP bring-up: wake the application processors (APs) via the LAPIC INIT/
- Language: h
- Symbols:
  - `SMP_H` (macro, line 2)

## spinlock.h
- Layer: utility
- Doc: ifndef SPINLOCK_H define SPINLOCK_H  spinlock.h -- Lightweight spinlock for MiniOS kernel.
- Language: h
- Symbols:
  - `spin_init` (function, line 44) `static inline void spin_init(spinlock_t *lock)`
  - `spin_save_irq` (function, line 50) `static inline irqflags_t spin_save_irq(void)`
  - `spin_restore_irq` (function, line 57) `static inline void spin_restore_irq(irqflags_t flags)`
  - `spin_lock` (function, line 65) `static inline void spin_lock(spinlock_t *lock)`
  - `spin_unlock` (function, line 75) `static inline void spin_unlock(spinlock_t *lock)`
  - `spin_unlock_irqrestore` (function, line 95) `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)`
  - `SPINLOCK_H` (macro, line 2)
  - `SPINLOCK_INIT` (macro, line 42)

## test_bdd.sh
- Layer: testing
- Doc: BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console (COM1). Every scenario s
- Language: sh
- Symbols:
  - `cleanup_stale_qemu` (function, line 31)
  - `scenario` (function, line 42)
  - `scenario_smp` (function, line 60)
  - `expect` (function, line 79)
  - `expect_count` (function, line 100)
  - `refute` (function, line 122)
  - `http_server_start` (function, line 626)
  - `http_server_stop` (function, line 633)
  - `http_fixture_start` (function, line 638)
  - `http_fixture_stop` (function, line 645)

## test_http_server.py
- Layer: testing
- Language: py
- Symbols:
  - `Handler` (class, line 21) `class Handler(BaseHTTPRequestHandler)`
  - `do_GET` (method, line 24) `def do_GET(self)`
  - `log_message` (method, line 114) `def log_message(self, fmt)`
- Depends on: `kernel/time.c`

## tls.h
- Layer: utility
- Doc: ifndef TLS_H define TLS_H  ========== TLS 1.2 client (RFC 5246) ==========
- Language: h
- Symbols:
  - `tls_root` (struct, line 70)
  - `sha256_ctx` (struct, line 79)
  - `tls_pubkey` (struct, line 85)
  - `tls_session` (struct, line 95)
  - `TLS_H` (macro, line 2)
  - `TLS_CT_CCS` (macro, line 7)
  - `TLS_CT_ALERT` (macro, line 8)
  - `TLS_CT_HANDSHAKE` (macro, line 9)
  - `TLS_CT_APPDATA` (macro, line 10)
  - `TLS_REC_HEADER` (macro, line 11)
  - `TLS_REC_MAX` (macro, line 12)
  - `TLS_MSG_MAX` (macro, line 13)
  - `TLS_PLAIN_MAX` (macro, line 14)
  - `TLS_VERSION_TLS12` (macro, line 15)
  - `TLS_VERSION_TLS10` (macro, line 16)
  - `TLS_HS_CLIENT_HELLO` (macro, line 19)
  - `TLS_HS_SERVER_HELLO` (macro, line 20)
  - `TLS_HS_CERTIFICATE` (macro, line 21)
  - `TLS_HS_SERVER_KEY_EXCHANGE` (macro, line 22)
  - `TLS_HS_SERVER_HELLO_DONE` (macro, line 23)
  - `TLS_HS_CLIENT_KEY_EXCHANGE` (macro, line 24)
  - `TLS_HS_FINISHED` (macro, line 25)
  - `TLS_CSUITE_ECDHE_RSA_AES128GCM` (macro, line 28)
  - `TLS_CSUITE_ECDHE_ECDSA_AES128GCM` (macro, line 29)
  - `TLS_SIG_RSA_PKCS1_SHA256` (macro, line 32)
  - `TLS_SIG_ECDSA_P256_SHA256` (macro, line 33)
  - `TLS_SIG_ECDSA_P384_SHA384` (macro, line 34)
  - `TLS_GROUP_SECP256R1` (macro, line 37)
  - `TLS_EXT_SERVER_NAME` (macro, line 40)
  - `TLS_EXT_SUPPORTED_GROUPS` (macro, line 41)
  - `TLS_EXT_EC_POINT_FORMATS` (macro, line 42)
  - `TLS_EXT_SIGNATURE_ALGS` (macro, line 43)
  - `TLS_ALERT_LEVEL_WARNING` (macro, line 46)
  - `TLS_ALERT_LEVEL_FATAL` (macro, line 47)
  - `TLS_HS_TIMEOUT_MS` (macro, line 50)
  - `TLS_READ_TIMEOUT_MS` (macro, line 51)
  - `TLS_HOST_MAX` (macro, line 54)
  - `TLS_CHAIN_MAX` (macro, line 57)
  - `TLS_CERT_MAX` (macro, line 58)
  - `TLS_BN_4096_WORDS` (macro, line 62)
  - `TLS_BN_384_WORDS` (macro, line 63)
  - `TLS_ROOT_COUNT` (macro, line 68)

## tls_port.h
- Layer: utility
- Doc: ifndef TLS_PORT_H define TLS_PORT_H  Portability shim between the MiniOS kernel and the host-side test
- Language: h
- Symbols:
  - `tls_now_days` (function, line 39) `static inline long tls_now_days(void)`
  - `tls_random` (function, line 43) `static inline void tls_random(unsigned char *out, unsigned len)`
  - `TLS_PORT_H` (macro, line 2)
  - `TLS_FD_MAX` (macro, line 17)
  - `TLS_PRINTF` (macro, line 19)
  - `TLS_MALLOC` (macro, line 21)
  - `TLS_FREE` (macro, line 22)
  - `TLS_MEMCPY` (macro, line 23)
  - `TLS_MEMSET` (macro, line 24)
  - `TLS_MEMCMP` (macro, line 25)
  - `TLS_STRLEN` (macro, line 26)
  - `TLS_SEND` (macro, line 34)
  - `TLS_RECV` (macro, line 36)
  - `TLS_RECV_TIMEOUT` (macro, line 37)
  - `TLS_CLOSE` (macro, line 38)
  - `TLS_PRINTF` (macro, line 62)
  - `TLS_MALLOC` (macro, line 64)
  - `TLS_FREE` (macro, line 65)
  - `TLS_MEMCPY` (macro, line 66)
  - `TLS_MEMSET` (macro, line 67)
  - `TLS_MEMCMP` (macro, line 68)
  - `TLS_STRLEN` (macro, line 69)
  - `TLS_SEND` (macro, line 70)
  - `TLS_RECV` (macro, line 72)
  - `TLS_RECV_TIMEOUT` (macro, line 73)
  - `TLS_CLOSE` (macro, line 74)
  - `TLS_FD_MAX` (macro, line 75)

## tls_roots.h
- Layer: utility
- Doc: tls_roots.h - embedded CA roots (DER), generated by mkroots.sh.
- Language: h

## tls_test.c
- Layer: testing
- Doc: tls_test.c - host-side tests for the kernel TLS stack.
- Language: c
- Symbols:
  - `tls_test_send` (function, line 25) `int tls_test_send(int fd, const char *buf, int len)`
  - `tls_test_recv` (function, line 35) `int tls_test_recv(int fd, char *buf, int len)`
  - `tls_test_recv_timeout` (function, line 40) `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
  - `tls_test_close` (function, line 53) `void tls_test_close(int fd)`
  - `hexdigit` (function, line 66) `static int hexdigit(int c)`
  - `unhex` (function, line 73) `static void unhex(const char *hex, unsigned char *out, int n)`
  - `bytes_eq` (function, line 79) `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)`
  - `test_sha256` (function, line 87) `static void test_sha256(void)`
  - `test_sha384` (function, line 102) `static void test_sha384(void)`
  - `test_gcm` (function, line 113) `static void test_gcm(void)`
  - `test_p256` (function, line 153) `static void test_p256(void)`
  - `test_rsa_ecdsa_vectors` (function, line 199) `static void test_rsa_ecdsa_vectors(void)`
  - `tcp_connect` (function, line 248) `static int tcp_connect(int port)`
  - `http_over_tls` (function, line 265) `static int http_over_tls(int port, const char *host)`
  - `scenario_good` (function, line 289) `static int scenario_good(int port)`
  - `scenario_wild_good` (function, line 295) `static int scenario_wild_good(int port)`
  - `scenario_wild_root` (function, line 298) `static int scenario_wild_root(int port)`
  - `scenario_wild_deep` (function, line 308) `static int scenario_wild_deep(int port)`
  - `scenario_bad_host` (function, line 318) `static int scenario_bad_host(int port)`
  - `scenario_bad_ca` (function, line 328) `static int scenario_bad_ca(int port)`
  - `scenario_expired` (function, line 338) `static int scenario_expired(int port)`
  - `main` (function, line 348) `int main(int argc, char **argv)`
  - `CHECK` (macro, line 61)

## tls_test.py
- Layer: testing
- Language: py
- Symbols:
  - `run` (function, line 26) `def run(cmd)`
  - `check` (function, line 30) `def check(cmd)`
  - `gen_certs` (function, line 37) `def gen_certs()`
  - `der_bytes` (function, line 154) `def der_bytes(pem_path)`
  - `rsa_params` (function, line 162) `def rsa_params(key_path)`
  - `ec_pub` (function, line 172) `def ec_pub(key_path)`
  - `c_bytes` (function, line 183) `def c_bytes(data, name)`
  - `gen_header` (function, line 191) `def gen_header(p)`
  - `Server` (class, line 241) `class Server(Thread)`
  - `serve` (method, line 280) `def serve(cert, key)`
  - `serve_openssl` (method, line 288) `def serve_openssl(cert, key, chain)`
  - `expect` (method, line 306) `def expect(bin_path, args, want_zero, marker)`
  - `main` (method, line 319) `def main()`
  - `server_cert` (method, line 61) `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
  - `__init__` (method, line 242) `def __init__(self, cert, key, tls13_ok)`
  - `run` (method, line 248) `def run(self)`
- Depends on: `kernel/time.c`

## tls_test_roots.h
- Layer: testing
- Doc: tls_test_roots.h - generated by tls_test.py; never built into the kernel. The test root replaces the production table.
- Language: h

## vga_fb.h
- Layer: utility
- Doc: ifndef VGA_FB_H define VGA_FB_H  include <stdint.h> include "minios_abi.h"  Framebuffer geometry. The boot loader probes
- Language: h
- Symbols:
  - `VGA_FB_H` (macro, line 2)
  - `FB_ADDR` (macro, line 17)
  - `DOOM_W` (macro, line 29)
  - `DOOM_H` (macro, line 30)
  - `DOOM_BACKBUF_ADDR` (macro, line 31)
  - `NK_W` (macro, line 48)
  - `NK_H` (macro, line 49)
  - `NK_BACKBUF_ADDR` (macro, line 50)
  - `COL_BG` (macro, line 57)
  - `COL_TASKBAR` (macro, line 58)
  - `COL_TASKBAR_TXT` (macro, line 59)
  - `COL_TITLEBAR` (macro, line 60)
  - `COL_TITLE_TXT` (macro, line 61)
  - `COL_TERMINAL` (macro, line 62)
  - `COL_TERM_TXT` (macro, line 63)
  - `COL_TERM_CUR` (macro, line 64)
  - `COL_BORDER` (macro, line 65)
  - `COL_WHITE` (macro, line 66)
  - `COL_SHADOW` (macro, line 67)
  - `COL_HIGHLIGHT` (macro, line 68)
  - `COL_SCROLLBAR` (macro, line 69)
  - `COL_SCROLL_THUMB` (macro, line 70)
  - `FONT_W` (macro, line 71)
  - `FONT_H` (macro, line 73)
  - `TERM_MAX_COLS` (macro, line 78)
  - `TERM_MAX_ROWS` (macro, line 79)
  - `TASKBAR_H` (macro, line 82)
  - `TASKBAR_PAD` (macro, line 83)
  - `TASKBAR_CLOCK_CH` (macro, line 84)
  - `TASKBAR_VOL_CH` (macro, line 85)
  - `TASKBAR_VOL_STEP` (macro, line 86)
  - `TASKBAR_ICON_W` (macro, line 87)
  - `TASKBAR_BTN_W` (macro, line 88)
  - `TILING_LEFT` (macro, line 91)
  - `TILING_RIGHT` (macro, line 92)
  - `TILING_TOP` (macro, line 93)
  - `TILING_BOTTOM` (macro, line 94)
  - `TILING_TOP_LEFT` (macro, line 95)
  - `TILING_TOP_RIGHT` (macro, line 96)
  - `TILING_BOTTOM_LEFT` (macro, line 97)
  - `TILING_BOTTOM_RIGHT` (macro, line 98)
  - `SCROLLBAR_W` (macro, line 101)
  - `SCROLLBAR_PAD` (macro, line 102)
  - `WM_BTN_W` (macro, line 107)
  - `WM_BTN_H` (macro, line 108)
  - `WM_BTN_PAD` (macro, line 109)
  - `WM_BTN_MIN` (macro, line 110)
  - `WM_BTN_MAX` (macro, line 111)
  - `WM_BTN_CLOSE` (macro, line 112)
  - `SB_MAX_LINES` (macro, line 132)
  - `SB_LINE_MAX` (macro, line 133)

## vma.c
- Layer: utility
- Doc: include "vma.h"
- Language: c
- Symbols:
  - `vma_tree_init` (function, line 21) `void vma_tree_init(void)`
  - `vma_alloc_node` (function, line 32) `static vma_node_t *vma_alloc_node(void)`
  - `vma_rotate_left` (function, line 37) `static void vma_rotate_left(vma_node_t **root, vma_node_t *x)`
  - `vma_rotate_right` (function, line 49) `static void vma_rotate_right(vma_node_t **root, vma_node_t *x)`
  - `vma_insert_fixup` (function, line 61) `static void vma_insert_fixup(vma_node_t **root, vma_node_t *z)`
  - `vma_tree_insert` (function, line 100) `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len)`
  - `vma_tree_find` (function, line 123) `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base)`
  - `vma_transplant` (function, line 133) `static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v)`
  - `vma_tree_minimum` (function, line 140) `static vma_node_t *vma_tree_minimum(vma_node_t *x)`
  - `vma_delete_fixup` (function, line 145) `static void vma_delete_fixup(vma_node_t **root, vma_node_t *x)`
  - `vma_tree_delete` (function, line 200) `int vma_tree_delete(vma_node_t **root, unsigned long base)`

## vma.h
- Layer: utility
- Doc: ifndef VMA_H define VMA_H
- Language: h
- Symbols:
  - `vma_node` (struct, line 21)
  - `VMA_H` (macro, line 2)
  - `VMA_MAX` (macro, line 27)

## zip.h
- Layer: utility
- Doc: ifndef ZIP_H define ZIP_H  zip.h — MiniOS integration API for the miniz zip library.
- Language: h
- Symbols:
  - `ZIP_H` (macro, line 2)
