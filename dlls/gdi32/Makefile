DESTDIR?=../..
CURRENT_DLL=DLL_GDI32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: gdi32.dll

gdi32.dll: gdi32.def
	x86_64-w64-mingw32-ld -shared gdi32.def -o gdi32.dll -nostdlib

qemu_gdi32.dll.so: main_h.o qemu_gdi32.spec
	$(WINEGCC) -shared qemu_gdi32.spec *_h.o -o qemu_gdi32.dll.so

%_g.o: %.c gdi32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c gdi32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
