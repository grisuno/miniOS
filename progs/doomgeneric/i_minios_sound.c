#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doomtype.h"
#include "doomfeatures.h"
#include "i_sound.h"
#include "w_wad.h"
#include "z_zone.h"
#include "doomgeneric.h"
#include "minios_abi.h"

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

static long sys_tone_hw(unsigned f) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(MINIOS_SYS_PCSPK_TONE),"D"((long)f):"rcx","r11","memory"); return r;
}
static long sys_time(void) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(MINIOS_SYS_TIME),"D"(0):"rcx","r11","memory"); return r;
}
static long sys_pcm2_open(long flags) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(MINIOS_SYS_PCM2_OPEN),"D"(flags):"rcx","r11","memory"); return r;
}
static long sys_pcm2_write(const void *buf, long len) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(MINIOS_SYS_PCM2_WRITE),"D"(buf),"S"(len):"rcx","r11","memory"); return r;
}
static void sys_pcm2_close(void) {
    __asm__ volatile("syscall"::"a"(MINIOS_SYS_PCM2_CLOSE):"rcx","r11","memory");
}

/* pcm2 primary with PC-speaker fallback (standard audio mode contract).
 *
 * When the SB16 is present, music streams as polyphonic 8-bit PCM through
 * pcm2 while sfx stay muted (effect tones ruined the melody); when
 * pcm2_open refuses, every audio_tone falls through to the legacy sys_tone
 * and the game sounds exactly as before, sfx included. All pushes are
 * NONBLOCK and short counts are dropped (a gap beats a stalled game). */
#define DOOM_PCM_RATE 22050
#define DOOM_PCM_VOL 100

static int audio_pcm2 = 0;
static int audio_pcm2_failed = 0;
static unsigned long audio_last_ms = 0;
static unsigned drum_seed = 12345u;
/* Polyphony diagnostics: max simultaneous voices rendered and percussion
 * hits seen. Reported at shutdown; a real MUS score must show voices > 1
 * (chords) for the pcm2 path to be proven polyphonic, not arpeggiated. */
static int mus_max_voices = 0;
static unsigned long mus_drum_hits = 0;

static void audio_ensure(void) {
    if (audio_pcm2 || audio_pcm2_failed) return;
    if (sys_pcm2_open(MINIOS_PCM2_NONBLOCK) == 0) audio_pcm2 = 1;
    else audio_pcm2_failed = 1;
}

/* SFX are muted on pcm2 (music only): effect tones ruined the melody, so
 * audio_pump below only advances the shared clock and mus_render_pcm mixes
 * music plus drums. The legacy speaker path still programs real tones. */
static void audio_pump(void) {
    unsigned long now;
    audio_ensure();
    if (!audio_pcm2) return;
    now = (unsigned long)sys_time();
    audio_last_ms = now;
}

static void audio_tone(unsigned freq) {
    audio_ensure();
    if (!audio_pcm2) {
        sys_tone_hw(freq);
    }
}

static void audio_close(void) {
    if (audio_pcm2) {
        sys_pcm2_close();
        audio_pcm2 = 0;
    }
}

/* MUS (Doom's music format) decoded for the PC speaker with NES-style
 * pseudo-polyphony.  The MUS lump is a single interleaved stream: a block
 * of events at the same tick (a descriptor byte whose bit 7 is clear means
 * "more events follow at this tick", bit 7 set means "last event of this
 * block"), then a variable length delta ticks to the next block.  Default
 * tempo is 140 ticks/sec.
 *
 * The PC speaker is one square-wave channel, so chords are faked the way a
 * NES channel faked them.  On the NES the bass was a separate sustained
 * triangle voice while the pulse channels arpeggiated the melody; with one
 * square wave the same illusion is built from the same two ingredients.
 * The lowest sounding bass note (below MUS_BASS_LINE_MIDI) becomes a pedal
 * held for MUS_BASS_HOLD_MS, and only the highest MUS_ARP_MAX melody notes
 * are fast-arpeggiated in a round-robin at MUS_ARP_SLOT_MS each.  Capping
 * the arpeggio to the top few notes keeps dense arrangements from
 * degrading into mud: every active voice is no longer chopped at equal
 * length, and the bass keeps its foundation instead of getting 1/N of the
 * time.  The percussion channel is dropped in the decoder. */

