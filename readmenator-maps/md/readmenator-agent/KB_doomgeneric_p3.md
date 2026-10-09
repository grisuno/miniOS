# Subsystem: doomgeneric (page 3 of 12)
Previous: [KB_doomgeneric_p2.md](KB_doomgeneric_p2.md)

## progs/doomgeneric/doomgeneric_sosox.c
- Doc: doomgeneric for soso os (nano-x version) TODO: get keys from X, not using direct keyboard access!
- Layer: utility
- Language: c
- Symbols:
  - `convert_to_doom_key` (function, line 39) `static unsigned char convert_to_doom_key(unsigned char scancode)`
  - `add_key_to_queue` (function, line 88) `static void add_key_to_queue(int pressed, unsigned char key_code)`
  - `disable_raw_mode` (function, line 102) `void disable_raw_mode()`
  - `enable_raw_mode` (function, line 107) `void enable_raw_mode()`
  - `DG_Init` (function, line 117) `void DG_Init()`
  - `handle_key_input` (function, line 159) `static void handle_key_input()`
  - `DG_DrawFrame` (function, line 187) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 225) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 230) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 235) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 256) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 24) `#define KEYQUEUE_SIZE`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`

## progs/doomgeneric/doomgeneric_win.c
- Layer: utility
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 20) `static unsigned char convertToDoomKey(unsigned char key)`
  - `addKeyToQueue` (function, line 59) `static void addKeyToQueue(int pressed, unsigned char keyCode)`
  - `wndProc` (function, line 70) `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
  - `DG_Init` (function, line 95) `void DG_Init()`
  - `DG_DrawFrame` (function, line 146) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 162) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 167) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 172) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 193) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 14) `#define KEYQUEUE_SIZE`
- Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`

## progs/doomgeneric/doomgeneric_xlib.c
- Layer: utility
- Language: c
- Symbols:
  - `convertToDoomKey` (function, line 27) `static unsigned char convertToDoomKey(unsigned int key)`
  - `addKeyToQueue` (function, line 68) `static void addKeyToQueue(int pressed, unsigned int keyCode)`
  - `DG_Init` (function, line 79) `void DG_Init()`
  - `DG_DrawFrame` (function, line 127) `void DG_DrawFrame()`
  - `DG_SleepMs` (function, line 172) `void DG_SleepMs(uint32_t ms)`
  - `DG_GetTicksMs` (function, line 177) `uint32_t DG_GetTicksMs()`
  - `DG_GetKey` (function, line 187) `int DG_GetKey(int* pressed, unsigned char* doomKey)`
  - `DG_SetWindowTitle` (function, line 208) `void DG_SetWindowTitle(const char * title)`
  - `KEYQUEUE_SIZE` (macro, line 21) `#define KEYQUEUE_SIZE`
- Depends on: `kernel/string.c`, `kernel/time.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`

