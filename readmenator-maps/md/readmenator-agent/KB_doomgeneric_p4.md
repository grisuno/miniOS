# Subsystem: doomgeneric (page 4 of 12)
Previous: [KB_doomgeneric_p3.md](KB_doomgeneric_p3.md)

## progs/doomgeneric/hu_lib.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `HUlib_init` (function, line 36) `void HUlib_init(void)`
  - `HUlib_clearTextLine` (function, line 40) `void HUlib_clearTextLine(hu_textline_t* t)`
  - `HUlib_initTextLine` (function, line 48) `void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )`
  - `HUlib_addCharToTextLine` (function, line 63) `boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )`
  - `HUlib_delCharFromTextLine` (function, line 80) `boolean HUlib_delCharFromTextLine(hu_textline_t* t)`
  - `HUlib_drawTextLine` (function, line 94) `void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )`
  - `HUlib_eraseTextLine` (function, line 137) `void HUlib_eraseTextLine(hu_textline_t* l)`
  - `HUlib_initSText` (function, line 169) `void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		star...`
  - `HUlib_addLineToSText` (function, line 192) `void HUlib_addLineToSText(hu_stext_t* s)`
  - `HUlib_addMessageToSText` (function, line 209) `void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )`
  - `HUlib_drawSText` (function, line 223) `void HUlib_drawSText(hu_stext_t* s)`
  - `HUlib_eraseSText` (function, line 246) `void HUlib_eraseSText(hu_stext_t* s)`
  - `HUlib_initIText` (function, line 262) `void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  ...`
  - `HUlib_delCharFromIText` (function, line 278) `void HUlib_delCharFromIText(hu_itext_t* it)`
  - `HUlib_eraseLineFromIText` (function, line 284) `void HUlib_eraseLineFromIText(hu_itext_t* it)`
  - `HUlib_resetIText` (function, line 291) `void HUlib_resetIText(hu_itext_t* it)`
  - `HUlib_addPrefixToIText` (function, line 298) `void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )`
  - `HUlib_keyInIText` (function, line 310) `boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )`
  - `HUlib_drawIText` (function, line 329) `void HUlib_drawIText(hu_itext_t* it)`
  - `HUlib_eraseIText` (function, line 340) `void HUlib_eraseIText(hu_itext_t* it)`
  - `automapactive` (variable, line 34) `extern boolean automapactive;`
  - `noterased` (macro, line 32) `#define noterased`
- Depends on: `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/r_draw.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/v_video.h`

## progs/doomgeneric/hu_lib.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `hu_textline_t` (struct, line 36)
  - `hu_stext_t` (struct, line 56)
  - `hu_itext_t` (struct, line 72)
  - `HUlib_init` (function, line 91) `void HUlib_init(void);`
  - `HUlib_clearTextLine` (function, line 98) `void HUlib_clearTextLine(hu_textline_t *t);`
  - `HUlib_initTextLine` (function, line 100) `void HUlib_initTextLine(hu_textline_t *t, int x, int y, patch_t **f, int sc);`
  - `HUlib_drawTextLine` (function, line 109) `void HUlib_drawTextLine(hu_textline_t *l, boolean drawcursor);`
  - `HUlib_eraseTextLine` (function, line 112) `void HUlib_eraseTextLine(hu_textline_t *l);`
  - `HUlib_initSText` (function, line 121) `void HUlib_initSText ( hu_stext_t* s, int x, int y, int h, patch_t** font, int startchar, boolean* on );`
  - `HUlib_addLineToSText` (function, line 131) `void HUlib_addLineToSText(hu_stext_t* s);`
  - `HUlib_addMessageToSText` (function, line 135) `void HUlib_addMessageToSText ( hu_stext_t* s, char* prefix, char* msg );`
  - `HUlib_drawSText` (function, line 141) `void HUlib_drawSText(hu_stext_t* s);`
  - `HUlib_eraseSText` (function, line 144) `void HUlib_eraseSText(hu_stext_t* s);`
  - `HUlib_initIText` (function, line 148) `void HUlib_initIText ( hu_itext_t* it, int x, int y, patch_t** font, int startchar, boolean* on );`
  - `HUlib_delCharFromIText` (function, line 157) `void HUlib_delCharFromIText(hu_itext_t* it);`
  - `HUlib_eraseLineFromIText` (function, line 160) `void HUlib_eraseLineFromIText(hu_itext_t* it);`
  - `HUlib_resetIText` (function, line 163) `void HUlib_resetIText(hu_itext_t* it);`
  - `HUlib_addPrefixToIText` (function, line 167) `void HUlib_addPrefixToIText ( hu_itext_t* it, char* str );`
  - `HUlib_drawIText` (function, line 177) `void HUlib_drawIText(hu_itext_t* it);`
  - `HUlib_eraseIText` (function, line 180) `void HUlib_eraseIText(hu_itext_t* it);`
  - `__HULIB__` (macro, line 19) `#define __HULIB__`
  - `HU_CHARERASE` (macro, line 25) `#define HU_CHARERASE`
  - `HU_MAXLINES` (macro, line 27) `#define HU_MAXLINES`
  - `HU_MAXLINELENGTH` (macro, line 28) `#define HU_MAXLINELENGTH`
