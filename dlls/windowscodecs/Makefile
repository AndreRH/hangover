+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WINDOWSCODECS
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DCONST_VTABLE -D_WIN32_WINNT=0x0602
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: windowscodecs.dll qemu_windowscodecs.dll.so

windowscodecs.dll: bitmap_g.o clipper_g.o clsfactory_g.o colorcontext_g.o converter_g.o decode_g.o dlldata.o encode_g.o imgfactory_g.o info_g.o main_g.o metadataquery_g.o palette_g.o propertybag_g.o proxy_g.o stream_g.o windowscodecs.spec windowscodecs_wincodec_p.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/windowscodecs.spec *_g.o dlldata.o windowscodecs_wincodec_p.o -o windowscodecs.dll -lwine -luuid -lole32 -loleaut32 -lrpcrt4 -L../../$(WINE_DIR)/libs/wine -L../../$(WINE_DIR)/dlls/winecrt0

qemu_windowscodecs.dll.so: bitmap_h.o clipper_h.o clsfactory_h.o colorcontext_h.o converter_h.o decode_h.o encode_h.o imgfactory_h.o info_h.o main_h.o metadataquery_h.o palette_h.o propertybag_h.o proxy_h.o qemu_windowscodecs.spec stream_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_windowscodecs.spec *_h.o -o qemu_windowscodecs.dll.so -lwindowscodecs

%_g.o: %.c qemu_windowscodecs.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../wine-guest32/include -I../../../wine/include -Wno-format

%_h.o: %.c qemu_windowscodecs.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

dlldata.o: dlldata.c Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -DENTRY_PREFIX=WIC_ -DPROXY_DELEGATION -I../../wine-guest32/include -I../../../wine/include -Wno-format

dlldata.c: windowscodecs_wincodec.idl Makefile $(SRCDIR)/Makefile
	$(DESTDIR)/build/wine-host/tools/widl/widl --dlldata-only -o dlldata.c windowscodecs_wincodec.idl

windowscodecs_wincodec_p.o: windowscodecs_wincodec_p.c windowscodecs_wincodec.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../wine-guest32/include -I../../../wine/include -Wno-format

windowscodecs_wincodec.h: windowscodecs_wincodec.idl Makefile $(SRCDIR)/Makefile
	$(DESTDIR)/build/wine-host/tools/widl/widl -o windowscodecs_wincodec.h -b $(GUEST_CC) -I../../wine-guest32/include -I../../../wine/include ../../../dlls/windowscodecs/windowscodecs_wincodec.idl

windowscodecs_wincodec_p.c: windowscodecs_wincodec.idl Makefile $(SRCDIR)/Makefile
	$(DESTDIR)/build/wine-host/tools/widl/widl -o windowscodecs_wincodec_p.c -b $(GUEST_CC) -I../../wine-guest32/include -I../../../wine/include ../../../dlls/windowscodecs/windowscodecs_wincodec.idl

clean:
	rm -rf *o *.dll *.so dlldata.c windowscodecs_wincodec.h windowscodecs_wincodec_p.c