## progs/doomgeneric/doomkeys.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `__DOOMKEYS__` (macro, line 20) `#define __DOOMKEYS__`
  - `KEY_RIGHTARROW` (macro, line 27) `#define KEY_RIGHTARROW`
  - `KEY_LEFTARROW` (macro, line 28) `#define KEY_LEFTARROW`
  - `KEY_UPARROW` (macro, line 29) `#define KEY_UPARROW`
  - `KEY_DOWNARROW` (macro, line 30) `#define KEY_DOWNARROW`
  - `KEY_STRAFE_L` (macro, line 31) `#define KEY_STRAFE_L`
  - `KEY_STRAFE_R` (macro, line 32) `#define KEY_STRAFE_R`
  - `KEY_USE` (macro, line 33) `#define KEY_USE`
  - `KEY_FIRE` (macro, line 34) `#define KEY_FIRE`
  - `KEY_ESCAPE` (macro, line 35) `#define KEY_ESCAPE`
  - `KEY_ENTER` (macro, line 36) `#define KEY_ENTER`
  - `KEY_TAB` (macro, line 37) `#define KEY_TAB`
  - `KEY_F1` (macro, line 38) `#define KEY_F1`
  - `KEY_F2` (macro, line 39) `#define KEY_F2`
  - `KEY_F3` (macro, line 40) `#define KEY_F3`
  - `KEY_F4` (macro, line 41) `#define KEY_F4`
  - `KEY_F5` (macro, line 42) `#define KEY_F5`
  - `KEY_F6` (macro, line 43) `#define KEY_F6`
  - `KEY_F7` (macro, line 44) `#define KEY_F7`
  - `KEY_F8` (macro, line 45) `#define KEY_F8`
  - `KEY_F9` (macro, line 46) `#define KEY_F9`
  - `KEY_F10` (macro, line 47) `#define KEY_F10`
  - `KEY_F11` (macro, line 48) `#define KEY_F11`
  - `KEY_F12` (macro, line 49) `#define KEY_F12`
  - `KEY_BACKSPACE` (macro, line 51) `#define KEY_BACKSPACE`
  - `KEY_PAUSE` (macro, line 52) `#define KEY_PAUSE`
  - `KEY_EQUALS` (macro, line 54) `#define KEY_EQUALS`
  - `KEY_MINUS` (macro, line 55) `#define KEY_MINUS`
  - `KEY_RSHIFT` (macro, line 57) `#define KEY_RSHIFT`
  - `KEY_RCTRL` (macro, line 58) `#define KEY_RCTRL`
  - `KEY_RALT` (macro, line 59) `#define KEY_RALT`
  - `KEY_LALT` (macro, line 61) `#define KEY_LALT`
  - `KEY_CAPSLOCK` (macro, line 65) `#define KEY_CAPSLOCK`
  - `KEY_NUMLOCK` (macro, line 66) `#define KEY_NUMLOCK`
  - `KEY_SCRLCK` (macro, line 67) `#define KEY_SCRLCK`
  - `KEY_PRTSCR` (macro, line 68) `#define KEY_PRTSCR`
  - `KEY_HOME` (macro, line 70) `#define KEY_HOME`
  - `KEY_END` (macro, line 71) `#define KEY_END`
  - `KEY_PGUP` (macro, line 72) `#define KEY_PGUP`
  - `KEY_PGDN` (macro, line 73) `#define KEY_PGDN`
  - `KEY_INS` (macro, line 74) `#define KEY_INS`
  - `KEY_DEL` (macro, line 75) `#define KEY_DEL`
  - `KEYP_0` (macro, line 77) `#define KEYP_0`
  - `KEYP_1` (macro, line 78) `#define KEYP_1`
  - `KEYP_2` (macro, line 79) `#define KEYP_2`
  - `KEYP_3` (macro, line 80) `#define KEYP_3`
  - `KEYP_4` (macro, line 81) `#define KEYP_4`
  - `KEYP_5` (macro, line 82) `#define KEYP_5`
  - `KEYP_6` (macro, line 83) `#define KEYP_6`
  - `KEYP_7` (macro, line 84) `#define KEYP_7`
  - `KEYP_8` (macro, line 85) `#define KEYP_8`
  - `KEYP_9` (macro, line 86) `#define KEYP_9`
  - `KEYP_DIVIDE` (macro, line 88) `#define KEYP_DIVIDE`
  - `KEYP_PLUS` (macro, line 89) `#define KEYP_PLUS`
  - `KEYP_MINUS` (macro, line 90) `#define KEYP_MINUS`
  - `KEYP_MULTIPLY` (macro, line 91) `#define KEYP_MULTIPLY`
  - `KEYP_PERIOD` (macro, line 92) `#define KEYP_PERIOD`
  - `KEYP_EQUALS` (macro, line 93) `#define KEYP_EQUALS`
  - `KEYP_ENTER` (macro, line 94) `#define KEYP_ENTER`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_win.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_lib.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/doomstat.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Depends on: `progs/doomgeneric/doomstat.h`

