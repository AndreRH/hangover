DESTDIR?=../..
CURRENT_DLL=DLL_D3D9
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: d3d9.dll qemu_d3d9.dll.so

d3d9.dll: d3d9.def d3d9_main_g.o main_g.o
	x86_64-w64-mingw32-ld -shared d3d9.def *_g.o -o d3d9.dll -nostdlib -e DllMain

qemu_d3d9.dll.so: main_h.o d3d9_main_h.o qemu_d3d9.spec
	$(WINEGCC) -shared qemu_d3d9.spec *_h.o -o qemu_d3d9.dll.so -ld3d9

%_g.o: %.c qemu_d3d9.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_d3d9.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
