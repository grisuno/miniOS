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

# Lua 5.4: the reference implementation built as a ring-3 static ELF, exactly
# like MicroPython (host gcc -static, Linux syscall ABI, ships on MiniFS).
LUA_URL ?= https://github.com/lua/lua
LUA_DIR ?= ../lua
LUA_REF ?= v5.4.7

NUKLEAR_URL ?= https://github.com/Immediate-Mode-UI/Nuklear
NUKLEAR_DIR ?= ../nuklear

# Nuked-OPL3: cycle-accurate YMF262 (OPL3) FM emulator, LGPL-2.1, pure C.
# Renders OPL3 audio to PCM at ring 3 (progs/src/opl3.c) fed to the kernel's
# SB16 driver through the MiniOS PCM syscalls.  The source rides on the host
# checkout; the LGPL relink/source obligations are met by shipping sources.
NUKED_OPL3_URL ?= https://github.com/nukeykt/Nuked-OPL3
NUKED_OPL3_DIR ?= ../nuked-opl3

Q2G_URL  ?= https://github.com/ozkl/quake2generic

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
QEMU_MEM   = -m 1G
# -smp is present so a second vCPU exists, but the kernel is currently
# single-core: without an SMP-aware kernel (AP boot, per-CPU APIC timer/stacks,
# spinlocks) the extra vCPU just idles.  It does not speed anything up yet.
QEMU_NIC   = -nic user,model=rtl8139 -smp 2
QEMU_AUDIO  = -audiodev pa,id=snd0 -machine pc,pcspk-audiodev=snd0 \
              -audiodev pa,id=snd1 -device sb16,iobase=0x220,irq=5,dma=1,audiodev=snd1
# CPU acceleration.  The default is NO acceleration (TCG).  KVM makes pure
# CPU-bound work fast, but it turns every IDE PIO port access into a VM-exit,
# so disk-heavy loads (loading DOOM's WAD, lsfs) get far slower under KVM than
# under TCG, which handles port I/O inline.  Enable KVM explicitly with
# `make run QEMU_ACCEL=-accel kvm` when the workload is CPU-bound.
QEMU_ACCEL  =

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
              -fno-omit-frame-pointer -g \
              -I. -Ithird_party -Ithird_party/stb -Ithird_party/xxhash \
              -I$(PROGS_DIR)

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
            $(OBJ_DIR)/stb.o $(OBJ_DIR)/xxhash.o $(OBJ_DIR)/dlmalloc.o \
            $(BIN_DIR)/minigcc.elf $(BIN_DIR)/cp \
            $(SRC_DIR)/build.py $(SRC_DIR)/shell.py $(SRC_DIR)/test.py \
            $(SRC_DIR)/test.lua \
            $(PROGS_DIR)/etc/alias \
            $(PROGS_DIR)/etc/shortcuts \
            $(PROGS_DIR)/etc/host.zip \
            $(PROGS_DIR)/etc/hostile.zip \
            $(PROGS_DIR)/icons/terminal.png \
            $(PROGS_DIR)/icons/doom.png \
            $(PROGS_DIR)/icons/nuklear.png \
            $(PROGS_DIR)/icons/piano.png \
            $(DOC_DIR)/test.png

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
	@if [ -d "$(NUKED_OPL3_DIR)/.git" ]; then \
	    echo "present  $(NUKED_OPL3_DIR)"; \
	elif [ -e "$(NUKED_OPL3_DIR)" ]; then \
	    echo "skipped  $(NUKED_OPL3_DIR) exists and is not a git clone"; \
	else \
	    echo "cloning  $(NUKED_OPL3_URL) -> $(NUKED_OPL3_DIR)"; \
	    $(GIT) clone --depth 1 "$(NUKED_OPL3_URL)" "$(NUKED_OPL3_DIR)" || exit 1; \
	fi
	@if [ -d "$(LUA_DIR)/.git" ]; then \
	    echo "present  $(LUA_DIR)"; \
	elif [ -e "$(LUA_DIR)" ]; then \
	    echo "skipped  $(LUA_DIR) exists and is not a git clone"; \
	else \
	    echo "cloning  $(LUA_URL) -> $(LUA_DIR) ($(LUA_REF))"; \
	    $(GIT) clone --depth 1 -b $(LUA_REF) "$(LUA_URL)" "$(LUA_DIR)" || exit 1; \
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

# mmap/munmap reclaim probe: repeatedly maps and unmaps a large region.  A
# kernel whose munmap never returns address space drains the cursor until a
# map fails with ENOMEM; exit 1 flags that leak.
$(BIN_DIR)/mmreuse.elf: $(SRC_DIR)/mmreuse.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

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

