#ifndef KERNEL_H
#define KERNEL_H

/* The user-window memory layout (load base, stack, brk cap, graphics
 * back-buffers, framebuffer, kernel heap) is defined ONCE in the ABI header
 * shared with ring-3 programs. The kernel derives its own constants from it,
 * so growing the window or moving a back-buffer cannot leave the two sides
 * disagreeing -- that mismatch is what made the lua/MicroPython in-OS tests
 * and DOOM's window go dark when the layout moved. Do not hardcode a layout
 * address in the kernel or in a ring-3 program; put it in minios_abi.h. */
#include "minios_abi.h"

/* ========== Port I/O helpers ========== */
#define ALIGN_UP(x, a) (((x) + (a) - 1) & ~((a) - 1))
#ifndef PORT_IO_DEFINED
#define PORT_IO_DEFINED
static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline unsigned char inb(unsigned short port) {
    unsigned char r;
    __asm__ volatile("inb %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}
static inline void outw(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}
static inline unsigned short inw(unsigned short port) {
    unsigned short r;
    __asm__ volatile("inw %1, %0" : "=a"(r) : "Nd"(port));
    return r;
}
#endif

/* ========== VGA text mode ========== */
#define VGA_BASE    ((volatile char *)0xB8000)
#define VGA_COLS    80
#define VGA_ROWS    25

void vga_clear(void);
void vga_putc(char c);
void vga_puts(const char *s);
void vga_scroll(void);
void vga_set_cursor(int x, int y);
void vga_newline(void);

/* ========== Serial console (COM1) ========== */
void serial_init(void);
void serial_putc(char c);
void serial_puts(const char *s);
int  serial_available(void);
int  serial_getc(void);

/* ========== Keyboard (PS/2) ========== */
#define KEY_BACKSPACE 0x0E
#define KEY_ENTER     0x1C
#define KEY_LSHIFT    0x2A
#define KEY_RSHIFT    0x36
#define KEY_CAPS      0x3A
#define KEY_E0        0xE0
#define KEY_UP        0x48
#define KEY_DOWN      0x50
#define KEY_PGUP      0x49
#define KEY_PGDN      0x51
#define KEY_ESC       0x1B
#define KEY_CSI       '['
#define KEY_ARR_UP    'A'
#define KEY_ARR_DOWN  'B'
#define KEY_ARR_RIGHT 'C'
#define KEY_ARR_LEFT  'D'
#define KEY_HOME_SEQ  'H'
#define KEY_END_SEQ   'F'
#define KEY_PGUP_SEQ  '5'
#define KEY_PGDN_SEQ  '6'
#define KEY_LEFT      0x4B
#define KEY_RIGHT     0x4D
#define KEY_LCTRL     0x1D
#define KEY_F5        0x3F
#define KEY_F11       0x57
#define KEY_TILDE     '~'
#define KEY_LALT      0x38
#define KEY_RALT      0x38
#define KEY_HOME      0x47
#define KEY_END       0x4F

int  kbd_read(void);
int  kbd_available(void);
void kbd_reset_for_shell(void);
void mouse_disable(void);
void mouse_enable(void);

/* ========== VGA cursor ========== */
void vga_cursor_enable(int on);

/* ========== User window and memory allocator ==========
 * All values derive from progs/minios_abi.h (single source of truth for the
 * kernel-ABI memory layout). USER_WIN_LO/HI are the asm-safe (no UL suffix)
 * mirrors the syscall return discriminator string-literal needs; static
 * asserts in kernel.c prove they cannot drift from the ABI header. */
#define USER_LOAD_BASE   MINIOS_USER_LOAD_BASE
#define USER_LOAD_END    MINIOS_USER_LOAD_END
#define USER_STACK_SIZE  MINIOS_USER_STACK_SIZE
#define USER_STACK_TOP   MINIOS_USER_STACK_TOP
#define USER_STACK_BASE  MINIOS_USER_STACK_BASE
#define USER_BRK_END     MINIOS_USER_BRK_END

/* Syscall kernel stack: a dedicated region below the kernel image, exchanged
 * on syscall entry so the kernel never runs on a user stack. The 32 KB region
 * [0x80000, 0x88000) also holds the per-SPAWN-child stack carved by k_exec_user. */
#define SYS_KSTK_TOP    0x00088000UL
#define SYS_KSTK_BASE   (SYS_KSTK_TOP - 0x8000)

#define HEAP_BASE  MINIOS_HEAP_BASE
#define HEAP_SIZE  MINIOS_HEAP_SIZE

void *kmalloc(unsigned long size);
void  kfree(void *ptr);
void *kcalloc(unsigned long nmemb, unsigned long size);
void *krealloc(void *ptr, unsigned long size);
void  kallocator_init(void);

/* dlmalloc backend (third_party/dlmalloc): an mspace rooted over the fixed
 * kernel heap. The kernel's allocator delegates to these. */
void  dlmalloc_init(void);
void *dlmalloc_malloc(unsigned long size);
void  dlmalloc_free(void *ptr);
void *dlmalloc_calloc(unsigned long nmemb, unsigned long size);
void *dlmalloc_realloc(void *ptr, unsigned long size);

/* =========================================================================
 * Ramdisk file system
 * =========================================================================
 * Flat namespace: files are identified by name (including path separators).
 * The ramdisk is a contiguous region in memory with a header, entry table,
 * and data area.  File names are at most RAMDISK_FNAME_LEN - 1 characters.
 *
 * Contract (RDFile):
 *   name:   NUL-terminated file name, at most RAMDISK_FNAME_LEN - 1 chars.
 *   size:   file size in bytes.  0 for empty files.
 *   offset: byte offset into the ramdisk data area.  Validated at load time
 *           to lie within [RD_DATA_START, RD_DATA_START + RD_DATA_MAX).
 *
 * Invariants:
 *   1. ramdisk_open returns a valid RDFile on success, NULL on failure.
 *   2. ramdisk_read/write validate offset + len against size before access.
 *   3. ramdisk_create allocates from the data area; returns NULL if full.
 *   4. ramdisk_delete marks the entry as free; the name is zeroed.
 *   5. ramdisk_setup_from validates the entire image before publishing.
 *   6. RAMDISK_MAX_FILES (128) limits concurrent entries.
 *   7. RAMDISK_FNAME_LEN (64) limits name length; truncation is a bug.
 * ========================================================================= */
#define RAMDISK_MAX_FILES 128
#define RAMDISK_FNAME_LEN 64

typedef struct {
    char     name[RAMDISK_FNAME_LEN];
    unsigned size;
    unsigned offset;
} RDFile;

void     ramdisk_init(void);
RDFile  *ramdisk_open(const char *name);
int      ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len);
int      ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len);
RDFile  *ramdisk_create(const char *name, unsigned size);
int      ramdisk_resize(RDFile *f, unsigned newsize);
int      ramdisk_delete(RDFile *f);
int      ramdisk_list(RDFile **out, int max);
void     ramdisk_setup_from(void *data, unsigned size);
int      ramdisk_count(void);
const char *ramdisk_file_name(int idx);

