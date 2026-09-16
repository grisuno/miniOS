/** Docstring: minifetch.h -- neofetch-style system screen contract.
 *
 * One entry point, shell_cmd_minifetch, prints a two-column screen: the
 * left column renders icons/doom.png as brightness ASCII (decoded live
 * from the ramdisk, embedded text fallback when undecodable) and the
 * right column lists machine, OS and toolchain facts gathered from the
 * same accessors the mem/net/date/smp builtins use. No new facts are
 * invented here; every line reuses an existing kernel source.
 */

#ifndef MINIFETCH_H
#define MINIFETCH_H

void shell_cmd_minifetch(void);

#endif
