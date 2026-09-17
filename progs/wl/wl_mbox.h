/** wl_mbox.h - Mailbox file transport for Wayland-mini (ADR-0026).
 *
 * Interim carrier needing zero kernel changes: one wire message per
 * file under WL_MBOX_DIR, pixels beside it in a .raw file. The kernel
 * already creates through the MiniFS fallback, unlinks through nr 87
 * and lists through DIR_LIST, and every ring-3 file flow proves the
 * primitives, so this header only owns names, frames and the box to
 * surface map. File bytes stay in the caller (stdio in wlcomp.c);
 * everything here is pure and host-tested. One surface maps per
 * connection: the box owns its slot, which bounds the server without
 * an id translation table. Every bound fails closed.
 */

#ifndef WL_MBOX_H
#define WL_MBOX_H

#include "wl_mini.h"

#define WL_MBOX_DIR "/shm/wl"
#define WL_MBOX_SUFFIX ".msg"
#define WL_MBOX_RAW_SUFFIX ".raw"
#define WL_MBOX_EV_SUFFIX ".ev"
#define WL_MBOX_BOX_MAX 17
#define WL_MBOX_NAME_MAX 64
#define WL_MBOX_MAGIC 0x424D4C57u
#define WL_MBOX_FRAME_HEAD 8
#define WL_MBOX_POLL_MAX 64
#define WL_MBOX_SEQ_HEX 8

typedef struct {
    char box[WL_MBOX_BOX_MAX];
    unsigned int seq_last;
    int used;
} wl_mbox_box_t;

static inline void wl_mbox_init(wl_mbox_box_t *boxes) {
    int i;
    int k;
    if (!boxes)
        return;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        for (k = 0; k < WL_MBOX_BOX_MAX; k++)
            boxes[i].box[k] = 0;
        boxes[i].seq_last = 0;
        boxes[i].used = 0;
    }
}

/** Box names are lowercase alphanumerics so they can never escape the
 * directory through dot or slash tricks. */
static inline int wl_mbox_box_ok(const char *box) {
    int n = 0;
    if (!box)
        return WL_ERR_STR;
    while (box[n] != '\0') {
        char ch = box[n];
        int ok = 0;
        if (ch >= 'a' && ch <= 'z')
            ok = 1;
        if (ch >= '0' && ch <= '9')
            ok = 1;
        if (!ok)
            return WL_ERR_STR;
        n++;
        if (n >= WL_MBOX_BOX_MAX)
            return WL_ERR_STR;
    }
    if (n == 0)
        return WL_ERR_STR;
    return WL_ERR_OK;
}

/** Sequence as fixed 8 lowercase hex so names sort chronologically. */
static inline int wl_mbox_hex(unsigned int v, char *dst) {
    int i;
    static const char digits[] = "0123456789abcdef";
    if (!dst)
        return WL_ERR_BOUND;
    for (i = 0; i < WL_MBOX_SEQ_HEX; i++) {
        dst[WL_MBOX_SEQ_HEX - 1 - i] =
            digits[v & 0xFu];
        v >>= 4;
    }
    return WL_ERR_OK;
}

static inline int wl_mbox_unhex(char ch, unsigned int *v) {
    if (!v)
        return WL_ERR_STR;
    if (ch >= '0' && ch <= '9') {
        *v = (unsigned int)(ch - '0');
        return WL_ERR_OK;
    }
    if (ch >= 'a' && ch <= 'f') {
        *v = (unsigned int)(ch - 'a') + 10u;
        return WL_ERR_OK;
    }
    return WL_ERR_STR;
}

/** Build WL_MBOX_DIR/box-seq.msg. Returns the length, never a prefix
 * of it, so a short buffer reads as an error and not a stray file. */
