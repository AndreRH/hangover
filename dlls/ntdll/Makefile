DESTDIR?=../..
CURRENT_DLL=DLL_NTDLL
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: ntdll.dll qemu_ntdll.dll.so

ntdll.dll: critsection_g.o file_g.o main_g.o nt_g.o ntdll.def rtl_g.o rtlstr_g.o signal_g.o string_g.o wcstring_g.o
	x86_64-w64-mingw32-ld -shared ntdll.def *_g.o -o ntdll.dll -nostdlib -e DllMain

qemu_ntdll.dll.so: critsection_h.o file_h.o main_h.o nt_h.o qemu_ntdll.spec rtl_h.o rtlstr_h.o signal_h.o string_h.o wcstring_h.o
	$(WINEGCC) -shared qemu_ntdll.spec *_h.o -o qemu_ntdll.dll.so

%_g.o: %.c ntdll.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c ntdll.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