## progs/doomgeneric/doomstat.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `nomonsters` (variable, line 46) `extern boolean nomonsters;`
  - `respawnparm` (variable, line 47) `extern boolean respawnparm;`
  - `fastparm` (variable, line 48) `extern boolean fastparm;`
  - `devparm` (variable, line 50) `extern boolean devparm;`
  - `gamemode` (variable, line 56) `extern GameMode_t gamemode;`
  - `gamemission` (variable, line 57) `extern GameMission_t gamemission;`
  - `gameversion` (variable, line 58) `extern GameVersion_t gameversion;`
  - `gamedescription` (variable, line 59) `extern char *gamedescription;`
  - `bfgedition` (variable, line 62) `extern boolean bfgedition;`
  - `modifiedgame` (variable, line 74) `extern boolean modifiedgame;`
  - `startskill` (variable, line 82) `extern skill_t startskill;`
  - `startepisode` (variable, line 83) `extern int startepisode;`
  - `startmap` (variable, line 84) `extern int startmap;`
  - `startloadgame` (variable, line 89) `extern int startloadgame;`
  - `autostart` (variable, line 91) `extern boolean autostart;`
  - `gameskill` (variable, line 94) `extern skill_t gameskill;`
  - `gameepisode` (variable, line 95) `extern int gameepisode;`
  - `gamemap` (variable, line 96) `extern int gamemap;`
  - `timelimit` (variable, line 99) `extern int timelimit;`
  - `respawnmonsters` (variable, line 102) `extern boolean respawnmonsters;`
  - `netgame` (variable, line 105) `extern boolean netgame;`
  - `deathmatch` (variable, line 108) `extern int deathmatch;`
  - `sfxVolume` (variable, line 120) `extern int sfxVolume;`
  - `musicVolume` (variable, line 121) `extern int musicVolume;`
  - `snd_MusicDevice` (variable, line 127) `extern int snd_MusicDevice;`
  - `snd_SfxDevice` (variable, line 128) `extern int snd_SfxDevice;`
  - `snd_DesiredMusicDevice` (variable, line 130) `extern int snd_DesiredMusicDevice;`
  - `snd_DesiredSfxDevice` (variable, line 131) `extern int snd_DesiredSfxDevice;`
  - `statusbaractive` (variable, line 141) `extern boolean statusbaractive;`
  - `automapactive` (variable, line 143) `extern boolean automapactive;`
  - `menuactive` (variable, line 144) `extern boolean menuactive;`
  - `paused` (variable, line 145) `extern boolean paused;`
  - `viewactive` (variable, line 148) `extern boolean viewactive;`
  - `nodrawers` (variable, line 150) `extern boolean nodrawers;`
  - `testcontrols` (variable, line 153) `extern boolean testcontrols;`
  - `testcontrols_mousespeed` (variable, line 154) `extern int testcontrols_mousespeed;`
  - `viewangleoffset` (variable, line 161) `extern int viewangleoffset;`
  - `consoleplayer` (variable, line 164) `extern int consoleplayer;`
  - `displayplayer` (variable, line 165) `extern int displayplayer;`
  - `totalkills` (variable, line 172) `extern int totalkills;`
  - `totalitems` (variable, line 173) `extern int totalitems;`
  - `totalsecret` (variable, line 174) `extern int totalsecret;`
  - `levelstarttic` (variable, line 177) `extern int levelstarttic;`
  - `leveltime` (variable, line 178) `extern int leveltime;`
  - `usergame` (variable, line 186) `extern boolean usergame;`
  - `demoplayback` (variable, line 189) `extern boolean demoplayback;`
  - `demorecording` (variable, line 190) `extern boolean demorecording;`
  - `lowres_turn` (variable, line 195) `extern boolean lowres_turn;`
  - `singledemo` (variable, line 198) `extern boolean singledemo;`
  - `gamestate` (variable, line 204) `extern gamestate_t gamestate;`
  - `players` (variable, line 220) `extern player_t players[MAXPLAYERS];`
  - `playeringame` (variable, line 223) `extern boolean playeringame[MAXPLAYERS];`
  - `deathmatchstarts` (variable, line 228) `extern mapthing_t deathmatchstarts[MAX_DM_STARTS];`
  - `deathmatch_p` (variable, line 229) `extern mapthing_t* deathmatch_p;`
  - `playerstarts` (variable, line 232) `extern mapthing_t playerstarts[MAXPLAYERS];`
  - `wminfo` (variable, line 236) `extern wbstartstruct_t wminfo;`
  - `savegamedir` (variable, line 249) `extern char * savegamedir;`
  - `basedefault` (variable, line 250) `extern char basedefault[1024];`
  - `precache` (variable, line 253) `extern boolean precache;`
  - `wipegamestate` (variable, line 258) `extern gamestate_t wipegamestate;`
  - `mouseSensitivity` (variable, line 260) `extern int mouseSensitivity;`
  - `bodyqueslot` (variable, line 262) `extern int bodyqueslot;`
  - `skyflatnum` (variable, line 269) `extern int skyflatnum;`
  - `rndindex` (variable, line 276) `extern int rndindex;`
  - `netcmds` (variable, line 278) `extern ticcmd_t *netcmds;`
  - `__D_STATE__` (macro, line 26) `#define __D_STATE__`
  - `logical_gamemission` (macro, line 69) `#define logical_gamemission`
  - `MAX_DM_STARTS` (macro, line 227) `#define MAX_DM_STARTS`
- Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomstat.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_maputl.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/p_telept.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/r_bsp.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_segs.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/doomtype.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `boolean` (type_alias, line 68) `typedef bool boolean;`
  - `byte` (type_alias, line 81) `typedef uint8_t byte;`
  - `__DOOMTYPE__` (macro, line 22) `#define __DOOMTYPE__`
  - `strcasecmp` (macro, line 30) `#define strcasecmp`
  - `strncasecmp` (macro, line 31) `#define strncasecmp`
  - `PACKEDATTR` (macro, line 50) `#define PACKEDATTR`
  - `PACKEDATTR` (macro, line 52) `#define PACKEDATTR`
  - `DIR_SEPARATOR` (macro, line 88) `#define DIR_SEPARATOR`
  - `DIR_SEPARATOR_S` (macro, line 89) `#define DIR_SEPARATOR_S`
  - `PATH_SEPARATOR` (macro, line 90) `#define PATH_SEPARATOR`
  - `DIR_SEPARATOR` (macro, line 94) `#define DIR_SEPARATOR`
  - `DIR_SEPARATOR_S` (macro, line 95) `#define DIR_SEPARATOR_S`
  - `PATH_SEPARATOR` (macro, line 96) `#define PATH_SEPARATOR`
  - `arrlen` (macro, line 100) `#define arrlen(array)`
- Imported by: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_mode.c`, `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/d_textur.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdata.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/dummy.c`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/gusconf.h`, `progs/doomgeneric/i_cdmus.c`, `progs/doomgeneric/i_endoom.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_scale.h`, `progs/doomgeneric/i_sound.c`, `progs/doomgeneric/i_sound.h`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_cheat.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/net_gui.h`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/sha1.h`, `progs/doomgeneric/sounds.c`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/tables.h`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_file.c`, `progs/doomgeneric/w_file.h`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.c`

## progs/doomgeneric/dstrings.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Depends on: `progs/doomgeneric/dstrings.h`

## progs/doomgeneric/dstrings.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `doom1_endmsg` (variable, line 37) `extern char *doom1_endmsg[];`
  - `doom2_endmsg` (variable, line 38) `extern char *doom2_endmsg[];`
  - `__DSTRINGS__` (macro, line 22) `#define __DSTRINGS__`
  - `SAVEGAMENAME` (macro, line 30) `#define SAVEGAMENAME`
  - `NUM_QUITMESSAGES` (macro, line 35) `#define NUM_QUITMESSAGES`
- Depends on: `progs/doomgeneric/d_englsh.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/dstrings.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/st_stuff.c`

## progs/doomgeneric/dummy.c
- Layer: utility
- Language: c
- Symbols:
  - `I_InitTimidityConfig` (function, line 43) `void I_InitTimidityConfig(void)`
- Depends on: `progs/doomgeneric/doomtype.h`

