CC       = gcc
LD       = ld
OBJCOPY  = objcopy

CFLAGS_BOOT = -m16 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -Os
CFLAGS_KERN = -m64 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs \
              -Wall -O1 -mno-red-zone -mno-sse -mno-mmx -fno-pic -fno-stack-protector

PROGS_DIR = progs
PROGS     = $(PROGS_DIR)/hello.o $(PROGS_DIR)/ftest.o $(PROGS_DIR)/minigcc.o \
            $(PROGS_DIR)/cvm.o $(PROGS_DIR)/lxhello.elf \
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

$(PROGS_DIR)/minigcc.o: /home/grisun0/src_note/c/miniGCC/minigcc.c
	$(CC) -c -ffreestanding -nostdlib -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/cvm.o: /home/grisun0/src_note/c/cvm/cvm2/cvm.c
	$(CC) -c -ffreestanding -nostdlib -D_GNU_SOURCE -DCVM_NO_MAIN -m64 -mno-red-zone -fno-pic -O2 -o $@ $<

$(PROGS_DIR)/test.c $(PROGS_DIR)/README.txt:
	@test -f $@ || true

# ── Ramdisk image ─────────────────────────────────────────────────
ramdisk.bin: $(PROGS)
	python3 mkramdisk.py $@ $(PROGS)

ramdisk_data.c: ramdisk.bin
	xxd -i $< | sed 's/ramdisk_bin/embedded_ramdisk/; s/unsigned char/const unsigned char/; s/\[\] =/[] __attribute__((section(".ramdisk"))) __attribute__((used)) =/' > $@

# ── Bootloader ────────────────────────────────────────────────────
bootloader.o: bootloader.c
	$(CC) $(CFLAGS_BOOT) -c $< -o $@

bootloader.elf: bootloader.o boot.ld
	$(LD) -m elf_i386 -T boot.ld $< -o $@

bootloader.bin: bootloader.elf
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
os.img: bootloader.bin kernel.bin
	dd if=/dev/zero of=$@ bs=512 count=2880 2>/dev/null
	dd if=bootloader.bin of=$@ conv=notrunc 2>/dev/null
	dd if=kernel.bin of=$@ bs=512 seek=1 conv=notrunc 2>/dev/null
	@echo "=== os.img built ==="
	@echo "bootloader: $$(stat -c%s bootloader.bin) bytes"
	@echo "kernel:     $$(stat -c%s kernel.bin) bytes"
	@ls -lh $@

run: os.img
	qemu-system-x86_64 -fda os.img -m 256M

debug: os.img
	qemu-system-x86_64 -fda os.img -m 256M -monitor stdio -no-reboot

serial: os.img
	qemu-system-x86_64 -fda os.img -m 256M -display none -serial stdio

clean:
	rm -f *.o *.elf *.bin *.img ramdisk_data.c ramdisk.bin
	rm -f $(PROGS_DIR)/*.o $(PROGS_DIR)/lxhello.elf

.PHONY: all run clean debug serial

