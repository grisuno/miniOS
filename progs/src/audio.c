#include "minios_abi.h"

static long syscall1(long n, long a1) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1) : "rcx","r11","memory");
    return r;
}

static long syscall2(long n, long a1, long a2) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2) : "rcx","r11","memory");
    return r;
}

static long syscall3(long n, long a1, long a2, long a3) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx","r11","memory");
    return r;
}

static long syscall0(long n) {
    long r;
    __asm__ volatile("syscall" : "=a"(r) : "a"(n) : "rcx","r11","memory");
    return r;
}

int audio_init(void) {
    return (int)syscall0(MINIOS_SYS_PCSPK_INIT);
}

void audio_tone(unsigned freq) {
    syscall1(MINIOS_SYS_PCSPK_TONE, (long)freq);
}

int audio_pcm_open(unsigned rate, unsigned channels, unsigned format) {
    (void)rate; (void)channels; (void)format;
    return (int)syscall1(MINIOS_SYS_SB16_OPEN, 1);
}

int audio_pcm_submit(const void *buf, unsigned len) {
    return (int)syscall2(MINIOS_SYS_SB16_SUBMIT, (long)buf, (long)len);
}

void audio_pcm_pump(void) {
    syscall0(MINIOS_SYS_SB16_PUMP);
}

void audio_pcm_close(void) {
    syscall1(MINIOS_SYS_SB16_OPEN, 0);
}

void audio_set_volume(unsigned volume) {
    syscall1(MINIOS_SYS_PCSPK_VOL, (long)volume);
}

unsigned audio_get_volume(void) {
    return (unsigned)syscall1(MINIOS_SYS_PCSPK_VOL, -1);
}

int audio_sb16_present(void) {
    return (int)syscall1(MINIOS_SYS_SB16_OPEN, 0);
}

int audio_stream_open(void) {
    return (int)syscall0(MINIOS_SYS_SB16_STREAM_OPEN);
}

void audio_stream_close(int id) {
    syscall1(MINIOS_SYS_SB16_STREAM_CLOSE, (long)id);
}

int audio_stream_submit(int id, const void *buf, unsigned len) {
    return (int)syscall3(MINIOS_SYS_SB16_STREAM_SUBMIT, (long)id, (long)buf, (long)len);
}

void audio_stream_volume(int id, unsigned char vol) {
    syscall2(MINIOS_SYS_SB16_STREAM_VOLUME, (long)id, (long)vol);
}
