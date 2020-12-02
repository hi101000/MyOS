git pull
nasm -f elf32 kernel.asm -o ksm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel.bin ksm.o kc.o
qemu-system-i386 -kernel kernel.bin
mv kernel.bin MyOS/boot/kernel.bin
grub-mkrescue -o myos.iso MyOS/
git stage kernel.c kernel.h kernel.asm myos.iso
git commit kernel.c kernel.h kernel.asm build.sh Myos.iso
git push
clear
