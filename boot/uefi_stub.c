/** Docstring: boot/uefi_stub.c -- Minimal MiniOS UEFI stub (Phase 1).
 *
 * A freestanding x86-64 PE/COFF application (BOOTX64.EFI) proving the
 * UEFI firmware handshake MiniOS needs: entry through efi_main with
 * the system table, console + COM1 banner, GOP mode query (reported
 * when the firmware ships a video driver, unavailable on headless
 * OVMF), a full memory-map retrieval and a boot-disk read proving
 * Block I/O (LBA 0 carries the MBR signature). Hand-rolled UEFI
 * types (no gnu-efi): only the tables this phase touches, with the
 * MS x64 ABI on every firmware call and the 24-byte table header
 * present (both were proven necessary the hard way: SysV calls hang
 * and a missing header turns the first call into a jump at the
 * "BOOTSERV" magic itself).
 *
 * Phase 2a (landed): SimpleFileSystem reads kernel.bin whole,
 * ExitBootServices, then a 64-bit entry prints the handoff block over
 * serial and halts (load + exit + jump with no kernel changes).
 * Slices (b) dynamic framebuffer and (c) full boot to shell stay
 * future work; VESA/VGA text is the fallback, INT 13h paths untouched.
 *
 * Hand-rolled GUIDs are byte-checked against EDK2, never memory:
 * LoadedImage is 5B1B31A1 (not B1) and SFS Data2 is 0x6459 (not
 * 0x52); each wrong byte is a silent EFI_NOT_FOUND with no hint
 * which nibble lied.
 */

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef u64 efi_status;
typedef void *efi_handle;
typedef u64 efi_physical_addr;
typedef u64 efi_virtual_addr;

/* UEFI firmware calls use the Microsoft x64 ABI (rcx, rdx, r8, r9),
 * never System V. Every function pointer below carries ms_abi, and
 * efi_main itself is entered that way; without this the first table
 * call jumps wild (proven by a silent hang after the COM1 banner,
 * which needs no tables at all). */
#define EFIABI __attribute__((ms_abi))

#define EFI_SUCCESS 0

typedef struct {
    char magic[8];
    u32 revision;
    u32 header_size;
    u32 crc32;
    u32 reserved;
} efi_table_header;

typedef struct {
    u16 scan;
    u16 unicode;
} efi_input_key;

typedef struct efi_simple_text_output efi_simple_text_output;
typedef efi_status (EFIABI *efi_text_out)(efi_simple_text_output *self, u16 *str);

struct efi_simple_text_output {
    void *reset;
    efi_text_out output_string;
    void *test_string;
    void *query_mode;
    void *set_mode;
    void *set_attribute;
    void *clear_screen;
    void *set_cursor;
    void *enable_cursor;
    void *mode;
};

typedef struct {
    u32 red_mask;
    u32 green_mask;
    u32 blue_mask;
    u32 reserved_mask;
} efi_pixel_bitmask;

typedef struct {
    u32 version;
    u32 horizontal;
    u32 vertical;
    int pixel_format;
    efi_pixel_bitmask pixel_info;
    u32 pixels_per_line;
} efi_gop_mode_info;

typedef struct {
    u32 max_mode;
    u32 mode;
    efi_gop_mode_info *info;
    u64 info_size;
    efi_physical_addr fb_base;
    u64 fb_size;
} efi_gop_mode;

typedef struct efi_gop efi_gop;
struct efi_gop {
    void *query_mode;
    void *set_mode;
    void *blt;
    efi_gop_mode *mode;
};

typedef struct {
    u32 type;
    efi_physical_addr phys;
    efi_virtual_addr virt;
    u64 pages;
    u64 attr;
} efi_mem_desc;

