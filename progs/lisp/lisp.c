/**
 * lisp.c -- small Lisp interpreter for MiniOS.
 *
 * A self-contained Lisp in one translation unit, built on the host as a
 * ring-3 static ELF and shipped on MiniFS with love :D
 * with a bare-name alias. Programs reach the kernel only through the Linux
 * syscall ABI plus the MiniOS custom numbers from minios_abi.h.
 *
 * Language surface: numbers (int64), strings, symbols, cons cells, closures
 * with lexical scope, and the special forms quote, if, begin, define, set!,
 * lambda and let. Diagnostics go to stderr, values to stdout, exit status
 * follows the script result.
 *
 * DRY note: every primitive validates its arguments the same way --
 * "N arguments of these types, or one specific error message". That
 * validation lives once, in check_args()/arity0(); primitives themselves
 * only encode the arity, the types and the message (see PRIM_* section).
 */
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minios_abi.h"

/**
 * Central configuration for every bound in the interpreter.
 *
 * No other literal below controls a limit, a port, a syscall number or a
 * user-visible string twice; edits happen here. Every array sized by one
 * of these constants below (open_files[], argv[], message[]) MUST spell
 * the constant, not the number, so this enum stays the single source of
 * truth it claims to be.
 */
enum LispConfig {
    LISP_MAX_OPEN_FILES = 64,
    LISP_INITIAL_BUFFER_CAPACITY = 256,
    LISP_INITIAL_INPUT_CAPACITY = 4096,
    LISP_MAX_INPUT_BYTES = 16u * 1024u * 1024u,
    LISP_MAX_FILE_BYTES = 8u * 1024u * 1024u,
    LISP_MAX_STRING_BYTES = 1024u * 1024u,
    LISP_MAX_EVAL_DEPTH = 1024,
    LISP_MAX_PRINT_DEPTH = 1024,
    LISP_MAX_SPAWN_ARGS = 64,
    LISP_PARSE_MESSAGE_BYTES = 160,
    LISP_REPL_LINE_BYTES = 4096,
    LISP_VOL_MIN = 0,
    LISP_VOL_MAX = 100,
    LISP_VOL_READ = -1,
    LISP_PALETTE_BYTES = 768
};

/**
 * Version string printed by --version and the REPL banner.
 */
static const char *lisp_version(void) {
    return "2.1";
}

typedef struct Runtime Runtime;
typedef struct Node Node;
typedef struct Env Env;
typedef struct Binding Binding;
typedef struct AllocTracker AllocTracker;

/**
 * Node type tag for every runtime value.
 */
typedef enum {
    TYPE_NIL,
    TYPE_NUM,
    TYPE_SYM,
    TYPE_STR,
    TYPE_CONS,
    TYPE_CLOSURE,
    TYPE_PRIM,
    TYPE_FILE,
    TYPE_ERROR
} NodeType;

/**
 * Primitive function signature shared by every builtin.
 */
typedef Node *(*PrimFn)(Runtime *, Node *);

/**
 * Parse outcome for one reader step.
 */
typedef enum {
    PARSE_OK,
    PARSE_EOF,
    PARSE_ERROR
} ParseStatus;

/**
 * Result of a single read step with a bounded diagnostic.
 */
typedef struct {
    ParseStatus status;
    Node *value;
    char message[LISP_PARSE_MESSAGE_BYTES];
} ParseResult;

/**
 * Runtime value node with one payload per type.
 */
struct Node {
    NodeType type;
    union {
        int64_t num;
        char *sym;
        char *str;
        struct {
            Node *car;
            Node *cdr;
        } pair;
        struct {
            Node *params;
            Node *body;
            Env *env;
        } closure;
        PrimFn prim;
        struct {
            FILE *handle;
            bool closed;
        } file;
        char *error;
    } as;
};

/**
 * Single name binding inside an environment frame.
 */
struct Binding {
    Node *symbol;
    Node *value;
    Binding *next;
};

/**
 * Lexical environment frame with a parent chain.
 */
struct Env {
    Env *parent;
    Binding *bindings;
};

/**
 * Allocation record so the whole heap frees at exit.
 */
struct AllocTracker {
    void *ptr;
    AllocTracker *next;
};

/**
 * Interpreter runtime with globals, streams and resource tables.
 */
struct Runtime {
    Node *nil;
    Node *true_value;
    Env *global;
    AllocTracker *allocations;
    FILE *out;
    FILE *err;
    FILE *in;
    FILE *open_files[LISP_MAX_OPEN_FILES];
    int eval_depth;
    int print_depth;
};

/**
 * Character cursor over an immutable source buffer.
 */
typedef struct {
    const char *data;
    size_t pos;
    size_t length;
    size_t line;
    size_t column;
} Reader;

/**
 * Growable byte buffer for tokens and strings.
 */
typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilder;

static void print_node(Runtime *rt, Node *node, bool readable);
static Node *eval(Runtime *rt, Node *expression, Env *env);
static ParseResult read_expr(Runtime *rt, Reader *reader);

/**
 * Raw 3-argument syscall through the x86-64 Linux ABI.
 */
static long msys(long n, long a1, long a2, long a3) {
    long ret;
    __asm__ volatile(
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3)
        : "rcx", "r11", "memory");
    return ret;
}

/**
 * Raw 5-argument syscall for SYS_SPAWN with path, redirect, argc, argv.
 */
static long msys5(long n, long a1, long a2, long a3, long a4, long a5) {
    long ret;
    register long r10 __asm__("r10") = a4;
    register long r8 __asm__("r8") = a5;
    __asm__ volatile(
        "syscall"
        : "=a"(ret)
        : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
        : "rcx", "r11", "memory");
    return ret;
}

/**
 * Report a fatal internal failure and terminate the process.
 */
static void fatal(Runtime *rt, const char *message) {
    FILE *err = rt && rt->err ? rt->err : stderr;
    fprintf(err, "fatal: %s\n", message);
    exit(EXIT_FAILURE);
}

/**
 * Allocate zeroed tracked memory that frees with the runtime.
 */
static void *xalloc(Runtime *rt, size_t size) {
    void *ptr;
    AllocTracker *tracker;
    if (size == 0) {
        size = 1;
    }
    ptr = calloc(1, size);
    if (!ptr) {
        fatal(rt, "out of memory");
    }
    tracker = malloc(sizeof *tracker);
    if (!tracker) {
        free(ptr);
        fatal(rt, "out of memory");
    }
    tracker->ptr = ptr;
    tracker->next = rt->allocations;
    rt->allocations = tracker;
    return ptr;
}

/**
 * Duplicate a string into tracked memory.
 */
static char *xstrdup(Runtime *rt, const char *source) {
    size_t length;
    char *copy;
    if (!source) {
        fatal(rt, "null string duplicate");
    }
    length = strlen(source) + 1;
    if (length > (size_t)LISP_MAX_STRING_BYTES + 1) {
        fatal(rt, "string exceeds bound");
    }
    copy = xalloc(rt, length);
    memcpy(copy, source, length);
    return copy;
}

/**
 * Allocate a node of the given type in tracked memory.
 */
static Node *make_node(Runtime *rt, NodeType type) {
    Node *node = xalloc(rt, sizeof *node);
    node->type = type;
    return node;
}

/**
 * Build an error value carrying a diagnostic message.
 */
static Node *make_error(Runtime *rt, const char *message) {
    Node *node = make_node(rt, TYPE_ERROR);
    node->as.error = xstrdup(rt, message ? message : "unknown error");
    return node;
}

/**
 * Build a numeric value node.
 */
static Node *make_num(Runtime *rt, int64_t value) {
    Node *node = make_node(rt, TYPE_NUM);
    node->as.num = value;
    return node;
}

/**
 * Build a string value node from a NUL-terminated source.
 */
