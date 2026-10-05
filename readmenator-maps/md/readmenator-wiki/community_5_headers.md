# headers

*Community 5 | 27 files | cohesion 0.42*

## Definition

This community groups 27 file(s) rooted at `headers` with dominant language c (cohesion 0.42). Central symbols: `CHECK`, `DMA_CH1_ADDR`, `DMA_CH1_CNT`, `DMA_CH1_MASK`, `DMA_CH1_PAGE`, `DMA_CH1_SINGLE_READ`, `DMA_CH1_UNMASK`, `DMA_FF_CLR`. Core file: `kernel/shell.c` (97 symbols). Documented purpose: drivers/pcm2.c -- low-latency PCM audio over SB16 single-cycle DMA..

## Files

### `headers` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/httpd.h` | h | presentation | 10 | yes |
| `headers/minifetch.h` | h | utility | 2 | yes |
| `headers/net.h` | h | utility | 71 | yes |
| `headers/pcm2.h` | h | utility | 21 | yes |
| `headers/pcm_ring.h` | h | utility | 7 | yes |

### `drivers` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/pcm2.c` | c | infrastructure | 43 | yes |
| `drivers/pcspk.c` | c | infrastructure | 18 | yes |
| `drivers/rtc.c` | c | infrastructure | 25 | yes |
| `drivers/sb16.c` | c | infrastructure | 64 | yes |

### `tests` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_httpd.c` | c | testing | 2 | yes |
| `tests/test_notify.c` | c | testing | 3 | no |
| `tests/test_pcm.c` | c | testing | 9 | yes |
| `tests/test_rtc.c` | c | testing | 2 | yes |

### `kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/minifetch.c` | c | utility | 6 | yes |
| `kernel/shell.c` | c | utility | 97 | no |

### `net` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 69 | yes |
| `net/rtl8139.c` | c | utility | 28 | no |

### `.` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `qga.c` | c | utility | 27 | yes |

### `headers/drivers` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/virtio_net.h` | h | infrastructure | 9 | yes |

### `headers/net` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net/rtl8139.h` | h | utility | 8 | no |

*... and 7 more files in this community.*


## Key Symbols

