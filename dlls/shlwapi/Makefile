DESTDIR?=../..
CURRENT_DLL=DLL_SHLWAPI
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: shlwapi.dll qemu_shlwapi.dll.so

shlwapi.dll: main_g.o path_g.o shlwapi.def string_g.o
	x86_64-w64-mingw32-ld -shared shlwapi.def *_g.o -o shlwapi.dll -nostdlib

qemu_shlwapi.dll.so: main_h.o path_h.o qemu_shlwapi.spec string_h.o
	$(WINEGCC) -shared qemu_shlwapi.spec *_h.o -o qemu_shlwapi.dll.so -lshlwapi

%_g.o: %.c shlwapi.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c shlwapi.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
