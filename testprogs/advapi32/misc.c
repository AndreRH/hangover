/* x86_64-w64-mingw32-gcc helloworld.c -o helloworld.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char buffer[] = "ThisIsAText";
    wchar_t buffer2[] = L"ThisIsAText";
    BOOL ret;
    HKEY key = NULL, key2 = NULL;
    LONG lret;
    wchar_t wstr[32];
    DWORD size = sizeof(wstr);
    DWORD disp;

    printf("Hello!\n");
    ret = IsTextUnicode(buffer, sizeof(buffer), NULL);
    printf("buffer: retval %u\n", ret);
    ret = IsTextUnicode(buffer2, sizeof(buffer2), NULL);
    printf("buffer2: retval %u\n", ret);

    lret = RegOpenKeyW(HKEY_CURRENT_USER, L"Environment", &key);
    printf("RegOpenKeyW %lu, key %p\n", lret, key);

    lret = RegQueryValueExW(key, L"TEMP", NULL, NULL, (BYTE *)wstr, &size);
    printf("RegQueryValueExW %lu, temp=%ls\n", lret, wstr);

    /* This doesn't seem to create the key. Never mind. */
    lret = RegCreateKeyExW(key, L"garbage", 0, NULL, REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS, NULL, &key2, &disp);
    printf("RegCreateKeyExW %lu, key=%p\n", lret, key2);

    lret = RegSetValueExW(key, L"testtest", 0, REG_SZ, (BYTE *)buffer2, sizeof(buffer2));
    printf("RegSetValueExW %lu\n", lret);

    lret = RegCloseKey(key);
    printf("RegCloseKey %lu\n", lret);

    ExitProcess(0);
}
