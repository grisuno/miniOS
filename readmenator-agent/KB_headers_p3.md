# Subsystem: headers (page 3 of 5)
Previous: [KB_headers_p2.md](KB_headers_p2.md)

## headers/lz4_kernel.h
- Layer: utility
- Language: h
- Symbols:
  - `LZ4_compress_default` (function, line 4) `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity);`
  - `LZ4_compressBound` (function, line 5) `int LZ4_compressBound(int inputSize);`
  - `LZ4_decompress_safe` (function, line 6) `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity);`
  - `LZ4_KERNEL_H` (macro, line 2) `#define LZ4_KERNEL_H`
- Imported by: `fs/minifs.c`, `kernel/lz4_kernel.c`, `kernel/mm/swap.c`, `kernel/syscalls.c`

## headers/minifetch.h
- Doc: Docstring: minifetch.h -- neofetch-style system screen contract.
- Layer: utility
- Language: h
- Symbols:
  - `shell_cmd_minifetch` (function, line 14) `void shell_cmd_minifetch(void);`
  - `MINIFETCH_H` (macro, line 12) `#define MINIFETCH_H`
- Imported by: `kernel/minifetch.c`, `kernel/shell.c`

## headers/minifs.h
- Doc: MiniFS: a minimal Unix-like filesystem for MiniOS.
- Layer: utility
- Language: h
- Symbols:
  - `MiniFSSuper` (struct, line 33)
  - `MiniFSInode` (struct, line 52)
  - `MiniFSDirEntry` (struct, line 68)
  - `MiniFSJournalSuper` (struct, line 90)
  - `MiniFSJournalEntry` (struct, line 98)
  - `MiniFSFile` (struct, line 110)
  - `minifs_compress` (function, line 30) `unsigned int minifs_compress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
  - `minifs_decompress` (function, line 31) `unsigned int minifs_decompress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
  - `minifs_init` (function, line 117) `void minifs_init(void);`
  - `minifs_mount` (function, line 118) `int minifs_mount(void);`
  - `minifs_mkfs` (function, line 119) `int minifs_mkfs(unsigned int total_blocks);`
  - `minifs_sync` (function, line 120) `int minifs_sync(void);`
  - `minifs_is_mounted` (function, line 121) `int minifs_is_mounted(void);`
  - `minifs_create` (function, line 123) `int minifs_create(const char *path, unsigned short mode);`
  - `minifs_mkdir` (function, line 124) `int minifs_mkdir(const char *path, unsigned short mode);`
  - `minifs_unlink` (function, line 125) `int minifs_unlink(const char *path);`
  - `minifs_rmdir` (function, line 126) `int minifs_rmdir(const char *path);`
  - `refuses` (function, line 129) `* An existing file dst refuses (no silent overwrite);`
  - `minifs_rename` (function, line 131) `int minifs_rename(const char *oldpath, const char *newpath);`
  - `minifs_read` (function, line 132) `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len);`
  - `minifs_write` (function, line 133) `int minifs_write(int inode_num, const void *buf, unsigned int offset, unsigned int len);`
  - `minifs_truncate` (function, line 134) `int minifs_truncate(int inode_num, unsigned int new_size);`
  - `minifs_stat` (function, line 135) `int minifs_stat(int inode_num, MiniFSInode *out);`
  - `minifs_access` (function, line 136) `int minifs_access(const char *path);`
  - `minifs_resolve_path` (function, line 138) `int minifs_resolve_path(const char *path);`
  - `minifs_dir_lookup` (function, line 139) `int minifs_dir_lookup(int dir_inode, const char *name);`
  - `minifs_dir_add_entry` (function, line 140) `int minifs_dir_add_entry(int dir_inode, const char *name, int child_inode, unsigned char type);`
  - `minifs_dir_remove_entry` (function, line 141) `int minifs_dir_remove_entry(int dir_inode, const char *name);`
  - `minifs_dir_read` (function, line 142) `int minifs_dir_read(int dir_inode, int index, MiniFSDirEntry *out, char *name_out);`
  - `minifs_alloc_block` (function, line 144) `int minifs_alloc_block(void);`
  - `minifs_free_block` (function, line 145) `void minifs_free_block(unsigned int block);`
  - `minifs_alloc_inode` (function, line 146) `int minifs_alloc_inode(void);`
  - `minifs_free_inode` (function, line 147) `void minifs_free_inode(int inode_num);`
  - `minifs_inode_get_block` (function, line 148) `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logical_block, unsigned int *phys_block);`
  - `minifs_inode_alloc_block` (function, line 149) `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logical_block);`
  - `minifs_journal_begin` (function, line 151) `void minifs_journal_begin(unsigned int txn_id);`
  - `minifs_journal_add_block` (function, line 152) `void minifs_journal_add_block(unsigned int block);`
  - `minifs_journal_touch` (function, line 153) `void minifs_journal_touch(unsigned int phys);`
  - `minifs_journal_commit` (function, line 154) `int minifs_journal_commit(unsigned int txn_id);`
  - `minifs_journal_clear` (function, line 155) `void minifs_journal_clear(void);`
  - `minifs_journal_abort` (function, line 156) `void minifs_journal_abort(void);`
  - `minifs_journal_recover` (function, line 157) `void minifs_journal_recover(void);`
  - `minifs_file_open` (function, line 159) `MiniFSFile *minifs_file_open(int inode_num, int flags);`
  - `minifs_file_close` (function, line 160) `int minifs_file_close(MiniFSFile *f);`
  - `minifs_get_lba_start` (function, line 162) `unsigned int minifs_get_lba_start(void);`
  - `minifs_get_total_blocks` (function, line 163) `unsigned int minifs_get_total_blocks(void);`
  - `minifs_usage` (function, line 165) `void minifs_usage(unsigned int *free_b, unsigned int *total_b, unsigned int *free_i, unsigned int *total_i);`
  - `MINIFS_H` (macro, line 2) `#define MINIFS_H`
  - `MINIFS_MAGIC` (macro, line 8) `#define MINIFS_MAGIC`
  - `MINIFS_VERSION` (macro, line 9) `#define MINIFS_VERSION`
  - `MINIFS_BLOCK_SIZE` (macro, line 10) `#define MINIFS_BLOCK_SIZE`
  - `MINIFS_MAX_FILENAME` (macro, line 11) `#define MINIFS_MAX_FILENAME`
  - `MINIFS_ROOT_INODE` (macro, line 12) `#define MINIFS_ROOT_INODE`
  - `MINIFS_INODES_PER_BLOCK` (macro, line 13) `#define MINIFS_INODES_PER_BLOCK`
  - `MINIFS_DIR_ENTRIES_PER_BLOCK` (macro, line 14) `#define MINIFS_DIR_ENTRIES_PER_BLOCK`
  - `MINIFS_S_IFMT` (macro, line 16) `#define MINIFS_S_IFMT`
  - `MINIFS_S_IFREG` (macro, line 17) `#define MINIFS_S_IFREG`
  - `MINIFS_S_IFDIR` (macro, line 18) `#define MINIFS_S_IFDIR`
  - `MINIFS_S_IFLNK` (macro, line 19) `#define MINIFS_S_IFLNK`
  - `MINIFS_S_IRWXU` (macro, line 20) `#define MINIFS_S_IRWXU`
  - `MINIFS_S_IRWXG` (macro, line 21) `#define MINIFS_S_IRWXG`
  - `MINIFS_S_IRWXO` (macro, line 22) `#define MINIFS_S_IRWXO`
  - `MINIFS_FT_FILE` (macro, line 24) `#define MINIFS_FT_FILE`
  - `MINIFS_FT_DIR` (macro, line 25) `#define MINIFS_FT_DIR`
  - `MINIFS_FT_SYMLINK` (macro, line 26) `#define MINIFS_FT_SYMLINK`
  - `MINIFS_INODE_COMPRESSED` (macro, line 28) `#define MINIFS_INODE_COMPRESSED`
  - `MINIFS_DIR_ENTRY_HDR_SIZE` (macro, line 75) `#define MINIFS_DIR_ENTRY_HDR_SIZE`
  - `MINIFS_JOURNAL_BLOCKS` (macro, line 77) `#define MINIFS_JOURNAL_BLOCKS`
  - `MINIFS_JOURNAL_MAX_ENTRIES` (macro, line 78) `#define MINIFS_JOURNAL_MAX_ENTRIES`
  - `MINIFS_JOP_WRITE` (macro, line 79) `#define MINIFS_JOP_WRITE`
  - `MINIFS_JOP_CREATE` (macro, line 80) `#define MINIFS_JOP_CREATE`
  - `MINIFS_JOP_DELETE` (macro, line 81) `#define MINIFS_JOP_DELETE`
  - `MINIFS_JOP_MKDIR` (macro, line 82) `#define MINIFS_JOP_MKDIR`
  - `MINIFS_JOP_RMDIR` (macro, line 83) `#define MINIFS_JOP_RMDIR`
  - `MINIFS_JOP_TRUNCATE` (macro, line 84) `#define MINIFS_JOP_TRUNCATE`
  - `MINIFS_JOP_COMMIT` (macro, line 85) `#define MINIFS_JOP_COMMIT`
  - `MINIFS_JSTATE_CLEAN` (macro, line 87) `#define MINIFS_JSTATE_CLEAN`
  - `MINIFS_JSTATE_DIRTY` (macro, line 88) `#define MINIFS_JSTATE_DIRTY`
