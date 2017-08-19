DESTDIR?=../..
CURRENT_DLL=DLL_IPHLPAPI
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: iphlpapi.dll qemu_iphlpapi.dll.so

iphlpapi.dll: icmp_g.o iphlpapi.def iphlpapi_main_g.o ipstats_g.o main_g.o
	x86_64-w64-mingw32-ld -shared iphlpapi.def *_g.o -o iphlpapi.dll -nostdlib -e DllMain

qemu_iphlpapi.dll.so: icmp_h.o iphlpapi_main_h.o ipstats_h.o main_h.o
	$(WINEGCC) -shared qemu_iphlpapi.spec *_h.o -o qemu_iphlpapi.dll.so -liphlpapi -DUSE_WS_PREFIX

%_g.o: %.c iphlpapi.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c iphlpapi.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