# ── Ring-0 ET_REL test objects (host-compiled, link against kernel symbols) ──
# stb.o: self-test for the kernel's stb image API (PNG load + pixel check)
$(OBJ_DIR)/stb.o: third_party/stb/stb_selftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -fno-stack-protector -O2 -o $@ $<

# xxhash.o: self-test for the kernel's XXH64 symbol (3 known-answer vectors)
$(OBJ_DIR)/xxhash.o: third_party/xxhash/xxhash_selftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -fno-stack-protector -O2 -o $@ $<

# dlmalloc.o: self-test for the kernel's dlmalloc-backed allocator
# (malloc/free/calloc/realloc burst, realloc copy, calloc zero, bounded growth).
$(OBJ_DIR)/dlmalloc.o: third_party/dlmalloc/dlmalloc_selftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -fno-stack-protector -O2 -o $@ $<

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
	$(CC) $(CFLAGS_DOOM) -I$(DOOM_DIR) -I$(PROGS_DIR) -c $< -o $@

$(BIN_DIR)/doomgeneric.elf: $(DOOM_OBJS)
	$(CC) -static -no-pie -o $@ $^ -lm
	chmod +x $@

# ── DOOM WAD file ───────────────────────────────────────────────────
# Doom1.wad is at the repository root (4.2 MB). It is packed into minifs
# under the name bin/DOOM1.WAD, which is the exact case-sensitive name the
# doomgeneric IWAD loader opens.
$(BIN_DIR)/DOOM1.WAD: Doom1.wad
	cp $< $@

# DOOM binaries live on minifs, not the ramdisk (kernel must stay < 3 MB)
MINIFS_DOOM_FILES = $(BIN_DIR)/doomgeneric.elf $(BIN_DIR)/DOOM1.WAD

# ── Quake 2 (quake2generic port, static glibc ELF) ───────────────────
# Same contract as DOOM: host gcc -static, ring-3 ET_EXEC, on MiniFS.
# Software renderer, 320x200 8-bit paletted, reuses the DOOM back-buffer
# infrastructure (SYS_DOOM_FRAME 211, DOOM_BACKBUF_ADDR 0x0B000000).
# Build is conditional: skipped when the upstream checkout is absent.
Q2G_DIR     = $(PROGS_DIR)/quake2generic
Q2G_UPSTREAM = $(Q2G_DIR)/quake2generic
Q2G_AVAILABLE := $(if $(wildcard $(Q2G_UPSTREAM)/client/cl_main.c),1,0)

Q2G_CLIENT_SRCS = cl_cin.c cl_ents.c cl_fx.c cl_newfx.c cl_input.c \
    cl_inv.c cl_main.c cl_parse.c cl_pred.c cl_tent.c cl_scrn.c \
    cl_view.c console.c keys.c menu.c qmenu.c \
    snd_dma.c snd_mem.c snd_mix.c

Q2G_QCOMMON_SRCS = cmd.c cmodel.c common.c crc.c cvar.c files.c \
    md4.c net_chan.c pmove.c

Q2G_SERVER_SRCS = sv_ccmds.c sv_ents.c sv_game.c sv_init.c sv_main.c \
    sv_send.c sv_user.c sv_world.c

Q2G_REF_SOFT_SRCS = r_aclip.c r_alias.c r_bsp.c r_draw.c r_edge.c \
    r_image.c r_light.c r_main.c r_misc.c r_model.c r_part.c r_poly.c \
    r_polyse.c r_rast.c r_scan.c r_sprite.c r_surf.c

Q2G_GAME_SRCS = g_ai.c p_client.c g_cmds.c g_svcmds.c g_combat.c \
    g_func.c g_items.c g_main.c g_misc.c g_monster.c g_phys.c \
    g_save.c g_spawn.c g_target.c g_trigger.c g_turret.c g_utils.c \
    g_weapon.c m_actor.c m_berserk.c m_boss2.c m_boss3.c m_boss31.c \
    m_boss32.c m_brain.c m_chick.c m_flipper.c m_float.c m_flyer.c \
    m_gladiator.c m_gunner.c m_hover.c m_infantry.c m_insane.c \
    m_medic.c m_move.c m_mutant.c m_parasite.c m_soldier.c \
    m_supertank.c m_tank.c p_hud.c p_trail.c p_view.c p_weapon.c \
    q_shared.c g_chase.c m_flash.c

Q2G_OTHER_SRCS  = q_hunk.c vid_menu.c vid_lib.c q_system.c glob.c
Q2G_NULL_SRCS   = cd_null.c
Q2G_NET_SRCS    = net_unix.c
Q2G_SOUND_SRCS  = snddma_null.c

Q2G_MINIOS_SRCS = q2generic_minios.c