#define RD_DATA_MAX (48UL * 1024 * 1024)

/* Path resolution choke point shared by the shell builtins and the zip
 * builtins. fs_resolve resolves a path against the cwd into `out`
 * (cap >= RAMDISK_FNAME_LEN); a name that does not fit is rejected like a
 * missing file, never truncated. */
int fs_resolve(const char *path, char *out, unsigned cap);
int fs_dir_exists(const char *dir);
int fs_is_dir(const char *resolved);

/* =========================================================================
 * VFS (Virtual File System) abstraction
 * =========================================================================
 * Registration-based filesystem dispatch.  Drivers register a prefix and a
 * set of operations; vfs_open matches the path prefix and dispatches to the
 * matching driver.
 *
 * Contract (vfs_ops_t):
 *   open:   path is non-NULL, NUL-terminated, within the user window.
 *           mode: 0=read, 1=write (truncate), 2=append.
 *           On success, *handle is set to driver-private state.
 *           On failure, returns negative errno; *handle is undefined.
 *   read:   handle is the value returned by open.  pos is the file offset,
 *           len is the byte count.  Returns bytes read (0 = EOF).
 *           Must not read past the file's actual size.
 *   write:  handle is the value returned by open.  pos is the file offset,
 *           len is the byte count.  Returns bytes written.
 *           For mode=1 (truncate), pos=0 on first write.
 *           For mode=2 (append), pos is ignored (appended at end).
 *   close:  handle is the value returned by open.  Releases all resources.
 *           Always called exactly once per open, even on error paths.
 *   fstat:  handle is the value returned by open.
 *           *size_out receives the file size in bytes.
 *           Returns 0 on success, negative errno on failure.
 *   truncate: handle is the value returned by open.  size is the new size.
 *             Files may grow (zero-filled) or shrink.
 *             Returns 0 on success, negative errno on failure.
 *
 * Contract (vfs_file_t):
 *   ops:    non-NULL after vfs_open succeeds.  NULL before open or after
 *           close.  Never modified after open.
 *   handle: driver-private state, valid between open and close.
 *   pos:    current file position.  Updated by read/write.  Never exceeds
 *           the file's size after a read.
 *   mode:   0=read, 1=write, 2=append.  Set by open, immutable after.
 *   is_console: 1 for stdin/stdout/stderr (console I/O path).
 *
 * Invariants:
 *   1. vfs_open returns a vfs_file_t with ops != NULL on success.
 *   2. Every successful open must be paired with exactly one close.
 *   3. read/write on a closed handle is undefined (debug builds assert).
 *   4. VFS_MAX_MOUNTS (8) limits concurrent registrations.
 *   5. Prefix matching is longest-prefix-first.
 * ========================================================================= */