static Node *make_str(Runtime *rt, const char *value) {
    Node *node = make_node(rt, TYPE_STR);
    node->as.str = xstrdup(rt, value ? value : "");
    return node;
}

/**
 * Build a symbol value node from a NUL-terminated name.
 */
static Node *make_sym(Runtime *rt, const char *value) {
    Node *node = make_node(rt, TYPE_SYM);
    node->as.sym = xstrdup(rt, value ? value : "");
    return node;
}

/**
 * Build a primitive function value node.
 */
static Node *make_prim(Runtime *rt, PrimFn function) {
    Node *node = make_node(rt, TYPE_PRIM);
    node->as.prim = function;
    return node;
}

/**
 * Build a cons cell from two values.
 */
static Node *cons(Runtime *rt, Node *car, Node *cdr) {
    Node *node = make_node(rt, TYPE_CONS);
    node->as.pair.car = car ? car : rt->nil;
    node->as.pair.cdr = cdr ? cdr : rt->nil;
    return node;
}

/**
 * Test whether a node is the empty list in any of its spellings.
 */
static bool is_nil(Runtime *rt, const Node *node) {
    return node == NULL || node == rt->nil || node->type == TYPE_NIL;
}

/**
 * Register an open FILE handle and wrap it in a file value node.
 */
static Node *make_file(Runtime *rt, FILE *handle) {
    size_t i;
    Node *node;
    if (!handle) {
        return make_error(rt, "null file handle");
    }
    for (i = 0; i < (size_t)LISP_MAX_OPEN_FILES; i++) {
        if (rt->open_files[i] == NULL) {
            node = make_node(rt, TYPE_FILE);
            node->as.file.handle = handle;
            node->as.file.closed = false;
            rt->open_files[i] = handle;
            return node;
        }
    }
    fclose(handle);
    return make_error(rt, "maximum number of open files exceeded");
}

/**
 * Close every tracked file and release every tracked allocation.
 */
