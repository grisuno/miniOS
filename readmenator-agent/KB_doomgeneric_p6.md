# Subsystem: doomgeneric (page 6 of 12)
Previous: [KB_doomgeneric_p5.md](KB_doomgeneric_p5.md)

## progs/doomgeneric/m_controls.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_BindBaseControls` (function, line 156) `void M_BindBaseControls(void);`
  - `M_BindHereticControls` (function, line 157) `void M_BindHereticControls(void);`
  - `M_BindHexenControls` (function, line 158) `void M_BindHexenControls(void);`
  - `M_BindStrifeControls` (function, line 159) `void M_BindStrifeControls(void);`
  - `M_BindWeaponControls` (function, line 160) `void M_BindWeaponControls(void);`
  - `M_BindMapControls` (function, line 161) `void M_BindMapControls(void);`
  - `M_BindMenuControls` (function, line 162) `void M_BindMenuControls(void);`
  - `M_BindChatControls` (function, line 163) `void M_BindChatControls(unsigned int num_players);`
  - `M_ApplyPlatformDefaults` (function, line 165) `void M_ApplyPlatformDefaults(void);`
  - `key_right` (variable, line 20) `extern int key_right;`
  - `key_left` (variable, line 21) `extern int key_left;`
  - `key_up` (variable, line 23) `extern int key_up;`
  - `key_down` (variable, line 24) `extern int key_down;`
  - `key_strafeleft` (variable, line 25) `extern int key_strafeleft;`
  - `key_straferight` (variable, line 26) `extern int key_straferight;`
  - `key_fire` (variable, line 27) `extern int key_fire;`
  - `key_use` (variable, line 28) `extern int key_use;`
  - `key_strafe` (variable, line 29) `extern int key_strafe;`
  - `key_speed` (variable, line 30) `extern int key_speed;`
  - `key_jump` (variable, line 32) `extern int key_jump;`
  - `key_flyup` (variable, line 34) `extern int key_flyup;`
  - `key_flydown` (variable, line 35) `extern int key_flydown;`
  - `key_flycenter` (variable, line 36) `extern int key_flycenter;`
  - `key_lookup` (variable, line 37) `extern int key_lookup;`
  - `key_lookdown` (variable, line 38) `extern int key_lookdown;`
  - `key_lookcenter` (variable, line 39) `extern int key_lookcenter;`
  - `key_invleft` (variable, line 40) `extern int key_invleft;`
  - `key_invright` (variable, line 41) `extern int key_invright;`
  - `key_useartifact` (variable, line 42) `extern int key_useartifact;`
  - `key_usehealth` (variable, line 45) `extern int key_usehealth;`
  - `key_invquery` (variable, line 46) `extern int key_invquery;`
  - `key_mission` (variable, line 47) `extern int key_mission;`
  - `key_invpop` (variable, line 48) `extern int key_invpop;`
  - `key_invkey` (variable, line 49) `extern int key_invkey;`
  - `key_invhome` (variable, line 50) `extern int key_invhome;`
  - `key_invend` (variable, line 51) `extern int key_invend;`
  - `key_invuse` (variable, line 52) `extern int key_invuse;`
  - `key_invdrop` (variable, line 53) `extern int key_invdrop;`
  - `key_message_refresh` (variable, line 55) `extern int key_message_refresh;`
  - `key_pause` (variable, line 56) `extern int key_pause;`
  - `key_multi_msg` (variable, line 58) `extern int key_multi_msg;`
  - `key_multi_msgplayer` (variable, line 59) `extern int key_multi_msgplayer[8];`
  - `key_weapon1` (variable, line 61) `extern int key_weapon1;`
  - `key_weapon2` (variable, line 62) `extern int key_weapon2;`
  - `key_weapon3` (variable, line 63) `extern int key_weapon3;`
  - `key_weapon4` (variable, line 64) `extern int key_weapon4;`
  - `key_weapon5` (variable, line 65) `extern int key_weapon5;`
  - `key_weapon6` (variable, line 66) `extern int key_weapon6;`
  - `key_weapon7` (variable, line 67) `extern int key_weapon7;`
  - `key_weapon8` (variable, line 68) `extern int key_weapon8;`
  - `key_arti_all` (variable, line 70) `extern int key_arti_all;`
  - `key_arti_health` (variable, line 71) `extern int key_arti_health;`
  - `key_arti_poisonbag` (variable, line 72) `extern int key_arti_poisonbag;`
  - `key_arti_blastradius` (variable, line 73) `extern int key_arti_blastradius;`
  - `key_arti_teleport` (variable, line 74) `extern int key_arti_teleport;`
  - `key_arti_teleportother` (variable, line 75) `extern int key_arti_teleportother;`
  - `key_arti_egg` (variable, line 76) `extern int key_arti_egg;`
  - `key_arti_invulnerability` (variable, line 77) `extern int key_arti_invulnerability;`
  - `key_demo_quit` (variable, line 79) `extern int key_demo_quit;`
  - `key_spy` (variable, line 80) `extern int key_spy;`
  - `key_prevweapon` (variable, line 81) `extern int key_prevweapon;`
  - `key_nextweapon` (variable, line 82) `extern int key_nextweapon;`
  - `key_map_north` (variable, line 84) `extern int key_map_north;`
  - `key_map_south` (variable, line 85) `extern int key_map_south;`
  - `key_map_east` (variable, line 86) `extern int key_map_east;`
  - `key_map_west` (variable, line 87) `extern int key_map_west;`
  - `key_map_zoomin` (variable, line 88) `extern int key_map_zoomin;`
  - `key_map_zoomout` (variable, line 89) `extern int key_map_zoomout;`
  - `key_map_toggle` (variable, line 90) `extern int key_map_toggle;`
  - `key_map_maxzoom` (variable, line 91) `extern int key_map_maxzoom;`
  - `key_map_follow` (variable, line 92) `extern int key_map_follow;`
  - `key_map_grid` (variable, line 93) `extern int key_map_grid;`
  - `key_map_mark` (variable, line 94) `extern int key_map_mark;`
  - `key_map_clearmark` (variable, line 95) `extern int key_map_clearmark;`
  - `key_menu_activate` (variable, line 99) `extern int key_menu_activate;`
  - `key_menu_up` (variable, line 100) `extern int key_menu_up;`
  - `key_menu_down` (variable, line 101) `extern int key_menu_down;`
  - `key_menu_left` (variable, line 102) `extern int key_menu_left;`
  - `key_menu_right` (variable, line 103) `extern int key_menu_right;`
  - `key_menu_back` (variable, line 104) `extern int key_menu_back;`
  - `key_menu_forward` (variable, line 105) `extern int key_menu_forward;`
  - `key_menu_confirm` (variable, line 106) `extern int key_menu_confirm;`
  - `key_menu_abort` (variable, line 107) `extern int key_menu_abort;`
  - `key_menu_help` (variable, line 109) `extern int key_menu_help;`
  - `key_menu_save` (variable, line 110) `extern int key_menu_save;`
  - `key_menu_load` (variable, line 111) `extern int key_menu_load;`
  - `key_menu_volume` (variable, line 112) `extern int key_menu_volume;`
  - `key_menu_detail` (variable, line 113) `extern int key_menu_detail;`
  - `key_menu_qsave` (variable, line 114) `extern int key_menu_qsave;`
  - `key_menu_endgame` (variable, line 115) `extern int key_menu_endgame;`
  - `key_menu_messages` (variable, line 116) `extern int key_menu_messages;`
  - `key_menu_qload` (variable, line 117) `extern int key_menu_qload;`
  - `key_menu_quit` (variable, line 118) `extern int key_menu_quit;`
  - `key_menu_gamma` (variable, line 119) `extern int key_menu_gamma;`
  - `key_menu_incscreen` (variable, line 121) `extern int key_menu_incscreen;`
  - `key_menu_decscreen` (variable, line 122) `extern int key_menu_decscreen;`
  - `key_menu_screenshot` (variable, line 123) `extern int key_menu_screenshot;`
  - `mousebfire` (variable, line 125) `extern int mousebfire;`
  - `mousebstrafe` (variable, line 126) `extern int mousebstrafe;`
  - `mousebforward` (variable, line 127) `extern int mousebforward;`
  - `mousebjump` (variable, line 129) `extern int mousebjump;`
  - `mousebstrafeleft` (variable, line 131) `extern int mousebstrafeleft;`
  - `mousebstraferight` (variable, line 132) `extern int mousebstraferight;`
  - `mousebbackward` (variable, line 133) `extern int mousebbackward;`
  - `mousebuse` (variable, line 134) `extern int mousebuse;`
  - `mousebprevweapon` (variable, line 136) `extern int mousebprevweapon;`
  - `mousebnextweapon` (variable, line 137) `extern int mousebnextweapon;`
  - `joybfire` (variable, line 139) `extern int joybfire;`
  - `joybstrafe` (variable, line 140) `extern int joybstrafe;`
  - `joybuse` (variable, line 141) `extern int joybuse;`
  - `joybspeed` (variable, line 142) `extern int joybspeed;`
  - `joybjump` (variable, line 144) `extern int joybjump;`
  - `joybstrafeleft` (variable, line 146) `extern int joybstrafeleft;`
  - `joybstraferight` (variable, line 147) `extern int joybstraferight;`
  - `joybprevweapon` (variable, line 149) `extern int joybprevweapon;`
  - `joybnextweapon` (variable, line 150) `extern int joybnextweapon;`
  - `joybmenu` (variable, line 152) `extern int joybmenu;`
  - `dclick_use` (variable, line 154) `extern int dclick_use;`
  - `__M_CONTROLS_H__` (macro, line 18) `#define __M_CONTROLS_H__`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`

## progs/doomgeneric/m_fixed.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `FixedMul` (function, line 34) `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
  - `FixedDiv` (function, line 47) `fixed_t FixedDiv(fixed_t a, fixed_t b)`
- Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_fixed.h`

## progs/doomgeneric/m_fixed.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `fixed_t` (type_alias, line 31) `typedef int fixed_t;`
  - `FixedMul` (function, line 34) `fixed_t FixedMul (fixed_t a, fixed_t b);`
  - `FixedDiv` (function, line 35) `fixed_t FixedDiv (fixed_t a, fixed_t b);`
  - `__M_FIXED__` (macro, line 21) `#define __M_FIXED__`
  - `FRACBITS` (macro, line 29) `#define FRACBITS`
  - `FRACUNIT` (macro, line 30) `#define FRACUNIT`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/info.c`, `progs/doomgeneric/m_bbox.h`, `progs/doomgeneric/m_fixed.c`, `progs/doomgeneric/p_mobj.h`, `progs/doomgeneric/p_pspr.h`, `progs/doomgeneric/r_defs.h`, `progs/doomgeneric/r_sky.c`, `progs/doomgeneric/tables.h`

## progs/doomgeneric/m_menu.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `menu_s` (struct, line 151)
  - `menuitem_t` (struct, line 133)
  - `numitems` (type_alias, line 148) `typedef struct menu_s { short numitems;`
  - `M_ReadSaveStrings` (function, line 503) `void M_ReadSaveStrings(void)`
  - `M_DrawLoad` (function, line 530) `void M_DrawLoad(void)`
  - `M_DrawSaveLoadBorder` (function, line 549) `void M_DrawSaveLoadBorder(int x,int y)`
  - `M_LoadSelect` (function, line 572) `void M_LoadSelect(int choice)`
  - `M_LoadGame` (function, line 585) `void M_LoadGame (int choice)`
  - `M_DrawSave` (function, line 601) `void M_DrawSave(void)`
  - `M_DoSave` (function, line 622) `void M_DoSave(int slot)`
  - `M_SaveSelect` (function, line 635) `void M_SaveSelect(int choice)`
  - `M_SaveGame` (function, line 650) `void M_SaveGame (int choice)`
  - `M_QuickSaveResponse` (function, line 672) `void M_QuickSaveResponse(int key)`
  - `M_QuickSave` (function, line 681) `void M_QuickSave(void)`
  - `M_QuickLoadResponse` (function, line 709) `void M_QuickLoadResponse(int key)`
  - `M_QuickLoad` (function, line 719) `void M_QuickLoad(void)`
  - `M_DrawReadThis1` (function, line 743) `void M_DrawReadThis1(void)`
  - `M_DrawReadThis2` (function, line 820) `void M_DrawReadThis2(void)`
  - `M_DrawSound` (function, line 834) `void M_DrawSound(void)`
  - `M_Sound` (function, line 845) `void M_Sound(int choice)`
  - `M_SfxVol` (function, line 850) `void M_SfxVol(int choice)`
  - `M_MusicVol` (function, line 867) `void M_MusicVol(int choice)`
  - `M_DrawMainMenu` (function, line 890) `void M_DrawMainMenu(void)`
  - `M_DrawNewGame` (function, line 902) `void M_DrawNewGame(void)`
  - `M_NewGame` (function, line 908) `void M_NewGame(int choice)`
  - `M_DrawEpisode` (function, line 930) `void M_DrawEpisode(void)`
  - `M_VerifyNightmare` (function, line 935) `void M_VerifyNightmare(int key)`
  - `M_ChooseSkill` (function, line 944) `void M_ChooseSkill(int choice)`
  - `M_Episode` (function, line 956) `void M_Episode(int choice)`
  - `M_DrawOptions` (function, line 987) `void M_DrawOptions(void)`
  - `M_Options` (function, line 1007) `void M_Options(int choice)`
  - `M_ChangeMessages` (function, line 1017) `void M_ChangeMessages(int choice)`
  - `M_EndGameResponse` (function, line 1035) `void M_EndGameResponse(int key)`
  - `M_EndGame` (function, line 1045) `void M_EndGame(int choice)`
  - `M_ReadThis` (function, line 1069) `void M_ReadThis(int choice)`
  - `M_ReadThis2` (function, line 1075) `void M_ReadThis2(int choice)`
  - `M_FinishReadThis` (function, line 1093) `void M_FinishReadThis(int choice)`
  - `M_QuitResponse` (function, line 1131) `void M_QuitResponse(int key)`
  - `M_SelectEndMessage` (function, line 1147) `static char *M_SelectEndMessage(void)`
  - `M_QuitDOOM` (function, line 1168) `void M_QuitDOOM(int choice)`
  - `M_ChangeSensitivity` (function, line 1179) `void M_ChangeSensitivity(int choice)`
  - `M_ChangeDetail` (function, line 1197) `void M_ChangeDetail(int choice)`
  - `M_SizeDisplay` (function, line 1213) `void M_SizeDisplay(int choice)`
  - `M_DrawThermo` (function, line 1244) `void
M_DrawThermo
( int	x,
  int	y,
  int	thermWidth,
  int	thermDot )`
  - `M_DrawEmptyCell` (function, line 1270) `void
M_DrawEmptyCell
( menu_t*	menu,
  int		item )`
  - `M_DrawSelCell` (function, line 1279) `void
M_DrawSelCell
( menu_t*	menu,
  int		item )`
  - `M_StartMessage` (function, line 1289) `void
M_StartMessage
( char*		string,
  void*		routine,
  boolean	input )`
  - `M_StopMessage` (function, line 1304) `void M_StopMessage(void)`
  - `M_StringWidth` (function, line 1315) `int M_StringWidth(char* string)`
  - `M_StringHeight` (function, line 1338) `int M_StringHeight(char* string)`
  - `M_WriteText` (function, line 1357) `void
M_WriteText
( int		x,
  int		y,
  char*		string)`
  - `IsNullKey` (function, line 1403) `static boolean IsNullKey(int key)`
  - `M_Responder` (function, line 1416) `boolean M_Responder (event_t* ev)`
  - `M_StartControlPanel` (function, line 1899) `void M_StartControlPanel (void)`
  - `M_DrawOPLDev` (function, line 1913) `static void M_DrawOPLDev(void)`
  - `M_Drawer` (function, line 1951) `void M_Drawer (void)`
  - `M_ClearMenus` (function, line 2041) `void M_ClearMenus (void)`
  - `M_SetupNextMenu` (function, line 2054) `void M_SetupNextMenu(menu_t *menudef)`
  - `M_Ticker` (function, line 2064) `void M_Ticker (void)`
  - `M_Init` (function, line 2077) `void M_Init (void)`
  - `M_StartGame` (function, line 193) `void M_StartGame(int choice);`
  - `I_OPL_DevMessages` (function, line 1915) `extern void I_OPL_DevMessages(char *, size_t);`
  - `hu_font` (variable, line 62) `extern patch_t* hu_font[HU_FONTSIZE];`
  - `message_dontfuckwithme` (variable, line 63) `extern boolean message_dontfuckwithme;`
  - `chat_on` (variable, line 65) `extern boolean chat_on;`
  - `sendpause` (variable, line 123) `extern boolean sendpause;`
  - `SKULLXOFF` (macro, line 120) `#define SKULLXOFF`
  - `LINEHEIGHT` (macro, line 121) `#define LINEHEIGHT`
- Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/m_menu.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_Ticker` (function, line 40) `void M_Ticker (void);`
  - `M_Drawer` (function, line 44) `void M_Drawer (void);`
  - `M_Init` (function, line 48) `void M_Init (void);`
  - `M_StartControlPanel` (function, line 52) `void M_StartControlPanel (void);`
  - `detailLevel` (variable, line 56) `extern int detailLevel;`
  - `screenblocks` (variable, line 57) `extern int screenblocks;`
  - `__M_MENU__` (macro, line 21) `#define __M_MENU__`
- Depends on: `progs/doomgeneric/d_event.h`
- Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/r_main.c`

## progs/doomgeneric/m_misc.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `M_MakeDirectory` (function, line 55) `void M_MakeDirectory(char *path)`
  - `M_FileExists` (function, line 66) `boolean M_FileExists(char *filename)`
  - `M_FileLength` (function, line 89) `long M_FileLength(FILE *handle)`
  - `M_WriteFile` (function, line 111) `boolean M_WriteFile(char *name, void *source, int length)`
  - `M_ReadFile` (function, line 135) `int M_ReadFile(char *name, byte **buffer)`
  - `M_TempFile` (function, line 166) `char *M_TempFile(char *s)`
  - `M_StrToInt` (function, line 189) `boolean M_StrToInt(const char *str, int *result)`
  - `M_ExtractFileBase` (function, line 197) `void M_ExtractFileBase(char *path, char *dest)`
  - `M_ForceUppercase` (function, line 242) `void M_ForceUppercase(char *text)`
  - `M_StrCaseStr` (function, line 258) `char *M_StrCaseStr(char *haystack, char *needle)`
  - `M_StringDuplicate` (function, line 291) `char *M_StringDuplicate(const char *orig)`
  - `M_StringReplace` (function, line 310) `char *M_StringReplace(const char *haystack, const char *needle,
                      const char ...`
  - `M_StringCopy` (function, line 372) `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)`
  - `M_StringConcat` (function, line 393) `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)`
  - `M_StringStartsWith` (function, line 408) `boolean M_StringStartsWith(const char *s, const char *prefix)`
  - `M_StringEndsWith` (function, line 416) `boolean M_StringEndsWith(const char *s, const char *suffix)`
  - `M_StringJoin` (function, line 425) `char *M_StringJoin(const char *s, ...)`
  - `M_vsnprintf` (function, line 481) `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)`
  - `M_snprintf` (function, line 507) `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)`
  - `M_OEMToUTF8` (function, line 519) `char *M_OEMToUTF8(const char *oem)`
  - `WIN32_LEAN_AND_MEAN` (macro, line 28) `#define WIN32_LEAN_AND_MEAN`
  - `vsnprintf` (macro, line 476) `#define vsnprintf`
