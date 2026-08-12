ENTRY(main)
SECTIONS
{
    . = 0x7C00;
    .text : { *(.text*) *(.rodata*) }
    .data : { *(.data*) }
    .sig 0x7DFE : { SHORT(0xAA55) }
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
