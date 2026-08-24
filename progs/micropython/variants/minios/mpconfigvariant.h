/*
 * MicroPython-on-MiniOS variant: a teaching REPL with floats, os module,
 * compiler, and no external dependencies.  Modeled on the unix "minimal"
 * variant but tuned for the MiniOS serial console (kernel line-based echo,
 * no termios/readline/sockets/FFI/threading).
 *
 * Built on the host with `gcc -static -no-pie` exactly like DOOM.
 */

// ── feature level ──────────────────────────────────────────────────
#define MICROPY_CONFIG_ROM_LEVEL (MICROPY_CONFIG_ROM_LEVEL_BASIC_FEATURES)

// ── floating point and long-int ────────────────────────────────────
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_DOUBLE)
#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_MPZ)

// ── compiler and diagnostics ───────────────────────────────────────
#define MICROPY_ERROR_REPORTING (MICROPY_ERROR_REPORTING_DETAILED)
#define MICROPY_WARNINGS (1)
#define MICROPY_DEBUG_PRINTERS (1)

// ── console: kernel handles echo and line editing ──────────────────
#define MICROPY_USE_READLINE (0)

// ── keyboard interrupt: Ctrl-C raises KeyboardInterrupt via signal ─
// The signal handler in unix_mphal.c references mp_kbd_exception
// unconditionally on non-Windows, so this must be enabled even though
// sigaction() will fail silently on MiniOS (ENOSYS).  The REPL still
// works; Ctrl-C simply has no effect.
#define MICROPY_KBD_EXCEPTION (1)
#define MICROPY_ASYNC_KBD_INTR (0)

// ── REPL helpers ───────────────────────────────────────────────────
#define MICROPY_HELPER_REPL (1)
#define MICROPY_PY_SYS_PS1 (1)
#define MICROPY_PY_SYS_PS2 (1)
#define MICROPY_PY_SYS_ATEXIT (1)
#define MICROPY_PY_SYS_EXC_INFO (1)

// ── os module: open, stat, import ──────────────────────────────────
#define MICROPY_PY_OS (1)
#define MICROPY_PY_OS_INCLUDEFILE "ports/unix/modos.c"
#define MICROPY_PY_OS_ERRNO (1)
#define MICROPY_PY_OS_GETENV_PUTENV_UNSETENV (0)
#define MICROPY_PY_OS_SYSTEM (0)
#define MICROPY_PY_OS_URANDOM (0)

// ── time module disabled (no select() syscall for sleep) ───────────
#define MICROPY_PY_TIME (0)

// ── explicit disables ─────────────────────────────────────────────
#define MICROPY_PY_SOCKET (0)
#define MICROPY_PY_SSL (0)
#define MICROPY_PY_FFI (0)
#define MICROPY_PY_THREAD (0)
#define MICROPY_PY_MACHINE (0)
#define MICROPY_PY_WEBSOCKET (0)

// ── persistent code (.mpy) ────────────────────────────────────────
#define MICROPY_PERSISTENT_CODE_LOAD (0)

// ── REPL emacs keys off (no readline) ─────────────────────────────
#define MICROPY_REPL_EMACS_WORDS_MOVE (0)
#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE (0)
#define MICROPY_USE_READLINE_HISTORY (0)

// ── performance ───────────────────────────────────────────────────
// x86-64 Linux: computed goto (gcc computed-goto extension) gives a
// meaningful speed-up over switch-dispatch for the bytecode interpreter.
#define MICROPY_OPT_COMPUTED_GOTO (1)

// ── emergency exception buffer (small, stack-friendly) ─────────────
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (1)
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE (256)

// ── gc return value ────────────────────────────────────────────────
#define MICROPY_PY_GC_COLLECT_RETVAL (1)

// ── VFS ROM (not used) ────────────────────────────────────────────
#define MICROPY_VFS_ROM (0)
#define MICROPY_VFS_ROM_IOCTL (0)

// ── compat (arch_prctl base etc.) ──────────────────────────────────
// MiniOS handles SET_FS_BASE / SET_GS_BASE via arch_prctl syscall 158.
// glibc needs this at static init.
