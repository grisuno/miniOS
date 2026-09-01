/*
 * TopoGPT3 C Inference Engine
 * Standalone static ELF for MiniOS - no external dependencies beyond ld stubs.
 *
 * Builds: gcc -O2 -static -o topogpt3 topogpt3.c -lm (Linux)
 *   or:   miniCC -> ld -f elf -o topogpt3.elf topogpt3.o
 *
 * Usage:
 *   topogpt3 -h                          Show help
 *   topogpt3 -p "prompt" [-n N] [-t T]   Headless mode
 *   topogpt3 -i                          Interactive mode
 *   topogpt3 -f file.txt                 Read prompt from file
 */

#pragma GCC diagnostic ignored "-Wunused-function"

#ifdef __has_include
  #if __has_include(<stdio.h>)
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
  #else
    /* MiniOS standalone: declare stdio from ld stubs */
    typedef struct { int _fd; } FILE;
    extern FILE *stdin;
    extern FILE *stdout;
    extern FILE *stderr;
    extern int printf(const char *, ...);
    extern int fprintf(FILE *, const char *, ...);
    extern int sprintf(char *, const char *, ...);
    extern int snprintf(char *, unsigned long, const char *, ...);
    extern int puts(const char *);
    extern int putchar(int);
    extern int fputc(int, FILE *);
    extern int fputs(const char *, FILE *);
    extern FILE *fopen(const char *, const char *);
    extern int fclose(FILE *);
    extern unsigned long fread(void *, unsigned long, unsigned long, FILE *);
    extern unsigned long fwrite(const void *, unsigned long, unsigned long, FILE *);
    extern int fseek(FILE *, long, int);
    extern long ftell(FILE *);
    extern int fflush(FILE *);
    #define NULL ((void*)0)
    #define SEEK_SET 0
    #define SEEK_CUR 1
    #define SEEK_END 2
    extern void *malloc(unsigned long);
    extern void free(void *);
    extern void *memcpy(void *, const void *, unsigned long);
    extern void *memset(void *, int, unsigned long);
    extern int strcmp(const char *, const char *);
    extern int strncmp(const char *, const char *, unsigned long);
    extern unsigned long strlen(const char *);
    extern char *strstr(const char *, const char *);
  #endif
#else
  #include <stdio.h>
  #include <string.h>
#endif

/* ======================================================================
 * SECTION 1: CONFIGURATION
 * ====================================================================== */

#define VOCAB_SIZE      50257
#define D_MODEL         256
#define N_HEADS         8
#define N_KV_HEADS      2
#define GQA_GROUPS      4
#define D_HEAD          32
#define D_QUAT          64
#define N_LAYERS        6
#define MAX_SEQ_LEN     512
#define N_EXPERTS       4
#define MOE_TOP_K       2
#define N_NODES         8
#define N_RADIAL        2
#define N_ANGULAR       4
#define N_EDGE_TYPES   4
#define N_EDGES        24
#define SPECTRAL_LATENT_DIM 128
#define D_LAT_Q            (SPECTRAL_LATENT_DIM / 4)  /* 32 */
#define TORUS_GRID_H    2
#define TORUS_GRID_W    4
#define FREQ_W          3
#define N_SPECTRAL_LAYERS 2
#define EXPERT_INNER    344
#define READOUT_INNER   512
#define EOS_TOKEN       50256
#define EMBED_INNER     680
#define PI              3.14159265358979323846f
#define EPS_RMS         1e-6f
#define TORUS_TEMP      0.3f
#define MAX_TOKENS      1024
#define MAX_PROMPT_LEN  4096
#define MAX_LINE        512
#define TOK_TAB_SIZE    16384
#define TOK_VOCAB_SIZE  256

/* ======================================================================
 * SECTION 2: STANDALONE MATH (no libm)
 * ====================================================================== */

static float tg_sqrt(float x) {
    if (x <= 0.0f) return 0.0f;
    float guess = x * 0.5f;
    int i;
    for (i = 0; i < 20; i++) {
        guess = (guess + x / guess) * 0.5f;
    }
    return guess;
}

static float tg_exp(float x) {
    if (x > 88.0f) return 3.4e38f;
    if (x < -88.0f) return 0.0f;
    int n = (int)(x * 1.4426950408889634f);
    float r = x - n * 0.6931471805599453f;
    float e = 1.0f + r * (1.0f + r * (0.5f + r * (0.16666666666666666f
        + r * (0.041666666666666664f + r * 0.008333333333333333f))));
    int i;
    float p = 1.0f;
    int abs_n = n < 0 ? -n : n;
    for (i = 0; i < abs_n; i++) p *= 2.0f;
    return n >= 0 ? e * p : e / p;
}

static float tg_tanh(float x) {
    if (x > 6.0f) return 1.0f;
    if (x < -6.0f) return -1.0f;
    float e2 = tg_exp(2.0f * x);
    return (e2 - 1.0f) / (e2 + 1.0f);
}

static float tg_sin(float x) {
    while (x > PI) x -= 2.0f * PI;
    while (x < -PI) x += 2.0f * PI;
    float x2 = x * x;
    float s = x * (1.0f - x2 * (1.0f/6.0f - x2 * (1.0f/120.0f - x2 * (1.0f/5040.0f
        - x2 * (1.0f/362880.0f - x2 * (1.0f/39916800.0f))))));
    return s;
}

static float tg_cos(float x) {
    return tg_sin(x + PI * 0.5f);
}

static float tg_fabs(float x) {
    return x < 0.0f ? -x : x;
}

static float tg_log(float x) {
    if (x <= 0.0f) return -1e30f;
    int k = 0;
    while (x > 2.0f) { x *= 0.5f; k++; }
    while (x < 0.5f) { x *= 2.0f; k--; }
    float z = (x - 1.0f) / (x + 1.0f);
    float z2 = z * z;
    float s = z * (1.0f + z2 * (1.0f/3.0f + z2 * (1.0f/5.0f
        + z2 * (1.0f/7.0f + z2 * (1.0f/9.0f + z2 / 11.0f)))));
    return s * 2.0f + k * 0.6931471805599453f;
}

static float tg_fmax(float a, float b) {
    return a > b ? a : b;
}

static float tg_fmin(float a, float b) {
    return a < b ? a : b;
}

/* ======================================================================
 * SECTION 3: DATA STRUCTURES
 * ====================================================================== */

