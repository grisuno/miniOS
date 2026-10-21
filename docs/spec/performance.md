# Performance work

Every optimization below is a measured change with the mechanism that
caused it, so the same trap is not re-discovered later. Numbers are the
observed ones on the reference host (QEMU, Linux).

### IDE PIO timing loop (`drivers/ide.c`)

*Symptom:* a 4 MB WAD load (`Doom1.wad`, 4,196,020 bytes) took about five
minutes under KVM and exited the hypervisor millions of times.

*Root cause:* `ide_delay` read the IDE control register 1000 times per call
as a crude timer, and `ide_select_drive` called it twice per sector. Every
one of those reads is a VM-exit under KVM, so a bulk load turned into
millions of exits and no wall-clock progress.

*Fix:* `ide_delay` is a short CPU pause loop with no port I/O at all
(200 `pause` instructions, `drivers/ide.c:13-21`). The historical "twice per
sector" figure describes the pre-fix path; the current `ide_select_drive`
performs one delay per call (`drivers/ide.c:53-57`).

*Measured result:* DOOM's load dropped to about 30 s under KVM, and TCG
stayed fast because the fix removes work instead of moving it.

### Block cache (`drivers/block.c`)

*Symptom:* `lsfs` was O(entries x blocks) in disk reads.

*Root cause:* MiniFS directory iteration re-reads the same directory block
for every entry (`minifs_dir_read` re-scans the whole directory), and IDE
PIO is the slowest part of the guest because every data word is an emulated
VM-exit under QEMU.

*Fix:* a direct-mapped, write-through cache of recently-read blocks: 16
ways of 4096 bytes (64 KB) in a heap-owned buffer, indexed by block number
(`drivers/block.c:34-66`). Writes are write-through and invalidate the
matching line before and after the device write, so a cached copy can never
go stale (`drivers/block.c:205-212`). A miss reads into a private heap
buffer with preemption allowed and installs the line atomically under an
irqsave lock, so two processes filling colliding lines each get their own
bytes instead of each other's (torn blocks read as wrong ELF bytes and wrong
dirents). A failed buffer allocation leaves the cache disabled and every read
goes straight to the device: slower but correct.

*Measured result:* directory iteration costs one read per directory block
plus one per touched inode.

### Windowed console output (`kernel/vga_fb.c`)

*Symptom:* 100,000 characters of console output took about 14 s.

*Root cause:* the windowed terminal redrew the whole active line (all
`term_cols` glyphs, through `term_render_active`) for every printable
character.

*Fix:* `term_draw_cell` draws only the changed cell of the active line
(`kernel/vga_fb.c:2842-2861`); a row or window repaint still happens when
the edit changes the number of display rows (wrap or newline).

*Measured result:* a single cell draw is about 100x cheaper than a full row
redraw, so `ls` and every other console output path are fast.

### SB16 DMA ring mapping (`drivers/sb16.c`, `arch/x86/boot/stage2.S`,
`headers/arch/x86/boot/bootdefs.h`)

*Symptom:* PCM written by the kernel could reach the speaker stale, so the
DMA played garbage.

*Root cause:* the 8237 DMA controller reads physical RAM directly and
bypasses the CPU caches, so a write-back mapping leaves freshly written PCM
sitting in cache instead of memory.

*Fix:* the DMA ring `[0x90000, 0x94000)` (8 slots of 2048 bytes) is
identity mapped and marked uncacheable (PCD) in the boot page tables:
`stage2.S:197-212` sets `PT_FLAGS_PCD` on the four PT0 entries
(`SB16_DMA_PT_ENTRY = 0x90000 >> 12`, `SB16_DMA_PT_PAGES = 4`,
`bootdefs.h:229-234`; the reservation itself is `BOOT_SB16_DMA_ADDR 0x90000`
and `BOOT_SB16_DMA_BYTES 0x4000`, `bootdefs.h:89-90`).

*Caveat that must survive:* the buffers are not a kernel-static array. The
8237 can only reach physical memory below 16 MB, and under KASLR the kernel
image's physical base can land above it, so the ring lives in the reserved
low region and the kernel stack starts above it and grows down
(`drivers/sb16.c:38-46`).

### SB16 DSP write wait (`drivers/sb16.c`)

*Symptom:* every DSP command byte paid a long spin before it was issued.

*Root cause:* the old write wait was a `SB16_PROBE_WAIT` (200,000
iteration) port-read spin on the DSP status register. The DSP takes the
byte once it catches up after a reset, so the spin bought nothing and, on
a machine with no SB16, burned the whole budget on every boot.

*Fix:* `sb16_wait_write` is a deadline-bounded poll through
`port_wait_mask` with a 100 ms budget: one port read per batch of 1024
pauses, an early bail when the bus floats at `0xFF`, and the byte still
issued after the timeout so a dead DSP can never hang the kernel
(`drivers/sb16.c:274-285`, `headers/kernel.h:61-86`). The reset probe
additionally pairs the `0xFF` float check with the `0xAA` signature byte,
so an absent device is detected in milliseconds instead of a 200,000-spin
(~1 s of KVM exits) budget (`drivers/sb16.c:305-320`).

