SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_RICHED20
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: riched20.dll qemu_riched20.dll.so

riched20.dll: editor_g.o main_g.o riched20.def txtsrv_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/riched20.def *_g.o -o riched20.dll -nostdlib -e DllMain

qemu_riched20.dll.so: editor_h.o main_h.o txtsrv_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_riched20.spec *_h.o -o qemu_riched20.dll.so -lriched20

%_g.o: %.c qemu_riched20.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_riched20.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
