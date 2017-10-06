SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WS2_32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ws2_32.dll qemu_ws2_32.dll.so

ws2_32.dll: async_g.o main_g.o socket_g.o ws2_32.def
	$(GUEST_CC)-ld -shared $(SRCDIR)/ws2_32.def *_g.o -o ws2_32.dll -nostdlib -e DllMain

qemu_ws2_32.dll.so: async_h.o main_h.o socket_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_ws2_32.spec *_h.o -o qemu_ws2_32.dll.so -lws2_32

%_g.o: %.c ws2_32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ws2_32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