Q2G_ALL_SRCS = $(Q2G_CLIENT_SRCS) $(Q2G_QCOMMON_SRCS) $(Q2G_SERVER_SRCS) \
    $(Q2G_REF_SOFT_SRCS) $(Q2G_GAME_SRCS) $(Q2G_OTHER_SRCS) \
    $(Q2G_NULL_SRCS) $(Q2G_NET_SRCS) $(Q2G_SOUND_SRCS) \
    $(Q2G_MINIOS_SRCS)

CFLAGS_Q2G = -std=gnu99 -Wall -O2 -Dstricmp=strcasecmp \
    -Wno-unused-result -Wno-sign-compare -Wno-pointer-sign \
    -Wno-unused-but-set-variable -Wno-unused-value \
    -Wno-format-security -Wno-format-truncation \
    -Wno-incompatible-pointer-types -Wno-return-type \
    -Wno-parentheses -Wno-aggressive-loop-optimizations \
    -Wno-misleading-indentation -Wno-implicit-function-declaration \
    -Wno-int-conversion -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast

Q2G_OBJS = $(patsubst %.c,$(Q2G_DIR)/build/%.o,$(Q2G_ALL_SRCS))

$(Q2G_DIR)/build:
	mkdir -p $@

Q2G_CFLAGS_ALL = $(CFLAGS_Q2G) -I$(Q2G_UPSTREAM) -I$(Q2G_UPSTREAM)/game \
    -I$(Q2G_UPSTREAM)/client -I$(Q2G_UPSTREAM)/qcommon \
    -I$(Q2G_UPSTREAM)/ref_soft -I$(Q2G_UPSTREAM)/server \
    -I$(Q2G_UPSTREAM)/null -I$(Q2G_UPSTREAM)/other -I$(Q2G_UPSTREAM)/net

# Upstream sources: client/ qcommon/ server/ ref_soft/ game/ other/ null/ net/ sound/
$(Q2G_DIR)/build/cl_%.o: $(Q2G_UPSTREAM)/client/cl_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/console.o: $(Q2G_UPSTREAM)/client/console.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/keys.o: $(Q2G_UPSTREAM)/client/keys.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/menu.o: $(Q2G_UPSTREAM)/client/menu.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/qmenu.o: $(Q2G_UPSTREAM)/client/qmenu.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/snd_dma.o: $(Q2G_UPSTREAM)/client/snd_dma.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/snd_mem.o: $(Q2G_UPSTREAM)/client/snd_mem.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/snd_mix.o: $(Q2G_UPSTREAM)/client/snd_mix.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/cmd.o: $(Q2G_UPSTREAM)/qcommon/cmd.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/cmodel.o: $(Q2G_UPSTREAM)/qcommon/cmodel.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/common.o: $(Q2G_UPSTREAM)/qcommon/common.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/crc.o: $(Q2G_UPSTREAM)/qcommon/crc.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/cvar.o: $(Q2G_UPSTREAM)/qcommon/cvar.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/files.o: $(Q2G_UPSTREAM)/qcommon/files.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/md4.o: $(Q2G_UPSTREAM)/qcommon/md4.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/net_chan.o: $(Q2G_UPSTREAM)/qcommon/net_chan.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/pmove.o: $(Q2G_UPSTREAM)/qcommon/pmove.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/sv_%.o: $(Q2G_UPSTREAM)/server/sv_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/r_%.o: $(Q2G_UPSTREAM)/ref_soft/r_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/g_%.o: $(Q2G_UPSTREAM)/game/g_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/m_%.o: $(Q2G_UPSTREAM)/game/m_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/p_%.o: $(Q2G_UPSTREAM)/game/p_%.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/q_shared.o: $(Q2G_UPSTREAM)/game/q_shared.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/q_hunk.o: $(Q2G_UPSTREAM)/other/q_hunk.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/vid_menu.o: $(Q2G_UPSTREAM)/other/vid_menu.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/vid_lib.o: $(Q2G_UPSTREAM)/other/vid_lib.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/q_system.o: $(Q2G_UPSTREAM)/other/q_system.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/glob.o: $(Q2G_UPSTREAM)/other/glob.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/cd_null.o: $(Q2G_UPSTREAM)/null/cd_null.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/net_unix.o: $(Q2G_UPSTREAM)/net/net_unix.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

$(Q2G_DIR)/build/snddma_null.o: $(Q2G_UPSTREAM)/sound/snddma_null.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -c $< -o $@

# MiniOS platform layer (lives beside the upstream clone)
$(Q2G_DIR)/build/q2generic_minios.o: $(Q2G_DIR)/q2generic_minios.c | $(Q2G_DIR)/build
	$(CC) $(Q2G_CFLAGS_ALL) -I$(PROGS_DIR) -c $< -o $@

