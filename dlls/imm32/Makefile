SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_IMM32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-host/tools/winebuild/winebuild --wine-objdir $(DESTDIR)/build/wine-host -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: imm32.dll qemu_imm32.dll.so

imm32.dll: imm32.spec imm_g.o main_g.o
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/imm32.spec *_g.o -L../../$(WINE_DIR)/dlls/winecrt0 -lwinecrt0 -o imm32.dll -nodefaultlibs -nostdlib -lkernel32 -Wl,--image-base,0xe0000000

qemu_imm32.dll.so: imm_h.o main_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_imm32.spec *_h.o -o qemu_imm32.dll.so -limm32

%_g.o: %.c qemu_imm32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_imm32.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
