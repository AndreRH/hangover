+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_MMDEVAPI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DCONST_VTABLE -D_WIN32_WINNT=0x0602
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: mmdevapi.dll qemu_mmdevapi.dll.so

mmdevapi.dll: audiovolume_g.o devenum_g.o driver_g.o main_g.o mmdevapi.spec
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/mmdevapi.spec *_g.o -o mmdevapi.dll -lole32 -loleaut32 -L../../$(WINE_DIR)/dlls/winecrt0

qemu_mmdevapi.dll.so: audiovolume_h.o devenum_h.o driver_h.o main_h.o qemu_mmdevapi.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_mmdevapi.spec *_h.o -o qemu_mmdevapi.dll.so -lole32

%_g.o: %.c qemu_mmdevapi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_mmdevapi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
