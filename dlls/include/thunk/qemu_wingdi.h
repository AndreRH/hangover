#ifndef HAVE_QEMU_WINGDI_H
#define HAVE_QEMU_WINGDI_H

struct qemu_DOCINFO
{
    INT         cbSize;
    qemu_ptr    lpszDocName;
    qemu_ptr    lpszOutput;
    qemu_ptr    lpszDatatype;
    DWORD       fwType;
};

static inline void DOCINFO_g2h(DOCINFOW *host, const struct qemu_DOCINFO *guest)
{
    host->cbSize = sizeof(*host);
    host->lpszDocName = (const WCHAR *)(ULONG_PTR)guest->lpszDocName;
    host->lpszOutput = (const WCHAR *)(ULONG_PTR)guest->lpszOutput;
    host->lpszDatatype = (const WCHAR *)(ULONG_PTR)guest->lpszDatatype;
    host->fwType = guest->fwType;
}

struct qemu_GCP_RESULTS
{
    DWORD       lStructSize;
    qemu_ptr    lpOutString;
    qemu_ptr    lpOrder;
    qemu_ptr    lpDx;
    qemu_ptr    lpCaretPos;
    qemu_ptr    lpClass;
    qemu_ptr    lpGlyphs;
    UINT        nGlyphs;
    UINT        nMaxFit;
};

static inline void GCP_RESULTS_h2g(struct qemu_GCP_RESULTS *guest, const GCP_RESULTSW *host)
{
    guest->lpOutString = (ULONG_PTR)host->lpOutString;
    guest->lpOrder = (ULONG_PTR)host->lpOrder;
    guest->lpDx = (ULONG_PTR)host->lpDx;
    guest->lpCaretPos = (ULONG_PTR)host->lpCaretPos;
    guest->lpClass = (ULONG_PTR)host->lpClass;
    guest->lpGlyphs = (ULONG_PTR)host->lpGlyphs;
    guest->nGlyphs = host->nGlyphs;
    guest->nMaxFit = host->nMaxFit;
}

static inline void GCP_RESULTS_g2h(GCP_RESULTSW *host, const struct qemu_GCP_RESULTS *guest)
{
    host->lStructSize = sizeof(*host);
    host->lpOutString = (WCHAR *)(ULONG_PTR)guest->lpOutString;
    host->lpOrder = (UINT *)(ULONG_PTR)guest->lpOrder;
    host->lpDx = (INT *)(ULONG_PTR)guest->lpDx;
    host->lpCaretPos = (INT *)(ULONG_PTR)guest->lpCaretPos;
    host->lpClass = (char *)(ULONG_PTR)guest->lpClass;
    host->lpGlyphs = (WCHAR *)(ULONG_PTR)guest->lpGlyphs;
    host->nGlyphs = host->nGlyphs;
    host->nMaxFit = host->nMaxFit;
}

struct qemu_BITMAP
{
    INT         bmType;
    INT         bmWidth;
    INT         bmHeight;
    INT         bmWidthBytes;
    WORD        bmPlanes;
    WORD        bmBitsPixel;
    qemu_ptr    bmBits;
};

static void BITMAP_h2g(struct qemu_BITMAP *guest, const BITMAP *host)
{
    guest->bmType = host->bmType;
    guest->bmWidth = host->bmWidth;
    guest->bmHeight = host->bmHeight;
    guest->bmWidthBytes = host->bmWidthBytes;
    guest->bmPlanes = host->bmPlanes;
    guest->bmBitsPixel = host->bmBitsPixel;
    guest->bmBits = (ULONG_PTR)host->bmBits;
}

static void BITMAP_g2h(BITMAP *host, const struct qemu_BITMAP *guest)
{
    host->bmType = guest->bmType;
    host->bmWidth = guest->bmWidth;
    host->bmHeight = guest->bmHeight;
    host->bmWidthBytes = guest->bmWidthBytes;
    host->bmPlanes = guest->bmPlanes;
    host->bmBitsPixel = guest->bmBitsPixel;
    host->bmBits = (void *)(ULONG_PTR)guest->bmBits;
}

