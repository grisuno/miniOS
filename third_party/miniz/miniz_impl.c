/* miniz_impl.c — kernel-side implementation of the miniz zip library.
 *
 * Compiles the amalgamated miniz 3.0.2 into the kernel image with the
 * allocator redirected to the kernel heap and stdio/time stripped out, so
 * the shell's unzip/zip builtins can read and write ZIP archives whole-file
 * in memory without ever touching a host file descriptor. The compression
 * tools contract applies: an archive is fully validated before any entry is
 * published, and every failure path reports a diagnostic and releases.
 *
 * miniz.c/miniz.h are a pristine upstream amalgamation (unlicense + MIT
 * header); none of it is edited, every knob is applied through the macros
 * below. The miniz header is included first with its own defaults so the
 * redefinition never triggers a warning; the allocator and libc-name macros
 * are then overridden before the implementation is compiled. The libc-name
 * macros are safe for the same reason the stb wrapper uses them: on this
 * x86-64 target size_t and unsigned long are the same type, so the
 * declarations glibc's string.h emits expand to the kernel kmem* signatures
 * exactly.
 */
#include "kernel.h"

#define MINIZ_NO_STDIO
#define MINIZ_NO_TIME

#include "miniz.h"

#undef  MZ_ASSERT
#undef  MZ_MALLOC
#undef  MZ_FREE
#undef  MZ_REALLOC
#define MZ_ASSERT(x)       do { if (!(x)) { for(;;); } } while(0)
#define MZ_MALLOC(x)       kmalloc((unsigned long)(x))
#define MZ_FREE(x)         kfree(x)
#define MZ_REALLOC(p, x)   krealloc((p), (unsigned long)(x))
#define memcpy(a, b, n)    kmemcpy(a, b, n)
#define memmove(a, b, n)   kmemmove(a, b, n)
#define memset(a, c, n)    kmemset(a, c, n)
#define memcmp(a, b, n)    kmemcmp(a, b, n)
#define strlen(s)          kstrlen(s)

#include "miniz.c"

/* MiniOS adapter: the amalgamated header forward-declares the writer's
 * internal state, so the heap writer's output buffer is exposed through
 * these two accessors defined here where the full struct is visible. The
 * returned pointer is owned by the archive and released by
 * mz_zip_writer_end. */
void *mz_zip_writer_mem_ptr(mz_zip_archive *pZip) {
    if (!pZip || !pZip->m_pState) return 0;
    return pZip->m_pState->m_pMem;
}

size_t mz_zip_writer_mem_size(mz_zip_archive *pZip) {
    if (!pZip || !pZip->m_pState) return 0;
    return pZip->m_pState->m_mem_size;
}