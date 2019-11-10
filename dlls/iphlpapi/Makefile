SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_IPHLPAPI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0603 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -DNTDDI_VERSION=0x06020000
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-host/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: iphlpapi.dll qemu_iphlpapi.dll.so

iphlpapi.dll: icmp_g.o iphlpapi.spec iphlpapi_main_g.o ipstats_g.o main_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/iphlpapi.spec *_g.o -lwinecrt0 -o iphlpapi.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x180000000 -lkernel32

qemu_iphlpapi.dll.so: icmp_h.o iphlpapi_main_h.o ipstats_h.o main_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_iphlpapi.spec *_h.o -o qemu_iphlpapi.dll.so -liphlpapi -DUSE_WS_PREFIX

%_g.o: %.c qemu_iphlpapi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_iphlpapi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
