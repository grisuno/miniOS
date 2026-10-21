# miniOS API Reference

> Generated offline by readmenator: 511 modules, 10345 documented entities, documentation coverage 29.3% (2769/9449 public items). Deterministic, zero tokens: signatures from source, docs parsed from Google, NumPy, reST, Javadoc/JSDoc/Doxygen, C# XML, and Rustdoc comments.

Navigate: [Interactive architecture and flows](flows.html) | [Architecture and flows (Mermaid)](architecture.md) | [Class hierarchy](classes.md) | [General index](genindex.md) | [Coverage and warnings](COVERAGE.md) | [`api/index.json`](api/index.json) | [HTML browser](index.html)

Languages: S (7), c (239), h (194), py (48), s (13), sh (10)

## Modules

### `.`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`bootloader.c`](modules/bootloader.c.md) |  | 0 | 2 | 33.3% |
| [`kernel.c`](modules/kernel.c.md) | kernel.c -- Mediator: boot orchestration and the syscall trampoline. | 0 | 12 | 38.5% |
| [`qga.c`](modules/qga.c.md) | MiniOS QEMU guest agent (QGA). | 1 | 3 | 40.0% |
| [`smp.c`](modules/smp.c.md) | SMP application-processor bring-up. | 0 | 36 | 40.5% |
| [`vma.c`](modules/vma.c.md) |  | 0 | 10 | 9.1% |

### `arch/x86`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`arch/x86/ap_entry.S`](modules/arch.x86.ap_entry.S.md) | ap_entry.S - SMP application-processor bootstrap stub. | 0 | 9 | 20.0% |
| [`arch/x86/ctx_sw.S`](modules/arch.x86.ctx_sw.S.md) |  | 0 | 9 | 20.0% |
| [`arch/x86/isr_stubs.S`](modules/arch.x86.isr_stubs.S.md) |  | 0 | 24 | 0.0% |
| [`arch/x86/syscall_entry.S`](modules/arch.x86.syscall_entry.S.md) |  | 0 | 4 | 0.0% |
| [`arch/x86/tlb_nmi.S`](modules/arch.x86.tlb_nmi.S.md) |  | 0 | 1 | 50.0% |

### `arch/x86/boot`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`arch/x86/boot/stage1.S`](modules/arch.x86.boot.stage1.S.md) | stage1.S - MiniOS boot sector. | 0 | 11 | 8.3% |
| [`arch/x86/boot/stage2.S`](modules/arch.x86.boot.stage2.S.md) | stage2.S - MiniOS second-stage loader. | 0 | 40 | 12.2% |

### `boot`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`boot/uefi_stub.c`](modules/boot.uefi_stub.c.md) |  | 25 | 16 | 7.1% |

### `drivers`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`drivers/block.c`](modules/drivers.block.c.md) | Block device layer for MiniFS. | 0 | 14 | 60.0% |
| [`drivers/driver.c`](modules/drivers.driver.c.md) | driver.c -- Device registry for the Strategy-pattern driver layer. | 0 | 5 | 16.7% |
| [`drivers/ide.c`](modules/drivers.ide.c.md) | IDE/ATA PIO driver for MiniOS. | 0 | 8 | 77.8% |
| [`drivers/kbd.c`](modules/drivers.kbd.c.md) | ================================================================ | 0 | 31 | 18.8% |
| [`drivers/mouse.c`](modules/drivers.mouse.c.md) | Docstring: PS/2 mouse device driver (drivers/mouse.c). | 0 | 4 | 80.0% |
| [`drivers/nvme.c`](modules/drivers.nvme.c.md) |  | 0 | 35 | 0.0% |
| [`drivers/pcm2.c`](modules/drivers.pcm2.c.md) | drivers/pcm2.c -- low-latency PCM audio over SB16 single-cycle DMA. | 0 | 33 | 8.8% |
| [`drivers/pcspk.c`](modules/drivers.pcspk.c.md) | PC speaker driver with a software master volume. | 0 | 14 | 13.3% |
| [`drivers/rtc.c`](modules/drivers.rtc.c.md) | CMOS RTC time-of-day reader. | 0 | 22 | 21.7% |
| [`drivers/sb16.c`](modules/drivers.sb16.c.md) | Sound Blaster 16 DMA audio driver. | 0 | 50 | 9.8% |
| [`drivers/usbblk.c`](modules/drivers.usbblk.c.md) | usbblk.c -- USB mass storage, Bulk-Only Transport over SCSI. | 1 | 31 | 57.6% |
| [`drivers/usbhid.c`](modules/drivers.usbhid.c.md) | usbhid.c -- USB HID boot-protocol keyboard and mouse. | 1 | 14 | 100.0% |
| [`drivers/virtio_blk.c`](modules/drivers.virtio_blk.c.md) | Docstring: drivers/virtio_blk.c -- Polled legacy virtio-blk driver. | 1 | 23 | 28.0% |
| [`drivers/virtio_net.c`](modules/drivers.virtio_net.c.md) | Docstring: drivers/virtio_net.c -- Polled legacy virtio-net driver. | 0 | 34 | 20.0% |
| [`drivers/xhci.c`](modules/drivers.xhci.c.md) | xhci.c -- xHCI host controller driver, polled event ring. | 4 | 147 | 32.2% |

### `fs`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`fs/ext4.c`](modules/fs.ext4.c.md) | ================================================================ | 2 | 22 | 20.0% |
| [`fs/fat32.c`](modules/fs.fat32.c.md) | ================================================================ | 1 | 16 | 33.3% |
| [`fs/fsimg.c`](modules/fs.fsimg.c.md) | ================================================================ | 0 | 4 | 100.0% |
| [`fs/kfile.c`](modules/fs.kfile.c.md) | ================================================================ | 0 | 26 | 33.3% |
| [`fs/minifs.c`](modules/fs.minifs.c.md) | MiniFS: minimal Unix-like filesystem for MiniOS. | 0 | 46 | 23.4% |
| [`fs/pcache.c`](modules/fs.pcache.c.md) | Docstring: fs/pcache.c -- page cache store for MiniFS (T5 slice 1). | 1 | 14 | 87.5% |
| [`fs/ramdisk.c`](modules/fs.ramdisk.c.md) | ================================================================ | 1 | 23 | 12.0% |
| [`fs/vfs.c`](modules/fs.vfs.c.md) | ================================================================ | 4 | 18 | 8.7% |
| [`fs/zip.c`](modules/fs.zip.c.md) | zip.c — the unzip/zip shell builtins over the miniz zip library. | 0 | 6 | 42.9% |

