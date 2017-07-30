#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

static BOOL swapped;

static LRESULT WINAPI my_wndproc(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
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

static LRESULT WINAPI my_wndproc2(HWND win, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (swapped)
    {
        printf("Wrong wndproc called!\n");
        exit(1);
    }
    my_wndproc(win, msg, wparam, lparam);
}

int main(int argc, char *argv[])
{
    WNDCLASSA wc = {0};
    ATOM a;
    MSG msg;
    HWND window, label;
    BOOL ret;
    ULONG_PTR wndproc;
    WNDPROC wndproc2;
    LRESULT lresult;

    wc.lpfnWndProc = my_wndproc2;
    wc.lpszClassName = "my_test_wc";
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(GRAY_BRUSH);
    a = RegisterClassA(&wc);
    printf("Got class atom %x, wndproc %p\n", a, my_wndproc);

    window = CreateWindowA("my_test_wc", "huhu test window!", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, 640, 480, NULL, NULL, NULL, NULL);
    printf("Got Window %p\n", window);

    wndproc = GetClassLongPtrA(window, GCLP_WNDPROC);
    if (wndproc != (ULONG_PTR)my_wndproc2)
        printf("Got class pointer %p, expected %p.\n", (void *)wndproc, my_wndproc2);

    swapped = TRUE;
    wndproc = SetClassLongPtrA(window, GCLP_WNDPROC, (LONG_PTR)my_wndproc);
    if (wndproc != (ULONG_PTR)my_wndproc2)
        printf("Got class pointer %p, expected %p.\n", (void *)wndproc, my_wndproc2);

    wndproc = GetClassLongPtrA(window, GCLP_WNDPROC);
    if (wndproc != (ULONG_PTR)my_wndproc)
        printf("Got class pointer %p, expected %p.\n", (void *)wndproc, my_wndproc);

    label = CreateWindowA("static", "huhu static window!", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, 640, 480, NULL, NULL, NULL, NULL);
    printf("Got Window %p\n", label);

    wndproc = GetClassLongPtrA(label, GCLP_WNDPROC);
    wndproc2 = (WNDPROC)GetClassLongPtrA(label, GCLP_WNDPROC);
    printf("Got static wndproc %p.\n", wndproc2);
    if ((WNDPROC)wndproc != wndproc2)
        printf("Got two different functions.\n");

    /* A simple test call. Should return 1.
     * Yeah, I should use CallWindowProc, but callWindowProc is nasty to implement. */
    lresult = wndproc2(label, WM_ERASEBKGND, 0, 0);
    printf("Called wndproc, got %lx\n", (long unsigned int)lresult);

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