- Depends on: `kernel/string.c`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/m_misc.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_ReadFile` (function, line 29) `int M_ReadFile(char *name, byte **buffer);`
  - `M_MakeDirectory` (function, line 30) `void M_MakeDirectory(char *dir);`
  - `M_TempFile` (function, line 31) `char *M_TempFile(char *s);`
  - `M_FileLength` (function, line 33) `long M_FileLength(FILE *handle);`
  - `M_ExtractFileBase` (function, line 35) `void M_ExtractFileBase(char *path, char *dest);`
  - `M_ForceUppercase` (function, line 36) `void M_ForceUppercase(char *text);`
  - `M_StrCaseStr` (function, line 37) `char *M_StrCaseStr(char *haystack, char *needle);`
  - `M_StringDuplicate` (function, line 38) `char *M_StringDuplicate(const char *orig);`
  - `M_StringReplace` (function, line 41) `char *M_StringReplace(const char *haystack, const char *needle, const char *replacement);`
  - `M_StringJoin` (function, line 43) `char *M_StringJoin(const char *s, ...);`
  - `M_vsnprintf` (function, line 46) `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);`
  - `M_snprintf` (function, line 47) `int M_snprintf(char *buf, size_t buf_len, const char *s, ...);`
  - `M_OEMToUTF8` (function, line 48) `char *M_OEMToUTF8(const char *ansi);`
  - `__M_MISC__` (macro, line 21) `#define __M_MISC__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_argv.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_controls.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_checksum.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/m_random.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `P_Random` (function, line 50) `int P_Random (void)`
  - `M_Random` (function, line 56) `int M_Random (void)`
  - `M_ClearRandom` (function, line 62) `void M_ClearRandom (void)`