static inline int wl_mbox_name(char *dst, int cap, const char *box,
        unsigned int seq) {
    int di = 0;
    int i = 0;
    static const char dir[] = WL_MBOX_DIR "/";
    static const char suf[] = WL_MBOX_SUFFIX;
    char hex[WL_MBOX_SEQ_HEX];
    if (!dst || !box || cap <= 0)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    if (wl_mbox_hex(seq, hex) != WL_ERR_OK)
        return WL_ERR_BOUND;
    while (dir[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = dir[i++];
    }
    i = 0;
    while (box[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = box[i++];
    }
    if (di >= cap - 1)
        return WL_ERR_BOUND;
    dst[di++] = '-';
    for (i = 0; i < WL_MBOX_SEQ_HEX; i++) {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = hex[i];
    }
    i = 0;
    while (suf[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = suf[i++];
    }
    dst[di] = '\0';
    return di;
}

/** Parse a mailbox path back into box plus sequence. Only exact
 * matches pass; a renamed stray or a foreign suffix never dispatches. */
static inline int wl_mbox_parse(const char *path, char *box, int boxcap,
        unsigned int *seq) {
    int dirlen = 8;
    int n = 0;
    int i;
    unsigned int v = 0;
    unsigned int d = 0;
    static const char dir[] = WL_MBOX_DIR "/";
    static const char suf[] = WL_MBOX_SUFFIX;
    if (!path || !box || !seq || boxcap <= 0)
        return WL_ERR_BOUND;
    for (i = 0; i < dirlen; i++) {
        if (path[i] != dir[i])
            return WL_ERR_STR;
    }
    path += dirlen;
    while (path[n] != '\0' && path[n] != '-')
        n++;
    if (path[n] != '-' || n == 0 || n >= WL_MBOX_BOX_MAX)
        return WL_ERR_STR;
    if (n + 1 >= boxcap)
        return WL_ERR_BOUND;
    for (i = 0; i < n; i++)
        box[i] = path[i];
    box[n] = '\0';
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    path += n + 1;
    for (i = 0; i < WL_MBOX_SEQ_HEX; i++) {
        if (wl_mbox_unhex(path[i], &d) != WL_ERR_OK)
            return WL_ERR_STR;
        v = (v << 4) | d;
    }
    path += WL_MBOX_SEQ_HEX;
    i = 0;
    while (suf[i] != '\0') {
        if (path[i] != suf[i])
            return WL_ERR_STR;
        i++;
    }
    if (path[i] != '\0')
        return WL_ERR_STR;
    *seq = v;
    return WL_ERR_OK;
}

/** Raw pixel path beside the mailbox, sized w*h by the last attach. */
static inline int wl_mbox_raw_name(char *dst, int cap, const char *box) {
    int di = 0;
    int i = 0;
    static const char dir[] = WL_MBOX_DIR "/";
    static const char suf[] = WL_MBOX_RAW_SUFFIX;
    if (!dst || !box || cap <= 0)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    while (dir[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = dir[i++];
    }
    i = 0;
    while (box[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = box[i++];
    }
    i = 0;
    while (suf[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = suf[i++];
    }
    dst[di] = '\0';
    return di;
}

/** Event path beside the mailbox, one fixed frame per focused box. */
static inline int wl_mbox_ev_name(char *dst, int cap, const char *box) {
    int di = 0;
    int i = 0;
    static const char dir[] = WL_MBOX_DIR "/";
    static const char suf[] = WL_MBOX_EV_SUFFIX;
    if (!dst || !box || cap <= 0)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    while (dir[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = dir[i++];
    }
    i = 0;
    while (box[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = box[i++];
    }
    i = 0;
    while (suf[i] != '\0') {
        if (di >= cap - 1)
            return WL_ERR_BOUND;
        dst[di++] = suf[i++];
    }
    dst[di] = '\0';
    return di;
}

/** Client box name: lowercase alnum program plus decimal pid, so two
 * instances of one app never share a mailbox. Pure, host-tested. */
static inline int wl_client_box(const char *prog, long pid, char *dst,
        int cap) {
    int o = 0;
    int i = 0;
    long p = 0;
    char digits[20];
    int nd = 0;
    if (!prog || !dst || cap <= 0)
        return WL_ERR_BOUND;
    if (pid < 0)
        return WL_ERR_BOUND;
    while (prog[i] != '\0' && o + 1 < cap && o < 16) {
        char ch = prog[i];
        if (ch >= 'A' && ch <= 'Z')
            ch = (char)(ch + ('a' - 'A'));
        if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            dst[o++] = ch;
        i++;
        if (i > 64)
            break;
    }
    if (o == 0 && cap > 6) {
        dst[0] = 'n';
        dst[1] = 'k';
        dst[2] = 'a';
        dst[3] = 'p';
        dst[4] = 'p';
        o = 5;
    }
    p = pid;
    if (p == 0) {
        if (o + 1 >= cap)
            return WL_ERR_BOUND;
        dst[o++] = '0';
    } else {
        while (p > 0 && nd < 20) {
            digits[nd++] = (char)('0' + (p % 10));
            p /= 10;
        }
        if (o + nd >= cap)
            return WL_ERR_BOUND;
        while (nd > 0)
            dst[o++] = digits[--nd];
    }
    dst[o] = '\0';
    if (wl_mbox_box_ok(dst) != WL_ERR_OK)
        return WL_ERR_STR;
    return WL_ERR_OK;
}

/** Frame one wire message: magic plus sequence plus the raw message.
 * The reader refuses anything short, anything foreign and anything
 * with trailing bytes, so a torn write waits for the next poll. */
static inline int wl_mbox_frame_encode(unsigned char *dst, int cap,
        unsigned int seq, const unsigned char *msg, int mlen) {
    int i;
    if (!dst || !msg)
        return WL_ERR_BOUND;
    if (mlen < WL_HDR_SZ || mlen > WL_MAX_MSG)
        return WL_ERR_BOUND;
    if (cap - mlen < WL_MBOX_FRAME_HEAD)
        return WL_ERR_BOUND;
    dst[0] = (unsigned char)(WL_MBOX_MAGIC & 0xFFu);
    dst[1] = (unsigned char)((WL_MBOX_MAGIC >> 8) & 0xFFu);
    dst[2] = (unsigned char)((WL_MBOX_MAGIC >> 16) & 0xFFu);
    dst[3] = (unsigned char)((WL_MBOX_MAGIC >> 24) & 0xFFu);
    dst[4] = (unsigned char)(seq & 0xFFu);
    dst[5] = (unsigned char)((seq >> 8) & 0xFFu);
    dst[6] = (unsigned char)((seq >> 16) & 0xFFu);
    dst[7] = (unsigned char)((seq >> 24) & 0xFFu);
    for (i = 0; i < mlen; i++)
        dst[WL_MBOX_FRAME_HEAD + i] = msg[i];
    return WL_MBOX_FRAME_HEAD + mlen;
}

static inline int wl_mbox_frame_decode(const unsigned char *src, int len,
        unsigned int *seq, int *off, int *mlen) {
    unsigned int magic = 0;
    if (!src || !seq || !off || !mlen)
        return WL_ERR_BOUND;
    if (len < WL_MBOX_FRAME_HEAD)
        return WL_ERR_TRUNC;
    magic = (unsigned int)src[0]
        | ((unsigned int)src[1] << 8)
        | ((unsigned int)src[2] << 16)
        | ((unsigned int)src[3] << 24);
    if (magic != WL_MBOX_MAGIC)
        return WL_ERR_BOUND;
    *seq = (unsigned int)src[4]
        | ((unsigned int)src[5] << 8)
        | ((unsigned int)src[6] << 16)
        | ((unsigned int)src[7] << 24);
    *off = WL_MBOX_FRAME_HEAD;
    *mlen = len - WL_MBOX_FRAME_HEAD;
    if (*mlen < WL_HDR_SZ || *mlen > WL_MAX_MSG)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

/** Claim the slot a box owns, stable across polls, fail-closed when
 * the server is full or the name is wild. */
static inline int wl_mbox_assign(wl_mbox_box_t *boxes, const char *box) {
    int free = -1;
    int i;
    int k;
    if (!boxes || !box)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (boxes[i].used) {
            k = 0;
            while (boxes[i].box[k] != '\0' && box[k] != '\0'
                && boxes[i].box[k] == box[k])
                k++;
            if (boxes[i].box[k] == '\0' && box[k] == '\0')
                return i;
        } else if (free < 0) {
            free = i;
        }
    }
    if (free < 0)
        return WL_ERR_BOUND;
    k = 0;
    while (box[k] != '\0' && k + 1 < WL_MBOX_BOX_MAX) {
        boxes[free].box[k] = box[k];
        k++;
    }
    boxes[free].box[k] = '\0';
    boxes[free].seq_last = 0;
    boxes[free].used = 1;
    return free;
}

/** Freshness of an arriving sequence: a repeat of the last accepted
 * one is a duplicate the server already consumed, anything else is
 * new work. Fail-closed on wild slots. */
static inline int wl_mbox_fresh(const wl_mbox_box_t *boxes, int slot,
        unsigned int seq) {
    if (!boxes || slot < 0 || slot >= WL_MAX_SURFACES)
        return WL_ERR_BOUND;
    if (boxes[slot].used && seq == boxes[slot].seq_last)
        return 0;
    return 1;
}

/** Route one mailbox message to the compositor state. The box owns
 * its slot, so a client id is only checked for range, never for
 * global meaning: each connection speaks its own id space exactly
 * like a real Wayland client, and the slot is the server resource.
 * Attach reports w/h for the pixel load, commit reports -1 for no
 * change, anything else that validates reports the slot too. */
static inline int wl_mbox_route(wl_comp_t *c, wl_mbox_box_t *boxes,
        const char *box, unsigned int id, unsigned int opcode,
        const unsigned char *arg, int alen,
        int *slot, int *w, int *h) {
    unsigned int pool = 0;
    unsigned int sid = 0;
    int s = -1;
    int i;
    int r;
    if (!c || !boxes || !box || !slot || !w || !h)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    s = wl_mbox_assign(boxes, box);
    if (s < 0)
        return s;
    *slot = s;
    *w = -1;
    *h = -1;
    sid = WL_ID_SURFACE_BASE + (unsigned int)s;
    for (i = 0; i < WL_MAX_SURFACES; i++) {
        if (c->items[i].id == sid)
            break;
    }
    if (i >= WL_MAX_SURFACES) {
        if (wl_comp_add(c, sid, 64, 64) != WL_ERR_OK)
            return WL_ERR_BOUND;
    }
    if (wl_surface_id_valid(id)) {
        if (opcode == WL_OP_SURFACE_ATTACH) {
            if (!arg || alen < WL_ATTACH_SZ)
                return WL_ERR_BOUND;
            r = wl_attach_decode(arg, alen, &pool, w, h);
            if (r != WL_ERR_OK)
                return r;
            return wl_comp_attach_buf(c, sid, pool, *w, *h);
        }
        if (opcode == WL_OP_SURFACE_COMMIT) {
            for (i = 0; i < WL_MAX_SURFACES; i++) {
                if (c->items[i].id == sid) {
                    c->items[i].mapped = 1;
                    return WL_ERR_OK;
                }
            }
            return WL_ERR_ID;
        }
        return WL_ERR_BOUND;
    }
    if (id == WL_ID_DISPLAY) {
        if (opcode == WL_OP_DISPLAY_GET_REGISTRY || opcode == 0)
            return WL_ERR_OK;
        return WL_ERR_BOUND;
    }
    if (id == WL_ID_REGISTRY) {
        if (opcode != WL_OP_REGISTRY_BIND)
            return WL_ERR_BOUND;
        if (!arg || alen < 4)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_COMPOSITOR) {
        if (opcode != WL_OP_COMPOSITOR_CREATE_SURFACE)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_SHM) {
        if (opcode != WL_OP_SHM_CREATE_POOL)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (id == WL_ID_XDG_BASE) {
        if (opcode != WL_OP_XDG_GET_TOPLEVEL)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    if (wl_pool_id_valid(id)) {
        if (opcode != WL_OP_POOL_CREATE_BUFFER)
            return WL_ERR_BOUND;
        return WL_ERR_OK;
    }
    return WL_ERR_ID;
}


#endif