## progs/doomgeneric/f_finale.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `textscreen_t` (struct, line 60)
  - `castinfo_t` (struct, line 300)
  - `F_StartFinale` (function, line 108) `void F_StartFinale (void)`
  - `F_Responder` (function, line 160) `boolean F_Responder (event_t *event)`
  - `F_Ticker` (function, line 172) `void F_Ticker (void)`
  - `F_TextWrite` (function, line 227) `void F_TextWrite (void)`
  - `F_StartCast` (function, line 340) `void F_StartCast (void)`
  - `F_CastTicker` (function, line 358) `void F_CastTicker (void)`
  - `F_CastResponder` (function, line 465) `boolean F_CastResponder (event_t* ev)`
  - `F_CastPrint` (function, line 486) `void F_CastPrint (char* text)`
  - `F_CastDrawer` (function, line 541) `void F_CastDrawer (void)`
  - `F_DrawPatchCol` (function, line 572) `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
  - `F_BunnyScroll` (function, line 606) `void F_BunnyScroll (void)`
  - `F_ArtScreenDrawer` (function, line 661) `static void F_ArtScreenDrawer(void)`
  - `F_Drawer` (function, line 702) `void F_Drawer (void)`
  - `hu_font` (variable, line 224) `extern patch_t *hu_font[HU_FONTSIZE];`
  - `TEXTSPEED` (macro, line 57) `#define	TEXTSPEED`
  - `TEXTWAIT` (macro, line 58) `#define	TEXTWAIT`
- Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/f_finale.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `F_Ticker` (function, line 34) `void F_Ticker (void);`
  - `F_Drawer` (function, line 37) `void F_Drawer (void);`
  - `F_StartFinale` (function, line 40) `void F_StartFinale (void);`
  - `__F_FINALE__` (macro, line 21) `#define __F_FINALE__`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`

## progs/doomgeneric/f_wipe.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `wipe_shittyColMajorXform` (function, line 43) `void
wipe_shittyColMajorXform
( short*	array,
  int		width,
  int		height )`
  - `wipe_initColorXForm` (function, line 65) `int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doColorXForm` (function, line 75) `int
wipe_doColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitColorXForm` (function, line 121) `int
wipe_exitColorXForm
( int	width,
  int	height,
  int	ticks )`
  - `wipe_initMelt` (function, line 133) `int
wipe_initMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_doMelt` (function, line 164) `int
wipe_doMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_exitMelt` (function, line 219) `int
wipe_exitMelt
( int	width,
  int	height,
  int	ticks )`
  - `wipe_StartScreen` (function, line 231) `int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_EndScreen` (function, line 243) `int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )`
  - `wipe_ScreenWipe` (function, line 256) `int
wipe_ScreenWipe
( int	wipeno,
  int	x,
  int	y,
  int	width,
  int	height,
  int	ticks )`
- Depends on: `kernel/string.c`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/f_wipe.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/f_wipe.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `wipe_StartScreen` (function, line 39) `int wipe_StartScreen ( int x, int y, int width, int height );`
  - `wipe_EndScreen` (function, line 47) `int wipe_EndScreen ( int x, int y, int width, int height );`
  - `wipe_ScreenWipe` (function, line 55) `int wipe_ScreenWipe ( int wipeno, int x, int y, int width, int height, int ticks );`
  - `__F_WIPE_H__` (macro, line 21) `#define __F_WIPE_H__`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_wipe.c`

