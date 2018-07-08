+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_MMDEVAPI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: mmdevapi.dll qemu_mmdevapi.dll.so

mmdevapi.dll: main_g.o mmdevapi.spec
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/mmdevapi.spec *_g.o -o mmdevapi.dll -nodefaultlibs -nostdlib -lwine -lmsvcrt -L../../$(WINE_DIR)/libs/wine

qemu_mmdevapi.dll.so: main_h.o qemu_mmdevapi.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_mmdevapi.spec *_h.o -o qemu_mmdevapi.dll.so

%_g.o: %.c qemu_mmdevapi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_mmdevapi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
