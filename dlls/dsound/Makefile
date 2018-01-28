+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_DSOUND
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: dsound.dll qemu_dsound.dll.so

dsound.dll: buffer_g.o capture_g.o dsound.spec dsound_g.o dsound_main_g.o duplex_g.o main_g.o propset_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/dsound.spec *_g.o -o dsound.dll -nodefaultlibs -nostdlib -lwine -luuid -lmsvcrt -Wl,--image-base,0x1c0000000 -L../../$(WINE_DIR)/libs/wine

qemu_dsound.dll.so: buffer_h.o capture_h.o dsound_h.o dsound_main_h.o duplex_h.o main_h.o propset_h.o qemu_dsound.spec
	$(WINEGCC) -shared $(SRCDIR)/qemu_dsound.spec *_h.o -o qemu_dsound.dll.so -ldsound

%_g.o: %.c qemu_dsound.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_dsound.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
