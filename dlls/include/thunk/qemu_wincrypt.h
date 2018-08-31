#ifndef HAVE_QEMU_THUNK_WINCRYPT_H
#define HAVE_QEMU_THUNK_WINCRYPT_H

#include "thunk/qemu_bcrypt.h"

struct qemu_CERT_CONTEXT
{
    DWORD      dwCertEncodingType;
    qemu_ptr   pbCertEncoded; /* BYTE * */
    DWORD      cbCertEncoded;
    qemu_ptr   pCertInfo; /* CERT_INFO * */
    qemu_ptr   hCertStore; /* HCERTSTORE */
};

static inline void CERT_CONTEXT_g2h(CERT_CONTEXT *host, const struct qemu_CERT_CONTEXT *guest)
{
    host->dwCertEncodingType = guest->dwCertEncodingType;
    host->pbCertEncoded = (BYTE *)(ULONG_PTR)guest->pbCertEncoded;
    host->cbCertEncoded = guest->cbCertEncoded;
    host->pCertInfo = (CERT_INFO *)(ULONG_PTR)guest->pCertInfo;
    host->hCertStore = (HCERTSTORE)(ULONG_PTR)guest->hCertStore;
}

static inline void CERT_CONTEXT_h2g(struct qemu_CERT_CONTEXT *guest, const CERT_CONTEXT *host)
{
    guest->dwCertEncodingType = host->dwCertEncodingType;
    guest->pbCertEncoded = (ULONG_PTR)host->pbCertEncoded;
    guest->cbCertEncoded = host->cbCertEncoded;
    guest->pCertInfo = (ULONG_PTR)host->pCertInfo;
    guest->hCertStore = (ULONG_PTR)host->hCertStore;
}

struct qemu_CRYPT_DATA_BLOB
{
    DWORD       cbData;
    qemu_ptr    pbData;
};

static inline void CRYPT_DATA_BLOB_g2h(CRYPT_DATA_BLOB *host, const struct qemu_CRYPT_DATA_BLOB *guest)
{
    host->cbData = guest->cbData;
    host->pbData = (BYTE *)(ULONG_PTR)guest->pbData;
}

static inline void CRYPT_DATA_BLOB_h2g(struct qemu_CRYPT_DATA_BLOB *guest, const CRYPT_DATA_BLOB *host)
{
    guest->cbData = host->cbData;
    guest->pbData = (ULONG_PTR)host->pbData;
}

struct qemu_CERT_KEY_CONTEXT
{
    DWORD       cbSize;
    qemu_ptr    hCryptProv;
    DWORD       dwKeySpec;
};

static inline void CERT_KEY_CONTEXT_g2h(CERT_KEY_CONTEXT *host, const struct qemu_CERT_KEY_CONTEXT *guest)
{
    host->cbSize = sizeof(*host);
    host->hCryptProv = (HCRYPTPROV)(ULONG_PTR)guest->hCryptProv;
    host->dwKeySpec = guest->dwKeySpec;
}

static inline void CERT_KEY_CONTEXT_h2g(struct qemu_CERT_KEY_CONTEXT *guest, const CERT_KEY_CONTEXT *host)
{
    guest->hCryptProv = (ULONG_PTR)host->hCryptProv;
    guest->dwKeySpec = host->dwKeySpec;
}

struct qemu_CRYPT_ALGORITHM_IDENTIFIER
{
    qemu_ptr              pszObjId;
    struct qemu_CRYPT_DATA_BLOB  Parameters;
};

static inline void CRYPT_ALGORITHM_IDENTIFIER_g2h(CRYPT_ALGORITHM_IDENTIFIER *host,
        const struct qemu_CRYPT_ALGORITHM_IDENTIFIER *guest)
{
    host->pszObjId = (char *)(ULONG_PTR)guest->pszObjId;
    CRYPT_DATA_BLOB_g2h(&host->Parameters, &guest->Parameters);
}

static inline void CRYPT_ALGORITHM_IDENTIFIER_h2g(struct qemu_CRYPT_ALGORITHM_IDENTIFIER *guest,
        const CRYPT_ALGORITHM_IDENTIFIER *host)
{
    guest->pszObjId = (ULONG_PTR)host->pszObjId;
    CRYPT_DATA_BLOB_h2g(&guest->Parameters, &host->Parameters);
}

struct qemu_CRYPT_BIT_BLOB
{
    DWORD       cbData;
    qemu_ptr    pbData;
    DWORD       cUnusedBits;
};

