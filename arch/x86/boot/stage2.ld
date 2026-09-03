ENTRY(stage2_main)
SECTIONS
{
    . = 0x9000;
    .text : { *(.text*) *(.rodata*) *(.data*) }
    /DISCARD/ : { *(.comment*) *(.note*) *(.eh_frame*) }
}