## progs/doomgeneric/m_random.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `M_Random` (function, line 30) `int M_Random (void);`
  - `P_Random` (function, line 33) `int P_Random (void);`
  - `M_ClearRandom` (function, line 36) `void M_ClearRandom (void);`
  - `__M_RANDOM__` (macro, line 21) `#define __M_RANDOM__`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_enemy.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_map.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`

## progs/doomgeneric/memio.c
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: c
- Symbols:
  - `_MEMFILE` (struct, line 32)
  - `mem_fopen_read` (function, line 42) `MEMFILE *mem_fopen_read(void *buf, size_t buflen)`
  - `mem_fread` (function, line 58) `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_fopen_write` (function, line 90) `MEMFILE *mem_fopen_write(void)`
  - `mem_fwrite` (function, line 107) `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)`
  - `mem_get_buf` (function, line 143) `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)`
  - `mem_fclose` (function, line 149) `void mem_fclose(MEMFILE *stream)`
  - `mem_ftell` (function, line 159) `long mem_ftell(MEMFILE *stream)`
  - `mem_fseek` (function, line 164) `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)`
- Depends on: `kernel/string.c`, `progs/doomgeneric/memio.h`, `progs/doomgeneric/z_zone.h`

## progs/doomgeneric/memio.h
- Doc: Copyright(C) 1993-1996 Id Software, Inc.
- Layer: utility
- Language: h
- Symbols:
  - `MEMFILE` (type_alias, line 18) `typedef struct _MEMFILE MEMFILE;`
  - `mem_fopen_read` (function, line 28) `MEMFILE *mem_fopen_read(void *buf, size_t buflen);`
  - `mem_fread` (function, line 29) `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);`
  - `mem_fopen_write` (function, line 30) `MEMFILE *mem_fopen_write(void);`
  - `mem_fwrite` (function, line 31) `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);`
  - `mem_get_buf` (function, line 32) `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);`
  - `mem_fclose` (function, line 33) `void mem_fclose(MEMFILE *stream);`
  - `mem_ftell` (function, line 34) `long mem_ftell(MEMFILE *stream);`
  - `mem_fseek` (function, line 35) `int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);`
  - `MEMIO_H` (macro, line 17) `#define MEMIO_H`
