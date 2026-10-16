# `progs/doomgeneric/i_joystick.h`

> Source: [progs/doomgeneric/i_joystick.h:1](../../progs/doomgeneric/i_joystick.h#L1) | language `h` | coverage 47.4% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: System-specific joystick interface.     Number of "virtual" joystick buttons defined in configuration files. This needs to be at least as large as the number of different key bindings supported by the higher-level game code (joyb* variables).  If this bit is set in a configuration file axis value, the axis is not actually a joystick axis, but instead is a "button axis". This means that instead of reading an SDL joystick axis, we read the state of two buttons to get the axis value. This is needed for eg.

## Contents

- **Functions:** [`I_InitJoystick`](#i_initjoystick), [`I_ShutdownJoystick`](#i_shutdownjoystick), [`I_UpdateJoystick`](#i_updatejoystick), [`I_BindJoystickVariables`](#i_bindjoystickvariables)
- **Macros:** [`__I_JOYSTICK__`](#__i_joystick__), [`NUM_VIRTUAL_BUTTONS`](#num_virtual_buttons), [`BUTTON_AXIS`](#button_axis), [`IS_BUTTON_AXIS`](#is_button_axis), [`BUTTON_AXIS_NEG`](#button_axis_neg), [`BUTTON_AXIS_POS`](#button_axis_pos), [`CREATE_BUTTON_AXIS`](#create_button_axis), [`HAT_AXIS`](#hat_axis), [`IS_HAT_AXIS`](#is_hat_axis), [`HAT_AXIS_HAT`](#hat_axis_hat), [`HAT_AXIS_DIRECTION`](#hat_axis_direction), [`CREATE_HAT_AXIS`](#create_hat_axis), [`HAT_AXIS_HORIZONTAL`](#hat_axis_horizontal), [`HAT_AXIS_VERTICAL`](#hat_axis_vertical)

## Functions

<a id="i_initjoystick"></a>

### `I_InitJoystick`

`function` | [progs/doomgeneric/i_joystick.h:63](../../progs/doomgeneric/i_joystick.h#L63)

```c
void I_InitJoystick(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="i_shutdownjoystick"></a>

### `I_ShutdownJoystick`

`function` | [progs/doomgeneric/i_joystick.h:64](../../progs/doomgeneric/i_joystick.h#L64)

```c
void I_ShutdownJoystick(void);
```

---

<a id="i_updatejoystick"></a>

### `I_UpdateJoystick`

`function` | [progs/doomgeneric/i_joystick.h:65](../../progs/doomgeneric/i_joystick.h#L65)

```c
void I_UpdateJoystick(void);
```

---

<a id="i_bindjoystickvariables"></a>

### `I_BindJoystickVariables`

`function` | [progs/doomgeneric/i_joystick.h:67](../../progs/doomgeneric/i_joystick.h#L67)

```c
void I_BindJoystickVariables(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

## Macros

<a id="__i_joystick__"></a>

### `__I_JOYSTICK__`

`macro` | [progs/doomgeneric/i_joystick.h:20](../../progs/doomgeneric/i_joystick.h#L20)

```c
#define __I_JOYSTICK__
```

---

<a id="num_virtual_buttons"></a>

### `NUM_VIRTUAL_BUTTONS`

`macro` | [progs/doomgeneric/i_joystick.h:25](../../progs/doomgeneric/i_joystick.h#L25)

```c
#define NUM_VIRTUAL_BUTTONS
```

Number of "virtual" joystick buttons defined in configuration files.

This needs to be at least as large as the number of different key bindings supported by the higher-level game code (joyb* variables).

---

<a id="button_axis"></a>

### `BUTTON_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:33](../../progs/doomgeneric/i_joystick.h#L33)

```c
#define BUTTON_AXIS
```

If this bit is set in a configuration file axis value, the axis is not actually a joystick axis, but instead is a "button axis".

This means that instead of reading an SDL joystick axis, we read the state of two buttons to get the axis value. This is needed for eg. the PS3 SIXAXIS controller, where the D-pad buttons register as buttons, not as two axes.

---

<a id="is_button_axis"></a>

### `IS_BUTTON_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:36](../../progs/doomgeneric/i_joystick.h#L36)

```c
#define IS_BUTTON_AXIS(axis)
```

Query whether a given axis value describes a button axis.

---

<a id="button_axis_neg"></a>

### `BUTTON_AXIS_NEG`

`macro` | [progs/doomgeneric/i_joystick.h:39](../../progs/doomgeneric/i_joystick.h#L39)

```c
#define BUTTON_AXIS_NEG(axis)
```

Get the individual buttons from a button axis value.

---

<a id="button_axis_pos"></a>

### `BUTTON_AXIS_POS`

`macro` | [progs/doomgeneric/i_joystick.h:40](../../progs/doomgeneric/i_joystick.h#L40)

```c
#define BUTTON_AXIS_POS(axis)
```

---

<a id="create_button_axis"></a>

### `CREATE_BUTTON_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:43](../../progs/doomgeneric/i_joystick.h#L43)

```c
#define CREATE_BUTTON_AXIS(neg, pos)
```

Create a button axis value from two button values.

---

<a id="hat_axis"></a>

### `HAT_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:48](../../progs/doomgeneric/i_joystick.h#L48)

```c
#define HAT_AXIS
```

If this bit is set in an axis value, the axis is not actually a joystick axis, but is a "hat" axis.

This means that we read (one of) the hats on the joystick.

---

<a id="is_hat_axis"></a>

### `IS_HAT_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:50](../../progs/doomgeneric/i_joystick.h#L50)

```c
#define IS_HAT_AXIS(axis)
```

---

<a id="hat_axis_hat"></a>

### `HAT_AXIS_HAT`

`macro` | [progs/doomgeneric/i_joystick.h:53](../../progs/doomgeneric/i_joystick.h#L53)

```c
#define HAT_AXIS_HAT(axis)
```

Get the hat number from a hat axis value.

---

<a id="hat_axis_direction"></a>

### `HAT_AXIS_DIRECTION`

`macro` | [progs/doomgeneric/i_joystick.h:55](../../progs/doomgeneric/i_joystick.h#L55)

```c
#define HAT_AXIS_DIRECTION(axis)
```

Which axis of the hat?

(horizonal or vertical)

---

<a id="create_hat_axis"></a>

### `CREATE_HAT_AXIS`

`macro` | [progs/doomgeneric/i_joystick.h:57](../../progs/doomgeneric/i_joystick.h#L57)

```c
#define CREATE_HAT_AXIS(hat, direction)
```

---

<a id="hat_axis_horizontal"></a>

### `HAT_AXIS_HORIZONTAL`

`macro` | [progs/doomgeneric/i_joystick.h:60](../../progs/doomgeneric/i_joystick.h#L60)

```c
#define HAT_AXIS_HORIZONTAL
```

---

<a id="hat_axis_vertical"></a>

### `HAT_AXIS_VERTICAL`

`macro` | [progs/doomgeneric/i_joystick.h:61](../../progs/doomgeneric/i_joystick.h#L61)

```c
#define HAT_AXIS_VERTICAL
```

---