static void cleanup(Runtime *rt) {
    size_t i;
    AllocTracker *current;
    for (i = 0; i < (size_t)LISP_MAX_OPEN_FILES; i++) {
        if (rt->open_files[i]) {
            fclose(rt->open_files[i]);
            rt->open_files[i] = NULL;
        }
    }
    current = rt->allocations;
    while (current) {
        AllocTracker *next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    rt->allocations = NULL;
}

/**
 * Initialize a runtime with streams, constants and empty tables.
 */
static void runtime_init(Runtime *rt) {
    memset(rt, 0, sizeof *rt);
    rt->out = stdout;
    rt->err = stderr;
    rt->in = stdin;
    rt->nil = make_node(rt, TYPE_NIL);
    rt->true_value = make_sym(rt, "t");
}

/**
 * Allocate a new environment frame with an optional parent.
 */
static Env *env_new(Runtime *rt, Env *parent) {
    Env *env = xalloc(rt, sizeof *env);
    env->parent = parent;
    env->bindings = NULL;
    return env;
}

/**
 * Bind a symbol to a value in the innermost frame.
 */
static void env_bind(Runtime *rt, Env *env, Node *symbol, Node *value) {
    Binding *binding = xalloc(rt, sizeof *binding);
    binding->symbol = symbol;
    binding->value = value;
    binding->next = env->bindings;
    env->bindings = binding;
}

/**
 * Update the nearest visible binding of a symbol.
 */
static bool env_set(Env *env, Node *symbol, Node *value) {
    Env *current;
    Binding *binding;
    if (!symbol || symbol->type != TYPE_SYM || !symbol->as.sym) {
        return false;
    }
    for (current = env; current; current = current->parent) {
        for (binding = current->bindings; binding; binding = binding->next) {
            if (binding->symbol && binding->symbol->type == TYPE_SYM &&
                binding->symbol->as.sym &&
                strcmp(binding->symbol->as.sym, symbol->as.sym) == 0) {
                binding->value = value;
                return true;
            }
        }
    }
    return false;
}

/**
 * Resolve the nearest visible binding of a symbol.
 */
static Node *env_lookup(Env *env, Node *symbol) {
    Env *current;
    Binding *binding;
    if (!symbol || symbol->type != TYPE_SYM || !symbol->as.sym) {
        return NULL;
    }
    for (current = env; current; current = current->parent) {
        for (binding = current->bindings; binding; binding = binding->next) {
            if (binding->symbol && binding->symbol->type == TYPE_SYM &&
                binding->symbol->as.sym &&
                strcmp(binding->symbol->as.sym, symbol->as.sym) == 0) {
                return binding->value;
            }
        }
    }
    return NULL;
}

/**
 * Peek at the current reader character without consuming it.
 */
static char reader_peek(const Reader *reader) {
    return reader->pos < reader->length ? reader->data[reader->pos] : '\0';
}

/**
 * Consume one reader character and track line and column.
 */
static char reader_next(Reader *reader) {
    char c;
    if (reader->pos >= reader->length) {
        return '\0';
    }
    c = reader->data[reader->pos++];
    if (c == '\n') {
        reader->line++;
        reader->column = 1;
    } else {
        reader->column++;
    }
    return c;
}

/**
 * Test whether the reader reached the end of its buffer.
 */
static bool reader_at_end(const Reader *reader) {
    return reader->pos >= reader->length;
}

/**
 * Skip whitespace and line comments starting with a semicolon.
 */
static void skip_space_and_comments(Reader *reader) {
    for (;;) {
        while (isspace((unsigned char)reader_peek(reader))) {
            reader_next(reader);
        }
        if (reader_peek(reader) != ';') {
            return;
        }
        while (!reader_at_end(reader) && reader_next(reader) != '\n') {
        }
    }
}

/**
 * Initialize a string builder with a bounded initial capacity.
 */
static void sb_init(StringBuilder *builder) {
    builder->capacity = (size_t)LISP_INITIAL_BUFFER_CAPACITY;
    builder->length = 0;
    builder->data = calloc(builder->capacity, 1);
    if (!builder->data) {
        fprintf(stderr, "fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Append one byte to a string builder with overflow-checked growth.
 */
static void sb_push(StringBuilder *builder, char value) {
    char *grown;
    size_t next;
    if (builder->length + 1 >= builder->capacity) {
        if (builder->capacity > (size_t)LISP_MAX_STRING_BYTES / 2) {
            free(builder->data);
            fprintf(stderr, "fatal: string exceeds bound\n");
            exit(EXIT_FAILURE);
        }
        next = builder->capacity * 2;
        grown = realloc(builder->data, next);
        if (!grown) {
            free(builder->data);
            fprintf(stderr, "fatal: out of memory\n");
            exit(EXIT_FAILURE);
        }
        builder->data = grown;
        builder->capacity = next;
    }
    builder->data[builder->length++] = value;
    builder->data[builder->length] = '\0';
}

/**
 * Build a successful parse result.
 */
static ParseResult parse_ok(Node *value) {
    ParseResult result;
    result.status = PARSE_OK;
    result.value = value;
    result.message[0] = '\0';
    return result;
}

/**
 * Build an end-of-input parse result.
 */
static ParseResult parse_eof(void) {
    ParseResult result;
    result.status = PARSE_EOF;
    result.value = NULL;
    result.message[0] = '\0';
    return result;
}

/**
 * Build a parse error result with a bounded message.
 */
static ParseResult parse_error(const char *message) {
    ParseResult result;
    result.status = PARSE_ERROR;
    result.value = NULL;
    snprintf(result.message, sizeof result.message, "%s",
        message ? message : "parse error");
    return result;
}

/**
 * Read a parenthesized list terminated by a closing paren.
 */
static ParseResult read_list(Runtime *rt, Reader *reader) {
    Node *head;
    Node **tail;
    reader_next(reader);
    head = rt->nil;
    tail = &head;
    for (;;) {
        ParseResult item;
        Node *cell;
        skip_space_and_comments(reader);
        if (reader_at_end(reader)) {
            return parse_error("unexpected EOF; expected ')'");
        }
        if (reader_peek(reader) == ')') {
            reader_next(reader);
            return parse_ok(head);
        }
        item = read_expr(rt, reader);
        if (item.status != PARSE_OK) {
            return item;
        }
        cell = cons(rt, item.value, rt->nil);
        *tail = cell;
        tail = &cell->as.pair.cdr;
    }
}

/**
 * Read a double-quoted string with backslash escapes.
 */
static ParseResult read_string(Runtime *rt, Reader *reader) {
    StringBuilder builder;
    Node *value;
    reader_next(reader);
    sb_init(&builder);
    while (!reader_at_end(reader)) {
        char c = reader_next(reader);
        if (c == '"') {
            if (builder.length > (size_t)LISP_MAX_STRING_BYTES) {
                free(builder.data);
                return parse_error("string exceeds bound");
            }
            value = make_str(rt, builder.data);
            free(builder.data);
            return parse_ok(value);
        }
        if (c == '\\') {
            if (reader_at_end(reader)) {
                free(builder.data);
                return parse_error("unterminated escape sequence");
            }
            c = reader_next(reader);
            switch (c) {
            case 'n':
                c = '\n';
                break;
            case 't':
                c = '\t';
                break;
            case 'r':
                c = '\r';
                break;
            case '\\':
                c = '\\';
                break;
            case '"':
                c = '"';
                break;
            default:
                break;
            }
        }
        sb_push(&builder, c);
    }
    free(builder.data);
    return parse_error("unexpected EOF; expected '\"'");
}

/**
 * Test whether a character terminates an atom token.
 */
static bool token_delimiter(char c) {
    return c == '\0' || isspace((unsigned char)c) || c == '(' ||
        c == ')' || c == '"' || c == ';';
}

/**
 * Read a number, nil, t or symbol token.
 */
static ParseResult read_atom(Runtime *rt, Reader *reader) {
    StringBuilder builder;
    Node *node;
    char *end = NULL;
    long long number = 0;
    sb_init(&builder);
    while (!token_delimiter(reader_peek(reader))) {
        sb_push(&builder, reader_next(reader));
    }
    if (builder.length == 0) {
        free(builder.data);
        return parse_error("expected expression");
    }
    errno = 0;
    number = strtoll(builder.data, &end, 10);
    if (errno == 0 && end != builder.data && *end == '\0') {
        if ((errno == ERANGE) || number > (long long)INT64_MAX ||
            number < (long long)INT64_MIN) {
            free(builder.data);
            return parse_error("integer literal out of range");
        }
        node = make_num(rt, (int64_t)number);
    } else if (strcmp(builder.data, "nil") == 0) {
        node = rt->nil;
    } else if (strcmp(builder.data, "t") == 0) {
        node = rt->true_value;
    } else {
        node = make_sym(rt, builder.data);
    }
    free(builder.data);
    return parse_ok(node);
}

/**
 * Read one expression, skipping whitespace and comments first.
 */
static ParseResult read_expr(Runtime *rt, Reader *reader) {
    ParseResult quoted;
    skip_space_and_comments(reader);
    if (reader_at_end(reader)) {
        return parse_eof();
    }
    switch (reader_peek(reader)) {
    case '(':
        return read_list(rt, reader);
    case ')':
        return parse_error("unexpected ')'");
    case '"':
        return read_string(rt, reader);
    case '\'':
        reader_next(reader);
        quoted = read_expr(rt, reader);
        if (quoted.status != PARSE_OK) {
            return quoted;
        }
        return parse_ok(cons(rt, make_sym(rt, "quote"),
            cons(rt, quoted.value, rt->nil)));
    default:
        return read_atom(rt, reader);
    }
}

/**
 * Count proper list elements and report whether the spine is proper.
 */
static size_t list_count(Runtime *rt, Node *list, bool *proper) {
    size_t count = 0;
    *proper = true;
    while (!is_nil(rt, list)) {
        if (list->type != TYPE_CONS) {
            *proper = false;
            return count;
        }
        count++;
        list = list->as.pair.cdr;
    }
    return count;
}

/**
 * Test whether an argument list has exactly the expected length.
 */
static bool has_arity(Runtime *rt, Node *args, size_t expected) {
    bool proper = false;
    return list_count(rt, args, &proper) == expected && proper;
}

/**
 * Fetch the positional argument at an index or NULL when absent.
 */
static Node *arg_at(Runtime *rt, Node *args, size_t index) {
    size_t i;
    for (i = 0; i < index; i++) {
        if (is_nil(rt, args) || args->type != TYPE_CONS) {
            return NULL;
        }
        args = args->as.pair.cdr;
    }
    if (is_nil(rt, args) || args->type != TYPE_CONS) {
        return NULL;
    }
    return args->as.pair.car;
}

/* =========================================================================
 * Generic argument checking
 * =========================================================================
 * Every primitive below used to hand-roll "right arity, right types, or
 * bail with a message" -- ~20 copies of the same three lines with small
 * variations. ArgKind + check_args() is that logic written once; a
 * primitive now just declares the shape of what it wants.
 *
 * arity0() covers the handful of primitives that take no arguments at all
 * (time-ms, rtc, fb-info), which is a degenerate case check_args() with
 * n == 0 could technically serve but reads oddly with an empty kinds[].
 * ========================================================================= */

/**
 * Expected type of one positional argument for check_args().
 */
typedef enum {
    ARG_ANY,   /* no type constraint, just "present" */
    ARG_NUM,   /* TYPE_NUM */
    ARG_STR,   /* TYPE_STR with a non-NULL payload */
    ARG_FILE   /* TYPE_FILE, open (not closed) */
} ArgKind;

/**
 * Test whether an already-fetched argument matches one ArgKind.
 */
static bool arg_matches(const Node *value, ArgKind kind) {
    if (!value) {
        return false;
    }
    switch (kind) {
    case ARG_NUM:
        return value->type == TYPE_NUM;
    case ARG_STR:
        return value->type == TYPE_STR && value->as.str != NULL;
    case ARG_FILE:
        return value->type == TYPE_FILE && !value->as.file.closed &&
            value->as.file.handle != NULL;
    case ARG_ANY:
    default:
        return true;
    }
}

/**
 * Validate that args is a proper list of exactly n elements whose types
 * match kinds[0..n), writing each fetched argument into out[0..n).
 *
 * Returns false (out[] left untouched) on any mismatch; the caller's one
 * job on failure is to pick the error message, since that is the only
 * part that legitimately differs between primitives.
 */
static bool check_args(Runtime *rt, Node *args, const ArgKind *kinds,
    size_t n, Node **out) {
    bool proper = false;
    size_t i;
    if (list_count(rt, args, &proper) != n || !proper) {
        return false;
    }
    for (i = 0; i < n; i++) {
        Node *value = arg_at(rt, args, i);
        if (!arg_matches(value, kinds[i])) {
            return false;
        }
        out[i] = value;
    }
    return true;
}

/**
 * Validate that args is the empty argument list.
 */
static bool arity0(Runtime *rt, Node *args) {
    bool proper = false;
    return list_count(rt, args, &proper) == 0 && proper;
}

/**
 * Add two numbers with overflow reported as an error value.
 */
static Node *prim_add(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    int64_t out;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "+ expects two numbers");
    }
    if (__builtin_add_overflow(v[0]->as.num, v[1]->as.num, &out)) {
        return make_error(rt, "integer overflow");
    }
    return make_num(rt, out);
}

/**
 * Subtract two numbers with overflow reported as an error value.
 */
static Node *prim_sub(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    int64_t out;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "- expects two numbers");
    }
    if (__builtin_sub_overflow(v[0]->as.num, v[1]->as.num, &out)) {
        return make_error(rt, "integer overflow");
    }
    return make_num(rt, out);
}