- Imported by: `progs/doomgeneric/memio.c`

## progs/doomgeneric/net_client.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: infrastructure
- Language: h
- Symbols:
  - `NET_CL_Disconnect` (function, line 26) `void NET_CL_Disconnect(void);`
  - `NET_CL_Run` (function, line 27) `void NET_CL_Run(void);`
  - `NET_CL_Init` (function, line 28) `void NET_CL_Init(void);`
  - `NET_CL_LaunchGame` (function, line 29) `void NET_CL_LaunchGame(void);`
  - `NET_CL_StartGame` (function, line 30) `void NET_CL_StartGame(net_gamesettings_t *settings);`
  - `NET_CL_SendTiccmd` (function, line 31) `void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);`
  - `NET_Init` (function, line 33) `void NET_Init(void);`
  - `NET_BindVariables` (function, line 35) `void NET_BindVariables(void);`
  - `net_client_connected` (variable, line 37) `extern boolean net_client_connected;`
  - `net_client_received_wait_data` (variable, line 38) `extern boolean net_client_received_wait_data;`
  - `net_client_wait_data` (variable, line 39) `extern net_waitdata_t net_client_wait_data;`
  - `net_waiting_for_launch` (variable, line 40) `extern boolean net_waiting_for_launch;`
  - `net_player_name` (variable, line 41) `extern char *net_player_name;`
  - `net_server_wad_sha1sum` (variable, line 43) `extern sha1_digest_t net_server_wad_sha1sum;`
  - `net_server_deh_sha1sum` (variable, line 44) `extern sha1_digest_t net_server_deh_sha1sum;`
  - `net_server_is_freedoom` (variable, line 45) `extern unsigned int net_server_is_freedoom;`
  - `net_local_wad_sha1sum` (variable, line 46) `extern sha1_digest_t net_local_wad_sha1sum;`
  - `net_local_deh_sha1sum` (variable, line 47) `extern sha1_digest_t net_local_deh_sha1sum;`
  - `net_local_is_freedoom` (variable, line 48) `extern unsigned int net_local_is_freedoom;`
  - `drone` (variable, line 50) `extern boolean drone;`
  - `NET_CLIENT_H` (macro, line 18) `#define NET_CLIENT_H`
