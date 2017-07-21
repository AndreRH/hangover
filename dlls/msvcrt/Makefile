DESTDIR?=../..
CURRENT_DLL=DLL_MSVCRT
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: msvcrt.dll qemu_msvcrt.dll.so

msvcrt.dll: cpp_g.o data_g.o except_g.o exit_g.o file_g.o heap_g.o locale_g.o lock_g.o main_g.o math_g.o misc_g.o msvcrt.def string_g.o wcs_g.o
	x86_64-w64-mingw32-ld -shared msvcrt.def *_g.o -o msvcrt.dll -nostdlib -L../kernel32 -lkernel32 -e DllMain

qemu_msvcrt.dll.so: cpp_h.o data_h.o except_h.o exit_h.o file_h.o heap_h.o locale_h.o lock_h.o main_h.o math_h.o misc_h.o qemu_msvcrt.spec string_h.o wcs_h.o
	$(WINEGCC) -shared qemu_msvcrt.spec *_h.o -o qemu_msvcrt.dll.so

%_g.o: %.c msvcrt.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c msvcrt.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
