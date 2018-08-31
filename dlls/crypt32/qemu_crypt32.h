/*
 * Copyright 2017 André Hentschel
 * Copyright 2018 Stefan Dösinger for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef QEMU_CRYPT32_H
#define QEMU_CRYPT32_H

enum crypt32_calls
{
    CALL_CERTADDCERTIFICATECONTEXTTOSTORE = 0,
    CALL_CERTADDCERTIFICATELINKTOSTORE,
    CALL_CERTADDCRLCONTEXTTOSTORE,
    CALL_CERTADDCTLCONTEXTTOSTORE,
    CALL_CERTADDENCODEDCERTIFICATETOSTORE,
    CALL_CERTADDENCODEDCERTIFICATETOSYSTEMSTOREA,
    CALL_CERTADDENCODEDCERTIFICATETOSYSTEMSTOREW,
    CALL_CERTADDENCODEDCRLTOSTORE,
    CALL_CERTADDENCODEDCTLTOSTORE,
    CALL_CERTADDENHANCEDKEYUSAGEIDENTIFIER,
    CALL_CERTADDSERIALIZEDELEMENTTOSTORE,
    CALL_CERTADDSTORETOCOLLECTION,
    CALL_CERTALGIDTOOID,
    CALL_CERTCLOSESTORE,
    CALL_CERTCOMPARECERTIFICATE,
    CALL_CERTCOMPARECERTIFICATENAME,
    CALL_CERTCOMPAREINTEGERBLOB,
    CALL_CERTCOMPAREPUBLICKEYINFO,
    CALL_CERTCONTROLSTORE,
    CALL_CERTCREATECERTIFICATECHAINENGINE,
    CALL_CERTCREATECERTIFICATECONTEXT,
    CALL_CERTCREATECONTEXT,
    CALL_CERTCREATECRLCONTEXT,
    CALL_CERTCREATECTLCONTEXT,
    CALL_CERTCREATESELFSIGNCERTIFICATE,
    CALL_CERTDELETECERTIFICATEFROMSTORE,
    CALL_CERTDELETECRLFROMSTORE,
    CALL_CERTDELETECTLFROMSTORE,
    CALL_CERTDUPLICATECERTIFICATECHAIN,
    CALL_CERTDUPLICATECERTIFICATECONTEXT,
    CALL_CERTDUPLICATECRLCONTEXT,
    CALL_CERTDUPLICATECTLCONTEXT,
    CALL_CERTDUPLICATESTORE,
    CALL_CERTENUMCERTIFICATECONTEXTPROPERTIES,
    CALL_CERTENUMCERTIFICATESINSTORE,
    CALL_CERTENUMCRLCONTEXTPROPERTIES,
    CALL_CERTENUMCRLSINSTORE,
    CALL_CERTENUMCTLCONTEXTPROPERTIES,
    CALL_CERTENUMCTLSINSTORE,
    CALL_CERTENUMPHYSICALSTORE,
    CALL_CERTENUMSYSTEMSTORE,
    CALL_CERTFINDATTRIBUTE,
    CALL_CERTFINDCERTIFICATEINCRL,
    CALL_CERTFINDCERTIFICATEINSTORE,
    CALL_CERTFINDCHAININSTORE,
    CALL_CERTFINDCRLINSTORE,
    CALL_CERTFINDCTLINSTORE,
    CALL_CERTFINDEXTENSION,
    CALL_CERTFINDRDNATTR,
    CALL_CERTFREECERTIFICATECHAIN,
    CALL_CERTFREECERTIFICATECHAINENGINE,
    CALL_CERTFREECERTIFICATECONTEXT,
    CALL_CERTFREECRLCONTEXT,
    CALL_CERTFREECTLCONTEXT,
    CALL_CERTGETCERTIFICATECHAIN,
    CALL_CERTGETCERTIFICATECONTEXTPROPERTY,
    CALL_CERTGETCRLCONTEXTPROPERTY,
    CALL_CERTGETCRLFROMSTORE,
    CALL_CERTGETCTLCONTEXTPROPERTY,
    CALL_CERTGETENHANCEDKEYUSAGE,
    CALL_CERTGETINTENDEDKEYUSAGE,
    CALL_CERTGETISSUERCERTIFICATEFROMSTORE,
    CALL_CERTGETNAMESTRINGA,
    CALL_CERTGETNAMESTRINGW,
    CALL_CERTGETPUBLICKEYLENGTH,
    CALL_CERTGETSTOREPROPERTY,
    CALL_CERTGETSUBJECTCERTIFICATEFROMSTORE,
    CALL_CERTGETVALIDUSAGES,
    CALL_CERTISRDNATTRSINCERTIFICATENAME,
    CALL_CERTISVALIDCRLFORCERTIFICATE,
    CALL_CERTNAMETOSTRA,
    CALL_CERTNAMETOSTRW,
    CALL_CERTOIDTOALGID,
    CALL_CERTOPENSTORE,
    CALL_CERTOPENSYSTEMSTOREA,
    CALL_CERTOPENSYSTEMSTOREW,
    CALL_CERTRDNVALUETOSTRA,
    CALL_CERTRDNVALUETOSTRW,
    CALL_CERTREGISTERPHYSICALSTORE,
    CALL_CERTREGISTERSYSTEMSTORE,
    CALL_CERTREMOVEENHANCEDKEYUSAGEIDENTIFIER,
    CALL_CERTREMOVESTOREFROMCOLLECTION,
    CALL_CERTSAVESTORE,
    CALL_CERTSERIALIZECERTIFICATESTOREELEMENT,
    CALL_CERTSERIALIZECRLSTOREELEMENT,
    CALL_CERTSERIALIZECTLSTOREELEMENT,
    CALL_CERTSETCERTIFICATECONTEXTPROPERTY,
    CALL_CERTSETCRLCONTEXTPROPERTY,
    CALL_CERTSETCTLCONTEXTPROPERTY,
    CALL_CERTSETENHANCEDKEYUSAGE,
    CALL_CERTSETSTOREPROPERTY,
    CALL_CERTSTRTONAMEA,
    CALL_CERTSTRTONAMEW,
    CALL_CERTUNREGISTERPHYSICALSTORE,
    CALL_CERTUNREGISTERSYSTEMSTORE,
    CALL_CERTVERIFYCERTIFICATECHAINPOLICY,
    CALL_CERTVERIFYCRLREVOCATION,
    CALL_CERTVERIFYCRLTIMEVALIDITY,
    CALL_CERTVERIFYCTLUSAGE,
    CALL_CERTVERIFYREVOCATION,
    CALL_CERTVERIFYSUBJECTCERTIFICATECONTEXT,
    CALL_CERTVERIFYTIMEVALIDITY,
    CALL_CERTVERIFYVALIDITYNESTING,
    CALL_CRYPTACQUIRECERTIFICATEPRIVATEKEY,
    CALL_CRYPTBINARYTOSTRINGA,
    CALL_CRYPTBINARYTOSTRINGW,
    CALL_CRYPTDECODEOBJECT,
    CALL_CRYPTDECODEOBJECTEX,
    CALL_CRYPTENCODEOBJECT,
    CALL_CRYPTENCODEOBJECTEX,
    CALL_CRYPTENCRYPTMESSAGE,
    CALL_CRYPTENUMOIDINFO,
    CALL_CRYPTEXPORTPUBLICKEYINFO,
    CALL_CRYPTEXPORTPUBLICKEYINFOEX,
    CALL_CRYPTFINDCERTIFICATEKEYPROVINFO,
    CALL_CRYPTFINDLOCALIZEDNAME,
    CALL_CRYPTFINDOIDINFO,
    CALL_CRYPTFORMATOBJECT,
    CALL_CRYPTFREEOIDFUNCTIONADDRESS,
    CALL_CRYPTGETDEFAULTOIDDLLLIST,
    CALL_CRYPTGETDEFAULTOIDFUNCTIONADDRESS,
    CALL_CRYPTGETMESSAGECERTIFICATES,
    CALL_CRYPTGETMESSAGESIGNERCOUNT,
    CALL_CRYPTGETOIDFUNCTIONADDRESS,
    CALL_CRYPTGETOIDFUNCTIONVALUE,
    CALL_CRYPTHASHCERTIFICATE,
    CALL_CRYPTHASHMESSAGE,
    CALL_CRYPTHASHPUBLICKEYINFO,
    CALL_CRYPTHASHTOBESIGNED,
    CALL_CRYPTIMPORTPUBLICKEYINFO,
    CALL_CRYPTIMPORTPUBLICKEYINFOEX,
    CALL_CRYPTINITOIDFUNCTIONSET,
    CALL_CRYPTINSTALLOIDFUNCTIONADDRESS,
    CALL_CRYPTMEMALLOC,
    CALL_CRYPTMEMFREE,
    CALL_CRYPTMEMREALLOC,
    CALL_CRYPTMSGCLOSE,
    CALL_CRYPTMSGCONTROL,
    CALL_CRYPTMSGDUPLICATE,
    CALL_CRYPTMSGENCODEANDSIGNCTL,
    CALL_CRYPTMSGGETANDVERIFYSIGNER,
    CALL_CRYPTMSGGETPARAM,
    CALL_CRYPTMSGOPENTODECODE,
    CALL_CRYPTMSGOPENTOENCODE,
    CALL_CRYPTMSGSIGNCTL,
    CALL_CRYPTMSGUPDATE,
    CALL_CRYPTMSGVERIFYCOUNTERSIGNATUREENCODED,
    CALL_CRYPTMSGVERIFYCOUNTERSIGNATUREENCODEDEX,
    CALL_CRYPTPROTECTDATA,
    CALL_CRYPTPROTECTMEMORY,
    CALL_CRYPTQUERYOBJECT,
    CALL_CRYPTREGISTERDEFAULTOIDFUNCTION,
    CALL_CRYPTREGISTEROIDFUNCTION,
    CALL_CRYPTREGISTEROIDINFO,
    CALL_CRYPTSETOIDFUNCTIONVALUE,
    CALL_CRYPTSIGNANDENCODECERTIFICATE,
    CALL_CRYPTSIGNCERTIFICATE,
    CALL_CRYPTSIGNMESSAGE,
    CALL_CRYPTSIPADDPROVIDER,
    CALL_CRYPTSIPCREATEINDIRECTDATA,
    CALL_CRYPTSIPGETSIGNEDDATAMSG,
    CALL_CRYPTSIPLOAD,
    CALL_CRYPTSIPPUTSIGNEDDATAMSG,
    CALL_CRYPTSIPREMOVEPROVIDER,
    CALL_CRYPTSIPREMOVESIGNEDDATAMSG,
    CALL_CRYPTSIPRETRIEVESUBJECTGUID,
    CALL_CRYPTSIPRETRIEVESUBJECTGUIDFORCATALOGFILE,
    CALL_CRYPTSIPVERIFYINDIRECTDATA,
    CALL_CRYPTSTRINGTOBINARYA,
    CALL_CRYPTSTRINGTOBINARYW,
    CALL_CRYPTUNPROTECTDATA,
    CALL_CRYPTUNPROTECTMEMORY,
    CALL_CRYPTUNREGISTERDEFAULTOIDFUNCTION,
    CALL_CRYPTUNREGISTEROIDFUNCTION,
    CALL_CRYPTVERIFYCERTIFICATESIGNATURE,
    CALL_CRYPTVERIFYCERTIFICATESIGNATUREEX,
    CALL_CRYPTVERIFYDETACHEDMESSAGEHASH,
    CALL_CRYPTVERIFYDETACHEDMESSAGESIGNATURE,
    CALL_CRYPTVERIFYMESSAGEHASH,
    CALL_CRYPTVERIFYMESSAGESIGNATURE,
    CALL_I_CERTUPDATESTORE,
    CALL_I_CRYPTALLOCTLS,
    CALL_I_CRYPTCREATELRUCACHE,
    CALL_I_CRYPTCREATELRUENTRY,
    CALL_I_CRYPTDETACHTLS,
    CALL_I_CRYPTFINDLRUENTRY,
    CALL_I_CRYPTFINDLRUENTRYDATA,
    CALL_I_CRYPTFLUSHLRUCACHE,
    CALL_I_CRYPTFREELRUCACHE,
    CALL_I_CRYPTFREETLS,
    CALL_I_CRYPTGETASN1DECODER,
    CALL_I_CRYPTGETASN1ENCODER,
    CALL_I_CRYPTGETDEFAULTCRYPTPROV,
    CALL_I_CRYPTGETOSSGLOBAL,
    CALL_I_CRYPTGETTLS,
    CALL_I_CRYPTINSTALLASN1MODULE,
    CALL_I_CRYPTINSTALLOSSGLOBAL,
    CALL_I_CRYPTREADTRUSTEDPUBLISHERDWORDVALUEFROMREGISTRY,
    CALL_I_CRYPTSETTLS,
    CALL_I_CRYPTUNINSTALLASN1MODULE,
    CALL_INIT_DLL,
    CALL_PFXEXPORTCERTSTORE,
    CALL_PFXEXPORTCERTSTOREEX,
    CALL_PFXIMPORTCERTSTORE,
    CALL_PFXISPFXBLOB,
    CALL_PFXVERIFYPASSWORD,
};

/* Taken from crypt32_private.h */
#define IS_INTOID(x)    (((ULONG_PTR)(x) >> 16) == 0)

