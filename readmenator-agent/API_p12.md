# API (page 12 of 21)
Previous: [API_p11.md](API_p11.md)

## progs/doomgeneric/i_cdmus.h
Imported by: `progs/doomgeneric/i_cdmus.c`
- `I_CDMusInit` (function) `progs/doomgeneric/i_cdmus.h:31` `int I_CDMusInit(void);`
- `I_CDMusPrintStartup` (function) `progs/doomgeneric/i_cdmus.h:32` `void I_CDMusPrintStartup(void);`
- `I_CDMusPlay` (function) `progs/doomgeneric/i_cdmus.h:33` `int I_CDMusPlay(int track);`
- `I_CDMusStop` (function) `progs/doomgeneric/i_cdmus.h:34` `int I_CDMusStop(void);`
- `I_CDMusResume` (function) `progs/doomgeneric/i_cdmus.h:35` `int I_CDMusResume(void);`
- `I_CDMusSetVolume` (function) `progs/doomgeneric/i_cdmus.h:36` `int I_CDMusSetVolume(int volume);`
- `I_CDMusFirstTrack` (function) `progs/doomgeneric/i_cdmus.h:37` `int I_CDMusFirstTrack(void);`
- `I_CDMusLastTrack` (function) `progs/doomgeneric/i_cdmus.h:38` `int I_CDMusLastTrack(void);`
- `I_CDMusTrackLength` (function) `progs/doomgeneric/i_cdmus.h:39` `int I_CDMusTrackLength(int track);`

## progs/doomgeneric/i_endoom.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`
- `I_Endoom` (function) `progs/doomgeneric/i_endoom.c:36` `void I_Endoom(byte *endoom_data)`

## progs/doomgeneric/i_endoom.h
Imported by: `progs/doomgeneric/d_main.c`
- `I_Endoom` (function) `progs/doomgeneric/i_endoom.h:26` `void I_Endoom(byte *data);`

## progs/doomgeneric/i_input.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `TranslateKey` (function) `progs/doomgeneric/i_input.c:225` `static unsigned char TranslateKey(unsigned char key)`
- `GetTypedChar` (function) `progs/doomgeneric/i_input.c:242` `static unsigned char GetTypedChar(unsigned char key)`
- `UpdateShiftStatus` (function) `progs/doomgeneric/i_input.c:263` `static void UpdateShiftStatus(int pressed, unsigned char key)`
- `I_GetEvent` (function) `progs/doomgeneric/i_input.c:279` `void I_GetEvent(void)`
- `I_InitInput` (function) `progs/doomgeneric/i_input.c:338` `void I_InitInput(void)`

## progs/doomgeneric/i_joystick.c
Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/pokemon/minios_stubs/SDL.h`
- `I_ShutdownJoystick` (function) `progs/doomgeneric/i_joystick.c:77` `void I_ShutdownJoystick(void)`
- `IsValidAxis` (function) `progs/doomgeneric/i_joystick.c:90` `static boolean IsValidAxis(int axis)` -- ifdef ORIGCODE
- `I_InitJoystick` (function) `progs/doomgeneric/i_joystick.c:115` `void I_InitJoystick(void)`
- `IsAxisButton` (function) `progs/doomgeneric/i_joystick.c:171` `static boolean IsAxisButton(int physbutton)` -- ifdef ORIGCODE
- `ReadButtonState` (function) `progs/doomgeneric/i_joystick.c:203` `static int ReadButtonState(int vbutton)`
- `GetButtonsState` (function) `progs/doomgeneric/i_joystick.c:228` `static int GetButtonsState(void)`
- `GetAxisState` (function) `progs/doomgeneric/i_joystick.c:248` `static int GetAxisState(int axis, int invert)`
- `I_UpdateJoystick` (function) `progs/doomgeneric/i_joystick.c:321` `void I_UpdateJoystick(void)` -- endif
- `I_BindJoystickVariables` (function) `progs/doomgeneric/i_joystick.c:339` `void I_BindJoystickVariables(void)`

## progs/doomgeneric/i_joystick.h
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`
- `I_InitJoystick` (function) `progs/doomgeneric/i_joystick.h:63` `void I_InitJoystick(void);`
- `I_ShutdownJoystick` (function) `progs/doomgeneric/i_joystick.h:64` `void I_ShutdownJoystick(void);`
- `I_UpdateJoystick` (function) `progs/doomgeneric/i_joystick.h:65` `void I_UpdateJoystick(void);`
- `I_BindJoystickVariables` (function) `progs/doomgeneric/i_joystick.h:67` `void I_BindJoystickVariables(void);`

## progs/doomgeneric/i_main.c
Depends on: `progs/doomgeneric/m_argv.h`
- `D_DoomMain` (function) `progs/doomgeneric/i_main.c:33` `void D_DoomMain (void);`
- `M_FindResponseFile` (function) `progs/doomgeneric/i_main.c:35` `void M_FindResponseFile(void);`
- `dg_Create` (function) `progs/doomgeneric/i_main.c:37` `void dg_Create();`
- `main` (function) `progs/doomgeneric/i_main.c:40` `int main(int argc, char **argv)`

