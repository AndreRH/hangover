DESTDIR?=../..
CURRENT_DLL=DLL_KERNEL32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL)

all: kernel32.dll qemu_kernel32.dll.so

kernel32.dll: kernel32.def process_g.o main_g.o environ_g.o file_g.o module_g.o sync_g.o thread_g.o time_g.o cpu_g.o virtual_g.o console_g.o version_g.o except_g.o
	x86_64-w64-mingw32-ld -shared kernel32.def *_g.o -o kernel32.dll -nostdlib -lntdll -L../ntdll

qemu_kernel32.dll.so: process_h.o main_h.o environ_h.o file_h.o kernel32.spec module_h.o sync_h.o thread_h.o time_h.o cpu_h.o virtual_h.o console_h.o version_h.o except_h.o
	winegcc -shared kernel32.spec *_h.o -o qemu_kernel32.dll.so

%_g.o: %.c kernel32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c kernel32.h Makefile ../include/dll_list.h
	winegcc $< -c -o $@ $(CFLAGS) -I$(DESTDIR)/build/install/include

clean:
	rm -rf *o *.dll *.so
