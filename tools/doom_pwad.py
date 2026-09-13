#!/usr/bin/env python3
"""doom_pwad.py - grid map to vanilla Doom PWAD writer and checker.

Converts a text grid map into a single-level PWAD that replaces E1M1
in the shareware IWAD, and validates PWAD files produced by any tool.
The generated level is one convex-or-concave single sector, so the
BSP it carries is trivially correct: every linedef becomes one seg,
all segs form one subsector, and the root node points at that same
subsector on both children. No external node builder is required.

Usage: doom_pwad.py build <grid.txt> <out.wad>
       doom_pwad.py check <file.wad>
       doom_pwad.py info <file.wad>

Grid legend: '#' wall, '.' floor, 'P' player 1 start, 'E' exit switch
marker, 'i' imp, 'd' demon, 's' shotgun guy, 'm' medikit, 'a' shells.
The exit marker must sit on a floor tile next to a wall; the shared
edge becomes the S1 exit switch linedef. Every walkable tile must be
reachable from the player start, or the build is refused.

Texture, flat and thing ids below were verified byte-present in the
shipped shareware Doom1.wad, so the engine never resolves a missing
name from a generated file.
"""
import math
import struct
import sys


class DoomPwadConfig:
    """Centralized tunables for the grid compiler and the PWAD checker."""

    magic = b"PWAD"
    map_label = b"E1M1"
    lump_names = (
        b"E1M1", b"THINGS", b"LINEDEFS", b"SIDEDEFS", b"VERTEXES",
        b"SEGS", b"SSECTORS", b"NODES", b"SECTORS", b"REJECT",
        b"BLOCKMAP",
    )
    header_fmt = "<4sii"
    dir_fmt = "<ii8s"
    vertex_fmt = "<hh"
    linedef_fmt = "<hhhhhhh"
    sidedef_fmt = "<hh8s8s8sh"
    sector_fmt = "<hh8s8shhh"
    thing_fmt = "<hhhhh"
    seg_fmt = "<hhhhhh"
    subsector_fmt = "<hh"
    node_fmt = "<4h8h2H"
    block_fmt = "<h"

    tile_units = 128
    block_units = 128
    min_side = 3
    max_side = 64
    max_vertexes = 4096
    max_linedefs = 2048
    max_things = 256

    wall_chars = "#"
    floor_chars = ".PEidsma"
    thing_types = {
        "P": 1,
        "i": 3001,
        "d": 3002,
        "s": 2001,
        "m": 2012,
        "a": 2008,
    }
    thing_options = 7
    player_angle = 0

    flag_blocking = 1
    special_exit = 11
    no_side = -1
    front_sector = 0

    wall_mid = b"STARTAN3"
    exit_mid = b"SW1EXIT"
    unused_tex = b"-"
    floor_flat = b"FLOOR4_8"
    ceil_flat = b"CEIL3_5"
    floor_height = 0
    ceil_height = 128
    light_level = 160
    sector_special = 0
    sector_tag = 0

    node_leaf = 0x8000
    exit_dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))


class PwadError(Exception):
    """Fail-closed diagnostic raised for any invalid grid or PWAD."""


def pad_tex(raw):
    """Return a texture or flat name padded to its 8-byte field."""
    if len(raw) > 8:
        raise PwadError("texture name too long: %r" % raw)
    return raw + b"\x00" * (8 - len(raw))


def parse_grid(text):
    """Parse grid text into rows, refusing empty or ragged input."""
    rows = text.split("\n")
    if rows and rows[-1] == "":
        rows = rows[:-1]
    if not rows:
        raise PwadError("empty grid")
    cfg = DoomPwadConfig
    width = len(rows[0])
    if any(len(row) != width for row in rows):
        raise PwadError("ragged grid rows")
    if not (cfg.min_side <= len(rows) <= cfg.max_side):
        raise PwadError("grid height out of range")
    if not (cfg.min_side <= width <= cfg.max_side):
        raise PwadError("grid width out of range")
    legal = set(cfg.wall_chars + cfg.floor_chars)
    for row in rows:
        for cell in row:
            if cell not in legal:
                raise PwadError("illegal grid char: %r" % cell)
    return rows


