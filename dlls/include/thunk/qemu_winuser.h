#ifndef HAVE_QEMU_WINUSER_H
#define HAVE_QEMU_WINUSER_H

struct qemu_WNDCLASSEX
{
    UINT        cbSize;
    UINT        style;
    qemu_ptr    lpfnWndProc;
    INT         cbClsExtra;
    INT         cbWndExtra;
    qemu_handle hInstance;
    qemu_handle hIcon;
    qemu_handle hCursor;
    qemu_handle hbrBackground;
    qemu_ptr    lpszMenuName;
    qemu_ptr    lpszClassName;
    qemu_handle hIconSm;
};

struct qemu_CREATESTRUCT
{
    qemu_ptr        lpCreateParams;
    qemu_handle     hInstance;
    qemu_handle     hMenu;
    qemu_handle     hwndParent;
    INT             cy;
    INT             cx;
    INT             y;
    INT             x;
    LONG            style;
    qemu_ptr        lpszName;
    qemu_ptr        lpszClass;
    DWORD           dwExStyle;
};

struct qemu_WINDOWPOS
{
    qemu_handle hwnd;
    qemu_handle hwndInsertAfter;
    INT         x;
    INT         y;
    INT         cx;
    INT         cy;
    UINT        flags;
};

#endif
