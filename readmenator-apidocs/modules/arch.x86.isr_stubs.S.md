# `arch/x86/isr_stubs.S`

> Source: [arch/x86/isr_stubs.S:1](../../arch/x86/isr_stubs.S#L1) | language `S` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`tf_rax`](#tf_rax), [`tf_rbx`](#tf_rbx), [`tf_rcx`](#tf_rcx), [`tf_rdx`](#tf_rdx), [`tf_rsi`](#tf_rsi), [`tf_rdi`](#tf_rdi), [`tf_rbp`](#tf_rbp), [`tf_r8`](#tf_r8), [`tf_r9`](#tf_r9), [`tf_r10`](#tf_r10), [`tf_r11`](#tf_r11), [`tf_r12`](#tf_r12), [`tf_r13`](#tf_r13), [`tf_r14`](#tf_r14), [`tf_r15`](#tf_r15), [`tf_rip`](#tf_rip), [`tf_cs`](#tf_cs), [`tf_rflags`](#tf_rflags), [`tf_rsp`](#tf_rsp), [`tf_ss`](#tf_ss), [`tf_vector`](#tf_vector), [`tf_errcode`](#tf_errcode), [`isr_common`](#isr_common), [`isr_stub_table`](#isr_stub_table)

## Functions

<a id="tf_rax"></a>

### `tf_rax`

`function` | [arch/x86/isr_stubs.S:67](../../arch/x86/isr_stubs.S#L67)

```asm
tf_rax: .quad 0
```

---

<a id="tf_rbx"></a>

### `tf_rbx`

`function` | [arch/x86/isr_stubs.S:68](../../arch/x86/isr_stubs.S#L68)

```asm
tf_rbx: .quad 0
```

---

<a id="tf_rcx"></a>

### `tf_rcx`

`function` | [arch/x86/isr_stubs.S:69](../../arch/x86/isr_stubs.S#L69)

```asm
tf_rcx: .quad 0
```

---

<a id="tf_rdx"></a>

### `tf_rdx`

`function` | [arch/x86/isr_stubs.S:70](../../arch/x86/isr_stubs.S#L70)

```asm
tf_rdx: .quad 0
```

---

<a id="tf_rsi"></a>

### `tf_rsi`

`function` | [arch/x86/isr_stubs.S:71](../../arch/x86/isr_stubs.S#L71)

```asm
tf_rsi: .quad 0
```

---

<a id="tf_rdi"></a>

### `tf_rdi`

`function` | [arch/x86/isr_stubs.S:72](../../arch/x86/isr_stubs.S#L72)

```asm
tf_rdi: .quad 0
```

---

<a id="tf_rbp"></a>

### `tf_rbp`

`function` | [arch/x86/isr_stubs.S:73](../../arch/x86/isr_stubs.S#L73)

```asm
tf_rbp: .quad 0
```

---

<a id="tf_r8"></a>

### `tf_r8`

`function` | [arch/x86/isr_stubs.S:74](../../arch/x86/isr_stubs.S#L74)

```asm
tf_r8: .quad 0
```

---

<a id="tf_r9"></a>

### `tf_r9`

`function` | [arch/x86/isr_stubs.S:75](../../arch/x86/isr_stubs.S#L75)

```asm
tf_r9: .quad 0
```

---

<a id="tf_r10"></a>

### `tf_r10`

`function` | [arch/x86/isr_stubs.S:76](../../arch/x86/isr_stubs.S#L76)

```asm
tf_r10: .quad 0
```

---

<a id="tf_r11"></a>

### `tf_r11`

`function` | [arch/x86/isr_stubs.S:77](../../arch/x86/isr_stubs.S#L77)

```asm
tf_r11: .quad 0
```

---

<a id="tf_r12"></a>

### `tf_r12`

`function` | [arch/x86/isr_stubs.S:78](../../arch/x86/isr_stubs.S#L78)

```asm
tf_r12: .quad 0
```

---

<a id="tf_r13"></a>

### `tf_r13`

`function` | [arch/x86/isr_stubs.S:79](../../arch/x86/isr_stubs.S#L79)

```asm
tf_r13: .quad 0
```

---

<a id="tf_r14"></a>

### `tf_r14`

`function` | [arch/x86/isr_stubs.S:80](../../arch/x86/isr_stubs.S#L80)

```asm
tf_r14: .quad 0
```

---

<a id="tf_r15"></a>

### `tf_r15`

`function` | [arch/x86/isr_stubs.S:81](../../arch/x86/isr_stubs.S#L81)

```asm
tf_r15: .quad 0
```

---

<a id="tf_rip"></a>

### `tf_rip`

`function` | [arch/x86/isr_stubs.S:82](../../arch/x86/isr_stubs.S#L82)

```asm
tf_rip: .quad 0
```

---

<a id="tf_cs"></a>

### `tf_cs`

`function` | [arch/x86/isr_stubs.S:83](../../arch/x86/isr_stubs.S#L83)

```asm
tf_cs: .quad 0
```

---

<a id="tf_rflags"></a>

### `tf_rflags`

`function` | [arch/x86/isr_stubs.S:84](../../arch/x86/isr_stubs.S#L84)

```asm
tf_rflags: .quad 0
```

---

<a id="tf_rsp"></a>

### `tf_rsp`

`function` | [arch/x86/isr_stubs.S:85](../../arch/x86/isr_stubs.S#L85)

```asm
tf_rsp: .quad 0
```

---

<a id="tf_ss"></a>

### `tf_ss`

`function` | [arch/x86/isr_stubs.S:86](../../arch/x86/isr_stubs.S#L86)

```asm
tf_ss: .quad 0
```

---

<a id="tf_vector"></a>

### `tf_vector`

`function` | [arch/x86/isr_stubs.S:87](../../arch/x86/isr_stubs.S#L87)

```asm
tf_vector: .quad 0
```

---

<a id="tf_errcode"></a>

### `tf_errcode`

`function` | [arch/x86/isr_stubs.S:88](../../arch/x86/isr_stubs.S#L88)

```asm
tf_errcode: .quad 0
```

---

<a id="isr_common"></a>

### `isr_common`

`function` | [arch/x86/isr_stubs.S:96](../../arch/x86/isr_stubs.S#L96)

```asm
isr_common:
```

---

<a id="isr_stub_table"></a>

### `isr_stub_table`

`function` | [arch/x86/isr_stubs.S:195](../../arch/x86/isr_stubs.S#L195)

```asm
isr_stub_table:
```

---
