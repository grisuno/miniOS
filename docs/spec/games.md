# Games on MiniOS: DOOM, Quake 2, Minicraft, Pokemon

Ring-3 Linux ports that run inside MiniOS unmodified, under one contract:
host compiler, `gcc -static -no-pie`, MiniOS syscalls instead of SDL, and
the kernel's shared back-buffer for presentation. The window manager,
the graphics contract and the audio paths are specified in
`docs/spec/desktop.md` and `docs/spec/audio.md`; this file owns the ports
themselves.

### Port contract

- **Build**: host toolchain, `-static -no-pie`, ring-3 `ET_EXEC`, Linux
  syscall ABI with MiniOS syscalls replacing SDL/DirectX. No MiniOS source
  is compiled by miniGCC: every engine here is built by the host compiler
  and runs unmodified inside the guest.
- **Shipping**: the ELFs live on MiniFS, never on the ramdisk (the kernel
  image must stay small). `tools/mkfs.minifs.py` writes every file argument
  to the MiniFS **root** by basename and every directory argument as a
  directory, so the shipped names are `doomgeneric.elf`, `DOOM1.WAD`,
  `quake2generic.elf`, `pokemon.elf`, `minicraft.elf` plus the bare alias
  `minicraft`, and `baseq2/` holds `pak0.pak` and `pak1.pak`. Verify with
  `python3 tools/minifs_dump.py minifs.bin`.
- **Presentation**: the guest writes a 320x200 paletted frame into the
  kernel back-buffer at `MINIOS_DOOM_BACKBUF_ADDR` (0x0B000000) and calls
  `MINIOS_SYS_GFX_PRESENT` (237) with buffer id `MINIOS_GFX_BUF_GAME` (0);
  `SYS_DOOM_FRAME` (211) survives as the compat alias
  (`MINIOS_SYS_FRAMEBUFFER_COMMIT`). True fullscreen is
  `MINIOS_SYS_GFX_ZOOM` (242) value 2. The window, title, zoom, focus and
  desktop-mode contract belongs to `docs/spec/desktop.md`.
- **Launch paths**: `run doomgeneric.elf`, `run quake2generic.elf +set
  basedir .`, `run minicraft.elf`, `run pokemon.elf`.
- **Desktop entries**: `progs/etc/shortcuts` (one `name|icon|command` per
  line) carries DOOM, Quake 2, Pokemon and Minicraft. The icons are custom
  art converted by `tools/gen_desktop_pngs.py` from `images/*.png`;
  `tools/gen_icons.py` owns only `terminal.png`. Icon decoding and the
  dock are specified in `docs/spec/desktop.md`.
- **Host addons**: `addons/doom.yaml`, `addons/quake2.yaml`,
  `addons/minicraft.yaml` (Pokemon has none: its ELF needs a ROM the
  repository must not carry).
- **Address rule**: every layout constant comes from `progs/minios_abi.h`.
  A port never hardcodes a window, back-buffer or syscall number.

### DOOM (doomgeneric)

Vendored in-repo: the engine sources under `progs/doomgeneric/`, the
platform layer `progs/doomgeneric/doomgeneric_minios.c` and the sound
module `progs/doomgeneric/i_minios_sound.c`. Build with `make
progs/bin/doomgeneric.elf`.

- **IWAD**: the shareware `doom1.wad` is not committed. The Makefile
  fetches it on demand (`DOOM1_WAD_URL`, archive.org), verifies
  `DOOM1_WAD_MD5` and packs it as `DOOM1.WAD`, the exact case-sensitive
  name the IWAD loader opens (`progs/doomgeneric/d_iwad.c:37`). A missing
  IWAD aborts the startup, so the fetch is a build prerequisite, not an
  optional extra.
- **Syscalls**: `MINIOS_SYS_TIME` (254), `MINIOS_SYS_KBD` (205),
  `MINIOS_SYS_KBD_RAW` (207), `MINIOS_SYS_PALETTE` (206),
  `MINIOS_SYS_VGA_MODE` (208), `MINIOS_SYS_PCSPK_TONE` (210),
  `MINIOS_SYS_GFX_PRESENT` (237), `MINIOS_SYS_GFX_ZOOM` (242) and the
  pcm2 pair 246/247/248. The port calls `vga_mode(1)` at startup so the
  kernel stops touching VGA text hardware while the game owns the display.