typedef struct {
    float norm1[D_MODEL];
    float norm2[D_MODEL];
    float q_proj[D_MODEL * D_MODEL];
    float k_proj[N_KV_HEADS * D_HEAD * D_MODEL];
    float v_proj[N_KV_HEADS * D_HEAD * D_MODEL];
    float o_proj[D_MODEL * D_MODEL];
    float temperature[1];
    /* Spectral autoencoder 1D kernels */
    float enc_kr[D_MODEL / 2 + 1];
    float enc_ki[D_MODEL / 2 + 1];
    float dec_kr[D_MODEL / 2 + 1];
    float dec_ki[D_MODEL / 2 + 1];
    /* Spectral autoencoder quaternion projections (enc: [32,64], dec: [64,32]) */
    float ae_ww[D_LAT_Q * D_QUAT], ae_wx[D_LAT_Q * D_QUAT];
    float ae_wy[D_LAT_Q * D_QUAT], ae_wz[D_LAT_Q * D_QUAT];
    float de_ww[D_QUAT * D_LAT_Q], de_wx[D_QUAT * D_LAT_Q];
    float de_wy[D_QUAT * D_LAT_Q], de_wz[D_QUAT * D_LAT_Q];
    /* Spectral 2D layers */
    float kr_w[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float ki_w[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float kr_x[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float ki_x[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float kr_y[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float ki_y[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float kr_z[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    float ki_z[N_SPECTRAL_LAYERS][D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W];
    /* Torus projection */
    float tp_ww[D_QUAT * D_QUAT], tp_wx[D_QUAT * D_QUAT];
    float tp_wy[D_QUAT * D_QUAT], tp_wz[D_QUAT * D_QUAT];
    float tp_lin[D_MODEL * 4];
    /* Node/edge embeddings */
    float node_embed[N_NODES * D_MODEL];
    float edge_quat[N_EDGE_TYPES * 4];
    /* Message passing */
    float mp_ww[D_QUAT * D_QUAT], mp_wx[D_QUAT * D_QUAT];
    float mp_wy[D_QUAT * D_QUAT], mp_wz[D_QUAT * D_QUAT];
    /* Readout */
    float ro_w1[READOUT_INNER * D_MODEL], ro_b1[READOUT_INNER];
    float ro_w2[D_MODEL * READOUT_INNER], ro_b2[D_MODEL];
    /* MoE experts */
    float gate_proj[N_EXPERTS][EXPERT_INNER * D_MODEL];
    float up_proj[N_EXPERTS][EXPERT_INNER * D_MODEL];
    float down_proj[N_EXPERTS][D_MODEL * EXPERT_INNER];
    /* MoE router */
    float router[N_EXPERTS * D_MODEL];
} LayerWeights;

typedef struct {
    float token_embed[VOCAB_SIZE * D_MODEL];
    LayerWeights layers[N_LAYERS];
    float final_norm[D_MODEL];
} ModelWeights;

/* Static model weights */
static ModelWeights W;

/* KV cache */
static float kv_cache_k[N_LAYERS][MAX_SEQ_LEN][N_KV_HEADS * D_HEAD];
static float kv_cache_v[N_LAYERS][MAX_SEQ_LEN][N_KV_HEADS * D_HEAD];
static int kv_len = 0;

/* Working buffers (allocated statically) */
static float x_buf[D_MODEL];
static float att_out[D_MODEL];
static float logits[VOCAB_SIZE];

/* RoPE cache */
static float cos_cache[MAX_SEQ_LEN][D_HEAD];
static float sin_cache[MAX_SEQ_LEN][D_HEAD];

/* Torus graph edge lists */
static int edges_i[N_EDGES], edges_j[N_EDGES], edge_type[N_EDGES];

/* Vocabulary for decoding (loaded from vocab.bin) */
static unsigned char *vocab_data[VOCAB_SIZE];  /* pointers into vocab_buf */
static int vocab_len[VOCAB_SIZE];
static int vocab_count = 0;

static void load_vocab(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) { printf("Warning: cannot open %s, using fallback decoder\n", path); return; }
    char magic[4];
    if (fread(magic, 1, 4, f) != 4 || memcmp(magic, "VOCB", 4) != 0) {
        printf("Warning: bad vocab magic\n"); fclose(f); return;
    }
    unsigned int n;
    if (fread(&n, 4, 1, f) != 1) { fclose(f); return; }
    if (n > VOCAB_SIZE) n = VOCAB_SIZE;
    vocab_count = (int)n;
    /* Read all vocab entries into a single buffer */
    long total_bytes = 0;
    long pos_start = ftell(f);
    int i;
    for (i = 0; i < vocab_count; i++) {
        unsigned short slen;
        if (fread(&slen, 2, 1, f) != 1) break;
        fseek(f, slen, SEEK_CUR);
        total_bytes += slen;
    }
    unsigned char *bigbuf = (unsigned char *)malloc(total_bytes);
    if (!bigbuf) { fclose(f); return; }
    fseek(f, pos_start, SEEK_SET);
    long offset = 0;
    for (i = 0; i < vocab_count; i++) {
        unsigned short slen;
        if (fread(&slen, 2, 1, f) != 1) break;
        vocab_data[i] = bigbuf + offset;
        vocab_len[i] = slen;
        if (slen > 0) fread(bigbuf + offset, 1, slen, f);
        offset += slen;
    }
    fclose(f);
    printf("Loaded vocab: %d tokens (%ld bytes)\n", vocab_count, total_bytes);
}

/* ======================================================================
 * SECTION 4: TORUS GRAPH BUILDER
 * ====================================================================== */

static void build_torus_graph(void) {
    int idx = 0;
    int r, a;
    for (r = 0; r < N_RADIAL; r++) {
        for (a = 0; a < N_ANGULAR; a++) {
            int n = r * N_ANGULAR + a;
            int neighbor;
            /* Angular left (type 0) */
            neighbor = r * N_ANGULAR + (a - 1 + N_ANGULAR) % N_ANGULAR;
            edges_i[idx] = n; edges_j[idx] = neighbor; edge_type[idx] = 0; idx++;
            /* Angular right (type 1) */
            neighbor = r * N_ANGULAR + (a + 1) % N_ANGULAR;
            edges_i[idx] = n; edges_j[idx] = neighbor; edge_type[idx] = 1; idx++;
            /* Radial inward (type 2) */
            if (r > 0) {
                neighbor = (r - 1) * N_ANGULAR + a;
                edges_i[idx] = n; edges_j[idx] = neighbor; edge_type[idx] = 2; idx++;
            }
            /* Radial outward (type 3) */
            if (r < N_RADIAL - 1) {
                neighbor = (r + 1) * N_ANGULAR + a;
                edges_i[idx] = n; edges_j[idx] = neighbor; edge_type[idx] = 3; idx++;
            }
        }
    }
}

/* ======================================================================
 * SECTION 5: ROPE PRECOMPUTATION
 * ====================================================================== */

static void precompute_rope(void) {
    int pos, i;
    float inv_freq[D_HEAD / 2];
    for (i = 0; i < D_HEAD / 2; i++) {
        float base = 10000.0f;
        float exp_val = (float)(2 * i) / (float)D_HEAD;
        float p = 1.0f;
        int j;
        for (j = 0; j < (int)exp_val; j++) p *= base;
        float frac = exp_val - (int)exp_val;
        float base_frac = 1.0f;
        if (frac > 0.0f) {
            float ln_base = tg_log(base);
            base_frac = tg_exp(frac * ln_base);
        }
        inv_freq[i] = 1.0f / (p * base_frac);
    }
    for (pos = 0; pos < MAX_SEQ_LEN; pos++) {
        for (i = 0; i < D_HEAD / 2; i++) {
            float freq = (float)pos * inv_freq[i];
            cos_cache[pos][i] = tg_cos(freq);
            cos_cache[pos][i + D_HEAD / 2] = tg_cos(freq);
            sin_cache[pos][i] = tg_sin(freq);
            sin_cache[pos][i + D_HEAD / 2] = tg_sin(freq);
        }
    }
}

/* ======================================================================
 * SECTION 6: MATRIX OPERATIONS
 * ====================================================================== */

static void matvec(const float *W, const float *x, float *y, int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        float s = 0.0f;
        for (j = 0; j < cols; j++) {
            s += W[i * cols + j] * x[j];
        }
        y[i] = s;
    }
}

static void matvec_bias(const float *W, const float *b, const float *x, float *y,
                         int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        float s = b[i];
        for (j = 0; j < cols; j++) {
            s += W[i * cols + j] * x[j];
        }
        y[i] = s;
    }
}

static void rmsnorm(const float *x, const float *w, float *y, int d) {
    float ss = 0.0f;
    int i;
    for (i = 0; i < d; i++) ss += x[i] * x[i];
    ss = ss / (float)d + EPS_RMS;
    ss = 1.0f / tg_sqrt(ss);
    for (i = 0; i < d; i++) y[i] = x[i] * ss * w[i];
}

static void softmax(float *x, int n) {
    float mx = x[0];
    int i;
    for (i = 1; i < n; i++) if (x[i] > mx) mx = x[i];
    float s = 0.0f;
    for (i = 0; i < n; i++) { x[i] = tg_exp(x[i] - mx); s += x[i]; }
    for (i = 0; i < n; i++) x[i] /= s;
}

static void gelu(float *x, int n) {
    int i;
    for (i = 0; i < n; i++) {
        float v = x[i];
        float c = tg_sqrt(2.0f / PI);
        float t = 0.044715f * v * v * v;
        x[i] = 0.5f * v * (1.0f + tg_tanh(c * (v + t)));
    }
}

static void silu(float *x, int n) {
    int i;
    for (i = 0; i < n; i++) {
        float s = 1.0f / (1.0f + tg_exp(-x[i]));
        x[i] = x[i] * s;
    }
}

static void swiglu(const float *gate_w, const float *up_w, const float *down_w,
                    const float *x, float *y, int d_model, int inner) {
    float gate_buf[EXPERT_INNER];
    float up_buf[EXPERT_INNER];
    float mid[EXPERT_INNER];
    int i;
    matvec(gate_w, x, gate_buf, inner, d_model);
    matvec(up_w, x, up_buf, inner, d_model);
    silu(gate_buf, inner);
    for (i = 0; i < inner; i++) mid[i] = gate_buf[i] * up_buf[i];
    matvec(down_w, mid, y, d_model, inner);
}

/* ======================================================================
 * SECTION 7: QUATERNION OPERATIONS
 * ====================================================================== */

static void quat_normalize(float *q) {
    float n = tg_sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    if (n > 1e-8f) { q[0]/=n; q[1]/=n; q[2]/=n; q[3]/=n; }
}

static void quat_hamilton(const float *a, const float *b, float *c) {
    c[0] = a[0]*b[0] - a[1]*b[1] - a[2]*b[2] - a[3]*b[3];
    c[1] = a[0]*b[1] + a[1]*b[0] + a[2]*b[3] - a[3]*b[2];
    c[2] = a[0]*b[2] - a[1]*b[3] + a[2]*b[0] + a[3]*b[1];
    c[3] = a[0]*b[3] + a[1]*b[2] - a[2]*b[1] + a[3]*b[0];
}

/* QuaternionLinear: x[w,x,y,z] -> y[w,x,y,z] */
static void quat_linear(const float *Ww, const float *Wx, const float *Wy, const float *Wz,
                         const float *x, float *y, int in_q, int out_q) {
    float xw[D_QUAT], xx[D_QUAT], xy[D_QUAT], xz[D_QUAT];
    float ow[D_QUAT], ox[D_QUAT], oy[D_QUAT], oz[D_QUAT];
    int i;
    for (i = 0; i < in_q; i++) {
        xw[i] = x[i]; xx[i] = x[i + in_q];
        xy[i] = x[i + 2*in_q]; xz[i] = x[i + 3*in_q];
    }
    matvec(Ww, xw, ow, out_q, in_q);
    matvec(Wx, xx, ox, out_q, in_q);
    matvec(Wy, xy, oy, out_q, in_q);
    matvec(Wz, xz, oz, out_q, in_q);
    for (i = 0; i < out_q; i++) y[i]              = ow[i] - ox[i] - oy[i] - oz[i];
    for (i = 0; i < out_q; i++) y[i + out_q]      = ow[i] + ox[i] + oy[i] - oz[i];
    for (i = 0; i < out_q; i++) y[i + 2*out_q]    = ow[i] - ox[i] + oy[i] + oz[i];
    for (i = 0; i < out_q; i++) y[i + 3*out_q]    = ow[i] + ox[i] - oy[i] + oz[i];
}

/* ======================================================================
 * SECTION 8: FFT (radix-2 DIT, in-place, for D_MODEL=256)
 * ====================================================================== */

static void fft_radix2(float *real, float *imag, int n) {
    int i, j, k, m;
    /* Bit reversal */
    j = 0;
    for (i = 0; i < n; i++) {
        if (i < j) {
            float tr = real[i]; real[i] = real[j]; real[j] = tr;
            float ti = imag[i]; imag[i] = imag[j]; imag[j] = ti;
        }
        m = n >> 1;
        while (m >= 1 && j >= m) { j -= m; m >>= 1; }
        j += m;
    }
    /* Butterfly */
    for (m = 2; m <= n; m <<= 1) {
        float angle = -2.0f * PI / (float)m;
        float wr = tg_cos(angle), wi = tg_sin(angle);
        for (k = 0; k < n; k += m) {
            float cur_r = 1.0f, cur_i = 0.0f;
            for (j = 0; j < m/2; j++) {
                float tr = cur_r * real[k+j+m/2] - cur_i * imag[k+j+m/2];
                float ti = cur_r * imag[k+j+m/2] + cur_i * real[k+j+m/2];
                real[k+j+m/2] = real[k+j] - tr;
                imag[k+j+m/2] = imag[k+j] - ti;
                real[k+j] += tr;
                imag[k+j] += ti;
                float nr = cur_r * wr - cur_i * wi;
                cur_i = cur_r * wi + cur_i * wr;
                cur_r = nr;
            }
        }
    }
}

static void ifft_radix2(float *real, float *imag, int n) {
    int i;
    for (i = 0; i < n; i++) imag[i] = -imag[i];
    fft_radix2(real, imag, n);
    for (i = 0; i < n; i++) { real[i] /= (float)n; imag[i] = -imag[i] / (float)n; }
}

/* Real FFT: x[n] -> X[n/2+1] complex */
static void rfft(const float *x, float *Xr, float *Xi, int n) {
    float re[n], im[n];
    int i;
    for (i = 0; i < n; i++) { re[i] = x[i]; im[i] = 0.0f; }
    fft_radix2(re, im, n);
    for (i = 0; i <= n/2; i++) { Xr[i] = re[i]; Xi[i] = im[i]; }
}

/* Inverse real FFT: X[n/2+1] complex -> x[n] */
static void irfft(const float *Xr, const float *Xi, float *x, int n) {
    float re[n], im[n];
    int i;
    re[0] = Xr[0]; im[0] = 0.0f;
    for (i = 1; i < n/2; i++) { re[i] = Xr[i]; im[i] = Xi[i]; }
    re[n/2] = Xr[n/2]; im[n/2] = 0.0f;
    for (i = n/2+1; i < n; i++) { re[i] = Xr[n-i]; im[i] = -Xi[n-i]; }
    ifft_radix2(re, im, n);
    for (i = 0; i < n; i++) x[i] = re[i];
}

/* ======================================================================
 * SECTION 9: SPECTRAL 1D FILTER
 * ====================================================================== */

static void filter1d(const float *x, const float *kr, const float *ki,
                      float *y, int d_model) {
    int n_freq = d_model / 2 + 1;
    float Xr[n_freq], Xi[n_freq];
    float Yr[d_model], Yi[d_model];
    int i;
    rfft(x, Xr, Xi, d_model);
    for (i = 0; i < n_freq; i++) {
        float cr = Xr[i], ci = Xi[i];
        float wr = kr[i], wi = ki[i];
        Yr[i] = cr * wr - ci * wi;
        Yi[i] = cr * wi + ci * wr;
    }
    irfft(Yr, Yi, y, d_model);
}

/* ======================================================================
 * SECTION 10: FFT2D (for small grids)
 * ====================================================================== */

/* 2D FFT on a small grid: data[h*w] real -> out_r[h][w], out_i[h][w] */
static void fft2d_real(const float *data, float *out_r, float *out_i, int h, int w) {
    float re[h * w], im[h * w];
    int i, r, c;
    /* Copy to complex array */
    for (i = 0; i < h * w; i++) { re[i] = data[i]; im[i] = 0.0f; }
    /* FFT rows */
    float row_re[w], row_im[w];
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) { row_re[c] = re[r*w+c]; row_im[c] = im[r*w+c]; }
        fft_radix2(row_re, row_im, w);
        for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; }
    }
    /* FFT columns */
    float col_re[h], col_im[h];
    for (c = 0; c < w; c++) {
        for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; }
        fft_radix2(col_re, col_im, h);
        for (r = 0; r < h; r++) { re[r*w+c] = col_re[r]; im[r*w+c] = col_im[r]; }
    }
    for (i = 0; i < h * w; i++) { out_r[i] = re[i]; out_i[i] = im[i]; }
}

