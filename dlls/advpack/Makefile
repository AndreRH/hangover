+SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_ADVPACK
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: advpack.dll qemu_advpack.dll.so

advpack.dll: advpack.def advpack_g.o files_g.o install_g.o main_g.o reg_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/advpack.def *_g.o -o advpack.dll -nostdlib -e DllMain

qemu_advpack.dll.so: advpack_h.o files_h.o install_h.o main_h.o reg_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_advpack.spec *_h.o -o qemu_advpack.dll.so -ladvpack

%_g.o: %.c advpack.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c advpack.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
