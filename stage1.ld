ENTRY(main)
SECTIONS
{
    . = 0x7C00;
    .text : { *(.text*) *(.rodata*) *(.data*) }
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