- Imported by: `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `fs/kfile.c`, `fs/minifs.c`, `fs/vfs.c`, `kernel.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm/paging.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `tests/test_ext4.c`, `tests/test_fat32.c`

## headers/net.h
- Doc: net_cmd_status: net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and *...
- Layer: utility
- Language: h
- Symbols:
  - `ring` (function, line 46) `* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SOCK_RX_BUF 16384 #define...`
  - `net_register_symbols` (function, line 66) `void net_register_symbols(void);`
  - `net_cmd_status` (function, line 69) `void net_cmd_status(void);`
  - `net_cmd_ping` (function, line 70) `void net_cmd_ping(const char *ip_text);`
  - `net_get_addrs` (function, line 71) `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]);`
  - `net_cmd_dns` (function, line 72) `void net_cmd_dns(const char *host);`
  - `net_open` (function, line 75) `int net_open(void);`
  - `net_connect` (function, line 76) `int net_connect(const char *host, unsigned short port);`
  - `net_send` (function, line 77) `int net_send(int fd, const char *buf, int len);`
  - `net_recv` (function, line 78) `int net_recv(int fd, char *buf, int len);`
  - `net_recv_timeout` (function, line 80) `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);`
  - `net_close` (function, line 81) `void net_close(int fd);`
  - `demux` (function, line 87) `* segment through the production demux (httpd selftest). */ int net_listen(unsigned short port);`
  - `net_accept_nb` (function, line 89) `int net_accept_nb(int fd);`
  - `net_accept` (function, line 90) `int net_accept(int fd, unsigned long timeout_ms);`
  - `net_sock_state` (function, line 91) `int net_sock_state(int fd);`
  - `net_sock_seq` (function, line 92) `int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out);`
  - `net_test_inject_tcp` (function, line 93) `int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport, unsigned short lport, unsigned char...`
  - `net_sys_socket` (function, line 98) `long net_sys_socket(long a1, long a2, long a3);`
  - `net_sys_connect` (function, line 99) `long net_sys_connect(long fd, long sockaddr, long addrlen);`
  - `net_sys_bind` (function, line 100) `long net_sys_bind(long fd, long sockaddr, long addrlen);`
  - `net_sys_listen` (function, line 101) `long net_sys_listen(long fd, long backlog);`
  - `net_sys_accept` (function, line 102) `long net_sys_accept(long fd, long sockaddr, long addrlen);`
  - `net_sys_sendto` (function, line 103) `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);`
  - `net_sys_recvfrom` (function, line 104) `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);`
  - `net_sys_shutdown` (function, line 105) `long net_sys_shutdown(long fd, long how);`
  - `net_sys_close` (function, line 106) `long net_sys_close(long fd);`
  - `net_sys_poll` (function, line 107) `long net_sys_poll(long fds, long nfds, long timeout_ms);`
  - `net_sys_dns` (function, line 108) `long net_sys_dns(long host);`
  - `net_time_ms` (function, line 111) `unsigned long net_time_ms(void);`
  - `net_rx_handle_frame` (function, line 115) `void net_rx_handle_frame(const unsigned char *frame, unsigned len);`
  - `stack` (function, line 118) `* the stack (dropped fragments);`
  - `tls_free_fd` (function, line 126) `void tls_free_fd(int fd);`
  - `net_rx_dropped` (variable, line 119) `extern unsigned int net_rx_dropped;`
  - `net6_rx_dropped` (variable, line 120) `extern unsigned int net6_rx_dropped;`
  - `NET_H` (macro, line 2) `#define NET_H`
  - `NET_IP_ADDR` (macro, line 5) `#define NET_IP_ADDR`
  - `NET_NETMASK` (macro, line 6) `#define NET_NETMASK`
  - `NET_GATEWAY` (macro, line 7) `#define NET_GATEWAY`
  - `NET_DNS` (macro, line 8) `#define NET_DNS`
  - `NET_PCI_VENDOR` (macro, line 11) `#define NET_PCI_VENDOR`
  - `NET_PCI_DEVICE` (macro, line 12) `#define NET_PCI_DEVICE`
  - `NET_RX_BUF_LEN` (macro, line 18) `#define NET_RX_BUF_LEN`
  - `NET_RX_ALIGN` (macro, line 19) `#define NET_RX_ALIGN`
  - `NET_RCR` (macro, line 22) `#define NET_RCR`
  - `NET_MAX_FRAME` (macro, line 23) `#define NET_MAX_FRAME`
  - `NET_TX_SLOTS` (macro, line 24) `#define NET_TX_SLOTS`
  - `NET_ETH_ALEN` (macro, line 27) `#define NET_ETH_ALEN`
  - `NET_ETHERTYPE_IP` (macro, line 28) `#define NET_ETHERTYPE_IP`
  - `NET_ETHERTYPE_ARP` (macro, line 29) `#define NET_ETHERTYPE_ARP`
  - `NET_ETHERTYPE_IPV6` (macro, line 30) `#define NET_ETHERTYPE_IPV6`
  - `NET_PROTO_ICMP` (macro, line 33) `#define NET_PROTO_ICMP`
  - `NET_PROTO_TCP` (macro, line 34) `#define NET_PROTO_TCP`
  - `NET_PROTO_UDP` (macro, line 35) `#define NET_PROTO_UDP`
  - `NET_ARP_CACHE` (macro, line 38) `#define NET_ARP_CACHE`
  - `NET_ARP_REQUEST` (macro, line 39) `#define NET_ARP_REQUEST`
  - `NET_ARP_REPLY` (macro, line 40) `#define NET_ARP_REPLY`
  - `NET_TCP_MSS` (macro, line 43) `#define NET_TCP_MSS`
  - `NET_TCP_WINDOW` (macro, line 44) `#define NET_TCP_WINDOW`
  - `NET_SOCK_RX_BUF` (macro, line 47) `#define NET_SOCK_RX_BUF`
  - `NET_RX_RING_SIZE` (macro, line 48) `#define NET_RX_RING_SIZE`
  - `NET_SOCKETS` (macro, line 49) `#define NET_SOCKETS`
  - `NET_DNS_PORT` (macro, line 50) `#define NET_DNS_PORT`
  - `NET_EPHEMERAL_MIN` (macro, line 51) `#define NET_EPHEMERAL_MIN`
  - `NET_DNS_TRIES` (macro, line 52) `#define NET_DNS_TRIES`
  - `NET_DNS_TMO_MS` (macro, line 53) `#define NET_DNS_TMO_MS`
  - `NET_CONNECT_TMO_S` (macro, line 54) `#define NET_CONNECT_TMO_S`
  - `NET_RETRY_MS` (macro, line 55) `#define NET_RETRY_MS`
  - `NET_ACCEPT_TMO_MS` (macro, line 56) `#define NET_ACCEPT_TMO_MS`
  - `NET_TX_MAX` (macro, line 57) `#define NET_TX_MAX`
  - `NET_FD_BASE` (macro, line 60) `#define NET_FD_BASE`