### SB16 completion watchdog (`drivers/sb16.c`, `kernel/sched.c`)

*Symptom:* the piano buzzed or fell silent, and every later submit was
refused.

*Root cause:* QEMU raises the completion IRQ only once its audio engine
consumes a transfer. A host backend that never consumes leaves the ring
full forever; the ring holds 8 slots of 2048 bytes with one permanent
silence slot, so 7 slots are usable (`SB16_SLOTS 8`, `SB16_RING_CAP 7`,
`headers/sb16.h:34-35`), and once it is full every submit is refused.

*Fix:* completion is driven by the SB16 IRQ *and* a timer-ISR watchdog.
`sb16_poll` (`drivers/sb16.c:457-464`) is the watchdog, forwarded from the
timer tick adapter in `kernel/sched.c:25-29`. Both paths funnel through
`sb16_arm` (`drivers/sb16.c:355-378`), which rate-limits the re-arm to one
per buffer duration (`SB16_ARM_PERIOD_MS`, 93 ms for a 2048-byte buffer at
22050 Hz), so the two paths are idempotent, the ring always drains at the
declared rate, and a fast backend can never drive an interrupt storm.

*Counters:* the `sb16` builtin reports `irq_arms`, `poll_arms`, `submits`
and `drops` next to the ring and stream state (`kernel/shell.c:3941-3956`;
counter fields in `headers/sb16.h:55-63`).

### Syscall trace flood (`kernel/syscalls.c`)

*Symptom:* `trace on` turned an interactive program into a 100
ms-per-syscall crawl.

*Root cause:* clock and poll reads are called inside every pacing spin
loop, so tracing them one-to-one floods the console.

*Fix:* `trace_is_noisy` filters the noisy syscall numbers out of the
trace; everything else is still traced one-to-one so a short program's
full dialogue stays visible (`kernel/syscalls.c:1247-1254` and
`kernel/syscalls.c:3443-3446`). The filter set is four numbers: 205
(keyboard), 219 (mouse), 236 (`getc_raw`) and 254 (the time syscall).

*Stale constant, fixed here:* the time syscall is no longer 204. ABI v12
relocated it to 254 because 204 belongs to Linux `sched_getaffinity`
(`progs/minios_abi.h:311-313`, dispatched at `kernel/syscalls.c:3825`),
but `SYS_NOISY_TIME` still said 204 (`kernel/syscalls.c:1251`): the
filter silenced `sched_getaffinity` and the time syscall was traced
again, so `trace on` still crawled.

### Multi-sector IDE PIO (`drivers/ide.c`)

*Symptom:* bulk loads paid one command setup per sector.

*Root cause:* `ide_read_sectors` and `ide_write_sectors` issued one
command per sector, so the command-setup port traffic grew with the
transfer size.

*Fix:* one command with `SECCOUNT = count`, then one `rep insw` /
`rep outsw` of `IDE_SECTOR_SIZE / 2` words per sector
(`drivers/ide.c:152-212`). The data path is still a 16-bit IDE port, so the
remaining MiniFS load time is bounded by QEMU's 16-bit-only IDE port, not
by the command count.

### AP LAPIC timer storm (`smp.c`)

*Symptom:* an idle 2-CPU guest burned 176% host CPU, and pokemon's 60
frames took 29 s instead of 11.4 s. `docs/spec/smp-sched.md:40-41` records
the same effect as a 2.6x slowdown.

*Root cause:* the AP timer was programmed with a count derived from
`PIT_HZ` (745 ticks at divide-by-16), but the LAPIC counts bus clocks, not
the PIT rate. Under QEMU it fired every ~12 us (~84 kHz) instead of
100 Hz and wedged the machine under an interrupt storm.

*Fix:* the local AP timer stays masked and the halted AP wakes only on the
BSP's 100 Hz IPI broadcast, which also drives its preemption ISR
(`smp.c:146-155`, `smp.c:215`). The AP's LAPIC SVR must still be enabled
first, or the AP cannot receive IPIs at all and its `hlt` never wakes.

*Measured result:* AP idle CPU back to 0.1%, 60 frames back at 11.4 s, and
`thdemo: PASS` with AP dispatch confirmed (`progs/src/thdemo.c:112`,
asserted by `tools/test_bdd.sh:235`).

*Opt-in path:* a per-AP 100 Hz LAPIC timer exists behind the compile-time
`MINIOS_AP_TIMER` (default off). It programs divide-by-16, vector 32, and
a count calibrated against the PIT (`lapic_cal_10ms`, 625,000 ticks per
10 ms by default), so scheduling no longer depends on the BSP broadcast
alone (`smp.c:156-209`).

