DESTDIR?=../..
CURRENT_DLL=DLL_KERNEL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2 -D_WIN32_WINNT=0x0603
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: kernel32.dll qemu_kernel32.dll.so

kernel32.dll: comm_g.o console_g.o cpu_g.o debugger_g.o environ_g.o except_g.o file_g.o format_msg_g.o heap_g.o kernel32.def lcformat_g.o locale_g.o main_g.o module_g.o powermgnt_g.o process_g.o special_g.o string_g.o sync_g.o thread_g.o time_g.o version_g.o virtual_g.o
	x86_64-w64-mingw32-ld -shared kernel32.def *_g.o -o kernel32.dll -nostdlib -lntdll -L../ntdll

qemu_kernel32.dll.so: comm_h.o console_h.o cpu_h.o debugger_h.o environ_h.o except_h.o file_h.o format_msg_h.o heap_h.o lcformat_h.o locale_h.o main_h.o module_h.o powermgnt_h.o process_h.o qemu_kernel32.spec special_h.o string_h.o sync_h.o thread_h.o time_h.o version_h.o virtual_h.o
	$(WINEGCC) -shared qemu_kernel32.spec *_h.o -o qemu_kernel32.dll.so

%_g.o: %.c kernel32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c kernel32.h Makefile ../include/dll_list.h
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
