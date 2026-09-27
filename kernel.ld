/* Memory-topology mirrors (item 6 of the review): the user-window
 * bounds live here as linker symbols so the LINKER enforces the
 * layout, not just post-link scripts. Values mirror
 * progs/minios_abi.h (the ring-3 source of truth, which a linker
 * script cannot share); the Makefile check-size gate proves the
 * mirrors equal the ABI header on every build, so the two can never
 * drift. Edit the window in minios_abi.h; the gate fails the build
 * if this file is not updated with it. */
_MINIOS_USER_BASE = 0x400000;
_MINIOS_USER_END = 0x0C000000;
ENTRY(kmain)
SECTIONS
{
    . = 0x100000;
    .text : {
        *(.init.text)
        *(.text*)
    }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .ramdisk : {
        ramdisk_start = .;
        *(.ramdisk)
        ramdisk_end = .;
    }
    /* Absolute symbol carrying the embedded image size. C must read it
     * by address ((unsigned long)ramdisk_size), never by subtracting
     * ramdisk_end - ramdisk_start: pointers into distinct objects make
     * the subtraction undefined behaviour (cppcheck subtractPointers). */
    ramdisk_size = ramdisk_end - ramdisk_start;
    .bss : { *(.bss*) *(COMMON) }
    _kernel_end = .;
    /* Linker-owned topology: absolute symbols carrying the user-window
     * bounds into the ELF symbol table (read C-side by address, like
     * ramdisk_size above), plus a hard link-time fence so an image
     * that overlaps the user window never links. */
    _user_win_lo = _MINIOS_USER_BASE;
    _user_win_hi = _MINIOS_USER_END;
    ASSERT(_kernel_end <= _user_win_lo,
           "kernel image overlaps user window - see progs/minios_abi.h")
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