## progs/doomgeneric/i_minios_sound.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/minios_abi.h`
- `sys_tone_hw` (function) `progs/doomgeneric/i_minios_sound.c:32` `static long sys_tone_hw(unsigned f)`
- `sys_time` (function) `progs/doomgeneric/i_minios_sound.c:35` `static long sys_time(void)`
- `sys_pcm2_open` (function) `progs/doomgeneric/i_minios_sound.c:38` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/doomgeneric/i_minios_sound.c:41` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/doomgeneric/i_minios_sound.c:44` `static void sys_pcm2_close(void)`
- `muted` (function) `progs/doomgeneric/i_minios_sound.c:51` `* pcm2 while sfx stay muted (effect tones ruined the melody);`
- `audio_ensure` (function) `progs/doomgeneric/i_minios_sound.c:68` `static void audio_ensure(void)`
- `audio_pump` (function) `progs/doomgeneric/i_minios_sound.c:77` `static void audio_pump(void)` -- SFX are muted on pcm2 (music only): effect tones ruined the melody, so audio_pump below only advances the shared...
- `audio_tone` (function) `progs/doomgeneric/i_minios_sound.c:85` `static void audio_tone(unsigned freq)`
- `audio_close` (function) `progs/doomgeneric/i_minios_sound.c:92` `static void audio_close(void)`
- `mus_read_varlen` (function) `progs/doomgeneric/i_minios_sound.c:169` `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
- `mus_next_block` (function) `progs/doomgeneric/i_minios_sound.c:183` `static int mus_next_block(mus_player_t *m, unsigned long *out)` -- Process one full block of events at the current tick and advance pos past * its delta.
- `mus_note_cmp` (function) `progs/doomgeneric/i_minios_sound.c:228` `static int mus_note_cmp(const void *a, const void *b)`
- `mus_build_chord` (function) `progs/doomgeneric/i_minios_sound.c:236` `static void mus_build_chord(mus_player_t *m)` -- Split the sounding notes into a bass pedal (the lowest note below the bass line) and the melody arpeggio (the...
- `mus_hold_tone` (function) `progs/doomgeneric/i_minios_sound.c:261` `static void mus_hold_tone(unsigned freq, unsigned long ms)` -- Hold a tone for the given number of milliseconds.
- `mus_play_chord` (function) `progs/doomgeneric/i_minios_sound.c:274` `static void mus_play_chord(mus_player_t *m)` -- Play one full cycle of the pseudo-polyphony: the bass pedal first, held long like the NES triangle voice, then the...
- `mus_advance` (function) `progs/doomgeneric/i_minios_sound.c:288` `static void mus_advance(mus_player_t *m, unsigned long ms)`
- `mus_render_pcm` (function) `progs/doomgeneric/i_minios_sound.c:320` `static void mus_render_pcm(mus_player_t *m, unsigned char *out, unsigned n)` -- Polyphonic pcm2 music: every sounding voice at once, as the score has it.
- `mus_render_push` (function) `progs/doomgeneric/i_minios_sound.c:359` `static void mus_render_push(mus_player_t *m, unsigned n)`
- `mus_advance_pcm` (function) `progs/doomgeneric/i_minios_sound.c:369` `static void mus_advance_pcm(mus_player_t *m)`
- `MUS_Init` (function) `progs/doomgeneric/i_minios_sound.c:410` `static boolean MUS_Init(void)`
- `MUS_Shutdown` (function) `progs/doomgeneric/i_minios_sound.c:415` `static void MUS_Shutdown(void)`
- `MUS_SetMusicVolume` (function) `progs/doomgeneric/i_minios_sound.c:422` `static void MUS_SetMusicVolume(int volume)`
- `MUS_Pause` (function) `progs/doomgeneric/i_minios_sound.c:424` `static void MUS_Pause(void)`
- `MUS_Resume` (function) `progs/doomgeneric/i_minios_sound.c:425` `static void MUS_Resume(void)`
- `MUS_RegisterSong` (function) `progs/doomgeneric/i_minios_sound.c:427` `static void *MUS_RegisterSong(void *data, int len)`
- `MUS_UnRegisterSong` (function) `progs/doomgeneric/i_minios_sound.c:442` `static void MUS_UnRegisterSong(void *handle)`
- `MUS_PlaySong` (function) `progs/doomgeneric/i_minios_sound.c:448` `static void MUS_PlaySong(void *handle, boolean looping)`
- `MUS_StopSong` (function) `progs/doomgeneric/i_minios_sound.c:469` `static void MUS_StopSong(void)`
- `MUS_MusicIsPlaying` (function) `progs/doomgeneric/i_minios_sound.c:474` `static boolean MUS_MusicIsPlaying(void)`
- `MUS_Poll` (function) `progs/doomgeneric/i_minios_sound.c:478` `static void MUS_Poll(void)`
- `PCSPK_Init` (function) `progs/doomgeneric/i_minios_sound.c:512` `static boolean PCSPK_Init(boolean use_sfx_prefix)`
- `PCSPK_Shutdown` (function) `progs/doomgeneric/i_minios_sound.c:519` `static void PCSPK_Shutdown(void)`
- `PCSPK_GetSfxLumpNum` (function) `progs/doomgeneric/i_minios_sound.c:529` `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
- `free_channel` (function) `progs/doomgeneric/i_minios_sound.c:540` `static void free_channel(int i)`
- `PCSPK_Update` (function) `progs/doomgeneric/i_minios_sound.c:549` `static void PCSPK_Update(void)`
- `PCSPK_UpdateSoundParams` (function) `progs/doomgeneric/i_minios_sound.c:587` `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
- `PCSPK_StartSound` (function) `progs/doomgeneric/i_minios_sound.c:591` `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
- `PCSPK_StopSound` (function) `progs/doomgeneric/i_minios_sound.c:641` `static void PCSPK_StopSound(int channel)`
- `PCSPK_SoundIsPlaying` (function) `progs/doomgeneric/i_minios_sound.c:647` `static boolean PCSPK_SoundIsPlaying(int channel)`
- `PCSPK_CacheSounds` (function) `progs/doomgeneric/i_minios_sound.c:653` `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`

