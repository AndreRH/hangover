SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_XINPUT1_3
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -DCONST_VTABLE -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT) -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-tools/tools/winegcc/winegcc --winebuild $(DESTDIR)/build/wine-tools/tools/winebuild/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: xinput1_3.dll qemu_xinput1_3.dll.so

xinput1_3.dll: main_g.o xinput1_3.spec xinput1_3_main_g.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/$(WINE_DIR) -shared -b $(GUEST_CC) $(SRCDIR)/xinput1_3.spec *_g.o -lwinecrt0 -o xinput1_3.dll -nodefaultlibs -nostdlib -Wl,--image-base,0x130000000

qemu_xinput1_3.dll.so: main_h.o xinput1_3_main_h.o
	$(WINEGCC) --wine-objdir $(DESTDIR)/build/wine-host -shared $(HOST_CC) $(SRCDIR)/qemu_xinput1_3.spec *_h.o -o qemu_xinput1_3.dll.so -lxinput

%_g.o: %.c qemu_xinput1_3.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_xinput1_3.h Makefile $(SRCDIR)/Makefile
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
