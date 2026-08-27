CC       = gcc
LD       = ld
OBJCOPY  = objcopy
QEMU    ?= qemu-system-x86_64

# The toolchain lives in three sibling repositories. Their locations are
# overridable so the image can be built against a checkout kept anywhere;
# `make sources` clones the ones that are missing and `make sources-update`
# pulls them, which is how the image is rebuilt from the latest upstream code
# instead of the prebuilt objects that ship in progs/.
GIT ?= git

MINIGCC_URL ?= https://github.com/grisuno/miniGCC
CVM_URL     ?= https://github.com/grisuno/cvm
LD_URL      ?= https://github.com/grisuno/ld

MINIGCC_DIR  ?= ../miniGCC
CVM_REPO_DIR ?= ../cvm
CVM_DIR      ?= $(CVM_REPO_DIR)/cvm2
LD_DIR       ?= ../ld

MICROPYTHON_URL ?= https://github.com/micropython/micropython
MICROPYTHON_DIR ?= ../micropython
MICROPYTHON_REF ?= v1.28.0

NUKLEAR_URL ?= https://github.com/Immediate-Mode-UI/Nuklear
NUKLEAR_DIR ?= ../nuklear

# The toolchain binaries are built into a directory this repository owns.
# Several of the sibling repositories ship a committed binary next to their
# sources; using those would mean the image was not built from source at all,
# and one of them is not even executable in a fresh clone.
TOOLS_DIR   ?= build
LD_TOOL     ?= $(TOOLS_DIR)/ld
MINIGCC_BIN ?= $(TOOLS_DIR)/minigcc
CVM_BIN     ?= $(TOOLS_DIR)/cvm

SOURCE_REPOS = $(MINIGCC_DIR)=$(MINIGCC_URL) \
               $(CVM_REPO_DIR)=$(CVM_URL) \
               $(LD_DIR)=$(LD_URL)

CFLAGS_HOST = -std=c99 -Wall -Wextra -O2
CFLAGS_DOOM = -std=gnu99 -Wall -O2 -DNORMALUNIX -DLINUX -DSNDSERV -D_DEFAULT_SOURCE \
              -Wno-unused-result -Wno-sign-compare -Wno-pointer-sign

BOOTDEFS = bootdefs.h

bootdef = $(shell sed -n 's/^#define[ \t]*$(1)[ \t]*\([0-9][0-9]*\).*/\1/p' $(BOOTDEFS))

SECTOR_BYTES        = $(call bootdef,SECTOR_BYTES)
STAGE2_LBA          = $(call bootdef,BOOT_STAGE2_LBA)
STAGE2_SECTORS      = $(call bootdef,BOOT_STAGE2_SECTORS)
KERNEL_LBA          = $(shell expr $(STAGE2_LBA) + $(STAGE2_SECTORS))
DISK_ALIGN_SECTORS  = 2048

QEMU_DRIVE = -drive file=os.img,format=raw,if=ide
QEMU_MEM   = -m 256M
QEMU_NIC   = -nic user,model=rtl8139
QEMU_AUDIO  = -audiodev pa,id=snd0 -machine pc,pcspk-audiodev=snd0

# KASLR randomizes the kernel image's physical base on every boot. Disable
# with `make ENABLE_KASLR=0` when a deterministic physical layout is wanted
# (e.g. register-level debugging of the boot path).
ENABLE_KASLR ?= 1
ifeq ($(ENABLE_KASLR),1)
KASLR_FLAG = -DKASLR
else
KASLR_FLAG =
endif

# The KASLR flag is a variable, not a file, so a flag change would otherwise
# leave a stale stage2.o behind. A stamp records the value in effect and is
# rewritten only when the value changes, so stage2.o rebuilds exactly when
# the flag does.
KASLR_STAMP = .kaslrflag
.PHONY: kaslr-flag-force
$(KASLR_STAMP): kaslr-flag-force
	@new='$(KASLR_FLAG)'; old="$$(cat $@ 2>/dev/null)"; \
	 if [ "$$new" != "$$old" ]; then printf '%s\n' "$$new" > $@; fi

CFLAGS_BOOT = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Os
CFLAGS_KERN = -m64 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs \
              -Wall -O1 -mno-red-zone -mno-sse -mno-mmx -fno-pic -fno-stack-protector \
              -fno-omit-frame-pointer

