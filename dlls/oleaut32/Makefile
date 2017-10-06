SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_OLEAUT32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: oleaut32.dll qemu_oleaut32.dll.so

oleaut32.dll: main_g.o oleaut32.def oleaut_g.o variant_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/oleaut32.def *_g.o -o oleaut32.dll -nostdlib -e DllMain

qemu_oleaut32.dll.so: main_h.o oleaut_h.o qemu_oleaut32.spec variant_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_oleaut32.spec *_h.o -o qemu_oleaut32.dll.so -loleaut32

%_g.o: %.c oleaut32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c oleaut32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