- Depends on: `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/net_defs.h`, `progs/doomgeneric/sha1.h`
- Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_main.c`

## progs/doomgeneric/net_dedicated.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `NET_DedicatedServer` (function, line 21) `void NET_DedicatedServer(void);`
  - `NET_DEDICATED_H` (macro, line 19) `#define NET_DEDICATED_H`
- Imported by: `progs/doomgeneric/d_main.c`

## progs/doomgeneric/net_defs.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `_net_packet_s` (struct, line 52)
  - `_net_module_s` (struct, line 60)
  - `_net_addr_s` (struct, line 95)
  - `net_connect_data_t` (struct, line 147)
  - `net_gamesettings_t` (struct, line 163)
  - `net_ticdiff_t` (struct, line 202)
  - `net_full_ticcmd_t` (struct, line 210)
  - `net_querydata_t` (struct, line 220)
  - `net_waitdata_t` (struct, line 233)
  - `net_module_t` (type_alias, line 46) `typedef struct _net_module_s net_module_t;`
  - `net_packet_t` (type_alias, line 48) `typedef struct _net_packet_s net_packet_t;`
  - `net_addr_t` (type_alias, line 49) `typedef struct _net_addr_s net_addr_t;`
  - `net_context_t` (type_alias, line 50) `typedef struct _net_context_s net_context_t;`
  - `NET_DEFS_H` (macro, line 19) `#define NET_DEFS_H`
  - `MAXNETNODES` (macro, line 31) `#define MAXNETNODES`
  - `NET_MAXPLAYERS` (macro, line 37) `#define NET_MAXPLAYERS`
  - `MAXPLAYERNAME` (macro, line 41) `#define MAXPLAYERNAME`
  - `BACKUPTICS` (macro, line 45) `#define BACKUPTICS`
  - `NET_MAGIC_NUMBER` (macro, line 103) `#define NET_MAGIC_NUMBER`
  - `NET_RELIABLE_PACKET` (macro, line 107) `#define NET_RELIABLE_PACKET`
  - `NET_TICDIFF_FORWARD` (macro, line 193) `#define NET_TICDIFF_FORWARD`
  - `NET_TICDIFF_SIDE` (macro, line 194) `#define NET_TICDIFF_SIDE`
  - `NET_TICDIFF_TURN` (macro, line 195) `#define NET_TICDIFF_TURN`
  - `NET_TICDIFF_BUTTONS` (macro, line 196) `#define NET_TICDIFF_BUTTONS`
  - `NET_TICDIFF_CONSISTANCY` (macro, line 197) `#define NET_TICDIFF_CONSISTANCY`
  - `NET_TICDIFF_CHATCHAR` (macro, line 198) `#define NET_TICDIFF_CHATCHAR`
  - `NET_TICDIFF_RAVEN` (macro, line 199) `#define NET_TICDIFF_RAVEN`
  - `NET_TICDIFF_STRIFE` (macro, line 200) `#define NET_TICDIFF_STRIFE`
