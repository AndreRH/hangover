+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WINDOWSCODECS
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DCONST_VTABLE -D_WIN32_WINNT=0x0602
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: windowscodecs.dll qemu_windowscodecs.dll.so

windowscodecs.dll: encode_g.o imgfactory_g.o info_g.o main_g.o metadataquery_g.o proxy_g.o windowscodecs.spec
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/windowscodecs.spec *_g.o -o windowscodecs.dll -nodefaultlibs -nostdlib -lkernel32 -lwine -lmsvcrt -luuid -lole32 -loleaut32 -L../../$(WINE_DIR)/libs/wine

qemu_windowscodecs.dll.so: encode_h.o imgfactory_h.o info_h.o main_h.o metadataquery_h.o proxy_h.o qemu_windowscodecs.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_windowscodecs.spec *_h.o -o qemu_windowscodecs.dll.so -lwindowscodecs

%_g.o: %.c qemu_windowscodecs.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_windowscodecs.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
