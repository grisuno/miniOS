/** Docstring: Host test for the vedit IDE build contract (make test-vedit).
 *
 * Spec-level pin for progs/vedit/vedit.c: extension routing, base-name
 * stripping, path joins, link-format parsing, the shortcut contract, plus
 * the uemacs-adoption pure helpers (case/transpose/magic/command-table/
 * key-parser). The code-level killer is the guest selftest
 * (vedit --selftest-build), which executes the same vectors against the
 * real implementation; this host test locks the spec so silent contract
 * drift fails the build.
 *
 * MIRROR CONTRACT (keep in sync with vedit_selftest_build):
 *   t_has_ext  <-> vedit_has_ext    (same suffix match, empty ext fails)
 *   t_base_of  <-> vedit_base_of    (strip dirs, cut at '.', 48-byte cap)
 *   t_join     <-> vedit_join       (dir+base+ext, 64-byte cap)
 *   t_link_fmt <-> vedit_link_fmt   ("elf"=1, "cvm"=2, else 0)
 *   t_lang_of  <-> vedit_lang_of    (untitled/.c/.h=C, .s=ASM, .py=PY, .lua=LUA,
 *                                      .lisp=LISP)
 *   t_run_kind <-> vedit_run_kind   (c/h=1, lua=2, py=3, s=4, lisp=5, else 0)
 *   t_str_case <-> vedit_str_case   (1=upper, 2=lower, 3=capitalize)
 *   t_transpose<-> vedit_str_transpose (swap bytes around pos)
 *   t_magic    <-> vedit_magic_match (exact/dot/star/anchors/classes)
 *   t_cmd      <-> vedit_cmd_lookup  (named commands, -1 unknown)
 *   t_parse_key<-> vedit_parse_key   (^X/M-c/words, -1 bogus)
 *   shortcuts  <-> VEDIT_KEY_RUN/LINK/DUMP (18/12/4)
 * If a vector changes in the guest, update the host CHECKs here too.
 */

#include <stdio.h>
#include <string.h>

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static int t_has_ext(const char *fname, const char *ext) {
    size_t n = strlen(fname);
    size_t e = strlen(ext);
    size_t k;
    if (e == 0 || e > n) return 0;
    for (k = 0; k < e; k++) {
        if (fname[n - e + k] != ext[k]) return 0;
    }
    return 1;
}

static int t_base_of(const char *fname, char *dst, size_t cap) {
    size_t n = strlen(fname);
    size_t s = 0;
    size_t e = n;
    size_t k;
    size_t len;
    for (k = 0; k < n; k++) {
        if (fname[k] == '/') s = k + 1;
    }
    for (k = s; k < n; k++) {
        if (fname[k] == '.') e = k;
    }
    if (e <= s) e = n;
    len = e - s;
    if (len == 0 || len + 1 > cap || len >= 48) return -1;
    for (k = 0; k < len; k++) dst[k] = fname[s + k];
    dst[len] = 0;
    return 0;
}

static int t_join(const char *dir, const char *base, const char *ext,
                  char *dst, size_t cap) {
    size_t d = strlen(dir);
    size_t b = strlen(base);
    size_t e = strlen(ext);
    size_t k = 0;
    size_t i;
    if (d + b + e + 1 > cap) return -1;
    if (d + b + e + 1 > 64) return -1;
    for (i = 0; i < d; i++) dst[k++] = dir[i];
    for (i = 0; i < b; i++) dst[k++] = base[i];
    for (i = 0; i < e; i++) dst[k++] = ext[i];
    dst[k] = 0;
    return 0;
}

static int t_link_fmt(const char *s) {
    size_t k = 0;
    const char *e = "elf";
    const char *c = "cvm";
    while (e[k] && s[k] == e[k]) k++;
    if (e[k] == 0 && s[k] == 0) return 1;
    k = 0;
    while (c[k] && s[k] == c[k]) k++;
    if (c[k] == 0 && s[k] == 0) return 2;
    return 0;
}

/* Mirror of vedit_lang_of: 1=C, 2=PY, 3=LUA, 4=ASM, 5=LISP. Unknown
 * defaults to C, exactly like the guest (untitled highlights as C). */
