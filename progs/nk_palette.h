/** nk_palette.h - one shared hybrid palette for every NK-window app.
 *
 * Indices 0-14 exactly match the desktop palette so the desktop behind
 * a graphics window is never recolored; 15-230 carry a 6x6x6 RGB cube,
 * 231-241 carry grays and 242-255 carry saturated accents. An app that
 * presents indexed pixels without uploading this table renders through
 * the kernel gray-ramp default instead, which reads as black on black
 * on true-color VBE modes. Every bound fails closed, never truncated.
 */

#ifndef NK_PALETTE_H
#define NK_PALETTE_H

#define NK_PAL_BYTES 768
#define NK_PAL_DESK 15
#define NK_PAL_CUBE 6
#define NK_PAL_GRAYS 11
#define NK_PAL_ACCENTS 14
#define NK_PAL_ERR_OK 0
#define NK_PAL_ERR_BOUND (-1)

static int nk_palette_build(unsigned char *pal, long cap) {
    static const unsigned char desk[NK_PAL_DESK][3] = {
        {0, 0, 0}, {15, 15, 50}, {100, 100, 110}, {255, 255, 255},
        {60, 90, 140}, {255, 255, 255}, {15, 15, 15}, {0, 220, 0},
        {0, 160, 0}, {180, 180, 190}, {255, 255, 255}, {30, 30, 40},
        {100, 140, 220}, {60, 60, 70}, {140, 140, 155}
    };
    static const unsigned char grays[NK_PAL_GRAYS] = {
        0, 25, 51, 76, 102, 127, 153, 178, 204, 229, 255
    };
    static const unsigned char accents[NK_PAL_ACCENTS][3] = {
        {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0},
        {0, 255, 255}, {255, 0, 255}, {255, 128, 0}, {128, 0, 255},
        {255, 0, 128}, {0, 128, 255}, {128, 255, 0}, {255, 128, 128},
        {128, 255, 128}, {128, 128, 255}
    };
    long idx;
    long r;
    long g;
    long b;
    long i;
    if (!pal || cap < NK_PAL_BYTES)
        return NK_PAL_ERR_BOUND;
    for (i = 0; i < NK_PAL_DESK; i++) {
        pal[i * 3] = desk[i][0];
        pal[i * 3 + 1] = desk[i][1];
        pal[i * 3 + 2] = desk[i][2];
    }
    idx = NK_PAL_DESK;
    for (r = 0; r < NK_PAL_CUBE; r++) {
        for (g = 0; g < NK_PAL_CUBE; g++) {
            for (b = 0; b < NK_PAL_CUBE; b++) {
                pal[idx * 3] = (unsigned char)(r * 51L);
                pal[idx * 3 + 1] = (unsigned char)(g * 51L);
                pal[idx * 3 + 2] = (unsigned char)(b * 51L);
                idx++;
            }
        }
    }
    for (i = 0; i < NK_PAL_GRAYS; i++) {
        pal[idx * 3] = grays[i];
        pal[idx * 3 + 1] = grays[i];
        pal[idx * 3 + 2] = grays[i];
        idx++;
    }
    for (i = 0; i < NK_PAL_ACCENTS; i++) {
        pal[idx * 3] = accents[i][0];
        pal[idx * 3 + 1] = accents[i][1];
        pal[idx * 3 + 2] = accents[i][2];
        idx++;
    }
    if (idx != NK_PAL_DESK + NK_PAL_CUBE * NK_PAL_CUBE * NK_PAL_CUBE
        + NK_PAL_GRAYS + NK_PAL_ACCENTS)
        return NK_PAL_ERR_BOUND;
    return NK_PAL_ERR_OK;
}

#endif
