#ifndef STB_API_H
#define STB_API_H

/* stb_api.h — MiniOS integration API for the stb single-header libraries.
 *
 * The stb headers live in this directory as pristine upstream copies. The
 * kernel compiles stb_impl.c (PNG/TGA decode only) into the image and
 * exports the functions below through the kernel symbol table, so ET_REL
 * programs — the ring-0 toolchain — can decode images without carrying the
 * implementation. Ring-3 programs that need stb (the Nuklear node editor)
 * compile the same headers directly into the app and reach files through the
 * Linux syscall ABI; this header is the shared surface both sides use.
 *
 * Every function returns a buffer allocated with the kernel allocator; free
 * it with stbi_image_free. Failure returns 0 and never a partial image.
 */

/* Decode an image file (ramdisk first, MiniFS fallback) into a raw channel
 * buffer. desired forces the output channel count (4 = RGBA) or 0 = as
 * stored; w/h receive the decoded dimensions, channels the stored count. */
unsigned char *stbi_load_file(const char *path, int *w, int *h,
                              int *channels, int desired);

/* Decode an image held in memory (e.g. a compressed blob already loaded).
 * Same semantics as stbi_load_file. */
unsigned char *stbi_load_from_memory(const unsigned char *data, int len,
                                     int *w, int *h, int *channels,
                                     int desired);

/* Release a buffer returned by the loaders. */
void stbi_image_free(void *retval_from_stbi_load);

#endif