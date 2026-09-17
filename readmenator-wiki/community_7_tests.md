# tests

*Community 7 | 2 files | cohesion 1.00*

## Definition

This community groups 2 file(s) rooted at `tests` with dominant language py (cohesion 1.00). Central symbols: `DoomPwadConfig`, `ExtendedLegendTests`, `GridValidationTests`, `MultiSectorMutationTests`, `MultiSectorTests`, `PwadError`, `PwadLayoutTests`, `PwadMutationTests`. Core file: `tests/test_doom_pwad.py` (44 symbols). Documented purpose: host contract suite for tools/doom_pwad.py.  Runs the grid compiler and the PWAD checker against fixed vectors: a known room builds to a pinned byte layout, the.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_doom_pwad.py` | py | testing | 44 | yes |
| `tools/doom_pwad.py` | py | utility | 25 | yes |

## Key Symbols

- `GridValidationTests` (class, `tests/test_doom_pwad.py:29`) `class GridValidationTests(TestCase)` - Grid parsing refuses malformed rooms before any byte is emitted.
- `test_valid_room_parses` (method, `tests/test_doom_pwad.py:32`) `def test_valid_room_parses(self)` - A closed room with player and exit parses to five rows.
- `test_ragged_rows_refused` (method, `tests/test_doom_pwad.py:36`) `def test_ragged_rows_refused(self)` - Rows of uneven length are rejected, never padded silently.
- `test_missing_player_refused` (method, `tests/test_doom_pwad.py:41`) `def test_missing_player_refused(self)` - A room without a player start cannot build.
- `test_missing_exit_refused` (method, `tests/test_doom_pwad.py:46`) `def test_missing_exit_refused(self)` - A room without an exit marker cannot build.
- `test_illegal_char_refused` (method, `tests/test_doom_pwad.py:51`) `def test_illegal_char_refused(self)` - Characters outside the legend are rejected outright.
- `test_unreachable_exit_refused` (method, `tests/test_doom_pwad.py:56`) `def test_unreachable_exit_refused(self)` - An exit sealed behind walls is refused instead of unplayable.
- `test_exit_needs_wall` (method, `tests/test_doom_pwad.py:66`) `def test_exit_needs_wall(self)` - An exit marker floating mid-floor has no switch edge to mark.
- `PwadLayoutTests` (class, `tests/test_doom_pwad.py:82`) `class PwadLayoutTests(TestCase)` - The emitted PWAD keeps the vanilla lump contract byte-exact.
- `test_roundtrip_check` (method, `tests/test_doom_pwad.py:85`) `def test_roundtrip_check(self)` - A built room passes the checker with a sane lump census.
- `test_header_pin` (method, `tests/test_doom_pwad.py:96`) `def test_header_pin(self)` - Magic, lump count and label lump stay pinned for the fixture.
- `test_lump_order_pin` (method, `tests/test_doom_pwad.py:103`) `def test_lump_order_pin(self)` - Lumps follow the ML_LABEL..ML_BLOCKMAP order the engine walks.
- `test_things_pin` (method, `tests/test_doom_pwad.py:115`) `def test_things_pin(self)` - Player and exit-adjacent layout land on expected coordinates.
- `test_exit_switch_pin` (method, `tests/test_doom_pwad.py:129`) `def test_exit_switch_pin(self)` - Exactly one linedef carries the exit special after a build.
- `test_exit_on_every_side` (method, `tests/test_doom_pwad.py:141`) `def test_exit_on_every_side(self)` - An exit against any of the four walls builds a closed room.
- `test_pillar_room_stays_closed` (method, `tests/test_doom_pwad.py:154`) `def test_pillar_room_stays_closed(self)` - Interior wall blocks add loops without opening the boundary.
- `test_open_boundary_dies` (method, `tests/test_doom_pwad.py:168`) `def test_open_boundary_dies(self)` - Retargeting one endpoint unbalances two vertexes, refused.
- `PwadMutationTests` (class, `tests/test_doom_pwad.py:181`) `class PwadMutationTests(TestCase)` - Single-byte and structural mutations of a good file all fail.
- `setUp` (method, `tests/test_doom_pwad.py:184`) `def setUp(self)` - Build one known-good image shared by every mutation case.
- `test_bad_magic_dies` (method, `tests/test_doom_pwad.py:188`) `def test_bad_magic_dies(self)` - An IWAD magic on a custom file is refused, never trusted.
- `test_truncated_file_dies` (method, `tests/test_doom_pwad.py:193`) `def test_truncated_file_dies(self)` - A file cut mid-directory is refused instead of half-parsed.
- `test_swapped_lumps_die` (method, `tests/test_doom_pwad.py:198`) `def test_swapped_lumps_die(self)` - Swapping two directory names breaks the order contract.
- `test_partial_record_dies` (method, `tests/test_doom_pwad.py:212`) `def test_partial_record_dies(self)` - A THINGS lump with a torn record is refused, never rounded.
- `test_wild_vertex_dies` (method, `tests/test_doom_pwad.py:221`) `def test_wild_vertex_dies(self)` - A linedef pointing past the vertex list is refused.
- `test_missing_exit_dies` (method, `tests/test_doom_pwad.py:230`) `def test_missing_exit_dies(self)` - Clearing the exit special leaves a file with no way out.
- `test_unterminated_blockmap_dies` (method, `tests/test_doom_pwad.py:243`) `def test_unterminated_blockmap_dies(self)` - A blockmap list without a terminator is refused, never scanned.
- `ExtendedLegendTests` (class, `tests/test_doom_pwad.py:255`) `class ExtendedLegendTests(TestCase)` - Every palette letter compiles to its engine thing id.
- `test_every_legend_char_builds` (method, `tests/test_doom_pwad.py:273`) `def test_every_legend_char_builds(self)` - A room holding the whole palette passes the checker.
- `test_every_thing_id_matches_engine` (method, `tests/test_doom_pwad.py:278`) `def test_every_thing_id_matches_engine(self)` - Each letter lands on the doomednum the engine spawns.
- `lump_blob` (method, `tests/test_doom_pwad.py:310`) `def lump_blob(blob, idx)` - Slice one lump payload out of a built image by directory order.

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- [INFERRED] shares_context community 0 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 7 (tests).
- [INFERRED] shares_context community 1 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 7 (tests).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in tests changed?
- Should tests be split, given cohesion 1.00?

## Sources

- `tests/test_doom_pwad.py`
- `tools/doom_pwad.py`
