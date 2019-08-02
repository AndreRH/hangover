SRCDIR?=build_from_build_dllsXX_YYY
DESTDIR?=../..
CURRENT_DLL=DLL_KERNEL32
CFLAGS+=-I$(SRCDIR)/../include -I$(SRCDIR)/../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -D_WIN32_WINNT=0x0603 -DGUEST_BIT=$(GUEST_BIT) -DHOST_BIT=$(HOST_BIT)
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

VPATH=$(SRCDIR)

all: kernel32.dll qemu_kernel32.dll.so

kernel32.dll: actctx_g.o atom_g.o change_g.o comm_g.o computername_g.o console_g.o cpu_g.o debugger_g.o environ_g.o except_g.o fiber_g.o file_g.o format_msg_g.o heap_g.o kernel32.spec lcformat_g.o locale_g.o lzexpand_g.o main_g.o module_g.o path_g.o powermgnt_g.o process_g.o profile_g.o resource_g.o special_g.o string_g.o sync_g.o tape_g.o thread_g.o time_g.o toolhelp_g.o version_g.o virtual_g.o volume_g.o wer_g.o my_winternl.h
	$(WINEGCC) -shared --sysroot=../.. -b $(GUEST_CC) $(SRCDIR)/kernel32.spec ../../$(WINE_DIR)/dlls/winecrt0/libwinecrt0.a *_g.o -o kernel32.dll -L../ntdll -lntdll -lkernel32 -lgcc -nodefaultlibs -nostdlib -Wl,--image-base,0x20000000

qemu_kernel32.dll.so: actctx_h.o atom_h.o change_h.o comm_h.o computername_h.o console_h.o cpu_h.o debugger_h.o environ_h.o except_h.o fiber_h.o file_h.o format_msg_h.o heap_h.o lcformat_h.o locale_h.o lzexpand_h.o main_h.o module_h.o path_h.o powermgnt_h.o process_h.o profile_h.o qemu_kernel32.spec resource_h.o special_h.o string_h.o sync_h.o tape_h.o thread_h.o time_h.o toolhelp_h.o version_h.o virtual_h.o volume_h.o wer_h.o
	$(WINEGCC) -shared $(HOST_CC) $(SRCDIR)/qemu_kernel32.spec *_h.o -o qemu_kernel32.dll.so

%_g.o: %.c qemu_kernel32.h Makefile $(SRCDIR)/Makefile
	$(GUEST_CC)-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c qemu_kernel32.h Makefile $(SRCDIR)/Makefile ../include/dll_list.h
	$(WINEGCC) $(HOST_CC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