- Depends on: `progs/doomgeneric/r_defs.h`
- Imported by: `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`

## progs/doomgeneric/hu_stuff.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `HU_Init` (function, line 286) `void HU_Init(void)`
  - `HU_Stop` (function, line 303) `void HU_Stop(void)`
  - `HU_Start` (function, line 308) `void HU_Start(void)`
  - `HU_Drawer` (function, line 383) `void HU_Drawer(void)`
  - `HU_Erase` (function, line 393) `void HU_Erase(void)`
  - `HU_Ticker` (function, line 402) `void HU_Ticker(void)`
  - `HU_queueChatChar` (function, line 482) `void HU_queueChatChar(char c)`
  - `HU_dequeueChatChar` (function, line 495) `char HU_dequeueChatChar(void)`
  - `HU_Responder` (function, line 512) `boolean HU_Responder(event_t *ev)`
  - `showMessages` (variable, line 103) `extern int showMessages;`
  - `HU_TITLE` (macro, line 47) `#define HU_TITLE`
  - `HU_TITLE2` (macro, line 48) `#define HU_TITLE2`
  - `HU_TITLEP` (macro, line 49) `#define HU_TITLEP`
  - `HU_TITLET` (macro, line 50) `#define HU_TITLET`
  - `HU_TITLE_CHEX` (macro, line 51) `#define HU_TITLE_CHEX`
  - `HU_TITLEHEIGHT` (macro, line 52) `#define HU_TITLEHEIGHT`
  - `HU_TITLEX` (macro, line 53) `#define HU_TITLEX`
  - `HU_TITLEY` (macro, line 54) `#define HU_TITLEY`
  - `HU_INPUTTOGGLE` (macro, line 56) `#define HU_INPUTTOGGLE`
  - `HU_INPUTX` (macro, line 57) `#define HU_INPUTX`
  - `HU_INPUTY` (macro, line 58) `#define HU_INPUTY`
  - `HU_INPUTWIDTH` (macro, line 59) `#define HU_INPUTWIDTH`
  - `HU_INPUTHEIGHT` (macro, line 60) `#define HU_INPUTHEIGHT`
  - `QUEUESIZE` (macro, line 475) `#define QUEUESIZE`
- Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_lib.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/hu_stuff.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `HU_Init` (function, line 46) `void HU_Init(void);`
  - `HU_Start` (function, line 47) `void HU_Start(void);`
  - `HU_Ticker` (function, line 51) `void HU_Ticker(void);`
  - `HU_Drawer` (function, line 52) `void HU_Drawer(void);`
  - `HU_dequeueChatChar` (function, line 53) `char HU_dequeueChatChar(void);`
  - `HU_Erase` (function, line 54) `void HU_Erase(void);`
  - `chat_macros` (variable, line 56) `extern char *chat_macros[10];`
  - `__HU_STUFF_H__` (macro, line 19) `#define __HU_STUFF_H__`
  - `HU_FONTSTART` (macro, line 27) `#define HU_FONTSTART`
  - `HU_FONTEND` (macro, line 28) `#define HU_FONTEND`
  - `HU_FONTSIZE` (macro, line 31) `#define HU_FONTSIZE`
  - `HU_BROADCAST` (macro, line 33) `#define HU_BROADCAST`
  - `HU_MSGX` (macro, line 35) `#define HU_MSGX`
  - `HU_MSGY` (macro, line 36) `#define HU_MSGY`
  - `HU_MSGWIDTH` (macro, line 37) `#define HU_MSGWIDTH`
  - `HU_MSGHEIGHT` (macro, line 38) `#define HU_MSGHEIGHT`
  - `HU_MSGTIMEOUT` (macro, line 40) `#define HU_MSGTIMEOUT`
- Depends on: `progs/doomgeneric/d_event.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_mobj.c`

## progs/doomgeneric/i_cdmus.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `I_CDMusInit` (function, line 38) `int I_CDMusInit(void)`
  - `I_CDMusPrintStartup` (function, line 92) `void I_CDMusPrintStartup(void)`
  - `I_CDMusPlay` (function, line 107) `int I_CDMusPlay(int track)`
  - `I_CDMusStop` (function, line 130) `int I_CDMusStop(void)`
  - `I_CDMusResume` (function, line 145) `int I_CDMusResume(void)`
  - `I_CDMusSetVolume` (function, line 160) `int I_CDMusSetVolume(int volume)`
  - `I_CDMusFirstTrack` (function, line 169) `int I_CDMusFirstTrack(void)`
  - `I_CDMusLastTrack` (function, line 202) `int I_CDMusLastTrack(void)`
  - `I_CDMusTrackLength` (function, line 219) `int I_CDMusTrackLength(int track_num)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_cdmus.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/i_cdmus.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `I_CDMusInit` (function, line 31) `int I_CDMusInit(void);`
  - `I_CDMusPrintStartup` (function, line 32) `void I_CDMusPrintStartup(void);`
  - `I_CDMusPlay` (function, line 33) `int I_CDMusPlay(int track);`
  - `I_CDMusStop` (function, line 34) `int I_CDMusStop(void);`
  - `I_CDMusResume` (function, line 35) `int I_CDMusResume(void);`
  - `I_CDMusSetVolume` (function, line 36) `int I_CDMusSetVolume(int volume);`
  - `I_CDMusFirstTrack` (function, line 37) `int I_CDMusFirstTrack(void);`
  - `I_CDMusLastTrack` (function, line 38) `int I_CDMusLastTrack(void);`
  - `I_CDMusTrackLength` (function, line 39) `int I_CDMusTrackLength(int track);`
  - `cd_Error` (variable, line 29) `extern int cd_Error;`
  - `__ICDMUS__` (macro, line 19) `#define __ICDMUS__`
  - `CDERR_NOTINSTALLED` (macro, line 21) `#define CDERR_NOTINSTALLED`
  - `CDERR_NOAUDIOSUPPORT` (macro, line 22) `#define CDERR_NOAUDIOSUPPORT`
  - `CDERR_NOAUDIOTRACKS` (macro, line 23) `#define CDERR_NOAUDIOTRACKS`
  - `CDERR_BADDRIVE` (macro, line 24) `#define CDERR_BADDRIVE`
  - `CDERR_BADTRACK` (macro, line 25) `#define CDERR_BADTRACK`
  - `CDERR_IOCTLBUFFMEM` (macro, line 26) `#define CDERR_IOCTLBUFFMEM`
  - `CDERR_DEVREQBASE` (macro, line 27) `#define CDERR_DEVREQBASE`
- Imported by: `progs/doomgeneric/i_cdmus.c`

## progs/doomgeneric/i_endoom.c
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: c
- Symbols:
  - `I_Endoom` (function, line 36) `void I_Endoom(byte *endoom_data)`
  - `ENDOOM_W` (macro, line 29) `#define ENDOOM_W`
  - `ENDOOM_H` (macro, line 30) `#define ENDOOM_H`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`

## progs/doomgeneric/i_endoom.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `I_Endoom` (function, line 26) `void I_Endoom(byte *data);`
  - `__I_ENDOOM__` (macro, line 21) `#define __I_ENDOOM__`
