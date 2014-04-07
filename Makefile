SOURCES=$(wildcard kernel/*.c)
HEADERS=$(wildcard kernel/*.h)
OBJ=${SOURCES:.c=.o}
all: image
clean:
	rm kernel/*.o
	rm boot/*.o
	rm *.img
	rm *.bin
	rm boot/*.bin
%.o: %.asm
	nasm $< -f elf -o $@
%.o: %.c ${HEADERS}
	gcc -nostdlib -nostdinc -ffreestanding -o $@ -c $<
%.bin: %.asm
	nasm -I boot/ $< -f bin -o $@
kernel.bin: boot/entry.o kernel/load_idt.o ${OBJ}
	ld -Ttext 0x1000 -o $@ $^ --oformat binary
image: kernel.bin boot/bootloader.bin
	cat boot/bootloader.bin kernel.bin > kernel.img