## progs/doomgeneric/i_scale.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/z_zone.h`
- `I_InitScale` (function) `progs/doomgeneric/i_scale.c:61` `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
- `I_Scale1x` (function) `progs/doomgeneric/i_scale.c:75` `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
- `I_Scale2x` (function) `progs/doomgeneric/i_scale.c:105` `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
- `I_Scale3x` (function) `progs/doomgeneric/i_scale.c:146` `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
- `I_Scale4x` (function) `progs/doomgeneric/i_scale.c:191` `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
- `I_Scale5x` (function) `progs/doomgeneric/i_scale.c:240` `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
- `FindNearestColor` (function) `progs/doomgeneric/i_scale.c:295` `static int FindNearestColor(byte *palette, int r, int g, int b)`
- `GenerateStretchTable` (function) `progs/doomgeneric/i_scale.c:332` `static byte *GenerateStretchTable(byte *palette, int pct)`
- `I_InitStretchTables` (function) `progs/doomgeneric/i_scale.c:361` `static void I_InitStretchTables(byte *palette)`
- `I_InitSquashTable` (function) `progs/doomgeneric/i_scale.c:387` `static void I_InitSquashTable(byte *palette)`
- `I_ResetScaleTables` (function) `progs/doomgeneric/i_scale.c:404` `void I_ResetScaleTables(byte *palette)`
- `WriteBlendedLine1x` (function) `progs/doomgeneric/i_scale.c:434` `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch1x` (function) `progs/doomgeneric/i_scale.c:450` `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
- `WriteLine2x` (function) `progs/doomgeneric/i_scale.c:507` `static inline void WriteLine2x(byte *dest, byte *src)`
- `WriteBlendedLine2x` (function) `progs/doomgeneric/i_scale.c:520` `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch2x` (function) `progs/doomgeneric/i_scale.c:539` `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
- `WriteLine3x` (function) `progs/doomgeneric/i_scale.c:620` `static inline void WriteLine3x(byte *dest, byte *src)`
- `WriteBlendedLine3x` (function) `progs/doomgeneric/i_scale.c:634` `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch3x` (function) `progs/doomgeneric/i_scale.c:654` `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
- `WriteLine4x` (function) `progs/doomgeneric/i_scale.c:759` `static inline void WriteLine4x(byte *dest, byte *src)`
- `WriteBlendedLine4x` (function) `progs/doomgeneric/i_scale.c:774` `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
- `I_Stretch4x` (function) `progs/doomgeneric/i_scale.c:795` `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
- `WriteLine5x` (function) `progs/doomgeneric/i_scale.c:924` `static inline void WriteLine5x(byte *dest, byte *src)`
- `I_Stretch5x` (function) `progs/doomgeneric/i_scale.c:942` `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine1x` (function) `progs/doomgeneric/i_scale.c:1030` `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
- `I_Squash1x` (function) `progs/doomgeneric/i_scale.c:1061` `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine2x` (function) `progs/doomgeneric/i_scale.c:1102` `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
- `I_Squash2x` (function) `progs/doomgeneric/i_scale.c:1160` `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine3x` (function) `progs/doomgeneric/i_scale.c:1197` `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
- `I_Squash3x` (function) `progs/doomgeneric/i_scale.c:1243` `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine4x` (function) `progs/doomgeneric/i_scale.c:1279` `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
- `I_Squash4x` (function) `progs/doomgeneric/i_scale.c:1354` `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
- `WriteSquashedLine5x` (function) `progs/doomgeneric/i_scale.c:1390` `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
- `I_Squash5x` (function) `progs/doomgeneric/i_scale.c:1419` `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`

## progs/doomgeneric/i_scale.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/i_input.c`
- `I_InitScale` (function) `progs/doomgeneric/i_scale.h:25` `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);`
- `I_ResetScaleTables` (function) `progs/doomgeneric/i_scale.h:26` `void I_ResetScaleTables(byte *palette);`

## progs/doomgeneric/i_sound.c
Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`
- `I_InitTimidityConfig` (function) `progs/doomgeneric/i_sound.c:65` `extern void I_InitTimidityConfig(void);`
- `SndDeviceInList` (function) `progs/doomgeneric/i_sound.c:116` `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
- `InitSfxModule` (function) `progs/doomgeneric/i_sound.c:135` `static void InitSfxModule(boolean use_sfx_prefix)`
- `InitMusicModule` (function) `progs/doomgeneric/i_sound.c:163` `static void InitMusicModule(void)`
- `I_InitSound` (function) `progs/doomgeneric/i_sound.c:195` `void I_InitSound(boolean use_sfx_prefix)`
- `I_ShutdownSound` (function) `progs/doomgeneric/i_sound.c:250` `void I_ShutdownSound(void)`
- `I_GetSfxLumpNum` (function) `progs/doomgeneric/i_sound.c:263` `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
- `I_UpdateSound` (function) `progs/doomgeneric/i_sound.c:275` `void I_UpdateSound(void)`
- `CheckVolumeSeparation` (function) `progs/doomgeneric/i_sound.c:288` `static void CheckVolumeSeparation(int *vol, int *sep)`
- `I_UpdateSoundParams` (function) `progs/doomgeneric/i_sound.c:309` `void I_UpdateSoundParams(int channel, int vol, int sep)`
- `I_StartSound` (function) `progs/doomgeneric/i_sound.c:318` `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
- `I_StopSound` (function) `progs/doomgeneric/i_sound.c:331` `void I_StopSound(int channel)`
- `I_SoundIsPlaying` (function) `progs/doomgeneric/i_sound.c:339` `boolean I_SoundIsPlaying(int channel)`
- `I_PrecacheSounds` (function) `progs/doomgeneric/i_sound.c:351` `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
- `I_InitMusic` (function) `progs/doomgeneric/i_sound.c:359` `void I_InitMusic(void)`
- `I_ShutdownMusic` (function) `progs/doomgeneric/i_sound.c:363` `void I_ShutdownMusic(void)`
- `I_SetMusicVolume` (function) `progs/doomgeneric/i_sound.c:368` `void I_SetMusicVolume(int volume)`
- `I_PauseSong` (function) `progs/doomgeneric/i_sound.c:376` `void I_PauseSong(void)`
- `I_ResumeSong` (function) `progs/doomgeneric/i_sound.c:384` `void I_ResumeSong(void)`
- `I_RegisterSong` (function) `progs/doomgeneric/i_sound.c:392` `void *I_RegisterSong(void *data, int len)`
- `I_UnRegisterSong` (function) `progs/doomgeneric/i_sound.c:404` `void I_UnRegisterSong(void *handle)`
- `I_PlaySong` (function) `progs/doomgeneric/i_sound.c:412` `void I_PlaySong(void *handle, boolean looping)`
- `I_StopSong` (function) `progs/doomgeneric/i_sound.c:420` `void I_StopSong(void)`
- `I_MusicIsPlaying` (function) `progs/doomgeneric/i_sound.c:428` `boolean I_MusicIsPlaying(void)`
- `I_BindSoundVariables` (function) `progs/doomgeneric/i_sound.c:440` `void I_BindSoundVariables(void)`

## progs/doomgeneric/i_sound.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sounds.h`
- `I_InitSound` (function) `progs/doomgeneric/i_sound.h:152` `void I_InitSound(boolean use_sfx_prefix);`
- `I_ShutdownSound` (function) `progs/doomgeneric/i_sound.h:153` `void I_ShutdownSound(void);`
- `I_GetSfxLumpNum` (function) `progs/doomgeneric/i_sound.h:154` `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);`
- `I_UpdateSound` (function) `progs/doomgeneric/i_sound.h:155` `void I_UpdateSound(void);`
- `I_UpdateSoundParams` (function) `progs/doomgeneric/i_sound.h:156` `void I_UpdateSoundParams(int channel, int vol, int sep);`
- `I_StartSound` (function) `progs/doomgeneric/i_sound.h:157` `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);`
- `I_StopSound` (function) `progs/doomgeneric/i_sound.h:158` `void I_StopSound(int channel);`
- `I_PrecacheSounds` (function) `progs/doomgeneric/i_sound.h:160` `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);`
- `I_InitMusic` (function) `progs/doomgeneric/i_sound.h:217` `void I_InitMusic(void);`
- `I_ShutdownMusic` (function) `progs/doomgeneric/i_sound.h:218` `void I_ShutdownMusic(void);`
- `I_SetMusicVolume` (function) `progs/doomgeneric/i_sound.h:219` `void I_SetMusicVolume(int volume);`
- `I_PauseSong` (function) `progs/doomgeneric/i_sound.h:220` `void I_PauseSong(void);`
- `I_ResumeSong` (function) `progs/doomgeneric/i_sound.h:221` `void I_ResumeSong(void);`
- `I_RegisterSong` (function) `progs/doomgeneric/i_sound.h:222` `void *I_RegisterSong(void *data, int len);`
- `I_UnRegisterSong` (function) `progs/doomgeneric/i_sound.h:223` `void I_UnRegisterSong(void *handle);`
- `I_PlaySong` (function) `progs/doomgeneric/i_sound.h:224` `void I_PlaySong(void *handle, boolean looping);`
- `I_StopSong` (function) `progs/doomgeneric/i_sound.h:225` `void I_StopSong(void);`
- `I_BindSoundVariables` (function) `progs/doomgeneric/i_sound.h:235` `void I_BindSoundVariables(void);`