static inline void CRYPT_BIT_BLOB_g2h(CRYPT_BIT_BLOB *host, const struct qemu_CRYPT_BIT_BLOB *guest)
{
    host->cbData = guest->cbData;
    host->pbData = (BYTE *)(ULONG_PTR)guest->pbData;
    host->cUnusedBits = guest->cUnusedBits;
}

static inline void CRYPT_BIT_BLOB_h2g(struct qemu_CRYPT_BIT_BLOB *guest, const CRYPT_BIT_BLOB *host)
{
    guest->cbData = host->cbData;
    guest->pbData = (ULONG_PTR)host->pbData;
    guest->cUnusedBits = host->cUnusedBits;
}

struct qemu_CERT_PUBLIC_KEY_INFO
{
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER Algorithm;
    struct qemu_CRYPT_BIT_BLOB             PublicKey;
};

static inline void CERT_PUBLIC_KEY_INFO_g2h(CERT_PUBLIC_KEY_INFO *host, const struct qemu_CERT_PUBLIC_KEY_INFO *guest)
{
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->Algorithm, &guest->Algorithm);
    CRYPT_BIT_BLOB_g2h(&host->PublicKey, &guest->PublicKey);
}

static inline void CERT_PUBLIC_KEY_INFO_h2g(struct qemu_CERT_PUBLIC_KEY_INFO *guest, const CERT_PUBLIC_KEY_INFO *host)
{
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->Algorithm, &host->Algorithm);
    CRYPT_BIT_BLOB_h2g(&guest->PublicKey, &host->PublicKey);
}

struct qemu_CERT_EXTENSION
{
    qemu_ptr                        pszObjId;
    BOOL                            fCritical;
    struct qemu_CRYPT_DATA_BLOB     Value;
};

static inline void CERT_EXTENSION_g2h(CERT_EXTENSION *host, const struct qemu_CERT_EXTENSION *guest)
{
    host->pszObjId = (char *)(ULONG_PTR)guest->pszObjId;
    host->fCritical = guest->fCritical;
    CRYPT_DATA_BLOB_g2h(&host->Value, &guest->Value);
}

static inline void CERT_EXTENSION_h2g(struct qemu_CERT_EXTENSION *guest, const CERT_EXTENSION *host)
{
    guest->pszObjId = (ULONG_PTR)host->pszObjId;
    guest->fCritical = host->fCritical;
    CRYPT_DATA_BLOB_h2g(&guest->Value, &host->Value);
}

struct qemu_CERT_INFO
{
    DWORD                                   dwVersion;
    struct qemu_CRYPT_DATA_BLOB             SerialNumber;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    struct qemu_CRYPT_DATA_BLOB             Issuer;
    FILETIME                                NotBefore;
    FILETIME                                NotAfter;
    struct qemu_CRYPT_DATA_BLOB             Subject;
    struct qemu_CERT_PUBLIC_KEY_INFO        SubjectPublicKeyInfo;
    struct qemu_CRYPT_BIT_BLOB              IssuerUniqueId;
    struct qemu_CRYPT_BIT_BLOB              SubjectUniqueId;
    DWORD                                   cExtension;
    qemu_ptr                                rgExtension;
};

static inline void CERT_INFO_g2h(CERT_INFO *host, const struct qemu_CERT_INFO *guest)
{
    host->dwVersion = guest->dwVersion;
    CRYPT_DATA_BLOB_g2h(&host->SerialNumber, &guest->SerialNumber);
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->SignatureAlgorithm, &guest->SignatureAlgorithm);
    CRYPT_DATA_BLOB_g2h(&host->Issuer, &guest->Issuer);
    host->NotBefore = guest->NotBefore;
    host->NotAfter = guest->NotAfter;
    CRYPT_DATA_BLOB_g2h(&host->Subject, &guest->Subject);
    CERT_PUBLIC_KEY_INFO_g2h(&host->SubjectPublicKeyInfo, &guest->SubjectPublicKeyInfo);
    CRYPT_BIT_BLOB_g2h(&host->IssuerUniqueId, &guest->IssuerUniqueId);
    CRYPT_BIT_BLOB_g2h(&host->SubjectUniqueId, &guest->SubjectUniqueId);
    host->cExtension = guest->cExtension;
    host->rgExtension = (PCERT_EXTENSION)(ULONG_PTR)guest->rgExtension; /* FIXME */
}