### `headers`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/abi.h`](modules/headers.abi.h.md) | Docstring: abi.h -- Boot-time ABI manifest gate contract. | 0 | 9 | 20.0% |
| [`headers/ap_stub.h`](modules/headers.ap_stub.h.md) | generated from ap_stub.bin - do not edit | 0 | 0 | 100.0% |
| [`headers/arena.h`](modules/headers.arena.h.md) | Docstring: bump arena for MiniOS, kernel and ring-3 alike. | 1 | 13 | 93.3% |
| [`headers/audio.h`](modules/headers.audio.h.md) | Unified audio API for MiniOS. | 0 | 17 | 38.9% |
| [`headers/batch.h`](modules/headers.batch.h.md) | Docstring: batch.h -- Batched synchronous syscall submission. | 1 | 10 | 8.3% |
| [`headers/block.h`](modules/headers.block.h.md) | Block device abstraction for MiniFS. | 0 | 13 | 64.3% |
| [`headers/desktop_icons.h`](modules/headers.desktop_icons.h.md) | desktop_icons.h -- embedded icon pixel data for desktop shortcuts. | 0 | 1 | 50.0% |
| [`headers/desktop_shortcuts.h`](modules/headers.desktop_shortcuts.h.md) | desktop_shortcuts.h -- configurable desktop icon shortcuts. | 1 | 20 | 72.7% |
| [`headers/driver.h`](modules/headers.driver.h.md) | driver.h -- Strategy pattern for hardware drivers (thesis correction 2). | 4 | 11 | 12.5% |
| [`headers/editor.h`](modules/headers.editor.h.md) | editor.h -- the built-in line editor contract. | 0 | 1 | 50.0% |
| [`headers/ext4.h`](modules/headers.ext4.h.md) | ext4.h -- Read-only ext4 loopback/device driver. | 1 | 12 | 28.6% |
| [`headers/fat32.h`](modules/headers.fat32.h.md) | fat32.h -- Read-only FAT32 loopback driver over ramdisk/MiniFS images. | 1 | 13 | 33.3% |
| [`headers/fsimg.h`](modules/headers.fsimg.h.md) | fsimg.h -- One image backend for read-only filesystem drivers. | 1 | 4 | 83.3% |
| [`headers/futex.h`](modules/headers.futex.h.md) | Docstring: futex.h -- Fast userspace mutex sleep/wake contract. | 1 | 26 | 21.4% |
| [`headers/httpd.h`](modules/headers.httpd.h.md) | Docstring: httpd.h -- Minimal static HTTP/1.0 server contract. | 0 | 9 | 30.0% |
| [`headers/ide.h`](modules/headers.ide.h.md) | IDE/ATA PIO driver for MiniOS. | 0 | 34 | 77.1% |
| [`headers/kernel.h`](modules/headers.kernel.h.md) | The user-window memory layout (load base, stack, brk cap, graphics | 19 | 366 | 20.5% |
| [`headers/ktime.h`](modules/headers.ktime.h.md) | ktime.h -- pure time-conversion helpers shared by the kernel clock | 0 | 2 | 66.7% |
| [`headers/ldso.h`](modules/headers.ldso.h.md) | Docstring: headers/ldso.h -- minimal dynamic-linking (T8 ld.so) contract. | 3 | 41 | 24.4% |
| [`headers/leakcheck.h`](modules/headers.leakcheck.h.md) | Docstring: allocation tracker for MiniOS, STB leakcheck lineage. | 2 | 21 | 54.2% |
| [`headers/lz4_kernel.h`](modules/headers.lz4_kernel.h.md) |  | 0 | 3 | 0.0% |
| [`headers/minifetch.h`](modules/headers.minifetch.h.md) | Docstring: minifetch.h -- neofetch-style system screen contract. | 0 | 1 | 50.0% |
| [`headers/minifs.h`](modules/headers.minifs.h.md) | MiniFS: a minimal Unix-like filesystem for MiniOS. | 6 | 70 | 3.9% |
| [`headers/net.h`](modules/headers.net.h.md) |  | 0 | 100 | 21.8% |
| [`headers/panic.h`](modules/headers.panic.h.md) | Docstring: panic.h -- Kernel panic backtrace contract (header-only). | 0 | 4 | 80.0% |
| [`headers/pcache.h`](modules/headers.pcache.h.md) | Docstring: pcache.h -- page cache for MiniFS, slice 1 (store only). | 0 | 16 | 94.1% |
| [`headers/pcm2.h`](modules/headers.pcm2.h.md) | pcm2.h -- low-latency PCM audio path over SB16 single-cycle DMA. | 1 | 19 | 4.8% |
| [`headers/pcm_ring.h`](modules/headers.pcm_ring.h.md) | pcm_ring.h -- single-producer/single-consumer byte ring for PCM audio. | 1 | 5 | 14.3% |
| [`headers/pcspk.h`](modules/headers.pcspk.h.md) |  | 0 | 8 | 11.1% |
| [`headers/percpu_rq.h`](modules/headers.percpu_rq.h.md) | Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing. | 1 | 12 | 7.1% |
| [`headers/pipe.h`](modules/headers.pipe.h.md) | Docstring: pipe.h -- Kernel pipe ring contract (header-only). | 2 | 14 | 52.9% |
| [`headers/proc_sec.h`](modules/headers.proc_sec.h.md) | Docstring: proc_sec.h -- per-process security state behind the Linux | 0 | 11 | 50.0% |
| [`headers/qga.h`](modules/headers.qga.h.md) |  | 0 | 28 | 72.4% |
| [`headers/randmix.h`](modules/headers.randmix.h.md) | randmix.h -- entropy mixer for getrandom (318). | 0 | 1 | 50.0% |
| [`headers/rcu.h`](modules/headers.rcu.h.md) | Docstring: rcu.h -- Read-copy-update, lite epoch edition. | 0 | 16 | 5.9% |
| [`headers/rtc.h`](modules/headers.rtc.h.md) |  | 0 | 5 | 66.7% |
| [`headers/sanitize.h`](modules/headers.sanitize.h.md) | Docstring: sanitize.h -- Single choke point for syscall argument checks. | 0 | 4 | 20.0% |
| [`headers/sb16.h`](modules/headers.sb16.h.md) | Sound Blaster 16 DMA audio driver contract. | 2 | 25 | 35.7% |
| [`headers/sched.h`](modules/headers.sched.h.md) |  | 6 | 133 | 29.3% |
| [`headers/seccomp_bpf.h`](modules/headers.seccomp_bpf.h.md) | Docstring: seccomp_bpf.h -- classic BPF checker and interpreter for | 2 | 55 | 13.8% |
| [`headers/select_map.h`](modules/headers.select_map.h.md) | Docstring: select_map.h -- fd_set <-> pollfd translation for select(2). | 1 | 14 | 37.5% |
| [`headers/shell.h`](modules/headers.shell.h.md) | shell.h -- shared shell constants and the line reader/parser reused by | 0 | 7 | 75.0% |
| [`headers/sign.h`](modules/headers.sign.h.md) | Docstring: sign.h -- MiniOS binary signing contract. | 1 | 12 | 21.4% |
| [`headers/smp.h`](modules/headers.smp.h.md) | SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI | 0 | 4 | 60.0% |
| [`headers/spawn.h`](modules/headers.spawn.h.md) |  | 1 | 7 | 88.9% |
| [`headers/spinlock.h`](modules/headers.spinlock.h.md) | spinlock.h -- Lightweight spinlock for MiniOS kernel. | 2 | 16 | 68.4% |
| [`headers/sync.h`](modules/headers.sync.h.md) | sync.h -- Blocking synchronization primitives (roadmap Phase 3.1). | 5 | 32 | 18.4% |
| [`headers/syscall_asm.h`](modules/headers.syscall_asm.h.md) | syscall_asm.h -- numeric contract for arch/x86/syscall_entry.S. | 0 | 12 | 92.3% |
| [`headers/syscalls_proc.h`](modules/headers.syscalls_proc.h.md) | syscalls_proc.h -- process-management syscall handlers shared with the | 0 | 19 | 20.0% |
| [`headers/tick.h`](modules/headers.tick.h.md) | Docstring: Tick listener bus contract. | 1 | 14 | 100.0% |
| [`headers/tlb.h`](modules/headers.tlb.h.md) | tlb.h - cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown"). | 0 | 5 | 66.7% |
| [`headers/tls.h`](modules/headers.tls.h.md) | ========== TLS 1.2 client (RFC 5246) ========== | 4 | 67 | 40.3% |
| [`headers/tls_port.h`](modules/headers.tls_port.h.md) | Portability shim between the MiniOS kernel and the host-side test | 0 | 48 | 2.0% |
| [`headers/tls_roots.h`](modules/headers.tls_roots.h.md) | tls_roots.h - embedded CA roots (DER), generated by mkroots.sh. | 0 | 0 | 100.0% |
| [`headers/vga_fb.h`](modules/headers.vga_fb.h.md) |  | 1 | 134 | 25.7% |
| [`headers/vga_fx.h`](modules/headers.vga_fx.h.md) | Docstring: DOOM-melt desktop effect contract for MiniOS. | 1 | 7 | 100.0% |
| [`headers/vma.h`](modules/headers.vma.h.md) |  | 4 | 13 | 22.2% |
| [`headers/wm_events.h`](modules/headers.wm_events.h.md) | Docstring: Window event contract for the MiniOS desktop. | 4 | 34 | 41.0% |
| [`headers/wm_focus.h`](modules/headers.wm_focus.h.md) | Docstring: Focus manager contract for the MiniOS desktop. | 1 | 3 | 100.0% |
| [`headers/wm_geom.h`](modules/headers.wm_geom.h.md) | Docstring: Window geometry contract for the MiniOS desktop. | 2 | 8 | 100.0% |
| [`headers/wm_gfxview.h`](modules/headers.wm_gfxview.h.md) | Docstring: Graphics-window view contract for the MiniOS desktop. | 3 | 11 | 93.3% |
| [`headers/wm_layout.h`](modules/headers.wm_layout.h.md) | Docstring: Unified layout contract for the MiniOS desktop. | 3 | 12 | 100.0% |
| [`headers/wm_notify.h`](modules/headers.wm_notify.h.md) | Docstring: Focus event bus for the MiniOS desktop. | 2 | 6 | 88.9% |
| [`headers/wm_render.h`](modules/headers.wm_render.h.md) | Docstring: Render pipeline contract for the MiniOS desktop. | 2 | 2 | 100.0% |
| [`headers/wm_tiling.h`](modules/headers.wm_tiling.h.md) | Docstring: Tiling layout contract for the MiniOS desktop. | 1 | 1 | 100.0% |
| [`headers/wm_window.h`](modules/headers.wm_window.h.md) | Docstring: Unified window contract for the MiniOS desktop. | 1 | 8 | 100.0% |
| [`headers/zip.h`](modules/headers.zip.h.md) | zip.h — MiniOS integration API for the miniz zip library. | 0 | 2 | 33.3% |

### `headers/arch/x86`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/arch/x86/cpu_setup.h`](modules/headers.arch.x86.cpu_setup.h.md) | cpu_setup.h - per-CPU control-register setup shared by the BSP (kmain) | 0 | 1 | 100.0% |
| [`headers/arch/x86/hal_io.h`](modules/headers.arch.x86.hal_io.h.md) | Docstring: x86 port I/O hardware abstraction contract. | 0 | 63 | 100.0% |
| [`headers/arch/x86/msr.h`](modules/headers.arch.x86.msr.h.md) | Model-Specific Register access for x86-64. | 0 | 8 | 11.1% |

### `headers/arch/x86/boot`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/arch/x86/boot/bootdefs.h`](modules/headers.arch.x86.boot.bootdefs.h.md) | bootdefs.h - centralized configuration for the MiniOS two-stage boot path. | 0 | 156 | 15.3% |

### `headers/drivers`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/drivers/kbd.h`](modules/headers.drivers.kbd.h.md) |  | 0 | 23 | 25.0% |
| [`headers/drivers/modifiers.h`](modules/headers.drivers.modifiers.h.md) |  | 2 | 8 | 45.5% |
| [`headers/drivers/mouse.h`](modules/headers.drivers.mouse.h.md) | Docstring: mouse.h -- boundary of the PS/2 mouse device driver | 0 | 3 | 100.0% |
| [`headers/drivers/nvme.h`](modules/headers.drivers.nvme.h.md) |  | 0 | 6 | 0.0% |
| [`headers/drivers/pci.h`](modules/headers.drivers.pci.h.md) | Docstring: drivers/pci.h -- PCI configuration-space access. | 1 | 52 | 48.1% |
| [`headers/drivers/usbblk.h`](modules/headers.drivers.usbblk.h.md) | Docstring: drivers/usbblk.h -- boundary of the USB mass-storage driver. | 1 | 11 | 76.9% |
| [`headers/drivers/usbhid.h`](modules/headers.drivers.usbhid.h.md) | Docstring: drivers/usbhid.h -- boundary of the USB HID boot-protocol driver. | 1 | 31 | 60.6% |
| [`headers/drivers/virtio_blk.h`](modules/headers.drivers.virtio_blk.h.md) | Docstring: drivers/virtio_blk.h -- virtio-blk boundary. | 0 | 6 | 28.6% |
| [`headers/drivers/virtio_net.h`](modules/headers.drivers.virtio_net.h.md) | Docstring: drivers/virtio_net.h -- virtio-net boundary. | 0 | 8 | 88.9% |
| [`headers/drivers/xhci.h`](modules/headers.drivers.xhci.h.md) | Docstring: drivers/xhci.h -- boundary of the xHCI host controller driver. | 4 | 46 | 72.5% |

### `headers/kernel`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/kernel/console_in.h`](modules/headers.kernel.console_in.h.md) | Docstring: console_in.h -- boundary of the console input device | 0 | 11 | 58.3% |
| [`headers/kernel/vga_cursor.h`](modules/headers.kernel.vga_cursor.h.md) | Docstring: vga_cursor.h -- boundary of the pointer sprite layer | 0 | 7 | 100.0% |

### `headers/net`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`headers/net/rtl8139.h`](modules/headers.net.rtl8139.h.md) |  | 0 | 7 | 87.5% |

### `kernel`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`kernel/abi.c`](modules/kernel.abi.c.md) | Docstring: kernel/abi.c -- Boot-time ABI manifest gate. | 0 | 2 | 100.0% |
| [`kernel/batch.c`](modules/kernel.batch.c.md) | Docstring: kernel/batch.c -- Ordered batch executor. | 0 | 1 | 100.0% |
| [`kernel/clip.c`](modules/kernel.clip.c.md) | Docstring: kernel/clip.c -- Shared text clipboard. | 0 | 4 | 80.0% |
| [`kernel/console.c`](modules/kernel.console.c.md) | console.c -- Execution-context output: text console, capture, libc names. | 0 | 24 | 28.0% |
| [`kernel/console_in.c`](modules/kernel.console_in.c.md) | Docstring: Console input device (kernel/console_in.c). | 0 | 18 | 68.4% |
| [`kernel/cvm_host.c`](modules/kernel.cvm_host.c.md) |  | 1 | 1 | 33.3% |
| [`kernel/ed25519.c`](modules/kernel.ed25519.c.md) |  | 3 | 4 | 62.5% |
| [`kernel/editor.c`](modules/kernel.editor.c.md) | ================================================================ | 2 | 4 | 14.3% |
| [`kernel/exec.c`](modules/kernel.exec.c.md) | exec.c - Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit. | 0 | 9 | 40.0% |
| [`kernel/futex.c`](modules/kernel.futex.c.md) | Docstring: kernel/futex.c -- Kernel side of the futex contract. | 1 | 5 | 85.7% |
| [`kernel/klog.c`](modules/kernel.klog.c.md) | klog.c - Structured kernel logging with levels and subsystems. | 0 | 6 | 14.3% |
| [`kernel/ldso_parse.c`](modules/kernel.ldso_parse.c.md) | Docstring: kernel/ldso_parse.c -- pure dynamic-table parsing (T8 ld.so). | 0 | 14 | 73.3% |
| [`kernel/loader.c`](modules/kernel.loader.c.md) | ================================================================ | 6 | 43 | 14.0% |
| [`kernel/lz4_kernel.c`](modules/kernel.lz4_kernel.c.md) |  | 0 | 6 | 0.0% |
| [`kernel/minifetch.c`](modules/kernel.minifetch.c.md) | Docstring: kernel/minifetch.c -- neofetch-style system screen. | 1 | 2 | 50.0% |
| [`kernel/mm.c`](modules/kernel.mm.c.md) | ================================================================ | 0 | 9 | 70.0% |
| [`kernel/panic.c`](modules/kernel.panic.c.md) | Docstring: kernel/panic.c -- Kernel panic screen. | 0 | 1 | 100.0% |
| [`kernel/percpu_rq.c`](modules/kernel.percpu_rq.c.md) | Docstring: kernel/percpu_rq.c -- Per-CPU runqueue hints and stealing. | 0 | 8 | 100.0% |
| [`kernel/printf.c`](modules/kernel.printf.c.md) | ================================================================ | 1 | 3 | 20.0% |
| [`kernel/proc_sec.c`](modules/kernel.proc_sec.c.md) | Docstring: proc_sec.c -- per-process security state: the Linux seccomp | 2 | 36 | 17.9% |
| [`kernel/rcu.c`](modules/kernel.rcu.c.md) | Docstring: kernel/rcu.c -- Epoch grace periods over scheduler ticks. | 2 | 9 | 75.0% |
| [`kernel/redirect.c`](modules/kernel.redirect.c.md) | ================================================================ | 0 | 3 | 25.0% |
| [`kernel/sched.c`](modules/kernel.sched.c.md) |  | 4 | 85 | 38.9% |
| [`kernel/scrollback.c`](modules/kernel.scrollback.c.md) | scrollback.c - Console scrollback ring buffer. | 0 | 8 | 22.2% |
| [`kernel/seccomp_bpf.c`](modules/kernel.seccomp_bpf.c.md) | Docstring: seccomp_bpf.c -- classic BPF checker and interpreter for Linux | 0 | 10 | 36.4% |
| [`kernel/serial.c`](modules/kernel.serial.c.md) | serial.c -- COM1 16550 UART driver. | 0 | 7 | 37.5% |
| [`kernel/shell.c`](modules/kernel.shell.c.md) |  | 3 | 36 | 25.0% |
| [`kernel/spawn.c`](modules/kernel.spawn.c.md) |  | 0 | 7 | 87.5% |
| [`kernel/string.c`](modules/kernel.string.c.md) | string.c -- Kernel string and memory functions. | 0 | 13 | 14.3% |
| [`kernel/symtab.c`](modules/kernel.symtab.c.md) | ================================================================ | 0 | 7 | 12.5% |
| [`kernel/sync.c`](modules/kernel.sync.c.md) | sync.c -- Blocking synchronization primitives (roadmap Phase 3.1). | 0 | 24 | 4.0% |
| [`kernel/syscalls.c`](modules/kernel.syscalls.c.md) | syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN. | 5 | 119 | 18.4% |
| [`kernel/syscalls_proc.c`](modules/kernel.syscalls_proc.c.md) | syscalls_proc.c - Process-management syscall handlers. | 0 | 24 | 28.0% |
| [`kernel/tick.c`](modules/kernel.tick.c.md) | Docstring: Tick listener bus implementation. | 1 | 10 | 100.0% |
| [`kernel/time.c`](modules/kernel.time.c.md) | ================================================================ | 0 | 2 | 100.0% |
| [`kernel/vga_cursor.c`](modules/kernel.vga_cursor.c.md) | Docstring: Hardware pointer sprite layer (kernel/vga_cursor.c). | 0 | 8 | 88.9% |
| [`kernel/vga_fb.c`](modules/kernel.vga_fb.c.md) |  | 1 | 108 | 51.8% |
| [`kernel/vga_fx.c`](modules/kernel.vga_fx.c.md) | DOOM-melt desktop effects (see headers/vga_fx.h for the contract). | 0 | 8 | 33.3% |

### `kernel/mm`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`kernel/mm/cow.c`](modules/kernel.mm.cow.c.md) | Docstring: kernel/mm/cow.c -- Copy-on-write fork support. | 1 | 17 | 36.8% |
| [`kernel/mm/paging.c`](modules/kernel.mm.paging.c.md) | paging.c - Page table management for the user window and per-process KPTI. | 0 | 25 | 57.7% |
| [`kernel/mm/swap.c`](modules/kernel.mm.swap.c.md) | swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap). | 0 | 9 | 20.0% |
| [`kernel/mm/tlb.c`](modules/kernel.mm.tlb.c.md) | tlb.c - cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown"). | 0 | 4 | 60.0% |

