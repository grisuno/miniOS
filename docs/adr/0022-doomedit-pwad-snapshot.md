# ADR-0022: Doom Map Editor with Immutable IWAD and PWAD Snapshots

## Status
Proposed. Spec-driven design for the Doom custom map pipeline.

## Context
I want to create Doom maps inside MiniOS, play them in the bundled
Doom port, and keep the shipped IWAD byte-identical across reboots.
The machine already runs Doom as a ring-3 static ELF on MiniFS, it
already preserves `saves/` across image rebuilds, and it already
ships a Nuklear node editor that proves the GUI pattern. What is
missing is a map authoring path: draw a level, export it, boot Doom
on it, and find the file still there after a reboot while the
original WAD is untouched.

I cloned `raycastlib` as a sibling checkout (`../raycastlib`, CC0,
single-header C89 fixed-point raycaster) for reference. I use it as
the editor live-preview renderer only, not as a Doom replacement.
The playable output is a vanilla PWAD that the existing Doom engine
loads at runtime.

## Key Finding
The shipped `Doom1.wad` is the shareware IWAD. The engine refuses
any `-file` PWAD under the shareware gamemode with `You cannot
-file with the shareware version`. This blocks the entire feature
unless I change one gate in the MiniOS-local Doom source
(`progs/doomgeneric/d_main.c`). The change is minimal and local: I
allow `-file` loading against the shareware IWAD while keeping the
registered-version lump check intact. The IWAD file itself stays
read-only; only the decision to abort changes. I treat this as a
documented port patch, not an upstream fix.

## Decision
I build three contracts, one file per contract.

### Contract 1: PWAD writer (`tools/doom_pwad.py`)
I write a single-file host tool that converts a grid map into a
vanilla PWAD replacing `E1M1`. The tool owns the full lump set the
engine requires: `THINGS`, `LINEDEFS`, `SIDEDEFS`, `VERTEXES`,
`SEGS`, `SSECTORS`, `NODES`, `SECTORS`, `REJECT`, `BLOCKMAP`.
Version 1 scope is one convex sector: every wall belongs to a
single closed room, so the BSP is trivial (one subsector, one node,
segs mirror the linedefs). This needs no external node builder and
I can verify it by hand. Multi-sector maps with a real BSP
compiler are an explicit Phase 2 and out of scope for version 1.
The tool fails closed on every malformed input: non-rectangular
grids, open perimeters, missing player start, missing exit switch
sector, oversized dimensions, and lump size arithmetic that would
overflow. All tunables live in one config class. No magic numbers,
no absolute paths.

### Contract 2: Map editor (`progs/doomedit/doomedit.c`)
I write a ring-3 Nuklear application built exactly like the
existing editor programs (host gcc `-static -no-pie`, ships on
MiniFS with a bare-name alias). The editor shows a tile grid
canvas, a wall brush, a player-start stamp, an exit-switch stamp,
and a small thing palette (imp, shotgun, shells, medikit). Every
edit repaints a live first-person preview rendered with the
`raycastlib` DDA approach over the same grid. Export writes
`saves/dmapN.wad` through the ordinary file syscalls. A Run
action (button plus Ctrl+R) spawns `doomgeneric.elf -file
saves/dmapN.wad` so the author plays the map without leaving the
editor flow. The editor never opens the IWAD for writing.

### Contract 3: Runtime snapshot semantics
The IWAD on MiniFS is immutable: no editor path, shell path, or
Doom path writes to it. Custom maps live only under `saves/` on
MiniFS, which the image rules already extract and repack across
rebuilds, so a map survives `make os.img` and `make clean` through
the same `saves-backup/` reseed that protects game saves today.
At boot Doom starts exactly as before when no `-file` argument is
given. A previously exported map replays by launching the editor
and pressing Run, or from the shell with `run doomgeneric.elf
-file saves/dmapN.wad`. Rebooting without arguments always
returns to the original game.

## Consequences
I accept single-room maps in version 1 to avoid shipping a BSP
compiler before the pipeline is proven. I accept patching the
shareware `-file` gate as MiniOS-local behavior with a BDD pin so
a rebase cannot silently re-lock the feature. I keep `raycastlib`
as a sibling reference plus a small preview implementation in the
editor rather than vendoring gameplay code I do not need.

## Verification
Host suite for the writer covers grid-to-PWAD vectors, fail-closed
inputs, and a byte-layout pin on a fixed fixture. In-OS BDD covers
export to `saves/`, Doom boot on the PWAD with a climbing `gfx
frames` counter, reboot persistence of the snapshot, and an
untouched IWAD hash. Scoped mutation covers the writer, the gate
patch, and the export path. The full `test_bdd.sh` and `mutate.sh`
run once at the end of the work, never between steps.

## Mechanism Note
A trailing shareware gate silently converts every custom-map
attempt into a fatal error at startup. The failure looks like a
broken PWAD when the real cause is a gamemode check far from the
file code. I document this so the next port with tiered IWAD
editions checks its edition gates before debugging its lumps.

## Revision 2: bundled levels and procedural maps
The editor now ships five compiled-in levels (`Hangar of Dawn`, `Imp
Gallery`, `Demon Pit`, `Crossfire Chapel`, `Fortress of Lead`) in the
same one-char-per-tile grid text the editor saves, a few hundred bytes
each, picked from a combo box beside a Random button that grows a fresh
map with the full thing palette (demons guaranteed) and keeps the
first layout the validator accepts. `doomedit --preset N out.wad`
exports a level headlessly; the selftest builds every preset plus a
fixed-seed random map, and `make test-doomedit` runs all five through
the Python checker so the two writers cannot drift.