/**
 * Multiply two numbers with overflow reported as an error value.
 */
static Node *prim_mul(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    int64_t out;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "* expects two numbers");
    }
    if (__builtin_mul_overflow(v[0]->as.num, v[1]->as.num, &out)) {
        return make_error(rt, "integer overflow");
    }
    return make_num(rt, out);
}

/**
 * Divide two numbers with zero and overflow reported as errors.
 */
static Node *prim_div(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    int64_t a;
    int64_t b;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "/ expects two numbers");
    }
    a = v[0]->as.num;
    b = v[1]->as.num;
    if (b == 0) {
        return make_error(rt, "division by zero");
    }
    if (a == INT64_MIN && b == -1) {
        return make_error(rt, "integer overflow");
    }
    return make_num(rt, a / b);
}

/**
 * Compare two numbers for equality.
 */
static Node *prim_eq(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "= expects two numbers");
    }
    return v[0]->as.num == v[1]->as.num ? rt->true_value : rt->nil;
}

/**
 * Compare two numbers with less-than.
 */
static Node *prim_lt(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "< expects two numbers");
    }
    return v[0]->as.num < v[1]->as.num ? rt->true_value : rt->nil;
}

/**
 * Return the first element of a cons cell or nil.
 */
static Node *prim_car(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "car expects one argument");
    }
    return v[0]->type == TYPE_CONS ? v[0]->as.pair.car : rt->nil;
}

/**
 * Return the rest of a cons cell or nil.
 */
static Node *prim_cdr(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "cdr expects one argument");
    }
    return v[0]->type == TYPE_CONS ? v[0]->as.pair.cdr : rt->nil;
}

/**
 * Build a cons cell from two values.
 */
static Node *prim_cons(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_ANY, ARG_ANY };
    Node *v[2];
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "cons expects two arguments");
    }
    return cons(rt, v[0], v[1]);
}

/**
 * Concatenate two strings with an overflow-checked allocation.
 */
static Node *prim_string_concat(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_STR, ARG_STR };
    Node *v[2];
    size_t la;
    size_t lb;
    char *data;
    Node *result;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "string-concat expects two arguments");
    }
    la = strlen(v[0]->as.str);
    lb = strlen(v[1]->as.str);
    if (la > (size_t)LISP_MAX_STRING_BYTES ||
        lb > (size_t)LISP_MAX_STRING_BYTES - la) {
        return make_error(rt, "string exceeds bound");
    }
    data = xalloc(rt, la + lb + 1);
    memcpy(data, v[0]->as.str, la);
    memcpy(data + la, v[1]->as.str, lb + 1);
    result = make_node(rt, TYPE_STR);
    result->as.str = data;
    return result;
}

/**
 * Compare two strings for equality.
 */
static Node *prim_string_eq(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_STR, ARG_STR };
    Node *v[2];
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "string-eq expects two arguments");
    }
    return strcmp(v[0]->as.str, v[1]->as.str) == 0 ? rt->true_value : rt->nil;
}

/**
 * Return the byte length of a string.
 */
static Node *prim_string_length(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_STR };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "string-length expects one string");
    }
    return make_num(rt, (int64_t)strlen(v[0]->as.str));
}

/**
 * Return the one-character string at a byte index or nil when out of range.
 */
static Node *prim_string_at(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_STR, ARG_NUM };
    Node *v[2];
    int64_t position;
    size_t length;
    char value[2];
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "string-at expects string and index");
    }
    position = v[1]->as.num;
    length = strlen(v[0]->as.str);
    if (position < 0 || (uint64_t)position >= length) {
        return rt->nil;
    }
    value[0] = v[0]->as.str[position];
    value[1] = '\0';
    return make_str(rt, value);
}

/**
 * Convert between a one-character string and its byte value.
 */
static Node *prim_char_code(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    char result[2];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "char-code expects one argument");
    }
    if (v[0]->type == TYPE_STR && v[0]->as.str && v[0]->as.str[0]) {
        return make_num(rt, (unsigned char)v[0]->as.str[0]);
    }
    if (v[0]->type == TYPE_NUM && v[0]->as.num >= 0 &&
        v[0]->as.num <= (int64_t)UCHAR_MAX) {
        result[0] = (char)v[0]->as.num;
        result[1] = '\0';
        return make_str(rt, result);
    }
    return make_error(rt, "char-code expects a non-empty string or byte value");
}

/**
 * Print a value without a trailing newline.
 */
static Node *prim_print(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "print expects one argument");
    }
    print_node(rt, v[0], false);
    fflush(rt->out);
    return rt->nil;
}

/**
 * Print a value with a trailing newline.
 */
static Node *prim_println(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "println expects one argument");
    }
    print_node(rt, v[0], false);
    fputc('\n', rt->out);
    fflush(rt->out);
    return rt->nil;
}

/**
 * Test whether a file mode string belongs to the safe whitelist.
 */
static bool file_mode_allowed(const char *mode) {
    static const char *const allowed[] = {
        "r", "rb", "w", "wb", "a", "ab"
    };
    size_t i;
    if (!mode) {
        return false;
    }
    for (i = 0; i < sizeof allowed / sizeof allowed[0]; i++) {
        if (strcmp(mode, allowed[i]) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Open a file with a whitelisted mode string.
 *
 * Variable arity (1 or 2), so this stays outside check_args() rather
 * than forcing a fixed-arity helper to grow an "optional" concept it
 * doesn't otherwise need.
 */
static Node *prim_open_file(Runtime *rt, Node *args) {
    Node *path;
    const char *mode = "r";
    bool proper = false;
    size_t count;
    FILE *handle;
    if (!args) {
        return make_error(rt, "open-file expects path and optional mode");
    }
    count = list_count(rt, args, &proper);
    if (!proper || (count != 1 && count != 2)) {
        return make_error(rt, "open-file expects path and optional mode");
    }
    path = arg_at(rt, args, 0);
    if (!arg_matches(path, ARG_STR)) {
        return make_error(rt, "open-file expects a string path");
    }
    if (count == 2) {
        Node *mode_node = arg_at(rt, args, 1);
        if (!arg_matches(mode_node, ARG_STR)) {
            return make_error(rt, "file mode must be a string");
        }
        mode = mode_node->as.str;
    }
    if (!file_mode_allowed(mode)) {
        return make_error(rt, "file mode not allowed");
    }
    handle = fopen(path->as.str, mode);
    if (!handle) {
        return make_error(rt, "could not open file");
    }
    return make_file(rt, handle);
}

/**
 * Read one byte from a file or nil at end of file.
 */
static Node *prim_read_char(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_FILE };
    Node *v[1];
    int value;
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "read-char expects an open file");
    }
    value = fgetc(v[0]->as.file.handle);
    if (value == EOF) {
        return rt->nil;
    }
    return make_num(rt, value);
}

/**
 * Write a string or byte value to an open file.
 */
static Node *prim_write(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_FILE, ARG_ANY };
    Node *v[2];
    int result;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "write expects an open file and a value");
    }
    if (v[1]->type == TYPE_STR && v[1]->as.str) {
        result = fputs(v[1]->as.str, v[0]->as.file.handle);
    } else if (v[1]->type == TYPE_NUM && v[1]->as.num >= 0 &&
        v[1]->as.num <= (int64_t)UCHAR_MAX) {
        result = fputc((unsigned char)v[1]->as.num, v[0]->as.file.handle);
    } else {
        return make_error(rt, "write expects a string or byte");
    }
    if (result == EOF || fflush(v[0]->as.file.handle) != 0) {
        return make_error(rt, "file write failed");
    }
    return rt->true_value;
}

/**
 * Close an open file and release its runtime slot.
 */
