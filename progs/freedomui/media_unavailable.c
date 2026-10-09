/** media_unavailable.c - FreeDom media decoder entry points for a build
 * without FFmpeg (docs/spec/network.md, freedom-gui).
 *
 * FreeDom links FFmpeg only through src/media_decoder.c. MiniOS builds the
 * browser with MEDIA_OBJ empty and links this file instead, so video fails
 * closed: no decoder process is ever started, and a direct --media-decoder
 * invocation answers with one MD_ERROR and exits.
 */
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "media_decoder.h"

static const char media_unavailable_msg[] = "media decoding is not available on MiniOS";

/** Writes all of buf, retrying on short writes; stops on error. */
static void write_all(int fd, const void *buf, size_t len) {
    const unsigned char *p = (const unsigned char *)buf;
    while (len > 0) {
        ssize_t n = write(fd, p, len);
        if (n <= 0) return;
        p += (size_t)n;
        len -= (size_t)n;
    }
}

/** Refuses to start a decoder: the caller reports the failure and stays
 * responsive (browser_ui video_play already handles a failed spawn). */
int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd) {
    (void)pid;
    (void)out_fd;
    (void)cmd_fd;
    errno = ENOSYS;
    return -1;
}

/** --media-decoder entry: one non-fatal MD_ERROR, then exit. */
void media_decoder_run(int out_fd, int cmd_fd) {
    uint8_t tag = MD_ERROR;
    size_t len = sizeof media_unavailable_msg - 1;
    (void)cmd_fd;
    write_all(out_fd, &tag, sizeof tag);
    write_all(out_fd, &len, sizeof len);
    write_all(out_fd, media_unavailable_msg, len);
    _exit(0);
}