## progs/doomgeneric/g_game.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `G_CmdChecksum` (function, line 233) `int G_CmdChecksum (ticcmd_t* cmd)`
  - `WeaponSelectable` (function, line 244) `static boolean WeaponSelectable(weapontype_t weapon)`
  - `G_NextWeapon` (function, line 281) `static int G_NextWeapon(int direction)`
  - `G_BuildTiccmd` (function, line 322) `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)`
  - `G_DoLoadLevel` (function, line 603) `void G_DoLoadLevel (void)`
  - `SetJoyButtons` (function, line 675) `static void SetJoyButtons(unsigned int buttons_mask)`
  - `SetMouseButtons` (function, line 703) `static void SetMouseButtons(unsigned int buttons_mask)`
  - `G_Responder` (function, line 733) `boolean G_Responder (event_t* ev)`
  - `G_Ticker` (function, line 854) `void G_Ticker (void)`
  - `G_InitPlayer` (function, line 1039) `void G_InitPlayer (int player)`
  - `G_PlayerFinishLevel` (function, line 1051) `void G_PlayerFinishLevel (int player)`
  - `G_PlayerReborn` (function, line 1072) `void G_PlayerReborn (int player)`
  - `G_CheckSpot` (function, line 1116) `boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing )`
  - `G_DeathMatchSpawnPlayer` (function, line 1223) `void G_DeathMatchSpawnPlayer (int playernum)`
  - `G_DoReborn` (function, line 1250) `void G_DoReborn (int playernum)`
  - `G_ScreenShot` (function, line 1296) `void G_ScreenShot (void)`
  - `G_ExitLevel` (function, line 1328) `void G_ExitLevel (void)`
  - `G_SecretExitLevel` (function, line 1335) `void G_SecretExitLevel (void)`
  - `G_DoCompleted` (function, line 1346) `void G_DoCompleted (void)`
  - `G_WorldDone` (function, line 1494) `void G_WorldDone (void)`
  - `G_DoWorldDone` (function, line 1519) `void G_DoWorldDone (void)`
  - `G_LoadGame` (function, line 1539) `void G_LoadGame (char* name)`
  - `G_DoLoadGame` (function, line 1548) `void G_DoLoadGame (void)`
  - `G_SaveGame` (function, line 1601) `void
G_SaveGame
( int	slot,
  char*	description )`
  - `G_DoSaveGame` (function, line 1610) `void G_DoSaveGame (void)`
  - `G_DeferedInitNew` (function, line 1698) `void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map)`
  - `G_DoNewGame` (function, line 1710) `void G_DoNewGame (void)`
  - `G_InitNew` (function, line 1727) `void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map )`
  - `G_ReadDemoTiccmd` (function, line 1898) `void G_ReadDemoTiccmd (ticcmd_t* cmd)`
  - `IncreaseDemoBuffer` (function, line 1926) `static void IncreaseDemoBuffer(void)`
  - `G_WriteDemoTiccmd` (function, line 1956) `void G_WriteDemoTiccmd (ticcmd_t* cmd)`
  - `G_RecordDemo` (function, line 2010) `void G_RecordDemo (char *name)`
  - `G_VanillaVersionCode` (function, line 2040) `int G_VanillaVersionCode(void)`
  - `G_BeginRecording` (function, line 2058) `void G_BeginRecording (void)`
  - `G_DeferedPlayDemo` (function, line 2107) `void G_DeferedPlayDemo (char* name)`
  - `DemoVersionDescription` (function, line 2115) `static char *DemoVersionDescription(int version)`
  - `G_DoPlayDemo` (function, line 2152) `void G_DoPlayDemo (void)`
  - `G_TimeDemo` (function, line 2215) `void G_TimeDemo (char* name)`
  - `G_CheckDemoStatus` (function, line 2243) `boolean G_CheckDemoStatus (void)`
  - `G_DoVictory` (function, line 88) `void G_DoVictory (void);`
  - `P_SpawnPlayer` (function, line 1113) `void P_SpawnPlayer (mapthing_t* mthing);`
  - `R_ExecuteSetViewSize` (function, line 1535) `void R_ExecuteSetViewSize (void);`
  - `player_names` (variable, line 939) `extern char *player_names[4];`
  - `pagename` (variable, line 1326) `extern char* pagename;`
  - `setsizeneeded` (variable, line 1534) `extern boolean setsizeneeded;`
  - `SAVEGAMESIZE` (macro, line 76) `#define SAVEGAMESIZE`
  - `MAXPLMOVE` (macro, line 152) `#define MAXPLMOVE`
  - `TURBOTHRESHOLD` (macro, line 154) `#define TURBOTHRESHOLD`
  - `SLOWTURNTICS` (macro, line 193) `#define SLOWTURNTICS`
  - `NUMKEYS` (macro, line 195) `#define NUMKEYS`
  - `MAX_JOY_BUTTONS` (macro, line 196) `#define MAX_JOY_BUTTONS`
  - `BODYQUESIZE` (macro, line 225) `#define	BODYQUESIZE`
  - `VERSIONSIZE` (macro, line 1545) `#define VERSIONSIZE`
  - `DEMOMARKER` (macro, line 1895) `#define DEMOMARKER`
