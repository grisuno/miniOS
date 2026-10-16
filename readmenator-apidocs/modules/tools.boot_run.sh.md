# `tools/boot_run.sh`

> Source: [tools/boot_run.sh:1](../../tools/boot_run.sh#L1) | language `sh` | coverage 100.0% | [API index](../index.md)

boot_run.sh -- boot the MiniOS image in QEMU and drive the shell over the serial console with a list of commands, capturing the full transcript.

This is the reusable harness behind the one-shot manual checks (lua in-OS suite, DOOM/Quake 2 autoquit render tests, toolchain compile/link/run) so a future run does not hand-roll a QEMU launch.  The guest powers itself off through the ACPI port; the timeout is only a safety net for hangs.  Usage: tools/boot_run.sh "cmd1" "cmd2" ... [--timeout N] [--log FILE]  - every non-option argument is a shell command sent to the guest in order - --timeout N   per-run timeout in seconds (default 200) - --log FILE    write the console transcript to FILE (default ./boot_run.log)  Examples: tools/boot_run.sh "lua src/test.lua" tools/boot_run.sh "gfx frames" "run doomgeneric.elf mini_autoframes 150" \ "gfx frames" --timeout 200 tools/boot_run.sh "gfx frames" \ "run bin/quake2generic.elf +set basedir . +set minios_autoframes 400" \ "gfx frames" --timeout 300