typedef struct vfs_ops {
    int      (*open)(const char *path, int mode, void **handle);
    int      (*read)(void *handle, void *buf, unsigned long pos, unsigned long len);
    int      (*write)(void *handle, const void *buf, unsigned long pos, unsigned long len);
    int      (*close)(void *handle);
    int      (*fstat)(void *handle, unsigned long *size_out);
    int      (*truncate)(void *handle, unsigned long size);
} vfs_ops_t;

typedef struct vfs_file {
    const vfs_ops_t *ops;
    void            *handle;
    unsigned         pos;
    int              mode;       /* 0=read, 1=write, 2=append */
    int              is_console;
} vfs_file_t;

int  vfs_register(const char *prefix, const vfs_ops_t *ops);
int  vfs_unregister(const char *prefix);
int  vfs_open(const char *path, int mode, vfs_file_t *f);
void vfs_init(void);
void vfs_register_builtins(void);
int  minifs_mkdir_p(const char *resolved);
extern char fs_cwd[];

/* =========================================================================
 * Simple FILE interface (for libc compat)
 * =========================================================================
 * Contract:
 *   KFILE wraps either a ramdisk file, a MiniFS file, or a VFS-backed file.
 *   Exactly one of {rf, vfs, minifs_ino} is active per open file.
 *
 *   rf:          non-NULL when backed by ramdisk.  NULL otherwise.
 *   pos:         current file position.  Updated by read/write/seek.
 *   wbuf/wsize:  write buffer for created files.  Flushed on close.
 *                NULL when reading or when backed by MiniFS/VFS.
 *   mode:        0=read, 1=write (truncate), 2=append.
 *   is_console:  1 for stdin/stdout/stderr.  Routed to console I/O.
 *   minifs_ino:  >= 0 when backed by MiniFS.  -1 when ramdisk or VFS.
 *   minifs_size: cached file size for MiniFS files.
 *   vfs:         non-NULL when backed by VFS driver.  When non-NULL,
 *                dispatch goes through vfs->ops instead of ramdisk/MiniFS.
 *
 * Invariants:
 *   1. kfopen returns a valid KFILE on success, NULL on failure.
 *   2. Every successful kfopen must be paired with exactly one kfclose.
 *   3. After kfclose, the KFILE is invalid and must not be reused.
 *   4. wbuf is allocated on write-mode open, freed on kfclose.
 *   5. For VFS-backed files, pos tracks the logical offset, not the
 *      driver's internal position (driver maintains its own state).
 * ========================================================================= */
