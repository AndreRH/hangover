+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_DINPUT
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: dinput.dll qemu_dinput.dll.so

dinput.dll: device_g.o dinput.spec main_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/dinput.spec *_g.o -o dinput.dll -nodefaultlibs -nostdlib -lwine -lmsvcrt -luuid -ldxguid -lkernel32 -L../../$(WINE_DIR)/libs/wine

qemu_dinput.dll.so: device_h.o main_h.o qemu_dinput.spec
	$(WINEGCC) -shared -b $(HOST_CC) $(SRCDIR)/qemu_dinput.spec *_h.o -o qemu_dinput.dll.so

%_g.o: %.c qemu_dinput.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_dinput.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) -b $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
