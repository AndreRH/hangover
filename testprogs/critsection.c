/* x86_64-w64-mingw32-gcc critsection.c -o critsection.exe -nostdlib -lkernel32 */

#include <windows.h>
#include <stdint.h>

static void ptr_to_char(char *c, const void *ptr);

static CRITICAL_SECTION cs;

void __stdcall WinMainCRTStartup()
{
    /* Testing critical sections without multithreading support is
     * largely pointless. */
    InitializeCriticalSection(&cs);
    EnterCriticalSection(&cs);
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);

    ExitProcess(0);
}
