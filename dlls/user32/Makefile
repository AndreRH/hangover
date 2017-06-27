DESTDIR?=../..
CURRENT_DLL=DLL_USER32
CFLAGS=-I../include -I../../qemu/include -DQEMU_CURRENT_DLL=$(CURRENT_DLL) -O2
WINEGCC=$(DESTDIR)/build/wine-host/tools/winegcc/winegcc -B$(DESTDIR)/build/wine-host/tools/winebuild -I$(DESTDIR)/build/wine-host/include -I$(DESTDIR)/wine/include

all: user32.dll qemu_user32.dll.so

user32.dll: caret_g.o class_g.o clipboard_g.o combo_g.o cursoricon_g.o defdlg_g.o defwnd_g.o desktop_g.o dialog_g.o exticon_g.o focus_g.o hook_g.o lstr_g.o main_g.o user32.def
	x86_64-w64-mingw32-ld -shared user32.def *_g.o -o user32.dll -nostdlib

qemu_user32.dll.so: caret_h.o class_h.o clipboard_h.o combo_h.o cursoricon_h.o defdlg_h.o defwnd_h.o desktop_h.o dialog_h.o exticon_h.o focus_h.o hook_h.o lstr_h.o main_h.o qemu_user32.spec
	$(WINEGCC) -shared qemu_user32.spec *_h.o -o qemu_user32.dll.so -luser32

%_g.o: %.c user32.h Makefile
	x86_64-w64-mingw32-gcc $< -c -o $@ $(CFLAGS) -DQEMU_DLL_GUEST

%_h.o: %.c user32.h Makefile
	$(WINEGCC) $< -c -o $@ $(CFLAGS)

clean:
	rm -rf *o *.dll *.so
