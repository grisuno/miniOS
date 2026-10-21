# Acknowledgments

MiniOS stands on the shoulders of third-party software. Thanks to every
author and contributor behind the projects below; without their work this
system would not exist.

- [DOOM](https://github.com/SPinti-Software/doomgeneric), by id Software, played through the `doomgeneric` port layer by ozkl, which is the bridge MiniOS builds its windowed port on.
- [Quake 2](https://github.com/ozkl/quake2generic), by id Software, played through `quake2generic`, also by ozkl, reusing the same back-buffer infrastructure as DOOM.
- [MicroPython](https://github.com/micropython/micropython), by Damien George and the MicroPython contributors: the unix-port `minios` variant runs unmodified sources as ring-3 programs.
- [Lua.org](https://www.lua.org/), by the PUC-Rio team (Roberto Ierusalimschy, Luiz Henrique de Figueiredo, Waldemar Celes): the 5.4 reference interpreter runs as a ring-3 static ELF.
- [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear), by Dmitry Hrabrov (vurtun): the single-header immediate-mode UI library behind the node editor, the file browser, the paint program, vedit and every other graphical tool.
- [Nuked-OPL3](https://github.com/nukeykt/Nuked-OPL3), by nukeykt: the cycle-accurate YMF262 emulator that renders FM audio for the piano at ring 3.
- [Lexbor](https://github.com/lexbor/lexbor), by Alexander Borisov and contributors: the HTML parser behind the real FreeDom engine port.
- [miniz](https://github.com/richgel999/miniz), by Rich Geldreich and contributors: the zip reader and writer behind the `zip` and `unzip` shell builtins.
- [dlmalloc](https://github.com/ennorehling/dlmalloc), by Doug Lea: the kernel heap allocator.
- [stb](https://github.com/nothings/stb), by Sean Barrett and contributors: `stb_image` decodes the PNG previews, icons and paint files.
- [xxHash](https://github.com/cyan4973/xxhash), by Yann Collet and contributors: the checksums behind the integrity selftests.
- [The pokecrystal disassembly project](https://github.com/arcanite24/gb-recompiled) and its community: the data source the Pokemon target builds from. [gb-recompiled](https://github.com/arcanite24/gb-recompiled)
- [QEMU](https://www.qemu.org/), by Fabrice Bellard and the QEMU developers: the machine MiniOS boots, tests and debugs on every day of development.
- [raycastlib](https://gitlab.com/drummyfish/raycastlib), public domain (CC0) ray casting library by drummyfish, cloned as a reference-only checkout that is never linked into the OS. [Pokitto demos](https://gitlab.com/drummyfish/Pokitto-Raycasting)

