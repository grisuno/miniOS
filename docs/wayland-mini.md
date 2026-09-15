# Wayland-mini: subset Wayland para miniOS (spec)

Estado: implementacion por fases (F0-F3). No es Weston ni libwayland
completo: es un wire subset + compositor ring-3 que reutiliza el
compositor kernel existente (`GFX_PRESENT`).

## Por que no portar libwayland

`libwayland` de freedesktop asume `AF_UNIX + SCM_RIGHTS`, `mmap/shm`,
`epoll`, `wayland-scanner` en runtime. miniOS no tiene sockets UNIX ni
paso de fds, y su red es TCP/UDP slirp (`10.0.2.x`). NovaOS
(`Wayland/client.h`) tampoco es Wayland completo: tabla de 32 clientes
sobre socket. El camino honesto es implementar el protocolo sobre
primitivas miniOS.

## Subset (congelado)

Interfaces: `wl_display`, `wl_registry`, `wl_compositor`, `wl_surface`,
`wl_shm`, `wl_shm_pool`, `wl_buffer`, `xdg_wm_base`, `xdg_surface`,
`xdg_toplevel`. Nada mas: sin decoracion cliente, sin DMA-BUF, sin
output hotplug, sin seat completo (puntero+teclado basico via
`SYS_MOUSE`/`SYS_KBD` ya existentes).

Wire format (igual que Wayland): cabecera `object_id u32 + opcode u16 +
size u16`, args `int/uint/string/fd`. Limites (`progs/wl/wl_mini.h`):
`WL_MAX_MSG 4096`, `WL_MAX_STR 256`, `WL_MAX_SURFACES 8`,
`WL_MAX_POOLS 8`, superficies max `800x360` (igual que `MINIOS_NK_W/H`).
Todo lo que exceda falla cerrado (`WL_ERR_*`), nunca trunca.

## Transporte

Fase 1: `pipe()` + memoria compartida sustituta: pool fijo por
superficie en heap del compositor, cliente escribe via `WL_ATTACH`
(syscall 243, reserva) o via `pipe` en modo shim. Sin `SCM_RIGHTS`:
el fd se sustituye por `pool_id` + `offset` validados contra la ventana
de usuario. Fase posterior: `AF_UNIX` real si el kernel lo gana.

## Compositor

`bin/wlcomp` ring-3 (no kernel): posee N<=8 superficies, z-order por
foco, compone sobre `FB_ADDR` y presenta con `GFX_PRESENT BUF_NK`
(compat con `vga_fb_blit_nk_window`). Input: foco posee `SYS_MOUSE` /
`SYS_KBD` (misma regla que `vga_fb_ps2_owner`). Titulo por
`GFX_SET_TITLE`. Contador `gfx frames` existente prueba render.

## Syscalls reservados (no cableados aun)

`243 WL_ATTACH`, `244 WL_COMMIT`, `245 WL_INPUT`. Definidos en
`progs/minios_abi.h`, fuera del checksum hasta que el kernel los
responda (entonces se sube `MINIOS_ABI_VERSION`). Hoy wlcomp corre en
modo shim `pipe()` sin necesitarlos.

## Pruebas

`make test-wl` (`tests/test_wl.c` vs `progs/wl/wl_mini.h`): encode/
decode, bounds, string truncada, object_id salvaje, pool overflow,
z-order. BDD: `wlcomp --selftest` imprime `wlcomp: frame ok (800x360)`.
Mutantes: size mentiroso, opcode truncado, attach fuera de ventana.
