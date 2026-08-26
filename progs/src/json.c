/* json.c - command path JSON tool: validate, pretty-print and query.
 * A self-contained JSON parser/serializer written in the miniGCC subset,
 * which has no structs, so values live in a flat node table of parallel
 * arrays.  A node is one of null/bool/number/string/object/array; object
 * members keep their key in js_str (the member value node) and their value
 * in the node itself, and object members / array elements are chained with
 * js_next.
 *
 * Usage: json <file>            validate and pretty-print
 *        json <file> <path>     print the value at a dotted path (.a.b, .a.3)
 */

void *malloc();
void free();
int printf();
int putchar();
int puts();
int strlen();
int strcmp();
void *fopen();
int fclose();
int fread();
int fseek();
int ftell();
void rewind();

#define JS_MAX_NODES 512
#define JS_POOL (16 * 1024)

#define JS_NULL 0
#define JS_BOOL 1
#define JS_NUM 2
#define JS_STR 3
#define JS_OBJ 4
#define JS_ARR 5

#define JS_SEEK_END 2
#define JS_EXIT_OK 0
#define JS_EXIT_FAIL 1

static char *js_key[JS_MAX_NODES];
static char *js_str[JS_MAX_NODES];
static int   js_type[JS_MAX_NODES];
static int   js_num[JS_MAX_NODES];
static int   js_first[JS_MAX_NODES];
static int   js_count[JS_MAX_NODES];
static int   js_next[JS_MAX_NODES];
static int   js_n;

static char  js_pool[JS_POOL];
static int   js_plen;

static char *js_src;
static int   js_pos;
static int   js_len;
static int   js_err;

static char *js_read_all(const char *name, int *len) {
    char *data;
    int got;
    void *f = fopen((char *)name, "r");
    if (!f) return 0;
    fseek(f, 0, JS_SEEK_END);
    *len = ftell(f);
    rewind(f);
    if (*len < 0) { fclose(f); return 0; }
    data = malloc(*len + 1);
    if (!data) { fclose(f); return 0; }
    got = fread(data, 1, *len, f);
    fclose(f);
    if (got != *len) { free(data); return 0; }
    data[*len] = 0;
    return data;
}

static int js_new(void) {
    if (js_n >= JS_MAX_NODES) { js_err = 1; return -1; }
    return js_n++;
}

static void js_skip_ws(void) {
    while (js_pos < js_len) {
        char c = js_src[js_pos];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') js_pos++;
        else break;
    }
}

static int js_peek(void) {
    js_skip_ws();
    if (js_pos >= js_len) return -1;
    return js_src[js_pos] & 255;
}

static int js_parse_value(void);

static int js_parse_string(void) {
    int i;
    if (js_pos >= js_len || js_src[js_pos] != '"') { js_err = 1; return -1; }
    js_pos++;
    i = js_plen;
    while (1) {
        char c;
        int esc;
        if (js_pos >= js_len) { js_err = 1; return -1; }
        c = js_src[js_pos];
        if (c == '"') { js_pos++; break; }
        esc = 0;
        if (c == '\\') {
            char e;
            esc = 1;
            js_pos++;
            if (js_pos >= js_len) { js_err = 1; return -1; }
            e = js_src[js_pos];
            if (e == 'n') { c = 10; js_pos++; }
            else if (e == 't') { c = 9; js_pos++; }
            else if (e == 'r') { c = 13; js_pos++; }
            else if (e == 'b') { c = 8; js_pos++; }
            else if (e == 'f') { c = 12; js_pos++; }
            else if (e == '/' || e == '\\' || e == '"') { c = e; js_pos++; }
            else if (e == 'u') { c = '?'; js_pos += 5; }
            else { js_err = 1; return -1; }
        }
        if (js_plen + 1 >= JS_POOL) { js_err = 1; return -1; }
        js_pool[js_plen++] = c;
        if (!esc) js_pos++;
    }
    js_pool[js_plen] = 0;
    js_plen++;
    return i;
}

static int js_parse_number(void) {
    int v;
    v = 0;
    while (js_pos < js_len && js_src[js_pos] >= '0' && js_src[js_pos] <= '9') {
        v = v * 10 + (js_src[js_pos] - '0');
        js_pos++;
    }
    return v;
}

static int js_key_match(int child, const char *key) {
    return strcmp(js_str[child], key) == 0;
}

