SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_OLE32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ole32.dll qemu_ole32.dll.so

ole32.dll: compobj_g.o main_g.o ole32.def
	$(GUEST_CC)-ld -shared $(SRCDIR)/ole32.def *_g.o -o ole32.dll -nostdlib -e DllMain

qemu_ole32.dll.so: compobj_h.o main_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_ole32.spec *_h.o -o qemu_ole32.dll.so -lole32

%_g.o: %.c ole32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ole32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