static void ifft2d(float *data_r, float *data_i, int h, int w) {
    float re[h * w], im[h * w];
    int i, r, c;
    for (i = 0; i < h * w; i++) { re[i] = data_r[i]; im[i] = data_i[i]; }
    /* IFFT rows */
    float row_re[w], row_im[w];
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) { row_re[c] = re[r*w+c]; row_im[c] = im[r*w+c]; }
        ifft_radix2(row_re, row_im, w);
        for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; }
    }
    /* IFFT columns */
    float col_re[h], col_im[h];
    for (c = 0; c < w; c++) {
        for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; }
        ifft_radix2(col_re, col_im, h);
        for (r = 0; r < h; r++) { re[r*w+c] = col_re[r]; im[r*w+c] = col_im[r]; }
    }
    for (i = 0; i < h * w; i++) { data_r[i] = re[i]; data_i[i] = im[i]; }
}

/* RFFT2: 2D real FFT, output is [h][w/2+1] complex */
static void rfft2d_real(const float *data, float *out_r, float *out_i,
                         int h, int w) {
    float re[h * w], im[h * w];
    int i, r, c;
    for (i = 0; i < h * w; i++) { re[i] = data[i]; im[i] = 0.0f; }
    float row_re[w], row_im[w];
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) { row_re[c] = re[r*w+c]; row_im[c] = im[r*w+c]; }
        fft_radix2(row_re, row_im, w);
        for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; }
    }
    float col_re[h], col_im[h];
    for (c = 0; c < w; c++) {
        for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; }
        fft_radix2(col_re, col_im, h);
        for (r = 0; r < h; r++) { re[r*w+c] = col_re[r]; im[r*w+c] = col_im[r]; }
    }
    int fw = w / 2 + 1;
    for (r = 0; r < h; r++) {
        for (c = 0; c < fw; c++) {
            out_r[r * fw + c] = re[r * w + c];
            out_i[r * fw + c] = im[r * w + c];
        }
    }
}

/* IRFFT2: inverse of rfft2d_real */
static void irfft2d(const float *in_r, const float *in_i, float *out,
                     int h, int w) {
    int fw = w / 2 + 1;
    float re[h * w], im[h * w];
    int r, c, i;
    for (r = 0; r < h; r++) {
        re[r*w] = in_r[r*fw]; im[r*w] = in_i[r*fw];
        for (c = 1; c < w/2; c++) {
            re[r*w+c] = in_r[r*fw+c]; im[r*w+c] = in_i[r*fw+c];
        }
        re[r*w + w/2] = in_r[r*fw + w/2]; im[r*w + w/2] = 0.0f;
        for (c = w/2+1; c < w; c++) {
            re[r*w+c] = in_r[r*fw + w - c]; im[r*w+c] = -in_i[r*fw + w - c];
        }
    }
    float row_re[w], row_im[w];
    for (r = 0; r < h; r++) {
        for (c = 0; c < w; c++) { row_re[c] = re[r*w+c]; row_im[c] = im[r*w+c]; }
        ifft_radix2(row_re, row_im, w);
        for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; }
    }
    float col_re[h], col_im[h];
    for (c = 0; c < w; c++) {
        for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; }
        ifft_radix2(col_re, col_im, h);
        for (r = 0; r < h; r++) { re[r*w+c] = col_re[r]; im[r*w+c] = col_im[r]; }
    }
    for (i = 0; i < h * w; i++) out[i] = re[i];
}

/* ======================================================================
 * SECTION 11: QUATERNION SPECTRAL LAYER 2D
 * ====================================================================== */

/* Complex multiply: (ar+bi)(cr+di) = (ac-bd)+(ad+bc)i */
static void cmul(float ar, float ai, float cr, float di, float *rr, float *ri) {
    *rr = ar*cr - ai*di;
    *ri = ar*di + ai*cr;
}

/* Contract: Y[o,h,w] = sum_i W[i,o,h,w] * X[b,i,h,w] (complex) */
static void spectral_contract(const float *Wr, const float *Wi,
                               const float *Xr, const float *Xi,
                               float *Yr, float *Yi,
                               int in_q, int out_q, int fh, int fw) {
    int o, h, w;
    for (o = 0; o < out_q; o++) {
        for (h = 0; h < fh; h++) {
            for (w = 0; w < fw; w++) {
                float sr = 0.0f, si = 0.0f;
                int i;
                for (i = 0; i < in_q; i++) {
                    float wr = Wr[(i*out_q+o)*fh*fw + h*fw+w];
                    float wi = Wi[(i*out_q+o)*fh*fw + h*fw+w];
                    float xr = Xr[(i)*fh*fw + h*fw+w];
                    float xi = Xi[(i)*fh*fw + h*fw+w];
                    sr += wr*xr - wi*xi;
                    si += wr*xi + wi*xr;
                }
                Yr[(o)*fh*fw + h*fw+w] = sr;
                Yi[(o)*fh*fw + h*fw+w] = si;
            }
        }
    }
}

static void quat_spectral_layer_2d(
    const float *x, float *y,
    const float *kr_w, const float *ki_w, const float *kr_x, const float *ki_x,
    const float *kr_y, const float *ki_y, const float *kr_z, const float *ki_z,
    int in_q, int out_q, int grid_h, int grid_w)
{
    int fh = grid_h, fw = grid_w;
    int q = in_q;
    int freq_w = fw / 2 + 1;
    float xw_r[fh*freq_w], xw_i[fh*freq_w];
    float xx_r[fh*freq_w], xx_i[fh*freq_w];
    float xy_r[fh*freq_w], xy_i[fh*freq_w];
    float xz_r[fh*freq_w], xz_i[fh*freq_w];
    int i;

    /* FFT2 each quaternion channel */
    rfft2d_real(x, xw_r, xw_i, fh, fw);
    rfft2d_real(x + q*fh*fw, xx_r, xx_i, fh, fw);
    rfft2d_real(x + 2*q*fh*fw, xy_r, xy_i, fh, fw);
    rfft2d_real(x + 3*q*fh*fw, xz_r, xz_i, fh, fw);

    /* 16 contractions: C[(wc,xc)] for each pair */
    float Cww_r[out_q*fh*freq_w], Cww_i[out_q*fh*freq_w];
    float Cwx_r[out_q*fh*freq_w], Cwx_i[out_q*fh*freq_w];
    float Cwy_r[out_q*fh*freq_w], Cwy_i[out_q*fh*freq_w];
    float Cwz_r[out_q*fh*freq_w], Cwz_i[out_q*fh*freq_w];
    float Cxw_r[out_q*fh*freq_w], Cxw_i[out_q*fh*freq_w];
    float Cxx_r[out_q*fh*freq_w], Cxx_i[out_q*fh*freq_w];
    float Cxy_r[out_q*fh*freq_w], Cxy_i[out_q*fh*freq_w];
    float Cxz_r[out_q*fh*freq_w], Cxz_i[out_q*fh*freq_w];
    float Cyw_r[out_q*fh*freq_w], Cyw_i[out_q*fh*freq_w];
    float Cyx_r[out_q*fh*freq_w], Cyx_i[out_q*fh*freq_w];
    float Cyy_r[out_q*fh*freq_w], Cyy_i[out_q*fh*freq_w];
    float Cyz_r[out_q*fh*freq_w], Cyz_i[out_q*fh*freq_w];
    float Czw_r[out_q*fh*freq_w], Czw_i[out_q*fh*freq_w];
    float Czx_r[out_q*fh*freq_w], Czx_i[out_q*fh*freq_w];
    float Czy_r[out_q*fh*freq_w], Czy_i[out_q*fh*freq_w];
    float Czz_r[out_q*fh*freq_w], Czz_i[out_q*fh*freq_w];

    spectral_contract(kr_w, ki_w, xw_r, xw_i, Cww_r, Cww_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_x, ki_x, xw_r, xw_i, Cwx_r, Cwx_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_y, ki_y, xw_r, xw_i, Cwy_r, Cwy_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_z, ki_z, xw_r, xw_i, Cwz_r, Cwz_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_w, ki_w, xx_r, xx_i, Cxw_r, Cxw_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_x, ki_x, xx_r, xx_i, Cxx_r, Cxx_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_y, ki_y, xx_r, xx_i, Cxy_r, Cxy_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_z, ki_z, xx_r, xx_i, Cxz_r, Cxz_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_w, ki_w, xy_r, xy_i, Cyw_r, Cyw_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_x, ki_x, xy_r, xy_i, Cyx_r, Cyx_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_y, ki_y, xy_r, xy_i, Cyy_r, Cyy_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_z, ki_z, xy_r, xy_i, Cyz_r, Cyz_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_w, ki_w, xz_r, xz_i, Czw_r, Czw_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_x, ki_x, xz_r, xz_i, Czx_r, Czx_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_y, ki_y, xz_r, xz_i, Czy_r, Czy_i, in_q, out_q, fh, freq_w);
    spectral_contract(kr_z, ki_z, xz_r, xz_i, Czz_r, Czz_i, in_q, out_q, fh, freq_w);

    /* Hamilton product in frequency domain */
    float Pw_r[out_q*fh*freq_w], Pw_i[out_q*fh*freq_w];
    float Px_r[out_q*fh*freq_w], Px_i[out_q*fh*freq_w];
    float Py_r[out_q*fh*freq_w], Py_i[out_q*fh*freq_w];
    float Pz_r[out_q*fh*freq_w], Pz_i[out_q*fh*freq_w];
    int sz = out_q * fh * freq_w;
    for (i = 0; i < sz; i++) {
        Pw_r[i] = Cww_r[i] - Cxx_r[i] - Cyy_r[i] - Czz_r[i];
        Pw_i[i] = Cww_i[i] - Cxx_i[i] - Cyy_i[i] - Czz_i[i];
        Px_r[i] = Cwx_r[i] + Cxw_r[i] + Cyz_r[i] - Czy_r[i];
        Px_i[i] = Cwx_i[i] + Cxw_i[i] + Cyz_i[i] - Czy_i[i];
        Py_r[i] = Cwy_r[i] - Cxz_r[i] + Cyw_r[i] + Czx_r[i];
        Py_i[i] = Cwy_i[i] - Cxz_i[i] + Cyw_i[i] + Czx_i[i];
        Pz_r[i] = Cwz_r[i] + Cxy_r[i] - Cyx_r[i] + Czw_r[i];
        Pz_i[i] = Cwz_i[i] + Cxy_i[i] - Cyx_i[i] + Czw_i[i];
    }

    /* IFFT2 */
    float ow[fh*fw], ox[fh*fw], oy[fh*fw], oz[fh*fw];
    irfft2d(Pw_r, Pw_i, ow, fh, fw);
    irfft2d(Px_r, Px_i, ox, fh, fw);
    irfft2d(Py_r, Py_i, oy, fh, fw);
    irfft2d(Pz_r, Pz_i, oz, fh, fw);

    for (i = 0; i < fh*fw; i++) y[i] = ow[i];
    for (i = 0; i < fh*fw; i++) y[out_q*fh*fw + i] = ox[i];
    for (i = 0; i < fh*fw; i++) y[2*out_q*fh*fw + i] = oy[i];
    for (i = 0; i < fh*fw; i++) y[3*out_q*fh*fw + i] = oz[i];
}