static inline void CERT_INFO_h2g(struct qemu_CERT_INFO *guest, const CERT_INFO *host)
{
    guest->dwVersion = host->dwVersion;
    CRYPT_DATA_BLOB_h2g(&guest->SerialNumber, &host->SerialNumber);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->SignatureAlgorithm, &host->SignatureAlgorithm);
    CRYPT_DATA_BLOB_h2g(&guest->Issuer, &host->Issuer);
    guest->NotBefore = host->NotBefore;
    guest->NotAfter = host->NotAfter;
    CRYPT_DATA_BLOB_h2g(&guest->Subject, &host->Subject);
    CERT_PUBLIC_KEY_INFO_h2g(&guest->SubjectPublicKeyInfo, &host->SubjectPublicKeyInfo);
    CRYPT_BIT_BLOB_h2g(&guest->IssuerUniqueId, &host->IssuerUniqueId);
    CRYPT_BIT_BLOB_h2g(&guest->SubjectUniqueId, &host->SubjectUniqueId);
    guest->cExtension = host->cExtension;
    guest->rgExtension = (ULONG_PTR)host->rgExtension; /* FIXME */
}

struct qemu_CRYPT_KEY_PROV_PARAM
{
    DWORD       dwParam;
    qemu_ptr    pbData;
    DWORD       cbData;
    DWORD       dwFlags;
};

static inline void CRYPT_KEY_PROV_PARAM_g2h(CRYPT_KEY_PROV_PARAM *host, const struct qemu_CRYPT_KEY_PROV_PARAM *guest)
{
    host->dwParam = guest->dwParam;
    host->pbData = (BYTE *)(ULONG_PTR)guest->pbData;
    host->cbData = guest->cbData;
    host->dwFlags = guest->dwFlags;
}

static inline void CRYPT_KEY_PROV_PARAM_h2g(struct qemu_CRYPT_KEY_PROV_PARAM *guest, const CRYPT_KEY_PROV_PARAM *host)
{
    guest->dwParam = host->dwParam;
    guest->pbData = (ULONG_PTR)host->pbData;
    guest->cbData = host->cbData;
    guest->dwFlags = host->dwFlags;
}

struct qemu_CRYPT_KEY_PROV_INFO
{
    qemu_ptr            pwszContainerName;
    qemu_ptr            pwszProvName;
    DWORD               dwProvType;
    DWORD               dwFlags;
    DWORD               cProvParam;
    qemu_ptr            rgProvParam;
    DWORD               dwKeySpec;
};

static inline void CRYPT_KEY_PROV_INFO_g2h(CRYPT_KEY_PROV_INFO *host, const struct qemu_CRYPT_KEY_PROV_INFO *guest)
{
    host->pwszContainerName = (WCHAR *)(ULONG_PTR)guest->pwszContainerName;
    host->pwszProvName = (WCHAR *)(ULONG_PTR)guest->pwszProvName;
    host->dwProvType = guest->dwProvType;
    host->dwFlags = guest->dwFlags;
    host->cProvParam = guest->cProvParam;
    host->rgProvParam = (CRYPT_KEY_PROV_PARAM *)(ULONG_PTR)guest->rgProvParam;
    host->dwKeySpec = guest->dwKeySpec;
}

static inline void CRYPT_KEY_PROV_INFO_h2g(struct qemu_CRYPT_KEY_PROV_INFO *guest, const CRYPT_KEY_PROV_INFO *host)
{
    guest->pwszContainerName = (ULONG_PTR)host->pwszContainerName;
    guest->pwszProvName = (ULONG_PTR)host->pwszProvName;
    guest->dwProvType = host->dwProvType;
    guest->dwFlags = host->dwFlags;
    guest->cProvParam = host->cProvParam;
    guest->rgProvParam = (ULONG_PTR)host->rgProvParam;
    guest->dwKeySpec = host->dwKeySpec;
}

struct qemu_CERT_SIGNED_CONTENT_INFO
{
    struct qemu_CRYPT_DATA_BLOB             ToBeSigned;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm;
    struct qemu_CRYPT_BIT_BLOB              Signature;
};

