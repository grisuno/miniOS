# `progs/micropython/variants/minios/mpconfigvariant.h`

> Source: [progs/micropython/variants/minios/mpconfigvariant.h:1](../../progs/micropython/variants/minios/mpconfigvariant.h#L1) | language `h` | coverage 40.4% | [API index](../index.md)

## Contents

- **Macros:** [`MICROPY_CONFIG_ROM_LEVEL`](#micropy_config_rom_level), [`MICROPY_FLOAT_IMPL`](#micropy_float_impl), [`MICROPY_LONGINT_IMPL`](#micropy_longint_impl), [`MICROPY_ERROR_REPORTING`](#micropy_error_reporting), [`MICROPY_WARNINGS`](#micropy_warnings), [`MICROPY_DEBUG_PRINTERS`](#micropy_debug_printers), [`MICROPY_USE_READLINE`](#micropy_use_readline), [`MICROPY_KBD_EXCEPTION`](#micropy_kbd_exception), [`MICROPY_ASYNC_KBD_INTR`](#micropy_async_kbd_intr), [`MICROPY_HELPER_REPL`](#micropy_helper_repl), [`MICROPY_PY_SYS_PS1`](#micropy_py_sys_ps1), [`MICROPY_PY_SYS_PS2`](#micropy_py_sys_ps2), [`MICROPY_PY_SYS_ATEXIT`](#micropy_py_sys_atexit), [`MICROPY_PY_SYS_EXC_INFO`](#micropy_py_sys_exc_info), [`MICROPY_PY_SYS_STDFILES`](#micropy_py_sys_stdfiles), [`MICROPY_PY_OS`](#micropy_py_os), [`MICROPY_PY_OS_INCLUDEFILE`](#micropy_py_os_includefile), [`MICROPY_PY_OS_ERRNO`](#micropy_py_os_errno), [`MICROPY_PY_OS_GETENV_PUTENV_UNSETENV`](#micropy_py_os_getenv_putenv_unsetenv), [`MICROPY_PY_OS_SYSTEM`](#micropy_py_os_system), [`MICROPY_PY_OS_URANDOM`](#micropy_py_os_urandom), [`MICROPY_PY_SELECT`](#micropy_py_select), [`MICROPY_PY_SELECT_POSIX_OPTIMISATIONS`](#micropy_py_select_posix_optimisations), [`MICROPY_PY_SELECT_SELECT`](#micropy_py_select_select), [`MICROPY_PY_ASYNCIO`](#micropy_py_asyncio), [`MICROPY_STREAMS_NON_BLOCK`](#micropy_streams_non_block), [`MICROPY_PY_ERRNO`](#micropy_py_errno), [`MICROPY_PY_TIME`](#micropy_py_time), [`MICROPY_PY_TIME_INCLUDEFILE`](#micropy_py_time_includefile), [`MICROPY_PY_TIME_TIME_TIME_NS`](#micropy_py_time_time_time_ns), [`MICROPY_PY_TIME_CUSTOM_SLEEP`](#micropy_py_time_custom_sleep), [`MICROPY_PY_SSL`](#micropy_py_ssl), [`MICROPY_PY_FFI`](#micropy_py_ffi), [`MICROPY_PY_THREAD`](#micropy_py_thread), [`MICROPY_PY_MACHINE`](#micropy_py_machine), [`MICROPY_PY_WEBSOCKET`](#micropy_py_websocket), [`MICROPY_PERSISTENT_CODE_LOAD`](#micropy_persistent_code_load), [`MICROPY_REPL_EMACS_WORDS_MOVE`](#micropy_repl_emacs_words_move), [`MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE`](#micropy_repl_emacs_extra_words_move), [`MICROPY_USE_READLINE_HISTORY`](#micropy_use_readline_history), [`MICROPY_OPT_COMPUTED_GOTO`](#micropy_opt_computed_goto), [`MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF`](#micropy_enable_emergency_exception_buf), [`MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE`](#micropy_emergency_exception_buf_size), [`MICROPY_PY_GC_COLLECT_RETVAL`](#micropy_py_gc_collect_retval), [`MICROPY_VFS_ROM`](#micropy_vfs_rom), [`MICROPY_VFS_ROM_IOCTL`](#micropy_vfs_rom_ioctl)

## Macros

<a id="micropy_config_rom_level"></a>

### `MICROPY_CONFIG_ROM_LEVEL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:11](../../progs/micropython/variants/minios/mpconfigvariant.h#L11)

```c
#define MICROPY_CONFIG_ROM_LEVEL
```

── feature level ──────────────────────────────────────────────────

---

<a id="micropy_float_impl"></a>

### `MICROPY_FLOAT_IMPL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:14](../../progs/micropython/variants/minios/mpconfigvariant.h#L14)

```c
#define MICROPY_FLOAT_IMPL
```

── floating point and long-int ────────────────────────────────────

---

<a id="micropy_longint_impl"></a>

### `MICROPY_LONGINT_IMPL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:15](../../progs/micropython/variants/minios/mpconfigvariant.h#L15)

```c
#define MICROPY_LONGINT_IMPL
```

---

<a id="micropy_error_reporting"></a>

### `MICROPY_ERROR_REPORTING`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:18](../../progs/micropython/variants/minios/mpconfigvariant.h#L18)

```c
#define MICROPY_ERROR_REPORTING
```

── compiler and diagnostics ───────────────────────────────────────

---

<a id="micropy_warnings"></a>

### `MICROPY_WARNINGS`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:19](../../progs/micropython/variants/minios/mpconfigvariant.h#L19)

```c
#define MICROPY_WARNINGS
```

---

<a id="micropy_debug_printers"></a>

### `MICROPY_DEBUG_PRINTERS`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:20](../../progs/micropython/variants/minios/mpconfigvariant.h#L20)

```c
#define MICROPY_DEBUG_PRINTERS
```

---

<a id="micropy_use_readline"></a>

### `MICROPY_USE_READLINE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:23](../../progs/micropython/variants/minios/mpconfigvariant.h#L23)

```c
#define MICROPY_USE_READLINE
```

── console: kernel handles echo and line editing ──────────────────

---

<a id="micropy_kbd_exception"></a>

### `MICROPY_KBD_EXCEPTION`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:30](../../progs/micropython/variants/minios/mpconfigvariant.h#L30)

```c
#define MICROPY_KBD_EXCEPTION
```

── keyboard interrupt: Ctrl-C raises KeyboardInterrupt via signal ─ The signal handler in unix_mphal.c references mp_kbd_exception unconditionally on non-Windows, so this must be enabled even though sigaction() will fail silently on MiniOS (ENOSYS).

The REPL still works; Ctrl-C simply has no effect.

---

<a id="micropy_async_kbd_intr"></a>

### `MICROPY_ASYNC_KBD_INTR`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:31](../../progs/micropython/variants/minios/mpconfigvariant.h#L31)

```c
#define MICROPY_ASYNC_KBD_INTR
```

---

<a id="micropy_helper_repl"></a>

### `MICROPY_HELPER_REPL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:34](../../progs/micropython/variants/minios/mpconfigvariant.h#L34)

```c
#define MICROPY_HELPER_REPL
```

── REPL helpers ───────────────────────────────────────────────────

---

<a id="micropy_py_sys_ps1"></a>

### `MICROPY_PY_SYS_PS1`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:35](../../progs/micropython/variants/minios/mpconfigvariant.h#L35)

```c
#define MICROPY_PY_SYS_PS1
```

---

<a id="micropy_py_sys_ps2"></a>

### `MICROPY_PY_SYS_PS2`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:36](../../progs/micropython/variants/minios/mpconfigvariant.h#L36)

```c
#define MICROPY_PY_SYS_PS2
```

---

<a id="micropy_py_sys_atexit"></a>

### `MICROPY_PY_SYS_ATEXIT`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:37](../../progs/micropython/variants/minios/mpconfigvariant.h#L37)

```c
#define MICROPY_PY_SYS_ATEXIT
```

---

<a id="micropy_py_sys_exc_info"></a>

### `MICROPY_PY_SYS_EXC_INFO`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:38](../../progs/micropython/variants/minios/mpconfigvariant.h#L38)

```c
#define MICROPY_PY_SYS_EXC_INFO
```

---

<a id="micropy_py_sys_stdfiles"></a>

### `MICROPY_PY_SYS_STDFILES`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:39](../../progs/micropython/variants/minios/mpconfigvariant.h#L39)

```c
#define MICROPY_PY_SYS_STDFILES
```

---

<a id="micropy_py_os"></a>

### `MICROPY_PY_OS`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:42](../../progs/micropython/variants/minios/mpconfigvariant.h#L42)

```c
#define MICROPY_PY_OS
```

── os module: open, stat, import ──────────────────────────────────

---

<a id="micropy_py_os_includefile"></a>

### `MICROPY_PY_OS_INCLUDEFILE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:43](../../progs/micropython/variants/minios/mpconfigvariant.h#L43)

```c
#define MICROPY_PY_OS_INCLUDEFILE
```

---

<a id="micropy_py_os_errno"></a>

### `MICROPY_PY_OS_ERRNO`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:44](../../progs/micropython/variants/minios/mpconfigvariant.h#L44)

```c
#define MICROPY_PY_OS_ERRNO
```

---

<a id="micropy_py_os_getenv_putenv_unsetenv"></a>

### `MICROPY_PY_OS_GETENV_PUTENV_UNSETENV`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:45](../../progs/micropython/variants/minios/mpconfigvariant.h#L45)

```c
#define MICROPY_PY_OS_GETENV_PUTENV_UNSETENV
```

---

<a id="micropy_py_os_system"></a>

### `MICROPY_PY_OS_SYSTEM`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:46](../../progs/micropython/variants/minios/mpconfigvariant.h#L46)

```c
#define MICROPY_PY_OS_SYSTEM
```

---

<a id="micropy_py_os_urandom"></a>

### `MICROPY_PY_OS_URANDOM`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:47](../../progs/micropython/variants/minios/mpconfigvariant.h#L47)

```c
#define MICROPY_PY_OS_URANDOM
```

---

<a id="micropy_py_select"></a>

### `MICROPY_PY_SELECT`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:60](../../progs/micropython/variants/minios/mpconfigvariant.h#L60)

```c
#define MICROPY_PY_SELECT
```

── select: poll-based (unix POSIX optimisations), like every variant ─

---

<a id="micropy_py_select_posix_optimisations"></a>

### `MICROPY_PY_SELECT_POSIX_OPTIMISATIONS`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:61](../../progs/micropython/variants/minios/mpconfigvariant.h#L61)

```c
#define MICROPY_PY_SELECT_POSIX_OPTIMISATIONS
```

---

<a id="micropy_py_select_select"></a>

### `MICROPY_PY_SELECT_SELECT`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:62](../../progs/micropython/variants/minios/mpconfigvariant.h#L62)

```c
#define MICROPY_PY_SELECT_SELECT
```

---

<a id="micropy_py_asyncio"></a>

### `MICROPY_PY_ASYNCIO`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:65](../../progs/micropython/variants/minios/mpconfigvariant.h#L65)

```c
#define MICROPY_PY_ASYNCIO
```

── asyncio: the extmod event loop over select.poll() and sockets ───

---

<a id="micropy_streams_non_block"></a>

### `MICROPY_STREAMS_NON_BLOCK`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:70](../../progs/micropython/variants/minios/mpconfigvariant.h#L70)

```c
#define MICROPY_STREAMS_NON_BLOCK
```

Non-blocking streams: EAGAIN reads answer None instead of raising (py/stream.h mp_is_nonblocking_error). asyncio's Stream.read relies on it: without this the socket read raises EAGAIN and every async stream dies mid-transfer.

---

<a id="micropy_py_errno"></a>

### `MICROPY_PY_ERRNO`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:73](../../progs/micropython/variants/minios/mpconfigvariant.h#L73)

```c
#define MICROPY_PY_ERRNO
```

── errno: the ecosystem (asyncio.stream) imports EINPROGRESS et al ─

---

<a id="micropy_py_time"></a>

### `MICROPY_PY_TIME`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:76](../../progs/micropython/variants/minios/mpconfigvariant.h#L76)

```c
#define MICROPY_PY_TIME
```

── time: unix modtime.c; sleep(select) is backed by pselect6(2) ────

---

<a id="micropy_py_time_includefile"></a>

### `MICROPY_PY_TIME_INCLUDEFILE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:77](../../progs/micropython/variants/minios/mpconfigvariant.h#L77)

```c
#define MICROPY_PY_TIME_INCLUDEFILE
```

---

<a id="micropy_py_time_time_time_ns"></a>

### `MICROPY_PY_TIME_TIME_TIME_NS`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:78](../../progs/micropython/variants/minios/mpconfigvariant.h#L78)

```c
#define MICROPY_PY_TIME_TIME_TIME_NS
```

---

<a id="micropy_py_time_custom_sleep"></a>

### `MICROPY_PY_TIME_CUSTOM_SLEEP`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:79](../../progs/micropython/variants/minios/mpconfigvariant.h#L79)

```c
#define MICROPY_PY_TIME_CUSTOM_SLEEP
```

---

<a id="micropy_py_ssl"></a>

### `MICROPY_PY_SSL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:82](../../progs/micropython/variants/minios/mpconfigvariant.h#L82)

```c
#define MICROPY_PY_SSL
```

── explicit disables ─────────────────────────────────────────────

---

<a id="micropy_py_ffi"></a>

### `MICROPY_PY_FFI`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:83](../../progs/micropython/variants/minios/mpconfigvariant.h#L83)

```c
#define MICROPY_PY_FFI
```

---

<a id="micropy_py_thread"></a>

### `MICROPY_PY_THREAD`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:84](../../progs/micropython/variants/minios/mpconfigvariant.h#L84)

```c
#define MICROPY_PY_THREAD
```

---

<a id="micropy_py_machine"></a>

### `MICROPY_PY_MACHINE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:85](../../progs/micropython/variants/minios/mpconfigvariant.h#L85)

```c
#define MICROPY_PY_MACHINE
```

---

<a id="micropy_py_websocket"></a>

### `MICROPY_PY_WEBSOCKET`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:86](../../progs/micropython/variants/minios/mpconfigvariant.h#L86)

```c
#define MICROPY_PY_WEBSOCKET
```

---

<a id="micropy_persistent_code_load"></a>

### `MICROPY_PERSISTENT_CODE_LOAD`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:89](../../progs/micropython/variants/minios/mpconfigvariant.h#L89)

```c
#define MICROPY_PERSISTENT_CODE_LOAD
```

── persistent code (.mpy) ────────────────────────────────────────

---

<a id="micropy_repl_emacs_words_move"></a>

### `MICROPY_REPL_EMACS_WORDS_MOVE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:92](../../progs/micropython/variants/minios/mpconfigvariant.h#L92)

```c
#define MICROPY_REPL_EMACS_WORDS_MOVE
```

── REPL emacs keys off (no readline) ─────────────────────────────

---

<a id="micropy_repl_emacs_extra_words_move"></a>

### `MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:93](../../progs/micropython/variants/minios/mpconfigvariant.h#L93)

```c
#define MICROPY_REPL_EMACS_EXTRA_WORDS_MOVE
```

---

<a id="micropy_use_readline_history"></a>

### `MICROPY_USE_READLINE_HISTORY`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:94](../../progs/micropython/variants/minios/mpconfigvariant.h#L94)

```c
#define MICROPY_USE_READLINE_HISTORY
```

---

<a id="micropy_opt_computed_goto"></a>

### `MICROPY_OPT_COMPUTED_GOTO`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:99](../../progs/micropython/variants/minios/mpconfigvariant.h#L99)

```c
#define MICROPY_OPT_COMPUTED_GOTO
```

── performance ─────────────────────────────────────────────────── x86-64 Linux: computed goto (gcc computed-goto extension) gives a meaningful speed-up over switch-dispatch for the bytecode interpreter.

---

<a id="micropy_enable_emergency_exception_buf"></a>

### `MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:102](../../progs/micropython/variants/minios/mpconfigvariant.h#L102)

```c
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF
```

── emergency exception buffer (small, stack-friendly) ─────────────

---

<a id="micropy_emergency_exception_buf_size"></a>

### `MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:103](../../progs/micropython/variants/minios/mpconfigvariant.h#L103)

```c
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE
```

---

<a id="micropy_py_gc_collect_retval"></a>

### `MICROPY_PY_GC_COLLECT_RETVAL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:106](../../progs/micropython/variants/minios/mpconfigvariant.h#L106)

```c
#define MICROPY_PY_GC_COLLECT_RETVAL
```

── gc return value ────────────────────────────────────────────────

---

<a id="micropy_vfs_rom"></a>

### `MICROPY_VFS_ROM`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:109](../../progs/micropython/variants/minios/mpconfigvariant.h#L109)

```c
#define MICROPY_VFS_ROM
```

── VFS ROM (not used) ────────────────────────────────────────────

---

<a id="micropy_vfs_rom_ioctl"></a>

### `MICROPY_VFS_ROM_IOCTL`

`macro` | [progs/micropython/variants/minios/mpconfigvariant.h:110](../../progs/micropython/variants/minios/mpconfigvariant.h#L110)

```c
#define MICROPY_VFS_ROM_IOCTL
```

---
