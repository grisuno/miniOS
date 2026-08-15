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

BOOTDEFS = bootdefs.h

bootdef = $(shell sed -n 's/^#define[ \t]*$(1)[ \t]*\([0-9][0-9]*\).*/\1/p' $(BOOTDEFS))

SECTOR_BYTES        = $(call bootdef,SECTOR_BYTES)
STAGE2_LBA          = $(call bootdef,BOOT_STAGE2_LBA)
STAGE2_SECTORS      = $(call bootdef,BOOT_STAGE2_SECTORS)
KERNEL_LBA          = $(shell expr $(STAGE2_LBA) + $(STAGE2_SECTORS))
DISK_ALIGN_SECTORS  = 2048

QEMU_DRIVE = -drive file=os.img,format=raw,if=ide
QEMU_MEM   = -m 256M

CFLAGS_BOOT = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Os
CFLAGS_KERN = -m64 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs \
              -Wall -O1 -mno-red-zone -mno-sse -mno-mmx -fno-pic -fno-stack-protector

PROGS_DIR = progs
PROGS     = $(PROGS_DIR)/hello.o $(PROGS_DIR)/ftest.o $(PROGS_DIR)/minigcc.o \
            $(PROGS_DIR)/ld.o $(PROGS_DIR)/cvm.o $(PROGS_DIR)/lxhello.elf \
            $(PROGS_DIR)/ldhello.elf $(PROGS_DIR)/w1.elf $(PROGS_DIR)/fib.elf \
            $(PROGS_DIR)/minigcc.elf $(PROGS_DIR)/fib.cvm $(PROGS_DIR)/w1.cvm \
            $(PROGS_DIR)/minigcc.cvm $(PROGS_DIR)/bin/cp $(PROGS_DIR)/bin/cp.c \
            $(PROGS_DIR)/test.c $(PROGS_DIR)/fib.c $(PROGS_DIR)/README.txt

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
$(PROGS_DIR)/hello.o: $(PROGS_DIR)/hello.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/ftest.o: $(PROGS_DIR)/ftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

# ── Real Linux ELF executable (ET_EXEC, static, no libc) ─────────
$(PROGS_DIR)/lxhello.elf: $(PROGS_DIR)/lxhello.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

# ── Demo programs: C -> miniGCC -> ld -> ELF / CVM ───────────────
# These are this repository's own sources, compiled through the full
# toolchain at build time. Depending on another project's test fixtures for
# ramdisk content would break the moment that project reorganizes them.
$(PROGS_DIR)/%.s: $(PROGS_DIR)/%.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(PROGS_DIR)/ldhello.elf: $(PROGS_DIR)/ldhello.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(PROGS_DIR)/w1.elf: $(PROGS_DIR)/w1.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(PROGS_DIR)/fib.elf: $(PROGS_DIR)/fib.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

$(PROGS_DIR)/minigcc.o: $(MINIGCC_DIR)/minigcc.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/ld.o: $(LD_DIR)/ld.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/cvm.o: $(CVM_DIR)/cvm.c $(CVM_DIR)/cvm.h cvm_host.c kernel.h
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(PROGS_DIR)/cvm_core.o $(CVM_DIR)/cvm.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(PROGS_DIR)/cvm_host.o cvm_host.c
	$(LD) -m elf_x86_64 -r -o $@ $(PROGS_DIR)/cvm_core.o $(PROGS_DIR)/cvm_host.o
	rm -f $(PROGS_DIR)/cvm_core.o $(PROGS_DIR)/cvm_host.o

# ── CVM modules (assembled from miniGCC output with 'ld') ────────
$(PROGS_DIR)/fib.cvm: $(PROGS_DIR)/fib.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(PROGS_DIR)/w1.cvm: $(PROGS_DIR)/w1.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(PROGS_DIR)/minigcc.cvm: $(TOOLS_DIR)/g2.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

# ── Command path utilities (bin/<cmd>, compiled by the toolchain) ──
# bin/cp: the C source ships on the ramdisk as bin/cp.c and the ELF as
# bin/cp, which the shell resolves for the plain command `cp`.
$(PROGS_DIR)/bin/cp.s: $(PROGS_DIR)/bin/cp.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(PROGS_DIR)/bin/cp: $(PROGS_DIR)/bin/cp.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<

