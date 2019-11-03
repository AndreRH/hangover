SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WS2_32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0603 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-host/tools/winebuild/winebuild --wine-objdir $(DESTDIR)/build/wine-host -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: ws2_32.dll qemu_ws2_32.dll.so

ws2_32.dll: async_g.o main_g.o socket_g.o ws2_32.spec
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/ws2_32.spec *_g.o -L../../$(WINE_DIR)/dlls/winecrt0 -lwinecrt0 -o ws2_32.dll -nodefaultlibs -nostdlib -lkernel32 -Wl,--image-base,0x170000000

qemu_ws2_32.dll.so: async_h.o main_h.o socket_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_ws2_32.spec *_h.o -o qemu_ws2_32.dll.so -lws2_32 -lpthread

%_g.o: %.c qemu_ws2_32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_ws2_32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