struct qemu_DIBSECTION
{
    struct qemu_BITMAP  dsBm;
    BITMAPINFOHEADER    dsBmih;
    DWORD               dsBitfields[3];
    qemu_ptr            dshSection;
    DWORD               dsOffset;
};

static void DIBSECTION_h2g(struct qemu_DIBSECTION *guest, const DIBSECTION *host)
{
    BITMAP_h2g(&guest->dsBm, &host->dsBm);
    guest->dsBmih = host->dsBmih;
    guest->dsBitfields[0] = host->dsBitfields[0];
    guest->dsBitfields[1] = host->dsBitfields[1];
    guest->dsBitfields[2] = host->dsBitfields[2];
    guest->dshSection = (ULONG_PTR)host->dshSection;
    guest->dsOffset = host->dsOffset;
}

static void DIBSECTION_g2h(DIBSECTION *host, const struct qemu_DIBSECTION *guest)
{
    BITMAP_g2h(&host->dsBm, &guest->dsBm);
    host->dsBmih = guest->dsBmih;
    host->dsBitfields[0] = guest->dsBitfields[0];
    host->dsBitfields[1] = guest->dsBitfields[1];
    host->dsBitfields[2] = guest->dsBitfields[2];
    host->dshSection = (HANDLE)(ULONG_PTR)guest->dshSection;
    host->dsOffset = guest->dsOffset;
}

struct qemu_LOGBRUSH
{
    UINT       lbStyle;
    COLORREF   lbColor;
    qemu_ptr   lbHatch;
};

static void LOGBRUSH_h2g(struct qemu_LOGBRUSH *guest, const LOGBRUSH *host)
{
    guest->lbStyle = host->lbStyle;
    guest->lbColor = host->lbColor;
    guest->lbHatch = (ULONG_PTR)host->lbHatch;
}

static void LOGBRUSH_g2h(LOGBRUSH *host, const struct qemu_LOGBRUSH *guest)
{
    host->lbStyle = guest->lbStyle;
    host->lbColor = guest->lbColor;
    host->lbHatch = (ULONG_PTR)guest->lbHatch;
}

#include <pshpack4.h>

struct qemu_PANOSE
{
    BYTE bFamilyType;
    BYTE bSerifStyle;
    BYTE bWeight;
    BYTE bProportion;
    BYTE bContrast;
    BYTE bStrokeVariation;
    BYTE bArmStyle;
    BYTE bLetterform;
    BYTE bMidline;
    BYTE bXHeight;
};

struct qemu_OUTLINETEXTMETRICA
{
    UINT          otmSize;
    TEXTMETRICA   otmTextMetrics;
    BYTE          otmFiller;
    struct qemu_PANOSE otmPanoseNumber;
    UINT          otmfsSelection;
    UINT          otmfsType;
    INT           otmsCharSlopeRise;
    INT           otmsCharSlopeRun;
    INT           otmItalicAngle;
    UINT          otmEMSquare;
    INT           otmAscent;
    INT           otmDescent;
    UINT          otmLineGap;
    UINT          otmsCapEmHeight;
    UINT          otmsXHeight;
    RECT          otmrcFontBox;
    INT           otmMacAscent;
    INT           otmMacDescent;
    UINT          otmMacLineGap;
    UINT          otmusMinimumPPEM;
    POINT         otmptSubscriptSize;
    POINT         otmptSubscriptOffset;
    POINT         otmptSuperscriptSize;
    POINT         otmptSuperscriptOffset;
    UINT          otmsStrikeoutSize;
    INT           otmsStrikeoutPosition;
    INT           otmsUnderscoreSize;
    INT           otmsUnderscorePosition;
    qemu_ptr      otmpFamilyName;
    qemu_ptr      otmpFaceName;
    qemu_ptr      otmpStyleName;
    qemu_ptr      otmpFullName;
};