ifeq ($(Q2G_AVAILABLE),1)
$(BIN_DIR)/quake2generic.elf: $(Q2G_OBJS)
	$(CC) -static -no-pie -o $@ $^ -lm
	chmod +x $@
else
$(BIN_DIR)/quake2generic.elf:
	@echo "SKIP $@ (upstream checkout missing at $(Q2G_UPSTREAM))"
endif

# The shareware pak0.pak omits the player model; package the loose retail
# player model (held under progs/quake2generic/players/male) as a second pak
# the game loads after pak0.pak.
Q2G_PLAYER_FILES = $(Q2G_DIR)/players/male/tris.md2 \
    $(Q2G_DIR)/players/male/grunt.pcx \
    $(Q2G_DIR)/players/male/weapon.md2 \
    $(Q2G_DIR)/players/male/grunt_i.pcx

$(PROGS_DIR)/baseq2/pak1.pak: $(Q2G_PLAYER_FILES) tools/mkpak1.py
	python3 tools/mkpak1.py

MINIFS_Q2G_FILES = $(if $(Q2G_AVAILABLE),$(BIN_DIR)/quake2generic.elf $(PROGS_DIR)/baseq2,)

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

# ── Lua 5.4 (reference interpreter + minios module, static glibc ELF) ──
# Same contract as MicroPython/DOOM: host gcc -static, ring-3 ET_EXEC, on
# MiniFS.  The upstream lua.c main is replaced by progs/lua/lua_main.c, which
# registers the `minios` kernel-services module (progs/lua/minios.c) as a
# global table, and supports -e / script / REPL.  os.execute() degrades to a
# failure inside MiniOS (no fork), but the REPL, io, string, table, math and
# the minios module all work.
LUA_LIB_SRCS = lapi.c lauxlib.c lbaselib.c lcode.c lcorolib.c lctype.c \
           ldblib.c ldebug.c ldo.c ldump.c lfunc.c lgc.c linit.c liolib.c \
           llex.c lmathlib.c lmem.c loadlib.c lobject.c lopcodes.c loslib.c \
           lparser.c lstate.c lstring.c lstrlib.c ltable.c ltablib.c ltm.c \
           lundump.c lutf8lib.c lvm.c lzio.c
LUA_APP_SRCS = $(PROGS_DIR)/lua/minios.c $(PROGS_DIR)/lua/lua_main.c

$(LUA_DIR)/lua.h:
	@echo "missing $@"
	@echo "run 'make sources' to clone the Lua repository"
	@exit 1

$(BIN_DIR)/lua.elf: $(addprefix $(LUA_DIR)/,$(LUA_LIB_SRCS)) $(LUA_APP_SRCS) $(LUA_DIR)/lua.h
	$(CC) -static -no-pie -std=gnu99 -O2 -Wall -DLUA_USE_LINUX -I$(LUA_DIR) \
	      -o $@ $(addprefix $(LUA_DIR)/,$(LUA_LIB_SRCS)) $(LUA_APP_SRCS) -lm -ldl
	chmod +x $@

# Bare-name alias so `lua` works without the .elf suffix.
$(BIN_DIR)/lua: $(BIN_DIR)/lua.elf
	cp $< $@

# Bare-name alias for the mmap/munmap reclaim probe.
$(BIN_DIR)/mmreuse: $(BIN_DIR)/mmreuse.elf
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
	      -I$(NUKLEAR_DIR) -I$(PROGS_DIR)/nuklear -I$(PROGS_DIR) \
	      -o $@ $(NUKLEAR_SRCS) -lm
	chmod +x $@

# Bare-name alias so `nuklear` works without the .elf suffix.
$(BIN_DIR)/nuklear: $(BIN_DIR)/nuklear.elf
	cp $< $@

# ── piano (Nuklear FM piano -> SB16 PCM) ───────────────────────────────
# A clickable two-octave piano keyboard in Nuklear that plays FM sound
# through the kernel's Sound Blaster 16 driver.  The synth is a DIRECT FM
# engine (modulator + carrier per voice into a sine table) instead of a
# cycle-accurate Yamaha chip emulator, so real-time rendering stays fast in
# QEMU and the UI never stutters.  The app streams 8-bit mono PCM via
# syscalls 221/222.  Built like the node editor (reuses nuklear_minios.c),
# static ring-3, ships on MiniFS.
PIANO_SRCS = $(PROGS_DIR)/piano/piano.c \
             $(PROGS_DIR)/nuklear/nuklear_minios.c

$(BIN_DIR)/piano.elf: $(PIANO_SRCS) $(NUKLEAR_DIR)/nuklear.h \
                      $(NUKED_OPL3_DIR)/opl3.c $(NUKED_OPL3_DIR)/opl3.h
	$(CC) -static -no-pie -std=c99 -O2 -Wno-unused-result \
	      -I$(NUKLEAR_DIR) -I$(PROGS_DIR)/nuklear -I$(NUKED_OPL3_DIR) \
	      -I$(PROGS_DIR) \
	      -o $@ $(PIANO_SRCS) $(NUKED_OPL3_DIR)/opl3.c -lm
	chmod +x $@

