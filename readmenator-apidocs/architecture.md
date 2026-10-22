# miniOS Architecture and Execution Flows

[Back to index](index.md)

## Architecture Overview

17 components stacked in 4 dependency tiers (weighted Eades-Lin-Smyth ordering: arrows point from dependent to dependency, top to bottom). Labels are import counts, thick arrows the top quartile; 4 transitively implied edges are omitted. Dashed red arrows are upward dependencies: the smallest set of imports that closes every cycle and breaks the layering. Cyan components hold entry points. Interactive version: `readmenator-apidocs/index.html#/flows`.

Upward dependencies to fix first: `progs/doomgeneric: p_spec` -> `progs/doomgeneric: d_englsh` (63 imports); `progs/doomgeneric: net_defs` -> `progs/doomgeneric: d_englsh` (12 imports); `progs/src` -> `progs/doomgeneric: d_englsh` (3 imports); `headers: kernel` -> `tools: tls_crypto` (2 imports); `headers: kernel` -> `headers: vga_fb` (2 imports); `tools: tls_crypto` -> `progs/doomgeneric: d_englsh` (2 imports); `progs/doomgeneric: net_defs` -> `progs/doomgeneric: p_spec` (2 imports); `progs/src` -> `headers: kernel` (1 imports); `progs/src` -> `progs/doomgeneric: p_spec` (1 imports)

```mermaid
flowchart TB
    classDef cycle fill:#1f1530,stroke:#f472b6,color:#fce7f3,stroke-width:2px;
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    subgraph lane_0["Tier 1 - entry / orchestration"]
        direction LR
        n_c1["progs/doomgeneric: d_englsh<br/>98 files, 2045 symbols<br/>Core / utility"]:::cycle
        n_c4["tools: tls_crypto<br/>30 files, 583 symbols<br/>Core / utility"]:::cycle
        n_c5["headers: vga_fb<br/>15 files, 384 symbols<br/>Core / utility"]:::cycle
        n_d_tools["tools<br/>35 files, 233 symbols<br/>Core / utility"]:::default
        n_d_progs["progs<br/>50 files, 813 symbols<br/>Core / utility"]:::default
        n_d_mcp["mcp<br/>2 files, 1 symbols<br/>Core / utility"]:::default
        n_d_kernel["kernel<br/>7 files, 83 symbols<br/>Core / utility"]:::default
        n_d_fs["fs<br/>2 files, 35 symbols<br/>Core / utility"]:::default
        n_d_arch["arch<br/>2 files, 10 symbols<br/>Core / utility"]:::default
        n_d__root_["(root)<br/>1 files, 2 symbols<br/>Core / utility"]:::default
        n_c9["tools: doom_pwad<br/>1 files, 25 symbols<br/>Core / utility"]:::default
    end
    subgraph lane_1["Tier 2"]
        direction LR
        n_c0["headers: kernel<br/>113 files, 4062 symbols<br/>Core / utility"]:::cycle
        n_c3["progs/doomgeneric: p_spec<br/>67 files, 1027 symbols<br/>Core / utility"]:::cycle
    end
    subgraph lane_2["Tier 3"]
        direction LR
        n_c6["progs/doomgeneric: net_defs<br/>13 files, 140 symbols<br/>Core / utility"]:::cycle
        n_c8["headers: tick<br/>2 files, 27 symbols<br/>Core / utility"]:::default
        n_c7["headers: batch<br/>2 files, 13 symbols<br/>Core / utility"]:::default
    end
    subgraph lane_3["Tier 4 - foundation"]
        direction LR
        n_c2["progs/src<br/>67 files, 2550 symbols<br/>Core / utility"]:::cycle
    end
    n_c0 ==>|"9"| n_c2
    n_c0 -->|"1"| n_c7
    n_c0 -->|"1"| n_c8
    n_c1 ==>|"77"| n_c3
    n_c3 -->|"4"| n_c6
    n_c4 -->|"3"| n_c0
    n_c5 ==>|"8"| n_c0
    n_c6 -->|"2"| n_c2
    n_c4 <-.-|"2 upward"| n_c0
    n_c5 <-.-|"2 upward"| n_c0
    n_c0 <-.-|"1 upward"| n_c2
    n_c1 <-.-|"3 upward"| n_c2
    n_c3 <-.-|"1 upward"| n_c2
    n_c1 <-.-|"63 upward"| n_c3
    n_c1 <-.-|"2 upward"| n_c4
    n_c1 <-.-|"12 upward"| n_c6
    n_c3 <-.-|"2 upward"| n_c6
    linkStyle 8,9,10,11,12,13,14,15,16 stroke:#f87171,stroke-width:2px;
    n_c1 ~~~ n_c0
    n_c0 ~~~ n_c6
    n_c6 ~~~ n_c2
```

