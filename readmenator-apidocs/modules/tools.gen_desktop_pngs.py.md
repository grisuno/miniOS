# `tools.gen_desktop_pngs`

> Source: [tools/gen_desktop_pngs.py:1](../../tools/gen_desktop_pngs.py#L1) | language `py` | coverage 60.0% | [API index](../index.md)

gen_desktop_pngs.py -- build MiniOS desktop art from user-supplied PNGs.

Sources (images/ by default, overridable with --src-dir):
  paint.png              paint icon source
  animegirl.png          wallpaper source (any size, RGB/RGBA)
  doom.png               DOOM icon source
  doomedit.png           doomedit map-editor icon source
  quake2.png             Quake 2 icon source
  piano.png              piano icon source
  nuklear.png            Nuklear icon source
  vedit.png              vedit editor icon source
  pokemon.png            Pokemon icon source (Pikachu art, not pixel art)
  freedom.png            FreeDom browser icon source

Outputs (under the MiniOS repo):
  progs/icons/doom.png, doomedit.png, quake2.png, piano.png, nuklear.png,
  vedit.png, pokemon.png, file.png, shell.png, paint.png, minicraft.png,
  freedom.png, folder.png, files.png, image.png, object.png  32x32 RGBA
  (folder/files/image/object are the file-browser kind icons).
  progs/wall/wallpaper.png                                   1024x768 RGB

The kernel runs in an 8-bit palette mode, so it maps icon pixels to the
16-entry icon palette and wallpaper pixels to a fixed 6x6x6 colour cube
at boot; these files only need the right dimensions. Icons keep alpha
(the kernel treats fully transparent pixels as transparent). The
wallpaper keeps the whole source visible: it is contain-scaled
(aspect-preserving fit, centred) over a blurred, darkened cover-scaled copy
of itself, so a square source never looks stretched or cropped.

Fail-closed: a missing source aborts with a diagnostic and nonzero exit
before anything is written; each output is written atomically (tmp +
rename), never a partial file.

Usage:
  python3 tools/gen_desktop_pngs.py [--src-dir DIR] [--repo DIR]

## Contents

- **Functions:** [`scaled`](#scaled), [`fit_wallpaper`](#fit_wallpaper), [`write_atomic`](#write_atomic), [`main`](#main)
- **Constants:** [`ICON_SIZE`](#icon_size), [`WALL_SRC`](#wall_src), [`WALL_BACKDROP_BLUR`](#wall_backdrop_blur), [`WALL_BACKDROP_DIM`](#wall_backdrop_dim), [`ICON_JOBS`](#icon_jobs)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_gen_desktop_pngs_py__fit_wallpaper(["fit_wallpaper"])
    n_tools_gen_desktop_pngs_py__scaled(["scaled"])
    n_tools_gen_desktop_pngs_py__main(["main"])
    n_tools_gen_desktop_pngs_py__write_atomic(["write_atomic"])
    n_tools_gen_desktop_pngs_py__fit_wallpaper --> n_tools_gen_desktop_pngs_py__scaled
    n_tools_gen_desktop_pngs_py__main --> n_tools_gen_desktop_pngs_py__fit_wallpaper
    n_tools_gen_desktop_pngs_py__main --> n_tools_gen_desktop_pngs_py__write_atomic
```

## Functions

<a id="scaled"></a>

### `scaled`

`function` | [tools/gen_desktop_pngs.py:75](../../tools/gen_desktop_pngs.py#L75)

```python
def scaled(im, scale)
```

Resize an image by a factor with Lanczos, never below one pixel.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `im` |  |  |  |
| `scale` |  |  |  |

*Called by:* [`fit_wallpaper`](#fit_wallpaper)

---

<a id="fit_wallpaper"></a>

### `fit_wallpaper`

`function` | [tools/gen_desktop_pngs.py:81](../../tools/gen_desktop_pngs.py#L81)

```python
def fit_wallpaper(im)
```

Whole source, centred, over a blurred and dimmed cover-scaled copy.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `im` |  |  |  |

*Calls:* [`scaled`](#scaled)

*Called by:* [`main`](#main)

---

<a id="write_atomic"></a>

### `write_atomic`

`function` | [tools/gen_desktop_pngs.py:93](../../tools/gen_desktop_pngs.py#L93)

```python
def write_atomic(img, path, **save_kw)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `img` |  |  |  |
| `path` |  |  |  |
| `**save_kw` |  |  |  |

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/gen_desktop_pngs.py:99](../../tools/gen_desktop_pngs.py#L99)

```python
def main()
```

*Calls:* [`fit_wallpaper`](#fit_wallpaper), [`write_atomic`](#write_atomic)

---

## Constants

<a id="icon_size"></a>

### `ICON_SIZE`

`constant` | [tools/gen_desktop_pngs.py:49](../../tools/gen_desktop_pngs.py#L49)

```python
ICON_SIZE = 32
```

---

<a id="wall_src"></a>

### `WALL_SRC`

`constant` | [tools/gen_desktop_pngs.py:51](../../tools/gen_desktop_pngs.py#L51)

```python
WALL_SRC = 'animegirl.png'
```

---

<a id="wall_backdrop_blur"></a>

### `WALL_BACKDROP_BLUR`

`constant` | [tools/gen_desktop_pngs.py:52](../../tools/gen_desktop_pngs.py#L52)

```python
WALL_BACKDROP_BLUR = 28
```

---

<a id="wall_backdrop_dim"></a>

### `WALL_BACKDROP_DIM`

`constant` | [tools/gen_desktop_pngs.py:53](../../tools/gen_desktop_pngs.py#L53)

```python
WALL_BACKDROP_DIM = 0.45
```

---

<a id="icon_jobs"></a>

### `ICON_JOBS`

`constant` | [tools/gen_desktop_pngs.py:55](../../tools/gen_desktop_pngs.py#L55)

```python
ICON_JOBS
```

---
