/** wl_client.h - Thin mailbox client for Wayland-mini (ADR-0026).
 *
 * One surface per connection: a client writes its pixels once as
 * <box>.raw sized w*h, then emits the six-message session as
 * sequenced <box>-<seq>.msg files. The server drains, tiles and
 * composites, so N clients in background (mrun a & mrun b &) become
 * N tiled windows with real multitasking under the existing
 * preemptive scheduler. File bytes stay here (stdio); names, frames
 * and wire encoding stay in wl_mbox.h and wl_mini.h. Every bound
 * fails closed, never truncates.
 */

#ifndef WL_CLIENT_H
#define WL_CLIENT_H

#include "wl/wl_mbox.h"

#define WL_CLIENT_MSGS 6

/** Write one framed session message as its own mailbox file. */
static inline int wl_client_emit_file(const char *box, unsigned int seq,
        const unsigned char *msg, int mlen) {
    char path[WL_MBOX_NAME_MAX];
    unsigned char frame[WL_MAX_MSG + WL_MBOX_FRAME_HEAD];
    FILE *f = 0;
    int n = 0;
    if (!box || !msg || mlen <= 0)
        return WL_ERR_BOUND;
    n = wl_mbox_frame_encode(frame, sizeof frame, seq, msg, mlen);
    if (n <= 0)
        return n;
    if (wl_mbox_name(path, sizeof path, box, seq) <= 0)
        return WL_ERR_BOUND;
    f = fopen(path, "wb");
    if (!f)
        return WL_ERR_BOUND;
    if (fwrite(frame, 1, (unsigned long)n, f) != (unsigned long)n) {
        fclose(f);
        return WL_ERR_BOUND;
    }
    if (fclose(f) != 0)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

/** Write the pixel blob the next attach sizes. Pixels first so the
 * server never attaches a surface whose raw file is missing. */
static inline int wl_client_raw_file(const char *box,
        const unsigned char *px, int w, int h) {
    char path[WL_MBOX_NAME_MAX];
    FILE *f = 0;
    long n = 0;
    if (!box || !px)
        return WL_ERR_BOUND;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_mbox_raw_name(path, sizeof path, box) <= 0)
        return WL_ERR_BOUND;
    f = fopen(path, "wb");
    if (!f)
        return WL_ERR_BOUND;
    n = (long)w * (long)h;
    if (fwrite(px, 1, (unsigned long)n, f) != (unsigned long)n) {
        fclose(f);
        return WL_ERR_BOUND;
    }
    if (fclose(f) != 0)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

/** Attach one surface: pixels first, then display, bind, create,
 * pool, attach and commit, each sequenced from seq0. Returns
 * WL_ERR_OK when all six messages landed. */
static inline int wl_client_attach(const char *box, unsigned int seq0,
        const unsigned char *px, int w, int h) {
    unsigned char msg[WL_MAX_MSG];
    wl_hdr_t hdr;
    unsigned int seq = 0;
    if (!box || !px)
        return WL_ERR_BOUND;
    if (wl_mbox_box_ok(box) != WL_ERR_OK)
        return WL_ERR_STR;
    if (wl_pool_fit(w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_raw_file(box, px, w, h) != WL_ERR_OK)
        return WL_ERR_BOUND;
    seq = seq0;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_DISPLAY,
            WL_OP_DISPLAY_GET_REGISTRY, 8, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_REGISTRY,
            WL_OP_REGISTRY_BIND, 12, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_u32_encode(msg, sizeof msg, 8, WL_ID_COMPOSITOR)
        != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 12) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_COMPOSITOR,
            WL_OP_COMPOSITOR_CREATE_SURFACE, 8, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SHM,
            WL_OP_SHM_CREATE_POOL, 8, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_ATTACH, 20, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_attach_encode(msg + 8, (int)sizeof msg - 8,
            WL_ID_POOL_BASE, w, h) != WL_ATTACH_SZ)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 20) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_hdr_encode(msg, sizeof msg, WL_ID_SURFACE_BASE,
            WL_OP_SURFACE_COMMIT, 8, &hdr) != WL_ERR_OK)
        return WL_ERR_BOUND;
    if (wl_client_emit_file(box, seq++, msg, 8) != WL_ERR_OK)
        return WL_ERR_BOUND;
    return WL_ERR_OK;
}

#endif
