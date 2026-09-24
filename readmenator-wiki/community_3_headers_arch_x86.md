# headers/arch/x86

*Community 3 | 4 files | cohesion 0.33*

## Definition

This community groups 4 file(s) rooted at `headers/arch/x86` with dominant language c (cohesion 0.33). Central symbols: `CHECK`, `HAL_IO_H`, `HAL_IO_HOST_TEST`, `HAL_LAPIC_EOI_ADDR`, `HAL_MOUSE_BUTTON_MASK`, `HAL_MOUSE_CMD_DEFAULTS`, `HAL_MOUSE_CMD_DISABLE`, `HAL_MOUSE_CMD_ENABLE`. Core file: `headers/arch/x86/hal_io.h` (52 symbols). Documented purpose: Docstring: PS/2 mouse device driver (drivers/mouse.c)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/mouse.c` | c | infrastructure | 7 | yes |
| `headers/arch/x86/hal_io.h` | h | utility | 52 | yes |
| `headers/drivers/mouse.h` | h | infrastructure | 4 | yes |
| `tests/test_hal_io.c` | c | testing | 3 | yes |

## Key Symbols

- `mouse_wait_data` (function, `drivers/mouse.c:20`) `static void mouse_wait_data(void)`
- `mouse_write` (function, `drivers/mouse.c:24`) `static void mouse_write(unsigned char data)`
- `mouse_read` (function, `drivers/mouse.c:31`) `static unsigned char mouse_read(void)`
- `mouse_hw_init` (function, `drivers/mouse.c:36`) `void mouse_hw_init(void)`
- `wrong` (function, `drivers/mouse.c:58`) `* later packet is framed wrong (a left press reads back as bit 1, * motion warps`
- `mouse_disable` (function, `drivers/mouse.c:87`) `void mouse_disable(void)`
- `mouse_enable` (function, `drivers/mouse.c:88`) `void mouse_enable(void)`
- `HAL_IO_H` (macro, `headers/arch/x86/hal_io.h:13`) `#define HAL_IO_H`
- `HAL_PIC1_CMD` (macro, `headers/arch/x86/hal_io.h:16`) `#define HAL_PIC1_CMD`
- `HAL_PIC1_DATA` (macro, `headers/arch/x86/hal_io.h:18`) `#define HAL_PIC1_DATA`
- `HAL_PIC2_CMD` (macro, `headers/arch/x86/hal_io.h:20`) `#define HAL_PIC2_CMD`
- `HAL_PIC2_DATA` (macro, `headers/arch/x86/hal_io.h:22`) `#define HAL_PIC2_DATA`
- `HAL_PIC_EOI` (macro, `headers/arch/x86/hal_io.h:24`) `#define HAL_PIC_EOI`
- `HAL_PIT_CMD` (macro, `headers/arch/x86/hal_io.h:27`) `#define HAL_PIT_CMD`
- `HAL_PIT_CH0` (macro, `headers/arch/x86/hal_io.h:29`) `#define HAL_PIT_CH0`
- `HAL_PS2_STATUS` (macro, `headers/arch/x86/hal_io.h:32`) `#define HAL_PS2_STATUS`
- `HAL_PS2_DATA` (macro, `headers/arch/x86/hal_io.h:34`) `#define HAL_PS2_DATA`
- `HAL_PS2_MOUSE_OBF` (macro, `headers/arch/x86/hal_io.h:36`) `#define HAL_PS2_MOUSE_OBF`
- `HAL_PS2_IBF_EMPTY` (macro, `headers/arch/x86/hal_io.h:38`) `#define HAL_PS2_IBF_EMPTY`
- `HAL_PS2_OBF_FULL` (macro, `headers/arch/x86/hal_io.h:40`) `#define HAL_PS2_OBF_FULL`
- `HAL_PS2_CMD_WRITE_MOUSE` (macro, `headers/arch/x86/hal_io.h:42`) `#define HAL_PS2_CMD_WRITE_MOUSE`
- `HAL_PS2_CMD_ENABLE_AUX` (macro, `headers/arch/x86/hal_io.h:44`) `#define HAL_PS2_CMD_ENABLE_AUX`
- `HAL_PS2_CMD_READ_CONFIG` (macro, `headers/arch/x86/hal_io.h:46`) `#define HAL_PS2_CMD_READ_CONFIG`
- `HAL_PS2_CMD_WRITE_CONFIG` (macro, `headers/arch/x86/hal_io.h:48`) `#define HAL_PS2_CMD_WRITE_CONFIG`
- `HAL_PS2_CONFIG_IRQ12` (macro, `headers/arch/x86/hal_io.h:50`) `#define HAL_PS2_CONFIG_IRQ12`
- `HAL_MOUSE_CMD_RESET` (macro, `headers/arch/x86/hal_io.h:52`) `#define HAL_MOUSE_CMD_RESET`
- `HAL_MOUSE_CMD_SET_RATE` (macro, `headers/arch/x86/hal_io.h:54`) `#define HAL_MOUSE_CMD_SET_RATE`
- `HAL_MOUSE_CMD_GET_ID` (macro, `headers/arch/x86/hal_io.h:56`) `#define HAL_MOUSE_CMD_GET_ID`
- `HAL_MOUSE_CMD_DEFAULTS` (macro, `headers/arch/x86/hal_io.h:58`) `#define HAL_MOUSE_CMD_DEFAULTS`
- `HAL_MOUSE_CMD_ENABLE` (macro, `headers/arch/x86/hal_io.h:60`) `#define HAL_MOUSE_CMD_ENABLE`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 6

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/arch/x86/hal_io.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/arch/x86/hal_io.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers/arch/x86 changed?
- Should headers/arch/x86 be split, given cohesion 0.33?

## Sources

- `drivers/mouse.c`
- `headers/arch/x86/hal_io.h`
- `headers/drivers/mouse.h`
- `tests/test_hal_io.c`
