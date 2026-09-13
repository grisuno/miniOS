/* test_driver.c -- Host test for the Strategy-pattern device registry.
 *
 * drivers/driver.c is dependency-free, so it compiles against the host
 * libc with only driver.h. Covers: register/find by name, find by type,
 * duplicate and null rejection, table-full fail-closed, reset semantics.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "driver.h"

static int rd_ok;
static int test_read(device_t *d, unsigned lba, unsigned count, void *buf) {
    (void)d; (void)lba; (void)count; (void)buf;
    rd_ok++;
    return 0;
}

static const block_ops_t test_block_ops = {
    test_read, 0, 0, 0,
};

static int pcm_opened;
static int pcm_submits;

static void test_pcm_open(device_t *d) {
    (void)d;
    pcm_opened++;
}

static int test_pcm_submit(device_t *d, const unsigned char *pcm, unsigned len) {
    (void)d; (void)pcm; (void)len;
    pcm_submits++;
    return 0;
}

static void test_tone(device_t *d, unsigned freq) {
    (void)d; (void)freq;
}

static const audio_ops_t tone_ops = {
    .tone = test_tone,
    .off = 0,
    .set_volume = 0,
    .get_volume = 0,
    .present = 0,
    .pcm_open = 0,
    .pcm_close = 0,
    .pcm_submit = 0,
};

static const audio_ops_t pcm_ops = {
    .tone = 0,
    .off = 0,
    .set_volume = 0,
    .get_volume = 0,
    .present = 0,
    .pcm_open = test_pcm_open,
    .pcm_close = 0,
    .pcm_submit = test_pcm_submit,
};

int main(void) {
    device_t a;
    memset(&a, 0, sizeof(a));
    strcpy(a.name, "ide0");
    a.type = DEV_TYPE_BLOCK;
    a.block = &test_block_ops;

    device_reset();
    assert(device_count() == 0);
    assert(device_find("ide0") == 0);
    assert(device_find_by_type(DEV_TYPE_BLOCK) == 0);

    assert(device_register(0) < 0);
    {
        device_t noname;
        memset(&noname, 0, sizeof(noname));
        assert(device_register(&noname) < 0);
    }
    assert(device_register(&a) == 0);
    assert(device_count() == 1);
    assert(device_register(&a) < 0);
    assert(device_count() == 1);

    {
        device_t *f = device_find("ide0");
        assert(f != 0);
        assert(f->type == DEV_TYPE_BLOCK);
        assert(f->block == &test_block_ops);
        assert(f->block->read_sectors(f, 0, 1, 0) == 0);
        assert(rd_ok == 1);
    }
    assert(device_find("nope") == 0);
    assert(device_find(0) == 0);
    assert(device_find_by_type(DEV_TYPE_BLOCK) != 0);
    assert(device_find_by_type(DEV_TYPE_NET) == 0);

    {
        int i;
        for (i = 1; i < DEV_MAX; i++) {
            device_t d;
            memset(&d, 0, sizeof(d));
            snprintf(d.name, sizeof(d.name), "dev%d", i);
            d.type = DEV_TYPE_CHAR;
            assert(device_register(&d) == 0);
        }
        assert(device_count() == DEV_MAX);
        {
            device_t extra;
            memset(&extra, 0, sizeof(extra));
            strcpy(extra.name, "full");
            assert(device_register(&extra) < 0);
        }
    }

    device_reset();
    assert(device_count() == 0);

    {
        device_t tone;
        device_t pcm;
        memset(&tone, 0, sizeof(tone));
        memset(&pcm, 0, sizeof(pcm));
        strcpy(tone.name, "pcspk0");
        tone.type = DEV_TYPE_AUDIO;
        tone.audio = &tone_ops;
        strcpy(pcm.name, "sb160");
        pcm.type = DEV_TYPE_AUDIO;
        pcm.audio = &pcm_ops;
        assert(device_register(&tone) == 0);
        assert(device_register(&pcm) == 0);
        assert(device_find("sb160") != 0);
        assert(device_find("sb160")->audio == &pcm_ops);
        assert(device_find("sb160")->audio->pcm_submit != 0);
        assert(device_find("pcspk0")->audio == &tone_ops);
        assert(device_find("pcspk0")->audio->pcm_submit == 0);
        assert(pcm_opened == 0);
        device_find("sb160")->audio->pcm_open(device_find("sb160"));
        assert(pcm_opened == 1);
        assert(device_find("sb160")->audio->pcm_submit(device_find("sb160"), 0, 0) == 0);
        assert(device_find("nope") == 0);
    }

    device_reset();
    assert(device_count() == 0);
    assert(device_find("ide0") == 0);

    printf("driver: ok\n");
    return 0;
}
