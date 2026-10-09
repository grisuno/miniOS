# API (page 4 of 19)
Previous: [API_p3.md](API_p3.md)

## headers/kernel/console_in.h
Imported by: `headers/shell.h`, `kernel/console_in.c`, `kernel/shell.c`
- `Consumers` (function) `headers/kernel/console_in.h:7` `* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into...`
- `console_peek` (function) `headers/kernel/console_in.h:17` `int console_peek(void);` -- Docstring: Blocking read from PS/2 or COM1 with PageUp/PageDown * scrollback detour. int console_getc(void); /**...
- `console_raw_try` (function) `headers/kernel/console_in.h:21` `int console_raw_try(void);` -- Docstring: Raw console multiplexer backing GETC_RAW: same sources, * no line buffering, echo or scrollback. try...
- `console_raw_get` (function) `headers/kernel/console_in.h:22` `int console_raw_get(void);`
- `console_job_try` (function) `headers/kernel/console_in.h:25` `int console_job_try(void);` -- Docstring: Raw console multiplexer backing GETC_RAW: same sources, * no line buffering, echo or scrollback. try...
- `console_job_get` (function) `headers/kernel/console_in.h:26` `int console_job_get(void);`
- `console_ungetc` (function) `headers/kernel/console_in.h:30` `void console_ungetc(unsigned char c);` -- Docstring: Push one byte back into the console FIFO; the next * console_getc/console_peek serves it first.
- `console_stdin_push` (function) `headers/kernel/console_in.h:37` `int console_stdin_push(const char *data, unsigned long len);` -- Docstring: Pipeline stdin override: the next console_getc calls serve len bytes from data, then report EOF (-1)...
- `console_stdin_clear` (function) `headers/kernel/console_in.h:38` `void console_stdin_clear(void);`
- `console_stdin_active` (function) `headers/kernel/console_in.h:39` `int console_stdin_active(void);`

## headers/kernel/vga_cursor.h
Imported by: `kernel/vga_cursor.c`, `kernel/vga_fb.c`
- `cursor_over` (function) `headers/kernel/vga_cursor.h:16` `int cursor_over(int x0, int y0, int w, int h);` -- Docstring: vga_cursor.h -- boundary of the pointer sprite layer (kernel/vga_cursor.c).
- `cursor_place` (function) `headers/kernel/vga_cursor.h:19` `void cursor_place(int mx, int my);` -- (kernel/vga_cursor.c).
- `cursor_move` (function) `headers/kernel/vga_cursor.h:22` `void cursor_move(int mx, int my);` -- #include "kernel.h" /** Docstring: Pointer sprite dimensions in pixels. #define CURSOR_W 8 #define CURSOR_H 8 /**...
- `cursor_erase` (function) `headers/kernel/vga_cursor.h:25` `void cursor_erase(void);` -- /** Docstring: Pointer sprite dimensions in pixels. #define CURSOR_W 8 #define CURSOR_H 8 /** Docstring: True when...
- `cursor_invalidate` (function) `headers/kernel/vga_cursor.h:28` `void cursor_invalidate(void);` -- /** Docstring: True when the sprite overlaps the given screen rectangle. int cursor_over(int x0, int y0, int w, int...
- `cursor_note_repaint` (function) `headers/kernel/vga_cursor.h:31` `void cursor_note_repaint(int x0, int y0, int w, int h);` -- /** Docstring: Paint the pointer at mx/my unconditionally. void cursor_place(int mx, int my); /** Docstring...

## headers/ktime.h
Imported by: `kernel/syscalls.c`, `kernel/time.c`, `tests/test_ktime.c`
- `ktime_us_from_delta` (function) `headers/ktime.h:19` `static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,
                      ...`
- `wall_us_from_parts` (function) `headers/ktime.h:30` `static inline unsigned long wall_us_from_parts(unsigned long base_sec,
                          ...` -- wall_us_from_parts: wall-clock microseconds from an RTC-anchored base. base_sec is the last seen RTC second...

## headers/ldso.h
Imported by: `headers/kernel.h`, `kernel/ldso_parse.c`, `kernel/loader.c`, `kernel/mm/paging.c`, `tests/test_ldso.c`
- `ldso_find_dynamic` (function) `headers/ldso.h:86` `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long *dyn_off, unsigned...` -- Docstring: Locate the PT_DYNAMIC file range.
- `ldso_vaddr_to_offset` (function) `headers/ldso.h:92` `int ldso_vaddr_to_offset(const unsigned char *file, unsigned long long fsize, unsigned long long va, unsigned long...` -- Docstring: Translate a link VA through PT_LOAD into a file offset.
- `ldso_segments` (function) `headers/ldso.h:97` `int ldso_segments(const unsigned char *file, unsigned long long fsize, LdsoSeg *segs, unsigned ncap, unsigned *nseg);` -- Docstring: Collect PT_LOAD spans (at most ncap) for reservation and * GOT-range checks.
- `ldso_scan_dynamic` (function) `headers/ldso.h:103` `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long dyn_off, unsigned long...` -- Docstring: Walk the dynamic array into info.
- `ldso_sym_count` (function) `headers/ldso.h:110` `int ldso_sym_count(const unsigned char *file, unsigned long long fsize, unsigned long long hash_off, unsigned *nsyms);` -- Docstring: Read the SYSV hash header at a file offset into bucket and chain counts.
- `ldso_copy_str` (function) `headers/ldso.h:116` `int ldso_copy_str(const unsigned char *file, unsigned long long fsize, unsigned long long strtab_off, unsigned long...` -- Docstring: Bounded copy of one dynamic string (NEEDED/SONAME/symbol).
- `ldso_sym_lookup` (function) `headers/ldso.h:124` `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize, unsigned long long symtab_off, unsigned...` -- Docstring: Linear search of a dynamic symbol table by name.
- `ldso_rela_count` (function) `headers/ldso.h:132` `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela);` -- Docstring: Validate the RELA header triple and report the row count.
- `ldso_read_rela` (function) `headers/ldso.h:137` `int ldso_read_rela(const unsigned char *file, unsigned long long fsize, unsigned long long rela_off, unsigned nrela...` -- Docstring: Read one RELA row with full validation: row inside the table, type GLOB_DAT/JUMP_SLOT (anything else is...
- `ldso_basename` (function) `headers/ldso.h:144` `void ldso_basename(char *out, const char *src);` -- Docstring: Basename normalization for registry keys ("a/b.so" to "b.so", bounded, always terminated).

## headers/leakcheck.h
Depends on: `kernel/string.c`
Imported by: `progs/file/file.c`, `progs/vedit/vedit.c`, `tests/test_leakcheck.c`
- `kmalloc` (function) `headers/leakcheck.h:79` `extern void *kmalloc(unsigned long size);` -- ifdef MINIOS_LK_KERNEL
- `kfree` (function) `headers/leakcheck.h:80` `extern void kfree(void *ptr);`
- `kprintf` (function) `headers/leakcheck.h:81` `extern int kprintf(const char *fmt, ...);`
- `lk_malloc` (function) `headers/leakcheck.h:96` `void *lk_malloc(size_t size, const char *file, int line)` -- #define MINIOS_LK_RAW_ALLOC(sz) kmalloc((unsigned long)(sz)) #define MINIOS_LK_RAW_FREE(p) kfree(p) #else #include...
- `lk_unlink` (function) `headers/leakcheck.h:110` `static void lk_unlink(lk_block_t *b)` -- void *lk_malloc(size_t size, const char *file, int line) { lk_block_t *b = (lk_block_t *)MINIOS_LK_RAW_ALLOC(size +...
- `lk_find` (function) `headers/leakcheck.h:120` `static lk_block_t *lk_find(void *ptr)` -- return b + 1; } /** Docstring: unlink one record from the live-block list. static void lk_unlink(lk_block_t *b) { if...
- `lk_free` (function) `headers/leakcheck.h:130` `void lk_free(void *ptr)` -- if (b->next) b->next->prev = b->prev; } /** Docstring: find the record owning ptr by scanning for its payload base....
- `lk_realloc` (function) `headers/leakcheck.h:143` `void *lk_realloc(void *ptr, size_t size, const char *file, int line)` -- /** Docstring: tracked free, passes unknown blocks to the raw backend. void lk_free(void *ptr) { lk_block_t *b; if...
- `lk_print` (function) `headers/leakcheck.h:186` `static void lk_print(const char *reason, const lk_block_t *b)` -- return ptr; } q = lk_malloc(size, file, line); if (q) { d = (unsigned char *)q; s = (unsigned char *)ptr; keep =...
- `lk_dumpmem` (function) `headers/leakcheck.h:197` `void lk_dumpmem(void)` -- } /** Docstring: print one live record on the configured pipe. static void lk_print(const char *reason, const...
- `lk_live_count` (function) `headers/leakcheck.h:206` `unsigned long lk_live_count(void)` -- b->file, b->line, (unsigned long)b->size, (const void *)(b + 1)); #endif } /** Docstring: report every block still...
- `lk_live_bytes` (function) `headers/leakcheck.h:217` `unsigned long lk_live_bytes(void)` -- } /** Docstring: count of blocks still live. unsigned long lk_live_count(void) { unsigned long n = 0; lk_block_t *b...

## headers/lz4_kernel.h
Imported by: `fs/minifs.c`, `kernel/lz4_kernel.c`, `kernel/mm/swap.c`, `kernel/syscalls.c`
- `LZ4_compress_default` (function) `headers/lz4_kernel.h:4` `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity);`
- `LZ4_compressBound` (function) `headers/lz4_kernel.h:5` `int LZ4_compressBound(int inputSize);`
- `LZ4_decompress_safe` (function) `headers/lz4_kernel.h:6` `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity);`

## headers/minifetch.h
Imported by: `kernel/minifetch.c`, `kernel/shell.c`
- `shell_cmd_minifetch` (function) `headers/minifetch.h:14` `void shell_cmd_minifetch(void);`

## headers/minifs.h
Imported by: `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `fs/kfile.c`, `fs/minifs.c`, `fs/vfs.c`, `kernel.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm/paging.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `tests/test_ext4.c`, `tests/test_fat32.c`
- `minifs_compress` (function) `headers/minifs.h:30` `unsigned int minifs_compress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
- `minifs_decompress` (function) `headers/minifs.h:31` `unsigned int minifs_decompress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
- `minifs_init` (function) `headers/minifs.h:117` `void minifs_init(void);`
- `minifs_mount` (function) `headers/minifs.h:118` `int minifs_mount(void);`
- `minifs_sync` (function) `headers/minifs.h:119` `int minifs_sync(void);`
- `minifs_is_mounted` (function) `headers/minifs.h:120` `int minifs_is_mounted(void);`
- `minifs_create` (function) `headers/minifs.h:122` `int minifs_create(const char *path, unsigned short mode);`
- `minifs_mkdir` (function) `headers/minifs.h:123` `int minifs_mkdir(const char *path, unsigned short mode);`
- `minifs_unlink` (function) `headers/minifs.h:124` `int minifs_unlink(const char *path);`
- `minifs_rmdir` (function) `headers/minifs.h:125` `int minifs_rmdir(const char *path);`
- `refuses` (function) `headers/minifs.h:128` `* An existing file dst refuses (no silent overwrite);`
- `minifs_rename` (function) `headers/minifs.h:130` `int minifs_rename(const char *oldpath, const char *newpath);` -- Docstring: Move one MiniFS directory entry to a new parent/name, keeping its inode (no data moves).
- `minifs_read` (function) `headers/minifs.h:131` `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len);`
- `minifs_write` (function) `headers/minifs.h:132` `int minifs_write(int inode_num, const void *buf, unsigned int offset, unsigned int len);`
- `minifs_truncate` (function) `headers/minifs.h:133` `int minifs_truncate(int inode_num, unsigned int new_size);`
- `minifs_stat` (function) `headers/minifs.h:134` `int minifs_stat(int inode_num, MiniFSInode *out);`
- `minifs_access` (function) `headers/minifs.h:135` `int minifs_access(const char *path);`
- `minifs_resolve_path` (function) `headers/minifs.h:137` `int minifs_resolve_path(const char *path);`
- `minifs_dir_lookup` (function) `headers/minifs.h:138` `int minifs_dir_lookup(int dir_inode, const char *name);`
- `minifs_dir_add_entry` (function) `headers/minifs.h:139` `int minifs_dir_add_entry(int dir_inode, const char *name, int child_inode, unsigned char type);`
- `minifs_dir_remove_entry` (function) `headers/minifs.h:140` `int minifs_dir_remove_entry(int dir_inode, const char *name);`
- `minifs_dir_read` (function) `headers/minifs.h:141` `int minifs_dir_read(int dir_inode, int index, MiniFSDirEntry *out, char *name_out);`
- `minifs_alloc_block` (function) `headers/minifs.h:143` `int minifs_alloc_block(void);`
- `minifs_free_block` (function) `headers/minifs.h:144` `void minifs_free_block(unsigned int block);`
- `minifs_alloc_inode` (function) `headers/minifs.h:145` `int minifs_alloc_inode(void);`
- `minifs_free_inode` (function) `headers/minifs.h:146` `void minifs_free_inode(int inode_num);`
- `minifs_inode_get_block` (function) `headers/minifs.h:147` `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logical_block, unsigned int *phys_block);`
- `minifs_inode_alloc_block` (function) `headers/minifs.h:148` `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logical_block);`
- `minifs_journal_begin` (function) `headers/minifs.h:150` `void minifs_journal_begin(unsigned int txn_id);`
- `minifs_journal_add_block` (function) `headers/minifs.h:151` `void minifs_journal_add_block(unsigned int block);`
- `minifs_journal_touch` (function) `headers/minifs.h:152` `void minifs_journal_touch(unsigned int phys);`
- `minifs_journal_commit` (function) `headers/minifs.h:153` `int minifs_journal_commit(unsigned int txn_id);`
- `minifs_journal_clear` (function) `headers/minifs.h:154` `void minifs_journal_clear(void);`
- `minifs_journal_abort` (function) `headers/minifs.h:155` `void minifs_journal_abort(void);`
- `minifs_journal_recover` (function) `headers/minifs.h:156` `void minifs_journal_recover(void);`
- `minifs_file_open` (function) `headers/minifs.h:158` `MiniFSFile *minifs_file_open(int inode_num, int flags);`
- `minifs_file_close` (function) `headers/minifs.h:159` `int minifs_file_close(MiniFSFile *f);`
- `minifs_get_lba_start` (function) `headers/minifs.h:161` `unsigned int minifs_get_lba_start(void);`
- `minifs_get_total_blocks` (function) `headers/minifs.h:162` `unsigned int minifs_get_total_blocks(void);`
- `minifs_usage` (function) `headers/minifs.h:164` `void minifs_usage(unsigned int *free_b, unsigned int *total_b, unsigned int *free_i, unsigned int *total_i);` -- void minifs_journal_begin(unsigned int txn_id); void minifs_journal_add_block(unsigned int block); void...

## headers/net.h
Imported by: `drivers/virtio_net.c`, `headers/net/rtl8139.h`, `headers/tls_port.h`, `kernel.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `net/net.c`, `net/rtl8139.c`
- `ring` (function) `headers/net.h:58` `* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SOCK_RX_BUF 16384 #define...`
- `net_sys_is_socket` (function) `headers/net.h:101` `int net_sys_is_socket(long fd);` -- net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and * 0..NET_SOCKETS-1 for the libc-style...
- `net_sys_setsockopt` (function) `headers/net.h:102` `long net_sys_setsockopt(long fd, long level, long name, long val, long len);`
- `net_sys_getsockopt` (function) `headers/net.h:103` `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp);`
- `net_sys_getsockname` (function) `headers/net.h:104` `long net_sys_getsockname(long fd, long addr, long lenp);`
- `net_sys_getpeername` (function) `headers/net.h:105` `long net_sys_getpeername(long fd, long addr, long lenp);`
- `net_sys_sendmsg` (function) `headers/net.h:106` `long net_sys_sendmsg(long fd, long msg, long flags);`
- `net_sys_sendmmsg` (function) `headers/net.h:107` `long net_sys_sendmmsg(long fd, long vec, long vlen, long flags);`
- `net_sys_fcntl` (function) `headers/net.h:108` `long net_sys_fcntl(long fd, long cmd, long arg);`
- `net_sys_ioctl` (function) `headers/net.h:109` `long net_sys_ioctl(long fd, long req, long arg);`
- `net_register_symbols` (function) `headers/net.h:110` `void net_register_symbols(void);`
- `net_cmd_status` (function) `headers/net.h:113` `void net_cmd_status(void);` -- void net_init(void); /* Linux socket ABI entry points (kernel/syscalls.c routes to them). int...
- `net_cmd_ping` (function) `headers/net.h:114` `void net_cmd_ping(const char *ip_text);`
- `net_get_addrs` (function) `headers/net.h:115` `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]);`
- `net_cmd_dns` (function) `headers/net.h:116` `void net_cmd_dns(const char *host);`
- `net_open` (function) `headers/net.h:119` `int net_open(void);` -- long net_sys_getpeername(long fd, long addr, long lenp); long net_sys_sendmsg(long fd, long msg, long flags); long...
- `net_connect` (function) `headers/net.h:120` `int net_connect(const char *host, unsigned short port);`
- `net_send` (function) `headers/net.h:121` `int net_send(int fd, const char *buf, int len);`
- `net_recv` (function) `headers/net.h:122` `int net_recv(int fd, char *buf, int len);`
- `net_recv_timeout` (function) `headers/net.h:124` `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);` -- void net_register_symbols(void); /* Shell commands void net_cmd_status(void); void net_cmd_ping(const char...
- `net_close` (function) `headers/net.h:125` `void net_close(int fd);`
- `demux` (function) `headers/net.h:131` `* segment through the production demux (httpd selftest). */ int net_listen(unsigned short port);`
- `net_accept_nb` (function) `headers/net.h:133` `int net_accept_nb(int fd);`
- `net_accept` (function) `headers/net.h:134` `int net_accept(int fd, unsigned long timeout_ms);`
- `net_sock_state` (function) `headers/net.h:135` `int net_sock_state(int fd);`
- `net_sock_seq` (function) `headers/net.h:136` `int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out);`
- `net_test_inject_tcp` (function) `headers/net.h:137` `int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport, unsigned short lport, unsigned char...`
- `net_sys_socket` (function) `headers/net.h:142` `long net_sys_socket(long a1, long a2, long a3);` -- index, or -1). net_accept_nb takes an established child without waiting; net_accept waits up to timeout_ms....
- `net_sys_connect` (function) `headers/net.h:143` `long net_sys_connect(long fd, long sockaddr, long addrlen);`
- `net_sys_bind` (function) `headers/net.h:144` `long net_sys_bind(long fd, long sockaddr, long addrlen);`
- `net_sys_listen` (function) `headers/net.h:145` `long net_sys_listen(long fd, long backlog);`
- `net_sys_accept` (function) `headers/net.h:146` `long net_sys_accept(long fd, long sockaddr, long addrlen);`
- `net_sys_sendto` (function) `headers/net.h:147` `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);`
- `net_sys_recvfrom` (function) `headers/net.h:148` `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);`
- `net_sys_shutdown` (function) `headers/net.h:149` `long net_sys_shutdown(long fd, long how);`
- `net_sys_close` (function) `headers/net.h:150` `long net_sys_close(long fd);`
- `net_sys_poll` (function) `headers/net.h:151` `long net_sys_poll(long fds, long nfds, long timeout_ms);`
- `net_sys_dns` (function) `headers/net.h:152` `long net_sys_dns(long host);`
- `net_time_ms` (function) `headers/net.h:155` `unsigned long net_time_ms(void);` -- /* Linux syscall ABI (sockaddr_in layout matches Linux) long net_sys_socket(long a1, long a2, long a3); long...
- `net_rx_handle_frame` (function) `headers/net.h:159` `void net_rx_handle_frame(const unsigned char *frame, unsigned len);` -- Demux entry point the rtl8139 driver (rtl8139.c) calls for every * frame drained from the RX ring; lives in net.c.
- `stack` (function) `headers/net.h:162` `* the stack (dropped fragments);`
- `tls_free_fd` (function) `headers/net.h:170` `void tls_free_fd(int fd);` -- TLS sessions attached to socket fds (tls.c); net_sys_close frees them.

## headers/net/rtl8139.h
Depends on: `headers/net.h`
Imported by: `net/net.c`, `net/rtl8139.c`
- `rtl_present` (function) `headers/net/rtl8139.h:18` `int rtl_present(void);` -- rtl8139 NIC driver interface.
- `rtl_init` (function) `headers/net/rtl8139.h:21` `void rtl_init(void);` -- This header is the boundary between the polled rtl8139 driver (rtl8139.c) and the protocol stack (net.c).
- `rtl_send` (function) `headers/net/rtl8139.h:25` `int rtl_send(const unsigned char *frame, unsigned len);` -- Transmit one raw Ethernet frame.
- `net_rx_handle_frame` (function) `headers/net/rtl8139.h:28` `* net_rx_handle_frame (the protocol demux in net.c). */ void rtl_poll(void);`
- `rtl_get_mac` (function) `headers/net/rtl8139.h:32` `void rtl_get_mac(unsigned char out[NET_ETH_ALEN]);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...
- `rtl_iobase` (function) `headers/net/rtl8139.h:35` `unsigned short rtl_iobase(void);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...
- `rtl_counters` (function) `headers/net/rtl8139.h:38` `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...