struct qemu_OUTLINETEXTMETRICW
{
    UINT          otmSize;
    TEXTMETRICW   otmTextMetrics;
    BYTE            otmFiller;
    struct qemu_PANOSE otmPanoseNumber;
    UINT          otmfsSelection;
    UINT          otmfsType;
    INT           otmsCharSlopeRise;
    INT           otmsCharSlopeRun;
    INT           otmItalicAngle;
    UINT          otmEMSquare;
    INT           otmAscent;
    INT           otmDescent;
    UINT          otmLineGap;
    UINT          otmsCapEmHeight;
    UINT          otmsXHeight;
    RECT          otmrcFontBox;
    INT           otmMacAscent;
    INT           otmMacDescent;
    UINT          otmMacLineGap;
    UINT          otmusMinimumPPEM;
    POINT         otmptSubscriptSize;
    POINT         otmptSubscriptOffset;
    POINT         otmptSuperscriptSize;
    POINT         otmptSuperscriptOffset;
    UINT          otmsStrikeoutSize;
    INT           otmsStrikeoutPosition;
    INT           otmsUnderscoreSize;
    INT           otmsUnderscorePosition;
    qemu_ptr      otmpFamilyName;
    qemu_ptr      otmpFaceName;
    qemu_ptr      otmpStyleName;
    qemu_ptr      otmpFullName;
};

#include <poppack.h>

static void OUTLINETEXTMETRICA_h2g(struct qemu_OUTLINETEXTMETRICA *guest, const OUTLINETEXTMETRICA *host)
{
    guest->otmSize = host->otmSize;
    guest->otmTextMetrics = host->otmTextMetrics;
    guest->otmFiller = host->otmFiller;
    memcpy(&guest->otmPanoseNumber, &host->otmPanoseNumber, sizeof(guest->otmPanoseNumber));
    guest->otmfsSelection = host->otmfsSelection;
    guest->otmfsType = host->otmfsType;
    guest->otmsCharSlopeRise = host->otmsCharSlopeRise;
    guest->otmsCharSlopeRun = host->otmsCharSlopeRun;
    guest->otmItalicAngle = host->otmItalicAngle;
    guest->otmEMSquare = host->otmEMSquare;
    guest->otmEMSquare = host->otmEMSquare;
    guest->otmAscent = host->otmAscent;
    guest->otmDescent = host->otmDescent;
    guest->otmLineGap = host->otmLineGap;
    guest->otmsCapEmHeight = host->otmsCapEmHeight;
    guest->otmsXHeight = host->otmsXHeight;
    guest->otmrcFontBox = host->otmrcFontBox;
    guest->otmMacAscent = host->otmMacAscent;
    guest->otmMacDescent = host->otmMacDescent;
    guest->otmMacLineGap = host->otmMacLineGap;
    guest->otmusMinimumPPEM = host->otmusMinimumPPEM;
    guest->otmptSubscriptSize = host->otmptSubscriptSize;
    guest->otmptSubscriptOffset = host->otmptSubscriptOffset;
    guest->otmptSuperscriptSize = host->otmptSuperscriptSize;
    guest->otmptSuperscriptOffset = host->otmptSuperscriptOffset;
    guest->otmsStrikeoutSize = host->otmsStrikeoutSize;
    guest->otmptSubscriptOffset = host->otmptSubscriptOffset;
    guest->otmsStrikeoutPosition = host->otmsStrikeoutPosition;
    guest->otmsUnderscoreSize = host->otmsUnderscoreSize;
    guest->otmpFamilyName = (ULONG_PTR)host->otmpFamilyName;
    guest->otmpFaceName = (ULONG_PTR)host->otmpFaceName;
    guest->otmpStyleName = (ULONG_PTR)host->otmpStyleName;
    guest->otmpFullName = (ULONG_PTR)host->otmpFullName;
}