### `mcp`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`mcp`](modules/mcp.__init__.py.md) |  | 0 | 0 | 0.0% |
| [`mcp.mcp_dbg_driver`](modules/mcp.mcp_dbg_driver.py.md) | Debug driver: boot MiniOS through the MCP bridge and run freedom. | 1 | 5 | 14.3% |
| [`mcp.mcp_dogfood`](modules/mcp.mcp_dogfood.py.md) | Dogfood: drive minios_mcp.py over stdio JSON-RPC and install the freedom addon from a git repo, then browse with the installed binary. | 1 | 5 | 14.3% |
| [`mcp.minios_addons`](modules/mcp.minios_addons.py.md) | MiniOS addon marketplace (lazyaddons-style). | 2 | 11 | 71.4% |
| [`mcp.minios_mcp`](modules/mcp.minios_mcp.py.md) | MiniOS MCP bridge. | 5 | 31 | 40.5% |
| [`mcp/mutate_mcp.sh`](modules/mcp.mutate_mcp.sh.md) | Mutation testing for the MiniOS MCP bridge. | 0 | 1 | 100.0% |

### `net`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`net/net.c`](modules/net.net.c.md) | MiniOS network stack: virtio-net preferred, rtl8139 fallback, under | 5 | 112 | 14.4% |
| [`net/rtl8139.c`](modules/net.rtl8139.c.md) |  | 0 | 18 | 42.1% |
| [`net/tls.c`](modules/net.tls.c.md) | tls.c - TLS 1.2 client sessions for MiniOS. | 0 | 11 | 50.0% |
| [`net/tls_crypto.c`](modules/net.tls_crypto.c.md) | tls_crypto.c - the crypto behind the kernel TLS 1.2 client. | 4 | 23 | 42.9% |
| [`net/tls_x509.c`](modules/net.tls_x509.c.md) | tls_x509.c - minimal X.509 DER parsing and chain verification. | 4 | 3 | 37.5% |

### `progs`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/minios_abi.h`](modules/progs.minios_abi.h.md) | minios_abi.h -- Single source of truth for the MiniOS user-kernel ABI. | 0 | 153 | 20.8% |
| [`progs/minios_png.h`](modules/progs.minios_png.h.md) | Docstring: shared ring-3 PNG helpers for MiniOS apps (progs/minios_png.h). | 0 | 20 | 52.4% |
| [`progs/nk_palette.h`](modules/progs.nk_palette.h.md) | nk_palette.h - one shared hybrid palette for every NK-window app. | 0 | 8 | 11.1% |