/* ======================================================================
 * SECTION 12: SPECTRAL AUTOENCODER FORWARD
 * ====================================================================== */

static void spectral_ae_encode(const float *x, float *z, const LayerWeights *lw) {
    float filtered[D_MODEL];
    filter1d(x, lw->enc_kr, lw->enc_ki, filtered, D_MODEL);
    gelu(filtered, D_MODEL);
    quat_linear(lw->ae_ww, lw->ae_wx, lw->ae_wy, lw->ae_wz,
                filtered, z, D_QUAT, D_LAT_Q);
}

static void spectral_ae_decode(const float *z, float *x, const LayerWeights *lw) {
    float proj_out[D_MODEL];
    quat_linear(lw->de_ww, lw->de_wx, lw->de_wy, lw->de_wz,
                z, proj_out, D_LAT_Q, D_QUAT);
    filter1d(proj_out, lw->dec_kr, lw->dec_ki, x, D_MODEL);
}

static void process_torus_grid(const float *grid, float *out, const LayerWeights *lw) {
    float h[4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W];
    float tmp[4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W];
    int i, j;
    int sz = 4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W;
    for (i = 0; i < sz; i++) h[i] = grid[i];
    for (j = 0; j < N_SPECTRAL_LAYERS; j++) {
        quat_spectral_layer_2d(h, tmp,
            lw->kr_w[j], lw->ki_w[j], lw->kr_x[j], lw->ki_x[j],
            lw->kr_y[j], lw->ki_y[j], lw->kr_z[j], lw->ki_z[j],
            D_QUAT, D_QUAT, TORUS_GRID_H, TORUS_GRID_W);
        gelu(tmp, sz);
        for (i = 0; i < sz; i++) h[i] = tmp[i];
    }
    for (i = 0; i < sz; i++) out[i] = h[i];
}

/* ======================================================================
 * SECTION 13: TORUS BRAIN FORWARD
 * ====================================================================== */

static void torus_soft_assign(const float *phi1, const float *phi2,
                               float *weights, int bs) {
    /* ang_pos = [-pi, -pi/3, pi/3, pi] (linspace(-pi, pi, 5)[:-1]) */
    float ang_pos[N_ANGULAR] = {-PI, -PI/3.0f, PI/3.0f, PI};
    float rad_pos[N_RADIAL] = {-PI, 0.0f};
    int i, r, a;
    for (i = 0; i < bs; i++) {
        float d_flat[N_NODES];
        for (r = 0; r < N_RADIAL; r++) {
            float dr = tg_sin((phi2[i] - rad_pos[r]) * 0.5f);
            dr = dr * dr;
            for (a = 0; a < N_ANGULAR; a++) {
                float da = tg_sin((phi1[i] - ang_pos[a]) * 0.5f);
                da = da * da;
                d_flat[r * N_ANGULAR + a] = dr + da;
            }
        }
        softmax(d_flat, N_NODES);
        for (int j = 0; j < N_NODES; j++) weights[i * N_NODES + j] = d_flat[j];
    }
}

static void message_passing(const float *node_feat, float *out,
                             const LayerWeights *lw) {
    float eq[4 * 4];
    int i, e, d;
    for (i = 0; i < 16; i++) eq[i] = lw->edge_quat[i];
    for (i = 0; i < 4; i++) quat_normalize(eq + i * 4);

    float agg[N_NODES * D_MODEL];
    for (i = 0; i < N_NODES * D_MODEL; i++) agg[i] = 0.0f;

    for (e = 0; e < N_EDGES; e++) {
        int src = edges_j[e];
        int dst = edges_i[e];
        int et = edge_type[e];
        float *eq_t = eq + et * 4;

        for (d = 0; d < D_QUAT; d++) {
            float src_q[4] = {
                node_feat[src * D_MODEL + d],
                node_feat[src * D_MODEL + D_QUAT + d],
                node_feat[src * D_MODEL + 2*D_QUAT + d],
                node_feat[src * D_MODEL + 3*D_QUAT + d]
            };
            float msg[4];
            quat_hamilton(eq_t, src_q, msg);
            agg[dst * D_MODEL + d] += msg[0];
            agg[dst * D_MODEL + D_QUAT + d] += msg[1];
            agg[dst * D_MODEL + 2*D_QUAT + d] += msg[2];
            agg[dst * D_MODEL + 3*D_QUAT + d] += msg[3];
        }
    }

    float combined[N_NODES * D_MODEL];
    for (i = 0; i < N_NODES * D_MODEL; i++) combined[i] = node_feat[i] + agg[i];

    /* node_net = QuaternionLinear(D_MODEL, D_MODEL) */
    float result[N_NODES * D_MODEL];
    for (i = 0; i < N_NODES; i++) {
        quat_linear(lw->mp_ww, lw->mp_wx, lw->mp_wy, lw->mp_wz,
                    combined + i * D_MODEL, result + i * D_MODEL,
                    D_QUAT, D_QUAT);
    }
    for (i = 0; i < N_NODES * D_MODEL; i++) out[i] = result[i];
}

static void torus_brain_forward(const float *x, float *out, float *recon_loss,
                                 const LayerWeights *lw) {
    int i, j;

    /* 1. Spectral autoencoder encode */
    float z[SPECTRAL_LATENT_DIM];
    spectral_ae_encode(x, z, lw);

    /* 2. Torus projection */
    float coords_raw[D_MODEL];
    quat_linear(lw->tp_ww, lw->tp_wx, lw->tp_wy, lw->tp_wz,
                x, coords_raw, D_QUAT, D_QUAT);
    gelu(coords_raw, D_MODEL);
    float coords[4];
    matvec(lw->tp_lin, coords_raw, coords, 4, D_MODEL);

    float phi1 = PI * tg_tanh(coords[0]);
    float phi2 = PI * tg_tanh(coords[1]);

    /* 3. Soft assign to torus nodes */
    float attn_w[N_NODES];
    torus_soft_assign(&phi1, &phi2, attn_w, 1);

    /* 4. Build node grid */
    float nodes[N_NODES * D_MODEL];
    for (i = 0; i < N_NODES; i++) {
        for (j = 0; j < D_MODEL; j++) {
            nodes[i * D_MODEL + j] = attn_w[i] * lw->node_embed[i * D_MODEL + j]
                                   + attn_w[i] * x[j];
        }
    }

    /* 5. Process through spectral layers */
    float grid[4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W];
    for (i = 0; i < 4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W; i++) grid[i] = 0.0f;
    /* Reshape nodes to grid: [N_NODES, D] -> [D, RADIAL, ANGULAR] */
    for (i = 0; i < N_NODES; i++) {
        int r = i / N_ANGULAR;
        int a = i % N_ANGULAR;
        for (j = 0; j < D_MODEL; j++) {
            grid[j * N_RADIAL * N_ANGULAR + r * N_ANGULAR + a] = nodes[i * D_MODEL + j];
        }
    }
    float grid_spec[4 * D_QUAT * TORUS_GRID_H * TORUS_GRID_W];
    process_torus_grid(grid, grid_spec, lw);

    /* 6. Back to node features */
    float grid_back[N_NODES * D_MODEL];
    for (i = 0; i < N_NODES; i++) {
        int r = i / N_ANGULAR;
        int a = i % N_ANGULAR;
        for (j = 0; j < D_MODEL; j++) {
            grid_back[i * D_MODEL + j] = grid_spec[j * N_RADIAL * N_ANGULAR + r * N_ANGULAR + a];
        }
    }

    /* 7. Message passing */
    float nodes_mp[N_NODES * D_MODEL];
    message_passing(grid_back, nodes_mp, lw);

    /* 8. Weighted readout */
    float pooled[D_MODEL];
    for (j = 0; j < D_MODEL; j++) {
        pooled[j] = 0.0f;
        for (i = 0; i < N_NODES; i++) {
            pooled[j] += attn_w[i] * nodes_mp[i * D_MODEL + j];
        }
    }

    /* 9. Readout MLP */
    float mid[READOUT_INNER];
    matvec_bias(lw->ro_w1, lw->ro_b1, pooled, mid, READOUT_INNER, D_MODEL);
    gelu(mid, READOUT_INNER);
    matvec_bias(lw->ro_w2, lw->ro_b2, mid, out, D_MODEL, READOUT_INNER);

    /* Recon loss (not used in inference but computed for completeness) */
    float recon[D_MODEL];
    spectral_ae_decode(z, recon, lw);
    float rl = 0.0f;
    for (i = 0; i < D_MODEL; i++) {
        float d = recon[i] - x[i];
        rl += d * d;
    }
    *recon_loss = rl / (float)D_MODEL;
}

