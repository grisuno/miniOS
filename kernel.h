#ifndef KERNEL_H
#define KERNEL_H

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

/* ========== Keyboard (PS/2) ========== */
#define KEY_BACKSPACE 0x0E
#define KEY_ENTER     0x1C
#define KEY_LSHIFT    0x2A
#define KEY_RSHIFT    0x36
#define KEY_CAPS      0x3A

int  kbd_read(void);
int  kbd_available(void);

/* ========== Memory allocator ========== */
void *kmalloc(unsigned long size);
void  kfree(void *ptr);
void *kcalloc(unsigned long nmemb, unsigned long size);
void *krealloc(void *ptr, unsigned long size);
void  kallocator_init(void);

/* ========== Ramdisk file system ========== */
#define RAMDISK_MAX_FILES 128
#define RAMDISK_FNAME_LEN 32

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
int      ramdisk_list(RDFile **out, int max);
void     ramdisk_setup_from(void *data, unsigned size);

/* ========== Simple FILE interface (for libc compat) ========== */
#define EOF (-1)

typedef struct {
    RDFile  *rf;
    unsigned pos;
    char    *wbuf;    /* write buffer for created files */
    unsigned wsize;
    unsigned wcap;
    int      mode;    /* 0=read, 1=write */
} KFILE;

KFILE *kfopen(const char *path, const char *mode);
int    kfclose(KFILE *f);
int    kfgetc(KFILE *f);
int    kfungetc(int c, KFILE *f);
unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);
unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);
int    kfseek(KFILE *f, long offset, int whence);
long   kftell(KFILE *f);
int    kfputs(const char *s, KFILE *f);
int    kfputc(int c, KFILE *f);
int    kfflush(KFILE *f);

/* ========== String functions ========== */
unsigned long kstrlen(const char *s);
char *kstrcpy(char *dst, const char *src);
char *kstrncpy(char *dst, const char *src, unsigned long n);
int   kstrcmp(const char *a, const char *b);
int   kstrncmp(const char *a, const char *b, unsigned long n);
char *kstrchr(const char *s, int c);
char *kstrstr(const char *hay, const char *ndl);
void *kmemcpy(void *dst, const void *src, unsigned long n);
void *kmemset(void *dst, int c, unsigned long n);
int   kmemcmp(const void *a, const void *b, unsigned long n);
void *kmemmove(void *dst, const void *src, unsigned long n);

/* ========== printf ========== */
int kprintf(const char *fmt, ...);
int kfprintf(KFILE *f, const char *fmt, ...);
int ksprintf(char *buf, const char *fmt, ...);

/* ========== Shell ========== */
void shell_init(void);
void shell_run(void);

/* ========== Program execution ========== */
typedef int (*prog_entry_t)(int argc, char **argv);
int  k_spawn(const char *name, int argc, char **argv);
void k_register_program(const char *name, prog_entry_t entry);
void k_register_symbol(const char *name, void *addr);

/* ========== ELF loader ========== */
void *elf_load(void *data, unsigned size);

/* ========== Syscall table ========== */
void *ksym_resolve(const char *name);

/* ========== Kernel info ========== */
extern unsigned long kernel_end;

#endif