# Bare-name alias so `piano` works without the .elf suffix.
$(BIN_DIR)/piano: $(BIN_DIR)/piano.elf
	cp $< $@

# ── opl3 (ring-3 Nuked-OPL3 FM synth -> SB16 PCM) ───────────────────
# Static ELF like DOOM. Renders a melody through the Nuked-OPL3 chip emulator
# and streams 8-bit mono PCM to the kernel SB16 driver (syscalls 221/222).
$(NUKED_OPL3_DIR)/opl3.h:
	@echo "missing $@"
	@echo "run 'make sources' to clone the Nuked-OPL3 repository"
	@exit 1

$(BIN_DIR)/opl3: $(SRC_DIR)/opl3.c $(NUKED_OPL3_DIR)/opl3.c $(NUKED_OPL3_DIR)/opl3.h
	$(CC) -static -no-pie -std=c99 -O2 -Wall \
	      -I$(NUKED_OPL3_DIR) -o $@ $(SRC_DIR)/opl3.c $(NUKED_OPL3_DIR)/opl3.c
	chmod +x $@

# sbtone: headless SB16 diagnostic. Streams a clean 440 Hz sine to the SB16
# and reports submit throughput, isolating the audio path from any GUI.
$(BIN_DIR)/sbtone: $(SRC_DIR)/sbtone.c
	$(CC) -static -no-pie -std=c99 -O2 -Wall -o $@ $(SRC_DIR)/sbtone.c -lm
	chmod +x $@

# ── topogpt3 (TopoGPT3 transformer inference, static ring-3 ELF) ──
# Self-contained single-file C engine.  Loads fp16 weights from MiniFS.
# Built like Lua/DOOM: host gcc -static, ring-3 ET_EXEC, on MiniFS.
TOPOGPT3_SRC = $(PROGS_DIR)/topogpt3/topogpt3.c
TOPOGPT3_WEIGHTS = $(abspath $(PROGS_DIR)/topogpt3/topogpt3.fp16)
TOPOGPT3_VOCAB   = $(abspath $(PROGS_DIR)/topogpt3/vocab.bin)

$(BIN_DIR)/topogpt3.elf: $(TOPOGPT3_SRC)
	$(CC) -static -no-pie -O2 -o $@ $< -lm
	chmod +x $@

# Bare-name alias so `topogpt3` works without the .elf suffix.
$(BIN_DIR)/topogpt3: $(BIN_DIR)/topogpt3.elf
	cp $< $@

# aes/unaes live on MiniFS (ramdisk budget): bare-name commands resolved
# against the MiniFS root by shell_run_elf_minifs; src/aes.c rides along so
# the OS can rebuild them without leaving the machine.
MINIFS_FILES = $(MINIFS_DOOM_FILES) $(MINIFS_Q2G_FILES) $(BIN_DIR)/micropython.elf $(BIN_DIR)/micropython \
               $(BIN_DIR)/lua.elf $(BIN_DIR)/lua \
               $(PROGS_DIR)/lua/minios.c $(PROGS_DIR)/lua/lua_main.c \
               $(BIN_DIR)/topogpt3.elf $(BIN_DIR)/topogpt3 \
               $(TOPOGPT3_WEIGHTS) $(TOPOGPT3_VOCAB) \
               $(BIN_DIR)/nuklear.elf $(BIN_DIR)/nuklear \
               $(BIN_DIR)/piano.elf $(BIN_DIR)/piano \
               $(PROGS_DIR)/piano/piano.c \
               $(BIN_DIR)/opl3 $(SRC_DIR)/opl3.c \
               $(BIN_DIR)/sbtone $(SRC_DIR)/sbtone.c \
               $(BIN_DIR)/aes $(BIN_DIR)/unaes $(SRC_DIR)/aes.c \
               $(BIN_DIR)/json $(SRC_DIR)/json.c \
               $(BIN_DIR)/freedom $(SRC_DIR)/freedom.c $(ASM_DIR)/freedom.s \
               $(BIN_DIR)/lzss $(BIN_DIR)/unlzss $(SRC_DIR)/lzss.c $(ASM_DIR)/lzss.s \
               $(BIN_DIR)/lz4 $(BIN_DIR)/unlz4 $(SRC_DIR)/lz4.c $(ASM_DIR)/lz4.s \
               $(OBJ_DIR)/hello.o $(OBJ_DIR)/ftest.o \
               $(BIN_DIR)/lxhello.elf $(BIN_DIR)/ldhello.elf $(BIN_DIR)/w1.elf \
               $(BIN_DIR)/fib.elf $(BIN_DIR)/http.elf \
               $(BIN_DIR)/cpl.elf $(BIN_DIR)/kmem.elf $(BIN_DIR)/nx.elf \
               $(BIN_DIR)/mmreuse.elf $(BIN_DIR)/mmreuse \
               $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm \
               $(SRC_DIR)/hello.c $(SRC_DIR)/ftest.c $(SRC_DIR)/test.c \
               $(SRC_DIR)/fib.c $(SRC_DIR)/ldhello.c $(SRC_DIR)/w1.c \
               $(SRC_DIR)/lxhello.c $(SRC_DIR)/cpl.c $(SRC_DIR)/kmem.c \
               $(SRC_DIR)/nx.c $(SRC_DIR)/http.c $(SRC_DIR)/cp.c \
               $(SRC_DIR)/hello.py \
               $(SRC_DIR)/test.lua \
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