static Node *prim_close_file(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_FILE };
    Node *v[1];
    FILE *handle;
    size_t i;
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "close-file expects an open file");
    }
    handle = v[0]->as.file.handle;
    if (fclose(handle) != 0) {
        return make_error(rt, "file close failed");
    }
    for (i = 0; i < (size_t)LISP_MAX_OPEN_FILES; i++) {
        if (rt->open_files[i] == handle) {
            rt->open_files[i] = NULL;
        }
    }
    v[0]->as.file.handle = NULL;
    v[0]->as.file.closed = true;
    return rt->true_value;
}

/**
 * Test whether a value is nil.
 */
static Node *prim_null_p(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "null? expects one argument");
    }
    return is_nil(rt, v[0]) ? rt->true_value : rt->nil;
}

/**
 * Test whether a value is a number.
 */
static Node *prim_number_p(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "number? expects one argument");
    }
    return v[0]->type == TYPE_NUM ? rt->true_value : rt->nil;
}

/**
 * Test whether a value is a string.
 */
static Node *prim_string_p(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "string? expects one argument");
    }
    return v[0]->type == TYPE_STR ? rt->true_value : rt->nil;
}

/**
 * Return the message of an error value or nil for other values.
 */
static Node *prim_error_message(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_ANY };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "error-message expects one argument");
    }
    if (v[0]->type != TYPE_ERROR) {
        return rt->nil;
    }
    return make_str(rt, v[0]->as.error ? v[0]->as.error : "unknown");
}

/**
 * Terminate the process with a numeric exit status.
 *
 * Variable arity (0 or 1); stays outside check_args() for the same
 * reason open-file does.
 */
static Node *prim_exit(Runtime *rt, Node *args) {
    bool proper = false;
    size_t count;
    Node *value;
    count = list_count(rt, args, &proper);
    if (!proper || (count != 0 && count != 1)) {
        return make_error(rt, "exit expects nothing or one number");
    }
    if (count == 0) {
        cleanup(rt);
        exit(EXIT_SUCCESS);
    }
    value = arg_at(rt, args, 0);
    if (!arg_matches(value, ARG_NUM)) {
        return make_error(rt, "exit expects a number");
    }
    {
        int status = value->as.num >= 0 && value->as.num <= 255 ?
            (int)value->as.num : EXIT_FAILURE;
        cleanup(rt);
        exit(status);
    }
}

/**
 * Return milliseconds since boot through the kernel time service.
 */
static Node *prim_time_ms(Runtime *rt, Node *args) {
    if (!arity0(rt, args)) {
        return make_error(rt, "time-ms expects no arguments");
    }
    return make_num(rt, (int64_t)msys((long)MINIOS_SYS_TIME, 0, 0, 0));
}

/**
 * Return the clock time as a three-element list or nil when unavailable.
 */
static Node *prim_rtc(Runtime *rt, Node *args) {
    int h = 0;
    int m = 0;
    int s = 0;
    if (!arity0(rt, args)) {
        return make_error(rt, "rtc expects no arguments");
    }
    if (msys((long)MINIOS_SYS_RTC, (long)&h, (long)&m, (long)&s) < 0) {
        return rt->nil;
    }
    return cons(rt, make_num(rt, h),
        cons(rt, make_num(rt, m), cons(rt, make_num(rt, s), rt->nil)));
}

/**
 * Return framebuffer width, height and pitch or nil when unavailable.
 */
static Node *prim_fb_info(Runtime *rt, Node *args) {
    int w = 0;
    int h = 0;
    int p = 0;
    if (!arity0(rt, args)) {
        return make_error(rt, "fb-info expects no arguments");
    }
    if (msys((long)MINIOS_SYS_FB_INFO, (long)&w, (long)&h, (long)&p) < 0) {
        return rt->nil;
    }
    return cons(rt, make_num(rt, w),
        cons(rt, make_num(rt, h), cons(rt, make_num(rt, p), rt->nil)));
}

/**
 * Read or set the speaker volume, clamped to the valid range.
 *
 * Variable arity (0 or 1); stays outside check_args() for the same
 * reason open-file does.
 */
static Node *prim_vol(Runtime *rt, Node *args) {
    bool proper = false;
    size_t count;
    Node *value;
    count = list_count(rt, args, &proper);
    if (!proper || (count != 0 && count != 1)) {
        return make_error(rt, "vol expects nothing or one number");
    }
    if (count == 0) {
        return make_num(rt,
            (int64_t)msys((long)MINIOS_SYS_PCSPK_VOL,
                (long)LISP_VOL_READ, 0, 0));
    }
    value = arg_at(rt, args, 0);
    if (!arg_matches(value, ARG_NUM)) {
        return make_error(rt, "vol expects a number");
    }
    if (value->as.num < (int64_t)LISP_VOL_MIN ||
        value->as.num > (int64_t)LISP_VOL_MAX) {
        return make_error(rt, "volume must be 0..100");
    }
    return make_num(rt,
        (int64_t)msys((long)MINIOS_SYS_PCSPK_VOL, (long)value->as.num, 0, 0));
}

/**
 * Load a 768-byte VGA palette from a string value.
 */
static Node *prim_pal(Runtime *rt, Node *args) {
    static const ArgKind kinds[1] = { ARG_STR };
    Node *v[1];
    if (!check_args(rt, args, kinds, 1, v)) {
        return make_error(rt, "pal expects one string");
    }
    if (strlen(v[0]->as.str) < (size_t)LISP_PALETTE_BYTES) {
        return make_error(rt, "palette must be 768 bytes");
    }
    msys((long)MINIOS_SYS_PALETTE, (long)v[0]->as.str, 0, 0);
    return rt->nil;
}

/**
 * Play a speaker tone for a bounded millisecond duration.
 */
static Node *prim_pcspeaker(Runtime *rt, Node *args) {
    static const ArgKind kinds[2] = { ARG_NUM, ARG_NUM };
    Node *v[2];
    long freq;
    long span;
    uint32_t start;
    if (!check_args(rt, args, kinds, 2, v)) {
        return make_error(rt, "pcspeaker expects frequency and ms");
    }
    if (v[1]->as.num < 0 || v[1]->as.num > 60000) {
        return make_error(rt, "pcspeaker duration out of range");
    }
    freq = (long)v[0]->as.num;
    span = (long)v[1]->as.num;
    msys((long)MINIOS_SYS_PCSPK_INIT, 0, 0, 0);
    msys((long)MINIOS_SYS_PCSPK_TONE, freq, 0, 0);
    start = (uint32_t)msys((long)MINIOS_SYS_TIME, 0, 0, 0);
    while ((uint32_t)msys((long)MINIOS_SYS_TIME, 0, 0, 0) - start <
        (uint32_t)span) {
    }
    msys((long)MINIOS_SYS_PCSPK_TONE, 0, 0, 0);
    return rt->nil;
}

/**
 * Quit the REPL cleanly by returning from the repl() function.
 * Note: This only works if called within the REPL loop context.
 * For a standalone script, use (quit).
 */
static Node *prim_quit(Runtime *rt, Node *args) {
    if (!arity0(rt, args)) {
        return make_error(rt, "quit expects no arguments");
    }
    // In a real REPL implementation, we might set a flag to break the loop.
    // Since our repl() is a simple loop, we can just call exit for simplicity
    // or rely on the user typing Ctrl+D. 
    // However, to make it explicit as requested:
    cleanup(rt);
    exit(EXIT_SUCCESS);
}

/**
 * Run a program through SYS_SPAWN and return its exit code.
 */
