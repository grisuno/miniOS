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
    .bss : { *(.bss*) *(COMMON) }
    _kernel_end = .;
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