- Imported by: `drivers/virtio_net.c`, `headers/net/rtl8139.h`, `headers/tls_port.h`, `kernel.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `net/net.c`, `net/rtl8139.c`

## headers/panic.h
- Doc: Docstring: panic.h -- Kernel panic backtrace contract (header-only).
- Layer: utility
- Language: h
- Symbols:
  - `panic_backtrace` (function, line 25) `static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid,
        unsigned long ...`
  - `PANIC_H` (macro, line 15) `#define PANIC_H`
  - `PANIC_BT_MAX` (macro, line 17) `#define PANIC_BT_MAX`
- Imported by: `kernel/panic.c`, `tests/test_panic.c`

## headers/pcache.h
- Doc: Docstring: pcache.h -- page cache for MiniFS, slice 1 (store only).
- Layer: utility
- Language: h
- Symbols:
  - `pcache_init` (function, line 28) `void pcache_init(void);`
  - `pcache_lookup` (function, line 32) `int pcache_lookup(int ino, unsigned index);`
  - `pcache_get` (function, line 42) `int pcache_get(int ino, unsigned index, int *is_new);`
  - `pcache_publish` (function, line 51) `int pcache_publish(int ino, unsigned index, const unsigned char *data);`
  - `pcache_put` (function, line 55) `void pcache_put(int slot);`
  - `pcache_ref` (function, line 61) `int pcache_ref(int ino, unsigned index);`
  - `pcache_unmap` (function, line 69) `void pcache_unmap(int ino, unsigned index);`
  - `match` (function, line 75) `* a phys match (owned, ref dropped unless already zero), 0 * otherwise. */ int pcache_put_if(int ino, unsigned...`
  - `pcache_ref_if` (function, line 83) `int pcache_ref_if(int ino, unsigned index, unsigned long phys);`
  - `pcache_owns_phys` (function, line 88) `int pcache_owns_phys(unsigned long phys);`
  - `pcache_data` (function, line 93) `unsigned char *pcache_data(int slot);`
  - `pcache_mark_dirty` (function, line 98) `void pcache_mark_dirty(int slot);`
  - `pcache_invalidate_ino` (function, line 102) `void pcache_invalidate_ino(int ino);`
  - `pcache_stats` (function, line 106) `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out, unsigned long *miss_out, unsigned long...`
  - `PCACHE_H` (macro, line 17) `#define PCACHE_H`
  - `PCACHE_PAGES` (macro, line 20) `#define PCACHE_PAGES`
  - `PCACHE_PAGE` (macro, line 23) `#define PCACHE_PAGE`
