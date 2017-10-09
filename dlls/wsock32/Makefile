SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WSOCK32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: wsock32.dll qemu_wsock32.dll.so

wsock32.dll: main_g.o protocol_g.o service_g.o socket_g.o wsock32.def
	$(GUEST_CC)-ld -shared $(SRCDIR)/wsock32.def *_g.o -o wsock32.dll -nostdlib -e DllMain

qemu_wsock32.dll.so: main_h.o protocol_h.o service_h.o socket_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_wsock32.spec *_h.o -o qemu_wsock32.dll.so -lwsock32

%_g.o: %.c qemu_wsock32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_wsock32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
