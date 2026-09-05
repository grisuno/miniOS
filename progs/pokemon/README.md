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

With a project elsewhere: `make POKEMON_DIR=/path/to/game os.img`.
Without any project the pokemon build is skipped with a hint
(`make` otherwise works normally, offline included).

`make run` boots the image; click the **Pokemon** desktop icon
(or run `pokemon.elf` from the shell).

## Controls

Arrows = D-pad, Z = A, X = B, Enter = Start, Backspace = Select.

## Game flags

`pokemon.elf --debug` enables the serial heartbeat (off by default;
serial prints cost frame rate). All other upstream runtime flags
(`--limit-frames`, `--input`, `--dump-frames`, …) work unchanged.

## Audio

PC speaker, DOOM-style: per-channel note frequencies are read from
the APU registers once per frame and played as bass pedal + melody
arpeggio (noise drums are dropped, like DOOM drops percussion). A PCM
energy gate keeps envelopes, fades and silence honest. Tune
`MINIOS_AUDIO_SILENCE_E` / `MINIOS_AUDIO_{MIN,MAX}_HZ` in
`platform_minios.c` if music sounds wrong on your speaker.

## Known limits

- No battery saves / RTC persistence yet (kernel `statx` stub
  returns ENOENT; the ROM is embedded in the binary so the game
  boots and plays regardless).
- The NK desktop window title says "Nuklear" (kernel-side label,
  cosmetic).
- Under QEMU-TCG (no KVM) the frame rate is low; use `run-kvm`
  when available.
