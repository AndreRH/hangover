#ifndef QEMU_DDRAW_H
#define QEMU_DDRAW_H

enum ddraw_calls
{
    CALL_DDRAW_CLIPPER_GETCLIPLIST = 0,
    CALL_DDRAW_CLIPPER_GETHWND,
    CALL_DDRAW_CLIPPER_INITIALIZE,
    CALL_DDRAW_CLIPPER_ISCLIPLISTCHANGED,
    CALL_DDRAW_CLIPPER_RELEASE,
    CALL_DDRAW_CLIPPER_SETCLIPLIST,
    CALL_DDRAW_CLIPPER_SETHWND,
    CALL_DIRECTDRAWCREATE,
    CALL_DIRECTDRAWCREATEEX,
    CALL_DIRECTDRAWENUMERATEA,
    CALL_DIRECTDRAWENUMERATEEXA,
    CALL_DIRECTDRAWENUMERATEEXW,
    CALL_DIRECTDRAWENUMERATEW,
    CALL_GETSURFACEFROMDC,
};

struct qemu_clipper
{
    /* Guest fields */
    IDirectDrawClipper IDirectDrawClipper_iface;
    ULONG ref;

    /* Host fields */
    IDirectDrawClipper *host;
};

#ifdef QEMU_DLL_GUEST

HRESULT ddraw_clipper_guest_init(struct qemu_clipper *clipper);
struct qemu_clipper *unsafe_impl_from_IDirectDrawClipper(IDirectDrawClipper *iface);

#else

void qemu_ddraw_clipper_Release(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetHWnd(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_SetClipList(struct qemu_syscall *call);
void qemu_ddraw_clipper_GetHWnd(struct qemu_syscall *call);
void qemu_ddraw_clipper_Initialize(struct qemu_syscall *call);
void qemu_ddraw_clipper_IsClipListChanged(struct qemu_syscall *call);

extern const struct qemu_ops *qemu_ops;

#endif

#endif
