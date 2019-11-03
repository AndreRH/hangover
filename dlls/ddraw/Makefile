+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_DDRAW
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-host/tools/winebuild/winebuild --wine-objdir $(DESTDIR)/build/wine-host -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ddraw.dll qemu_ddraw.dll.so

ddraw.dll: clipper_g.o ddraw.spec ddraw_g.o device_g.o executebuffer_g.o light_g.o main_g.o material_g.o palette_g.o surface_g.o vertexbuffer_g.o viewport_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/ddraw.spec *_g.o -o ddraw.dll -luuid -ldxguid -L../../$(WINE_DIR)/dlls/winecrt0 -L../../wine-guest/dlls/dxguid -L../../wine-guest/dlls/uuid

qemu_ddraw.dll.so: clipper_h.o ddraw_h.o device_h.o executebuffer_h.o light_h.o main_h.o material_h.o palette_h.o qemu_ddraw.spec surface_h.o vertexbuffer_h.o viewport_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_ddraw.spec *_h.o -o qemu_ddraw.dll.so -lddraw -luuid -ldxguid

%_g.o: %.c qemu_ddraw.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_ddraw.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
