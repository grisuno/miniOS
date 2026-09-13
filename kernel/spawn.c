#include "kernel.h"
#include "sched.h"
#include "vma.h"
#include "spawn.h"
#include "minifs.h"
#include "vga_fb.h"
#include "arch/x86/msr.h"

/** Docstring: File-static VMA pool copy, stack-safe by construction. */
static vma_node_t spawn_vma_copy[VMA_MAX];

/** Docstring: Save the caller shared-window view into ctx. */
void spawn_backup(spawn_ctx_t *ctx)
{
    int i;
    ctx->brk = g_brk;
    ctx->brk_lim = g_brk_limit;
    ctx->mmap_cur = user_mmap_cur;
    ctx->fsbase = rdmsr(MSR_FSBASE);
    ctx->gsbase = rdmsr(MSR_GSBASE);
    ctx->p0_kstack = procs[0].kstack;
    for (i = 0; i < vma_pool_n; i++)
        spawn_vma_copy[i] = vma_pool[i];
    ctx->live_root = vma_live_root;
    ctx->free_root = vma_free_root;
    ctx->pool_n = vma_pool_n;
    for (i = 0; i < KFD_MAX; i++)
        ctx->kfd[i] = kfd_table[i];
}

/** Docstring: Restore a view previously saved by spawn_backup. */
void spawn_restore(const spawn_ctx_t *ctx)
{
    int i;
    g_brk = ctx->brk;
    g_brk_limit = ctx->brk_lim;
    user_mmap_cur = ctx->mmap_cur;
    procs[0].kstack = ctx->p0_kstack;
    for (i = 0; i < ctx->pool_n; i++)
        vma_pool[i] = spawn_vma_copy[i];
    vma_pool_n = ctx->pool_n;
    vma_live_root = ctx->live_root;
    vma_free_root = ctx->free_root;
    wrmsr(MSR_FSBASE, ctx->fsbase);
    wrmsr(MSR_GSBASE, ctx->gsbase);
    for (i = 0; i < KFD_MAX; i++)
        kfd_table[i] = ctx->kfd[i];
}

/** Docstring: Release a copy produced by spawn_copy_argv. */
void spawn_free_argv(char **kargv, int argc)
{
    int i;
    if (!kargv) return;
    for (i = 0; i < argc; i++)
        if (kargv[i]) kfree(kargv[i]);
    kfree(kargv);
}

/** Docstring: Copy user argv into kernel memory, zero terminated. */
char **spawn_copy_argv(int argc, const char **uargv)
{
    char **kargv;
    int i;
    if (argc <= 0 || !uargv) return 0;
    kargv = (char **)kmalloc((unsigned)(argc + 1) * sizeof(char *));
    if (!kargv) return 0;
    for (i = 0; i <= argc; i++) kargv[i] = 0;
    for (i = 0; i < argc; i++) {
        unsigned slen;
        if (!uargv[i]) break;
        slen = (unsigned)kstrlen(uargv[i]) + 1;
        kargv[i] = (char *)kmalloc(slen);
        if (!kargv[i]) { spawn_free_argv(kargv, i); return 0; }
        kmemcpy(kargv[i], uargv[i], slen);
    }
    kargv[argc] = 0;
    return kargv;
}

/** Docstring: Validate user argv words against the user window. */
int spawn_validate_argv(int argc, const char **uargv)
{
    int i;
    if (argc <= 0 || !uargv) return 1;
    if (!user_range_ok((unsigned long)uargv,
                       (unsigned long)(argc + 1) * sizeof(char *)))
        return 0;
    for (i = 0; i < argc; i++) {
        unsigned long s;
        if (!uargv[i]) break;
        s = (unsigned long)uargv[i];
        if (s < USER_LOAD_BASE || s >= USER_LOAD_END) return 0;
        if (!user_str_ok(s, USER_LOAD_END - s)) return 0;
    }
    return 1;
}

