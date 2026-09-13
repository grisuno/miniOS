#!/usr/bin/env python3
"""test_doom_pwad.py - host contract suite for tools/doom_pwad.py.

Runs the grid compiler and the PWAD checker against fixed vectors:
a known room builds to a pinned byte layout, the output passes the
checker, and every malformed input or mutated file is refused with a
diagnostic instead of a partial artifact.
"""
import os
import struct
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "tools"))
import doom_pwad
from doom_pwad import DoomPwadConfig as Cfg
from doom_pwad import PwadError, build_pwad, check_pwad, parse_grid


ROOM = (
    "#####\n"
    "#...#\n"
    "#.P.#\n"
    "#.E.#\n"
    "#####\n"
)


class GridValidationTests(unittest.TestCase):
    """Grid parsing refuses malformed rooms before any byte is emitted."""

    def test_valid_room_parses(self):
        """A closed room with player and exit parses to five rows."""
        self.assertEqual(len(parse_grid(ROOM)), 5)

    def test_ragged_rows_refused(self):
        """Rows of uneven length are rejected, never padded silently."""
        with self.assertRaises(PwadError):
            parse_grid("####\n#..\n####\n")

    def test_missing_player_refused(self):
        """A room without a player start cannot build."""
        with self.assertRaises(PwadError):
            build_pwad(parse_grid("#####\n#...#\n#.E.#\n#...#\n#####\n"))

    def test_missing_exit_refused(self):
        """A room without an exit marker cannot build."""
        with self.assertRaises(PwadError):
            build_pwad(parse_grid("#####\n#...#\n#.P.#\n#...#\n#####\n"))

    def test_illegal_char_refused(self):
        """Characters outside the legend are rejected outright."""
        with self.assertRaises(PwadError):
            parse_grid("#####\n#.@.#\n#.P.#\n#.E.#\n#####\n")

    def test_unreachable_exit_refused(self):
        """An exit sealed behind walls is refused instead of unplayable."""
        grid = (
            "#######\n"
            "#.P.#E#\n"
            "#######\n"
        )
        with self.assertRaises(PwadError):
            build_pwad(parse_grid(grid))

    def test_exit_needs_wall(self):
        """An exit marker floating mid-floor has no switch edge to mark."""
        grid = (
            "#######\n"
            "#.....#\n"
            "#.P.E.#\n"
            "#.....#\n"
            "#######\n"
        )
        rows = [list(line) for line in parse_grid(grid)]
        rows[1][3] = "."
        rows[3][3] = "."
        with self.assertRaises(PwadError):
            build_pwad(["".join(line) for line in rows])


