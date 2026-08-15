CC       = gcc
LD       = ld
OBJCOPY  = objcopy
QEMU    ?= qemu-system-x86_64

MINIGCC_DIR ?= ../miniGCC
CVM_DIR     ?= ../cvm/cvm2
LD_DIR      ?= ../ld
LD_TOOL     ?= $(LD_DIR)/ld

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
            $(PROGS_DIR)/fib.cvm $(PROGS_DIR)/w1.cvm $(PROGS_DIR)/minigcc.cvm \
            $(PROGS_DIR)/test.c $(PROGS_DIR)/README.txt

all: os.img

# ── Programs (.o files) ──────────────────────────────────────────
$(PROGS_DIR)/hello.o: $(PROGS_DIR)/hello.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/ftest.o: $(PROGS_DIR)/ftest.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

# ── Real Linux ELF executable (ET_EXEC, static, no libc) ─────────
$(PROGS_DIR)/lxhello.elf: $(PROGS_DIR)/lxhello.c
	$(CC) -static -no-pie -nostdlib -ffreestanding -fno-pic -mno-red-zone -O2 -o $@ $<

# ── ELF executables produced by ld from miniGCC assembly ─────────
$(PROGS_DIR)/ldhello.elf: $(LD_DIR)/tests/t1.s
	$(LD_TOOL) -f elf -o $@ $<

$(PROGS_DIR)/w1.elf: $(LD_DIR)/tests/w1.s
	$(LD_TOOL) -f elf -o $@ $<

$(PROGS_DIR)/fib.elf: $(LD_DIR)/tests/fib.s
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
$(PROGS_DIR)/fib.cvm: $(LD_DIR)/tests/fib.s
	$(LD_TOOL) -f cvm -o $@ $<

$(PROGS_DIR)/w1.cvm: $(LD_DIR)/tests/w1.s
	$(LD_TOOL) -f cvm -o $@ $<

$(PROGS_DIR)/minigcc.cvm: $(MINIGCC_DIR)/minigccg2.s
	$(LD_TOOL) -f cvm -o $@ $<

# ── Ramdisk image ─────────────────────────────────────────────────
ramdisk.bin: $(PROGS) mkramdisk.py
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
	rm -f *.o *.elf *.bin *.img ramdisk_data.c ramdisk.bin
	rm -f $(PROGS_DIR)/*.o $(PROGS_DIR)/lxhello.elf $(PROGS_DIR)/ldhello.elf \
	      $(PROGS_DIR)/w1.elf $(PROGS_DIR)/fib.elf

.PHONY: all run clean debug serial test