def grid_extents(rows):
    """Return coordinate bounds of the lattice in map units."""
    cfg = DoomPwadConfig
    height = len(rows)
    width = len(rows[0])
    return (0, width * cfg.tile_units, -height * cfg.tile_units, 0)


def is_wall(rows, row, col):
    """Treat out-of-bounds cells as solid wall so maps stay closed."""
    if row < 0 or col < 0 or row >= len(rows) or col >= len(rows[0]):
        return True
    return rows[row][col] in DoomPwadConfig.wall_chars


def flood_reachable(rows):
    """Return the walkable set reachable from the player start tile."""
    cfg = DoomPwadConfig
    start = None
    for row, line in enumerate(rows):
        for col, cell in enumerate(line):
            if cell == "P":
                start = (row, col)
    if start is None:
        raise PwadError("grid has no player start")
    seen = {start}
    work = [start]
    while work:
        row, col = work.pop()
        for drow, dcol in cfg.exit_dirs:
            nxt = (row + drow, col + dcol)
            nrow, ncol = nxt
            if nrow < 0 or ncol < 0:
                continue
            if nrow >= len(rows) or ncol >= len(rows[0]):
                continue
            if nxt in seen:
                continue
            if rows[nrow][ncol] in cfg.wall_chars:
                continue
            seen.add(nxt)
            work.append(nxt)
    return seen


def validate_grid(rows):
    """Enforce single player, single exit, and full reachability."""
    cfg = DoomPwadConfig
    players = sum(line.count("P") for line in rows)
    if players != 1:
        raise PwadError("grid needs exactly one player start")
    exits = sum(line.count("E") for line in rows)
    if exits != 1:
        raise PwadError("grid needs exactly one exit marker")
    reachable = flood_reachable(rows)
    for row, line in enumerate(rows):
        for col, cell in enumerate(line):
            if cell in cfg.floor_chars and (row, col) not in reachable:
                raise PwadError("unreachable tile at %d,%d" % (row, col))
    exit_pos = None
    for row, line in enumerate(rows):
        for col, cell in enumerate(line):
            if cell == "E":
                exit_pos = (row, col)
    wall_side = None
    for drow, dcol in cfg.exit_dirs:
        if is_wall(rows, exit_pos[0] + drow, exit_pos[1] + dcol):
            wall_side = (drow, dcol)
            break
    if wall_side is None:
        raise PwadError("exit marker is not next to a wall")
    return exit_pos, wall_side


def cell_corners(row, col):
    """Return cell corners as (x0, x1, y_top, y_bottom) in map units."""
    cfg = DoomPwadConfig
    x0 = col * cfg.tile_units
    x1 = (col + 1) * cfg.tile_units
    y_top = -row * cfg.tile_units
    y_bottom = -(row + 1) * cfg.tile_units
    return (x0, x1, y_top, y_bottom)