- **Windowing**: the game asks for true fullscreen at startup
  (`MINIOS_GFX_ZOOM_FULLSCREEN`); `mini_windowed` on the command line, or
  a headless `mini_autoframes <n>` run, keeps the historical titled 1:1
  window with the shell visible around it (see `docs/spec/desktop.md`,
  "Graphics view contract").
- **Headless proof**: `mini_autoframes <n>` counts composited frames and
  exits, so the BDD suite can assert that `gfx frames` climbed.

| Key | Action |
|-----|--------|
| WASD | move |
| Ctrl | fire |
| Space | use / open |
| Arrow keys | turn / strafe |
| 1-7 | weapon select |
| Shift | run |
| Esc | menu |

- **Sound effects**: the PC speaker carries them through the original Doom
  PC-speaker frequency table (`dp_freq_table`, 256 entries). A DP sound
  lump is 2 bytes of priority, then a 1-byte frequency index and a 1-byte
  duration in 14 ms ticks (about 70 Hz), so `i_minios_sound.c` maps it to
  `dp_freq_table[index]` and ends the note after `duration * 14` ms.
  Four channels are mixed (`PCSPK_CHANNELS` 4) and, when several are
  active at once, the lump priority field decides which one is sounded.
- **Music**: `music_pcspeaker_module` decodes the MUS lump (the
  interleaved event stream at the stock 140 ticks/sec, `MUS_TICKS_PER_SEC`
  140) with NES-style pseudo-polyphony. The lowest sounding bass note
  (below MIDI 43) becomes a sustained 28 ms pedal, the top 4 melody notes
  arpeggiate round-robin at 7 ms per slot, and the percussion channel (15)
  is dropped. The module is selected when `snd_musicdevice` is the PC
  speaker, and `S_UpdateSounds` is polled every frame
  (`progs/doomgeneric/d_main.c:466`) so the sfx sequencer and the music
  decoder both advance; before that they were never polled and the game
  was mute.
- **Host wiring**: the PC speaker only reaches the emulator with
  `-machine pc,pcspk-audiodev=<id>` next to `-audiodev`; the Makefile's
  `QEMU_AUDIO` carries both. A bare `-audiodev` routes nothing and the
  beeps are silent. The driver contract is `docs/spec/audio.md`.

### Quake 2 (quake2generic)

The upstream engine is a git-ignored checkout nested at
`progs/quake2generic/quake2generic`; the MiniOS platform layer
`progs/quake2generic/q2generic_minios.c` and the sound backend
`progs/quake2generic/snddma_minios.c` live beside it. The engine itself,
its renderer, its audio mixer geometry and its BDD scenarios are specified
in `docs/spec/apps.md` ("Quake 2"); this section owns the port.

- **Build**: `make progs/bin/quake2generic.elf`. The target is skipped
  with a hint when the upstream checkout is absent (`Q2G_AVAILABLE` gates
  on `client/cl_main.c`), so a fresh clone still builds offline.
- **Run**: `run quake2generic.elf +set basedir .`. The engine searches
  `basedir/baseq2/pak0.pak`, and `+set basedir .` points it at the MiniFS
  root where the `baseq2/` directory lives.
- **Data**: `baseq2/pak0.pak` is not committed either. The Makefile
  fetches the pinned demo installer on demand (`Q2_DEMO_URL`, SHA1
  `5b4dedc59ceee306956a3e48a8bdf6dd33bc91ed`) and extracts the pak,
  verifying SHA1 `b86e8878a8e8706595ceebe88b3e6b4c1ba5bcab`; the recipe
  runs only when the file is absent. The pak in this tree is the full
  retail data set: 183,997,730 bytes, 3307 entries, covering base1..base3
  plus every campaign map (warehouse, installation, command, boss1/boss2,
  fact, hangar, jail, mine, power). The retail player model ships
  separately as `baseq2/pak1.pak`, built by `tools/mkpak1.py` from the
  tracked loose files under `progs/quake2generic/players/male/`
  (`tris.md2`, `grunt.pcx`, `weapon.md2`, `grunt_i.pcx`), because pak0
  omits the player model. No `pak2.pak` exists: the demo-map alias pak
  was removed once the full pak made it redundant.
