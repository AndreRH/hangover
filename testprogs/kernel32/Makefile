all: consolehandler.exe critsection.exe helloworld.exe lasterror.exe library.exe process.exe startupinfo.exe time.exe virtual.exe version.exe fileops.exe format_msg.exe misc.exe except.exe

format_msg.exe: format_msg.o format_msg.res Makefile
	x86_64-w64-mingw32-gcc format_msg.o format_msg.res -o $@ -Wl,-eWinMainCRTStartup

except.exe: except.o Makefile
	x86_64-w64-mingw32-gcc except.o -o $@ -Wl,-eWinMainCRTStartup

misc.exe: misc.o Makefile
	x86_64-w64-mingw32-gcc misc.o -o $@ -Wl,-eWinMainCRTStartup

format_msg.res: format_msg.rc Makefile
	x86_64-w64-mingw32-windres $< -O coff -o $@

format_msg.rc: format_msg.mc Makefile
	../../build/wine-host/tools/wmc/wmc -U -O rc -o format_msg.rc format_msg.mc

%.exe: %.c Makefile
	x86_64-w64-mingw32-gcc $< -o $@ -lkernel32 -nostdlib

format_msg.o: format_msg.c format_msg.rc Makefile
	x86_64-w64-mingw32-gcc $< -c

%.o: %.c Makefile
	x86_64-w64-mingw32-gcc $< -c

clean:
	rm -rf *.exe *.o format_msg.rc *.bin format_msg.h format_msg.res