#define EOF (-1)

typedef struct {
    RDFile  *rf;
    unsigned pos;
    char    *wbuf;    /* write buffer for created files */
    unsigned wsize;
    unsigned wcap;
    int      mode;       /* 0=read, 1=write (truncate), 2=append */
    int      is_console; /* 1 = stdin/stdout/stderr, routed to the console */
    int      minifs_ino; /* >=0 when backed by minifs, -1 = ramdisk */
    unsigned minifs_size;
    struct vfs_file *vfs; /* VFS backend (when non-NULL, dispatch via ops) */
} KFILE;

KFILE *kfopen(const char *path, const char *mode);
int    kfclose(KFILE *f);
int    kfgetc(KFILE *f);
char  *kfgets(char *buf, int size, KFILE *f);
int    kfungetc(int c, KFILE *f);
unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);
unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);
int    kfseek(KFILE *f, long offset, int whence);
long   kftell(KFILE *f);
int    kfputs(const char *s, KFILE *f);
int    kfputc(int c, KFILE *f);
int    kfflush(KFILE *f);
void   krewind(KFILE *f);

extern KFILE *kstdin;
extern KFILE *kstdout;
extern KFILE *kstderr;
KFILE *kfile_stdin(void);
KFILE *kfile_stdout(void);
KFILE *kfile_stderr(void);

/* ========== String functions ========== */
unsigned long kstrlen(const char *s);
char *kstrcpy(char *dst, const char *src);
char *kstrncpy(char *dst, const char *src, unsigned long n);
char *kstrncat(char *dst, const char *src, unsigned long n);
int   kstrcmp(const char *a, const char *b);
int   kstrncmp(const char *a, const char *b, unsigned long n);
char *kstrchr(const char *s, int c);
char *kstrstr(const char *hay, const char *ndl);
void *kmemcpy(void *dst, const void *src, unsigned long n);
void *kmemset(void *dst, int c, unsigned long n);
int   kmemcmp(const void *a, const void *b, unsigned long n);
void *kmemmove(void *dst, const void *src, unsigned long n);
long   katol(const char *s);

/* ========== printf ========== */
int kprintf(const char *fmt, ...);
int kfprintf(KFILE *f, const char *fmt, ...);
int ksprintf(char *buf, const char *fmt, ...);
int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);

/* ========== Shell ========== */
void shell_init(void);
void shell_run(void);
int  console_getc(void);
int  redirect_suspend(void);
void redirect_resume(int was);
int  redirect_begin(void);
int  redirect_commit(const char *path, int append_mode);
int  redirect_active(void);
int  shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);
int  shell_run_any(const char *name, int argc, char **argv);
void shell_exec_builtin(int argc, char **argv);
void shell_report_exit(int code);
void shell_report(const char *what, const char *detail);

/* ========== Symbol table and program registry ========== */
typedef int (*prog_entry_t)(int argc, char **argv);

#define KSYM_MAX 256
#define KPROG_MAX 64

typedef struct {
    const char *name;
    void       *addr;
} KSym;

typedef struct {
    char         name[31];
    prog_entry_t entry;
    void        *proc_entry;
    int          is_proc;
} KProg;

extern KSym  ksym_table[];
extern int   ksym_count;
extern KProg kprog_table[];
extern int   kprog_count;

