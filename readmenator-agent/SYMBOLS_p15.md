# Symbols (page 15 of 27)
Previous: [SYMBOLS_p14.md](SYMBOLS_p14.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `mus_render_push` | function | `progs/doomgeneric/i_minios_sound.c:359` | `static void mus_render_push(mus_player_t *m, unsigned n)` |
| `muted` | function | `progs/doomgeneric/i_minios_sound.c:51` | `* pcm2 while sfx stay muted (effect tones ruined the melody);` |
| `pcspk_channel_t` | struct | `progs/doomgeneric/i_minios_sound.c:17` | `` |
| `sys_pcm2_close` | function | `progs/doomgeneric/i_minios_sound.c:44` | `static void sys_pcm2_close(void)` |
| `sys_pcm2_open` | function | `progs/doomgeneric/i_minios_sound.c:38` | `static long sys_pcm2_open(long flags)` |
| `sys_pcm2_write` | function | `progs/doomgeneric/i_minios_sound.c:41` | `static long sys_pcm2_write(const void *buf, long len)` |
| `sys_time` | function | `progs/doomgeneric/i_minios_sound.c:35` | `static long sys_time(void)` |
| `sys_tone_hw` | function | `progs/doomgeneric/i_minios_sound.c:32` | `static long sys_tone_hw(unsigned f)` |
| `DRAW_PIXEL2` | macro | `progs/doomgeneric/i_scale.c:1099` | `#define DRAW_PIXEL2` |
| `DRAW_PIXEL3` | macro | `progs/doomgeneric/i_scale.c:1194` | `#define DRAW_PIXEL3` |
| `DRAW_PIXEL4` | macro | `progs/doomgeneric/i_scale.c:1276` | `#define DRAW_PIXEL4` |
| `DRAW_PIXEL5` | macro | `progs/doomgeneric/i_scale.c:1387` | `#define DRAW_PIXEL5` |
| `FindNearestColor` | function | `progs/doomgeneric/i_scale.c:295` | `static int FindNearestColor(byte *palette, int r, int g, int b)` |
| `GenerateStretchTable` | function | `progs/doomgeneric/i_scale.c:332` | `static byte *GenerateStretchTable(byte *palette, int pct)` |
| `I_InitScale` | function | `progs/doomgeneric/i_scale.c:61` | `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)` |
| `I_InitSquashTable` | function | `progs/doomgeneric/i_scale.c:387` | `static void I_InitSquashTable(byte *palette)` |
| `I_InitStretchTables` | function | `progs/doomgeneric/i_scale.c:361` | `static void I_InitStretchTables(byte *palette)` |
| `I_ResetScaleTables` | function | `progs/doomgeneric/i_scale.c:404` | `void I_ResetScaleTables(byte *palette)` |
| `I_Scale1x` | function | `progs/doomgeneric/i_scale.c:75` | `static boolean I_Scale1x(int x1, int y1, int x2, int y2)` |
| `I_Scale2x` | function | `progs/doomgeneric/i_scale.c:105` | `static boolean I_Scale2x(int x1, int y1, int x2, int y2)` |
| `I_Scale3x` | function | `progs/doomgeneric/i_scale.c:146` | `static boolean I_Scale3x(int x1, int y1, int x2, int y2)` |
| `I_Scale4x` | function | `progs/doomgeneric/i_scale.c:191` | `static boolean I_Scale4x(int x1, int y1, int x2, int y2)` |
| `I_Scale5x` | function | `progs/doomgeneric/i_scale.c:240` | `static boolean I_Scale5x(int x1, int y1, int x2, int y2)` |
| `I_Squash1x` | function | `progs/doomgeneric/i_scale.c:1061` | `static boolean I_Squash1x(int x1, int y1, int x2, int y2)` |
| `I_Squash2x` | function | `progs/doomgeneric/i_scale.c:1160` | `static boolean I_Squash2x(int x1, int y1, int x2, int y2)` |
| `I_Squash3x` | function | `progs/doomgeneric/i_scale.c:1243` | `static boolean I_Squash3x(int x1, int y1, int x2, int y2)` |
| `I_Squash4x` | function | `progs/doomgeneric/i_scale.c:1354` | `static boolean I_Squash4x(int x1, int y1, int x2, int y2)` |
| `I_Squash5x` | function | `progs/doomgeneric/i_scale.c:1419` | `static boolean I_Squash5x(int x1, int y1, int x2, int y2)` |
| `I_Stretch1x` | function | `progs/doomgeneric/i_scale.c:450` | `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)` |
| `I_Stretch2x` | function | `progs/doomgeneric/i_scale.c:539` | `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)` |
| `I_Stretch3x` | function | `progs/doomgeneric/i_scale.c:654` | `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)` |
| `I_Stretch4x` | function | `progs/doomgeneric/i_scale.c:795` | `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)` |
| `I_Stretch5x` | function | `progs/doomgeneric/i_scale.c:942` | `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)` |
| `WriteBlendedLine1x` | function | `progs/doomgeneric/i_scale.c:434` | `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2,                        ...` |
| `WriteBlendedLine2x` | function | `progs/doomgeneric/i_scale.c:520` | `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2,                        ...` |
| `WriteBlendedLine3x` | function | `progs/doomgeneric/i_scale.c:634` | `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2,                        ...` |
| `WriteBlendedLine4x` | function | `progs/doomgeneric/i_scale.c:774` | `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2,                        ...` |
| `WriteLine2x` | function | `progs/doomgeneric/i_scale.c:507` | `static inline void WriteLine2x(byte *dest, byte *src)` |
| `WriteLine3x` | function | `progs/doomgeneric/i_scale.c:620` | `static inline void WriteLine3x(byte *dest, byte *src)` |
| `WriteLine4x` | function | `progs/doomgeneric/i_scale.c:759` | `static inline void WriteLine4x(byte *dest, byte *src)` |
| `WriteLine5x` | function | `progs/doomgeneric/i_scale.c:924` | `static inline void WriteLine5x(byte *dest, byte *src)` |
| `WriteSquashedLine1x` | function | `progs/doomgeneric/i_scale.c:1030` | `static inline void WriteSquashedLine1x(byte *dest, byte *src)` |
| `WriteSquashedLine2x` | function | `progs/doomgeneric/i_scale.c:1102` | `static inline void WriteSquashedLine2x(byte *dest, byte *src)` |
| `WriteSquashedLine3x` | function | `progs/doomgeneric/i_scale.c:1197` | `static inline void WriteSquashedLine3x(byte *dest, byte *src)` |
| `WriteSquashedLine4x` | function | `progs/doomgeneric/i_scale.c:1279` | `static inline void WriteSquashedLine4x(byte *dest, byte *src)` |
| `WriteSquashedLine5x` | function | `progs/doomgeneric/i_scale.c:1390` | `static inline void WriteSquashedLine5x(byte *dest, byte *src)` |
| `inline` | macro | `progs/doomgeneric/i_scale.c:32` | `#define inline` |
| `I_InitScale` | function | `progs/doomgeneric/i_scale.h:25` | `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);` |
| `I_ResetScaleTables` | function | `progs/doomgeneric/i_scale.h:26` | `void I_ResetScaleTables(byte *palette);` |
| `__I_SCALE__` | macro | `progs/doomgeneric/i_scale.h:21` | `#define __I_SCALE__` |
| `mode_scale_1x` | variable | `progs/doomgeneric/i_scale.h:30` | `extern screen_mode_t mode_scale_1x;` |
| `mode_scale_2x` | variable | `progs/doomgeneric/i_scale.h:31` | `extern screen_mode_t mode_scale_2x;` |
| `mode_scale_3x` | variable | `progs/doomgeneric/i_scale.h:32` | `extern screen_mode_t mode_scale_3x;` |
| `mode_scale_4x` | variable | `progs/doomgeneric/i_scale.h:33` | `extern screen_mode_t mode_scale_4x;` |
| `mode_scale_5x` | variable | `progs/doomgeneric/i_scale.h:34` | `extern screen_mode_t mode_scale_5x;` |
| `mode_squash_1x` | variable | `progs/doomgeneric/i_scale.h:46` | `extern screen_mode_t mode_squash_1x;` |
| `mode_squash_2x` | variable | `progs/doomgeneric/i_scale.h:47` | `extern screen_mode_t mode_squash_2x;` |
| `mode_squash_3x` | variable | `progs/doomgeneric/i_scale.h:48` | `extern screen_mode_t mode_squash_3x;` |
| `mode_squash_4x` | variable | `progs/doomgeneric/i_scale.h:49` | `extern screen_mode_t mode_squash_4x;` |
| `mode_squash_5x` | variable | `progs/doomgeneric/i_scale.h:50` | `extern screen_mode_t mode_squash_5x;` |
| `mode_stretch_1x` | variable | `progs/doomgeneric/i_scale.h:38` | `extern screen_mode_t mode_stretch_1x;` |
| `mode_stretch_2x` | variable | `progs/doomgeneric/i_scale.h:39` | `extern screen_mode_t mode_stretch_2x;` |
| `mode_stretch_3x` | variable | `progs/doomgeneric/i_scale.h:40` | `extern screen_mode_t mode_stretch_3x;` |
| `mode_stretch_4x` | variable | `progs/doomgeneric/i_scale.h:41` | `extern screen_mode_t mode_stretch_4x;` |
| `mode_stretch_5x` | variable | `progs/doomgeneric/i_scale.h:42` | `extern screen_mode_t mode_stretch_5x;` |
| `CheckVolumeSeparation` | function | `progs/doomgeneric/i_sound.c:288` | `static void CheckVolumeSeparation(int *vol, int *sep)` |
| `I_BindSoundVariables` | function | `progs/doomgeneric/i_sound.c:440` | `void I_BindSoundVariables(void)` |
| `I_GetSfxLumpNum` | function | `progs/doomgeneric/i_sound.c:263` | `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)` |
| `I_InitMusic` | function | `progs/doomgeneric/i_sound.c:359` | `void I_InitMusic(void)` |
| `I_InitSound` | function | `progs/doomgeneric/i_sound.c:195` | `void I_InitSound(boolean use_sfx_prefix)` |
| `I_InitTimidityConfig` | function | `progs/doomgeneric/i_sound.c:65` | `extern void I_InitTimidityConfig(void);` |
| `I_MusicIsPlaying` | function | `progs/doomgeneric/i_sound.c:428` | `boolean I_MusicIsPlaying(void)` |
| `I_PauseSong` | function | `progs/doomgeneric/i_sound.c:376` | `void I_PauseSong(void)` |
| `I_PlaySong` | function | `progs/doomgeneric/i_sound.c:412` | `void I_PlaySong(void *handle, boolean looping)` |
| `I_PrecacheSounds` | function | `progs/doomgeneric/i_sound.c:351` | `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)` |
| `I_RegisterSong` | function | `progs/doomgeneric/i_sound.c:392` | `void *I_RegisterSong(void *data, int len)` |
| `I_ResumeSong` | function | `progs/doomgeneric/i_sound.c:384` | `void I_ResumeSong(void)` |
| `I_SetMusicVolume` | function | `progs/doomgeneric/i_sound.c:368` | `void I_SetMusicVolume(int volume)` |
| `I_ShutdownMusic` | function | `progs/doomgeneric/i_sound.c:363` | `void I_ShutdownMusic(void)` |
| `I_ShutdownSound` | function | `progs/doomgeneric/i_sound.c:250` | `void I_ShutdownSound(void)` |
| `I_SoundIsPlaying` | function | `progs/doomgeneric/i_sound.c:339` | `boolean I_SoundIsPlaying(int channel)` |
| `I_StartSound` | function | `progs/doomgeneric/i_sound.c:318` | `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)` |
| `I_StopSong` | function | `progs/doomgeneric/i_sound.c:420` | `void I_StopSong(void)` |
| `I_StopSound` | function | `progs/doomgeneric/i_sound.c:331` | `void I_StopSound(int channel)` |
| `I_UnRegisterSong` | function | `progs/doomgeneric/i_sound.c:404` | `void I_UnRegisterSong(void *handle)` |
| `I_UpdateSound` | function | `progs/doomgeneric/i_sound.c:275` | `void I_UpdateSound(void)` |
| `I_UpdateSoundParams` | function | `progs/doomgeneric/i_sound.c:309` | `void I_UpdateSoundParams(int channel, int vol, int sep)` |
| `InitMusicModule` | function | `progs/doomgeneric/i_sound.c:163` | `static void InitMusicModule(void)` |
| `InitSfxModule` | function | `progs/doomgeneric/i_sound.c:135` | `static void InitSfxModule(boolean use_sfx_prefix)` |
| `SndDeviceInList` | function | `progs/doomgeneric/i_sound.c:116` | `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,                            ...` |
| `libsamplerate_scale` | variable | `progs/doomgeneric/i_sound.c:444` | `extern float libsamplerate_scale;` |
| `music_opl_module` | variable | `progs/doomgeneric/i_sound.c:69` | `extern music_module_t music_opl_module;` |
| `music_pcspeaker_module` | variable | `progs/doomgeneric/i_sound.c:70` | `extern music_module_t music_pcspeaker_module;` |
| `music_sdl_module` | variable | `progs/doomgeneric/i_sound.c:68` | `extern music_module_t music_sdl_module;` |
| `opl_io_port` | variable | `progs/doomgeneric/i_sound.c:74` | `extern int opl_io_port;` |
| `sound_pcsound_module` | variable | `progs/doomgeneric/i_sound.c:67` | `extern sound_module_t sound_pcsound_module;` |
| `sound_sdl_module` | variable | `progs/doomgeneric/i_sound.c:66` | `extern sound_module_t sound_sdl_module;` |
| `timidity_cfg_path` | variable | `progs/doomgeneric/i_sound.c:78` | `extern char *timidity_cfg_path;` |
| `use_libsamplerate` | variable | `progs/doomgeneric/i_sound.c:443` | `extern int use_libsamplerate;` |
| `I_BindSoundVariables` | function | `progs/doomgeneric/i_sound.h:235` | `void I_BindSoundVariables(void);` |
| `I_GetSfxLumpNum` | function | `progs/doomgeneric/i_sound.h:154` | `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);` |
| `I_InitMusic` | function | `progs/doomgeneric/i_sound.h:217` | `void I_InitMusic(void);` |
| `I_InitSound` | function | `progs/doomgeneric/i_sound.h:152` | `void I_InitSound(boolean use_sfx_prefix);` |
| `I_PauseSong` | function | `progs/doomgeneric/i_sound.h:220` | `void I_PauseSong(void);` |
| `I_PlaySong` | function | `progs/doomgeneric/i_sound.h:224` | `void I_PlaySong(void *handle, boolean looping);` |
| `I_PrecacheSounds` | function | `progs/doomgeneric/i_sound.h:160` | `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);` |
| `I_RegisterSong` | function | `progs/doomgeneric/i_sound.h:222` | `void *I_RegisterSong(void *data, int len);` |
| `I_ResumeSong` | function | `progs/doomgeneric/i_sound.h:221` | `void I_ResumeSong(void);` |
| `I_SetMusicVolume` | function | `progs/doomgeneric/i_sound.h:219` | `void I_SetMusicVolume(int volume);` |
| `I_ShutdownMusic` | function | `progs/doomgeneric/i_sound.h:218` | `void I_ShutdownMusic(void);` |
| `I_ShutdownSound` | function | `progs/doomgeneric/i_sound.h:153` | `void I_ShutdownSound(void);` |
| `I_StartSound` | function | `progs/doomgeneric/i_sound.h:157` | `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);` |
| `I_StopSong` | function | `progs/doomgeneric/i_sound.h:225` | `void I_StopSong(void);` |
| `I_StopSound` | function | `progs/doomgeneric/i_sound.h:158` | `void I_StopSound(int channel);` |
| `I_UnRegisterSong` | function | `progs/doomgeneric/i_sound.h:223` | `void I_UnRegisterSong(void *handle);` |
| `I_UpdateSound` | function | `progs/doomgeneric/i_sound.h:155` | `void I_UpdateSound(void);` |
| `I_UpdateSoundParams` | function | `progs/doomgeneric/i_sound.h:156` | `void I_UpdateSoundParams(int channel, int vol, int sep);` |
| `__I_SOUND__` | macro | `progs/doomgeneric/i_sound.h:21` | `#define __I_SOUND__` |
| `music_module_t` | struct | `progs/doomgeneric/i_sound.h:164` | `` |
| `musicinfo_t` | struct | `progs/doomgeneric/i_sound.h:72` | `` |
| `sfxinfo_struct` | struct | `progs/doomgeneric/i_sound.h:31` | `` |
| `sfxinfo_t` | type_alias | `progs/doomgeneric/i_sound.h:29` | `typedef struct sfxinfo_struct sfxinfo_t;` |
| `snd_cachesize` | variable | `progs/doomgeneric/i_sound.h:231` | `extern int snd_cachesize;` |
| `snd_maxslicetime_ms` | variable | `progs/doomgeneric/i_sound.h:232` | `extern int snd_maxslicetime_ms;` |
| `snd_musiccmd` | variable | `progs/doomgeneric/i_sound.h:233` | `extern char *snd_musiccmd;` |
| `snd_musicdevice` | variable | `progs/doomgeneric/i_sound.h:229` | `extern int snd_musicdevice;` |
| `snd_samplerate` | variable | `progs/doomgeneric/i_sound.h:230` | `extern int snd_samplerate;` |
| `snd_sfxdevice` | variable | `progs/doomgeneric/i_sound.h:228` | `extern int snd_sfxdevice;` |
| `sound_module_t` | struct | `progs/doomgeneric/i_sound.h:105` | `` |
| `LONG` | macro | `progs/doomgeneric/i_swap.h:35` | `#define LONG(x)` |
| `LONG` | macro | `progs/doomgeneric/i_swap.h:48` | `#define LONG(x)` |
| `SHORT` | macro | `progs/doomgeneric/i_swap.h:34` | `#define SHORT(x)` |
| `SHORT` | macro | `progs/doomgeneric/i_swap.h:47` | `#define SHORT(x)` |
| `SYS_BIG_ENDIAN` | macro | `progs/doomgeneric/i_swap.h:42` | `#define SYS_BIG_ENDIAN` |
| `SYS_LITTLE_ENDIAN` | macro | `progs/doomgeneric/i_swap.h:40` | `#define SYS_LITTLE_ENDIAN` |
| `SYS_LITTLE_ENDIAN` | macro | `progs/doomgeneric/i_swap.h:50` | `#define SYS_LITTLE_ENDIAN` |
| `__I_SWAP__` | macro | `progs/doomgeneric/i_swap.h:21` | `#define __I_SWAP__` |
| `AutoAllocMemory` | function | `progs/doomgeneric/i_system.c:95` | `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)` |
| `DEFAULT_RAM` | macro | `progs/doomgeneric/i_system.c:58` | `#define DEFAULT_RAM` |
| `DOS_MEM_DUMP_SIZE` | macro | `progs/doomgeneric/i_system.c:490` | `#define DOS_MEM_DUMP_SIZE` |
| `EscapeShellString` | function | `progs/doomgeneric/i_system.c:280` | `static char *EscapeShellString(char *string)` |
| `I_AtExit` | function | `progs/doomgeneric/i_system.c:73` | `void I_AtExit(atexit_func_t func, boolean run_on_error)` |
| `I_ConsoleStdout` | function | `progs/doomgeneric/i_system.c:210` | `boolean I_ConsoleStdout(void)` |
| `I_Error` | function | `progs/doomgeneric/i_system.c:359` | `void I_Error (char *error, ...)` |
| `I_GetMemoryValue` | function | `progs/doomgeneric/i_system.c:502` | `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)` |
| `I_PrintBanner` | function | `progs/doomgeneric/i_system.c:166` | `void I_PrintBanner(char *msg)` |
| `I_PrintDivider` | function | `progs/doomgeneric/i_system.c:177` | `void I_PrintDivider(void)` |
| `I_PrintStartupBanner` | function | `progs/doomgeneric/i_system.c:189` | `void I_PrintStartupBanner(char *gamedescription)` |
| `I_Quit` | function | `progs/doomgeneric/i_system.c:246` | `void I_Quit (void)` |
| `I_Tactile` | function | `progs/doomgeneric/i_system.c:87` | `void I_Tactile(int on, int off, int total)` |
| `I_ZoneBase` | function | `progs/doomgeneric/i_system.c:133` | `byte *I_ZoneBase (int *size)` |
| `MIN_RAM` | macro | `progs/doomgeneric/i_system.c:59` | `#define MIN_RAM` |
| `WIN32_LEAN_AND_MEAN` | macro | `progs/doomgeneric/i_system.c:27` | `#define WIN32_LEAN_AND_MEAN` |
| `ZENITY_BINARY` | macro | `progs/doomgeneric/i_system.c:268` | `#define ZENITY_BINARY` |
| `ZenityAvailable` | function | `progs/doomgeneric/i_system.c:272` | `static int ZenityAvailable(void)` |
| `ZenityErrorBox` | function | `progs/doomgeneric/i_system.c:323` | `static int ZenityErrorBox(char *message)` |
| `atexit_listentry_s` | struct | `progs/doomgeneric/i_system.c:64` | `` |
| `atexit_listentry_t` | type_alias | `progs/doomgeneric/i_system.c:60` | `typedef struct atexit_listentry_s atexit_listentry_t;` |
| `I_AtExit` | function | `progs/doomgeneric/i_system.h:65` | `void I_AtExit(atexit_func_t func, boolean run_if_error);` |
| `I_BaseTiccmd` | function | `progs/doomgeneric/i_system.h:48` | `ticcmd_t* I_BaseTiccmd (void);` |
| `I_BindVariables` | function | `progs/doomgeneric/i_system.h:69` | `void I_BindVariables(void);` |
| `I_Error` | function | `progs/doomgeneric/i_system.h:55` | `void I_Error (char *error, ...);` |
| `I_Init` | function | `progs/doomgeneric/i_system.h:30` | `void I_Init (void);` |
| `I_PrintBanner` | function | `progs/doomgeneric/i_system.h:77` | `void I_PrintBanner(char *text);` |
| `I_PrintDivider` | function | `progs/doomgeneric/i_system.h:81` | `void I_PrintDivider(void);` |
| `I_PrintStartupBanner` | function | `progs/doomgeneric/i_system.h:73` | `void I_PrintStartupBanner(char *gamedescription);` |
| `I_Quit` | function | `progs/doomgeneric/i_system.h:53` | `void I_Quit (void);` |
| `I_Tactile` | function | `progs/doomgeneric/i_system.h:57` | `void I_Tactile (int on, int off, int total);` |
| `I_ZoneBase` | function | `progs/doomgeneric/i_system.h:35` | `byte* I_ZoneBase (int *size);` |
| `__I_SYSTEM__` | macro | `progs/doomgeneric/i_system.h:21` | `#define __I_SYSTEM__` |
| `I_GetTicks` | function | `progs/doomgeneric/i_timer.c:37` | `int I_GetTicks(void)` |
| `I_GetTime` | function | `progs/doomgeneric/i_timer.c:42` | `int  I_GetTime (void)` |
| `I_GetTimeMS` | function | `progs/doomgeneric/i_timer.c:61` | `int I_GetTimeMS(void)` |
| `I_InitTimer` | function | `progs/doomgeneric/i_timer.c:89` | `void I_InitTimer(void)` |
| `I_Sleep` | function | `progs/doomgeneric/i_timer.c:75` | `void I_Sleep(int ms)` |
| `I_WaitVBL` | function | `progs/doomgeneric/i_timer.c:83` | `void I_WaitVBL(int count)` |
| `I_GetTime` | function | `progs/doomgeneric/i_timer.h:27` | `int I_GetTime (void);` |
| `I_GetTimeMS` | function | `progs/doomgeneric/i_timer.h:30` | `int I_GetTimeMS (void);` |
| `I_InitTimer` | function | `progs/doomgeneric/i_timer.h:36` | `void I_InitTimer(void);` |
| `I_Sleep` | function | `progs/doomgeneric/i_timer.h:33` | `void I_Sleep(int ms);` |
| `I_WaitVBL` | function | `progs/doomgeneric/i_timer.h:39` | `void I_WaitVBL(int count);` |
| `TICRATE` | macro | `progs/doomgeneric/i_timer.h:23` | `#define TICRATE` |
| `__I_TIMER__` | macro | `progs/doomgeneric/i_timer.h:21` | `#define __I_TIMER__` |
| `FB_BitField` | struct | `progs/doomgeneric/i_video.c:54` | `` |
| `FB_ScreenInfo` | struct | `progs/doomgeneric/i_video.c:60` | `` |
| `GFX_RGB565` | macro | `progs/doomgeneric/i_video.c:310` | `#define GFX_RGB565(r, g, b)` |
| `GFX_RGB565_B` | macro | `progs/doomgeneric/i_video.c:313` | `#define GFX_RGB565_B(color)` |
| `GFX_RGB565_G` | macro | `progs/doomgeneric/i_video.c:312` | `#define GFX_RGB565_G(color)` |
| `GFX_RGB565_R` | macro | `progs/doomgeneric/i_video.c:311` | `#define GFX_RGB565_R(color)` |
| `I_BeginRead` | function | `progs/doomgeneric/i_video.c:369` | `void I_BeginRead (void)` |
| `I_BindVideoVariables` | function | `progs/doomgeneric/i_video.c:394` | `void I_BindVideoVariables (void)` |
| `I_CheckIsScreensaver` | function | `progs/doomgeneric/i_video.c:402` | `void I_CheckIsScreensaver (void)` |
| `I_DisplayFPSDots` | function | `progs/doomgeneric/i_video.c:398` | `void I_DisplayFPSDots (boolean dots_on)` |
| `I_EnableLoadingDisk` | function | `progs/doomgeneric/i_video.c:390` | `void I_EnableLoadingDisk(void)` |
| `I_EndRead` | function | `progs/doomgeneric/i_video.c:373` | `void I_EndRead (void)` |
| `I_FinishUpdate` | function | `progs/doomgeneric/i_video.c:255` | `void I_FinishUpdate (void)` |
| `I_GetEvent` | function | `progs/doomgeneric/i_video.c:89` | `void I_GetEvent(void);` |
| `I_GetPaletteIndex` | function | `progs/doomgeneric/i_video.c:333` | `int I_GetPaletteIndex (int r, int g, int b)` |
| `I_GraphicsCheckCommandLine` | function | `progs/doomgeneric/i_video.c:382` | `void I_GraphicsCheckCommandLine (void)` |
| `I_InitGraphics` | function | `progs/doomgeneric/i_video.c:179` | `void I_InitGraphics (void)` |
| `I_InitInput` | function | `progs/doomgeneric/i_video.c:228` | `extern int I_InitInput(void);` |
| `I_ReadScreen` | function | `progs/doomgeneric/i_video.c:302` | `void I_ReadScreen (byte* scr)` |
| `I_SetGrabMouseCallback` | function | `progs/doomgeneric/i_video.c:386` | `void I_SetGrabMouseCallback (grabmouse_callback_t func)` |
| `I_SetPalette` | function | `progs/doomgeneric/i_video.c:315` | `void I_SetPalette (byte* palette)` |
| `I_SetWindowTitle` | function | `progs/doomgeneric/i_video.c:377` | `void I_SetWindowTitle (char *title)` |
| `I_ShutdownGraphics` | function | `progs/doomgeneric/i_video.c:232` | `void I_ShutdownGraphics (void)` |
| `I_StartFrame` | function | `progs/doomgeneric/i_video.c:237` | `void I_StartFrame (void)` |
| `I_StartTic` | function | `progs/doomgeneric/i_video.c:242` | `void I_StartTic (void)` |
| `I_UpdateNoBlit` | function | `progs/doomgeneric/i_video.c:247` | `void I_UpdateNoBlit (void)` |
| `cmap_to_fb` | function | `progs/doomgeneric/i_video.c:152` | `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)` |
| `cmap_to_rgb565` | function | `progs/doomgeneric/i_video.c:131` | `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)` |
| `col_t` | struct | `progs/doomgeneric/i_video.c:120` | `` |
| `color` | struct | `progs/doomgeneric/i_video.c:80` | `` |
| `minios_palette_dirty` | variable | `progs/doomgeneric/i_video.c:52` | `extern volatile int minios_palette_dirty;` |
| `I_BeginRead` | function | `progs/doomgeneric/i_video.h:112` | `void I_BeginRead (void);` |
| `I_BindVideoVariables` | function | `progs/doomgeneric/i_video.h:120` | `void I_BindVideoVariables(void);` |
| `I_CheckIsScreensaver` | function | `progs/doomgeneric/i_video.h:116` | `void I_CheckIsScreensaver(void);` |
| `I_DisplayFPSDots` | function | `progs/doomgeneric/i_video.h:119` | `void I_DisplayFPSDots(boolean dots_on);` |
| `I_EnableLoadingDisk` | function | `progs/doomgeneric/i_video.h:137` | `void I_EnableLoadingDisk(void);` |
| `I_FinishUpdate` | function | `progs/doomgeneric/i_video.h:108` | `void I_FinishUpdate (void);` |
| `I_GetPaletteIndex` | function | `progs/doomgeneric/i_video.h:105` | `int I_GetPaletteIndex(int r, int g, int b);` |
| `I_GraphicsCheckCommandLine` | function | `progs/doomgeneric/i_video.h:99` | `void I_GraphicsCheckCommandLine(void);` |
| `I_InitGraphics` | function | `progs/doomgeneric/i_video.h:97` | `void I_InitGraphics (void);` |
| `I_InitWindowIcon` | function | `progs/doomgeneric/i_video.h:123` | `void I_InitWindowIcon(void);` |
| `I_InitWindowTitle` | function | `progs/doomgeneric/i_video.h:122` | `void I_InitWindowTitle(void);` |
| `I_ReadScreen` | function | `progs/doomgeneric/i_video.h:110` | `void I_ReadScreen (byte* scr);` |
| `I_SetGrabMouseCallback` | function | `progs/doomgeneric/i_video.h:117` | `void I_SetGrabMouseCallback(grabmouse_callback_t func);` |
| `I_SetPalette` | function | `progs/doomgeneric/i_video.h:104` | `void I_SetPalette (byte* palette);` |
| `I_SetWindowTitle` | function | `progs/doomgeneric/i_video.h:114` | `void I_SetWindowTitle(char *title);` |
| `I_ShutdownGraphics` | function | `progs/doomgeneric/i_video.h:101` | `void I_ShutdownGraphics(void);` |
| `I_StartFrame` | function | `progs/doomgeneric/i_video.h:128` | `void I_StartFrame (void);` |
| `I_StartTic` | function | `progs/doomgeneric/i_video.h:133` | `void I_StartTic (void);` |
| `I_UpdateNoBlit` | function | `progs/doomgeneric/i_video.h:107` | `void I_UpdateNoBlit (void);` |
| `I_VideoBuffer` | variable | `progs/doomgeneric/i_video.h:147` | `extern byte *I_VideoBuffer;` |
| `MAX_MOUSE_BUTTONS` | macro | `progs/doomgeneric/i_video.h:38` | `#define MAX_MOUSE_BUTTONS` |
| `SCREENHEIGHT` | macro | `progs/doomgeneric/i_video.h:28` | `#define SCREENHEIGHT` |
| `SCREENHEIGHT_4_3` | macro | `progs/doomgeneric/i_video.h:36` | `#define SCREENHEIGHT_4_3` |
| `SCREENWIDTH` | macro | `progs/doomgeneric/i_video.h:27` | `#define SCREENWIDTH` |
| `SCREENWIDTH_4_3` | macro | `progs/doomgeneric/i_video.h:32` | `#define SCREENWIDTH_4_3` |
| `__I_VIDEO__` | macro | `progs/doomgeneric/i_video.h:21` | `#define __I_VIDEO__` |
| `aspect_ratio_correct` | variable | `progs/doomgeneric/i_video.h:153` | `extern int aspect_ratio_correct;` |
| `diskicon_readbytes` | variable | `progs/doomgeneric/i_video.h:156` | `extern int diskicon_readbytes;` |
| `fullscreen` | variable | `progs/doomgeneric/i_video.h:152` | `extern int fullscreen;` |
| `mouse_acceleration` | variable | `progs/doomgeneric/i_video.h:142` | `extern float mouse_acceleration;` |
| `mouse_threshold` | variable | `progs/doomgeneric/i_video.h:143` | `extern int mouse_threshold;` |
| `screen_bpp` | variable | `progs/doomgeneric/i_video.h:151` | `extern int screen_bpp;` |
| `screen_height` | variable | `progs/doomgeneric/i_video.h:150` | `extern int screen_height;` |
| `screen_mode_t` | struct | `progs/doomgeneric/i_video.h:40` | `` |
| `screen_width` | variable | `progs/doomgeneric/i_video.h:149` | `extern int screen_width;` |
| `screensaver_mode` | variable | `progs/doomgeneric/i_video.h:145` | `extern boolean screensaver_mode;` |
| `screenvisible` | variable | `progs/doomgeneric/i_video.h:140` | `extern boolean screenvisible;` |
| `show_diskicon` | variable | `progs/doomgeneric/i_video.h:155` | `extern int show_diskicon;` |
| `usegamma` | variable | `progs/doomgeneric/i_video.h:146` | `extern int usegamma;` |
| `vanilla_keyboard_mapping` | variable | `progs/doomgeneric/i_video.h:144` | `extern int vanilla_keyboard_mapping;` |
| `video_driver` | variable | `progs/doomgeneric/i_video.h:139` | `extern char *video_driver;` |
| `A_BFGSpray` | function | `progs/doomgeneric/info.c:73` | `void A_BFGSpray();` |
| `A_BFGsound` | function | `progs/doomgeneric/info.c:71` | `void A_BFGsound();` |
| `A_BabyMetal` | function | `progs/doomgeneric/info.c:110` | `void A_BabyMetal();` |
| `A_BossDeath` | function | `progs/doomgeneric/info.c:100` | `void A_BossDeath();` |
| `A_BrainAwake` | function | `progs/doomgeneric/info.c:120` | `void A_BrainAwake();` |
| `A_BrainDie` | function | `progs/doomgeneric/info.c:119` | `void A_BrainDie();` |
| `A_BrainExplode` | function | `progs/doomgeneric/info.c:124` | `void A_BrainExplode();` |
| `A_BrainPain` | function | `progs/doomgeneric/info.c:117` | `void A_BrainPain();` |
| `A_BrainScream` | function | `progs/doomgeneric/info.c:118` | `void A_BrainScream();` |
| `A_BrainSpit` | function | `progs/doomgeneric/info.c:121` | `void A_BrainSpit();` |
| `A_BruisAttack` | function | `progs/doomgeneric/info.c:106` | `void A_BruisAttack();` |
| `A_BspiAttack` | function | `progs/doomgeneric/info.c:111` | `void A_BspiAttack();` |
| `A_CPosAttack` | function | `progs/doomgeneric/info.c:101` | `void A_CPosAttack();` |
| `A_CPosRefire` | function | `progs/doomgeneric/info.c:102` | `void A_CPosRefire();` |
| `A_Chase` | function | `progs/doomgeneric/info.c:80` | `void A_Chase();` |
| `A_CheckReload` | function | `progs/doomgeneric/info.c:62` | `void A_CheckReload();` |
| `A_CloseShotgun2` | function | `progs/doomgeneric/info.c:65` | `void A_CloseShotgun2();` |
| `A_CyberAttack` | function | `progs/doomgeneric/info.c:113` | `void A_CyberAttack();` |
| `A_Explode` | function | `progs/doomgeneric/info.c:74` | `void A_Explode();` |
| `A_FaceTarget` | function | `progs/doomgeneric/info.c:81` | `void A_FaceTarget();` |
| `A_Fall` | function | `progs/doomgeneric/info.c:77` | `void A_Fall();` |
| `A_FatAttack1` | function | `progs/doomgeneric/info.c:97` | `void A_FatAttack1();` |
| `A_FatAttack2` | function | `progs/doomgeneric/info.c:98` | `void A_FatAttack2();` |
| `A_FatAttack3` | function | `progs/doomgeneric/info.c:99` | `void A_FatAttack3();` |
| `A_FatRaise` | function | `progs/doomgeneric/info.c:96` | `void A_FatRaise();` |
| `A_Fire` | function | `progs/doomgeneric/info.c:90` | `void A_Fire();` |
| `A_FireBFG` | function | `progs/doomgeneric/info.c:72` | `void A_FireBFG();` |
| `A_FireCGun` | function | `progs/doomgeneric/info.c:66` | `void A_FireCGun();` |
| `A_FireCrackle` | function | `progs/doomgeneric/info.c:91` | `void A_FireCrackle();` |
| `A_FireMissile` | function | `progs/doomgeneric/info.c:68` | `void A_FireMissile();` |
| `A_FirePistol` | function | `progs/doomgeneric/info.c:57` | `void A_FirePistol();` |
| `A_FirePlasma` | function | `progs/doomgeneric/info.c:70` | `void A_FirePlasma();` |
| `A_FireShotgun` | function | `progs/doomgeneric/info.c:59` | `void A_FireShotgun();` |
| `A_FireShotgun2` | function | `progs/doomgeneric/info.c:61` | `void A_FireShotgun2();` |
| `A_GunFlash` | function | `progs/doomgeneric/info.c:67` | `void A_GunFlash();` |
| `A_HeadAttack` | function | `progs/doomgeneric/info.c:105` | `void A_HeadAttack();` |
| `A_Hoof` | function | `progs/doomgeneric/info.c:112` | `void A_Hoof();` |
| `A_KeenDie` | function | `progs/doomgeneric/info.c:116` | `void A_KeenDie();` |
| `A_Light0` | function | `progs/doomgeneric/info.c:51` | `void A_Light0();` |
| `A_Light1` | function | `progs/doomgeneric/info.c:58` | `void A_Light1();` |
| `A_Light2` | function | `progs/doomgeneric/info.c:60` | `void A_Light2();` |
| `A_LoadShotgun2` | function | `progs/doomgeneric/info.c:64` | `void A_LoadShotgun2();` |
| `A_Look` | function | `progs/doomgeneric/info.c:79` | `void A_Look();` |
| `A_Lower` | function | `progs/doomgeneric/info.c:53` | `void A_Lower();` |
| `A_Metal` | function | `progs/doomgeneric/info.c:108` | `void A_Metal();` |
| `A_OpenShotgun2` | function | `progs/doomgeneric/info.c:63` | `void A_OpenShotgun2();` |
| `A_Pain` | function | `progs/doomgeneric/info.c:75` | `void A_Pain();` |
| `A_PainAttack` | function | `progs/doomgeneric/info.c:114` | `void A_PainAttack();` |
| `A_PainDie` | function | `progs/doomgeneric/info.c:115` | `void A_PainDie();` |
| `A_PlayerScream` | function | `progs/doomgeneric/info.c:76` | `void A_PlayerScream();` |
| `A_PosAttack` | function | `progs/doomgeneric/info.c:82` | `void A_PosAttack();` |
| `A_Punch` | function | `progs/doomgeneric/info.c:55` | `void A_Punch();` |
| `A_Raise` | function | `progs/doomgeneric/info.c:54` | `void A_Raise();` |
| `A_ReFire` | function | `progs/doomgeneric/info.c:56` | `void A_ReFire();` |
| `A_SPosAttack` | function | `progs/doomgeneric/info.c:84` | `void A_SPosAttack();` |
| `A_SargAttack` | function | `progs/doomgeneric/info.c:104` | `void A_SargAttack();` |
| `A_Saw` | function | `progs/doomgeneric/info.c:69` | `void A_Saw();` |
| `A_Scream` | function | `progs/doomgeneric/info.c:83` | `void A_Scream();` |
| `A_SkelFist` | function | `progs/doomgeneric/info.c:94` | `void A_SkelFist();` |
| `A_SkelMissile` | function | `progs/doomgeneric/info.c:95` | `void A_SkelMissile();` |
| `A_SkelWhoosh` | function | `progs/doomgeneric/info.c:93` | `void A_SkelWhoosh();` |
| `A_SkullAttack` | function | `progs/doomgeneric/info.c:107` | `void A_SkullAttack();` |
| `A_SpawnFly` | function | `progs/doomgeneric/info.c:123` | `void A_SpawnFly();` |
| `A_SpawnSound` | function | `progs/doomgeneric/info.c:122` | `void A_SpawnSound();` |
| `A_SpidRefire` | function | `progs/doomgeneric/info.c:109` | `void A_SpidRefire();` |
| `A_StartFire` | function | `progs/doomgeneric/info.c:89` | `void A_StartFire();` |
| `A_Tracer` | function | `progs/doomgeneric/info.c:92` | `void A_Tracer();` |
| `A_TroopAttack` | function | `progs/doomgeneric/info.c:103` | `void A_TroopAttack();` |
| `A_VileAttack` | function | `progs/doomgeneric/info.c:88` | `void A_VileAttack();` |
| `A_VileChase` | function | `progs/doomgeneric/info.c:85` | `void A_VileChase();` |
| `A_VileStart` | function | `progs/doomgeneric/info.c:86` | `void A_VileStart();` |
| `A_VileTarget` | function | `progs/doomgeneric/info.c:87` | `void A_VileTarget();` |
| `A_WeaponReady` | function | `progs/doomgeneric/info.c:52` | `void A_WeaponReady();` |
| `A_XScream` | function | `progs/doomgeneric/info.c:78` | `void A_XScream();` |
| `__INFO__` | macro | `progs/doomgeneric/info.h:22` | `#define __INFO__` |
| `mobjinfo` | variable | `progs/doomgeneric/info.h:1329` | `extern mobjinfo_t mobjinfo[NUMMOBJTYPES];` |
| `mobjinfo_t` | struct | `progs/doomgeneric/info.h:1301` | `` |
| `sprnames` | variable | `progs/doomgeneric/info.h:1157` | `extern char *sprnames[];` |
| `state_t` | struct | `progs/doomgeneric/info.h:1144` | `` |
| `states` | variable | `progs/doomgeneric/info.h:1156` | `extern state_t states[NUMSTATES];` |
| `LoadResponseFile` | function | `progs/doomgeneric/m_argv.c:75` | `static void LoadResponseFile(int argv_index)` |
| `MAXARGVS` | macro | `progs/doomgeneric/m_argv.c:73` | `#define MAXARGVS` |
| `M_CheckParm` | function | `progs/doomgeneric/m_argv.c:68` | `int M_CheckParm(char *check)` |
| `M_CheckParmWithArgs` | function | `progs/doomgeneric/m_argv.c:43` | `int M_CheckParmWithArgs(char *check, int num_args)` |
| `M_FindResponseFile` | function | `progs/doomgeneric/m_argv.c:235` | `void M_FindResponseFile(void)` |
| `M_GetExecutableName` | function | `progs/doomgeneric/m_argv.c:250` | `char *M_GetExecutableName(void)` |
| `M_ParmExists` | function | `progs/doomgeneric/m_argv.c:63` | `boolean M_ParmExists(char *check)` |
| `M_CheckParm` | function | `progs/doomgeneric/m_argv.h:33` | `int M_CheckParm (char* check);` |
| `M_CheckParmWithArgs` | function | `progs/doomgeneric/m_argv.h:37` | `int M_CheckParmWithArgs(char *check, int num_args);` |
| `M_FindResponseFile` | function | `progs/doomgeneric/m_argv.h:39` | `void M_FindResponseFile(void);` |
| `M_GetExecutableName` | function | `progs/doomgeneric/m_argv.h:47` | `char *M_GetExecutableName(void);` |
| `__M_ARGV__` | macro | `progs/doomgeneric/m_argv.h:21` | `#define __M_ARGV__` |
| `myargc` | variable | `progs/doomgeneric/m_argv.h:28` | `extern int myargc;` |
| `myargv` | variable | `progs/doomgeneric/m_argv.h:29` | `extern char** myargv;` |
| `M_AddToBox` | function | `progs/doomgeneric/m_bbox.c:36` | `void M_AddToBox ( fixed_t*	box,   fixed_t	x,   fixed_t	y )` |
| `M_ClearBox` | function | `progs/doomgeneric/m_bbox.c:29` | `void M_ClearBox (fixed_t *box)` |
| `M_AddToBox` | function | `progs/doomgeneric/m_bbox.h:41` | `void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );` |
| `M_ClearBox` | function | `progs/doomgeneric/m_bbox.h:38` | `void M_ClearBox (fixed_t* box);` |
| `__M_BBOX__` | macro | `progs/doomgeneric/m_bbox.h:21` | `#define __M_BBOX__` |
| `cht_CheckCheat` | function | `progs/doomgeneric/m_cheat.c:35` | `int cht_CheckCheat ( cheatseq_t*	cht,   char		key )` |
| `cht_GetParam` | function | `progs/doomgeneric/m_cheat.c:82` | `void cht_GetParam ( cheatseq_t*	cht,   char*		buffer )` |
| `CHEAT` | macro | `progs/doomgeneric/m_cheat.h:29` | `#define CHEAT(value, parameters)` |
| `MAX_CHEAT_LEN` | macro | `progs/doomgeneric/m_cheat.h:32` | `#define MAX_CHEAT_LEN` |
| `MAX_CHEAT_PARAMS` | macro | `progs/doomgeneric/m_cheat.h:33` | `#define MAX_CHEAT_PARAMS` |
| `__M_CHEAT__` | macro | `progs/doomgeneric/m_cheat.h:21` | `#define __M_CHEAT__` |
| `cheatseq_t` | struct | `progs/doomgeneric/m_cheat.h:35` | `` |
| `cht_CheckCheat` | function | `progs/doomgeneric/m_cheat.h:51` | `int cht_CheckCheat ( cheatseq_t* cht, char key );` |
| `cht_GetParam` | function | `progs/doomgeneric/m_cheat.h:57` | `void cht_GetParam ( cheatseq_t* cht, char* buffer );` |
| `CONFIG_VARIABLE_FLOAT` | macro | `progs/doomgeneric/m_config.c:104` | `#define CONFIG_VARIABLE_FLOAT(name)` |
| `CONFIG_VARIABLE_GENERIC` | macro | `progs/doomgeneric/m_config.c:95` | `#define CONFIG_VARIABLE_GENERIC(name, type)` |
| `CONFIG_VARIABLE_INT` | macro | `progs/doomgeneric/m_config.c:100` | `#define CONFIG_VARIABLE_INT(name)` |
| `CONFIG_VARIABLE_INT_HEX` | macro | `progs/doomgeneric/m_config.c:102` | `#define CONFIG_VARIABLE_INT_HEX(name)` |
| `CONFIG_VARIABLE_KEY` | macro | `progs/doomgeneric/m_config.c:98` | `#define CONFIG_VARIABLE_KEY(name)` |
| `CONFIG_VARIABLE_STRING` | macro | `progs/doomgeneric/m_config.c:106` | `#define CONFIG_VARIABLE_STRING(name)` |
| `GetDefaultConfigDir` | function | `progs/doomgeneric/m_config.c:2043` | `static char *GetDefaultConfigDir(void)` |
| `GetDefaultForName` | function | `progs/doomgeneric/m_config.c:1937` | `static default_t *GetDefaultForName(char *name)` |
| `LoadDefaultCollection` | function | `progs/doomgeneric/m_config.c:1771` | `static void LoadDefaultCollection(default_collection_t *collection)` |
| `M_BindVariable` | function | `progs/doomgeneric/m_config.c:1964` | `void M_BindVariable(char *name, void *location)` |
| `M_GetFloatVariable` | function | `progs/doomgeneric/m_config.c:2025` | `float M_GetFloatVariable(char *name)` |
| `M_GetIntVariable` | function | `progs/doomgeneric/m_config.c:1995` | `int M_GetIntVariable(char *name)` |
| `M_GetSaveGameDir` | function | `progs/doomgeneric/m_config.c:2087` | `char *M_GetSaveGameDir(char *iwadname)` |
| `M_GetStrVariable` | function | `progs/doomgeneric/m_config.c:2010` | `const char *M_GetStrVariable(char *name)` |
| `M_LoadDefaults` | function | `progs/doomgeneric/m_config.c:1881` | `void M_LoadDefaults (void)` |
| `M_SaveDefaults` | function | `progs/doomgeneric/m_config.c:1846` | `void M_SaveDefaults (void)` |
| `M_SaveDefaultsAlternate` | function | `progs/doomgeneric/m_config.c:1856` | `void M_SaveDefaultsAlternate(char *main, char *extra)` |
| `M_SetConfigDir` | function | `progs/doomgeneric/m_config.c:2059` | `void M_SetConfigDir(char *dir)` |
| `M_SetConfigFilenames` | function | `progs/doomgeneric/m_config.c:1836` | `void M_SetConfigFilenames(char *main_config, char *extra_config)` |
| `M_SetVariable` | function | `progs/doomgeneric/m_config.c:1977` | `boolean M_SetVariable(char *name, char *value)` |
| `ParseIntParameter` | function | `progs/doomgeneric/m_config.c:1716` | `static int ParseIntParameter(char *strparm)` |
| `SaveDefaultCollection` | function | `progs/doomgeneric/m_config.c:1609` | `static void SaveDefaultCollection(default_collection_t *collection)` |
| `SearchCollection` | function | `progs/doomgeneric/m_config.c:1563` | `static default_t *SearchCollection(default_collection_t *collection, char *name)` |
| `SetVariable` | function | `progs/doomgeneric/m_config.c:1728` | `static void SetVariable(default_t *def, char *value)` |
| `default_collection_t` | struct | `progs/doomgeneric/m_config.c:88` | `` |
| `default_t` | struct | `progs/doomgeneric/m_config.c:61` | `` |
| `M_BindVariable` | function | `progs/doomgeneric/m_config.h:29` | `void M_BindVariable(char *name, void *variable);` |
| `M_GetFloatVariable` | function | `progs/doomgeneric/m_config.h:33` | `float M_GetFloatVariable(char *name);` |
| `M_GetIntVariable` | function | `progs/doomgeneric/m_config.h:31` | `int M_GetIntVariable(char *name);` |
| `M_GetSaveGameDir` | function | `progs/doomgeneric/m_config.h:35` | `char *M_GetSaveGameDir(char *iwadname);` |
| `M_GetStrVariable` | function | `progs/doomgeneric/m_config.h:32` | `const char *M_GetStrVariable(char *name);` |
| `M_LoadDefaults` | function | `progs/doomgeneric/m_config.h:25` | `void M_LoadDefaults(void);` |
| `M_SaveDefaults` | function | `progs/doomgeneric/m_config.h:26` | `void M_SaveDefaults(void);` |
| `M_SaveDefaultsAlternate` | function | `progs/doomgeneric/m_config.h:27` | `void M_SaveDefaultsAlternate(char *main, char *extra);` |
| `M_SetConfigDir` | function | `progs/doomgeneric/m_config.h:28` | `void M_SetConfigDir(char *dir);` |
| `M_SetConfigFilenames` | function | `progs/doomgeneric/m_config.h:34` | `void M_SetConfigFilenames(char *main_config, char *extra_config);` |
| `__M_CONFIG__` | macro | `progs/doomgeneric/m_config.h:21` | `#define __M_CONFIG__` |
| `configdir` | variable | `progs/doomgeneric/m_config.h:37` | `extern char *configdir;` |
| `M_ApplyPlatformDefaults` | function | `progs/doomgeneric/m_controls.c:394` | `void M_ApplyPlatformDefaults(void)` |
| `M_BindBaseControls` | function | `progs/doomgeneric/m_controls.c:204` | `void M_BindBaseControls(void)` |
| `M_BindChatControls` | function | `progs/doomgeneric/m_controls.c:375` | `void M_BindChatControls(unsigned int num_players)` |
| `M_BindHereticControls` | function | `progs/doomgeneric/m_controls.c:241` | `void M_BindHereticControls(void)` |
| `M_BindHexenControls` | function | `progs/doomgeneric/m_controls.c:256` | `void M_BindHexenControls(void)` |
| `M_BindMapControls` | function | `progs/doomgeneric/m_controls.c:328` | `void M_BindMapControls(void)` |
| `M_BindMenuControls` | function | `progs/doomgeneric/m_controls.c:344` | `void M_BindMenuControls(void)` |
| `M_BindStrifeControls` | function | `progs/doomgeneric/m_controls.c:272` | `void M_BindStrifeControls(void)` |
| `M_BindWeaponControls` | function | `progs/doomgeneric/m_controls.c:307` | `void M_BindWeaponControls(void)` |
| `M_ApplyPlatformDefaults` | function | `progs/doomgeneric/m_controls.h:165` | `void M_ApplyPlatformDefaults(void);` |
| `M_BindBaseControls` | function | `progs/doomgeneric/m_controls.h:156` | `void M_BindBaseControls(void);` |
| `M_BindChatControls` | function | `progs/doomgeneric/m_controls.h:163` | `void M_BindChatControls(unsigned int num_players);` |
| `M_BindHereticControls` | function | `progs/doomgeneric/m_controls.h:157` | `void M_BindHereticControls(void);` |
| `M_BindHexenControls` | function | `progs/doomgeneric/m_controls.h:158` | `void M_BindHexenControls(void);` |
| `M_BindMapControls` | function | `progs/doomgeneric/m_controls.h:161` | `void M_BindMapControls(void);` |
| `M_BindMenuControls` | function | `progs/doomgeneric/m_controls.h:162` | `void M_BindMenuControls(void);` |
| `M_BindStrifeControls` | function | `progs/doomgeneric/m_controls.h:159` | `void M_BindStrifeControls(void);` |
| `M_BindWeaponControls` | function | `progs/doomgeneric/m_controls.h:160` | `void M_BindWeaponControls(void);` |
| `__M_CONTROLS_H__` | macro | `progs/doomgeneric/m_controls.h:18` | `#define __M_CONTROLS_H__` |
| `dclick_use` | variable | `progs/doomgeneric/m_controls.h:154` | `extern int dclick_use;` |
| `joybfire` | variable | `progs/doomgeneric/m_controls.h:139` | `extern int joybfire;` |
| `joybjump` | variable | `progs/doomgeneric/m_controls.h:144` | `extern int joybjump;` |
| `joybmenu` | variable | `progs/doomgeneric/m_controls.h:152` | `extern int joybmenu;` |
| `joybnextweapon` | variable | `progs/doomgeneric/m_controls.h:150` | `extern int joybnextweapon;` |
| `joybprevweapon` | variable | `progs/doomgeneric/m_controls.h:149` | `extern int joybprevweapon;` |
| `joybspeed` | variable | `progs/doomgeneric/m_controls.h:142` | `extern int joybspeed;` |
| `joybstrafe` | variable | `progs/doomgeneric/m_controls.h:140` | `extern int joybstrafe;` |
| `joybstrafeleft` | variable | `progs/doomgeneric/m_controls.h:146` | `extern int joybstrafeleft;` |
| `joybstraferight` | variable | `progs/doomgeneric/m_controls.h:147` | `extern int joybstraferight;` |
| `joybuse` | variable | `progs/doomgeneric/m_controls.h:141` | `extern int joybuse;` |
| `key_arti_all` | variable | `progs/doomgeneric/m_controls.h:70` | `extern int key_arti_all;` |
| `key_arti_blastradius` | variable | `progs/doomgeneric/m_controls.h:73` | `extern int key_arti_blastradius;` |
| `key_arti_egg` | variable | `progs/doomgeneric/m_controls.h:76` | `extern int key_arti_egg;` |
| `key_arti_health` | variable | `progs/doomgeneric/m_controls.h:71` | `extern int key_arti_health;` |
| `key_arti_invulnerability` | variable | `progs/doomgeneric/m_controls.h:77` | `extern int key_arti_invulnerability;` |
| `key_arti_poisonbag` | variable | `progs/doomgeneric/m_controls.h:72` | `extern int key_arti_poisonbag;` |
| `key_arti_teleport` | variable | `progs/doomgeneric/m_controls.h:74` | `extern int key_arti_teleport;` |
| `key_arti_teleportother` | variable | `progs/doomgeneric/m_controls.h:75` | `extern int key_arti_teleportother;` |
| `key_demo_quit` | variable | `progs/doomgeneric/m_controls.h:79` | `extern int key_demo_quit;` |
| `key_down` | variable | `progs/doomgeneric/m_controls.h:24` | `extern int key_down;` |
| `key_fire` | variable | `progs/doomgeneric/m_controls.h:27` | `extern int key_fire;` |
| `key_flycenter` | variable | `progs/doomgeneric/m_controls.h:36` | `extern int key_flycenter;` |
| `key_flydown` | variable | `progs/doomgeneric/m_controls.h:35` | `extern int key_flydown;` |
| `key_flyup` | variable | `progs/doomgeneric/m_controls.h:34` | `extern int key_flyup;` |
| `key_invdrop` | variable | `progs/doomgeneric/m_controls.h:53` | `extern int key_invdrop;` |
| `key_invend` | variable | `progs/doomgeneric/m_controls.h:51` | `extern int key_invend;` |
| `key_invhome` | variable | `progs/doomgeneric/m_controls.h:50` | `extern int key_invhome;` |
| `key_invkey` | variable | `progs/doomgeneric/m_controls.h:49` | `extern int key_invkey;` |
| `key_invleft` | variable | `progs/doomgeneric/m_controls.h:40` | `extern int key_invleft;` |
| `key_invpop` | variable | `progs/doomgeneric/m_controls.h:48` | `extern int key_invpop;` |
| `key_invquery` | variable | `progs/doomgeneric/m_controls.h:46` | `extern int key_invquery;` |
| `key_invright` | variable | `progs/doomgeneric/m_controls.h:41` | `extern int key_invright;` |
| `key_invuse` | variable | `progs/doomgeneric/m_controls.h:52` | `extern int key_invuse;` |
| `key_jump` | variable | `progs/doomgeneric/m_controls.h:32` | `extern int key_jump;` |
| `key_left` | variable | `progs/doomgeneric/m_controls.h:21` | `extern int key_left;` |
| `key_lookcenter` | variable | `progs/doomgeneric/m_controls.h:39` | `extern int key_lookcenter;` |
| `key_lookdown` | variable | `progs/doomgeneric/m_controls.h:38` | `extern int key_lookdown;` |
| `key_lookup` | variable | `progs/doomgeneric/m_controls.h:37` | `extern int key_lookup;` |
| `key_map_clearmark` | variable | `progs/doomgeneric/m_controls.h:95` | `extern int key_map_clearmark;` |
| `key_map_east` | variable | `progs/doomgeneric/m_controls.h:86` | `extern int key_map_east;` |
| `key_map_follow` | variable | `progs/doomgeneric/m_controls.h:92` | `extern int key_map_follow;` |
| `key_map_grid` | variable | `progs/doomgeneric/m_controls.h:93` | `extern int key_map_grid;` |
| `key_map_mark` | variable | `progs/doomgeneric/m_controls.h:94` | `extern int key_map_mark;` |
| `key_map_maxzoom` | variable | `progs/doomgeneric/m_controls.h:91` | `extern int key_map_maxzoom;` |
| `key_map_north` | variable | `progs/doomgeneric/m_controls.h:84` | `extern int key_map_north;` |
| `key_map_south` | variable | `progs/doomgeneric/m_controls.h:85` | `extern int key_map_south;` |
| `key_map_toggle` | variable | `progs/doomgeneric/m_controls.h:90` | `extern int key_map_toggle;` |
| `key_map_west` | variable | `progs/doomgeneric/m_controls.h:87` | `extern int key_map_west;` |
| `key_map_zoomin` | variable | `progs/doomgeneric/m_controls.h:88` | `extern int key_map_zoomin;` |
| `key_map_zoomout` | variable | `progs/doomgeneric/m_controls.h:89` | `extern int key_map_zoomout;` |
| `key_menu_abort` | variable | `progs/doomgeneric/m_controls.h:107` | `extern int key_menu_abort;` |
| `key_menu_activate` | variable | `progs/doomgeneric/m_controls.h:99` | `extern int key_menu_activate;` |
| `key_menu_back` | variable | `progs/doomgeneric/m_controls.h:104` | `extern int key_menu_back;` |
| `key_menu_confirm` | variable | `progs/doomgeneric/m_controls.h:106` | `extern int key_menu_confirm;` |
| `key_menu_decscreen` | variable | `progs/doomgeneric/m_controls.h:122` | `extern int key_menu_decscreen;` |
| `key_menu_detail` | variable | `progs/doomgeneric/m_controls.h:113` | `extern int key_menu_detail;` |
| `key_menu_down` | variable | `progs/doomgeneric/m_controls.h:101` | `extern int key_menu_down;` |
| `key_menu_endgame` | variable | `progs/doomgeneric/m_controls.h:115` | `extern int key_menu_endgame;` |
| `key_menu_forward` | variable | `progs/doomgeneric/m_controls.h:105` | `extern int key_menu_forward;` |
| `key_menu_gamma` | variable | `progs/doomgeneric/m_controls.h:119` | `extern int key_menu_gamma;` |
| `key_menu_help` | variable | `progs/doomgeneric/m_controls.h:109` | `extern int key_menu_help;` |
| `key_menu_incscreen` | variable | `progs/doomgeneric/m_controls.h:121` | `extern int key_menu_incscreen;` |
| `key_menu_left` | variable | `progs/doomgeneric/m_controls.h:102` | `extern int key_menu_left;` |
| `key_menu_load` | variable | `progs/doomgeneric/m_controls.h:111` | `extern int key_menu_load;` |
| `key_menu_messages` | variable | `progs/doomgeneric/m_controls.h:116` | `extern int key_menu_messages;` |
| `key_menu_qload` | variable | `progs/doomgeneric/m_controls.h:117` | `extern int key_menu_qload;` |
| `key_menu_qsave` | variable | `progs/doomgeneric/m_controls.h:114` | `extern int key_menu_qsave;` |
| `key_menu_quit` | variable | `progs/doomgeneric/m_controls.h:118` | `extern int key_menu_quit;` |
| `key_menu_right` | variable | `progs/doomgeneric/m_controls.h:103` | `extern int key_menu_right;` |
| `key_menu_save` | variable | `progs/doomgeneric/m_controls.h:110` | `extern int key_menu_save;` |
| `key_menu_screenshot` | variable | `progs/doomgeneric/m_controls.h:123` | `extern int key_menu_screenshot;` |
| `key_menu_up` | variable | `progs/doomgeneric/m_controls.h:100` | `extern int key_menu_up;` |

Next: [SYMBOLS_p16.md](SYMBOLS_p16.md)
