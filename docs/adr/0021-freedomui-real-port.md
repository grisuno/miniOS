# ADR-0021: Real FreeDom browser on MiniOS (DOOM/Q2G pattern)

Status: accepted

## Context

`freedom_wl` is a text browser in a graphics window: it reimplements fetch,
filter and layout instead of running the FreeDom engine. The engine already
separates pure core from orchestrator: `url` (omnibox, RFC 3986), `link_nav`
(href policy), `html_parse` (Lexbor, scripts stripped), `ui_layout` (wrap,
scroll clamp) carry no Wayland or Cairo dependency. DOOM and Quake 2 prove
the hosting shape: host gcc `-static -no-pie` links upstream plus one
platform file, the ELF ships on MiniFS and runs as a ring-3 process through
the Linux syscall ABI plus MiniOS syscalls. Lexbor ships a static archive
on the build host, so static linkage is possible.

## Decision

**Platform layer.** `progs/freedomui/freedomui_minios.c` owns the mapping in
one file. The NK back-buffer window (`MINIOS_NK_W` x `MINIOS_NK_H`) is the
surface. Present uses `GFX_PRESENT` with `BUF_NK`. Title uses
`GFX_SET_TITLE`. Pointer uses `SYS_MOUSE`. Keyboard uses `SYS_KBD`.
Palette uses `SYS_PALETTE` with the Nuklear hybrid table before every
present, so the page stays visible on true-color VBE modes. Time uses
`SYS_TIME`. Display uses `VGA_MODE`. Fetch runs over the socket syscalls
with DNS from syscall 200 and https through the shared ring-3 TLS engine.
Every tunable lives in `FreedomUiConfig`. Every address comes from
`minios_abi.h`.

**Engine, not a rewrite.** Omnibox resolves through `url_omnibox`.
Parsing runs `hp_parse` with secure defaults. Text comes from
`hp_extract_text` and layout from `ui_wrap_text`, so the pixels are engine
output. `freedomui --selftest` parses built-in HTML and presents one frame.
`freedomui --once <url-or-query>` fetches, renders and exits for scripts
and the BDD suite. Search input is refused in v1 with a diagnostic.

**Out of scope for v1.** JS, images, video, sandbox confinement,
persistence. Each arrives as its own file behind its own ADR.

**Conditional build.** `FREEDOMUI_AVAILABLE` guards the rule like
`Q2G_AVAILABLE`: the sibling checkout plus the static Lexbor archive must
exist. `FREEDOMUI_LEXBOR` is overridable and derived from pkg-config, never
a hardcoded host path.

## Proof

Host suite `make test-freedomui` pins config, palette, omnibox, Lexbor
parse, wrap and probe. Guest binary `bin/freedomui` ships on MiniFS. BDD
pins `freedomui --selftest` (`frame ok (800x360)`) and
`freedomui --once http://10.0.2.2:8899/README.txt`
(`freedomui: 10.0.2.2 (`). Live boot proves `gfx frames` climbs 0 to 1.
Two mutants (palette-bg, omnibox-kind) die in `mutate.sh`.

## Consequences

`freedom_wl` stays as the http-only miniGCC twin path. Full box layout,
JS, images and confinement target this backend instead of raw syscalls.
No syscall number changes in this ADR, so the ABI version does not move.