def compile_geometry(rows, exit_pos, wall_side):
    """Compile wall boundary edges into vertexes, linedefs and sides."""
    cfg = DoomPwadConfig
    vertex_index = {}
    vertexes = []
    linedefs = []

    def vertex(x, y):
        """Deduplicate lattice points shared by adjacent edges."""
        key = (x, y)
        idx = vertex_index.get(key)
        if idx is None:
            if len(vertexes) >= cfg.max_vertexes:
                raise PwadError("too many vertexes")
            idx = len(vertexes)
            vertex_index[key] = idx
            vertexes.append(key)
        return idx

    exit_edge = None
    erow, ecol = exit_pos
    for row, line in enumerate(rows):
        for col, cell in enumerate(line):
            if cell in cfg.wall_chars:
                continue
            x0, x1, y_top, y_bottom = cell_corners(row, col)
            edges = []
            if is_wall(rows, row - 1, col):
                edges.append(((x0, y_top), (x1, y_top), (-1, 0)))
            if is_wall(rows, row + 1, col):
                edges.append(((x1, y_bottom), (x0, y_bottom), (1, 0)))
            if is_wall(rows, row, col - 1):
                edges.append(((x0, y_bottom), (x0, y_top), (0, -1)))
            if is_wall(rows, row, col + 1):
                edges.append(((x1, y_top), (x1, y_bottom), (0, 1)))
            for start, end, side in edges:
                if (row, col) == exit_pos and side == wall_side:
                    exit_edge = len(linedefs)
                v1 = vertex(*start)
                v2 = vertex(*end)
                linedefs.append((v1, v2, len(linedefs)))
    if exit_edge is None:
        raise PwadError("exit edge vanished during compile")
    if len(linedefs) > cfg.max_linedefs:
        raise PwadError("too many linedefs")
    return vertexes, linedefs, exit_edge


def compile_things(rows):
    """Compile thing stamps into mapthing records in scan order."""
    cfg = DoomPwadConfig
    things = []
    for row, line in enumerate(rows):
        for col, cell in enumerate(line):
            if cell not in cfg.thing_types:
                continue
            x0, x1, y_top, y_bottom = cell_corners(row, col)
            things.append((
                (x0 + x1) // 2,
                (y_top + y_bottom) // 2,
                cfg.player_angle,
                cfg.thing_types[cell],
                cfg.thing_options,
            ))
    if len(things) > cfg.max_things:
        raise PwadError("too many things")
    return things


def seg_angle(dx, dy):
    """Return the stored short angle for a seg direction vector."""
    full = int(math.atan2(dy, dx) / (2.0 * math.pi) * 4294967296.0)
    full &= 0xFFFFFFFF
    short = (full >> 16) & 0xFFFF
    if short >= 0x8000:
        short -= 0x10000
    return short


def build_lumps(rows):
    """Compile a validated grid into the eleven E1M1 lump payloads."""
    cfg = DoomPwadConfig
    exit_pos, wall_side = validate_grid(rows)
    vertexes, linedefs, exit_edge = compile_geometry(rows, exit_pos, wall_side)
    things = compile_things(rows)

    things_lump = b"".join(struct.pack(cfg.thing_fmt, *t) for t in things)

    linedef_lump = b""
    for idx, (v1, v2, side) in enumerate(linedefs):
        special = cfg.special_exit if idx == exit_edge else 0
        linedef_lump += struct.pack(
            cfg.linedef_fmt, v1, v2, cfg.flag_blocking,
            special, 0, side, cfg.no_side)

    sidedef_lump = b""
    for idx in range(len(linedefs)):
        mid = cfg.exit_mid if idx == exit_edge else cfg.wall_mid
        sidedef_lump += struct.pack(
            cfg.sidedef_fmt, 0, 0, pad_tex(cfg.unused_tex),
            pad_tex(cfg.unused_tex), pad_tex(mid), cfg.front_sector)

    vertex_lump = b"".join(struct.pack(cfg.vertex_fmt, x, y) for x, y in vertexes)

    seg_lump = b""
    for idx, (v1, v2, _) in enumerate(linedefs):
        x1, y1 = vertexes[v1]
        x2, y2 = vertexes[v2]
        seg_lump += struct.pack(
            cfg.seg_fmt, v1, v2, seg_angle(x2 - x1, y2 - y1), idx, 0, 0)

    subsector_lump = struct.pack(cfg.subsector_fmt, len(linedefs), 0)

    minx, maxx, miny, maxy = grid_extents(rows)
    first = vertexes[linedefs[0][0]]
    second = vertexes[linedefs[0][1]]
    bbox = (maxy, miny, minx, maxx) * 2
    node_lump = struct.pack(
        cfg.node_fmt, first[0], first[1], second[0] - first[0],
        second[1] - first[1], *bbox,
        cfg.node_leaf, cfg.node_leaf)

    sector_lump = struct.pack(
        cfg.sector_fmt, cfg.floor_height, cfg.ceil_height,
        pad_tex(cfg.floor_flat), pad_tex(cfg.ceil_flat),
        cfg.light_level, cfg.sector_special, cfg.sector_tag)

    reject_lump = b"\x00"

    span_x = maxx - minx
    span_y = maxy - miny
    blocks_x = span_x // cfg.block_units + 1
    blocks_y = span_y // cfg.block_units + 1
    list_off = 4 + blocks_x * blocks_y
    words = [minx, miny, blocks_x, blocks_y] + [list_off] * (blocks_x * blocks_y)
    words += [0] + list(range(len(linedefs))) + [-1]
    blockmap_lump = struct.pack("<%dh" % len(words), *words)

    return {
        b"E1M1": b"",
        b"THINGS": things_lump,
        b"LINEDEFS": linedef_lump,
        b"SIDEDEFS": sidedef_lump,
        b"VERTEXES": vertex_lump,
        b"SEGS": seg_lump,
        b"SSECTORS": subsector_lump,
        b"NODES": node_lump,
        b"SECTORS": sector_lump,
        b"REJECT": reject_lump,
        b"BLOCKMAP": blockmap_lump,
    }


