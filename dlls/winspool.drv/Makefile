+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WINSPOOL
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: winspool.drv qemu_winspool.drv.so

winspool.drv: winspool.drv.spec main_g.o info_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/winspool.drv.spec *_g.o -o winspool.drv -nodefaultlibs -nostdlib

qemu_winspool.drv.so: main_h.o info_h.o qemu_winspool.drv.spec
	$(WINEGCC) -shared $(SRCDIR)/qemu_winspool.drv.spec *_h.o -o qemu_winspool.drv.so -lwinspool

%_g.o: %.c qemu_winspool.drv.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine

%_h.o: %.c qemu_winspool.drv.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