/* ======================================================================
 * SECTION 14: ATTENTION FORWARD
 * ====================================================================== */

static void attention_forward(const float *x, float *out, int layer_idx, int pos, int total_kv_count) {
    int h, j, k;
    float q[D_MODEL], kv_k[N_KV_HEADS * D_HEAD], kv_v[N_KV_HEADS * D_HEAD];

    /* Q projection */
    matvec(W.layers[layer_idx].q_proj, x, q, D_MODEL, D_MODEL);

    /* K projection */
    matvec(W.layers[layer_idx].k_proj, x, kv_k, N_KV_HEADS * D_HEAD, D_MODEL);

    /* V projection */
    matvec(W.layers[layer_idx].v_proj, x, kv_v, N_KV_HEADS * D_HEAD, D_MODEL);

    /* Apply RoPE to Q */

    /* Apply RoPE to Q */
    float q_heads[N_HEADS][D_HEAD];
    for (h = 0; h < N_HEADS; h++) {
        for (j = 0; j < D_HEAD; j++) {
            float val = q[h * D_HEAD + j];
            float c = cos_cache[pos][j];
            float s = sin_cache[pos][j];
            if (j < D_HEAD / 2) {
                q_heads[h][j] = val * c - q[h * D_HEAD + j + D_HEAD/2] * s;
            } else {
                q_heads[h][j] = val * c + q[h * D_HEAD + j - D_HEAD/2] * s;
            }
        }
    }

    /* Apply RoPE to K and store in cache */
    for (h = 0; h < N_KV_HEADS; h++) {
        for (j = 0; j < D_HEAD; j++) {
            float val = kv_k[h * D_HEAD + j];
            float c = cos_cache[pos][j];
            float s = sin_cache[pos][j];
            float rotated;
            if (j < D_HEAD / 2) {
                rotated = val * c - kv_k[h * D_HEAD + j + D_HEAD/2] * s;
            } else {
                rotated = val * c + kv_k[h * D_HEAD + j - D_HEAD/2] * s;
            }
            kv_cache_k[layer_idx][pos][h * D_HEAD + j] = rotated;
        }
        for (j = 0; j < D_HEAD; j++) {
            kv_cache_v[layer_idx][pos][h * D_HEAD + j] = kv_v[h * D_HEAD + j];
        }
    }

    /* Compute attention: expand KV heads to match Q heads (GQA) */
    float scale = 1.0f / tg_sqrt((float)D_HEAD);
    float temp = W.layers[layer_idx].temperature[0];
    if (tg_fabs(temp) > 1e-6f) scale /= tg_fabs(temp);

    float attn_scores[MAX_SEQ_LEN];
    float attn_out[D_HEAD];

    for (h = 0; h < N_HEADS; h++) {
        int kv_head = h / GQA_GROUPS;

        /* Compute attention scores against all cached KV positions */
        int kv_count = total_kv_count;
        for (k = 0; k < kv_count; k++) {
            float score = 0.0f;
            for (j = 0; j < D_HEAD; j++) {
                score += q_heads[h][j] * kv_cache_k[layer_idx][k][kv_head * D_HEAD + j];
            }
            attn_scores[k] = score * scale;

            /* Causal mask */
            if (k > pos) attn_scores[k] = -1e30f;

            /* Sliding window mask (window=128) */
            if (pos - k >= 128) attn_scores[k] = -1e30f;
        }

        softmax(attn_scores, kv_count);

        /* Weighted sum of V */
        for (j = 0; j < D_HEAD; j++) {
            attn_out[j] = 0.0f;
            for (k = 0; k < kv_count; k++) {
                attn_out[j] += attn_scores[k] * kv_cache_v[layer_idx][k][kv_head * D_HEAD + j];
            }
        }

        /* Copy to output */
        for (j = 0; j < D_HEAD; j++) {
            att_out[h * D_HEAD + j] = attn_out[j];
        }
    }

    /* O projection */
    matvec(W.layers[layer_idx].o_proj, att_out, out, D_MODEL, D_MODEL);
}

/* ======================================================================
 * SECTION 15: MoE ROUTING
 * ====================================================================== */

static void moe_forward(const float *x, float *out, const LayerWeights *lw) {
    float router_probs[N_EXPERTS];
    int i, j;

    /* Router logits */
    matvec(lw->router, x, router_probs, N_EXPERTS, D_MODEL);
    softmax(router_probs, N_EXPERTS);

    /* Top-K selection */
    int top_k = MOE_TOP_K;
    int top_idx[N_EXPERTS];
    float top_val[N_EXPERTS];
    for (i = 0; i < N_EXPERTS; i++) { top_idx[i] = i; top_val[i] = router_probs[i]; }
    for (i = 0; i < top_k; i++) {
        for (j = i + 1; j < N_EXPERTS; j++) {
            if (top_val[j] > top_val[i]) {
                float tv = top_val[i]; top_val[i] = top_val[j]; top_val[j] = tv;
                int ti = top_idx[i]; top_idx[i] = top_idx[j]; top_idx[j] = ti;
            }
        }
    }
    float top_sum = 0.0f;
    for (i = 0; i < top_k; i++) top_sum += top_val[i];
    for (i = 0; i < top_k; i++) top_val[i] /= (top_sum + 1e-9f);

    /* Initialize output */
    for (j = 0; j < D_MODEL; j++) out[j] = 0.0f;

    /* Run top-K experts and accumulate */
    for (i = 0; i < top_k; i++) {
        int e = top_idx[i];
        float w = top_val[i];
        float expert_out[D_MODEL];
        swiglu(lw->gate_proj[e], lw->up_proj[e], lw->down_proj[e],
               x, expert_out, D_MODEL, EXPERT_INNER);
        for (j = 0; j < D_MODEL; j++) out[j] += w * expert_out[j];
    }
}

/* ======================================================================
 * SECTION 16: FULL MODEL FORWARD
 *
 * Processes tokens autoregressively through all layers.
 * Each token position goes through ALL layers before the next position.
 * This is the correct order: layer 0 must see all positions before
 * layer 1 can process them.
 *
 * After processing, logits_out holds logits for the LAST position only.
 * ====================================================================== */

static void forward(const int *token_ids, int seq_len, float *logits_out) {
    int i, j, l;

    for (i = 0; i < seq_len; i++) {
        int cur_pos = kv_len + i;
        int cur_kv_count = kv_len + i + 1; /* positions in cache including current */

        /* Embed this token */
        for (j = 0; j < D_MODEL; j++) {
            x_buf[j] = W.token_embed[token_ids[i] * D_MODEL + j];
        }

        /* Process through all layers */
        for (l = 0; l < N_LAYERS; l++) {
            LayerWeights *lw = &W.layers[l];

            /* Pre-norm + Attention */
            float normed[D_MODEL];
            rmsnorm(x_buf, lw->norm1, normed, D_MODEL);
            float attn_out[D_MODEL];
            attention_forward(normed, attn_out, l, cur_pos, cur_kv_count);
            for (j = 0; j < D_MODEL; j++) x_buf[j] += attn_out[j];

            /* Pre-norm + TopoMoEBrain */
            rmsnorm(x_buf, lw->norm2, normed, D_MODEL);
            float brain_out[D_MODEL];
            float rl;
            torus_brain_forward(normed, brain_out, &rl, lw);

            /* MoE: shared expert + routed experts */
            float expert_out[D_MODEL];
            moe_forward(normed, expert_out, lw);
            for (j = 0; j < D_MODEL; j++) brain_out[j] += expert_out[j];

            for (j = 0; j < D_MODEL; j++) x_buf[j] += brain_out[j];
        }
    }

    kv_len += seq_len;

    /* Final norm */
    float normed[D_MODEL];
    rmsnorm(x_buf, W.final_norm, normed, D_MODEL);

    /* LM head (tied with token_embed) - logits for last position only */
    matvec(W.token_embed, normed, logits_out, VOCAB_SIZE, D_MODEL);
}

/* ======================================================================
 * SECTION 17: TOKENIZER (simple byte-level hash table)
 *
 * NOTE: This is a simplified byte-level tokenizer. For best results with
 * GPT-2 BPE models, use the Python tokenize.py to pre-tokenize input
 * and pass binary token IDs with the -T flag.
 * ====================================================================== */

/* Simple hash-based tokenizer mapping bytes/strings to token IDs.
 * For a proper BPE tokenizer, use the Python helper to pre-tokenize. */
static int tokenize_byte(unsigned char b) {
    /* GPT-2 byte encoding: maps byte values to printable characters */
    int n = (int)b;
    if (n >= 33 && n <= 126) return n - 33;
    if (n >= 161) return n - 161 + 94;
    if (n >= 173) return n - 173 + 163;
    return n + 190;
}

static int tokenize_string(const char *text, int *tokens, int max_tokens) {
    int pos = 0;
    int tcount = 0;
    while (text[pos] && tcount < max_tokens) {
        unsigned char b = (unsigned char)text[pos];
        tokens[tcount++] = tokenize_byte(b);
        pos++;
    }
    return tcount;
}

/* ======================================================================
 * SECTION 18: SAMPLING
 * ====================================================================== */

static void apply_temperature(float *logits, int n, float temp) {
    int i;
    float t = temp > 1e-6f ? temp : 1e-6f;
    for (i = 0; i < n; i++) logits[i] /= t;
}

static void apply_repetition_penalty(float *logits, int n, const int *tokens,
                                      int n_tokens, float penalty) {
    int i;
    if (penalty <= 1.0f) return;
    for (i = 0; i < n_tokens; i++) {
        int tid = tokens[i];
        if (tid >= 0 && tid < n) {
            if (logits[tid] > 0) logits[tid] /= penalty;
            else logits[tid] *= penalty;
        }
    }
}