- Imported by: `fs/minifs.c`, `fs/pcache.c`, `kernel.c`, `kernel/loader.c`, `kernel/mm/paging.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_pcache.c`

## headers/pcm2.h
- Doc: low-latency PCM audio path over SB16 single-cycle DMA.
- Layer: utility
- Language: h
- Symbols:
  - `pcm2_counters_t` (struct, line 67)
  - `pcm2_active` (function, line 77) `int pcm2_active(void);`
  - `pcm2_open` (function, line 78) `int pcm2_open(unsigned flags, int owner);`
  - `pcm2_write` (function, line 79) `int pcm2_write(const unsigned char *user, unsigned len, int owner);`
  - `pcm2_close` (function, line 80) `void pcm2_close(int owner);`
  - `pcm2_irq` (function, line 81) `void pcm2_irq(void);`
  - `pcm2_poll` (function, line 82) `void pcm2_poll(void);`
  - `pcm2_counters` (function, line 83) `void pcm2_counters(pcm2_counters_t *out);`
  - `PCM2_H` (macro, line 2) `#define PCM2_H`
  - `PCM2_RATE` (macro, line 52) `#define PCM2_RATE`
  - `PCM2_FRAG` (macro, line 53) `#define PCM2_FRAG`
  - `PCM2_FRAGS` (macro, line 54) `#define PCM2_FRAGS`
  - `PCM2_DMA_BYTES` (macro, line 55) `#define PCM2_DMA_BYTES`
  - `PCM2_RING` (macro, line 56) `#define PCM2_RING`
  - `PCM2_FLAG_NONBLOCK` (macro, line 58) `#define PCM2_FLAG_NONBLOCK`
  - `PCM2_ERR_BUSY` (macro, line 60) `#define PCM2_ERR_BUSY`
  - `PCM2_ERR_NODEV` (macro, line 61) `#define PCM2_ERR_NODEV`
  - `PCM2_ERR_NOMEM` (macro, line 62) `#define PCM2_ERR_NOMEM`
  - `PCM2_ERR_PERM` (macro, line 63) `#define PCM2_ERR_PERM`
  - `PCM2_ERR_PIPE` (macro, line 64) `#define PCM2_ERR_PIPE`
  - `PCM2_ERR_INVAL` (macro, line 65) `#define PCM2_ERR_INVAL`
- Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`

## headers/pcm_ring.h
- Doc: single-producer/single-consumer byte ring for PCM audio.
- Layer: utility
- Language: h
- Symbols:
  - `pcm_ring_t` (struct, line 26)
  - `pcm_ring_init` (function, line 36) `static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,
                             ...`
  - `pcm_ring_used` (function, line 47) `static inline unsigned pcm_ring_used(const pcm_ring_t *r)`
  - `pcm_ring_free` (function, line 51) `static inline unsigned pcm_ring_free(const pcm_ring_t *r)`
  - `pcm_ring_write` (function, line 55) `static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,
                  ...`
  - `pcm_ring_read` (function, line 76) `static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,
                         ...`
  - `PCM_RING_H` (macro, line 2) `#define PCM_RING_H`
- Imported by: `drivers/pcm2.c`, `tests/test_pcm.c`

## headers/pcspk.h
- Layer: utility
- Language: h
- Symbols:
  - `pcspk_init` (function, line 8) `void pcspk_init(void);`
  - `pcspk_tone` (function, line 9) `void pcspk_tone(unsigned freq);`
  - `pcspk_off` (function, line 10) `void pcspk_off(void);`
  - `pcspk_set_volume` (function, line 11) `void pcspk_set_volume(unsigned volume);`
  - `pcspk_get_volume` (function, line 12) `unsigned pcspk_get_volume(void);`
  - `PCSPK_H` (macro, line 2) `#define PCSPK_H`
  - `PCSPK_VOL_MIN` (macro, line 4) `#define PCSPK_VOL_MIN`
  - `PCSPK_VOL_MAX` (macro, line 5) `#define PCSPK_VOL_MAX`
  - `PCSPK_VOL_DEFAULT` (macro, line 6) `#define PCSPK_VOL_DEFAULT`