static void OUTLINETEXTMETRICA_g2h(OUTLINETEXTMETRICA *host, const struct qemu_OUTLINETEXTMETRICA *guest)
{
    host->otmSize = guest->otmSize;
    host->otmTextMetrics = guest->otmTextMetrics;
    host->otmFiller = guest->otmFiller;
    memcpy(&host->otmPanoseNumber, &guest->otmPanoseNumber, sizeof(guest->otmPanoseNumber));
    host->otmfsSelection = guest->otmfsSelection;
    host->otmfsType = guest->otmfsType;
    host->otmsCharSlopeRise = guest->otmsCharSlopeRise;
    host->otmsCharSlopeRun = guest->otmsCharSlopeRun;
    host->otmItalicAngle = guest->otmItalicAngle;
    host->otmEMSquare = guest->otmEMSquare;
    host->otmEMSquare = guest->otmEMSquare;
    host->otmAscent = guest->otmAscent;
    host->otmDescent = guest->otmDescent;
    host->otmLineGap = guest->otmLineGap;
    host->otmsCapEmHeight = guest->otmsCapEmHeight;
    host->otmsXHeight = guest->otmsXHeight;
    host->otmrcFontBox = guest->otmrcFontBox;
    host->otmMacAscent = guest->otmMacAscent;
    host->otmMacDescent = guest->otmMacDescent;
    host->otmMacLineGap = guest->otmMacLineGap;
    host->otmusMinimumPPEM = guest->otmusMinimumPPEM;
    host->otmptSubscriptSize = guest->otmptSubscriptSize;
    host->otmptSubscriptOffset = guest->otmptSubscriptOffset;
    host->otmptSuperscriptSize = guest->otmptSuperscriptSize;
    host->otmptSuperscriptOffset = guest->otmptSuperscriptOffset;
    host->otmsStrikeoutSize = guest->otmsStrikeoutSize;
    host->otmptSubscriptOffset = guest->otmptSubscriptOffset;
    host->otmsStrikeoutPosition = guest->otmsStrikeoutPosition;
    host->otmsUnderscoreSize = guest->otmsUnderscoreSize;
    host->otmpFamilyName = (char *)(ULONG_PTR)guest->otmpFamilyName;
    host->otmpFaceName = (char *)(ULONG_PTR)guest->otmpFaceName;
    host->otmpStyleName = (char *)(ULONG_PTR)guest->otmpStyleName;
    host->otmpFullName = (char *)(ULONG_PTR)guest->otmpFullName;
}

static void OUTLINETEXTMETRICW_h2g(struct qemu_OUTLINETEXTMETRICW *guest, const OUTLINETEXTMETRICW *host)
{
    guest->otmSize = host->otmSize;
    guest->otmTextMetrics = host->otmTextMetrics;
    guest->otmFiller = host->otmFiller;
    memcpy(&guest->otmPanoseNumber, &host->otmPanoseNumber, sizeof(guest->otmPanoseNumber));
    guest->otmfsSelection = host->otmfsSelection;
    guest->otmfsType = host->otmfsType;
    guest->otmsCharSlopeRise = host->otmsCharSlopeRise;
    guest->otmsCharSlopeRun = host->otmsCharSlopeRun;
    guest->otmItalicAngle = host->otmItalicAngle;
    guest->otmEMSquare = host->otmEMSquare;
    guest->otmEMSquare = host->otmEMSquare;
    guest->otmAscent = host->otmAscent;
    guest->otmDescent = host->otmDescent;
    guest->otmLineGap = host->otmLineGap;
    guest->otmsCapEmHeight = host->otmsCapEmHeight;
    guest->otmsXHeight = host->otmsXHeight;
    guest->otmrcFontBox = host->otmrcFontBox;
    guest->otmMacAscent = host->otmMacAscent;
    guest->otmMacDescent = host->otmMacDescent;
    guest->otmMacLineGap = host->otmMacLineGap;
    guest->otmusMinimumPPEM = host->otmusMinimumPPEM;
    guest->otmptSubscriptSize = host->otmptSubscriptSize;
    guest->otmptSubscriptOffset = host->otmptSubscriptOffset;
    guest->otmptSuperscriptSize = host->otmptSuperscriptSize;
    guest->otmptSuperscriptOffset = host->otmptSuperscriptOffset;
    guest->otmsStrikeoutSize = host->otmsStrikeoutSize;
    guest->otmptSubscriptOffset = host->otmptSubscriptOffset;
    guest->otmsStrikeoutPosition = host->otmsStrikeoutPosition;
    guest->otmsUnderscoreSize = host->otmsUnderscoreSize;
    guest->otmpFamilyName = (ULONG_PTR)host->otmpFamilyName;
    guest->otmpFaceName = (ULONG_PTR)host->otmpFaceName;
    guest->otmpStyleName = (ULONG_PTR)host->otmpStyleName;
    guest->otmpFullName = (ULONG_PTR)host->otmpFullName;
}

