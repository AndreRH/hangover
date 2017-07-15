DESTDIR?=../..
CURRENT_DLL=DLL_COMCTL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: comctl32.dll qemu_comctl32.dll.so

comctl32.dll: comctl32.def commctrl_g.o main_g.o
	x86_64-w64-mingw32-ld -shared comctl32.def *_g.o -o comctl32.dll -nostdlib -e DllMain

qemu_comctl32.dll.so: commctrl_h.o main_h.o qemu_comctl32.spec
	$(WINEGCC) -shared qemu_comctl32.spec *_h.o -o qemu_comctl32.dll.so -lcomctl32

%_g.o: %.c comctl32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c comctl32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