PROGS_DIR = progs
OBJ_DIR   = $(PROGS_DIR)/objects
CVMOD_DIR = $(PROGS_DIR)/cvm
BIN_DIR   = $(PROGS_DIR)/bin
SRC_DIR   = $(PROGS_DIR)/src
ASM_DIR   = $(PROGS_DIR)/asm
DOC_DIR   = $(PROGS_DIR)/docs

# Everything the ramdisk carries, organized by kind: objects/ (ET_REL
# toolchain), cvm/ (CVM modules), bin/ (Linux ELFs + command path utilities),
# src/ (C sources), asm/ (miniGCC assembly), docs/ and README.txt.
PROGS     = $(OBJ_DIR)/minigcc.o \
            $(OBJ_DIR)/ld.o $(OBJ_DIR)/cvm.o \
            $(BIN_DIR)/minigcc.elf $(BIN_DIR)/cp \
            $(SRC_DIR)/build.py $(SRC_DIR)/shell.py $(SRC_DIR)/test.py \
            $(PROGS_DIR)/etc/alias

all: os.img

# ── Toolchain sources ─────────────────────────────────────────────
# Clone whatever is missing. An existing directory is never touched, so a
# checkout with local work is left exactly as it is.
sources:
	@for pair in $(SOURCE_REPOS); do \
	    dir="$${pair%%=*}"; url="$${pair#*=}"; \
	    if [ -d "$$dir/.git" ]; then \
	        echo "present  $$dir"; \
	    elif [ -e "$$dir" ]; then \
	        echo "skipped  $$dir exists and is not a git clone"; \
	    else \
	        echo "cloning  $$url -> $$dir"; \
	        $(GIT) clone "$$url" "$$dir" || exit 1; \
	    fi; \
	done
	@if [ -d "$(MICROPYTHON_DIR)/.git" ]; then \
	    echo "present  $(MICROPYTHON_DIR)"; \
	elif [ -e "$(MICROPYTHON_DIR)" ]; then \
	    echo "skipped  $(MICROPYTHON_DIR) exists and is not a git clone"; \
	else \
	    echo "cloning  $(MICROPYTHON_URL) -> $(MICROPYTHON_DIR) ($(MICROPYTHON_REF))"; \
	    $(GIT) clone --depth 1 -b $(MICROPYTHON_REF) "$(MICROPYTHON_URL)" "$(MICROPYTHON_DIR)" || exit 1; \
	fi
	@if [ -d "$(NUKLEAR_DIR)/.git" ]; then \
	    echo "present  $(NUKLEAR_DIR)"; \
	elif [ -e "$(NUKLEAR_DIR)" ]; then \
	    echo "skipped  $(NUKLEAR_DIR) exists and is not a git clone"; \
	else \
	    echo "cloning  $(NUKLEAR_URL) -> $(NUKLEAR_DIR)"; \
	    $(GIT) clone --depth 1 "$(NUKLEAR_URL)" "$(NUKLEAR_DIR)" || exit 1; \
	fi

sources-update: sources
	@for pair in $(SOURCE_REPOS); do \
	    dir="$${pair%%=*}"; \
	    if [ -d "$$dir/.git" ]; then \
	        echo "updating $$dir"; \
	        $(GIT) -C "$$dir" pull --ff-only || exit 1; \
	    fi; \
	done

sources-status:
	@for pair in $(SOURCE_REPOS); do \
	    dir="$${pair%%=*}"; \
	    if [ -d "$$dir/.git" ]; then \
	        printf '%-16s %s\n' "$$dir" "$$($(GIT) -C "$$dir" log -1 --format='%h %ad %s' --date=short)"; \
	    elif [ -e "$$dir" ]; then \
	        printf '%-16s %s\n' "$$dir" "local directory, not a git clone"; \
	    else \
	        printf '%-16s %s\n' "$$dir" "absent (run 'make sources')"; \
	    fi; \
	done

# A missing source tree gets a direct instruction instead of make's own
# "no rule to make target" message.
$(LD_DIR)/ld.c $(MINIGCC_DIR)/minigcc.c $(CVM_DIR)/cvm.c:
	@echo "missing $@"
	@echo "run 'make sources' to clone the toolchain repositories from GitHub"
	@exit 1

$(TOOLS_DIR):
	mkdir -p $@

$(LD_TOOL): $(LD_DIR)/ld.c | $(TOOLS_DIR)
	$(CC) $(CFLAGS_HOST) -Wpedantic -o $@ $<

