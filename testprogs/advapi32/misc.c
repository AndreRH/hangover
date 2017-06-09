/* x86_64-w64-mingw32-gcc helloworld.c -o helloworld.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdio.h>

int WINAPI WinMain2()
{
    char buffer[] = "ThisIsAText";
    wchar_t buffer2[] = L"ThisIsAText";
    BOOL ret;
    HKEY key = NULL;
    LONG lret;

    fprintf(stdout, "Hello!\n");
    ret = IsTextUnicode(buffer, sizeof(buffer), NULL);
    fprintf(stdout, "buffer: retval %u\n", ret);
    ret = IsTextUnicode(buffer2, sizeof(buffer2), NULL);
    fprintf(stdout, "buffer2: retval %u\n", ret);

    lret = RegOpenKeyW(HKEY_CURRENT_USER, L"Environment", &key);
    fprintf(stdout, "RegOpenKeyW %lu, key %p\n", lret, key);

    lret = RegCloseKey(key);
    fprintf(stdout, "RegCloseKey %lu\n", lret);

    ExitProcess(0);
}