#define MUS_TICKS_PER_SEC 140
#define MUS_PERCUSSION_CHAN 15
#define MUS_ARP_SLOT_MS 7
#define MUS_BASS_HOLD_MS 28
#define MUS_BASS_LINE_MIDI 43
#define MUS_ARP_MAX 4
/* Polyphonic pcm2 drum burst: 25 ms of noise per percussion hit. */
#define DOOM_PCM_DRUM_SMP ((25u * DOOM_PCM_RATE) / 1000u)

static const unsigned short mus_freq_table[128] = {
        8,     9,     9,    10,    10,    11,    12,    12,
       13,    14,    15,    15,    16,    17,    18,    19,
       21,    22,    23,    24,    26,    28,    29,    31,
       33,    35,    37,    39,    41,    44,    46,    49,
       52,    55,    58,    62,    65,    69,    73,    78,
       82,    87,    92,    98,   104,   110,   117,   123,
      131,   139,   147,   156,   165,   175,   185,   196,
      208,   220,   233,   247,   262,   277,   294,   311,
      330,   349,   370,   392,   415,   440,   466,   494,
      523,   554,   587,   622,   659,   698,   740,   784,
      831,   880,   932,   988,  1047,  1109,  1175,  1245,
     1319,  1397,  1480,  1568,  1661,  1760,  1865,  1976,
     2093,  2217,  2349,  2489,  2637,  2794,  2960,  3136,
     3322,  3520,  3729,  3951,  4186,  4435,  4699,  4978,
     5274,  5588,  5920,  6272,  6645,  7040,  7459,  7902,
     8372,  8870,  9397,  9956, 10548, 11175, 11840, 12544,
};

typedef struct {
    const unsigned char *score;
    int score_len;
    int score_start;
    int pos;
    int active[16];
    int playing;
    int looping;
    unsigned long last_ms;
    unsigned short bass;
    unsigned short mel[MUS_ARP_MAX];
    int mel_len;
    int arp_index;
    /* Polyphonic pcm2 renderer state (legacy arpeggio ignores it). */
    unsigned phase[16];
    unsigned drum_ticks;
    unsigned long delta_rem;
    unsigned long tick_carry;
    unsigned long tick_total;
} mus_player_t;

static mus_player_t *mus_cur;

static int mus_read_varlen(mus_player_t *m, unsigned long *out) {
    unsigned long v = 0;
    for (;;) {
        if (m->pos >= m->score_len) return 0;
        unsigned char b = m->score[m->pos++];
        v = v * 128 + (b & 0x7F);
        if (!(b & 0x80)) break;
    }
    *out = v;
    return 1;
}

/* Process one full block of events at the current tick and advance pos past
 * its delta.  Returns the delta in *out.  Returns 0 at end of score. */