## headers/panic.h
Imported by: `kernel/panic.c`, `tests/test_panic.c`
- `panic_backtrace` (function) `headers/panic.h:25` `static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid,
        unsigned long ...` -- Docstring: Walk up to max frame pointers from rbp, storing each frame's return address (*(rbp+8)) into out.

## headers/pcache.h
Imported by: `fs/minifs.c`, `fs/pcache.c`, `kernel.c`, `kernel/loader.c`, `kernel/mm/paging.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_pcache.c`
- `pcache_init` (function) `headers/pcache.h:28` `void pcache_init(void);` -- Docstring: Allocate the page pool; disabled (all calls fail closed) when the heap cannot spare it, exactly like the...
- `pcache_lookup` (function) `headers/pcache.h:32` `int pcache_lookup(int ino, unsigned index);` -- Docstring: Find a cached page without reserving.
- `pcache_get` (function) `headers/pcache.h:42` `int pcache_get(int ino, unsigned index, int *is_new);` -- Docstring: Get a page, pinned with one ref.
- `pcache_publish` (function) `headers/pcache.h:51` `int pcache_publish(int ino, unsigned index, const unsigned char *data);` -- Docstring: Publish a privately filled page into the cache atomically.
- `pcache_put` (function) `headers/pcache.h:55` `void pcache_put(int slot);` -- Docstring: Drop one ref taken by get.
- `pcache_ref` (function) `headers/pcache.h:61` `int pcache_ref(int ino, unsigned index);` -- Docstring: Take one more ref on a cached page without allocating.
- `pcache_unmap` (function) `headers/pcache.h:69` `void pcache_unmap(int ino, unsigned index);` -- Docstring: Drop the ref a mapping holds on one cached page.
- `match` (function) `headers/pcache.h:75` `* a phys match (owned, ref dropped unless already zero), 0 * otherwise. */ int pcache_put_if(int ino, unsigned...`
- `pcache_ref_if` (function) `headers/pcache.h:83` `int pcache_ref_if(int ino, unsigned index, unsigned long phys);` -- Docstring: Take one more ref only when the cached page is the exact phys the caller shares.
- `pcache_owns_phys` (function) `headers/pcache.h:88` `int pcache_owns_phys(unsigned long phys);` -- Docstring: True when phys is a cache pool page.
- `pcache_data` (function) `headers/pcache.h:93` `unsigned char *pcache_data(int slot);` -- Docstring: Page data for a slot from get/lookup, 0 on a bad slot.
- `pcache_mark_dirty` (function) `headers/pcache.h:98` `void pcache_mark_dirty(int slot);` -- Docstring: Mark a pinned page dirty.
- `pcache_invalidate_ino` (function) `headers/pcache.h:102` `void pcache_invalidate_ino(int ino);` -- Docstring: Drop every page of an inode (truncate/unlink). * Dirty pages drop with them until slice 3 teaches writeback.
- `pcache_stats` (function) `headers/pcache.h:106` `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out, unsigned long *miss_out, unsigned long...` -- Docstring: Snapshot for the mem builtin and BDD: live pages, * cumulative hits/misses/evictions, dirty count.

