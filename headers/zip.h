#ifndef ZIP_H
#define ZIP_H

/* zip.h — MiniOS integration API for the miniz zip library.
 *
 * The shell builtins over miniz (see zip.c) are declared here so kernel.c's
 * shell dispatcher can route the unzip/zip commands. Both builtins work
 * whole-file in memory over the unified file API (ramdisk first, MiniFS
 * fallback), matching the compression tools contract: an archive is fully
 * validated before any entry is published and every failure path reports a
 * diagnostic and releases.
 */

void shell_cmd_unzip(int argc, char **argv);
void shell_cmd_zip(int argc, char **argv);

#endif