static Node *prim_minios_run(Runtime *rt, Node *args) {
    bool proper = false;
    size_t count;
    Node *path;
    Node *arg_list;
    Node *redir_node;
    const char *argv[LISP_MAX_SPAWN_ARGS + 1];
    const char *redir = NULL;
    size_t n = 0;
    Node *cursor;
    long ret;
    count = list_count(rt, args, &proper);
    if (!proper || (count != 1 && count != 2 && count != 3)) {
        return make_error(rt, "minios-run expects path, args and redirect");
    }
    path = arg_at(rt, args, 0);
    if (!arg_matches(path, ARG_STR)) {
        return make_error(rt, "minios-run expects a string path");
    }
    arg_list = count >= 2 ? arg_at(rt, args, 1) : rt->nil;
    redir_node = count >= 3 ? arg_at(rt, args, 2) : rt->nil;
    argv[0] = path->as.str;
    cursor = arg_list;
    if (!is_nil(rt, cursor)) {
        while (!is_nil(rt, cursor)) {
            Node *item;
            if (cursor->type != TYPE_CONS) {
                return make_error(rt, "minios-run args must be a list");
            }
            item = cursor->as.pair.car;
            if (!arg_matches(item, ARG_STR)) {
                return make_error(rt, "minios-run args must be strings");
            }
            if (n + 1 >= (size_t)LISP_MAX_SPAWN_ARGS) {
                return make_error(rt, "too many args");
            }
            argv[n + 1] = item->as.str;
            n++;
            cursor = cursor->as.pair.cdr;
        }
    }
    if (!is_nil(rt, redir_node)) {
        if (!arg_matches(redir_node, ARG_STR)) {
            return make_error(rt, "minios-run redirect must be a string");
        }
        redir = redir_node->as.str;
    }
    argv[n + 1] = NULL;
    ret = msys5((long)MINIOS_SYS_SPAWN, (long)path->as.str, (long)redir,
        (long)(n + 1), (long)argv, 0);
    if (ret < 0) {
        return make_error(rt, "spawn failed");
    }
    return make_num(rt, (int64_t)ret);
}

/**
 * Evaluate every element of a list into a fresh proper list.
 *
 * Error results travel as ordinary values so programs can inspect them
 * with error-message; only a hard evaluation failure aborts the walk.
 */
static Node *eval_list(Runtime *rt, Node *list, Env *env) {
    Node *head = rt->nil;
    Node **tail = &head;
    while (!is_nil(rt, list)) {
        Node *value;
        Node *cell;
        if (list->type != TYPE_CONS) {
            return make_error(rt, "improper argument list");
        }
        value = eval(rt, list->as.pair.car, env);
        if (!value) {
            return make_error(rt, "evaluation failed");
        }
        cell = cons(rt, value, rt->nil);
        *tail = cell;
        tail = &cell->as.pair.cdr;
        list = list->as.pair.cdr;
    }
    return head;
}

/**
 * Evaluate a body sequence and return the last value.
 */
static Node *eval_sequence(Runtime *rt, Node *body, Env *env) {
    Node *result = rt->nil;
    while (!is_nil(rt, body)) {
        if (body->type != TYPE_CONS) {
            return make_error(rt, "improper body list");
        }
        result = eval(rt, body->as.pair.car, env);
        if (!result || result->type == TYPE_ERROR) {
            return result ? result : make_error(rt, "evaluation failed");
        }
        body = body->as.pair.cdr;
    }
    return result;
}

/**
 * Test whether a parameter list holds only symbols.
 */
static bool valid_params(Runtime *rt, Node *params) {
    while (!is_nil(rt, params)) {
        if (params->type != TYPE_CONS || !params->as.pair.car ||
            params->as.pair.car->type != TYPE_SYM) {
            return false;
        }
        params = params->as.pair.cdr;
    }
    return true;
}

/**
 * Evaluate an expression with tail-call reuse and a bounded depth.
 */
static Node *eval(Runtime *rt, Node *expression, Env *env) {
    bool entered = false;
    Node *result = NULL;
    for (;;) {
        Node *operator;
        Node *args;
        Node *function;
        Node *evaluated_args;
        const char *name;
        if (!entered) {
            if (rt->eval_depth >= (int)LISP_MAX_EVAL_DEPTH) {
                return make_error(rt, "evaluation depth exceeded");
            }
            rt->eval_depth++;
            entered = true;
        }
        if (is_nil(rt, expression)) {
            result = rt->nil;
            break;
        }
        if (expression->type == TYPE_NUM || expression->type == TYPE_STR ||
            expression->type == TYPE_FILE ||
            expression->type == TYPE_CLOSURE ||
            expression->type == TYPE_PRIM ||
            expression->type == TYPE_ERROR) {
            result = expression;
            break;
        }
        if (expression->type == TYPE_SYM) {
            Node *value = env_lookup(env, expression);
            result = value ? value : make_error(rt, "unbound symbol");
            break;
        }
        if (expression->type == TYPE_NIL) {
            result = rt->nil;
            break;
        }
        if (expression->type != TYPE_CONS) {
            result = make_error(rt, "invalid expression");
            break;
        }
        operator = expression->as.pair.car;
        args = expression->as.pair.cdr;
        if (!operator) {
            result = make_error(rt, "invalid expression");
            break;
        }
        if (operator->type == TYPE_SYM && operator->as.sym) {
            name = operator->as.sym;
            if (strcmp(name, "quote") == 0) {
                if (!has_arity(rt, args, 1)) {
                    result = make_error(rt, "quote expects one argument");
                    break;
                }
                result = arg_at(rt, args, 0);
                if (!result) {
                    result = make_error(rt, "quote expects one argument");
                }
                break;
            }
            if (strcmp(name, "if") == 0) {
                bool proper = false;
                size_t count = list_count(rt, args, &proper);
                Node *condition;
                if (!proper || (count != 2 && count != 3)) {
                    result = make_error(rt, "if expects two or three arguments");
                    break;
                }
                condition = eval(rt, arg_at(rt, args, 0), env);
                if (!condition || condition->type == TYPE_ERROR) {
                    result = condition ?
                        condition : make_error(rt, "evaluation failed");
                    break;
                }
                expression = !is_nil(rt, condition) ?
                    arg_at(rt, args, 1) :
                    (count == 3 ? arg_at(rt, args, 2) : rt->nil);
                continue;
            }
            if (strcmp(name, "begin") == 0) {
                result = eval_sequence(rt, args, env);
                break;
            }
            if (strcmp(name, "define") == 0) {
                Node *symbol;
                Node *value;
                if (!has_arity(rt, args, 2)) {
                    result = make_error(rt, "define expects symbol and value");
                    break;
                }
                symbol = arg_at(rt, args, 0);
                if (!symbol || symbol->type != TYPE_SYM) {
                    result = make_error(rt, "define requires a symbol");
                    break;
                }
                value = eval(rt, arg_at(rt, args, 1), env);
                if (!value) {
                    result = make_error(rt, "evaluation failed");
                    break;
                }
                env_bind(rt, env, symbol, value);
                result = symbol;
                break;
            }
            if (strcmp(name, "set!") == 0) {
                Node *symbol;
                Node *value;
                if (!has_arity(rt, args, 2)) {
                    result = make_error(rt, "set! expects symbol and value");
                    break;
                }
                symbol = arg_at(rt, args, 0);
                if (!symbol || symbol->type != TYPE_SYM) {
                    result = make_error(rt, "set! requires a symbol");
                    break;
                }
                value = eval(rt, arg_at(rt, args, 1), env);
                if (!value) {
                    result = make_error(rt, "evaluation failed");
                    break;
                }
                if (!env_set(env, symbol, value)) {
                    result = make_error(rt, "set! on unbound symbol");
                    break;
                }
                result = value;
                break;
            }
            if (strcmp(name, "lambda") == 0) {
                bool proper = false;
                size_t count = list_count(rt, args, &proper);
                Node *params;
                Node *closure;
                if (!proper || count < 2) {
                    result = make_error(rt,
                        "lambda expects parameters and body");
                    break;
                }
                params = arg_at(rt, args, 0);
                if (!valid_params(rt, params)) {
                    result = make_error(rt, "invalid lambda parameters");
                    break;
                }
                closure = make_node(rt, TYPE_CLOSURE);
                closure->as.closure.params = params;
                closure->as.closure.body = args->as.pair.cdr;
                closure->as.closure.env = env;
                result = closure;
                break;
            }
            if (strcmp(name, "let") == 0) {
                bool proper = false;
                size_t count = list_count(rt, args, &proper);
                Node *bindings;
                Env *local;
                if (!proper || count < 2) {
                    result = make_error(rt,
                        "let expects bindings and body");
                    break;
                }
                bindings = arg_at(rt, args, 0);
                local = env_new(rt, env);
                result = NULL;
                while (!is_nil(rt, bindings)) {
                    Node *binding;
                    Node *symbol;
                    Node *value;
                    if (bindings->type != TYPE_CONS) {
                        result = make_error(rt, "invalid let bindings");
                        break;
                    }
                    binding = bindings->as.pair.car;
                    if (!binding || binding->type != TYPE_CONS ||
                        !has_arity(rt, binding, 2)) {
                        result = make_error(rt, "invalid let binding");
                        break;
                    }
                    symbol = arg_at(rt, binding, 0);
                    if (!symbol || symbol->type != TYPE_SYM) {
                        result = make_error(rt,
                            "let binding requires symbol");
                        break;
                    }
                    value = eval(rt, arg_at(rt, binding, 1), env);
                    if (!value) {
                        result = make_error(rt, "evaluation failed");
                        break;
                    }
                    env_bind(rt, local, symbol, value);
                    bindings = bindings->as.pair.cdr;
                }
                if (result) {
                    break;
                }
                result = eval_sequence(rt, args->as.pair.cdr, local);
                break;
            }
        }
        function = eval(rt, operator, env);
        if (!function || function->type == TYPE_ERROR) {
            result = function ?
                function : make_error(rt, "evaluation failed");
            break;
        }
        evaluated_args = eval_list(rt, args, env);
        if (!evaluated_args || evaluated_args->type == TYPE_ERROR) {
            result = evaluated_args ?
                evaluated_args : make_error(rt, "evaluation failed");
            break;
        }
        if (function->type == TYPE_PRIM) {
            if (!function->as.prim) {
                result = make_error(rt, "invalid primitive");
                break;
            }
            result = function->as.prim(rt, evaluated_args);
            break;
        }
        if (function->type == TYPE_CLOSURE) {
            Node *params = function->as.closure.params;
            Node *body = function->as.closure.body;
            bool params_proper = false;
            bool args_proper = false;
            size_t parameter_count = list_count(rt, params, &params_proper);
            size_t argument_count =
                list_count(rt, evaluated_args, &args_proper);
            Env *local;
            if (!params_proper || !args_proper ||
                parameter_count != argument_count) {
                result = make_error(rt, "wrong number of arguments");
                break;
            }
            local = env_new(rt, function->as.closure.env);
            while (!is_nil(rt, params)) {
                env_bind(rt, local, params->as.pair.car,
                    evaluated_args->as.pair.car);
                params = params->as.pair.cdr;
                evaluated_args = evaluated_args->as.pair.cdr;
            }
            if (!body || body->type != TYPE_CONS) {
                result = make_error(rt, "invalid closure body");
                break;
            }
            if (body->as.pair.cdr == rt->nil) {
                env = local;
                expression = body->as.pair.car;
                continue;
            }
            result = eval_sequence(rt, body, local);
            break;
        }
        result = make_error(rt, "attempt to call a non-function");
        break;
    }
    if (entered) {
        rt->eval_depth--;
    }
    return result ? result : make_error(rt, "evaluation failed");
}

