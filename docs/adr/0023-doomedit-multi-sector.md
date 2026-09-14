# ADR-0023: Multi-Sector DoomEdit Maps Without a BSP Compiler

## Status
Accepted. Phase 2 slice: real sectors, trivial BSP.

## Context
ADR-0022 shipped DoomEdit with a single-sector exporter and named
multi-sector maps with a real BSP compiler an explicit Phase 2. The
single sector flattened every map to one light level, one floor
height and one flat, and doors were impossible: a door is a sector
whose ceiling moves, and there was no second sector to move.

## Key Finding
A correct BSP tree is only needed to order subsectors. With exactly
one subsector there is nothing to order, so the trivial tree (every
linedef becomes one seg, all segs in subsector 0, root node with both
children leaf) stays correct for any sector count. Sight, collision
and clipping all work off the line/sector/sidedef lists, which carry
the multi-sector information directly: front/back sector indices on
two-sided lines, per-sector light/heights/flats/tags, a blockmap over
every line, and a REJECT bit table sized for the sector count. The
only cost is rendering performance (one subsector draws every seg),
which is irrelevant at 32x20 tiles on a 320x200 software renderer. A
partition-searching builder remains a later phase for large maps, not
a correctness requirement.

## Decision
Regions are same-style floor areas: the labeller floods walkable
cells that share a class, so `+` door cells stand alone and `,`
dark / `~` nukage cells never merge into normal rooms. Each region
becomes one sector; each orthogonally-connected door block becomes
one tagged door sector (ceiling 64, D1 open-door special 31 on both
faces). Same-height seams (room to dark room) emit invisible
two-sided lines whose only effect is the light step; floor steps
(nukage at -16) emit lower faces in each side's wall skin. Interior
T-junctions at door frames are legitimate, so the checker requires
vertex degree >= 2 instead of even degree. REJECT is sized
`(nsec*nsec+7)/8`, nonzero line tags must match a sector tag, and the
exit switch stays untagged. The C exporter mirrors the Python writer
under the existing no-drift contract (`make test-doomedit` runs all
nine bundled levels plus the demo through the Python checker, and the
BDD suite boots Doom on a door map with `exit code: 0`).

## Consequences
Maps gain working push-doors, dark zones and damaging slime with no
node builder to maintain. Deliberately out of scope: partition
search, seg splitting, concave sectors needing splits, lifts and
teleporters.
