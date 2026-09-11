/** test_freedom_wl - host suite for the Wayland to MiniOS mapping.
 *
 * Exercises the pure logic of progs/src/freedom_wl without syscalls.
 * Fail-closed on every bound. Exit nonzero on first failure.
 */
#include <stdio.h>

#define FREEDOM_WL_HOST_TEST 1
#include "../progs/src/freedom_wl.c"

/** Report helper for single check lines. */
static int check_host(int cond, const char *name) {
    if (!cond) {
        printf("FAIL: %s\n", name);
        return 1;
    }
    printf("PASS: %s\n", name);
    return 0;
}

/** Entry point running all mapping checks. */
int main(void) {
    FreedomWlConfig c = freedom_wl_default();
    long x;
    long y;
    long w;
    long h;
    char t1[8];
    char t2[8];
    char t3[8];
    int fails = 0;
    fails += check_host(c.surface_w == 800L, "surface width");
    fails += check_host(c.surface_h == 360L, "surface height");
    fails += check_host(c.present_buf == 1L, "present buffer nk");
    fails += check_host(c.title_max == 31L, "title bound");
    x = 10L;
    y = 10L;
    w = 100L;
    h = 100L;
    fails += check_host(freedom_wl_clip_rect(&c, &x, &y, &w, &h) == 0L, "clip inside");
    x = -5L;
    y = -5L;
    w = 20L;
    h = 20L;
    fails += check_host(freedom_wl_clip_rect(&c, &x, &y, &w, &h) == 0L && x == 0L && y == 0L && w == 15L && h == 15L, "clip negative origin");
    x = 0L;
    y = 0L;
    w = 5000L;
    h = 5000L;
    fails += check_host(freedom_wl_clip_rect(&c, &x, &y, &w, &h) == 0L && w == 800L && h == 360L, "clip oversize");
    x = 900L;
    y = 0L;
    w = 10L;
    h = 10L;
    fails += check_host(freedom_wl_clip_rect(&c, &x, &y, &w, &h) != 0L, "clip outside fails");
    x = 0L;
    y = 0L;
    w = 0L;
    h = 10L;
    fails += check_host(freedom_wl_clip_rect(&c, &x, &y, &w, &h) != 0L, "clip zero width fails");
    fails += check_host(freedom_wl_clip_rect(0, &x, &y, &w, &h) != 0L, "clip null config fails");
    fails += check_host(freedom_wl_frame_bytes(&c, 800L, 360L) == 288000L, "frame bytes full");
    fails += check_host(freedom_wl_frame_bytes(&c, 0L, 10L) < 0L, "frame zero fails");
    fails += check_host(freedom_wl_frame_bytes(&c, 5000L, 5000L) < 0L, "frame oversize fails");
    fails += check_host(freedom_wl_keysym(&c, 0x01L) == 27L, "keysym esc");
    fails += check_host(freedom_wl_keysym(&c, 0x1CL) == 13L, "keysym enter");
    fails += check_host(freedom_wl_keysym(&c, 0x39L) == 32L, "keysym space");
    fails += check_host(freedom_wl_keysym(&c, 0xFFL) < 0L, "keysym unknown fails");
    t1[0] = 'h';
    t1[1] = 'i';
    t1[2] = 0;
    fails += check_host(freedom_wl_sanitize_utf8(t1, 8L) == 2L, "utf8 ascii");
    t2[0] = (char)0xFF;
    t2[1] = 0;
    fails += check_host(freedom_wl_sanitize_utf8(t2, 8L) == 1L && t2[0] == '?', "utf8 invalid replaced");
    t3[0] = (char)0xC3;
    t3[1] = (char)0xA9;
    t3[2] = 0;
    fails += check_host(freedom_wl_sanitize_utf8(t3, 8L) == 2L, "utf8 two byte kept");
    fails += check_host(freedom_wl_sanitize_utf8(0, 8L) < 0L, "utf8 null fails");
    fails += check_host(freedom_wl_title_ok(&c, t1, 2L) == 0L, "title ok");
    fails += check_host(freedom_wl_title_ok(&c, t1, 99L) != 0L, "title oversize fails");
    fails += check_host(freedom_wl_host_probe(&c) == 0, "host probe");
    fails += check_host(wl_has_scheme("https://a.b") == 1L, "scheme https");
    fails += check_host(wl_has_scheme("javascript:alert(1)") == 1L, "scheme js");
    fails += check_host(wl_has_scheme("google.com") == 0L, "scheme bare");
    fails += check_host(wl_looks_like_url("google.com") == 1L, "looks url");
    fails += check_host(wl_looks_like_url("hello world") == 0L, "looks query");
    {
        char uh[64];
        char up[128];
        long uport;
        long usec;
        fails += check_host(wl_split_url(&c, "https://google.com/a/b", uh, up, &uport, &usec) == 1L, "split https");
        fails += check_host(uport == 443L && usec == 1L, "split https port");
        fails += check_host(up[0] == '/' && up[1] == 'a', "split https path");
        fails += check_host(wl_split_url(&c, "http://h:8080/x", uh, up, &uport, &usec) == 1L, "split port");
        fails += check_host(uport == 8080L && usec == 0L, "split port value");
        fails += check_host(wl_split_url(&c, "http://h:0/x", uh, up, &uport, &usec) == 0L, "split bad port fails");
        fails += check_host(wl_split_url(&c, "ftp://h/x", uh, up, &uport, &usec) == 0L, "split scheme fails");
        fails += check_host(wl_split_url(&c, "http://h", uh, up, &uport, &usec) == 1L && up[0] == '/' && up[1] == 0, "split root path");
    }
    {
        char rh[64];
        char rp[128];
        long rport;
        long rsec;
        wl_copy(rh, "a.b", 64L);
        wl_copy(rp, "/d/i", 128L);
        rport = 80L;
        fails += check_host(wl_resolve_redirect(&c, "http://x.y/z", 1L, rh, rp, &rport, &rsec) == 1L, "redir absolute");
        fails += check_host(rsec == 0L, "redir absolute secure");
        wl_copy(rp, "/d/i", 128L);
        fails += check_host(wl_resolve_redirect(&c, "/n", 0L, rh, rp, &rport, &rsec) == 1L && rp[0] == '/' && rp[1] == 'n', "redir root");
        fails += check_host(wl_resolve_redirect(&c, "javascript:x", 0L, rh, rp, &rport, &rsec) == -1L, "redir scheme refused");
        wl_copy(rp, "/d/i", 128L);
        fails += check_host(wl_resolve_redirect(&c, "n", 0L, rh, rp, &rport, &rsec) == 1L, "redir relative");
    }
    {
        char fb[256];
        char fl[4][32];
        long nl;
        wl_copy(fb, "<html><body><p>hi <b>there</b></p><script>evil()</script>ok &amp; bye<br>end", 256L);
        nl = wl_filter_wrap(&c, fb, wl_strlen(fb, 256L), (char *)fl, 4L, 32L);
        fails += check_host(nl == 4L, "filter lines");
        fails += check_host(fl[1][0] == 'h' && fl[1][1] == 'i', "filter text");
        fails += check_host(fl[2][0] == 'o' && fl[2][1] == 'k', "filter script dropped");
        wl_copy(fb, "a&lt;b&#65;&#x42;", 256L);
        nl = wl_filter_wrap(&c, fb, wl_strlen(fb, 256L), (char *)fl, 4L, 32L);
        fails += check_host(nl == 1L && fl[0][0] == 'a' && fl[0][1] == '<' && fl[0][2] == 'b' && fl[0][3] == 'A' && fl[0][4] == 'B', "filter entities");
        wl_copy(fb, "<!-- hid -->shown", 256L);
        nl = wl_filter_wrap(&c, fb, wl_strlen(fb, 256L), (char *)fl, 4L, 32L);
        fails += check_host(nl == 1L && fl[0][0] == 's', "filter comment dropped");
    }
    fails += check_host(wl_scroll_clamp(&c, -5L, 100L) == 0L, "scroll negative");
    fails += check_host(wl_scroll_clamp(&c, 9999L, 100L) == 100L - 44L, "scroll top");
    fails += check_host(wl_scroll_clamp(&c, 7L, 10L) == 0L, "scroll short page");
    {
        char st[100];
        char sq[64];
        fails += check_host(wl_status_text(&c, "h", 12L, 0L, 3L, st, 100L) > 0L, "status ok");
        fails += check_host(wl_status_text(&c, "h", -1L, 0L, 3L, st, 100L) < 0L, "status neg fails");
        fails += check_host(wl_ci_contains("Transfer-Encoding: chunked", "chunked") == 1L, "ci contains");
        fails += check_host(wl_ci_contains("text/html", "chunked") == 0L, "ci miss");
        fails += check_host(wl_make_search(sq, "a b&c", 64L) > 0L, "search encode");
    }
    if (fails) {
        printf("freedom_wl: %d failures\n", fails);
        return 1;
    }
    printf("freedom_wl: ok\n");
    return 0;
}
