DESTDIR?=../..
CURRENT_DLL=DLL_USER32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: user32.dll qemu_user32.dll.so

user32.dll: user32.def caret_g.o main_g.o lstr_g.o
	x86_64-w64-mingw32-ld -shared user32.def *_g.o -o user32.dll -nostdlib

qemu_user32.dll.so: caret_h.o main_h.o qemu_user32.spec lstr_h.o
	$(WINEGCC) -shared qemu_user32.spec *_h.o -o qemu_user32.dll.so -luser32

%_g.o: %.c user32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c user32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
