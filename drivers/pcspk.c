#include "kernel.h"
#include "pcspk.h"
#include "driver.h"

/* PC speaker driver with a software master volume. The speaker has no
 * hardware amplitude, so the volume control is a mute at PCSPK_VOL_MIN and
 * full output above it: PIT channel 2 runs the tone as a fixed square wave
 * and port 0x61 bits 0 and 1 (speaker data and gate) must both be high for
 * the PIT2 output to reach the speaker. Opening the gate directly keeps the
 * default-volume path byte-for-byte identical to the pre-volume driver so a
 * tone always sounds; volume 0 keeps the gate closed (silence). Every
 * constant is named. */

#define PIT_CH2_DATA      0x42
#define PIT_CH2_CMD       0x43
#define SPEAKER_PORT      0x61
#define PIT_FREQ          1193182u

#define PCSPK_MIN_FREQ    20
#define PCSPK_MAX_FREQ    20000

#define SPEAKER_DATA_BIT   0x01
#define SPEAKER_GATE_BIT   0x02
#define SPEAKER_ENABLE_BITS (SPEAKER_DATA_BIT | SPEAKER_GATE_BIT)

static unsigned pcspk_volume = PCSPK_VOL_DEFAULT;

void pcspk_tone(unsigned freq);
void pcspk_off(void);
void pcspk_set_volume(unsigned volume);
unsigned pcspk_get_volume(void);

static void pcspk_ops_tone(device_t *dev, unsigned freq) {
    (void)dev;
    pcspk_tone(freq);
}

static void pcspk_ops_off(device_t *dev) {
    (void)dev;
    pcspk_off();
}

static void pcspk_ops_set_volume(device_t *dev, unsigned vol) {
    (void)dev;
    pcspk_set_volume(vol);
}

static unsigned pcspk_ops_get_volume(device_t *dev) {
    (void)dev;
    return pcspk_get_volume();
}

static const audio_ops_t pcspk_audio_ops = {
    .tone = pcspk_ops_tone,
    .off = pcspk_ops_off,
    .set_volume = pcspk_ops_set_volume,
    .get_volume = pcspk_ops_get_volume,
    .present = 0,
    .pcm_open = 0,
    .pcm_close = 0,
    .pcm_submit = 0,
};

static device_t pcspk_device = {
    "pcspk0",
    DEV_TYPE_AUDIO,
    0,
    &pcspk_audio_ops,
    0,
};

void pcspk_init(void) {
    pcspk_volume = PCSPK_VOL_DEFAULT;
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);
    device_register(&pcspk_device);
}

void pcspk_set_volume(unsigned volume) {
    pcspk_volume = (volume > PCSPK_VOL_MAX) ? PCSPK_VOL_MAX : volume;
}

unsigned pcspk_get_volume(void) {
    return pcspk_volume;
}

void pcspk_tone(unsigned freq) {
    unsigned divisor;
    if (freq == 0) {
        pcspk_off();
        return;
    }
    if (freq < PCSPK_MIN_FREQ) freq = PCSPK_MIN_FREQ;
    if (freq > PCSPK_MAX_FREQ) freq = PCSPK_MAX_FREQ;
    divisor = PIT_FREQ / freq;
    outb(PIT_CH2_CMD, 0xB6);
    outb(PIT_CH2_DATA, divisor & 0xFF);
    outb(PIT_CH2_DATA, (divisor >> 8) & 0xFF);
    /* A muted speaker keeps both bits low; otherwise open the gate exactly as
     * the pre-volume driver did so the tone reaches the speaker. */
    if (pcspk_volume != PCSPK_VOL_MIN)
        outb(SPEAKER_PORT, inb(SPEAKER_PORT) | SPEAKER_ENABLE_BITS);
}

void pcspk_off(void) {
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);
}