- Imported by: `drivers/pcspk.c`, `kernel/shell.c`, `kernel/syscalls.c`

## headers/percpu_rq.h
- Doc: Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing.
- Layer: utility
- Language: h
- Symbols:
  - `percpu_rq_t` (struct, line 50)
  - `rq_init` (function, line 61) `void rq_init(void);`
  - `rq_enqueue` (function, line 62) `void rq_enqueue(int cpu, int pid);`
  - `rq_pop_local` (function, line 63) `int rq_pop_local(int cpu);`
  - `rq_steal_once` (function, line 64) `int rq_steal_once(int self_cpu, int *from_cpu);`
  - `rq_empty` (function, line 65) `int rq_empty(int cpu);`
  - `rq_should_rescan` (function, line 66) `int rq_should_rescan(int cpu);`
  - `rq_note_poll` (function, line 67) `void rq_note_poll(int cpu);`
  - `rq_stats` (function, line 68) `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals, unsigned long *drops);`
  - `PERCPU_RQ_H` (macro, line 2) `#define PERCPU_RQ_H`
  - `RQ_DEPTH` (macro, line 45) `#define RQ_DEPTH`
  - `RQ_RESCAN_PERIOD` (macro, line 46) `#define RQ_RESCAN_PERIOD`
  - `RQ_VALIDATE_ATTEMPTS` (macro, line 47) `#define RQ_VALIDATE_ATTEMPTS`
  - `WQ_NONE_HINT` (macro, line 48) `#define WQ_NONE_HINT`
- Depends on: `headers/sched.h`, `headers/spinlock.h`
- Imported by: `kernel/percpu_rq.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_percpu_rq.c`

## headers/pipe.h
- Doc: Docstring: pipe.h -- Kernel pipe ring contract (header-only).
- Layer: utility
- Language: h
- Symbols:
  - `pipe_ring_t` (struct, line 27)
  - `pipe_cfg_t` (struct, line 36)
  - `pipe_ring_init` (function, line 46) `static inline int pipe_ring_init(pipe_ring_t *r, unsigned char *buf,
        unsigned cap)`
  - `pipe_ring_avail` (function, line 62) `static inline unsigned pipe_ring_avail(const pipe_ring_t *r)`
  - `pipe_ring_space` (function, line 69) `static inline unsigned pipe_ring_space(const pipe_ring_t *r)`
  - `pipe_ring_write` (function, line 77) `static inline unsigned pipe_ring_write(pipe_ring_t *r,
        const unsigned char *src, unsigned...`
  - `pipe_ring_close_writer` (function, line 116) `static inline int pipe_ring_close_writer(pipe_ring_t *r)`
  - `pipe_ring_stat` (function, line 125) `static inline int pipe_ring_stat(const pipe_ring_t *r, pipe_cfg_t *out)`
  - `ends` (function, line 4) `* * Single source of truth for the pipe byte ring shared by the kernel * pipe ends (fs/kfile.c), the pipe/dup/dup2...`
  - `PIPE_H` (macro, line 19) `#define PIPE_H`
  - `PIPE_CAP_DEFAULT` (macro, line 21) `#define PIPE_CAP_DEFAULT`
  - `PIPE_CAP_MAX` (macro, line 22) `#define PIPE_CAP_MAX`
  - `PIPE_ERR_BOUND` (macro, line 24) `#define PIPE_ERR_BOUND`
  - `PIPE_EMPTY` (macro, line 25) `#define PIPE_EMPTY`
  - `PIPE_CFG_DEFAULT` (macro, line 42) `#define PIPE_CFG_DEFAULT`
- Imported by: `headers/kernel.h`, `kernel/console_in.c`, `tests/test_pipe.c`