/**
 * Write a string with escape sequences for readable output.
 */
static void print_escaped_string(FILE *out, const char *value) {
    const unsigned char *p;
    fputc('"', out);
    for (p = (const unsigned char *)value; *p; p++) {
        switch (*p) {
        case '\n':
            fputs("\\n", out);
            break;
        case '\t':
            fputs("\\t", out);
            break;
        case '\r':
            fputs("\\r", out);
            break;
        case '\\':
            fputs("\\\\", out);
            break;
        case '"':
            fputs("\\\"", out);
            break;
        default:
            fputc(*p, out);
            break;
        }
    }
    fputc('"', out);
}

/**
 * Print a value in readable or display form with a bounded depth.
 */
static void print_node(Runtime *rt, Node *node, bool readable) {
    bool entered = false;
    if (rt->print_depth >= (int)LISP_MAX_PRINT_DEPTH) {
        fputs("<depth-exceeded>", rt->out);
        return;
    }
    rt->print_depth++;
    entered = true;
    if (is_nil(rt, node)) {
        fputs("nil", rt->out);
    } else if (!node) {
        fputs("nil", rt->out);
    } else switch (node->type) {
    case TYPE_NUM:
        fprintf(rt->out, "%" PRId64, node->as.num);
        break;
    case TYPE_SYM:
        fputs(node->as.sym ? node->as.sym : "?", rt->out);
        break;
    case TYPE_STR:
        if (!node->as.str) {
            fputs("\"\"", rt->out);
        } else if (readable) {
            print_escaped_string(rt->out, node->as.str);
        } else {
            fputs(node->as.str, rt->out);
        }
        break;
    case TYPE_ERROR:
        fprintf(rt->out, "<error: %s>",
            node->as.error ? node->as.error : "unknown");
        break;
    case TYPE_PRIM:
    case TYPE_CLOSURE:
        fputs("<function>", rt->out);
        break;
    case TYPE_FILE:
        fputs(node->as.file.closed ? "<closed-file>" : "<file>", rt->out);
        break;
    case TYPE_NIL:
        fputs("nil", rt->out);
        break;
    case TYPE_CONS: {
        Node *current = node;
        bool first = true;
        fputc('(', rt->out);
        while (!is_nil(rt, current)) {
            if (!current || current->type != TYPE_CONS) {
                fputs(" . ", rt->out);
                print_node(rt, current, readable);
                break;
            }
            if (!first) {
                fputc(' ', rt->out);
            }
            print_node(rt, current->as.pair.car, readable);
            first = false;
            current = current->as.pair.cdr;
        }
        fputc(')', rt->out);
        break;
    }
    }
    if (entered) {
        rt->print_depth--;
    }
}

/**
 * Register one named primitive in an environment frame.
 */
static void bind_primitive(Runtime *rt, Env *env, const char *name,
    PrimFn function) {
    env_bind(rt, env, make_sym(rt, name), make_prim(rt, function));
}

/* =========================================================================
 * Primitive registry
 * =========================================================================
 * A flat name -> function table instead of ~30 repeated bind_primitive()
 * calls. Adding a builtin is now one row here; init_env() itself never
 * needs to change again to register it.
 * ========================================================================= */
typedef struct {
    const char *name;
    PrimFn fn;
} PrimEntry;

static const PrimEntry PRIMITIVES[] = {
    { "+", prim_add },
    { "-", prim_sub },
    { "*", prim_mul },
    { "/", prim_div },
    { "=", prim_eq },
    { "<", prim_lt },
    { "car", prim_car },
    { "cdr", prim_cdr },
    { "cons", prim_cons },
    { "null?", prim_null_p },
    { "number?", prim_number_p },
    { "string?", prim_string_p },
    { "error-message", prim_error_message },
    { "string-concat", prim_string_concat },
    { "string-eq", prim_string_eq },
    { "string-length", prim_string_length },
    { "string-at", prim_string_at },
    { "char-code", prim_char_code },
    { "print", prim_print },
    { "println", prim_println },
    { "open-file", prim_open_file },
    { "read-char", prim_read_char },
    { "write", prim_write },
    { "close-file", prim_close_file },
    { "exit", prim_exit },
    { "time-ms", prim_time_ms },
    { "rtc", prim_rtc },
    { "fb-info", prim_fb_info },
    { "vol", prim_vol },
    { "pal", prim_pal },
    { "pcspeaker", prim_pcspeaker },
    { "exit", prim_exit },
    { "quit", prim_quit },
    { "minios-run", prim_minios_run }
};