# xxHash XXH64: pure integer, freestanding-safe, compiled straight into the
# kernel image. Exposed to ET_REL programs through the kernel symbol table
# ("XXH64") and to the shell through the `hash` builtin.  The full xxhash.c
# drags in XXH3/XXH128 which reference memcpy/memcmp/free; redirect those
# to the kernel's own implementations so the link resolves.
xxhash.o: third_party/xxhash/xxhash.c third_party/xxhash/xxhash.h
	$(CC) $(CFLAGS_KERN) -Dmemcpy=kmemcpy -Dmemmove=kmemmove -Dmemset=kmemset -Dmemcmp=kmemcmp -Dmalloc=kmalloc -Dfree=kfree -c $< -o $@

# stb image API: the single-header decode library compiled into the kernel
# with PNG/TGA codecs only and the allocator redirected to the kernel heap.
# -Wno-unused-function silences the JPEG-only static helpers that stb_image.h
# carries even when STBI_NO_JPEG is set.  STBI_ASSERT is redirected to a
# kernel panic so the freestanding build does not need libc assert.
stb_impl.o: third_party/stb/stb_impl.c third_party/stb/stb_image.h \
            third_party/stb/stb_api.h kernel.h
	$(CC) $(CFLAGS_KERN) -Wno-unused-function -c $< -o $@

# miniz zip library: the amalgamated 3.0.2 compiled into the kernel with the
# allocator redirected to the kernel heap and stdio/time stripped (see
# miniz_impl.c). The unzip/zip builtins in zip.c call its public API.
miniz_impl.o: third_party/miniz/miniz_impl.c third_party/miniz/miniz.h \
              third_party/miniz/miniz.c kernel.h
	$(CC) $(CFLAGS_KERN) -Ithird_party/miniz -c $< -o $@

zip.o: zip.c zip.h kernel.h third_party/miniz/miniz.h
	$(CC) $(CFLAGS_KERN) -Ithird_party/miniz -c $< -o $@

# dlmalloc: Doug Lea's malloc compiled into the kernel as a private mspace
# over the fixed heap (HAVE_MORECORE/HAVE_MMAP disabled, ONLY_MSPACES so no
# global malloc/free symbols are emitted). kernel.c delegates kmalloc/kfree/
# realloc/calloc to it via the dlmalloc_* accessors in dlmalloc_impl.c.
dlmalloc_impl.o: third_party/dlmalloc/dlmalloc_impl.c third_party/dlmalloc/malloc.c kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

# Desktop icon PNGs: generated from pixel data by tools/gen_icons.py.
$(PROGS_DIR)/icons/terminal.png $(PROGS_DIR)/icons/doom.png \
$(PROGS_DIR)/icons/nuklear.png $(PROGS_DIR)/icons/piano.png: tools/gen_icons.py
	python3 tools/gen_icons.py $(PROGS_DIR)/icons/

# Zip test fixtures: host-produced archives for the unzip builtin. host.zip
# proves interop with a reference writer; hostile.zip carries escaping entry
# names and must extract without writing outside the extraction root.
$(PROGS_DIR)/etc/host.zip $(PROGS_DIR)/etc/hostile.zip: tools/gen_zip_fixtures.py
	python3 tools/gen_zip_fixtures.py $(PROGS_DIR)/etc/

sched.o: sched.c sched.h kernel.h bootdefs.h vga_fb.h pcspk.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

vga_fb.o: vga_fb.c vga_fb.h kernel.h rtc.h pcspk.h desktop_shortcuts.h \
           third_party/stb/stb_api.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

pcspk.o: pcspk.c pcspk.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

sb16.o: sb16.c sb16.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

rtc.o: rtc.c rtc.h kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