- Depends on: `kernel/string.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/deh_misc.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/p_setup.h`, `progs/doomgeneric/p_tick.h`, `progs/doomgeneric/r_data.h`, `progs/doomgeneric/r_sky.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/statdump.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/g_game.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `G_DeathMatchSpawnPlayer` (function, line 31) `void G_DeathMatchSpawnPlayer (int playernum);`
  - `G_InitNew` (function, line 33) `void G_InitNew (skill_t skill, int episode, int map);`
  - `G_DeferedInitNew` (function, line 38) `void G_DeferedInitNew (skill_t skill, int episode, int map);`
  - `G_DeferedPlayDemo` (function, line 40) `void G_DeferedPlayDemo (char* demo);`
  - `G_LoadGame` (function, line 44) `void G_LoadGame (char* name);`
  - `G_DoLoadGame` (function, line 46) `void G_DoLoadGame (void);`
  - `G_SaveGame` (function, line 49) `void G_SaveGame (int slot, char* description);`
  - `G_RecordDemo` (function, line 52) `void G_RecordDemo (char* name);`
  - `G_BeginRecording` (function, line 54) `void G_BeginRecording (void);`
  - `G_PlayDemo` (function, line 56) `void G_PlayDemo (char* name);`
  - `G_TimeDemo` (function, line 57) `void G_TimeDemo (char* name);`
  - `G_ExitLevel` (function, line 60) `void G_ExitLevel (void);`
  - `G_SecretExitLevel` (function, line 61) `void G_SecretExitLevel (void);`
  - `G_WorldDone` (function, line 63) `void G_WorldDone (void);`
  - `G_BuildTiccmd` (function, line 67) `void G_BuildTiccmd (ticcmd_t *cmd, int maketic);`
  - `G_Ticker` (function, line 69) `void G_Ticker (void);`
  - `G_ScreenShot` (function, line 72) `void G_ScreenShot (void);`
  - `G_DrawMouseSpeedBox` (function, line 74) `void G_DrawMouseSpeedBox(void);`
  - `G_VanillaVersionCode` (function, line 75) `int G_VanillaVersionCode(void);`
  - `vanilla_savegame_limit` (variable, line 77) `extern int vanilla_savegame_limit;`
  - `vanilla_demo_limit` (variable, line 78) `extern int vanilla_demo_limit;`
  - `__G_GAME__` (macro, line 21) `#define __G_GAME__`
- Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomdef.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/gusconf.c
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: c
- Symbols:
  - `gus_config_t` (struct, line 34)
  - `MappingIndex` (function, line 43) `static unsigned int MappingIndex(void)`
  - `SplitLine` (function, line 61) `static int SplitLine(char *line, char **fields, unsigned int max_fields)`
  - `ParseLine` (function, line 108) `static void ParseLine(gus_config_t *config, char *line)`
  - `ParseDMXConfig` (function, line 129) `static void ParseDMXConfig(char *dmxconf, gus_config_t *config)`
  - `FreeDMXConfig` (function, line 165) `static void FreeDMXConfig(gus_config_t *config)`
  - `ReadDMXConfig` (function, line 175) `static char *ReadDMXConfig(void)`
  - `WriteTimidityConfig` (function, line 197) `static boolean WriteTimidityConfig(char *path, gus_config_t *config)`
  - `GUS_WriteConfig` (function, line 244) `boolean GUS_WriteConfig(char *path)`
  - `MAX_INSTRUMENTS` (macro, line 32) `#define MAX_INSTRUMENTS`
- Depends on: `kernel/string.c`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/gusconf.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `gus_patch_path` (variable, line 23) `extern char *gus_patch_path;`
  - `gus_ram_kb` (variable, line 24) `extern unsigned int gus_ram_kb;`
  - `__GUSCONF_H__` (macro, line 19) `#define __GUSCONF_H__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/i_sound.c`


Next: [KB_doomgeneric_p4.md](KB_doomgeneric_p4.md)