### `progs/asm`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/asm/aes.s`](modules/progs.asm.aes.s.md) |  | 0 | 30 | 0.0% |
| [`progs/asm/cp.s`](modules/progs.asm.cp.s.md) |  | 0 | 2 | 0.0% |
| [`progs/asm/cvmfmt.s`](modules/progs.asm.cvmfmt.s.md) |  | 0 | 4 | 0.0% |
| [`progs/asm/fib.s`](modules/progs.asm.fib.s.md) |  | 0 | 3 | 0.0% |
| [`progs/asm/freedom.s`](modules/progs.asm.freedom.s.md) |  | 0 | 92 | 0.0% |
| [`progs/asm/http.s`](modules/progs.asm.http.s.md) |  | 0 | 3 | 0.0% |
| [`progs/asm/json.s`](modules/progs.asm.json.s.md) |  | 0 | 32 | 0.0% |
| [`progs/asm/ldhello.s`](modules/progs.asm.ldhello.s.md) |  | 0 | 2 | 0.0% |
| [`progs/asm/lz4.s`](modules/progs.asm.lz4.s.md) |  | 0 | 7 | 0.0% |
| [`progs/asm/lzss.s`](modules/progs.asm.lzss.s.md) |  | 0 | 30 | 0.0% |
| [`progs/asm/mtop.s`](modules/progs.asm.mtop.s.md) |  | 0 | 36 | 0.0% |
| [`progs/asm/sign.s`](modules/progs.asm.sign.s.md) |  | 0 | 85 | 0.0% |
| [`progs/asm/w1.s`](modules/progs.asm.w1.s.md) |  | 0 | 2 | 0.0% |

### `progs/doomedit`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/doomedit/doomedit.c`](modules/progs.doomedit.doomedit.c.md) | doomedit.c - tile map editor that builds playable Doom PWADs. | 0 | 58 | 3.4% |