static int js_parse_object(void) {
    int node, first, last, cnt, keyidx;
    js_pos++;
    node = js_new();
    if (node < 0) return -1;
    js_type[node] = JS_OBJ;
    first = -1;
    last = -1;
    cnt = 0;
    if (js_peek() == '}') { js_pos++; js_first[node] = -1; js_count[node] = 0; return node; }
    while (1) {
        int child;
        if (js_peek() != '"') { js_err = 1; return -1; }
        keyidx = js_parse_string();
        if (keyidx < 0) return -1;
        if (js_peek() != ':') { js_err = 1; return -1; }
        js_pos++;
        child = js_parse_value();
        if (child < 0) return -1;
        js_key[child] = js_pool + keyidx;
        if (first < 0) first = child;
        else js_next[last] = child;
        js_next[child] = -1;
        last = child;
        cnt++;
        if (js_peek() == ',') { js_pos++; continue; }
        break;
    }
    if (js_peek() != '}') { js_err = 1; return -1; }
    js_pos++;
    js_first[node] = first;
    js_count[node] = cnt;
    return node;
}

static int js_parse_array(void) {
    int node, first, last, cnt;
    js_pos++;
    node = js_new();
    if (node < 0) return -1;
    js_type[node] = JS_ARR;
    first = -1;
    last = -1;
    cnt = 0;
    if (js_peek() == ']') { js_pos++; js_first[node] = -1; js_count[node] = 0; return node; }
    while (1) {
        int child;
        child = js_parse_value();
        if (child < 0) return -1;
        if (first < 0) first = child;
        else js_next[last] = child;
        js_next[child] = -1;
        last = child;
        cnt++;
        if (js_peek() == ',') { js_pos++; continue; }
        break;
    }
    if (js_peek() != ']') { js_err = 1; return -1; }
    js_pos++;
    js_first[node] = first;
    js_count[node] = cnt;
    return node;
}

static int js_parse_value(void) {
    int c, node, i;
    c = js_peek();
    if (c < 0) return -1;
    if (c == '{') return js_parse_object();
    if (c == '[') return js_parse_array();
    if (c == '"') {
        i = js_parse_string();
        if (i < 0) return -1;
        node = js_new();
        if (node < 0) return -1;
        js_type[node] = JS_STR;
        js_str[node] = js_pool + i;
        return node;
    }
    if (c == 't') {
        if (js_len - js_pos >= 4 && js_src[js_pos] == 't' && js_src[js_pos + 1] == 'r' &&
            js_src[js_pos + 2] == 'u' && js_src[js_pos + 3] == 'e') {
            js_pos += 4;
            node = js_new();
            if (node < 0) return -1;
            js_type[node] = JS_BOOL;
            js_num[node] = 1;
            return node;
        }
        js_err = 1;
        return -1;
    }
    if (c == 'f') {
        if (js_len - js_pos >= 5 && js_src[js_pos] == 'f' && js_src[js_pos + 1] == 'a' &&
            js_src[js_pos + 2] == 'l' && js_src[js_pos + 3] == 's' && js_src[js_pos + 4] == 'e') {
            js_pos += 5;
            node = js_new();
            if (node < 0) return -1;
            js_type[node] = JS_BOOL;
            js_num[node] = 0;
            return node;
        }
        js_err = 1;
        return -1;
    }
    if (c == 'n') {
        if (js_len - js_pos >= 4 && js_src[js_pos] == 'n' && js_src[js_pos + 1] == 'u' &&
            js_src[js_pos + 2] == 'l' && js_src[js_pos + 3] == 'l') {
            js_pos += 4;
            node = js_new();
            if (node < 0) return -1;
            js_type[node] = JS_NULL;
            return node;
        }
        js_err = 1;
        return -1;
    }
    if (c == '-' || (c >= '0' && c <= '9')) {
        int neg;
        neg = 0;
        if (c == '-') { neg = 1; js_pos++; }
        node = js_new();
        if (node < 0) return -1;
        js_type[node] = JS_NUM;
        js_num[node] = js_parse_number();
        if (neg) js_num[node] = 0 - js_num[node];
        return node;
    }
    js_err = 1;
    return -1;
}

/* ---- Output ---- */

static void js_indent(int n) {
    int i;
    for (i = 0; i < n; i++) putchar(' ');
}

