# `tools/make_usb.sh`

> Source: [tools/make_usb.sh:1](../../tools/make_usb.sh#L1) | language `sh` | coverage 33.3% | [API index](../index.md)

Build the MiniOS bootable USB image and optionally write it to a device.

Wraps the Makefile targets so there is a single source of truth for the layout (os.usb.img), the distribution copy (os.iso) and the write safety checks (make usb): this script only orchestrates, it never writes bytes itself.  Usage: tools/make_usb.sh [--list] [--device /dev/sdX] [--yes] [--vdi]  With no arguments and a terminal on stdin, runs an interactive wizard that asks for every needed value step by step and ends with a bootable USB stick. With no arguments and no terminal (pipe, CI), builds the image, lists candidate devices and exits without writing anything.  Inputs: --list            print candidate target devices and exit. --device DEV      write the image to DEV after building it. --yes             answer the Makefile YES confirmation non-interactively. System-disk and size refusals still apply, they are never skipped. --vdi             also build os.vdi for VirtualBox (hard disk attach). --help            print this help and exit. USB=/dev/sdX      environment fallback for --device.  Outputs: os.usb.img, os.iso (and os.vdi with --vdi) in the repository root.  Failure modes:

## Contents

- **Functions:** [`usage`](#usage), [`wizard`](#wizard)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_make_usb_sh__wizard(["wizard"])
    n_headers_driver_h__device["driver.device"]
    n_tools_make_usb_sh__wizard -.-> n_headers_driver_h__device
```

## Functions

<a id="usage"></a>

### `usage`

`function` | [tools/make_usb.sh:40](../../tools/make_usb.sh#L40)

```bash
usage()
```

---

<a id="wizard"></a>

### `wizard`

`function` | [tools/make_usb.sh:56](../../tools/make_usb.sh#L56)

```bash
wizard()
```

*Calls:* [`device`](headers.driver.h.md#device)

---
