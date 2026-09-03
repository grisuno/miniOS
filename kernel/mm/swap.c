/* swap.c - Swap-out/swap-in for the user window (LZ4-compressed disk swap).
 *
 * Extracted from kernel.c. Provides:
 *   swap_out  - write parent's user window to swap area, compressed
 *   swap_in   - restore parent's user window from swap area
 *
 * Used by k_syscall_spawn (SYS_SPAWN) to preserve the parent's memory
 * across a child process execution.
 */

#include "kernel.h"
#include "ide.h"
#include "lz4_kernel.h"

#define SWAP_CHUNK_RAW     65536
#define SWAP_CHUNK_SECTORS 128
#define SWAP_HDR_SECTORS   1
#define SWAP_MAX_SECTORS   131072
#define SWAP_MAGIC         0x53574150

static unsigned char swap_buf_raw[SWAP_CHUNK_RAW];
static unsigned char swap_buf_cmp[SWAP_CHUNK_RAW + 1024];

static unsigned long swap_lba(void) {
    unsigned int total = ide_total_sectors();
    if (total <= SWAP_MAX_SECTORS) return 0;
    return (unsigned long)(total - SWAP_MAX_SECTORS);
}

int swap_out(unsigned long window_sz) {
    unsigned long slba = swap_lba();
    if (!slba) return 0;
    unsigned long nchunks = (window_sz + SWAP_CHUNK_RAW - 1) / SWAP_CHUNK_RAW;
    if (nchunks * SWAP_CHUNK_SECTORS + SWAP_HDR_SECTORS > SWAP_MAX_SECTORS)
        return 0;

    unsigned long data_lba = slba;
    for (unsigned long i = 0; i < nchunks; i++) {
        unsigned long off = i * SWAP_CHUNK_RAW;
        unsigned long raw_sz = window_sz - off;
        if (raw_sz > SWAP_CHUNK_RAW) raw_sz = SWAP_CHUNK_RAW;

        kmemcpy(swap_buf_raw, (void *)(USER_LOAD_BASE + off), raw_sz);
        if (raw_sz < SWAP_CHUNK_RAW)
            kmemset(swap_buf_raw + raw_sz, 0, SWAP_CHUNK_RAW - raw_sz);

        int csz = LZ4_compress_default((const char *)swap_buf_raw,
                    (char *)swap_buf_cmp + 4,
                    (int)SWAP_CHUNK_RAW, (int)(sizeof(swap_buf_cmp) - 4));
        unsigned int disk_csz;
        if (csz > 0 && (unsigned long)csz < raw_sz) {
            disk_csz = (unsigned int)csz;
        } else {
            disk_csz = 0;
            kmemcpy(swap_buf_cmp + 4, swap_buf_raw, raw_sz);
        }
        *(unsigned int *)swap_buf_cmp = disk_csz;

        unsigned long total = 4 + (disk_csz ? disk_csz : raw_sz);
        unsigned long sects = (total + IDE_SECTOR_SIZE - 1) / IDE_SECTOR_SIZE;
        if (ide_write_sectors((unsigned int)data_lba, (unsigned int)sects,
                              swap_buf_cmp) < 0)
            return 0;
        data_lba += sects;
    }

    unsigned long hdr_lba = slba + SWAP_MAX_SECTORS - SWAP_HDR_SECTORS;
    unsigned int hdr[3];
    hdr[0] = SWAP_MAGIC;
    hdr[1] = (unsigned int)window_sz;
    hdr[2] = (unsigned int)nchunks;
    kmemset(hdr + 3, 0, IDE_SECTOR_SIZE - 12);
    if (ide_write_sectors((unsigned int)hdr_lba, SWAP_HDR_SECTORS, hdr) < 0)
        return 0;

    return 1;
}

int swap_in(void) {
    unsigned long slba = swap_lba();
    if (!slba) return 0;

    unsigned long hdr_lba = slba + SWAP_MAX_SECTORS - SWAP_HDR_SECTORS;
    unsigned int hdr[3];
    if (ide_read_sectors((unsigned int)hdr_lba, SWAP_HDR_SECTORS, hdr) < 0)
        return 0;
    if (hdr[0] != SWAP_MAGIC) return 0;
    unsigned long window_sz = hdr[1];
    unsigned long nchunks   = hdr[2];

    unsigned long data_lba = slba;
    unsigned long dst = USER_LOAD_BASE;
    for (unsigned long i = 0; i < nchunks; i++) {
        if (ide_read_sectors((unsigned int)data_lba, SWAP_CHUNK_SECTORS,
                             swap_buf_cmp) < 0)
            return 0;
        unsigned int csz = *(unsigned int *)swap_buf_cmp;

        unsigned long raw_sz = window_sz - (dst - USER_LOAD_BASE);
        if (raw_sz > SWAP_CHUNK_RAW) raw_sz = SWAP_CHUNK_RAW;

        if (csz) {
            int dsz = LZ4_decompress_safe((const char *)swap_buf_cmp + 4,
                        (char *)swap_buf_raw, (int)csz, (int)SWAP_CHUNK_RAW);
            if (dsz < 0 || (unsigned long)dsz != raw_sz)
                return 0;
        } else {
            kmemcpy(swap_buf_raw, swap_buf_cmp + 4, raw_sz);
        }
        kmemcpy((void *)dst, swap_buf_raw, raw_sz);
        dst += raw_sz;
        data_lba += SWAP_CHUNK_SECTORS;
    }
    return 1;
}
