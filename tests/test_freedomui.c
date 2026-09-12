/** test_freedomui - host suite for the real FreeDom MiniOS backend.
 *
 * Exercises the pure backend of progs/freedomui/freedomui_minios.c plus the
 * linked engine modules (url omnibox, Lexbor parse, ui wrap). Fail-closed
 * on every bound. Exit nonzero on first failure.
 */
#include <stdio.h>
#include <string.h>

#define FREEDOMUI_HOST_TEST 1
#include "../progs/freedomui/freedomui_minios.c"

/** Report helper for single check lines. */
static int check_ui(int cond, const char *name) {
    if (!cond) {
        printf("FAIL: %s\n", name);
        return 1;
    }
    printf("PASS: %s\n", name);
    return 0;
}

/** Entry point running all backend checks. */
int main(void) {
    FreedomUiConfig c = freedomui_default();
    unsigned char pal[768];
    char nav[512];
    url_omni_kind kind;
    char *title;
    char *text;
    long elems;
    int fails = 0;
    fails += check_ui(c.surface_w == 800L, "surface width");
    fails += check_ui(c.surface_h == 360L, "surface height");
    fails += check_ui(c.present_buf == 1L, "present buffer nk");
    fails += check_ui(c.title_max == 31L, "title bound");
    fails += check_ui(freedomui_build_palette(pal, 768L) == 0L, "palette ok");
    fails += check_ui(pal[6 * 3] == 15 && pal[6 * 3 + 1] == 15 && pal[6 * 3 + 2] == 15, "palette bg terminal");
    fails += check_ui(pal[7 * 3] == 0 && pal[7 * 3 + 1] == 220 && pal[7 * 3 + 2] == 0, "palette fg terminal text");
    fails += check_ui(pal[4 * 3] == 60 && pal[4 * 3 + 1] == 90 && pal[4 * 3 + 2] == 140, "palette titlebar");
    fails += check_ui(freedomui_build_palette(0, 768L) != 0L, "palette null fails");
    fails += check_ui(freedomui_build_palette(pal, 100L) != 0L, "palette short fails");
    fails += check_ui(url_omnibox("example.com", &kind, nav, sizeof(nav)) == 0 && kind == 0, "omnibox bare host navigates");
    fails += check_ui(url_omnibox("https://example.com/a", &kind, nav, sizeof(nav)) == 0 && kind == 0, "omnibox https navigates");
    fails += check_ui(url_omnibox("hello world", &kind, nav, sizeof(nav)) == 0 && kind == 1, "omnibox query searches");
    fails += check_ui(url_omnibox("javascript:alert(1)", &kind, nav, sizeof(nav)) == 0 && kind == 1, "omnibox js searches");
    {
        char html[64];
        ui_layout lay;
        html[0] = '<';
        html[1] = 't';
        html[2] = 'i';
        html[3] = 't';
        html[4] = 'l';
        html[5] = 'e';
        html[6] = '>';
        html[7] = 'H';
        html[8] = 'i';
        html[9] = '<';
        html[10] = '/';
        html[11] = 't';
        html[12] = 'i';
        html[13] = 't';
        html[14] = 'l';
        html[15] = 'e';
        html[16] = '>';
        html[17] = '<';
        html[18] = 'p';
        html[19] = '>';
        html[20] = 'b';
        html[21] = 'o';
        html[22] = 'd';
        html[23] = 'y';
        html[24] = 't';
        html[25] = 'e';
        html[26] = 'x';
        html[27] = 't';
        html[28] = '<';
        html[29] = '/';
        html[30] = 'p';
        html[31] = '>';
        html[32] = 0;
        title = 0;
        text = 0;
        elems = freedomui_engine_text(html, 32L, &title, &text);
        fails += check_ui(elems > 0L && text != 0, "engine parse text");
        fails += check_ui(title != 0 && title[0] == 'H' && title[1] == 'i', "engine parse title");
        if (text) {
            fails += check_ui(ui_wrap_text(text, strlen(text), (size_t)c.cols, &lay) == 0 && lay.count > 0, "engine wrap lines");
            ui_layout_free(&lay);
            hp_free(text);
        }
        if (title) {
            hp_free(title);
        }
        title = 0;
        text = 0;
        fails += check_ui(freedomui_engine_text(0, 10L, &title, &text) < 0L, "engine null fails");
        fails += check_ui(freedomui_host_probe(&c) == 0, "host probe");
        fails += check_ui(freedomui_host_probe(0) != 0L, "host probe null fails");
    }
    if (fails) {
        printf("freedomui: %d failures\n", fails);
        return 1;
    }
    printf("freedomui: ok\n");
    return 0;
}