typedef struct {
    /* The table opens with the 24-byte header (Signature, Revision,
     * HeaderSize, CRC32, Reserved): omitting it shifts every slot by
     * three and turns the first call into a jump to the "BOOTSERV"
     * magic itself (#GP with RIP="BOOTSERV", the signature failure
     * of hand-rolled headers). */
    efi_table_header hdr;
    u64 (EFIABI *raise_tpl)(u64 tpl);
    void (EFIABI *restore_tpl)(u64 old);
    efi_status (EFIABI *allocate_pages)(int type, int mem, u64 pages,
        u64 *addr);
    void *free_pages;
    efi_status (EFIABI *get_memory_map)(u64 *size, efi_mem_desc *map, u64 *key,
        u64 *desc_size, u32 *desc_ver);
    efi_status (EFIABI *allocate_pool)(int type, u64 size, void **buf);
    efi_status (EFIABI *free_pool)(void *buf);
    void *create_event;
    void *set_timer;
    void *wait_for_event;
    void *signal_event;
    void *close_event;
    void *check_event;
    void *install_protocol;
    void *reinstall_protocol;
    void *uninstall_protocol;
    efi_status (EFIABI *handle_protocol)(efi_handle handle, u8 *guid,
        void **iface);
    char _pad1[8];
    void *register_notify;
    void *locate_handle;
    void *locate_device_path;
    void *install_config_table;
    void *load_image;
    void *start_image;
    void *exit;
    void *unload_image;
    efi_status (EFIABI *exit_boot_services)(efi_handle image, u64 key);
    efi_status (EFIABI *get_next_mono)(u64 *count);
    efi_status (EFIABI *stall)(u64 us);
    void *set_watchdog;
    void *connect_controller;
    void *disconnect_controller;
    void *open_protocol;
    void *close_protocol;
    void *open_protocol_info;
    void *protocols_per_handle;
    void *locate_handle_buffer;
    efi_status (EFIABI *locate_protocol)(void *guid, void *reg, void **iface);
    void *install_mult_protocols;
    void *uninstall_mult_protocols;
    void *calc_crc32;
    void (EFIABI *copy_mem)(void *dst, void *src, u64 len);
    void *set_mem;
    void *create_event_ex;
} efi_boot_services;

typedef struct {
    efi_table_header hdr;
    u16 *fw_vendor;
    u32 fw_revision;
    efi_handle con_in_handle;
    void *con_in;
    efi_handle con_out_handle;
    efi_simple_text_output *con_out;
    efi_handle stderr_handle;
    efi_simple_text_output *stderr_out;
    void *runtime;
    efi_boot_services *boot;
} efi_system_table;

static efi_system_table *st;
static efi_boot_services *bs;

static void com1_putc(char c) {
    unsigned short port = 0x3F8;
    unsigned char s;
    do {
        __asm__ volatile("inb %1, %0" : "=a"(s) : "Nd"((unsigned short)(port + 5)));
    } while (!(s & 0x20));
    __asm__ volatile("outb %0, %1" : : "a"((unsigned char)c), "Nd"(port));
}

static void puts_both(const char *s) {
    while (*s) {
        if (*s == '\n')
            com1_putc('\r');
        com1_putc(*s++);
    }
}

static void puts_con(const u16 *s) {
    if (st && st->con_out && st->con_out->output_string)
        st->con_out->output_string(st->con_out, (u16 *)s);
}

static void put_u64(u64 v) {
    char buf[20];
    int i = 0, k;
    if (v == 0) {
        puts_both("0");
        return;
    }
    while (v > 0 && i < 19) {
        buf[i++] = (char)('0' + (v % 10));
        v /= 10;
    }
    for (k = i - 1; k >= 0; k--) {
        char c = buf[k];
        com1_putc(c);
    }
}

static void put_hex(u64 v) {
    int i;
    puts_both("0x");
    for (i = 15; i >= 0; i--)
        com1_putc("0123456789abcdef"[(v >> (i * 4)) & 0xF]);
}

static u8 gop_guid[16] = { 0xDE, 0xA9, 0x42, 0x90, 0xDC, 0x23, 0x38, 0x4A,
    0x96, 0xFB, 0x7A, 0xDE, 0xD8, 0x05, 0x16, 0x0A };

/* Block I/O protocol (boot disk proof): Revision, Media pointer,
 * Reset, ReadBlocks, WriteBlocks, FlushBlocks. Only Media->BlockSize
 * and a one-block read are touched. */
typedef struct {
    u64 revision;
    void *media;
    void *reset;
    efi_status (EFIABI *read_blocks)(void *self, u32 media_id, u64 lba,
        u64 buf_size, void *buf);
    void *write_blocks;
    void *flush_blocks;
} efi_block_io;

typedef struct {
    u32 media_id;
    u8 removable;
    u8 present;
    u8 logical_partition;
    u8 read_only;
    u8 write_caching;
    u32 block_size;
    u32 io_align;
    u64 last_block;
} efi_block_media;

