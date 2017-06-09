DESTDIR?=../..
CURRENT_DLL=DLL_MSVCRT
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: msvcrt.dll qemu_msvcrt.dll.so

msvcrt.dll: msvcrt.def main_g.o exit_g.o heap_g.o string_g.o file_g.o data_g.o locale_g.o math_g.o
	x86_64-w64-mingw32-ld -shared msvcrt.def *_g.o -o msvcrt.dll -nostdlib

qemu_msvcrt.dll.so: main_h.o exit_h.o qemu_msvcrt.spec heap_h.o string_h.o file_h.o data_h.o locale_h.o math_h.o
	winegcc -shared qemu_msvcrt.spec *_h.o -o qemu_msvcrt.dll.so

%_g.o: %.c msvcrt.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c msvcrt.h Makefile
	winegcc $< -c -o $@ $(CFLAGS) -I$(DESTDIR)/build/install/include

clean:
	rm -rf *o *.dll *.so
