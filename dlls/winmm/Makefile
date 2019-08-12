SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_WINMM
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: winmm.dll qemu_winmm.dll.so

winmm.dll: driver_g.o joystick_g.o main_g.o mci_g.o mmio_g.o playsound_g.o time_g.o waveform_g.o winmm.spec winmm_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/winmm.spec *_g.o -L../../$(WINE_DIR)/dlls/winecrt0 -lwinecrt0 -o winmm.dll -nodefaultlibs -nostdlib -lkernel32

qemu_winmm.dll.so: driver_h.o joystick_h.o main_h.o mci_h.o mmio_h.o playsound_h.o time_h.o waveform_h.o winmm_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_winmm.spec *_h.o -o qemu_winmm.dll.so -lwinmm -luser32

%_g.o: %.c qemu_winmm.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_winmm.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