static void apply_top_k(float *logits, int n, int k) {
    int i, j;
    if (k <= 0 || k >= n) return;
    float vals[n];
    for (i = 0; i < n; i++) vals[i] = logits[i];
    /* Partial sort to find k-th largest */
    for (i = 0; i < k; i++) {
        for (j = i + 1; j < n; j++) {
            if (vals[j] > vals[i]) {
                float t = vals[i]; vals[i] = vals[j]; vals[j] = t;
            }
        }
    }
    float threshold = vals[k - 1];
    for (i = 0; i < n; i++) {
        if (logits[i] < threshold) logits[i] = -1e30f;
    }
}

static int sample(const float *logits, int n) {
    /* Softmax + multinomial */
    float probs[n];
    float mx = logits[0];
    int i;
    for (i = 1; i < n; i++) if (logits[i] > mx) mx = logits[i];
    float s = 0.0f;
    for (i = 0; i < n; i++) { probs[i] = tg_exp(logits[i] - mx); s += probs[i]; }
    for (i = 0; i < n; i++) probs[i] /= s;

    /* Simple PRNG (xorshift32) */
    static unsigned int rng_state = 42;
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    float r = (float)(rng_state & 0xFFFF) / 65536.0f;

    float cum = 0.0f;
    for (i = 0; i < n; i++) {
        cum += probs[i];
        if (r <= cum) return i;
    }
    return n - 1;
}

/* ======================================================================
 * SECTION 19: WEIGHT LOADER
 *
 * Reads the binary file produced by convert_weights.py.
 * The converter writes tensors in a fixed order. We read them in the same
 * order, matching each to its destination buffer by position. No string
 * parsing needed.
 * ====================================================================== */

static int load_weights(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;

    char magic[4];
    if (fread(magic, 1, 4, f) != 4 || magic[0] != 'T' || magic[1] != 'G'
        || magic[2] != '3' || magic[3] != 'W') {
        fclose(f);
        return -1;
    }

    unsigned int version, n_tensors;
    if (fread(&version, 4, 1, f) != 1) { fclose(f); return -1; }
    if (fread(&n_tensors, 4, 1, f) != 1) { fclose(f); return -1; }

    printf("Loading %u tensors (v%u)...\n", n_tensors, version);

    /* Skip tensor: read header + data and discard */
    #define SKIP_TENSOR() do { \
        unsigned int nl, nd, tot = 1, dd; \
        if (fread(&nl, 4, 1, f) != 1) { fclose(f); return -1; } \
        if (fseek(f, nl, SEEK_CUR) != 0) { fclose(f); return -1; } \
        if (fread(&nd, 4, 1, f) != 1) { fclose(f); return -1; } \
        for (dd = 0; dd < nd; dd++) { unsigned int d; fread(&d, 4, 1, f); tot *= d; } \
        if (fseek(f, tot * 4, SEEK_CUR) != 0) { fclose(f); return -1; } \
    } while(0)

    /* Read one tensor into dest buffer */
    #define READ_TENSOR(dest, count) do { \
        unsigned int nl, nd, tot = 1, dd; \
        if (fread(&nl, 4, 1, f) != 1) { fclose(f); return -1; } \
        if (fseek(f, nl, SEEK_CUR) != 0) { fclose(f); return -1; } \
        if (fread(&nd, 4, 1, f) != 1) { fclose(f); return -1; } \
        for (dd = 0; dd < nd; dd++) { unsigned int d; fread(&d, 4, 1, f); tot *= d; } \
        if (tot != (count)) { \
            printf("Shape mismatch for tensor: expected %u, got %u\n", (unsigned)(count), tot); \
            fclose(f); return -1; \
        } \
        if (fread((dest), 4, tot, f) != tot) { fclose(f); return -1; } \
    } while(0)

    int i, j;

    /* token_embed.weight: [50257, 256] */
    READ_TENSOR(W.token_embed, VOCAB_SIZE * D_MODEL);

    for (i = 0; i < N_LAYERS; i++) {
        LayerWeights *lw = &W.layers[i];

        /* norms */
        READ_TENSOR(lw->norm1, D_MODEL);
        READ_TENSOR(lw->norm2, D_MODEL);

        /* attention projections */
        READ_TENSOR(lw->q_proj, D_MODEL * D_MODEL);
        READ_TENSOR(lw->k_proj, N_KV_HEADS * D_HEAD * D_MODEL);
        READ_TENSOR(lw->v_proj, N_KV_HEADS * D_HEAD * D_MODEL);
        READ_TENSOR(lw->o_proj, D_MODEL * D_MODEL);
        READ_TENSOR(lw->temperature, 1);

        /* spectral autoencoder 1D kernels */
        READ_TENSOR(lw->enc_kr, D_MODEL / 2 + 1);
        READ_TENSOR(lw->enc_ki, D_MODEL / 2 + 1);
        READ_TENSOR(lw->dec_kr, D_MODEL / 2 + 1);
        READ_TENSOR(lw->dec_ki, D_MODEL / 2 + 1);

        /* spectral autoencoder quaternion projections */
        READ_TENSOR(lw->ae_ww, D_LAT_Q * D_QUAT);
        READ_TENSOR(lw->ae_wx, D_LAT_Q * D_QUAT);
        READ_TENSOR(lw->ae_wy, D_LAT_Q * D_QUAT);
        READ_TENSOR(lw->ae_wz, D_LAT_Q * D_QUAT);
        READ_TENSOR(lw->de_ww, D_QUAT * D_LAT_Q);
        READ_TENSOR(lw->de_wx, D_QUAT * D_LAT_Q);
        READ_TENSOR(lw->de_wy, D_QUAT * D_LAT_Q);
        READ_TENSOR(lw->de_wz, D_QUAT * D_LAT_Q);

        /* spectral 2D layers (2 layers) */
        for (j = 0; j < N_SPECTRAL_LAYERS; j++) {
            int sz = D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W;
            READ_TENSOR(lw->kr_w[j], sz);
            READ_TENSOR(lw->ki_w[j], sz);
            READ_TENSOR(lw->kr_x[j], sz);
            READ_TENSOR(lw->ki_x[j], sz);
            READ_TENSOR(lw->kr_y[j], sz);
            READ_TENSOR(lw->ki_y[j], sz);
            READ_TENSOR(lw->kr_z[j], sz);
            READ_TENSOR(lw->ki_z[j], sz);
        }

        /* torus projection */
        READ_TENSOR(lw->tp_ww, D_QUAT * D_QUAT);
        READ_TENSOR(lw->tp_wx, D_QUAT * D_QUAT);
        READ_TENSOR(lw->tp_wy, D_QUAT * D_QUAT);
        READ_TENSOR(lw->tp_wz, D_QUAT * D_QUAT);
        READ_TENSOR(lw->tp_lin, D_MODEL * 4);

        /* node/edge embeddings */
        READ_TENSOR(lw->node_embed, N_NODES * D_MODEL);
        READ_TENSOR(lw->edge_quat, N_EDGE_TYPES * 4);

        /* message passing */
        READ_TENSOR(lw->mp_ww, D_QUAT * D_QUAT);
        READ_TENSOR(lw->mp_wx, D_QUAT * D_QUAT);
        READ_TENSOR(lw->mp_wy, D_QUAT * D_QUAT);
        READ_TENSOR(lw->mp_wz, D_QUAT * D_QUAT);

        /* readout */
        READ_TENSOR(lw->ro_w1, READOUT_INNER * D_MODEL);
        READ_TENSOR(lw->ro_b1, READOUT_INNER);
        READ_TENSOR(lw->ro_w2, D_MODEL * READOUT_INNER);
        READ_TENSOR(lw->ro_b2, D_MODEL);

        /* MoE experts */
        for (j = 0; j < N_EXPERTS; j++) {
            READ_TENSOR(lw->gate_proj[j], EXPERT_INNER * D_MODEL);
        }
        for (j = 0; j < N_EXPERTS; j++) {
            READ_TENSOR(lw->up_proj[j], EXPERT_INNER * D_MODEL);
        }
        for (j = 0; j < N_EXPERTS; j++) {
            READ_TENSOR(lw->down_proj[j], D_MODEL * EXPERT_INNER);
        }

        /* MoE router */
        READ_TENSOR(lw->router, N_EXPERTS * D_MODEL);

        printf("  Layer %d loaded\n", i);
    }

    /* final_norm */
    READ_TENSOR(W.final_norm, D_MODEL);

    #undef SKIP_TENSOR
    #undef READ_TENSOR

    fclose(f);
    printf("Weights loaded successfully.\n");
    return 0;
}

/* ======================================================================
 * SECTION 19b: FLOAT16 WEIGHT LOADING (MiniOS compact format)
 *
 * Reads TG16 format: float16 weights that convert to float32 on load.
 * Saves ~50% disk space (47MB vs 94MB) for MiniFS.
 * ====================================================================== */

static float fp16_to_fp32(unsigned short h) {
    unsigned int sign = (h >> 15) & 1;
    unsigned int exp  = (h >> 10) & 0x1f;
    unsigned int mant = h & 0x3ff;
    unsigned int f;
    if (exp == 0) {
        if (mant == 0) { f = sign << 31; }
        else { /* denormalized */
            exp = 1;
            while (!(mant & 0x400)) { mant <<= 1; exp--; }
            mant &= 0x3ff;
            f = (sign << 31) | ((exp + 127 - 15) << 23) | (mant << 13);
        }
    } else if (exp == 31) {
        f = (sign << 31) | 0x7f800000 | (mant << 13);
    } else {
        f = (sign << 31) | ((exp + 127 - 15) << 23) | (mant << 13);
    }
    float result;
    memcpy(&result, &f, 4);
    return result;
}

