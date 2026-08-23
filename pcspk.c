#include "kernel.h"
#include "pcspk.h"

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

void pcspk_init(void) {
    pcspk_volume = PCSPK_VOL_DEFAULT;
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);
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
