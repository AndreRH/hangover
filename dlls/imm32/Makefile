DESTDIR?=../..
CURRENT_DLL=DLL_IMM32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: imm32.dll qemu_imm32.dll.so

imm32.dll: imm32.def main_g.o
	x86_64-w64-mingw32-ld -shared imm32.def *_g.o -o imm32.dll -nostdlib -e DllMain

qemu_imm32.dll.so: main_h.o
	$(WINEGCC) -shared qemu_imm32.spec *_h.o -o qemu_imm32.dll.so -limm32

%_g.o: %.c imm32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c imm32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
