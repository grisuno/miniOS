/* ap_entry.ld - place the AP bootstrap stub at its real-mode SIPI address.
 * The stub is a flat binary loaded at 0x6000 (below 1 MB); every absolute
 * address inside it is correct only when it lives at AP_STUB_ADDR, which is
 * what this script guarantees.  objcopy -O binary extracts the bytes. */

OUTPUT_FORMAT(elf64-x86-64)
SECTIONS
{
    . = 0x6000;
    .text : { *(.text*) }
    . = ALIGN(4);
}
