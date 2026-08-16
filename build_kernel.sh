set -e

make clean
make all

cd grub_modules
gcc -O0 -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nostdinc -fno-pic -g -c banking_program.c -o banking_program.o
ld -T banking_program.ld -melf_i386 banking_program.o ../lib/io.o ../lib/util_lib.o -o banking_program.elf
objcopy -O binary banking_program.elf banking_program.bin

gcc -O0 -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostdlib -nostdinc -fno-pic -g -c evil_program.c -o evil_program.o
ld -T evil_program.ld -melf_i386 evil_program.o ../lib/io.o ../lib/util_lib.o ../lib/serial.o -o evil_program.elf
objcopy -O binary evil_program.elf evil_program.bin

cd ..

cp grub_modules/banking_program.bin iso/boot/banking_program.bin
cp grub_modules/evil_program.bin iso/boot/evil_program.bin
cp grub.cfg iso/boot/grub/grub.cfg
grub-mkrescue -o ritamOS.iso iso -d /usr/lib/grub/i386-pc

qemu-system-i386 -cdrom ritamOS.iso -serial file:com1.out