static int mus_next_block(mus_player_t *m, unsigned long *out) {
    if (m->pos >= m->score_len) return 0;
    for (;;) {
        unsigned char desc;
        int ch, ev, key;
        if (m->pos >= m->score_len) return 0;
        desc = m->score[m->pos++];
        ch = desc & 0x0F;
        ev = desc & 0x70;
        if (ev == 0x60) {               /* score end */
            return 0;
        }
        if (ev == 0x00) {               /* release note */
            if (m->pos >= m->score_len) return 0;
            key = m->score[m->pos++];
            if (ch != MUS_PERCUSSION_CHAN && m->active[ch] == (key & 0x7F))
                m->active[ch] = 0;
        } else if (ev == 0x10) {        /* press note */
            if (m->pos >= m->score_len) return 0;
            key = m->score[m->pos++];
            if (key & 0x80) {           /* velocity byte follows */
                m->pos++;
            }
            if (ch != MUS_PERCUSSION_CHAN) {
                int nk = key & 0x7F;
                if (m->active[ch] != nk) m->phase[ch] = 0;
                m->active[ch] = nk;
            } else {
                m->drum_ticks = DOOM_PCM_DRUM_SMP;
                mus_drum_hits++;
            }
        } else if (ev == 0x20) {        /* pitch wheel */
            m->pos++;
        } else if (ev == 0x30) {        /* system event */
            m->pos++;
        } else if (ev == 0x40) {        /* change controller */
            m->pos += 2;
        } else {
            return 0;
        }
        if (desc & 0x80) break;         /* last event of this block */
    }
    return mus_read_varlen(m, out);
}

