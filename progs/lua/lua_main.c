/*
 * lua_main.c -- Lua 5.4 entry point for MiniOS.
 *
 * A self-contained replacement for the upstream lua.c main so the `minios`
 * C module (minios.c) can be registered globally before any script runs:
 * `minios.run(...)`, `minios.time_ms()`, etc. are available as a plain global
 * table, exactly like `import minios` in MicroPython.  Everything else is a
 * minimal but faithful CLI: `lua -e <code>`, `lua -l <lib>`, `lua <script>
 * [args]` and an interactive REPL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int luaopen_minios(lua_State *L);

static void luaL_require_global(lua_State *L, const char *name,
                                lua_CFunction openf) {
    luaL_requiref(L, name, openf, 1);
    lua_pop(L, 1);
}

static void set_arg_table(lua_State *L, int argc, char **argv, int first) {
    /* Set the global `arg` table: arg[0] is the script, arg[1..] the rest. */
    lua_createtable(L, argc - first, 1);
    lua_pushinteger(L, argc - first);
    lua_setfield(L, -2, "n");
    int i;
    for (i = 0; i < argc - first; i++) {
        lua_pushstring(L, argv[first + i]);
        lua_rawseti(L, -2, i);
    }
    lua_setglobal(L, "arg");
}

static int docode(lua_State *L, const char *code) {
    int status = luaL_loadstring(L, code) || lua_pcall(L, 0, LUA_MULTRET, 0);
    if (status != LUA_OK) {
        const char *msg = lua_tostring(L, -1);
        fprintf(stderr, "lua: %s\n", msg ? msg : "unknown error");
        lua_pop(L, 1);
    }
    return status == LUA_OK ? 0 : 1;
}

static int dofile(lua_State *L, const char *name) {
    int status = luaL_loadfile(L, name) || lua_pcall(L, 0, LUA_MULTRET, 0);
    if (status != LUA_OK) {
        const char *msg = lua_tostring(L, -1);
        fprintf(stderr, "lua: %s\n", msg ? msg : "unknown error");
        lua_pop(L, 1);
    }
    return status == LUA_OK ? 0 : 1;
}

static int repl(lua_State *L) {
    char line[1024];
    printf("Lua %s  (MiniOS)  type 'os.exit()' to quit\n", LUA_VERSION);
    for (;;) {
        printf("> ");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = 0;
        if (len == 0) continue;
        char buf[1100];
        if (line[0] == '=') {
            snprintf(buf, sizeof(buf), "return %s", line + 1);
        } else {
            snprintf(buf, sizeof(buf), "%s", line);
        }
        if (luaL_loadbuffer(L, buf, strlen(buf), "stdin")
            || lua_pcall(L, 0, LUA_MULTRET, 0)) {
            const char *msg = lua_tostring(L, -1);
            fprintf(stderr, "%s\n", msg ? msg : "error");
            lua_pop(L, 1);
            continue;
        }
        int n = lua_gettop(L);
        if (n > 0) {
            int i;
            for (i = 1; i <= n; i++) {
                if (lua_isstring(L, i)) {
                    printf("%s", lua_tostring(L, i));
                } else {
                    lua_getglobal(L, "print");
                    lua_pushvalue(L, i);
                    lua_call(L, 1, 0);
                }
                if (i < n) printf("\t");
            }
            printf("\n");
        }
        lua_settop(L, 0);
    }
    return 0;
}

int main(int argc, char **argv) {
    lua_State *L = luaL_newstate();
    if (!L) return 1;
    luaL_openlibs(L);
    luaL_require_global(L, "minios", luaopen_minios);

    int status = 0;
    int script_start = argc;
    int i;
    for (i = 1; i < argc; i++) {
        const char *a = argv[i];
        if (a[0] != '-') { script_start = i; break; }
        if (strcmp(a, "--") == 0) { script_start = i + 1; break; }
        if (strcmp(a, "-v") == 0 || strcmp(a, "--version") == 0) {
            printf("Lua %s  (MiniOS)\n", LUA_VERSION);
            continue;
        }
        if (strcmp(a, "-e") == 0 && i + 1 < argc) {
            if (docode(L, argv[++i])) status = 1;
            continue;
        }
        if (strcmp(a, "-l") == 0 && i + 1 < argc) {
            /* Only the statically-linked minios module is loadable. */
            const char *lib = argv[++i];
            if (strcmp(lib, "minios") == 0)
                luaL_require_global(L, "minios", luaopen_minios);
            else
                fprintf(stderr, "lua: cannot load library '%s'\n", lib);
            continue;
        }
        fprintf(stderr, "lua: unknown option '%s'\n", a);
        return 1;
    }

    if (script_start < argc) {
        set_arg_table(L, argc, argv, script_start);
        status = dofile(L, argv[script_start]);
    } else if (status == 0) {
        /* no script and no -e: interactive REPL */
        repl(L);
    }

    lua_close(L);
    return status;
}