## progs/doomgeneric/i_system.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/pokemon/minios_stubs/SDL.h`
- `I_AtExit` (function) `progs/doomgeneric/i_system.c:73` `void I_AtExit(atexit_func_t func, boolean run_on_error)`
- `I_Tactile` (function) `progs/doomgeneric/i_system.c:87` `void I_Tactile(int on, int off, int total)`
- `AutoAllocMemory` (function) `progs/doomgeneric/i_system.c:95` `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)`
- `I_ZoneBase` (function) `progs/doomgeneric/i_system.c:133` `byte *I_ZoneBase (int *size)`
- `I_PrintBanner` (function) `progs/doomgeneric/i_system.c:166` `void I_PrintBanner(char *msg)`
- `I_PrintDivider` (function) `progs/doomgeneric/i_system.c:177` `void I_PrintDivider(void)`
- `I_PrintStartupBanner` (function) `progs/doomgeneric/i_system.c:189` `void I_PrintStartupBanner(char *gamedescription)`
- `I_ConsoleStdout` (function) `progs/doomgeneric/i_system.c:210` `boolean I_ConsoleStdout(void)`
- `I_Quit` (function) `progs/doomgeneric/i_system.c:246` `void I_Quit (void)`
- `ZenityAvailable` (function) `progs/doomgeneric/i_system.c:272` `static int ZenityAvailable(void)`
- `EscapeShellString` (function) `progs/doomgeneric/i_system.c:280` `static char *EscapeShellString(char *string)`
- `ZenityErrorBox` (function) `progs/doomgeneric/i_system.c:323` `static int ZenityErrorBox(char *message)`
- `I_Error` (function) `progs/doomgeneric/i_system.c:359` `void I_Error (char *error, ...)`
- `I_GetMemoryValue` (function) `progs/doomgeneric/i_system.c:502` `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)`

## progs/doomgeneric/i_system.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_sight.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`
- `I_Init` (function) `progs/doomgeneric/i_system.h:30` `void I_Init (void);` -- Called by DoomMain.
- `I_ZoneBase` (function) `progs/doomgeneric/i_system.h:35` `byte* I_ZoneBase (int *size);` -- Called by startup code to get the ammount of memory to malloc for the zone management.
- `I_BaseTiccmd` (function) `progs/doomgeneric/i_system.h:48` `ticcmd_t* I_BaseTiccmd (void);` -- Either returns a null ticcmd, or calls a loadable driver to build it.
- `I_Quit` (function) `progs/doomgeneric/i_system.h:53` `void I_Quit (void);` -- Called by M_Responder when quit is selected.
- `I_Error` (function) `progs/doomgeneric/i_system.h:55` `void I_Error (char *error, ...);`
- `I_Tactile` (function) `progs/doomgeneric/i_system.h:57` `void I_Tactile (int on, int off, int total);`
- `I_AtExit` (function) `progs/doomgeneric/i_system.h:65` `void I_AtExit(atexit_func_t func, boolean run_if_error);`
- `I_BindVariables` (function) `progs/doomgeneric/i_system.h:69` `void I_BindVariables(void);`
- `I_PrintStartupBanner` (function) `progs/doomgeneric/i_system.h:73` `void I_PrintStartupBanner(char *gamedescription);`
- `I_PrintBanner` (function) `progs/doomgeneric/i_system.h:77` `void I_PrintBanner(char *text);`
- `I_PrintDivider` (function) `progs/doomgeneric/i_system.h:81` `void I_PrintDivider(void);`

## progs/doomgeneric/i_timer.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_timer.h`
- `I_GetTicks` (function) `progs/doomgeneric/i_timer.c:37` `int I_GetTicks(void)`
- `I_GetTime` (function) `progs/doomgeneric/i_timer.c:42` `int  I_GetTime (void)`
- `I_GetTimeMS` (function) `progs/doomgeneric/i_timer.c:61` `int I_GetTimeMS(void)`
- `I_Sleep` (function) `progs/doomgeneric/i_timer.c:75` `void I_Sleep(int ms)`
- `I_WaitVBL` (function) `progs/doomgeneric/i_timer.c:83` `void I_WaitVBL(int count)`
- `I_InitTimer` (function) `progs/doomgeneric/i_timer.c:89` `void I_InitTimer(void)`

