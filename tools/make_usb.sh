#!/usr/bin/env bash
# Build the MiniOS bootable USB image and optionally write it to a device.
#
# Wraps the Makefile targets so there is a single source of truth for the
# layout (os.usb.img), the distribution copy (os.iso) and the write safety
# checks (make usb): this script only orchestrates, it never writes bytes
# itself.
#
# Usage:
#   tools/make_usb.sh [--list] [--device /dev/sdX] [--yes] [--vdi]
#
# With no arguments and a terminal on stdin, runs an interactive wizard
# that asks for every needed value step by step and ends with a bootable
# USB stick. With no arguments and no terminal (pipe, CI), builds the
# image, lists candidate devices and exits without writing anything.
#
# Inputs:
#   --list            print candidate target devices and exit.
#   --device DEV      write the image to DEV after building it.
#   --yes             answer the Makefile YES confirmation non-interactively.
#                     System-disk and size refusals still apply, they are
#                     never skipped.
#   --vdi             also build os.vdi for VirtualBox (hard disk attach).
#   --help            print this help and exit.
#   USB=/dev/sdX      environment fallback for --device.
#
# Outputs:
#   os.usb.img, os.iso (and os.vdi with --vdi) in the repository root.
#
# Failure modes:
#   Exits nonzero when the build fails, the device is not a block device,
#   the Makefile refuses the target (system disk, too small), or the YES
#   confirmation is not given. Never writes without the Makefile checks.
set -euo pipefail

DEVICE="${USB:-}"
ASSUME_YES=0
BUILD_VDI=0

usage() {
    sed -n '2,/^set -euo pipefail/p' "$0" | sed '$d' | sed 's/^# \?//'
}

while [ $# -gt 0 ]; do
    case "$1" in
        --list)    exec make usb-list ;;
        --device)  DEVICE="${2:?--device needs an argument}"; shift 2 ;;
        --yes)     ASSUME_YES=1; shift ;;
        --vdi)     BUILD_VDI=1; shift ;;
        --help|-h) usage; exit 0 ;;
        /dev/*)    DEVICE="$1"; shift ;;
        *)         echo "make_usb.sh: unknown argument: $1" >&2; usage >&2; exit 2 ;;
    esac
done

wizard() {
    echo "=== MiniOS USB wizard ==="
    echo "This builds the bootable image and writes it to a USB stick."
    echo ""
    make usb-list
    echo ""
    while true; do
        read -r -p "Step 1/3 - target device (e.g. /dev/sdb, 'q' to quit): " DEVICE
        case "$DEVICE" in
            q|Q|quit|exit) echo "Aborted."; exit 1 ;;
        esac
        case "$DEVICE" in
            /dev/*) ;;
            *) DEVICE="/dev/$DEVICE" ;;
        esac
        if [ -b "$DEVICE" ]; then
            break
        fi
        echo "'$DEVICE' is not a block device, try again."
        DEVICE=""
    done
    echo "Target: $DEVICE ($(lsblk -dno SIZE,MODEL "$DEVICE" | tr -s ' '))"
    read -r -p "Step 2/3 - also build os.vdi for VirtualBox? [y/N]: " ans
    case "$ans" in
        [Yy]*) BUILD_VDI=1 ;;
    esac
    echo "Step 3/3 - writing next (you confirm with YES before anything is written)."
}

if [ -z "$DEVICE" ]; then
    if [ -t 0 ]; then
        wizard
    else
        echo "=== [1/2] building bootable image ==="
        make os.usb.img os.iso
        echo "=== [2/2] image ready, no device given ==="
        make usb-list
        echo ""
        echo "Write it with:  tools/make_usb.sh --device /dev/sdX"
        echo "Or manually:    make usb USB=/dev/sdX"
        echo "Rufus users: select os.iso in DD mode (NOT ISO mode)."
        exit 0
    fi
fi

if [ ! -b "$DEVICE" ]; then
    echo "make_usb.sh: $DEVICE is not a block device" >&2
    exit 1
fi

echo "=== [1/3] building bootable image ==="
make os.usb.img os.iso

if [ "$BUILD_VDI" -eq 1 ]; then
    echo "=== [2/3] building VirtualBox disk ==="
    make vdi
fi

echo "=== [3/3] writing to $DEVICE ==="
if [ "$ASSUME_YES" -eq 1 ]; then
    printf 'YES\n' | make usb "USB=$DEVICE"
else
    make usb "USB=$DEVICE"
fi

echo ""
echo "Done. Boot the stick with Legacy/CSM boot, Secure Boot off,"
echo "USB-HDD first in the boot order. There is no UEFI entry."
echo "Rufus users: select os.iso in DD mode (NOT ISO mode)."