$(MINIGCC_BIN): $(MINIGCC_DIR)/minigcc.c | $(TOOLS_DIR)
	$(CC) $(CFLAGS_HOST) -o $@ $<

$(CVM_BIN): $(CVM_DIR)/cvm.c $(CVM_DIR)/cvm.h | $(TOOLS_DIR)
	$(CC) $(CFLAGS_HOST) -D_GNU_SOURCE -DCVM_STANDALONE -o $@ $(CVM_DIR)/cvm.c -ldl

toolchain: $(LD_TOOL) $(MINIGCC_BIN) $(CVM_BIN)
	@echo "toolchain ready: $(MINIGCC_BIN) $(LD_TOOL) $(CVM_BIN)"

# ── Programs (.o files) ──────────────────────────────────────────
$(OBJ_DIR)/hello.o: $(SRC_DIR)/hello.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(OBJ_DIR)/ftest.o: $(SRC_DIR)/ftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

# ── Real Linux ELF executable (ET_EXEC, static, no libc) ─────────
$(BIN_DIR)/lxhello.elf: $(SRC_DIR)/lxhello.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

# ── Isolation probes: report the runtime CPL and test that kernel-space
#    pointers are rejected by the syscall boundary (same build recipe). ──
$(BIN_DIR)/cpl.elf: $(SRC_DIR)/cpl.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

$(BIN_DIR)/kmem.elf: $(SRC_DIR)/kmem.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

# NX probe: calls a `ret` written to the stack through a function pointer.
# Kept at -O0 so the indirect call survives, and volatile so the buffer
# really lives on the stack instead of being materialized in .data.
$(BIN_DIR)/nx.elf: $(SRC_DIR)/nx.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O0 -o $@ $<

# ── Demo programs: C -> miniGCC -> ld -> ELF / CVM ───────────────
# These are this repository's own sources, compiled through the full
# toolchain at build time. Depending on another project's test fixtures for
# ramdisk content would break the moment that project reorganizes them.
$(ASM_DIR)/%.s: $(SRC_DIR)/%.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/ldhello.elf: $(ASM_DIR)/ldhello.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(BIN_DIR)/w1.elf: $(ASM_DIR)/w1.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(BIN_DIR)/fib.elf: $(ASM_DIR)/fib.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(OBJ_DIR)/minigcc.o: $(MINIGCC_DIR)/minigcc.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(OBJ_DIR)/ld.o: $(LD_DIR)/ld.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(OBJ_DIR)/cvm.o: $(CVM_DIR)/cvm.c $(CVM_DIR)/cvm.h cvm_host.c kernel.h \
                  $(CVM_DIR)/cvm_jit.c $(CVM_DIR)/cvm_jit.h \
                  $(CVM_DIR)/cvm_jit_x86.c $(CVM_DIR)/cvm_jit_x86.h \
                  $(CVM_DIR)/cvm_jit_help.c $(CVM_DIR)/cvm_jit_help.h
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -DCVM_JIT \
	      -DCVM_FREESTANDING -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_core.o $(CVM_DIR)/cvm.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -DCVM_JIT \
	      -DCVM_FREESTANDING -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_host.o cvm_host.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -DCVM_JIT \
	      -DCVM_FREESTANDING -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_jit.o $(CVM_DIR)/cvm_jit.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -DCVM_JIT \
	      -DCVM_FREESTANDING -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_jit_x86.o $(CVM_DIR)/cvm_jit_x86.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -DCVM_JIT \
	      -DCVM_FREESTANDING -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_jit_help.o $(CVM_DIR)/cvm_jit_help.c
	$(LD) -m elf_x86_64 -r -o $@ $(OBJ_DIR)/cvm_core.o $(OBJ_DIR)/cvm_host.o \
	      $(OBJ_DIR)/cvm_jit.o $(OBJ_DIR)/cvm_jit_x86.o $(OBJ_DIR)/cvm_jit_help.o
	rm -f $(OBJ_DIR)/cvm_core.o $(OBJ_DIR)/cvm_host.o \
	      $(OBJ_DIR)/cvm_jit.o $(OBJ_DIR)/cvm_jit_x86.o $(OBJ_DIR)/cvm_jit_help.o