- Imported by: `progs/doomgeneric/d_main.c`

## progs/doomgeneric/i_input.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `TranslateKey` (function, line 225) `static unsigned char TranslateKey(unsigned char key)`
  - `GetTypedChar` (function, line 242) `static unsigned char GetTypedChar(unsigned char key)`
  - `UpdateShiftStatus` (function, line 263) `static void UpdateShiftStatus(int pressed, unsigned char key)`
  - `I_GetEvent` (function, line 279) `void I_GetEvent(void)`
  - `I_InitInput` (function, line 338) `void I_InitInput(void)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/i_joystick.c
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: c
- Symbols:
  - `I_ShutdownJoystick` (function, line 77) `void I_ShutdownJoystick(void)`
  - `IsValidAxis` (function, line 90) `static boolean IsValidAxis(int axis)`
  - `I_InitJoystick` (function, line 115) `void I_InitJoystick(void)`
  - `IsAxisButton` (function, line 171) `static boolean IsAxisButton(int physbutton)`
  - `ReadButtonState` (function, line 203) `static int ReadButtonState(int vbutton)`
  - `GetButtonsState` (function, line 228) `static int GetButtonsState(void)`
  - `GetAxisState` (function, line 248) `static int GetAxisState(int axis, int invert)`
  - `I_UpdateJoystick` (function, line 321) `void I_UpdateJoystick(void)`
  - `I_BindJoystickVariables` (function, line 339) `void I_BindJoystickVariables(void)`
  - `DEAD_ZONE` (macro, line 38) `#define DEAD_ZONE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/pokemon/minios_stubs/SDL.h`

