#ifndef MINIFS_H
#define MINIFS_H

/* MiniFS: a minimal Unix-like filesystem for MiniOS.
 * Inode-based, bitmap-allocated, with optional LZ4 compression.
 * Designed for a QEMU IDE disk appended after the kernel image. */

#define MINIFS_MAGIC         0x4D494E49
#define MINIFS_VERSION       1
#define MINIFS_BLOCK_SIZE    4096
#define MINIFS_MAX_FILENAME  255
#define MINIFS_ROOT_INODE    2
#define MINIFS_INODES_PER_BLOCK  (MINIFS_BLOCK_SIZE / 128)
#define MINIFS_DIR_ENTRIES_PER_BLOCK (MINIFS_BLOCK_SIZE / 64)

#define MINIFS_S_IFMT       0170000
#define MINIFS_S_IFREG      0100000
#define MINIFS_S_IFDIR      0040000
#define MINIFS_S_IFLNK      0120000
#define MINIFS_S_IRWXU      00700
#define MINIFS_S_IRWXG      00070
#define MINIFS_S_IRWXO      00007

#define MINIFS_FT_FILE      1
#define MINIFS_FT_DIR       2
#define MINIFS_FT_SYMLINK   3

#define MINIFS_INODE_COMPRESSED  0x01

unsigned int minifs_compress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);
unsigned int minifs_decompress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);

typedef struct {
    unsigned int magic;
    unsigned int version;
    unsigned int block_size;
    unsigned int total_blocks;
    unsigned int free_blocks;
    unsigned int total_inodes;
    unsigned int free_inodes;
    unsigned int root_inode;
    unsigned int inode_bitmap_start;
    unsigned int block_bitmap_start;
    unsigned int inode_table_start;
    unsigned int data_start;
    unsigned int first_free_hint;
    unsigned char compression;
    unsigned char dirty;
    unsigned short checksum;
} MiniFSSuper;

typedef struct {
    unsigned short mode;
    unsigned short link_count;
    unsigned int uid;
    unsigned int size;
    unsigned int atime;
    unsigned int ctime;
    unsigned int mtime;
    unsigned int direct[10];
    unsigned int indirect;
    unsigned int dindirect;
    unsigned int flags;
    unsigned int checksum;
    unsigned char __pad[48];  /* pad to 128 bytes for on-disk slot */
} MiniFSInode;

typedef struct {
    unsigned int inode;
    unsigned short rec_len;
    unsigned char name_len;
    unsigned char file_type;
} MiniFSDirEntry;

#define MINIFS_DIR_ENTRY_HDR_SIZE sizeof(MiniFSDirEntry)

#define MINIFS_JOURNAL_BLOCKS  64
#define MINIFS_JOURNAL_MAX_ENTRIES 62
#define MINIFS_JOP_WRITE    1
#define MINIFS_JOP_CREATE   2
#define MINIFS_JOP_DELETE   3
#define MINIFS_JOP_MKDIR    4
#define MINIFS_JOP_RMDIR    5
#define MINIFS_JOP_TRUNCATE 6
#define MINIFS_JOP_COMMIT   7

#define MINIFS_JSTATE_CLEAN    0
#define MINIFS_JSTATE_DIRTY    1

typedef struct {
    unsigned int magic;
    unsigned int state;
    unsigned int next_txn;
    unsigned int count;
    unsigned int checksum;
} MiniFSJournalSuper;

typedef struct {
    unsigned int txn_id;
    unsigned char op_type;
    unsigned char committed;
    unsigned short num_blocks;
    unsigned int inode_num;
    unsigned int old_size;
    unsigned int new_size;
    unsigned int affected_blocks[16];
    unsigned int checksum;
} MiniFSJournalEntry;

typedef struct {
    int inode_num;
    unsigned int pos;
    int flags;
    MiniFSInode *inode_cache;
} MiniFSFile;

void minifs_init(void);
int  minifs_mount(void);
int  minifs_mkfs(unsigned int total_blocks);
int  minifs_sync(void);
int  minifs_is_mounted(void);

int  minifs_create(const char *path, unsigned short mode);
int  minifs_mkdir(const char *path, unsigned short mode);
int  minifs_unlink(const char *path);
int  minifs_rmdir(const char *path);
int  minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len);
int  minifs_write(int inode_num, const void *buf, unsigned int offset, unsigned int len);
int  minifs_truncate(int inode_num, unsigned int new_size);
int  minifs_stat(int inode_num, MiniFSInode *out);
int  minifs_access(const char *path);

int  minifs_resolve_path(const char *path);
int  minifs_dir_lookup(int dir_inode, const char *name);
int  minifs_dir_add_entry(int dir_inode, const char *name, int child_inode, unsigned char type);
int  minifs_dir_remove_entry(int dir_inode, const char *name);
int  minifs_dir_read(int dir_inode, int index, MiniFSDirEntry *out, char *name_out);

int  minifs_alloc_block(void);
void minifs_free_block(unsigned int block);
int  minifs_alloc_inode(void);
void minifs_free_inode(int inode_num);
int  minifs_inode_get_block(MiniFSInode *inode, unsigned int logical_block, unsigned int *phys_block);
int  minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logical_block);

void minifs_journal_begin(unsigned int txn_id);
void minifs_journal_add_block(unsigned int block);
int  minifs_journal_commit(unsigned int txn_id);
void minifs_journal_recover(void);

MiniFSFile *minifs_file_open(int inode_num, int flags);
int  minifs_file_close(MiniFSFile *f);

unsigned int minifs_get_lba_start(void);
unsigned int minifs_get_total_blocks(void);

#endif
