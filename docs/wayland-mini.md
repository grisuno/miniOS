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

Fase 1 (hecha): el wire de attach/commit existe como encode/decode
puros (`wl_attach_encode/decode` para pool mas dimensiones,
`wl_commit_encode/decode` para el id de superficie) y cada cliente lo
habla logicamente: `freedom_wl` lo recorre en su selftest y en su
sonda de host. Sin `SCM_RIGHTS`: el fd se sustituye por `pool_id`
validado. El transporte vivo entre procesos por `pipe()` sigue abierto:
las superficies son estado dentro del compositor y ningun byte shm
cruza procesos todavia. Fase posterior: `AF_UNIX` real si el kernel
lo gana.

Shared clipboard: object `WL_ID_CLIPBOARD` with `WL_OP_CLIPBOARD_SET`
(publish) and `WL_OP_CLIPBOARD_GET` (fetch), bounded by `WL_CLIP_MAX`
4096 bytes through `wl_clip_encode/decode` (fail-closed on oversize,
truncation and liar sizes, same discipline as attach/commit). The
kernel slot behind syscalls 249/250 and the shell `clip` builtin speak
the same bounds. Terminal selection and vedit paste on top are Phase 2.

## Compositor

`bin/wlcomp` ring-3 (no kernel): posee N<=8 superficies, z-order por
foco, las embaldosa con `wl_comp_layout_tile` (una llena, dos en
vertical, tres o mas en rejilla), compone pixeles reales de cliente
con `wlcomp_blit` sobre el back-buffer NK y presenta con
`GFX_PRESENT BUF_NK` (compat con `vga_fb_blit_nk_window`). Geometria
movil por `wl_comp_set_rect` con validacion. Input: foco posee
`SYS_MOUSE` / `SYS_KBD` (misma regla que `vga_fb_ps2_owner`). Titulo
por `GFX_SET_TITLE`. Contador `gfx frames` existente prueba render.

## Syscalls reservados (no cableados aun)

`243 WL_ATTACH`, `244 WL_COMMIT`, `245 WL_INPUT`. Definidos en
`progs/minios_abi.h`, fuera del checksum hasta que el kernel los
responda (entonces se sube `MINIOS_ABI_VERSION`). Hoy wlcomp compone
en ring-3 sin necesitarlos.

## Sesion (Fase 2)

La sesion vive separada del transporte y corre sobre cualquier fuente
de bytes: `wl_stream_t` reensambla mensajes partidos en cualquier
punto (incluso a mitad de cabecera) con buffer acotado
(`WL_STREAM_CAP`, `WL_ERR_MORE` pide mas bytes, un size mentiroso
mata la conexion), `wl_iface_t` lleva las tablas de descriptores
escritas a mano para las diez interfaces (sin scanner a esta escala),
`wl_comp_attach_buf` enlaza un buffer a su superficie, y
`wl_dispatch` enruta cada pedido del subset a las operaciones
`wl_comp_*` existentes, fallando cerrado ante id salvaje, opcode
desconocido y payload corto. `wlcomp --selftest` lo prueba con una
sesion sintetica de nueve mensajes alimentada en dos trozos.

## Multiproceso y escritorio (Fase 3)

El transporte mailbox lleva los primeros bytes vivos entre procesos
sin ningun cambio de kernel: un mensaje de wire por fichero bajo
`/shm/wl/<box>-<seq>.msg` (magia `WLMB` mas secuencia), pixeles al
lado como `<box>.raw` del tamano exacto del ultimo attach. El
servidor drena como maximo `WL_MBOX_POLL_MAX` ficheros por tick en
el orden listado (attach y commit son independientes del orden por
construccion), valida cada marco antes de despachar, borra lo
consumido y deja los escritos a medias para el proximo poll. Una
superficie por conexion (la caja duena su slot) acota el servidor a
`WL_MAX_SURFACES` sin tabla de traduccion; el espacio completo de
ids queda para el futuro carrier `pipe()`. El ruteo vive en
`wl_mbox_route` (puro y testeado) y la frescura en `wl_mbox_fresh`;
el IO (stdio, `DIR_LIST`, `unlink`) queda en `wlcomp.c` y se prueba
vivo en guest.

`wlcomp` deja de ser demo de un disparo: `--server` dueno de la
pantalla por `SYS_VGA_MODE`, sube la paleta compartida antes de cada
present, enfoca al click, arrastra con `wl_comp_set_rect`, remalla
con `t`, sale con ESC redibujando el escritorio. `--once` drena una
vez para scripts. `--client` adjunta una superficie desde otro
proceso. `--clean` borra el directorio. Como el layout redimensiona
celdas y los pixeles llegan al tamano del attach, el servidor
reescala al encajar (`wl_scale_nearest`, vecino mas cercano); un raw
mentiroso cae a tinta solida, nunca a marco roto.

La paleta hibrida de 768 bytes vivia en tres copias identicas
mientras el programa que mas la necesitaba no tenia ninguna, y en
VBE truecolor eso se leia como glitch. Hoy vive una vez en
`progs/nk_palette.h` con los tres sitios como envoltorios delgados,
y `wlcomp` la sube antes de cada present como toda app NK.

## Pruebas

`make test-wl` (`tests/test_wl.c` vs `progs/wl/wl_mini.h`): encode/
decode, bounds, string truncada, object_id salvaje, pool overflow,
z-order, rectangulos, geometria de embaldosado, blit de pixeles,
roundtrip de attach/commit y pool/id salvaje en decode, reensamblado
partido, sesion completa de nueve mensajes y tabla de interfaces. BDD:
`wlcomp --selftest` imprime `wlcomp: frame ok (800x360)`.
Mutantes: size mentiroso, opcode truncado, attach fuera de ventana,
columnas de layout, borde de blit, id de commit, ajuste de rect,
stream partido, consume salteado, attach corto, tamano de creacion,
lookup de interfaz. Decisión: `docs/adr/0025-wayland-session.md`.