static u8 blk_guid[16] = { 0x21, 0x5B, 0x4E, 0x96, 0x59, 0x64, 0xD2, 0x11,
    0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B };

static u8 mmap_buf[16384];

#define EFI_LOADER_DATA 2
#define EFI_FILE_MODE_READ 1u
#define EFI_BUFFER_TOO_SMALL 0x8000000000000005ULL
#define UEFI_KERNEL_MAX (32u * 1024u * 1024u)

typedef struct {
    u32 rev;
    u32 _pad;
    efi_handle parent;
    void *systab;
    efi_handle dev;
} efi_loaded_image;

typedef struct efi_file efi_file;
typedef efi_status (EFIABI *efi_file_open)(efi_file *self, efi_file **nh,
    u16 *name, u64 mode, u64 attr);
typedef efi_status (EFIABI *efi_file_read)(efi_file *self, u64 *size,
    void *buf);
typedef efi_status (EFIABI *efi_file_getinfo)(efi_file *self, u8 *guid,
    u64 *size, void *buf);

struct efi_file {
    u64 rev;
    efi_file_open open;
    void *close;
    void *del;
    efi_file_read read;
    void *write;
    void *getpos;
    void *setpos;
    efi_file_getinfo get_info;
    void *set_info;
    void *flush;
};

typedef struct {
    u64 rev;
    efi_status (EFIABI *open_volume)(void *self, efi_file **root);
} efi_sfs;

static u8 sfs_guid[16] = { 0x22, 0x5B, 0x4E, 0x96, 0x59, 0x64, 0xD2, 0x11,
    0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B };

static u8 loaded_guid[16] = { 0xA1, 0x31, 0x1B, 0x5B, 0x62, 0x95, 0xD2, 0x11,
    0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B };

static u8 fileinfo_guid[16] = { 0x92, 0x6E, 0x57, 0x09, 0x3F, 0x6D, 0xD2, 0x11,
    0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B };

#define UBOOT_LOW_PAGES 160u
#define UBOOT_KERN_PAGES 768u
#define UBOOT_KERN_SPAN 0x300000UL
#define UBOOT_KERN_BASE 0x100000UL
#define UBOOT_TRAMP 0x7000UL
#define TRAMP_LGDT_OFF 53u
#define TRAMP_LEN 70u
#define UBOOT_GDT 0x8000UL
#define UBOOT_GDT_DESC 0x7E40UL

/* Trampoline copied to 0x7000 and called post-exit: CLI, PAE/LME/PG
 * onto our identity tables, RSP, LGDT (/2 is 0x15, /3 would load the
 * IDT instead), then REX.W RETF with CS 0x08 pushed (EA ptr16:32 and
 * FF/5 m16:64 both fault in long mode: #UD and #GP respectively).
 * Position-free: the only memory operand (LGDT) is RIP-relative with
 * its displacement patched at copy time. */
static const unsigned char tramp_template[TRAMP_LEN] = {
    0xFA,
    0x0F, 0x20, 0xE0, 0x83, 0xC8, 0x20, 0x0F, 0x22, 0xE0,
    0xB9, 0x80, 0x00, 0xC0, 0x00, 0x0F, 0x32,
    0x0D, 0x00, 0x01, 0x00, 0x00, 0x0F, 0x30,
    0xB8, 0x00, 0x10, 0x00, 0x00, 0x0F, 0x22, 0xD8,
    0x0F, 0x20, 0xC0, 0x0D, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x22, 0xC0,
    0x48, 0xBC, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x01, 0x15, 0x00, 0x00, 0x00, 0x00,
    0x6A, 0x08, 0xB8, 0x00, 0x00, 0x10, 0x00, 0x50, 0x48, 0xCB
};

static u64 ugop_fb;
static unsigned ugop_pitch;
static unsigned ugop_w;
static unsigned ugop_h;
static int ugop_ok;

static void w_u16(unsigned long addr, unsigned v) {
    volatile unsigned char *p = (volatile unsigned char *)addr;
    p[0] = (unsigned char)(v & 0xFFu);
    p[1] = (unsigned char)((v >> 8) & 0xFFu);
}

