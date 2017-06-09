DESTDIR?=../..
CURRENT_DLL=DLL_COMDLG32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: comdlg32.dll

comdlg32.dll: comdlg32.def
	x86_64-w64-mingw32-ld -shared comdlg32.def -o comdlg32.dll -nostdlib

qemu_comdlg32.dll.so: main_h.o qemu_comdlg32.spec
	winegcc -shared qemu_comdlg32.spec *_h.o -o qemu_comdlg32.dll.so

%_g.o: %.c comdlg32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c comdlg32.h Makefile
	winegcc $< -c -o $@ $(CFLAGS) -I$(DESTDIR)/build/install/include

clean:
	rm -rf *o *.dll *.so