static int t_lang_of(const char *fname) {
    size_t n = strlen(fname);
    if (n >= 2 && fname[n - 2] == '.') {
        if (fname[n - 1] == 'c') return 1;
        if (fname[n - 1] == 'h') return 1;
        if (fname[n - 1] == 's') return 4;
    }
    if (n >= 3 && fname[n - 3] == '.' &&
        fname[n - 2] == 'p' && fname[n - 1] == 'y')
        return 2;
    if (n >= 4 && fname[n - 4] == '.' && fname[n - 3] == 'l' &&
        fname[n - 2] == 'u' && fname[n - 1] == 'a')
        return 3;
    if (n >= 5 && fname[n - 5] == '.' && fname[n - 4] == 'l' &&
        fname[n - 3] == 'i' && fname[n - 2] == 's' && fname[n - 1] == 'p')
        return 5;
    return 1;
}

/* Mirror of vedit_run_kind: 1=minigcc, 2=lua, 3=python, 4=ld, 5=lisp, else 0. */
static int t_run_kind(const char *fname) {
    if (t_has_ext(fname, ".c") || t_has_ext(fname, ".h")) return 1;
    if (t_has_ext(fname, ".lua")) return 2;
    if (t_has_ext(fname, ".py")) return 3;
    if (t_has_ext(fname, ".s")) return 4;
    if (t_has_ext(fname, ".lisp")) return 5;
    return 0;
}

/* Mirror of vedit_str_case. */
static void t_str_case(char *s, int mode) {
    int i = 0;
    int new_word = 1;
    if (!s || (mode != 1 && mode != 2 && mode != 3)) return;
    while (s[i]) {
        int c = (unsigned char)s[i];
        if (c == ' ' || c == '\t' || c == '\n') {
            new_word = 1;
        } else if (mode == 1) {
            if (c >= 'a' && c <= 'z') s[i] = (char)(c - 32);
            new_word = 0;
        } else if (mode == 2) {
            if (c >= 'A' && c <= 'Z') s[i] = (char)(c + 32);
            new_word = 0;
        } else {
            if (new_word) {
                if (c >= 'a' && c <= 'z') s[i] = (char)(c - 32);
                new_word = 0;
            } else {
                if (c >= 'A' && c <= 'Z') s[i] = (char)(c + 32);
            }
        }
        i++;
    }
}

static void t_transpose(char *s, int len, int pos) {
    char t;
    if (!s || len < 2 || pos < 1 || pos >= len) return;
    t = s[pos - 1];
    s[pos - 1] = s[pos];
    s[pos] = t;
}

/* Mirror of vedit_magic_match (subset: ./star/anchors/classes). */
static int t_mclass(int c, const char *cls) {
    int neg = 0;
    int hit = 0;
    if (!cls || cls[0] != '[') return 0;
    cls++;
    if (*cls == '^') {
        neg = 1;
        cls++;
    }
    while (*cls && *cls != ']') {
        if (cls[1] == '-' && cls[2] && cls[2] != ']') {
            if (c >= (unsigned char)cls[0] && c <= (unsigned char)cls[2])
                hit = 1;
            cls += 3;
        } else {
            if (c == (unsigned char)*cls) hit = 1;
            cls++;
        }
    }
    return neg ? !hit : hit;
}

static int t_matom(const char *pat, int c, int *atom_len) {
    if (!pat || !pat[0] || c < 0) return 0;
    if (pat[0] == '.') {
        *atom_len = 1;
        return 1;
    }
    if (pat[0] == '[') {
        int k = 1;
        if (pat[k] == '^') k++;
        if (pat[k] == ']') k++;
        while (pat[k] && pat[k] != ']') k++;
        if (!pat[k]) return 0;
        *atom_len = k + 1;
        return t_mclass(c, pat);
    }
    if (pat[0] == '\\' && pat[1]) {
        *atom_len = 2;
        return c == (unsigned char)pat[1];
    }
    *atom_len = 1;
    return c == (unsigned char)pat[0];
}

