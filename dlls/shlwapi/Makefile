SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_SHLWAPI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -D_WIN32_IE=_WIN32_IE_IE60SP2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: shlwapi.dll qemu_shlwapi.dll.so

shlwapi.dll: assoc_g.o istream_g.o main_g.o path_g.o shlwapi.spec string_g.o url_g.o wsprintf_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/shlwapi.spec *_g.o -o shlwapi.dll -lgcc -nodefaultlibs -nostdlib -Wl,--image-base,0x90000000

qemu_shlwapi.dll.so: assoc_h.o istream_h.o main_h.o path_h.o qemu_shlwapi.spec string_h.o url_h.o wsprintf_h.o
	$(WINEGCC) -shared -b $(HOST_CC) $(SRCDIR)/qemu_shlwapi.spec *_h.o -o qemu_shlwapi.dll.so -lshlwapi

%_g.o: %.c qemu_shlwapi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_shlwapi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) -b $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