## progs/doomgeneric/i_joystick.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `I_InitJoystick` (function, line 63) `void I_InitJoystick(void);`
  - `I_ShutdownJoystick` (function, line 64) `void I_ShutdownJoystick(void);`
  - `I_UpdateJoystick` (function, line 65) `void I_UpdateJoystick(void);`
  - `I_BindJoystickVariables` (function, line 67) `void I_BindJoystickVariables(void);`
  - `__I_JOYSTICK__` (macro, line 20) `#define __I_JOYSTICK__`
  - `NUM_VIRTUAL_BUTTONS` (macro, line 25) `#define NUM_VIRTUAL_BUTTONS`
  - `BUTTON_AXIS` (macro, line 33) `#define BUTTON_AXIS`
  - `IS_BUTTON_AXIS` (macro, line 36) `#define IS_BUTTON_AXIS(axis)`
  - `BUTTON_AXIS_NEG` (macro, line 39) `#define BUTTON_AXIS_NEG(axis)`
  - `BUTTON_AXIS_POS` (macro, line 40) `#define BUTTON_AXIS_POS(axis)`
  - `CREATE_BUTTON_AXIS` (macro, line 43) `#define CREATE_BUTTON_AXIS(neg, pos)`
  - `HAT_AXIS` (macro, line 48) `#define HAT_AXIS`
  - `IS_HAT_AXIS` (macro, line 50) `#define IS_HAT_AXIS(axis)`
  - `HAT_AXIS_HAT` (macro, line 53) `#define HAT_AXIS_HAT(axis)`
  - `HAT_AXIS_DIRECTION` (macro, line 55) `#define HAT_AXIS_DIRECTION(axis)`
  - `CREATE_HAT_AXIS` (macro, line 57) `#define CREATE_HAT_AXIS(hat, direction)`
  - `HAT_AXIS_HORIZONTAL` (macro, line 60) `#define HAT_AXIS_HORIZONTAL`
  - `HAT_AXIS_VERTICAL` (macro, line 61) `#define HAT_AXIS_VERTICAL`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`

## progs/doomgeneric/i_main.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 40) `int main(int argc, char **argv)`
  - `D_DoomMain` (function, line 33) `void D_DoomMain (void);`
  - `M_FindResponseFile` (function, line 35) `void M_FindResponseFile(void);`
  - `dg_Create` (function, line 37) `void dg_Create();`
- Depends on: `progs/doomgeneric/m_argv.h`

## progs/doomgeneric/i_minios_sound.c
- Doc: audio_pump: SFX are muted on pcm2 (music only): effect tones ruined the melody, so audio_pump...
- Layer: utility
- Language: c
- Symbols:
  - `pcspk_channel_t` (struct, line 17)
  - `mus_player_t` (struct, line 146)
  - `sys_tone_hw` (function, line 32) `static long sys_tone_hw(unsigned f)`
  - `sys_time` (function, line 35) `static long sys_time(void)`
  - `sys_pcm2_open` (function, line 38) `static long sys_pcm2_open(long flags)`
  - `sys_pcm2_write` (function, line 41) `static long sys_pcm2_write(const void *buf, long len)`
  - `sys_pcm2_close` (function, line 44) `static void sys_pcm2_close(void)`
  - `audio_ensure` (function, line 68) `static void audio_ensure(void)`
  - `audio_pump` (function, line 77) `static void audio_pump(void)`
  - `audio_tone` (function, line 85) `static void audio_tone(unsigned freq)`
  - `audio_close` (function, line 92) `static void audio_close(void)`
  - `mus_read_varlen` (function, line 169) `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
  - `mus_next_block` (function, line 183) `static int mus_next_block(mus_player_t *m, unsigned long *out)`
  - `mus_note_cmp` (function, line 228) `static int mus_note_cmp(const void *a, const void *b)`
  - `mus_build_chord` (function, line 236) `static void mus_build_chord(mus_player_t *m)`
  - `mus_hold_tone` (function, line 261) `static void mus_hold_tone(unsigned freq, unsigned long ms)`
  - `mus_play_chord` (function, line 274) `static void mus_play_chord(mus_player_t *m)`
  - `mus_advance` (function, line 288) `static void mus_advance(mus_player_t *m, unsigned long ms)`
  - `mus_render_pcm` (function, line 320) `static void mus_render_pcm(mus_player_t *m, unsigned char *out, unsigned n)`
  - `mus_render_push` (function, line 359) `static void mus_render_push(mus_player_t *m, unsigned n)`
  - `mus_advance_pcm` (function, line 369) `static void mus_advance_pcm(mus_player_t *m)`
  - `MUS_Init` (function, line 410) `static boolean MUS_Init(void)`
  - `MUS_Shutdown` (function, line 415) `static void MUS_Shutdown(void)`
  - `MUS_SetMusicVolume` (function, line 422) `static void MUS_SetMusicVolume(int volume)`
  - `MUS_Pause` (function, line 424) `static void MUS_Pause(void)`
  - `MUS_Resume` (function, line 425) `static void MUS_Resume(void)`
  - `MUS_RegisterSong` (function, line 427) `static void *MUS_RegisterSong(void *data, int len)`
  - `MUS_UnRegisterSong` (function, line 442) `static void MUS_UnRegisterSong(void *handle)`
  - `MUS_PlaySong` (function, line 448) `static void MUS_PlaySong(void *handle, boolean looping)`
  - `MUS_StopSong` (function, line 469) `static void MUS_StopSong(void)`
  - `MUS_MusicIsPlaying` (function, line 474) `static boolean MUS_MusicIsPlaying(void)`
  - `MUS_Poll` (function, line 478) `static void MUS_Poll(void)`
  - `PCSPK_Init` (function, line 512) `static boolean PCSPK_Init(boolean use_sfx_prefix)`
  - `PCSPK_Shutdown` (function, line 519) `static void PCSPK_Shutdown(void)`
  - `PCSPK_GetSfxLumpNum` (function, line 529) `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
  - `free_channel` (function, line 540) `static void free_channel(int i)`
  - `PCSPK_Update` (function, line 549) `static void PCSPK_Update(void)`
  - `PCSPK_UpdateSoundParams` (function, line 587) `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
  - `PCSPK_StartSound` (function, line 591) `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
  - `PCSPK_StopSound` (function, line 641) `static void PCSPK_StopSound(int channel)`
  - `PCSPK_SoundIsPlaying` (function, line 647) `static boolean PCSPK_SoundIsPlaying(int channel)`
  - `PCSPK_CacheSounds` (function, line 653) `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`
  - `muted` (function, line 51) `* pcm2 while sfx stay muted (effect tones ruined the melody);`
  - `PCSPK_CHANNELS` (macro, line 12) `#define PCSPK_CHANNELS`
  - `PCSPK_TICK_MS` (macro, line 13) `#define PCSPK_TICK_MS`
  - `DOOM_PCM_RATE` (macro, line 55) `#define DOOM_PCM_RATE`
  - `DOOM_PCM_VOL` (macro, line 56) `#define DOOM_PCM_VOL`
  - `MUS_TICKS_PER_SEC` (macro, line 118) `#define MUS_TICKS_PER_SEC`
  - `MUS_PERCUSSION_CHAN` (macro, line 119) `#define MUS_PERCUSSION_CHAN`
  - `MUS_ARP_SLOT_MS` (macro, line 120) `#define MUS_ARP_SLOT_MS`
  - `MUS_BASS_HOLD_MS` (macro, line 121) `#define MUS_BASS_HOLD_MS`
  - `MUS_BASS_LINE_MIDI` (macro, line 122) `#define MUS_BASS_LINE_MIDI`
  - `MUS_ARP_MAX` (macro, line 123) `#define MUS_ARP_MAX`
  - `DOOM_PCM_DRUM_SMP` (macro, line 125) `#define DOOM_PCM_DRUM_SMP`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`, `progs/minios_abi.h`

## progs/doomgeneric/i_scale.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `I_InitScale` (function, line 61) `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
  - `I_Scale1x` (function, line 75) `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
  - `I_Scale2x` (function, line 105) `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
  - `I_Scale3x` (function, line 146) `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
  - `I_Scale4x` (function, line 191) `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
  - `I_Scale5x` (function, line 240) `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
  - `FindNearestColor` (function, line 295) `static int FindNearestColor(byte *palette, int r, int g, int b)`
  - `GenerateStretchTable` (function, line 332) `static byte *GenerateStretchTable(byte *palette, int pct)`
  - `I_InitStretchTables` (function, line 361) `static void I_InitStretchTables(byte *palette)`
  - `I_InitSquashTable` (function, line 387) `static void I_InitSquashTable(byte *palette)`
  - `I_ResetScaleTables` (function, line 404) `void I_ResetScaleTables(byte *palette)`
  - `WriteBlendedLine1x` (function, line 434) `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch1x` (function, line 450) `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
  - `WriteLine2x` (function, line 507) `static inline void WriteLine2x(byte *dest, byte *src)`
  - `WriteBlendedLine2x` (function, line 520) `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch2x` (function, line 539) `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
  - `WriteLine3x` (function, line 620) `static inline void WriteLine3x(byte *dest, byte *src)`
  - `WriteBlendedLine3x` (function, line 634) `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch3x` (function, line 654) `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
  - `WriteLine4x` (function, line 759) `static inline void WriteLine4x(byte *dest, byte *src)`
  - `WriteBlendedLine4x` (function, line 774) `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
  - `I_Stretch4x` (function, line 795) `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
  - `WriteLine5x` (function, line 924) `static inline void WriteLine5x(byte *dest, byte *src)`
  - `I_Stretch5x` (function, line 942) `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine1x` (function, line 1030) `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
  - `I_Squash1x` (function, line 1061) `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine2x` (function, line 1102) `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
  - `I_Squash2x` (function, line 1160) `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine3x` (function, line 1197) `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
  - `I_Squash3x` (function, line 1243) `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine4x` (function, line 1279) `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
  - `I_Squash4x` (function, line 1354) `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
  - `WriteSquashedLine5x` (function, line 1390) `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
  - `I_Squash5x` (function, line 1419) `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`
  - `inline` (macro, line 32) `#define inline`
  - `DRAW_PIXEL2` (macro, line 1099) `#define DRAW_PIXEL2`
  - `DRAW_PIXEL3` (macro, line 1194) `#define DRAW_PIXEL3`
  - `DRAW_PIXEL4` (macro, line 1276) `#define DRAW_PIXEL4`
  - `DRAW_PIXEL5` (macro, line 1387) `#define DRAW_PIXEL5`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/i_scale.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `I_InitScale` (function, line 25) `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);`
  - `I_ResetScaleTables` (function, line 26) `void I_ResetScaleTables(byte *palette);`
  - `mode_scale_1x` (variable, line 30) `extern screen_mode_t mode_scale_1x;`
  - `mode_scale_2x` (variable, line 31) `extern screen_mode_t mode_scale_2x;`
  - `mode_scale_3x` (variable, line 32) `extern screen_mode_t mode_scale_3x;`
  - `mode_scale_4x` (variable, line 33) `extern screen_mode_t mode_scale_4x;`
  - `mode_scale_5x` (variable, line 34) `extern screen_mode_t mode_scale_5x;`
  - `mode_stretch_1x` (variable, line 38) `extern screen_mode_t mode_stretch_1x;`
  - `mode_stretch_2x` (variable, line 39) `extern screen_mode_t mode_stretch_2x;`
  - `mode_stretch_3x` (variable, line 40) `extern screen_mode_t mode_stretch_3x;`
  - `mode_stretch_4x` (variable, line 41) `extern screen_mode_t mode_stretch_4x;`
  - `mode_stretch_5x` (variable, line 42) `extern screen_mode_t mode_stretch_5x;`
  - `mode_squash_1x` (variable, line 46) `extern screen_mode_t mode_squash_1x;`
  - `mode_squash_2x` (variable, line 47) `extern screen_mode_t mode_squash_2x;`
  - `mode_squash_3x` (variable, line 48) `extern screen_mode_t mode_squash_3x;`
  - `mode_squash_4x` (variable, line 49) `extern screen_mode_t mode_squash_4x;`
  - `mode_squash_5x` (variable, line 50) `extern screen_mode_t mode_squash_5x;`
  - `__I_SCALE__` (macro, line 21) `#define __I_SCALE__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_input.c`

