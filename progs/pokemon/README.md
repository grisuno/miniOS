# Pokémon on MiniOS (gb-recompiled port)

Runs a recompiled Game Boy / Game Boy Color game as a ring-3 MiniOS
program, with a clickable desktop icon. Same contract as the DOOM and
Quake 2 ports: host clang, statically-linked ELF, MiniOS syscalls
instead of SDL2.

This directory holds the MiniOS-owned files (they work with **any**
gb-recompiled generated project, no per-game patches):

- `platform_minios.c` — implements the `gb_platform_*` interface with
  MiniOS syscalls: 800×360 NK backbuffer (GB at exact 2x), PS/2
  keyboard, PC speaker audio, timing.
- `Makefile.minios` — static build of a generated project + runtime.
- `minios_stubs/` — minimal `SDL.h` so the `GB_HAS_SDL2`-guarded
  prototypes stay visible without SDL2.
- `fetch.sh` — clones the upstream tool (recompiler + runtime).

## New-user flow

Upstream ships no ROMs and no pre-generated game code, so a game
project is generated locally from a ROM image you legally own:

```sh
cd progs/pokemon
./fetch.sh                    # clone https://github.com/arcanite24/gb-recompiled → upstream/
# build gbrecomp per upstream README (cmake, ninja, SDL2 dev files), then:
upstream/build/bin/gbrecomp /path/to/your/game.gbc -o game/
```

Then build the MiniOS image from the repository root:

```sh
make os.img                     # POKEMON_DIR defaults to progs/pokemon/game
```

The build auto-applies two tiny additive patches to pristine
generated trees (`main-minios.patch`: `--debug` flag,
`runtime-audio-voice.patch`: speaker accessor), marker-gated and
loud on failure. SDL builds are untouched by both.

With a project elsewhere: `make POKEMON_DIR=/path/to/game os.img`.
Without any project the pokemon build is skipped with a hint
(`make` otherwise works normally, offline included).

`make run` boots the image; click the **Pokemon** desktop icon
(or run `pokemon.elf` from the shell).

## Controls

Arrows = D-pad, Z = A, X = B, Enter = Start, Backspace = Select.

Savestates: F5 or Ctrl+S = save, F8 or Ctrl+L = load.
SPACE (hold) = momentary fast-forward; Ctrl+Space latches it on,
Ctrl+Shift+Space releases it. Turbo means no vsync wait, muted audio
and frameskip 29 (1 of every 30 frames uploaded).

FILE menu (top bar, no game pixels hidden): click FILE or press Esc,
then click or use Up/Down + Enter. Items: Save State, Load State,
Enable/Disable frameskip (same sticky turbo as Ctrl+Space), Quit
(flushes battery and exits to the shell). OSD confirmations appear
bottom-left for 3 s. The menu never pauses the game.

## Game flags

`pokemon.elf --debug` enables the serial heartbeat (off by default;
serial prints cost frame rate). All other upstream runtime flags
(`--limit-frames`, `--input`, `--dump-frames`, …) work unchanged.

## Audio

PC speaker, DOOM-style: per-channel note frequencies come from
`gb_audio_voice()` (a small additive runtime accessor over live
channel state) once per frame and play as bass pedal + melody
arpeggio (noise drums are dropped, like DOOM drops percussion).
A PCM energy gate keeps envelopes, fades and silence honest. Tune
`MINIOS_AUDIO_SILENCE_E` / `MINIOS_AUDIO_{MIN,MAX}_HZ` in
`platform_minios.c` if music sounds wrong on your speaker.

## Saves

Battery saves and RTC data persist on MiniFS (`saves/<save-id>.sav`,
`saves/<save-id>.rtc`) and survive reboot — unlike ramdisk files.
The full-emulator savestate (`saves/<save-id>.state`, F5/Ctrl+S to
save, F8/Ctrl+L to load) lives on MiniFS too, so it survives reboot
and poweroff: save, `poweroff`, boot again, load, and the game
resumes where it was. Saving a savestate also flushes battery/RTC
first so both agree. The battery files auto-load on next boot; the
`.state` file is manual (load key). `saves/` is used deliberately:
`bin/` exists on the ramdisk (`bin/cp`, `bin/minigcc.elf`), so a
`bin/` save would land on volatile ramdisk and vanish on reboot.
Writes are direct (no atomic temp+rename yet: MiniOS has no
`rename` syscall). If the in-game save says it saved but the file
is missing after reboot, check `minifs_dump.py minifs.bin`.
Rebuilding is safe: `make minifs.bin` / `make os.img` extract the
live `saves/` out of the previous `os.img` (`tools/minifs_saves.py`)
and pack it back into the fresh image, so saves survive rebuilds
too. Only `make clean` (which deletes the images) loses them.

## Known limits

- The NK desktop window title says "Nuklear" (kernel-side label,
  cosmetic).
- The NK desktop window title says "Nuklear" (kernel-side label,
  cosmetic).
- Under QEMU-TCG (no KVM) the frame rate is low; use `run-kvm`
  when available.
