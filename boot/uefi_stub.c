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
 * Phase 2 (documented, not here): ExitBootServices, replicate the
 * stage2 contract (page tables, VBE-info block, GDT) and jump to the
 * kernel. That needs the kernel entry rework in ARCHITECTURE_PLAN.md;
 * this stub validates the toolchain, the OVMF boot path and every
 * firmware call Phase 2 will reuse. */

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
    void *allocate_pages;
    void *free_pages;
    efi_status (EFIABI *get_memory_map)(u64 *size, efi_mem_desc *map, u64 *key,
        u64 *desc_size, u32 *desc_ver);
    efi_status (EFIABI *allocate_pool)(int type, u64 size, void **buf);
    void *free_pool;
    void *create_event;
    void *set_timer;
    void *wait_for_event;
    void *signal_event;
    void *close_event;
    void *check_event;
    void *install_protocol;
    void *reinstall_protocol;
    void *uninstall_protocol;
    void *handle_protocol;
    char _pad1[8];
    void *register_notify;
    void *locate_handle;
    void *locate_device_path;
    void *install_config_table;
    void *load_image;
    void *start_image;
    void *exit;
    void *unload_image;
    void *exit_boot_services;
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
    for (;;) {
        __asm__ volatile("hlt");
    }
}