- **Syscalls**: DOOM's set plus `MINIOS_SYS_MOUSE` (219) and
  `MINIOS_SYS_GFX_SET_TITLE` (223), which sets the window title to
  "Quake 2" (`SYS_Q2G_SET_TITLE` is the retired name of that number).
- **Sound is wired, not stubbed**: the engine mixes through the pcm2 DMA
  backend (`progs/quake2generic/snddma_minios.c`, syscalls 246/247/248)
  with a 16-bit mono 22050 Hz mixer downconverted to 8-bit on the way out;
  when pcm2 refuses to open the backend leaves `dma.buffer` NULL and the
  game runs silently instead of crashing. See `docs/spec/apps.md` ("Quake
  2 > Audio") and `docs/spec/audio.md`.

| Key | Action |
|-----|--------|
| WASD | move |
| Ctrl | fire |
| Space | use / open |
| Arrow keys | turn / strafe |
| Mouse | look |
| Shift | run |
| Esc | menu |

### Quake 2 bring-up: memory layout and the three kernel bugs

The retail pak forced the user window to grow, and the growth exposed
three bugs that only exist once a memory map moves. They are recorded here
as contracts, not as history: root cause, symptom, fix, invariant.

#### Layout (current)

| Element | Value | Source |
|---------|-------|--------|
| User window | 0x00400000 .. 0x0C000000 (192 MB) | `MINIOS_USER_LOAD_BASE` / `MINIOS_USER_LOAD_END` |
| Heap/mmap ceiling | 0x09000000 (144 MB, `USER_HEAP_CEIL`) | `headers/kernel.h` |
| Page-table zone | [0x10000, 0x70000), 384 KB | `PT_USER_TABLES_ADDR` / `PT_USER_TABLES_BYTES` |
| DOOM/Q2 back-buffer | 0x0B000000 (176 MB) | `MINIOS_DOOM_BACKBUF_ADDR` |
| Nuklear back-buffer | 0x0B600000, RGB at 0x0B700000 | `MINIOS_NK_BACKBUF_ADDR` |
| Kernel heap | 0x0C000000 + 448 MB -> 0x28000000 | `MINIOS_HEAP_BASE` / `MINIOS_HEAP_SIZE` |
| KASLR window | base 0x28000000, 64 slots x 2 MB | `KASLR_MIN_ADDR` / `KASLR_MAX_UNITS` |
| Guest RAM | `-m 1G` | `QEMU_MEM` (`tools/test_bdd.sh` mirrors `MEM=1G`) |
| MiniFS | 196608 blocks x 4096 = 768 MB | `MINIFS_BLOCKS` |

A 192 MB window needs 94 user page tables (one 4 KB table per 2 MB PD
slot) and the 384 KB zone holds 96; the boot check
`hi - lo + 1 > PT_USER_TABLES_BYTES / 0x1000`
(`kernel/mm/paging.c:55`) fails closed when the window outgrows the zone.
The graphics tail sits above the heap/mmap ceiling, so brk and mmap can
never reach the pages the kernel maps for rendering, and the KASLR base
equals the heap end (`_Static_assert` in `kernel.c:68`).

#### Bug 1: the syscall trampoline silently downgraded the game to ring 0

- **Root cause**: the entry decided how to return from the restored stack
  pointer against the window bounds, and the bound it compared against,
  `USER_WIN_HI`, was still 0x07400000 (116 MB) after the window grew to
  192 MB. A game stack sits at the top of the window, so every syscall saw
  `rsp >= USER_WIN_HI` and took the ring-0 return path.
- **Symptom**: the game ran at CPL0 for its whole life. The tell was the
  crash dump: `cs=8` (kernel) with a user stack pointer, a combination
  impossible for a real ring-3 fault.
- **Fix**: `USER_WIN_HI` corrected to 0x0C000000, and the decision moved
  to the caller RIP (`arch/x86/syscall_entry.S:225`): RSP is
  attacker-settable without faulting, while RIP is constrained to
  executable mappings, so an `RSP=0` spoof can no longer retain CPL0. The
  entry range-checks the pid and fails closed with `-EFAULT` before
  touching any per-pid state (`arch/x86/syscall_entry.S:104` and the
  `98:` fail-closed block at `arch/x86/syscall_entry.S:236`).
- **Invariant**: `SYSCALL_USER_WIN_HI == MINIOS_USER_LOAD_END`, pinned by
  `_Static_assert` in `kernel.c:66`. Any ring-3 program whose stack sits
  high in a grown window would otherwise silently lose its protection.

#### Bug 2: the LAPIC page directory erased the user window's page tables

- **Root cause**: every boot `smp_init` parks a dedicated page directory
  for the local APIC and zeroes it. It was parked at physical 0x60000, a
  "dead boot staging buffer" address, and it stopped being dead when the
  page-table zone grew: the index-82 user page table (the slot that maps
  roughly 165 MB of the window) lives at exactly 0x60000.
- **Symptom**: on every boot `smp_init` wrote zeros over the very page
  tables that made the game's 165 MB usable, and the game faulted "page
  not present" the moment its mmap reached that region. A page-table walk
  at the fault showed `pte=0` while the boot-time dump showed the page
  present.
- **Fix**: `LAPIC_PD_ADDR` moved to 0x70000, just above the page-table
  zone and below the syscall kernel stack (0x88000) (`smp.c:70`).
- **Invariant**: the page-table zone is dedicated; nothing else may claim
  a page inside it. A fixed low-memory address that was "dead" stays dead
  only until the map grows into it.

#### Bug 3: the back-buffers were mapped from an unaligned heap pointer

- **Root cause**: x86 masks a PTE's low 12 bits into flags, so mapping a
  16-byte-aligned `kmalloc` pointer silently drops the offset: the first
  mapped page starts at `buf & ~0xFFF`, up to 4095 bytes *before* the
  buffer.
- **Symptom**: a guest rendering its whole frame to the mapped address
  overwrote the heap chunk in front of the buffer; when that chunk was a
  live `KFILE` the next seek read pixel data as a pointer (`kfile: corrupt
  handle`, `kfree: wild pointer`, then an unrecoverable `#GP`). It only
  surfaced through `SYS_SPAWN`, after a few spawned programs, because that
  is when the chunk in front of the buffer holds a live handle: DoomEdit's
  Run button and the file browser opening a text file in vedit reproduced
  it every time, while the same binaries run from the shell did not.
- **Fix**: `mm_page_aligned_alloc` over-allocates one page and rounds the
  base up (`kmalloc_aligned`, 0x1000), and the boot asserts
  `phys & 0xFFF == 0` for each buffer
  (`kernel/mm/paging.c:32`, `kernel/mm/paging.c:120`).
- **Invariant**: every kernel-heap buffer mapped into the user window is
  page aligned; the DOOM, Nuklear and Nuklear-RGB back-buffers are mapped
  one PTE at a time and the alignment assert is the gate.

#### Regression that taught the rule

After Quake worked, DOOM showed a black window while the game ran fine
(audio and menu still responded). Quake and DOOM share the back-buffer
infrastructure, so the mapping was not the problem: the *address DOOM
wrote to* was. The kernel and Quake had moved to 0x0B000000 while DOOM's
platform layer still rendered into the old 0x7C00000, so the kernel
composited an empty buffer. The fix was one constant in
`doomgeneric_minios.c`. Every consumer of a moved address has to move
together; the address itself lives once in `progs/minios_abi.h`.

#### Invariant

A window sized for the biggest ring-3 program, a page-table zone nothing
else may touch, a back-buffer above the mmap ceiling, a KASLR range above
the heap, and RAM and a filesystem large enough for the payload are one
layout, not independent tuning knobs. Changing any of them means
re-checking every fixed low-memory address that assumed it was alone.

### Minicraft (voxel walker)

One file: `progs/minicraft/minicraft.c`, built by host gcc
(`-static -no-pie -std=c99 -O2`) into `minicraft.elf`. The ELF, the bare
alias `minicraft` and the source `minicraft.c` all ship on MiniFS, so the
game can be rebuilt inside the OS with miniGCC. Host addon:
`addons/minicraft.yaml`.

- **Rendering**: 64x64x32 block world in 16x16 chunks loaded in a radius
  of 3, drawn by a per-pixel DDA voxel raycaster (Amanatides and Woo)
  with integer traversal, a 60-degree view and a 128-step budget. The
  frame goes into `MINIOS_DOOM_BACKBUF_ADDR` and is presented with
  `MINIOS_SYS_GFX_PRESENT` / `MINIOS_GFX_BUF_GAME`, exactly like DOOM.
  Face shading plus exponential distance fog toward the sky, with an
  ordered Bayer dither because the buffer is palette-indexed and cannot
  blend. Per-column skylight runs from 1.0 at the surface to 0.22 deep.
- **Physics**: AABB player with gravity, jump, swim, axis-separated
  collision and a one-block autostep; falling damage, drowning, hunger and
  20 HP.
- **Interaction**: left click breaks (reach 6 blocks, hold-to-break with
  a progress bar and a 1 s grace window), right click places the
  selected hotbar block. A placement is refused with `VACIO` when the
  inventory is empty and with `OCUPADO` when the block would intersect
  the player. Nine hotbar slots hold a block inventory.
- **Mobs**: 5 pigs and 3 creepers by default (100 maximum). Creepers
  sense the player in 3D within 12 blocks with a vertical gate of 4, fuse
  on contact and blast with radius 2, and can be defused past radius 3.5.
- **Day/night**: below `MC_NIGHT_LIGHT` (0.35) the pigs chase at 2.2
  instead of 1.6 and the creepers at 2.4 instead of 2.0, and pigs hit
  twice as hard. Dead mobs come back after
  `MC_RESPAWN_MS` (10 s); at night dead creepers regenerate after
  `MC_CREEP_NIGHT_MS` (3 s), so the dark stays dangerous, while by day
  dead pigs regenerate after `MC_PIG_DAY_MS` (3 s), so there is always
  pork to hunt and heal with.
- **Goal chain** (shown on the HUD): `G:4 WOOD` -> `G:16 PLANKS(K)` ->
  `G:PICK(J)` -> `G:1 PORK` -> `G:PLACE BED` -> `G:DONE`. The wood-10
  milestone prints `minicraft: GOAL firewood x10 DONE` on the serial
  console and `GOAL DONE` on the HUD.
- **HUD**: `X<n> Y<n> Z<n> F:<facing> <fps>`, the targeted block with its
  distance and the selected block with its count (`T:<block> <d>M
  S:<block>X<n>`), `HP`, hunger and pork, a `FLY` flag, and a `T:SALIR`
  hint when the player is buried below the surface column.
- **Camera invariant**: forward, right and up stay separate and pitch
  rotates in the forward/up plane, so looking up and down works at every
  yaw and W always walks toward the crosshair. The host selftest pins it
  ("W does not advance", "W strafes", "crosshair ray off +X").
- **Persistence**: the world, player state and inventory live in
  `/saves/minicraft.map` (magic 0x4D434631, version 4, CRC-seeded), with
  per-chunk files under `/saves/mc_c_<cx>_<cy>.bin`. The `saves/` area
  survives image rebuilds through `tools/minifs_saves.py`.
- **Syscalls**: `MINIOS_SYS_TIME` (254), `MINIOS_SYS_KBD` (205),
  `MINIOS_SYS_KBD_RAW` (207), `MINIOS_SYS_GETC_RAW` (236),
  `MINIOS_SYS_PALETTE` (206), `MINIOS_SYS_VGA_MODE` (208),
  `MINIOS_SYS_MOUSE` (219), `MINIOS_SYS_PCSPK_INIT` (209) /
  `MINIOS_SYS_PCSPK_TONE` (210), `MINIOS_SYS_GFX_PRESENT` (237),
  `MINIOS_SYS_GFX_SET_TITLE` (223), `MINIOS_SYS_GFX_ZOOM` (242) and the
  Linux `sched_yield` (24).

| Key | Action |
|-----|--------|
| WASD | move (W walks to the crosshair) |
| Mouse / arrow keys | look (pitch clamped to +-1.25 rad, about +-72 degrees) |
| Space | jump (fly mode: rise) |
| Shift | sprint x1.6 |
| F | toggle fly (Space up, C down) |
| 1-9 / wheel | hotbar select |
| Left click | break block (adds to inventory) |
| Right click | place selected block (spends inventory) |
| R | save world |
| T | rescue to surface |
| N | new world |
| C | level view |
| P | position report on serial |
| Esc | save and quit |

- **Headless proofs**: `minicraft --selftest` builds the world, renders
  one frame and checks the pixels, printing `minicraft: frame ok
  (320x200)`; `minicraft autoframes <n>` renders n frames with a slow yaw
  spin; `minicraft walkframes <n>` flies up and walks across chunks;
  `minicraft standframes <n>` stands still while mobs converge, explode
  and kill the player, then reports the deaths and saves. All of them
  climb `gfx frames` so the BDD suite observes real rendering.
  `make test-minicraft` runs the host selftest (movement, crosshair,
  pitch sweep). `tools/probe_minicraft.py` boots the image, runs the game
  in the background and asserts over the serial console that frames climb,
  that the upper and lower framebuffer bands read sky over ground, and
  that QMP keys move the player (arrow-key turn, fly toggle, Space rise,
  W walk, all confirmed through the `P` report).

### Pokemon (gb-recompiled port)

A game-agnostic gb-recompiled port: it runs any Game Boy / Game Boy Color
project generated by the upstream recompiler, with no per-game patch.

| File | Role |
|------|------|
| `progs/pokemon/platform_minios.c` | implements the `gb_platform_*` interface on MiniOS syscalls |
| `progs/pokemon/Makefile.minios` | static build of a generated project plus the runtime |
| `progs/pokemon/minios_stubs/SDL.h` | minimal `SDL.h` so `GB_HAS_SDL2`-guarded prototypes stay visible without SDL2 |
| `progs/pokemon/fetch.sh` | clones the upstream tool (recompiler plus runtime) into `upstream/` |
| `progs/pokemon/main-minios.patch` | additive, marker-gated: `--debug` flag in the generated `main.c` |
| `progs/pokemon/runtime-audio-voice.patch` | additive, marker-gated: `gb_audio_voice()` speaker accessor over live channel state |

- **Upstream**: `make pokemon-fetch` clones
  `https://github.com/arcanite24/gb-recompiled` into
  `progs/pokemon/upstream/`. Upstream ships no ROMs and no pre-generated
  game code, so the project is generated locally from a ROM image the
  user legally owns: build `gbrecomp` per its README (cmake, ninja, SDL2
  dev files) and run
  `upstream/build/bin/gbrecomp /path/to/game.gbc -o game/`.
- **Image build**: `make os.img` with `POKEMON_DIR` defaulting to
  `progs/pokemon/game`; `make POKEMON_DIR=/path/to/game os.img` for a
  project kept elsewhere; `make pokemon-clean` removes
  `progs/pokemon/build/`. Without a generated project the Pokemon build
  is skipped with a hint and the rest of `make` works normally, offline
  included. The ELF ships on MiniFS as `pokemon.elf`.
- **Video**: the GB screen (160x144) renders at exact 2x (320x288),
  centered in the 800x360 Nuklear back-buffer
  (`MINIOS_NK_BACKBUF_ADDR`), because the 320x200 DOOM buffer cannot fit a
  2x GB frame. The frame stays indexed at one byte per pixel (3-3-2)
  because under emulation memory traffic dominates; an RGB companion was
  tried and measured slower. The palette ramp is pushed once at init with
  `MINIOS_SYS_PALETTE` (206), frames are presented with
  `MINIOS_SYS_NK_FRAME` (220) and the title with
  `MINIOS_SYS_GFX_SET_TITLE` (223).
- **Side fringes**: the right strip always shows `/icons/pokemon.png`
  (`MPNG_RIGHT_PATH`); the left strip shows the first decodable entry of
  the shared candidate list in `progs/minios_png.h` (10 repo-root icon
  files, cgoblin excluded as too large). Both are integer-scaled and
  centered below the menu bar, and each side degrades to black when its
  file is missing or hostile. The helpers (3-3-2 quantize, nearest
  palette, scale, blit, bounded load) live once in `progs/minios_png.h`
  and are shared with the file browser preview; `make test-png` pins them
  (`tests/test_minios_png.c`).
- **Controls**: the driver consumes raw PS/2 Set 1 scancodes through
  `MINIOS_SYS_KBD_RAW` (207). Arrows are the D-pad, Z is A, X is B, Enter
  is Start, Backspace is Select. SPACE held is a momentary fast-forward,
  Ctrl+SPACE latches turbo and Ctrl+Shift+SPACE releases it (turbo means
  no vsync wait, muted audio and frameskip 29). F5 or Ctrl+S saves the
  savestate, F8 or Ctrl+L loads it. The FILE menu (click FILE or press
  Esc) offers Save State, Load State, Enable/Disable frameskip and Quit;
  the menu never pauses the game and shows 3 s OSD confirmations
  bottom-left.
- **Audio**: pcm2 is the primary path (syscalls 246/247/248). The runtime
  mixes 44100 Hz stereo PCM, but a syscall per sample (44k/s) would not
  survive emulation, so the per-sample callback only accumulates zero
  crossings and energy (integer ops, no syscalls) and stages 8-bit mono
  PCM, pushed with one NONBLOCK write per 512 B stage. Once per rendered
  frame the live APU voices are sampled through `gb_audio_voice()` (the
  enabled flag, DAC, live envelope volume and master switch; never the
  raw `io[]` mirror, whose channel bits are never set on that path) for
  the two square channels plus the wave channel, and played as one
  non-blocking tone round-robined across the bass and melody voices; the
  old blocking bass-pedal and arpeggio slots are gone. The noise channel
  is dropped, exactly like DOOM drops percussion. The PCM energy gate
  `MINIOS_AUDIO_SILENCE_E` (default 256 mean-abs) keeps envelopes, fades
  and silence honest so a decayed-but-on channel can never drone;
  passages with no tonal voice (noise SFX, sweep zaps) fall back to the
  raw mix estimate. The playable band is clamped by
  `MINIOS_AUDIO_MIN_HZ` (40) and `MINIOS_AUDIO_MAX_HZ` (12000); tune all
  three in `platform_minios.c` if music sounds wrong on a given speaker.
- **Saves**: battery RAM and RTC data persist on MiniFS as
  `saves/<save-id>.sav` and `saves/<save-id>.rtc`, and the full
  emulator savestate as `saves/<save-id>.state`. `saves/` is deliberate:
  `bin/` exists on the ramdisk (`bin/cp`, `bin/minigcc.elf`), so a `bin/`
  save would land on volatile ramdisk and vanish on reboot; the legacy
  `bin/<save-id>.*` path is still read as a fallback. Writes are direct
  (`fopen`/`fwrite`/`fclose`) because MiniOS has no `rename` syscall yet,
  so there is no atomic temp-plus-rename. Loads are size-checked: a
  short or overlong file fails closed and flags
  `persistence_load_failed`, never a partial SRAM image. The runtime
  only persists on clean exit, which QEMU poweroff never takes, so
  MiniOS flushes SRAM itself every 60 s (`MINIOS_AUTOSAVE_MS`), plus the
  on-demand savestates above.
- **Flags**: `pokemon.elf --debug` enables the serial heartbeat (off by
  default; serial prints cost frame rate) and arrives through
  `gb_platform_set_debug()`, wired by `main-minios.patch`. All other
  upstream runtime flags (`--limit-frames`, `--input`, `--dump-frames`)
  work unchanged. Do not reintroduce argv sniffing via `_dl_argv` in a
  constructor: this toolchain's loader internals do not expose a usable
  vector and the old scanner faulted at startup on unrelated storage.
- **Known limits**: the Nuklear desktop window title says "Nuklear" (a
  kernel-side label, cosmetic). Under QEMU-TCG without KVM the frame rate
  is low; prefer `make run-kvm`. The Pokemon ELF is about 97 MB in the
  current image (102,075,120 bytes) and `pak0.pak` is 184 MB, so the
  768 MB MiniFS is the binding constraint; the Makefile note near
  `MINIFS_BLOCKS` records the same budget.