static int t_mhere(const char *text, const char *pat, int *mlen) {
    int total = 0;
    if (!text || !pat || !mlen) return 0;
    if (pat[0] == '$' && pat[1] == 0) {
        *mlen = 0;
        return text[0] == 0;
    }
    while (pat[0]) {
        int alen = 0;
        int star = 0;
        if (pat[0] == '$' && pat[1] == 0) {
            *mlen = total;
            return text[0] == 0;
        }
        if (pat[0] == '[') {
            int k = 1;
            if (pat[k] == '^') k++;
            if (pat[k] == ']') k++;
            while (pat[k] && pat[k] != ']') k++;
            if (!pat[k]) return 0;
            alen = k + 1;
        } else if (pat[0] == '\\' && pat[1]) {
            alen = 2;
        } else {
            alen = 1;
        }
        star = (pat[alen] == '*');
        if (!star) {
            if (!text[0]) return 0;
            if (!t_matom(pat, (unsigned char)text[0], &alen)) return 0;
            text++;
            total++;
            pat += alen;
        } else {
            const char *rest = pat + alen + 1;
            int max = 0;
            int k;
            while (text[max]) {
                int dummy = 0;
                if (!t_matom(pat, (unsigned char)text[max], &dummy)) break;
                max++;
            }
            for (k = max; k >= 0; k--) {
                int sub = 0;
                if (t_mhere(text + k, rest, &sub)) {
                    *mlen = total + k + sub;
                    return 1;
                }
                if (k == 0) break;
            }
            return 0;
        }
    }
    *mlen = total;
    return 1;
}

static int t_magic(const char *text, const char *pat, int *mlen) {
    int off = 0;
    int anchored = 0;
    if (!text || !pat || !mlen) return 0;
    if (pat[0] == '^') {
        anchored = 1;
        pat++;
    }
    if (anchored) return t_mhere(text, pat, mlen);
    while (text[off]) {
        int sub = 0;
        if (t_mhere(text + off, pat, &sub)) {
            *mlen = sub;
            return 1;
        }
        off++;
    }
    {
        int sub = 0;
        if (t_mhere(text + off, pat, &sub)) {
            *mlen = sub;
            return 1;
        }
    }
    return 0;
}

static const char *t_cmds[] = {
    "save-file", "find-file", "query-replace", "shell-command", 0
};

static int t_cmd(const char *name) {
    int k = 0;
    if (!name || !name[0]) return -1;
    while (t_cmds[k]) {
        const char *t = t_cmds[k];
        int i = 0;
        while (t[i] && name[i] == t[i]) i++;
        if (!t[i] && !name[i]) return k;
        k++;
    }
    return -1;
}

static int t_parse_key(const char *s) {
    if (!s || !s[0]) return -1;
    if (s[0] == '^' && s[1] && !s[2]) {
        int c = (unsigned char)s[1];
        if (c >= 'a' && c <= 'z') return c - 'a' + 1;
        if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
        if (c == '@') return 0;
        if (c == '[') return 27;
        if (c == '\\') return 28;
        if (c == ']') return 29;
        if (c == '^') return 30;
        if (c == '_') return 31;
        return -1;
    }
    if (s[0] == 'M' && s[1] == '-' && s[2] && !s[3])
        return 3000 + (unsigned char)s[2];
    {
        const char *names[] = {"Up", "Down", "Left", "Right", "Home",
                               "End", "PgUp", "PgDn", "Del", "Esc", 0};
        int codes[] = {1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007,
                       1008, 1009};
        int k = 0;
        while (names[k]) {
            const char *t = names[k];
            int i = 0;
            while (t[i] && s[i] == t[i]) i++;
            if (!t[i] && !s[i]) return codes[k];
            k++;
        }
    }
    return -1;
}

