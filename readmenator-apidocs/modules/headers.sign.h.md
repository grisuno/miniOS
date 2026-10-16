# `headers/sign.h`

> Source: [headers/sign.h:1](../../headers/sign.h#L1) | language `h` | coverage 21.4% | [API index](../index.md)

Docstring: sign.h -- MiniOS binary signing contract.

## Contents

- **Structs:** [`ed_sha`](#ed_sha)
- **Functions:** [`sign_pubkey`](#sign_pubkey), [`ed_sha512_init`](#ed_sha512_init), [`ed_sha512_update`](#ed_sha512_update), [`ed_sha512_final`](#ed_sha512_final), [`ed25519_verify`](#ed25519_verify)
- **Macros:** [`SIGN_KEY_DEV`](#sign_key_dev), [`SIGN_KEY_PROD`](#sign_key_prod), [`SIGN_KEYS`](#sign_keys), [`SIGN_PUB_BYTES`](#sign_pub_bytes), [`SIGN_SIG_BYTES`](#sign_sig_bytes), [`SIGN_DESC_BYTES`](#sign_desc_bytes), [`SIGN_NOTE_TYPE`](#sign_note_type)

## Structs

<a id="ed_sha"></a>

### `ed_sha`

`struct` | [headers/sign.h:61](../../headers/sign.h#L61)

```c
typedef struct
```

---

## Functions

<a id="sign_pubkey"></a>

### `sign_pubkey`

`function` `const` `inline` `static` | [headers/sign.h:47](../../headers/sign.h#L47)

```c
static inline const unsigned char *sign_pubkey(unsigned id)
```

Docstring: Look up the trusted public key for a key id.

Answers 0 for unknown ids and for the unprovisioned slot.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `id` | `unsigned` |  |  |

**Returns:** `unsigned char *`

---

<a id="ed_sha512_init"></a>

### `ed_sha512_init`

`function` | [headers/sign.h:69](../../headers/sign.h#L69)

```c
void ed_sha512_init(ed_sha *c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `ed_sha *` |  |  |

---

<a id="ed_sha512_update"></a>

### `ed_sha512_update`

`function` | [headers/sign.h:70](../../headers/sign.h#L70)

```c
void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `ed_sha *` |  |  |
| `data` | `unsigned char *` |  |  |
| `len` | `unsigned long` |  |  |

---

<a id="ed_sha512_final"></a>

### `ed_sha512_final`

`function` | [headers/sign.h:71](../../headers/sign.h#L71)

```c
void ed_sha512_final(ed_sha *c, unsigned char out[64]);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `ed_sha *` |  |  |
| `out` | `unsigned char [64]` |  |  |

---

<a id="ed25519_verify"></a>

### `ed25519_verify`

`function` | [headers/sign.h:75](../../headers/sign.h#L75)

```c
int ed25519_verify(const unsigned char sig[64], const unsigned char *msg, unsigned long msglen, const unsigned char pub[32]);
```

Docstring: Verify an Ed25519 signature, 1 valid else 0.

See kernel/ed25519.c for the full contract.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sig` | `unsigned char [64]` |  |  |
| `msg` | `unsigned char *` |  |  |
| `msglen` | `unsigned long` |  |  |
| `pub` | `unsigned char [32]` |  |  |

**Returns:** `int`

---

## Macros

<a id="sign_key_dev"></a>

### `SIGN_KEY_DEV`

`macro` | [headers/sign.h:19](../../headers/sign.h#L19)

```c
#define SIGN_KEY_DEV
```

---

<a id="sign_key_prod"></a>

### `SIGN_KEY_PROD`

`macro` | [headers/sign.h:20](../../headers/sign.h#L20)

```c
#define SIGN_KEY_PROD
```

---

<a id="sign_keys"></a>

### `SIGN_KEYS`

`macro` | [headers/sign.h:21](../../headers/sign.h#L21)

```c
#define SIGN_KEYS
```

---

<a id="sign_pub_bytes"></a>

### `SIGN_PUB_BYTES`

`macro` | [headers/sign.h:22](../../headers/sign.h#L22)

```c
#define SIGN_PUB_BYTES
```

---

<a id="sign_sig_bytes"></a>

### `SIGN_SIG_BYTES`

`macro` | [headers/sign.h:23](../../headers/sign.h#L23)

```c
#define SIGN_SIG_BYTES
```

---

<a id="sign_desc_bytes"></a>

### `SIGN_DESC_BYTES`

`macro` | [headers/sign.h:24](../../headers/sign.h#L24)

```c
#define SIGN_DESC_BYTES
```

---

<a id="sign_note_type"></a>

### `SIGN_NOTE_TYPE`

`macro` | [headers/sign.h:25](../../headers/sign.h#L25)

```c
#define SIGN_NOTE_TYPE
```

---
