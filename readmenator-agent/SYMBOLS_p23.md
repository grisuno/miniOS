# Symbols (page 23 of 26)
Previous: [SYMBOLS_p22.md](SYMBOLS_p22.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `VEDIT_BASE_MAX` | macro | `progs/vedit/vedit.c:142` | `#define VEDIT_BASE_MAX` |
| `VEDIT_BUILD_LOG` | macro | `progs/vedit/vedit.c:138` | `#define VEDIT_BUILD_LOG` |
| `VEDIT_CLIP_MAX` | macro | `progs/vedit/vedit.c:3262` | `#define VEDIT_CLIP_MAX` |
| `VEDIT_CMD_MAX` | macro | `progs/vedit/vedit.c:255` | `#define VEDIT_CMD_MAX` |
| `VEDIT_COL_COMMENT` | macro | `progs/vedit/vedit.c:158` | `#define VEDIT_COL_COMMENT` |
| `VEDIT_COL_DEFAULT` | macro | `progs/vedit/vedit.c:155` | `#define VEDIT_COL_DEFAULT` |
| `VEDIT_COL_KEYWORD` | macro | `progs/vedit/vedit.c:156` | `#define VEDIT_COL_KEYWORD` |
| `VEDIT_COL_NUMBER` | macro | `progs/vedit/vedit.c:159` | `#define VEDIT_COL_NUMBER` |
| `VEDIT_COL_PREPROC` | macro | `progs/vedit/vedit.c:160` | `#define VEDIT_COL_PREPROC` |
| `VEDIT_COL_STRING` | macro | `progs/vedit/vedit.c:157` | `#define VEDIT_COL_STRING` |
| `VEDIT_DEFAULT_FILE` | macro | `progs/vedit/vedit.c:119` | `#define VEDIT_DEFAULT_FILE` |
| `VEDIT_DIR_ASM` | macro | `progs/vedit/vedit.c:135` | `#define VEDIT_DIR_ASM` |
| `VEDIT_DIR_BIN` | macro | `progs/vedit/vedit.c:136` | `#define VEDIT_DIR_BIN` |
| `VEDIT_DIR_CVM` | macro | `progs/vedit/vedit.c:137` | `#define VEDIT_DIR_CVM` |
| `VEDIT_ESC_MS` | macro | `progs/vedit/vedit.c:123` | `#define VEDIT_ESC_MS` |
| `VEDIT_FILE_MAX` | macro | `progs/vedit/vedit.c:117` | `#define VEDIT_FILE_MAX` |
| `VEDIT_FILL_COL` | macro | `progs/vedit/vedit.c:1611` | `#define VEDIT_FILL_COL` |
| `VEDIT_FNAME_MAX` | macro | `progs/vedit/vedit.c:118` | `#define VEDIT_FNAME_MAX` |
| `VEDIT_FRAME_MS` | macro | `progs/vedit/vedit.c:124` | `#define VEDIT_FRAME_MS` |
| `VEDIT_HIST_N` | macro | `progs/vedit/vedit.c:254` | `#define VEDIT_HIST_N` |
| `VEDIT_KEY_ARG` | macro | `progs/vedit/vedit.c:258` | `#define VEDIT_KEY_ARG` |
| `VEDIT_KEY_BOL` | macro | `progs/vedit/vedit.c:264` | `#define VEDIT_KEY_BOL` |
| `VEDIT_KEY_DEL` | macro | `progs/vedit/vedit.c:178` | `#define VEDIT_KEY_DEL` |
| `VEDIT_KEY_DOWN` | macro | `progs/vedit/vedit.c:171` | `#define VEDIT_KEY_DOWN` |
| `VEDIT_KEY_DUMP` | macro | `progs/vedit/vedit.c:128` | `#define VEDIT_KEY_DUMP` |
| `VEDIT_KEY_END` | macro | `progs/vedit/vedit.c:175` | `#define VEDIT_KEY_END` |
| `VEDIT_KEY_EOL` | macro | `progs/vedit/vedit.c:265` | `#define VEDIT_KEY_EOL` |
| `VEDIT_KEY_ESC` | macro | `progs/vedit/vedit.c:179` | `#define VEDIT_KEY_ESC` |
| `VEDIT_KEY_FENCE` | macro | `progs/vedit/vedit.c:263` | `#define VEDIT_KEY_FENCE` |
| `VEDIT_KEY_HOME` | macro | `progs/vedit/vedit.c:174` | `#define VEDIT_KEY_HOME` |
| `VEDIT_KEY_KILL_LINE` | macro | `progs/vedit/vedit.c:260` | `#define VEDIT_KEY_KILL_LINE` |
| `VEDIT_KEY_LEFT` | macro | `progs/vedit/vedit.c:172` | `#define VEDIT_KEY_LEFT` |
| `VEDIT_KEY_LINK` | macro | `progs/vedit/vedit.c:127` | `#define VEDIT_KEY_LINK` |
| `VEDIT_KEY_MARK` | macro | `progs/vedit/vedit.c:259` | `#define VEDIT_KEY_MARK` |
| `VEDIT_KEY_META` | macro | `progs/vedit/vedit.c:257` | `#define VEDIT_KEY_META(c)` |
| `VEDIT_KEY_PGDN` | macro | `progs/vedit/vedit.c:177` | `#define VEDIT_KEY_PGDN` |
| `VEDIT_KEY_PGUP` | macro | `progs/vedit/vedit.c:176` | `#define VEDIT_KEY_PGUP` |
| `VEDIT_KEY_RIGHT` | macro | `progs/vedit/vedit.c:173` | `#define VEDIT_KEY_RIGHT` |
| `VEDIT_KEY_RUN` | macro | `progs/vedit/vedit.c:126` | `#define VEDIT_KEY_RUN` |
| `VEDIT_KEY_TRANSPOSE` | macro | `progs/vedit/vedit.c:262` | `#define VEDIT_KEY_TRANSPOSE` |
| `VEDIT_KEY_UP` | macro | `progs/vedit/vedit.c:170` | `#define VEDIT_KEY_UP` |
| `VEDIT_KEY_YANK` | macro | `progs/vedit/vedit.c:261` | `#define VEDIT_KEY_YANK` |
| `VEDIT_KILL_MAX` | macro | `progs/vedit/vedit.c:252` | `#define VEDIT_KILL_MAX` |
| `VEDIT_KILL_N` | macro | `progs/vedit/vedit.c:251` | `#define VEDIT_KILL_N` |
| `VEDIT_LANG_ASM` | macro | `progs/vedit/vedit.c:151` | `#define VEDIT_LANG_ASM` |
| `VEDIT_LANG_C` | macro | `progs/vedit/vedit.c:148` | `#define VEDIT_LANG_C` |
| `VEDIT_LANG_LISP` | macro | `progs/vedit/vedit.c:152` | `#define VEDIT_LANG_LISP` |
| `VEDIT_LANG_LUA` | macro | `progs/vedit/vedit.c:150` | `#define VEDIT_LANG_LUA` |
| `VEDIT_LANG_PY` | macro | `progs/vedit/vedit.c:149` | `#define VEDIT_LANG_PY` |
| `VEDIT_LANG_TEXT` | macro | `progs/vedit/vedit.c:147` | `#define VEDIT_LANG_TEXT` |
| `VEDIT_LINE_MAX` | macro | `progs/vedit/vedit.c:115` | `#define VEDIT_LINE_MAX` |
| `VEDIT_LINE_USED` | macro | `progs/vedit/vedit.c:116` | `#define VEDIT_LINE_USED` |
| `VEDIT_LINK_CVM` | macro | `progs/vedit/vedit.c:140` | `#define VEDIT_LINK_CVM` |
| `VEDIT_LINK_ELF` | macro | `progs/vedit/vedit.c:139` | `#define VEDIT_LINK_ELF` |
| `VEDIT_LOG_TAIL` | macro | `progs/vedit/vedit.c:144` | `#define VEDIT_LOG_TAIL` |
| `VEDIT_MACRO_MAX` | macro | `progs/vedit/vedit.c:253` | `#define VEDIT_MACRO_MAX` |
| `VEDIT_MAGIC_MAX` | macro | `progs/vedit/vedit.c:256` | `#define VEDIT_MAGIC_MAX` |
| `VEDIT_MAX_LINES` | macro | `progs/vedit/vedit.c:114` | `#define VEDIT_MAX_LINES` |
| `VEDIT_MSG_MAX` | macro | `progs/vedit/vedit.c:120` | `#define VEDIT_MSG_MAX` |
| `VEDIT_NBUF` | macro | `progs/vedit/vedit.c:250` | `#define VEDIT_NBUF` |
| `VEDIT_PATH_MAX` | macro | `progs/vedit/vedit.c:143` | `#define VEDIT_PATH_MAX` |
| `VEDIT_PROMPT_BINDCMD` | macro | `progs/vedit/vedit.c:327` | `#define VEDIT_PROMPT_BINDCMD` |
| `VEDIT_PROMPT_BINDKEY` | macro | `progs/vedit/vedit.c:326` | `#define VEDIT_PROMPT_BINDKEY` |
| `VEDIT_PROMPT_CMD` | macro | `progs/vedit/vedit.c:316` | `#define VEDIT_PROMPT_CMD` |
| `VEDIT_PROMPT_FILTER` | macro | `progs/vedit/vedit.c:323` | `#define VEDIT_PROMPT_FILTER` |
| `VEDIT_PROMPT_FIND` | macro | `progs/vedit/vedit.c:312` | `#define VEDIT_PROMPT_FIND` |
| `VEDIT_PROMPT_GOTO` | macro | `progs/vedit/vedit.c:313` | `#define VEDIT_PROMPT_GOTO` |
| `VEDIT_PROMPT_GREP` | macro | `progs/vedit/vedit.c:325` | `#define VEDIT_PROMPT_GREP` |
| `VEDIT_PROMPT_ISEARCH_F` | macro | `progs/vedit/vedit.c:317` | `#define VEDIT_PROMPT_ISEARCH_F` |
| `VEDIT_PROMPT_ISEARCH_R` | macro | `progs/vedit/vedit.c:318` | `#define VEDIT_PROMPT_ISEARCH_R` |
| `VEDIT_PROMPT_LINK` | macro | `progs/vedit/vedit.c:315` | `#define VEDIT_PROMPT_LINK` |
| `VEDIT_PROMPT_NAME` | macro | `progs/vedit/vedit.c:314` | `#define VEDIT_PROMPT_NAME` |
| `VEDIT_PROMPT_QREP` | macro | `progs/vedit/vedit.c:321` | `#define VEDIT_PROMPT_QREP` |
| `VEDIT_PROMPT_REP_NEW` | macro | `progs/vedit/vedit.c:320` | `#define VEDIT_PROMPT_REP_NEW` |
| `VEDIT_PROMPT_REP_OLD` | macro | `progs/vedit/vedit.c:319` | `#define VEDIT_PROMPT_REP_OLD` |
| `VEDIT_PROMPT_SELECT` | macro | `progs/vedit/vedit.c:324` | `#define VEDIT_PROMPT_SELECT` |
| `VEDIT_PROMPT_SHELLCMD` | macro | `progs/vedit/vedit.c:322` | `#define VEDIT_PROMPT_SHELLCMD` |
| `VEDIT_SH_ARGS` | macro | `progs/vedit/vedit.c:3260` | `#define VEDIT_SH_ARGS` |
| `VEDIT_SH_LINE` | macro | `progs/vedit/vedit.c:3261` | `#define VEDIT_SH_LINE` |
| `VEDIT_STATUS_MAX` | macro | `progs/vedit/vedit.c:141` | `#define VEDIT_STATUS_MAX` |
| `VEDIT_ST_BLOCK` | macro | `progs/vedit/vedit.c:163` | `#define VEDIT_ST_BLOCK` |
| `VEDIT_ST_LUABLK` | macro | `progs/vedit/vedit.c:166` | `#define VEDIT_ST_LUABLK` |
| `VEDIT_ST_LUASTR` | macro | `progs/vedit/vedit.c:167` | `#define VEDIT_ST_LUASTR` |
| `VEDIT_ST_PY3D` | macro | `progs/vedit/vedit.c:165` | `#define VEDIT_ST_PY3D` |
| `VEDIT_ST_PY3S` | macro | `progs/vedit/vedit.c:164` | `#define VEDIT_ST_PY3S` |
| `VEDIT_TAB_W` | macro | `progs/vedit/vedit.c:122` | `#define VEDIT_TAB_W` |
| `VEDIT_TMP_F` | macro | `progs/vedit/vedit.c:3259` | `#define VEDIT_TMP_F` |
| `VEDIT_TMP_IN` | macro | `progs/vedit/vedit.c:3258` | `#define VEDIT_TMP_IN` |
| `VEDIT_TMP_OUT` | macro | `progs/vedit/vedit.c:3257` | `#define VEDIT_TMP_OUT` |
| `VEDIT_TOOL_CVM` | macro | `progs/vedit/vedit.c:131` | `#define VEDIT_TOOL_CVM` |
| `VEDIT_TOOL_LD` | macro | `progs/vedit/vedit.c:130` | `#define VEDIT_TOOL_LD` |
| `VEDIT_TOOL_LISP` | macro | `progs/vedit/vedit.c:134` | `#define VEDIT_TOOL_LISP` |
| `VEDIT_TOOL_LUA` | macro | `progs/vedit/vedit.c:132` | `#define VEDIT_TOOL_LUA` |
| `VEDIT_TOOL_MINIGCC` | macro | `progs/vedit/vedit.c:129` | `#define VEDIT_TOOL_MINIGCC` |
| `VEDIT_TOOL_PY` | macro | `progs/vedit/vedit.c:133` | `#define VEDIT_TOOL_PY` |
| `VEDIT_UI_MEMORY` | macro | `progs/vedit/vedit.c:125` | `#define VEDIT_UI_MEMORY` |
| `VEDIT_WORD_MAX` | macro | `progs/vedit/vedit.c:121` | `#define VEDIT_WORD_MAX` |
| `definitions` | function | `progs/vedit/vedit.c:267` | `* definitions (C99, one file, no headers). */ static void vedit_str_case(char *s, int mode);` |
| `main` | function | `progs/vedit/vedit.c:4823` | `int main(int argc, char **argv)` |
| `separators` | function | `progs/vedit/vedit.c:402` | `* allow_quote exists because C digit separators (1'000'000) are not  * valid in Python/Lua number...` |
| `strcmp` | function | `progs/vedit/vedit.c:3180` | `strcmp(name, "describe-bindings") == 0)` |
| `vedit_ansi_for` | function | `progs/vedit/vedit.c:3730` | `static void vedit_ansi_for(int col)` |
| `vedit_backspace` | function | `progs/vedit/vedit.c:846` | `static void vedit_backspace(void)` |
| `vedit_base_of` | function | `progs/vedit/vedit.c:2268` | `static int vedit_base_of(const char *fname, char *dst, size_t cap)` |
| `vedit_buf_alloc` | function | `progs/vedit/vedit.c:1178` | `static int vedit_buf_alloc(int idx)` |
| `vedit_c_bg` | function | `progs/vedit/vedit.c:182` | `static struct nk_color vedit_c_bg(void)` |
| `vedit_c_comment` | function | `progs/vedit/vedit.c:187` | `static struct nk_color vedit_c_comment(void)` |
| `vedit_c_cursor` | function | `progs/vedit/vedit.c:193` | `static struct nk_color vedit_c_cursor(void)` |
| `vedit_c_default` | function | `progs/vedit/vedit.c:184` | `static struct nk_color vedit_c_default(void)` |
| `vedit_c_gutter` | function | `progs/vedit/vedit.c:183` | `static struct nk_color vedit_c_gutter(void)` |
| `vedit_c_header` | function | `progs/vedit/vedit.c:190` | `static struct nk_color vedit_c_header(void)` |
| `vedit_c_headtxt` | function | `progs/vedit/vedit.c:191` | `static struct nk_color vedit_c_headtxt(void)` |
| `vedit_c_keyword` | function | `progs/vedit/vedit.c:185` | `static struct nk_color vedit_c_keyword(void)` |
| `vedit_c_number` | function | `progs/vedit/vedit.c:188` | `static struct nk_color vedit_c_number(void)` |
| `vedit_c_preproc` | function | `progs/vedit/vedit.c:189` | `static struct nk_color vedit_c_preproc(void)` |
| `vedit_c_status` | function | `progs/vedit/vedit.c:192` | `static struct nk_color vedit_c_status(void)` |
| `vedit_c_string` | function | `progs/vedit/vedit.c:186` | `static struct nk_color vedit_c_string(void)` |
| `vedit_case_word` | function | `progs/vedit/vedit.c:1450` | `static int vedit_case_word(int mode)` |
| `vedit_clamp` | function | `progs/vedit/vedit.c:772` | `static void vedit_clamp(void)` |
| `vedit_clip_get` | function | `progs/vedit/vedit.c:105` | `static long vedit_clip_get(char *out, long cap)` |
| `vedit_clip_paste` | function | `progs/vedit/vedit.c:3337` | `static int vedit_clip_paste(void)` |
| `vedit_clip_set` | function | `progs/vedit/vedit.c:97` | `static long vedit_clip_set(const char *s, long len)` |
| `vedit_cmd_bind` | function | `progs/vedit/vedit.c:2925` | `static int vedit_cmd_bind(int key, int cmd)` |
| `vedit_cmd_bound` | function | `progs/vedit/vedit.c:2941` | `static int vedit_cmd_bound(int key)` |
| `vedit_cmd_exec` | function | `progs/vedit/vedit.c:2365` | `static void vedit_cmd_exec(const char *out, int kind)` |
| `vedit_cmd_exec_id` | function | `progs/vedit/vedit.c:2992` | `static void vedit_cmd_exec_id(int id, const char *arg, int *quit,                               i...` |
| `vedit_cmd_link` | function | `progs/vedit/vedit.c:2465` | `static void vedit_cmd_link(const char *fmt)` |
| `vedit_cmd_lookup` | function | `progs/vedit/vedit.c:2857` | `static int vedit_cmd_lookup(const char *name)` |
| `vedit_cmd_run` | function | `progs/vedit/vedit.c:2388` | `static void vedit_cmd_run(void)` |
| `vedit_console_dump` | function | `progs/vedit/vedit.c:3738` | `static void vedit_console_dump(void)` |
| `vedit_copy_region` | function | `progs/vedit/vedit.c:1268` | `static int vedit_copy_region(void)` |
| `vedit_count` | macro | `progs/vedit/vedit.c:294` | `#define vedit_count` |
| `vedit_count_open` | function | `progs/vedit/vedit.c:2797` | `static int vedit_count_open(void)` |
| `vedit_count_words` | function | `progs/vedit/vedit.c:1578` | `static void vedit_count_words(void)` |
| `vedit_cx` | macro | `progs/vedit/vedit.c:295` | `#define vedit_cx` |
| `vedit_cy` | macro | `progs/vedit/vedit.c:296` | `#define vedit_cy` |
| `vedit_delete_char` | function | `progs/vedit/vedit.c:882` | `static void vedit_delete_char(void)` |
| `vedit_delete_line_at` | function | `progs/vedit/vedit.c:835` | `static void vedit_delete_line_at(int idx)` |
| `vedit_dirty` | macro | `progs/vedit/vedit.c:299` | `#define vedit_dirty` |
| `vedit_draw_row` | function | `progs/vedit/vedit.c:3854` | `static void vedit_draw_row(struct nk_command_buffer *canvas,                            struct nk...` |
| `vedit_draw_ui` | function | `progs/vedit/vedit.c:3952` | `static void vedit_draw_ui(struct nk_context *ctx, struct nk_user_font *font,                     ...` |
| `vedit_fill_paragraph` | function | `progs/vedit/vedit.c:1813` | `static int vedit_fill_paragraph(void)` |
| `vedit_filter_buffer` | function | `progs/vedit/vedit.c:3505` | `static void vedit_filter_buffer(const char *prog)` |
| `vedit_find` | function | `progs/vedit/vedit.c:1897` | `static void vedit_find(const char *needle)` |
| `vedit_first_open` | function | `progs/vedit/vedit.c:2777` | `static int vedit_first_open(void)` |
| `vedit_fname` | macro | `progs/vedit/vedit.c:302` | `#define vedit_fname` |
| `vedit_follow` | function | `progs/vedit/vedit.c:784` | `static void vedit_follow(void)` |
| `vedit_getc_raw` | function | `progs/vedit/vedit.c:38` | `static long vedit_getc_raw(long blocking)` |
| `vedit_goto_fence` | function | `progs/vedit/vedit.c:1512` | `static int vedit_goto_fence(void)` |
| `vedit_grep` | function | `progs/vedit/vedit.c:3565` | `static void vedit_grep(const char *pat)` |
| `vedit_gui_run` | function | `progs/vedit/vedit.c:4656` | `static void vedit_gui_run(void)` |
| `vedit_has_ext` | function | `progs/vedit/vedit.c:2256` | `static int vedit_has_ext(const char *fname, const char *ext)` |
| `vedit_help_text` | function | `progs/vedit/vedit.c:2976` | `static void vedit_help_text(void)` |
| `vedit_hist_push` | function | `progs/vedit/vedit.c:1220` | `static void vedit_hist_push(const char *fname)` |
| `vedit_hist_show` | function | `progs/vedit/vedit.c:2968` | `static void vedit_hist_show(void)` |
| `vedit_hoff` | macro | `progs/vedit/vedit.c:298` | `#define vedit_hoff` |
| `vedit_ink` | function | `progs/vedit/vedit.c:195` | `static struct nk_color vedit_ink(int col)` |
| `vedit_insert_buf` | function | `progs/vedit/vedit.c:2182` | `static char *vedit_insert_buf(long size)` |
| `vedit_insert_char` | function | `progs/vedit/vedit.c:797` | `static void vedit_insert_char(int c)` |
| `vedit_insert_file` | function | `progs/vedit/vedit.c:2195` | `static int vedit_insert_file(const char *fname)` |
| `vedit_is_alpha` | function | `progs/vedit/vedit.c:367` | `static int vedit_is_alpha(int c)` |
| `vedit_is_digit` | function | `progs/vedit/vedit.c:371` | `static int vedit_is_digit(int c)` |
| `vedit_is_kw` | function | `progs/vedit/vedit.c:379` | `static int vedit_is_kw(const char *table, const char *word, int wlen)` |
| `vedit_is_wordc` | function | `progs/vedit/vedit.c:375` | `static int vedit_is_wordc(int c)` |
| `vedit_isearch_step` | function | `progs/vedit/vedit.c:1713` | `static void vedit_isearch_step(void)` |
| `vedit_join` | function | `progs/vedit/vedit.c:2289` | `static int vedit_join(const char *dir, const char *base, const char *ext,                       c...` |
| `vedit_kbd_raw` | function | `progs/vedit/vedit.c:80` | `static long vedit_kbd_raw(int on)` |
| `vedit_key` | function | `progs/vedit/vedit.c:4406` | `static void vedit_key(int key, int *quit, int *save_and_quit)` |
| `vedit_kill_line` | function | `progs/vedit/vedit.c:1344` | `static int vedit_kill_line(void)` |
| `vedit_kill_region` | function | `progs/vedit/vedit.c:1298` | `static int vedit_kill_region(void)` |
| `vedit_lang` | macro | `progs/vedit/vedit.c:301` | `#define vedit_lang` |
| `vedit_lang_name` | function | `progs/vedit/vedit.c:478` | `static const char *vedit_lang_name(int lang)` |
| `vedit_lang_of` | function | `progs/vedit/vedit.c:457` | `static int vedit_lang_of(const char *fname)` |
| `vedit_link_fmt` | function | `progs/vedit/vedit.c:2306` | `static int vedit_link_fmt(const char *s)` |
| `vedit_list_buffers` | function | `progs/vedit/vedit.c:2949` | `static void vedit_list_buffers(void)` |
| `vedit_load` | function | `progs/vedit/vedit.c:2050` | `static int vedit_load(void)` |
| `vedit_magic_atom` | function | `progs/vedit/vedit.c:1065` | `static int vedit_magic_atom(const char *pat, int c, int *atom_len)` |
| `vedit_magic_class` | function | `progs/vedit/vedit.c:1043` | `static int vedit_magic_class(int c, const char *cls)` |
| `vedit_magic_here` | function | `progs/vedit/vedit.c:1088` | `static int vedit_magic_here(const char *text, const char *pat, int *mlen)` |
| `vedit_magic_match` | function | `progs/vedit/vedit.c:1149` | `static int vedit_magic_match(const char *text, const char *pat, int *mlen)` |
| `vedit_match_at` | function | `progs/vedit/vedit.c:1621` | `static int vedit_match_at(int row, int col, const char *needle, int magic,                       ...` |
| `vedit_msg` | macro | `progs/vedit/vedit.c:303` | `#define vedit_msg` |
| `vedit_next_buffer` | function | `progs/vedit/vedit.c:1206` | `static int vedit_next_buffer(void)` |
| `vedit_next_error` | function | `progs/vedit/vedit.c:3628` | `static void vedit_next_error(void)` |
| `vedit_next_pane` | function | `progs/vedit/vedit.c:2825` | `static void vedit_next_pane(void)` |
| `vedit_open_in_buffer` | function | `progs/vedit/vedit.c:2121` | `static int vedit_open_in_buffer(const char *fname, int ro)` |
| `vedit_pane_load` | function | `progs/vedit/vedit.c:2785` | `static void vedit_pane_load(int p)` |
| `vedit_pane_save` | function | `progs/vedit/vedit.c:2769` | `static void vedit_pane_save(int p)` |
| `vedit_parse_key` | function | `progs/vedit/vedit.c:2873` | `static int vedit_parse_key(const char *s)` |
| `vedit_parse_keyword` | function | `progs/vedit/vedit.c:440` | `static int vedit_parse_keyword(const char *t, int len, int i,                                cons...` |
| `vedit_parse_number` | function | `progs/vedit/vedit.c:425` | `static int vedit_parse_number(const char *t, int len, int i, int allow_quote)` |
| `vedit_pool` | macro | `progs/vedit/vedit.c:292` | `#define vedit_pool` |
| `vedit_print_log` | function | `progs/vedit/vedit.c:2319` | `static void vedit_print_log(const char *path)` |
| `vedit_prompt_find` | function | `progs/vedit/vedit.c:3779` | `static void vedit_prompt_find(void)` |
| `vedit_prompt_isearch` | function | `progs/vedit/vedit.c:3783` | `static void vedit_prompt_isearch(int dir)` |
| `vedit_prompt_key` | function | `progs/vedit/vedit.c:4232` | `static void vedit_prompt_key(int key)` |
| `vedit_prompt_open` | function | `progs/vedit/vedit.c:3768` | `static void vedit_prompt_open(const char *label, int mode)` |
| `vedit_prompt_saveas` | function | `progs/vedit/vedit.c:3844` | `static void vedit_prompt_saveas(void)` |
| `vedit_qrep_answer` | function | `progs/vedit/vedit.c:3805` | `static void vedit_qrep_answer(int key)` |
| `vedit_qrep_next` | function | `progs/vedit/vedit.c:3793` | `static void vedit_qrep_next(int r, int c)` |
| `vedit_read_key_poll` | function | `progs/vedit/vedit.c:3676` | `static int vedit_read_key_poll(void)` |
| `vedit_region` | function | `progs/vedit/vedit.c:1247` | `static int vedit_region(int *y0, int *x0, int *y1, int *x1)` |
| `vedit_region_to_clip` | function | `progs/vedit/vedit.c:3367` | `static int vedit_region_to_clip(void)` |
| `vedit_replace_all` | function | `progs/vedit/vedit.c:1760` | `static int vedit_replace_all(const char *old_s, const char *new_s,                              i...` |
| `vedit_replace_at` | function | `progs/vedit/vedit.c:1740` | `static int vedit_replace_at(int row, int col, const char *old_s,                             cons...` |
| `vedit_row_ptr` | function | `progs/vedit/vedit.c:768` | `static char *vedit_row_ptr(int idx)` |
| `vedit_run_kind` | function | `progs/vedit/vedit.c:2378` | `static int vedit_run_kind(const char *fname)` |
| `vedit_run_rc` | function | `progs/vedit/vedit.c:3198` | `static void vedit_run_rc(const char *path)` |
| `vedit_save` | function | `progs/vedit/vedit.c:1987` | `static int vedit_save(void)` |
| `vedit_scan_line` | function | `progs/vedit/vedit.c:488` | `static int vedit_scan_line(const char *t, int len, int st)` |
| `vedit_search_fwd` | function | `progs/vedit/vedit.c:1658` | `static int vedit_search_fwd(int row, int col, const char *needle, int magic,                     ...` |
| `vedit_search_rev` | function | `progs/vedit/vedit.c:1690` | `static int vedit_search_rev(int row, int col, const char *needle, int magic)` |
| `vedit_sel_clear` | function | `progs/vedit/vedit.c:3276` | `static void vedit_sel_clear(void)` |
| `vedit_sel_copy` | function | `progs/vedit/vedit.c:3294` | `static int vedit_sel_copy(void)` |
| `vedit_sel_norm` | function | `progs/vedit/vedit.c:3281` | `static void vedit_sel_norm(void)` |
| `vedit_selftest` | function | `progs/vedit/vedit.c:4747` | `static int vedit_selftest(void)` |
| `vedit_selftest_build` | function | `progs/vedit/vedit.c:2516` | `static int vedit_selftest_build(void)` |
| `vedit_selftest_leak` | function | `progs/vedit/vedit.c:2709` | `static int vedit_selftest_leak(void)` |
| `vedit_set_mark` | function | `progs/vedit/vedit.c:1239` | `static void vedit_set_mark(void)` |
| `vedit_set_msg` | function | `progs/vedit/vedit.c:360` | `static void vedit_set_msg(const char *s)` |
| `vedit_set_title` | function | `progs/vedit/vedit.c:47` | `static long vedit_set_title(const char *t)` |
| `vedit_sh_split` | function | `progs/vedit/vedit.c:3412` | `static int vedit_sh_split(const char *line, char *buf, const char **argv)` |
| `vedit_shell_command` | function | `progs/vedit/vedit.c:3432` | `static void vedit_shell_command(const char *line)` |
| `vedit_spawn` | function | `progs/vedit/vedit.c:56` | `static long vedit_spawn(const char *path, const char *redir, int argc,                         co...` |
| `vedit_spawn_visible` | function | `progs/vedit/vedit.c:2336` | `static long vedit_spawn_visible(const char *tool, const char *redir, int argc,                   ...` |
| `vedit_split` | function | `progs/vedit/vedit.c:915` | `static void vedit_split(void)` |
| `vedit_split_set` | function | `progs/vedit/vedit.c:2806` | `static void vedit_split_set(int on)` |
| `vedit_state_at` | function | `progs/vedit/vedit.c:759` | `static int vedit_state_at(int row)` |
| `vedit_str_case` | function | `progs/vedit/vedit.c:1004` | `static void vedit_str_case(char *s, int mode)` |
| `vedit_str_transpose` | function | `progs/vedit/vedit.c:1031` | `static void vedit_str_transpose(char *s, int len, int pos)` |
| `vedit_sync_title` | function | `progs/vedit/vedit.c:4646` | `static void vedit_sync_title(void)` |
| `vedit_tab` | function | `progs/vedit/vedit.c:968` | `static void vedit_tab(void)` |
| `vedit_time_ms` | function | `progs/vedit/vedit.c:89` | `static unsigned long vedit_time_ms(void)` |
| `vedit_top` | macro | `progs/vedit/vedit.c:297` | `#define vedit_top` |
| `vedit_transpose` | function | `progs/vedit/vedit.c:1489` | `static int vedit_transpose(void)` |
| `vedit_trunc` | macro | `progs/vedit/vedit.c:300` | `#define vedit_trunc` |
| `vedit_used` | macro | `progs/vedit/vedit.c:293` | `#define vedit_used` |
| `vedit_vga` | function | `progs/vedit/vedit.c:68` | `static long vedit_vga(int on)` |
| `vedit_word_move` | function | `progs/vedit/vedit.c:1415` | `static int vedit_word_move(int dir)` |
| `vedit_write_region` | function | `progs/vedit/vedit.c:3461` | `static int vedit_write_region(const char *path, int *y0o, int *x0o, int *y1o,                    ...` |
| `vedit_yank` | function | `progs/vedit/vedit.c:1382` | `static int vedit_yank(void)` |
| `WL_CLIENT_H` | macro | `progs/wl/wl_client.h:14` | `#define WL_CLIENT_H` |
| `WL_CLIENT_MSGS` | macro | `progs/wl/wl_client.h:18` | `#define WL_CLIENT_MSGS` |
| `wl_client_attach` | function | `progs/wl/wl_client.h:75` | `static inline int wl_client_attach(const char *box, unsigned int seq0,         const unsigned cha...` |
| `wl_client_emit_file` | function | `progs/wl/wl_client.h:21` | `static inline int wl_client_emit_file(const char *box, unsigned int seq,         const unsigned c...` |
| `wl_client_raw_file` | function | `progs/wl/wl_client.h:48` | `static inline int wl_client_raw_file(const char *box,         const unsigned char *px, int w, int h)` |
| `WL_MBOX_BOX_MAX` | macro | `progs/wl/wl_mbox.h:23` | `#define WL_MBOX_BOX_MAX` |
| `WL_MBOX_DIR` | macro | `progs/wl/wl_mbox.h:19` | `#define WL_MBOX_DIR` |
| `WL_MBOX_EV_SUFFIX` | macro | `progs/wl/wl_mbox.h:22` | `#define WL_MBOX_EV_SUFFIX` |
| `WL_MBOX_FRAME_HEAD` | macro | `progs/wl/wl_mbox.h:26` | `#define WL_MBOX_FRAME_HEAD` |
| `WL_MBOX_H` | macro | `progs/wl/wl_mbox.h:15` | `#define WL_MBOX_H` |
| `WL_MBOX_MAGIC` | macro | `progs/wl/wl_mbox.h:25` | `#define WL_MBOX_MAGIC` |
| `WL_MBOX_NAME_MAX` | macro | `progs/wl/wl_mbox.h:24` | `#define WL_MBOX_NAME_MAX` |
| `WL_MBOX_POLL_MAX` | macro | `progs/wl/wl_mbox.h:27` | `#define WL_MBOX_POLL_MAX` |
| `WL_MBOX_RAW_SUFFIX` | macro | `progs/wl/wl_mbox.h:21` | `#define WL_MBOX_RAW_SUFFIX` |
| `WL_MBOX_SEQ_HEX` | macro | `progs/wl/wl_mbox.h:28` | `#define WL_MBOX_SEQ_HEX` |
| `WL_MBOX_SUFFIX` | macro | `progs/wl/wl_mbox.h:20` | `#define WL_MBOX_SUFFIX` |
| `wl_client_box` | function | `progs/wl/wl_mbox.h:257` | `static inline int wl_client_box(const char *prog, long pid, char *dst,         int cap)` |
| `wl_mbox_assign` | function | `progs/wl/wl_mbox.h:358` | `static inline int wl_mbox_assign(wl_mbox_box_t *boxes, const char *box)` |
| `wl_mbox_box_ok` | function | `progs/wl/wl_mbox.h:51` | `static inline int wl_mbox_box_ok(const char *box)` |
| `wl_mbox_box_t` | struct | `progs/wl/wl_mbox.h:30` | `` |
| `wl_mbox_ev_name` | function | `progs/wl/wl_mbox.h:225` | `static inline int wl_mbox_ev_name(char *dst, int cap, const char *box)` |
| `wl_mbox_frame_decode` | function | `progs/wl/wl_mbox.h:332` | `static inline int wl_mbox_frame_decode(const unsigned char *src, int len,         unsigned int *s...` |
| `wl_mbox_frame_encode` | function | `progs/wl/wl_mbox.h:310` | `static inline int wl_mbox_frame_encode(unsigned char *dst, int cap,         unsigned int seq, con...` |
| `wl_mbox_fresh` | function | `progs/wl/wl_mbox.h:394` | `static inline int wl_mbox_fresh(const wl_mbox_box_t *boxes, int slot,         unsigned int seq)` |
| `wl_mbox_hex` | function | `progs/wl/wl_mbox.h:74` | `static inline int wl_mbox_hex(unsigned int v, char *dst)` |
| `wl_mbox_init` | function | `progs/wl/wl_mbox.h:36` | `static inline void wl_mbox_init(wl_mbox_box_t *boxes)` |
| `wl_mbox_name` | function | `progs/wl/wl_mbox.h:103` | `static inline int wl_mbox_name(char *dst, int cap, const char *box,         unsigned int seq)` |
| `wl_mbox_parse` | function | `progs/wl/wl_mbox.h:147` | `static inline int wl_mbox_parse(const char *path, char *box, int boxcap,         unsigned int *seq)` |
| `wl_mbox_raw_name` | function | `progs/wl/wl_mbox.h:194` | `static inline int wl_mbox_raw_name(char *dst, int cap, const char *box)` |
| `wl_mbox_route` | function | `progs/wl/wl_mbox.h:409` | `static inline int wl_mbox_route(wl_comp_t *c, wl_mbox_box_t *boxes,         const char *box, unsi...` |
| `wl_mbox_unhex` | function | `progs/wl/wl_mbox.h:87` | `static inline int wl_mbox_unhex(char ch, unsigned int *v)` |
| `WLCOMP_BG` | macro | `progs/wl/wl_mini.h:509` | `#define WLCOMP_BG` |
| `WLCOMP_BORDER` | macro | `progs/wl/wl_mini.h:510` | `#define WLCOMP_BORDER` |
| `WL_ATTACH_SZ` | macro | `progs/wl/wl_mini.h:28` | `#define WL_ATTACH_SZ` |
| `WL_CFG_DEFAULT` | macro | `progs/wl/wl_mini.h:69` | `#define WL_CFG_DEFAULT` |
| `WL_CLIP_MAX` | macro | `progs/wl/wl_mini.h:905` | `#define WL_CLIP_MAX` |
| `WL_CLOSE_INK` | macro | `progs/wl/wl_mini.h:243` | `#define WL_CLOSE_INK` |
| `WL_CLOSE_W` | macro | `progs/wl/wl_mini.h:239` | `#define WL_CLOSE_W` |
| `WL_COMMIT_SZ` | macro | `progs/wl/wl_mini.h:29` | `#define WL_COMMIT_SZ` |
| `WL_ERR_BOUND` | macro | `progs/wl/wl_mini.h:32` | `#define WL_ERR_BOUND` |
| `WL_ERR_ID` | macro | `progs/wl/wl_mini.h:35` | `#define WL_ERR_ID` |
| `WL_ERR_MORE` | macro | `progs/wl/wl_mini.h:37` | `#define WL_ERR_MORE` |
| `WL_ERR_OK` | macro | `progs/wl/wl_mini.h:31` | `#define WL_ERR_OK` |
| `WL_ERR_SIZE` | macro | `progs/wl/wl_mini.h:34` | `#define WL_ERR_SIZE` |
| `WL_ERR_STR` | macro | `progs/wl/wl_mini.h:36` | `#define WL_ERR_STR` |
| `WL_ERR_TRUNC` | macro | `progs/wl/wl_mini.h:33` | `#define WL_ERR_TRUNC` |
| `WL_EV_MAGIC` | macro | `progs/wl/wl_mini.h:964` | `#define WL_EV_MAGIC` |
| `WL_EV_SC_MAX` | macro | `progs/wl/wl_mini.h:965` | `#define WL_EV_SC_MAX` |
| `WL_EV_SZ` | macro | `progs/wl/wl_mini.h:966` | `#define WL_EV_SZ` |
| `WL_HDR_SZ` | macro | `progs/wl/wl_mini.h:27` | `#define WL_HDR_SZ` |
| `WL_HIT_BODY` | macro | `progs/wl/wl_mini.h:246` | `#define WL_HIT_BODY` |
| `WL_HIT_CLOSE` | macro | `progs/wl/wl_mini.h:248` | `#define WL_HIT_CLOSE` |
| `WL_HIT_NONE` | macro | `progs/wl/wl_mini.h:245` | `#define WL_HIT_NONE` |
| `WL_HIT_RESIZE` | macro | `progs/wl/wl_mini.h:249` | `#define WL_HIT_RESIZE` |
| `WL_HIT_TITLE` | macro | `progs/wl/wl_mini.h:247` | `#define WL_HIT_TITLE` |
| `WL_ID_BUFFER_BASE` | macro | `progs/wl/wl_mini.h:46` | `#define WL_ID_BUFFER_BASE` |
| `WL_ID_CLIPBOARD` | macro | `progs/wl/wl_mini.h:902` | `#define WL_ID_CLIPBOARD` |
| `WL_ID_COMPOSITOR` | macro | `progs/wl/wl_mini.h:41` | `#define WL_ID_COMPOSITOR` |
| `WL_ID_DISPLAY` | macro | `progs/wl/wl_mini.h:39` | `#define WL_ID_DISPLAY` |
| `WL_ID_POOL_BASE` | macro | `progs/wl/wl_mini.h:45` | `#define WL_ID_POOL_BASE` |
| `WL_ID_REGISTRY` | macro | `progs/wl/wl_mini.h:40` | `#define WL_ID_REGISTRY` |
| `WL_ID_SHM` | macro | `progs/wl/wl_mini.h:42` | `#define WL_ID_SHM` |
| `WL_ID_SURFACE_BASE` | macro | `progs/wl/wl_mini.h:44` | `#define WL_ID_SURFACE_BASE` |
| `WL_ID_XDG_BASE` | macro | `progs/wl/wl_mini.h:43` | `#define WL_ID_XDG_BASE` |
| `WL_IFACE_COUNT` | macro | `progs/wl/wl_mini.h:1185` | `#define WL_IFACE_COUNT` |
| `WL_MAX_MSG` | macro | `progs/wl/wl_mini.h:20` | `#define WL_MAX_MSG` |
| `WL_MAX_POOLS` | macro | `progs/wl/wl_mini.h:23` | `#define WL_MAX_POOLS` |
| `WL_MAX_STR` | macro | `progs/wl/wl_mini.h:21` | `#define WL_MAX_STR` |
| `WL_MAX_SURFACES` | macro | `progs/wl/wl_mini.h:22` | `#define WL_MAX_SURFACES` |
| `WL_MINI_H` | macro | `progs/wl/wl_mini.h:18` | `#define WL_MINI_H` |
| `WL_OP_CLIPBOARD_GET` | macro | `progs/wl/wl_mini.h:904` | `#define WL_OP_CLIPBOARD_GET` |
| `WL_OP_CLIPBOARD_SET` | macro | `progs/wl/wl_mini.h:903` | `#define WL_OP_CLIPBOARD_SET` |
| `WL_OP_COMPOSITOR_CREATE_SURFACE` | macro | `progs/wl/wl_mini.h:50` | `#define WL_OP_COMPOSITOR_CREATE_SURFACE` |
| `WL_OP_DISPLAY_GET_REGISTRY` | macro | `progs/wl/wl_mini.h:48` | `#define WL_OP_DISPLAY_GET_REGISTRY` |
| `WL_OP_POOL_CREATE_BUFFER` | macro | `progs/wl/wl_mini.h:52` | `#define WL_OP_POOL_CREATE_BUFFER` |
| `WL_OP_REGISTRY_BIND` | macro | `progs/wl/wl_mini.h:49` | `#define WL_OP_REGISTRY_BIND` |
| `WL_OP_SHM_CREATE_POOL` | macro | `progs/wl/wl_mini.h:51` | `#define WL_OP_SHM_CREATE_POOL` |
| `WL_OP_SURFACE_ATTACH` | macro | `progs/wl/wl_mini.h:53` | `#define WL_OP_SURFACE_ATTACH` |
| `WL_OP_SURFACE_COMMIT` | macro | `progs/wl/wl_mini.h:54` | `#define WL_OP_SURFACE_COMMIT` |
| `WL_OP_XDG_GET_TOPLEVEL` | macro | `progs/wl/wl_mini.h:55` | `#define WL_OP_XDG_GET_TOPLEVEL` |
| `WL_POOL_MAX` | macro | `progs/wl/wl_mini.h:26` | `#define WL_POOL_MAX` |
| `WL_RESIZE_EDGE` | macro | `progs/wl/wl_mini.h:240` | `#define WL_RESIZE_EDGE` |
| `WL_STREAM_CAP` | macro | `progs/wl/wl_mini.h:1122` | `#define WL_STREAM_CAP` |
| `WL_SURF_MAX_H` | macro | `progs/wl/wl_mini.h:25` | `#define WL_SURF_MAX_H` |
| `WL_SURF_MAX_W` | macro | `progs/wl/wl_mini.h:24` | `#define WL_SURF_MAX_W` |
| `WL_TITLE_ACTIVE` | macro | `progs/wl/wl_mini.h:241` | `#define WL_TITLE_ACTIVE` |
| `WL_TITLE_H` | macro | `progs/wl/wl_mini.h:238` | `#define WL_TITLE_H` |
| `WL_TITLE_INACTIVE` | macro | `progs/wl/wl_mini.h:242` | `#define WL_TITLE_INACTIVE` |
| `body` | function | `progs/wl/wl_mini.h:698` | `* resampled into the body (inside the 1 px border, below the title),  * the exact rect wl_ev_map ...` |
| `coords` | function | `progs/wl/wl_mini.h:959` | `* coords (mapped by wl_ev_map, -1 when outside), wheel is a * monotonic total the client diffs, scancodes are raw...` |
| `wl_attach_decode` | function | `progs/wl/wl_mini.h:842` | `static inline int wl_attach_decode(const unsigned char *src, int len,         unsigned int *pool,...` |
| `wl_attach_encode` | function | `progs/wl/wl_mini.h:823` | `static inline int wl_attach_encode(unsigned char *dst, int cap,         unsigned int pool, int w,...` |
| `wl_cfg_t` | struct | `progs/wl/wl_mini.h:63` | `` |
| `wl_client_init` | function | `progs/wl/wl_mini.h:1092` | `static inline void wl_client_init(wl_client_t *cl)` |
| `wl_client_pool` | function | `progs/wl/wl_mini.h:1109` | `static inline int wl_client_pool(wl_client_t *cl, unsigned int *id)` |
| `wl_client_surface` | function | `progs/wl/wl_mini.h:1100` | `static inline int wl_client_surface(wl_client_t *cl, unsigned int *id)` |
| `wl_client_t` | struct | `progs/wl/wl_mini.h:1086` | `` |
| `wl_clip_decode` | function | `progs/wl/wl_mini.h:930` | `static inline int wl_clip_decode(const unsigned char *src, int len,         unsigned char *dst, i...` |
| `wl_clip_encode` | function | `progs/wl/wl_mini.h:907` | `static inline int wl_clip_encode(unsigned char *dst, int cap,         const unsigned char *text, ...` |
| `wl_commit_decode` | function | `progs/wl/wl_mini.h:883` | `static inline int wl_commit_decode(const unsigned char *src, int len,         unsigned int *id)` |
| `wl_commit_encode` | function | `progs/wl/wl_mini.h:870` | `static inline int wl_commit_encode(unsigned char *dst, int cap,         unsigned int id)` |
| `wl_comp_add` | function | `progs/wl/wl_mini.h:309` | `static inline int wl_comp_add(wl_comp_t *c, unsigned int id, int w, int h)` |
| `wl_comp_attach_buf` | function | `progs/wl/wl_mini.h:1218` | `static inline int wl_comp_attach_buf(wl_comp_t *c, unsigned int id,         unsigned int pool, in...` |
| `wl_comp_focus` | function | `progs/wl/wl_mini.h:372` | `static inline int wl_comp_focus(wl_comp_t *c, unsigned int id)` |
| `wl_comp_hit` | function | `progs/wl/wl_mini.h:397` | `static inline int wl_comp_hit(const wl_comp_t *c, int x, int y)` |
| `wl_comp_init` | function | `progs/wl/wl_mini.h:271` | `static inline void wl_comp_init(wl_comp_t *c)` |
| `wl_comp_layout_tile` | function | `progs/wl/wl_mini.h:577` | `static inline int wl_comp_layout_tile(wl_comp_t *c, int fb_w, int fb_h)` |
| `wl_comp_refresh_active` | function | `progs/wl/wl_mini.h:289` | `static inline void wl_comp_refresh_active(wl_comp_t *c)` |
| `wl_comp_remove` | function | `progs/wl/wl_mini.h:345` | `static inline int wl_comp_remove(wl_comp_t *c, unsigned int id)` |
| `wl_comp_set_color` | function | `progs/wl/wl_mini.h:487` | `static inline int wl_comp_set_color(wl_comp_t *c, unsigned int id, int color)` |
| `wl_comp_set_minimized` | function | `progs/wl/wl_mini.h:460` | `static inline int wl_comp_set_minimized(wl_comp_t *c, unsigned int id,         int minimized)` |
| `wl_comp_set_rect` | function | `progs/wl/wl_mini.h:550` | `static inline int wl_comp_set_rect(wl_comp_t *c, unsigned int id,         int x, int y, int w, in...` |
| `wl_comp_t` | struct | `progs/wl/wl_mini.h:264` | `` |
| `wl_comp_top_visible` | function | `progs/wl/wl_mini.h:441` | `static inline int wl_comp_top_visible(const wl_comp_t *c)` |
| `wl_dispatch` | function | `progs/wl/wl_mini.h:1245` | `static inline int wl_dispatch(wl_comp_t *c, wl_client_t *cl,         unsigned int id, unsigned in...` |
| `wl_ev_decode` | function | `progs/wl/wl_mini.h:1008` | `static inline int wl_ev_decode(const unsigned char *src, int len,         wl_ev_t *ev)` |
| `wl_ev_encode` | function | `progs/wl/wl_mini.h:978` | `static inline int wl_ev_encode(unsigned char *dst, int cap,         const wl_ev_t *ev)` |
| `wl_ev_map` | function | `progs/wl/wl_mini.h:1051` | `static inline int wl_ev_map(int fx, int fy, int sx, int sy, int sw,         int sh, int rw, int r...` |
| `wl_ev_t` | struct | `progs/wl/wl_mini.h:968` | `` |
| `wl_hdr_decode` | function | `progs/wl/wl_mini.h:99` | `static inline int wl_hdr_decode(const unsigned char *src, int len,         wl_hdr_t *out)` |
| `wl_hdr_encode` | function | `progs/wl/wl_mini.h:71` | `static inline int wl_hdr_encode(unsigned char *dst, int cap,         unsigned int id, unsigned in...` |
| `wl_hdr_t` | struct | `progs/wl/wl_mini.h:57` | `` |
| `wl_iface_find` | function | `progs/wl/wl_mini.h:1187` | `static inline int wl_iface_find(const char *name)` |
| `wl_iface_t` | struct | `progs/wl/wl_mini.h:1179` | `` |
| `wl_pool_fit` | function | `progs/wl/wl_mini.h:223` | `static inline int wl_pool_fit(int w, int h)` |
| `wl_pool_id_valid` | function | `progs/wl/wl_mini.h:219` | `static inline int wl_pool_id_valid(unsigned int id)` |
| `wl_scale_nearest` | function | `progs/wl/wl_mini.h:793` | `static inline int wl_scale_nearest(unsigned char *dst, int dw, int dh,         const unsigned cha...` |
| `wl_str_decode` | function | `progs/wl/wl_mini.h:188` | `static inline int wl_str_decode(const unsigned char *src, int len, int off,         char *dst, in...` |
| `wl_str_encode` | function | `progs/wl/wl_mini.h:163` | `static inline int wl_str_encode(unsigned char *dst, int cap, int off,         const char *s)` |
| `wl_stream_consume` | function | `progs/wl/wl_mini.h:1166` | `static inline int wl_stream_consume(wl_stream_t *s, int n)` |
| `wl_stream_feed` | function | `progs/wl/wl_mini.h:1135` | `static inline int wl_stream_feed(wl_stream_t *s, const unsigned char *src,         int n)` |
| `wl_stream_init` | function | `progs/wl/wl_mini.h:1129` | `static inline void wl_stream_init(wl_stream_t *s)` |
| `wl_stream_next` | function | `progs/wl/wl_mini.h:1150` | `static inline int wl_stream_next(wl_stream_t *s, int *size)` |
| `wl_stream_t` | struct | `progs/wl/wl_mini.h:1124` | `` |
| `wl_strlen_bounded` | function | `progs/wl/wl_mini.h:150` | `static inline int wl_strlen_bounded(const char *s)` |
| `wl_surface_hit_zone` | function | `progs/wl/wl_mini.h:415` | `static inline int wl_surface_hit_zone(const wl_surface_t *s, int x, int y)` |
| `wl_surface_id_valid` | function | `progs/wl/wl_mini.h:214` | `static inline int wl_surface_id_valid(unsigned int id)` |
| `wl_surface_t` | struct | `progs/wl/wl_mini.h:251` | `` |
| `wl_u32_decode` | function | `progs/wl/wl_mini.h:139` | `static inline int wl_u32_decode(const unsigned char *src, int len, int off,         unsigned int *v)` |
| `wl_u32_encode` | function | `progs/wl/wl_mini.h:128` | `static inline int wl_u32_encode(unsigned char *dst, int cap, int off,         unsigned int v)` |
| `wlcomp_blit` | function | `progs/wl/wl_mini.h:637` | `static inline int wlcomp_blit(const wl_comp_t *c, unsigned char *fb,         int fb_w, int fb_h, ...` |
| `wlcomp_render` | function | `progs/wl/wl_mini.h:512` | `static inline int wlcomp_render(const wl_comp_t *c, unsigned char *fb,         int fb_w, int fb_h)` |
| `MINIOS_WL_PIXBUF_H` | macro | `progs/wl/wl_pixbuf.h:17` | `#define MINIOS_WL_PIXBUF_H` |
| `WPIX_BUDGET_MAX` | macro | `progs/wl/wl_pixbuf.h:44` | `#define WPIX_BUDGET_MAX` |
| `WPIX_MAX_H` | macro | `progs/wl/wl_pixbuf.h:36` | `#define WPIX_MAX_H` |
| `WPIX_MAX_SLOTS` | macro | `progs/wl/wl_pixbuf.h:28` | `#define WPIX_MAX_SLOTS` |
| `WPIX_MAX_W` | macro | `progs/wl/wl_pixbuf.h:32` | `#define WPIX_MAX_W` |
| `WPIX_SLOT_MAX` | macro | `progs/wl/wl_pixbuf.h:40` | `#define WPIX_SLOT_MAX` |
| `wpix_commit` | function | `progs/wl/wl_pixbuf.h:175` | `static int wpix_commit(struct wpix_store *s, int idx, const unsigned char *src, int w, int h)` |
| `wpix_drop` | function | `progs/wl/wl_pixbuf.h:127` | `static void wpix_drop(struct wpix_store *s, int idx)` |
| `wpix_dst` | function | `progs/wl/wl_pixbuf.h:121` | `static unsigned char *wpix_dst(struct wpix_store *s)` |
| `wpix_ensure` | function | `progs/wl/wl_pixbuf.h:153` | `static int wpix_ensure(struct wpix_store *s, int idx, int w, int h)` |
| `wpix_free` | function | `progs/wl/wl_pixbuf.h:78` | `static void wpix_free(struct wpix_store *s)` |
| `wpix_init` | function | `progs/wl/wl_pixbuf.h:63` | `static int wpix_init(struct wpix_store *s)` |
| `wpix_ptr` | function | `progs/wl/wl_pixbuf.h:107` | `static unsigned char *wpix_ptr(struct wpix_store *s, int idx)` |
| `wpix_raw` | function | `progs/wl/wl_pixbuf.h:115` | `static unsigned char *wpix_raw(struct wpix_store *s)` |
| `wpix_slot` | struct | `progs/wl/wl_pixbuf.h:48` | `` |
| `wpix_store` | struct | `progs/wl/wl_pixbuf.h:55` | `` |
| `wpix_tmp` | function | `progs/wl/wl_pixbuf.h:136` | `static int wpix_tmp(struct wpix_store *s, size_t need)` |
| `wpix_used` | function | `progs/wl/wl_pixbuf.h:95` | `static size_t wpix_used(const struct wpix_store *s)` |
| `WLCOMP_CFG_DEFAULT` | macro | `progs/wl/wlcomp.c:53` | `#define WLCOMP_CFG_DEFAULT` |
| `WLCOMP_H` | macro | `progs/wl/wlcomp.c:40` | `#define WLCOMP_H` |
| `WLCOMP_W` | macro | `progs/wl/wlcomp.c:39` | `#define WLCOMP_W` |
| `forever` | function | `progs/wl/wlcomp.c:844` | `* one of the WL_MAX_SURFACES slots forever (eight bad names used to lock  * every real client out...` |
| `main` | function | `progs/wl/wlcomp.c:1467` | `int main(int argc, char **argv)` |
| `wlclient_find` | function | `progs/wl/wlcomp.c:1005` | `static const wlclient_pat_t *wlclient_find(const char *name)` |

Next: [SYMBOLS_p24.md](SYMBOLS_p24.md)