static void OUTLINETEXTMETRICW_g2h(OUTLINETEXTMETRICW *host, const struct qemu_OUTLINETEXTMETRICW *guest)
{
    host->otmSize = guest->otmSize;
    host->otmTextMetrics = guest->otmTextMetrics;
    host->otmFiller = guest->otmFiller;
    memcpy(&host->otmPanoseNumber, &guest->otmPanoseNumber, sizeof(guest->otmPanoseNumber));
    host->otmfsSelection = guest->otmfsSelection;
    host->otmfsType = guest->otmfsType;
    host->otmsCharSlopeRise = guest->otmsCharSlopeRise;
    host->otmsCharSlopeRun = guest->otmsCharSlopeRun;
    host->otmItalicAngle = guest->otmItalicAngle;
    host->otmEMSquare = guest->otmEMSquare;
    host->otmEMSquare = guest->otmEMSquare;
    host->otmAscent = guest->otmAscent;
    host->otmDescent = guest->otmDescent;
    host->otmLineGap = guest->otmLineGap;
    host->otmsCapEmHeight = guest->otmsCapEmHeight;
    host->otmsXHeight = guest->otmsXHeight;
    host->otmrcFontBox = guest->otmrcFontBox;
    host->otmMacAscent = guest->otmMacAscent;
    host->otmMacDescent = guest->otmMacDescent;
    host->otmMacLineGap = guest->otmMacLineGap;
    host->otmusMinimumPPEM = guest->otmusMinimumPPEM;
    host->otmptSubscriptSize = guest->otmptSubscriptSize;
    host->otmptSubscriptOffset = guest->otmptSubscriptOffset;
    host->otmptSuperscriptSize = guest->otmptSuperscriptSize;
    host->otmptSuperscriptOffset = guest->otmptSuperscriptOffset;
    host->otmsStrikeoutSize = guest->otmsStrikeoutSize;
    host->otmptSubscriptOffset = guest->otmptSubscriptOffset;
    host->otmsStrikeoutPosition = guest->otmsStrikeoutPosition;
    host->otmsUnderscoreSize = guest->otmsUnderscoreSize;
    host->otmpFamilyName = (char *)(ULONG_PTR)guest->otmpFamilyName;
    host->otmpFaceName = (char *)(ULONG_PTR)guest->otmpFaceName;
    host->otmpStyleName = (char *)(ULONG_PTR)guest->otmpStyleName;
    host->otmpFullName = (char *)(ULONG_PTR)guest->otmpFullName;
}

struct qemu_EXTLOGPEN
{
    DWORD    elpPenStyle;
    DWORD    elpWidth;
    UINT     elpBrushStyle;
    COLORREF elpColor;
    qemu_ptr elpHatch;
    DWORD    elpNumEntries;
    DWORD    elpStyleEntry[1];
};

static void EXTLOGPEN_h2g(struct qemu_EXTLOGPEN *guest, const EXTLOGPEN *host)
{
    guest->elpPenStyle = host->elpPenStyle;
    guest->elpWidth = host->elpWidth;
    guest->elpBrushStyle = host->elpBrushStyle;
    guest->elpColor = host->elpColor;
    guest->elpHatch = host->elpHatch;
    guest->elpNumEntries = host->elpNumEntries;
    memcpy(guest->elpStyleEntry, host->elpStyleEntry, guest->elpNumEntries * sizeof(guest->elpStyleEntry));
}

static void EXTLOGPEN_g2h(EXTLOGPEN *host, const struct qemu_EXTLOGPEN *guest)
{
    host->elpPenStyle = guest->elpPenStyle;
    host->elpWidth = guest->elpWidth;
    host->elpBrushStyle = guest->elpBrushStyle;
    host->elpColor = guest->elpColor;
    host->elpHatch = guest->elpHatch;
    host->elpNumEntries = guest->elpNumEntries;
    memcpy(host->elpStyleEntry, guest->elpStyleEntry, guest->elpNumEntries * sizeof(host->elpStyleEntry));
}

#endif
