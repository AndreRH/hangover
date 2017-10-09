SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_IMM32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: imm32.dll qemu_imm32.dll.so

imm32.dll: imm32.def imm_g.o main_g.o
	$(GUEST_CC)-ld -shared $(SRCDIR)/imm32.def *_g.o -o imm32.dll -nostdlib -e DllMain

qemu_imm32.dll.so: imm_h.o main_h.o
	$(WINEGCC) -shared $(SRCDIR)/qemu_imm32.spec *_h.o -o qemu_imm32.dll.so -limm32

%_g.o: %.c qemu_imm32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_imm32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
