DESTDIR?=../..
CURRENT_DLL=DLL_WINMM
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: winmm.dll qemu_winmm.dll.so

winmm.dll: driver_g.o joystick_g.o main_g.o mci_g.o mmio_g.o playsound_g.o time_g.o waveform_g.o winmm.def winmm_g.o
	x86_64-w64-mingw32-ld -shared winmm.def *_g.o -o winmm.dll -nostdlib -e DllMain

qemu_winmm.dll.so: driver_h.o joystick_h.o main_h.o mci_h.o mmio_h.o playsound_h.o time_h.o waveform_h.o winmm_h.o
	$(WINEGCC) -shared qemu_winmm.spec *_h.o -o qemu_winmm.dll.so -lwinmm

%_g.o: %.c winmm.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c winmm.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
