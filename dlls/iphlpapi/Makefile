SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_IPHLPAPI
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: iphlpapi.dll qemu_iphlpapi.dll.so

iphlpapi.dll: icmp_g.o iphlpapi.def iphlpapi_main_g.o ipstats_g.o main_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/iphlpapi.def *_g.o -o iphlpapi.dll -nostdlib -e DllMain

qemu_iphlpapi.dll.so: icmp_h.o iphlpapi_main_h.o ipstats_h.o main_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_iphlpapi.spec *_h.o -o qemu_iphlpapi.dll.so -liphlpapi -DUSE_WS_PREFIX

%_g.o: %.c qemu_iphlpapi.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_iphlpapi.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
