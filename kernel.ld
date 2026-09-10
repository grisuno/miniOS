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
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