## headers/qga.h
- Layer: utility
- Language: h
- Symbols:
  - `qga_init` (function, line 48) `void qga_init(void);`
  - `qga_poll` (function, line 49) `void qga_poll(void);`
  - `QGA_H` (macro, line 2) `#define QGA_H`
  - `QGA_COM2_BASE` (macro, line 5) `#define QGA_COM2_BASE`
  - `QGA_COM2_IRQ` (macro, line 6) `#define QGA_COM2_IRQ`
  - `QGA_UART_THR` (macro, line 9) `#define QGA_UART_THR`
  - `QGA_UART_RBR` (macro, line 10) `#define QGA_UART_RBR`
  - `QGA_UART_DLL` (macro, line 11) `#define QGA_UART_DLL`
  - `QGA_UART_DLM` (macro, line 12) `#define QGA_UART_DLM`
  - `QGA_UART_IER` (macro, line 13) `#define QGA_UART_IER`
  - `QGA_UART_FCR` (macro, line 14) `#define QGA_UART_FCR`
  - `QGA_UART_LCR` (macro, line 15) `#define QGA_UART_LCR`
  - `QGA_UART_LSR` (macro, line 16) `#define QGA_UART_LSR`
  - `QGA_UART_MCR` (macro, line 17) `#define QGA_UART_MCR`
  - `QGA_UART_LSR_TX_RDY` (macro, line 18) `#define QGA_UART_LSR_TX_RDY`
  - `QGA_UART_LSR_RX_RDY` (macro, line 19) `#define QGA_UART_LSR_RX_RDY`
  - `QGA_UART_LCR_DLAB` (macro, line 20) `#define QGA_UART_LCR_DLAB`
  - `QGA_UART_LCR_8N1` (macro, line 21) `#define QGA_UART_LCR_8N1`
  - `QGA_UART_FCR_CFG` (macro, line 22) `#define QGA_UART_FCR_CFG`
  - `QGA_UART_MCR_CFG` (macro, line 23) `#define QGA_UART_MCR_CFG`
  - `QGA_BAUD_DIVISOR` (macro, line 25) `#define QGA_BAUD_DIVISOR`
  - `QGA_LINE_MAX` (macro, line 30) `#define QGA_LINE_MAX`
  - `QGA_RESP_MAX` (macro, line 31) `#define QGA_RESP_MAX`
  - `QGA_FILE_READ_MAX` (macro, line 34) `#define QGA_FILE_READ_MAX`
  - `QGA_MAX_PAIRS` (macro, line 37) `#define QGA_MAX_PAIRS`
  - `QGA_KEY_MAX` (macro, line 38) `#define QGA_KEY_MAX`
  - `QGA_STR_MAX` (macro, line 39) `#define QGA_STR_MAX`
  - `QGA_MAX_DEPTH` (macro, line 42) `#define QGA_MAX_DEPTH`
  - `QGA_FILE_MAX` (macro, line 46) `#define QGA_FILE_MAX`
- Imported by: `qga.c`

## headers/randmix.h
- Doc: entropy mixer for getrandom (318).
- Layer: utility
- Language: h
- Symbols:
  - `source` (function, line 11) `* source (all-zero seed) still walks, because the increment is inside
 * the mixer, not in the ca...`
  - `RANDMIX_H` (macro, line 2) `#define RANDMIX_H`
- Imported by: `kernel/syscalls.c`, `tests/test_randmix.c`

## headers/rcu.h
- Doc: Docstring: rcu.h -- Read-copy-update, lite epoch edition.
- Layer: utility
- Language: h
- Symbols:
  - `retirement` (function, line 30) `* retirement (the writer keeps ownership) instead of dropping the free. * Callbacks run in tick context with...`
  - `rcu_init` (function, line 51) `void rcu_init(void);`
  - `rcu_read_lock` (function, line 52) `void rcu_read_lock(void);`
  - `rcu_read_unlock` (function, line 53) `void rcu_read_unlock(void);`
  - `rcu_deref` (function, line 54) `void *rcu_deref(void *volatile *pp);`
  - `rcu_publish` (function, line 55) `void rcu_publish(void *volatile *pp, void *v);`
  - `rcu_call` (function, line 56) `long rcu_call(rcu_cb_t fn, void *arg);`
  - `rcu_note_tick` (function, line 57) `void rcu_note_tick(int cpu);`
  - `rcu_note_idle` (function, line 58) `void rcu_note_idle(int cpu);`
  - `rcu_poll` (function, line 59) `void rcu_poll(void);`
  - `rcu_synchronize` (function, line 60) `long rcu_synchronize(void);`
  - `RCU_H` (macro, line 2) `#define RCU_H`
  - `RCU_CB_MAX` (macro, line 42) `#define RCU_CB_MAX`
  - `RCU_SYNC_SPINS` (macro, line 43) `#define RCU_SYNC_SPINS`
  - `RCU_OK` (macro, line 45) `#define RCU_OK`
  - `RCU_ERR_FULL` (macro, line 46) `#define RCU_ERR_FULL`
  - `RCU_ERR_TIMEOUT` (macro, line 47) `#define RCU_ERR_TIMEOUT`
