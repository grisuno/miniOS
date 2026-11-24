# Symbols (page 24 of 28)
Previous: [SYMBOLS_p23.md](SYMBOLS_p23.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `mthread_create` | function | `progs/src/mthreads.h:117` | `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)` |
| `mthread_entry` | function | `progs/src/mthreads.h:98` | `static void mthread_entry(void *p)` |
| `mthread_join` | function | `progs/src/mthreads.h:144` | `static int mthread_join(mthread_t t, void **retval)` |
| `mthread_slot_t` | struct | `progs/src/mthreads.h:42` | `` |
| `mthread_t` | type_alias | `progs/src/mthreads.h:35` | `typedef int mthread_t;` |
| `myield` | function | `progs/src/mthreads.h:59` | `static inline void myield(void)` |
| `MTOP_DISK_BUF` | macro | `progs/src/mtop.c:47` | `#define MTOP_DISK_BUF` |
| `MTOP_DISK_MAX` | macro | `progs/src/mtop.c:48` | `#define MTOP_DISK_MAX` |
| `MTOP_HIST` | macro | `progs/src/mtop.c:46` | `#define MTOP_HIST` |
| `MTOP_MINFO` | macro | `progs/src/mtop.c:49` | `#define MTOP_MINFO` |
| `close` | function | `progs/src/mtop.c:43` | `int close();` |
| `emit` | function | `progs/src/mtop.c:90` | `static void emit(char *s)` |
| `fclose` | function | `progs/src/mtop.c:39` | `int fclose();` |
| `fopen` | function | `progs/src/mtop.c:38` | `void *fopen();` |
| `fread` | function | `progs/src/mtop.c:40` | `int fread();` |
| `main` | function | `progs/src/mtop.c:531` | `int main(int argc, char **argv)` |
| `mtop_atoi` | function | `progs/src/mtop.c:117` | `static int mtop_atoi(char *s)` |
| `mtop_bar` | function | `progs/src/mtop.c:179` | `static void mtop_bar(long v, long max, int w)` |
| `mtop_clear` | function | `progs/src/mtop.c:113` | `static void mtop_clear(void)` |
| `mtop_clear_ansi` | function | `progs/src/mtop.c:103` | `static void mtop_clear_ansi(void)` |
| `mtop_cpu` | function | `progs/src/mtop.c:253` | `static long mtop_cpu(long *count, long *busy)` |
| `mtop_disk_open` | function | `progs/src/mtop.c:289` | `static void mtop_disk_open(void)` |
| `mtop_disk_read` | function | `progs/src/mtop.c:313` | `static long mtop_disk_read(long *bytes)` |
| `mtop_frame` | function | `progs/src/mtop.c:355` | `static void mtop_frame(int n)` |
| `mtop_hist_max` | function | `progs/src/mtop.c:194` | `static long mtop_hist_max(long *h, int n)` |
| `mtop_hist_push` | function | `progs/src/mtop.c:204` | `static void mtop_hist_push(long *h, long v)` |
| `mtop_key` | function | `progs/src/mtop.c:80` | `static long mtop_key(void)` |
| `mtop_mem` | function | `progs/src/mtop.c:242` | `static long mtop_mem(long *used, long *freeb, long *total)` |
| `mtop_minfo` | function | `progs/src/mtop.c:84` | `static long mtop_minfo(long sel, long *o1, long *o2)` |
| `mtop_net_probe` | function | `progs/src/mtop.c:337` | `static long mtop_net_probe(long *dns_ms, long *sock_ok)` |
| `mtop_put2` | function | `progs/src/mtop.c:158` | `static void mtop_put2(int v)` |
| `mtop_put_kb` | function | `progs/src/mtop.c:163` | `static void mtop_put_kb(long kb)` |
| `mtop_putu` | function | `progs/src/mtop.c:136` | `static void mtop_putu(long v)` |
| `mtop_quit_key` | function | `progs/src/mtop.c:94` | `static int mtop_quit_key(long k)` |
| `mtop_rtc` | function | `progs/src/mtop.c:76` | `static long mtop_rtc(int *h, int *m, int *s)` |
| `mtop_spark` | function | `progs/src/mtop.c:214` | `static void mtop_spark(long *h, int n)` |
| `mtop_time` | function | `progs/src/mtop.c:72` | `static long mtop_time(void)` |
| `net_dns_resolve` | function | `progs/src/mtop.c:44` | `int net_dns_resolve();` |
| `putchar` | function | `progs/src/mtop.c:35` | `int putchar();` |
| `rewind` | function | `progs/src/mtop.c:41` | `void rewind();` |
| `sc3` | function | `progs/src/mtop.c:63` | `static long sc3(long n, long a1, long a2, long a3)` |
| `socket` | function | `progs/src/mtop.c:42` | `int socket();` |
| `strcmp` | function | `progs/src/mtop.c:37` | `int strcmp();` |
| `strlen` | function | `progs/src/mtop.c:36` | `int strlen();` |
| `syscall` | function | `progs/src/mtop.c:12` | `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...` |
| `lmain` | function | `progs/src/mvrn.c:32` | `int lmain(void)` |
| `mvrn_exit` | function | `progs/src/mvrn.c:20` | `static void mvrn_exit(long code)` |
| `mvrn_fail` | function | `progs/src/mvrn.c:24` | `static void mvrn_fail(int step)` |
| `mvrn_sc3` | function | `progs/src/mvrn.c:9` | `static long mvrn_sc3(long n, long a1, long a2, long a3)` |
| `mvrn_write` | function | `progs/src/mvrn.c:16` | `static void mvrn_write(const char *s, unsigned long len)` |
| `_start` | function | `progs/src/nx.c:23` | `void _start(void)` |
| `exit_now` | function | `progs/src/nx.c:19` | `static void exit_now(long code)` |
| `write_str` | function | `progs/src/nx.c:11` | `static long write_str(const char *s, long n)` |
| `BUF_MS` | macro | `progs/src/opl3.c:32` | `#define BUF_MS` |
| `F_NUM_FACTOR` | macro | `progs/src/opl3.c:34` | `#define F_NUM_FACTOR` |
| `MONO_BYTES` | macro | `progs/src/opl3.c:30` | `#define MONO_BYTES` |
| `SAMPLE_RATE` | macro | `progs/src/opl3.c:28` | `#define SAMPLE_RATE` |
| `STEREO_FRAMES` | macro | `progs/src/opl3.c:29` | `#define STEREO_FRAMES` |
| `SYS_SB16_OPEN` | macro | `progs/src/opl3.c:22` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/opl3.c:23` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/opl3.c:21` | `#define SYS_TIME` |
| `SYS_WRITE` | macro | `progs/src/opl3.c:24` | `#define SYS_WRITE` |
| `busy_ms` | function | `progs/src/opl3.c:46` | `static void busy_ms(long ms)` |
| `main` | function | `progs/src/opl3.c:107` | `int main(void)` |
| `note_t` | struct | `progs/src/opl3.c:102` | `` |
| `opl3_note` | function | `progs/src/opl3.c:69` | `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)` |
| `opl3_set_instrument` | function | `progs/src/opl3.c:52` | `static void opl3_set_instrument(opl3_chip *chip)` |
| `render` | function | `progs/src/opl3.c:77` | `static void render(opl3_chip *chip, long ms, long *fail)` |
| `sys_open` | function | `progs/src/opl3.c:39` | `static long sys_open(long on)` |
| `sys_submit` | function | `progs/src/opl3.c:42` | `static long sys_submit(const void *buf, long len)` |
| `sys_time` | function | `progs/src/opl3.c:36` | `static long sys_time(void)` |
| `_start` | function | `progs/src/pcmap.c:75` | `void _start(void)` |
| `sc_exit` | function | `progs/src/pcmap.c:42` | `static void sc_exit(long code)` |
| `sc_fnv` | function | `progs/src/pcmap.c:46` | `static unsigned long sc_fnv(const char *p, long n)` |
| `sc_hex8` | function | `progs/src/pcmap.c:56` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mmap` | function | `progs/src/pcmap.c:21` | `static long sc_mmap(long len, long prot, long flags, long fd, long off)` |
| `sc_munmap` | function | `progs/src/pcmap.c:65` | `static long sc_munmap(long addr, long len)` |
| `sc_open` | function | `progs/src/pcmap.c:12` | `static long sc_open(const char *p)` |
| `sc_write` | function | `progs/src/pcmap.c:34` | `static long sc_write(long fd, const char *s, long n)` |
| `PIP_EXEC_FAILED` | macro | `progs/src/pip.c:26` | `#define PIP_EXEC_FAILED` |
| `PIP_MODULE_FLAG` | macro | `progs/src/pip.c:21` | `#define PIP_MODULE_FLAG` |
| `PIP_MODULE_NAME` | macro | `progs/src/pip.c:22` | `#define PIP_MODULE_NAME` |
| `PIP_PREFIX_WORDS` | macro | `progs/src/pip.c:24` | `#define PIP_PREFIX_WORDS` |
| `PIP_PYTHON_PATH` | macro | `progs/src/pip.c:19` | `#define PIP_PYTHON_PATH` |
| `main` | function | `progs/src/pip.c:45` | `int main(int argc, char **argv)` |
| `pip_note` | struct | `progs/src/pip.c:30` | `` |
| `lmain` | function | `progs/src/pollready.c:63` | `int lmain(long argc, char **argv)` |
| `p_atoi` | function | `progs/src/pollready.c:40` | `static int p_atoi(const char *s)` |
| `p_parse_ip` | function | `progs/src/pollready.c:46` | `static int p_parse_ip(const char *s, unsigned char out[4])` |
| `p_puts` | function | `progs/src/pollready.c:36` | `static void p_puts(long fd, const char *s)` |
| `p_strlen` | function | `progs/src/pollready.c:30` | `static unsigned long p_strlen(const char *s)` |
| `p_write` | function | `progs/src/pollready.c:26` | `static long p_write(long fd, const char *s, long n)` |
| `BUF` | macro | `progs/src/sbtone.c:26` | `#define BUF` |
| `RATE` | macro | `progs/src/sbtone.c:25` | `#define RATE` |
| `SYS_SB16_OPEN` | macro | `progs/src/sbtone.c:21` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/sbtone.c:22` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/sbtone.c:23` | `#define SYS_TIME` |
| `WINDOW_MS` | macro | `progs/src/sbtone.c:27` | `#define WINDOW_MS` |
| `buffers` | function | `progs/src/sbtone.c:14` | `*  * Exit code is the number of submitted buffers (0 on failure to open).  */  #include <stdio.h>...` |
| `main` | function | `progs/src/sbtone.c:36` | `int main(void)` |
| `SC_ARENA` | macro | `progs/src/scfuzz.c:16` | `#define SC_ARENA` |
| `SC_OPS` | macro | `progs/src/scfuzz.c:15` | `#define SC_OPS` |
| `SC_PAGE` | macro | `progs/src/scfuzz.c:17` | `#define SC_PAGE` |
| `SC_PAGES` | macro | `progs/src/scfuzz.c:18` | `#define SC_PAGES` |
| `SC_T0_BASE` | macro | `progs/src/scfuzz.c:19` | `#define SC_T0_BASE` |
| `SC_T0_N` | macro | `progs/src/scfuzz.c:20` | `#define SC_T0_N` |
| `SC_T1_BASE` | macro | `progs/src/scfuzz.c:21` | `#define SC_T1_BASE` |
| `SC_T1_N` | macro | `progs/src/scfuzz.c:22` | `#define SC_T1_N` |
| `_start` | function | `progs/src/scfuzz.c:167` | `void _start(void)` |
| `guest` | function | `progs/src/scfuzz.c:7` | `* the guest (the BDD timeout then talks). All fuzz maps stay inside  * one private 4 MB arena (pa...` |
| `sc_exit` | function | `progs/src/scfuzz.c:61` | `static void sc_exit(long code)` |
| `sc_fold` | function | `progs/src/scfuzz.c:76` | `static unsigned long sc_fold(unsigned long h, unsigned long v)` |
| `sc_hex8` | function | `progs/src/scfuzz.c:88` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mprotect` | function | `progs/src/scfuzz.c:38` | `static long sc_mprotect(long addr, long len, long prot)` |
| `sc_munmap` | function | `progs/src/scfuzz.c:49` | `static long sc_munmap(long addr, long len)` |
| `sc_rng` | function | `progs/src/scfuzz.c:67` | `static unsigned long sc_rng(unsigned long *s)` |
| `sc_thread1` | function | `progs/src/scfuzz.c:161` | `static void *sc_thread1(void *arg)` |
| `sc_worker` | function | `progs/src/scfuzz.c:97` | `static unsigned long sc_worker(int me, unsigned long seed)` |
| `sc_write` | function | `progs/src/scfuzz.c:53` | `static long sc_write(long fd, const char *s, long n)` |
| `expand` | function | `progs/src/shell.py:30` | `def expand(line, env)` |
| `main` | function | `progs/src/shell.py:36` | `def main()` |
| `run_capture` | function | `progs/src/shell.py:20` | `def run_capture(cmd, args)` |
| `SIGN_DESC_BYTES` | macro | `progs/src/sign.c:52` | `#define SIGN_DESC_BYTES` |
| `SIGN_EHDR_SIZE` | macro | `progs/src/sign.c:48` | `#define SIGN_EHDR_SIZE` |
| `SIGN_EM_X86_64` | macro | `progs/src/sign.c:44` | `#define SIGN_EM_X86_64` |
| `SIGN_ET_DYN` | macro | `progs/src/sign.c:43` | `#define SIGN_ET_DYN` |
| `SIGN_ET_EXEC` | macro | `progs/src/sign.c:42` | `#define SIGN_ET_EXEC` |
| `SIGN_EXIT_FAIL` | macro | `progs/src/sign.c:40` | `#define SIGN_EXIT_FAIL` |
| `SIGN_KEY_ID` | macro | `progs/src/sign.c:39` | `#define SIGN_KEY_ID` |
| `SIGN_MAX_FILE` | macro | `progs/src/sign.c:56` | `#define SIGN_MAX_FILE` |
| `SIGN_NOTE_HDR` | macro | `progs/src/sign.c:51` | `#define SIGN_NOTE_HDR` |
| `SIGN_NOTE_TOTAL` | macro | `progs/src/sign.c:54` | `#define SIGN_NOTE_TOTAL` |
| `SIGN_NOTE_TYPE` | macro | `progs/src/sign.c:55` | `#define SIGN_NOTE_TYPE` |
| `SIGN_PHDR_SIZE` | macro | `progs/src/sign.c:49` | `#define SIGN_PHDR_SIZE` |
| `SIGN_PT_LOAD` | macro | `progs/src/sign.c:45` | `#define SIGN_PT_LOAD` |
| `SIGN_PT_NOTE` | macro | `progs/src/sign.c:46` | `#define SIGN_PT_NOTE` |
| `SIGN_SEEK_END` | macro | `progs/src/sign.c:57` | `#define SIGN_SEEK_END` |
| `SIGN_SHDR_SIZE` | macro | `progs/src/sign.c:50` | `#define SIGN_SHDR_SIZE` |
| `SIGN_SHT_NOTE` | macro | `progs/src/sign.c:47` | `#define SIGN_SHT_NOTE` |
| `SIGN_SIG_BYTES` | macro | `progs/src/sign.c:53` | `#define SIGN_SIG_BYTES` |
| `below` | function | `progs/src/sign.c:195` | `* every other op below (`\|`, `<<`) is low-32 exact. */ static void sign_rotr(unsigned int *lo, un...` |
| `bits` | function | `progs/src/sign.c:672` | `* values here always fit 32 bits (limbs below 2^16, carries and  * products below 2^32), so the s...` |
| `fclose` | function | `progs/src/sign.c:31` | `int fclose();` |
| `fe_add` | function | `progs/src/sign.c:617` | `static void fe_add(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_cmov` | function | `progs/src/sign.c:573` | `static void fe_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` |
| `fe_copy` | function | `progs/src/sign.c:549` | `static void fe_copy(unsigned int *r, unsigned int *a)` |
| `fe_curved` | function | `progs/src/sign.c:812` | `static void fe_curved(unsigned int *d, unsigned int *d2)` |
| `fe_foldadd` | function | `progs/src/sign.c:690` | `static void fe_foldadd(unsigned int *row, int at, unsigned int x)` |
| `fe_frombytes` | function | `progs/src/sign.c:790` | `static void fe_frombytes(unsigned int *r, char *b)` |
| `fe_ge` | function | `progs/src/sign.c:586` | `static unsigned int fe_ge(unsigned int *a, unsigned int *b)` |
| `fe_inv` | function | `progs/src/sign.c:771` | `static void fe_inv(unsigned int *r, unsigned int *a)` |
| `fe_mul` | function | `progs/src/sign.c:696` | `static void fe_mul(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_off` | function | `progs/src/sign.c:845` | `static unsigned int *fe_off(unsigned int *p, int n)` |
| `fe_one` | function | `progs/src/sign.c:567` | `static void fe_one(unsigned int *r)` |
| `fe_rawsub` | function | `progs/src/sign.c:601` | `static void fe_rawsub(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_sq` | function | `progs/src/sign.c:766` | `static void fe_sq(unsigned int *r, unsigned int *a)` |
| `fe_sub` | function | `progs/src/sign.c:636` | `static void fe_sub(unsigned int *r, unsigned int *a, unsigned int *b)` |
| `fe_tobytes` | function | `progs/src/sign.c:800` | `static void fe_tobytes(char *b, unsigned int *a)` |
| `fe_zero` | function | `progs/src/sign.c:558` | `static void fe_zero(unsigned int *r)` |
| `fopen` | function | `progs/src/sign.c:30` | `void *fopen();` |
| `fread` | function | `progs/src/sign.c:32` | `int fread();` |
| `free` | function | `progs/src/sign.c:37` | `void free();` |
| `fseek` | function | `progs/src/sign.c:34` | `int fseek();` |
| `ftell` | function | `progs/src/sign.c:35` | `int ftell();` |
| `fwrite` | function | `progs/src/sign.c:33` | `int fwrite();` |
| `ge_add` | function | `progs/src/sign.c:860` | `static void ge_add(unsigned int *r, unsigned int *p, unsigned int *q, unsigned int *d2)` |
| `ge_cmov` | function | `progs/src/sign.c:850` | `static void ge_cmov(unsigned int *r, unsigned int *b, unsigned int flag)` |
| `ge_copy` | function | `progs/src/sign.c:829` | `static void ge_copy(unsigned int *r, unsigned int *a)` |
| `ge_double` | function | `progs/src/sign.c:892` | `static void ge_double(unsigned int *r, unsigned int *p)` |
| `ge_scalarmult` | function | `progs/src/sign.c:926` | `static void ge_scalarmult(unsigned int *r, unsigned int *p, char *s, unsigned int *d2)` |
| `main` | function | `progs/src/sign.c:1657` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/src/sign.c:36` | `void *malloc();` |
| `printf` | function | `progs/src/sign.c:28` | `int printf();` |
| `sc_mod_l` | function | `progs/src/sign.c:951` | `static void sc_mod_l(unsigned int *r, unsigned int *t16)` |
| `sc_mul_add` | function | `progs/src/sign.c:1013` | `static void sc_mul_add(unsigned int *r, unsigned int *a, unsigned int *b, unsigned int *c)` |
| `sign_add3` | function | `progs/src/sign.c:237` | `static unsigned int sign_add3(unsigned int *s, unsigned int a, unsigned int b, unsigned int c)` |
| `sign_append` | function | `progs/src/sign.c:1393` | `static int sign_append(char *name, char *img, int size, int shoff, int shnum, int shentsize,     ...` |
| `sign_be32` | function | `progs/src/sign.c:247` | `static unsigned int sign_be32(char *p, int off)` |
| `sign_block` | function | `progs/src/sign.c:253` | `static void sign_block(void)` |
| `sign_borrow2` | function | `progs/src/sign.c:230` | `static unsigned int sign_borrow2(unsigned int x, unsigned int y, unsigned int s)` |
| `sign_byte` | function | `progs/src/sign.c:111` | `static unsigned int sign_byte(char *p, int i)` |
| `sign_copy` | function | `progs/src/sign.c:119` | `static void sign_copy(char *dst, char *src, int n)` |
| `sign_digest` | function | `progs/src/sign.c:1112` | `static void sign_digest(char *sig, char *digest)` |
| `sign_digest_of` | function | `progs/src/sign.c:1307` | `static int sign_digest_of(char *img, int size, int entry, char *ph, int phnum, char *digest)` |
| `sign_feed32` | function | `progs/src/sign.c:490` | `static void sign_feed32(unsigned int v)` |
| `sign_file` | function | `progs/src/sign.c:1529` | `static int sign_file(char *name)` |
| `sign_hexval` | function | `progs/src/sign.c:89` | `static unsigned int sign_hexval(char c)` |
| `sign_key_init` | function | `progs/src/sign.c:500` | `static void sign_key_init(void)` |
| `sign_le16` | function | `progs/src/sign.c:136` | `static unsigned int sign_le16(char *p, int off)` |
| `sign_le32` | function | `progs/src/sign.c:141` | `static unsigned int sign_le32(char *p, int off)` |
| `sign_note_span` | function | `progs/src/sign.c:1273` | `static int sign_note_span(char *img, int off, int len, int *desc)` |
| `sign_offok` | function | `progs/src/sign.c:180` | `static int sign_offok(char *p, int off, int *lo)` |
| `sign_patch_notes` | function | `progs/src/sign.c:1356` | `static int sign_patch_notes(char *img, int size, char *ph, int phnum, char *desc)` |
| `sign_points_init` | function | `progs/src/sign.c:1081` | `static void sign_points_init(void)` |
| `sign_put32` | function | `progs/src/sign.c:147` | `static void sign_put32(char *p, int off, unsigned int v)` |
| `sign_read` | function | `progs/src/sign.c:1232` | `static char *sign_read(char *name, int *len)` |
| `sign_rev32` | function | `progs/src/sign.c:1070` | `static void sign_rev32(char *b)` |
| `sign_selftest` | function | `progs/src/sign.c:1637` | `static int sign_selftest(void)` |
| `sign_sha_final` | function | `progs/src/sign.c:442` | `static void sign_sha_final(char *out)` |
| `sign_sha_init` | function | `progs/src/sign.c:387` | `static void sign_sha_init(void)` |
| `sign_sha_update` | function | `progs/src/sign.c:410` | `static void sign_sha_update(char *data, int len)` |
| `sign_strlen` | function | `progs/src/sign.c:128` | `static int sign_strlen(char *s)` |
| `sign_unhex` | function | `progs/src/sign.c:100` | `static void sign_unhex(char *out, char *in, int n)` |
| `sign_write` | function | `progs/src/sign.c:1260` | `static int sign_write(char *name, char *data, int len)` |
| `strcmp` | function | `progs/src/sign.c:29` | `int strcmp();` |
| `SPIN_WLA` | macro | `progs/src/spin.c:58` | `#define SPIN_WLA` |
| `SPIN_WLB` | macro | `progs/src/spin.c:59` | `#define SPIN_WLB` |
| `SPIN_WLH` | macro | `progs/src/spin.c:57` | `#define SPIN_WLH` |
| `SPIN_WLW` | macro | `progs/src/spin.c:56` | `#define SPIN_WLW` |
| `lmain` | function | `progs/src/spin.c:225` | `int lmain(long argc, char **argv)` |
| `lx_atoi` | function | `progs/src/spin.c:42` | `static long lx_atoi(const char *s)` |
| `lx_strlen` | function | `progs/src/spin.c:20` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/spin.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/spin.c:26` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/spin.c:30` | `static void lx_write_int(long v)` |
| `spin_box_ok` | function | `progs/src/spin.c:82` | `static int spin_box_ok(const char *box)` |
| `spin_emit` | function | `progs/src/spin.c:114` | `static int spin_emit(const char *box, unsigned int seq,         const unsigned char *msg, long mlen)` |
| `spin_hdr` | function | `progs/src/spin.c:73` | `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,         unsigned long ...` |
| `spin_hex8` | function | `progs/src/spin.c:95` | `static void spin_hex8(unsigned int v, char *dst)` |
| `spin_pixels` | function | `progs/src/spin.c:169` | `static void spin_pixels(long off)` |
| `spin_raw_file` | function | `progs/src/spin.c:145` | `static int spin_raw_file(const char *box)` |
| `spin_u32` | function | `progs/src/spin.c:66` | `static void spin_u32(unsigned char *d, unsigned long v)` |
| `spin_wl` | function | `progs/src/spin.c:181` | `static int spin_wl(const char *box, const char *narg)` |
| `spin_write_all` | function | `progs/src/spin.c:104` | `static long spin_write_all(long fd, const unsigned char *buf, long len)` |
| `add` | function | `progs/src/test.c:1` | `int add(int a, int b)` |
| `main` | function | `progs/src/test.c:2` | `int main(void)` |
| `check` | function | `progs/src/test.lua:12` | `` |
| `read_file` | function | `progs/src/test.lua:30` | `` |
| `test_bin_aes` | function | `progs/src/test.lua:175` | `` |
| `test_bin_cp` | function | `progs/src/test.lua:135` | `` |
| `test_bin_freedom` | function | `progs/src/test.lua:205` | `` |
| `test_bin_json` | function | `progs/src/test.lua:194` | `` |
| `test_bin_lz4` | function | `progs/src/test.lua:141` | `` |
| `test_bin_lzss` | function | `progs/src/test.lua:158` | `` |
| `test_dlmalloc` | function | `progs/src/test.lua:80` | `` |
| `test_filesystem` | function | `progs/src/test.lua:53` | `` |
| `test_ftest` | function | `progs/src/test.lua:90` | `` |
| `test_hello` | function | `progs/src/test.lua:85` | `` |
| `test_ld` | function | `progs/src/test.lua:100` | `` |
| `test_minigcc` | function | `progs/src/test.lua:95` | `` |
| `test_module_bindings` | function | `progs/src/test.lua:40` | `` |
| `test_spawn_preserves_interpreter` | function | `progs/src/test.lua:122` | `` |
| `test_stb` | function | `progs/src/test.lua:75` | `` |
| `test_toolchain_roundtrip` | function | `progs/src/test.lua:112` | `` |
| `test_xxhash` | function | `progs/src/test.lua:70` | `` |
| `write_file` | function | `progs/src/test.lua:22` | `` |
| `check` | function | `progs/src/test.py:15` | `def check(name, cond, detail)` |
| `main` | function | `progs/src/test.py:261` | `def main()` |
| `safe_run` | function | `progs/src/test.py:25` | `def safe_run()` |
| `test_bin_aes` | function | `progs/src/test.py:209` | `def test_bin_aes()` |
| `test_bin_cp` | function | `progs/src/test.py:148` | `def test_bin_cp()` |
| `test_bin_freedom` | function | `progs/src/test.py:253` | `def test_bin_freedom()` |
| `test_bin_json` | function | `progs/src/test.py:239` | `def test_bin_json()` |
| `test_bin_lz4` | function | `progs/src/test.py:153` | `def test_bin_lz4()` |
| `test_bin_lzss` | function | `progs/src/test.py:181` | `def test_bin_lzss()` |
| `test_dlmalloc` | function | `progs/src/test.py:82` | `def test_dlmalloc()` |
| `test_filesystem` | function | `progs/src/test.py:56` | `def test_filesystem()` |
| `test_ftest` | function | `progs/src/test.py:92` | `def test_ftest()` |
| `test_hello` | function | `progs/src/test.py:87` | `def test_hello()` |
| `test_ld` | function | `progs/src/test.py:102` | `def test_ld()` |
| `test_minigcc` | function | `progs/src/test.py:97` | `def test_minigcc()` |
| `test_module_bindings` | function | `progs/src/test.py:38` | `def test_module_bindings()` |
| `test_spawn_preserves_interpreter` | function | `progs/src/test.py:134` | `def test_spawn_preserves_interpreter()` |
| `test_stb` | function | `progs/src/test.py:77` | `def test_stb()` |
| `test_toolchain_roundtrip` | function | `progs/src/test.py:119` | `def test_toolchain_roundtrip()` |
| `test_xxhash` | function | `progs/src/test.py:72` | `def test_xxhash()` |
| `_asyncio_double` | function | `progs/src/test_py.py:79` | `def _asyncio_double(n, ms)` |
| `_asyncio_main` | function | `progs/src/test_py.py:84` | `def _asyncio_main()` |
| `_asyncio_wire_check` | function | `progs/src/test_py.py:88` | `def _asyncio_wire_check(host, port)` |
| `_one` | function | `progs/src/test_py.py:89` | `def _one()` |
| `check` | function | `progs/src/test_py.py:12` | `def check(name, cond)` |
| `BUFSZ` | macro | `progs/src/thdemo.c:24` | `#define BUFSZ` |
| `EXPECTED_N` | macro | `progs/src/thdemo.c:26` | `#define EXPECTED_N` |
| `EXPECTED_SUM` | macro | `progs/src/thdemo.c:27` | `#define EXPECTED_SUM` |
| `NCONS` | macro | `progs/src/thdemo.c:22` | `#define NCONS` |
| `NPROD` | macro | `progs/src/thdemo.c:21` | `#define NPROD` |
| `PER_PROD` | macro | `progs/src/thdemo.c:23` | `#define PER_PROD` |
| `consumer` | function | `progs/src/thdemo.c:57` | `static void *consumer(void *p)` |
| `main` | function | `progs/src/thdemo.c:82` | `int main(void)` |
| `producer` | function | `progs/src/thdemo.c:36` | `static void *producer(void *p)` |
| `threads` | function | `progs/src/thdemo.c:3` | `* * Ten threads (1 main + 5 producers + 4 consumers) share one address * space through thread_spawn (MiniOS syscall...` |
| `main` | function | `progs/src/w1.c:3` | `int main(void)` |
| `write` | function | `progs/src/w1.c:1` | `int write(int fd, char *buf, int n);` |
| `_DEFAULT_SOURCE` | macro | `progs/tls_u/tls_u_main.c:15` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `progs/tls_u/tls_u_main.c:14` | `#define _POSIX_C_SOURCE` |
| `main` | function | `progs/tls_u/tls_u_main.c:61` | `int main(int argc, char **argv)` |
| `parse_port` | function | `progs/tls_u/tls_u_main.c:47` | `static int parse_port(const char *s)` |
| `syscall` | function | `progs/tls_u/tls_u_main.c:10` | `* the MiniOS DNS syscall (200, sig 0: error-check only, sends nothing).  * The kernel keeps servi...` |
| `_DEFAULT_SOURCE` | macro | `progs/tls_u/tls_u_port.c:13` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `progs/tls_u/tls_u_port.c:12` | `#define _POSIX_C_SOURCE` |
| `answer` | function | `progs/tls_u/tls_u_port.c:163` | `* answer (some resolvers go IPv6-only on the first query). */ memset(&hints, 0, sizeof(hints));` |
| `net_dns_resolve` | function | `progs/tls_u/tls_u_port.c:183` | `int net_dns_resolve(const char *host)` |
| `parse_quad` | function | `progs/tls_u/tls_u_port.c:122` | `static int parse_quad(const char *s, unsigned *ip_out)` |
| `sockets` | function | `progs/tls_u/tls_u_port.c:5` | `* sockets: on the host they are host sockets (used by the  * openssl-s_server interop test), insi...` |
| `tls_close` | function | `progs/tls_u/tls_u_port.c:67` | `void tls_close(int fd)` |
| `tls_free_fd` | function | `progs/tls_u/tls_u_port.c:66` | `void tls_free_fd(int fd);` |
| `tls_now_days` | function | `progs/tls_u/tls_u_port.c:72` | `long tls_now_days(void)` |
| `tls_random` | function | `progs/tls_u/tls_u_port.c:78` | `void tls_random(unsigned char *out, unsigned len)` |
| `tls_u_close` | function | `progs/tls_u/tls_u_port.c:55` | `void tls_u_close(int fd)` |
| `tls_u_recv` | function | `progs/tls_u/tls_u_port.c:39` | `int tls_u_recv(int fd, char *buf, int len)` |
| `tls_u_recv_timeout` | function | `progs/tls_u/tls_u_port.c:44` | `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms)` |
| `tls_u_resolve` | function | `progs/tls_u/tls_u_port.c:147` | `int tls_u_resolve(const char *host, unsigned *ip_out)` |
| `u_raw_syscall3` | function | `progs/tls_u/tls_u_port.c:99` | `static long u_raw_syscall3(long n, long a1, long a2, long a3)` |
| `D_HEAD` | macro | `progs/topogpt3/topogpt3.c:70` | `#define D_HEAD` |
| `D_LAT_Q` | macro | `progs/topogpt3/topogpt3.c:82` | `#define D_LAT_Q` |
| `D_MODEL` | macro | `progs/topogpt3/topogpt3.c:66` | `#define D_MODEL` |
| `D_QUAT` | macro | `progs/topogpt3/topogpt3.c:71` | `#define D_QUAT` |
| `EMBED_INNER` | macro | `progs/topogpt3/topogpt3.c:90` | `#define EMBED_INNER` |
| `EOS_TOKEN` | macro | `progs/topogpt3/topogpt3.c:89` | `#define EOS_TOKEN` |
| `EPS_RMS` | macro | `progs/topogpt3/topogpt3.c:92` | `#define EPS_RMS` |
| `EXPERT_INNER` | macro | `progs/topogpt3/topogpt3.c:87` | `#define EXPERT_INNER` |
| `FILE` | struct | `progs/topogpt3/topogpt3.c:24` | `` |
| `FREQ_W` | macro | `progs/topogpt3/topogpt3.c:85` | `#define FREQ_W` |
| `GQA_GROUPS` | macro | `progs/topogpt3/topogpt3.c:69` | `#define GQA_GROUPS` |
| `LayerWeights` | struct | `progs/topogpt3/topogpt3.c:176` | `` |
| `MAX_LINE` | macro | `progs/topogpt3/topogpt3.c:96` | `#define MAX_LINE` |
| `MAX_PROMPT_LEN` | macro | `progs/topogpt3/topogpt3.c:95` | `#define MAX_PROMPT_LEN` |
| `MAX_SEQ_LEN` | macro | `progs/topogpt3/topogpt3.c:73` | `#define MAX_SEQ_LEN` |
| `MAX_TOKENS` | macro | `progs/topogpt3/topogpt3.c:94` | `#define MAX_TOKENS` |
| `MOE_TOP_K` | macro | `progs/topogpt3/topogpt3.c:75` | `#define MOE_TOP_K` |
| `ModelWeights` | struct | `progs/topogpt3/topogpt3.c:224` | `` |
| `NULL` | macro | `progs/topogpt3/topogpt3.c:43` | `#define NULL` |
| `N_ANGULAR` | macro | `progs/topogpt3/topogpt3.c:78` | `#define N_ANGULAR` |
| `N_EDGES` | macro | `progs/topogpt3/topogpt3.c:80` | `#define N_EDGES` |
| `N_EDGE_TYPES` | macro | `progs/topogpt3/topogpt3.c:79` | `#define N_EDGE_TYPES` |
| `N_EXPERTS` | macro | `progs/topogpt3/topogpt3.c:74` | `#define N_EXPERTS` |
| `N_HEADS` | macro | `progs/topogpt3/topogpt3.c:67` | `#define N_HEADS` |
| `N_KV_HEADS` | macro | `progs/topogpt3/topogpt3.c:68` | `#define N_KV_HEADS` |
| `N_LAYERS` | macro | `progs/topogpt3/topogpt3.c:72` | `#define N_LAYERS` |
| `N_NODES` | macro | `progs/topogpt3/topogpt3.c:76` | `#define N_NODES` |
| `N_RADIAL` | macro | `progs/topogpt3/topogpt3.c:77` | `#define N_RADIAL` |
| `N_SPECTRAL_LAYERS` | macro | `progs/topogpt3/topogpt3.c:86` | `#define N_SPECTRAL_LAYERS` |
| `PI` | macro | `progs/topogpt3/topogpt3.c:91` | `#define PI` |
| `READOUT_INNER` | macro | `progs/topogpt3/topogpt3.c:88` | `#define READOUT_INNER` |
| `READ_TENSOR` | macro | `progs/topogpt3/topogpt3.c:1310` | `#define READ_TENSOR(dest, count)` |
| `READ_TENSOR16` | macro | `progs/topogpt3/topogpt3.c:1480` | `#define READ_TENSOR16(dest, count)` |
| `SEEK_CUR` | macro | `progs/topogpt3/topogpt3.c:45` | `#define SEEK_CUR` |
| `SEEK_END` | macro | `progs/topogpt3/topogpt3.c:46` | `#define SEEK_END` |
| `SEEK_SET` | macro | `progs/topogpt3/topogpt3.c:44` | `#define SEEK_SET` |
| `SKIP_TENSOR` | macro | `progs/topogpt3/topogpt3.c:1300` | `#define SKIP_TENSOR()` |
| `SKIP_TENSOR16` | macro | `progs/topogpt3/topogpt3.c:1470` | `#define SKIP_TENSOR16()` |
| `SPECTRAL_LATENT_DIM` | macro | `progs/topogpt3/topogpt3.c:81` | `#define SPECTRAL_LATENT_DIM` |
| `TOK_TAB_SIZE` | macro | `progs/topogpt3/topogpt3.c:97` | `#define TOK_TAB_SIZE` |
| `TOK_VOCAB_SIZE` | macro | `progs/topogpt3/topogpt3.c:98` | `#define TOK_VOCAB_SIZE` |
| `TORUS_GRID_H` | macro | `progs/topogpt3/topogpt3.c:83` | `#define TORUS_GRID_H` |
| `TORUS_GRID_W` | macro | `progs/topogpt3/topogpt3.c:84` | `#define TORUS_GRID_W` |
| `TORUS_TEMP` | macro | `progs/topogpt3/topogpt3.c:93` | `#define TORUS_TEMP` |
| `VOCAB_SIZE` | macro | `progs/topogpt3/topogpt3.c:65` | `#define VOCAB_SIZE` |
| `apply_repetition_penalty` | function | `progs/topogpt3/topogpt3.c:1216` | `static void apply_repetition_penalty(float *logits, int n, const int *tokens,                    ...` |
| `apply_temperature` | function | `progs/topogpt3/topogpt3.c:1210` | `static void apply_temperature(float *logits, int n, float temp)` |
| `apply_top_k` | function | `progs/topogpt3/topogpt3.c:1229` | `static void apply_top_k(float *logits, int n, int k)` |
| `attention_forward` | function | `progs/topogpt3/topogpt3.c:978` | `static void attention_forward(const float *x, float *out, int layer_idx, int pos, int total_kv_co...` |
| `build_torus_graph` | function | `progs/topogpt3/topogpt3.c:296` | `static void build_torus_graph(void)` |
| `cmul` | function | `progs/topogpt3/topogpt3.c:664` | `static void cmul(float ar, float ai, float cr, float di, float *rr, float *ri)` |
| `decode_token` | function | `progs/topogpt3/topogpt3.c:1614` | `static void decode_token(int tid)` |
| `decode_token_tiktoken` | function | `progs/topogpt3/topogpt3.c:1652` | `static void decode_token_tiktoken(int tid)` |
| `fclose` | function | `progs/topogpt3/topogpt3.c:37` | `extern int fclose(FILE *);` |
| `fflush` | function | `progs/topogpt3/topogpt3.c:42` | `extern int fflush(FILE *);` |
| `filter1d` | function | `progs/topogpt3/topogpt3.c:537` | `static void filter1d(const float *x, const float *kr, const float *ki,                       floa...` |
| `fopen` | function | `progs/topogpt3/topogpt3.c:36` | `extern FILE *fopen(const char *, const char *);` |
| `forward` | function | `progs/topogpt3/topogpt3.c:1128` | `static void forward(const int *token_ids, int seq_len, float *logits_out)` |
| `fprintf` | function | `progs/topogpt3/topogpt3.c:29` | `extern int fprintf(FILE *, const char *, ...);` |
| `fputc` | function | `progs/topogpt3/topogpt3.c:34` | `extern int fputc(int, FILE *);` |
| `fputs` | function | `progs/topogpt3/topogpt3.c:35` | `extern int fputs(const char *, FILE *);` |
| `fread` | function | `progs/topogpt3/topogpt3.c:38` | `extern unsigned long fread(void *, unsigned long, unsigned long, FILE *);` |
| `free` | function | `progs/topogpt3/topogpt3.c:48` | `extern void free(void *);` |
| `fseek` | function | `progs/topogpt3/topogpt3.c:40` | `extern int fseek(FILE *, long, int);` |
| `ftell` | function | `progs/topogpt3/topogpt3.c:41` | `extern long ftell(FILE *);` |
| `fwrite` | function | `progs/topogpt3/topogpt3.c:39` | `extern unsigned long fwrite(const void *, unsigned long, unsigned long, FILE *);` |
| `gelu` | function | `progs/topogpt3/topogpt3.c:400` | `static void gelu(float *x, int n)` |
| `generate` | function | `progs/topogpt3/topogpt3.c:1725` | `static void generate(const char *prompt, int max_new_tokens, float temperature,                  ...` |
| `generate_tokens` | function | `progs/topogpt3/topogpt3.c:1661` | `static void generate_tokens(int *prompt_tokens, int n_prompt, int max_new_tokens,                ...` |
| `ifft2d` | function | `progs/topogpt3/topogpt3.c:580` | `static void ifft2d(float *data_r, float *data_i, int h, int w)` |
| `ifft_radix2` | function | `progs/topogpt3/topogpt3.c:505` | `static void ifft_radix2(float *real, float *imag, int n)` |
| `interactive_mode` | function | `progs/topogpt3/topogpt3.c:1736` | `static void interactive_mode(void)` |
| `irfft` | function | `progs/topogpt3/topogpt3.c:522` | `static void irfft(const float *Xr, const float *Xi, float *x, int n)` |
| `irfft2d` | function | `progs/topogpt3/topogpt3.c:629` | `static void irfft2d(const float *in_r, const float *in_i, float *out,                      int h,...` |
| `load_token_file` | function | `progs/topogpt3/topogpt3.c:1629` | `static int load_token_file(const char *path, int *out_ids, int max_ids)` |
| `load_vocab` | function | `progs/topogpt3/topogpt3.c:255` | `static void load_vocab(const char *path)` |
| `load_weights` | function | `progs/topogpt3/topogpt3.c:1282` | `static int load_weights(const char *path)` |
| `load_weights_auto` | function | `progs/topogpt3/topogpt3.c:1583` | `static int load_weights_auto(const char *path)` |
| `load_weights_fp16` | function | `progs/topogpt3/topogpt3.c:1452` | `static int load_weights_fp16(const char *path)` |
| `main` | function | `progs/topogpt3/topogpt3.c:1885` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/topogpt3/topogpt3.c:47` | `extern void *malloc(unsigned long);` |
| `matvec` | function | `progs/topogpt3/topogpt3.c:359` | `static void matvec(const float *W, const float *x, float *y, int rows, int cols)` |
| `matvec_bias` | function | `progs/topogpt3/topogpt3.c:370` | `static void matvec_bias(const float *W, const float *b, const float *x, float *y,                ...` |
| `memcpy` | function | `progs/topogpt3/topogpt3.c:49` | `extern void *memcpy(void *, const void *, unsigned long);` |
| `memset` | function | `progs/topogpt3/topogpt3.c:50` | `extern void *memset(void *, int, unsigned long);` |
| `message_passing` | function | `progs/topogpt3/topogpt3.c:843` | `static void message_passing(const float *node_feat, float *out,                              cons...` |
| `moe_forward` | function | `progs/topogpt3/topogpt3.c:1078` | `static void moe_forward(const float *x, float *out, const LayerWeights *lw)` |
| `precompute_rope` | function | `progs/topogpt3/topogpt3.c:327` | `static void precompute_rope(void)` |
| `print_help` | function | `progs/topogpt3/topogpt3.c:1850` | `static void print_help(void)` |
| `printf` | function | `progs/topogpt3/topogpt3.c:28` | `extern int printf(const char *, ...);` |
| `process_torus_grid` | function | `progs/topogpt3/topogpt3.c:800` | `static void process_torus_grid(const float *grid, float *out, const LayerWeights *lw)` |
| `putchar` | function | `progs/topogpt3/topogpt3.c:33` | `extern int putchar(int);` |
| `puts` | function | `progs/topogpt3/topogpt3.c:32` | `extern int puts(const char *);` |
| `quat_hamilton` | function | `progs/topogpt3/topogpt3.c:440` | `static void quat_hamilton(const float *a, const float *b, float *c)` |
| `quat_linear` | function | `progs/topogpt3/topogpt3.c:448` | `static void quat_linear(const float *Ww, const float *Wx, const float *Wy, const float *Wz,      ...` |
| `quat_normalize` | function | `progs/topogpt3/topogpt3.c:435` | `static void quat_normalize(float *q)` |
| `quat_spectral_layer_2d` | function | `progs/topogpt3/topogpt3.c:695` | `static void quat_spectral_layer_2d(     const float *x, float *y,     const float *kr_w, const fl...` |
| `rfft` | function | `progs/topogpt3/topogpt3.c:513` | `static void rfft(const float *x, float *Xr, float *Xi, int n)` |
| `rfft2d_real` | function | `progs/topogpt3/topogpt3.c:602` | `static void rfft2d_real(const float *data, float *out_r, float *out_i,                          i...` |
| `rmsnorm` | function | `progs/topogpt3/topogpt3.c:382` | `static void rmsnorm(const float *x, const float *w, float *y, int d)` |
| `sample` | function | `progs/topogpt3/topogpt3.c:1248` | `static int sample(const float *logits, int n)` |
| `silu` | function | `progs/topogpt3/topogpt3.c:410` | `static void silu(float *x, int n)` |
| `snprintf` | function | `progs/topogpt3/topogpt3.c:31` | `extern int snprintf(char *, unsigned long, const char *, ...);` |
| `softmax` | function | `progs/topogpt3/topogpt3.c:391` | `static void softmax(float *x, int n)` |
| `spectral_ae_decode` | function | `progs/topogpt3/topogpt3.c:793` | `static void spectral_ae_decode(const float *z, float *x, const LayerWeights *lw)` |
| `spectral_ae_encode` | function | `progs/topogpt3/topogpt3.c:785` | `static void spectral_ae_encode(const float *x, float *z, const LayerWeights *lw)` |
| `spectral_contract` | function | `progs/topogpt3/topogpt3.c:670` | `static void spectral_contract(const float *Wr, const float *Wi,                                co...` |
| `sprintf` | function | `progs/topogpt3/topogpt3.c:30` | `extern int sprintf(char *, const char *, ...);` |
| `stderr` | variable | `progs/topogpt3/topogpt3.c:27` | `extern FILE *stderr;` |
| `stdin` | variable | `progs/topogpt3/topogpt3.c:25` | `extern FILE *stdin;` |
| `stdout` | variable | `progs/topogpt3/topogpt3.c:26` | `extern FILE *stdout;` |
| `strcmp` | function | `progs/topogpt3/topogpt3.c:51` | `extern int strcmp(const char *, const char *);` |
| `strlen` | function | `progs/topogpt3/topogpt3.c:53` | `extern unsigned long strlen(const char *);` |
| `strncmp` | function | `progs/topogpt3/topogpt3.c:52` | `extern int strncmp(const char *, const char *, unsigned long);` |
| `strstr` | function | `progs/topogpt3/topogpt3.c:54` | `extern char *strstr(const char *, const char *);` |
| `swiglu` | function | `progs/topogpt3/topogpt3.c:418` | `static void swiglu(const float *gate_w, const float *up_w, const float *down_w,                  ...` |
| `tg_cos` | function | `progs/topogpt3/topogpt3.c:144` | `static float tg_cos(float x)` |
| `tg_exp` | function | `progs/topogpt3/topogpt3.c:114` | `static float tg_exp(float x)` |
| `tg_fabs` | function | `progs/topogpt3/topogpt3.c:148` | `static float tg_fabs(float x)` |
| `tg_fmax` | function | `progs/topogpt3/topogpt3.c:164` | `static float tg_fmax(float a, float b)` |
| `tg_fmin` | function | `progs/topogpt3/topogpt3.c:168` | `static float tg_fmin(float a, float b)` |
| `tg_log` | function | `progs/topogpt3/topogpt3.c:152` | `static float tg_log(float x)` |
| `tg_sin` | function | `progs/topogpt3/topogpt3.c:135` | `static float tg_sin(float x)` |
| `tg_tanh` | function | `progs/topogpt3/topogpt3.c:128` | `static float tg_tanh(float x)` |
| `time_now_ms` | function | `progs/topogpt3/topogpt3.c:1600` | `static double time_now_ms(void)` |
| `tokenize_string` | function | `progs/topogpt3/topogpt3.c:1195` | `static int tokenize_string(const char *text, int *tokens, int max_tokens)` |
| `torus_brain_forward` | function | `progs/topogpt3/topogpt3.c:888` | `static void torus_brain_forward(const float *x, float *out, float *recon_loss,                   ...` |
| `torus_soft_assign` | function | `progs/topogpt3/topogpt3.c:821` | `static void torus_soft_assign(const float *phi1, const float *phi2,                              ...` |
| `MINIOS_LEAKCHECK_IMPL` | macro | `progs/vedit/vedit.c:33` | `#define MINIOS_LEAKCHECK_IMPL` |
| `MINIOS_LK_ENABLE` | macro | `progs/vedit/vedit.c:34` | `#define MINIOS_LK_ENABLE` |
| `VEDIT_BASE_MAX` | macro | `progs/vedit/vedit.c:143` | `#define VEDIT_BASE_MAX` |
| `VEDIT_BUILD_LOG` | macro | `progs/vedit/vedit.c:139` | `#define VEDIT_BUILD_LOG` |
| `VEDIT_CLIP_MAX` | macro | `progs/vedit/vedit.c:3278` | `#define VEDIT_CLIP_MAX` |
| `VEDIT_CMD_MAX` | macro | `progs/vedit/vedit.c:256` | `#define VEDIT_CMD_MAX` |
| `VEDIT_COL_COMMENT` | macro | `progs/vedit/vedit.c:159` | `#define VEDIT_COL_COMMENT` |
| `VEDIT_COL_DEFAULT` | macro | `progs/vedit/vedit.c:156` | `#define VEDIT_COL_DEFAULT` |
| `VEDIT_COL_KEYWORD` | macro | `progs/vedit/vedit.c:157` | `#define VEDIT_COL_KEYWORD` |
| `VEDIT_COL_NUMBER` | macro | `progs/vedit/vedit.c:160` | `#define VEDIT_COL_NUMBER` |
| `VEDIT_COL_PREPROC` | macro | `progs/vedit/vedit.c:161` | `#define VEDIT_COL_PREPROC` |
| `VEDIT_COL_STRING` | macro | `progs/vedit/vedit.c:158` | `#define VEDIT_COL_STRING` |
| `VEDIT_DEFAULT_FILE` | macro | `progs/vedit/vedit.c:119` | `#define VEDIT_DEFAULT_FILE` |
| `VEDIT_DIR_ASM` | macro | `progs/vedit/vedit.c:136` | `#define VEDIT_DIR_ASM` |
| `VEDIT_DIR_BIN` | macro | `progs/vedit/vedit.c:137` | `#define VEDIT_DIR_BIN` |
| `VEDIT_DIR_CVM` | macro | `progs/vedit/vedit.c:138` | `#define VEDIT_DIR_CVM` |
| `VEDIT_ESC_MS` | macro | `progs/vedit/vedit.c:123` | `#define VEDIT_ESC_MS` |
| `VEDIT_FILE_MAX` | macro | `progs/vedit/vedit.c:117` | `#define VEDIT_FILE_MAX` |
| `VEDIT_FILL_COL` | macro | `progs/vedit/vedit.c:1612` | `#define VEDIT_FILL_COL` |
| `VEDIT_FNAME_MAX` | macro | `progs/vedit/vedit.c:118` | `#define VEDIT_FNAME_MAX` |
| `VEDIT_FRAME_MS` | macro | `progs/vedit/vedit.c:124` | `#define VEDIT_FRAME_MS` |
| `VEDIT_HIST_N` | macro | `progs/vedit/vedit.c:255` | `#define VEDIT_HIST_N` |
| `VEDIT_KEY_ARG` | macro | `progs/vedit/vedit.c:259` | `#define VEDIT_KEY_ARG` |
| `VEDIT_KEY_BOL` | macro | `progs/vedit/vedit.c:265` | `#define VEDIT_KEY_BOL` |
| `VEDIT_KEY_DEL` | macro | `progs/vedit/vedit.c:179` | `#define VEDIT_KEY_DEL` |
| `VEDIT_KEY_DOWN` | macro | `progs/vedit/vedit.c:172` | `#define VEDIT_KEY_DOWN` |
| `VEDIT_KEY_DUMP` | macro | `progs/vedit/vedit.c:128` | `#define VEDIT_KEY_DUMP` |
| `VEDIT_KEY_END` | macro | `progs/vedit/vedit.c:176` | `#define VEDIT_KEY_END` |
| `VEDIT_KEY_EOL` | macro | `progs/vedit/vedit.c:266` | `#define VEDIT_KEY_EOL` |
| `VEDIT_KEY_ESC` | macro | `progs/vedit/vedit.c:180` | `#define VEDIT_KEY_ESC` |
| `VEDIT_KEY_FENCE` | macro | `progs/vedit/vedit.c:264` | `#define VEDIT_KEY_FENCE` |
| `VEDIT_KEY_HOME` | macro | `progs/vedit/vedit.c:175` | `#define VEDIT_KEY_HOME` |
| `VEDIT_KEY_KILL_LINE` | macro | `progs/vedit/vedit.c:261` | `#define VEDIT_KEY_KILL_LINE` |
| `VEDIT_KEY_LEFT` | macro | `progs/vedit/vedit.c:173` | `#define VEDIT_KEY_LEFT` |
| `VEDIT_KEY_LINK` | macro | `progs/vedit/vedit.c:127` | `#define VEDIT_KEY_LINK` |
| `VEDIT_KEY_MARK` | macro | `progs/vedit/vedit.c:260` | `#define VEDIT_KEY_MARK` |
| `VEDIT_KEY_META` | macro | `progs/vedit/vedit.c:258` | `#define VEDIT_KEY_META(c)` |
| `VEDIT_KEY_PGDN` | macro | `progs/vedit/vedit.c:178` | `#define VEDIT_KEY_PGDN` |
| `VEDIT_KEY_PGUP` | macro | `progs/vedit/vedit.c:177` | `#define VEDIT_KEY_PGUP` |
| `VEDIT_KEY_RIGHT` | macro | `progs/vedit/vedit.c:174` | `#define VEDIT_KEY_RIGHT` |
| `VEDIT_KEY_RUN` | macro | `progs/vedit/vedit.c:126` | `#define VEDIT_KEY_RUN` |
| `VEDIT_KEY_TRANSPOSE` | macro | `progs/vedit/vedit.c:263` | `#define VEDIT_KEY_TRANSPOSE` |
| `VEDIT_KEY_UP` | macro | `progs/vedit/vedit.c:171` | `#define VEDIT_KEY_UP` |
| `VEDIT_KEY_YANK` | macro | `progs/vedit/vedit.c:262` | `#define VEDIT_KEY_YANK` |
| `VEDIT_KILL_MAX` | macro | `progs/vedit/vedit.c:253` | `#define VEDIT_KILL_MAX` |
| `VEDIT_KILL_N` | macro | `progs/vedit/vedit.c:252` | `#define VEDIT_KILL_N` |
| `VEDIT_LANG_ASM` | macro | `progs/vedit/vedit.c:152` | `#define VEDIT_LANG_ASM` |
| `VEDIT_LANG_C` | macro | `progs/vedit/vedit.c:149` | `#define VEDIT_LANG_C` |
| `VEDIT_LANG_LISP` | macro | `progs/vedit/vedit.c:153` | `#define VEDIT_LANG_LISP` |
| `VEDIT_LANG_LUA` | macro | `progs/vedit/vedit.c:151` | `#define VEDIT_LANG_LUA` |
| `VEDIT_LANG_PY` | macro | `progs/vedit/vedit.c:150` | `#define VEDIT_LANG_PY` |
| `VEDIT_LANG_TEXT` | macro | `progs/vedit/vedit.c:148` | `#define VEDIT_LANG_TEXT` |
| `VEDIT_LINE_MAX` | macro | `progs/vedit/vedit.c:115` | `#define VEDIT_LINE_MAX` |
| `VEDIT_LINE_USED` | macro | `progs/vedit/vedit.c:116` | `#define VEDIT_LINE_USED` |
| `VEDIT_LINK_CVM` | macro | `progs/vedit/vedit.c:141` | `#define VEDIT_LINK_CVM` |
| `VEDIT_LINK_ELF` | macro | `progs/vedit/vedit.c:140` | `#define VEDIT_LINK_ELF` |
| `VEDIT_LOG_TAIL` | macro | `progs/vedit/vedit.c:145` | `#define VEDIT_LOG_TAIL` |
| `VEDIT_MACRO_MAX` | macro | `progs/vedit/vedit.c:254` | `#define VEDIT_MACRO_MAX` |
| `VEDIT_MAGIC_MAX` | macro | `progs/vedit/vedit.c:257` | `#define VEDIT_MAGIC_MAX` |
| `VEDIT_MAX_LINES` | macro | `progs/vedit/vedit.c:114` | `#define VEDIT_MAX_LINES` |
| `VEDIT_MSG_MAX` | macro | `progs/vedit/vedit.c:120` | `#define VEDIT_MSG_MAX` |
| `VEDIT_NBUF` | macro | `progs/vedit/vedit.c:251` | `#define VEDIT_NBUF` |

Next: [SYMBOLS_p25.md](SYMBOLS_p25.md)
