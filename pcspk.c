#include "kernel.h"

#define PIT_CH2_DATA   0x42
#define PIT_CH2_CMD    0x43
#define SPEAKER_PORT   0x61
#define PIT_FREQ       1193182u

void pcspk_init(void) {
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);
}

void pcspk_tone(unsigned freq) {
    if (freq == 0) {
        pcspk_off();
        return;
    }
    if (freq < 20) freq = 20;
    if (freq > 20000) freq = 20000;
    unsigned divisor = PIT_FREQ / freq;
    outb(PIT_CH2_CMD, 0xB6);
    outb(PIT_CH2_DATA, divisor & 0xFF);
    outb(PIT_CH2_DATA, (divisor >> 8) & 0xFF);
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) | 0x03);
}

void pcspk_off(void) {
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & 0xFC);
}
