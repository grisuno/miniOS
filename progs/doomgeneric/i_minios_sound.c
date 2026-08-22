#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doomtype.h"
#include "doomfeatures.h"
#include "i_sound.h"
#include "w_wad.h"
#include "z_zone.h"
#include "doomgeneric.h"

#define PCSPK_CHANNELS 4
#define PCSPK_TICK_MS 14

static snddevice_t pcspk_devices[] = { SNDDEVICE_PCSPEAKER };

typedef struct {
    sfxinfo_t *sfx;
    int active;
    int priority;
    unsigned freq;
    unsigned char *data;
    int datalen;
    int pos;
    unsigned note_end;
} pcspk_channel_t;

static pcspk_channel_t channels[PCSPK_CHANNELS];
static int pcspk_ready;
static boolean pcspk_sfx_prefix;

static long sys_tone(unsigned f) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(210),"D"((long)f):"rcx","r11","memory"); return r;
}
static long sys_time(void) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(204),"D"(0):"rcx","r11","memory"); return r;
}

static const unsigned short dp_freq_table[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    178, 181, 184, 187, 190, 193, 196, 199, 203, 206, 209, 212, 216, 219, 222, 226,
    230, 233, 237, 241, 245, 249, 253, 257, 261, 266, 270, 275, 279, 284, 289, 294,
    299, 304, 310, 315, 321, 327, 332, 339, 345, 351, 357, 364, 371, 377, 384, 392,
    399, 406, 414, 422, 430, 438, 446, 454, 463, 472, 481, 490, 500, 510, 520, 531,
    542, 553, 565, 577, 589, 602, 615, 628, 642, 656, 671, 686, 702, 718, 735, 752,
    770, 788, 807, 826, 846, 867, 889, 911, 934, 958, 982, 1007, 1033, 1059, 1087, 1115,
    1144, 1174, 1205, 1237, 1270, 1304, 1339, 1376, 1413, 1452, 1492, 1533, 1576, 1620, 1666, 1714,
    1763, 1814, 1867, 1922, 1979, 2038, 2100, 2164, 2230, 2299, 2371, 2446, 2524, 2605, 2690, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static boolean PCSPK_Init(boolean use_sfx_prefix) {
    pcspk_sfx_prefix = use_sfx_prefix;
    memset(channels, 0, sizeof(channels));
    pcspk_ready = 1;
    return true;
}

static void PCSPK_Shutdown(void) {
    sys_tone(0);
    pcspk_ready = 0;
}

static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx) {
    char n[16]; int l;
    if (pcspk_sfx_prefix) {
        snprintf(n, sizeof(n), "dp%s", sfx->name);
        l = W_CheckNumForName(n);
        if (l >= 0) return l;
    }
    snprintf(n, sizeof(n), "ds%s", sfx->name);
    return W_CheckNumForName(n);
}

static void free_channel(int i) {
    if (channels[i].data) {
        Z_Free(channels[i].data - 2);
        channels[i].data = 0;
    }
    channels[i].datalen = 0;
    channels[i].active = 0;
}

static void PCSPK_Update(void) {
    if (!pcspk_ready) return;
    int best = -1, bestpri = -1;
    unsigned now = (unsigned)sys_time();
    int i;
    for (i = 0; i < PCSPK_CHANNELS; i++) {
        if (!channels[i].active) continue;
        while (now >= channels[i].note_end) {
            channels[i].pos += 2;
            if (channels[i].pos + 1 >= channels[i].datalen) {
                channels[i].active = 0;
                break;
            }
            unsigned char fi = channels[i].data[channels[i].pos];
            if (fi == 0) {
                channels[i].active = 0;
                break;
            }
            unsigned char dv = channels[i].data[channels[i].pos + 1];
            if (dv == 0) dv = 1;
            channels[i].freq = dp_freq_table[fi];
            channels[i].note_end += dv * PCSPK_TICK_MS;
        }
        if (!channels[i].active) continue;
        if (channels[i].priority < bestpri) continue;
        best = i;
        bestpri = channels[i].priority;
    }
    if (best >= 0) sys_tone(channels[best].freq);
    else sys_tone(0);
}

static void PCSPK_UpdateSoundParams(int ch, int v, int s) {
    (void)ch; (void)v; (void)s;
}

static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep) {
    (void)vol; (void)sep;
    if (!pcspk_ready) return -1;
    int ch = channel % PCSPK_CHANNELS;
    if (ch < 0) ch = 0;
    if (channels[ch].active) free_channel(ch);

    channels[ch].active = 0;
    channels[ch].data = 0;
    channels[ch].datalen = 0;
    channels[ch].pos = 0;
    channels[ch].freq = 440;

    int lump = PCSPK_GetSfxLumpNum(sfx);
    if (lump >= 0) {
        int len = W_LumpLength(lump);
        if (len > 4 && len < 65536) {
            unsigned char *tmp = (unsigned char *)Z_Malloc(len, PU_STATIC, 0);
            if (tmp) {
                W_ReadLump(lump, tmp);
                unsigned char fi = tmp[2];
                unsigned char dv = tmp[3];
                if (fi != 0) {
                    if (dv == 0) dv = 1;
                    channels[ch].data = tmp + 2;
                    channels[ch].datalen = len - 2;
                    channels[ch].pos = 0;
                    channels[ch].freq = dp_freq_table[fi];
                    channels[ch].note_end = (unsigned)sys_time() + dv * PCSPK_TICK_MS;
                    channels[ch].active = 1;
                } else {
                    Z_Free(tmp);
                }
            }
        }
    }

    if (!channels[ch].active) {
        channels[ch].data = 0;
        channels[ch].freq = 440;
        channels[ch].note_end = (unsigned)sys_time() + 200;
        channels[ch].active = 1;
    }

    channels[ch].sfx = sfx;
    channels[ch].priority = sfx->priority;
    sys_tone(channels[ch].freq);
    return ch;
}

static void PCSPK_StopSound(int channel) {
    int ch = channel % PCSPK_CHANNELS;
    if (ch < 0) ch = 0;
    free_channel(ch);
}

static boolean PCSPK_SoundIsPlaying(int channel) {
    int ch = channel % PCSPK_CHANNELS;
    if (ch < 0) ch = 0;
    return channels[ch].active != 0;
}

static void PCSPK_CacheSounds(sfxinfo_t *s, int n) { (void)s; (void)n; }

sound_module_t sound_pcsound_module = {
    pcspk_devices, 1,
    PCSPK_Init, PCSPK_Shutdown, PCSPK_GetSfxLumpNum,
    PCSPK_Update, PCSPK_UpdateSoundParams,
    PCSPK_StartSound, PCSPK_StopSound, PCSPK_SoundIsPlaying,
    PCSPK_CacheSounds
};

sound_module_t sound_sdl_module = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

music_module_t music_opl_module = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

music_module_t music_sdl_module = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
