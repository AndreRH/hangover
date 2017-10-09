SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_COMDLG32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: comdlg32.dll qemu_comdlg32.dll.so

comdlg32.dll: cdlg32_g.o colordlg_g.o comdlg32.spec filedlg_g.o finddlg_g.o fontdlg_g.o main_g.o printdlg_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/comdlg32.spec *_g.o -o comdlg32.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x50000000

qemu_comdlg32.dll.so: cdlg32_h.o colordlg_h.o filedlg_h.o finddlg_h.o fontdlg_h.o main_h.o printdlg_h.o qemu_comdlg32.spec
	$(WINEGCC) -shared $(SRCDIR)/qemu_comdlg32.spec *_h.o -o qemu_comdlg32.dll.so -lcomdlg32

%_g.o: %.c qemu_comdlg32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_comdlg32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
