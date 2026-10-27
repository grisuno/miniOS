# `progs/src/opl3.c`

> Source: [progs/src/opl3.c:1](../../progs/src/opl3.c#L1) | language `c` | coverage 8.3% | [API index](../index.md)

## Contents

- **Structs:** [`note_t`](#note_t)
- **Functions:** [`main`](#main)
- **Macros:** [`SYS_TIME`](#sys_time), [`SYS_SB16_OPEN`](#sys_sb16_open), [`SYS_SB16_SUBMIT`](#sys_sb16_submit), [`SYS_WRITE`](#sys_write), [`SAMPLE_RATE`](#sample_rate), [`STEREO_FRAMES`](#stereo_frames), [`MONO_BYTES`](#mono_bytes), [`BUF_MS`](#buf_ms), [`F_NUM_FACTOR`](#f_num_factor)

## Structs

<a id="note_t"></a>

### `note_t`

`struct` | [progs/src/opl3.c:102](../../progs/src/opl3.c#L102)

```c
typedef struct { unsigned block; unsigned fnum; long ms; } note_t;
```

---

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/opl3.c:107](../../progs/src/opl3.c#L107)

```c
int main(void)
```

**Returns:** `int`

---

## Macros

<a id="sys_time"></a>

### `SYS_TIME`

`macro` | [progs/src/opl3.c:21](../../progs/src/opl3.c#L21)

```c
#define SYS_TIME
```

---

<a id="sys_sb16_open"></a>

### `SYS_SB16_OPEN`

`macro` | [progs/src/opl3.c:22](../../progs/src/opl3.c#L22)

```c
#define SYS_SB16_OPEN
```

---

<a id="sys_sb16_submit"></a>

### `SYS_SB16_SUBMIT`

`macro` | [progs/src/opl3.c:23](../../progs/src/opl3.c#L23)

```c
#define SYS_SB16_SUBMIT
```

---

<a id="sys_write"></a>

### `SYS_WRITE`

`macro` | [progs/src/opl3.c:24](../../progs/src/opl3.c#L24)

```c
#define SYS_WRITE
```

---

<a id="sample_rate"></a>

### `SAMPLE_RATE`

`macro` | [progs/src/opl3.c:28](../../progs/src/opl3.c#L28)

```c
#define SAMPLE_RATE
```

---

<a id="stereo_frames"></a>

### `STEREO_FRAMES`

`macro` | [progs/src/opl3.c:29](../../progs/src/opl3.c#L29)

```c
#define STEREO_FRAMES
```

---

<a id="mono_bytes"></a>

### `MONO_BYTES`

`macro` | [progs/src/opl3.c:30](../../progs/src/opl3.c#L30)

```c
#define MONO_BYTES
```

int16 pairs per submit == SB16 PCM buf

---

<a id="buf_ms"></a>

### `BUF_MS`

`macro` | [progs/src/opl3.c:32](../../progs/src/opl3.c#L32)

```c
#define BUF_MS
```

---

<a id="f_num_factor"></a>

### `F_NUM_FACTOR`

`macro` | [progs/src/opl3.c:34](../../progs/src/opl3.c#L34)

```c
#define F_NUM_FACTOR
```

---