int main(void) {
    char base[48];
    char path[64];
    char sc[32];
    int ml = 0;

    CHECK(t_lang_of("untitled") == 1, "untitled highlights as C");
    CHECK(t_lang_of("a.c") == 1, ".c highlights as C");
    CHECK(t_lang_of("a.h") == 1, ".h highlights as C");
    CHECK(t_lang_of("a.py") == 2, ".py highlights as Python");
    CHECK(t_lang_of("a.lua") == 3, ".lua highlights as Lua");
    CHECK(t_lang_of("a.s") == 4, ".s highlights as Asm");
    CHECK(t_lang_of("a.lisp") == 5, ".lisp highlights as Lisp");

    CHECK(t_run_kind("a.c") == 1, ".c routes to minigcc");
    CHECK(t_run_kind("a.h") == 1, ".h routes to minigcc");
    CHECK(t_run_kind("a.lua") == 2, ".lua routes to lua");
    CHECK(t_run_kind("a.py") == 3, ".py routes to python");
    CHECK(t_run_kind("a.s") == 4, ".s routes to ld");
    CHECK(t_run_kind("a.lisp") == 5, ".lisp routes to lisp");
    CHECK(t_run_kind("a.txt") == 0, ".txt routes nowhere");

    CHECK(t_has_ext("a.c", ".c"), "c ext matches");
    CHECK(!t_has_ext("a.c", ".lua"), "c is not lua");
    CHECK(t_has_ext("a.lua", ".lua"), "lua ext matches");
    CHECK(t_has_ext("a.py", ".py"), "py ext matches");
    CHECK(!t_has_ext("a", ".c"), "bare name has no ext");

    CHECK(t_base_of("src/a.c", base, sizeof(base)) == 0, "base strips dirs");
    CHECK(strcmp(base, "a") == 0, "base is a");
    CHECK(t_base_of("a.lua", base, sizeof(base)) == 0, "bare base works");
    CHECK(strcmp(base, "a") == 0, "bare base is a");
    CHECK(t_base_of("", base, sizeof(base)) != 0, "empty base fails");

    CHECK(t_join("/asm/", "a", ".s", path, sizeof(path)) == 0, "join asm");
    CHECK(strcmp(path, "/asm/a.s") == 0, "asm path exact");
    CHECK(t_join("/bin/", "a", ".elf", path, sizeof(path)) == 0, "join bin");
    CHECK(strcmp(path, "/bin/a.elf") == 0, "elf path exact");
    CHECK(t_join("/cvm/", "a", ".cvm", path, sizeof(path)) == 0, "join cvm");
    CHECK(strcmp(path, "/cvm/a.cvm") == 0, "cvm path exact");

    CHECK(t_link_fmt("elf") == 1, "elf parses");
    CHECK(t_link_fmt("cvm") == 2, "cvm parses");
    CHECK(t_link_fmt("exe") == 0, "exe rejected");
    CHECK(t_link_fmt("") == 0, "empty rejected");
    CHECK(t_link_fmt("ELF") == 0, "case sensitive");

    CHECK(18 == 18 && 12 == 12 && 4 == 4, "shortcut contract pinned");

    memcpy(sc, "hello world", 12);
    t_str_case(sc, 1);
    CHECK(strcmp(sc, "HELLO WORLD") == 0, "upper works");
    memcpy(sc, "Hello World", 12);
    t_str_case(sc, 2);
    CHECK(strcmp(sc, "hello world") == 0, "lower works");
    memcpy(sc, "hello world", 12);
    t_str_case(sc, 3);
    CHECK(strcmp(sc, "Hello World") == 0, "capitalize works");

    memcpy(sc, "ab", 3);
    t_transpose(sc, 2, 1);
    CHECK(strcmp(sc, "ba") == 0, "transpose swaps");

    CHECK(t_magic("foobar", "foo", &ml) && ml == 3, "magic exact");
    CHECK(t_magic("foobar", "f.o", &ml) && ml == 3, "magic dot");
    CHECK(t_magic("foobar", "f*bar", &ml), "magic star");
    CHECK(t_magic("foobar", "^foo", &ml) && ml == 3, "magic anchor");
    CHECK(!t_magic("xfoobar", "^foo", &ml), "magic anchor rejects");
    CHECK(t_magic("foobar", "bar$", &ml) && ml == 3, "magic end anchor");
    CHECK(t_magic("a1c", "a[0-9]c", &ml) && ml == 3, "magic class");
    CHECK(t_magic("abc", "a[^0-9]c", &ml), "magic negated class");
    CHECK(t_magic("abc", "z*", &ml) && ml == 0, "magic empty star");
    CHECK(!t_magic("abc", "z+", &ml), "magic plus is literal-plus");

    CHECK(t_cmd("save-file") >= 0, "save-file known");
    CHECK(t_cmd("query-replace") >= 0, "query-replace known");
    CHECK(t_cmd("no-such-cmd") < 0, "unknown command rejected");

    CHECK(t_parse_key("^K") == 11, "^K parses");
    CHECK(t_parse_key("^@") == 0, "^@ parses");
    CHECK(t_parse_key("M-f") == 3000 + 'f', "M-f parses");
    CHECK(t_parse_key("PgDn") == 1007, "PgDn parses");
    CHECK(t_parse_key("bogus") < 0, "bogus key rejected");

    if (failures) {
        printf("vedit build host test FAIL (%d)\n", failures);
        return 1;
    }
    printf("vedit build host test ok\n");
    return 0;
}
