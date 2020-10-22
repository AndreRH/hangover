SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_D3D9
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-tools/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-tools/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: d3d9.dll qemu_d3d9.dll.so

d3d9.dll: buffer_g.o d3d9.spec d3d9_main_g.o device_g.o directx_g.o main_g.o query_g.o shader_g.o stateblock_g.o surface_g.o swapchain_g.o texture_g.o vertexdeclaration_g.o volume_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/d3d9.spec *_g.o -o d3d9.dll -Wl,--image-base,0xc0000000

qemu_d3d9.dll.so: buffer_h.o d3d9_main_h.o device_h.o directx_h.o main_h.o qemu_d3d9.spec query_h.o shader_h.o stateblock_h.o surface_h.o swapchain_h.o texture_h.o vertexdeclaration_h.o volume_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_d3d9.spec *_h.o -o qemu_d3d9.dll.so -ld3d9 -ldxguid -luuid

%_g.o: %.c qemu_d3d9.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_d3d9.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
