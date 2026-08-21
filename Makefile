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
QEMU_NIC   = -nic user,model=rtl8139

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
              -Wall -O1 -mno-red-zone -mno-sse -mno-mmx -fno-pic -fno-stack-protector

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
PROGS     = $(OBJ_DIR)/hello.o $(OBJ_DIR)/ftest.o $(OBJ_DIR)/minigcc.o \
            $(OBJ_DIR)/ld.o $(OBJ_DIR)/cvm.o \
            $(BIN_DIR)/lxhello.elf $(BIN_DIR)/ldhello.elf $(BIN_DIR)/w1.elf \
            $(BIN_DIR)/fib.elf $(BIN_DIR)/minigcc.elf $(BIN_DIR)/http.elf \
            $(BIN_DIR)/cpl.elf $(BIN_DIR)/kmem.elf $(BIN_DIR)/nx.elf \
            $(BIN_DIR)/cp $(BIN_DIR)/freedom \
            $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm \
            $(SRC_DIR)/hello.c $(SRC_DIR)/ftest.c $(SRC_DIR)/test.c \
            $(SRC_DIR)/fib.c $(SRC_DIR)/ldhello.c $(SRC_DIR)/w1.c \
            $(SRC_DIR)/lxhello.c $(SRC_DIR)/cpl.c $(SRC_DIR)/kmem.c \
            $(SRC_DIR)/nx.c $(SRC_DIR)/http.c $(SRC_DIR)/freedom.c \
            $(SRC_DIR)/cp.c $(ASM_DIR)/fib.s $(ASM_DIR)/ldhello.s \
            $(ASM_DIR)/w1.s $(ASM_DIR)/http.s $(ASM_DIR)/cp.s \
            $(ASM_DIR)/freedom.s $(DOC_DIR)/hostile.html \
            $(PROGS_DIR)/README.txt

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

$(OBJ_DIR)/cvm.o: $(CVM_DIR)/cvm.c $(CVM_DIR)/cvm.h cvm_host.c kernel.h
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_core.o $(CVM_DIR)/cvm.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -m64 -mno-red-zone \
	      -fno-pic -O2 -I$(CVM_DIR) \
	      -o $(OBJ_DIR)/cvm_host.o cvm_host.c
	$(LD) -m elf_x86_64 -r -o $@ $(OBJ_DIR)/cvm_core.o $(OBJ_DIR)/cvm_host.o
	rm -f $(OBJ_DIR)/cvm_core.o $(OBJ_DIR)/cvm_host.o

# ── CVM modules (assembled from miniGCC output with 'ld') ────────
$(CVMOD_DIR)/fib.cvm: $(ASM_DIR)/fib.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(CVMOD_DIR)/w1.cvm: $(ASM_DIR)/w1.s $(LD_TOOL)
	$(LD_TOOL) -f cvm -o $@ $<

$(CVMOD_DIR)/minigcc.cvm: $(TOOLS_DIR)/g2.s $(LD_TOOL)
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

# ── freedom: the headless text browser (curlfree-style engine,
#    FreeDom-style omnibox), rebuilt from its C source at build time.
$(ASM_DIR)/freedom.s: $(SRC_DIR)/freedom.c $(MINIGCC_BIN)
	$(MINIGCC_BIN) $< > $@.tmp && mv $@.tmp $@

$(BIN_DIR)/freedom: $(ASM_DIR)/freedom.s $(LD_TOOL)
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
kernel.o: kernel.c kernel.h tls.h
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

kernel.elf: kernel.o net.o tls.o tls_crypto.o tls_x509.o ramdisk_data.o kernel.ld
	$(LD) -m elf_x86_64 -T kernel.ld kernel.o net.o tls.o tls_crypto.o \
	      tls_x509.o ramdisk_data.o -o $@

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
	$(QEMU) $(QEMU_DRIVE) $(QEMU_MEM) $(QEMU_NIC)

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
	      $(BIN_DIR)/cp $(BIN_DIR)/freedom
	rm -f $(CVMOD_DIR)/fib.cvm $(CVMOD_DIR)/w1.cvm $(CVMOD_DIR)/minigcc.cvm
	rm -f $(ASM_DIR)/fib.s $(ASM_DIR)/ldhello.s $(ASM_DIR)/w1.s \
	      $(ASM_DIR)/http.s $(ASM_DIR)/cp.s $(ASM_DIR)/freedom.s

.SECONDARY:

.PHONY: all run clean debug gdb serial test sources sources-update \
        sources-status toolchain selfhost