isr_stubs.o: isr_stubs.S
	$(CC) -c -m64 $< -o $@

ctx_sw.o: ctx_sw.S
	$(CC) -c -m64 $< -o $@

# ── SMP AP bootstrap stub ───────────────────────────────────────────────
# A flat binary the BSP copies to AP_STUB_ADDR (0x6000) and wakes every AP
# with.  Placed at its real-mode address by ap_entry.ld, then extracted with
# objcopy and embedded as a C array plus the runtime patch offset.
ap_stub.bin: ap_entry.S ap_entry.ld $(BOOTDEFS)
	$(CC) -c -m64 ap_entry.S -o ap_entry.o
	$(LD) -m elf_x86_64 -T ap_entry.ld ap_entry.o -o ap_entry.elf
	$(OBJCOPY) -O binary ap_entry.elf ap_stub.bin

ap_stub.h: ap_stub.bin
	@echo "/* generated from ap_stub.bin - do not edit */" > $@
	@echo "static const unsigned char ap_stub_blob[] = {" >> $@
	@xxd -i ap_stub.bin | awk '/^  0x/{print "    "$$0}' >> $@
	@echo "};" >> $@
	@echo "static const unsigned int ap_stub_len = $$(stat -c%s ap_stub.bin);" >> $@
	@echo "static const unsigned long ap_patch_off = $$(( 0x$$(nm ap_entry.elf | awk '/ap_patch_slot/{print $$1}') - 0x6000 ));" >> $@

smp.o: smp.c smp.h kernel.h bootdefs.h ap_stub.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

kernel.elf: kernel.o net.o tls.o tls_crypto.o tls_x509.o ramdisk_data.o ide.o block.o minifs.o lz4_kernel.o sched.o isr_stubs.o ctx_sw.o vga_fb.o pcspk.o sb16.o rtc.o xxhash.o stb_impl.o miniz_impl.o zip.o dlmalloc_impl.o smp.o kernel.ld
	$(LD) -m elf_x86_64 -T kernel.ld kernel.o net.o tls.o tls_crypto.o \
	      tls_x509.o ramdisk_data.o ide.o block.o minifs.o lz4_kernel.o \
	      sched.o isr_stubs.o ctx_sw.o vga_fb.o pcspk.o sb16.o rtc.o xxhash.o \
	      stb_impl.o miniz_impl.o zip.o dlmalloc_impl.o smp.o -o $@

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

# ── Disk image ────────────────────────────────────────────────────
# MiniFS image: 128 MB filesystem appended after the kernel, contains DOOM
MINIFS_BLOCKS ?= 65536

# MiniFS content list lives in this Makefile too, so editing it must
# invalidate the filesystem image exactly like ramdisk.bin.
minifs.bin: $(MINIGCC_BIN) $(LD_TOOL) $(MINIFS_FILES) $(PROGS_DIR)/baseq2/pak1.pak mkfs.minifs.py Makefile
	python3 mkfs.minifs.py $@ $(MINIFS_BLOCKS) $(MINIFS_FILES)

