#ifndef NTDLL_H
#define NTDLL_H

enum ntdll_calls
{
    CALL___C_SPECIFIC_HANDLER = 0,
    CALL___ISASCII,
    CALL___ISCSYM,
    CALL___ISCSYMF,
    CALL___TOASCII,
    CALL___WINE_DBG_GET_CHANNEL_FLAGS,
    CALL___WINE_DBG_HEADER,
    CALL___WINE_DBG_OUTPUT,
    CALL___WINE_DBG_STRDUP,
    CALL__ATOI64,
    CALL__I64TOA,
    CALL__I64TOW,
    CALL__ITOA,
    CALL__ITOW,
    CALL__LOCAL_UNWIND,
    CALL__LTOA,
    CALL__LTOW,
    CALL__MEMCCPY,
    CALL__MEMICMP,
    CALL__SNPRINTF_S,
    CALL__SPLITPATH,
    CALL__STRICMP,
    CALL__STRLWR,
    CALL__STRNICMP,
    CALL__STRUPR,
    CALL__TOLOWER,
    CALL__TOUPPER,
    CALL__UI64TOA,
    CALL__UI64TOW,
    CALL__ULTOA,
    CALL__ULTOW,
    CALL__VSNPRINTF_S,
    CALL__WCSICMP,
    CALL__WCSLWR,
    CALL__WCSNICMP,
    CALL__WCSUPR,
    CALL__WTOI,
    CALL__WTOI64,
    CALL__WTOL,
    CALL_ATOI,
    CALL_ATOL,
    CALL_ETWEVENTENABLED,
    CALL_ETWEVENTREGISTER,
    CALL_ETWEVENTSETINFORMATION,
    CALL_ETWEVENTUNREGISTER,
    CALL_ETWEVENTWRITE,
    CALL_ETWREGISTERTRACEGUIDSA,
    CALL_ETWREGISTERTRACEGUIDSW,
    CALL_ETWUNREGISTERTRACEGUIDS,
    CALL_ISALNUM,
    CALL_ISALPHA,
    CALL_ISCNTRL,
    CALL_ISDIGIT,
    CALL_ISGRAPH,
    CALL_ISLOWER,
    CALL_ISPRINT,
    CALL_ISPUNCT,
    CALL_ISSPACE,
    CALL_ISUPPER,
    CALL_ISWALPHA,
    CALL_ISWCTYPE,
    CALL_ISWDIGIT,
    CALL_ISWLOWER,
    CALL_ISWSPACE,
    CALL_ISWXDIGIT,
    CALL_ISXDIGIT,
    CALL_LDRACCESSRESOURCE,
    CALL_LDRADDREFDLL,
    CALL_LDRDISABLETHREADCALLOUTSFORDLL,
    CALL_LDRENUMERATELOADEDMODULES,
    CALL_LDRFINDENTRYFORADDRESS,
    CALL_LDRFINDRESOURCE_U,
    CALL_LDRFINDRESOURCEDIRECTORY_U,
    CALL_LDRGETDLLHANDLE,
    CALL_LDRGETPROCEDUREADDRESS,
    CALL_LDRINITIALIZETHUNK,
    CALL_LDRLOADDLL,
    CALL_LDRLOCKLOADERLOCK,
    CALL_LDRPROCESSRELOCATIONBLOCK,
    CALL_LDRQUERYIMAGEFILEEXECUTIONOPTIONS,
    CALL_LDRQUERYPROCESSMODULEINFORMATION,
    CALL_LDRREGISTERDLLNOTIFICATION,
    CALL_LDRRESOLVEDELAYLOADEDAPI,
    CALL_LDRSHUTDOWNPROCESS,
    CALL_LDRSHUTDOWNTHREAD,
    CALL_LDRUNLOADDLL,
    CALL_LDRUNLOCKLOADERLOCK,
    CALL_LDRUNREGISTERDLLNOTIFICATION,
    CALL_MBSTOWCS,
    CALL_MEMCHR,
    CALL_MEMCMP,
    CALL_MEMCPY,
    CALL_MEMMOVE,
    CALL_MEMSET,
    CALL_NTACCEPTCONNECTPORT,
    CALL_NTACCESSCHECK,
    CALL_NTACCESSCHECKANDAUDITALARM,
    CALL_NTADJUSTGROUPSTOKEN,
    CALL_NTADJUSTPRIVILEGESTOKEN,
    CALL_NTALERTRESUMETHREAD,
    CALL_NTALERTTHREAD,
    CALL_NTALLOCATELOCALLYUNIQUEID,
    CALL_NTALLOCATEUUIDS,
    CALL_NTASSIGNPROCESSTOJOBOBJECT,
    CALL_NTCANCELIOFILE,
    CALL_NTCANCELIOFILEEX,
    CALL_NTCANCELTIMER,
    CALL_NTCLEAREVENT,
    CALL_NTCLOSE,
    CALL_NTCOMPLETECONNECTPORT,
    CALL_NTCONNECTPORT,
    CALL_NTCREATEDIRECTORYOBJECT,
    CALL_NTCREATEEVENT,
    CALL_NTCREATEFILE,
    CALL_NTCREATEIOCOMPLETION,
    CALL_NTCREATEJOBOBJECT,
    CALL_NTCREATEKEY,
    CALL_NTCREATEKEYEDEVENT,
    CALL_NTCREATEKEYTRANSACTED,
    CALL_NTCREATEMAILSLOTFILE,
    CALL_NTCREATEMUTANT,
    CALL_NTCREATENAMEDPIPEFILE,
    CALL_NTCREATEPAGINGFILE,
    CALL_NTCREATEPORT,
    CALL_NTCREATESEMAPHORE,
    CALL_NTCREATESYMBOLICLINKOBJECT,
    CALL_NTCREATETIMER,
    CALL_NTDELAYEXECUTION,
    CALL_NTDELETEFILE,
    CALL_NTDELETEKEY,
    CALL_NTDELETEVALUEKEY,
    CALL_NTDEVICEIOCONTROLFILE,
    CALL_NTDISPLAYSTRING,
    CALL_NTDLL__SNPRINTF,
    CALL_NTDLL__SNWPRINTF,
    CALL_NTDLL__VSNPRINTF,
    CALL_NTDLL__VSNWPRINTF,
    CALL_NTDLL_SPRINTF,
    CALL_NTDLL_SWPRINTF,
    CALL_NTDLL_VSPRINTF,
    CALL_NTDUPLICATEOBJECT,
    CALL_NTDUPLICATETOKEN,
    CALL_NTENUMERATEKEY,
    CALL_NTENUMERATEVALUEKEY,
    CALL_NTFLUSHBUFFERSFILE,
    CALL_NTFLUSHINSTRUCTIONCACHE,
    CALL_NTFLUSHKEY,
    CALL_NTFSCONTROLFILE,
    CALL_NTGETCURRENTPROCESSORNUMBER,
    CALL_NTGETTICKCOUNT,
    CALL_NTIMPERSONATEANONYMOUSTOKEN,
    CALL_NTINITIATEPOWERACTION,
    CALL_NTISPROCESSINJOB,
    CALL_NTLISTENPORT,
    CALL_NTLOADDRIVER,
    CALL_NTLOADKEY,
    CALL_NTLOADKEY2,
    CALL_NTLOCKFILE,
    CALL_NTMAKETEMPORARYOBJECT,
    CALL_NTNOTIFYCHANGEDIRECTORYFILE,
    CALL_NTNOTIFYCHANGEKEY,
    CALL_NTNOTIFYCHANGEMULTIPLEKEYS,
    CALL_NTOPENDIRECTORYOBJECT,
    CALL_NTOPENEVENT,
    CALL_NTOPENFILE,
    CALL_NTOPENIOCOMPLETION,
    CALL_NTOPENJOBOBJECT,
    CALL_NTOPENKEY,
    CALL_NTOPENKEYEDEVENT,
    CALL_NTOPENKEYEX,
    CALL_NTOPENKEYTRANSACTED,
    CALL_NTOPENKEYTRANSACTEDEX,
    CALL_NTOPENMUTANT,
    CALL_NTOPENPROCESS,
    CALL_NTOPENPROCESSTOKEN,
    CALL_NTOPENPROCESSTOKENEX,
    CALL_NTOPENSEMAPHORE,
    CALL_NTOPENSYMBOLICLINKOBJECT,
    CALL_NTOPENTHREAD,
    CALL_NTOPENTHREADTOKEN,
    CALL_NTOPENTHREADTOKENEX,
    CALL_NTOPENTIMER,
    CALL_NTPOWERINFORMATION,
    CALL_NTPRIVILEGECHECK,
    CALL_NTPULSEEVENT,
    CALL_NTQUERYATTRIBUTESFILE,
    CALL_NTQUERYDEFAULTLOCALE,
    CALL_NTQUERYDEFAULTUILANGUAGE,
    CALL_NTQUERYDIRECTORYFILE,
    CALL_NTQUERYDIRECTORYOBJECT,
    CALL_NTQUERYEAFILE,
    CALL_NTQUERYEVENT,
    CALL_NTQUERYFULLATTRIBUTESFILE,
    CALL_NTQUERYINFORMATIONFILE,
    CALL_NTQUERYINFORMATIONJOBOBJECT,
    CALL_NTQUERYINFORMATIONPROCESS,
    CALL_NTQUERYINFORMATIONTHREAD,
    CALL_NTQUERYINFORMATIONTOKEN,
    CALL_NTQUERYINSTALLUILANGUAGE,
    CALL_NTQUERYIOCOMPLETION,
    CALL_NTQUERYKEY,
    CALL_NTQUERYLICENSEVALUE,
    CALL_NTQUERYMULTIPLEVALUEKEY,
    CALL_NTQUERYMUTANT,
    CALL_NTQUERYOBJECT,
    CALL_NTQUERYPERFORMANCECOUNTER,
    CALL_NTQUERYSECURITYOBJECT,
    CALL_NTQUERYSEMAPHORE,
    CALL_NTQUERYSYMBOLICLINKOBJECT,
    CALL_NTQUERYSYSTEMENVIRONMENTVALUE,
    CALL_NTQUERYSYSTEMENVIRONMENTVALUEEX,
    CALL_NTQUERYSYSTEMINFORMATION,
    CALL_NTQUERYSYSTEMINFORMATIONEX,
    CALL_NTQUERYSYSTEMTIME,
    CALL_NTQUERYTIMER,
    CALL_NTQUERYTIMERRESOLUTION,
    CALL_NTQUERYVALUEKEY,
    CALL_NTQUERYVOLUMEINFORMATIONFILE,
    CALL_NTQUEUEAPCTHREAD,
    CALL_NTRAISEEXCEPTION,
    CALL_NTRAISEHARDERROR,
    CALL_NTREADFILE,
    CALL_NTREADFILESCATTER,
    CALL_NTREGISTERTHREADTERMINATEPORT,
    CALL_NTRELEASEKEYEDEVENT,
    CALL_NTRELEASEMUTANT,
    CALL_NTRELEASESEMAPHORE,
    CALL_NTREMOVEIOCOMPLETION,
    CALL_NTRENAMEKEY,
    CALL_NTREPLACEKEY,
    CALL_NTREPLYWAITRECEIVEPORT,
    CALL_NTREQUESTWAITREPLYPORT,
    CALL_NTRESETEVENT,
    CALL_NTRESTOREKEY,
    CALL_NTRESUMEPROCESS,
    CALL_NTRESUMETHREAD,
    CALL_NTSAVEKEY,
    CALL_NTSECURECONNECTPORT,
    CALL_NTSETCONTEXTTHREAD,
    CALL_NTSETDEFAULTLOCALE,
    CALL_NTSETDEFAULTUILANGUAGE,
    CALL_NTSETEAFILE,
    CALL_NTSETEVENT,
    CALL_NTSETINFORMATIONFILE,
    CALL_NTSETINFORMATIONJOBOBJECT,
    CALL_NTSETINFORMATIONKEY,
    CALL_NTSETINFORMATIONOBJECT,
    CALL_NTSETINFORMATIONPROCESS,
    CALL_NTSETINFORMATIONTHREAD,
    CALL_NTSETINFORMATIONTOKEN,
    CALL_NTSETINTERVALPROFILE,
    CALL_NTSETIOCOMPLETION,
    CALL_NTSETLDTENTRIES,
    CALL_NTSETSECURITYOBJECT,
    CALL_NTSETSYSTEMINFORMATION,
    CALL_NTSETSYSTEMTIME,
    CALL_NTSETTIMER,
    CALL_NTSETTIMERRESOLUTION,
    CALL_NTSETVALUEKEY,
    CALL_NTSETVOLUMEINFORMATIONFILE,
    CALL_NTSHUTDOWNSYSTEM,
    CALL_NTSIGNALANDWAITFORSINGLEOBJECT,
    CALL_NTSUSPENDPROCESS,
    CALL_NTSUSPENDTHREAD,
    CALL_NTSYSTEMDEBUGCONTROL,
    CALL_NTTERMINATEJOBOBJECT,
    CALL_NTTERMINATEPROCESS,
    CALL_NTTERMINATETHREAD,
    CALL_NTUNLOADDRIVER,
    CALL_NTUNLOADKEY,
    CALL_NTUNLOCKFILE,
    CALL_NTWAITFORKEYEDEVENT,
    CALL_NTWAITFORMULTIPLEOBJECTS,
    CALL_NTWAITFORSINGLEOBJECT,
    CALL_NTWRITEFILE,
    CALL_NTWRITEFILEGATHER,
    CALL_NTYIELDEXECUTION,
    CALL_RTLABSOLUTETOSELFRELATIVESD,
    CALL_RTLACQUIREPEBLOCK,
    CALL_RTLACQUIRERESOURCEEXCLUSIVE,
    CALL_RTLACQUIRERESOURCESHARED,
    CALL_RTLACQUIRESRWLOCKEXCLUSIVE,
    CALL_RTLACQUIRESRWLOCKSHARED,
    CALL_RTLACTIVATEACTIVATIONCONTEXT,
    CALL_RTLADDACCESSALLOWEDACE,
    CALL_RTLADDACCESSALLOWEDACEEX,
    CALL_RTLADDACCESSALLOWEDOBJECTACE,
    CALL_RTLADDACCESSDENIEDACE,
    CALL_RTLADDACCESSDENIEDACEEX,
    CALL_RTLADDACCESSDENIEDOBJECTACE,
    CALL_RTLADDACE,
    CALL_RTLADDAUDITACCESSACE,
    CALL_RTLADDAUDITACCESSACEEX,
    CALL_RTLADDAUDITACCESSOBJECTACE,
    CALL_RTLADDFUNCTIONTABLE,
    CALL_RTLADDMANDATORYACE,
    CALL_RTLADDREFACTIVATIONCONTEXT,
    CALL_RTLADDVECTOREDCONTINUEHANDLER,
    CALL_RTLADDVECTOREDEXCEPTIONHANDLER,
    CALL_RTLADJUSTPRIVILEGE,
    CALL_RTLALLOCATEANDINITIALIZESID,
    CALL_RTLALLOCATEHEAP,
    CALL_RTLANSICHARTOUNICODECHAR,
    CALL_RTLANSISTRINGTOUNICODESIZE,
    CALL_RTLANSISTRINGTOUNICODESTRING,
    CALL_RTLAPPENDASCIIZTOSTRING,
    CALL_RTLAPPENDSTRINGTOSTRING,
    CALL_RTLAPPENDUNICODESTRINGTOSTRING,
    CALL_RTLAPPENDUNICODETOSTRING,
    CALL_RTLAREALLACCESSESGRANTED,
    CALL_RTLAREANYACCESSESGRANTED,
    CALL_RTLAREBITSCLEAR,
    CALL_RTLAREBITSSET,
    CALL_RTLASSERT,
    CALL_RTLCAPTURESTACKBACKTRACE,
    CALL_RTLCHARTOINTEGER,
    CALL_RTLCHECKREGISTRYKEY,
    CALL_RTLCLEARALLBITS,
    CALL_RTLCLEARBITS,
    CALL_RTLCOMPACTHEAP,
    CALL_RTLCOMPAREMEMORY,
    CALL_RTLCOMPAREMEMORYULONG,
    CALL_RTLCOMPARESTRING,
    CALL_RTLCOMPAREUNICODESTRING,
    CALL_RTLCOMPAREUNICODESTRINGS,
    CALL_RTLCOMPRESSBUFFER,
    CALL_RTLCOMPUTECRC32,
    CALL_RTLCONVERTSIDTOUNICODESTRING,
    CALL_RTLCONVERTTOAUTOINHERITSECURITYOBJECT,
    CALL_RTLCOPYLUID,
    CALL_RTLCOPYLUIDANDATTRIBUTESARRAY,
    CALL_RTLCOPYMEMORY,
    CALL_RTLCOPYSECURITYDESCRIPTOR,
    CALL_RTLCOPYSID,
    CALL_RTLCOPYSTRING,
    CALL_RTLCOPYUNICODESTRING,
    CALL_RTLCREATEACL,
    CALL_RTLCREATEACTIVATIONCONTEXT,
    CALL_RTLCREATEENVIRONMENT,
    CALL_RTLCREATEHEAP,
    CALL_RTLCREATEPROCESSPARAMETERS,
    CALL_RTLCREATEPROCESSPARAMETERSEX,
    CALL_RTLCREATESECURITYDESCRIPTOR,
    CALL_RTLCREATETIMER,
    CALL_RTLCREATETIMERQUEUE,
    CALL_RTLCREATEUNICODESTRING,
    CALL_RTLCREATEUNICODESTRINGFROMASCIIZ,
    CALL_RTLCREATEUSERPROCESS,
    CALL_RTLCREATEUSERTHREAD,
    CALL_RTLDEACTIVATEACTIVATIONCONTEXT,
    CALL_RTLDECODEPOINTER,
    CALL_RTLDECOMPRESSBUFFER,
    CALL_RTLDECOMPRESSFRAGMENT,
    CALL_RTLDELETEACE,
    CALL_RTLDELETECRITICALSECTION,
    CALL_RTLDELETEFUNCTIONTABLE,
    CALL_RTLDELETEREGISTRYVALUE,
    CALL_RTLDELETERESOURCE,
    CALL_RTLDELETESECURITYOBJECT,
    CALL_RTLDELETETIMER,
    CALL_RTLDELETETIMERQUEUEEX,
    CALL_RTLDENORMALIZEPROCESSPARAMS,
    CALL_RTLDEREGISTERWAIT,
    CALL_RTLDEREGISTERWAITEX,
    CALL_RTLDESTROYENVIRONMENT,
    CALL_RTLDESTROYHEAP,
    CALL_RTLDESTROYPROCESSPARAMETERS,
    CALL_RTLDETERMINEDOSPATHNAMETYPE_U,
    CALL_RTLDLLSHUTDOWNINPROGRESS,
    CALL_RTLDOESFILEEXISTS_U,
    CALL_RTLDOSPATHNAMETONTPATHNAME_U,
    CALL_RTLDOSSEARCHPATH_U,
    CALL_RTLDOWNCASEUNICODECHAR,
    CALL_RTLDOWNCASEUNICODESTRING,
    CALL_RTLDUMPRESOURCE,
    CALL_RTLDUPLICATEUNICODESTRING,
    CALL_RTLENCODEPOINTER,
    CALL_RTLENTERCRITICALSECTION,
    CALL_RTLEQUALCOMPUTERNAME,
    CALL_RTLEQUALDOMAINNAME,
    CALL_RTLEQUALLUID,
    CALL_RTLEQUALPREFIXSID,
    CALL_RTLEQUALSID,
    CALL_RTLEQUALSTRING,
    CALL_RTLEQUALUNICODESTRING,
    CALL_RTLERASEUNICODESTRING,
    CALL_RTLEXITUSERPROCESS,
    CALL_RTLEXPANDENVIRONMENTSTRINGS,
    CALL_RTLEXPANDENVIRONMENTSTRINGS_U,
    CALL_RTLFILLMEMORY,
    CALL_RTLFILLMEMORYULONG,
    CALL_RTLFINDACTIVATIONCONTEXTSECTIONGUID,
    CALL_RTLFINDACTIVATIONCONTEXTSECTIONSTRING,
    CALL_RTLFINDCHARINUNICODESTRING,
    CALL_RTLFINDCLEARBITS,
    CALL_RTLFINDCLEARBITSANDSET,
    CALL_RTLFINDCLEARRUNS,
    CALL_RTLFINDLASTBACKWARDRUNCLEAR,
    CALL_RTLFINDLASTBACKWARDRUNSET,
    CALL_RTLFINDLEASTSIGNIFICANTBIT,
    CALL_RTLFINDLONGESTRUNCLEAR,
    CALL_RTLFINDLONGESTRUNSET,
    CALL_RTLFINDMESSAGE,
    CALL_RTLFINDMOSTSIGNIFICANTBIT,
    CALL_RTLFINDNEXTFORWARDRUNCLEAR,
    CALL_RTLFINDNEXTFORWARDRUNSET,
    CALL_RTLFINDSETBITS,
    CALL_RTLFINDSETBITSANDCLEAR,
    CALL_RTLFINDSETRUNS,
    CALL_RTLFIRSTENTRYSLIST,
    CALL_RTLFIRSTFREEACE,
    CALL_RTLFORMATCURRENTUSERKEYPATH,
    CALL_RTLFORMATMESSAGE,
    CALL_RTLFREEANSISTRING,
    CALL_RTLFREEHEAP,
    CALL_RTLFREEOEMSTRING,
    CALL_RTLFREESID,
    CALL_RTLFREETHREADACTIVATIONCONTEXTSTACK,
    CALL_RTLFREEUNICODESTRING,
    CALL_RTLGETACE,
    CALL_RTLGETACTIVEACTIVATIONCONTEXT,
    CALL_RTLGETCOMPRESSIONWORKSPACESIZE,
    CALL_RTLGETCONTROLSECURITYDESCRIPTOR,
    CALL_RTLGETCURRENTDIRECTORY_U,
    CALL_RTLGETCURRENTPEB,
    CALL_RTLGETCURRENTPROCESSORNUMBEREX,
    CALL_RTLGETCURRENTTRANSACTION,
    CALL_RTLGETDACLSECURITYDESCRIPTOR,
    CALL_RTLGETFULLPATHNAME_U,
    CALL_RTLGETGROUPSECURITYDESCRIPTOR,
    CALL_RTLGETLASTNTSTATUS,
    CALL_RTLGETLASTWIN32ERROR,
    CALL_RTLGETLONGESTNTPATHLENGTH,
    CALL_RTLGETNTGLOBALFLAGS,
    CALL_RTLGETNTPRODUCTTYPE,
    CALL_RTLGETNTVERSIONNUMBERS,
    CALL_RTLGETOWNERSECURITYDESCRIPTOR,
    CALL_RTLGETPROCESSHEAPS,
    CALL_RTLGETPRODUCTINFO,
    CALL_RTLGETSACLSECURITYDESCRIPTOR,
    CALL_RTLGETTHREADERRORMODE,
    CALL_RTLGETUNLOADEVENTTRACE,
    CALL_RTLGETUNLOADEVENTTRACEEX,
    CALL_RTLGETVERSION,
    CALL_RTLGUIDFROMSTRING,
    CALL_RTLHASHUNICODESTRING,
    CALL_RTLIDENTIFIERAUTHORITYSID,
    CALL_RTLIMPERSONATESELF,
    CALL_RTLINITANSISTRING,
    CALL_RTLINITANSISTRINGEX,
    CALL_RTLINITIALIZEBITMAP,
    CALL_RTLINITIALIZECONDITIONVARIABLE,
    CALL_RTLINITIALIZECRITICALSECTION,
    CALL_RTLINITIALIZECRITICALSECTIONANDSPINCOUNT,
    CALL_RTLINITIALIZECRITICALSECTIONEX,
    CALL_RTLINITIALIZEGENERICTABLE,
    CALL_RTLINITIALIZEGENERICTABLEAVL,
    CALL_RTLINITIALIZERESOURCE,
    CALL_RTLINITIALIZESID,
    CALL_RTLINITIALIZESLISTHEAD,
    CALL_RTLINITIALIZESRWLOCK,
    CALL_RTLINITSTRING,
    CALL_RTLINITUNICODESTRING,
    CALL_RTLINITUNICODESTRINGEX,
    CALL_RTLINSERTELEMENTGENERICTABLEAVL,
    CALL_RTLINTEGERTOCHAR,
    CALL_RTLINTEGERTOUNICODESTRING,
    CALL_RTLINTERLOCKEDFLUSHSLIST,
    CALL_RTLINTERLOCKEDPOPENTRYSLIST,
    CALL_RTLINTERLOCKEDPUSHENTRYSLIST,
    CALL_RTLINTERLOCKEDPUSHLISTSLIST,
    CALL_RTLINTERLOCKEDPUSHLISTSLISTEX,
    CALL_RTLIPV4ADDRESSTOSTRINGA,
    CALL_RTLIPV4ADDRESSTOSTRINGEXA,
    CALL_RTLIPV4ADDRESSTOSTRINGEXW,
    CALL_RTLIPV4ADDRESSTOSTRINGW,
    CALL_RTLIPV4STRINGTOADDRESSEXW,
    CALL_RTLISACTIVATIONCONTEXTACTIVE,
    CALL_RTLISCRITICALSECTIONLOCKED,
    CALL_RTLISCRITICALSECTIONLOCKEDBYTHREAD,
    CALL_RTLISDOSDEVICENAME_U,
    CALL_RTLISNAMELEGALDOS8DOT3,
    CALL_RTLISTEXTUNICODE,
    CALL_RTLLEAVECRITICALSECTION,
    CALL_RTLLENGTHREQUIREDSID,
    CALL_RTLLENGTHSECURITYDESCRIPTOR,
    CALL_RTLLENGTHSID,
    CALL_RTLLOCALTIMETOSYSTEMTIME,
    CALL_RTLLOCKHEAP,
    CALL_RTLLOOKUPFUNCTIONENTRY,
    CALL_RTLMAKESELFRELATIVESD,
    CALL_RTLMAPGENERICMASK,
    CALL_RTLMOVEMEMORY,
    CALL_RTLMULTIBYTETOUNICODEN,
    CALL_RTLMULTIBYTETOUNICODESIZE,
    CALL_RTLNEWSECURITYOBJECT,
    CALL_RTLNORMALIZEPROCESSPARAMS,
    CALL_RTLNTSTATUSTODOSERROR,
    CALL_RTLNTSTATUSTODOSERRORNOTEB,
    CALL_RTLNUMBEROFCLEARBITS,
    CALL_RTLNUMBEROFSETBITS,
    CALL_RTLOEMSTRINGTOUNICODESIZE,
    CALL_RTLOEMSTRINGTOUNICODESTRING,
    CALL_RTLOEMTOUNICODEN,
    CALL_RTLOPENCURRENTUSER,
    CALL_RTLPCTOFILEHEADER,
    CALL_RTLPNTCREATEKEY,
    CALL_RTLPNTENUMERATESUBKEY,
    CALL_RTLPNTMAKETEMPORARYKEY,
    CALL_RTLPNTOPENKEY,
    CALL_RTLPNTQUERYVALUEKEY,
    CALL_RTLPNTSETVALUEKEY,
    CALL_RTLPREFIXSTRING,
    CALL_RTLPREFIXUNICODESTRING,
    CALL_RTLPUNWAITCRITICALSECTION,
    CALL_RTLPWAITFORCRITICALSECTION,
    CALL_RTLQUERYDEPTHSLIST,
    CALL_RTLQUERYDYNAMICTIMEZONEINFORMATION,
    CALL_RTLQUERYENVIRONMENTVARIABLE_U,
    CALL_RTLQUERYHEAPINFORMATION,
    CALL_RTLQUERYINFORMATIONACL,
    CALL_RTLQUERYINFORMATIONACTIVATIONCONTEXT,
    CALL_RTLQUERYREGISTRYVALUES,
    CALL_RTLQUERYTIMEZONEINFORMATION,
    CALL_RTLQUERYUNBIASEDINTERRUPTTIME,
    CALL_RTLQUEUEWORKITEM,
    CALL_RTLRAISESTATUS,
    CALL_RTLRANDOM,
    CALL_RTLREALLOCATEHEAP,
    CALL_RTLREGISTERWAIT,
    CALL_RTLRELEASEACTIVATIONCONTEXT,
    CALL_RTLRELEASEPEBLOCK,
    CALL_RTLRELEASERESOURCE,
    CALL_RTLRELEASESRWLOCKEXCLUSIVE,
    CALL_RTLRELEASESRWLOCKSHARED,
    CALL_RTLREMOVEVECTOREDCONTINUEHANDLER,
    CALL_RTLREMOVEVECTOREDEXCEPTIONHANDLER,
    CALL_RTLRESTORECONTEXT,
    CALL_RTLRUNONCEBEGININITIALIZE,
    CALL_RTLRUNONCECOMPLETE,
    CALL_RTLRUNONCEEXECUTEONCE,
    CALL_RTLRUNONCEINITIALIZE,
    CALL_RTLSECONDSSINCE1970TOTIME,
    CALL_RTLSECONDSSINCE1980TOTIME,
    CALL_RTLSELFRELATIVETOABSOLUTESD,
    CALL_RTLSETALLBITS,
    CALL_RTLSETBITS,
    CALL_RTLSETCONTROLSECURITYDESCRIPTOR,
    CALL_RTLSETCRITICALSECTIONSPINCOUNT,
    CALL_RTLSETCURRENTDIRECTORY_U,
    CALL_RTLSETCURRENTENVIRONMENT,
    CALL_RTLSETCURRENTTRANSACTION,
    CALL_RTLSETDACLSECURITYDESCRIPTOR,
    CALL_RTLSETENVIRONMENTVARIABLE,
    CALL_RTLSETGROUPSECURITYDESCRIPTOR,
    CALL_RTLSETHEAPINFORMATION,
    CALL_RTLSETIOCOMPLETIONCALLBACK,
    CALL_RTLSETLASTWIN32ERROR,
    CALL_RTLSETLASTWIN32ERRORANDNTSTATUSFROMNTSTATUS,
    CALL_RTLSETOWNERSECURITYDESCRIPTOR,
    CALL_RTLSETSACLSECURITYDESCRIPTOR,
    CALL_RTLSETTHREADERRORMODE,
    CALL_RTLSETTIMEZONEINFORMATION,
    CALL_RTLSIZEHEAP,
    CALL_RTLSLEEPCONDITIONVARIABLECS,
    CALL_RTLSLEEPCONDITIONVARIABLESRW,
    CALL_RTLSTRINGFROMGUID,
    CALL_RTLSUBAUTHORITYCOUNTSID,
    CALL_RTLSUBAUTHORITYSID,
    CALL_RTLSYSTEMTIMETOLOCALTIME,
    CALL_RTLTIMEFIELDSTOTIME,
    CALL_RTLTIMETOELAPSEDTIMEFIELDS,
    CALL_RTLTIMETOSECONDSSINCE1970,
    CALL_RTLTIMETOSECONDSSINCE1980,
    CALL_RTLTIMETOTIMEFIELDS,
    CALL_RTLTRYACQUIRESRWLOCKEXCLUSIVE,
    CALL_RTLTRYACQUIRESRWLOCKSHARED,
    CALL_RTLTRYENTERCRITICALSECTION,
    CALL_RTLUNICODESTRINGTOANSISIZE,
    CALL_RTLUNICODESTRINGTOANSISTRING,
    CALL_RTLUNICODESTRINGTOINTEGER,
    CALL_RTLUNICODESTRINGTOOEMSIZE,
    CALL_RTLUNICODESTRINGTOOEMSTRING,
    CALL_RTLUNICODETOMULTIBYTEN,
    CALL_RTLUNICODETOMULTIBYTESIZE,
    CALL_RTLUNICODETOOEMN,
    CALL_RTLUNIFORM,
    CALL_RTLUNLOCKHEAP,
    CALL_RTLUNWINDEX,
    CALL_RTLUPCASEUNICODECHAR,
    CALL_RTLUPCASEUNICODESTRING,
    CALL_RTLUPCASEUNICODESTRINGTOANSISTRING,
    CALL_RTLUPCASEUNICODESTRINGTOCOUNTEDOEMSTRING,
    CALL_RTLUPCASEUNICODESTRINGTOOEMSTRING,
    CALL_RTLUPCASEUNICODETOMULTIBYTEN,
    CALL_RTLUPCASEUNICODETOOEMN,
    CALL_RTLUPDATETIMER,
    CALL_RTLUPPERCHAR,
    CALL_RTLUPPERSTRING,
    CALL_RTLVALIDACL,
    CALL_RTLVALIDATEHEAP,
    CALL_RTLVALIDRELATIVESECURITYDESCRIPTOR,
    CALL_RTLVALIDSECURITYDESCRIPTOR,
    CALL_RTLVALIDSID,
    CALL_RTLVERIFYVERSIONINFO,
    CALL_RTLVIRTUALUNWIND,
    CALL_RTLWAKEALLCONDITIONVARIABLE,
    CALL_RTLWAKECONDITIONVARIABLE,
    CALL_RTLWALKHEAP,
    CALL_RTLWOW64ENABLEFSREDIRECTION,
    CALL_RTLWOW64ENABLEFSREDIRECTIONEX,
    CALL_RTLWRITEREGISTRYVALUE,
    CALL_RTLZEROMEMORY,
    CALL_RTLZOMBIFYACTIVATIONCONTEXT,
    CALL_SET_CALLBACKS,
    CALL_STRCAT,
    CALL_STRCHR,
    CALL_STRCMP,
    CALL_STRCPY,
    CALL_STRCSPN,
    CALL_STRLEN,
    CALL_STRNCAT,
    CALL_STRNCMP,
    CALL_STRNCPY,
    CALL_STRPBRK,
    CALL_STRRCHR,
    CALL_STRSPN,
    CALL_STRSTR,
    CALL_STRTOL,
    CALL_STRTOUL,
    CALL_TOLOWER,
    CALL_TOUPPER,
    CALL_TOWLOWER,
    CALL_TOWUPPER,
    CALL_TPALLOCCLEANUPGROUP,
    CALL_TPALLOCPOOL,
    CALL_TPALLOCTIMER,
    CALL_TPALLOCWAIT,
    CALL_TPALLOCWORK,
    CALL_TPCALLBACKLEAVECRITICALSECTIONONCOMPLETION,
    CALL_TPCALLBACKMAYRUNLONG,
    CALL_TPCALLBACKRELEASEMUTEXONCOMPLETION,
    CALL_TPCALLBACKRELEASESEMAPHOREONCOMPLETION,
    CALL_TPCALLBACKSETEVENTONCOMPLETION,
    CALL_TPCALLBACKUNLOADDLLONCOMPLETION,
    CALL_TPDISASSOCIATECALLBACK,
    CALL_TPISTIMERSET,
    CALL_TPPOSTWORK,
    CALL_TPRELEASECLEANUPGROUP,
    CALL_TPRELEASECLEANUPGROUPMEMBERS,
    CALL_TPRELEASEPOOL,
    CALL_TPRELEASETIMER,
    CALL_TPRELEASEWAIT,
    CALL_TPRELEASEWORK,
    CALL_TPSETPOOLMAXTHREADS,
    CALL_TPSETPOOLMINTHREADS,
    CALL_TPSETTIMER,
    CALL_TPSETWAIT,
    CALL_TPSIMPLETRYPOST,
    CALL_TPWAITFORTIMER,
    CALL_TPWAITFORWAIT,
    CALL_TPWAITFORWORK,
    CALL_VERSETCONDITIONMASK,
    CALL_WCSCAT,
    CALL_WCSCHR,
    CALL_WCSCMP,
    CALL_WCSCPY,
    CALL_WCSCSPN,
    CALL_WCSLEN,
    CALL_WCSNCAT,
    CALL_WCSNCMP,
    CALL_WCSNCPY,
    CALL_WCSPBRK,
    CALL_WCSRCHR,
    CALL_WCSSPN,
    CALL_WCSSTR,
    CALL_WCSTOK,
    CALL_WCSTOL,
    CALL_WCSTOMBS,
    CALL_WCSTOUL,
    CALL_WINSQMENDSESSION,
    CALL_WINSQMISOPTEDIN,
    CALL_WINSQMSTARTSESSION,
};

