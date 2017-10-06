SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_XINPUT1_3
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: xinput1_3.dll qemu_xinput1_3.dll.so

xinput1_3.dll: main_g.o xinput1_3.def xinput1_3_main_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/xinput1_3.def *_g.o -o xinput1_3.dll -nostdlib -e DllMain

qemu_xinput1_3.dll.so: main_h.o xinput1_3_main_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_xinput1_3.spec *_h.o -o qemu_xinput1_3.dll.so -lxinput

%_g.o: %.c xinput1_3.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c xinput1_3.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
