#ifndef SPAWN_H
#define SPAWN_H

#include "kernel.h"
#include "vma.h"
#include "sched.h"

/** Docstring: Scalar shared-window view saved across a child run. */
typedef struct {
    unsigned long brk;
    unsigned long brk_lim;
    unsigned long mmap_cur;
    unsigned long fsbase;
    unsigned long gsbase;
    uint64_t p0_kstack;
    vma_node_t *live_root;
    vma_node_t *free_root;
    int pool_n;
    KFILE *kfd[KFD_MAX];
} spawn_ctx_t;

/** Docstring: Save the caller shared-window view into ctx. */
void spawn_backup(spawn_ctx_t *ctx);

/** Docstring: Restore a view previously saved by spawn_backup. */
void spawn_restore(const spawn_ctx_t *ctx);

/** Docstring: Validate user argv words against the user window. */
int spawn_validate_argv(int argc, const char **uargv);

/** Docstring: Copy user argv into kernel memory, zero terminated. */
char **spawn_copy_argv(int argc, const char **uargv);

/** Docstring: Release a copy produced by spawn_copy_argv. */
void spawn_free_argv(char **kargv, int argc);

/** Docstring: Snapshot a resolved path into a kernel buffer. */
unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);

/** Docstring: Run a loaded image by ELF type, return child status. */
int spawn_execute(const char *resolved, const char *redirect,
                  unsigned char *data, unsigned data_size,
                  int argc, char **kargv, const char **uargv_fallback);

#endif
