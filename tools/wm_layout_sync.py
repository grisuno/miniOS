#!/usr/bin/env python3
"""Docstring: Synchronize the WM layout manifest from source truth.

I read wm_layout.h and tests/test_wm.c and regenerate
docs/wm_layout_manifest.md so documentation never drifts from code.
I fail closed with nonzero exit on missing contracts or mode gaps.
"""

from __future__ import annotations

import argparse
import pathlib
import re
import sys


class WmLayoutSyncConfig:
    """Docstring: Centralized paths and bounds for layout sync."""

    def __init__(self, root: pathlib.Path) -> None:
        """Docstring: Bind all paths to one repository root."""
        self.root = root
        self.header = root / "wm_layout.h"
        self.tests = root / "tests" / "test_wm.c"
        self.manifest = root / "docs" / "wm_layout_manifest.md"
        self.required_modes = ("tile", "bsp", "cascade", "fibonacci", "fullscreen")
        self.required_symbols = (
            "wm_layout_compute",
            "wm_layout_fullscreen_cell",
            "wm_layout_same",
            "wm_layout_mode_name",
            "wm_layout_mode_valid",
        )


class WmLayoutSyncResult:
    """Docstring: Outcome of one manifest synchronization."""

    def __init__(self, modes: list[str], symbols: list[str], checks: int) -> None:
        """Docstring: Store discovered modes, symbols and check count."""
        self.modes = modes
        self.symbols = symbols
        self.checks = checks


class WmLayoutSync:
    """Docstring: Manifest builder driven only by source files."""

    def __init__(self, config: WmLayoutSyncConfig) -> None:
        """Docstring: Hold config as the sole tunable source."""
        self.config = config

    def discover(self) -> WmLayoutSyncResult:
        """Docstring: Extract modes, symbols and test checks from sources."""
        header_text = self._read_text(self.config.header)
        tests_text = self._read_text(self.config.tests)
        modes = self._extract_modes(header_text)
        symbols = self._extract_symbols(header_text)
        checks = self._count_layout_checks(tests_text)
        self._require_modes(modes)
        self._require_symbols(symbols)
        if checks <= 0:
            raise ValueError("layout test vectors missing in tests/test_wm.c")
        return WmLayoutSyncResult(modes, symbols, checks)

    def render(self, result: WmLayoutSyncResult) -> str:
        """Docstring: Build manifest markdown from discovery result."""
        lines = [
            "# WM Layout Manifest",
            "",
            "I generate this file from `wm_layout.h` and `tests/test_wm.c`.",
            "I never edit it by hand. I run `tools/wm_layout_sync.py` instead.",
            "",
            "## Modes",
            "",
        ]
        for mode in result.modes:
            lines.append(f"- {mode}")
        lines.extend(["", "## Symbols", ""])
        for symbol in result.symbols:
            lines.append(f"- `{symbol}`")
        lines.extend(
            [
                "",
                "## Vectors",
                "",
                f"Host layout checks in `tests/test_wm.c`: {result.checks}.",
                "",
                "## Contracts",
                "",
                "- `wm_layout.h` owns placement for every mode.",
                "- `tests/test_wm.c` pins tile parity plus bsp, cascade,",
                "  fibonacci, fullscreen uniformity and fail-closed inputs.",
                "- Kernel `vga_fb_tile_all` consumes the plan and skips",
                "  redraws when the plan is unchanged.",
                "",
            ]
        )
        return "\n".join(lines)

    def synchronize(self, write: bool) -> WmLayoutSyncResult:
        """Docstring: Discover, render and optionally write the manifest."""
        result = self.discover()
        text = self.render(result)
        if write:
            self.config.manifest.parent.mkdir(parents=True, exist_ok=True)
            self.config.manifest.write_text(text, encoding="utf-8")
        return result

    def _read_text(self, path: pathlib.Path) -> str:
        """Docstring: Read one source file or fail with a clear error."""
        if not path.is_file():
            raise FileNotFoundError(f"missing source: {path}")
        return path.read_text(encoding="utf-8")

    def _extract_modes(self, header_text: str) -> list[str]:
        """Docstring: Collect layout mode names from the mode table."""
        found = re.findall(r'return\s+"(tile|bsp|cascade|fibonacci|fullscreen)"', header_text)
        ordered: list[str] = []
        for mode in self.config.required_modes:
            if mode in found and mode not in ordered:
                ordered.append(mode)
        return ordered

    def _extract_symbols(self, header_text: str) -> list[str]:
        """Docstring: Collect required public symbols present in header."""
        present: list[str] = []
        for symbol in self.config.required_symbols:
            if re.search(rf"\b{re.escape(symbol)}\b", header_text):
                present.append(symbol)
        return present

    def _count_layout_checks(self, tests_text: str) -> int:
        """Docstring: Count layout assertions guarding the contract."""
        hits = re.findall(r"wm_layout_[a-z_]+\(", tests_text)
        return len(hits)

    def _require_modes(self, modes: list[str]) -> None:
        """Docstring: Refuse a header missing any required mode."""
        missing = [m for m in self.config.required_modes if m not in modes]
        if missing:
            raise ValueError(f"layout modes missing: {','.join(missing)}")

    def _require_symbols(self, symbols: list[str]) -> None:
        """Docstring: Refuse a header missing any required symbol."""
        missing = [s for s in self.config.required_symbols if s not in symbols]
        if missing:
            raise ValueError(f"layout symbols missing: {','.join(missing)}")


def parse_args(argv: list[str]) -> argparse.Namespace:
    """Docstring: Parse CLI flags for check or write modes."""
    parser = argparse.ArgumentParser(description="Sync WM layout manifest from source.")
    parser.add_argument("--check", action="store_true", help="verify manifest without writing")
    parser.add_argument("--root", default=".", help="repository root holding wm_layout.h")
    return parser.parse_args(argv)


def main(argv: list[str]) -> int:
    """Docstring: Run discovery and write or verify the manifest."""
    args = parse_args(argv)
    root = pathlib.Path(args.root).resolve()
    config = WmLayoutSyncConfig(root)
    sync = WmLayoutSync(config)
    try:
        result = sync.discover()
    except (FileNotFoundError, ValueError) as exc:
        print(f"wm_layout_sync: {exc}", file=sys.stderr)
        return 1
    if args.check:
        if not config.manifest.is_file():
            print("wm_layout_sync: manifest missing", file=sys.stderr)
            return 1
        current = config.manifest.read_text(encoding="utf-8")
        expected = sync.render(result)
        if current != expected:
            print("wm_layout_sync: manifest drifted, run without --check", file=sys.stderr)
            return 1
        print(f"wm_layout_sync: ok ({len(result.modes)} modes, {result.checks} checks)")
        return 0
    sync.synchronize(write=True)
    print(f"wm_layout_sync: wrote {config.manifest} ({len(result.modes)} modes, {result.checks} checks)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
