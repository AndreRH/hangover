CURRENT_DLL=DLL_KERNEL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: kernel32.dll qemu_kernel32.dll.so

kernel32.dll: process_g.o main_g.o environ_g.o
	x86_64-w64-mingw32-ld -shared *_g.o -o kernel32.dll -nostdlib

qemu_kernel32.dll.so: process_h.o main_h.o environ_h.o kernel32.spec
	winegcc -shared kernel32.spec *_h.o -o qemu_kernel32.dll.so

%_g.o: %.c kernel32.h
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c kernel32.h
	winegcc $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