## headers/pcm2.h
Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `pcm2_active` (function) `headers/pcm2.h:77` `int pcm2_active(void);`
- `pcm2_open` (function) `headers/pcm2.h:78` `int pcm2_open(unsigned flags, int owner);`
- `pcm2_write` (function) `headers/pcm2.h:79` `int pcm2_write(const unsigned char *user, unsigned len, int owner);`
- `pcm2_close` (function) `headers/pcm2.h:80` `void pcm2_close(int owner);`
- `pcm2_irq` (function) `headers/pcm2.h:81` `void pcm2_irq(void);`
- `pcm2_poll` (function) `headers/pcm2.h:82` `void pcm2_poll(void);`
- `pcm2_counters` (function) `headers/pcm2.h:83` `void pcm2_counters(pcm2_counters_t *out);`

## headers/pcm_ring.h
Imported by: `drivers/pcm2.c`, `tests/test_pcm.c`
- `pcm_ring_init` (function) `headers/pcm_ring.h:36` `static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,
                             ...`
- `pcm_ring_used` (function) `headers/pcm_ring.h:47` `static inline unsigned pcm_ring_used(const pcm_ring_t *r)`
- `pcm_ring_free` (function) `headers/pcm_ring.h:51` `static inline unsigned pcm_ring_free(const pcm_ring_t *r)`
- `pcm_ring_write` (function) `headers/pcm_ring.h:55` `static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,
                  ...`
