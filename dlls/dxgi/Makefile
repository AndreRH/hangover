+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_DXGI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-tools/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-tools/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: dxgi.dll qemu_dxgi.dll.so

dxgi.dll: adapter_g.o device_g.o dxgi.spec factory_g.o main_g.o output_g.o surface_g.o swapchain_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/dxgi.spec *_g.o -o dxgi.dll -ldxguid -luuid

qemu_dxgi.dll.so: adapter_h.o device_h.o factory_h.o main_h.o output_h.o qemu_dxgi.spec surface_h.o swapchain_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_dxgi.spec *_h.o -o qemu_dxgi.dll.so -ldxgi -ldxguid

%_g.o: %.c qemu_dxgi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../wine-guest32/include -I../../../wine/include -Wno-format

%_h.o: %.c qemu_dxgi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
