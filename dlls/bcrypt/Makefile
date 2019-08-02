+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_BCRYPT
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: bcrypt.dll qemu_bcrypt.dll.so

bcrypt.dll: bcrypt.spec main_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/bcrypt.spec *_g.o -o bcrypt.dll -L../../$(WINE_DIR)/dlls/winecrt0

qemu_bcrypt.dll.so: main_h.o qemu_bcrypt.spec
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_bcrypt.spec *_h.o -o qemu_bcrypt.dll.so -lbcrypt

%_g.o: %.c qemu_bcrypt.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST -I../../../wine/include/wine -Wno-format

%_h.o: %.c qemu_bcrypt.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