static inline void CERT_SIGNED_CONTENT_INFO_g2h(CERT_SIGNED_CONTENT_INFO *host,
        const struct qemu_CERT_SIGNED_CONTENT_INFO *guest)
{
    CRYPT_DATA_BLOB_g2h(&host->ToBeSigned, &guest->ToBeSigned);
    CRYPT_ALGORITHM_IDENTIFIER_g2h(&host->SignatureAlgorithm, &guest->SignatureAlgorithm);
    CRYPT_BIT_BLOB_g2h(&host->Signature, &guest->Signature);
}

static inline void CERT_SIGNED_CONTENT_INFO_h2g(struct qemu_CERT_SIGNED_CONTENT_INFO *guest,
        const CERT_SIGNED_CONTENT_INFO *host)
{
    CRYPT_DATA_BLOB_h2g(&guest->ToBeSigned, &host->ToBeSigned);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->SignatureAlgorithm, &host->SignatureAlgorithm);
    CRYPT_BIT_BLOB_h2g(&guest->Signature, &host->Signature);
}

#ifndef QEMU_DLL_GUEST
struct qemu_CERT_CHAIN_ENGINE_CONFIG
{
    DWORD       cbSize;
    qemu_ptr    hRestrictedRoot;
    qemu_ptr    hRestrictedTrust;
    qemu_ptr    hRestrictedOther;
    DWORD       cAdditionalStore;
    qemu_ptr    *rghAdditionalStore;
    DWORD       dwFlags;
    DWORD       dwUrlRetrievalTimeout;
    DWORD       MaximumCachedCertificates;
    DWORD       CycleDetectionModulus;
    qemu_ptr    hExclusiveRoot;
    qemu_ptr    hExclusiveRootTrustedPeople;
};

static inline void CERT_CHAIN_ENGINE_CONFIG_g2h(CERT_CHAIN_ENGINE_CONFIG *host,
        const struct qemu_CERT_CHAIN_ENGINE_CONFIG *guest)
{
    host->cbSize = sizeof(*host);
    host->hRestrictedRoot = (HCERTSTORE)(ULONG_PTR)guest->hRestrictedRoot;
    host->hRestrictedTrust = (HCERTSTORE)(ULONG_PTR)guest->hRestrictedTrust;
    host->hRestrictedOther = (HCERTSTORE)(ULONG_PTR)guest->hRestrictedOther;
    host->cAdditionalStore = guest->cAdditionalStore;
    host->rghAdditionalStore = (HCERTSTORE)(ULONG_PTR)guest->rghAdditionalStore;
    host->dwFlags = guest->dwFlags;
    host->dwUrlRetrievalTimeout = guest->dwUrlRetrievalTimeout;
    host->MaximumCachedCertificates = guest->MaximumCachedCertificates;
    host->CycleDetectionModulus = guest->CycleDetectionModulus;
    if (guest->cbSize == sizeof(*guest))
    {
        host->hExclusiveRoot = (HCERTSTORE)(ULONG_PTR)guest->hExclusiveRoot;
        host->hExclusiveRootTrustedPeople = (HCERTSTORE)(ULONG_PTR)guest->hExclusiveRootTrustedPeople;
    }
    else
    {
        host->hExclusiveRoot = NULL;
        host->hExclusiveRootTrustedPeople = NULL;
    }
}

struct qemu_CTL_USAGE
{
    DWORD       cUsageIdentifier;
    qemu_ptr    rgpszUsageIdentifier;
};

static inline void CTL_USAGE_g2h(CTL_USAGE *host, const struct qemu_CTL_USAGE *guest)
{
    host->cUsageIdentifier = guest->cUsageIdentifier;
    host->rgpszUsageIdentifier = (char **)(ULONG_PTR)guest->rgpszUsageIdentifier;
}

static inline void CTL_USAGE_h2g(struct qemu_CTL_USAGE *guest, const CTL_USAGE *host)
{
    guest->cUsageIdentifier = host->cUsageIdentifier;
    guest->rgpszUsageIdentifier = (ULONG_PTR)host->rgpszUsageIdentifier;
}

struct qemu_CERT_USAGE_MATCH
{
    DWORD                   dwType;
    struct qemu_CTL_USAGE   Usage;
};

static inline void CERT_USAGE_MATCH_g2h(CERT_USAGE_MATCH *host, const struct qemu_CERT_USAGE_MATCH *guest)
{
    host->dwType = guest->dwType;
    CTL_USAGE_g2h(&host->Usage, &guest->Usage);
}