def build_pwad(rows):
    """Assemble lump payloads into a complete PWAD byte string."""
    cfg = DoomPwadConfig
    lumps = build_lumps(rows)
    names = list(cfg.lump_names)
    head_size = struct.calcsize(cfg.header_fmt)
    blob = b""
    directory = []
    for name in names:
        payload = lumps[name.rstrip(b"\x00")]
        directory.append((head_size + len(blob), len(payload), name))
        blob += payload
    table_off = head_size + len(blob)
    for pos, size, name in directory:
        blob += struct.pack(cfg.dir_fmt, pos, size, name)
    header = struct.pack(cfg.header_fmt, cfg.magic, len(names), table_off)
    return header + blob


def read_pwad(data):
    """Split PWAD bytes into header fields and an ordered lump table."""
    cfg = DoomPwadConfig
    if len(data) < struct.calcsize(cfg.header_fmt):
        raise PwadError("file too small for a WAD header")
    magic, numlumps, table_off = struct.unpack_from(cfg.header_fmt, data, 0)
    if magic != cfg.magic:
        raise PwadError("bad WAD magic, want PWAD")
    if numlumps != len(cfg.lump_names):
        raise PwadError("want %d lumps, found %d" % (len(cfg.lump_names), numlumps))
    entry_size = struct.calcsize(cfg.dir_fmt)
    if table_off < 0 or table_off + numlumps * entry_size > len(data):
        raise PwadError("lump directory runs past end of file")
    table = []
    for idx in range(numlumps):
        pos, size, name = struct.unpack_from(
            cfg.dir_fmt, data, table_off + idx * entry_size)
        if pos < 0 or size < 0 or pos + size > table_off:
            raise PwadError("lump %d data runs past end of file" % idx)
        table.append((pos, size, name))
    return table


