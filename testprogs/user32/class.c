#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

LRESULT WINAPI my_wndproc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_MOUSEMOVE:
            printf("WM_MOUSEMOVE %dx%d\n", GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
            /* Drop through */
        default:
            return DefWindowProc(win, msg, wparam, lparam);
    }
}

int main(int argc, char *argv[])
{
    WNDCLASSA wc = {0};
    ATOM a;
    MSG msg;
    HWND window;
    BOOL ret;
    ULONG_PTR wndproc;

    wc.lpfnWndProc = my_wndproc;
    wc.lpszClassName = "my_test_wc";
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(GRAY_BRUSH);
    a = RegisterClassA(&wc);
    printf("Got class atom %x, wndproc %p\n", a, my_wndproc);

    window = CreateWindowA("my_test_wc", "huhu test window!", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, 640, 480, NULL, NULL, NULL, NULL);
    printf("Got Window %p\n", window);

    wndproc = GetClassLongPtrA(window, GCLP_WNDPROC);
    if (wndproc != (ULONG_PTR)my_wndproc)
        printf("Got class pointer %p, expected %p.\n", (void *)wndproc, my_wndproc);
    else
        printf("Class pointer matches.\n");

    while (ret = GetMessageA(&msg, NULL, 0, 0))
    {
        if (ret == -1)
        {
            printf("GetMessageA error\n");
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    DestroyWindow(window);

    ret = UnregisterClassA((char *)(DWORD_PTR)a, NULL);
    printf("Orderly exit %u\n", ret);

    return 0;
}
