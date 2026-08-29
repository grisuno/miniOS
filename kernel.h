#ifndef KERNEL_H
#define KERNEL_H

/* ========== Port I/O helpers ========== */
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
void mouse_disable(void);
void mouse_enable(void);

/* ========== VGA cursor ========== */
void vga_cursor_enable(int on);

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
int      ramdisk_resize(RDFile *f, unsigned newsize);
int      ramdisk_delete(RDFile *f);
int      ramdisk_list(RDFile **out, int max);
void     ramdisk_setup_from(void *data, unsigned size);

/* Path resolution choke point shared by the shell builtins and the zip
 * builtins. fs_resolve resolves a path against the cwd into `out`
 * (cap >= RAMDISK_FNAME_LEN); a name that does not fit is rejected like a
 * missing file, never truncated. */
int fs_resolve(const char *path, char *out, unsigned cap);
int fs_dir_exists(const char *dir);
int fs_is_dir(const char *resolved);

/* ========== Simple FILE interface (for libc compat) ========== */
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

/* ========== printf ========== */
int kprintf(const char *fmt, ...);
int kfprintf(KFILE *f, const char *fmt, ...);
int ksprintf(char *buf, const char *fmt, ...);
int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);

/* ========== Shell ========== */
void shell_init(void);
void shell_run(void);

/* ========== Program execution ========== */
typedef int (*prog_entry_t)(int argc, char **argv);
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

/* ========== ELF loader ========== */
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

#endif
