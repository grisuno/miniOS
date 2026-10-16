# `headers/audio.h`

> Source: [headers/audio.h:1](../../headers/audio.h#L1) | language `h` | coverage 38.9% | [API index](../index.md)

Unified audio API for MiniOS.

## Contents

- **Functions:** [`audio_init`](#audio_init), [`audio_tone`](#audio_tone), [`audio_pcm_open`](#audio_pcm_open), [`audio_pcm_submit`](#audio_pcm_submit), [`audio_pcm_pump`](#audio_pcm_pump), [`audio_pcm_close`](#audio_pcm_close), [`audio_set_volume`](#audio_set_volume), [`audio_get_volume`](#audio_get_volume), [`audio_sb16_present`](#audio_sb16_present), [`audio_stream_open`](#audio_stream_open), [`audio_stream_close`](#audio_stream_close), [`audio_stream_submit`](#audio_stream_submit), [`audio_stream_volume`](#audio_stream_volume)
- **Macros:** [`AUDIO_RATE_DEFAULT`](#audio_rate_default), [`AUDIO_CHANNELS_MONO`](#audio_channels_mono), [`AUDIO_FORMAT_U8`](#audio_format_u8), [`AUDIO_FORMAT_S16`](#audio_format_s16)

## Functions

<a id="audio_init"></a>

### `audio_init`

`function` | [headers/audio.h:21](../../headers/audio.h#L21)

```c
int audio_init(void);
```

Initialize the audio subsystem.

Probes for SB16, resets PC speaker.

**Returns:** `int`

---

<a id="audio_tone"></a>

### `audio_tone`

`function` | [headers/audio.h:24](../../headers/audio.h#L24)

```c
void audio_tone(unsigned freq);
```

Tone mode: play a square wave at `freq` Hz.

0 = silence.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `freq` | `unsigned` |  |  |

---

<a id="audio_pcm_open"></a>

### `audio_pcm_open`

`function` | [headers/audio.h:27](../../headers/audio.h#L27)

```c
int audio_pcm_open(unsigned rate, unsigned channels, unsigned format);
```

PCM streaming mode (SB16).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `rate` | `unsigned` |  |  |
| `channels` | `unsigned` |  |  |
| `format` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="audio_pcm_submit"></a>

### `audio_pcm_submit`

`function` | [headers/audio.h:28](../../headers/audio.h#L28)

```c
int audio_pcm_submit(const void *buf, unsigned len);
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

`function` | [headers/audio.h:29](../../headers/audio.h#L29)

```c
void audio_pcm_pump(void);
```

---

<a id="audio_pcm_close"></a>

### `audio_pcm_close`

`function` | [headers/audio.h:30](../../headers/audio.h#L30)

```c
void audio_pcm_close(void);
```

---

<a id="audio_set_volume"></a>

### `audio_set_volume`

`function` | [headers/audio.h:33](../../headers/audio.h#L33)

```c
void audio_set_volume(unsigned volume);
```

Volume control (PC speaker mute switch).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `unsigned` |  |  |

---

<a id="audio_get_volume"></a>

### `audio_get_volume`

`function` | [headers/audio.h:34](../../headers/audio.h#L34)

```c
unsigned audio_get_volume(void);
```

**Returns:** `unsigned`

---

<a id="audio_sb16_present"></a>

### `audio_sb16_present`

`function` | [headers/audio.h:37](../../headers/audio.h#L37)

```c
int audio_sb16_present(void);
```

Query hardware presence.

**Returns:** `int`

---

<a id="audio_stream_open"></a>

### `audio_stream_open`

`function` | [headers/audio.h:40](../../headers/audio.h#L40)

```c
int audio_stream_open(void);
```

Mixer stream API (SB16 multicanal).

**Returns:** `int`

---

<a id="audio_stream_close"></a>

### `audio_stream_close`

`function` | [headers/audio.h:41](../../headers/audio.h#L41)

```c
void audio_stream_close(int id);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |

---

<a id="audio_stream_submit"></a>

### `audio_stream_submit`

`function` | [headers/audio.h:42](../../headers/audio.h#L42)

```c
int audio_stream_submit(int id, const void *buf, unsigned len);
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

`function` | [headers/audio.h:43](../../headers/audio.h#L43)

```c
void audio_stream_volume(int id, unsigned char vol);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `int` |  |  |
| `vol` | `unsigned char` |  |  |

---

## Macros

<a id="audio_rate_default"></a>

### `AUDIO_RATE_DEFAULT`

`macro` | [headers/audio.h:15](../../headers/audio.h#L15)

```c
#define AUDIO_RATE_DEFAULT
```

---

<a id="audio_channels_mono"></a>

### `AUDIO_CHANNELS_MONO`

`macro` | [headers/audio.h:16](../../headers/audio.h#L16)

```c
#define AUDIO_CHANNELS_MONO
```

---

<a id="audio_format_u8"></a>

### `AUDIO_FORMAT_U8`

`macro` | [headers/audio.h:17](../../headers/audio.h#L17)

```c
#define AUDIO_FORMAT_U8
```

---

<a id="audio_format_s16"></a>

### `AUDIO_FORMAT_S16`

`macro` | [headers/audio.h:18](../../headers/audio.h#L18)

```c
#define AUDIO_FORMAT_S16
```

---