## progs/doomgeneric/i_timer.h
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/m_menu.c`
- `I_GetTime` (function) `progs/doomgeneric/i_timer.h:27` `int I_GetTime (void);` -- Called by D_DoomLoop, returns current time in tics.
- `I_GetTimeMS` (function) `progs/doomgeneric/i_timer.h:30` `int I_GetTimeMS (void);` -- returns current time in ms
- `I_Sleep` (function) `progs/doomgeneric/i_timer.h:33` `void I_Sleep(int ms);` -- Pause for a specified number of ms
- `I_InitTimer` (function) `progs/doomgeneric/i_timer.h:36` `void I_InitTimer(void);` -- Initialize timer
- `I_WaitVBL` (function) `progs/doomgeneric/i_timer.h:39` `void I_WaitVBL(int count);` -- Wait for vertical retrace or pause a bit.

## progs/doomgeneric/i_video.c
Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`
- `I_GetEvent` (function) `progs/doomgeneric/i_video.c:89` `void I_GetEvent(void);`
- `cmap_to_rgb565` (function) `progs/doomgeneric/i_video.c:131` `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)`
- `cmap_to_fb` (function) `progs/doomgeneric/i_video.c:152` `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)`
- `I_InitGraphics` (function) `progs/doomgeneric/i_video.c:179` `void I_InitGraphics (void)`
- `I_InitInput` (function) `progs/doomgeneric/i_video.c:228` `extern int I_InitInput(void);`
- `I_ShutdownGraphics` (function) `progs/doomgeneric/i_video.c:232` `void I_ShutdownGraphics (void)`
- `I_StartFrame` (function) `progs/doomgeneric/i_video.c:237` `void I_StartFrame (void)`
- `I_StartTic` (function) `progs/doomgeneric/i_video.c:242` `void I_StartTic (void)`
- `I_UpdateNoBlit` (function) `progs/doomgeneric/i_video.c:247` `void I_UpdateNoBlit (void)`
- `I_FinishUpdate` (function) `progs/doomgeneric/i_video.c:255` `void I_FinishUpdate (void)`
- `I_ReadScreen` (function) `progs/doomgeneric/i_video.c:302` `void I_ReadScreen (byte* scr)` -- I_ReadScreen
- `I_SetPalette` (function) `progs/doomgeneric/i_video.c:315` `void I_SetPalette (byte* palette)`
- `I_GetPaletteIndex` (function) `progs/doomgeneric/i_video.c:333` `int I_GetPaletteIndex (int r, int g, int b)`
- `I_BeginRead` (function) `progs/doomgeneric/i_video.c:369` `void I_BeginRead (void)`
- `I_EndRead` (function) `progs/doomgeneric/i_video.c:373` `void I_EndRead (void)`
- `I_SetWindowTitle` (function) `progs/doomgeneric/i_video.c:377` `void I_SetWindowTitle (char *title)`
- `I_GraphicsCheckCommandLine` (function) `progs/doomgeneric/i_video.c:382` `void I_GraphicsCheckCommandLine (void)`
- `I_SetGrabMouseCallback` (function) `progs/doomgeneric/i_video.c:386` `void I_SetGrabMouseCallback (grabmouse_callback_t func)`
- `I_EnableLoadingDisk` (function) `progs/doomgeneric/i_video.c:390` `void I_EnableLoadingDisk(void)`
- `I_BindVideoVariables` (function) `progs/doomgeneric/i_video.c:394` `void I_BindVideoVariables (void)`
- `I_DisplayFPSDots` (function) `progs/doomgeneric/i_video.c:398` `void I_DisplayFPSDots (boolean dots_on)`
- `I_CheckIsScreensaver` (function) `progs/doomgeneric/i_video.c:402` `void I_CheckIsScreensaver (void)`

## progs/doomgeneric/i_video.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_wad.c`
- `I_InitGraphics` (function) `progs/doomgeneric/i_video.h:97` `void I_InitGraphics (void);` -- Called by D_DoomMain, determines the hardware configuration and sets up the video mode
- `I_GraphicsCheckCommandLine` (function) `progs/doomgeneric/i_video.h:99` `void I_GraphicsCheckCommandLine(void);`
- `I_ShutdownGraphics` (function) `progs/doomgeneric/i_video.h:101` `void I_ShutdownGraphics(void);`
- `I_SetPalette` (function) `progs/doomgeneric/i_video.h:104` `void I_SetPalette (byte* palette);` -- Takes full 8 bit values.
- `I_GetPaletteIndex` (function) `progs/doomgeneric/i_video.h:105` `int I_GetPaletteIndex(int r, int g, int b);`
- `I_UpdateNoBlit` (function) `progs/doomgeneric/i_video.h:107` `void I_UpdateNoBlit (void);`
- `I_FinishUpdate` (function) `progs/doomgeneric/i_video.h:108` `void I_FinishUpdate (void);`
- `I_ReadScreen` (function) `progs/doomgeneric/i_video.h:110` `void I_ReadScreen (byte* scr);`
- `I_BeginRead` (function) `progs/doomgeneric/i_video.h:112` `void I_BeginRead (void);`
- `I_SetWindowTitle` (function) `progs/doomgeneric/i_video.h:114` `void I_SetWindowTitle(char *title);`
- `I_CheckIsScreensaver` (function) `progs/doomgeneric/i_video.h:116` `void I_CheckIsScreensaver(void);`
- `I_SetGrabMouseCallback` (function) `progs/doomgeneric/i_video.h:117` `void I_SetGrabMouseCallback(grabmouse_callback_t func);`
- `I_DisplayFPSDots` (function) `progs/doomgeneric/i_video.h:119` `void I_DisplayFPSDots(boolean dots_on);`
- `I_BindVideoVariables` (function) `progs/doomgeneric/i_video.h:120` `void I_BindVideoVariables(void);`
- `I_InitWindowTitle` (function) `progs/doomgeneric/i_video.h:122` `void I_InitWindowTitle(void);`
- `I_InitWindowIcon` (function) `progs/doomgeneric/i_video.h:123` `void I_InitWindowIcon(void);`
- `I_StartFrame` (function) `progs/doomgeneric/i_video.h:128` `void I_StartFrame (void);`
- `I_StartTic` (function) `progs/doomgeneric/i_video.h:133` `void I_StartTic (void);`
- `I_EnableLoadingDisk` (function) `progs/doomgeneric/i_video.h:137` `void I_EnableLoadingDisk(void);`