static int load_weights_fp16(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;

    char magic[4];
    if (fread(magic, 1, 4, f) != 4 || magic[0] != 'T' || magic[1] != 'G'
        || magic[2] != '1' || magic[3] != '6') {
        fclose(f);
        return -1;
    }

    unsigned int version, n_tensors;
    if (fread(&version, 4, 1, f) != 1) { fclose(f); return -1; }
    if (fread(&n_tensors, 4, 1, f) != 1) { fclose(f); return -1; }

    printf("Loading %u tensors (fp16 v%u)...\n", n_tensors, version);

    /* Skip tensor: read header + fp16 data and discard */
    #define SKIP_TENSOR16() do { \
        unsigned int nl, nd, tot = 1, dd; \
        if (fread(&nl, 4, 1, f) != 1) { fclose(f); return -1; } \
        if (fseek(f, nl, SEEK_CUR) != 0) { fclose(f); return -1; } \
        if (fread(&nd, 4, 1, f) != 1) { fclose(f); return -1; } \
        for (dd = 0; dd < nd; dd++) { unsigned int d; fread(&d, 4, 1, f); tot *= d; } \
        if (fseek(f, tot * 2, SEEK_CUR) != 0) { fclose(f); return -1; } \
    } while(0)

    /* Read fp16 tensor into float32 dest buffer, converting on the fly */
    #define READ_TENSOR16(dest, count) do { \
        unsigned int nl, nd, tot = 1, dd; \
        if (fread(&nl, 4, 1, f) != 1) { fclose(f); return -1; } \
        if (fseek(f, nl, SEEK_CUR) != 0) { fclose(f); return -1; } \
        if (fread(&nd, 4, 1, f) != 1) { fclose(f); return -1; } \
        for (dd = 0; dd < nd; dd++) { unsigned int d; fread(&d, 4, 1, f); tot *= d; } \
        if (tot != (count)) { \
            printf("Shape mismatch: expected %u, got %u\n", (unsigned)(count), tot); \
            fclose(f); return -1; \
        } \
        { unsigned int _ii; \
          unsigned short *_buf = (unsigned short *)malloc(tot * 2); \
          if (!_buf) { printf("OOM reading tensor\n"); fclose(f); return -1; } \
          if (fread(_buf, 2, tot, f) != tot) { free(_buf); fclose(f); return -1; } \
          for (_ii = 0; _ii < tot; _ii++) \
              ((float *)(dest))[_ii] = fp16_to_fp32(_buf[_ii]); \
          free(_buf); \
        } \
    } while(0)

    int i, j;

    READ_TENSOR16(W.token_embed, VOCAB_SIZE * D_MODEL);

    for (i = 0; i < N_LAYERS; i++) {
        LayerWeights *lw = &W.layers[i];

        READ_TENSOR16(lw->norm1, D_MODEL);
        READ_TENSOR16(lw->norm2, D_MODEL);
        READ_TENSOR16(lw->q_proj, D_MODEL * D_MODEL);
        READ_TENSOR16(lw->k_proj, N_KV_HEADS * D_HEAD * D_MODEL);
        READ_TENSOR16(lw->v_proj, N_KV_HEADS * D_HEAD * D_MODEL);
        READ_TENSOR16(lw->o_proj, D_MODEL * D_MODEL);
        READ_TENSOR16(lw->temperature, 1);

        READ_TENSOR16(lw->enc_kr, D_MODEL / 2 + 1);
        READ_TENSOR16(lw->enc_ki, D_MODEL / 2 + 1);
        READ_TENSOR16(lw->dec_kr, D_MODEL / 2 + 1);
        READ_TENSOR16(lw->dec_ki, D_MODEL / 2 + 1);

        READ_TENSOR16(lw->ae_ww, D_LAT_Q * D_QUAT);
        READ_TENSOR16(lw->ae_wx, D_LAT_Q * D_QUAT);
        READ_TENSOR16(lw->ae_wy, D_LAT_Q * D_QUAT);
        READ_TENSOR16(lw->ae_wz, D_LAT_Q * D_QUAT);
        READ_TENSOR16(lw->de_ww, D_QUAT * D_LAT_Q);
        READ_TENSOR16(lw->de_wx, D_QUAT * D_LAT_Q);
        READ_TENSOR16(lw->de_wy, D_QUAT * D_LAT_Q);
        READ_TENSOR16(lw->de_wz, D_QUAT * D_LAT_Q);

        for (j = 0; j < N_SPECTRAL_LAYERS; j++) {
            int sz = D_QUAT * D_QUAT * TORUS_GRID_H * FREQ_W;
            READ_TENSOR16(lw->kr_w[j], sz);
            READ_TENSOR16(lw->ki_w[j], sz);
            READ_TENSOR16(lw->kr_x[j], sz);
            READ_TENSOR16(lw->ki_x[j], sz);
            READ_TENSOR16(lw->kr_y[j], sz);
            READ_TENSOR16(lw->ki_y[j], sz);
            READ_TENSOR16(lw->kr_z[j], sz);
            READ_TENSOR16(lw->ki_z[j], sz);
        }

        READ_TENSOR16(lw->tp_ww, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->tp_wx, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->tp_wy, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->tp_wz, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->tp_lin, D_MODEL * 4);

        READ_TENSOR16(lw->node_embed, N_NODES * D_MODEL);
        READ_TENSOR16(lw->edge_quat, N_EDGE_TYPES * 4);

        READ_TENSOR16(lw->mp_ww, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->mp_wx, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->mp_wy, D_QUAT * D_QUAT);
        READ_TENSOR16(lw->mp_wz, D_QUAT * D_QUAT);

        READ_TENSOR16(lw->ro_w1, READOUT_INNER * D_MODEL);
        READ_TENSOR16(lw->ro_b1, READOUT_INNER);
        READ_TENSOR16(lw->ro_w2, D_MODEL * READOUT_INNER);
        READ_TENSOR16(lw->ro_b2, D_MODEL);

        for (j = 0; j < N_EXPERTS; j++)
            READ_TENSOR16(lw->gate_proj[j], EXPERT_INNER * D_MODEL);
        for (j = 0; j < N_EXPERTS; j++)
            READ_TENSOR16(lw->up_proj[j], EXPERT_INNER * D_MODEL);
        for (j = 0; j < N_EXPERTS; j++)
            READ_TENSOR16(lw->down_proj[j], D_MODEL * EXPERT_INNER);

        READ_TENSOR16(lw->router, N_EXPERTS * D_MODEL);

        printf("  Layer %d loaded\n", i);
    }

    READ_TENSOR16(W.final_norm, D_MODEL);

    #undef SKIP_TENSOR16
    #undef READ_TENSOR16

    fclose(f);
    printf("Weights loaded successfully (fp16).\n");
    return 0;
}

/* Auto-detect format and load weights */
static int load_weights_auto(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    char magic[4];
    if (fread(magic, 1, 4, f) != 4) { fclose(f); return -1; }
    fclose(f);

    if (magic[0] == 'T' && magic[1] == 'G' && magic[2] == '1' && magic[3] == '6')
        return load_weights_fp16(path);
    return load_weights(path);
}

/* ======================================================================
 * SECTION 20: TIMING
 * ====================================================================== */

/* Portable wall-clock timer using rdtsc where available, else microseconds */
static double time_now_ms(void) {
    /* x86-64 rdtsc: counts CPU cycles since boot.
     * Convert to milliseconds assuming ~2.5 GHz base clock.
     * Works on both Linux and MiniOS (both run on x86-64). */
    unsigned int lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    unsigned long long tsc = ((unsigned long long)hi << 32) | lo;
    return (double)tsc / 2500000.0;  /* cycles -> ms at 2.5 GHz */
}

/* ======================================================================
 * SECTION 21: GENERATION
 * ====================================================================== */

static void decode_token(int tid) {
    if (tid < 256) {
        /* Map GPT-2 byte-level encoding back to original byte */
        int n = tid;
        if (n < 94) n += 33;
        else if (n < 163) n += 161 - 94;
        else n += 173 - 163;
        putchar(n);
    } else {
        /* Multi-byte token: output placeholder or skip */
        putchar('?');
    }
}

/* Load pre-tokenized binary file (format: "TKID" + uint32 count + int32 ids[]) */
static int load_token_file(const char *path, int *out_ids, int max_ids) {
    FILE *f = fopen(path, "rb");
    if (!f) { printf("Error: cannot open %s\n", path); return 0; }
    char magic[4];
    if (fread(magic, 1, 4, f) != 4 || memcmp(magic, "TKID", 4) != 0) {
        printf("Error: %s is not a valid token file (bad magic)\n", path);
        fclose(f); return 0;
    }
    unsigned int n;
    if (fread(&n, 4, 1, f) != 1) { fclose(f); return 0; }
    if (n > (unsigned)max_ids) n = max_ids;
    int count = (int)n;
    int i;
    for (i = 0; i < count; i++) {
        int id;
        if (fread(&id, 4, 1, f) != 1) break;
        out_ids[i] = id;
    }
    fclose(f);
    return count;
}

/* Decode token ID using loaded vocabulary */
static void decode_token_tiktoken(int tid) {
    if (tid >= 0 && tid < vocab_count && vocab_len[tid] > 0) {
        fwrite(vocab_data[tid], 1, vocab_len[tid], stdout);
        return;
    }
    /* Fallback: show token ID */
    printf("<%d>", tid);
}

static void generate_tokens(int *prompt_tokens, int n_prompt, int max_new_tokens,
                            float temperature, int top_k, float rep_penalty) {
    if (n_prompt == 0) {
        printf("Error: empty prompt\n");
        return;
    }

    printf("Prompt: %d tokens\n", n_prompt);
    printf("---\n");
    fflush(stdout);

    int all_tokens[MAX_TOKENS];
    int total = 0;
    int i;
    for (i = 0; i < n_prompt && i < MAX_TOKENS; i++) {
        all_tokens[i] = prompt_tokens[i];
        total++;
    }

    kv_len = 0;

    double t_start = time_now_ms();

    forward(all_tokens, n_prompt, logits);

    float logits_copy[VOCAB_SIZE];
    for (i = 0; i < VOCAB_SIZE; i++) logits_copy[i] = logits[i];
    apply_temperature(logits_copy, VOCAB_SIZE, temperature);
    apply_repetition_penalty(logits_copy, VOCAB_SIZE, all_tokens, total, rep_penalty);
    apply_top_k(logits_copy, VOCAB_SIZE, top_k);
    int next_token = sample(logits_copy, VOCAB_SIZE);
    all_tokens[total++] = next_token;
    decode_token_tiktoken(next_token);
    fflush(stdout);

    int step;
    for (step = 1; step < max_new_tokens; step++) {
        int pos_tokens[1] = {next_token};
        forward(pos_tokens, 1, logits);

        for (i = 0; i < VOCAB_SIZE; i++) logits_copy[i] = logits[i];
        apply_temperature(logits_copy, VOCAB_SIZE, temperature);
        apply_repetition_penalty(logits_copy, VOCAB_SIZE, all_tokens, total, rep_penalty);
        apply_top_k(logits_copy, VOCAB_SIZE, top_k);
        next_token = sample(logits_copy, VOCAB_SIZE);

        if (next_token == EOS_TOKEN) break;
        if (total >= MAX_TOKENS) break;

        all_tokens[total++] = next_token;
        decode_token_tiktoken(next_token);
        fflush(stdout);
    }

    double t_end = time_now_ms();
    double elapsed_s = (t_end - t_start) / 1000.0;
    int n_generated = step + 1;
    double tok_per_sec = (elapsed_s > 0.001) ? (double)n_generated / elapsed_s : 0.0;

    printf("\n---\n");
    printf("Generated %d tokens in %.2fs (%.2f tok/s)\n",
           n_generated, elapsed_s, tok_per_sec);
}

