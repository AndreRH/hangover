DESTDIR?=../..
CURRENT_DLL=DLL_SECUR32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -D_WIN32_WINNT=0x0600 -DSECURITY_WIN32
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: secur32.dll qemu_secur32.dll.so

secur32.dll: lsa_g.o main_g.o secur32.def secur32_g.o wrapper_g.o
	x86_64-w64-mingw32-ld -shared secur32.def *_g.o -o secur32.dll -nostdlib -e DllMain

qemu_secur32.dll.so: lsa_h.o main_h.o secur32_h.o wrapper_h.o
	$(WINEGCC) -shared qemu_secur32.spec *_h.o -o qemu_secur32.dll.so -lsecur32 -DUSE_WS_PREFIX

%_g.o: %.c secur32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c secur32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS) -DUSE_WS_PREFIX

clean:
	rm -rf *o *.dll *.so