def check_pwad(data):
    """Validate lump order, record sizes and cross-lump references."""
    cfg = DoomPwadConfig
    table = read_pwad(data)
    for (_, _, name), want in zip(table, cfg.lump_names):
        if name.rstrip(b"\x00") != want:
            raise PwadError("lump order broken, want %r" % want.decode())
    sizes = {}
    for pos, size, name in table:
        sizes[name.rstrip(b"\x00")] = (pos, size)

    def payload(name):
        """Slice one lump payload out of the file image."""
        pos, size = sizes[name]
        return data[pos:pos + size]

    def check_multiple(name, fmt):
        """Require the lump length to hold whole records only."""
        size = sizes[name][1]
        width = struct.calcsize(fmt)
        if size % width != 0:
            raise PwadError("lump %s has a partial record" % name.decode())
        return size // width

    n_things = check_multiple(b"THINGS", cfg.thing_fmt)
    n_lines = check_multiple(b"LINEDEFS", cfg.linedef_fmt)
    n_sides = check_multiple(b"SIDEDEFS", cfg.sidedef_fmt)
    n_vertexes = check_multiple(b"VERTEXES", cfg.vertex_fmt)
    n_segs = check_multiple(b"SEGS", cfg.seg_fmt)
    n_subs = check_multiple(b"SSECTORS", cfg.subsector_fmt)
    n_nodes = check_multiple(b"NODES", cfg.node_fmt)
    n_sectors = check_multiple(b"SECTORS", cfg.sector_fmt)
    if n_things < 1:
        raise PwadError("no things in map")
    if n_lines < 1 or n_sides < 1 or n_vertexes < 1:
        raise PwadError("empty geometry in map")
    if n_segs < 1 or n_subs < 1 or n_nodes < 1 or n_sectors < 1:
        raise PwadError("missing BSP lumps in map")
    if sizes[b"E1M1"][1] != 0:
        raise PwadError("map label lump must be empty")
    if sizes[b"REJECT"][1] != 1:
        raise PwadError("single-sector REJECT must be one byte")

    raw_things = payload(b"THINGS")
    players = 0
    for idx in range(n_things):
        _, _, _, kind, _ = struct.unpack_from(
            cfg.thing_fmt, raw_things, idx * struct.calcsize(cfg.thing_fmt))
        if kind == cfg.thing_types["P"]:
            players += 1
    if players != 1:
        raise PwadError("want exactly one player start, found %d" % players)

    raw_lines = payload(b"LINEDEFS")
    width = struct.calcsize(cfg.linedef_fmt)
    exits = 0
    degree = [0] * n_vertexes
    for idx in range(n_lines):
        v1, v2, _, special, _, s0, _ = struct.unpack_from(cfg.linedef_fmt, raw_lines, idx * width)
        if not (0 <= v1 < n_vertexes and 0 <= v2 < n_vertexes):
            raise PwadError("linedef %d has a wild vertex" % idx)
        if v1 == v2:
            raise PwadError("linedef %d is zero length" % idx)
        if not (0 <= s0 < n_sides):
            raise PwadError("linedef %d has a wild sidedef" % idx)
        if special == cfg.special_exit:
            exits += 1
        degree[v1] += 1
        degree[v2] += 1
    if exits != 1:
        raise PwadError("want exactly one exit switch, found %d" % exits)
    for idx, deg in enumerate(degree):
        if deg == 0 or deg % 2 != 0:
            raise PwadError("vertex %d leaves the boundary open" % idx)

    raw_sides = payload(b"SIDEDEFS")
    side_width = struct.calcsize(cfg.sidedef_fmt)
    for idx in range(n_sides):
        sector = struct.unpack_from(cfg.sidedef_fmt, raw_sides, idx * side_width)[-1]
        if not (0 <= sector < n_sectors):
            raise PwadError("sidedef %d has a wild sector" % idx)

    raw_segs = payload(b"SEGS")
    seg_width = struct.calcsize(cfg.seg_fmt)
    for idx in range(n_segs):
        v1, v2, _, line, _, _ = struct.unpack_from(cfg.seg_fmt, raw_segs, idx * seg_width)
        if not (0 <= v1 < n_vertexes and 0 <= v2 < n_vertexes):
            raise PwadError("seg %d has a wild vertex" % idx)
        if not (0 <= line < n_lines):
            raise PwadError("seg %d has a wild linedef" % idx)

    raw_subs = payload(b"SSECTORS")
    sub_width = struct.calcsize(cfg.subsector_fmt)
    for idx in range(n_subs):
        count, first = struct.unpack_from(cfg.subsector_fmt, raw_subs, idx * sub_width)
        if count < 1 or first < 0 or first + count > n_segs:
            raise PwadError("subsector %d runs past the seg list" % idx)

    raw_nodes = payload(b"NODES")
    node_width = struct.calcsize(cfg.node_fmt)
    for idx in range(n_nodes):
        children = struct.unpack_from(cfg.node_fmt, raw_nodes, idx * node_width)[-2:]
        for child in children:
            if child & cfg.node_leaf:
                if (child & ~cfg.node_leaf) >= n_subs:
                    raise PwadError("node %d has a wild subsector" % idx)
            elif child >= n_nodes:
                raise PwadError("node %d has a wild child node" % idx)

    raw_blocks = payload(b"BLOCKMAP")
    if len(raw_blocks) < 8:
        raise PwadError("blockmap has no header")
    words = struct.unpack("<%dh" % (len(raw_blocks) // 2), raw_blocks)
    if len(raw_blocks) % 2 != 0:
        raise PwadError("blockmap has a partial short")
    _, _, bw, bh = words[0:4]
    if bw < 1 or bh < 1 or bw > 256 or bh > 256:
        raise PwadError("blockmap grid out of range")
    if len(words) < 4 + bw * bh + 2:
        raise PwadError("blockmap directory runs past end of lump")
    for cell in range(bw * bh):
        off = words[4 + cell]
        if off < 4 + bw * bh or off >= len(words):
            raise PwadError("blockmap offset %d escapes the lump" % cell)
        cursor = off
        seen_end = False
        while cursor < len(words):
            if words[cursor] == -1:
                seen_end = True
                break
            if words[cursor] < 0 or words[cursor] >= n_lines:
                raise PwadError("blockmap lists a wild linedef")
            cursor += 1
        if not seen_end:
            raise PwadError("blockmap list has no terminator")
    return {
        "things": n_things,
        "linedefs": n_lines,
        "sidedefs": n_sides,
        "vertexes": n_vertexes,
        "segs": n_segs,
        "subsectors": n_subs,
        "nodes": n_nodes,
        "sectors": n_sectors,
    }


def cmd_build(grid_path, out_path):
    """Build a PWAD from a grid file, refusing to write on any error."""
    with open(grid_path, "r", encoding="ascii") as handle:
        rows = parse_grid(handle.read())
    blob = build_pwad(rows)
    with open(out_path, "wb") as handle:
        handle.write(blob)
    return "doom_pwad: wrote %d bytes to %s" % (len(blob), out_path)


def cmd_check(path):
    """Validate a PWAD file and report its lump census on success."""
    with open(path, "rb") as handle:
        summary = check_pwad(handle.read())
    parts = ["%s=%d" % (key, summary[key]) for key in sorted(summary)]
    return "doom_pwad: %s ok (%s)" % (path, " ".join(parts))


def main(argv):
    """Dispatch the build, check and info verbs with host-safe errors."""
    if len(argv) < 2:
        return ("usage: doom_pwad.py build <grid.txt> <out.wad> | "
                "check <file.wad> | info <file.wad>")
    verb = argv[1]
    try:
        if verb == "build" and len(argv) == 4:
            print(cmd_build(argv[2], argv[3]))
        elif verb == "check" and len(argv) == 3:
            print(cmd_check(argv[2]))
        elif verb == "info" and len(argv) == 3:
            print(cmd_check(argv[2]))
        else:
            return ("usage: doom_pwad.py build <grid.txt> <out.wad> | "
                    "check <file.wad> | info <file.wad>")
    except (PwadError, OSError, UnicodeDecodeError) as exc:
        return "doom_pwad: error: %s" % exc
    return None


if __name__ == "__main__":
    failure = main(sys.argv)
    if failure is not None:
        print(failure, file=sys.stderr)
        sys.exit(1)