## progs/doomgeneric/info.c
Depends on: `progs/doomgeneric/info.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/sounds.h`
- `A_Light0` (function) `progs/doomgeneric/info.c:51` `void A_Light0();` -- Doesn't work with g++, needs actionf_p1
- `A_WeaponReady` (function) `progs/doomgeneric/info.c:52` `void A_WeaponReady();`
- `A_Lower` (function) `progs/doomgeneric/info.c:53` `void A_Lower();`
- `A_Raise` (function) `progs/doomgeneric/info.c:54` `void A_Raise();`
- `A_Punch` (function) `progs/doomgeneric/info.c:55` `void A_Punch();`
- `A_ReFire` (function) `progs/doomgeneric/info.c:56` `void A_ReFire();`
- `A_FirePistol` (function) `progs/doomgeneric/info.c:57` `void A_FirePistol();`
- `A_Light1` (function) `progs/doomgeneric/info.c:58` `void A_Light1();`
- `A_FireShotgun` (function) `progs/doomgeneric/info.c:59` `void A_FireShotgun();`
- `A_Light2` (function) `progs/doomgeneric/info.c:60` `void A_Light2();`
- `A_FireShotgun2` (function) `progs/doomgeneric/info.c:61` `void A_FireShotgun2();`
- `A_CheckReload` (function) `progs/doomgeneric/info.c:62` `void A_CheckReload();`
- `A_OpenShotgun2` (function) `progs/doomgeneric/info.c:63` `void A_OpenShotgun2();`
- `A_LoadShotgun2` (function) `progs/doomgeneric/info.c:64` `void A_LoadShotgun2();`
- `A_CloseShotgun2` (function) `progs/doomgeneric/info.c:65` `void A_CloseShotgun2();`
- `A_FireCGun` (function) `progs/doomgeneric/info.c:66` `void A_FireCGun();`
- `A_GunFlash` (function) `progs/doomgeneric/info.c:67` `void A_GunFlash();`
- `A_FireMissile` (function) `progs/doomgeneric/info.c:68` `void A_FireMissile();`
- `A_Saw` (function) `progs/doomgeneric/info.c:69` `void A_Saw();`
- `A_FirePlasma` (function) `progs/doomgeneric/info.c:70` `void A_FirePlasma();`
- `A_BFGsound` (function) `progs/doomgeneric/info.c:71` `void A_BFGsound();`
- `A_FireBFG` (function) `progs/doomgeneric/info.c:72` `void A_FireBFG();`
- `A_BFGSpray` (function) `progs/doomgeneric/info.c:73` `void A_BFGSpray();`
- `A_Explode` (function) `progs/doomgeneric/info.c:74` `void A_Explode();`
- `A_Pain` (function) `progs/doomgeneric/info.c:75` `void A_Pain();`
- `A_PlayerScream` (function) `progs/doomgeneric/info.c:76` `void A_PlayerScream();`
- `A_Fall` (function) `progs/doomgeneric/info.c:77` `void A_Fall();`
- `A_XScream` (function) `progs/doomgeneric/info.c:78` `void A_XScream();`
- `A_Look` (function) `progs/doomgeneric/info.c:79` `void A_Look();`
- `A_Chase` (function) `progs/doomgeneric/info.c:80` `void A_Chase();`
- `A_FaceTarget` (function) `progs/doomgeneric/info.c:81` `void A_FaceTarget();`
- `A_PosAttack` (function) `progs/doomgeneric/info.c:82` `void A_PosAttack();`
- `A_Scream` (function) `progs/doomgeneric/info.c:83` `void A_Scream();`
- `A_SPosAttack` (function) `progs/doomgeneric/info.c:84` `void A_SPosAttack();`
- `A_VileChase` (function) `progs/doomgeneric/info.c:85` `void A_VileChase();`
- `A_VileStart` (function) `progs/doomgeneric/info.c:86` `void A_VileStart();`
- `A_VileTarget` (function) `progs/doomgeneric/info.c:87` `void A_VileTarget();`
- `A_VileAttack` (function) `progs/doomgeneric/info.c:88` `void A_VileAttack();`
- `A_StartFire` (function) `progs/doomgeneric/info.c:89` `void A_StartFire();`
- `A_Fire` (function) `progs/doomgeneric/info.c:90` `void A_Fire();`
- `A_FireCrackle` (function) `progs/doomgeneric/info.c:91` `void A_FireCrackle();`
- `A_Tracer` (function) `progs/doomgeneric/info.c:92` `void A_Tracer();`
- `A_SkelWhoosh` (function) `progs/doomgeneric/info.c:93` `void A_SkelWhoosh();`
- `A_SkelFist` (function) `progs/doomgeneric/info.c:94` `void A_SkelFist();`
- `A_SkelMissile` (function) `progs/doomgeneric/info.c:95` `void A_SkelMissile();`
- `A_FatRaise` (function) `progs/doomgeneric/info.c:96` `void A_FatRaise();`
- `A_FatAttack1` (function) `progs/doomgeneric/info.c:97` `void A_FatAttack1();`
- `A_FatAttack2` (function) `progs/doomgeneric/info.c:98` `void A_FatAttack2();`
- `A_FatAttack3` (function) `progs/doomgeneric/info.c:99` `void A_FatAttack3();`
- `A_BossDeath` (function) `progs/doomgeneric/info.c:100` `void A_BossDeath();`
- `A_CPosAttack` (function) `progs/doomgeneric/info.c:101` `void A_CPosAttack();`
- `A_CPosRefire` (function) `progs/doomgeneric/info.c:102` `void A_CPosRefire();`
- `A_TroopAttack` (function) `progs/doomgeneric/info.c:103` `void A_TroopAttack();`
- `A_SargAttack` (function) `progs/doomgeneric/info.c:104` `void A_SargAttack();`
- `A_HeadAttack` (function) `progs/doomgeneric/info.c:105` `void A_HeadAttack();`
- `A_BruisAttack` (function) `progs/doomgeneric/info.c:106` `void A_BruisAttack();`
- `A_SkullAttack` (function) `progs/doomgeneric/info.c:107` `void A_SkullAttack();`
- `A_Metal` (function) `progs/doomgeneric/info.c:108` `void A_Metal();`
- `A_SpidRefire` (function) `progs/doomgeneric/info.c:109` `void A_SpidRefire();`
- `A_BabyMetal` (function) `progs/doomgeneric/info.c:110` `void A_BabyMetal();`
- `A_BspiAttack` (function) `progs/doomgeneric/info.c:111` `void A_BspiAttack();`
- `A_Hoof` (function) `progs/doomgeneric/info.c:112` `void A_Hoof();`
- `A_CyberAttack` (function) `progs/doomgeneric/info.c:113` `void A_CyberAttack();`
- `A_PainAttack` (function) `progs/doomgeneric/info.c:114` `void A_PainAttack();`
- `A_PainDie` (function) `progs/doomgeneric/info.c:115` `void A_PainDie();`
- `A_KeenDie` (function) `progs/doomgeneric/info.c:116` `void A_KeenDie();`
- `A_BrainPain` (function) `progs/doomgeneric/info.c:117` `void A_BrainPain();`
- `A_BrainScream` (function) `progs/doomgeneric/info.c:118` `void A_BrainScream();`
- `A_BrainDie` (function) `progs/doomgeneric/info.c:119` `void A_BrainDie();`
- `A_BrainAwake` (function) `progs/doomgeneric/info.c:120` `void A_BrainAwake();`
- `A_BrainSpit` (function) `progs/doomgeneric/info.c:121` `void A_BrainSpit();`
- `A_SpawnSound` (function) `progs/doomgeneric/info.c:122` `void A_SpawnSound();`
- `A_SpawnFly` (function) `progs/doomgeneric/info.c:123` `void A_SpawnFly();`
- `A_BrainExplode` (function) `progs/doomgeneric/info.c:124` `void A_BrainExplode();`