static void js_print_str(const char *s) {
    int i;
    putchar('"');
    i = 0;
    while (s[i]) {
        char c;
        c = s[i];
        if (c == '"' || c == '\\') { putchar('\\'); putchar(c); }
        else if (c == 10) { putchar('\\'); putchar('n'); }
        else if (c == 9) { putchar('\\'); putchar('t'); }
        else if (c == 13) { putchar('\\'); putchar('r'); }
        else putchar(c);
        i++;
    }
    putchar('"');
}

static void js_print_value(int node, int depth) {
    int i, c;
    if (node < 0) return;
    if (js_type[node] == JS_NULL) { printf("null"); return; }
    if (js_type[node] == JS_BOOL) { printf(js_num[node] ? "true" : "false"); return; }
    if (js_type[node] == JS_NUM) { printf("%d", js_num[node]); return; }
    if (js_type[node] == JS_STR) { js_print_str(js_str[node]); return; }
    if (js_type[node] == JS_OBJ) {
        putchar('{');
        if (js_count[node] > 0) putchar('\n');
        c = js_first[node];
        i = 0;
        while (c >= 0) {
            js_indent(depth + 1);
            js_print_str(js_key[c]);
            printf(": ");
            js_print_value(c, depth + 1);
            if (i < js_count[node] - 1) putchar(',');
            putchar('\n');
            i++;
            c = js_next[c];
        }
        js_indent(depth);
        putchar('}');
        return;
    }
    putchar('[');
    if (js_count[node] > 0) putchar('\n');
    c = js_first[node];
    i = 0;
    while (c >= 0) {
        js_indent(depth + 1);
        js_print_value(c, depth + 1);
        if (i < js_count[node] - 1) putchar(',');
        putchar('\n');
        i++;
        c = js_next[c];
    }
    js_indent(depth);
    putchar(']');
}

/* ---- Query (dotted path) ---- */

static int js_find_member(int obj, const char *key) {
    int c;
    c = js_first[obj];
    while (c >= 0) {
        if (strcmp(js_key[c], key) == 0) return c;
        c = js_next[c];
    }
    return -1;
}

static int js_array_at(int arr, int idx) {
    int c, i;
    c = js_first[arr];
    i = 0;
    while (c >= 0) {
        if (i == idx) return c;
        i++;
        c = js_next[c];
    }
    return -1;
}

static int js_query(int root, const char *path) {
    int cur, i;
    char seg[64];
    int seglen;
    cur = root;
    if (path[0] == '.') path++;
    while (*path) {
        seglen = 0;
        while (*path && *path != '.' && seglen < 63) {
            seg[seglen] = *path;
            seglen++;
            path++;
        }
        seg[seglen] = 0;
        if (cur < 0) return -1;
        if (js_type[cur] == JS_OBJ) {
            cur = js_find_member(cur, seg);
        } else if (js_type[cur] == JS_ARR) {
            int idx;
            idx = 0;
            i = 0;
            while (seg[i] >= '0' && seg[i] <= '9') { idx = idx * 10 + (seg[i] - '0'); i++; }
            if (seg[i] != 0) return -1;
            cur = js_array_at(cur, idx);
        } else {
            return -1;
        }
        if (*path == '.') path++;
    }
    return cur;
}

int main(int argc, char **argv) {
    char *data;
    int len;
    int root;
    if (argc < 2) { puts("usage: json <file> [path]"); return JS_EXIT_FAIL; }
    data = js_read_all(argv[1], &len);
    if (!data) { printf("json: cannot open %s\n", argv[1]); return JS_EXIT_FAIL; }
    js_src = data;
    js_pos = 0;
    js_len = len;
    js_n = 0;
    js_plen = 0;
    js_err = 0;
    root = js_parse_value();
    if (root < 0 || js_err || js_peek() != -1) {
        printf("json: %s: invalid JSON\n", argv[1]);
        free(data);
        return JS_EXIT_FAIL;
    }
    if (argc >= 3) {
        int n;
        n = js_query(root, argv[2]);
        if (n < 0) { printf("json: %s: not found\n", argv[2]); free(data); return JS_EXIT_FAIL; }
        js_print_value(n, 0);
        putchar('\n');
        free(data);
        return JS_EXIT_OK;
    }
    js_print_value(root, 0);
    putchar('\n');
    free(data);
    return JS_EXIT_OK;
}
