CC				= i586-elf-gcc
LD				= i586-elf-ld
AS				= nasm

CFLAGS			= -I. -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS			= -felf
LDFLAGS			= -Tlink.ld

KERNEL			= toastk

TOAST_TARGET	= ~/programming/toast/toast-hdd-img/
SOURCES			=	boot/boot.o \
					screen/console.o \
					string/common.o \
					kernel.o \
					lowlevel.o\
					panic.o

all: $(SOURCES) link

clean:
	- rm *.o */*.o $(KERNEL)

link:
	- $(LD) $(LDFLAGS) -o $(KERNEL) $(SOURCES)

.s.o:
	- nasm $(ASFLAGS) $<

install:
	# need a better way to automate this first bit
	sudo mount /dev/loop0p1 $(TOAST_TARGET)

	sudo cp $(KERNEL) $(TOAST_TARGET)
	ls $(TOAST_TARGET)
	sudo umount $(TOAST_TARGET)
	#bochs -qf bochsrc
	qemu-system-i386 -m 64 -hdd ../toast-hdd.img
