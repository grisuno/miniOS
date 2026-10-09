# Index (page 2 of 2)
Previous: [INDEX.md](INDEX.md)

| File | Purpose | Subsystem | Symbols | Used by |
|------|---------|-----------|---------|---------|
| `tests/test_sync.c` | Host-side unit test for the blocking sync primitives (kernel/sync.c). | tests | 6 | 0 |
| `tests/test_theme.c` | Docstring: host test for the shared Nuklear theme contract. | tests | 8 | 0 |
| `tests/test_tick.c` | Docstring: Host test for kernel/tick.c (make test-tick). | tests | 6 | 0 |
| `tests/test_usbblk.c` | Docstring: Host test for the USB mass-storage driver (make test-usbblk). | tests | 4 | 0 |
| `tests/test_usbhid.c` | Docstring: Host test for the USB HID driver (make test-usbhid). | tests | 5 | 0 |
| `tests/test_vedit_build.c` | Docstring: Host test for the vedit IDE build contract (make test-vedit). | tests | 16 | 0 |
| `tests/test_vma.c` | Host-side unit test for the VMA red-black tree (vma.c). | tests | 9 | 0 |
| `tests/test_vma_bench.c` | RB-tree vs sorted-list benchmark (boyscout gap #9). | tests | 6 | 0 |
| `tests/test_wl.c` | Host test for progs/wl/wl_mini.h (make test-wl). | tests | 2 | 0 |
| `tests/test_wm.c` | Docstring: Host test for wm_geom.h and wm_events.h (make test-wm). | tests | 2 | 0 |
| `tests/test_xhci.c` | Docstring: Host test for the xHCI controller driver (make test-xhci). | tests | 2 | 0 |
| `tls_test.c` | host-side tests for the kernel TLS stack. | root | 23 | 0 |
| `tools/abi_stamp.c` | Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator. | tools | 1 | 0 |
| `tools/boot_run.sh` | boot the MiniOS image in QEMU and drive the shell over the serial console with a list of... | tools | 0 | 0 |
| `tools/boot_wl.py` | boot the miniOS Wayland-mini desktop in one step. | tools | 15 | 0 |
| `tools/check_abi_numbers.py` | MiniOS syscall numbers vs Linux x86-64 truth. | tools | 4 | 0 |
| `tools/check_addons.py` | validate the MiniOS addon marketplace index. | tools | 2 | 0 |
| `tools/check_cohesion.py` | Architectural cohesion gate for MiniOS CI. | tools | 4 | 0 |
| `tools/check_complexity.py` | Kernel complexity gate for MiniOS CI. | tools | 3 | 0 |
| `tools/check_fork_stubs.py` | Fail-closed stub gate for unimplemented process syscalls.  vfork has no implementation in this... | tools | 4 | 0 |
| `tools/check_kb_sync.py` | Verify KNOWLEDGE_BASE.md is in sync with code. | tools | 2 | 0 |
| `tools/check_mutant_anchors.py` | Verify every mutate.sh mutant anchor matches its target file. | tools | 6 | 0 |
| `tools/check_spin_discipline.py` | Check spinlock call-site discipline across kernel C sources. | tools | 4 | 0 |
| `tools/check_surprising.py` | Detect surprising architectural connections. | tools | 5 | 0 |
| `tools/check_syscall_sanitize.py` | Scoped audit gate for syscall user-pointer sanitization. | tools | 8 | 0 |
| `tools/clip_bridge.py` | Host to MiniOS clipboard bridge plan builder. | tools | 5 | 0 |
| `tools/doom_pwad.py` | grid map to vanilla Doom PWAD writer and checker. | tools | 25 | 1 |
| `tools/extract_shell.py` | tools/extract_shell.py -- Plan for Phase 6.1 shell extraction. | tools | 0 | 0 |
| `tools/gdb_repro.py` | — drive a graphics-program sequence under the GDB stub. | tools | 4 | 0 |
| `tools/gen_desktop_pngs.py` | build MiniOS desktop art from user-supplied PNGs. | tools | 2 | 0 |
| `tools/gen_icons.py` | generate 32x32 RGBA PNG icon files for the MiniOS desktop. | tools | 3 | 0 |
| `tools/gen_minifs.py` | Generate minifs.c for MiniOS. | tools | 0 | 0 |
| `tools/gen_zip_fixtures.py` | generate the zip test fixtures shipped on the ramdisk. | tools | 2 | 0 |
| `tools/install.sh` | - | tools | 0 | 0 |
| `tools/kernel_feature_survey.py` | verify which C features the MiniOS kernel needs. | tools | 8 | 0 |
| `tools/lisp_scoped.sh` | Docstring: Scoped Lisp validation for the MiniOS interpreter contract. | tools | 5 | 0 |
| `tools/make_usb.sh` | Build the MiniOS bootable USB image and optionally write it to a device. | tools | 2 | 0 |
| `tools/minifs_dump.py` | Dump/inspect a MiniFS filesystem image. | tools | 12 | 0 |
| `tools/minifs_fsck.py` | Check MiniFS filesystem consistency. | tools | 19 | 0 |
| `tools/minifs_saves.py` | preserve the guest's saves/ dir across image rebuilds. | tools | 21 | 0 |
| `tools/minios_cli.py` | — drive MiniOS through the MCP bridge, not by hand. | tools | 6 | 0 |
| `tools/minios_gui.py` | — inject VGA-mode input and capture the framebuffer. | tools | 9 | 0 |
| `tools/minios_hyper.py` | host-side ring-minus-one debugger for MiniOS. | tools | 51 | 0 |
| `tools/mkfs.minifs.py` | Create a MiniFS filesystem image for MiniOS. | tools | 23 | 0 |
| `tools/mkpak1.py` | Build baseq2/pak1.pak carrying the player model. | tools | 1 | 0 |
| `tools/mkramdisk.py` | Build a MiniOS ramdisk image from files in a directory tree. | tools | 2 | 0 |
| `tools/mkroots.sh` | regenerate tls_roots.h from the DER files in tls_roots_src/. | tools | 0 | 0 |
| `tools/mkvocab.py` | Build progs/topogpt3/vocab.bin from the GPT-2 encoder.json. | tools | 2 | 0 |
| `tools/mutate.sh` | Mutation testing for MiniOS. | tools | 5 | 0 |
| `tools/probe_compute_vga.py` | Docstring: VGA liveness probe during CPU-bound ring-3 compute. | tools | 6 | 0 |
| `tools/probe_minicraft.py` | numeric minicraft probe without any PNG. | tools | 6 | 0 |
| `tools/qga_client.py` | Minimal QEMU guest agent client for MiniOS. | tools | 4 | 0 |
| `tools/qga_test.sh` | Quick standalone smoke test for the QEMU guest agent: boots os.img once with the agent socket... | tools | 3 | 0 |
| `tools/repro_gui.py` | — reproduce the VGA/mouse state bug after ring-3 programs. | tools | 10 | 0 |
| `tools/test_bdd.sh` | BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console... | tools | 14 | 0 |
| `tools/test_call_align.py` | verify stack alignment at call sites, both parities. | tools | 4 | 0 |
| `tools/test_codecs.sh` | exercise the lzss/lz4/aes command-pair tools inside the OS. | tools | 0 | 0 |
| `tools/test_gui_fashion.py` | GUI proof for the cursor/flicker/quit fixes. | tools | 18 | 0 |
| `tools/test_gui_freedom.py` | GUI proof that freedom-gui takes real input. | tools | 24 | 0 |
| `tools/test_gui_gfxview.py` | pixel + serial proof of the graphics view contract. | tools | 7 | 0 |
| `tools/test_gui_icon_cwd.py` | GUI proof that dock launches ignore shell cwd. | tools | 17 | 0 |
| `tools/test_gui_menu.py` | serial proof that the minicraft pause menu works. | tools | 1 | 0 |
| `tools/test_gui_wm.py` | GUI proof that graphics windows survive the WM. | tools | 17 | 3 |
| `tools/test_gui_zoom.py` | pixel proof that GFX_ZOOM doubles the game window. | tools | 1 | 0 |
| `tools/test_http_server.py` | - | tools | 3 | 0 |
| `tools/test_lisp.py` | Host test suite for the MiniOS Lisp interpreter. | tools | 16 | 0 |
| `tools/test_net_fixture.py` | host-side UDP and TCP echo fixture for lxnet. | tools | 5 | 0 |
| `tools/test_sb16.sh` | — targeted BDD harness for the SB16 audio path. | tools | 1 | 0 |
| `tools/tls_test.py` | Host-side TLS test driver for the MiniOS kernel TLS client. | tools | 16 | 0 |
| `tools/wl_scoped.sh` | Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor. | tools | 4 | 0 |
| `tools/wm_layout_sync.py` | Docstring: Synchronize the WM layout manifest from source truth. | tools | 17 | 0 |
| `tools/wm_scoped.sh` | Docstring: Scoped WM validation for Alt-Tab and tile across all windows. | tools | 2 | 0 |
| `vma.c` | vma_tree_find_containing: Docstring: Find the live node containing va (base <= va < base+len)... | root | 17 | 0 |