- Depends on: `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sha1.h`
- Imported by: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_player.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_io.h`, `progs/doomgeneric/net_loop.h`, `progs/doomgeneric/net_packet.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/net_sdl.h`

## progs/doomgeneric/net_gui.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `NET_WaitForLaunch` (function, line 26) `extern void NET_WaitForLaunch(void);`
  - `NET_GUI_H` (macro, line 22) `#define NET_GUI_H`
- Depends on: `progs/doomgeneric/doomtype.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_io.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `NET_NewContext` (function, line 25) `net_context_t *NET_NewContext(void);`
  - `NET_AddModule` (function, line 26) `void NET_AddModule(net_context_t *context, net_module_t *module);`
  - `NET_SendPacket` (function, line 27) `void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);`
  - `NET_SendBroadcast` (function, line 28) `void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);`
  - `NET_AddrToString` (function, line 31) `char *NET_AddrToString(net_addr_t *addr);`
  - `NET_FreeAddress` (function, line 32) `void NET_FreeAddress(net_addr_t *addr);`
  - `NET_ResolveAddress` (function, line 33) `net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);`
  - `net_broadcast_addr` (variable, line 23) `extern net_addr_t net_broadcast_addr;`
  - `NET_IO_H` (macro, line 19) `#define NET_IO_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_loop.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `net_loop_client_module` (variable, line 23) `extern net_module_t net_loop_client_module;`
  - `net_loop_server_module` (variable, line 24) `extern net_module_t net_loop_server_module;`
  - `NET_LOOP_H` (macro, line 19) `#define NET_LOOP_H`