static inline void CERT_USAGE_MATCH_h2g(struct qemu_CERT_USAGE_MATCH *guest, const CERT_USAGE_MATCH *host)
{
    guest->dwType = host->dwType;
    CTL_USAGE_h2g(&guest->Usage, &host->Usage);
}

struct qemu_CERT_CHAIN_PARA
{
    DWORD                           cbSize;
    struct qemu_CERT_USAGE_MATCH    RequestedUsage;
#ifdef CERT_CHAIN_PARA_HAS_EXTRA_FIELDS
    struct qemu_CERT_USAGE_MATCH    RequestedIssuancePolicy;
    DWORD                           dwUrlRetrievalTimeout;
    BOOL                            fCheckRevocationFreshnessTime;
    DWORD                           dwRevocationFreshnessTime;
    qemu_ptr                        pftCacheResync;
#endif
};

static inline void CERT_CHAIN_PARA_g2h(CERT_CHAIN_PARA *host, const struct qemu_CERT_CHAIN_PARA *guest)
{
    host->cbSize = sizeof(*host);
    CERT_USAGE_MATCH_g2h(&host->RequestedUsage, &guest->RequestedUsage);
#ifdef CERT_CHAIN_PARA_HAS_EXTRA_FIELDS
    CERT_USAGE_MATCH_g2h(&host->RequestedIssuancePolicy, &guest->RequestedIssuancePolicy);
    host->dwUrlRetrievalTimeout = guest->dwUrlRetrievalTimeout;
    host->fCheckRevocationFreshnessTime = guest->fCheckRevocationFreshnessTime;
    host->dwRevocationFreshnessTime = guest->dwRevocationFreshnessTime;
    host->pftCacheResync = (FILETIME *)(ULONG_PTR)guest->pftCacheResync;
#endif
}
#endif

struct qemu_CMSG_SIGNER_INFO
{
    DWORD                                   dwVersion;
    struct qemu_CRYPT_DATA_BLOB             Issuer;
    struct qemu_CRYPT_DATA_BLOB             SerialNumber;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm;
    struct qemu_CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm;
    struct qemu_CRYPT_DATA_BLOB             EncryptedHash;
    CRYPT_ATTRIBUTES                        AuthAttrs;
    CRYPT_ATTRIBUTES                        UnauthAttrs;
};

static inline void CMSG_SIGNER_INFO_h2g(struct qemu_CMSG_SIGNER_INFO *guest, const CMSG_SIGNER_INFO *host)
{
    guest->dwVersion = host->dwVersion;
    CRYPT_DATA_BLOB_h2g(&guest->Issuer, &host->Issuer);
    CRYPT_DATA_BLOB_h2g(&guest->SerialNumber, &host->SerialNumber);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->HashAlgorithm, &host->HashAlgorithm);
    CRYPT_ALGORITHM_IDENTIFIER_h2g(&guest->HashEncryptionAlgorithm, &host->HashEncryptionAlgorithm);
    CRYPT_DATA_BLOB_h2g(&guest->EncryptedHash, &host->EncryptedHash);
    /* FIXME Needs more complicated data */
}

struct qemu_CERT_CHAIN_POLICY_STATUS
{
    DWORD cbSize;
    DWORD dwError;
    LONG  lChainIndex;
    LONG  lElementIndex;
    qemu_ptr pvExtraPolicyStatus;
};

static inline void CERT_CHAIN_POLICY_STATUS_h2g(struct qemu_CERT_CHAIN_POLICY_STATUS *guest,
        const CERT_CHAIN_POLICY_STATUS *host)
{
    guest->dwError = host->dwError;
    guest->lChainIndex = host->lChainIndex;
    guest->lElementIndex = host->lElementIndex;
    guest->pvExtraPolicyStatus = (ULONG_PTR)host->pvExtraPolicyStatus;
}

static inline void CERT_CHAIN_POLICY_STATUS_g2h(CERT_CHAIN_POLICY_STATUS *host,
        const struct qemu_CERT_CHAIN_POLICY_STATUS *guest)
{
    host->cbSize = sizeof(*host);
    host->dwError = guest->dwError;
    host->lChainIndex = guest->lChainIndex;
    host->lElementIndex = guest->lElementIndex;
    host->pvExtraPolicyStatus = (void *)(ULONG_PTR)guest->pvExtraPolicyStatus;
}

struct qemu_CERT_CHAIN_POLICY_PARA
{
    DWORD cbSize;
    DWORD dwFlags;
    qemu_ptr pvExtraPolicyPara;
};