static void generate(const char *prompt, int max_new_tokens, float temperature,
                      int top_k, float rep_penalty) {
    int prompt_tokens[MAX_PROMPT_LEN];
    int n_prompt = tokenize_string(prompt, prompt_tokens, MAX_PROMPT_LEN);
    generate_tokens(prompt_tokens, n_prompt, max_new_tokens, temperature, top_k, rep_penalty);
}

/* ======================================================================
 * SECTION 22: INTERACTIVE MODE
 * ====================================================================== */

static void interactive_mode(void) {
    char line[MAX_LINE];
    char prompt_buf[MAX_PROMPT_LEN];
    int prompt_len = 0;

    printf("TopoGPT3 Interactive Mode\n");
    printf("Type your prompt, press Enter to generate.\n");
    printf("Commands: /help /quit /clear /temp N /topk N /rep N /newtokens N\n");
    printf(">\n");

    float temperature = 0.3f;
    int top_k = 50;
    float rep_penalty = 1.1f;
    int max_new = 256;

    while (1) {
        printf("topogpt3> ");
        fflush(stdout);

        if (!fgets(line, MAX_LINE, stdin)) break;

        /* Strip newline */
        int len = 0;
        while (line[len] && line[len] != '\n') len++;
        line[len] = 0;

        if (len == 0) {
            /* Empty line = generate from accumulated prompt */
            if (prompt_len > 0) {
                prompt_buf[prompt_len] = 0;
                printf("\n[Generating with temp=%.2f top_k=%d rep=%.2f max=%d]\n",
                       temperature, top_k, rep_penalty, max_new);
                generate(prompt_buf, max_new, temperature, top_k, rep_penalty);
                prompt_len = 0;
                printf("\n");
            }
            continue;
        }

        /* Commands */
        if (line[0] == '/') {
            if (strcmp(line, "/help") == 0) {
                printf("Commands:\n");
                printf("  /help       - Show this help\n");
                printf("  /quit       - Exit\n");
                printf("  /clear      - Clear prompt buffer\n");
                printf("  /temp N     - Set temperature (default: 0.3)\n");
                printf("  /topk N     - Set top-k (default: 50)\n");
                printf("  /rep N      - Set repetition penalty (default: 1.1)\n");
                printf("  /newtokens N - Set max new tokens (default: 256)\n");
                printf("  /status     - Show current settings\n");
                printf("\nType a prompt and press Enter to generate.\n");
            } else if (strcmp(line, "/quit") == 0 || strcmp(line, "/exit") == 0) {
                break;
            } else if (strcmp(line, "/clear") == 0) {
                prompt_len = 0;
                printf("Prompt cleared.\n");
            } else if (strcmp(line, "/status") == 0) {
                printf("temp=%.2f top_k=%d rep=%.2f max_new=%d prompt_len=%d\n",
                       temperature, top_k, rep_penalty, max_new, prompt_len);
            } else if (strncmp(line, "/temp ", 6) == 0) {
                /* Parse float manually */
                float v = 0.0f;
                int sign = 1;
                const char *p = line + 6;
                if (*p == '-') { sign = -1; p++; }
                while (*p >= '0' && *p <= '9') { v = v * 10.0f + (*p - '0'); p++; }
                if (*p == '.') { p++; float d = 1.0f; while (*p >= '0' && *p <= '9') { d *= 0.1f; v += (*p - '0') * d; p++; } }
                temperature = v * sign;
                printf("temperature = %.3f\n", temperature);
            } else if (strncmp(line, "/topk ", 6) == 0) {
                top_k = 0;
                const char *p = line + 6;
                while (*p >= '0' && *p <= '9') { top_k = top_k * 10 + (*p - '0'); p++; }
                printf("top_k = %d\n", top_k);
            } else if (strncmp(line, "/rep ", 5) == 0) {
                float v = 0.0f;
                int sign = 1;
                const char *p = line + 5;
                if (*p == '-') { sign = -1; p++; }
                while (*p >= '0' && *p <= '9') { v = v * 10.0f + (*p - '0'); p++; }
                if (*p == '.') { p++; float d = 1.0f; while (*p >= '0' && *p <= '9') { d *= 0.1f; v += (*p - '0') * d; p++; } }
                rep_penalty = v * sign;
                printf("rep_penalty = %.3f\n", rep_penalty);
            } else if (strncmp(line, "/newtokens ", 11) == 0) {
                max_new = 0;
                const char *p = line + 11;
                while (*p >= '0' && *p <= '9') { max_new = max_new * 10 + (*p - '0'); p++; }
                printf("max_new_tokens = %d\n", max_new);
            } else {
                printf("Unknown command: %s (try /help)\n", line);
            }
            continue;
        }

        /* Accumulate prompt text */
        if (prompt_len + len < MAX_PROMPT_LEN - 1) {
            if (prompt_len > 0) {
                prompt_buf[prompt_len++] = '\n';
            }
            int i;
            for (i = 0; i < len; i++) prompt_buf[prompt_len++] = line[i];
            prompt_buf[prompt_len] = 0;
            printf("[Prompt: %d chars]\n", prompt_len);
        } else {
            printf("Prompt buffer full. /clear to reset.\n");
        }
    }
}

/* ======================================================================
 * SECTION 23: HELP AND MAIN
 * ====================================================================== */

static void print_help(void) {
    printf(
        "TopoGPT3 - Quaternion Topological Transformer Inference\n"
        "\n"
        "Usage:\n"
        "  topogpt3 -h                      Show this help\n"
        "  topogpt3 -p \"prompt\" [options]   Generate text (headless)\n"
        "  topogpt3 -i [options]            Interactive mode\n"
        "  topogpt3 -f file.txt [options]   Read prompt from file\n"
        "  topogpt3 -T tokens.bin           Read pre-tokenized binary IDs\n"
        "\n"
        "Options:\n"
        "  -w FILE    Weight file (default: topogpt3.weights)\n"
        "  -n NUM     Max new tokens (default: 256)\n"
        "  -t NUM     Temperature (default: 0.3)\n"
        "  -k NUM     Top-k (default: 50)\n"
        "  -r NUM     Repetition penalty (default: 1.1)\n"
        "\n"
        "Interactive mode commands:\n"
        "  /help      Show commands\n"
        "  /quit      Exit\n"
        "  /clear     Clear prompt buffer\n"
        "  /temp N    Set temperature\n"
        "  /topk N    Set top-k\n"
        "  /rep N     Set repetition penalty\n"
        "  /newtokens N  Set max new tokens\n"
        "\n"
        "Examples:\n"
        "  topogpt3 -p \"def fibonacci(n)\" -n 100 -t 0.2 -w topogpt3.fp16 -v vocab.bin\n"
        "  topogpt3 -i\n"
        "  topogpt3 -f prompt.txt -n 512\n"
        "  topogpt3 -T tokens.bin -n 100\n"
    );
}

int main(int argc, char **argv) {
    int mode = 0; /* 0=help, 1=headless, 2=interactive, 3=file, 4=tokens */
    const char *prompt = 0;
    const char *weight_file = "topogpt3.weights";
    const char *vocab_file = "vocab.bin";
    const char *input_file = 0;
    const char *token_file = 0;
    int max_new_tokens = 256;
    float temperature = 0.3f;
    int top_k = 50;
    float rep_penalty = 1.1f;

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            mode = 1;
            prompt = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0) {
            mode = 2;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            mode = 3;
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-T") == 0 && i + 1 < argc) {
            mode = 4;
            token_file = argv[++i];
        } else if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            weight_file = argv[++i];
        } else if (strcmp(argv[i], "-v") == 0 && i + 1 < argc) {
            vocab_file = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            max_new_tokens = 0;
            const char *p = argv[++i];
            while (*p >= '0' && *p <= '9') { max_new_tokens = max_new_tokens * 10 + (*p - '0'); p++; }
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            temperature = 0.0f;
            int sign = 1;
            const char *p = argv[++i];
            if (*p == '-') { sign = -1; p++; }
            while (*p >= '0' && *p <= '9') { temperature = temperature * 10.0f + (*p - '0'); p++; }
            if (*p == '.') { p++; float d = 1.0f; while (*p >= '0' && *p <= '9') { d *= 0.1f; temperature += (*p - '0') * d; p++; } }
            temperature *= sign;
        } else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc) {
            top_k = 0;
            const char *p = argv[++i];
            while (*p >= '0' && *p <= '9') { top_k = top_k * 10 + (*p - '0'); p++; }
        } else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            rep_penalty = 0.0f;
            const char *p = argv[++i];
            while (*p >= '0' && *p <= '9') { rep_penalty = rep_penalty * 10.0f + (*p - '0'); p++; }
            if (*p == '.') { p++; float d = 1.0f; while (*p >= '0' && *p <= '9') { d *= 0.1f; rep_penalty += (*p - '0') * d; p++; } }
        } else {
            /* Treat as prompt if no -p or -i given */
            if (mode == 0) {
                mode = 1;
                prompt = argv[i];
            }
        }
    }

    /* If only -w was given without -p/-i/-f, default to interactive mode */
    if (mode == 0) {
        mode = 2;
    }

    printf("TopoGPT3 Inference Engine\n");
    printf("Model: small (d=%d, heads=%d, layers=%d, kv=%d)\n",
           D_MODEL, N_HEADS, N_LAYERS, N_KV_HEADS);
    printf("Loading weights from: %s\n", weight_file);

    build_torus_graph();
    precompute_rope();
    load_vocab(vocab_file);

    if (load_weights_auto(weight_file) != 0) {
        printf("Error: failed to load weights from %s\n", weight_file);
        printf("Run convert_weights.py or convert_weights_minios.py first.\n");
        return 1;
    }

    printf("Ready.\n\n");

    if (mode == 1) {
        generate(prompt, max_new_tokens, temperature, top_k, rep_penalty);
    } else if (mode == 2) {
        interactive_mode();
    } else if (mode == 3) {
        FILE *f = fopen(input_file, "r");
        if (!f) {
            printf("Error: cannot open %s\n", input_file);
            return 1;
        }
        char buf[MAX_PROMPT_LEN];
        int total = 0;
        int c;
        while ((c = fgetc(f)) != EOF && total < MAX_PROMPT_LEN - 1) {
            buf[total++] = (char)c;
        }
        buf[total] = 0;
        fclose(f);
        generate(buf, max_new_tokens, temperature, top_k, rep_penalty);
    } else if (mode == 4) {
        int token_buf[MAX_PROMPT_LEN];
        int n_tokens = load_token_file(token_file, token_buf, MAX_PROMPT_LEN);
        if (n_tokens == 0) {
            printf("Error: no tokens loaded from %s\n", token_file);
            return 1;
        }
        generate_tokens(token_buf, n_tokens, max_new_tokens, temperature, top_k, rep_penalty);
    }

    return 0;
}
