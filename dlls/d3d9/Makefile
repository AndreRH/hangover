DESTDIR?=../..
CURRENT_DLL=DLL_D3D9
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: d3d9.dll qemu_d3d9.dll.so

d3d9.dll: buffer_g.o d3d9.def d3d9_main_g.o device_g.o directx_g.o main_g.o query_g.o shader_g.o stateblock_g.o surface_g.o swapchain_g.o texture_g.o vertexdeclaration_g.o
	x86_64-w64-mingw32-ld -shared d3d9.def *_g.o -o d3d9.dll -nostdlib -e DllMain

qemu_d3d9.dll.so: buffer_h.o d3d9_main_h.o device_h.o directx_h.o main_h.o qemu_d3d9.spec query_h.o shader_h.o stateblock_h.o surface_h.o swapchain_h.o texture_h.o vertexdeclaration_h.o
	$(WINEGCC) -shared qemu_d3d9.spec *_h.o -o qemu_d3d9.dll.so -ld3d9 -ldxguid

%_g.o: %.c qemu_d3d9.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_d3d9.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
