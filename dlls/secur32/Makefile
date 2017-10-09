SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_SECUR32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: secur32.dll qemu_secur32.dll.so

secur32.dll: lsa_g.o main_g.o secur32.spec secur32_g.o wrapper_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/secur32.spec *_g.o -o secur32.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x190000000

qemu_secur32.dll.so: lsa_h.o main_h.o secur32_h.o wrapper_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_secur32.spec *_h.o -o qemu_secur32.dll.so -lsecur32 -DUSE_WS_PREFIX

%_g.o: %.c qemu_secur32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_secur32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
