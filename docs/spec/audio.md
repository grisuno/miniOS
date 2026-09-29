# Audio: PC speaker, SB16, pcm2, Doom music

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### PC speaker audio (`pcspk.c` + Doom)
The kernel owns the QEMU PC speaker through two syscalls: 209 `pcspk_init`
and 210 `pcspk_tone(freq)` (0 = off). The driver programs PIT channel 2
(ports 0x42/0x43, divisor `1193182/freq`) and gates the speaker on/off via
bit 1 of port 0x61; frequencies are clamped to the audible 20..20000 Hz
range and no other sound device is emulated. QEMU does **not** route the
PC speaker to the host with a bare `-audiodev`: the machine option
`-machine pc,pcspk-audiodev=<id>` is required in addition. The Makefile's
`QEMU_AUDIO` carries both (`-audiodev pa,id=snd0 -machine pc,pcspk-audiodev=snd0`).

Doom (a ring-3 Linux ELF) reaches the speaker through `i_minios_sound.c`,
selected when `snd_sfxdevice == SNDDEVICE_PCSPEAKER` and `I_InitSound(true)`
runs (it was once commented out in `d_main.c`, which left `sound_module`
NULL and every `I_StartSound` a silent no-op). Each DP lump is a PC-speaker
sequence: 2-byte big-endian priority, then pairs of (1-byte index into the
original Doom frequency table 178..2690 Hz, 1-byte duration in 70 Hz
ticks); index 0 ends the sequence. `PCSPK_StartSound` loads the lump and
starts a tone immediately, and `PCSPK_Update` (per game tic) advances
through the note sequence by elapsed time and programs the highest-priority
active channel, turning the speaker off when none remain. `S_UpdateSounds`
in `d_main.c` was re-enabled so `I_UpdateSound` actually runs each frame;
before that neither the sfx sequencer nor the music decoder was ever polled.

Doom uses pcm2 as its primary sink (standard audio mode contract) for
music only: the MUS score streams as polyphonic 8-bit PCM while sfx stay
muted, because effect tones mixed into the music read as a second melody;
on the legacy speaker (no SB16) sfx and music share the single channel as
before, so nothing is ever silent. `S_Shutdown` (via
`I_AtExit`, plus explicitly on the `mini_autoframes` exit path which
bypasses `I_Quit`) releases pcm2 so the next program can open it; the
kernel also reclaims a dead owner's device on the next open.