# ── Self-hosted compiler (compiled by minigcc, linked by 'ld') ────
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

$(PROGS_DIR)/minigcc.elf: $(TOOLS_DIR)/g3.s $(LD_TOOL)
	$(LD_TOOL) -f elf -o $@ $<
	chmod +x $@

selfhost: $(PROGS_DIR)/minigcc.elf
	./$(PROGS_DIR)/minigcc.elf $(MINIGCC_DIR)/minigcc.c > $(TOOLS_DIR)/g4.s
	@cmp -s $(TOOLS_DIR)/g3.s $(TOOLS_DIR)/g4.s \
	    && echo "selfhost OK: g3.s == g4.s (fixed point)" \
	    || { echo "selfhost FAIL: fixed point not reached"; exit 1; }

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

stage2.o: stage2.S $(BOOTDEFS) kernel.bin
	$(CC) $(CFLAGS_BOOT) \
	      -DKERNEL_SECTORS=$$(( ($$(stat -c%s kernel.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )) \
	      -c $< -o $@

stage2.elf: stage2.o stage2.ld
	$(LD) -m elf_i386 -T stage2.ld $< -o $@

stage2.bin: stage2.elf
	$(OBJCOPY) -O binary $< $@

# ── Kernel ────────────────────────────────────────────────────────
kernel.o: kernel.c kernel.h
	$(CC) $(CFLAGS_KERN) -c $< -o $@

ramdisk_data.o: ramdisk_data.c
	$(CC) $(CFLAGS_KERN) -c $< -o $@

kernel.elf: kernel.o ramdisk_data.o kernel.ld
	$(LD) -m elf_x86_64 -T kernel.ld kernel.o ramdisk_data.o -o $@

kernel.bin: kernel.elf
	$(OBJCOPY) -O binary $< $@

# ── Disk image ────────────────────────────────────────────────────
os.img: stage1.bin stage2.bin kernel.bin
	@ksec=$$(( ($$(stat -c%s kernel.bin) + $(SECTOR_BYTES) - 1) / $(SECTOR_BYTES) )); \
	 total=$$(( $(KERNEL_LBA) + ksec )); \
	 img=$$(( (total + $(DISK_ALIGN_SECTORS) - 1) / $(DISK_ALIGN_SECTORS) * $(DISK_ALIGN_SECTORS) )); \
	 dd if=/dev/zero of=$@ bs=$(SECTOR_BYTES) count=$$img status=none; \
	 dd if=stage1.bin of=$@ conv=notrunc status=none; \
	 dd if=stage2.bin of=$@ bs=$(SECTOR_BYTES) seek=$(STAGE2_LBA) conv=notrunc status=none; \
	 dd if=kernel.bin of=$@ bs=$(SECTOR_BYTES) seek=$(KERNEL_LBA) conv=notrunc status=none; \
	 echo "=== os.img built ==="; \
	 echo "stage1:  $$(stat -c%s stage1.bin) bytes at LBA 0"; \
	 echo "stage2:  $$(stat -c%s stage2.bin) bytes at LBA $(STAGE2_LBA)"; \
	 echo "kernel:  $$(stat -c%s kernel.bin) bytes ($$ksec sectors) at LBA $(KERNEL_LBA)"; \
	 echo "image:   $$img sectors"

run: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM)

debug: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) -monitor stdio -no-reboot

serial: os.img
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) -display none -serial stdio

test: os.img
	./test_bdd.sh

clean:
	rm -rf $(TOOLS_DIR)
	rm -f *.o *.elf *.bin *.img ramdisk_data.c ramdisk.bin
	rm -f $(PROGS_DIR)/*.o $(PROGS_DIR)/lxhello.elf $(PROGS_DIR)/ldhello.elf \
	      $(PROGS_DIR)/w1.elf $(PROGS_DIR)/fib.elf $(PROGS_DIR)/minigcc.elf \
	      $(PROGS_DIR)/bin/cp $(PROGS_DIR)/bin/cp.s \
	      $(PROGS_DIR)/ldhello.s $(PROGS_DIR)/w1.s $(PROGS_DIR)/fib.s \
	      $(PROGS_DIR)/fib.cvm $(PROGS_DIR)/w1.cvm $(PROGS_DIR)/minigcc.cvm

.SECONDARY:

.PHONY: all run clean debug serial test sources sources-update \
        sources-status toolchain selfhost
