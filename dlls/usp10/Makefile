SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_USP10
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: usp10.dll qemu_usp10.dll.so

usp10.dll: main_g.o usp10.spec usp10_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/usp10.spec *_g.o -o usp10.dll -nodefaultlibs -nostdlib -Wl,--image-base,0xf0000000

qemu_usp10.dll.so: main_h.o usp10_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_usp10.spec *_h.o -o qemu_usp10.dll.so -lusp10

%_g.o: %.c qemu_usp10.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_usp10.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
