DESTDIR?=../..
CURRENT_DLL=DLL_USP10
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: usp10.dll qemu_usp10.dll.so

usp10.dll: main_g.o usp10.def usp10_g.o
	x86_64-w64-mingw32-ld -shared usp10.def *_g.o -o usp10.dll -nostdlib -e DllMain

qemu_usp10.dll.so: main_h.o usp10_h.o
	$(WINEGCC) -shared qemu_usp10.spec *_h.o -o qemu_usp10.dll.so -lusp10

%_g.o: %.c qemu_usp10.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_usp10.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