#ifdef QEMU_DLL_GUEST

typedef void LDR_MODULE;
NTSTATUS WINAPI ntdll_LdrFindEntryForAddress(const void *addr, LDR_MODULE **mod);
PVOID WINAPI ntdll_RtlImageDirectoryEntryToData( HMODULE module, BOOL image, WORD dir, ULONG *size );
NTSTATUS WINAPI ntdll_NtTerminateProcess(HANDLE handle, LONG exit_code);
NTSTATUS WINAPI ntdll_NtCreateKeyedEvent(HANDLE *handle, ACCESS_MASK access, const OBJECT_ATTRIBUTES *attr, ULONG flags);
PVOID WINAPI ntdll_RtlAllocateHeap(HANDLE heap, ULONG flags, SIZE_T size);
BOOLEAN WINAPI ntdll_RtlFreeHeap(HANDLE heap, ULONG flags, PVOID ptr);

extern HANDLE keyed_event;

#ifdef _WIN64
PRUNTIME_FUNCTION NTAPI ntdll_RtlLookupFunctionEntry(DWORD64 pc, DWORD64 *base, UNWIND_HISTORY_TABLE *history);
PEXCEPTION_ROUTINE WINAPI ntdll_RtlVirtualUnwind(DWORD type, DWORD64 base, DWORD64 pc,
        PRUNTIME_FUNCTION function, PCONTEXT context, PVOID *data, PDWORD64 frame_ret,
        PKNONVOLATILE_CONTEXT_POINTERS ctx_ptr);