os.img: stage1.bin stage2.bin kernel.bin minifs.bin
	@ksec=$$(( ($$(stat -c%s kernel.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )); \
	 total=$$(( $(KERNEL_LBA) + ksec )); \
	 img=$$(( (total + $(DISK_ALIGN_SECTORS) - 1) / $(DISK_ALIGN_SECTORS) * $(DISK_ALIGN_SECTORS) )); \
	 fsec=$$(( ($$(stat -c%s minifs.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )); \
	 swap=131072; \
	 final=$$(( img + fsec + swap )); \
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
	 echo "swap:    $$swap sectors (64 MB) at end of disk"; \
	 echo "image:   $$final sectors"

# ── USB bootable image (MBR partition table + boot chain) ───────────
# Adds a partition table to os.img so fdisk/parted see a valid disk.
# The bootloader (stage1+stage2) reads raw LBAs and ignores the
# partition table, so booting is unchanged.  Tools like Rufus write
# this image to USB in DD mode and the BIOS boots it via INT 13h LBA.
os.usb.img: os.img
	@python3 -c " \
	import struct; \
	img = bytearray(open('$<','rb').read()); \
	assert img[510]==0x55 and img[511]==0xAA, 'no MBR signature'; \
	total = len(img)//512; \
	start = 2048; size = total - start; \
	e = struct.pack('<BBBBBBBBBBBBBBBB', \
	  0x00, 0x00,0x01,0x00, 0x83, 0xFE,0xFF,0xFF, \
	  start&0xFF,(start>>8)&0xFF,(start>>16)&0xFF,(start>>24)&0xFF, \
	  size&0xFF,(size>>8)&0xFF,(size>>16)&0xFF,(size>>24)&0xFF); \
	img[0x1BE:0x1CE] = e; \
	img[0x1CE:0x1FE] = b'\\x00'*(0x1FE-0x1CE); \
	open('$@','wb').write(img); \
	print('os.usb.img: %d sectors, partition LBA %d (%d sectors)' % (total,start,size))"

# ── ISO image (distribution + USB bootable via DD) ──────────────────
# The kernel reads the ramdisk from absolute LBAs (LBA 2048+), which
# is incompatible with ISO9660 disc layout.  This ISO contains os.img
# as a raw file: write it to a USB pendrive with dd or Rufus (DD mode)
# and the BIOS boots it via INT 13h LBA, identical to os.img itself.
# CD/DVD boot (El Torito) is not supported.
os.iso: os.img
	cp $< $@
	@echo "=== os.iso built (raw disk image for USB) ==="; \
	 echo "Write to USB:  sudo dd if=$@ of=/dev/sdX bs=4M status=progress conv=fsync"; \
	 echo "Boot in QEMU:  make run-iso"

# Boot in QEMU (IDE drive, same as real hardware USB boot)
run-iso: os.img
	$(QEMU) -drive file=$<,format=raw,if=ide $(QEMU_MEM) $(QEMU_NIC) $(QEMU_ACCEL) $(QEMU_AUDIO)

# Write os.img directly to a USB drive (INT 13h LBA, same as QEMU IDE)
usb: os.img
	@echo "=== USB writer ==="; \
	 echo "This will DESTROY all data on the target device."; \
	 echo "Available block devices:"; \
	 lsblk -d -o NAME,SIZE,MODEL | grep -v loop | grep -v sr0; \
	 echo ""; \
	 read -p "Enter USB device (e.g. /dev/sdb): " dev; \
	 if [ ! -b "/dev/$$dev" ] && [ ! -b "$$dev" ]; then \
	   echo "Error: not a block device"; exit 1; fi; \
	 dev=$$(echo "$$dev" | sed 's|^/dev/||'); \
	 sudo dd if=os.img of=/dev/$$dev bs=4M status=progress conv=fsync; \
	 echo "=== written to /dev/$$dev ==="

run: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) $(QEMU_ACCEL) $(QEMU_AUDIO)

# Run with KVM acceleration. (Cannot use QEMU_ACCEL=-accel kvm on the command
# line: the space splits the value.) Useful to compare KVM vs TCG.
run-kvm: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) -accel kvm $(QEMU_AUDIO)

# Headless run over the serial console. QEMU's GUI mode renders the VESA
# framebuffer to the host by software, which is slow even under KVM (a ring-3
# GUI app that repaints a whole window each frame appears laggy for that
# reason alone). -display none -serial stdio drops the GUI window and gives a
# fast, interactive console; the SB16 audio backend is kept so tone/sbtone
# can still be heard on the host.
run-headless: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) $(QEMU_ACCEL) \
		-display none -serial stdio $(QEMU_AUDIO)

debug: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC) $(QEMU_ACCEL) -monitor stdio -no-reboot

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
	rm -f .kaslrflag .mutate-state Makefile.bak
	rm -f *.log qemu.log qemu_trace.log qemu_trace2.log test_bdd.log
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
	      $(BIN_DIR)/lua.elf $(BIN_DIR)/lua \
	      $(BIN_DIR)/nuklear.elf $(BIN_DIR)/nuklear \
	      $(BIN_DIR)/quake2generic.elf
	rm -f $(BIN_DIR)/opl3
	rm -f $(BIN_DIR)/sbtone
	rm -f $(BIN_DIR)/piano.elf $(BIN_DIR)/piano
	rm -f $(PROGS_DIR)/icons/piano.png
	rm -f $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm
	rm -f $(ASM_DIR)/fib.s $(ASM_DIR)/ldhello.s $(ASM_DIR)/w1.s \
	      $(ASM_DIR)/http.s $(ASM_DIR)/cp.s $(ASM_DIR)/lzss.s \
	      $(ASM_DIR)/lz4.s $(ASM_DIR)/json.s $(ASM_DIR)/aes.s \
	      $(ASM_DIR)/freedom.s
	rm -f sb16.o smp.o ap_stub.bin ap_stub.h ap_entry.o ap_entry.elf

.SECONDARY:

minifs-mkfs:
	python3 mkfs.minifs.py minifs.bin $(MINIFS_BLOCKS) $(MINIFS_FILES)

minifs-dump:
	python3 minifs_dump.py minifs.bin $(ARGS)

minifs-fsck:
	python3 minifs_fsck.py minifs.bin

.PHONY: all run run-kvm run-headless clean debug gdb serial test \
        sources sources-update sources-status toolchain selfhost \
        minifs-mkfs minifs-dump minifs-fsck os.iso usb os.usb.img
