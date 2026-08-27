/* stb_impl.c — kernel-side implementation of the stb image API.
 *
 * Compiles stb_image.h into the kernel image with the allocator redirected
 * to the kernel heap and every codec but PNG/TGA disabled, so the image
 * carries exactly the decode paths MiniOS uses. stbi_load_file reads the
 * whole file through the kernel file API (ramdisk first, MiniFS fallback),
 * matching the whole-file-in-memory contract the compression tools use:
 * an image is decoded to a freshly allocated buffer or the load fails, never
 * a partial result. The entry points are exported through the kernel symbol
 * table (see register_libc_symbols in kernel.c).
 *
 * stb_image.h is a pristine upstream single-header library; none of it is
 * edited, every knob is applied through the macros below.
 */
#include "kernel.h"

#define STBI_MALLOC(sz)       kmalloc(sz)
#define STBI_REALLOC(p, sz)   krealloc(p, sz)
#define STBI_FREE(p)          kfree(p)
#define STBI_ASSERT(x)        do { if (!(x)) { for(;;); } } while(0)
#define memcpy(a, b, n)       kmemcpy(a, b, n)
#define memset(a, c, n)       kmemset(a, c, n)

#define STBI_NO_JPEG
#define STBI_NO_BMP
#define STBI_NO_PSD
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#define STBI_NO_LINEAR
#define STBI_NO_STDIO

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "stb_api.h"

unsigned char *stbi_load_file(const char *path, int *w, int *h,
                              int *channels, int desired) {
    KFILE *f;
    unsigned long size, read_total, chunk;
    unsigned char *buf, *img;

    if (!path) return 0;
    f = kfopen(path, "r");
    if (!f) return 0;

    /* Grow a whole-file buffer until the read stops making progress. The
     * buffer is bounded by the file size, so a hostile file cannot drive an
     * oversized allocation. */
    size = 0;
    buf = 0;
    for (;;) {
        unsigned char *nb = krealloc(buf, size + 4096);
        if (!nb) { if (buf) kfree(buf); kfclose(f); return 0; }
        buf = nb;
        read_total = 0;
        while (read_total < 4096) {
            chunk = kfread(buf + size + read_total, 1, 4096 - read_total, f);
            if (chunk == 0) break;
            read_total += chunk;
        }
        size += read_total;
        if (read_total == 0) break;
    }
    kfclose(f);
    if (size == 0) { kfree(buf); return 0; }

    img = stbi_load_from_memory(buf, (int)size, w, h, channels, desired);
    kfree(buf);
    return img;
}