### `progs/doomgeneric`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/doomgeneric/am_map.c`](modules/progs.doomgeneric.am_map.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 5 | 82 | 26.1% |
| [`progs/doomgeneric/am_map.h`](modules/progs.doomgeneric.am_map.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 71.4% |
| [`progs/doomgeneric/config.h`](modules/progs.doomgeneric.config.h.md) | config.hin. | 0 | 10 | 100.0% |
| [`progs/doomgeneric/d_englsh.h`](modules/progs.doomgeneric.d_englsh.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 286 | 3.1% |
| [`progs/doomgeneric/d_event.c`](modules/progs.doomgeneric.d_event.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 50.0% |
| [`progs/doomgeneric/d_event.h`](modules/progs.doomgeneric.d_event.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 3 | 60.0% |
| [`progs/doomgeneric/d_items.c`](modules/progs.doomgeneric.d_items.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 0 | 100.0% |
| [`progs/doomgeneric/d_items.h`](modules/progs.doomgeneric.d_items.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 1 | 66.7% |
| [`progs/doomgeneric/d_iwad.c`](modules/progs.doomgeneric.d_iwad.c.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 1 | 13 | 6.7% |
| [`progs/doomgeneric/d_iwad.h`](modules/progs.doomgeneric.d_iwad.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 1 | 13 | 6.7% |
| [`progs/doomgeneric/d_loop.c`](modules/progs.doomgeneric.d_loop.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 8 | 60.0% |
| [`progs/doomgeneric/d_loop.h`](modules/progs.doomgeneric.d_loop.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 7 | 66.7% |
| [`progs/doomgeneric/d_main.c`](modules/progs.doomgeneric.d_main.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 18 | 47.4% |
| [`progs/doomgeneric/d_main.h`](modules/progs.doomgeneric.d_main.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 7 | 25.0% |
| [`progs/doomgeneric/d_mode.c`](modules/progs.doomgeneric.d_mode.c.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 6 | 14.3% |
| [`progs/doomgeneric/d_mode.h`](modules/progs.doomgeneric.d_mode.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 25.0% |
| [`progs/doomgeneric/d_net.c`](modules/progs.doomgeneric.d_net.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 66.7% |
| [`progs/doomgeneric/d_player.h`](modules/progs.doomgeneric.d_player.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 4 | 1 | 66.7% |
| [`progs/doomgeneric/d_textur.h`](modules/progs.doomgeneric.d_textur.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 1 | 66.7% |
| [`progs/doomgeneric/d_think.h`](modules/progs.doomgeneric.d_think.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 1 | 80.0% |
| [`progs/doomgeneric/d_ticcmd.h`](modules/progs.doomgeneric.d_ticcmd.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 1 | 33.3% |
| [`progs/doomgeneric/deh_main.h`](modules/progs.doomgeneric.deh_main.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 7 | 12.5% |
| [`progs/doomgeneric/deh_misc.h`](modules/progs.doomgeneric.deh_misc.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 32 | 3.0% |
| [`progs/doomgeneric/deh_str.h`](modules/progs.doomgeneric.deh_str.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 10 | 9.1% |
| [`progs/doomgeneric/doom.h`](modules/progs.doomgeneric.doom.h.md) |  | 0 | 1 | 0.0% |
| [`progs/doomgeneric/doomdata.h`](modules/progs.doomgeneric.doomdata.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 11 | 91.7% |
| [`progs/doomgeneric/doomdef.c`](modules/progs.doomgeneric.doomdef.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 0 | 100.0% |
| [`progs/doomgeneric/doomdef.h`](modules/progs.doomgeneric.doomdef.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 9 | 70.0% |
| [`progs/doomgeneric/doomfeatures.h`](modules/progs.doomgeneric.doomfeatures.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 1 | 50.0% |
| [`progs/doomgeneric/doomgeneric.c`](modules/progs.doomgeneric.doomgeneric.c.md) |  | 0 | 1 | 0.0% |
| [`progs/doomgeneric/doomgeneric.h`](modules/progs.doomgeneric.doomgeneric.h.md) |  | 0 | 9 | 0.0% |
| [`progs/doomgeneric/doomgeneric_minios.c`](modules/progs.doomgeneric.doomgeneric_minios.c.md) | doomgeneric_minios.c - MiniOS platform layer for doomgeneric. | 1 | 11 | 30.8% |
| [`progs/doomgeneric/doomgeneric_sdl.c`](modules/progs.doomgeneric.doomgeneric_sdl.c.md) | doomgeneric for soso os | 0 | 7 | 12.5% |
| [`progs/doomgeneric/doomgeneric_soso.c`](modules/progs.doomgeneric.doomgeneric_soso.c.md) | doomgeneric for soso os | 1 | 9 | 9.1% |
| [`progs/doomgeneric/doomgeneric_sosox.c`](modules/progs.doomgeneric.doomgeneric_sosox.c.md) | doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access! | 0 | 9 | 10.0% |
| [`progs/doomgeneric/doomgeneric_win.c`](modules/progs.doomgeneric.doomgeneric_win.c.md) |  | 0 | 7 | 0.0% |
| [`progs/doomgeneric/doomgeneric_xlib.c`](modules/progs.doomgeneric.doomgeneric_xlib.c.md) |  | 0 | 7 | 0.0% |
| [`progs/doomgeneric/doomkeys.h`](modules/progs.doomgeneric.doomkeys.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 59 | 5.0% |
| [`progs/doomgeneric/doomstat.c`](modules/progs.doomgeneric.doomstat.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 0 | 100.0% |
| [`progs/doomgeneric/doomstat.h`](modules/progs.doomgeneric.doomstat.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 50.0% |
| [`progs/doomgeneric/doomtype.h`](modules/progs.doomgeneric.doomtype.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 12 | 20.0% |
| [`progs/doomgeneric/dstrings.c`](modules/progs.doomgeneric.dstrings.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 0 | 100.0% |
| [`progs/doomgeneric/dstrings.h`](modules/progs.doomgeneric.dstrings.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 75.0% |
| [`progs/doomgeneric/dummy.c`](modules/progs.doomgeneric.dummy.c.md) |  | 0 | 1 | 0.0% |
| [`progs/doomgeneric/f_finale.c`](modules/progs.doomgeneric.f_finale.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 14 | 47.1% |
| [`progs/doomgeneric/f_finale.h`](modules/progs.doomgeneric.f_finale.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 60.0% |
| [`progs/doomgeneric/f_wipe.c`](modules/progs.doomgeneric.f_wipe.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 10 | 9.1% |
| [`progs/doomgeneric/f_wipe.h`](modules/progs.doomgeneric.f_wipe.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 25.0% |
| [`progs/doomgeneric/g_game.c`](modules/progs.doomgeneric.g_game.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 45 | 43.5% |
| [`progs/doomgeneric/g_game.h`](modules/progs.doomgeneric.g_game.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 20 | 28.6% |
| [`progs/doomgeneric/gusconf.c`](modules/progs.doomgeneric.gusconf.c.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 1 | 2 | 25.0% |
| [`progs/doomgeneric/gusconf.h`](modules/progs.doomgeneric.gusconf.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 0 | 100.0% |
| [`progs/doomgeneric/hu_lib.c`](modules/progs.doomgeneric.hu_lib.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 21 | 59.1% |
| [`progs/doomgeneric/hu_lib.h`](modules/progs.doomgeneric.hu_lib.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 21 | 64.0% |
| [`progs/doomgeneric/hu_stuff.c`](modules/progs.doomgeneric.hu_stuff.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 23 | 8.3% |
| [`progs/doomgeneric/hu_stuff.h`](modules/progs.doomgeneric.hu_stuff.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 15 | 18.8% |
| [`progs/doomgeneric/i_cdmus.c`](modules/progs.doomgeneric.i_cdmus.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 9 | 10.0% |
| [`progs/doomgeneric/i_cdmus.h`](modules/progs.doomgeneric.i_cdmus.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 17 | 5.6% |
| [`progs/doomgeneric/i_endoom.c`](modules/progs.doomgeneric.i_endoom.c.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 2 | 33.3% |
| [`progs/doomgeneric/i_endoom.h`](modules/progs.doomgeneric.i_endoom.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 33.3% |
| [`progs/doomgeneric/i_input.c`](modules/progs.doomgeneric.i_input.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 33.3% |
| [`progs/doomgeneric/i_joystick.c`](modules/progs.doomgeneric.i_joystick.c.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 5 | 33.3% |
| [`progs/doomgeneric/i_joystick.h`](modules/progs.doomgeneric.i_joystick.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 18 | 47.4% |
| [`progs/doomgeneric/i_main.c`](modules/progs.doomgeneric.i_main.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 20.0% |
| [`progs/doomgeneric/i_minios_sound.c`](modules/progs.doomgeneric.i_minios_sound.c.md) |  | 2 | 12 | 13.3% |
| [`progs/doomgeneric/i_scale.c`](modules/progs.doomgeneric.i_scale.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 7 | 12.5% |
| [`progs/doomgeneric/i_scale.h`](modules/progs.doomgeneric.i_scale.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 25.0% |
| [`progs/doomgeneric/i_sound.c`](modules/progs.doomgeneric.i_sound.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 21 | 4.5% |
| [`progs/doomgeneric/i_sound.h`](modules/progs.doomgeneric.i_sound.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 5 | 19 | 12.0% |
| [`progs/doomgeneric/i_swap.h`](modules/progs.doomgeneric.i_swap.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 8 | 11.1% |
| [`progs/doomgeneric/i_system.c`](modules/progs.doomgeneric.i_system.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 15 | 27.8% |
| [`progs/doomgeneric/i_system.h`](modules/progs.doomgeneric.i_system.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 12 | 38.5% |
| [`progs/doomgeneric/i_timer.c`](modules/progs.doomgeneric.i_timer.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 85.7% |
| [`progs/doomgeneric/i_timer.h`](modules/progs.doomgeneric.i_timer.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 7 | 75.0% |
| [`progs/doomgeneric/i_video.c`](modules/progs.doomgeneric.i_video.c.md) | Emacs style mode select -*- C++ -*- ----------------------------------------------------------------------------- $Id:$ Copyright (C) 1993-1996 by id Software... | 4 | 26 | 16.1% |
| [`progs/doomgeneric/i_video.h`](modules/progs.doomgeneric.i_video.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 25 | 11.1% |
| [`progs/doomgeneric/icon.c`](modules/progs.doomgeneric.icon.c.md) |  | 0 | 0 | 0.0% |
| [`progs/doomgeneric/info.c`](modules/progs.doomgeneric.info.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 74 | 2.7% |
| [`progs/doomgeneric/info.h`](modules/progs.doomgeneric.info.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 1 | 25.0% |
| [`progs/doomgeneric/m_argv.c`](modules/progs.doomgeneric.m_argv.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 42.9% |
| [`progs/doomgeneric/m_argv.h`](modules/progs.doomgeneric.m_argv.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 5 | 50.0% |
| [`progs/doomgeneric/m_bbox.c`](modules/progs.doomgeneric.m_bbox.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 66.7% |
| [`progs/doomgeneric/m_bbox.h`](modules/progs.doomgeneric.m_bbox.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 50.0% |
| [`progs/doomgeneric/m_cheat.c`](modules/progs.doomgeneric.m_cheat.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 33.3% |
| [`progs/doomgeneric/m_cheat.h`](modules/progs.doomgeneric.m_cheat.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 6 | 12.5% |
| [`progs/doomgeneric/m_config.c`](modules/progs.doomgeneric.m_config.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 17 | 5.0% |
| [`progs/doomgeneric/m_config.h`](modules/progs.doomgeneric.m_config.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 11 | 8.3% |
| [`progs/doomgeneric/m_controls.c`](modules/progs.doomgeneric.m_controls.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 9 | 10.0% |
| [`progs/doomgeneric/m_controls.h`](modules/progs.doomgeneric.m_controls.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 9 | 10.0% |
| [`progs/doomgeneric/m_fixed.c`](modules/progs.doomgeneric.m_fixed.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 33.3% |
| [`progs/doomgeneric/m_fixed.h`](modules/progs.doomgeneric.m_fixed.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 5 | 42.9% |
| [`progs/doomgeneric/m_menu.c`](modules/progs.doomgeneric.m_menu.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 58 | 46.8% |
| [`progs/doomgeneric/m_menu.h`](modules/progs.doomgeneric.m_menu.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 5 | 83.3% |
| [`progs/doomgeneric/m_misc.c`](modules/progs.doomgeneric.m_misc.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 22 | 17.4% |
| [`progs/doomgeneric/m_misc.h`](modules/progs.doomgeneric.m_misc.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 14 | 6.7% |
| [`progs/doomgeneric/m_random.c`](modules/progs.doomgeneric.m_random.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 100.0% |
| [`progs/doomgeneric/m_random.h`](modules/progs.doomgeneric.m_random.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 80.0% |
| [`progs/doomgeneric/memio.c`](modules/progs.doomgeneric.memio.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 8 | 10.0% |
| [`progs/doomgeneric/memio.h`](modules/progs.doomgeneric.memio.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 8 | 20.0% |
| [`progs/doomgeneric/net_client.h`](modules/progs.doomgeneric.net_client.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 8 | 11.1% |
| [`progs/doomgeneric/net_dedicated.h`](modules/progs.doomgeneric.net_dedicated.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 1 | 50.0% |
| [`progs/doomgeneric/net_defs.h`](modules/progs.doomgeneric.net_defs.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 13 | 14 | 7.1% |
| [`progs/doomgeneric/net_gui.h`](modules/progs.doomgeneric.net_gui.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 1 | 50.0% |
| [`progs/doomgeneric/net_io.h`](modules/progs.doomgeneric.net_io.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 7 | 12.5% |
| [`progs/doomgeneric/net_loop.h`](modules/progs.doomgeneric.net_loop.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 0 | 100.0% |
| [`progs/doomgeneric/net_packet.h`](modules/progs.doomgeneric.net_packet.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 8 | 11.1% |
| [`progs/doomgeneric/net_query.h`](modules/progs.doomgeneric.net_query.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 11 | 8.3% |
| [`progs/doomgeneric/net_sdl.h`](modules/progs.doomgeneric.net_sdl.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 0 | 100.0% |
| [`progs/doomgeneric/net_server.h`](modules/progs.doomgeneric.net_server.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 5 | 16.7% |
| [`progs/doomgeneric/p_ceilng.c`](modules/progs.doomgeneric.p_ceilng.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 71.4% |
| [`progs/doomgeneric/p_doors.c`](modules/progs.doomgeneric.p_doors.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 10 | 36.4% |
| [`progs/doomgeneric/p_enemy.c`](modules/progs.doomgeneric.p_enemy.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 67 | 32.4% |
| [`progs/doomgeneric/p_floor.c`](modules/progs.doomgeneric.p_floor.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 40.0% |
| [`progs/doomgeneric/p_inter.c`](modules/progs.doomgeneric.p_inter.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 10 | 9.1% |
| [`progs/doomgeneric/p_inter.h`](modules/progs.doomgeneric.p_inter.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/p_lights.c`](modules/progs.doomgeneric.p_lights.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 11 | 66.7% |
| [`progs/doomgeneric/p_local.h`](modules/progs.doomgeneric.p_local.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 60 | 17.5% |
| [`progs/doomgeneric/p_map.c`](modules/progs.doomgeneric.p_map.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 21 | 54.5% |
| [`progs/doomgeneric/p_maputl.c`](modules/progs.doomgeneric.p_maputl.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 15 | 17.6% |
| [`progs/doomgeneric/p_mobj.c`](modules/progs.doomgeneric.p_mobj.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 20 | 42.9% |
| [`progs/doomgeneric/p_mobj.h`](modules/progs.doomgeneric.p_mobj.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 1 | 75.0% |
| [`progs/doomgeneric/p_plats.c`](modules/progs.doomgeneric.p_plats.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 28.6% |
| [`progs/doomgeneric/p_pspr.c`](modules/progs.doomgeneric.p_pspr.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 34 | 28.6% |
| [`progs/doomgeneric/p_pspr.h`](modules/progs.doomgeneric.p_pspr.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 3 | 40.0% |
| [`progs/doomgeneric/p_saveg.c`](modules/progs.doomgeneric.p_saveg.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 20 | 42.9% |
| [`progs/doomgeneric/p_saveg.h`](modules/progs.doomgeneric.p_saveg.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 14 | 13.3% |
| [`progs/doomgeneric/p_setup.c`](modules/progs.doomgeneric.p_setup.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 15 | 87.5% |
| [`progs/doomgeneric/p_setup.h`](modules/progs.doomgeneric.p_setup.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 50.0% |
| [`progs/doomgeneric/p_sight.c`](modules/progs.doomgeneric.p_sight.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 5 | 50.0% |
| [`progs/doomgeneric/p_switch.c`](modules/progs.doomgeneric.p_switch.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 40.0% |
| [`progs/doomgeneric/p_telept.c`](modules/progs.doomgeneric.p_telept.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/p_tick.c`](modules/progs.doomgeneric.p_tick.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 6 | 100.0% |
| [`progs/doomgeneric/p_tick.h`](modules/progs.doomgeneric.p_tick.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 66.7% |
| [`progs/doomgeneric/p_user.c`](modules/progs.doomgeneric.p_user.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 8 | 77.8% |
| [`progs/doomgeneric/r_bsp.c`](modules/progs.doomgeneric.r_bsp.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 10 | 58.3% |
| [`progs/doomgeneric/r_bsp.h`](modules/progs.doomgeneric.r_bsp.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 40.0% |
| [`progs/doomgeneric/r_data.c`](modules/progs.doomgeneric.r_data.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 13 | 76.5% |
| [`progs/doomgeneric/r_data.h`](modules/progs.doomgeneric.r_data.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 7 | 50.0% |
| [`progs/doomgeneric/r_defs.h`](modules/progs.doomgeneric.r_defs.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 19 | 6 | 69.2% |
| [`progs/doomgeneric/r_draw.c`](modules/progs.doomgeneric.r_draw.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 20 | 66.7% |
| [`progs/doomgeneric/r_draw.h`](modules/progs.doomgeneric.r_draw.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 14 | 60.0% |
| [`progs/doomgeneric/r_local.h`](modules/progs.doomgeneric.r_local.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/r_main.c`](modules/progs.doomgeneric.r_main.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 19 | 60.0% |
| [`progs/doomgeneric/r_main.h`](modules/progs.doomgeneric.r_main.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 20 | 33.3% |
| [`progs/doomgeneric/r_plane.c`](modules/progs.doomgeneric.r_plane.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 9 | 60.0% |
| [`progs/doomgeneric/r_plane.h`](modules/progs.doomgeneric.r_plane.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 8 | 11.1% |
| [`progs/doomgeneric/r_segs.c`](modules/progs.doomgeneric.r_segs.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 5 | 33.3% |
| [`progs/doomgeneric/r_segs.h`](modules/progs.doomgeneric.r_segs.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 2 | 33.3% |
| [`progs/doomgeneric/r_sky.c`](modules/progs.doomgeneric.r_sky.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 100.0% |
| [`progs/doomgeneric/r_sky.h`](modules/progs.doomgeneric.r_sky.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 4 | 80.0% |
| [`progs/doomgeneric/r_state.h`](modules/progs.doomgeneric.r_state.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/r_things.c`](modules/progs.doomgeneric.r_things.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 16 | 50.0% |
| [`progs/doomgeneric/r_things.h`](modules/progs.doomgeneric.r_things.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 11 | 8.3% |
| [`progs/doomgeneric/s_sound.c`](modules/progs.doomgeneric.s_sound.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 21 | 30.4% |
| [`progs/doomgeneric/s_sound.h`](modules/progs.doomgeneric.s_sound.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 14 | 46.7% |
| [`progs/doomgeneric/sha1.c`](modules/progs.doomgeneric.sha1.c.md) | sha1.c - SHA1 hash function | 0 | 18 | 15.8% |
| [`progs/doomgeneric/sha1.h`](modules/progs.doomgeneric.sha1.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 3 | 5 | 22.2% |
| [`progs/doomgeneric/sounds.c`](modules/progs.doomgeneric.sounds.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 25.0% |
| [`progs/doomgeneric/sounds.h`](modules/progs.doomgeneric.sounds.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/st_lib.c`](modules/progs.doomgeneric.st_lib.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 10 | 18.2% |
| [`progs/doomgeneric/st_lib.h`](modules/progs.doomgeneric.st_lib.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 4 | 10 | 26.7% |
| [`progs/doomgeneric/st_stuff.c`](modules/progs.doomgeneric.st_stuff.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 134 | 25.2% |
| [`progs/doomgeneric/st_stuff.h`](modules/progs.doomgeneric.st_stuff.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 7 | 75.0% |
| [`progs/doomgeneric/statdump.c`](modules/progs.doomgeneric.statdump.c.md) |  | 0 | 3 | 0.0% |
| [`progs/doomgeneric/statdump.h`](modules/progs.doomgeneric.statdump.h.md) |  | 0 | 2 | 0.0% |
| [`progs/doomgeneric/tables.c`](modules/progs.doomgeneric.tables.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 100.0% |
| [`progs/doomgeneric/tables.h`](modules/progs.doomgeneric.tables.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 16 | 22.2% |
| [`progs/doomgeneric/v_patch.h`](modules/progs.doomgeneric.v_patch.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 0 | 100.0% |
| [`progs/doomgeneric/v_video.c`](modules/progs.doomgeneric.v_video.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 28 | 20.7% |
| [`progs/doomgeneric/v_video.h`](modules/progs.doomgeneric.v_video.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 25 | 7.7% |
| [`progs/doomgeneric/w_checksum.c`](modules/progs.doomgeneric.w_checksum.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/w_checksum.h`](modules/progs.doomgeneric.w_checksum.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/w_file.c`](modules/progs.doomgeneric.w_file.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 3 | 25.0% |
| [`progs/doomgeneric/w_file.h`](modules/progs.doomgeneric.w_file.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 4 | 25.0% |
| [`progs/doomgeneric/w_file_stdc.c`](modules/progs.doomgeneric.w_file_stdc.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 1 | 1 | 33.3% |
| [`progs/doomgeneric/w_main.c`](modules/progs.doomgeneric.w_main.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 1 | 50.0% |
| [`progs/doomgeneric/w_main.h`](modules/progs.doomgeneric.w_main.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 0 | 100.0% |
| [`progs/doomgeneric/w_merge.h`](modules/progs.doomgeneric.w_merge.h.md) | Copyright(C) 2005-2014 Simon Howard This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License... | 0 | 6 | 14.3% |
| [`progs/doomgeneric/w_wad.c`](modules/progs.doomgeneric.w_wad.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 15 | 37.5% |
| [`progs/doomgeneric/w_wad.h`](modules/progs.doomgeneric.w_wad.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 13 | 12.5% |
| [`progs/doomgeneric/wi_stuff.c`](modules/progs.doomgeneric.wi_stuff.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 2 | 63 | 25.8% |
| [`progs/doomgeneric/wi_stuff.h`](modules/progs.doomgeneric.wi_stuff.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 5 | 83.3% |
| [`progs/doomgeneric/z_zone.c`](modules/progs.doomgeneric.z_zone.c.md) | Copyright(C) 1993-1996 Id Software, Inc. | 3 | 15 | 52.6% |
| [`progs/doomgeneric/z_zone.h`](modules/progs.doomgeneric.z_zone.h.md) | Copyright(C) 1993-1996 Id Software, Inc. | 0 | 13 | 14.3% |

### `progs/file`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/file/file.c`](modules/progs.file.file.c.md) | Docstring: MiniOS file browser (Nuklear ring-3 app, MiniFS: file/file.elf). | 1 | 38 | 10.0% |
| [`progs/file/file_assoc.h`](modules/progs.file.file_assoc.h.md) | Docstring: dynamic association table for the MiniOS file browser. | 2 | 14 | 64.7% |

### `progs/freedomui`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/freedomui/freedomui_minios.c`](modules/progs.freedomui.freedomui_minios.c.md) | freedomui_minios - Real FreeDom browser on MiniOS, DOOM/Q2G pattern. | 2 | 19 | 40.9% |
| [`progs/freedomui/media_unavailable.c`](modules/progs.freedomui.media_unavailable.c.md) | media_unavailable.c - FreeDom media decoder entry points for a build | 0 | 1 | 100.0% |
| [`progs/freedomui/platform_minios.c`](modules/progs.freedomui.platform_minios.c.md) |  | 3 | 33 | 32.4% |
| [`progs/freedomui/ps2_keymap.c`](modules/progs.freedomui.ps2_keymap.c.md) | ps2_keymap.c - pure PS/2 set 1 scancode to keysym translator (US layout). | 2 | 74 | 5.2% |
| [`progs/freedomui/ps2_keymap.h`](modules/progs.freedomui.ps2_keymap.h.md) | ps2_keymap.h - pure PS/2 set 1 scancode to keysym translator (US layout). | 4 | 8 | 61.5% |

### `progs/lisp`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/lisp/lisp.c`](modules/progs.lisp.lisp.c.md) |  | 15 | 3 | 57.9% |
| [`progs/lisp/tin.c`](modules/progs.lisp.tin.c.md) |  | 0 | 1 | 0.0% |

### `progs/lua`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/lua/lua_main.c`](modules/progs.lua.lua_main.c.md) |  | 0 | 2 | 0.0% |
| [`progs/lua/minios.c`](modules/progs.lua.minios.c.md) |  | 0 | 9 | 10.0% |

### `progs/micropython/variants/minios`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs.micropython.variants.minios.manifest`](modules/progs.micropython.variants.minios.manifest.py.md) | manifest.py -- frozen modules for the MiniOS MicroPython variant. | 0 | 0 | 100.0% |
| [`progs/micropython/variants/minios/minios_module.c`](modules/progs.micropython.variants.minios.minios_module.c.md) |  | 0 | 8 | 11.1% |
| [`progs/micropython/variants/minios/mpconfigvariant.h`](modules/progs.micropython.variants.minios.mpconfigvariant.h.md) |  | 0 | 46 | 40.4% |

### `progs/micropython/variants/minios/lib`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs.micropython.variants.minios.lib`](modules/progs.micropython.variants.minios.lib.__init__.py.md) | MiniOS frozen library package. | 0 | 0 | 100.0% |
| [`progs.micropython.variants.minios.lib.hello`](modules/progs.micropython.variants.minios.lib.hello.py.md) | hello.py -- frozen demo: runs at import time as a smoke test. | 0 | 0 | 100.0% |
| [`progs.micropython.variants.minios.lib.mip`](modules/progs.micropython.variants.minios.lib.mip.py.md) | mip.py -- MiniOS package installer (frozen module). | 0 | 11 | 100.0% |

### `progs/minicraft`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/minicraft/minicraft.c`](modules/progs.minicraft.minicraft.c.md) | minicraft.c - Minecraft-like voxel walker for MiniOS (ring 3, static ELF). | 6 | 108 | 7.0% |

### `progs/nuklear`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/nuklear/cvm_emit.c`](modules/progs.nuklear.cvm_emit.c.md) | cvm_emit.c — node-graph to CVM bytecode compiler. | 1 | 44 | 8.7% |
| [`progs/nuklear/cvm_emit.h`](modules/progs.nuklear.cvm_emit.h.md) | cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2). | 2 | 3 | 66.7% |
| [`progs/nuklear/font8x8.c`](modules/progs.nuklear.font8x8.c.md) | font8x8 - shared 8x8 bitmap font for MiniOS ring-3 graphics programs. | 0 | 0 | 100.0% |
| [`progs/nuklear/node_editor.c`](modules/progs.nuklear.node_editor.c.md) | node_editor.c — visual low-code editor that compiles to CVM bytecode. | 2 | 13 | 37.5% |
| [`progs/nuklear/nuklear_minios.c`](modules/progs.nuklear.nuklear_minios.c.md) | nuklear_minios.c — MiniOS platform layer for Nuklear. | 0 | 23 | 41.7% |
| [`progs/nuklear/nuklear_minios.h`](modules/progs.nuklear.nuklear_minios.h.md) | nuklear_minios.h — MiniOS platform layer for Nuklear. | 4 | 23 | 53.6% |
| [`progs/nuklear/nuklear_theme.c`](modules/progs.nuklear.nuklear_theme.c.md) | Docstring: shared Nuklear theme loader, linked by every NK app. | 1 | 4 | 66.7% |
| [`progs/nuklear/nuklear_theme.h`](modules/progs.nuklear.nuklear_theme.h.md) | Docstring: shared Nuklear theme contract for every MiniOS NK app. | 1 | 11 | 38.5% |

### `progs/paint`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/paint/paint.c`](modules/progs.paint.paint.c.md) | Docstring: MiniOS paint program (Nuklear ring-3 app, MiniFS: paint/paint.elf). | 0 | 27 | 10.7% |

### `progs/piano`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/piano/piano.c`](modules/progs.piano.piano.c.md) | piano.c — a Nuklear piano that plays FM sound through the SB16 driver. | 0 | 29 | 30.0% |

### `progs/pokemon`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/pokemon/fetch.sh`](modules/progs.pokemon.fetch.sh.md) | fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream. | 0 | 0 | 100.0% |
| [`progs/pokemon/platform_minios.c`](modules/progs.pokemon.platform_minios.c.md) |  | 1 | 57 | 11.9% |

### `progs/pokemon/minios_stubs`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/pokemon/minios_stubs/SDL.h`](modules/progs.pokemon.minios_stubs.SDL.h.md) | SDL.h stub for MiniOS cross-compilation | 5 | 5 | 18.2% |

### `progs/quake2generic`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/quake2generic/q2generic_minios.c`](modules/progs.quake2generic.q2generic_minios.c.md) | q2generic_minios.c - MiniOS platform layer for quake2generic. | 0 | 20 | 28.6% |
| [`progs/quake2generic/snddma_minios.c`](modules/progs.quake2generic.snddma_minios.c.md) | snddma_minios.c - Quake 2 DMA sound backend over the MiniOS pcm2 path. | 0 | 11 | 41.7% |

### `progs/src`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/src/aes.c`](modules/progs.src.aes.c.md) | aes.c - command path AES-256-CTR encryption tools: aes and unaes. | 0 | 33 | 2.9% |
| [`progs/src/apsse.c`](modules/progs.src.apsse.c.md) |  | 1 | 12 | 7.1% |
| [`progs/src/aslr.c`](modules/progs.src.aslr.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/audio.c`](modules/progs.src.audio.c.md) |  | 0 | 13 | 42.9% |
| [`progs/src/burn.c`](modules/progs.src.burn.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/cp.c`](modules/progs.src.cp.c.md) |  | 0 | 8 | 0.0% |
| [`progs/src/cpl.c`](modules/progs.src.cpl.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/cvmfmt.c`](modules/progs.src.cvmfmt.c.md) | cvmfmt.c - CVM formatting probe. | 0 | 1 | 50.0% |
| [`progs/src/execho.c`](modules/progs.src.execho.c.md) | execho -- fork(57) + execve(59) + wait4(61) probe. | 0 | 3 | 25.0% |
| [`progs/src/execthr.c`](modules/progs.src.execthr.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/fib.c`](modules/progs.src.fib.c.md) |  | 0 | 2 | 0.0% |
| [`progs/src/forktest.c`](modules/progs.src.forktest.c.md) |  | 0 | 10 | 0.0% |
| [`progs/src/fptest.c`](modules/progs.src.fptest.c.md) | fptest.c -- FPU/SSE context-switch probe (Phase 0.1, ADR-0014). | 1 | 3 | 20.0% |
| [`progs/src/freedom.c`](modules/progs.src.freedom.c.md) | freedom - a headless text browser for MiniOS. | 0 | 29 | 20.0% |
| [`progs/src/freedom_wl.c`](modules/progs.src.freedom_wl.c.md) | freedom_wl - Wayland to MiniOS intermediate layer for FreeDom. | 2 | 23 | 34.6% |
| [`progs/src/ftest.c`](modules/progs.src.ftest.c.md) |  | 0 | 6 | 14.3% |
| [`progs/src/hello.c`](modules/progs.src.hello.c.md) |  | 0 | 2 | 33.3% |
| [`progs.src.hello`](modules/progs.src.hello.py.md) |  | 0 | 0 | 0.0% |
| [`progs/src/http.c`](modules/progs.src.http.c.md) | Minimal HTTP/1.0 GET through the Linux socket syscalls. | 0 | 13 | 14.3% |
| [`progs/src/json.c`](modules/progs.src.json.c.md) | json.c - command path JSON tool: validate, pretty-print and query. | 0 | 25 | 3.8% |
| [`progs/src/kmem.c`](modules/progs.src.kmem.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/ldhello.c`](modules/progs.src.ldhello.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/lxabi.c`](modules/progs.src.lxabi.c.md) |  | 2 | 24 | 3.7% |
| [`progs/src/lxhello.c`](modules/progs.src.lxhello.c.md) |  | 0 | 3 | 25.0% |
| [`progs/src/lxnet.c`](modules/progs.src.lxnet.c.md) |  | 0 | 8 | 11.1% |
| [`progs/src/lxproc.c`](modules/progs.src.lxproc.c.md) |  | 1 | 6 | 50.0% |
| [`progs/src/lxsecc.c`](modules/progs.src.lxsecc.c.md) |  | 0 | 15 | 6.2% |
| [`progs/src/lxsel.c`](modules/progs.src.lxsel.c.md) | lxsel.c -- select(2)/pselect6(2) ABI probe (docs/spec/python.md). | 0 | 7 | 25.0% |
| [`progs/src/lxtls.c`](modules/progs.src.lxtls.c.md) | lxtls.c - libcurl/OpenSSL fetch probe (FreeDom readiness step 6, | 0 | 6 | 14.3% |
| [`progs/src/lz4.c`](modules/progs.src.lz4.c.md) | lz4.c - command path LZ4 (de)compression tools: lz4 and unlz4. | 0 | 21 | 4.5% |
| [`progs/src/lzss.c`](modules/progs.src.lzss.c.md) | lzss.c - command path LZSS (de)compression tools: lzss and unlzss. | 0 | 31 | 3.1% |
| [`progs/src/mmreuse.c`](modules/progs.src.mmreuse.c.md) | mmap/munmap reclaim stress test. | 0 | 2 | 33.3% |
| [`progs/src/mprot.c`](modules/progs.src.mprot.c.md) | mprotect probe. | 0 | 1 | 50.0% |
| [`progs/src/mthreads.h`](modules/progs.src.mthreads.h.md) | mthreads.h -- Minimal pthread-like threads for MiniOS ELFs (roadmap | 3 | 16 | 20.0% |
| [`progs/src/mtop.c`](modules/progs.src.mtop.c.md) | mtop.c - ASCII real-time system monitor for MiniOS. | 0 | 16 | 5.9% |
| [`progs/src/mvrn.c`](modules/progs.src.mvrn.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/nx.c`](modules/progs.src.nx.c.md) | NX probe. | 0 | 1 | 50.0% |
| [`progs/src/opl3.c`](modules/progs.src.opl3.c.md) |  | 1 | 10 | 8.3% |
| [`progs/src/pcmap.c`](modules/progs.src.pcmap.c.md) |  | 0 | 1 | 0.0% |
| [`progs/src/pip.c`](modules/progs.src.pip.c.md) | pip -- launcher for `python3 -m pip`, and pip3 as a copy of this image. | 1 | 6 | 87.5% |
| [`progs/src/pollready.c`](modules/progs.src.pollready.c.md) |  | 0 | 1 | 50.0% |
| [`progs/src/sbtone.c`](modules/progs.src.sbtone.c.md) | sbtone.c — headless SB16 diagnostic (ring-3, no GUI). | 0 | 8 | 11.1% |
| [`progs/src/scfuzz.c`](modules/progs.src.scfuzz.c.md) | scfuzz: deterministic syscall fuzzer (syzkaller spirit, BDD scale). | 0 | 10 | 9.1% |
| [`progs.src.shell`](modules/progs.src.shell.py.md) | shell.py -- pybash: a Python shell layer on top of MiniOS's C shell. | 0 | 3 | 25.0% |
| [`progs/src/sign.c`](modules/progs.src.sign.c.md) | sign.c - in-OS Ed25519 code signer for MiniOS secure boot. | 0 | 31 | 3.1% |
| [`progs/src/spin.c`](modules/progs.src.spin.c.md) |  | 0 | 5 | 16.7% |
| [`progs/src/thdemo.c`](modules/progs.src.thdemo.c.md) | thdemo.c -- Producer-consumer over mthreads (roadmap Phase 1, M1). | 0 | 8 | 11.1% |
| [`progs/src/w1.c`](modules/progs.src.w1.c.md) |  | 0 | 2 | 0.0% |

### `progs/tls_u`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/tls_u/tls_u_main.c`](modules/progs.tls_u.tls_u_main.c.md) | tlsget - minimal HTTPS GET over the ring-3 TLS stack. | 0 | 4 | 20.0% |
| [`progs/tls_u/tls_u_port.c`](modules/progs.tls_u.tls_u_port.c.md) | tls_u_port.c - ring-3 transport for the shared TLS stack (TLS_RING3). | 0 | 13 | 28.6% |

### `progs/topogpt3`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/topogpt3/topogpt3.c`](modules/progs.topogpt3.topogpt3.c.md) |  | 3 | 65 | 8.7% |

### `progs/vedit`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/vedit/vedit.c`](modules/progs.vedit.vedit.c.md) | vedit IDE build and run contract. | 0 | 116 | 7.7% |

### `progs/wl`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`progs/wl/wl_client.h`](modules/progs.wl.wl_client.h.md) | wl_client.h - Thin mailbox client for Wayland-mini (ADR-0026). | 0 | 4 | 80.0% |
| [`progs/wl/wl_mbox.h`](modules/progs.wl.wl_mbox.h.md) | wl_mbox.h - Mailbox file transport for Wayland-mini (ADR-0026). | 1 | 24 | 46.2% |
| [`progs/wl/wl_mini.h`](modules/progs.wl.wl_mini.h.md) | wl_mini.h - Wayland-mini subset contract (header-only, ADR-0024). | 8 | 100 | 18.3% |
| [`progs/wl/wl_pixbuf.h`](modules/progs.wl.wl_pixbuf.h.md) | Docstring: heap pixel store for the Wayland-mini server. | 2 | 14 | 76.5% |
| [`progs/wl/wlcomp.c`](modules/progs.wl.wlcomp.c.md) | wlcomp - Wayland-mini ring-3 compositor (ADR-0024, ADR-0026). | 3 | 4 | 37.5% |

### `tools`

| Module | Summary | Types | Callables | Coverage |
|---|---|---|---|---|
| [`tools/abi_stamp.c`](modules/tools.abi_stamp.c.md) | Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator. | 0 | 1 | 50.0% |
| [`tools/boot_run.sh`](modules/tools.boot_run.sh.md) | boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial console with a list of commands, capturing the full transcript. | 0 | 0 | 100.0% |
| [`tools.boot_wl`](modules/tools.boot_wl.py.md) | boot_wl.py - boot the miniOS Wayland-mini desktop in one step. | 2 | 13 | 6.2% |
| [`tools.check_abi_numbers`](modules/tools.check_abi_numbers.py.md) | check_abi_numbers.py -- MiniOS syscall numbers vs Linux x86-64 truth. | 0 | 5 | 33.3% |
| [`tools.check_addons`](modules/tools.check_addons.py.md) | check_addons.py -- validate the MiniOS addon marketplace index. | 0 | 2 | 33.3% |
| [`tools.check_cohesion`](modules/tools.check_cohesion.py.md) | check_cohesion.py -- Architectural cohesion gate for MiniOS CI. | 0 | 4 | 80.0% |
| [`tools.check_complexity`](modules/tools.check_complexity.py.md) | check_complexity.py -- Kernel complexity gate for MiniOS CI. | 0 | 3 | 75.0% |
| [`tools.check_fork_stubs`](modules/tools.check_fork_stubs.py.md) | Fail-closed stub gate for unimplemented process syscalls. | 1 | 3 | 100.0% |
| [`tools.check_kb_sync`](modules/tools.check_kb_sync.py.md) | check_kb_sync.py -- Verify KNOWLEDGE_BASE.md is in sync with code. | 0 | 2 | 66.7% |
| [`tools.check_mutant_anchors`](modules/tools.check_mutant_anchors.py.md) | Verify every mutate.sh mutant anchor matches its target file. | 1 | 5 | 100.0% |
| [`tools.check_spin_discipline`](modules/tools.check_spin_discipline.py.md) | Check spinlock call-site discipline across kernel C sources. | 1 | 3 | 80.0% |
| [`tools.check_surprising`](modules/tools.check_surprising.py.md) | check_surprising.py -- Detect surprising architectural connections. | 0 | 5 | 83.3% |
| [`tools.check_syscall_sanitize`](modules/tools.check_syscall_sanitize.py.md) | Scoped audit gate for syscall user-pointer sanitization. | 1 | 7 | 100.0% |
| [`tools.clip_bridge`](modules/tools.clip_bridge.py.md) | Host to MiniOS clipboard bridge plan builder. | 1 | 4 | 100.0% |
| [`tools.doom_pwad`](modules/tools.doom_pwad.py.md) | doom_pwad.py - grid map to vanilla Doom PWAD writer and checker. | 2 | 20 | 100.0% |
| [`tools.extract_shell`](modules/tools.extract_shell.py.md) | tools/extract_shell.py -- Plan for Phase 6.1 shell extraction. | 0 | 0 | 100.0% |
| [`tools.gdb_repro`](modules/tools.gdb_repro.py.md) | gdb_repro.py — drive a graphics-program sequence under the GDB stub. | 0 | 2 | 33.3% |
| [`tools.gen_desktop_pngs`](modules/tools.gen_desktop_pngs.py.md) | gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs. | 0 | 2 | 33.3% |
| [`tools.gen_icons`](modules/tools.gen_icons.py.md) | gen_icons.py -- generate 32x32 RGBA PNG icon files for the MiniOS desktop. | 0 | 3 | 50.0% |
| [`tools.gen_minifs`](modules/tools.gen_minifs.py.md) | Generate minifs.c for MiniOS. | 0 | 0 | 100.0% |
| [`tools.gen_zip_fixtures`](modules/tools.gen_zip_fixtures.py.md) | gen_zip_fixtures.py -- generate the zip test fixtures shipped on the ramdisk. | 0 | 2 | 66.7% |
| [`tools/install.sh`](modules/tools.install.sh.md) |  | 0 | 0 | 0.0% |
| [`tools.kernel_feature_survey`](modules/tools.kernel_feature_survey.py.md) | kernel_feature_survey.py - verify which C features the MiniOS kernel needs. | 1 | 7 | 100.0% |
| [`tools/lisp_scoped.sh`](modules/tools.lisp_scoped.sh.md) | Docstring: Scoped Lisp validation for the MiniOS interpreter contract. | 0 | 5 | 16.7% |
| [`tools/make_usb.sh`](modules/tools.make_usb.sh.md) | Build the MiniOS bootable USB image and optionally write it to a device. | 0 | 2 | 33.3% |
| [`tools.minifs_dump`](modules/tools.minifs_dump.py.md) | minifs_dump.py - Dump/inspect a MiniFS filesystem image. | 1 | 10 | 8.3% |
| [`tools.minifs_fsck`](modules/tools.minifs_fsck.py.md) | minifs_fsck.py - Check MiniFS filesystem consistency. | 1 | 16 | 16.7% |
| [`tools.minifs_saves`](modules/tools.minifs_saves.py.md) | minifs_saves.py - preserve the guest's saves/ dir across image rebuilds. | 2 | 18 | 14.3% |
| [`tools.minios_cli`](modules/tools.minios_cli.py.md) | minios_cli.py — drive MiniOS through the MCP bridge, not by hand. | 1 | 5 | 14.3% |
| [`tools.minios_gui`](modules/tools.minios_gui.py.md) | minios_gui.py — inject VGA-mode input and capture the framebuffer. | 1 | 7 | 11.1% |
| [`tools.minios_hyper`](modules/tools.minios_hyper.py.md) | minios_hyper.py -- host-side ring-minus-one debugger for MiniOS. | 7 | 37 | 66.7% |
| [`tools.mkcpyzip`](modules/tools.mkcpyzip.py.md) | mkcpyzip.py -- pack a CPython Lib tree into a zipimport stdlib. | 0 | 2 | 66.7% |
| [`tools.mkfs.minifs`](modules/tools.mkfs.minifs.py.md) | mkfs.minifs.py - Create a MiniFS filesystem image for MiniOS. | 1 | 21 | 17.4% |
| [`tools.mkpak1`](modules/tools.mkpak1.py.md) | Build baseq2/pak1.pak carrying the player model. | 0 | 1 | 50.0% |
| [`tools.mkramdisk`](modules/tools.mkramdisk.py.md) | Build a MiniOS ramdisk image from files in a directory tree. | 0 | 3 | 50.0% |
| [`tools/mkroots.sh`](modules/tools.mkroots.sh.md) | mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/. | 0 | 0 | 100.0% |
| [`tools.mkvocab`](modules/tools.mkvocab.py.md) | Build progs/topogpt3/vocab.bin from the GPT-2 encoder.json. | 0 | 2 | 100.0% |
| [`tools/mutate.sh`](modules/tools.mutate.sh.md) | Mutation testing for MiniOS. | 0 | 5 | 33.3% |
| [`tools.probe_compute_vga`](modules/tools.probe_compute_vga.py.md) | Docstring: VGA liveness probe during CPU-bound ring-3 compute. | 0 | 1 | 50.0% |
| [`tools.probe_minicraft`](modules/tools.probe_minicraft.py.md) | probe_minicraft.py -- numeric minicraft probe without any PNG. | 0 | 1 | 50.0% |
| [`tools.qga_client`](modules/tools.qga_client.py.md) | Minimal QEMU guest agent client for MiniOS. | 0 | 4 | 40.0% |
| [`tools.repro_gui`](modules/tools.repro_gui.py.md) | repro_gui.py — reproduce the VGA/mouse state bug after ring-3 programs. | 1 | 6 | 12.5% |
| [`tools.sign_elf`](modules/tools.sign_elf.py.md) | Sign MiniOS user binaries with Ed25519 (development key). . | 1 | 22 | 100.0% |
| [`tools/wl_scoped.sh`](modules/tools.wl_scoped.sh.md) | Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor. | 0 | 4 | 20.0% |
| [`tools.wm_layout_sync`](modules/tools.wm_layout_sync.py.md) | Docstring: Synchronize the WM layout manifest from source truth. | 3 | 8 | 100.0% |
| [`tools/wm_scoped.sh`](modules/tools.wm_scoped.sh.md) | Docstring: Scoped WM validation for Alt-Tab and tile across all windows. | 0 | 2 | 33.3% |