## progs/doomgeneric/m_argv.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`
- `M_CheckParmWithArgs` (function) `progs/doomgeneric/m_argv.c:43` `int M_CheckParmWithArgs(char *check, int num_args)`
- `M_ParmExists` (function) `progs/doomgeneric/m_argv.c:63` `boolean M_ParmExists(char *check)`
- `M_CheckParm` (function) `progs/doomgeneric/m_argv.c:68` `int M_CheckParm(char *check)`
- `LoadResponseFile` (function) `progs/doomgeneric/m_argv.c:75` `static void LoadResponseFile(int argv_index)`
- `M_FindResponseFile` (function) `progs/doomgeneric/m_argv.c:235` `void M_FindResponseFile(void)`
- `M_GetExecutableName` (function) `progs/doomgeneric/m_argv.c:250` `char *M_GetExecutableName(void)`

## progs/doomgeneric/m_argv.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_main.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_main.c`
- `M_CheckParm` (function) `progs/doomgeneric/m_argv.h:33` `int M_CheckParm (char* check);` -- Returns the position of the given parameter in the arg list (0 if not found).
- `M_CheckParmWithArgs` (function) `progs/doomgeneric/m_argv.h:37` `int M_CheckParmWithArgs(char *check, int num_args);` -- Same as M_CheckParm, but checks that num_args arguments are available following the specified argument.
- `M_FindResponseFile` (function) `progs/doomgeneric/m_argv.h:39` `void M_FindResponseFile(void);`
- `M_GetExecutableName` (function) `progs/doomgeneric/m_argv.h:47` `char *M_GetExecutableName(void);`

## progs/doomgeneric/m_bbox.c
Depends on: `progs/doomgeneric/m_bbox.h`
- `M_ClearBox` (function) `progs/doomgeneric/m_bbox.c:29` `void M_ClearBox (fixed_t *box)`
- `M_AddToBox` (function) `progs/doomgeneric/m_bbox.c:36` `void
M_AddToBox
( fixed_t*	box,
  fixed_t	x,
  fixed_t	y )`

## progs/doomgeneric/m_bbox.h
Depends on: `progs/doomgeneric/m_fixed.h`
Imported by: `progs/doomgeneric/m_bbox.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_main.c`, `progs/doomgeneric/v_video.c`
- `M_ClearBox` (function) `progs/doomgeneric/m_bbox.h:38` `void M_ClearBox (fixed_t* box);` -- Bounding box functions.
- `M_AddToBox` (function) `progs/doomgeneric/m_bbox.h:41` `void M_AddToBox ( fixed_t* box, fixed_t x, fixed_t y );`

## progs/doomgeneric/m_cheat.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_cheat.h`
- `cht_CheckCheat` (function) `progs/doomgeneric/m_cheat.c:35` `int
cht_CheckCheat
( cheatseq_t*	cht,
  char		key )`
- `cht_GetParam` (function) `progs/doomgeneric/m_cheat.c:82` `void
cht_GetParam
( cheatseq_t*	cht,
  char*		buffer )`

## progs/doomgeneric/m_cheat.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/st_stuff.h`
- `cht_CheckCheat` (function) `progs/doomgeneric/m_cheat.h:51` `int cht_CheckCheat ( cheatseq_t* cht, char key );`
- `cht_GetParam` (function) `progs/doomgeneric/m_cheat.h:57` `void cht_GetParam ( cheatseq_t* cht, char* buffer );`