#endif

void __fastcall qemu_exception_handler(EXCEPTION_POINTERS *except);

#else

extern const struct qemu_ops *qemu_ops;

void qemu___C_specific_handler(struct qemu_syscall *call);
void qemu___isascii(struct qemu_syscall *call);
void qemu___iscsym(struct qemu_syscall *call);
void qemu___iscsymf(struct qemu_syscall *call);
void qemu___toascii(struct qemu_syscall *call);
void qemu___wine_dbg_get_channel_flags(struct qemu_syscall *call);
void qemu___wine_dbg_header(struct qemu_syscall *call);
void qemu___wine_dbg_output(struct qemu_syscall *call);
void qemu___wine_dbg_strdup(struct qemu_syscall *call);
void qemu__atoi64(struct qemu_syscall *call);
void qemu__i64toa(struct qemu_syscall *call);
void qemu__i64tow(struct qemu_syscall *call);
void qemu__itoa(struct qemu_syscall *call);
void qemu__itow(struct qemu_syscall *call);
void qemu__local_unwind(struct qemu_syscall *call);
void qemu__ltoa(struct qemu_syscall *call);
void qemu__ltow(struct qemu_syscall *call);
void qemu__memccpy(struct qemu_syscall *call);
void qemu__memicmp(struct qemu_syscall *call);
void qemu__snprintf_s(struct qemu_syscall *call);
void qemu__splitpath(struct qemu_syscall *call);
void qemu__stricmp(struct qemu_syscall *call);
void qemu__strlwr(struct qemu_syscall *call);
void qemu__strnicmp(struct qemu_syscall *call);
void qemu__strupr(struct qemu_syscall *call);
void qemu__tolower(struct qemu_syscall *call);
void qemu__toupper(struct qemu_syscall *call);
void qemu__ui64toa(struct qemu_syscall *call);
void qemu__ui64tow(struct qemu_syscall *call);
void qemu__ultoa(struct qemu_syscall *call);
void qemu__ultow(struct qemu_syscall *call);
void qemu__vsnprintf_s(struct qemu_syscall *call);
void qemu__wcsicmp(struct qemu_syscall *call);
void qemu__wcslwr(struct qemu_syscall *call);
void qemu__wcsnicmp(struct qemu_syscall *call);
void qemu__wcsupr(struct qemu_syscall *call);
void qemu__wtoi(struct qemu_syscall *call);
void qemu__wtoi64(struct qemu_syscall *call);
void qemu__wtol(struct qemu_syscall *call);
void qemu_atoi(struct qemu_syscall *call);
void qemu_atol(struct qemu_syscall *call);
void qemu_EtwEventEnabled(struct qemu_syscall *call);
void qemu_EtwEventRegister(struct qemu_syscall *call);
void qemu_EtwEventSetInformation(struct qemu_syscall *call);
void qemu_EtwEventUnregister(struct qemu_syscall *call);
void qemu_EtwEventWrite(struct qemu_syscall *call);
void qemu_EtwRegisterTraceGuidsA(struct qemu_syscall *call);
void qemu_EtwRegisterTraceGuidsW(struct qemu_syscall *call);
void qemu_EtwUnregisterTraceGuids(struct qemu_syscall *call);
void qemu_isalnum(struct qemu_syscall *call);
void qemu_isalpha(struct qemu_syscall *call);
void qemu_iscntrl(struct qemu_syscall *call);
void qemu_isdigit(struct qemu_syscall *call);
void qemu_isgraph(struct qemu_syscall *call);
void qemu_islower(struct qemu_syscall *call);
void qemu_isprint(struct qemu_syscall *call);
void qemu_ispunct(struct qemu_syscall *call);
void qemu_isspace(struct qemu_syscall *call);
void qemu_isupper(struct qemu_syscall *call);
void qemu_iswalpha(struct qemu_syscall *call);
void qemu_iswctype(struct qemu_syscall *call);
void qemu_iswdigit(struct qemu_syscall *call);
void qemu_iswlower(struct qemu_syscall *call);
void qemu_iswspace(struct qemu_syscall *call);
void qemu_iswxdigit(struct qemu_syscall *call);
void qemu_isxdigit(struct qemu_syscall *call);
void qemu_LdrAccessResource(struct qemu_syscall *call);
void qemu_LdrAddRefDll(struct qemu_syscall *call);
void qemu_LdrDisableThreadCalloutsForDll(struct qemu_syscall *call);
void qemu_LdrEnumerateLoadedModules(struct qemu_syscall *call);
void qemu_LdrFindEntryForAddress(struct qemu_syscall *call);
void qemu_LdrFindResource_U(struct qemu_syscall *call);
void qemu_LdrFindResourceDirectory_U(struct qemu_syscall *call);
void qemu_LdrGetDllHandle(struct qemu_syscall *call);
void qemu_LdrGetProcedureAddress(struct qemu_syscall *call);
void qemu_LdrInitializeThunk(struct qemu_syscall *call);
void qemu_LdrLoadDll(struct qemu_syscall *call);
void qemu_LdrLockLoaderLock(struct qemu_syscall *call);
void qemu_LdrProcessRelocationBlock(struct qemu_syscall *call);
void qemu_LdrQueryImageFileExecutionOptions(struct qemu_syscall *call);
void qemu_LdrQueryProcessModuleInformation(struct qemu_syscall *call);
void qemu_LdrRegisterDllNotification(struct qemu_syscall *call);
void qemu_LdrResolveDelayLoadedAPI(struct qemu_syscall *call);
void qemu_LdrShutdownProcess(struct qemu_syscall *call);
void qemu_LdrShutdownThread(struct qemu_syscall *call);
void qemu_LdrUnloadDll(struct qemu_syscall *call);
void qemu_LdrUnlockLoaderLock(struct qemu_syscall *call);
void qemu_LdrUnregisterDllNotification(struct qemu_syscall *call);
void qemu_mbstowcs(struct qemu_syscall *call);
void qemu_memchr(struct qemu_syscall *call);
void qemu_memcmp(struct qemu_syscall *call);
void qemu_memcpy(struct qemu_syscall *call);
void qemu_memmove(struct qemu_syscall *call);
void qemu_memset(struct qemu_syscall *call);
void qemu_NtAcceptConnectPort(struct qemu_syscall *call);
void qemu_NtAccessCheck(struct qemu_syscall *call);
void qemu_NtAccessCheckAndAuditAlarm(struct qemu_syscall *call);
void qemu_NtAdjustGroupsToken(struct qemu_syscall *call);
void qemu_NtAdjustPrivilegesToken(struct qemu_syscall *call);
void qemu_NtAlertResumeThread(struct qemu_syscall *call);
void qemu_NtAlertThread(struct qemu_syscall *call);
void qemu_NtAllocateLocallyUniqueId(struct qemu_syscall *call);
void qemu_NtAllocateUuids(struct qemu_syscall *call);
void qemu_NtAssignProcessToJobObject(struct qemu_syscall *call);
void qemu_NtCancelIoFile(struct qemu_syscall *call);
void qemu_NtCancelIoFileEx(struct qemu_syscall *call);
void qemu_NtCancelTimer(struct qemu_syscall *call);
void qemu_NtClearEvent(struct qemu_syscall *call);
void qemu_NtClose(struct qemu_syscall *call);
void qemu_NtCompleteConnectPort(struct qemu_syscall *call);
void qemu_NtConnectPort(struct qemu_syscall *call);
void qemu_NtCreateDirectoryObject(struct qemu_syscall *call);
void qemu_NtCreateEvent(struct qemu_syscall *call);
void qemu_NtCreateFile(struct qemu_syscall *call);
void qemu_NtCreateIoCompletion(struct qemu_syscall *call);
void qemu_NtCreateJobObject(struct qemu_syscall *call);
void qemu_NtCreateKey(struct qemu_syscall *call);
void qemu_NtCreateKeyedEvent(struct qemu_syscall *call);
void qemu_NtCreateKeyTransacted(struct qemu_syscall *call);
void qemu_NtCreateMailslotFile(struct qemu_syscall *call);
void qemu_NtCreateMutant(struct qemu_syscall *call);
void qemu_NtCreateNamedPipeFile(struct qemu_syscall *call);
void qemu_NtCreatePagingFile(struct qemu_syscall *call);
void qemu_NtCreatePort(struct qemu_syscall *call);
void qemu_NtCreateSemaphore(struct qemu_syscall *call);
void qemu_NtCreateSymbolicLinkObject(struct qemu_syscall *call);
void qemu_NtCreateTimer(struct qemu_syscall *call);
void qemu_NtDelayExecution(struct qemu_syscall *call);
void qemu_NtDeleteFile(struct qemu_syscall *call);
void qemu_NtDeleteKey(struct qemu_syscall *call);
void qemu_NtDeleteValueKey(struct qemu_syscall *call);
void qemu_NtDeviceIoControlFile(struct qemu_syscall *call);
void qemu_NtDisplayString(struct qemu_syscall *call);
void qemu_NTDLL__snwprintf(struct qemu_syscall *call);
void qemu_NTDLL__vsnwprintf(struct qemu_syscall *call);
void qemu_NTDLL_swprintf(struct qemu_syscall *call);
void qemu_NtDuplicateObject(struct qemu_syscall *call);
void qemu_NtDuplicateToken(struct qemu_syscall *call);
void qemu_NtEnumerateKey(struct qemu_syscall *call);
void qemu_NtEnumerateValueKey(struct qemu_syscall *call);
void qemu_NtFlushBuffersFile(struct qemu_syscall *call);
void qemu_NtFlushInstructionCache(struct qemu_syscall *call);
void qemu_NtFlushKey(struct qemu_syscall *call);
void qemu_NtFsControlFile(struct qemu_syscall *call);
void qemu_NtGetCurrentProcessorNumber(struct qemu_syscall *call);
void qemu_NtGetTickCount(struct qemu_syscall *call);
void qemu_NtImpersonateAnonymousToken(struct qemu_syscall *call);
void qemu_NtInitiatePowerAction(struct qemu_syscall *call);
void qemu_NtIsProcessInJob(struct qemu_syscall *call);
void qemu_NtListenPort(struct qemu_syscall *call);
void qemu_NtLoadDriver(struct qemu_syscall *call);
void qemu_NtLoadKey(struct qemu_syscall *call);
void qemu_NtLoadKey2(struct qemu_syscall *call);
void qemu_NtLockFile(struct qemu_syscall *call);
void qemu_NtMakeTemporaryObject(struct qemu_syscall *call);
void qemu_NtNotifyChangeDirectoryFile(struct qemu_syscall *call);
void qemu_NtNotifyChangeKey(struct qemu_syscall *call);
void qemu_NtNotifyChangeMultipleKeys(struct qemu_syscall *call);
void qemu_NtOpenDirectoryObject(struct qemu_syscall *call);
void qemu_NtOpenEvent(struct qemu_syscall *call);
void qemu_NtOpenFile(struct qemu_syscall *call);
void qemu_NtOpenIoCompletion(struct qemu_syscall *call);
void qemu_NtOpenJobObject(struct qemu_syscall *call);
void qemu_NtOpenKey(struct qemu_syscall *call);
void qemu_NtOpenKeyedEvent(struct qemu_syscall *call);
void qemu_NtOpenKeyEx(struct qemu_syscall *call);
void qemu_NtOpenKeyTransacted(struct qemu_syscall *call);
void qemu_NtOpenKeyTransactedEx(struct qemu_syscall *call);
void qemu_NtOpenMutant(struct qemu_syscall *call);
void qemu_NtOpenProcess(struct qemu_syscall *call);
void qemu_NtOpenProcessToken(struct qemu_syscall *call);
void qemu_NtOpenProcessTokenEx(struct qemu_syscall *call);
void qemu_NtOpenSemaphore(struct qemu_syscall *call);
void qemu_NtOpenSymbolicLinkObject(struct qemu_syscall *call);
void qemu_NtOpenThread(struct qemu_syscall *call);
void qemu_NtOpenThreadToken(struct qemu_syscall *call);
void qemu_NtOpenThreadTokenEx(struct qemu_syscall *call);
void qemu_NtOpenTimer(struct qemu_syscall *call);
void qemu_NtPowerInformation(struct qemu_syscall *call);
void qemu_NtPrivilegeCheck(struct qemu_syscall *call);
void qemu_NtPulseEvent(struct qemu_syscall *call);
void qemu_NtQueryAttributesFile(struct qemu_syscall *call);
void qemu_NtQueryDefaultLocale(struct qemu_syscall *call);
void qemu_NtQueryDefaultUILanguage(struct qemu_syscall *call);
void qemu_NtQueryDirectoryFile(struct qemu_syscall *call);
void qemu_NtQueryDirectoryObject(struct qemu_syscall *call);
void qemu_NtQueryEaFile(struct qemu_syscall *call);
void qemu_NtQueryEvent(struct qemu_syscall *call);
void qemu_NtQueryFullAttributesFile(struct qemu_syscall *call);
void qemu_NtQueryInformationFile(struct qemu_syscall *call);
void qemu_NtQueryInformationJobObject(struct qemu_syscall *call);
void qemu_NtQueryInformationProcess(struct qemu_syscall *call);
void qemu_NtQueryInformationThread(struct qemu_syscall *call);
void qemu_NtQueryInformationToken(struct qemu_syscall *call);
void qemu_NtQueryInstallUILanguage(struct qemu_syscall *call);
void qemu_NtQueryIoCompletion(struct qemu_syscall *call);
void qemu_NtQueryKey(struct qemu_syscall *call);
void qemu_NtQueryLicenseValue(struct qemu_syscall *call);
void qemu_NtQueryMultipleValueKey(struct qemu_syscall *call);
void qemu_NtQueryMutant(struct qemu_syscall *call);
void qemu_NtQueryObject(struct qemu_syscall *call);
void qemu_NtQueryPerformanceCounter(struct qemu_syscall *call);
void qemu_NtQuerySecurityObject(struct qemu_syscall *call);
void qemu_NtQuerySemaphore(struct qemu_syscall *call);
void qemu_NtQuerySymbolicLinkObject(struct qemu_syscall *call);
void qemu_NtQuerySystemEnvironmentValue(struct qemu_syscall *call);
void qemu_NtQuerySystemEnvironmentValueEx(struct qemu_syscall *call);
void qemu_NtQuerySystemInformation(struct qemu_syscall *call);
void qemu_NtQuerySystemInformationEx(struct qemu_syscall *call);
void qemu_NtQuerySystemTime(struct qemu_syscall *call);
void qemu_NtQueryTimer(struct qemu_syscall *call);
void qemu_NtQueryTimerResolution(struct qemu_syscall *call);
void qemu_NtQueryValueKey(struct qemu_syscall *call);
void qemu_NtQueryVolumeInformationFile(struct qemu_syscall *call);
void qemu_NtQueueApcThread(struct qemu_syscall *call);
void qemu_NtRaiseException(struct qemu_syscall *call);
void qemu_NtRaiseHardError(struct qemu_syscall *call);
void qemu_NtReadFile(struct qemu_syscall *call);
void qemu_NtReadFileScatter(struct qemu_syscall *call);
void qemu_NtRegisterThreadTerminatePort(struct qemu_syscall *call);
void qemu_NtReleaseKeyedEvent(struct qemu_syscall *call);
void qemu_NtReleaseMutant(struct qemu_syscall *call);
void qemu_NtReleaseSemaphore(struct qemu_syscall *call);
void qemu_NtRemoveIoCompletion(struct qemu_syscall *call);
void qemu_NtRenameKey(struct qemu_syscall *call);
void qemu_NtReplaceKey(struct qemu_syscall *call);
void qemu_NtReplyWaitReceivePort(struct qemu_syscall *call);
void qemu_NtRequestWaitReplyPort(struct qemu_syscall *call);
void qemu_NtResetEvent(struct qemu_syscall *call);
void qemu_NtRestoreKey(struct qemu_syscall *call);
void qemu_NtResumeProcess(struct qemu_syscall *call);
void qemu_NtResumeThread(struct qemu_syscall *call);
void qemu_NtSaveKey(struct qemu_syscall *call);
void qemu_NtSecureConnectPort(struct qemu_syscall *call);
void qemu_NtSetContextThread(struct qemu_syscall *call);
void qemu_NtSetDefaultLocale(struct qemu_syscall *call);
void qemu_NtSetDefaultUILanguage(struct qemu_syscall *call);
void qemu_NtSetEaFile(struct qemu_syscall *call);
void qemu_NtSetEvent(struct qemu_syscall *call);
void qemu_NtSetInformationFile(struct qemu_syscall *call);
void qemu_NtSetInformationJobObject(struct qemu_syscall *call);
void qemu_NtSetInformationKey(struct qemu_syscall *call);
void qemu_NtSetInformationObject(struct qemu_syscall *call);
void qemu_NtSetInformationProcess(struct qemu_syscall *call);
void qemu_NtSetInformationThread(struct qemu_syscall *call);
void qemu_NtSetInformationToken(struct qemu_syscall *call);
void qemu_NtSetIntervalProfile(struct qemu_syscall *call);
void qemu_NtSetIoCompletion(struct qemu_syscall *call);
void qemu_NtSetLdtEntries(struct qemu_syscall *call);
void qemu_NtSetSecurityObject(struct qemu_syscall *call);
void qemu_NtSetSystemInformation(struct qemu_syscall *call);
void qemu_NtSetSystemTime(struct qemu_syscall *call);
void qemu_NtSetTimer(struct qemu_syscall *call);
void qemu_NtSetTimerResolution(struct qemu_syscall *call);
void qemu_NtSetValueKey(struct qemu_syscall *call);
void qemu_NtSetVolumeInformationFile(struct qemu_syscall *call);
void qemu_NtShutdownSystem(struct qemu_syscall *call);
void qemu_NtSignalAndWaitForSingleObject(struct qemu_syscall *call);
void qemu_NtSuspendProcess(struct qemu_syscall *call);
void qemu_NtSuspendThread(struct qemu_syscall *call);
void qemu_NtSystemDebugControl(struct qemu_syscall *call);
void qemu_NtTerminateJobObject(struct qemu_syscall *call);
void qemu_NtTerminateProcess(struct qemu_syscall *call);
void qemu_NtTerminateThread(struct qemu_syscall *call);
void qemu_NtUnloadDriver(struct qemu_syscall *call);
void qemu_NtUnloadKey(struct qemu_syscall *call);
void qemu_NtUnlockFile(struct qemu_syscall *call);
void qemu_NtWaitForKeyedEvent(struct qemu_syscall *call);
void qemu_NtWaitForMultipleObjects(struct qemu_syscall *call);
void qemu_NtWaitForSingleObject(struct qemu_syscall *call);
void qemu_NtWriteFile(struct qemu_syscall *call);
void qemu_NtWriteFileGather(struct qemu_syscall *call);
void qemu_NtYieldExecution(struct qemu_syscall *call);
void qemu_RtlAbsoluteToSelfRelativeSD(struct qemu_syscall *call);
void qemu_RtlAcquirePebLock(struct qemu_syscall *call);
void qemu_RtlAcquireResourceExclusive(struct qemu_syscall *call);
void qemu_RtlAcquireResourceShared(struct qemu_syscall *call);
void qemu_RtlAcquireSRWLockExclusive(struct qemu_syscall *call);
void qemu_RtlAcquireSRWLockShared(struct qemu_syscall *call);
void qemu_RtlActivateActivationContext(struct qemu_syscall *call);
void qemu_RtlAddAccessAllowedAce(struct qemu_syscall *call);
void qemu_RtlAddAccessAllowedAceEx(struct qemu_syscall *call);
void qemu_RtlAddAccessAllowedObjectAce(struct qemu_syscall *call);
void qemu_RtlAddAccessDeniedAce(struct qemu_syscall *call);
void qemu_RtlAddAccessDeniedAceEx(struct qemu_syscall *call);
void qemu_RtlAddAccessDeniedObjectAce(struct qemu_syscall *call);
void qemu_RtlAddAce(struct qemu_syscall *call);
void qemu_RtlAddAuditAccessAce(struct qemu_syscall *call);
void qemu_RtlAddAuditAccessAceEx(struct qemu_syscall *call);
void qemu_RtlAddAuditAccessObjectAce(struct qemu_syscall *call);
void qemu_RtlAddFunctionTable(struct qemu_syscall *call);
void qemu_RtlAddMandatoryAce(struct qemu_syscall *call);
void qemu_RtlAddRefActivationContext(struct qemu_syscall *call);
void qemu_RtlAddVectoredContinueHandler(struct qemu_syscall *call);
void qemu_RtlAddVectoredExceptionHandler(struct qemu_syscall *call);
void qemu_RtlAdjustPrivilege(struct qemu_syscall *call);
void qemu_RtlAllocateAndInitializeSid(struct qemu_syscall *call);
void qemu_RtlAllocateHeap(struct qemu_syscall *call);
void qemu_RtlAnsiCharToUnicodeChar(struct qemu_syscall *call);
void qemu_RtlAnsiStringToUnicodeSize(struct qemu_syscall *call);
void qemu_RtlAnsiStringToUnicodeString(struct qemu_syscall *call);
void qemu_RtlAppendAsciizToString(struct qemu_syscall *call);
void qemu_RtlAppendStringToString(struct qemu_syscall *call);
void qemu_RtlAppendUnicodeStringToString(struct qemu_syscall *call);
void qemu_RtlAppendUnicodeToString(struct qemu_syscall *call);
void qemu_RtlAreAllAccessesGranted(struct qemu_syscall *call);
void qemu_RtlAreAnyAccessesGranted(struct qemu_syscall *call);
void qemu_RtlAreBitsClear(struct qemu_syscall *call);
void qemu_RtlAreBitsSet(struct qemu_syscall *call);
void qemu_RtlAssert(struct qemu_syscall *call);
void qemu_RtlCaptureStackBackTrace(struct qemu_syscall *call);
void qemu_RtlCharToInteger(struct qemu_syscall *call);
void qemu_RtlCheckRegistryKey(struct qemu_syscall *call);
void qemu_RtlClearAllBits(struct qemu_syscall *call);
void qemu_RtlClearBits(struct qemu_syscall *call);
void qemu_RtlCompactHeap(struct qemu_syscall *call);
void qemu_RtlCompareMemory(struct qemu_syscall *call);
void qemu_RtlCompareMemoryUlong(struct qemu_syscall *call);
void qemu_RtlCompareString(struct qemu_syscall *call);
void qemu_RtlCompareUnicodeString(struct qemu_syscall *call);
void qemu_RtlCompareUnicodeStrings(struct qemu_syscall *call);
void qemu_RtlCompressBuffer(struct qemu_syscall *call);
void qemu_RtlComputeCrc32(struct qemu_syscall *call);
void qemu_RtlConvertSidToUnicodeString(struct qemu_syscall *call);
void qemu_RtlConvertToAutoInheritSecurityObject(struct qemu_syscall *call);
void qemu_RtlCopyLuid(struct qemu_syscall *call);
void qemu_RtlCopyLuidAndAttributesArray(struct qemu_syscall *call);
void qemu_RtlCopyMemory(struct qemu_syscall *call);
void qemu_RtlCopySecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlCopySid(struct qemu_syscall *call);
void qemu_RtlCopyString(struct qemu_syscall *call);
void qemu_RtlCopyUnicodeString(struct qemu_syscall *call);
void qemu_RtlCreateAcl(struct qemu_syscall *call);
void qemu_RtlCreateActivationContext(struct qemu_syscall *call);
void qemu_RtlCreateEnvironment(struct qemu_syscall *call);
void qemu_RtlCreateHeap(struct qemu_syscall *call);
void qemu_RtlCreateProcessParameters(struct qemu_syscall *call);
void qemu_RtlCreateProcessParametersEx(struct qemu_syscall *call);
void qemu_RtlCreateSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlCreateTimer(struct qemu_syscall *call);
void qemu_RtlCreateTimerQueue(struct qemu_syscall *call);
void qemu_RtlCreateUnicodeString(struct qemu_syscall *call);
void qemu_RtlCreateUnicodeStringFromAsciiz(struct qemu_syscall *call);
void qemu_RtlCreateUserProcess(struct qemu_syscall *call);
void qemu_RtlCreateUserThread(struct qemu_syscall *call);
void qemu_RtlDeactivateActivationContext(struct qemu_syscall *call);
void qemu_RtlDecodePointer(struct qemu_syscall *call);
void qemu_RtlDecompressBuffer(struct qemu_syscall *call);
void qemu_RtlDecompressFragment(struct qemu_syscall *call);
void qemu_RtlDeleteAce(struct qemu_syscall *call);
void qemu_RtlDeleteCriticalSection(struct qemu_syscall *call);
void qemu_RtlDeleteFunctionTable(struct qemu_syscall *call);
void qemu_RtlDeleteRegistryValue(struct qemu_syscall *call);
void qemu_RtlDeleteResource(struct qemu_syscall *call);
void qemu_RtlDeleteSecurityObject(struct qemu_syscall *call);
void qemu_RtlDeleteTimer(struct qemu_syscall *call);
void qemu_RtlDeleteTimerQueueEx(struct qemu_syscall *call);
void qemu_RtlDeNormalizeProcessParams(struct qemu_syscall *call);
void qemu_RtlDeregisterWait(struct qemu_syscall *call);
void qemu_RtlDeregisterWaitEx(struct qemu_syscall *call);
void qemu_RtlDestroyEnvironment(struct qemu_syscall *call);
void qemu_RtlDestroyHeap(struct qemu_syscall *call);
void qemu_RtlDestroyProcessParameters(struct qemu_syscall *call);
void qemu_RtlDetermineDosPathNameType_U(struct qemu_syscall *call);
void qemu_RtlDllShutdownInProgress(struct qemu_syscall *call);
void qemu_RtlDoesFileExists_U(struct qemu_syscall *call);
void qemu_RtlDosPathNameToNtPathName_U(struct qemu_syscall *call);
void qemu_RtlDosSearchPath_U(struct qemu_syscall *call);
void qemu_RtlDowncaseUnicodeChar(struct qemu_syscall *call);
void qemu_RtlDowncaseUnicodeString(struct qemu_syscall *call);
void qemu_RtlDumpResource(struct qemu_syscall *call);
void qemu_RtlDuplicateUnicodeString(struct qemu_syscall *call);
void qemu_RtlEncodePointer(struct qemu_syscall *call);
void qemu_RtlEnterCriticalSection(struct qemu_syscall *call);
void qemu_RtlEqualComputerName(struct qemu_syscall *call);
void qemu_RtlEqualDomainName(struct qemu_syscall *call);
void qemu_RtlEqualLuid(struct qemu_syscall *call);
void qemu_RtlEqualPrefixSid(struct qemu_syscall *call);
void qemu_RtlEqualSid(struct qemu_syscall *call);
void qemu_RtlEqualString(struct qemu_syscall *call);
void qemu_RtlEqualUnicodeString(struct qemu_syscall *call);
void qemu_RtlEraseUnicodeString(struct qemu_syscall *call);
void qemu_RtlExitUserProcess(struct qemu_syscall *call);
void qemu_RtlExpandEnvironmentStrings(struct qemu_syscall *call);
void qemu_RtlExpandEnvironmentStrings_U(struct qemu_syscall *call);
void qemu_RtlFillMemory(struct qemu_syscall *call);
void qemu_RtlFillMemoryUlong(struct qemu_syscall *call);
void qemu_RtlFindActivationContextSectionGuid(struct qemu_syscall *call);
void qemu_RtlFindActivationContextSectionString(struct qemu_syscall *call);
void qemu_RtlFindCharInUnicodeString(struct qemu_syscall *call);
void qemu_RtlFindClearBits(struct qemu_syscall *call);
void qemu_RtlFindClearBitsAndSet(struct qemu_syscall *call);
void qemu_RtlFindClearRuns(struct qemu_syscall *call);
void qemu_RtlFindLastBackwardRunClear(struct qemu_syscall *call);
void qemu_RtlFindLastBackwardRunSet(struct qemu_syscall *call);
void qemu_RtlFindLeastSignificantBit(struct qemu_syscall *call);
void qemu_RtlFindLongestRunClear(struct qemu_syscall *call);
void qemu_RtlFindLongestRunSet(struct qemu_syscall *call);
void qemu_RtlFindMessage(struct qemu_syscall *call);
void qemu_RtlFindMostSignificantBit(struct qemu_syscall *call);
void qemu_RtlFindNextForwardRunClear(struct qemu_syscall *call);
void qemu_RtlFindNextForwardRunSet(struct qemu_syscall *call);
void qemu_RtlFindSetBits(struct qemu_syscall *call);
void qemu_RtlFindSetBitsAndClear(struct qemu_syscall *call);
void qemu_RtlFindSetRuns(struct qemu_syscall *call);
void qemu_RtlFirstEntrySList(struct qemu_syscall *call);
void qemu_RtlFirstFreeAce(struct qemu_syscall *call);
void qemu_RtlFormatCurrentUserKeyPath(struct qemu_syscall *call);
void qemu_RtlFormatMessage(struct qemu_syscall *call);
void qemu_RtlFreeAnsiString(struct qemu_syscall *call);
void qemu_RtlFreeHeap(struct qemu_syscall *call);
void qemu_RtlFreeOemString(struct qemu_syscall *call);
void qemu_RtlFreeSid(struct qemu_syscall *call);
void qemu_RtlFreeThreadActivationContextStack(struct qemu_syscall *call);
void qemu_RtlFreeUnicodeString(struct qemu_syscall *call);
void qemu_RtlGetAce(struct qemu_syscall *call);
void qemu_RtlGetActiveActivationContext(struct qemu_syscall *call);
void qemu_RtlGetCompressionWorkSpaceSize(struct qemu_syscall *call);
void qemu_RtlGetControlSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlGetCurrentDirectory_U(struct qemu_syscall *call);
void qemu_RtlGetCurrentPeb(struct qemu_syscall *call);
void qemu_RtlGetCurrentProcessorNumberEx(struct qemu_syscall *call);
void qemu_RtlGetCurrentTransaction(struct qemu_syscall *call);
void qemu_RtlGetDaclSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlGetFullPathName_U(struct qemu_syscall *call);
void qemu_RtlGetGroupSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlGetLastNtStatus(struct qemu_syscall *call);
void qemu_RtlGetLastWin32Error(struct qemu_syscall *call);
void qemu_RtlGetLongestNtPathLength(struct qemu_syscall *call);
void qemu_RtlGetNtGlobalFlags(struct qemu_syscall *call);
void qemu_RtlGetNtProductType(struct qemu_syscall *call);
void qemu_RtlGetNtVersionNumbers(struct qemu_syscall *call);
void qemu_RtlGetOwnerSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlGetProcessHeaps(struct qemu_syscall *call);
void qemu_RtlGetProductInfo(struct qemu_syscall *call);
void qemu_RtlGetSaclSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlGetThreadErrorMode(struct qemu_syscall *call);
void qemu_RtlGetUnloadEventTrace(struct qemu_syscall *call);
void qemu_RtlGetUnloadEventTraceEx(struct qemu_syscall *call);
void qemu_RtlGetVersion(struct qemu_syscall *call);
void qemu_RtlGUIDFromString(struct qemu_syscall *call);
void qemu_RtlHashUnicodeString(struct qemu_syscall *call);
void qemu_RtlIdentifierAuthoritySid(struct qemu_syscall *call);
void qemu_RtlImpersonateSelf(struct qemu_syscall *call);
void qemu_RtlInitAnsiString(struct qemu_syscall *call);
void qemu_RtlInitAnsiStringEx(struct qemu_syscall *call);
void qemu_RtlInitializeBitMap(struct qemu_syscall *call);
void qemu_RtlInitializeConditionVariable(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSection(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSectionAndSpinCount(struct qemu_syscall *call);
void qemu_RtlInitializeCriticalSectionEx(struct qemu_syscall *call);
void qemu_RtlInitializeGenericTable(struct qemu_syscall *call);
void qemu_RtlInitializeGenericTableAvl(struct qemu_syscall *call);
void qemu_RtlInitializeResource(struct qemu_syscall *call);
void qemu_RtlInitializeSid(struct qemu_syscall *call);
void qemu_RtlInitializeSListHead(struct qemu_syscall *call);
void qemu_RtlInitializeSRWLock(struct qemu_syscall *call);
void qemu_RtlInitString(struct qemu_syscall *call);
void qemu_RtlInitUnicodeString(struct qemu_syscall *call);
void qemu_RtlInitUnicodeStringEx(struct qemu_syscall *call);
void qemu_RtlInsertElementGenericTableAvl(struct qemu_syscall *call);
void qemu_RtlIntegerToChar(struct qemu_syscall *call);
void qemu_RtlIntegerToUnicodeString(struct qemu_syscall *call);
void qemu_RtlInterlockedFlushSList(struct qemu_syscall *call);
void qemu_RtlInterlockedPopEntrySList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushEntrySList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushListSList(struct qemu_syscall *call);
void qemu_RtlInterlockedPushListSListEx(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringA(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringExA(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringExW(struct qemu_syscall *call);
void qemu_RtlIpv4AddressToStringW(struct qemu_syscall *call);
void qemu_RtlIpv4StringToAddressExW(struct qemu_syscall *call);
void qemu_RtlIsActivationContextActive(struct qemu_syscall *call);
void qemu_RtlIsCriticalSectionLocked(struct qemu_syscall *call);
void qemu_RtlIsCriticalSectionLockedByThread(struct qemu_syscall *call);
void qemu_RtlIsDosDeviceName_U(struct qemu_syscall *call);
void qemu_RtlIsNameLegalDOS8Dot3(struct qemu_syscall *call);
void qemu_RtlIsTextUnicode(struct qemu_syscall *call);
void qemu_RtlLeaveCriticalSection(struct qemu_syscall *call);
void qemu_RtlLengthRequiredSid(struct qemu_syscall *call);
void qemu_RtlLengthSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlLengthSid(struct qemu_syscall *call);
void qemu_RtlLocalTimeToSystemTime(struct qemu_syscall *call);
void qemu_RtlLockHeap(struct qemu_syscall *call);
void qemu_RtlLookupFunctionEntry(struct qemu_syscall *call);
void qemu_RtlMakeSelfRelativeSD(struct qemu_syscall *call);
void qemu_RtlMapGenericMask(struct qemu_syscall *call);
void qemu_RtlMoveMemory(struct qemu_syscall *call);
void qemu_RtlMultiByteToUnicodeN(struct qemu_syscall *call);
void qemu_RtlMultiByteToUnicodeSize(struct qemu_syscall *call);
void qemu_RtlNewSecurityObject(struct qemu_syscall *call);
void qemu_RtlNormalizeProcessParams(struct qemu_syscall *call);
void qemu_RtlNtStatusToDosError(struct qemu_syscall *call);
void qemu_RtlNtStatusToDosErrorNoTeb(struct qemu_syscall *call);
void qemu_RtlNumberOfClearBits(struct qemu_syscall *call);
void qemu_RtlNumberOfSetBits(struct qemu_syscall *call);
void qemu_RtlOemStringToUnicodeSize(struct qemu_syscall *call);
void qemu_RtlOemStringToUnicodeString(struct qemu_syscall *call);
void qemu_RtlOemToUnicodeN(struct qemu_syscall *call);
void qemu_RtlOpenCurrentUser(struct qemu_syscall *call);
void qemu_RtlPcToFileHeader(struct qemu_syscall *call);
void qemu_RtlpNtCreateKey(struct qemu_syscall *call);
void qemu_RtlpNtEnumerateSubKey(struct qemu_syscall *call);
void qemu_RtlpNtMakeTemporaryKey(struct qemu_syscall *call);
void qemu_RtlpNtOpenKey(struct qemu_syscall *call);
void qemu_RtlpNtQueryValueKey(struct qemu_syscall *call);
void qemu_RtlpNtSetValueKey(struct qemu_syscall *call);
void qemu_RtlPrefixString(struct qemu_syscall *call);
void qemu_RtlPrefixUnicodeString(struct qemu_syscall *call);
void qemu_RtlpUnWaitCriticalSection(struct qemu_syscall *call);
void qemu_RtlpWaitForCriticalSection(struct qemu_syscall *call);
void qemu_RtlQueryDepthSList(struct qemu_syscall *call);
void qemu_RtlQueryDynamicTimeZoneInformation(struct qemu_syscall *call);
void qemu_RtlQueryEnvironmentVariable_U(struct qemu_syscall *call);
void qemu_RtlQueryHeapInformation(struct qemu_syscall *call);
void qemu_RtlQueryInformationAcl(struct qemu_syscall *call);
void qemu_RtlQueryInformationActivationContext(struct qemu_syscall *call);
void qemu_RtlQueryRegistryValues(struct qemu_syscall *call);
void qemu_RtlQueryTimeZoneInformation(struct qemu_syscall *call);
void qemu_RtlQueryUnbiasedInterruptTime(struct qemu_syscall *call);
void qemu_RtlQueueWorkItem(struct qemu_syscall *call);
void qemu_RtlRaiseStatus(struct qemu_syscall *call);
void qemu_RtlRandom(struct qemu_syscall *call);
void qemu_RtlReAllocateHeap(struct qemu_syscall *call);
void qemu_RtlRegisterWait(struct qemu_syscall *call);
void qemu_RtlReleaseActivationContext(struct qemu_syscall *call);
void qemu_RtlReleasePebLock(struct qemu_syscall *call);
void qemu_RtlReleaseResource(struct qemu_syscall *call);
void qemu_RtlReleaseSRWLockExclusive(struct qemu_syscall *call);
void qemu_RtlReleaseSRWLockShared(struct qemu_syscall *call);
void qemu_RtlRemoveVectoredContinueHandler(struct qemu_syscall *call);
void qemu_RtlRemoveVectoredExceptionHandler(struct qemu_syscall *call);
void qemu_RtlRestoreContext(struct qemu_syscall *call);
void qemu_RtlRunOnceBeginInitialize(struct qemu_syscall *call);
void qemu_RtlRunOnceComplete(struct qemu_syscall *call);
void qemu_RtlRunOnceExecuteOnce(struct qemu_syscall *call);
void qemu_RtlRunOnceInitialize(struct qemu_syscall *call);
void qemu_RtlSecondsSince1970ToTime(struct qemu_syscall *call);
void qemu_RtlSecondsSince1980ToTime(struct qemu_syscall *call);
void qemu_RtlSelfRelativeToAbsoluteSD(struct qemu_syscall *call);
void qemu_RtlSetAllBits(struct qemu_syscall *call);
void qemu_RtlSetBits(struct qemu_syscall *call);
void qemu_RtlSetControlSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlSetCriticalSectionSpinCount(struct qemu_syscall *call);
void qemu_RtlSetCurrentDirectory_U(struct qemu_syscall *call);
void qemu_RtlSetCurrentEnvironment(struct qemu_syscall *call);
void qemu_RtlSetCurrentTransaction(struct qemu_syscall *call);
void qemu_RtlSetDaclSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlSetEnvironmentVariable(struct qemu_syscall *call);
void qemu_RtlSetGroupSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlSetHeapInformation(struct qemu_syscall *call);
void qemu_RtlSetIoCompletionCallback(struct qemu_syscall *call);
void qemu_RtlSetLastWin32Error(struct qemu_syscall *call);
void qemu_RtlSetLastWin32ErrorAndNtStatusFromNtStatus(struct qemu_syscall *call);
void qemu_RtlSetOwnerSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlSetSaclSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlSetThreadErrorMode(struct qemu_syscall *call);
void qemu_RtlSetTimeZoneInformation(struct qemu_syscall *call);
void qemu_RtlSizeHeap(struct qemu_syscall *call);
void qemu_RtlSleepConditionVariableCS(struct qemu_syscall *call);
void qemu_RtlSleepConditionVariableSRW(struct qemu_syscall *call);
void qemu_RtlStringFromGUID(struct qemu_syscall *call);
void qemu_RtlSubAuthorityCountSid(struct qemu_syscall *call);
void qemu_RtlSubAuthoritySid(struct qemu_syscall *call);
void qemu_RtlSystemTimeToLocalTime(struct qemu_syscall *call);
void qemu_RtlTimeFieldsToTime(struct qemu_syscall *call);
void qemu_RtlTimeToElapsedTimeFields(struct qemu_syscall *call);
void qemu_RtlTimeToSecondsSince1970(struct qemu_syscall *call);
void qemu_RtlTimeToSecondsSince1980(struct qemu_syscall *call);
void qemu_RtlTimeToTimeFields(struct qemu_syscall *call);
void qemu_RtlTryAcquireSRWLockExclusive(struct qemu_syscall *call);
void qemu_RtlTryAcquireSRWLockShared(struct qemu_syscall *call);
void qemu_RtlTryEnterCriticalSection(struct qemu_syscall *call);
void qemu_RtlUnicodeStringToAnsiSize(struct qemu_syscall *call);
void qemu_RtlUnicodeStringToAnsiString(struct qemu_syscall *call);
void qemu_RtlUnicodeStringToInteger(struct qemu_syscall *call);
void qemu_RtlUnicodeStringToOemSize(struct qemu_syscall *call);
void qemu_RtlUnicodeStringToOemString(struct qemu_syscall *call);
void qemu_RtlUnicodeToMultiByteN(struct qemu_syscall *call);
void qemu_RtlUnicodeToMultiByteSize(struct qemu_syscall *call);
void qemu_RtlUnicodeToOemN(struct qemu_syscall *call);
void qemu_RtlUniform(struct qemu_syscall *call);
void qemu_RtlUnlockHeap(struct qemu_syscall *call);
void qemu_RtlUnwindEx(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeChar(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeString(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeStringToAnsiString(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeStringToCountedOemString(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeStringToOemString(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeToMultiByteN(struct qemu_syscall *call);
void qemu_RtlUpcaseUnicodeToOemN(struct qemu_syscall *call);
void qemu_RtlUpdateTimer(struct qemu_syscall *call);
void qemu_RtlUpperChar(struct qemu_syscall *call);
void qemu_RtlUpperString(struct qemu_syscall *call);
void qemu_RtlValidAcl(struct qemu_syscall *call);
void qemu_RtlValidateHeap(struct qemu_syscall *call);
void qemu_RtlValidRelativeSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlValidSecurityDescriptor(struct qemu_syscall *call);
void qemu_RtlValidSid(struct qemu_syscall *call);
void qemu_RtlVerifyVersionInfo(struct qemu_syscall *call);
void qemu_RtlVirtualUnwind(struct qemu_syscall *call);
void qemu_RtlWakeAllConditionVariable(struct qemu_syscall *call);
void qemu_RtlWakeConditionVariable(struct qemu_syscall *call);
void qemu_RtlWalkHeap(struct qemu_syscall *call);
void qemu_RtlWow64EnableFsRedirection(struct qemu_syscall *call);
void qemu_RtlWow64EnableFsRedirectionEx(struct qemu_syscall *call);
void qemu_RtlWriteRegistryValue(struct qemu_syscall *call);
void qemu_RtlZeroMemory(struct qemu_syscall *call);
void qemu_RtlZombifyActivationContext(struct qemu_syscall *call);
void qemu_sprintf(struct qemu_syscall *call);
void qemu_strcat(struct qemu_syscall *call);
void qemu_strchr(struct qemu_syscall *call);
void qemu_strcmp(struct qemu_syscall *call);
void qemu_strcpy(struct qemu_syscall *call);
void qemu_strcspn(struct qemu_syscall *call);
void qemu_strlen(struct qemu_syscall *call);
void qemu_strncat(struct qemu_syscall *call);
void qemu_strncmp(struct qemu_syscall *call);
void qemu_strncpy(struct qemu_syscall *call);
void qemu_strpbrk(struct qemu_syscall *call);
void qemu_strrchr(struct qemu_syscall *call);
void qemu_strspn(struct qemu_syscall *call);
void qemu_strstr(struct qemu_syscall *call);
void qemu_strtol(struct qemu_syscall *call);
void qemu_strtoul(struct qemu_syscall *call);
void qemu_tolower(struct qemu_syscall *call);
void qemu_toupper(struct qemu_syscall *call);
void qemu_towlower(struct qemu_syscall *call);
void qemu_towupper(struct qemu_syscall *call);
void qemu_TpAllocCleanupGroup(struct qemu_syscall *call);
void qemu_TpAllocPool(struct qemu_syscall *call);
void qemu_TpAllocTimer(struct qemu_syscall *call);
void qemu_TpAllocWait(struct qemu_syscall *call);
void qemu_TpAllocWork(struct qemu_syscall *call);
void qemu_TpCallbackLeaveCriticalSectionOnCompletion(struct qemu_syscall *call);
void qemu_TpCallbackMayRunLong(struct qemu_syscall *call);
void qemu_TpCallbackReleaseMutexOnCompletion(struct qemu_syscall *call);
void qemu_TpCallbackReleaseSemaphoreOnCompletion(struct qemu_syscall *call);
void qemu_TpCallbackSetEventOnCompletion(struct qemu_syscall *call);
void qemu_TpCallbackUnloadDllOnCompletion(struct qemu_syscall *call);
void qemu_TpDisassociateCallback(struct qemu_syscall *call);
void qemu_TpIsTimerSet(struct qemu_syscall *call);
void qemu_TpPostWork(struct qemu_syscall *call);
void qemu_TpReleaseCleanupGroup(struct qemu_syscall *call);
void qemu_TpReleaseCleanupGroupMembers(struct qemu_syscall *call);
void qemu_TpReleasePool(struct qemu_syscall *call);
void qemu_TpReleaseTimer(struct qemu_syscall *call);
void qemu_TpReleaseWait(struct qemu_syscall *call);
void qemu_TpReleaseWork(struct qemu_syscall *call);
void qemu_TpSetPoolMaxThreads(struct qemu_syscall *call);
void qemu_TpSetPoolMinThreads(struct qemu_syscall *call);
void qemu_TpSetTimer(struct qemu_syscall *call);
void qemu_TpSetWait(struct qemu_syscall *call);
void qemu_TpSimpleTryPost(struct qemu_syscall *call);
void qemu_TpWaitForTimer(struct qemu_syscall *call);
void qemu_TpWaitForWait(struct qemu_syscall *call);
void qemu_TpWaitForWork(struct qemu_syscall *call);
void qemu_VerSetConditionMask(struct qemu_syscall *call);
void qemu_wcscat(struct qemu_syscall *call);
void qemu_wcschr(struct qemu_syscall *call);
void qemu_wcscmp(struct qemu_syscall *call);
void qemu_wcscpy(struct qemu_syscall *call);
void qemu_wcscspn(struct qemu_syscall *call);
void qemu_wcslen(struct qemu_syscall *call);
void qemu_wcsncat(struct qemu_syscall *call);
void qemu_wcsncmp(struct qemu_syscall *call);
void qemu_wcsncpy(struct qemu_syscall *call);
void qemu_wcspbrk(struct qemu_syscall *call);
void qemu_wcsrchr(struct qemu_syscall *call);
void qemu_wcsspn(struct qemu_syscall *call);
void qemu_wcsstr(struct qemu_syscall *call);
void qemu_wcstok(struct qemu_syscall *call);
void qemu_wcstol(struct qemu_syscall *call);
void qemu_wcstombs(struct qemu_syscall *call);
void qemu_wcstoul(struct qemu_syscall *call);
void qemu_WinSqmEndSession(struct qemu_syscall *call);
void qemu_WinSqmIsOptedIn(struct qemu_syscall *call);
void qemu_WinSqmStartSession(struct qemu_syscall *call);

WCHAR *(* CDECL p_wcsrchr)(WCHAR *str, WCHAR ch);
void * (* CDECL p_memchr)(const void *ptr, int c, size_t n);
int (* CDECL p_memcmp)(const void *ptr1, const void *ptr2, size_t n);
void * (* CDECL p_memcpy)(void *dst, const void *src, size_t n);
void * (* CDECL p_memmove)(void *dst, const void *src, size_t n);
void * (* CDECL p_memset)(void *dst, int c, size_t n);
char * (* CDECL p_strcat)(char *dst, const char *src);
char * (* CDECL p_strchr)(const char *str, int c);
int (* CDECL p_strcmp)(const char *str1, const char *str2);
char * (* CDECL p_strcpy)(char *dst, const char *src);
size_t (* CDECL p_strcspn)(const char *str, const char *reject);
size_t (* CDECL p_strlen)(const char *str);
char * (* CDECL p_strncat)(char *dst, const char *src, size_t len);
int (* CDECL p_strncmp)(const char *str1, const char *str2, size_t len);
char * (* CDECL p_strncpy)(char *dst, const char *src, size_t len);
char * (* CDECL p_strpbrk)(const char *str, const char *accept);
char * (* CDECL p_strrchr)(const char *str, int c);
size_t (* CDECL p_strspn)(const char *str, const char *accept);
char * (* CDECL p_strstr)(const char *haystack, const char *needle);
void * (* CDECL p__memccpy)(void *dst, const void *src, int c, size_t n);
INT (* CDECL p__memicmp)(LPCSTR s1, LPCSTR s2, DWORD len);
int (* CDECL p__stricmp)(LPCSTR str1, LPCSTR str2);
int (* CDECL p__strnicmp)(LPCSTR str1, LPCSTR str2, size_t n);
LPSTR (* CDECL p__strupr)(LPSTR str);
LPSTR (* CDECL p__strlwr)(LPSTR str);
int (* CDECL p_tolower)(int c);
int (* CDECL p_toupper)(int c);
int (* CDECL p_isalnum)(int c);
int (* CDECL p_isalpha)(int c);
int (* CDECL p_iscntrl)(int c);
int (* CDECL p_isdigit)(int c);
int (* CDECL p_isgraph)(int c);
int (* CDECL p_islower)(int c);
int (* CDECL p_isprint)(int c);
int (* CDECL p_ispunct)(int c);
int (* CDECL p_isspace)(int c);
int (* CDECL p_isupper)(int c);
int (* CDECL p_isxdigit)(int c);
int (* CDECL p___isascii)(int c);
int (* CDECL p___toascii)(int c);
int (* CDECL p___iscsym)(int c);
int (* CDECL p___iscsymf)(int c);
int (* CDECL p__toupper)(int c);
int (* CDECL p__tolower)(int c);
LONG (* CDECL p_strtol)(const char *nptr, char **endptr, int base);
ULONG (* CDECL p_strtoul)(const char *nptr, char **endptr, int base);
char * (* CDECL p__ultoa)(ULONG value, char *str, int radix);
char * (* CDECL p__ltoa)(LONG value, char *str, int radix);
char * (* CDECL p__itoa)(int value, char *str, int radix);
char * (* CDECL p__ui64toa)(ULONGLONG value, char *str, int radix);
char * (* CDECL p__i64toa)(LONGLONG value, char *str, int radix);
LONGLONG (* CDECL p__atoi64)(const char *str);
int (* CDECL p_atoi)(const char *nptr);
LONG (* CDECL p_atol)(const char *nptr);
void (* CDECL p__splitpath)(const char* inpath, char * drv, char * dir, char* fname, char * ext);

INT (* CDECL p__wcsicmp)(LPCWSTR str1, LPCWSTR str2);
LPWSTR (* CDECL p__wcslwr)(LPWSTR str);
INT (* CDECL p__wcsnicmp)(LPCWSTR str1, LPCWSTR str2, INT n);
LPWSTR (* CDECL p__wcsupr)(LPWSTR str);
WCHAR (* CDECL p_towlower)(WCHAR ch);
WCHAR (* CDECL p_towupper)(WCHAR ch);
LPWSTR (* CDECL p_wcscat)(LPWSTR dst, LPCWSTR src);
LPWSTR (* CDECL p_wcschr)(LPCWSTR str, WCHAR ch);
INT (* CDECL p_wcscmp)(LPCWSTR str1, LPCWSTR str2);
LPWSTR (* CDECL p_wcscpy)(LPWSTR dst, LPCWSTR src);
INT (* CDECL p_wcscspn)(LPCWSTR str, LPCWSTR reject);
INT (* CDECL p_wcslen)(LPCWSTR str);
LPWSTR (* CDECL p_wcsncat)(LPWSTR s1, LPCWSTR s2, INT n);
INT (* CDECL p_wcsncmp)(LPCWSTR str1, LPCWSTR str2, INT n);
LPWSTR (* CDECL p_wcsncpy)(LPWSTR s1, LPCWSTR s2, INT n);
LPWSTR (* CDECL p_wcspbrk)(LPCWSTR str, LPCWSTR accept);
INT (* CDECL p_wcsspn)(LPCWSTR str, LPCWSTR accept);
LPWSTR (* CDECL p_wcsstr)(LPCWSTR str, LPCWSTR sub);
LPWSTR (* CDECL p_wcstok)(LPWSTR str, LPCWSTR delim);
INT (* CDECL p_wcstombs)(LPSTR dst, LPCWSTR src, INT n);
INT (* CDECL p_mbstowcs)(LPWSTR dst, LPCSTR src, INT n);
LONG (* CDECL p_wcstol)(LPCWSTR s, LPWSTR *end, INT base);
ULONG (* CDECL p_wcstoul)(LPCWSTR s, LPWSTR *end, INT base);
INT (* CDECL p_iswctype)(WCHAR wc, WCHAR wct);
INT (* CDECL p_iswalpha)(WCHAR wc);
INT (* CDECL p_iswdigit)(WCHAR wc);
INT (* CDECL p_iswlower)(WCHAR wc);
INT (* CDECL p_iswspace)(WCHAR wc);
INT (* CDECL p_iswxdigit)(WCHAR wc);
LPWSTR (* CDECL p__ultow)(ULONG value, LPWSTR str, INT radix);
LPWSTR (* CDECL p__ltow)(LONG value, LPWSTR str, INT radix);
LPWSTR (* CDECL p__itow)(int value, LPWSTR str, INT radix);
LPWSTR (* CDECL p__ui64tow)(ULONGLONG value, LPWSTR str, INT radix);
LPWSTR (* CDECL p__i64tow)(LONGLONG value, LPWSTR str, INT radix);
LONG (* CDECL p__wtol)(LPCWSTR str);
int (* CDECL p__wtoi)(LPCWSTR str);
LONGLONG (* CDECL p__wtoi64)(LPCWSTR str);

int (* CDECL p_vsprintf)(char *str, const char *format, __ms_va_list args);
int (* CDECL p__vsnprintf)(char *str, SIZE_T len, const char *format, __ms_va_list args);
int (* CDECL p__vsnprintf_s)(char *str, unsigned int len, unsigned int count, const char *format, __ms_va_list valist);

struct IOSB_data
{
    IO_STATUS_BLOCK iosb;
    HANDLE host_event, guest_event;

    struct qemu_IO_STATUS_BLOCK *guest_iosb;

    /*
     * Ignore this for now. It'll probably be needed for some cancel function.
    struct list free_list_entry;
    struct wine_rb_entry rbtree_entry;
    BOOL in_tree;
     */
};

#endif

#endif