#ifdef QEMU_DLL_GUEST

#else

#include <wine/rbtree.h>

extern const struct qemu_ops *qemu_ops;

void qemu_CertAddCRLContextToStore(struct qemu_syscall *call);
void qemu_CertAddCTLContextToStore(struct qemu_syscall *call);
void qemu_CertAddCertificateContextToStore(struct qemu_syscall *call);
void qemu_CertAddCertificateLinkToStore(struct qemu_syscall *call);
void qemu_CertAddEncodedCRLToStore(struct qemu_syscall *call);
void qemu_CertAddEncodedCTLToStore(struct qemu_syscall *call);
void qemu_CertAddEncodedCertificateToStore(struct qemu_syscall *call);
void qemu_CertAddEncodedCertificateToSystemStoreA(struct qemu_syscall *call);
void qemu_CertAddEncodedCertificateToSystemStoreW(struct qemu_syscall *call);
void qemu_CertAddEnhancedKeyUsageIdentifier(struct qemu_syscall *call);
void qemu_CertAddSerializedElementToStore(struct qemu_syscall *call);
void qemu_CertAddStoreToCollection(struct qemu_syscall *call);
void qemu_CertAlgIdToOID(struct qemu_syscall *call);
void qemu_CertCloseStore(struct qemu_syscall *call);
void qemu_CertCompareCertificate(struct qemu_syscall *call);
void qemu_CertCompareCertificateName(struct qemu_syscall *call);
void qemu_CertCompareIntegerBlob(struct qemu_syscall *call);
void qemu_CertComparePublicKeyInfo(struct qemu_syscall *call);
void qemu_CertControlStore(struct qemu_syscall *call);
void qemu_CertCreateCRLContext(struct qemu_syscall *call);
void qemu_CertCreateCTLContext(struct qemu_syscall *call);
void qemu_CertCreateCertificateChainEngine(struct qemu_syscall *call);
void qemu_CertCreateCertificateContext(struct qemu_syscall *call);
void qemu_CertCreateContext(struct qemu_syscall *call);
void qemu_CertCreateSelfSignCertificate(struct qemu_syscall *call);
void qemu_CertDeleteCRLFromStore(struct qemu_syscall *call);
void qemu_CertDeleteCTLFromStore(struct qemu_syscall *call);
void qemu_CertDeleteCertificateFromStore(struct qemu_syscall *call);
void qemu_CertDuplicateCRLContext(struct qemu_syscall *call);
void qemu_CertDuplicateCTLContext(struct qemu_syscall *call);
void qemu_CertDuplicateCertificateChain(struct qemu_syscall *call);
void qemu_CertDuplicateCertificateContext(struct qemu_syscall *call);
void qemu_CertDuplicateStore(struct qemu_syscall *call);
void qemu_CertEnumCRLContextProperties(struct qemu_syscall *call);
void qemu_CertEnumCRLsInStore(struct qemu_syscall *call);
void qemu_CertEnumCTLContextProperties(struct qemu_syscall *call);
void qemu_CertEnumCTLsInStore(struct qemu_syscall *call);
void qemu_CertEnumCertificateContextProperties(struct qemu_syscall *call);
void qemu_CertEnumCertificatesInStore(struct qemu_syscall *call);
void qemu_CertEnumPhysicalStore(struct qemu_syscall *call);
void qemu_CertEnumSystemStore(struct qemu_syscall *call);
void qemu_CertFindAttribute(struct qemu_syscall *call);
void qemu_CertFindCRLInStore(struct qemu_syscall *call);
void qemu_CertFindCTLInStore(struct qemu_syscall *call);
void qemu_CertFindCertificateInCRL(struct qemu_syscall *call);
void qemu_CertFindCertificateInStore(struct qemu_syscall *call);
void qemu_CertFindChainInStore(struct qemu_syscall *call);
void qemu_CertFindExtension(struct qemu_syscall *call);
void qemu_CertFindRDNAttr(struct qemu_syscall *call);
void qemu_CertFreeCRLContext(struct qemu_syscall *call);
void qemu_CertFreeCTLContext(struct qemu_syscall *call);
void qemu_CertFreeCertificateChain(struct qemu_syscall *call);
void qemu_CertFreeCertificateChainEngine(struct qemu_syscall *call);
void qemu_CertFreeCertificateContext(struct qemu_syscall *call);
void qemu_CertGetCRLContextProperty(struct qemu_syscall *call);
void qemu_CertGetCRLFromStore(struct qemu_syscall *call);
void qemu_CertGetCTLContextProperty(struct qemu_syscall *call);
void qemu_CertGetCertificateChain(struct qemu_syscall *call);
void qemu_CertGetCertificateContextProperty(struct qemu_syscall *call);
void qemu_CertGetEnhancedKeyUsage(struct qemu_syscall *call);
void qemu_CertGetIntendedKeyUsage(struct qemu_syscall *call);
void qemu_CertGetIssuerCertificateFromStore(struct qemu_syscall *call);
void qemu_CertGetNameStringA(struct qemu_syscall *call);
void qemu_CertGetNameStringW(struct qemu_syscall *call);
void qemu_CertGetPublicKeyLength(struct qemu_syscall *call);
void qemu_CertGetStoreProperty(struct qemu_syscall *call);
void qemu_CertGetSubjectCertificateFromStore(struct qemu_syscall *call);
void qemu_CertGetValidUsages(struct qemu_syscall *call);
void qemu_CertIsRDNAttrsInCertificateName(struct qemu_syscall *call);
void qemu_CertIsValidCRLForCertificate(struct qemu_syscall *call);
void qemu_CertNameToStrA(struct qemu_syscall *call);
void qemu_CertNameToStrW(struct qemu_syscall *call);
void qemu_CertOIDToAlgId(struct qemu_syscall *call);
void qemu_CertOpenStore(struct qemu_syscall *call);
void qemu_CertOpenSystemStoreA(struct qemu_syscall *call);
void qemu_CertOpenSystemStoreW(struct qemu_syscall *call);
void qemu_CertRDNValueToStrA(struct qemu_syscall *call);
void qemu_CertRDNValueToStrW(struct qemu_syscall *call);
void qemu_CertRegisterPhysicalStore(struct qemu_syscall *call);
void qemu_CertRegisterSystemStore(struct qemu_syscall *call);
void qemu_CertRemoveEnhancedKeyUsageIdentifier(struct qemu_syscall *call);
void qemu_CertRemoveStoreFromCollection(struct qemu_syscall *call);
void qemu_CertSaveStore(struct qemu_syscall *call);
void qemu_CertSerializeCRLStoreElement(struct qemu_syscall *call);
void qemu_CertSerializeCTLStoreElement(struct qemu_syscall *call);
void qemu_CertSerializeCertificateStoreElement(struct qemu_syscall *call);
void qemu_CertSetCRLContextProperty(struct qemu_syscall *call);
void qemu_CertSetCTLContextProperty(struct qemu_syscall *call);
void qemu_CertSetCertificateContextProperty(struct qemu_syscall *call);
void qemu_CertSetEnhancedKeyUsage(struct qemu_syscall *call);
void qemu_CertSetStoreProperty(struct qemu_syscall *call);
void qemu_CertStrToNameA(struct qemu_syscall *call);
void qemu_CertStrToNameW(struct qemu_syscall *call);
void qemu_CertUnregisterPhysicalStore(struct qemu_syscall *call);
void qemu_CertUnregisterSystemStore(struct qemu_syscall *call);
void qemu_CertVerifyCRLRevocation(struct qemu_syscall *call);
void qemu_CertVerifyCRLTimeValidity(struct qemu_syscall *call);
void qemu_CertVerifyCTLUsage(struct qemu_syscall *call);
void qemu_CertVerifyCertificateChainPolicy(struct qemu_syscall *call);
void qemu_CertVerifyRevocation(struct qemu_syscall *call);
void qemu_CertVerifySubjectCertificateContext(struct qemu_syscall *call);
void qemu_CertVerifyTimeValidity(struct qemu_syscall *call);
void qemu_CertVerifyValidityNesting(struct qemu_syscall *call);
void qemu_CryptAcquireCertificatePrivateKey(struct qemu_syscall *call);
void qemu_CryptBinaryToStringA(struct qemu_syscall *call);
void qemu_CryptBinaryToStringW(struct qemu_syscall *call);
void qemu_CryptDecodeObject(struct qemu_syscall *call);
void qemu_CryptDecodeObjectEx(struct qemu_syscall *call);
void qemu_CryptEncodeObject(struct qemu_syscall *call);
void qemu_CryptEncodeObjectEx(struct qemu_syscall *call);
void qemu_CryptEncryptMessage(struct qemu_syscall *call);
void qemu_CryptEnumOIDInfo(struct qemu_syscall *call);
void qemu_CryptExportPublicKeyInfo(struct qemu_syscall *call);
void qemu_CryptExportPublicKeyInfoEx(struct qemu_syscall *call);
void qemu_CryptFindCertificateKeyProvInfo(struct qemu_syscall *call);
void qemu_CryptFindLocalizedName(struct qemu_syscall *call);
void qemu_CryptFindOIDInfo(struct qemu_syscall *call);
void qemu_CryptFormatObject(struct qemu_syscall *call);
void qemu_CryptFreeOIDFunctionAddress(struct qemu_syscall *call);
void qemu_CryptGetDefaultOIDDllList(struct qemu_syscall *call);
void qemu_CryptGetDefaultOIDFunctionAddress(struct qemu_syscall *call);
void qemu_CryptGetMessageCertificates(struct qemu_syscall *call);
void qemu_CryptGetMessageSignerCount(struct qemu_syscall *call);
void qemu_CryptGetOIDFunctionAddress(struct qemu_syscall *call);
void qemu_CryptGetOIDFunctionValue(struct qemu_syscall *call);
void qemu_CryptHashCertificate(struct qemu_syscall *call);
void qemu_CryptHashMessage(struct qemu_syscall *call);
void qemu_CryptHashPublicKeyInfo(struct qemu_syscall *call);
void qemu_CryptHashToBeSigned(struct qemu_syscall *call);
void qemu_CryptImportPublicKeyInfo(struct qemu_syscall *call);
void qemu_CryptImportPublicKeyInfoEx(struct qemu_syscall *call);
void qemu_CryptInitOIDFunctionSet(struct qemu_syscall *call);
void qemu_CryptInstallOIDFunctionAddress(struct qemu_syscall *call);
void qemu_CryptMsgClose(struct qemu_syscall *call);
void qemu_CryptMsgControl(struct qemu_syscall *call);
void qemu_CryptMsgDuplicate(struct qemu_syscall *call);
void qemu_CryptMsgEncodeAndSignCTL(struct qemu_syscall *call);
void qemu_CryptMsgGetAndVerifySigner(struct qemu_syscall *call);
void qemu_CryptMsgGetParam(struct qemu_syscall *call);
void qemu_CryptMsgOpenToDecode(struct qemu_syscall *call);
void qemu_CryptMsgOpenToEncode(struct qemu_syscall *call);
void qemu_CryptMsgSignCTL(struct qemu_syscall *call);
void qemu_CryptMsgUpdate(struct qemu_syscall *call);
void qemu_CryptMsgVerifyCountersignatureEncoded(struct qemu_syscall *call);
void qemu_CryptMsgVerifyCountersignatureEncodedEx(struct qemu_syscall *call);
void qemu_CryptProtectData(struct qemu_syscall *call);
void qemu_CryptQueryObject(struct qemu_syscall *call);
void qemu_CryptRegisterDefaultOIDFunction(struct qemu_syscall *call);
void qemu_CryptRegisterOIDFunction(struct qemu_syscall *call);
void qemu_CryptRegisterOIDInfo(struct qemu_syscall *call);
void qemu_CryptSIPAddProvider(struct qemu_syscall *call);
void qemu_CryptSIPCreateIndirectData(struct qemu_syscall *call);
void qemu_CryptSIPGetSignedDataMsg(struct qemu_syscall *call);
void qemu_CryptSIPLoad(struct qemu_syscall *call);
void qemu_CryptSIPPutSignedDataMsg(struct qemu_syscall *call);
void qemu_CryptSIPRemoveProvider(struct qemu_syscall *call);
void qemu_CryptSIPRemoveSignedDataMsg(struct qemu_syscall *call);
void qemu_CryptSIPRetrieveSubjectGuid(struct qemu_syscall *call);
void qemu_CryptSIPRetrieveSubjectGuidForCatalogFile(struct qemu_syscall *call);
void qemu_CryptSIPVerifyIndirectData(struct qemu_syscall *call);
void qemu_CryptSetOIDFunctionValue(struct qemu_syscall *call);
void qemu_CryptSignAndEncodeCertificate(struct qemu_syscall *call);
void qemu_CryptSignCertificate(struct qemu_syscall *call);
void qemu_CryptSignMessage(struct qemu_syscall *call);
void qemu_CryptStringToBinaryA(struct qemu_syscall *call);
void qemu_CryptStringToBinaryW(struct qemu_syscall *call);
void qemu_CryptUnprotectData(struct qemu_syscall *call);
void qemu_CryptUnregisterDefaultOIDFunction(struct qemu_syscall *call);
void qemu_CryptUnregisterOIDFunction(struct qemu_syscall *call);
void qemu_CryptVerifyCertificateSignature(struct qemu_syscall *call);
void qemu_CryptVerifyCertificateSignatureEx(struct qemu_syscall *call);
void qemu_CryptVerifyDetachedMessageHash(struct qemu_syscall *call);
void qemu_CryptVerifyDetachedMessageSignature(struct qemu_syscall *call);
void qemu_CryptVerifyMessageHash(struct qemu_syscall *call);
void qemu_CryptVerifyMessageSignature(struct qemu_syscall *call);
void qemu_I_CertUpdateStore(struct qemu_syscall *call);
void qemu_PFXExportCertStore(struct qemu_syscall *call);
void qemu_PFXExportCertStoreEx(struct qemu_syscall *call);
void qemu_PFXImportCertStore(struct qemu_syscall *call);
void qemu_PFXIsPFXBlob(struct qemu_syscall *call);
void qemu_PFXVerifyPassword(struct qemu_syscall *call);

struct qemu_cert_context
{
    struct qemu_CERT_CONTEXT cert32;
    struct qemu_CERT_INFO cert_info;
    const CERT_CONTEXT *cert64;
    ULONG ref;
    struct wine_rb_entry entry;
};

struct qemu_cert_context *context32_create(const CERT_CONTEXT *cert64);
void context32_decref(struct qemu_cert_context *context);

static inline struct qemu_cert_context *context_impl_from_context32(struct qemu_CERT_CONTEXT *cert32)
{
    if (!cert32)
        return NULL;
    return CONTAINING_RECORD(cert32, struct qemu_cert_context, cert32);
}

extern HCERTSTORE empty_store;
extern uint64_t empty_store_replace;
HCERTSTORE cert_store_g2h(uint64_t store);

struct qemu_cert_chain_context
{
    struct qemu_CERT_CHAIN_CONTEXT context32;
    const CERT_CHAIN_CONTEXT *context64;
    LONG ref;
};

#endif

#endif
