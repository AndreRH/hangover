DESTDIR?=../..
CURRENT_DLL=DLL_D3DX10_43
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: d3dx10_43.dll

d3dx10_43.dll: d3dx10_43.def
	x86_64-w64-mingw32-ld -shared d3dx10_43.def -o d3dx10_43.dll -nostdlib

clean:
	rm -rf *o *.dll *.so