- Depends on: `progs/doomgeneric/net_defs.h`
- Imported by: `progs/doomgeneric/d_loop.c`

## progs/doomgeneric/net_packet.h
- Doc: Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it...
- Layer: utility
- Language: h
- Symbols:
  - `NET_NewPacket` (function, line 23) `net_packet_t *NET_NewPacket(int initial_size);`
  - `NET_PacketDup` (function, line 24) `net_packet_t *NET_PacketDup(net_packet_t *packet);`
  - `NET_FreePacket` (function, line 25) `void NET_FreePacket(net_packet_t *packet);`
  - `NET_ReadString` (function, line 35) `char *NET_ReadString(net_packet_t *packet);`
  - `NET_WriteInt8` (function, line 37) `void NET_WriteInt8(net_packet_t *packet, unsigned int i);`
  - `NET_WriteInt16` (function, line 38) `void NET_WriteInt16(net_packet_t *packet, unsigned int i);`
  - `NET_WriteInt32` (function, line 39) `void NET_WriteInt32(net_packet_t *packet, unsigned int i);`
  - `NET_WriteString` (function, line 41) `void NET_WriteString(net_packet_t *packet, char *string);`
  - `NET_PACKET_H` (macro, line 19) `#define NET_PACKET_H`
- Depends on: `progs/doomgeneric/net_defs.h`


Next: [KB_doomgeneric_p7.md](KB_doomgeneric_p7.md)
