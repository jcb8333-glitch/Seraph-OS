CC  := x86_64-w64-mingw32-gcc
AR  := x86_64-w64-mingw32-ar

GNUEFI_SRC ?= $(HOME)/.local/src/gnu-efi
GNUEFI     ?= $(HOME)/.local/gnu-efi

BUILD ?= ../../../build
ESP   := $(BUILD)/esp/EFI/BOOT

COMMON := -DGNU_EFI_USE_MS_ABI -ffreestanding -fno-stack-protector \
          -fno-stack-check -fshort-wchar -mno-red-zone \
          -maccumulate-outgoing-args -fno-builtin
INCS   := -I$(GNUEFI)/include -I$(GNUEFI)/include/x86_64 -I$(GNUEFI)/include/protocol

all: $(BUILD)/boot.efi
	mkdir -p $(ESP)
	cp $< $(ESP)/BOOTX64.EFI

$(BUILD)/boot.o: boot.c $(GNUEFI)/lib/libgnuefi.a
	mkdir -p $(BUILD)
	$(CC) $(COMMON) $(INCS) -Wall -c $< -o $@

$(BUILD)/boot.efi: $(BUILD)/boot.o
	$(CC) -nostdlib -Wl,--subsystem,10 -e efi_main $< \
	    -L$(GNUEFI)/lib -lgnuefi -lgcc -o $@

$(GNUEFI)/lib/libgnuefi.a:
	@echo "gnu-efi not installed, run: make setup"; exit 1

setup:
	[ -d $(GNUEFI_SRC) ] || git clone https://github.com/ncroxon/gnu-efi.git $(GNUEFI_SRC)
	mkdir -p $(GNUEFI)/include $(GNUEFI)/lib $(GNUEFI)/obj
	cp -R $(GNUEFI_SRC)/inc/. $(GNUEFI)/include/
	for f in $(GNUEFI_SRC)/lib/*.c $(GNUEFI_SRC)/lib/runtime/*.c \
	         $(GNUEFI_SRC)/lib/x86_64/initplat.c $(GNUEFI_SRC)/lib/x86_64/math.c; do \
	    $(CC) $(COMMON) $(INCS) -I$(GNUEFI_SRC)/lib -w -c $$f \
	        -o $(GNUEFI)/obj/$$(basename $$f .c).o || exit 1; \
	done
	$(AR) rcs $(GNUEFI)/lib/libgnuefi.a $(GNUEFI)/obj/*.o

run: all
	cp /opt/homebrew/share/qemu/edk2-i386-vars.fd $(BUILD)/OVMF_VARS.fd
	qemu-system-x86_64 -machine q35 -m 512M \
	  -drive if=pflash,format=raw,readonly=on,file=/opt/homebrew/share/qemu/edk2-x86_64-code.fd \
	  -drive if=pflash,format=raw,file=$(BUILD)/OVMF_VARS.fd \
	  -drive format=raw,file=fat:rw:$(BUILD)/esp \
	  -serial stdio -net none

clean:
	rm -rf $(BUILD)/boot.o $(BUILD)/boot.efi $(BUILD)/esp

.PHONY: all setup run clean