- `pcm_ring_read` (function) `headers/pcm_ring.h:76` `static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,
                         ...`

## headers/pcspk.h
Imported by: `drivers/pcspk.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `pcspk_init` (function) `headers/pcspk.h:8` `void pcspk_init(void);`
- `pcspk_tone` (function) `headers/pcspk.h:9` `void pcspk_tone(unsigned freq);`
- `pcspk_off` (function) `headers/pcspk.h:10` `void pcspk_off(void);`
- `pcspk_set_volume` (function) `headers/pcspk.h:11` `void pcspk_set_volume(unsigned volume);`
- `pcspk_get_volume` (function) `headers/pcspk.h:12` `unsigned pcspk_get_volume(void);`

## headers/percpu_rq.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `kernel/percpu_rq.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_percpu_rq.c`
- `rq_init` (function) `headers/percpu_rq.h:61` `void rq_init(void);`
- `rq_enqueue` (function) `headers/percpu_rq.h:62` `void rq_enqueue(int cpu, int pid);`
- `rq_pop_local` (function) `headers/percpu_rq.h:63` `int rq_pop_local(int cpu);`
- `rq_steal_once` (function) `headers/percpu_rq.h:64` `int rq_steal_once(int self_cpu, int *from_cpu);`
- `rq_empty` (function) `headers/percpu_rq.h:65` `int rq_empty(int cpu);`
- `rq_should_rescan` (function) `headers/percpu_rq.h:66` `int rq_should_rescan(int cpu);`
- `rq_note_poll` (function) `headers/percpu_rq.h:67` `void rq_note_poll(int cpu);`
- `rq_stats` (function) `headers/percpu_rq.h:68` `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals, unsigned long *drops);`

## headers/pipe.h
Imported by: `headers/kernel.h`, `kernel/console_in.c`, `tests/test_pipe.c`
- `ends` (function) `headers/pipe.h:4` `* * Single source of truth for the pipe byte ring shared by the kernel * pipe ends (fs/kfile.c), the pipe/dup/dup2...`
- `pipe_ring_init` (function) `headers/pipe.h:47` `static inline int pipe_ring_init(pipe_ring_t *r, unsigned char *buf,
        unsigned cap)` -- Docstring: Bind a caller-owned buffer to a ring.
- `pipe_ring_avail` (function) `headers/pipe.h:64` `static inline unsigned pipe_ring_avail(const pipe_ring_t *r)` -- return PIPE_ERR_BOUND; if (cap == 0u || cap > PIPE_CAP_MAX) return PIPE_ERR_BOUND; r->buf = buf; r->cap = cap...
- `pipe_ring_space` (function) `headers/pipe.h:71` `static inline unsigned pipe_ring_space(const pipe_ring_t *r)` -- r->count = 0u; r->wopen = 1; r->ropen = 1; return 0; } /** Docstring: Bytes available to read.
- `pipe_ring_write` (function) `headers/pipe.h:79` `static inline unsigned pipe_ring_write(pipe_ring_t *r,
        const unsigned char *src, unsigned...` -- Docstring: Append up to len bytes, return bytes stored.
- `pipe_ring_close_writer` (function) `headers/pipe.h:118` `static inline int pipe_ring_close_writer(pipe_ring_t *r)` -- Docstring: Mark the writer closed.
- `pipe_ring_close_reader` (function) `headers/pipe.h:128` `static inline int pipe_ring_close_reader(pipe_ring_t *r)` -- Docstring: Mark the reader closed.
- `pipe_ring_ropen` (function) `headers/pipe.h:135` `static inline int pipe_ring_ropen(const pipe_ring_t *r)` -- Docstring: Mark the reader closed.
- `pipe_ring_stat` (function) `headers/pipe.h:140` `static inline int pipe_ring_stat(const pipe_ring_t *r, pipe_cfg_t *out)` -- Docstring: Snapshot ring geometry into a caller struct.

## headers/proc_sec.h
Imported by: `kernel/exec.c`, `kernel/proc_sec.c`, `kernel/sched.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`
- `proc_sec_inherit` (function) `headers/proc_sec.h:23` `void proc_sec_inherit(int child, int parent);` -- Exit code of a process or thread a filter kills: a death by SIGSYS (31), recorded negative like every MiniOS signal...
- `proc_sec_release` (function) `headers/proc_sec.h:24` `void proc_sec_release(int pid);`
- `proc_sec_exec` (function) `headers/proc_sec.h:25` `void proc_sec_exec(int pid);`
- `proc_sec_set_exe` (function) `headers/proc_sec.h:26` `void proc_sec_set_exe(int pid, const char *resolved);`
- `proc_sec_exe` (function) `headers/proc_sec.h:28` `const char *proc_sec_exe(int pid);` -- Exit code of a process or thread a filter kills: a death by SIGSYS (31), recorded negative like every MiniOS signal...
- `it` (function) `headers/proc_sec.h:31` `* the syscall must answer in *ret when a filter decided it (ERRNO, TRACE, * USER_NOTIF);`
- `proc_sec_filter` (function) `headers/proc_sec.h:34` `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret);` -- Run the caller's filters for syscall n.
- `proc_sec_prctl` (function) `headers/proc_sec.h:36` `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5);`
- `proc_sec_seccomp` (function) `headers/proc_sec.h:37` `long proc_sec_seccomp(long op, long flags, long uargs);`

## headers/qga.h
Imported by: `qga.c`
- `qga_init` (function) `headers/qga.h:48` `void qga_init(void);`
- `qga_poll` (function) `headers/qga.h:49` `void qga_poll(void);`

## headers/randmix.h
Imported by: `kernel/syscalls.c`, `tests/test_randmix.c`
- `source` (function) `headers/randmix.h:11` `* source (all-zero seed) still walks, because the increment is inside
 * the mixer, not in the ca...`

## headers/rcu.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `kernel/rcu.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_rcu.c`
- `retirement` (function) `headers/rcu.h:30` `* retirement (the writer keeps ownership) instead of dropping the free. * Callbacks run in tick context with...`
- `rcu_init` (function) `headers/rcu.h:51` `void rcu_init(void);`
- `rcu_read_lock` (function) `headers/rcu.h:52` `void rcu_read_lock(void);`
- `rcu_read_unlock` (function) `headers/rcu.h:53` `void rcu_read_unlock(void);`
- `rcu_deref` (function) `headers/rcu.h:54` `void *rcu_deref(void *volatile *pp);`
- `rcu_publish` (function) `headers/rcu.h:55` `void rcu_publish(void *volatile *pp, void *v);`
- `rcu_call` (function) `headers/rcu.h:56` `long rcu_call(rcu_cb_t fn, void *arg);`
- `rcu_note_tick` (function) `headers/rcu.h:57` `void rcu_note_tick(int cpu);`
- `rcu_note_idle` (function) `headers/rcu.h:58` `void rcu_note_idle(int cpu);`
- `rcu_poll` (function) `headers/rcu.h:59` `void rcu_poll(void);`
- `rcu_synchronize` (function) `headers/rcu.h:60` `long rcu_synchronize(void);`

## headers/rtc.h
Imported by: `drivers/rtc.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `qga.c`, `tests/test_rtc.c`
- `rtc_read_tod` (function) `headers/rtc.h:4` `int rtc_read_tod(int *hour, int *min, int *sec);`
- `rtc_read_date` (function) `headers/rtc.h:11` `int rtc_read_date(int *year, int *mon, int *day);` -- Calendar date from the CMOS RTC (registers 0x07-0x09).
- `suite` (function) `headers/rtc.h:15` `* host suite (tests/test_rtc.c);`
- `rtc_days_from_civil` (function) `headers/rtc.h:18` `static inline long rtc_days_from_civil(long y, long m, long d)` -- Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm, pure integer arithmetic, no tables).
- `rtc_wall_seconds` (function) `headers/rtc.h:33` `int rtc_wall_seconds(unsigned long *out);` -- Wall-clock seconds since the Unix epoch from one RTC snapshot.

