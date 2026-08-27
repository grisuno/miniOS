/* stb_selftest.c — ring-0 ET_REL self-test for the kernel's stb image API.
 *
 * Loaded through the kernel symbol table: stbi_load_file reads a whole file
 * from the ramdisk and decodes it, stbi_image_free releases the buffer, and
 * the test verifies the image dimensions plus one known pixel (top-left red)
 * before printing the success string.  Fails closed on any error: a bad
 * load, wrong size or wrong pixel all abort with a diagnostic.
 *
 * Build: gcc -c -ffreestanding -m64 -mno-red-zone -fno-pic -o objects/stb.o stb_selftest.c
 * (host gcc, not miniGCC — the symbols resolve against the kernel table at load.)
 * Ship on the ramdisk as objects/stb.o.
 * Usage: run objects/stb.o
 */
extern unsigned char *stbi_load_file(const char *path, int *w, int *h,
                                     int *channels, int desired);
extern void stbi_image_free(void *retval_from_stbi_load);
extern int printf(const char *fmt, ...);

int main(void) {
    int w = 0, h = 0, ch = 0;
    unsigned char *img;

    img = stbi_load_file("docs/test.png", &w, &h, &ch, 4);
    if (!img) {
        printf("stb: cannot load docs/test.png\n");
        return 1;
    }

    if (w != 8 || h != 8) {
        printf("stb: unexpected size %dx%d\n", w, h);
        stbi_image_free(img);
        return 1;
    }

    /* RGBA decode: img[0..3] = R, G, B, A.  Pixel (0,0) is pure red. */
    if (img[0] != 255 || img[1] != 0 || img[2] != 0 || img[3] != 255) {
        printf("stb: pixel(0,0) = %d %d %d %d, expected 255 0 0 255\n",
               img[0], img[1], img[2], img[3]);
        stbi_image_free(img);
        return 1;
    }

    stbi_image_free(img);
    printf("stb: png ok (%dx%d)\n", w, h);
    return 0;
}
