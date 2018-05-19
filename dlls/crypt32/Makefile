+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_CRYPT32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: crypt32.dll qemu_crypt32.dll.so

crypt32.dll: base64_g.o collectionstore_g.o crypt32.spec main_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/crypt32.spec *_g.o -o crypt32.dll -nodefaultlibs -nostdlib -lwine -lmsvcrt -luuid -ldxguid -lkernel32 -L../../$(WINE_DIR)/libs/wine

qemu_crypt32.dll.so: base64_h.o collectionstore_h.o main_h.o qemu_crypt32.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_crypt32.spec *_h.o -o qemu_crypt32.dll.so -lcrypt32

%_g.o: %.c qemu_crypt32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_crypt32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
