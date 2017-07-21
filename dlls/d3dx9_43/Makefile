DESTDIR?=../..
CURRENT_DLL=DLL_D3DX9_43
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: d3dx9_43.dll qemu_d3dx9_43.dll.so

d3dx9_43.dll: d3dx9_43.def main_g.o math_g.o
	x86_64-w64-mingw32-ld -shared d3dx9_43.def *_g.o -o d3dx9_43.dll -nostdlib -e DllMain

qemu_d3dx9_43.dll.so: main_h.o math_h.o
	$(WINEGCC) -shared qemu_d3dx9_43.spec *_h.o -o qemu_d3dx9_43.dll.so -ld3dx9

%_g.o: %.c d3dx9_43.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c d3dx9_43.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