/** Docstring: Snapshot a resolved path into a kernel buffer. */
unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)
{
    RDFile *f = ramdisk_open(resolved);
    unsigned char *data = 0;
    unsigned data_size = 0;
    *size_out = 0;
    if (f) {
        data_size = f->size ? f->size : 1;
        data = (unsigned char *)kmalloc(data_size);
        if (!data) return 0;
        ramdisk_read(f, data, 0, f->size);
    } else if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) {
            MiniFSInode mi;
            if (minifs_stat(ino, &mi) >= 0 && mi.size > 0) {
                data_size = mi.size;
                data = (unsigned char *)kmalloc(data_size);
                if (data) minifs_read(ino, data, 0, data_size);
            }
        }
    }
    if (!data) return 0;
    *size_out = data_size;
    return data;
}

/** Docstring: Run one ET_REL child through the ring-0 loader. */
static int spawn_run_rel(const char *resolved, const char *redirect,
                         unsigned char *data, unsigned data_size,
                         int argc, char **kargv, const char **uargv_fallback)
{
    const char *rp = resolved;
    prog_entry_t entry;
    void *base = 0;
    int did_redirect = 0;
    int rc;
    if (rp[0] == '/') rp++;
    if (kstrncmp(rp, ETREL_TRUSTED_DIR, ETREL_TRUSTED_LEN) != 0) {
        kprintf("SPAWN: refusing untrusted ET_REL");
        return EFAULT;
    }
    entry = elf_load((void *)data, data_size, &base);
    if (redirect && redirect[0]) did_redirect = redirect_begin();
    rc = EFAULT;
    if (entry)
        rc = k_run_rel(entry, argc, kargv ? kargv : (char **)uargv_fallback);
    kfree(base);
    if (did_redirect && redirect_commit(redirect, 0) != 0)
        kprintf("SPAWN: redirect to %s failed, output dropped", redirect);
    return rc;
}

/** Docstring: Run one ET_EXEC child in an isolated window. */
static int spawn_run_exec(const char *resolved, const char *redirect,
                           unsigned char *data, unsigned data_size,
                           int argc, char **kargv, const char **uargv_fallback)
{
    int did_redirect = 0;
    int pid;
    int rc = EFAULT;
    if (redirect && redirect[0]) did_redirect = redirect_begin();
    pid = proc_spawn_elf(resolved, data, data_size, argc,
                         kargv ? kargv : (char **)uargv_fallback);
    if (pid > 0) {
        /* Interruptible wait: the old blocking do_waitpid left a ring-3
         * SPAWN parent (file browser, vedit IDE) unkillable when its
         * child waited on stdin or looped forever (Ctrl+R on hello.py
         * with input() hung the machine with no way out). Poll with
         * do_waitpid_nb and yield like the shell foreground wait does:
         * Ctrl+C kills the child (exit 130) and the title-bar X is
         * honoured through wm_close_pending the same way. */
        for (;;) {
            rc = do_waitpid_nb(pid);
            if (rc != WAITPID_NONE) break;
            if (wm_close_pending()) {
                wm_clear_close();
                do_kill(pid);
                do_waitpid(pid);
                rc = 130;
                break;
            }
            if (console_peek() == 0x03) {
                console_getc();
                kprintf("^C\n");
                do_kill(pid);
                do_waitpid(pid);
                rc = 130;
                break;
            }
            yield();
        }
    }
    if (did_redirect && redirect_commit(redirect, 0) != 0)
        kprintf("SPAWN: redirect to %s failed, output dropped", redirect);
    return rc;
}

/** Docstring: Run a loaded image by ELF type, return child status. */
int spawn_execute(const char *resolved, const char *redirect,
                  unsigned char *data, unsigned data_size,
                  int argc, char **kargv, const char **uargv_fallback)
{
    Elf64_Half etype = ((const Elf64_Ehdr *)data)->e_type;
    if (etype == ET_REL)
        return spawn_run_rel(resolved, redirect, data, data_size,
                             argc, kargv, uargv_fallback);
    if (etype == ET_EXEC || etype == ET_DYN)
        return spawn_run_exec(resolved, redirect, data, data_size,
                              argc, kargv, uargv_fallback);
    return EFAULT;
}