static inline void CERT_CHAIN_POLICY_PARA_h2g(struct qemu_CERT_CHAIN_POLICY_PARA *guest,
        const CERT_CHAIN_POLICY_PARA *host)
{
    guest->dwFlags = host->dwFlags;
    guest->pvExtraPolicyPara = (ULONG_PTR)host->pvExtraPolicyPara;
}

static inline void CERT_CHAIN_POLICY_PARA_g2h(CERT_CHAIN_POLICY_PARA *host,
        const struct qemu_CERT_CHAIN_POLICY_PARA *guest)
{
    host->cbSize = sizeof(*host);
    host->dwFlags = guest->dwFlags;
    host->pvExtraPolicyPara = (void *)(ULONG_PTR)guest->pvExtraPolicyPara;
}

struct qemu_CERT_TRUST_LIST_INFO
{
    DWORD           cbSize;
    qemu_ptr        pCtlEntry;
    qemu_ptr        pCtlContext;
};

struct qemu_CERT_CHAIN_ELEMENT
{
    DWORD                 cbSize;
    qemu_ptr              pCertContext;
    CERT_TRUST_STATUS     TrustStatus;
    qemu_ptr              pRevocationInfo;
    qemu_ptr              pIssuanceUsage;
    qemu_ptr              pApplicationUsage;
    qemu_ptr              pwszExtendedErrorInfo;
};

static inline void CERT_CHAIN_ELEMENT_h2g(struct qemu_CERT_CHAIN_ELEMENT *guest,
        const CERT_CHAIN_ELEMENT *host)
{
    guest->cbSize = sizeof(*guest);
    guest->pCertContext = (ULONG_PTR)host->pCertContext;
    guest->TrustStatus = host->TrustStatus;
    guest->pRevocationInfo = (ULONG_PTR)host->pRevocationInfo;
    guest->pIssuanceUsage = (ULONG_PTR)host->pIssuanceUsage;
    guest->pApplicationUsage = (ULONG_PTR)host->pApplicationUsage;
    guest->pwszExtendedErrorInfo = (ULONG_PTR)host->pwszExtendedErrorInfo;
}

struct qemu_CERT_SIMPLE_CHAIN
{
    DWORD                 cbSize;
    CERT_TRUST_STATUS     TrustStatus;
    DWORD                 cElement;
    qemu_ptr              rgpElement;
    qemu_ptr              pTrustListInfo;
    BOOL                  fHasRevocationFreshnessTime;
    DWORD                 dwRevocationFreshnessTime;
};

/* rgpElement and pTrustListInfo have to be handled by the caller. */
static inline void CERT_SIMPLE_CHAIN_h2g(struct qemu_CERT_SIMPLE_CHAIN *guest,
        const CERT_SIMPLE_CHAIN *host)
{
    guest->cbSize = sizeof(*guest);
    guest->TrustStatus = host->TrustStatus;
    guest->cElement = host->cElement;
    guest->rgpElement = (ULONG_PTR)host->rgpElement;
    guest->pTrustListInfo = (ULONG_PTR)host->pTrustListInfo;
    guest->fHasRevocationFreshnessTime = host->fHasRevocationFreshnessTime;
    guest->dwRevocationFreshnessTime = host->dwRevocationFreshnessTime;
}

struct qemu_CERT_CHAIN_CONTEXT
{
    DWORD                 cbSize;
    CERT_TRUST_STATUS     TrustStatus;
    DWORD                 cChain;
    qemu_ptr              rgpChain;
    DWORD                 cLowerQualityChainContext;
    qemu_ptr              rgpLowerQualityChainContext;
    BOOL                  fHasRevocationFreshnessTime;
    DWORD                 dwRevocationFreshnessTime;
};

/* rgpChain and rgpLowerQualityChainContext need to be handled by the caller. */
static inline void CERT_CHAIN_CONTEXT_h2g(struct qemu_CERT_CHAIN_CONTEXT *guest,
        const CERT_CHAIN_CONTEXT *host)
{
    guest->cbSize = sizeof(*guest);
    guest->TrustStatus = host->TrustStatus;
    guest->cChain = host->cChain;
    guest->cLowerQualityChainContext = host->cLowerQualityChainContext;
    guest->fHasRevocationFreshnessTime = host->fHasRevocationFreshnessTime;
    guest->dwRevocationFreshnessTime = host->dwRevocationFreshnessTime;
}

#endif
