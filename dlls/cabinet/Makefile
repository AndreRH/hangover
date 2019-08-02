+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_CABINET
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: cabinet.dll qemu_cabinet.dll.so

cabinet.dll: cabinet.spec fci_g.o fdi_g.o main_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/cabinet.spec *_g.o -o cabinet.dll -L../../$(WINE_DIR)/dlls/winecrt0

qemu_cabinet.dll.so: fci_h.o fdi_h.o main_h.o qemu_cabinet.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_cabinet.spec *_h.o -o qemu_cabinet.dll.so -lcabinet

%_g.o: %.c qemu_cabinet.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_cabinet.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