## progs/doomgeneric/i_sound.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `SndDeviceInList` (function, line 116) `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
  - `InitSfxModule` (function, line 135) `static void InitSfxModule(boolean use_sfx_prefix)`
  - `InitMusicModule` (function, line 163) `static void InitMusicModule(void)`
  - `I_InitSound` (function, line 195) `void I_InitSound(boolean use_sfx_prefix)`
  - `I_ShutdownSound` (function, line 250) `void I_ShutdownSound(void)`
  - `I_GetSfxLumpNum` (function, line 263) `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
  - `I_UpdateSound` (function, line 275) `void I_UpdateSound(void)`
  - `CheckVolumeSeparation` (function, line 288) `static void CheckVolumeSeparation(int *vol, int *sep)`
  - `I_UpdateSoundParams` (function, line 309) `void I_UpdateSoundParams(int channel, int vol, int sep)`
  - `I_StartSound` (function, line 318) `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
  - `I_StopSound` (function, line 331) `void I_StopSound(int channel)`
  - `I_SoundIsPlaying` (function, line 339) `boolean I_SoundIsPlaying(int channel)`
  - `I_PrecacheSounds` (function, line 351) `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
  - `I_InitMusic` (function, line 359) `void I_InitMusic(void)`
  - `I_ShutdownMusic` (function, line 363) `void I_ShutdownMusic(void)`
  - `I_SetMusicVolume` (function, line 368) `void I_SetMusicVolume(int volume)`
  - `I_PauseSong` (function, line 376) `void I_PauseSong(void)`
  - `I_ResumeSong` (function, line 384) `void I_ResumeSong(void)`
  - `I_RegisterSong` (function, line 392) `void *I_RegisterSong(void *data, int len)`
  - `I_UnRegisterSong` (function, line 404) `void I_UnRegisterSong(void *handle)`
  - `I_PlaySong` (function, line 412) `void I_PlaySong(void *handle, boolean looping)`
  - `I_StopSong` (function, line 420) `void I_StopSong(void)`
  - `I_MusicIsPlaying` (function, line 428) `boolean I_MusicIsPlaying(void)`
  - `I_BindSoundVariables` (function, line 440) `void I_BindSoundVariables(void)`
  - `I_InitTimidityConfig` (function, line 65) `extern void I_InitTimidityConfig(void);`
  - `sound_sdl_module` (variable, line 66) `extern sound_module_t sound_sdl_module;`
  - `sound_pcsound_module` (variable, line 67) `extern sound_module_t sound_pcsound_module;`
  - `music_sdl_module` (variable, line 68) `extern music_module_t music_sdl_module;`
  - `music_opl_module` (variable, line 69) `extern music_module_t music_opl_module;`
  - `music_pcspeaker_module` (variable, line 70) `extern music_module_t music_pcspeaker_module;`
  - `opl_io_port` (variable, line 74) `extern int opl_io_port;`
  - `timidity_cfg_path` (variable, line 78) `extern char *timidity_cfg_path;`
  - `use_libsamplerate` (variable, line 443) `extern int use_libsamplerate;`
  - `libsamplerate_scale` (variable, line 444) `extern float libsamplerate_scale;`
- Depends on: `progs/doomgeneric/config.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`

## progs/doomgeneric/i_sound.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `sfxinfo_struct` (struct, line 31)
  - `musicinfo_t` (struct, line 72)
  - `sound_module_t` (struct, line 105)
  - `music_module_t` (struct, line 164)
  - `sfxinfo_t` (type_alias, line 29) `typedef struct sfxinfo_struct sfxinfo_t;`
  - `I_InitSound` (function, line 152) `void I_InitSound(boolean use_sfx_prefix);`
  - `I_ShutdownSound` (function, line 153) `void I_ShutdownSound(void);`
  - `I_GetSfxLumpNum` (function, line 154) `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);`
  - `I_UpdateSound` (function, line 155) `void I_UpdateSound(void);`
  - `I_UpdateSoundParams` (function, line 156) `void I_UpdateSoundParams(int channel, int vol, int sep);`
  - `I_StartSound` (function, line 157) `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);`
  - `I_StopSound` (function, line 158) `void I_StopSound(int channel);`
  - `I_PrecacheSounds` (function, line 160) `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);`
  - `I_InitMusic` (function, line 217) `void I_InitMusic(void);`
  - `I_ShutdownMusic` (function, line 218) `void I_ShutdownMusic(void);`
  - `I_SetMusicVolume` (function, line 219) `void I_SetMusicVolume(int volume);`
  - `I_PauseSong` (function, line 220) `void I_PauseSong(void);`
  - `I_ResumeSong` (function, line 221) `void I_ResumeSong(void);`
  - `I_RegisterSong` (function, line 222) `void *I_RegisterSong(void *data, int len);`
  - `I_UnRegisterSong` (function, line 223) `void I_UnRegisterSong(void *handle);`
  - `I_PlaySong` (function, line 224) `void I_PlaySong(void *handle, boolean looping);`
  - `I_StopSong` (function, line 225) `void I_StopSong(void);`
  - `I_BindSoundVariables` (function, line 235) `void I_BindSoundVariables(void);`
  - `snd_sfxdevice` (variable, line 228) `extern int snd_sfxdevice;`
  - `snd_musicdevice` (variable, line 229) `extern int snd_musicdevice;`
  - `snd_samplerate` (variable, line 230) `extern int snd_samplerate;`
  - `snd_cachesize` (variable, line 231) `extern int snd_cachesize;`
  - `snd_maxslicetime_ms` (variable, line 232) `extern int snd_maxslicetime_ms;`
  - `snd_musiccmd` (variable, line 233) `extern char *snd_musiccmd;`
  - `__I_SOUND__` (macro, line 21) `#define __I_SOUND__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sounds.h`


Next: [KB_doomgeneric_p5.md](KB_doomgeneric_p5.md)