KProg *kprog_slot(const char *name);
KProg *kprog_lookup(const char *name);
void  *ksym_resolve(const char *name);
int  k_spawn(const char *name, int argc, char **argv);
void k_register_program(const char *name, prog_entry_t entry);
void k_register_process(const char *name, void *proc_entry);
void k_register_symbol(const char *name, void *addr);

/* ========== Process execution (Linux ELF binaries) ========== */
int  k_exec_user(void *entry, int argc, char **argv);
int  k_run_rel(prog_entry_t entry, int argc, char **argv);
void kexit(int code);

/* ========== Desktop shortcut launch ========== */
void desktop_launch(const char *cmd);
void shell_queue_launch(const char *cmd);

/* ========== Page table helpers (kernel.c) ========== */
void *pt_page_alloc(void);
void  pt_page_free(void *ptr);
void  mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);
void  mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);

/* ========== VMA red-black tree (loader.c) ========== */
typedef struct vma_node {
    unsigned long    base;
    unsigned long    len;
    int              red;
    struct vma_node *left, *right, *parent;
} vma_node_t;

void vma_tree_init(void);
vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);
vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);
int  vma_tree_delete(vma_node_t **root, unsigned long base);

/* VMA tree globals (loader.c) */
#define VMA_MAX 4096
extern vma_node_t *VMA_NIL;
extern vma_node_t *vma_live_root;
extern vma_node_t *vma_free_root;

/* brk/mmap globals (loader.c) */
extern unsigned long g_brk;
extern unsigned long g_brk_limit;
extern unsigned long user_mmap_cur;

/* ========== ELF loader (loader.c) ========== */

/* Minimal ELF64 definitions (used by shell_load, shell_run_elf_buf, SPAWN) */
#define EI_NIDENT 16
typedef unsigned long long Elf64_Addr;
typedef unsigned long long Elf64_Off;
typedef unsigned int       Elf64_Word;
typedef unsigned short     Elf64_Half;
typedef unsigned long long Elf64_Xword;
typedef long long          Elf64_Sxword;

typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
} Elf64_Ehdr;

#define ET_REL      1
#define ET_EXEC     2
#define ET_DYN      3

/* VMA pool (used by SPAWN to save/restore across child execution) */
extern vma_node_t vma_pool[];
extern int        vma_pool_n;

void *elf_load(void *data, unsigned size);       /* ET_REL relocatable .o */
void *load_exec_elf(void *data, unsigned size);  /* ET_EXEC / ET_DYN */

/* ========== Linux syscall interface ========== */
void syscall_init(void);

/* ========== Syscall table ========== */
void *ksym_resolve(const char *name);

/* ========== Kernel info ========== */
extern unsigned long kernel_end;
extern char ramdisk_start[];
extern char ramdisk_end[];

/* ========== Kernel clock ========== */
unsigned long ktime_ms(void);

/* ========== PC speaker ========== */
void     pcspk_init(void);
void     pcspk_tone(unsigned freq);
void     pcspk_off(void);
void     pcspk_set_volume(unsigned volume);
unsigned pcspk_get_volume(void);

/* ========== RTC time-of-day ========== */
int rtc_read_tod(int *hour, int *min, int *sec);

/* ========== IDE driver ========== */
void ide_init(void);
int  ide_read_sectors(unsigned int lba, unsigned int count, void *buf);
int  ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);
int  ide_read_sector(unsigned int lba, void *buf);
int  ide_write_sector(unsigned int lba, const void *buf);
unsigned int ide_total_sectors(void);
int  ide_present(void);

/* ========== Block device layer ========== */
void block_init(void);
int  block_read(unsigned int block_num, void *buf);
int  block_write(unsigned int block_num, const void *buf);
int  block_read_multi(unsigned int block_num, unsigned int count, void *buf);
int  block_write_multi(unsigned int block_num, unsigned int count, const void *buf);
unsigned int block_total(void);

/* ========== User-mode fault recovery ========== */
void k_user_fault_return(void);

#endif
