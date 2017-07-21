#ifndef COMCTL32_H
#define COMCTL32_H

#include <stdlib.h>

enum oleaut32_calls
{
    CALL_DOSDATETIMETOVARIANTTIME = 0,
    CALL_GETACTIVEOBJECT,
    CALL_GETALTMONTHNAMES,
    CALL_OABUILDVERSION,
    CALL_OLEICONTOCURSOR,
    CALL_OLETRANSLATECOLOR,
    CALL_REGISTERACTIVEOBJECT,
    CALL_REVOKEACTIVEOBJECT,
    CALL_SETOANOCACHE,
    CALL_SYSALLOCSTRING,
    CALL_SYSALLOCSTRINGBYTELEN,
    CALL_SYSALLOCSTRINGLEN,
    CALL_SYSFREESTRING,
    CALL_SYSREALLOCSTRING,
    CALL_SYSREALLOCSTRINGLEN,
    CALL_SYSSTRINGBYTELEN,
    CALL_SYSSTRINGLEN,
    CALL_SYSTEMTIMETOVARIANTTIME,
    CALL_VARABS,
    CALL_VARADD,
    CALL_VARAND,
    CALL_VARCAT,
    CALL_VARCMP,
    CALL_VARDATEFROMUDATE,
    CALL_VARDATEFROMUDATEEX,
    CALL_VARDIV,
    CALL_VAREQV,
    CALL_VARFIX,
    CALL_VARIANTCHANGETYPE,
    CALL_VARIANTCHANGETYPEEX,
    CALL_VARIANTCLEAR,
    CALL_VARIANTCOPY,
    CALL_VARIANTCOPYIND,
    CALL_VARIANTINIT,
    CALL_VARIANTTIMETODOSDATETIME,
    CALL_VARIANTTIMETOSYSTEMTIME,
    CALL_VARIDIV,
    CALL_VARIMP,
    CALL_VARINT,
    CALL_VARMOD,
    CALL_VARMUL,
    CALL_VARNEG,
    CALL_VARNOT,
    CALL_VARNUMFROMPARSENUM,
    CALL_VAROR,
    CALL_VARPARSENUMFROMSTR,
    CALL_VARPOW,
    CALL_VARROUND,
    CALL_VARSUB,
    CALL_VARUDATEFROMDATE,
    CALL_VARXOR,
};

#ifndef QEMU_DLL_GUEST

extern const struct qemu_ops *qemu_ops;

void qemu_DosDateTimeToVariantTime(struct qemu_syscall *c);
void qemu_GetActiveObject(struct qemu_syscall *c);
void qemu_GetAltMonthNames(struct qemu_syscall *c);
void qemu_OaBuildVersion(struct qemu_syscall *c);
void qemu_OleIconToCursor(struct qemu_syscall *c);
void qemu_OleTranslateColor(struct qemu_syscall *c);
void qemu_RegisterActiveObject(struct qemu_syscall *c);
void qemu_RevokeActiveObject(struct qemu_syscall *c);
void qemu_SetOaNoCache(struct qemu_syscall *c);
void qemu_SysAllocString(struct qemu_syscall *c);
void qemu_SysAllocStringByteLen(struct qemu_syscall *c);
void qemu_SysAllocStringLen(struct qemu_syscall *c);
void qemu_SysFreeString(struct qemu_syscall *c);
void qemu_SysReAllocString(struct qemu_syscall *c);
void qemu_SysReAllocStringLen(struct qemu_syscall *c);
void qemu_SysStringByteLen(struct qemu_syscall *c);
void qemu_SysStringLen(struct qemu_syscall *c);
void qemu_SystemTimeToVariantTime(struct qemu_syscall *c);
void qemu_VarAbs(struct qemu_syscall *c);
void qemu_VarAdd(struct qemu_syscall *c);
void qemu_VarAnd(struct qemu_syscall *c);
void qemu_VarCat(struct qemu_syscall *c);
void qemu_VarCmp(struct qemu_syscall *c);
void qemu_VarDateFromUdate(struct qemu_syscall *c);
void qemu_VarDateFromUdateEx(struct qemu_syscall *c);
void qemu_VarDiv(struct qemu_syscall *c);
void qemu_VarEqv(struct qemu_syscall *c);
void qemu_VarFix(struct qemu_syscall *c);
void qemu_VariantChangeType(struct qemu_syscall *c);
void qemu_VariantChangeTypeEx(struct qemu_syscall *c);
void qemu_VariantClear(struct qemu_syscall *c);
void qemu_VariantCopy(struct qemu_syscall *c);
void qemu_VariantCopyInd(struct qemu_syscall *c);
void qemu_VariantInit(struct qemu_syscall *c);
void qemu_VariantTimeToDosDateTime(struct qemu_syscall *c);
void qemu_VariantTimeToSystemTime(struct qemu_syscall *c);
void qemu_VarIdiv(struct qemu_syscall *c);
void qemu_VarImp(struct qemu_syscall *c);
void qemu_VarInt(struct qemu_syscall *c);
void qemu_VarMod(struct qemu_syscall *c);
void qemu_VarMul(struct qemu_syscall *c);
void qemu_VarNeg(struct qemu_syscall *c);
void qemu_VarNot(struct qemu_syscall *c);
void qemu_VarNumFromParseNum(struct qemu_syscall *c);
void qemu_VarOr(struct qemu_syscall *c);
void qemu_VarParseNumFromStr(struct qemu_syscall *c);
void qemu_VarPow(struct qemu_syscall *c);
void qemu_VarRound(struct qemu_syscall *c);
void qemu_VarSub(struct qemu_syscall *c);
void qemu_VarUdateFromDate(struct qemu_syscall *c);
void qemu_VarXor(struct qemu_syscall *c);

#endif

#endif