The level music is played by a `music_pcspeaker_module` in
`i_minios_sound.c`, selected when `snd_musicdevice == SNDDEVICE_PCSPEAKER`.
It decodes each MUS lump (Doom's music format, `D_E1M1` etc.) straight from
its interleaved event stream at the stock 140 ticks/sec: a block of events
at one tick ends when a descriptor byte's bit 7 is set, then a
variable-length delta leads to the next block. On pcm2 (standard mode) the
score plays as written, polyphonically: every tick renders all its sounding
voices at once (each with a persistent phase, normalized to a constant
level), plus a short noise burst for percussion hits on channel 15, with
tick-exact timing that never drifts. SFX stay muted on pcm2 (effect tones
ruined the melody); they sound on the legacy speaker fallback. Timing and
rendering share one clock (`audio_last_ms`), so nothing ever
double-renders an interval. When pcm2 is unavailable the same decoder falls
back to the single-speaker arpeggio: the lowest sounding bass note (below
`MUS_BASS_LINE_MIDI`, midi 43) becomes a pedal held for `MUS_BASS_HOLD_MS`
like the NES triangle voice, and only the highest `MUS_ARP_MAX` melody
notes are fast-arpeggiated round-robin at `MUS_ARP_SLOT_MS` (7 ms) each by
busy-waiting on `sys_time` (the percussion channel 15 is dropped in the
decoder).  Capping the arpeggio to the top few melody notes keeps dense
arrangements from degrading into mud — every active voice is no longer
chopped at equal length, and the bass keeps its foundation instead of
getting a fraction of the cycle.  At that cadence the ear integrates the
rapid cycle into a single strummed chord instead of hearing one voice, the
classic chiptune broke-chord sound. A handle is allocated in
`MUS_RegisterSong` (validated against the `MUS\x1a`
magic and the 12-byte header), `MUS_PlaySong` resets the cursor, active
notes and chord, `MUS_Poll` advances by elapsed ms and loops by rewinding
to the score start, and `MUS_StopSong` silences the speaker. The
`music_sdl_module`/`music_opl_module` stubs stay
all-zero. Shutdown reports `mus: maxvoices=N drums=M` plus `mus: polyphonic`
when more than one voice sounded together (BDD-pinned), so an arpeggio
regression reads as `maxvoices=1`.

### Sound Blaster 16 DMA audio (`sb16.c` + piano)
The kernel owns a real PCM audio device (QEMU `-device sb16`, 8-bit mono at
`SB16_PCM_RATE` 22050 Hz through the 8237 DMA controller on channel 1) and
exposes two sinks: `sb16_tone` (square wave, the `sys_tone` sink) and
`sb16_pcm_open`/`sb16_pcm_submit` (raw 8-bit PCM streamed from a ring-3
renderer, the piano's FM synth path). The rate is programmed with the DSP 0x41
command (two frequency bytes, low then high) so the clock matches the declared
`SB16_PCM_RATE` exactly.

- **pcm2 is the standard audio mode for ring-3 programs.** Every audio
  consumer (piano, Quake 2, DOOM, Pokémon) opens pcm2 (syscalls
  246/247/248: 8-bit mono 22050 Hz single-cycle DMA, ~23 ms latency) and
  falls back to the legacy path only when `pcm2_open` refuses (no SB16).
  The legacy SB16 ring (221/222, ~650 ms) and the PC speaker (209/210)
  stay as the fallback sinks so nothing goes silent on a deviceless
  machine; they are never the primary path for anything new. Do not add a
  third engine: one low-latency path plus the two legacy fallbacks is the
  whole audio surface.

- **DMA completion is driven by an interrupt AND a timer watchdog.** QEMU
  raises the SB16 completion IRQ (vector 37) only once its audio engine has
  consumed the transferred block; a host backend that never consumes (a
  suspended PulseAudio stream, a full buffer, or the `none` backend) therefore
  never raises it. A driver that re-arms solely from the IRQ wedges: the
  7-slot ring fills once and every later submit is refused, deadening the
  audio. `sb16_poll`, called from the 100 Hz timer ISR, re-arms on elapsed
  guest time as a fallback, and both paths funnel through `sb16_arm`, which
  gates re-arms to at most one per `SB16_ARM_PERIOD_MS` so the two are
  idempotent and a fast backend can never drive an interrupt storm.
- **Ring accounting is guest-side**: `pcm_free` is incremented when a queued
  slot is armed, independent of whether QEMU actually consumed it, so the
  guest-side ring always drains at the declared rate.
- **Idle ticks never mix**: `sb16_pump` returns before `sb16_mix_all` when
  no stream holds data (the arm path already plays the permanent silence
  slot on underrun), so a silent machine pays no 100 Hz mixing tax; and the
  mixer walks each stream with a wrapping index instead of a per-sample
  modulo, the same sample sequence with no division in the hot loop.
- **Observability**: the `sb16` builtin prints presence, mode, ring free
  count and the driver counters (`irq_arms`, `poll_arms`, `submits`, `drops`),
  so ring health is testable over the serial console without ears.
- The DMA buffers live in the reserved identity-mapped low region
  `[0x90000, 0x94000)` (8 slots of 2 KB, the last is the permanent silence
  buffer); no kernel-static array is used because under KASLR the kernel
  image's physical base can land above the 16 MB the 8237 can reach.
- **Piano pacing**: `progs/piano/piano.c` renders through the pcm2 path
  below (NONBLOCK writes of what each frame synthesizes, capped at
  `PIANO_FRAME_MS` 80 ms; debt past 500 ms is dropped, never repaid, so
  a stall cannot overproduce into a ring the engine already padded).
  A short write is held and retried next frame (`sb_flush`); the hold
  buffer fits a whole `MAX_AUDIO_MS` (600 ms) stall, and once it fills
  the synth idles instead of burning OPL3 time into a dead backend.
  Video runs dirty-or-500 ms through the indexed present (id 1); audio
  runs every iteration. The frame loop yields (`SYS_SCHED_YIELD`)
  instead of busy-spinning, so input polling stays fresh while audio
  renders.
- **Piano keyboard**: three octaves C4..B6 (middle-C base, 21 white + 15
  black keys fitting the 800 px window) clickable with velocity, plus a
  PC-keyboard MIDI layer Fruity Loops style fed by a raw-scancode hook in
  `nuklear_minios` (`nk_set_scancode_hook`): A-row whites, Q-row blacks,
  Z-row bass whites, digits aliasing the upper blacks, comma/period for
  octave shift. Each scancode owns its voice (`sc_chan`) so chords and
  melodies are playable; the pressed mouse key is latched so releasing
  off-key cannot stick a voice.
- **Low-latency path pcm2 (`pcm2.h` + `drivers/pcm2.c`, syscalls
  246/247/248)**: the standard SB16 engine for ring-3 audio (piano, Quake 2,
  DOOM, Pokémon; see the standard-mode contract above). The
  legacy ring above is ~650 ms of buffering re-armed from a watchdog:
  right for Doom music, wrong for a piano (every 100 ms of buffer reads
  as input lag, and a blind re-arm replays stale audio). pcm2 programs
  the DSP once (rate 0x41 high-then-low like the legacy path, speaker
  on) and arms one 512 B single-cycle block at a time at
  `BOOT_PCM2_DMA_ADDR` (0x94000, never crossing a 64 KB page) with DMA
  mode 0x49 (single-cycle read) and DSP 0x14 (single-cycle 8-bit). IRQ5
  (acked at 0x22E) retires the block and re-arms the next at once (the
  audible gap is the ISR), with a `ktime_ms` poll on the 100 Hz audio
  tick as the null-backend fallback; the heap ring (`pcm_ring.h`, 1024 B:
  overrun counts drops, underrun pads 0x80 silence and counts, never
  stalls) feeds both. Steady latency is about one block (~23 ms). Writes
  block (`PROC_BLOCKED` + `schedule`, predicate and sleep sharing one
  irqsave lock, futex discipline) unless opened `NONBLOCK`; the device
  is exclusive open (OSS-style) with mutual `-EBUSY` against the
  legacy engine in both directions, and a killed owner is released
  with `-EPIPE` instead of stranding a writer. The `sb16` builtin
  reports the pcm2 counters beside the legacy ones; `make test-pcm`
  pins the ring on the host and the `pcm2` BDD slice pins
  open/stream/release under the null backend.
- **HAZARD — never program the SB16 in auto-init DMA mode.** This is the
  bug that froze the whole machine the moment the piano opened the audio
  device, and the reason `pcm2.c` uses single-cycle transfers. Mechanism,
  measured with the QEMU debug log and the gdb stub, not assumed: auto-init
  (`DSP 0xC6` mode 0, plus 8237 mode `0x59`) leaves the DMA controller
  looping without any guest re-arm. Under QEMU the emulated 8237 ends up
  holding the ISA DMA engine busy, and the IDE controller that shares that
  emulated bus stops advancing: its status register latches `0x80`
  (`IDE_STATUS_BSY`) with neither DRQ nor ERR, forever. `ide_wait_drq`
  (`drivers/ide.c`) is a bounded poll but the bound is `IDE_TIMEOUT` =
  1,000,000 spins, and MiniFS runs the PIO under `fs_lock` (irqsave), so
  the CPU spins those million iterations with `IF=0`: no timer, no mouse,
  no shell — about ten minutes per read, which reads as a hard hang. The
  first pcm2 open is enough because the very next thing the piano does is
  read its theme file from MiniFS. Single-cycle DMA never does this: one
  512 B block is armed, its terminal count raises IRQ5, and the driver
  re-arms (`0x49`/`0x14`, the same shape the legacy engine has always
  used). Rule for every future SB16/DMA consumer: arm one transfer at a
  time with a terminal-count IRQ and a timer-poll fallback; auto-init and
  any "program once, let the hardware loop" DMA scheme are forbidden.
  Diagnosis recipe for a freeze with no serial output: boot with
  `-d int,cpu_reset,guest_errors -D <log>` and `-s`, drive to the freeze,
  then `gdb -batch -ex 'file kernel.elf' -ex 'target remote :1234'
  -ex 'thread apply all bt'`. A log that stops on a vector-32 (or 37)
  delivery and a backtrace landing in `ide_wait_drq` is this hazard; a
  `status` of `0x80` with `eflags IF=0` confirms the wedged-controller
  spin. Clicking the dock icon over QEMU with a serial-idle watchdog
  reproduced it deterministically (TCG, `-smp 2`, SB16 attached, either
  audio backend, with or without PulseAudio).
