all: consolehandler.exe critsection.exe helloworld.exe lasterror.exe library.exe process.exe startupinfo.exe time.exe virtual.exe version.exe

%.exe: %.c Makefile
	x86_64-w64-mingw32-gcc $< -o $@ -lkernel32 -nostdlib

clean:
	rm -rf *.exe