- Depends on: `headers/sched.h`, `headers/spinlock.h`
- Imported by: `kernel/rcu.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_rcu.c`

## headers/rtc.h
- Doc: rtc_days_from_civil: Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm, pure...
- Layer: utility
- Language: h
- Symbols:
  - `rtc_days_from_civil` (function, line 18) `static inline long rtc_days_from_civil(long y, long m, long d)`
  - `rtc_read_tod` (function, line 4) `int rtc_read_tod(int *hour, int *min, int *sec);`
  - `rtc_read_date` (function, line 11) `int rtc_read_date(int *year, int *mon, int *day);`
  - `suite` (function, line 15) `* host suite (tests/test_rtc.c);`
  - `rtc_wall_seconds` (function, line 33) `int rtc_wall_seconds(unsigned long *out);`
  - `RTC_H` (macro, line 2) `#define RTC_H`
- Imported by: `drivers/rtc.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `qga.c`, `tests/test_rtc.c`

## headers/sanitize.h
- Doc: Docstring: sanitize.h -- Single choke point for syscall argument checks.
- Layer: utility
- Language: h
- Symbols:
  - `SANITIZE_H` (macro, line 2) `#define SANITIZE_H`
  - `SANITIZE_LEN_NEG` (macro, line 32) `#define SANITIZE_LEN_NEG(var)`
  - `SANITIZE_RANGE` (macro, line 37) `#define SANITIZE_RANGE(ptr, len)`
  - `SANITIZE_STR` (macro, line 43) `#define SANITIZE_STR(ptr, maxlen)`
  - `SANITIZE_COPY_IN` (macro, line 49) `#define SANITIZE_COPY_IN(kbuf, uptr, count, elemsz)`
- Imported by: `kernel/syscalls.c`, `kernel/syscalls_proc.c`, `tests/test_sanitize.c`

## headers/sb16.h
- Doc: Sound Blaster 16 DMA audio driver contract.
- Layer: utility
- Language: h
- Symbols:
  - `sb16_stream_t` (struct, line 46)
  - `sb16_counters_t` (struct, line 55)
  - `sb16_init` (function, line 65) `int sb16_init(void);`
  - `sb16_present` (function, line 66) `int sb16_present(void);`
  - `sb16_tone` (function, line 67) `void sb16_tone(unsigned freq);`
  - `sb16_irq` (function, line 68) `void sb16_irq(void);`
  - `sb16_poll` (function, line 69) `void sb16_poll(void);`
  - `sb16_pcm_open` (function, line 73) `void sb16_pcm_open(void);`
  - `sb16_pcm_submit` (function, line 74) `int sb16_pcm_submit(const unsigned char *pcm, unsigned len);`
  - `sb16_pcm_close` (function, line 75) `void sb16_pcm_close(void);`
  - `sb16_pump` (function, line 76) `void sb16_pump(void);`
  - `sb16_stream_open` (function, line 79) `int sb16_stream_open(void);`
  - `sb16_stream_close` (function, line 80) `void sb16_stream_close(int id);`
  - `sb16_stream_submit` (function, line 81) `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len);`
  - `sb16_stream_volume` (function, line 82) `void sb16_stream_volume(int id, unsigned char vol);`
  - `sb16_stream_count` (function, line 83) `int sb16_stream_count(void);`
  - `sb16_ring_free` (function, line 85) `unsigned sb16_ring_free(void);`
  - `sb16_mode_active` (function, line 86) `int sb16_mode_active(void);`
  - `sb16_legacy_busy` (function, line 91) `int sb16_legacy_busy(void);`
  - `sb16_counters` (function, line 93) `void sb16_counters(sb16_counters_t *out);`
  - `SB16_H` (macro, line 2) `#define SB16_H`
  - `SB16_PCM_BUF` (macro, line 32) `#define SB16_PCM_BUF`
  - `SB16_PCM_RATE` (macro, line 33) `#define SB16_PCM_RATE`
  - `SB16_SLOTS` (macro, line 34) `#define SB16_SLOTS`
  - `SB16_RING_CAP` (macro, line 35) `#define SB16_RING_CAP`
  - `SB16_ARM_PERIOD_MS` (macro, line 36) `#define SB16_ARM_PERIOD_MS`
  - `SB16_STREAMS` (macro, line 42) `#define SB16_STREAMS`
  - `SB16_STREAM_BUF` (macro, line 43) `#define SB16_STREAM_BUF`
- Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`


Next: [KB_headers_p4.md](KB_headers_p4.md)