- `PCM2_BASE_PORT` (macro, `drivers/pcm2.c:26`) `#define PCM2_BASE_PORT`
- `PCM2_DSP_RESET` (macro, `drivers/pcm2.c:27`) `#define PCM2_DSP_RESET`
- `PCM2_DSP_WRITE_DATA` (macro, `drivers/pcm2.c:28`) `#define PCM2_DSP_WRITE_DATA`
- `PCM2_DSP_STATUS` (macro, `drivers/pcm2.c:29`) `#define PCM2_DSP_STATUS`
- `PCM2_IRQ_ACK` (macro, `drivers/pcm2.c:30`) `#define PCM2_IRQ_ACK`
- `PCM2_CMD_SET_FREQ` (macro, `drivers/pcm2.c:32`) `#define PCM2_CMD_SET_FREQ`
- `PCM2_CMD_SPK_ON` (macro, `drivers/pcm2.c:33`) `#define PCM2_CMD_SPK_ON`
- `PCM2_CMD_PLAY8` (macro, `drivers/pcm2.c:34`) `#define PCM2_CMD_PLAY8`
- `PCM2_CMD_STOP_NOW` (macro, `drivers/pcm2.c:35`) `#define PCM2_CMD_STOP_NOW`
- `PCM2_DMA_MODE_PORT` (macro, `drivers/pcm2.c:42`) `#define PCM2_DMA_MODE_PORT`
- `PCM2_DMA_CH1_SINGLE` (macro, `drivers/pcm2.c:43`) `#define PCM2_DMA_CH1_SINGLE`
- `PCM2_DMA_CH1_ADDR` (macro, `drivers/pcm2.c:44`) `#define PCM2_DMA_CH1_ADDR`
- `PCM2_DMA_CH1_CNT` (macro, `drivers/pcm2.c:45`) `#define PCM2_DMA_CH1_CNT`
- `PCM2_DMA_CH1_PAGE` (macro, `drivers/pcm2.c:46`) `#define PCM2_DMA_CH1_PAGE`
- `PCM2_DMA_MASK` (macro, `drivers/pcm2.c:47`) `#define PCM2_DMA_MASK`
- `PCM2_DMA_FF_CLR` (macro, `drivers/pcm2.c:48`) `#define PCM2_DMA_FF_CLR`
- `PCM2_DMA_CH1_MASK` (macro, `drivers/pcm2.c:49`) `#define PCM2_DMA_CH1_MASK`
- `PCM2_DMA_CH1_UNMASK` (macro, `drivers/pcm2.c:50`) `#define PCM2_DMA_CH1_UNMASK`
- `PCM2_DMA_ADDR` (macro, `drivers/pcm2.c:52`) `#define PCM2_DMA_ADDR`
- `PCM2_DMA_COUNT` (macro, `drivers/pcm2.c:53`) `#define PCM2_DMA_COUNT`
- `PCM2_READY_MASK` (macro, `drivers/pcm2.c:54`) `#define PCM2_READY_MASK`
- `PCM2_PROBE_WAIT` (macro, `drivers/pcm2.c:55`) `#define PCM2_PROBE_WAIT`
- `PCM2_SILENCE` (macro, `drivers/pcm2.c:56`) `#define PCM2_SILENCE`
- `PCM2_BLOCK_MS` (macro, `drivers/pcm2.c:59`) `#define PCM2_BLOCK_MS`
- `PCM2_BLOCK_SLACK_MS` (macro, `drivers/pcm2.c:60`) `#define PCM2_BLOCK_SLACK_MS`
- `pcm2_dma` (function, `drivers/pcm2.c:79`) `static unsigned char *pcm2_dma(void)`
- `pcm2_wait_write` (function, `drivers/pcm2.c:83`) `static int pcm2_wait_write(void)`
- `pcm2_cmd` (function, `drivers/pcm2.c:90`) `static void pcm2_cmd(unsigned char c)`
- `pcm2_dma_program` (function, `drivers/pcm2.c:95`) `static void pcm2_dma_program(void)`
- `pcm2_dma_stop` (function, `drivers/pcm2.c:108`) `static void pcm2_dma_stop(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 34
- Cross-boundary resolved imports (EXTRACTED): 46

## Connections

- [EXTRACTED] depends_on community 5 <-> 10 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/sched.h.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/arch/x86/boot/bootdefs.h.
- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/pcspk.c imports headers/driver.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/virtio_net.c imports headers/drivers/pci.h.
- [EXTRACTED] depends_on community 16 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/net.h.

## Risks

- [layer strict] `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation)
- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/sb16.c:531` `sb16_init` `major`: `major` assigned at line 531 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_net.c:146` `vnet_desc` `d`: `d` assigned at line 146 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/shell.c:1672` `context` `buf`: `buf` may be read before initialization (declared line 1664).
- [dataflow DEAD_STORE] `net/net.c:301` `net_dns_resolve` `rc`: `rc` assigned at line 301 but never read afterwards.

## Open Questions

- Why do 6 file(s) lack file-level docs (e.g. `headers/net/rtl8139.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.42?

## Sources

- `drivers/pcm2.c`
- `drivers/pcspk.c`
- `drivers/rtc.c`
- `drivers/sb16.c`
- `drivers/virtio_net.c`
- `headers/drivers/virtio_net.h`
- `headers/httpd.h`
- `headers/minifetch.h`
- `headers/net.h`
- `headers/net/rtl8139.h`
- `headers/pcm2.h`
- `headers/pcm_ring.h`
- `headers/pcspk.h`
- `headers/qga.h`
- `headers/rtc.h`
- `headers/sb16.h`
- `headers/wm_notify.h`
- `headers/zip.h`
- `kernel/minifetch.c`
- `kernel/shell.c`
- *... and 7 more*