# ── CVM modules (assembled from miniGCC output with 'ld') ────────
$(CVMOD_DIR)/fib.cvm: $(ASM_DIR)/fib.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(CVMOD_DIR)/w1.cvm: $(ASM_DIR)/w1.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(CVMOD_DIR)/minigcc.cvm: $(TOOLS_DIR)/g2.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(TOOLS_DIR)/ld.s: $(LD_DIR)/ld.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(CVMOD_DIR)/ld.cvm: $(TOOLS_DIR)/ld.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(BIN_DIR)/http.elf: $(ASM_DIR)/http.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── Command path utilities (bin/<cmd>, compiled by the toolchain) ──
# bin/cp: the C source ships on the ramdisk as src/cp.c and the ELF as
# bin/cp, which the shell resolves for the plain command `cp`.
$(ASM_DIR)/cp.s: $(SRC_DIR)/cp.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/cp: $(ASM_DIR)/cp.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── lzss / unlzss: one source, two command-path binaries.  The same asm is
# linked under both names; the program selects its mode from argv[0] (-d
# forces decode).  See progs/src/lzss.c and the CLAUDE.md spec.
$(ASM_DIR)/lzss.s: $(SRC_DIR)/lzss.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/lzss: $(ASM_DIR)/lzss.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(BIN_DIR)/unlzss: $(ASM_DIR)/lzss.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── lz4 / unlz4: thin syscall front-ends over the kernel LZ4 (216/217).
# One source, both binaries, argv[0] dispatch.  See progs/src/lz4.c and the
# CLAUDE.md spec.
$(ASM_DIR)/lz4.s: $(SRC_DIR)/lz4.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/lz4: $(ASM_DIR)/lz4.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(BIN_DIR)/unlz4: $(ASM_DIR)/lz4.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── json: JSON validate / pretty-print / query, a hand-rolled parser in the
# miniGCC subset (flat node arrays, no structs).  See progs/src/json.c and
# the CLAUDE.md spec.
$(ASM_DIR)/json.s: $(SRC_DIR)/json.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/json: $(ASM_DIR)/json.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── aes / unaes: AES-256-CTR command tools over one miniGCC source.  The
# S-box is generated procedurally and the container is the fail-closed
# AES1 header.  See progs/src/aes.c and the CLAUDE.md spec.
$(ASM_DIR)/aes.s: $(SRC_DIR)/aes.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/aes: $(ASM_DIR)/aes.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(BIN_DIR)/unaes: $(ASM_DIR)/aes.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── freedom: the headless text browser (curlfree-style engine,
#    FreeDom-style omnibox), rebuilt from its C source at build time.
$(ASM_DIR)/freedom.s: $(SRC_DIR)/freedom.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/freedom: $(ASM_DIR)/freedom.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── DOOM (doomgeneric port) ──────────────────────────────────────────────
# Full doomgeneric engine compiled as a static Linux ELF.  Uses the
# host libc (static) for malloc/printf/fopen etc; the kernel provides
# the Linux syscalls these translate to.  Platform layer is
# doomgeneric_minios.c (VGA Mode 13h framebuffer + PS/2 keyboard).
DOOM_DIR = $(PROGS_DIR)/doomgeneric
DOOM_SRCS = am_map.c doomdef.c doomstat.c dstrings.c d_event.c d_items.c \
            d_iwad.c d_loop.c d_main.c d_mode.c d_net.c f_finale.c \
            f_wipe.c g_game.c hu_lib.c hu_stuff.c info.c i_cdmus.c \
            i_endoom.c i_joystick.c i_scale.c i_sound.c i_system.c \
            i_timer.c memio.c m_argv.c m_bbox.c m_cheat.c m_config.c \
            m_controls.c m_fixed.c m_menu.c m_misc.c m_random.c \
            p_ceilng.c p_doors.c p_enemy.c p_floor.c p_inter.c \
            p_lights.c p_map.c p_maputl.c p_mobj.c p_plats.c \
            p_pspr.c p_saveg.c p_setup.c p_sight.c p_spec.c \
            p_switch.c p_telept.c p_tick.c p_user.c r_bsp.c r_data.c \
            r_draw.c r_main.c r_plane.c r_segs.c r_sky.c r_things.c \
            sha1.c sounds.c statdump.c st_lib.c st_stuff.c s_sound.c \
            tables.c v_video.c wi_stuff.c w_checksum.c w_file.c \
            w_main.c w_wad.c z_zone.c w_file_stdc.c i_input.c \
            i_video.c i_main.c dummy.c doomgeneric.c doomgeneric_minios.c \
            i_minios_sound.c

DOOM_OBJS = $(patsubst %.c,$(DOOM_DIR)/build/%.o,$(DOOM_SRCS))

$(DOOM_DIR)/build:
	mkdir -p $@

$(DOOM_DIR)/build/%.o: $(DOOM_DIR)/%.c | $(DOOM_DIR)/build
	$(CC) $(CFLAGS_DOOM) -I$(DOOM_DIR) -c $< -o $@

$(BIN_DIR)/doomgeneric.elf: $(DOOM_OBJS)
	$(CC) -static -no-pie -o $@ $^ -lm
	chmod +x $@

# ── Archivo WAD de DOOM ──────────────────────────────────────────────────
# Doom1.wad ya está en la raíz del repositorio (4,2 MB). Se empaqueta en
# la ramdisk bajo el nombre bin/doom1.wad para que los programas dentro
# del OS puedan acceder a los niveles.  Se añade a PROGS para que la
# imagen se reconstruya al editarlo.
$(BIN_DIR)/doom1.wad: Doom1.wad
	cp $< $@

# DOOM binaries live on minifs, not the ramdisk (kernel must stay < 3 MB)
MINIFS_DOOM_FILES = $(BIN_DIR)/doomgeneric.elf $(BIN_DIR)/doom1.wad $(BIN_DIR)/DOOM1.WAD

# ── MicroPython (microPython unix port, static glibc ELF) ──────────
# Same contract as DOOM: host gcc -static, ring-3 ET_EXEC, on MiniFS.
# The build writes into the micropython checkout (ports/unix/build-*),
# and the ELF is copied into progs/bin/.
MPY_VARIANT_DIR = $(abspath $(PROGS_DIR)/micropython/variants/minios)
MPY_BUILD       = $(MICROPYTHON_DIR)/ports/unix/build-minios
MPY_CROSS       = $(MICROPYTHON_DIR)/mpy-cross/mpy-cross

$(MICROPYTHON_DIR)/ports/unix/main.c:
	@echo "missing $@"
	@echo "run 'make sources' to clone the MicroPython repository"
	@exit 1

$(MPY_CROSS):
	$(MAKE) -C $(MICROPYTHON_DIR)/mpy-cross -j$(shell nproc 2>/dev/null || echo 4)

$(BIN_DIR)/micropython.elf: $(MICROPYTHON_DIR)/ports/unix/main.c \
                           $(PROGS_DIR)/micropython/variants/minios/mpconfigvariant.h \
                           $(PROGS_DIR)/micropython/variants/minios/mpconfigvariant.mk \
                           $(PROGS_DIR)/micropython/variants/minios/minios_module.c \
                           $(PROGS_DIR)/micropython/variants/minios/manifest.py \
                           $(PROGS_DIR)/micropython/variants/minios/lib/__init__.py \
                           $(PROGS_DIR)/micropython/variants/minios/lib/hello.py \
                           | $(MPY_CROSS)
	$(MAKE) -C $(MICROPYTHON_DIR)/ports/unix \
	    VARIANT_DIR=$(MPY_VARIANT_DIR) \
	    LDFLAGS_EXTRA="-static -no-pie" \
	    -j$(shell nproc 2>/dev/null || echo 4)
	cp $(MPY_BUILD)/micropython $@

# Bare-name alias so `micropython` works without the .elf suffix.
$(BIN_DIR)/micropython: $(BIN_DIR)/micropython.elf
	cp $< $@

# ── Nuklear node editor (nuklear_minios.c + node_editor.c + cvm_emit.c) ──
# The visual "low-code tool for the CVM": a ring-3 Nuklear app that renders
# a node graph into the kernel back-buffer (SYS_NK_FRAME 220) and compiles
# the graph to a .cvm module (cvm_emit.c) the interpreter can run. Built
# exactly like DOOM: host gcc -static, ring-3 ET_EXEC, ships on MiniFS.
NUKLEAR_SRCS = $(PROGS_DIR)/nuklear/nuklear_minios.c \
               $(PROGS_DIR)/nuklear/node_editor.c \
               $(PROGS_DIR)/nuklear/cvm_emit.c

$(NUKLEAR_DIR)/nuklear.h:
	@echo "missing $@"
	@echo "run 'make sources' to clone the Nuklear repository"
	@exit 1

$(BIN_DIR)/nuklear.elf: $(NUKLEAR_SRCS) $(NUKLEAR_DIR)/nuklear.h
	$(CC) -static -no-pie -std=c99 -O2 -Wno-unused-result \
	      -I$(NUKLEAR_DIR) -I$(PROGS_DIR)/nuklear \
	      -o $@ $(NUKLEAR_SRCS) -lm
	chmod +x $@

# Bare-name alias so `nuklear` works without the .elf suffix.
$(BIN_DIR)/nuklear: $(BIN_DIR)/nuklear.elf
	cp $< $@

# aes/unaes live on MiniFS (ramdisk budget): bare-name commands resolved
# against the MiniFS root by shell_run_elf_minifs; src/aes.c rides along so
# the OS can rebuild them without leaving the machine.
MINIFS_FILES = $(MINIFS_DOOM_FILES) $(BIN_DIR)/micropython.elf $(BIN_DIR)/micropython \
               $(BIN_DIR)/nuklear.elf $(BIN_DIR)/nuklear \
               $(BIN_DIR)/aes $(BIN_DIR)/unaes $(SRC_DIR)/aes.c \
               $(BIN_DIR)/json $(SRC_DIR)/json.c \
               $(BIN_DIR)/freedom $(SRC_DIR)/freedom.c $(ASM_DIR)/freedom.s \
               $(BIN_DIR)/lzss $(BIN_DIR)/unlzss $(SRC_DIR)/lzss.c $(ASM_DIR)/lzss.s \
               $(BIN_DIR)/lz4 $(BIN_DIR)/unlz4 $(SRC_DIR)/lz4.c $(ASM_DIR)/lz4.s \
               $(OBJ_DIR)/hello.o $(OBJ_DIR)/ftest.o \
               $(BIN_DIR)/lxhello.elf $(BIN_DIR)/ldhello.elf $(BIN_DIR)/w1.elf \
               $(BIN_DIR)/fib.elf $(BIN_DIR)/http.elf \
               $(BIN_DIR)/cpl.elf $(BIN_DIR)/kmem.elf $(BIN_DIR)/nx.elf \
               $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm \
               $(SRC_DIR)/hello.c $(SRC_DIR)/ftest.c $(SRC_DIR)/test.c \
               $(SRC_DIR)/fib.c $(SRC_DIR)/ldhello.c $(SRC_DIR)/w1.c \
               $(SRC_DIR)/lxhello.c $(SRC_DIR)/cpl.c $(SRC_DIR)/kmem.c \
               $(SRC_DIR)/nx.c $(SRC_DIR)/http.c $(SRC_DIR)/cp.c \
               $(SRC_DIR)/hello.py \
               $(ASM_DIR)/fib.s $(ASM_DIR)/ldhello.s \
               $(ASM_DIR)/w1.s $(ASM_DIR)/http.s $(ASM_DIR)/cp.s \
               $(DOC_DIR)/hostile.html \
               $(PROGS_DIR)/README.txt

# Generation 2: gen1 minigcc compiles its own source; 'ld' links it.
# Generation 3: the ld-linked compiler compiles itself again; the gen3
# binary is what ships on the ramdisk. `make selfhost` additionally
# verifies that gen3 reaches the fixed point: its own output of its own
# source is bit-identical to gen3's assembly.
$(TOOLS_DIR)/g2.s: $(MINIGCC_DIR)/minigcc.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(TOOLS_DIR)/g2.elf: $(TOOLS_DIR)/g2.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<
	chmod +x $@

$(TOOLS_DIR)/g3.s: $(TOOLS_DIR)/g2.elf $(MINIGCC_DIR)/minigcc.c
	./$(TOOLS_DIR)/g2.elf $(MINIGCC_DIR)/minigcc.c > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/minigcc.elf: $(TOOLS_DIR)/g3.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<
	chmod +x $@

selfhost: $(BIN_DIR)/minigcc.elf
	./$(BIN_DIR)/minigcc.elf $(MINIGCC_DIR)/minigcc.c > $(TOOLS_DIR)/g4.s
	@cmp -s $(TOOLS_DIR)/g3.s $(TOOLS_DIR)/g4.s \
	    && echo "selfhost OK: g3.s == g4.s (fixed point)" \
	    || { echo "selfhost FAIL: fixed point not reached"; exit 1; }

# ── Host-side TLS test suite ──────────────────────────────────────
# The TLS engine compiles against the host libc with a generated test
# root injected (tls_test_roots.h); the kernel build never includes it.
# Fixed vectors plus full TLS 1.2 handshakes against openssl-driven
# servers (RSA and ECDSA chains, correct hostname), plus the negative
# set (unknown CA, wrong hostname, expired certificate).
tls_test_roots.h: tls_test.py
	python3 tls_test.py --gen-only

tls_test: tls_test.c tls_test_roots.h tls.c tls_crypto.c tls_x509.c \
          tls.h tls_port.h
	$(CC) $(CFLAGS_HOST) -DTLS_TEST -I. -o $(TOOLS_DIR)/tls_test \
	      tls_test.c tls.c tls_crypto.c tls_x509.c

test-tls: tls_test
	python3 tls_test.py

# ── Ramdisk image ─────────────────────────────────────────────────
# The Makefile is a prerequisite because it carries the file list: editing
# PROGS must invalidate the image even when no individual file changed.
ramdisk.bin: $(PROGS) mkramdisk.py Makefile
	python3 mkramdisk.py $@ $(PROGS)

ramdisk_data.c: ramdisk.bin
	xxd -i $< | sed 's/ramdisk_bin/embedded_ramdisk/; s/unsigned char/const unsigned char/; s/\[\] =/[] __attribute__((section(".ramdisk"))) __attribute__((used)) =/' > $@

# ── Boot path ─────────────────────────────────────────────────────
stage1.o: stage1.S $(BOOTDEFS)
	$(CC) $(CFLAGS_BOOT) -c $< -o $@

stage1.elf: stage1.o stage1.ld
	$(LD) -m elf_i386 -T stage1.ld $< -o $@

stage1.bin: stage1.elf
	$(OBJCOPY) -O binary $< $@

stage2.o: stage2.S $(BOOTDEFS) kernel.bin $(KASLR_STAMP)
	$(CC) $(CFLAGS_BOOT) $(KASLR_FLAG) \
	      -DKERNEL_SECTORS=$$(( ($$(stat -c%s kernel.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )) \
	      -c $< -o $@

stage2.elf: stage2.o stage2.ld
	$(LD) -m elf_i386 -T stage2.ld $< -o $@

stage2.bin: stage2.elf
	$(OBJCOPY) -O binary $< $@

# ── Kernel ────────────────────────────────────────────────────────
kernel.o: kernel.c kernel.h tls.h minifs.h ide.h block.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

net.o: net.c net.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

tls.o: tls.c tls.h tls_port.h tls_roots.h kernel.h net.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

tls_crypto.o: tls_crypto.c tls.h tls_port.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

tls_x509.o: tls_x509.c tls.h tls_port.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

ramdisk_data.o: ramdisk_data.c
	$(CC) $(CFLAGS_KERN) -c $< -o $@

ide.o: ide.c ide.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

block.o: block.c block.h ide.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

minifs.o: minifs.c minifs.h block.h ide.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

lz4_kernel.o: lz4_kernel.c lz4_kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

sched.o: sched.c sched.h kernel.h bootdefs.h vga_fb.h pcspk.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

vga_fb.o: vga_fb.c vga_fb.h kernel.h rtc.h pcspk.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

pcspk.o: pcspk.c pcspk.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

rtc.o: rtc.c rtc.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

isr_stubs.o: isr_stubs.S
	$(CC) -c -m64 $< -o $@

ctx_sw.o: ctx_sw.S
	$(CC) -c -m64 $< -o $@

kernel.elf: kernel.o net.o tls.o tls_crypto.o tls_x509.o ramdisk_data.o ide.o block.o minifs.o lz4_kernel.o sched.o isr_stubs.o ctx_sw.o vga_fb.o pcspk.o rtc.o kernel.ld
	$(LD) -m elf_x86_64 -T kernel.ld kernel.o net.o tls.o tls_crypto.o \
	      tls_x509.o ramdisk_data.o ide.o block.o minifs.o lz4_kernel.o \
	      sched.o isr_stubs.o ctx_sw.o vga_fb.o pcspk.o rtc.o -o $@

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

# ── Disk image ────────────────────────────────────────────────────
# MiniFS image: 128 MB filesystem appended after the kernel, contains DOOM
MINIFS_BLOCKS ?= 32768

# MiniFS content list lives in this Makefile too, so editing it must
# invalidate the filesystem image exactly like ramdisk.bin.
minifs.bin: $(MINIGCC_BIN) $(LD_TOOL) $(MINIFS_FILES) Makefile
	python3 mkfs.minifs.py $@ $(MINIFS_BLOCKS) $(MINIFS_FILES)

os.img: stage1.bin stage2.bin kernel.bin minifs.bin
	@ksec=$$(( ($$(stat -c%s kernel.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )); \
	 total=$$(( $(KERNEL_LBA) + ksec )); \
	 img=$$(( (total + $(DISK_ALIGN_SECTORS) - 1) / $(DISK_ALIGN_SECTORS) * $(DISK_ALIGN_SECTORS) )); \
	 fsec=$$(( ($$(stat -c%s minifs.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )); \
	 final=$$(( img + fsec )); \
	 dd if=/dev/zero of=$@ bs=$(SECTOR_BYTES) count=$$final status=none; \
	 dd if=stage1.bin of=$@ conv=notrunc status=none; \
	 dd if=stage2.bin of=$@ bs=$(SECTOR_BYTES) seek=$(STAGE2_LBA) conv=notrunc status=none; \
	 dd if=kernel.bin of=$@ bs=$(SECTOR_BYTES) seek=$(KERNEL_LBA) conv=notrunc status=none; \
	 dd if=minifs.bin of=$@ bs=$(SECTOR_BYTES) seek=$$img conv=notrunc status=none; \
	 echo "=== os.img built ==="; \
	 echo "stage1:  $$(stat -c%s stage1.bin) bytes at LBA 0"; \
	 echo "stage2:  $$(stat -c%s stage2.bin) bytes at LBA $(STAGE2_LBA)"; \
	 echo "kernel:  $$(stat -c%s kernel.bin) bytes ($$ksec sectors) at LBA $(KERNEL_LBA)"; \
	 echo "minifs:  $$(stat -c%s minifs.bin) bytes ($$fsec sectors) at LBA $$img"; \
	 echo "image:   $$final sectors"

run: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) $(QEMU_AUDIO)

debug: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) -monitor stdio -no-reboot

# Boot paused under the gdb stub. Attach with:
#   gdb -ex 'target remote :1234' -ex 'add-symbol-file kernel.elf 0x100000'
gdb: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) -display none -serial stdio -s -S

serial: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) -display none -serial stdio

test: os.img
	./test_bdd.sh

clean:
	rm -rf $(TOOLS_DIR)
	rm -f *.o *.elf *.bin *.img ramdisk_data.c ramdisk.bin
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/lxhello.elf $(BIN_DIR)/ldhello.elf \
	      $(BIN_DIR)/w1.elf $(BIN_DIR)/fib.elf $(BIN_DIR)/minigcc.elf \
	      $(BIN_DIR)/cpl.elf $(BIN_DIR)/kmem.elf $(BIN_DIR)/nx.elf \
	      $(BIN_DIR)/cp $(BIN_DIR)/freedom \
	      $(BIN_DIR)/lzss $(BIN_DIR)/unlzss \
	      $(BIN_DIR)/lz4 $(BIN_DIR)/unlz4 \
	      $(BIN_DIR)/json \
	      $(BIN_DIR)/aes $(BIN_DIR)/unaes \
	      $(BIN_DIR)/micropython.elf $(BIN_DIR)/micropython \
	      $(BIN_DIR)/nuklear.elf $(BIN_DIR)/nuklear
	rm -f $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm
	rm -f $(ASM_DIR)/fib.s $(ASM_DIR)/ldhello.s $(ASM_DIR)/w1.s \
	      $(ASM_DIR)/http.s $(ASM_DIR)/cp.s $(ASM_DIR)/lzss.s \
	      $(ASM_DIR)/lz4.s $(ASM_DIR)/json.s $(ASM_DIR)/aes.s \
	      $(ASM_DIR)/freedom.s

.SECONDARY:

minifs-mkfs:
	python3 mkfs.minifs.py minifs.bin $(MINIFS_BLOCKS) $(MINIFS_FILES)

minifs-dump:
	python3 minifs_dump.py minifs.bin $(ARGS)

minifs-fsck:
	python3 minifs_fsck.py minifs.bin

.PHONY: all run clean debug gdb serial test sources sources-update \
        sources-status toolchain selfhost minifs-mkfs minifs-dump minifs-fsck
