# headers

*Community 3 | 64 files | cohesion 0.63*

## Definition

This community groups 64 file(s) rooted at `headers` with dominant language c (cohesion 0.63). Central symbols: `ALIGN_UP`, `ARCH_X86_MSR_H`, `BOOTLOG_MAX`, `C`, `CHECK`, `CMD_BUF_SZ`, `COL_BG`, `COL_BLACK`. Core file: `headers/kernel.h` (316 symbols). Documented purpose: scrollback.c - Console scrollback ring buffer..

## Files

### `headers` (22 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/editor.h` | h | infrastructure | 2 | yes |
| `headers/kernel.h` | h | utility | 316 | yes |

### `kernel` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/console.c` | c | utility | 31 | yes |
| `kernel/console_in.c` | c | utility | 32 | yes |

### `net` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 70 | yes |
| `net/rtl8139.c` | c | utility | 34 | yes |

### `tests` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_ktime.c` | c | testing | 3 | yes |
| `tests/test_notify.c` | c | testing | 9 | yes |

### `fs` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/kfile.c` | c | utility | 30 | yes |
| `fs/ramdisk.c` | c | infrastructure | 25 | yes |

### `.` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 41 | yes |
| `qga.c` | c | utility | 31 | yes |

### `drivers` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/pcspk.c` | c | infrastructure | 20 | yes |
| `drivers/rtc.c` | c | infrastructure | 27 | yes |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 8 | yes |

### `headers/arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/msr.h` | h | utility | 10 | yes |

### `headers/drivers` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 23 | yes |

### `headers/net` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net/rtl8139.h` | h | utility | 8 | yes |

### `kernel/mm` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/paging.c` | c | utility | 21 | yes |

### `progs/tls_u` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_main.c` | c | utility | 11 | yes |

*... and 44 more files in this community.*


## Key Symbols

- `PIT_CH2_DATA` (macro, `drivers/pcspk.c:13`) `#define PIT_CH2_DATA`
- `PIT_CH2_CMD` (macro, `drivers/pcspk.c:15`) `#define PIT_CH2_CMD`
- `SPEAKER_PORT` (macro, `drivers/pcspk.c:16`) `#define SPEAKER_PORT`
- `PIT_FREQ` (macro, `drivers/pcspk.c:17`) `#define PIT_FREQ`
- `PCSPK_MIN_FREQ` (macro, `drivers/pcspk.c:18`) `#define PCSPK_MIN_FREQ`
- `PCSPK_MAX_FREQ` (macro, `drivers/pcspk.c:20`) `#define PCSPK_MAX_FREQ`
- `SPEAKER_DATA_BIT` (macro, `drivers/pcspk.c:21`) `#define SPEAKER_DATA_BIT`
- `SPEAKER_GATE_BIT` (macro, `drivers/pcspk.c:23`) `#define SPEAKER_GATE_BIT`
- `SPEAKER_ENABLE_BITS` (macro, `drivers/pcspk.c:24`) `#define SPEAKER_ENABLE_BITS`
- `pcspk_ops_tone` (function, `drivers/pcspk.c:32`) `static void pcspk_ops_tone(device_t *dev, unsigned freq)`
- `pcspk_ops_off` (function, `drivers/pcspk.c:37`) `static void pcspk_ops_off(device_t *dev)`
- `pcspk_ops_set_volume` (function, `drivers/pcspk.c:42`) `static void pcspk_ops_set_volume(device_t *dev, unsigned vol)`
- `pcspk_ops_get_volume` (function, `drivers/pcspk.c:47`) `static unsigned pcspk_ops_get_volume(device_t *dev)`
- `pcspk_init` (function, `drivers/pcspk.c:71`) `void pcspk_init(void)`
- `outb` (function, `drivers/pcspk.c:74`) `outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);`
- `device_register` (function, `drivers/pcspk.c:75`) `device_register(&pcspk_device);`
- `pcspk_set_volume` (function, `drivers/pcspk.c:77`) `void pcspk_set_volume(unsigned volume)`
- `pcspk_get_volume` (function, `drivers/pcspk.c:81`) `unsigned pcspk_get_volume(void)`
- `pcspk_tone` (function, `drivers/pcspk.c:85`) `void pcspk_tone(unsigned freq)`
- `pcspk_off` (function, `drivers/pcspk.c:103`) `void pcspk_off(void)`
- `RTC_CMOS_ADDR` (macro, `drivers/rtc.c:8`) `#define RTC_CMOS_ADDR`
- `RTC_CMOS_DATA` (macro, `drivers/rtc.c:10`) `#define RTC_CMOS_DATA`
- `RTC_REG_SEC` (macro, `drivers/rtc.c:11`) `#define RTC_REG_SEC`
- `RTC_REG_MIN` (macro, `drivers/rtc.c:13`) `#define RTC_REG_MIN`
- `RTC_REG_HOUR` (macro, `drivers/rtc.c:14`) `#define RTC_REG_HOUR`
- `RTC_REG_DAY` (macro, `drivers/rtc.c:15`) `#define RTC_REG_DAY`
- `RTC_REG_MON` (macro, `drivers/rtc.c:16`) `#define RTC_REG_MON`
- `RTC_REG_YEAR` (macro, `drivers/rtc.c:17`) `#define RTC_REG_YEAR`
- `RTC_REG_STATUS_A` (macro, `drivers/rtc.c:18`) `#define RTC_REG_STATUS_A`
- `RTC_REG_STATUS_B` (macro, `drivers/rtc.c:19`) `#define RTC_REG_STATUS_B`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 122
- Cross-boundary resolved imports (EXTRACTED): 72

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 3 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 3 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/vma.h.
- [EXTRACTED] depends_on community 3 <-> 10 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [EXTRACTED] depends_on community 4 <-> 3 (strength 0.9): Extracted import edge crosses communities: kernel/abi.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 3 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/exec.c imports headers/arch/x86/boot/bootdefs.h.
- [EXTRACTED] depends_on community 3 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/shell.c imports headers/wm_layout.h.
- [EXTRACTED] depends_on community 3 <-> 6 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/ktime.h` via `subprocess` (2 hops)

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `drivers/pcspk.c`
- `drivers/rtc.c`
- `drivers/sb16.c`
- `fs/kfile.c`
- `fs/ramdisk.c`
- `fs/vfs.c`
- `fs/zip.c`
- `headers/arch/x86/msr.h`
- `headers/drivers/kbd.h`
- `headers/editor.h`
- `headers/kernel.h`
- `headers/kernel/console_in.h`
- `headers/kernel/vga_cursor.h`
- `headers/ktime.h`
- `headers/minifetch.h`
- `headers/minifs.h`
- `headers/net.h`
- `headers/net/rtl8139.h`
- `headers/pcspk.h`
- `headers/qga.h`
- *... and 44 more*