---

## Execution Flows

Entry points are scored from `__main__` guards, `main` functions, entry-style names and files, and call-graph sources. Each flow walks resolved calls in call-site order (depth <= 4, <= 40 steps); numbers give the call order, dashed arrows revisit an already expanded callee, red arrows are recursion. Interactive version with zoom and per-node docs: `readmenator-apidocs/index.html#/flows`.

### `bootloader.main`

`bootloader.c:21`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    n_bootloader_c__main["bootloader.main<br/>bootloader.c:21"]:::entry
    n_bootloader_c__main -.->|"recursion"| n_bootloader_c__main
    linkStyle 0 stroke:#f87171,stroke-width:2px;
```

### `doomedit.main`

`progs/doomedit/doomedit.c:2246`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    classDef external fill:#1a1530,stroke:#a78bfa,color:#ede9fe;
    n_progs_doomedit_doomedit_c__main["doomedit.main<br/>doomedit.c:2246"]:::entry
    n_progs_doomedit_doomedit_c__dmap_selftest["doomedit.dmap_selftest<br/>/** Headless demo room shared by --demo and t...<br/>doomedit.c:2122"]:::default
    n_progs_nuklear_nuklear_minios_h__nk_minios_font["nuklear_minios.nk_minios_font<br/>Hybrid palette: indices 0-14 are the desktop...<br/>nuklear_minios.h:63"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_sys_vga_mode["nuklear_minios.nk_sys_vga_mode<br/>nuklear_minios.h:45"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_sys_kbd_raw["nuklear_minios.nk_sys_kbd_raw<br/>nuklear_minios.h:44"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_build_palette["nuklear_minios.nk_build_palette<br/>Hybrid palette: indices 0-14 are the desktop...<br/>nuklear_minios.h:57"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_sys_palette["nuklear_minios.nk_sys_palette<br/>nuklear_minios.h:43"]:::external
    n_progs_doomedit_doomedit_c__dmap_new["doomedit.dmap_new<br/>case DMAP_RSUIT: case DMAP_CMAP: case DMAP_LA...<br/>doomedit.c:639"]:::default
    n_progs_doomedit_doomedit_c__dmap_push_history["doomedit.dmap_push_history<br/>doomedit.c:272"]:::default
    n_progs_nuklear_nuklear_minios_h__nk_rasterize["nuklear_minios.nk_rasterize<br/>Hybrid palette: indices 0-14 are the desktop...<br/>nuklear_minios.h:66"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_rgb_available["nuklear_minios.nk_rgb_available<br/>RGB companion buffer (R,G,B byte order, NK_W...<br/>nuklear_minios.h:33"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_sys_nk_frame["nuklear_minios.nk_sys_nk_frame<br/>nuklear_minios.h:52"]:::external
    n_progs_nuklear_nuklear_minios_h__nk_sys_fb_info["nuklear_minios.nk_sys_fb_info<br/>nuklear_minios.h:46"]:::external
    n_progs_doomedit_doomedit_c__dmap_demo_room["doomedit.dmap_demo_room<br/>nk_set_window_origin(origin[0], origin[1])#59; n...<br/>doomedit.c:2110"]:::default
    n_progs_doomedit_doomedit_c__dmap_build_wad["doomedit.dmap_build_wad<br/>Compile the grid into a vanilla multi-sector...<br/>doomedit.c:1343"]:::default
    n_progs_doomedit_doomedit_c__dmap_validate["doomedit.dmap_validate<br/>dmap_sec_floor[nsec] = DMAP_FLOOR_H#59; dmap_sec...<br/>doomedit.c:1244"]:::default
    n_progs_doomedit_doomedit_c__dmap_walkable["doomedit.dmap_walkable<br/>__asm__ volatile(#quot;syscall#quot; : #quot;=a#quot;(ret) : #quot;a#quot;(...<br/>doomedit.c:577"]:::default
    n_progs_doomedit_doomedit_c__dmap_is_wall["doomedit.dmap_is_wall<br/>: #quot;rcx#quot;, #quot;r11#quot;, #quot;memory#quot;)#59; return ret#59; } /**...<br/>doomedit.c:570"]:::default
    n_progs_doomedit_doomedit_c__dmap_label_regions["doomedit.dmap_label_regions<br/>Sector table backing the multi-sector exporter.<br/>doomedit.c:1163"]:::default
    n_progs_doomedit_doomedit_c__dmap_thing_type["doomedit.dmap_thing_type<br/>Thing type ids from the engine mobjinfo table...<br/>doomedit.c:165"]:::default
    n_progs_doomedit_doomedit_c__dmap_w16["doomedit.dmap_w16<br/>doomedit.c:1318"]:::default
    n_progs_doomedit_doomedit_c__dmap_wtex["doomedit.dmap_wtex<br/>doomedit.c:1326"]:::default
    n_progs_doomedit_doomedit_c__dmap_w8["doomedit.dmap_w8<br/>doomedit.c:1317"]:::default
    n_progs_doomedit_doomedit_c__dmap_seg_angle["doomedit.dmap_seg_angle<br/>dmap_wp++ = (unsigned char)(v & 0xFF)#59; dmap_w...<br/>doomedit.c:1333"]:::default
    n_progs_doomedit_doomedit_c__dmap_w32["doomedit.dmap_w32<br/>doomedit.c:1322"]:::default
    n_progs_doomedit_doomedit_c__main -.->|"recursion"| n_progs_doomedit_doomedit_c__main
    n_progs_doomedit_doomedit_c__main -->|"1"| n_progs_doomedit_doomedit_c__dmap_selftest
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"1"| n_progs_nuklear_nuklear_minios_h__nk_minios_font
    n_progs_nuklear_nuklear_minios_h__nk_minios_font -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_minios_font
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"2"| n_progs_nuklear_nuklear_minios_h__nk_sys_vga_mode
    n_progs_nuklear_nuklear_minios_h__nk_sys_vga_mode -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_sys_vga_mode
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"3"| n_progs_nuklear_nuklear_minios_h__nk_sys_kbd_raw
    n_progs_nuklear_nuklear_minios_h__nk_sys_kbd_raw -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_sys_kbd_raw
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"4"| n_progs_nuklear_nuklear_minios_h__nk_build_palette
    n_progs_nuklear_nuklear_minios_h__nk_build_palette -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_build_palette
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"5"| n_progs_nuklear_nuklear_minios_h__nk_sys_palette
    n_progs_nuklear_nuklear_minios_h__nk_sys_palette -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_sys_palette
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"6"| n_progs_doomedit_doomedit_c__dmap_new
    n_progs_doomedit_doomedit_c__dmap_new -->|"1"| n_progs_doomedit_doomedit_c__dmap_push_history
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"7"| n_progs_nuklear_nuklear_minios_h__nk_rasterize
    n_progs_nuklear_nuklear_minios_h__nk_rasterize -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_rasterize
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"8"| n_progs_nuklear_nuklear_minios_h__nk_rgb_available
    n_progs_nuklear_nuklear_minios_h__nk_rgb_available -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_rgb_available
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"9"| n_progs_nuklear_nuklear_minios_h__nk_sys_nk_frame
    n_progs_nuklear_nuklear_minios_h__nk_sys_nk_frame -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_sys_nk_frame
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"10"| n_progs_nuklear_nuklear_minios_h__nk_sys_fb_info
    n_progs_nuklear_nuklear_minios_h__nk_sys_fb_info -.->|"recursion"| n_progs_nuklear_nuklear_minios_h__nk_sys_fb_info
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"11"| n_progs_doomedit_doomedit_c__dmap_demo_room
    n_progs_doomedit_doomedit_c__dmap_demo_room -.-> n_progs_doomedit_doomedit_c__dmap_new
    n_progs_doomedit_doomedit_c__dmap_selftest -->|"12"| n_progs_doomedit_doomedit_c__dmap_build_wad
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"1"| n_progs_doomedit_doomedit_c__dmap_validate
    n_progs_doomedit_doomedit_c__dmap_validate -->|"1"| n_progs_doomedit_doomedit_c__dmap_walkable
    n_progs_doomedit_doomedit_c__dmap_validate -->|"2"| n_progs_doomedit_doomedit_c__dmap_is_wall
    n_progs_doomedit_doomedit_c__dmap_validate -->|"3"| n_progs_doomedit_doomedit_c__dmap_label_regions
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"2"| n_progs_doomedit_doomedit_c__dmap_thing_type
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"3"| n_progs_doomedit_doomedit_c__dmap_is_wall
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"4"| n_progs_doomedit_doomedit_c__dmap_walkable
    n_progs_doomedit_doomedit_c__dmap_walkable -.-> n_progs_doomedit_doomedit_c__dmap_thing_type
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"5"| n_progs_doomedit_doomedit_c__dmap_w16
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"6"| n_progs_doomedit_doomedit_c__dmap_wtex
    n_progs_doomedit_doomedit_c__dmap_wtex -->|"1"| n_progs_doomedit_doomedit_c__dmap_w8
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"7"| n_progs_doomedit_doomedit_c__dmap_seg_angle
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"8"| n_progs_doomedit_doomedit_c__dmap_w8
    n_progs_doomedit_doomedit_c__dmap_build_wad -->|"9"| n_progs_doomedit_doomedit_c__dmap_w32
    n_progs_doomedit_doomedit_c__dmap_w32 -.-> n_progs_doomedit_doomedit_c__dmap_w16
    linkStyle 0,3,5,7,9,11,15,17,19,21 stroke:#f87171,stroke-width:2px;
```

