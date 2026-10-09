# Symbols (page 20 of 26)
Previous: [SYMBOLS_p19.md](SYMBOLS_p19.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `s_title` | function | `progs/minicraft/minicraft.c:448` | `static long s_title(const char *t)` |
| `s_vga` | function | `progs/minicraft/minicraft.c:433` | `static long s_vga(long on)` |
| `s_yield` | function | `progs/minicraft/minicraft.c:463` | `static void s_yield(void)` |
| `s_zoom` | function | `progs/minicraft/minicraft.c:458` | `static long s_zoom(long on)` |
| `save_chunk_file` | function | `progs/minicraft/minicraft.c:2942` | `static int save_chunk_file(int slot)` |
| `save_compute_crc` | function | `progs/minicraft/minicraft.c:2932` | `static uint32_t save_compute_crc(const SaveHeader *hd)` |
| `save_validate_loaded` | function | `progs/minicraft/minicraft.c:3056` | `static int save_validate_loaded(void)` |
| `save_world` | function | `progs/minicraft/minicraft.c:330` | `static int save_world(void);` |
| `sc_hist_push` | function | `progs/minicraft/minicraft.c:2151` | `static void sc_hist_push(unsigned char b)` |
| `selftest` | function | `progs/minicraft/minicraft.c:3345` | `static int selftest(void)` |
| `ser_get` | function | `progs/minicraft/minicraft.c:373` | `static long ser_get(void)` |
| `ser_unget` | function | `progs/minicraft/minicraft.c:386` | `static void ser_unget(unsigned char b)` |
| `set_b` | function | `progs/minicraft/minicraft.c:774` | `static void set_b(int x, int y, int z, unsigned char b)` |
| `set_b_raw` | function | `progs/minicraft/minicraft.c:790` | `static void set_b_raw(int x, int y, int z, unsigned char b)` |
| `shade_block` | function | `progs/minicraft/minicraft.c:1602` | `static unsigned char shade_block(unsigned char b, int face, int bx, int by, int bz,              ...` |
| `sky_color` | function | `progs/minicraft/minicraft.c:1569` | `static unsigned char sky_color(float dz, float sun_dot, int x, int y, float tsec)` |
| `sky_light` | function | `progs/minicraft/minicraft.c:801` | `static float sky_light(int x, int y, int z)` |
| `tick_discover` | function | `progs/minicraft/minicraft.c:2630` | `static void tick_discover(long now)` |
| `tick_goals` | function | `progs/minicraft/minicraft.c:2619` | `static void tick_goals(void)` |
| `tick_hunger` | function | `progs/minicraft/minicraft.c:2596` | `static void tick_hunger(long now)` |
| `tick_interact` | function | `progs/minicraft/minicraft.c:2668` | `static void tick_interact(void)` |
| `tick_mob` | function | `progs/minicraft/minicraft.c:1386` | `static void tick_mob(Pig *p, int id, float dt, long now)` |
| `tick_pigs` | function | `progs/minicraft/minicraft.c:1512` | `static void tick_pigs(float dt, long now)` |
| `tick_player` | function | `progs/minicraft/minicraft.c:2449` | `static void tick_player(float dt)` |
| `tick_water` | function | `progs/minicraft/minicraft.c:2548` | `static void tick_water(long now)` |
| `title_menu` | function | `progs/minicraft/minicraft.c:3754` | `static int title_menu(int have_save, int *seed_io)` |
| `try_autostep` | function | `progs/minicraft/minicraft.c:2413` | `static void try_autostep(float tx, float ty)` |
| `voro_site` | function | `progs/minicraft/minicraft.c:861` | `static void voro_site(int cx, int cy, unsigned int seed, int cell,     int *sx, int *sy)` |
| `world_max_recompute` | function | `progs/minicraft/minicraft.c:606` | `static void world_max_recompute(void)` |
| `DOOM_BACKBUF_ADDR` | function | `progs/minios_abi.h:128` | `* * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap), * so a growing heap or mmap region can...` |
| `MINIOS_ABI_CHECKSUM` | macro | `progs/minios_abi.h:45` | `#define MINIOS_ABI_CHECKSUM` |
| `MINIOS_ABI_H` | macro | `progs/minios_abi.h:2` | `#define MINIOS_ABI_H` |
| `MINIOS_ABI_VERSION` | macro | `progs/minios_abi.h:41` | `#define MINIOS_ABI_VERSION` |
| `MINIOS_DEV_MMIO_VBASE` | macro | `progs/minios_abi.h:209` | `#define MINIOS_DEV_MMIO_VBASE` |
| `MINIOS_DOOM_BACKBUF_ADDR` | macro | `progs/minios_abi.h:135` | `#define MINIOS_DOOM_BACKBUF_ADDR` |
| `MINIOS_DOOM_H` | macro | `progs/minios_abi.h:137` | `#define MINIOS_DOOM_H` |
| `MINIOS_DOOM_W` | macro | `progs/minios_abi.h:136` | `#define MINIOS_DOOM_W` |
| `MINIOS_EABI_MISMATCH` | macro | `progs/minios_abi.h:427` | `#define MINIOS_EABI_MISMATCH` |
| `MINIOS_FB_ADDR` | macro | `progs/minios_abi.h:138` | `#define MINIOS_FB_ADDR` |
| `MINIOS_FB_HEIGHT_MAX` | macro | `progs/minios_abi.h:215` | `#define MINIOS_FB_HEIGHT_MAX` |
| `MINIOS_FB_WIDTH_MAX` | macro | `progs/minios_abi.h:214` | `#define MINIOS_FB_WIDTH_MAX` |
| `MINIOS_GFX_BUF_GAME` | macro | `progs/minios_abi.h:397` | `#define MINIOS_GFX_BUF_GAME` |
| `MINIOS_GFX_BUF_NK` | macro | `progs/minios_abi.h:398` | `#define MINIOS_GFX_BUF_NK` |
| `MINIOS_GFX_BUF_NK_RGB` | macro | `progs/minios_abi.h:399` | `#define MINIOS_GFX_BUF_NK_RGB` |
| `MINIOS_GFX_ZOOM_2X` | macro | `progs/minios_abi.h:410` | `#define MINIOS_GFX_ZOOM_2X` |
| `MINIOS_GFX_ZOOM_FULLSCREEN` | macro | `progs/minios_abi.h:411` | `#define MINIOS_GFX_ZOOM_FULLSCREEN` |
| `MINIOS_GFX_ZOOM_NATIVE` | macro | `progs/minios_abi.h:409` | `#define MINIOS_GFX_ZOOM_NATIVE` |
| `MINIOS_GFX_ZOOM_WINDOWED` | macro | `progs/minios_abi.h:412` | `#define MINIOS_GFX_ZOOM_WINDOWED` |
| `MINIOS_HEAP_BASE` | macro | `progs/minios_abi.h:172` | `#define MINIOS_HEAP_BASE` |
| `MINIOS_HEAP_SIZE` | macro | `progs/minios_abi.h:173` | `#define MINIOS_HEAP_SIZE` |
| `MINIOS_LDSO_BASE` | macro | `progs/minios_abi.h:156` | `#define MINIOS_LDSO_BASE` |
| `MINIOS_LDSO_END` | macro | `progs/minios_abi.h:158` | `#define MINIOS_LDSO_END` |
| `MINIOS_LDSO_SIZE` | macro | `progs/minios_abi.h:157` | `#define MINIOS_LDSO_SIZE` |
| `MINIOS_NK_BACKBUF_ADDR` | macro | `progs/minios_abi.h:139` | `#define MINIOS_NK_BACKBUF_ADDR` |
| `MINIOS_NK_H` | macro | `progs/minios_abi.h:141` | `#define MINIOS_NK_H` |
| `MINIOS_NK_RGB_ADDR` | macro | `progs/minios_abi.h:166` | `#define MINIOS_NK_RGB_ADDR` |
| `MINIOS_NK_RGB_BYTES` | macro | `progs/minios_abi.h:167` | `#define MINIOS_NK_RGB_BYTES` |
| `MINIOS_NK_W` | macro | `progs/minios_abi.h:140` | `#define MINIOS_NK_W` |
| `MINIOS_PCI_MMIO_SIZE` | macro | `progs/minios_abi.h:197` | `#define MINIOS_PCI_MMIO_SIZE` |
| `MINIOS_PCM2_FRAG` | macro | `progs/minios_abi.h:386` | `#define MINIOS_PCM2_FRAG` |
| `MINIOS_PCM2_NONBLOCK` | macro | `progs/minios_abi.h:381` | `#define MINIOS_PCM2_NONBLOCK` |
| `MINIOS_PCM2_RATE` | macro | `progs/minios_abi.h:385` | `#define MINIOS_PCM2_RATE` |
| `MINIOS_SYS_ACCESS` | macro | `progs/minios_abi.h:248` | `#define MINIOS_SYS_ACCESS` |
| `MINIOS_SYS_ARCH_PRCTL` | macro | `progs/minios_abi.h:275` | `#define MINIOS_SYS_ARCH_PRCTL` |
| `MINIOS_SYS_BRK` | macro | `progs/minios_abi.h:243` | `#define MINIOS_SYS_BRK` |
| `MINIOS_SYS_CLIP_GET` | macro | `progs/minios_abi.h:363` | `#define MINIOS_SYS_CLIP_GET` |
| `MINIOS_SYS_CLIP_SET` | macro | `progs/minios_abi.h:362` | `#define MINIOS_SYS_CLIP_SET` |
| `MINIOS_SYS_CLOCK_GETTIME` | macro | `progs/minios_abi.h:293` | `#define MINIOS_SYS_CLOCK_GETTIME` |
| `MINIOS_SYS_CLONE` | macro | `progs/minios_abi.h:388` | `#define MINIOS_SYS_CLONE` |
| `MINIOS_SYS_CLOSE` | macro | `progs/minios_abi.h:236` | `#define MINIOS_SYS_CLOSE` |
| `MINIOS_SYS_CONNECT` | macro | `progs/minios_abi.h:252` | `#define MINIOS_SYS_CONNECT` |
| `MINIOS_SYS_DIR_LIST` | macro | `progs/minios_abi.h:339` | `#define MINIOS_SYS_DIR_LIST` |
| `MINIOS_SYS_DNS` | macro | `progs/minios_abi.h:297` | `#define MINIOS_SYS_DNS` |
| `MINIOS_SYS_DOOM_FRAME` | macro | `progs/minios_abi.h:313` | `#define MINIOS_SYS_DOOM_FRAME` |
| `MINIOS_SYS_EXECVE` | macro | `progs/minios_abi.h:258` | `#define MINIOS_SYS_EXECVE` |
| `MINIOS_SYS_EXIT` | macro | `progs/minios_abi.h:259` | `#define MINIOS_SYS_EXIT` |
| `MINIOS_SYS_EXIT_GROUP` | macro | `progs/minios_abi.h:291` | `#define MINIOS_SYS_EXIT_GROUP` |
| `MINIOS_SYS_FB_INFO` | macro | `progs/minios_abi.h:315` | `#define MINIOS_SYS_FB_INFO` |
| `MINIOS_SYS_FDATASYNC` | macro | `progs/minios_abi.h:272` | `#define MINIOS_SYS_FDATASYNC` |
| `MINIOS_SYS_FLOCK` | macro | `progs/minios_abi.h:270` | `#define MINIOS_SYS_FLOCK` |
| `MINIOS_SYS_FORK` | macro | `progs/minios_abi.h:256` | `#define MINIOS_SYS_FORK` |
| `MINIOS_SYS_FRAMEBUFFER_COMMIT` | macro | `progs/minios_abi.h:400` | `#define MINIOS_SYS_FRAMEBUFFER_COMMIT` |
| `MINIOS_SYS_FSTAT` | macro | `progs/minios_abi.h:237` | `#define MINIOS_SYS_FSTAT` |
| `MINIOS_SYS_FSYNC` | macro | `progs/minios_abi.h:271` | `#define MINIOS_SYS_FSYNC` |
| `MINIOS_SYS_FUTEX_WAIT` | macro | `progs/minios_abi.h:331` | `#define MINIOS_SYS_FUTEX_WAIT` |
| `MINIOS_SYS_FUTEX_WAKE` | macro | `progs/minios_abi.h:332` | `#define MINIOS_SYS_FUTEX_WAKE` |
| `MINIOS_SYS_GETCWD` | macro | `progs/minios_abi.h:273` | `#define MINIOS_SYS_GETCWD` |
| `MINIOS_SYS_GETC_RAW` | macro | `progs/minios_abi.h:334` | `#define MINIOS_SYS_GETC_RAW` |
| `MINIOS_SYS_GETPID` | macro | `progs/minios_abi.h:250` | `#define MINIOS_SYS_GETPID` |
| `MINIOS_SYS_GETRANDOM` | macro | `progs/minios_abi.h:289` | `#define MINIOS_SYS_GETRANDOM` |
| `MINIOS_SYS_GETTID` | macro | `progs/minios_abi.h:266` | `#define MINIOS_SYS_GETTID` |
| `MINIOS_SYS_GETTIMEOFDAY` | macro | `progs/minios_abi.h:274` | `#define MINIOS_SYS_GETTIMEOFDAY` |
| `MINIOS_SYS_GFX_PRESENT` | macro | `progs/minios_abi.h:335` | `#define MINIOS_SYS_GFX_PRESENT` |
| `MINIOS_SYS_GFX_SET_TITLE` | macro | `progs/minios_abi.h:324` | `#define MINIOS_SYS_GFX_SET_TITLE` |
| `MINIOS_SYS_GFX_ZOOM` | macro | `progs/minios_abi.h:340` | `#define MINIOS_SYS_GFX_ZOOM` |
| `MINIOS_SYS_IOCTL` | macro | `progs/minios_abi.h:246` | `#define MINIOS_SYS_IOCTL` |
| `MINIOS_SYS_KBD` | macro | `progs/minios_abi.h:307` | `#define MINIOS_SYS_KBD` |
| `MINIOS_SYS_KBD_RAW` | macro | `progs/minios_abi.h:309` | `#define MINIOS_SYS_KBD_RAW` |
| `MINIOS_SYS_KILL` | macro | `progs/minios_abi.h:261` | `#define MINIOS_SYS_KILL` |
| `MINIOS_SYS_LSEEK` | macro | `progs/minios_abi.h:239` | `#define MINIOS_SYS_LSEEK` |
| `MINIOS_SYS_LZ4_COMPRESS` | macro | `progs/minios_abi.h:318` | `#define MINIOS_SYS_LZ4_COMPRESS` |
| `MINIOS_SYS_LZ4_DECOMPRESS` | macro | `progs/minios_abi.h:319` | `#define MINIOS_SYS_LZ4_DECOMPRESS` |
| `MINIOS_SYS_MINFO` | macro | `progs/minios_abi.h:380` | `#define MINIOS_SYS_MINFO` |
| `MINIOS_SYS_MMAP` | macro | `progs/minios_abi.h:240` | `#define MINIOS_SYS_MMAP` |
| `MINIOS_SYS_MOUSE` | macro | `progs/minios_abi.h:320` | `#define MINIOS_SYS_MOUSE` |
| `MINIOS_SYS_MPROTECT` | macro | `progs/minios_abi.h:241` | `#define MINIOS_SYS_MPROTECT` |
| `MINIOS_SYS_MUNMAP` | macro | `progs/minios_abi.h:242` | `#define MINIOS_SYS_MUNMAP` |
| `MINIOS_SYS_NEWFSTATAT` | macro | `progs/minios_abi.h:277` | `#define MINIOS_SYS_NEWFSTATAT` |
| `MINIOS_SYS_NICE` | macro | `progs/minios_abi.h:337` | `#define MINIOS_SYS_NICE` |
| `MINIOS_SYS_NK_FRAME` | macro | `progs/minios_abi.h:321` | `#define MINIOS_SYS_NK_FRAME` |
| `MINIOS_SYS_OPEN` | macro | `progs/minios_abi.h:235` | `#define MINIOS_SYS_OPEN` |
| `MINIOS_SYS_OPENAT` | macro | `progs/minios_abi.h:276` | `#define MINIOS_SYS_OPENAT` |
| `MINIOS_SYS_PALETTE` | macro | `progs/minios_abi.h:308` | `#define MINIOS_SYS_PALETTE` |
| `MINIOS_SYS_PCM2_CLOSE` | macro | `progs/minios_abi.h:354` | `#define MINIOS_SYS_PCM2_CLOSE` |
| `MINIOS_SYS_PCM2_OPEN` | macro | `progs/minios_abi.h:352` | `#define MINIOS_SYS_PCM2_OPEN` |
| `MINIOS_SYS_PCM2_WRITE` | macro | `progs/minios_abi.h:353` | `#define MINIOS_SYS_PCM2_WRITE` |
| `MINIOS_SYS_PCSPK_INIT` | macro | `progs/minios_abi.h:311` | `#define MINIOS_SYS_PCSPK_INIT` |
| `MINIOS_SYS_PCSPK_TONE` | macro | `progs/minios_abi.h:312` | `#define MINIOS_SYS_PCSPK_TONE` |
| `MINIOS_SYS_PCSPK_VOL` | macro | `progs/minios_abi.h:316` | `#define MINIOS_SYS_PCSPK_VOL` |
| `MINIOS_SYS_POLL` | macro | `progs/minios_abi.h:238` | `#define MINIOS_SYS_POLL` |
| `MINIOS_SYS_PRLIMIT64` | macro | `progs/minios_abi.h:288` | `#define MINIOS_SYS_PRLIMIT64` |
| `MINIOS_SYS_READ` | macro | `progs/minios_abi.h:233` | `#define MINIOS_SYS_READ` |
| `MINIOS_SYS_READLINK` | macro | `progs/minios_abi.h:265` | `#define MINIOS_SYS_READLINK` |
| `MINIOS_SYS_RECVFROM` | macro | `progs/minios_abi.h:254` | `#define MINIOS_SYS_RECVFROM` |
| `MINIOS_SYS_RENAME` | macro | `progs/minios_abi.h:264` | `#define MINIOS_SYS_RENAME` |
| `MINIOS_SYS_RLIMIT` | macro | `progs/minios_abi.h:338` | `#define MINIOS_SYS_RLIMIT` |
| `MINIOS_SYS_RSEQ` | macro | `progs/minios_abi.h:290` | `#define MINIOS_SYS_RSEQ` |
| `MINIOS_SYS_RTC` | macro | `progs/minios_abi.h:314` | `#define MINIOS_SYS_RTC` |
| `MINIOS_SYS_RT_SIGACTION` | macro | `progs/minios_abi.h:244` | `#define MINIOS_SYS_RT_SIGACTION` |
| `MINIOS_SYS_RT_SIGPROCMASK` | macro | `progs/minios_abi.h:245` | `#define MINIOS_SYS_RT_SIGPROCMASK` |
| `MINIOS_SYS_SB16_OPEN` | macro | `progs/minios_abi.h:322` | `#define MINIOS_SYS_SB16_OPEN` |
| `MINIOS_SYS_SB16_PUMP` | macro | `progs/minios_abi.h:325` | `#define MINIOS_SYS_SB16_PUMP` |
| `MINIOS_SYS_SB16_STREAM_CLOSE` | macro | `progs/minios_abi.h:327` | `#define MINIOS_SYS_SB16_STREAM_CLOSE` |
| `MINIOS_SYS_SB16_STREAM_OPEN` | macro | `progs/minios_abi.h:326` | `#define MINIOS_SYS_SB16_STREAM_OPEN` |
| `MINIOS_SYS_SB16_STREAM_SUBMIT` | macro | `progs/minios_abi.h:328` | `#define MINIOS_SYS_SB16_STREAM_SUBMIT` |
| `MINIOS_SYS_SB16_STREAM_VOLUME` | macro | `progs/minios_abi.h:329` | `#define MINIOS_SYS_SB16_STREAM_VOLUME` |
| `MINIOS_SYS_SB16_SUBMIT` | macro | `progs/minios_abi.h:323` | `#define MINIOS_SYS_SB16_SUBMIT` |
| `MINIOS_SYS_SCHED_YIELD` | macro | `progs/minios_abi.h:249` | `#define MINIOS_SYS_SCHED_YIELD` |
| `MINIOS_SYS_SECCOMP` | macro | `progs/minios_abi.h:336` | `#define MINIOS_SYS_SECCOMP` |
| `MINIOS_SYS_SENDTO` | macro | `progs/minios_abi.h:253` | `#define MINIOS_SYS_SENDTO` |
| `MINIOS_SYS_SET_ROBUST_LIST` | macro | `progs/minios_abi.h:284` | `#define MINIOS_SYS_SET_ROBUST_LIST` |
| `MINIOS_SYS_SET_TID_ADDRESS` | macro | `progs/minios_abi.h:292` | `#define MINIOS_SYS_SET_TID_ADDRESS` |
| `MINIOS_SYS_SHUTDOWN` | macro | `progs/minios_abi.h:255` | `#define MINIOS_SYS_SHUTDOWN` |
| `MINIOS_SYS_SOCKET` | macro | `progs/minios_abi.h:251` | `#define MINIOS_SYS_SOCKET` |
| `MINIOS_SYS_SPAWN` | macro | `progs/minios_abi.h:317` | `#define MINIOS_SYS_SPAWN` |
| `MINIOS_SYS_STATX` | macro | `progs/minios_abi.h:280` | `#define MINIOS_SYS_STATX` |
| `MINIOS_SYS_SUBMIT_BATCH` | macro | `progs/minios_abi.h:333` | `#define MINIOS_SYS_SUBMIT_BATCH` |
| `MINIOS_SYS_TGKILL` | macro | `progs/minios_abi.h:294` | `#define MINIOS_SYS_TGKILL` |
| `MINIOS_SYS_THREAD_SPAWN` | macro | `progs/minios_abi.h:330` | `#define MINIOS_SYS_THREAD_SPAWN` |
| `MINIOS_SYS_TIME` | macro | `progs/minios_abi.h:306` | `#define MINIOS_SYS_TIME` |
| `MINIOS_SYS_TLS_HANDSHAKE` | macro | `progs/minios_abi.h:303` | `#define MINIOS_SYS_TLS_HANDSHAKE` |
| `MINIOS_SYS_TLS_RECV` | macro | `progs/minios_abi.h:305` | `#define MINIOS_SYS_TLS_RECV` |
| `MINIOS_SYS_TLS_SEND` | macro | `progs/minios_abi.h:304` | `#define MINIOS_SYS_TLS_SEND` |
| `MINIOS_SYS_UNAME` | macro | `progs/minios_abi.h:262` | `#define MINIOS_SYS_UNAME` |
| `MINIOS_SYS_UNLINK` | macro | `progs/minios_abi.h:263` | `#define MINIOS_SYS_UNLINK` |
| `MINIOS_SYS_VFORK` | macro | `progs/minios_abi.h:257` | `#define MINIOS_SYS_VFORK` |
| `MINIOS_SYS_VGA_MODE` | macro | `progs/minios_abi.h:310` | `#define MINIOS_SYS_VGA_MODE` |
| `MINIOS_SYS_WAIT4` | macro | `progs/minios_abi.h:260` | `#define MINIOS_SYS_WAIT4` |
| `MINIOS_SYS_WINDOW_PRESENT` | macro | `progs/minios_abi.h:401` | `#define MINIOS_SYS_WINDOW_PRESENT` |
| `MINIOS_SYS_WINDOW_TITLE` | macro | `progs/minios_abi.h:402` | `#define MINIOS_SYS_WINDOW_TITLE` |
| `MINIOS_SYS_WL_ATTACH` | macro | `progs/minios_abi.h:345` | `#define MINIOS_SYS_WL_ATTACH` |
| `MINIOS_SYS_WL_COMMIT` | macro | `progs/minios_abi.h:346` | `#define MINIOS_SYS_WL_COMMIT` |
| `MINIOS_SYS_WL_INPUT` | macro | `progs/minios_abi.h:347` | `#define MINIOS_SYS_WL_INPUT` |
| `MINIOS_SYS_WRITE` | macro | `progs/minios_abi.h:234` | `#define MINIOS_SYS_WRITE` |
| `MINIOS_SYS_WRITEV` | macro | `progs/minios_abi.h:247` | `#define MINIOS_SYS_WRITEV` |
| `MINIOS_USER_BRK_END` | macro | `progs/minios_abi.h:118` | `#define MINIOS_USER_BRK_END` |
| `MINIOS_USER_LOAD_BASE` | macro | `progs/minios_abi.h:113` | `#define MINIOS_USER_LOAD_BASE` |
| `MINIOS_USER_LOAD_END` | macro | `progs/minios_abi.h:114` | `#define MINIOS_USER_LOAD_END` |
| `MINIOS_USER_STACK_BASE` | macro | `progs/minios_abi.h:117` | `#define MINIOS_USER_STACK_BASE` |
| `MINIOS_USER_STACK_SIZE` | macro | `progs/minios_abi.h:115` | `#define MINIOS_USER_STACK_SIZE` |
| `MINIOS_USER_STACK_TOP` | macro | `progs/minios_abi.h:116` | `#define MINIOS_USER_STACK_TOP` |
| `SYS_FB_INFO` | macro | `progs/minios_abi.h:420` | `#define SYS_FB_INFO` |
| `SYS_PALETTE` | macro | `progs/minios_abi.h:416` | `#define SYS_PALETTE` |
| `SYS_PCSPK_INIT` | macro | `progs/minios_abi.h:417` | `#define SYS_PCSPK_INIT` |
| `SYS_PCSPK_TONE` | macro | `progs/minios_abi.h:418` | `#define SYS_PCSPK_TONE` |
| `SYS_PCSPK_VOL` | macro | `progs/minios_abi.h:421` | `#define SYS_PCSPK_VOL` |
| `SYS_RTC` | macro | `progs/minios_abi.h:419` | `#define SYS_RTC` |
| `SYS_SPAWN` | macro | `progs/minios_abi.h:422` | `#define SYS_SPAWN` |
| `SYS_TIME` | macro | `progs/minios_abi.h:423` | `#define SYS_TIME` |
| `SYS_TIME_MS` | macro | `progs/minios_abi.h:415` | `#define SYS_TIME_MS` |
| `SYS_WRITE` | macro | `progs/minios_abi.h:424` | `#define SYS_WRITE` |
| `in` | function | `progs/minios_abi.h:356` | `* bytes in (refused past 4096, never truncated), GET copies out up to * the caller's cap (refused when empty or...` |
| `MINIOS_PNG_H` | macro | `progs/minios_png.h:22` | `#define MINIOS_PNG_H` |
| `MPNG_BIG_DIM` | macro | `progs/minios_png.h:33` | `#define MPNG_BIG_DIM` |
| `MPNG_ERR_BOUND` | macro | `progs/minios_png.h:40` | `#define MPNG_ERR_BOUND` |
| `MPNG_ERR_EMPTY` | macro | `progs/minios_png.h:41` | `#define MPNG_ERR_EMPTY` |
| `MPNG_ERR_OK` | macro | `progs/minios_png.h:39` | `#define MPNG_ERR_OK` |
| `MPNG_FILE_MAX` | macro | `progs/minios_png.h:28` | `#define MPNG_FILE_MAX` |
| `MPNG_LEFT_N` | macro | `progs/minios_png.h:38` | `#define MPNG_LEFT_N` |
| `MPNG_MAX_DIM` | macro | `progs/minios_png.h:29` | `#define MPNG_MAX_DIM` |
| `MPNG_PAL_BYTES` | macro | `progs/minios_png.h:35` | `#define MPNG_PAL_BYTES` |
| `MPNG_PAL_N` | macro | `progs/minios_png.h:34` | `#define MPNG_PAL_N` |
| `MPNG_PATH_MAX` | macro | `progs/minios_png.h:36` | `#define MPNG_PATH_MAX` |
| `MPNG_RIGHT_PATH` | macro | `progs/minios_png.h:37` | `#define MPNG_RIGHT_PATH` |
| `bound` | function | `progs/minios_png.h:140` | `* its 512 source bound (pinned by the host suite), so icon and policy  * art never grow through t...` |
| `mpng_332_idx` | function | `progs/minios_png.h:58` | `static int mpng_332_idx(unsigned r, unsigned g, unsigned b)` |
| `mpng_blit_idx` | function | `progs/minios_png.h:196` | `static int mpng_blit_idx(unsigned char *fb, int fw, int fh,                          const unsign...` |
| `mpng_center` | function | `progs/minios_png.h:84` | `static int mpng_center(int outer, int inner)` |
| `mpng_fit_scale` | function | `progs/minios_png.h:93` | `static int mpng_fit_scale(int sw, int sh, int boxw, int boxh)` |
| `mpng_load_file` | function | `progs/minios_png.h:222` | `static int mpng_load_file(const char *path, unsigned char **out, long *out_n,                    ...` |
| `mpng_nearest` | function | `progs/minios_png.h:63` | `static int mpng_nearest(const unsigned char *pal, long pal_n, unsigned r,                        ...` |
| `mpng_rgb_to_332_scaled` | function | `progs/minios_png.h:172` | `static int mpng_rgb_to_332_scaled(const unsigned char *rgb, int sw, int sh,                      ...` |
| `mpng_rgb_to_idx_scaled` | function | `progs/minios_png.h:108` | `static int mpng_rgb_to_idx_scaled(const unsigned char *rgb, int sw, int sh,                      ...` |
| `NK_PALETTE_H` | macro | `progs/nk_palette.h:12` | `#define NK_PALETTE_H` |
| `NK_PAL_ACCENTS` | macro | `progs/nk_palette.h:18` | `#define NK_PAL_ACCENTS` |
| `NK_PAL_BYTES` | macro | `progs/nk_palette.h:14` | `#define NK_PAL_BYTES` |
| `NK_PAL_CUBE` | macro | `progs/nk_palette.h:16` | `#define NK_PAL_CUBE` |
| `NK_PAL_DESK` | macro | `progs/nk_palette.h:15` | `#define NK_PAL_DESK` |
| `NK_PAL_ERR_BOUND` | macro | `progs/nk_palette.h:20` | `#define NK_PAL_ERR_BOUND` |
| `NK_PAL_ERR_OK` | macro | `progs/nk_palette.h:19` | `#define NK_PAL_ERR_OK` |
| `NK_PAL_GRAYS` | macro | `progs/nk_palette.h:17` | `#define NK_PAL_GRAYS` |
| `nk_palette_build` | function | `progs/nk_palette.h:22` | `static int nk_palette_build(unsigned char *pal, long cap)` |
| `CVM_FUNC_ENTRY_SIZE` | macro | `progs/nuklear/cvm_emit.c:35` | `#define CVM_FUNC_ENTRY_SIZE` |
| `CVM_GLOBAL_ENTRY_SIZE` | macro | `progs/nuklear/cvm_emit.c:36` | `#define CVM_GLOBAL_ENTRY_SIZE` |
| `CVM_MAGIC_0` | macro | `progs/nuklear/cvm_emit.c:29` | `#define CVM_MAGIC_0` |
| `CVM_MAGIC_1` | macro | `progs/nuklear/cvm_emit.c:30` | `#define CVM_MAGIC_1` |
| `CVM_MAGIC_2` | macro | `progs/nuklear/cvm_emit.c:31` | `#define CVM_MAGIC_2` |
| `CVM_MAGIC_3` | macro | `progs/nuklear/cvm_emit.c:32` | `#define CVM_MAGIC_3` |
| `CVM_MAX_NODES` | macro | `progs/nuklear/cvm_emit.c:71` | `#define CVM_MAX_NODES` |
| `CVM_MODULE_HEADER_SIZE` | macro | `progs/nuklear/cvm_emit.c:34` | `#define CVM_MODULE_HEADER_SIZE` |
| `CVM_NATIVE_ENTRY_SIZE` | macro | `progs/nuklear/cvm_emit.c:37` | `#define CVM_NATIVE_ENTRY_SIZE` |
| `CVM_VERSION_MAJOR` | macro | `progs/nuklear/cvm_emit.c:33` | `#define CVM_VERSION_MAJOR` |
| `OP_ADD` | macro | `progs/nuklear/cvm_emit.c:46` | `#define OP_ADD` |
| `OP_AND` | macro | `progs/nuklear/cvm_emit.c:52` | `#define OP_AND` |
| `OP_CALL_NATIVE` | macro | `progs/nuklear/cvm_emit.c:67` | `#define OP_CALL_NATIVE` |
| `OP_CMP_EQ` | macro | `progs/nuklear/cvm_emit.c:58` | `#define OP_CMP_EQ` |
| `OP_CMP_GE` | macro | `progs/nuklear/cvm_emit.c:63` | `#define OP_CMP_GE` |
| `OP_CMP_GT` | macro | `progs/nuklear/cvm_emit.c:62` | `#define OP_CMP_GT` |
| `OP_CMP_LE` | macro | `progs/nuklear/cvm_emit.c:61` | `#define OP_CMP_LE` |
| `OP_CMP_LT` | macro | `progs/nuklear/cvm_emit.c:60` | `#define OP_CMP_LT` |
| `OP_CMP_NE` | macro | `progs/nuklear/cvm_emit.c:59` | `#define OP_CMP_NE` |
| `OP_DIV` | macro | `progs/nuklear/cvm_emit.c:49` | `#define OP_DIV` |
| `OP_HALT` | macro | `progs/nuklear/cvm_emit.c:69` | `#define OP_HALT` |
| `OP_JMP` | macro | `progs/nuklear/cvm_emit.c:65` | `#define OP_JMP` |
| `OP_JZ` | macro | `progs/nuklear/cvm_emit.c:66` | `#define OP_JZ` |
| `OP_LEA_DATA` | macro | `progs/nuklear/cvm_emit.c:68` | `#define OP_LEA_DATA` |
| `OP_LNOT` | macro | `progs/nuklear/cvm_emit.c:64` | `#define OP_LNOT` |
| `OP_MOD` | macro | `progs/nuklear/cvm_emit.c:50` | `#define OP_MOD` |
| `OP_MUL` | macro | `progs/nuklear/cvm_emit.c:48` | `#define OP_MUL` |
| `OP_NEG` | macro | `progs/nuklear/cvm_emit.c:51` | `#define OP_NEG` |
| `OP_NOT` | macro | `progs/nuklear/cvm_emit.c:55` | `#define OP_NOT` |
| `OP_OR` | macro | `progs/nuklear/cvm_emit.c:53` | `#define OP_OR` |
| `OP_PUSH_IMM32` | macro | `progs/nuklear/cvm_emit.c:41` | `#define OP_PUSH_IMM32` |
| `OP_PUSH_IMM64` | macro | `progs/nuklear/cvm_emit.c:40` | `#define OP_PUSH_IMM64` |
| `OP_PUSH_IMM8` | macro | `progs/nuklear/cvm_emit.c:42` | `#define OP_PUSH_IMM8` |
| `OP_PUSH_LOCAL` | macro | `progs/nuklear/cvm_emit.c:44` | `#define OP_PUSH_LOCAL` |
| `OP_PUSH_ZERO` | macro | `progs/nuklear/cvm_emit.c:43` | `#define OP_PUSH_ZERO` |
| `OP_SHL` | macro | `progs/nuklear/cvm_emit.c:56` | `#define OP_SHL` |
| `OP_SHR` | macro | `progs/nuklear/cvm_emit.c:57` | `#define OP_SHR` |
| `OP_STORE_LOCAL` | macro | `progs/nuklear/cvm_emit.c:45` | `#define OP_STORE_LOCAL` |
| `OP_SUB` | macro | `progs/nuklear/cvm_emit.c:47` | `#define OP_SUB` |
| `OP_XOR` | macro | `progs/nuklear/cvm_emit.c:54` | `#define OP_XOR` |
| `cb_i64` | function | `progs/nuklear/cvm_emit.c:97` | `static int cb_i64(struct codebuf *cb, long long v)` |
| `cb_imm` | function | `progs/nuklear/cvm_emit.c:111` | `static int cb_imm(struct codebuf *cb, long long v)` |
| `cb_patch_u32` | function | `progs/nuklear/cvm_emit.c:103` | `static void cb_patch_u32(struct codebuf *cb, size_t pos, unsigned long v)` |
| `cb_push` | function | `progs/nuklear/cvm_emit.c:79` | `static int cb_push(struct codebuf *cb, unsigned char c)` |
| `cb_u32` | function | `progs/nuklear/cvm_emit.c:91` | `static int cb_u32(struct codebuf *cb, unsigned long v)` |
| `code` | function | `progs/nuklear/cvm_emit.c:8` | `* exit code (OP_HALT leaves the operand-stack top as the exit status, which  * the shell reports ...` |
| `codebuf` | struct | `progs/nuklear/cvm_emit.c:73` | `` |
| `cvm_compile` | function | `progs/nuklear/cvm_emit.c:236` | `int cvm_compile(const struct cvm_node *nodes, int n,                 unsigned char **out, size_t ...` |
| `emit_jmp` | function | `progs/nuklear/cvm_emit.c:230` | `static int emit_jmp(struct codebuf *code, size_t *rel_pos)` |
| `emit_jz` | function | `progs/nuklear/cvm_emit.c:224` | `static int emit_jz(struct codebuf *code, size_t *rel_pos)` |
| `emit_operand` | function | `progs/nuklear/cvm_emit.c:213` | `static int emit_operand(struct codebuf *code, const struct cvm_node *nodes,                      ...` |
| `is_sink` | function | `progs/nuklear/cvm_emit.c:145` | `static int is_sink(enum cvm_node_type t)` |
| `module` | function | `progs/nuklear/cvm_emit.c:3` | `* * Emits a cvm2 module (format v2) from a dataflow graph. Nodes are * topologically sorted (a true DAG order, so...` |
| `req_inputs` | function | `progs/nuklear/cvm_emit.c:126` | `static int req_inputs(enum cvm_node_type t)` |
| `topo_sort` | function | `progs/nuklear/cvm_emit.c:150` | `static int topo_sort(const struct cvm_node *nodes, int n,                      int *order, char *...` |
| `w32` | function | `progs/nuklear/cvm_emit.c:491` | `void w32(void *p, unsigned v)` |
| `CVM_EMIT_H` | macro | `progs/nuklear/cvm_emit.h:2` | `#define CVM_EMIT_H` |
| `CVM_NODE_STR_MAX` | macro | `progs/nuklear/cvm_emit.h:19` | `#define CVM_NODE_STR_MAX` |
| `cvm_node` | struct | `progs/nuklear/cvm_emit.h:56` | `` |
| `cvm_node_type` | enum | `progs/nuklear/cvm_emit.h:22` | `` |
| `err` | function | `progs/nuklear/cvm_emit.h:67` | `* err (err_cap bytes). The module is heap-allocated and owned by the caller * (free it). */ int cvm_compile(const...` |
| `graph` | function | `progs/nuklear/cvm_emit.h:6` | `* * A node graph (constants, arithmetic, bitwise, comparisons, a conditional * select, and string constants feeding...` |
| `BEZIER_PAD` | macro | `progs/nuklear/node_editor.c:518` | `#define BEZIER_PAD` |
| `GRID_SIZE` | macro | `progs/nuklear/node_editor.c:519` | `#define GRID_SIZE` |
| `MAX_NODES` | macro | `progs/nuklear/node_editor.c:33` | `#define MAX_NODES` |
| `NODE_W` | macro | `progs/nuklear/node_editor.c:514` | `#define NODE_W` |
| `PIN_DIAM` | macro | `progs/nuklear/node_editor.c:517` | `#define PIN_DIAM` |
| `PIN_R` | macro | `progs/nuklear/node_editor.c:516` | `#define PIN_R` |
| `STR_MAX` | macro | `progs/nuklear/node_editor.c:34` | `#define STR_MAX` |
| `TITLE_H` | macro | `progs/nuklear/node_editor.c:515` | `#define TITLE_H` |
| `UI_MEMORY` | macro | `progs/nuklear/node_editor.c:500` | `#define UI_MEMORY` |
| `adderr` | function | `progs/nuklear/node_editor.c:193` | `void adderr(const char *s)` |
| `addrep` | function | `progs/nuklear/node_editor.c:183` | `void addrep(const char *s)` |
| `compile_to` | function | `progs/nuklear/node_editor.c:283` | `static int compile_to(const char *path)` |
| `gnode` | struct | `progs/nuklear/node_editor.c:44` | `` |
| `graph_add` | function | `progs/nuklear/node_editor.c:122` | `static int graph_add(int kind)` |
| `graph_clear` | function | `progs/nuklear/node_editor.c:116` | `static void graph_clear(void)` |
| `graph_del` | function | `progs/nuklear/node_editor.c:136` | `static void graph_del(int idx)` |
| `graph_to_compiler` | function | `progs/nuklear/node_editor.c:154` | `static int graph_to_compiler(struct cvm_node *out, int cap)` |
| `gui_run` | function | `progs/nuklear/node_editor.c:931` | `static void gui_run(void)` |
| `kind_color` | function | `progs/nuklear/node_editor.c:111` | `static struct nk_color kind_color(int k)` |
| `kind_name` | function | `progs/nuklear/node_editor.c:106` | `static const char *kind_name(int k)` |
| `main` | function | `progs/nuklear/node_editor.c:983` | `int main(int argc, char **argv)` |
| `node_h` | function | `progs/nuklear/node_editor.c:534` | `static float node_h(struct gnode *n)` |
| `node_inputs` | function | `progs/nuklear/node_editor.c:96` | `static int node_inputs(int k)` |
| `node_outputs` | function | `progs/nuklear/node_editor.c:101` | `static int node_outputs(int k)` |
| `nodedef` | struct | `progs/nuklear/node_editor.c:55` | `` |
| `parse_graph_file` | function | `progs/nuklear/node_editor.c:430` | `static int parse_graph_file(const char *path)` |
| `parse_input` | function | `progs/nuklear/node_editor.c:443` | `int parse_input(const char *tok, int idx, int k)` |
| `pin_y` | function | `progs/nuklear/node_editor.c:522` | `static float pin_y(struct gnode *n, int slot, int is_output)` |
| `repair_graph` | function | `progs/nuklear/node_editor.c:176` | `static int repair_graph(char *rep, size_t repcap, char *herr, size_t herrcap,                    ...` |
| `resolve` | function | `progs/nuklear/node_editor.c:437` | `int resolve(const char *nme, int upto)` |
| `save_graph_file` | function | `progs/nuklear/node_editor.c:392` | `static int save_graph_file(const char *path)` |
| `ui_build` | function | `progs/nuklear/node_editor.c:622` | `static void ui_build(struct nk_context *ctx, float win_w, float win_h)` |
| `ui_inspector` | function | `progs/nuklear/node_editor.c:542` | `static void ui_inspector(struct nk_context *ctx)` |
| `write_quoted` | function | `progs/nuklear/node_editor.c:339` | `static void write_quoted(FILE *f, const char *s)` |
| `NK_IMPLEMENTATION` | macro | `progs/nuklear/nuklear_minios.c:17` | `#define NK_IMPLEMENTATION` |
| `col_to_idx` | function | `progs/nuklear/nuklear_minios.c:438` | `static int col_to_idx(struct nk_color c)` |
| `cur_bg_set` | function | `progs/nuklear/nuklear_minios.c:190` | `static void cur_bg_set(struct nk_color c)` |
| `cur_set` | function | `progs/nuklear/nuklear_minios.c:186` | `static void cur_set(struct nk_color c)` |
| `draw_arc` | function | `progs/nuklear/nuklear_minios.c:615` | `static void draw_arc(int cx, int cy, int r, float a0, float a1,                      int filled, ...` |
| `draw_line` | function | `progs/nuklear/nuklear_minios.c:529` | `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)` |
| `draw_text` | function | `progs/nuklear/nuklear_minios.c:601` | `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)` |
| `feed_key` | function | `progs/nuklear/nuklear_minios.c:854` | `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)` |
| `fill_circle` | function | `progs/nuklear/nuklear_minios.c:547` | `static void fill_circle(int cx, int cy, int r, int c)` |
| `fill_poly` | function | `progs/nuklear/nuklear_minios.c:571` | `static void fill_poly(int *xs, int *ys, int n, int c)` |
| `fill_rect` | function | `progs/nuklear/nuklear_minios.c:522` | `static void fill_rect(int x, int y, int w, int h, int c)` |
| `handle_scancode` | function | `progs/nuklear/nuklear_minios.c:866` | `static void handle_scancode(struct nk_context *ctx, unsigned char sc)` |
| `list` | function | `progs/nuklear/nuklear_minios.c:4` | `* abstract draw command list (nk__begin/nk__next);` |
| `nk_build_palette` | function | `progs/nuklear/nuklear_minios.c:418` | `void nk_build_palette(unsigned char *pal768)` |
| `nk_client_hash` | function | `progs/nuklear/nuklear_minios.c:216` | `static unsigned nk_client_hash(const unsigned char *p, unsigned n)` |
| `nk_client_poll` | function | `progs/nuklear/nuklear_minios.c:914` | `static void nk_client_poll(struct nk_context *ctx)` |
| `nk_client_probe` | function | `progs/nuklear/nuklear_minios.c:72` | `static int nk_client_probe(void)` |
| `nk_client_publish` | function | `progs/nuklear/nuklear_minios.c:227` | `static int nk_client_publish(void)` |
| `nk_foreach` | function | `progs/nuklear/nuklear_minios.c:641` | `nk_foreach(cmd, ctx)` |
| `nk_idx_to_rgb` | function | `progs/nuklear/nuklear_minios.c:170` | `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g,                    unsigned char *b)` |
| `nk_minios_font` | function | `progs/nuklear/nuklear_minios.c:819` | `struct nk_user_font nk_minios_font(void)` |
| `nk_minios_font_width` | function | `progs/nuklear/nuklear_minios.c:813` | `static float nk_minios_font_width(nk_handle handle, float height,                                ...` |
| `nk_mirror_box` | function | `progs/nuklear/nuklear_minios.c:314` | `static void nk_mirror_box(char *dst, int cap)` |
| `nk_mirror_emit` | function | `progs/nuklear/nuklear_minios.c:335` | `static int nk_mirror_emit(const char *box, unsigned seq,         const unsigned char *msg, int mlen)` |
| `nk_mirror_tick` | function | `progs/nuklear/nuklear_minios.c:352` | `static void nk_mirror_tick(void)` |
| `nk_poll_input` | function | `progs/nuklear/nuklear_minios.c:961` | `void nk_poll_input(struct nk_context *ctx)` |
| `nk_quit_requested` | function | `progs/nuklear/nuklear_minios.c:1008` | `int nk_quit_requested(void)` |
| `nk_rasterize` | function | `progs/nuklear/nuklear_minios.c:636` | `void nk_rasterize(struct nk_context *ctx)` |
| `nk_rgb_available` | function | `progs/nuklear/nuklear_minios.c:147` | `int nk_rgb_available(void)` |
| `nk_set_scancode_hook` | function | `progs/nuklear/nuklear_minios.c:861` | `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud)` |
| `nk_set_window_origin` | function | `progs/nuklear/nuklear_minios.c:1000` | `void nk_set_window_origin(int x, int y)` |
| `nk_sys_fb_info` | function | `progs/nuklear/nuklear_minios.c:121` | `long nk_sys_fb_info(int *w, int *h, int *pitch)` |
| `nk_sys_fb_info_rgb` | function | `progs/nuklear/nuklear_minios.c:137` | `static long nk_sys_fb_info_rgb(int *w, int *h, int *pitch, int *rgb)` |
| `nk_sys_getpid` | function | `progs/nuklear/nuklear_minios.c:53` | `long nk_sys_getpid(void)` |
| `nk_sys_gfx_set_title` | function | `progs/nuklear/nuklear_minios.c:409` | `long nk_sys_gfx_set_title(const char *t)` |
| `nk_sys_kbd` | function | `progs/nuklear/nuklear_minios.c:38` | `long nk_sys_kbd(void)` |
| `nk_sys_kbd_raw` | function | `progs/nuklear/nuklear_minios.c:48` | `long nk_sys_kbd_raw(int on)` |
| `nk_sys_mouse` | function | `progs/nuklear/nuklear_minios.c:193` | `long nk_sys_mouse(int *xybw)` |
| `nk_sys_mouse_badptr` | function | `progs/nuklear/nuklear_minios.c:198` | `long nk_sys_mouse_badptr(void)` |
| `nk_sys_nk_frame` | function | `progs/nuklear/nuklear_minios.c:280` | `long nk_sys_nk_frame(int *origin)` |
| `nk_sys_palette` | function | `progs/nuklear/nuklear_minios.c:43` | `long nk_sys_palette(const unsigned char *pal)` |
| `nk_sys_time_ms` | function | `progs/nuklear/nuklear_minios.c:33` | `long nk_sys_time_ms(void)` |
| `nk_sys_vga_mode` | function | `progs/nuklear/nuklear_minios.c:114` | `long nk_sys_vga_mode(int on)` |
| `pal_prepare` | function | `progs/nuklear/nuklear_minios.c:427` | `static void pal_prepare(void)` |
| `program_invocation_short_name` | variable | `progs/nuklear/nuklear_minios.c:27` | `extern char *program_invocation_short_name;` |
| `px` | function | `progs/nuklear/nuklear_minios.c:479` | `static void px(int x, int y, int c)` |
| `px_bg` | function | `progs/nuklear/nuklear_minios.c:492` | `static void px_bg(int x, int y, int c)` |
| `px_idx` | function | `progs/nuklear/nuklear_minios.c:506` | `static void px_idx(int x, int y, int c)` |
| `rgb256_prepare` | function | `progs/nuklear/nuklear_minios.c:162` | `static void rgb256_prepare(void)` |
| `set_clip` | function | `progs/nuklear/nuklear_minios.c:469` | `static void set_clip(int x, int y, int w, int h)` |
| `stroke_circle` | function | `progs/nuklear/nuklear_minios.c:553` | `static void stroke_circle(int cx, int cy, int r, int th, int c)` |
| `stroke_poly` | function | `progs/nuklear/nuklear_minios.c:594` | `static void stroke_poly(int *xs, int *ys, int n, int th, int c)` |
| `NK_BACKBUF` | macro | `progs/nuklear/nuklear_minios.h:26` | `#define NK_BACKBUF` |
| `NK_H` | macro | `progs/nuklear/nuklear_minios.h:25` | `#define NK_H` |
| `NK_MINIOS_IMG_MAX` | macro | `progs/nuklear/nuklear_minios.h:73` | `#define NK_MINIOS_IMG_MAX` |
| `NK_RGB_BUF` | macro | `progs/nuklear/nuklear_minios.h:30` | `#define NK_RGB_BUF` |
| `NK_W` | macro | `progs/nuklear/nuklear_minios.h:24` | `#define NK_W` |
| `NUKLEAR_MINIOS_H` | macro | `progs/nuklear/nuklear_minios.h:2` | `#define NUKLEAR_MINIOS_H` |
| `SYS_NK_FRAME` | function | `progs/nuklear/nuklear_minios.h:85` | `* SYS_NK_FRAME (nk_set_window_origin). */ void nk_set_window_origin(int x, int y);` |
| `nk_build_palette` | function | `progs/nuklear/nuklear_minios.h:57` | `void nk_build_palette(unsigned char *pal768);` |
| `nk_command_buffer` | struct | `progs/nuklear/nuklear_minios.h:22` | `` |
| `nk_context` | struct | `progs/nuklear/nuklear_minios.h:20` | `` |
| `nk_idx_to_rgb` | function | `progs/nuklear/nuklear_minios.h:37` | `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g, unsigned char *b);` |
| `nk_minios_font` | function | `progs/nuklear/nuklear_minios.h:63` | `struct nk_user_font nk_minios_font(void);` |
| `nk_minios_img` | struct | `progs/nuklear/nuklear_minios.h:74` | `` |
| `nk_poll_input` | function | `progs/nuklear/nuklear_minios.h:87` | `void nk_poll_input(struct nk_context *ctx);` |
| `nk_quit_requested` | function | `progs/nuklear/nuklear_minios.h:92` | `int nk_quit_requested(void);` |
| `nk_rasterize` | function | `progs/nuklear/nuklear_minios.h:66` | `void nk_rasterize(struct nk_context *ctx);` |
| `nk_rgb_available` | function | `progs/nuklear/nuklear_minios.h:33` | `int nk_rgb_available(void);` |
| `nk_set_scancode_hook` | function | `progs/nuklear/nuklear_minios.h:101` | `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud);` |
| `nk_sys_fb_info` | function | `progs/nuklear/nuklear_minios.h:46` | `long nk_sys_fb_info(int *w, int *h, int *pitch);` |
| `nk_sys_gfx_set_title` | function | `progs/nuklear/nuklear_minios.h:53` | `long nk_sys_gfx_set_title(const char *t);` |
| `nk_sys_kbd` | function | `progs/nuklear/nuklear_minios.h:42` | `long nk_sys_kbd(void);` |
| `nk_sys_kbd_raw` | function | `progs/nuklear/nuklear_minios.h:44` | `long nk_sys_kbd_raw(int on);` |
| `nk_sys_mouse` | function | `progs/nuklear/nuklear_minios.h:47` | `long nk_sys_mouse(int *xybw);` |
| `nk_sys_mouse_badptr` | function | `progs/nuklear/nuklear_minios.h:51` | `long nk_sys_mouse_badptr(void);` |
| `nk_sys_nk_frame` | function | `progs/nuklear/nuklear_minios.h:52` | `long nk_sys_nk_frame(int *origin);` |
| `nk_sys_palette` | function | `progs/nuklear/nuklear_minios.h:43` | `long nk_sys_palette(const unsigned char *pal768);` |
| `nk_sys_time_ms` | function | `progs/nuklear/nuklear_minios.h:41` | `long nk_sys_time_ms(void);` |
| `nk_sys_vga_mode` | function | `progs/nuklear/nuklear_minios.h:45` | `long nk_sys_vga_mode(int on);` |
| `nk_user_font` | struct | `progs/nuklear/nuklear_minios.h:21` | `` |
| `X` | macro | `progs/nuklear/nuklear_theme.c:21` | `#define X(k, i)` |
| `nk_theme_active` | function | `progs/nuklear/nuklear_theme.c:49` | `int nk_theme_active(char *dst, int cap)` |
| `nk_theme_apply` | function | `progs/nuklear/nuklear_theme.c:141` | `int nk_theme_apply(struct nk_context *ctx, const char *name)` |
| `nk_theme_name_ok` | function | `progs/nuklear/nuklear_theme.c:37` | `static int nk_theme_name_ok(const char *name)` |
| `nk_theme_parse_line` | function | `progs/nuklear/nuklear_theme.c:73` | `static int nk_theme_parse_line(const char *line,                                unsigned char rgb...` |
| `nk_theme_probe` | function | `progs/nuklear/nuklear_theme.c:105` | `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3])` |
| `nk_theme_slot` | struct | `progs/nuklear/nuklear_theme.c:15` | `` |
| `NK_THEME_DEFAULT` | macro | `progs/nuklear/nuklear_theme.h:20` | `#define NK_THEME_DEFAULT` |
| `NK_THEME_KEY_COUNT` | macro | `progs/nuklear/nuklear_theme.h:57` | `#define NK_THEME_KEY_COUNT` |
| `NK_THEME_KEY_LIST` | macro | `progs/nuklear/nuklear_theme.h:23` | `#define NK_THEME_KEY_LIST` |
| `NK_THEME_KEY_MAX` | macro | `progs/nuklear/nuklear_theme.h:16` | `#define NK_THEME_KEY_MAX` |
| `NK_THEME_LINE_MAX` | macro | `progs/nuklear/nuklear_theme.h:17` | `#define NK_THEME_LINE_MAX` |
| `NK_THEME_NAME_MAX` | macro | `progs/nuklear/nuklear_theme.h:15` | `#define NK_THEME_NAME_MAX` |
| `NK_THEME_PATH_CURRENT` | macro | `progs/nuklear/nuklear_theme.h:19` | `#define NK_THEME_PATH_CURRENT` |
| `NK_THEME_PATH_DIR` | macro | `progs/nuklear/nuklear_theme.h:18` | `#define NK_THEME_PATH_DIR` |
| `NUKLEAR_THEME_H` | macro | `progs/nuklear/nuklear_theme.h:2` | `#define NUKLEAR_THEME_H` |
| `nk_context` | struct | `progs/nuklear/nuklear_theme.h:59` | `` |
| `nk_theme_active` | function | `progs/nuklear/nuklear_theme.h:62` | `int nk_theme_active(char *dst, int cap);` |
| `nk_theme_apply` | function | `progs/nuklear/nuklear_theme.h:68` | `int nk_theme_apply(struct nk_context *ctx, const char *name);` |
| `nk_theme_probe` | function | `progs/nuklear/nuklear_theme.h:65` | `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);` |
| `PAINT_DEFAULT_PATH` | macro | `progs/paint/paint.c:42` | `#define PAINT_DEFAULT_PATH` |
| `PAINT_FILE_BTN_W` | macro | `progs/paint/paint.c:44` | `#define PAINT_FILE_BTN_W` |
| `PAINT_FILE_MAX` | macro | `progs/paint/paint.c:36` | `#define PAINT_FILE_MAX` |
| `PAINT_FRAME_ATTEMPTS` | macro | `progs/paint/paint.c:46` | `#define PAINT_FRAME_ATTEMPTS` |
| `PAINT_FRAME_MS` | macro | `progs/paint/paint.c:45` | `#define PAINT_FRAME_MS` |
| `PAINT_H` | macro | `progs/paint/paint.c:33` | `#define PAINT_H` |
| `PAINT_N` | macro | `progs/paint/paint.c:34` | `#define PAINT_N` |
| `PAINT_NCOLORS` | macro | `progs/paint/paint.c:47` | `#define PAINT_NCOLORS` |
| `PAINT_NSIZES` | macro | `progs/paint/paint.c:48` | `#define PAINT_NSIZES` |
| `PAINT_NTOOLS` | macro | `progs/paint/paint.c:49` | `#define PAINT_NTOOLS` |
| `PAINT_PANEL_TITLE` | macro | `progs/paint/paint.c:43` | `#define PAINT_PANEL_TITLE` |
| `PAINT_PATH_MAX` | macro | `progs/paint/paint.c:35` | `#define PAINT_PATH_MAX` |
| `PAINT_PNG_MAX` | macro | `progs/paint/paint.c:39` | `#define PAINT_PNG_MAX` |
| `PAINT_PNG_MAX_DIM` | macro | `progs/paint/paint.c:40` | `#define PAINT_PNG_MAX_DIM` |
| `PAINT_STATUS_MAX` | macro | `progs/paint/paint.c:37` | `#define PAINT_STATUS_MAX` |
| `PAINT_TITLE` | macro | `progs/paint/paint.c:41` | `#define PAINT_TITLE` |
| `PAINT_TOOL_BRUSH` | macro | `progs/paint/paint.c:52` | `#define PAINT_TOOL_BRUSH` |
| `PAINT_TOOL_CIRCLE` | macro | `progs/paint/paint.c:55` | `#define PAINT_TOOL_CIRCLE` |
| `PAINT_TOOL_ERASER` | macro | `progs/paint/paint.c:57` | `#define PAINT_TOOL_ERASER` |
| `PAINT_TOOL_FILL` | macro | `progs/paint/paint.c:56` | `#define PAINT_TOOL_FILL` |
| `PAINT_TOOL_LINE` | macro | `progs/paint/paint.c:53` | `#define PAINT_TOOL_LINE` |
| `PAINT_TOOL_RECT` | macro | `progs/paint/paint.c:54` | `#define PAINT_TOOL_RECT` |
| `PAINT_UI_MEMORY` | macro | `progs/paint/paint.c:38` | `#define PAINT_UI_MEMORY` |
| `PAINT_W` | macro | `progs/paint/paint.c:32` | `#define PAINT_W` |
| `STBI_NO_STDIO` | macro | `progs/paint/paint.c:28` | `#define STBI_NO_STDIO` |
| `STBI_ONLY_PNG` | macro | `progs/paint/paint.c:27` | `#define STBI_ONLY_PNG` |
| `STB_IMAGE_IMPLEMENTATION` | macro | `progs/paint/paint.c:26` | `#define STB_IMAGE_IMPLEMENTATION` |
| `main` | function | `progs/paint/paint.c:992` | `int main(int argc, char **argv)` |
| `paint_adler` | function | `progs/paint/paint.c:296` | `static unsigned long paint_adler(const unsigned char *p, unsigned long n)` |
| `paint_blit` | function | `progs/paint/paint.c:549` | `static void paint_blit(int ox, int oy)` |
| `paint_circle_fill` | function | `progs/paint/paint.c:161` | `static int paint_circle_fill(unsigned char *buf, int w, int h, int cx,                           ...` |
| `paint_clamp` | function | `progs/paint/paint.c:92` | `static int paint_clamp(int v, int lo, int hi)` |
| `paint_crc_init` | function | `progs/paint/paint.c:272` | `static void paint_crc_init(void)` |
| `paint_crc_update` | function | `progs/paint/paint.c:285` | `static unsigned long paint_crc_update(unsigned long c,                                       cons...` |
| `paint_dab` | function | `progs/paint/paint.c:108` | `static void paint_dab(unsigned char *buf, int w, int h, int x, int y,                       unsig...` |
| `paint_flood` | function | `progs/paint/paint.c:179` | `static int paint_flood(unsigned char *buf, int w, int h, int x, int y,                        uns...` |
| `paint_gui_run` | function | `progs/paint/paint.c:942` | `static void paint_gui_run(void)` |
| `paint_handle_input` | function | `progs/paint/paint.c:577` | `static void paint_handle_input(struct nk_context *ctx)` |
| `paint_ink` | function | `progs/paint/paint.c:570` | `static unsigned char paint_ink(void)` |
| `paint_line` | function | `progs/paint/paint.c:119` | `static int paint_line(unsigned char *buf, int w, int h, int x0, int y0,                       int...` |
| `paint_load_file` | function | `progs/paint/paint.c:461` | `static int paint_load_file(const char *path)` |
| `paint_nearest` | function | `progs/paint/paint.c:223` | `static int paint_nearest(const unsigned char *pal, unsigned r, unsigned g,                       ...` |
| `paint_pal` | function | `progs/paint/paint.c:240` | `static const unsigned char *paint_pal(void)` |
| `paint_path_ok` | function | `progs/paint/paint.c:251` | `static int paint_path_ok(const char *p)` |
| `paint_pattern_present` | function | `progs/paint/paint.c:720` | `static int paint_pattern_present(int fw, int fh, int fp, int *ox, int *oy)` |
| `paint_plot` | function | `progs/paint/paint.c:99` | `static int paint_plot(unsigned char *buf, int w, int h, int x, int y,                       unsig...` |
| `paint_png_encode` | function | `progs/paint/paint.c:333` | `static long paint_png_encode(unsigned char *dst, unsigned long cap,                              ...` |
| `paint_put_bytes` | function | `progs/paint/paint.c:320` | `static int paint_put_bytes(unsigned char *dst, unsigned long cap,                            unsi...` |
| `paint_put_u32` | function | `progs/paint/paint.c:308` | `static int paint_put_u32(unsigned char *dst, unsigned long cap,                          unsigned...` |
| `paint_rect_fill` | function | `progs/paint/paint.c:144` | `static int paint_rect_fill(unsigned char *buf, int w, int h, int x0, int y0,                     ...` |
| `paint_save_file` | function | `progs/paint/paint.c:514` | `static int paint_save_file(const char *path)` |
| `paint_selftest` | function | `progs/paint/paint.c:755` | `static int paint_selftest(void)` |
| `paint_ui_build` | function | `progs/paint/paint.c:636` | `static void paint_ui_build(struct nk_context *ctx)` |
| `BK_H` | macro | `progs/piano/piano.c:193` | `#define BK_H` |
| `BK_W` | macro | `progs/piano/piano.c:192` | `#define BK_W` |
| `BTN_GAP` | macro | `progs/piano/piano.c:548` | `#define BTN_GAP` |
| `BTN_W` | macro | `progs/piano/piano.c:547` | `#define BTN_W` |
| `CTRL_H` | macro | `progs/piano/piano.c:546` | `#define CTRL_H` |
| `CTRL_Y` | macro | `progs/piano/piano.c:545` | `#define CTRL_Y` |
| `FX_DELAY_CAP` | macro | `progs/piano/piano.c:407` | `#define FX_DELAY_CAP` |
| `FX_DELAY_MAX_MS` | macro | `progs/piano/piano.c:408` | `#define FX_DELAY_MAX_MS` |
| `FX_FEEDBACK` | macro | `progs/piano/piano.c:409` | `#define FX_FEEDBACK` |
| `FX_TREM_FREQ` | macro | `progs/piano/piano.c:411` | `#define FX_TREM_FREQ` |
| `FX_WET` | macro | `progs/piano/piano.c:410` | `#define FX_WET` |
| `KBD_NO_NOTE` | macro | `progs/piano/piano.c:297` | `#define KBD_NO_NOTE` |
| `KEY_H` | macro | `progs/piano/piano.c:191` | `#define KEY_H` |
| `KEY_W` | macro | `progs/piano/piano.c:190` | `#define KEY_W` |
| `KEY_Y` | macro | `progs/piano/piano.c:194` | `#define KEY_Y` |
| `MAX_AUDIO_MS` | macro | `progs/piano/piano.c:76` | `#define MAX_AUDIO_MS` |
| `MAX_VOICES` | macro | `progs/piano/piano.c:221` | `#define MAX_VOICES` |
| `NCTRLS` | macro | `progs/piano/piano.c:561` | `#define NCTRLS` |
| `NKEYS` | macro | `progs/piano/piano.c:209` | `#define NKEYS` |
| `PCM_BUF` | macro | `progs/piano/piano.c:63` | `#define PCM_BUF` |
| `PCM_FRAG` | macro | `progs/piano/piano.c:62` | `#define PCM_FRAG` |
| `PIANO_BASE_MIDI` | macro | `progs/piano/piano.c:195` | `#define PIANO_BASE_MIDI` |
| `PIANO_FRAME_MS` | macro | `progs/piano/piano.c:84` | `#define PIANO_FRAME_MS` |
| `PIANO_FRAME_PERIOD` | macro | `progs/piano/piano.c:91` | `#define PIANO_FRAME_PERIOD` |
| `PIANO_OCTAVES` | macro | `progs/piano/piano.c:196` | `#define PIANO_OCTAVES` |
| `RATE` | macro | `progs/piano/piano.c:61` | `#define RATE` |
| `SYS_PCM2_CLOSE` | macro | `progs/piano/piano.c:59` | `#define SYS_PCM2_CLOSE` |
| `SYS_PCM2_OPEN` | macro | `progs/piano/piano.c:57` | `#define SYS_PCM2_OPEN` |
| `SYS_PCM2_WRITE` | macro | `progs/piano/piano.c:58` | `#define SYS_PCM2_WRITE` |
| `UI_MEMORY` | macro | `progs/piano/piano.c:54` | `#define UI_MEMORY` |
| `clamp_midi` | function | `progs/piano/piano.c:234` | `static int clamp_midi(int m)` |

Next: [SYMBOLS_p21.md](SYMBOLS_p21.md)
