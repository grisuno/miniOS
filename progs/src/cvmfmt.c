/* cvmfmt.c - CVM formatting probe.
 *
 * Runs as a CVM module inside MiniOS. It pins the host natives that
 * format values (sprintf/snprintf/printf): the CVM in the guest used to
 * ship stub natives that wrote an empty string, so a module could not
 * print a number at all.
 *
 * The buffers are poisoned before the call, so a missing terminator
 * shows up as a trailing '#' in the output. The window and its canary
 * are globals on purpose: the canary has to sit right behind the window
 * to prove that the formatter never writes past it.
 */
#include <stdio.h>
#include <string.h>

static char fwin[8];
static char fcanary[9];

int main(void) {
    char buf[32];
    int n;

    memset(buf, '#', 32);
    n = snprintf(buf, 32, "n=%d s=%s", 42, "ok");
    printf("%s len=%d\n", buf, n);

    memset(buf, '#', 32);
    sprintf(buf, "t=%u x=%x", 7, 255);
    printf("%s\n", buf);

    memset(fwin, '#', 8);
    memset(fcanary, 'C', 8);
    fcanary[8] = 0;
    snprintf(fwin, 8, "%s", "0123456789ABCDEF");
    printf("win=%s canary=%s\n", fwin, fcanary);
    return 0;
}