class PwadLayoutTests(unittest.TestCase):
    """The emitted PWAD keeps the vanilla lump contract byte-exact."""

    def test_roundtrip_check(self):
        """A built room passes the checker with a sane lump census."""
        summary = check_pwad(build_pwad(parse_grid(ROOM)))
        self.assertEqual(summary["sectors"], 1)
        self.assertEqual(summary["nodes"], 1)
        self.assertEqual(summary["subsectors"], 1)
        self.assertEqual(summary["things"], 1)
        self.assertEqual(summary["linedefs"], 12)
        self.assertEqual(summary["segs"], 12)
        self.assertEqual(summary["vertexes"], 12)

    def test_header_pin(self):
        """Magic, lump count and label lump stay pinned for the fixture."""
        blob = build_pwad(parse_grid(ROOM))
        magic, numlumps, _ = struct.unpack_from(Cfg.header_fmt, blob, 0)
        self.assertEqual(magic, b"PWAD")
        self.assertEqual(numlumps, len(Cfg.lump_names))

    def test_lump_order_pin(self):
        """Lumps follow the ML_LABEL..ML_BLOCKMAP order the engine walks."""
        blob = build_pwad(parse_grid(ROOM))
        _, _, table_off = struct.unpack_from(Cfg.header_fmt, blob, 0)
        width = struct.calcsize(Cfg.dir_fmt)
        names = []
        for idx in range(len(Cfg.lump_names)):
            _, _, name = struct.unpack_from(
                Cfg.dir_fmt, blob, table_off + idx * width)
            names.append(name.rstrip(b"\x00"))
        self.assertEqual(tuple(names), Cfg.lump_names)

    def test_things_pin(self):
        """Player and exit-adjacent layout land on expected coordinates."""
        blob = build_pwad(parse_grid(ROOM))
        table = doom_pwad.read_pwad(blob)
        pos, size, _ = table[1]
        raw = blob[pos:pos + size]
        width = struct.calcsize(Cfg.thing_fmt)
        kinds = set()
        for idx in range(size // width):
            x, y, _, kind, _ = struct.unpack_from(Cfg.thing_fmt, raw, idx * width)
            kinds.add(kind)
            self.assertEqual(x % Cfg.tile_units, Cfg.tile_units // 2)
        self.assertIn(1, kinds)

    def test_exit_switch_pin(self):
        """Exactly one linedef carries the exit special after a build."""
        blob = build_pwad(parse_grid(ROOM))
        table = doom_pwad.read_pwad(blob)
        pos, size, _ = table[2]
        raw = blob[pos:pos + size]
        width = struct.calcsize(Cfg.linedef_fmt)
        specials = []
        for idx in range(size // width):
            specials.append(struct.unpack_from(Cfg.linedef_fmt, raw, idx * width)[3])
        self.assertEqual(specials.count(Cfg.special_exit), 1)

    def test_exit_on_every_side(self):
        """An exit against any of the four walls builds a closed room."""
        templates = {
            "north": ("#####\n#.E.#\n#.P.#\n#...#\n#####\n"),
            "south": ("#####\n#...#\n#.P.#\n#.E.#\n#####\n"),
            "west": ("#####\n#...#\n#EP.#\n#...#\n#####\n"),
            "east": ("#####\n#...#\n#.PE#\n#...#\n#####\n"),
        }
        for side, grid in templates.items():
            with self.subTest(side=side):
                summary = check_pwad(build_pwad(parse_grid(grid)))
                self.assertEqual(summary["sectors"], 1)

    def test_pillar_room_stays_closed(self):
        """Interior wall blocks add loops without opening the boundary."""
        grid = (
            "#######\n"
            "#.....#\n"
            "#.P...#\n"
            "#..#..#\n"
            "#.....#\n"
            "#..E..#\n"
            "#######\n"
        )
        summary = check_pwad(build_pwad(parse_grid(grid)))
        self.assertGreater(summary["linedefs"], 20)

    def test_open_boundary_dies(self):
        """Retargeting one endpoint unbalances two vertexes, refused."""
        blob = bytearray(build_pwad(parse_grid(ROOM)))
        table = doom_pwad.read_pwad(bytes(blob))
        pos, _, _ = table[2]
        width = struct.calcsize(Cfg.linedef_fmt)
        fields = list(struct.unpack_from(Cfg.linedef_fmt, blob, pos))
        fields[0] = (fields[0] + 1) % 12
        struct.pack_into(Cfg.linedef_fmt, blob, pos, *fields)
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))


class PwadMutationTests(unittest.TestCase):
    """Single-byte and structural mutations of a good file all fail."""

    def setUp(self):
        """Build one known-good image shared by every mutation case."""
        self.good = build_pwad(parse_grid(ROOM))

    def test_bad_magic_dies(self):
        """An IWAD magic on a custom file is refused, never trusted."""
        with self.assertRaises(PwadError):
            check_pwad(b"IWAD" + self.good[4:])

    def test_truncated_file_dies(self):
        """A file cut mid-directory is refused instead of half-parsed."""
        with self.assertRaises(PwadError):
            check_pwad(self.good[:len(self.good) // 2])

    def test_swapped_lumps_die(self):
        """Swapping two directory names breaks the order contract."""
        blob = bytearray(self.good)
        _, _, table_off = struct.unpack_from(Cfg.header_fmt, bytes(blob), 0)
        width = struct.calcsize(Cfg.dir_fmt)
        first = table_off
        second = table_off + width
        entry_a = bytes(blob[first:first + width])
        entry_b = bytes(blob[second:second + width])
        blob[first:first + width] = entry_b
        blob[second:second + width] = entry_a
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))

    def test_partial_record_dies(self):
        """A THINGS lump with a torn record is refused, never rounded."""
        table = doom_pwad.read_pwad(self.good)
        pos, size, _ = table[1]
        blob = bytearray(self.good)
        del blob[pos + size - 1]
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))

    def test_wild_vertex_dies(self):
        """A linedef pointing past the vertex list is refused."""
        table = doom_pwad.read_pwad(self.good)
        pos, _, _ = table[2]
        blob = bytearray(self.good)
        struct.pack_into(Cfg.linedef_fmt, blob, pos, 9000, 9001, 1, 0, 0, 0, -1)
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))

    def test_missing_exit_dies(self):
        """Clearing the exit special leaves a file with no way out."""
        table = doom_pwad.read_pwad(self.good)
        pos, size, _ = table[2]
        blob = bytearray(self.good)
        width = struct.calcsize(Cfg.linedef_fmt)
        for idx in range(size // width):
            fields = list(struct.unpack_from(Cfg.linedef_fmt, blob, pos + idx * width))
            fields[3] = 0
            struct.pack_into(Cfg.linedef_fmt, blob, pos + idx * width, *fields)
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))

    def test_unterminated_blockmap_dies(self):
        """A blockmap list without a terminator is refused, never scanned."""
        table = doom_pwad.read_pwad(self.good)
        pos, size, _ = table[10]
        blob = bytearray(self.good)
        for idx in range(pos, pos + size, 2):
            if struct.unpack_from("<h", blob, idx)[0] == -1:
                struct.pack_into("<h", blob, idx, 0)
        with self.assertRaises(PwadError):
            check_pwad(bytes(blob))


if __name__ == "__main__":
    unittest.main(verbosity=2)