static void w_u32(unsigned long addr, unsigned long v) {
    volatile unsigned char *p = (volatile unsigned char *)addr;
    p[0] = (unsigned char)(v & 0xFFu);
    p[1] = (unsigned char)((v >> 8) & 0xFFu);
    p[2] = (unsigned char)((v >> 16) & 0xFFu);
    p[3] = (unsigned char)((v >> 24) & 0xFFu);
}

static void w_u64(unsigned long addr, unsigned long long v) {
    unsigned i;
    volatile unsigned char *p = (volatile unsigned char *)addr;
    for (i = 0; i < 8; i++)
        p[i] = (unsigned char)((v >> (i * 8)) & 0xFFu);
}

static void boot_kernel(unsigned long src, unsigned long len) {
    unsigned char *d = (unsigned char *)UBOOT_KERN_BASE;
    unsigned char *s = (unsigned char *)src;
    unsigned char *t = (unsigned char *)UBOOT_TRAMP;
    unsigned long n;
    unsigned i;
    unsigned disp;
    for (n = 0; n < len; n++) d[n] = s[n];
    for (n = len; n < UBOOT_KERN_SPAN; n++) d[n] = 0;
    puts_both("uefi: copied\n");
    w_u32(0x7E14u, UBOOT_KERN_BASE);
    if (ugop_ok) {
        w_u32(0x7E20u, (unsigned long)ugop_fb);
        w_u16(0x7E24u, ugop_pitch);
        w_u16(0x7E26u, ugop_w);
        w_u16(0x7E28u, ugop_h);
        *(volatile unsigned char *)0x7E2Au = 1;
        *(volatile unsigned char *)0x7E2Bu = 32;
    } else {
        for (i = 0; i < 12; i++)
            *(volatile unsigned char *)(0x7E20UL + i) = 0;
    }
    w_u64(UBOOT_GDT, 0x0000000000000000ULL);
    w_u64(UBOOT_GDT + 8u, 0x00209A0000000000ULL);
    w_u64(UBOOT_GDT + 16u, 0x0000920000000000ULL);
    w_u64(UBOOT_GDT + 24u, 0x0000F20000000000ULL);
    w_u64(UBOOT_GDT + 32u, 0x0020FA0000000000ULL);
    w_u16(UBOOT_GDT_DESC, 39u);
    w_u32(UBOOT_GDT_DESC + 2u, UBOOT_GDT);
    for (n = 0; n < 12288u; n++)
        *(volatile unsigned char *)(0x1000u + n) = 0;
    w_u64(0x1000u, 0x2003u);
    w_u64(0x2000u, 0x3003u);
    for (i = 0; i < 512; i++)
        w_u64(0x3000u + (unsigned long)i * 8u,
                ((unsigned long long)i << 21) | 0x83u);
    for (i = 0; i < TRAMP_LEN; i++) t[i] = tramp_template[i];
    disp = 0x7E40u - (UBOOT_TRAMP + TRAMP_LGDT_OFF + 7u);
    t[TRAMP_LGDT_OFF + 3u] = (unsigned char)(disp & 0xFFu);
    t[TRAMP_LGDT_OFF + 4u] = (unsigned char)((disp >> 8) & 0xFFu);
    t[TRAMP_LGDT_OFF + 5u] = (unsigned char)((disp >> 16) & 0xFFu);
    t[TRAMP_LGDT_OFF + 6u] = (unsigned char)((disp >> 24) & 0xFFu);
    ((void (*)(void))(UBOOT_TRAMP))();
}