## headers/sb16.h
Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `sb16_init` (function) `headers/sb16.h:65` `int sb16_init(void);`
- `sb16_present` (function) `headers/sb16.h:66` `int sb16_present(void);`
- `sb16_tone` (function) `headers/sb16.h:67` `void sb16_tone(unsigned freq);`
- `sb16_irq` (function) `headers/sb16.h:68` `void sb16_irq(void);`
- `sb16_poll` (function) `headers/sb16.h:69` `void sb16_poll(void);`
- `sb16_pcm_open` (function) `headers/sb16.h:73` `void sb16_pcm_open(void);` -- Legacy single-stream API (maps to mixer stream 0: pcm_open allocates it, * pcm_submit forwards into it, pcm_close...
- `sb16_pcm_submit` (function) `headers/sb16.h:74` `int sb16_pcm_submit(const unsigned char *pcm, unsigned len);`
- `sb16_pcm_close` (function) `headers/sb16.h:75` `void sb16_pcm_close(void);`
- `sb16_pump` (function) `headers/sb16.h:76` `void sb16_pump(void);`
- `sb16_stream_open` (function) `headers/sb16.h:79` `int sb16_stream_open(void);` -- Legacy single-stream API (maps to mixer stream 0: pcm_open allocates it, * pcm_submit forwards into it, pcm_close...
- `sb16_stream_close` (function) `headers/sb16.h:80` `void sb16_stream_close(int id);`
- `sb16_stream_submit` (function) `headers/sb16.h:81` `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len);`
- `sb16_stream_volume` (function) `headers/sb16.h:82` `void sb16_stream_volume(int id, unsigned char vol);`
- `sb16_stream_count` (function) `headers/sb16.h:83` `int sb16_stream_count(void);`
- `sb16_ring_free` (function) `headers/sb16.h:85` `unsigned sb16_ring_free(void);`
- `sb16_mode_active` (function) `headers/sb16.h:86` `int sb16_mode_active(void);`
- `sb16_legacy_busy` (function) `headers/sb16.h:91` `int sb16_legacy_busy(void);` -- True while the legacy engine audibly owns the DSP (PCM stream open or a tone sounding). pcm2_open consults it for...
- `sb16_counters` (function) `headers/sb16.h:93` `void sb16_counters(sb16_counters_t *out);`

## headers/sched.h
Depends on: `headers/spinlock.h`, `headers/vma.h`
Imported by: `drivers/kbd.c`, `drivers/pcm2.c`, `headers/futex.h`, `headers/percpu_rq.h`, `headers/rcu.h`, `headers/spawn.h`, `headers/sync.h`, `kernel.c`, `kernel/console.c`, `kernel/exec.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm.c`, `kernel/mm/cow.c`, `kernel/panic.c`, `kernel/proc_sec.c`, `kernel/sched.c`, `kernel/serial.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`, `kernel/vga_fb.c`, `net/net.c`, `net/rtl8139.c`, `progs/src/lxabi.c`, `smp.c`
- `group` (function) `headers/sched.h:108` `* process is its own group (tgid == pid);`
- `entry` (function) `headers/sched.h:135` `* private view with one KFILE ref per live entry (0 on OOM), release * drops the view at reap, cloexec closes marked...`
- `kfd_view_copy` (function) `headers/sched.h:138` `int kfd_view_copy(proc_t *child, proc_t *parent);`
- `kfd_view_release` (function) `headers/sched.h:139` `void kfd_view_release(proc_t *p);`
- `kfd_view_cloexec` (function) `headers/sched.h:140` `void kfd_view_cloexec(void);`
- `kfd_view_root` (function) `headers/sched.h:141` `kfd_view_t *kfd_view_root(void);`
- `bytes` (function) `headers/sched.h:173` `* RLIM_AS total user bytes (brk growth + mmap) beyond the load base * RLIM_CPU timer ticks of CPU time, then...`
- `first` (function) `headers/sched.h:232` `* address first (SYSCALL_FRAME_WORDS in syscall_asm.h). It ends exactly at * the saved top (sc_top_save[pid]);`
- `syscall_frame_current` (function) `headers/sched.h:245` `const syscall_frame_t *syscall_frame_current(void);` -- The frame syscall_entry.S builds on the per-proc kernel stack, lowest address first (SYSCALL_FRAME_WORDS in...
- `sched_init` (function) `headers/sched.h:376` `void sched_init(void);` -- Per-CPU TSS selectors: slot 5 + 2*cpu in the runtime GDT (each TSS descriptor occupies two 8-byte slots).
- `kstack_report` (function) `headers/sched.h:377` `void kstack_report(void);`
- `schedtop_report` (function) `headers/sched.h:378` `void schedtop_report(void);`
- `irqstat_report` (function) `headers/sched.h:379` `void irqstat_report(void);`
- `gdb_regs_report` (function) `headers/sched.h:380` `void gdb_regs_report(int pid);`
- `gdb_dump_report` (function) `headers/sched.h:381` `void gdb_dump_report(unsigned long addr, unsigned long len);`
- `tss_init_ap` (function) `headers/sched.h:385` `void tss_init_ap(int cpu);`
- `smp_ap_idle_loop` (function) `headers/sched.h:386` `void smp_ap_idle_loop(void);`
- `proc_create` (function) `headers/sched.h:387` `int proc_create(const char *name, int parent_pid);`
- `proc_get` (function) `headers/sched.h:388` `proc_t *proc_get(int pid);`
- `schedule` (function) `headers/sched.h:389` `void schedule(void);`
- `sched_set_nice` (function) `headers/sched.h:390` `int sched_set_nice(int pid, int nice);`
- `seccomp_deny_one` (function) `headers/sched.h:391` `int seccomp_deny_one(int pid, int n);`
- `seccomp_allow_one` (function) `headers/sched.h:392` `int seccomp_allow_one(int pid, int n);`
- `seccomp_denied` (function) `headers/sched.h:393` `int seccomp_denied(int pid, int n);`
- `rlimit_cpu_exceeded` (function) `headers/sched.h:394` `int rlimit_cpu_exceeded(int pid);`
- `rlimit_cpu_tick` (function) `headers/sched.h:395` `void rlimit_cpu_tick(int pid);`
- `switch_to` (function) `headers/sched.h:396` `void switch_to(proc_t *prev, proc_t *next);`
- `switch_to_notrap` (function) `headers/sched.h:397` `void switch_to_notrap(proc_t *prev, proc_t *next);`
- `switch_save_only` (function) `headers/sched.h:398` `void switch_save_only(proc_t *prev);`
- `resume_iretq` (function) `headers/sched.h:405` `void resume_iretq(void);`
- `yield` (function) `headers/sched.h:406` `void yield(void);`
- `do_exit` (function) `headers/sched.h:407` `void do_exit(int code);`
- `do_clone` (function) `headers/sched.h:408` `long do_clone(long flags, long newsp);`
- `do_fork` (function) `headers/sched.h:409` `long do_fork(void);`
- `do_fork_ex` (function) `headers/sched.h:410` `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid);`
- `do_linux_clone` (function) `headers/sched.h:411` `long do_linux_clone(unsigned long flags, unsigned long newsp, unsigned long ptid, unsigned long ctid, unsigned long...`
- `do_group_exit` (function) `headers/sched.h:413` `void do_group_exit(int code);`
- `mm_view_claim_current` (function) `headers/sched.h:414` `void mm_view_claim_current(void);`
- `do_kill_code` (function) `headers/sched.h:415` `int do_kill_code(int pid, int code);`
- `fork_child_settid` (function) `headers/sched.h:418` `void fork_child_settid(void);` -- void     sched_park_capture(proc_t *cur); void     resume_iretq(void); void     yield(void); void     do_exit(int...
- `aslr_stack_bytes` (function) `headers/sched.h:428` `unsigned long aslr_stack_bytes(void);` -- ASLR jitter, fresh per exec (TSC + ticks + per-exec counter, never zero for stack/brk so consecutive execs differ...
- `aslr_brk_pages` (function) `headers/sched.h:429` `unsigned long aslr_brk_pages(void);`
- `aslr_mmap_pages` (function) `headers/sched.h:430` `unsigned long aslr_mmap_pages(void);`
- `aslr_dyn_base` (function) `headers/sched.h:431` `unsigned long aslr_dyn_base(void);`
- `failure` (function) `headers/sched.h:436` `* failure (negative errno);`
- `do_execve` (function) `headers/sched.h:437` `long do_execve(char *kpath, int kargc, char **kargv);` -- do_execve() - replace the caller's image with a fresh ET_EXEC/ET_DYN program (kernel/sched.c).
- `do_thread_spawn` (function) `headers/sched.h:438` `long do_thread_spawn(unsigned long fn, unsigned long stack, unsigned long arg);`
- `do_waitpid` (function) `headers/sched.h:440` `int do_waitpid(int pid);`
- `do_waitpid_nb` (function) `headers/sched.h:441` `int do_waitpid_nb(int pid);`
- `shell_reap_nb` (function) `headers/sched.h:442` `int shell_reap_nb(int *pid_out, int *code_out);`
- `shell_reap_one` (function) `headers/sched.h:443` `int shell_reap_one(int pid, int *code_out);`
- `shell_nchildren` (function) `headers/sched.h:444` `int shell_nchildren(void);`
- `do_waitpid_linux` (function) `headers/sched.h:448` `int do_waitpid_linux(int pid, int nohang, int *found);` -- kstack slot family, fd table and limits; everything else (window, VMA, brk view, stack, FPU, FSBASE, name) is rebuilt.
- `do_kill` (function) `headers/sched.h:449` `int do_kill(int pid);`
- `timer_tick` (function) `headers/sched.h:450` `void timer_tick(void);`
- `pt_clone_user` (function) `headers/sched.h:453` `uint64_t pt_clone_user(uint64_t parent_cr3);` -- unsigned long arg); int      do_waitpid(int pid); int      do_waitpid_nb(int pid); int      shell_reap_nb(int...
- `pt_free_user` (function) `headers/sched.h:454` `void pt_free_user(uint64_t cr3);`
- `caller` (function) `headers/sched.h:459` `* caller (shell mrun) reaps it with do_waitpid. Returns pid or -1. * Programs using mmap/VMA or expecting a shared...`

## headers/seccomp_bpf.h
Imported by: `kernel/proc_sec.c`, `kernel/seccomp_bpf.c`, `tests/test_seccomp_bpf.c`
- `sbpf_check` (function) `headers/seccomp_bpf.h:95` `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch);` -- Validate a program before it ever runs: 1..SBPF_MAX_INSNS instructions, only the opcodes Linux accepts for seccomp...
- `sbpf_run` (function) `headers/seccomp_bpf.h:100` `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d);` -- Run a program sbpf_check accepted over one syscall's data; returns the 32-bit action.
- `sbpf_action_rank` (function) `headers/seccomp_bpf.h:104` `int sbpf_action_rank(unsigned int action);` -- Restrictiveness rank of an action (0 = most restrictive): the order * stacked filters are combined in.

## headers/shell.h
Depends on: `headers/kernel.h`, `headers/kernel/console_in.h`
Imported by: `kernel/editor.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `shell_readline_buf` (function) `headers/shell.h:18` `void shell_readline_buf(char *buf, int size);` -- Read one line into buf with arrow-key editing; used by the built-in * editor to edit file text.
- `shell_parse` (function) `headers/shell.h:21` `int shell_parse(char *line, char **argv, int max_args);` -- Read one line into buf with arrow-key editing; used by the built-in * editor to edit file text. void...
- `shell_parse_long` (function) `headers/shell.h:29` `int shell_parse_long(const char *s, long *out);` -- Strict signed decimal parse for numeric shell/editor operands: an optional sign followed by at least one digit...
- `shell_parse_pid` (function) `headers/shell.h:34` `int shell_parse_pid(const char *s, int min_pid, int *out);` -- Bounded pid parse: strict shell_parse_long plus min_pid <= pid < MAX_PROCS.
- `shell_cmd_sh` (function) `headers/shell.h:39` `int shell_cmd_sh(int argc, char **argv);` -- Execute a shell script: read `path` line by line, skip blanks and `#` comments, parse each line and dispatch it...

## headers/smp.h
Depends on: `headers/spinlock.h`
Imported by: `kernel.c`, `kernel/sched.c`, `kernel/shell.c`, `smp.c`
- `smp_init` (function) `headers/smp.h:41` `void smp_init(void);`
- `smp_ap_entry` (function) `headers/smp.h:42` `void smp_ap_entry(void);`
- `smp_ipi_broadcast` (function) `headers/smp.h:43` `void smp_ipi_broadcast(int vector);` -- PIT-anchored LAPIC calibration (ticks per 10 ms at divide-by-16).

## headers/spawn.h
Depends on: `headers/kernel.h`, `headers/sched.h`, `headers/vma.h`
Imported by: `kernel/sched.c`, `kernel/spawn.c`, `kernel/syscalls.c`
- `spawn_backup` (function) `headers/spawn.h:28` `int spawn_backup(spawn_ctx_t *ctx);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_restore` (function) `headers/spawn.h:31` `void spawn_restore(spawn_ctx_t *ctx);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_validate_argv` (function) `headers/spawn.h:34` `int spawn_validate_argv(int argc, const char **uargv);` -- Docstring: Save the caller shared-window view into ctx.
- `spawn_copy_argv` (function) `headers/spawn.h:39` `char **spawn_copy_argv(int argc, const char **uargv);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_free_argv` (function) `headers/spawn.h:42` `void spawn_free_argv(char **kargv, int argc);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_load_image` (function) `headers/spawn.h:45` `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out);` -- Docstring: Copy user argv into kernel memory, zero terminated.
- `spawn_execute` (function) `headers/spawn.h:48` `int spawn_execute(const char *resolved, const char *redirect, unsigned char *data, unsigned data_size, int argc...` -- Docstring: Copy user argv into kernel memory, zero terminated.

## headers/spinlock.h
Imported by: `drivers/pcm2.c`, `headers/futex.h`, `headers/kernel.h`, `headers/percpu_rq.h`, `headers/rcu.h`, `headers/sched.h`, `headers/smp.h`, `headers/sync.h`
- `spin_init` (function) `headers/spinlock.h:46` `static inline void spin_init(spinlock_t *lock)`
- `spin_save_irq` (function) `headers/spinlock.h:56` `static inline irqflags_t spin_save_irq(void)` -- Host unit-test variants (tests/test_sync.c, `make test-sync`): cli/sti and pushf/popf are privileged and fault in...
- `spin_restore_irq` (function) `headers/spinlock.h:57` `static inline void spin_restore_irq(irqflags_t flags)`
- `spin_lock` (function) `headers/spinlock.h:58` `static inline void spin_lock(spinlock_t *lock)`
- `spin_unlock` (function) `headers/spinlock.h:64` `static inline void spin_unlock(spinlock_t *lock)`
- `spin_lock_irqsave` (function) `headers/spinlock.h:68` `static inline void spin_lock_irqsave(spinlock_t *lock, irqflags_t *flags)`
- `spin_unlock_irqrestore` (function) `headers/spinlock.h:75` `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)`
- `spin_unlock_keep_irq` (function) `headers/spinlock.h:80` `static inline void spin_unlock_keep_irq(spinlock_t *lock)`
- `spin_trylock` (function) `headers/spinlock.h:84` `static inline int spin_trylock(spinlock_t *lock)`
- `spin_save_irq` (function) `headers/spinlock.h:92` `static inline irqflags_t spin_save_irq(void)` -- __sync_lock_release(&lock->locked); } static inline void spin_unlock_keep_irq(spinlock_t *lock) {...
- `spin_restore_irq` (function) `headers/spinlock.h:99` `static inline void spin_restore_irq(irqflags_t flags)` -- int was = __sync_lock_test_and_set(&lock->locked, 1); if (!was) __sync_synchronize(); return !was; } #else /* Read...
- `spin_lock` (function) `headers/spinlock.h:107` `static inline void spin_lock(spinlock_t *lock)` -- Acquire the lock and disable interrupts.
- `spin_unlock` (function) `headers/spinlock.h:118` `static inline void spin_unlock(spinlock_t *lock)` -- Release the lock and re-enable interrupts.
- `spin_unlock_keep_irq` (function) `headers/spinlock.h:130` `static inline void spin_unlock_keep_irq(spinlock_t *lock)` -- Release the lock WITHOUT touching interrupts (IF stays as-is).
- `spin_unlock_irqrestore` (function) `headers/spinlock.h:150` `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)` -- Release the lock and restore the saved interrupt state.

## headers/sync.h
Depends on: `headers/sched.h`, `headers/spinlock.h`
Imported by: `drivers/sb16.c`, `headers/futex.h`, `kernel/futex.c`, `kernel/sched.c`, `kernel/sync.c`, `kernel/syscalls.c`, `tests/test_sync.c`
- `wq_init` (function) `headers/sync.h:50` `void wq_init(wait_queue_t *q);`
- `sleep_on` (function) `headers/sync.h:51` `void sleep_on(wait_queue_t *q);`
- `wake_up` (function) `headers/sync.h:52` `int wake_up(wait_queue_t *q);`
- `wake_up_all` (function) `headers/sync.h:53` `int wake_up_all(wait_queue_t *q);`
- `inheritance` (function) `headers/sync.h:56` `* Priority inheritance (thesis correction 3): a low-priority holder that * blocks a high-priority waiter is boosted...`
- `mutex_init` (function) `headers/sync.h:72` `void mutex_init(mutex_t *m);`
- `mutex_lock` (function) `headers/sync.h:73` `void mutex_lock(mutex_t *m);`
- `mutex_unlock` (function) `headers/sync.h:74` `void mutex_unlock(mutex_t *m);`
- `mutex_trylock` (function) `headers/sync.h:75` `int mutex_trylock(mutex_t *m);`
- `mutex_note_waiter` (function) `headers/sync.h:76` `void mutex_note_waiter(mutex_t *m, int waiter);`
- `pi_set_base` (function) `headers/sync.h:77` `void pi_set_base(int pid, int prio);`
- `pi_get_eff` (function) `headers/sync.h:78` `int pi_get_eff(int pid);`
- `sem_init` (function) `headers/sync.h:89` `void sem_init(sem_t *s, int value);`
- `sem_wait` (function) `headers/sync.h:90` `void sem_wait(sem_t *s);`
- `sem_post` (function) `headers/sync.h:91` `void sem_post(sem_t *s);`
- `cond_init` (function) `headers/sync.h:103` `void cond_init(cond_t *c);`
- `cond_wait` (function) `headers/sync.h:104` `void cond_wait(cond_t *c, mutex_t *m);`
- `cond_signal` (function) `headers/sync.h:105` `void cond_signal(cond_t *c);`
- `cond_broadcast` (function) `headers/sync.h:106` `void cond_broadcast(cond_t *c);`
- `rwlock_init` (function) `headers/sync.h:118` `void rwlock_init(rwlock_t *rw);`
- `rwlock_read_lock` (function) `headers/sync.h:119` `void rwlock_read_lock(rwlock_t *rw);`
- `rwlock_read_unlock` (function) `headers/sync.h:120` `void rwlock_read_unlock(rwlock_t *rw);`
- `rwlock_write_lock` (function) `headers/sync.h:121` `void rwlock_write_lock(rwlock_t *rw);`
- `rwlock_write_unlock` (function) `headers/sync.h:122` `void rwlock_write_unlock(rwlock_t *rw);`

## headers/syscalls_proc.h
Imported by: `kernel/proc_sec.c`, `kernel/syscalls.c`, `kernel/syscalls_proc.c`
- `dispatcher` (function) `headers/syscalls_proc.h:5` `* dispatcher (kernel/syscalls.c). These handlers touch only scheduler * state (current_pid, procs[], do_* /...`
- `sys_minios_nice` (function) `headers/syscalls_proc.h:12` `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_minios_clone` (function) `headers/syscalls_proc.h:13` `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6);`
- `sys_minios_thread_spawn` (function) `headers/syscalls_proc.h:14` `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_yield` (function) `headers/syscalls_proc.h:15` `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_getpid` (function) `headers/syscalls_proc.h:16` `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_gettid` (function) `headers/syscalls_proc.h:17` `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_fork` (function) `headers/syscalls_proc.h:18` `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_clone` (function) `headers/syscalls_proc.h:19` `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_vfork` (function) `headers/syscalls_proc.h:20` `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_execve` (function) `headers/syscalls_proc.h:21` `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_exit` (function) `headers/syscalls_proc.h:22` `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_wait4` (function) `headers/syscalls_proc.h:23` `long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);`
- `sys_linux_kill` (function) `headers/syscalls_proc.h:24` `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);`
- `linux_signal_fatal` (function) `headers/syscalls_proc.h:31` `int linux_signal_fatal(long sig);` -- Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target. * The foreground shell reports a signal death...
- `do_proc_exit` (function) `headers/syscalls_proc.h:34` `long do_proc_exit(long code);` -- Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target. * The foreground shell reports a signal death...

## headers/tick.h
Imported by: `kernel/sched.c`, `kernel/tick.c`, `tests/test_tick.c`
- `tick_reset` (function) `headers/tick.h:47` `void tick_reset(void);` -- needs; the bound exists so the tables stay fixed-size. #define TICK_MAX_USB_LISTENERS 2 /** Docstring: Default bus...
- `tick_register_audio` (function) `headers/tick.h:54` `int tick_register_audio(tick_fn_t fn, void *ctx);` -- Docstring: Register an unconditional BSP audio effect.
- `tick_register_desktop` (function) `headers/tick.h:61` `int tick_register_desktop(tick_fn_t fn, void *ctx);` -- Docstring: Register a gated desktop effect.
- `tick_register_usb` (function) `headers/tick.h:69` `int tick_register_usb(tick_fn_t fn, void *ctx);` -- Docstring: Register a polled USB controller effect.
- `tick_run_usb` (function) `headers/tick.h:72` `void tick_run_usb(void);` -- Docstring: Register a polled USB controller effect.
- `tick_run_audio` (function) `headers/tick.h:75` `void tick_run_audio(void);` -- Docstring: Register a polled USB controller effect.
- `tick_run_desktop` (function) `headers/tick.h:78` `void tick_run_desktop(void);` -- The xHCI event ring is polled by decision rather than interrupt-driven, so this listener is the polling trigger.
- `tick_audio_count` (function) `headers/tick.h:81` `int tick_audio_count(void);` -- handler is null or the USB table is full.
- `tick_desktop_count` (function) `headers/tick.h:84` `int tick_desktop_count(void);` -- /** Docstring: Run USB listeners in registration order. void tick_run_usb(void); /** Docstring: Run audio listeners...
- `tick_desktop_due` (function) `headers/tick.h:92` `int tick_desktop_due(unsigned long long ticks, unsigned interval);` -- Docstring: Pure desktop gating predicate.


Next: [API_p5.md](API_p5.md)
