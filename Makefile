CC				= i586-elf-gcc
LD				= i586-elf-ld
AS				= nasm

CFLAGS			= -I. -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS			= -felf
LDFLAGS			= -Tlink.ld

TOAST_TARGET	= ~/programming/toast/toast_img/
SOURCES			=	boot/boot.o \
					screen/console.o \
					string/common.o \
					kernel.o \
					lowlevel.o

all: $(SOURCES) link

clean:
	- rm *.o */*.o kernel

link:
	- $(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	- nasm $(ASFLAGS) $<

install:
#	sudo umount $(TOAST_TARGET)
	sudo mount /dev/loop0p1 $(TOAST_TARGET)
	sudo cp kernel $(TOAST_TARGET)
	sudo umount $(TOAST_TARGET)
	bochs -qf bochsrc
