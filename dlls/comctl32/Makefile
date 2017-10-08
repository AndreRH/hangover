SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_COMCTL32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: comctl32.dll qemu_comctl32.dll.so

comctl32.dll: comctl32.def comctl32undoc_g.o commctrl_g.o dpa_g.o draglist_g.o dsa_g.o flatsb_g.o imagelist_g.o main_g.o propsheet_g.o smoothscroll_g.o string_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/comctl32.def *_g.o -o comctl32.dll -nostdlib -e DllMain

qemu_comctl32.dll.so: comctl32undoc_h.o commctrl_h.o dpa_h.o draglist_h.o dsa_h.o flatsb_h.o imagelist_h.o main_h.o propsheet_h.o qemu_comctl32.spec smoothscroll_h.o string_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_comctl32.spec *_h.o -o qemu_comctl32.dll.so -lcomctl32 -lshlwapi

%_g.o: %.c qemu_comctl32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_comctl32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