efi_status EFIABI efi_main(efi_handle image, efi_system_table *systab) {
    efi_gop *gop = 0;
    efi_status rc;
    u64 mmap_size = 0;
    u64 mmap_key = 0;
    u64 desc_size = 0;
    u32 desc_ver = 0;
    (void)image;
    st = systab;
    bs = systab->boot;
    puts_con((u16 *)L"MiniOS UEFI stub\r\n");
    puts_both("uefi: MiniOS stub alive\n");
    rc = bs->locate_protocol(gop_guid, 0, (void **)&gop);
    if (rc == EFI_SUCCESS && gop && gop->mode && gop->mode->info) {
        puts_both("uefi: GOP ok\n");
        if (gop->mode->fb_base != 0 &&
                gop->mode->info->pixel_format >= 0 &&
                gop->mode->info->pixel_format <= 2 &&
                gop->mode->info->pixels_per_line > 0 &&
                gop->mode->info->pixels_per_line < 16384u) {
            ugop_fb = gop->mode->fb_base;
            ugop_pitch = gop->mode->info->pixels_per_line * 4u;
            ugop_w = gop->mode->info->horizontal;
            ugop_h = gop->mode->info->vertical;
            ugop_ok = (ugop_w > 0 && ugop_h > 0) ? 1 : 0;
        }
        puts_both("uefi: mode ");
        put_u64(gop->mode->mode);
        puts_both(" ");
        put_u64(gop->mode->info->horizontal);
        puts_both("x");
        put_u64(gop->mode->info->vertical);
        puts_both(" fb=");
        put_hex(gop->mode->fb_base);
        puts_both(" pitch=");
        put_u64(gop->mode->info->pixels_per_line);
        puts_both("\n");
    } else {
        puts_both("uefi: GOP unavailable\n");
    }
    rc = bs->get_memory_map(&mmap_size, 0, &mmap_key, &desc_size, &desc_ver);
    if (mmap_size == 0 || mmap_size > sizeof(mmap_buf)) {
        puts_both("uefi: mmap probe failed\n");
        for (;;) {
            __asm__ volatile("hlt");
        }
    }
    if (mmap_size > 0 && mmap_size <= sizeof(mmap_buf)) {
        rc = bs->get_memory_map(&mmap_size, (efi_mem_desc *)mmap_buf,
            &mmap_key, &desc_size, &desc_ver);
        if (rc != EFI_SUCCESS || desc_size == 0) {
            puts_both("uefi: mmap read failed\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        puts_both("uefi: mmap entries=");
        put_u64(mmap_size / desc_size);
        puts_both("\n");
    }
    puts_both("uefi: stub ok (GOP+mmap proven, kernel handoff is Phase 2)\n");
    {
        /* Boot-disk proof: the Block I/O protocol must exist (we
         * booted from this disk), and LBA 0 must carry the MBR
         * signature this image was built with. */
        efi_block_io *blk = 0;
        rc = bs->locate_protocol(blk_guid, 0, (void **)&blk);
        if (rc == EFI_SUCCESS && blk) {
            efi_block_media *m = (efi_block_media *)blk->media;
            static u8 sec[512];
            if (m && blk->read_blocks) {
                rc = blk->read_blocks(blk, m->media_id, 0, 512, sec);
                if (rc == EFI_SUCCESS && sec[510] == 0x55 && sec[511] == 0xAA)
                    puts_both("uefi: LBA0 ok\n");
                else
                    puts_both("uefi: LBA0 mismatch\n");
            } else {
                puts_both("uefi: blockio unavailable\n");
            }
        } else {
            puts_both("uefi: blockio unavailable\n");
        }
    }
    {
        efi_loaded_image *loaded = 0;
        efi_sfs *fs = 0;
        efi_file *root = 0;
        efi_file *kfile = 0;
        u64 info_size = 0;
        u64 fsize = 0;
        void *kbuf = 0;
        unsigned char *magic = 0;
        rc = bs->handle_protocol(image, loaded_guid, (void **)&loaded);
        if (rc == EFI_SUCCESS && loaded && loaded->dev)
            rc = bs->handle_protocol(loaded->dev, sfs_guid, (void **)&fs);
        else
            rc = 1;
        if (rc == EFI_SUCCESS && fs && fs->open_volume)
            rc = fs->open_volume(fs, &root);
        else
            rc = 1;
        if (rc == EFI_SUCCESS && root && root->open)
            rc = root->open(root, &kfile, (u16 *)L"kernel.bin",
                EFI_FILE_MODE_READ, 0);
        else
            rc = 1;
        if (rc != EFI_SUCCESS || !kfile || !kfile->get_info || !kfile->read) {
            puts_both("uefi: SFS unavailable\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        puts_both("uefi: SFS ok\n");
        rc = kfile->get_info(kfile, fileinfo_guid, &info_size, (void *)0);
        if ((rc != EFI_SUCCESS && rc != EFI_BUFFER_TOO_SMALL) ||
                info_size < 16 || info_size > 4096) {
            puts_both("uefi: kernel.bin unreadable\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        {
            void *ibuf = 0;
            unsigned char *ib = 0;
            unsigned i;
            rc = bs->allocate_pool(EFI_LOADER_DATA, info_size, &ibuf);
            if (rc != EFI_SUCCESS || !ibuf) {
                puts_both("uefi: kernel.bin unreadable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
            rc = kfile->get_info(kfile, fileinfo_guid, &info_size, ibuf);
            if (rc != EFI_SUCCESS) {
                puts_both("uefi: kernel.bin unreadable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
            ib = (unsigned char *)ibuf;
            fsize = 0;
            for (i = 0; i < 8; i++)
                fsize |= (u64)ib[8 + i] << (i * 8);
            bs->free_pool(ibuf);
        }
        if (fsize < 4096 || fsize > UEFI_KERNEL_MAX) {
            puts_both("uefi: kernel.bin unreadable\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        rc = bs->allocate_pool(EFI_LOADER_DATA, fsize, &kbuf);
        if (rc != EFI_SUCCESS || !kbuf) {
            puts_both("uefi: kernel.bin unreadable\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        {
            u64 want = fsize;
            rc = kfile->read(kfile, &fsize, kbuf);
            if (rc != EFI_SUCCESS || fsize != want) {
                puts_both("uefi: kernel.bin unreadable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
        }
        puts_both("uefi: kernel ");
        put_u64(fsize);
        puts_both(" bytes\n");
        magic = (unsigned char *)kbuf;
        if (fsize < 4096 || (magic[0] | magic[1] | magic[2] | magic[3]) == 0) {
            puts_both("uefi: image mismatch\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        puts_both("uefi: image ok\n");
        {
            u64 kb = (u64)UBOOT_KERN_BASE;
            u64 r1 = 0x1000u;
            u64 r2 = 0x10000u;
            rc = bs->allocate_pages(2, 2, 8u, &r1);
            if (rc != EFI_SUCCESS || r1 != 0x1000u) {
                puts_both("uefi: low tables unavailable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
            rc = bs->allocate_pages(2, 2, 96u, &r2);
            if (rc != EFI_SUCCESS || r2 != 0x10000u) {
                puts_both("uefi: user tables unavailable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
            {
                u64 off;
                int ok = 1;
                for (off = 0; off + desc_size <= mmap_size; off += desc_size) {
                    efi_mem_desc *d = (efi_mem_desc *)(mmap_buf + off);
                    u64 start = d->phys;
                    u64 end = d->phys + d->pages * 4096u;
                    unsigned t;
                    if (desc_size == 0 || end <= 0x80000u || start >= 0x9F000u)
                        continue;
                    t = d->type;
                    if (t != 1 && t != 2 && t != 3 && t != 4 && t != 7 &&
                            t != 9)
                        ok = 0;
                }
                if (!ok) {
                    puts_both("uefi: stack memory reserved\n");
                    for (;;) {
                        __asm__ volatile("hlt");
                    }
                }
                puts_both("uefi: stack zone borrowed post-exit\n");
            }
            rc = bs->allocate_pages(2, 2, UBOOT_KERN_PAGES, &kb);
            if (rc != EFI_SUCCESS || kb != (u64)UBOOT_KERN_BASE) {
                puts_both("uefi: kernel memory unavailable\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
        }
        mmap_size = sizeof(mmap_buf);
        rc = bs->get_memory_map(&mmap_size, (efi_mem_desc *)mmap_buf,
            &mmap_key, &desc_size, &desc_ver);
        if (rc != EFI_SUCCESS || desc_size == 0) {
            puts_both("uefi: mmap read failed\n");
            for (;;) {
                __asm__ volatile("hlt");
            }
        }
        {
            u64 entries = mmap_size / desc_size;
            rc = bs->exit_boot_services(image, mmap_key);
            if (rc != EFI_SUCCESS) {
                puts_both("uefi: exit failed\n");
                for (;;) {
                    __asm__ volatile("hlt");
                }
            }
            puts_both("uefi: exited boot services\n");
            puts_both("uefi: handoff kernel=");
            put_u64(fsize);
            puts_both(" mmap=");
            put_u64(entries);
            puts_both("\n");
            puts_both("uefi: jumping to kernel\n");
            boot_kernel((unsigned long)kbuf, (unsigned long)fsize);
            puts_both("uefi: jump failed\n");
        }
    }
    for (;;) {
        __asm__ volatile("hlt");
    }
}
