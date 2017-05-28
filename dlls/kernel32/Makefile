CURRENT_DLL=DLL_KERNEL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: kernel32.dll qemu_kernel32.dll.so

kernel32.dll: process_g.o
	x86_64-w64-mingw32-ld -shared process_g.o -o kernel32.dll -nostdlib

qemu_kernel32.dll.so: process_h.o
	winegcc -shared process_h.o -o qemu_kernel32.dll.so

process_g.o: process.c
	x86_64-w64-mingw32-gcc process.c -c -o process_g.o $(CFLAGS) -DQEMU_DLL_GUEST

process_h.o: process.c
	winegcc process.c -c -o process_h.o $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
