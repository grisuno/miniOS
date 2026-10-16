# `progs/src/audio.c`

> Source: [progs/src/audio.c:1](../../progs/src/audio.c#L1) | language `c` | coverage 42.9% | [API index](../index.md)

## Contents

- **Functions:** [`audio_init`](#audio_init), [`audio_tone`](#audio_tone), [`audio_pcm_open`](#audio_pcm_open), [`audio_pcm_submit`](#audio_pcm_submit), [`audio_pcm_pump`](#audio_pcm_pump), [`audio_pcm_close`](#audio_pcm_close), [`audio_set_volume`](#audio_set_volume), [`audio_get_volume`](#audio_get_volume), [`audio_sb16_present`](#audio_sb16_present), [`audio_stream_open`](#audio_stream_open), [`audio_stream_close`](#audio_stream_close), [`audio_stream_submit`](#audio_stream_submit), [`audio_stream_volume`](#audio_stream_volume)

## Functions

<a id="audio_init"></a>

### `audio_init`

`function` | [progs/src/audio.c:27](../../progs/src/audio.c#L27)

```c
int audio_init(void)
```

Initialize the audio subsystem.

Probes for SB16, resets PC speaker.

**Returns:** `int`

> **Inherited:** Documentation from [`audio_init`](#audio_init) (headers/audio.h:21).

---

<a id="audio_tone"></a>

### `audio_tone`

`function` | [progs/src/audio.c:31](../../progs/src/audio.c#L31)

```c
void audio_tone(unsigned freq)
```

Tone mode: play a square wave at `freq` Hz.

0 = silence.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `freq` | `unsigned` |  |  |

> **Inherited:** Documentation from [`audio_tone`](#audio_tone) (headers/audio.h:24).

---

<a id="audio_pcm_open"></a>

### `audio_pcm_open`

`function` | [progs/src/audio.c:35](../../progs/src/audio.c#L35)

```c
int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)
```

PCM streaming mode (SB16).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rate` | `unsigned` |  |  |
| `channels` | `unsigned` |  |  |
| `format` | `unsigned` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`audio_pcm_open`](#audio_pcm_open) (headers/audio.h:27).

---

<a id="audio_pcm_submit"></a>

### `audio_pcm_submit`

`function` | [progs/src/audio.c:40](../../progs/src/audio.c#L40)

```c
int audio_pcm_submit(const void *buf, unsigned len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `void *` |  |  |
| `len` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="audio_pcm_pump"></a>

### `audio_pcm_pump`

`function` | [progs/src/audio.c:44](../../progs/src/audio.c#L44)

```c
void audio_pcm_pump(void)
```

---

<a id="audio_pcm_close"></a>

### `audio_pcm_close`

`function` | [progs/src/audio.c:48](../../progs/src/audio.c#L48)

```c
void audio_pcm_close(void)
```

---

<a id="audio_set_volume"></a>

### `audio_set_volume`

`function` | [progs/src/audio.c:52](../../progs/src/audio.c#L52)

```c
void audio_set_volume(unsigned volume)
```

Volume control (PC speaker mute switch).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `unsigned` |  |  |

> **Inherited:** Documentation from [`audio_set_volume`](#audio_set_volume) (headers/audio.h:33).

---

<a id="audio_get_volume"></a>

### `audio_get_volume`

`function` | [progs/src/audio.c:56](../../progs/src/audio.c#L56)

```c
unsigned audio_get_volume(void)
```

**Returns:** `unsigned`

---

<a id="audio_sb16_present"></a>

### `audio_sb16_present`

`function` | [progs/src/audio.c:60](../../progs/src/audio.c#L60)

```c
int audio_sb16_present(void)
```

Query hardware presence.

**Returns:** `int`

> **Inherited:** Documentation from [`audio_sb16_present`](#audio_sb16_present) (headers/audio.h:37).

---

<a id="audio_stream_open"></a>

### `audio_stream_open`

`function` | [progs/src/audio.c:64](../../progs/src/audio.c#L64)

```c
int audio_stream_open(void)
```

Mixer stream API (SB16 multicanal).

**Returns:** `int`

> **Inherited:** Documentation from [`audio_stream_open`](#audio_stream_open) (headers/audio.h:40).

---

<a id="audio_stream_close"></a>

### `audio_stream_close`

`function` | [progs/src/audio.c:68](../../progs/src/audio.c#L68)

```c
void audio_stream_close(int id)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |

---

<a id="audio_stream_submit"></a>

### `audio_stream_submit`

`function` | [progs/src/audio.c:72](../../progs/src/audio.c#L72)

```c
int audio_stream_submit(int id, const void *buf, unsigned len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |
| `buf` | `void *` |  |  |
| `len` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="audio_stream_volume"></a>

### `audio_stream_volume`

`function` | [progs/src/audio.c:76](../../progs/src/audio.c#L76)

```c
void audio_stream_volume(int id, unsigned char vol)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |
| `vol` | `unsigned char` |  |  |

---
