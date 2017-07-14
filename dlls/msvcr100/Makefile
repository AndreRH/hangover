DESTDIR?=../..
CURRENT_DLL=DLL_MSVCR100
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: msvcr100.dll qemu_msvcr100.dll.so

msvcr100.dll: msvcr100.def main_g.o exit_g.o heap_g.o string_g.o file_g.o data_g.o locale_g.o math_g.o lock_g.o except_g.o wcs_g.o
	x86_64-w64-mingw32-ld -shared msvcr100.def *_g.o -o msvcr100.dll -nostdlib

qemu_msvcr100.dll.so: main_h.o exit_h.o qemu_msvcr100.spec heap_h.o string_h.o file_h.o data_h.o locale_h.o math_h.o lock_h.o except_h.o wcs_h.o
	$(WINEGCC) -shared qemu_msvcr100.spec *_h.o -o qemu_msvcr100.dll.so

%_g.o: %.c msvcrt.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c msvcrt.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
