DESTDIR?=../..
CURRENT_DLL=DLL_SHELL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: shell32.dll qemu_shell32.dll.so

shell32.dll: main_g.o
	x86_64-w64-mingw32-ld -shared shell32.def *_g.o -o shell32.dll -nostdlib

qemu_shell32.dll.so: main_h.o
	$(WINEGCC) -shared qemu_shell32.spec *_h.o -o qemu_shell32.dll.so -lshell32

%_g.o: %.c shell32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c shell32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
