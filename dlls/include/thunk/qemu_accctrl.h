#ifndef HAVE_QEMU_ACCCTRL_H
#define HAVE_QEMU_ACCCTRL_H

struct qemu_TRUSTEE
{
    qemu_ptr                    pMultipleTrustee;
    MULTIPLE_TRUSTEE_OPERATION  MultipleTrusteeOperation;
    TRUSTEE_FORM                TrusteeForm;
    TRUSTEE_TYPE                TrusteeType;
    qemu_ptr                    ptstrName;
};

static inline void TRUSTEE_g2h(TRUSTEE_W *host, const struct qemu_TRUSTEE *guest)
{
    host->pMultipleTrustee = (TRUSTEE_W *)(ULONG_PTR)guest->pMultipleTrustee;
    host->MultipleTrusteeOperation = guest->MultipleTrusteeOperation;
    host->TrusteeForm = guest->TrusteeForm;
    host->TrusteeType = guest->TrusteeType;
    host->ptstrName = (WCHAR *)(ULONG_PTR)guest->ptstrName;
}

static inline void TRUSTEE_h2g(struct qemu_TRUSTEE *guest, const TRUSTEE_W *host)
{
    guest->pMultipleTrustee = (ULONG_PTR)host->pMultipleTrustee;
    guest->MultipleTrusteeOperation = host->MultipleTrusteeOperation;
    guest->TrusteeForm = host->TrusteeForm;
    guest->TrusteeType = host->TrusteeType;
    guest->ptstrName = (ULONG_PTR)host->ptstrName;
}

struct qemu_OBJECTS_AND_SID
{
    DWORD   ObjectsPresent;
    GUID    ObjectTypeGuid;
    GUID    InheritedObjectTypeGuid;
    qemu_ptr pSid;
};

static inline void OBJECTS_AND_SID_g2h(OBJECTS_AND_SID *host, const struct qemu_OBJECTS_AND_SID *guest)
{
    host->ObjectsPresent = guest->ObjectsPresent;
    host->ObjectTypeGuid = guest->ObjectTypeGuid;
    host->InheritedObjectTypeGuid = guest->InheritedObjectTypeGuid;
    host->pSid = (SID *)(ULONG_PTR)guest->pSid;
}

static inline void OBJECTS_AND_SID_h2g(struct qemu_OBJECTS_AND_SID *guest, const OBJECTS_AND_SID *host)
{
    guest->ObjectsPresent = host->ObjectsPresent;
    guest->ObjectTypeGuid = host->ObjectTypeGuid;
    guest->InheritedObjectTypeGuid = host->InheritedObjectTypeGuid;
    guest->pSid = (ULONG_PTR)host->pSid;
}

struct qemu_OBJECTS_AND_NAME
{
    DWORD          ObjectsPresent;
    SE_OBJECT_TYPE ObjectType;
    qemu_ptr       ObjectTypeName;
    qemu_ptr       InheritedObjectTypeName;
    qemu_ptr       ptstrName;
};

static inline void OBJECTS_AND_NAME_g2h(OBJECTS_AND_NAME_W *host, const struct qemu_OBJECTS_AND_NAME *guest)
{
    host->ObjectsPresent = guest->ObjectsPresent;
    host->ObjectType = guest->ObjectType;
    host->ObjectTypeName = (WCHAR *)(ULONG_PTR)guest->ObjectTypeName;
    host->InheritedObjectTypeName = (WCHAR *)(ULONG_PTR)guest->InheritedObjectTypeName;
    host->ptstrName = (WCHAR *)(ULONG_PTR)guest->ptstrName;
}

static inline void OBJECTS_AND_NAME_h2g(struct qemu_OBJECTS_AND_NAME *guest, const OBJECTS_AND_NAME_W *host)
{
    guest->ObjectsPresent = host->ObjectsPresent;
    guest->ObjectType = host->ObjectType;
    guest->ObjectTypeName = (ULONG_PTR)host->ObjectTypeName;
    guest->InheritedObjectTypeName = (ULONG_PTR)host->InheritedObjectTypeName;
    guest->ptstrName = (ULONG_PTR)host->ptstrName;
}

#endif

