# Symbols (page 15 of 26)
Previous: [SYMBOLS_p14.md](SYMBOLS_p14.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `key_menu_volume` | variable | `progs/doomgeneric/m_controls.h:112` | `extern int key_menu_volume;` |
| `key_message_refresh` | variable | `progs/doomgeneric/m_controls.h:55` | `extern int key_message_refresh;` |
| `key_mission` | variable | `progs/doomgeneric/m_controls.h:47` | `extern int key_mission;` |
| `key_multi_msg` | variable | `progs/doomgeneric/m_controls.h:58` | `extern int key_multi_msg;` |
| `key_multi_msgplayer` | variable | `progs/doomgeneric/m_controls.h:59` | `extern int key_multi_msgplayer[8];` |
| `key_nextweapon` | variable | `progs/doomgeneric/m_controls.h:82` | `extern int key_nextweapon;` |
| `key_pause` | variable | `progs/doomgeneric/m_controls.h:56` | `extern int key_pause;` |
| `key_prevweapon` | variable | `progs/doomgeneric/m_controls.h:81` | `extern int key_prevweapon;` |
| `key_right` | variable | `progs/doomgeneric/m_controls.h:20` | `extern int key_right;` |
| `key_speed` | variable | `progs/doomgeneric/m_controls.h:30` | `extern int key_speed;` |
| `key_spy` | variable | `progs/doomgeneric/m_controls.h:80` | `extern int key_spy;` |
| `key_strafe` | variable | `progs/doomgeneric/m_controls.h:29` | `extern int key_strafe;` |
| `key_strafeleft` | variable | `progs/doomgeneric/m_controls.h:25` | `extern int key_strafeleft;` |
| `key_straferight` | variable | `progs/doomgeneric/m_controls.h:26` | `extern int key_straferight;` |
| `key_up` | variable | `progs/doomgeneric/m_controls.h:23` | `extern int key_up;` |
| `key_use` | variable | `progs/doomgeneric/m_controls.h:28` | `extern int key_use;` |
| `key_useartifact` | variable | `progs/doomgeneric/m_controls.h:42` | `extern int key_useartifact;` |
| `key_usehealth` | variable | `progs/doomgeneric/m_controls.h:45` | `extern int key_usehealth;` |
| `key_weapon1` | variable | `progs/doomgeneric/m_controls.h:61` | `extern int key_weapon1;` |
| `key_weapon2` | variable | `progs/doomgeneric/m_controls.h:62` | `extern int key_weapon2;` |
| `key_weapon3` | variable | `progs/doomgeneric/m_controls.h:63` | `extern int key_weapon3;` |
| `key_weapon4` | variable | `progs/doomgeneric/m_controls.h:64` | `extern int key_weapon4;` |
| `key_weapon5` | variable | `progs/doomgeneric/m_controls.h:65` | `extern int key_weapon5;` |
| `key_weapon6` | variable | `progs/doomgeneric/m_controls.h:66` | `extern int key_weapon6;` |
| `key_weapon7` | variable | `progs/doomgeneric/m_controls.h:67` | `extern int key_weapon7;` |
| `key_weapon8` | variable | `progs/doomgeneric/m_controls.h:68` | `extern int key_weapon8;` |
| `mousebbackward` | variable | `progs/doomgeneric/m_controls.h:133` | `extern int mousebbackward;` |
| `mousebfire` | variable | `progs/doomgeneric/m_controls.h:125` | `extern int mousebfire;` |
| `mousebforward` | variable | `progs/doomgeneric/m_controls.h:127` | `extern int mousebforward;` |
| `mousebjump` | variable | `progs/doomgeneric/m_controls.h:129` | `extern int mousebjump;` |
| `mousebnextweapon` | variable | `progs/doomgeneric/m_controls.h:137` | `extern int mousebnextweapon;` |
| `mousebprevweapon` | variable | `progs/doomgeneric/m_controls.h:136` | `extern int mousebprevweapon;` |
| `mousebstrafe` | variable | `progs/doomgeneric/m_controls.h:126` | `extern int mousebstrafe;` |
| `mousebstrafeleft` | variable | `progs/doomgeneric/m_controls.h:131` | `extern int mousebstrafeleft;` |
| `mousebstraferight` | variable | `progs/doomgeneric/m_controls.h:132` | `extern int mousebstraferight;` |
| `mousebuse` | variable | `progs/doomgeneric/m_controls.h:134` | `extern int mousebuse;` |
| `FixedDiv` | function | `progs/doomgeneric/m_fixed.c:47` | `fixed_t FixedDiv(fixed_t a, fixed_t b)` |
| `FixedMul` | function | `progs/doomgeneric/m_fixed.c:34` | `fixed_t FixedMul ( fixed_t	a,   fixed_t	b )` |
| `FRACBITS` | macro | `progs/doomgeneric/m_fixed.h:29` | `#define FRACBITS` |
| `FRACUNIT` | macro | `progs/doomgeneric/m_fixed.h:30` | `#define FRACUNIT` |
| `FixedDiv` | function | `progs/doomgeneric/m_fixed.h:35` | `fixed_t FixedDiv (fixed_t a, fixed_t b);` |
| `FixedMul` | function | `progs/doomgeneric/m_fixed.h:34` | `fixed_t FixedMul (fixed_t a, fixed_t b);` |
| `__M_FIXED__` | macro | `progs/doomgeneric/m_fixed.h:21` | `#define __M_FIXED__` |
| `fixed_t` | type_alias | `progs/doomgeneric/m_fixed.h:31` | `typedef int fixed_t;` |
| `I_OPL_DevMessages` | function | `progs/doomgeneric/m_menu.c:1915` | `extern void I_OPL_DevMessages(char *, size_t);` |
| `IsNullKey` | function | `progs/doomgeneric/m_menu.c:1403` | `static boolean IsNullKey(int key)` |
| `LINEHEIGHT` | macro | `progs/doomgeneric/m_menu.c:121` | `#define LINEHEIGHT` |
| `M_ChangeDetail` | function | `progs/doomgeneric/m_menu.c:1197` | `void M_ChangeDetail(int choice)` |
| `M_ChangeMessages` | function | `progs/doomgeneric/m_menu.c:1017` | `void M_ChangeMessages(int choice)` |
| `M_ChangeSensitivity` | function | `progs/doomgeneric/m_menu.c:1179` | `void M_ChangeSensitivity(int choice)` |
| `M_ChooseSkill` | function | `progs/doomgeneric/m_menu.c:944` | `void M_ChooseSkill(int choice)` |
| `M_ClearMenus` | function | `progs/doomgeneric/m_menu.c:2041` | `void M_ClearMenus (void)` |
| `M_DoSave` | function | `progs/doomgeneric/m_menu.c:622` | `void M_DoSave(int slot)` |
| `M_DrawEmptyCell` | function | `progs/doomgeneric/m_menu.c:1270` | `void M_DrawEmptyCell ( menu_t*	menu,   int		item )` |
| `M_DrawEpisode` | function | `progs/doomgeneric/m_menu.c:930` | `void M_DrawEpisode(void)` |
| `M_DrawLoad` | function | `progs/doomgeneric/m_menu.c:530` | `void M_DrawLoad(void)` |
| `M_DrawMainMenu` | function | `progs/doomgeneric/m_menu.c:890` | `void M_DrawMainMenu(void)` |
| `M_DrawNewGame` | function | `progs/doomgeneric/m_menu.c:902` | `void M_DrawNewGame(void)` |
| `M_DrawOPLDev` | function | `progs/doomgeneric/m_menu.c:1913` | `static void M_DrawOPLDev(void)` |
| `M_DrawOptions` | function | `progs/doomgeneric/m_menu.c:987` | `void M_DrawOptions(void)` |
| `M_DrawReadThis1` | function | `progs/doomgeneric/m_menu.c:743` | `void M_DrawReadThis1(void)` |
| `M_DrawReadThis2` | function | `progs/doomgeneric/m_menu.c:820` | `void M_DrawReadThis2(void)` |
| `M_DrawSave` | function | `progs/doomgeneric/m_menu.c:601` | `void M_DrawSave(void)` |
| `M_DrawSaveLoadBorder` | function | `progs/doomgeneric/m_menu.c:549` | `void M_DrawSaveLoadBorder(int x,int y)` |
| `M_DrawSelCell` | function | `progs/doomgeneric/m_menu.c:1279` | `void M_DrawSelCell ( menu_t*	menu,   int		item )` |
| `M_DrawSound` | function | `progs/doomgeneric/m_menu.c:834` | `void M_DrawSound(void)` |
| `M_DrawThermo` | function | `progs/doomgeneric/m_menu.c:1244` | `void M_DrawThermo ( int	x,   int	y,   int	thermWidth,   int	thermDot )` |
| `M_Drawer` | function | `progs/doomgeneric/m_menu.c:1951` | `void M_Drawer (void)` |
| `M_EndGame` | function | `progs/doomgeneric/m_menu.c:1045` | `void M_EndGame(int choice)` |
| `M_EndGameResponse` | function | `progs/doomgeneric/m_menu.c:1035` | `void M_EndGameResponse(int key)` |
| `M_Episode` | function | `progs/doomgeneric/m_menu.c:956` | `void M_Episode(int choice)` |
| `M_FinishReadThis` | function | `progs/doomgeneric/m_menu.c:1093` | `void M_FinishReadThis(int choice)` |
| `M_Init` | function | `progs/doomgeneric/m_menu.c:2077` | `void M_Init (void)` |
| `M_LoadGame` | function | `progs/doomgeneric/m_menu.c:585` | `void M_LoadGame (int choice)` |
| `M_LoadSelect` | function | `progs/doomgeneric/m_menu.c:572` | `void M_LoadSelect(int choice)` |
| `M_MusicVol` | function | `progs/doomgeneric/m_menu.c:867` | `void M_MusicVol(int choice)` |
| `M_NewGame` | function | `progs/doomgeneric/m_menu.c:908` | `void M_NewGame(int choice)` |
| `M_Options` | function | `progs/doomgeneric/m_menu.c:1007` | `void M_Options(int choice)` |
| `M_QuickLoad` | function | `progs/doomgeneric/m_menu.c:719` | `void M_QuickLoad(void)` |
| `M_QuickLoadResponse` | function | `progs/doomgeneric/m_menu.c:709` | `void M_QuickLoadResponse(int key)` |
| `M_QuickSave` | function | `progs/doomgeneric/m_menu.c:681` | `void M_QuickSave(void)` |
| `M_QuickSaveResponse` | function | `progs/doomgeneric/m_menu.c:672` | `void M_QuickSaveResponse(int key)` |
| `M_QuitDOOM` | function | `progs/doomgeneric/m_menu.c:1168` | `void M_QuitDOOM(int choice)` |
| `M_QuitResponse` | function | `progs/doomgeneric/m_menu.c:1131` | `void M_QuitResponse(int key)` |
| `M_ReadSaveStrings` | function | `progs/doomgeneric/m_menu.c:503` | `void M_ReadSaveStrings(void)` |
| `M_ReadThis` | function | `progs/doomgeneric/m_menu.c:1069` | `void M_ReadThis(int choice)` |
| `M_ReadThis2` | function | `progs/doomgeneric/m_menu.c:1075` | `void M_ReadThis2(int choice)` |
| `M_Responder` | function | `progs/doomgeneric/m_menu.c:1416` | `boolean M_Responder (event_t* ev)` |
| `M_SaveGame` | function | `progs/doomgeneric/m_menu.c:650` | `void M_SaveGame (int choice)` |
| `M_SaveSelect` | function | `progs/doomgeneric/m_menu.c:635` | `void M_SaveSelect(int choice)` |
| `M_SelectEndMessage` | function | `progs/doomgeneric/m_menu.c:1147` | `static char *M_SelectEndMessage(void)` |
| `M_SetupNextMenu` | function | `progs/doomgeneric/m_menu.c:2054` | `void M_SetupNextMenu(menu_t *menudef)` |
| `M_SfxVol` | function | `progs/doomgeneric/m_menu.c:850` | `void M_SfxVol(int choice)` |
| `M_SizeDisplay` | function | `progs/doomgeneric/m_menu.c:1213` | `void M_SizeDisplay(int choice)` |
| `M_Sound` | function | `progs/doomgeneric/m_menu.c:845` | `void M_Sound(int choice)` |
| `M_StartControlPanel` | function | `progs/doomgeneric/m_menu.c:1899` | `void M_StartControlPanel (void)` |
| `M_StartGame` | function | `progs/doomgeneric/m_menu.c:193` | `void M_StartGame(int choice);` |
| `M_StartMessage` | function | `progs/doomgeneric/m_menu.c:1289` | `void M_StartMessage ( char*		string,   void*		routine,   boolean	input )` |
| `M_StopMessage` | function | `progs/doomgeneric/m_menu.c:1304` | `void M_StopMessage(void)` |
| `M_StringHeight` | function | `progs/doomgeneric/m_menu.c:1338` | `int M_StringHeight(char* string)` |
| `M_StringWidth` | function | `progs/doomgeneric/m_menu.c:1315` | `int M_StringWidth(char* string)` |
| `M_Ticker` | function | `progs/doomgeneric/m_menu.c:2064` | `void M_Ticker (void)` |
| `M_VerifyNightmare` | function | `progs/doomgeneric/m_menu.c:935` | `void M_VerifyNightmare(int key)` |
| `M_WriteText` | function | `progs/doomgeneric/m_menu.c:1357` | `void M_WriteText ( int		x,   int		y,   char*		string)` |
| `SKULLXOFF` | macro | `progs/doomgeneric/m_menu.c:120` | `#define SKULLXOFF` |
| `chat_on` | variable | `progs/doomgeneric/m_menu.c:65` | `extern boolean chat_on;` |
| `hu_font` | variable | `progs/doomgeneric/m_menu.c:62` | `extern patch_t* hu_font[HU_FONTSIZE];` |
| `menu_s` | struct | `progs/doomgeneric/m_menu.c:151` | `` |
| `menuitem_t` | struct | `progs/doomgeneric/m_menu.c:133` | `` |
| `message_dontfuckwithme` | variable | `progs/doomgeneric/m_menu.c:63` | `extern boolean message_dontfuckwithme;` |
| `numitems` | type_alias | `progs/doomgeneric/m_menu.c:148` | `typedef struct menu_s { short numitems;` |
| `sendpause` | variable | `progs/doomgeneric/m_menu.c:123` | `extern boolean sendpause;` |
| `M_Drawer` | function | `progs/doomgeneric/m_menu.h:44` | `void M_Drawer (void);` |
| `M_Init` | function | `progs/doomgeneric/m_menu.h:48` | `void M_Init (void);` |
| `M_StartControlPanel` | function | `progs/doomgeneric/m_menu.h:52` | `void M_StartControlPanel (void);` |
| `M_Ticker` | function | `progs/doomgeneric/m_menu.h:40` | `void M_Ticker (void);` |
| `__M_MENU__` | macro | `progs/doomgeneric/m_menu.h:21` | `#define __M_MENU__` |
| `detailLevel` | variable | `progs/doomgeneric/m_menu.h:56` | `extern int detailLevel;` |
| `screenblocks` | variable | `progs/doomgeneric/m_menu.h:57` | `extern int screenblocks;` |
| `M_ExtractFileBase` | function | `progs/doomgeneric/m_misc.c:197` | `void M_ExtractFileBase(char *path, char *dest)` |
| `M_FileExists` | function | `progs/doomgeneric/m_misc.c:66` | `boolean M_FileExists(char *filename)` |
| `M_FileLength` | function | `progs/doomgeneric/m_misc.c:89` | `long M_FileLength(FILE *handle)` |
| `M_ForceUppercase` | function | `progs/doomgeneric/m_misc.c:242` | `void M_ForceUppercase(char *text)` |
| `M_MakeDirectory` | function | `progs/doomgeneric/m_misc.c:55` | `void M_MakeDirectory(char *path)` |
| `M_OEMToUTF8` | function | `progs/doomgeneric/m_misc.c:519` | `char *M_OEMToUTF8(const char *oem)` |
| `M_ReadFile` | function | `progs/doomgeneric/m_misc.c:135` | `int M_ReadFile(char *name, byte **buffer)` |
| `M_StrCaseStr` | function | `progs/doomgeneric/m_misc.c:258` | `char *M_StrCaseStr(char *haystack, char *needle)` |
| `M_StrToInt` | function | `progs/doomgeneric/m_misc.c:189` | `boolean M_StrToInt(const char *str, int *result)` |
| `M_StringConcat` | function | `progs/doomgeneric/m_misc.c:393` | `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)` |
| `M_StringCopy` | function | `progs/doomgeneric/m_misc.c:372` | `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)` |
| `M_StringDuplicate` | function | `progs/doomgeneric/m_misc.c:291` | `char *M_StringDuplicate(const char *orig)` |
| `M_StringEndsWith` | function | `progs/doomgeneric/m_misc.c:416` | `boolean M_StringEndsWith(const char *s, const char *suffix)` |
| `M_StringJoin` | function | `progs/doomgeneric/m_misc.c:425` | `char *M_StringJoin(const char *s, ...)` |
| `M_StringReplace` | function | `progs/doomgeneric/m_misc.c:310` | `char *M_StringReplace(const char *haystack, const char *needle,                       const char ...` |
| `M_StringStartsWith` | function | `progs/doomgeneric/m_misc.c:408` | `boolean M_StringStartsWith(const char *s, const char *prefix)` |
| `M_TempFile` | function | `progs/doomgeneric/m_misc.c:166` | `char *M_TempFile(char *s)` |
| `M_WriteFile` | function | `progs/doomgeneric/m_misc.c:111` | `boolean M_WriteFile(char *name, void *source, int length)` |
| `M_snprintf` | function | `progs/doomgeneric/m_misc.c:507` | `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)` |
| `M_vsnprintf` | function | `progs/doomgeneric/m_misc.c:481` | `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)` |
| `WIN32_LEAN_AND_MEAN` | macro | `progs/doomgeneric/m_misc.c:28` | `#define WIN32_LEAN_AND_MEAN` |
| `vsnprintf` | macro | `progs/doomgeneric/m_misc.c:476` | `#define vsnprintf` |
| `M_ExtractFileBase` | function | `progs/doomgeneric/m_misc.h:35` | `void M_ExtractFileBase(char *path, char *dest);` |
| `M_FileLength` | function | `progs/doomgeneric/m_misc.h:33` | `long M_FileLength(FILE *handle);` |
| `M_ForceUppercase` | function | `progs/doomgeneric/m_misc.h:36` | `void M_ForceUppercase(char *text);` |
| `M_MakeDirectory` | function | `progs/doomgeneric/m_misc.h:30` | `void M_MakeDirectory(char *dir);` |
| `M_OEMToUTF8` | function | `progs/doomgeneric/m_misc.h:48` | `char *M_OEMToUTF8(const char *ansi);` |
| `M_ReadFile` | function | `progs/doomgeneric/m_misc.h:29` | `int M_ReadFile(char *name, byte **buffer);` |
| `M_StrCaseStr` | function | `progs/doomgeneric/m_misc.h:37` | `char *M_StrCaseStr(char *haystack, char *needle);` |
| `M_StringDuplicate` | function | `progs/doomgeneric/m_misc.h:38` | `char *M_StringDuplicate(const char *orig);` |
| `M_StringJoin` | function | `progs/doomgeneric/m_misc.h:43` | `char *M_StringJoin(const char *s, ...);` |
| `M_StringReplace` | function | `progs/doomgeneric/m_misc.h:41` | `char *M_StringReplace(const char *haystack, const char *needle, const char *replacement);` |
| `M_TempFile` | function | `progs/doomgeneric/m_misc.h:31` | `char *M_TempFile(char *s);` |
| `M_snprintf` | function | `progs/doomgeneric/m_misc.h:47` | `int M_snprintf(char *buf, size_t buf_len, const char *s, ...);` |
| `M_vsnprintf` | function | `progs/doomgeneric/m_misc.h:46` | `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);` |
| `__M_MISC__` | macro | `progs/doomgeneric/m_misc.h:21` | `#define __M_MISC__` |
| `M_ClearRandom` | function | `progs/doomgeneric/m_random.c:62` | `void M_ClearRandom (void)` |
| `M_Random` | function | `progs/doomgeneric/m_random.c:56` | `int M_Random (void)` |
| `P_Random` | function | `progs/doomgeneric/m_random.c:50` | `int P_Random (void)` |
| `M_ClearRandom` | function | `progs/doomgeneric/m_random.h:36` | `void M_ClearRandom (void);` |
| `M_Random` | function | `progs/doomgeneric/m_random.h:30` | `int M_Random (void);` |
| `P_Random` | function | `progs/doomgeneric/m_random.h:33` | `int P_Random (void);` |
| `__M_RANDOM__` | macro | `progs/doomgeneric/m_random.h:21` | `#define __M_RANDOM__` |
| `_MEMFILE` | struct | `progs/doomgeneric/memio.c:32` | `` |
| `mem_fclose` | function | `progs/doomgeneric/memio.c:149` | `void mem_fclose(MEMFILE *stream)` |
| `mem_fopen_read` | function | `progs/doomgeneric/memio.c:42` | `MEMFILE *mem_fopen_read(void *buf, size_t buflen)` |
| `mem_fopen_write` | function | `progs/doomgeneric/memio.c:90` | `MEMFILE *mem_fopen_write(void)` |
| `mem_fread` | function | `progs/doomgeneric/memio.c:58` | `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)` |
| `mem_fseek` | function | `progs/doomgeneric/memio.c:164` | `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)` |
| `mem_ftell` | function | `progs/doomgeneric/memio.c:159` | `long mem_ftell(MEMFILE *stream)` |
| `mem_fwrite` | function | `progs/doomgeneric/memio.c:107` | `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)` |
| `mem_get_buf` | function | `progs/doomgeneric/memio.c:143` | `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)` |
| `MEMFILE` | type_alias | `progs/doomgeneric/memio.h:18` | `typedef struct _MEMFILE MEMFILE;` |
| `MEMIO_H` | macro | `progs/doomgeneric/memio.h:17` | `#define MEMIO_H` |
| `mem_fclose` | function | `progs/doomgeneric/memio.h:33` | `void mem_fclose(MEMFILE *stream);` |
| `mem_fopen_read` | function | `progs/doomgeneric/memio.h:28` | `MEMFILE *mem_fopen_read(void *buf, size_t buflen);` |
| `mem_fopen_write` | function | `progs/doomgeneric/memio.h:30` | `MEMFILE *mem_fopen_write(void);` |
| `mem_fread` | function | `progs/doomgeneric/memio.h:29` | `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);` |
| `mem_fseek` | function | `progs/doomgeneric/memio.h:35` | `int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);` |
| `mem_ftell` | function | `progs/doomgeneric/memio.h:34` | `long mem_ftell(MEMFILE *stream);` |
| `mem_fwrite` | function | `progs/doomgeneric/memio.h:31` | `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);` |
| `mem_get_buf` | function | `progs/doomgeneric/memio.h:32` | `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);` |
| `NET_BindVariables` | function | `progs/doomgeneric/net_client.h:35` | `void NET_BindVariables(void);` |
| `NET_CLIENT_H` | macro | `progs/doomgeneric/net_client.h:18` | `#define NET_CLIENT_H` |
| `NET_CL_Disconnect` | function | `progs/doomgeneric/net_client.h:26` | `void NET_CL_Disconnect(void);` |
| `NET_CL_Init` | function | `progs/doomgeneric/net_client.h:28` | `void NET_CL_Init(void);` |
| `NET_CL_LaunchGame` | function | `progs/doomgeneric/net_client.h:29` | `void NET_CL_LaunchGame(void);` |
| `NET_CL_Run` | function | `progs/doomgeneric/net_client.h:27` | `void NET_CL_Run(void);` |
| `NET_CL_SendTiccmd` | function | `progs/doomgeneric/net_client.h:31` | `void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);` |
| `NET_CL_StartGame` | function | `progs/doomgeneric/net_client.h:30` | `void NET_CL_StartGame(net_gamesettings_t *settings);` |
| `NET_Init` | function | `progs/doomgeneric/net_client.h:33` | `void NET_Init(void);` |
| `drone` | variable | `progs/doomgeneric/net_client.h:50` | `extern boolean drone;` |
| `net_client_connected` | variable | `progs/doomgeneric/net_client.h:37` | `extern boolean net_client_connected;` |
| `net_client_received_wait_data` | variable | `progs/doomgeneric/net_client.h:38` | `extern boolean net_client_received_wait_data;` |
| `net_client_wait_data` | variable | `progs/doomgeneric/net_client.h:39` | `extern net_waitdata_t net_client_wait_data;` |
| `net_local_deh_sha1sum` | variable | `progs/doomgeneric/net_client.h:47` | `extern sha1_digest_t net_local_deh_sha1sum;` |
| `net_local_is_freedoom` | variable | `progs/doomgeneric/net_client.h:48` | `extern unsigned int net_local_is_freedoom;` |
| `net_local_wad_sha1sum` | variable | `progs/doomgeneric/net_client.h:46` | `extern sha1_digest_t net_local_wad_sha1sum;` |
| `net_player_name` | variable | `progs/doomgeneric/net_client.h:41` | `extern char *net_player_name;` |
| `net_server_deh_sha1sum` | variable | `progs/doomgeneric/net_client.h:44` | `extern sha1_digest_t net_server_deh_sha1sum;` |
| `net_server_is_freedoom` | variable | `progs/doomgeneric/net_client.h:45` | `extern unsigned int net_server_is_freedoom;` |
| `net_server_wad_sha1sum` | variable | `progs/doomgeneric/net_client.h:43` | `extern sha1_digest_t net_server_wad_sha1sum;` |
| `net_waiting_for_launch` | variable | `progs/doomgeneric/net_client.h:40` | `extern boolean net_waiting_for_launch;` |
| `NET_DEDICATED_H` | macro | `progs/doomgeneric/net_dedicated.h:19` | `#define NET_DEDICATED_H` |
| `NET_DedicatedServer` | function | `progs/doomgeneric/net_dedicated.h:21` | `void NET_DedicatedServer(void);` |
| `BACKUPTICS` | macro | `progs/doomgeneric/net_defs.h:45` | `#define BACKUPTICS` |
| `MAXNETNODES` | macro | `progs/doomgeneric/net_defs.h:31` | `#define MAXNETNODES` |
| `MAXPLAYERNAME` | macro | `progs/doomgeneric/net_defs.h:41` | `#define MAXPLAYERNAME` |
| `NET_DEFS_H` | macro | `progs/doomgeneric/net_defs.h:19` | `#define NET_DEFS_H` |
| `NET_MAGIC_NUMBER` | macro | `progs/doomgeneric/net_defs.h:103` | `#define NET_MAGIC_NUMBER` |
| `NET_MAXPLAYERS` | macro | `progs/doomgeneric/net_defs.h:37` | `#define NET_MAXPLAYERS` |
| `NET_RELIABLE_PACKET` | macro | `progs/doomgeneric/net_defs.h:107` | `#define NET_RELIABLE_PACKET` |
| `NET_TICDIFF_BUTTONS` | macro | `progs/doomgeneric/net_defs.h:196` | `#define NET_TICDIFF_BUTTONS` |
| `NET_TICDIFF_CHATCHAR` | macro | `progs/doomgeneric/net_defs.h:198` | `#define NET_TICDIFF_CHATCHAR` |
| `NET_TICDIFF_CONSISTANCY` | macro | `progs/doomgeneric/net_defs.h:197` | `#define NET_TICDIFF_CONSISTANCY` |
| `NET_TICDIFF_FORWARD` | macro | `progs/doomgeneric/net_defs.h:193` | `#define NET_TICDIFF_FORWARD` |
| `NET_TICDIFF_RAVEN` | macro | `progs/doomgeneric/net_defs.h:199` | `#define NET_TICDIFF_RAVEN` |
| `NET_TICDIFF_SIDE` | macro | `progs/doomgeneric/net_defs.h:194` | `#define NET_TICDIFF_SIDE` |
| `NET_TICDIFF_STRIFE` | macro | `progs/doomgeneric/net_defs.h:200` | `#define NET_TICDIFF_STRIFE` |
| `NET_TICDIFF_TURN` | macro | `progs/doomgeneric/net_defs.h:195` | `#define NET_TICDIFF_TURN` |
| `_net_addr_s` | struct | `progs/doomgeneric/net_defs.h:95` | `` |
| `_net_module_s` | struct | `progs/doomgeneric/net_defs.h:60` | `` |
| `_net_packet_s` | struct | `progs/doomgeneric/net_defs.h:52` | `` |
| `net_addr_t` | type_alias | `progs/doomgeneric/net_defs.h:49` | `typedef struct _net_addr_s net_addr_t;` |
| `net_connect_data_t` | struct | `progs/doomgeneric/net_defs.h:147` | `` |
| `net_context_t` | type_alias | `progs/doomgeneric/net_defs.h:50` | `typedef struct _net_context_s net_context_t;` |
| `net_full_ticcmd_t` | struct | `progs/doomgeneric/net_defs.h:210` | `` |
| `net_gamesettings_t` | struct | `progs/doomgeneric/net_defs.h:163` | `` |
| `net_module_t` | type_alias | `progs/doomgeneric/net_defs.h:46` | `typedef struct _net_module_s net_module_t;` |
| `net_packet_t` | type_alias | `progs/doomgeneric/net_defs.h:48` | `typedef struct _net_packet_s net_packet_t;` |
| `net_querydata_t` | struct | `progs/doomgeneric/net_defs.h:220` | `` |
| `net_ticdiff_t` | struct | `progs/doomgeneric/net_defs.h:202` | `` |
| `net_waitdata_t` | struct | `progs/doomgeneric/net_defs.h:233` | `` |
| `NET_GUI_H` | macro | `progs/doomgeneric/net_gui.h:22` | `#define NET_GUI_H` |
| `NET_WaitForLaunch` | function | `progs/doomgeneric/net_gui.h:26` | `extern void NET_WaitForLaunch(void);` |
| `NET_AddModule` | function | `progs/doomgeneric/net_io.h:26` | `void NET_AddModule(net_context_t *context, net_module_t *module);` |
| `NET_AddrToString` | function | `progs/doomgeneric/net_io.h:31` | `char *NET_AddrToString(net_addr_t *addr);` |
| `NET_FreeAddress` | function | `progs/doomgeneric/net_io.h:32` | `void NET_FreeAddress(net_addr_t *addr);` |
| `NET_IO_H` | macro | `progs/doomgeneric/net_io.h:19` | `#define NET_IO_H` |
| `NET_NewContext` | function | `progs/doomgeneric/net_io.h:25` | `net_context_t *NET_NewContext(void);` |
| `NET_ResolveAddress` | function | `progs/doomgeneric/net_io.h:33` | `net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);` |
| `NET_SendBroadcast` | function | `progs/doomgeneric/net_io.h:28` | `void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);` |
| `NET_SendPacket` | function | `progs/doomgeneric/net_io.h:27` | `void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);` |
| `net_broadcast_addr` | variable | `progs/doomgeneric/net_io.h:23` | `extern net_addr_t net_broadcast_addr;` |
| `NET_LOOP_H` | macro | `progs/doomgeneric/net_loop.h:19` | `#define NET_LOOP_H` |
| `net_loop_client_module` | variable | `progs/doomgeneric/net_loop.h:23` | `extern net_module_t net_loop_client_module;` |
| `net_loop_server_module` | variable | `progs/doomgeneric/net_loop.h:24` | `extern net_module_t net_loop_server_module;` |
| `NET_FreePacket` | function | `progs/doomgeneric/net_packet.h:25` | `void NET_FreePacket(net_packet_t *packet);` |
| `NET_NewPacket` | function | `progs/doomgeneric/net_packet.h:23` | `net_packet_t *NET_NewPacket(int initial_size);` |
| `NET_PACKET_H` | macro | `progs/doomgeneric/net_packet.h:19` | `#define NET_PACKET_H` |
| `NET_PacketDup` | function | `progs/doomgeneric/net_packet.h:24` | `net_packet_t *NET_PacketDup(net_packet_t *packet);` |
| `NET_ReadString` | function | `progs/doomgeneric/net_packet.h:35` | `char *NET_ReadString(net_packet_t *packet);` |
| `NET_WriteInt16` | function | `progs/doomgeneric/net_packet.h:38` | `void NET_WriteInt16(net_packet_t *packet, unsigned int i);` |
| `NET_WriteInt32` | function | `progs/doomgeneric/net_packet.h:39` | `void NET_WriteInt32(net_packet_t *packet, unsigned int i);` |
| `NET_WriteInt8` | function | `progs/doomgeneric/net_packet.h:37` | `void NET_WriteInt8(net_packet_t *packet, unsigned int i);` |
| `NET_WriteString` | function | `progs/doomgeneric/net_packet.h:41` | `void NET_WriteString(net_packet_t *packet, char *string);` |
| `NET_FindLANServer` | function | `progs/doomgeneric/net_query.h:34` | `extern net_addr_t *NET_FindLANServer(void);` |
| `NET_LANQuery` | function | `progs/doomgeneric/net_query.h:31` | `extern void NET_LANQuery(void);` |
| `NET_MasterQuery` | function | `progs/doomgeneric/net_query.h:32` | `extern void NET_MasterQuery(void);` |
| `NET_QUERY_H` | macro | `progs/doomgeneric/net_query.h:19` | `#define NET_QUERY_H` |
| `NET_QueryAddress` | function | `progs/doomgeneric/net_query.h:33` | `extern void NET_QueryAddress(char *addr);` |
| `NET_Query_AddToMaster` | function | `progs/doomgeneric/net_query.h:39` | `extern void NET_Query_AddToMaster(net_addr_t *master_addr);` |
| `NET_Query_CheckAddedToMaster` | function | `progs/doomgeneric/net_query.h:40` | `extern boolean NET_Query_CheckAddedToMaster(boolean *result);` |
| `NET_Query_MasterResponse` | function | `progs/doomgeneric/net_query.h:41` | `extern void NET_Query_MasterResponse(net_packet_t *packet);` |
| `NET_Query_Poll` | function | `progs/doomgeneric/net_query.h:36` | `extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);` |
| `NET_Query_ResolveMaster` | function | `progs/doomgeneric/net_query.h:38` | `extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);` |
| `NET_StartLANQuery` | function | `progs/doomgeneric/net_query.h:28` | `extern int NET_StartLANQuery(void);` |
| `NET_StartMasterQuery` | function | `progs/doomgeneric/net_query.h:29` | `extern int NET_StartMasterQuery(void);` |
| `NET_SDL_H` | macro | `progs/doomgeneric/net_sdl.h:19` | `#define NET_SDL_H` |
| `net_sdl_module` | variable | `progs/doomgeneric/net_sdl.h:23` | `extern net_module_t net_sdl_module;` |
| `NET_SERVER_H` | macro | `progs/doomgeneric/net_server.h:18` | `#define NET_SERVER_H` |
| `NET_SV_AddModule` | function | `progs/doomgeneric/net_server.h:35` | `void NET_SV_AddModule(net_module_t *module);` |
| `NET_SV_Init` | function | `progs/doomgeneric/net_server.h:22` | `void NET_SV_Init(void);` |
| `NET_SV_RegisterWithMaster` | function | `progs/doomgeneric/net_server.h:39` | `void NET_SV_RegisterWithMaster(void);` |
| `NET_SV_Run` | function | `progs/doomgeneric/net_server.h:26` | `void NET_SV_Run(void);` |
| `NET_SV_Shutdown` | function | `progs/doomgeneric/net_server.h:31` | `void NET_SV_Shutdown(void);` |
| `EV_CeilingCrushStop` | function | `progs/doomgeneric/p_ceilng.c:303` | `int	EV_CeilingCrushStop(line_t	*line)` |
| `EV_DoCeiling` | function | `progs/doomgeneric/p_ceilng.c:161` | `int EV_DoCeiling ( line_t*	line,   ceiling_e	type )` |
| `P_ActivateInStasisCeiling` | function | `progs/doomgeneric/p_ceilng.c:280` | `void P_ActivateInStasisCeiling(line_t* line)` |
| `P_AddActiveCeiling` | function | `progs/doomgeneric/p_ceilng.c:240` | `void P_AddActiveCeiling(ceiling_t* c)` |
| `P_RemoveActiveCeiling` | function | `progs/doomgeneric/p_ceilng.c:259` | `void P_RemoveActiveCeiling(ceiling_t* c)` |
| `T_MoveCeiling` | function | `progs/doomgeneric/p_ceilng.c:45` | `void T_MoveCeiling (ceiling_t* ceiling)` |
| `EV_DoDoor` | function | `progs/doomgeneric/p_doors.c:252` | `int EV_DoDoor ( line_t*	line,   vldoor_e	type )` |
| `EV_DoLockedDoor` | function | `progs/doomgeneric/p_doors.c:195` | `int EV_DoLockedDoor ( line_t*	line,   vldoor_e	type,   mobj_t*	thing )` |
| `EV_SlidingDoor` | function | `progs/doomgeneric/p_doors.c:727` | `void EV_SlidingDoor ( line_t*	line,   mobj_t*	thing )` |
| `EV_VerticalDoor` | function | `progs/doomgeneric/p_doors.c:337` | `void EV_VerticalDoor ( line_t*	line,   mobj_t*	thing )` |
| `P_FindSlidingDoorType` | function | `progs/doomgeneric/p_doors.c:624` | `int P_FindSlidingDoorType(line_t*	line)` |
| `P_InitSlidingDoorFrames` | function | `progs/doomgeneric/p_doors.c:580` | `void P_InitSlidingDoorFrames(void)` |
| `P_SpawnDoorCloseIn30` | function | `progs/doomgeneric/p_doors.c:519` | `void P_SpawnDoorCloseIn30 (sector_t* sec)` |
| `P_SpawnDoorRaiseIn5Mins` | function | `progs/doomgeneric/p_doors.c:542` | `void P_SpawnDoorRaiseIn5Mins ( sector_t*	sec,   int		secnum )` |
| `T_SlidingDoor` | function | `progs/doomgeneric/p_doors.c:639` | `void T_SlidingDoor (slidedoor_t*	door)` |
| `T_VerticalDoor` | function | `progs/doomgeneric/p_doors.c:57` | `void T_VerticalDoor (vldoor_t* door)` |
| `A_BabyMetal` | function | `progs/doomgeneric/p_enemy.c:1769` | `void A_BabyMetal (mobj_t* mo)` |
| `A_BossDeath` | function | `progs/doomgeneric/p_enemy.c:1656` | `void A_BossDeath (mobj_t* mo)` |
| `A_BrainAwake` | function | `progs/doomgeneric/p_enemy.c:1811` | `void A_BrainAwake (mobj_t* mo)` |
| `A_BrainDie` | function | `progs/doomgeneric/p_enemy.c:1894` | `void A_BrainDie (mobj_t*	mo)` |
| `A_BrainExplode` | function | `progs/doomgeneric/p_enemy.c:1873` | `void A_BrainExplode (mobj_t* mo)` |
| `A_BrainPain` | function | `progs/doomgeneric/p_enemy.c:1841` | `void A_BrainPain (mobj_t*	mo)` |
| `A_BrainScream` | function | `progs/doomgeneric/p_enemy.c:1847` | `void A_BrainScream (mobj_t*	mo)` |
| `A_BrainSpit` | function | `progs/doomgeneric/p_enemy.c:1899` | `void A_BrainSpit (mobj_t*	mo)` |
| `A_BruisAttack` | function | `progs/doomgeneric/p_enemy.c:964` | `void A_BruisAttack (mobj_t* actor)` |
| `A_BspiAttack` | function | `progs/doomgeneric/p_enemy.c:883` | `void A_BspiAttack (mobj_t *actor)` |
| `A_CPosAttack` | function | `progs/doomgeneric/p_enemy.c:830` | `void A_CPosAttack (mobj_t* actor)` |
| `A_CPosRefire` | function | `progs/doomgeneric/p_enemy.c:850` | `void A_CPosRefire (mobj_t* actor)` |
| `A_Chase` | function | `progs/doomgeneric/p_enemy.c:657` | `void A_Chase (mobj_t*	actor)` |
| `A_CloseShotgun2` | function | `progs/doomgeneric/p_enemy.c:1797` | `void A_CloseShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_CyberAttack` | function | `progs/doomgeneric/p_enemy.c:954` | `void A_CyberAttack (mobj_t* actor)` |
| `A_Explode` | function | `progs/doomgeneric/p_enemy.c:1594` | `void A_Explode (mobj_t* thingy)` |
| `A_FaceTarget` | function | `progs/doomgeneric/p_enemy.c:767` | `void A_FaceTarget (mobj_t* actor)` |
| `A_Fall` | function | `progs/doomgeneric/p_enemy.c:1581` | `void A_Fall (mobj_t *actor)` |
| `A_FatAttack1` | function | `progs/doomgeneric/p_enemy.c:1346` | `void A_FatAttack1 (mobj_t* actor)` |
| `A_FatAttack2` | function | `progs/doomgeneric/p_enemy.c:1366` | `void A_FatAttack2 (mobj_t* actor)` |
| `A_FatAttack3` | function | `progs/doomgeneric/p_enemy.c:1385` | `void A_FatAttack3 (mobj_t*	actor)` |
| `A_FatRaise` | function | `progs/doomgeneric/p_enemy.c:1339` | `void A_FatRaise (mobj_t *actor)` |
| `A_Fire` | function | `progs/doomgeneric/p_enemy.c:1242` | `void A_Fire (mobj_t* actor)` |
| `A_FireCrackle` | function | `progs/doomgeneric/p_enemy.c:1236` | `void A_FireCrackle (mobj_t* actor)` |
| `A_HeadAttack` | function | `progs/doomgeneric/p_enemy.c:935` | `void A_HeadAttack (mobj_t* actor)` |
| `A_Hoof` | function | `progs/doomgeneric/p_enemy.c:1757` | `void A_Hoof (mobj_t* mo)` |
| `A_KeenDie` | function | `progs/doomgeneric/p_enemy.c:551` | `void A_KeenDie (mobj_t* mo)` |
| `A_LoadShotgun2` | function | `progs/doomgeneric/p_enemy.c:1784` | `void A_LoadShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_Look` | function | `progs/doomgeneric/p_enemy.c:589` | `void A_Look (mobj_t* actor)` |
| `A_Metal` | function | `progs/doomgeneric/p_enemy.c:1763` | `void A_Metal (mobj_t* mo)` |
| `A_OpenShotgun2` | function | `progs/doomgeneric/p_enemy.c:1776` | `void A_OpenShotgun2 ( player_t*	player,   pspdef_t*	psp )` |
| `A_Pain` | function | `progs/doomgeneric/p_enemy.c:1573` | `void A_Pain (mobj_t* actor)` |
| `A_PainAttack` | function | `progs/doomgeneric/p_enemy.c:1508` | `void A_PainAttack (mobj_t* actor)` |
| `A_PainDie` | function | `progs/doomgeneric/p_enemy.c:1518` | `void A_PainDie (mobj_t* actor)` |
| `A_PainShootSkull` | function | `progs/doomgeneric/p_enemy.c:1446` | `void A_PainShootSkull ( mobj_t*	actor,   angle_t	angle )` |
| `A_PlayerScream` | function | `progs/doomgeneric/p_enemy.c:1992` | `void A_PlayerScream (mobj_t* mo)` |
| `A_PosAttack` | function | `progs/doomgeneric/p_enemy.c:787` | `void A_PosAttack (mobj_t* actor)` |
| `A_ReFire` | function | `progs/doomgeneric/p_enemy.c:1792` | `void A_ReFire ( player_t* player, pspdef_t* psp );` |
| `A_SPosAttack` | function | `progs/doomgeneric/p_enemy.c:806` | `void A_SPosAttack (mobj_t* actor)` |
| `A_SargAttack` | function | `progs/doomgeneric/p_enemy.c:920` | `void A_SargAttack (mobj_t* actor)` |
| `A_Scream` | function | `progs/doomgeneric/p_enemy.c:1531` | `void A_Scream (mobj_t* actor)` |
| `A_SkelFist` | function | `progs/doomgeneric/p_enemy.c:1086` | `void A_SkelFist (mobj_t*	actor)` |
| `A_SkelMissile` | function | `progs/doomgeneric/p_enemy.c:987` | `void A_SkelMissile (mobj_t* actor)` |
| `A_SkelWhoosh` | function | `progs/doomgeneric/p_enemy.c:1078` | `void A_SkelWhoosh (mobj_t*	actor)` |
| `A_SkullAttack` | function | `progs/doomgeneric/p_enemy.c:1415` | `void A_SkullAttack (mobj_t* actor)` |
| `A_SpawnFly` | function | `progs/doomgeneric/p_enemy.c:1934` | `void A_SpawnFly (mobj_t* mo)` |
| `A_SpawnSound` | function | `progs/doomgeneric/p_enemy.c:1928` | `void A_SpawnSound (mobj_t* mo)` |
| `A_SpidRefire` | function | `progs/doomgeneric/p_enemy.c:867` | `void A_SpidRefire (mobj_t* actor)` |
| `A_StartFire` | function | `progs/doomgeneric/p_enemy.c:1230` | `void A_StartFire (mobj_t* actor)` |
| `A_Tracer` | function | `progs/doomgeneric/p_enemy.c:1006` | `void A_Tracer (mobj_t* actor)` |
| `A_TroopAttack` | function | `progs/doomgeneric/p_enemy.c:898` | `void A_TroopAttack (mobj_t* actor)` |
| `A_VileAttack` | function | `progs/doomgeneric/p_enemy.c:1298` | `void A_VileAttack (mobj_t* actor)` |
| `A_VileChase` | function | `progs/doomgeneric/p_enemy.c:1152` | `void A_VileChase (mobj_t* actor)` |
| `A_VileStart` | function | `progs/doomgeneric/p_enemy.c:1218` | `void A_VileStart (mobj_t* actor)` |
| `A_VileTarget` | function | `progs/doomgeneric/p_enemy.c:1273` | `void A_VileTarget (mobj_t*	actor)` |
| `A_XScream` | function | `progs/doomgeneric/p_enemy.c:1568` | `void A_XScream (mobj_t* actor)` |
| `CheckBossEnd` | function | `progs/doomgeneric/p_enemy.c:1605` | `static boolean CheckBossEnd(mobjtype_t motype)` |
| `FATSPREAD` | macro | `progs/doomgeneric/p_enemy.c:1337` | `#define	FATSPREAD` |
| `PIT_VileCheck` | function | `progs/doomgeneric/p_enemy.c:1114` | `boolean PIT_VileCheck (mobj_t*	thing)` |
| `P_CheckMeleeRange` | function | `progs/doomgeneric/p_enemy.c:167` | `boolean P_CheckMeleeRange (mobj_t*	actor)` |
| `P_CheckMissileRange` | function | `progs/doomgeneric/p_enemy.c:190` | `boolean P_CheckMissileRange (mobj_t* actor)` |
| `P_LookForPlayers` | function | `progs/doomgeneric/p_enemy.c:487` | `boolean P_LookForPlayers ( mobj_t*	actor,   boolean	allaround )` |

Next: [SYMBOLS_p16.md](SYMBOLS_p16.md)
