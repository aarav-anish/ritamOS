INCDIRS = ./include/
CODEDIRS = . lib

CC = gcc
DEPFLAGS = -MP -MD
NOFLAGS = -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding
CFLAGS = -m32 -Wall -Wextra -Werror -g $(foreach D, $(INCDIRS), -I$(D)) $(DEPFLAGS) $(NOFLAGS)

LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf32

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))

OBJECTS = $(patsubst %.c, %.o, $(CFILES)) loader.o
DEPFILES = $(patsubst %.c, %.d, $(CFILES))

-include $(DEPFILES)

.PHONY: all clean

all: kernel.elf
	mkdir -p iso/boot/grub
	cp grub.cfg iso/boot/grub/grub.cfg
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o ritamOS.iso iso -d /usr/lib/grub/i386-pc

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

runbochs: all
	bochs -f bochsrc.txt

runqemu: all
	qemu-system-i386 -cdrom ritamOS.iso

clean:
	rm -rf *.o *.d lib/*.d lib/*.o kernel.elf ritamOS.iso iso/