## progs/doomgeneric/m_config.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/z_zone.h`
- `SearchCollection` (function) `progs/doomgeneric/m_config.c:1563` `static default_t *SearchCollection(default_collection_t *collection, char *name)`
- `SaveDefaultCollection` (function) `progs/doomgeneric/m_config.c:1609` `static void SaveDefaultCollection(default_collection_t *collection)`
- `ParseIntParameter` (function) `progs/doomgeneric/m_config.c:1716` `static int ParseIntParameter(char *strparm)`
- `SetVariable` (function) `progs/doomgeneric/m_config.c:1728` `static void SetVariable(default_t *def, char *value)`
- `LoadDefaultCollection` (function) `progs/doomgeneric/m_config.c:1771` `static void LoadDefaultCollection(default_collection_t *collection)`
- `M_SetConfigFilenames` (function) `progs/doomgeneric/m_config.c:1836` `void M_SetConfigFilenames(char *main_config, char *extra_config)`
- `M_SaveDefaults` (function) `progs/doomgeneric/m_config.c:1846` `void M_SaveDefaults (void)`
- `M_SaveDefaultsAlternate` (function) `progs/doomgeneric/m_config.c:1856` `void M_SaveDefaultsAlternate(char *main, char *extra)`
- `M_LoadDefaults` (function) `progs/doomgeneric/m_config.c:1881` `void M_LoadDefaults (void)`
- `GetDefaultForName` (function) `progs/doomgeneric/m_config.c:1937` `static default_t *GetDefaultForName(char *name)`
- `M_BindVariable` (function) `progs/doomgeneric/m_config.c:1964` `void M_BindVariable(char *name, void *location)`
- `M_SetVariable` (function) `progs/doomgeneric/m_config.c:1977` `boolean M_SetVariable(char *name, char *value)`
- `M_GetIntVariable` (function) `progs/doomgeneric/m_config.c:1995` `int M_GetIntVariable(char *name)`
- `M_GetStrVariable` (function) `progs/doomgeneric/m_config.c:2010` `const char *M_GetStrVariable(char *name)`
- `M_GetFloatVariable` (function) `progs/doomgeneric/m_config.c:2025` `float M_GetFloatVariable(char *name)`
- `GetDefaultConfigDir` (function) `progs/doomgeneric/m_config.c:2043` `static char *GetDefaultConfigDir(void)`
- `M_SetConfigDir` (function) `progs/doomgeneric/m_config.c:2059` `void M_SetConfigDir(char *dir)`
- `M_GetSaveGameDir` (function) `progs/doomgeneric/m_config.c:2087` `char *M_GetSaveGameDir(char *iwadname)`

## progs/doomgeneric/m_config.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_controls.c`
- `M_LoadDefaults` (function) `progs/doomgeneric/m_config.h:25` `void M_LoadDefaults(void);`
- `M_SaveDefaults` (function) `progs/doomgeneric/m_config.h:26` `void M_SaveDefaults(void);`
- `M_SaveDefaultsAlternate` (function) `progs/doomgeneric/m_config.h:27` `void M_SaveDefaultsAlternate(char *main, char *extra);`
- `M_SetConfigDir` (function) `progs/doomgeneric/m_config.h:28` `void M_SetConfigDir(char *dir);`
- `M_BindVariable` (function) `progs/doomgeneric/m_config.h:29` `void M_BindVariable(char *name, void *variable);`
- `M_GetIntVariable` (function) `progs/doomgeneric/m_config.h:31` `int M_GetIntVariable(char *name);`
- `M_GetStrVariable` (function) `progs/doomgeneric/m_config.h:32` `const char *M_GetStrVariable(char *name);`
- `M_GetFloatVariable` (function) `progs/doomgeneric/m_config.h:33` `float M_GetFloatVariable(char *name);`
- `M_SetConfigFilenames` (function) `progs/doomgeneric/m_config.h:34` `void M_SetConfigFilenames(char *main_config, char *extra_config);`
- `M_GetSaveGameDir` (function) `progs/doomgeneric/m_config.h:35` `char *M_GetSaveGameDir(char *iwadname);`

## progs/doomgeneric/m_controls.c
Depends on: `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`
- `M_BindBaseControls` (function) `progs/doomgeneric/m_controls.c:204` `void M_BindBaseControls(void)`
- `M_BindHereticControls` (function) `progs/doomgeneric/m_controls.c:241` `void M_BindHereticControls(void)`
- `M_BindHexenControls` (function) `progs/doomgeneric/m_controls.c:256` `void M_BindHexenControls(void)`
- `M_BindStrifeControls` (function) `progs/doomgeneric/m_controls.c:272` `void M_BindStrifeControls(void)`
- `M_BindWeaponControls` (function) `progs/doomgeneric/m_controls.c:307` `void M_BindWeaponControls(void)`
- `M_BindMapControls` (function) `progs/doomgeneric/m_controls.c:328` `void M_BindMapControls(void)`
- `M_BindMenuControls` (function) `progs/doomgeneric/m_controls.c:344` `void M_BindMenuControls(void)`
- `M_BindChatControls` (function) `progs/doomgeneric/m_controls.c:375` `void M_BindChatControls(unsigned int num_players)`
- `M_ApplyPlatformDefaults` (function) `progs/doomgeneric/m_controls.c:394` `void M_ApplyPlatformDefaults(void)`

## progs/doomgeneric/m_controls.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`
- `M_BindBaseControls` (function) `progs/doomgeneric/m_controls.h:156` `void M_BindBaseControls(void);`
- `M_BindHereticControls` (function) `progs/doomgeneric/m_controls.h:157` `void M_BindHereticControls(void);`
- `M_BindHexenControls` (function) `progs/doomgeneric/m_controls.h:158` `void M_BindHexenControls(void);`
- `M_BindStrifeControls` (function) `progs/doomgeneric/m_controls.h:159` `void M_BindStrifeControls(void);`
- `M_BindWeaponControls` (function) `progs/doomgeneric/m_controls.h:160` `void M_BindWeaponControls(void);`
- `M_BindMapControls` (function) `progs/doomgeneric/m_controls.h:161` `void M_BindMapControls(void);`
- `M_BindMenuControls` (function) `progs/doomgeneric/m_controls.h:162` `void M_BindMenuControls(void);`
- `M_BindChatControls` (function) `progs/doomgeneric/m_controls.h:163` `void M_BindChatControls(unsigned int num_players);`
- `M_ApplyPlatformDefaults` (function) `progs/doomgeneric/m_controls.h:165` `void M_ApplyPlatformDefaults(void);`

## progs/doomgeneric/m_fixed.c
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_fixed.h`
- `FixedMul` (function) `progs/doomgeneric/m_fixed.c:34` `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
- `FixedDiv` (function) `progs/doomgeneric/m_fixed.c:47` `fixed_t FixedDiv(fixed_t a, fixed_t b)`

## progs/doomgeneric/m_fixed.h
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/tables.h`
- `FixedMul` (function) `progs/doomgeneric/m_fixed.h:34` `fixed_t FixedMul (fixed_t a, fixed_t b);`
- `FixedDiv` (function) `progs/doomgeneric/m_fixed.h:35` `fixed_t FixedDiv (fixed_t a, fixed_t b);`


Next: [API_p13.md](API_p13.md)