/**
 * Build the global environment with arithmetic, strings, files and MiniOS.
 */
static Env *init_env(Runtime *rt) {
    Env *env = env_new(rt, NULL);
    size_t i;
    env_bind(rt, env, rt->true_value, rt->true_value);
    for (i = 0; i < sizeof PRIMITIVES / sizeof PRIMITIVES[0]; i++) {
        bind_primitive(rt, env, PRIMITIVES[i].name, PRIMITIVES[i].fn);
    }
    return env;
}

/**
 * Expose the script argument vector as a proper list of strings.
 */
static void bind_argv(Runtime *rt, Env *env, int argc, char **argv, int first) {
    Node *head = rt->nil;
    int i;
    for (i = argc - 1; i >= first; i--) {
        head = cons(rt, make_str(rt, argv[i] ? argv[i] : ""), head);
    }
    env_bind(rt, env, make_sym(rt, "*argv*"), head);
}

/**
 * Read a whole file into memory with a hard size cap.
 */
static char *read_all_file(const char *filename, size_t max_bytes) {
    FILE *file = fopen(filename, "rb");
    size_t length = 0;
    size_t capacity = (size_t)LISP_INITIAL_INPUT_CAPACITY;
    char *data;
    if (!file) {
        return NULL;
    }
    data = malloc(capacity + 1);
    if (!data) {
        fclose(file);
        return NULL;
    }
    for (;;) {
        size_t count;
        char *grown;
        size_t next;
        if (length == capacity) {
            if (capacity > max_bytes / 2) {
                free(data);
                fclose(file);
                return NULL;
            }
            next = capacity * 2;
            if (next > max_bytes) {
                next = max_bytes;
            }
            grown = realloc(data, next + 1);
            if (!grown) {
                free(data);
                fclose(file);
                return NULL;
            }
            data = grown;
            capacity = next;
        }
        count = fread(data + length, 1, capacity - length, file);
        length += count;
        if (count == 0) {
            break;
        }
        if (length >= max_bytes) {
            break;
        }
    }
    if (ferror(file)) {
        free(data);
        fclose(file);
        return NULL;
    }
    data[length] = '\0';
    fclose(file);
    return data;
}

/**
 * Evaluate every form in a source buffer and report the first failure.
 */
static int process_source(Runtime *rt, const char *source,
    const char *source_name, bool echo) {
    Reader reader;
    int status = EXIT_SUCCESS;
    reader.data = source;
    reader.pos = 0;
    reader.length = strlen(source);
    reader.line = 1;
    reader.column = 1;
    for (;;) {
        ParseResult parsed = read_expr(rt, &reader);
        Node *result;
        if (parsed.status == PARSE_EOF) {
            break;
        }
        if (parsed.status == PARSE_ERROR) {
            fprintf(rt->err, "%s:%zu:%zu: parse error: %s\n", source_name,
                reader.line, reader.column, parsed.message);
            return EXIT_FAILURE;
        }
        result = eval(rt, parsed.value, rt->global);
        if (!result) {
            fprintf(rt->err, "%s: evaluation failed\n", source_name);
            return EXIT_FAILURE;
        }
        if (result->type == TYPE_ERROR) {
            fprintf(rt->err, "%s: %s\n", source_name,
                result->as.error ? result->as.error : "error");
            status = EXIT_FAILURE;
            continue;
        }
        if (echo) {
            print_node(rt, result, true);
            fputc('\n', rt->out);
        }
    }
    return status;
}

/**
 * Evaluate one inline expression from the -e flag.
 */
static int process_inline(Runtime *rt, const char *code) {
    return process_source(rt, code, "-e", true);
}

/**
 * Print usage for the command line interface.
 */
static void print_usage(Runtime *rt) {
    fprintf(rt->err, "usage: lisp [--version] [-e expr] [script [args...]]\n");
}

/**
 * Run the interactive read-eval loop on the runtime input stream.
 */
static int repl(Runtime *rt) {
    char *line = malloc((size_t)LISP_REPL_LINE_BYTES);
    if (!line) {
        fatal(rt, "out of memory");
    }
    fprintf(rt->out, "Lisp %s (MiniOS)\n", lisp_version());
    for (;;) {
        Reader reader;
        ParseResult parsed;
        Node *result;
        fputs("> ", rt->out);
        fflush(rt->out);
        if (!fgets(line, (int)LISP_REPL_LINE_BYTES, rt->in)) {
            break;
        }
        reader.data = line;
        reader.pos = 0;
        reader.length = strlen(line);
        reader.line = 1;
        reader.column = 1;
        for (;;) {
            parsed = read_expr(rt, &reader);
            if (parsed.status == PARSE_EOF) {
                break;
            }
            if (parsed.status == PARSE_ERROR) {
                fprintf(rt->err, "parse error at %zu:%zu: %s\n", reader.line,
                    reader.column, parsed.message);
                break;
            }
            result = eval(rt, parsed.value, rt->global);
            if (!result) {
                fprintf(rt->err, "evaluation failed\n");
                break;
            }
            print_node(rt, result, true);
            fputc('\n', rt->out);
        }
    }
    free(line);
    fputc('\n', rt->out);
    return EXIT_SUCCESS;
}

/**
 * Entry point with -e, script and REPL modes plus bounded arguments.
 */
int main(int argc, char **argv) {
    Runtime runtime;
    int status = EXIT_SUCCESS;
    int script_at = -1;
    int i;
    bool ran_code = false;
    runtime_init(&runtime);
    runtime.global = init_env(&runtime);
    for (i = 1; i < argc; i++) {
        const char *a = argv[i] ? argv[i] : "";
        if (strcmp(a, "--") == 0) {
            script_at = i + 1;
            break;
        }
        if (strcmp(a, "-v") == 0 || strcmp(a, "--version") == 0) {
            fprintf(runtime.out, "lisp %s (MiniOS)\n", lisp_version());
            ran_code = true;
            continue;
        }
        if (strcmp(a, "-h") == 0 || strcmp(a, "--help") == 0) {
            print_usage(&runtime);
            cleanup(&runtime);
            return EXIT_SUCCESS;
        }
        if (strcmp(a, "-e") == 0) {
            if (i + 1 >= argc) {
                fprintf(runtime.err, "lisp: -e needs an expression\n");
                cleanup(&runtime);
                return EXIT_FAILURE;
            }
            if (process_inline(&runtime, argv[i + 1]) != EXIT_SUCCESS) {
                status = EXIT_FAILURE;
            }
            ran_code = true;
            i++;
            continue;
        }
        if (a[0] == '-' && a[1] != '\0') {
            fprintf(runtime.err, "lisp: unknown option '%s'\n", a);
            print_usage(&runtime);
            cleanup(&runtime);
            return EXIT_FAILURE;
        }
        script_at = i;
        break;
    }
    if (script_at >= 0 && script_at < argc) {
        char *source;
        bind_argv(&runtime, runtime.global, argc, argv, script_at);
        source = read_all_file(argv[script_at], (size_t)LISP_MAX_FILE_BYTES);
        if (!source) {
            fprintf(runtime.err, "cannot read '%s'\n", argv[script_at]);
            cleanup(&runtime);
            return EXIT_FAILURE;
        }
        status = process_source(&runtime, source, argv[script_at], false);
        free(source);
    } else if (!ran_code) {
        bind_argv(&runtime, runtime.global, 0, NULL, 0);
        status = repl(&runtime);
    }
    cleanup(&runtime);
    return status;
}