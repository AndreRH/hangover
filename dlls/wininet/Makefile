SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WININET
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: wininet.dll qemu_wininet.dll.so

wininet.dll: cookie_g.o dialogs_g.o ftp_g.o gopher_g.o http_g.o internet_g.o main_g.o urlcache_g.o wininet.def
	$(GUEST_CC)-ld -shared $(SRCDIR)/wininet.def *_g.o -o wininet.dll -nostdlib -e DllMain

qemu_wininet.dll.so: cookie_h.o dialogs_h.o ftp_h.o gopher_h.o http_h.o internet_h.o main_h.o urlcache_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_wininet.spec *_h.o -o qemu_wininet.dll.so -lwininet

%_g.o: %.c wininet.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c wininet.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
