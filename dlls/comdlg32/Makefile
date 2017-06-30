DESTDIR?=../..
CURRENT_DLL=DLL_COMDLG32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: comdlg32.dll qemu_comdlg32.dll.so

comdlg32.dll: comdlg32.def main_g.o filedlg_g.o
	x86_64-w64-mingw32-ld -shared comdlg32.def *_g.o -o comdlg32.dll -nostdlib

qemu_comdlg32.dll.so: main_h.o qemu_comdlg32.spec filedlg_h.o
	$(WINEGCC) -shared qemu_comdlg32.spec *_h.o -o qemu_comdlg32.dll.so -lcomdlg32

%_g.o: %.c comdlg32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c comdlg32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
