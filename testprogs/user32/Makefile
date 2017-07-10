all: class.exe

%.o: %.c Makefile
	x86_64-w64-mingw32-gcc -c $< -o $@

%.exe: %.o Makefile
	x86_64-w64-mingw32-gcc $< -o $@ -Wl,-eWinMainCRTStartup -lgdi32

clean:
	rm -rf *.exe *.o