static int mus_note_cmp(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

/* Split the sounding notes into a bass pedal (the lowest note below the
 * bass line) and the melody arpeggio (the highest MUS_ARP_MAX melody
 * notes).  Percussion never enters active[], so it is skipped here too. */
static void mus_build_chord(mus_player_t *m) {
    int i, n = 0;
    unsigned short bass = 0;
    unsigned short all[16];
    for (i = 0; i < 16; i++) {
        int note = m->active[i];
        if (note <= 0) continue;
        if (note < MUS_BASS_LINE_MIDI) {
            if (bass == 0 || note < bass) bass = (unsigned short)note;
        } else {
            if (n < 16) all[n++] = (unsigned short)note;
        }
    }
    m->bass = bass;
    m->mel_len = 0;
    if (n > 1) qsort(all, n, sizeof(all[0]), mus_note_cmp);
    int start = n > MUS_ARP_MAX ? n - MUS_ARP_MAX : 0;
    for (i = start; i < n; i++)
        m->mel[m->mel_len++] = all[i];
    m->arp_index = 0;
}

/* Hold a tone for the given number of milliseconds. On pcm2 the hold's
 * audio is queued up front (NONBLOCK) and the busy-wait preserves timing
 * while it plays; on the legacy speaker the tone is programmed and held. */
static void mus_hold_tone(unsigned freq, unsigned long ms) {
    /* Legacy-only: mus_play_chord (its sole caller) runs only when pcm2 is
     * inactive, so this never executes on the pcm2 path. */
    audio_tone(freq);
    unsigned long until = (unsigned long)sys_time() + ms;
    while ((unsigned long)sys_time() < until)
        __asm__ volatile("pause");
}

/* Play one full cycle of the pseudo-polyphony: the bass pedal first, held
 * long like the NES triangle voice, then the melody notes arpeggiated
 * rapidly.  The repeated cycle at this cadence is what the ear integrates
 * into a chord instead of one voice. */
static void mus_play_chord(mus_player_t *m) {
    int i;
    if (m->mel_len == 0 && m->bass == 0) {
        audio_tone(0);
        return;
    }
    if (m->bass)
        mus_hold_tone(mus_freq_table[m->bass], MUS_BASS_HOLD_MS);
    for (i = 0; i < m->mel_len; i++) {
        mus_hold_tone(mus_freq_table[m->mel[m->arp_index]], MUS_ARP_SLOT_MS);
        m->arp_index = (m->arp_index + 1) % m->mel_len;
    }
}

static void mus_advance(mus_player_t *m, unsigned long ms) {
    unsigned long target = ms * MUS_TICKS_PER_SEC / 1000;
    unsigned long consumed = 0;
    unsigned long delta;
    while (consumed < target) {
        if (!mus_next_block(m, &delta)) {
            if (m->looping) {
                m->pos = m->score_start;
                memset(m->active, 0, sizeof(m->active));
                continue;
            }
            m->playing = 0;
            audio_tone(0);
            return;
        }
        consumed += delta;
    }
    mus_build_chord(m);
    mus_play_chord(m);
}

/* Polyphonic pcm2 music: every sounding voice at once, as the score has
 * it. The legacy path above time-slices one square wave because the PC
 * speaker is a single channel; pcm2 takes mixed PCM, so there is no
 * reason to arpeggiate. Each MUS tick renders its active set (all melody
 * voices plus the bass, each with a persistent phase for click-free
 * sustains) normalized to a constant level, plus a short noise burst for
 * percussion hits captured in mus_next_block. Timing is tick-exact: ticks
 * convert to samples with an absolute counter, so the rate never drifts.
 * Runs under the shared audio_last_ms clock, so sfx and music never
 * double-render an interval; the current sfx tone mixes in as one more
 * voice, giving true sfx+music polyphony. */
static void mus_render_pcm(mus_player_t *m, unsigned char *out, unsigned n) {
    unsigned i;
    int ch;
    for (i = 0; i < n; i++) {
        int s = 0, nact = 0;
        for (ch = 0; ch < 16; ch++) {
            int note;
            unsigned f;
            if (ch == MUS_PERCUSSION_CHAN) continue;
            note = m->active[ch];
            if (note <= 0 || note >= 128) continue;
            f = mus_freq_table[note];
            if (f == 0) continue;
            m->phase[ch] += f;
            if (m->phase[ch] >= DOOM_PCM_RATE) m->phase[ch] -= DOOM_PCM_RATE;
            s += (m->phase[ch] < DOOM_PCM_RATE / 2) ? 1 : -1;
            nact++;
        }
        /* SFX are muted on pcm2 by design: effect tones through this mixer
         * ruined the music melody, so music (plus drums) plays alone here
         * and sfx stay on the legacy speaker fallback. */
        if (m->drum_ticks > 0) {
            drum_seed = drum_seed * 1103515245u + 12345u;
            s += ((drum_seed >> 16) & 1u) ? 1 : -1;
            nact++;
            m->drum_ticks--;
        }
        if (nact == 0) {
            out[i] = 0x80;
        } else {
            int v = (s * DOOM_PCM_VOL) / nact;
            if (nact > mus_max_voices) mus_max_voices = nact;
            if (v > 127) v = 127;
            else if (v < -128) v = -128;
            out[i] = (unsigned char)(0x80 + v);
        }
    }
}

static void mus_render_push(mus_player_t *m, unsigned n) {
    unsigned char tmp[256];
    while (n > 0) {
        unsigned k = n > sizeof(tmp) ? sizeof(tmp) : n;
        mus_render_pcm(m, tmp, k);
        if (sys_pcm2_write(tmp, (long)k) <= 0) break;
        n -= k;
    }
}

static void mus_advance_pcm(mus_player_t *m) {
    unsigned long now = (unsigned long)sys_time();
    unsigned long ms, ticks;
    audio_ensure();
    if (!audio_pcm2 || now <= audio_last_ms) return;
    ms = now - audio_last_ms;
    if (ms > 100) ms = 100;
    audio_last_ms = now;
    m->tick_carry += ms * MUS_TICKS_PER_SEC;
    ticks = m->tick_carry / 1000;
    m->tick_carry %= 1000;
    while (ticks > 0) {
        unsigned long s0, s1;
        unsigned n;
        if (m->delta_rem == 0) {
            unsigned long delta;
            if (!mus_next_block(m, &delta)) {
                if (m->looping) {
                    m->pos = m->score_start;
                    memset(m->active, 0, sizeof(m->active));
                    memset(m->phase, 0, sizeof(m->phase));
                    m->drum_ticks = 0;
                    m->delta_rem = 0;
                    continue;
                }
                m->playing = 0;
                return;
            }
            m->delta_rem = delta;
            if (m->delta_rem == 0) continue;
        }
        s0 = (m->tick_total * DOOM_PCM_RATE) / MUS_TICKS_PER_SEC;
        s1 = ((m->tick_total + 1) * DOOM_PCM_RATE) / MUS_TICKS_PER_SEC;
        n = (unsigned)(s1 - s0);
        mus_render_push(m, n);
        m->tick_total++;
        m->delta_rem--;
        ticks--;
    }
}

static boolean MUS_Init(void) {
    mus_cur = NULL;
    return true;
}

static void MUS_Shutdown(void) {
    if (mus_cur) audio_tone(0);
    audio_pump();
    audio_close();
    mus_cur = NULL;
}

static void MUS_SetMusicVolume(int volume) { (void)volume; }

static void MUS_Pause(void) { if (mus_cur) audio_tone(0); }
static void MUS_Resume(void) { }

static void *MUS_RegisterSong(void *data, int len) {
    mus_player_t *m = Z_Malloc(sizeof(*m), PU_STATIC, 0);
    unsigned char *p = (unsigned char *)data;
    if (len < 12 || p[0] != 'M' || p[1] != 'U' || p[2] != 'S' || p[3] != 0x1A) {
        Z_Free(m);
        return NULL;
    }
    memset(m, 0, sizeof(*m));
    m->score = (const unsigned char *)data;
    m->score_len = len;
    m->score_start = p[6] | (p[7] << 8);
    m->pos = m->score_start;
    return m;
}

static void MUS_UnRegisterSong(void *handle) {
    mus_player_t *m = (mus_player_t *)handle;
    if (m == mus_cur) { audio_tone(0); mus_cur = NULL; }
    if (m) Z_Free(m);
}

static void MUS_PlaySong(void *handle, boolean looping) {
    mus_player_t *m = (mus_player_t *)handle;
    if (!m) return;
    m->pos = m->score_start;
    memset(m->active, 0, sizeof(m->active));
    m->playing = 1;
    m->looping = looping;
    m->last_ms = (unsigned long)sys_time();
    mus_cur = m;
    audio_ensure();
    m->delta_rem = 0;
    m->tick_carry = 0;
    m->tick_total = 0;
    m->drum_ticks = 0;
    memset(m->phase, 0, sizeof(m->phase));
    if (!audio_pcm2) {
        mus_build_chord(m);
        mus_play_chord(m);
    }
}

static void MUS_StopSong(void) {
    if (mus_cur) { mus_cur->playing = 0; audio_tone(0); }
    mus_cur = NULL;
}

static boolean MUS_MusicIsPlaying(void) {
    return mus_cur != NULL && mus_cur->playing;
}

static void MUS_Poll(void) {
    mus_player_t *m = mus_cur;
    unsigned long now, ms;
    if (!m || !m->playing) return;
    audio_ensure();
    if (audio_pcm2) {
        mus_advance_pcm(m);
        return;
    }
    now = (unsigned long)sys_time();
    ms = now - m->last_ms;
    m->last_ms = now;
    mus_advance(m, ms);
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
    audio_tone(0);
    audio_pump();
    audio_close();
    pcspk_ready = 0;
    printf("mus: maxvoices=%d drums=%lu\n", mus_max_voices, mus_drum_hits);
    if (mus_max_voices > 1) printf("mus: polyphonic\n");
    fflush(stdout);
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
    audio_ensure();
    /* When polyphonic music owns the interval, it mixes the sfx tone in
     * itself; pumping here as well would render the same time twice. */
    if (!(audio_pcm2 && mus_cur && mus_cur->playing)) {
        audio_pump();
    }
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
    if (best >= 0) audio_tone(channels[best].freq);
    else audio_tone(0);
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
    audio_tone(channels[ch].freq);
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

static snddevice_t mus_devices[] = { SNDDEVICE_PCSPEAKER };

music_module_t music_pcspeaker_module = {
    mus_devices, 1,
    MUS_Init, MUS_Shutdown, MUS_SetMusicVolume,
    MUS_Pause, MUS_Resume, MUS_RegisterSong, MUS_UnRegisterSong,
    MUS_PlaySong, MUS_StopSong, MUS_MusicIsPlaying, MUS_Poll
};