Cross-file sequence:

```mermaid
sequenceDiagram
    autonumber
    participant p_progs_doomedit_doomedit_c as doomedit.c
    participant p_progs_nuklear_nuklear_minios_h as nuklear_minios.h
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_minios_font()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_sys_vga_mode()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_sys_kbd_raw()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_build_palette()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_sys_palette()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_rasterize()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_rgb_available()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_sys_nk_frame()
    p_progs_doomedit_doomedit_c->>p_progs_nuklear_nuklear_minios_h: nk_sys_fb_info()
```

### `i_main.main`

`progs/doomgeneric/i_main.c:40`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    n_progs_doomgeneric_i_main_c__main["i_main.main<br/>i_main.c:40"]:::entry
    n_progs_doomgeneric_i_main_c__M_FindResponseFile["i_main.M_FindResponseFile<br/>i_main.c:35"]:::default
    n_progs_doomgeneric_i_main_c__dg_Create["i_main.dg_Create<br/>i_main.c:37"]:::default
    n_progs_doomgeneric_i_main_c__D_DoomMain["i_main.D_DoomMain<br/>i_main.c:33"]:::default
    n_progs_doomgeneric_i_main_c__main -.->|"recursion"| n_progs_doomgeneric_i_main_c__main
    n_progs_doomgeneric_i_main_c__main -->|"1"| n_progs_doomgeneric_i_main_c__M_FindResponseFile
    n_progs_doomgeneric_i_main_c__M_FindResponseFile -.->|"recursion"| n_progs_doomgeneric_i_main_c__M_FindResponseFile
    n_progs_doomgeneric_i_main_c__main -->|"2"| n_progs_doomgeneric_i_main_c__dg_Create
    n_progs_doomgeneric_i_main_c__dg_Create -.->|"recursion"| n_progs_doomgeneric_i_main_c__dg_Create
    n_progs_doomgeneric_i_main_c__main -->|"3"| n_progs_doomgeneric_i_main_c__D_DoomMain
    n_progs_doomgeneric_i_main_c__D_DoomMain -.->|"recursion"| n_progs_doomgeneric_i_main_c__D_DoomMain
    linkStyle 0,2,4,6 stroke:#f87171,stroke-width:2px;
```

---
