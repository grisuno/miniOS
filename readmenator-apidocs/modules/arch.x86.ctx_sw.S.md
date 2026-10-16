# `arch/x86/ctx_sw.S`

> Source: [arch/x86/ctx_sw.S:1](../../arch/x86/ctx_sw.S#L1) | language `S` | coverage 20.0% | [API index](../index.md)

## Contents

- **Functions:** [`sched_park_capture`](#sched_park_capture), [`switch_save_only`](#switch_save_only), [`switch_to`](#switch_to), [`switch_to_notrap`](#switch_to_notrap), [`user_trampoline`](#user_trampoline), [`fork_trampoline`](#fork_trampoline), [`exec_enter`](#exec_enter), [`resume_iretq`](#resume_iretq), [`k_run_on_stack`](#k_run_on_stack)

## Functions

<a id="sched_park_capture"></a>

### `sched_park_capture`

`function` | [arch/x86/ctx_sw.S:70](../../arch/x86/ctx_sw.S#L70)

```asm
sched_park_capture:
```

sched_park_capture -- park the live schedule() continuation (pure asm). void sched_park_capture(proc_t *cur);  rdi = &cur (ctx at offset 0).

Replaces the old __builtin_frame_address/__builtin_return_address C
helper with deterministic asm: no builtins, no optimizer interaction.
Entered with `call` and no prologue/epilogue, so by construction:
  8(%rbp) = schedule()'s return address   -> ctx.rip (see below)
  %rbp    = schedule()'s frame pointer     -> ctx.rsp = rbp + 16
  (%rbp)  = schedule()'s saved rbp         -> ctx.rbp
Only caller-saved regs are touched (rcx); switch_save_only already
captured the rest. Offsets mirror CTX_*_OFF in headers/sched.h
(asserted in C). Requires frame pointers (CFLAGS_KERN carries
-fno-omit-frame-pointer; without it %rbp is meaningless here).

rip MUST be 8(%rbp) -- the return into schedule()'s CALLER (yield /
do_waitpid / do_exit) -- never (%rsp), the return into schedule()
itself. A resume into schedule's tail re-runs the publish/unlock/
switch sequence a second time (double unlock of sched_lock plus a
switch to the stale nxt), which hangs the machine; a resume into
the caller simply continues it (callees restore rsp from rbp with
`leave`, so the parked rsp=rbp+16 is exact). This mirrors what GCC
lowers __builtin_return_address(0) to (*(rbp+8)) and is the reason
the old comment insists the tail must never run twice.

*Called by:* [`schedule`](kernel.sched.c.md#schedule)

---

<a id="switch_save_only"></a>

### `switch_save_only`

`function` | [arch/x86/ctx_sw.S:82](../../arch/x86/ctx_sw.S#L82)

```asm
switch_save_only:
```

---

<a id="switch_to"></a>

### `switch_to`

`function` | [arch/x86/ctx_sw.S:91](../../arch/x86/ctx_sw.S#L91)

```asm
switch_to:
```

---

<a id="switch_to_notrap"></a>

### `switch_to_notrap`

`function` | [arch/x86/ctx_sw.S:134](../../arch/x86/ctx_sw.S#L134)

```asm
switch_to_notrap:
```

---

<a id="user_trampoline"></a>

### `user_trampoline`

`function` | [arch/x86/ctx_sw.S:221](../../arch/x86/ctx_sw.S#L221)

```asm
user_trampoline:
```

---

<a id="fork_trampoline"></a>

### `fork_trampoline`

`function` | [arch/x86/ctx_sw.S:233](../../arch/x86/ctx_sw.S#L233)

```asm
fork_trampoline:
```

---

<a id="exec_enter"></a>

### `exec_enter`

`function` | [arch/x86/ctx_sw.S:273](../../arch/x86/ctx_sw.S#L273)

```asm
exec_enter:
```

---

<a id="resume_iretq"></a>

### `resume_iretq`

`function` | [arch/x86/ctx_sw.S:302](../../arch/x86/ctx_sw.S#L302)

```asm
resume_iretq:
```

---

<a id="k_run_on_stack"></a>

### `k_run_on_stack`

`function` | [arch/x86/ctx_sw.S:342](../../arch/x86/ctx_sw.S#L342)

```asm
k_run_on_stack:
```

ET_REL stack switch (arch/x86/ctx_sw.S): runs entry(argc, argv) on the 64 KB stack ending at stack_top.

See the asm contract there.

> **Inherited:** Documentation from [`k_run_on_stack`](#k_run_on_stack) (headers/kernel.h:646).

---
