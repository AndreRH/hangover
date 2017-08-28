#ifndef USER32_H
#define USER32_H

#include <stdlib.h>

enum user32_calls
{
    CALL_ACTIVATEKEYBOARDLAYOUT = 0,
    CALL_ADDCLIPBOARDFORMATLISTENER,
    CALL_ADJUSTWINDOWRECT,
    CALL_ADJUSTWINDOWRECTEX,
    CALL_ALIGNRECTS,
    CALL_ALLOWSETFOREGROUNDWINDOW,
    CALL_ANIMATEWINDOW,
    CALL_ANYPOPUP,
    CALL_APPENDMENUA,
    CALL_APPENDMENUW,
    CALL_ARRANGEICONICWINDOWS,
    CALL_ATTACHTHREADINPUT,
    CALL_BEGINDEFERWINDOWPOS,
    CALL_BEGINPAINT,
    CALL_BLOCKINPUT,
    CALL_BRINGWINDOWTOTOP,
    CALL_BROADCASTSYSTEMMESSAGEA,
    CALL_BROADCASTSYSTEMMESSAGEEXA,
    CALL_BROADCASTSYSTEMMESSAGEEXW,
    CALL_BROADCASTSYSTEMMESSAGEW,
    CALL_CALCCHILDSCROLL,
    CALL_CALL_WNDPROC,
    CALL_CALLMSGFILTERA,
    CALL_CALLMSGFILTERW,
    CALL_CALLNEXTHOOKEX,
    CALL_CALLWINDOWPROCA,
    CALL_CALLWINDOWPROCW,
    CALL_CASCADECHILDWINDOWS,
    CALL_CASCADEWINDOWS,
    CALL_CHANGECLIPBOARDCHAIN,
    CALL_CHANGEDISPLAYSETTINGSA,
    CALL_CHANGEDISPLAYSETTINGSEXA,
    CALL_CHANGEDISPLAYSETTINGSEXW,
    CALL_CHANGEDISPLAYSETTINGSW,
    CALL_CHANGEMENUA,
    CALL_CHANGEMENUW,
    CALL_CHANGEWINDOWMESSAGEFILTER,
    CALL_CHARLOWERA,
    CALL_CHARLOWERBUFFA,
    CALL_CHARLOWERBUFFW,
    CALL_CHARLOWERW,
    CALL_CHARNEXTA,
    CALL_CHARNEXTEXA,
    CALL_CHARNEXTEXW,
    CALL_CHARNEXTW,
    CALL_CHARPREVA,
    CALL_CHARPREVEXA,
    CALL_CHARPREVEXW,
    CALL_CHARPREVW,
    CALL_CHARTOOEMA,
    CALL_CHARTOOEMBUFFA,
    CALL_CHARTOOEMBUFFW,
    CALL_CHARTOOEMW,
    CALL_CHARUPPERA,
    CALL_CHARUPPERBUFFA,
    CALL_CHARUPPERBUFFW,
    CALL_CHARUPPERW,
    CALL_CHECKDLGBUTTON,
    CALL_CHECKMENUITEM,
    CALL_CHECKMENURADIOITEM,
    CALL_CHECKRADIOBUTTON,
    CALL_CHILDWINDOWFROMPOINT,
    CALL_CHILDWINDOWFROMPOINTEX,
    CALL_CLIENTTOSCREEN,
    CALL_CLIPCURSOR,
    CALL_CLOSECLIPBOARD,
    CALL_CLOSEDESKTOP,
    CALL_CLOSEWINDOW,
    CALL_CLOSEWINDOWSTATION,
    CALL_COPYACCELERATORTABLEA,
    CALL_COPYACCELERATORTABLEW,
    CALL_COPYICON,
    CALL_COPYIMAGE,
    CALL_COPYRECT,
    CALL_COUNTCLIPBOARDFORMATS,
    CALL_CREATEACCELERATORTABLEA,
    CALL_CREATEACCELERATORTABLEW,
    CALL_CREATECARET,
    CALL_CREATECURSOR,
    CALL_CREATEDESKTOPA,
    CALL_CREATEDESKTOPW,
    CALL_CREATEDIALOGINDIRECTPARAMA,
    CALL_CREATEDIALOGINDIRECTPARAMAORW,
    CALL_CREATEDIALOGINDIRECTPARAMW,
    CALL_CREATEDIALOGPARAMA,
    CALL_CREATEDIALOGPARAMW,
    CALL_CREATEICON,
    CALL_CREATEICONFROMRESOURCE,
    CALL_CREATEICONFROMRESOURCEEX,
    CALL_CREATEICONINDIRECT,
    CALL_CREATEMDIWINDOWA,
    CALL_CREATEMDIWINDOWW,
    CALL_CREATEMENU,
    CALL_CREATEPOPUPMENU,
    CALL_CREATEWINDOWEXA,
    CALL_CREATEWINDOWEXW,
    CALL_CREATEWINDOWSTATIONA,
    CALL_CREATEWINDOWSTATIONW,
    CALL_DDEABANDONTRANSACTION,
    CALL_DDEACCESSDATA,
    CALL_DDEADDDATA,
    CALL_DDECLIENTTRANSACTION,
    CALL_DDECMPSTRINGHANDLES,
    CALL_DDECONNECT,
    CALL_DDECONNECTLIST,
    CALL_DDECREATEDATAHANDLE,
    CALL_DDECREATESTRINGHANDLEA,
    CALL_DDECREATESTRINGHANDLEW,
    CALL_DDEDISCONNECT,
    CALL_DDEDISCONNECTLIST,
    CALL_DDEENABLECALLBACK,
    CALL_DDEFREEDATAHANDLE,
    CALL_DDEFREESTRINGHANDLE,
    CALL_DDEGETDATA,
    CALL_DDEGETLASTERROR,
    CALL_DDEIMPERSONATECLIENT,
    CALL_DDEINITIALIZEA,
    CALL_DDEINITIALIZEW,
    CALL_DDEKEEPSTRINGHANDLE,
    CALL_DDENAMESERVICE,
    CALL_DDEPOSTADVISE,
    CALL_DDEQUERYCONVINFO,
    CALL_DDEQUERYNEXTSERVER,
    CALL_DDEQUERYSTRINGA,
    CALL_DDEQUERYSTRINGW,
    CALL_DDERECONNECT,
    CALL_DDESETQUALITYOFSERVICE,
    CALL_DDEUNACCESSDATA,
    CALL_DDEUNINITIALIZE,
    CALL_DEFDLGPROCA,
    CALL_DEFDLGPROCW,
    CALL_DEFERWINDOWPOS,
    CALL_DEFFRAMEPROCA,
    CALL_DEFFRAMEPROCW,
    CALL_DEFMDICHILDPROCA,
    CALL_DEFMDICHILDPROCW,
    CALL_DEFRAWINPUTPROC,
    CALL_DEFWINDOWPROCA,
    CALL_DEFWINDOWPROCW,
    CALL_DELETEMENU,
    CALL_DEREGISTERSHELLHOOKWINDOW,
    CALL_DESTROYACCELERATORTABLE,
    CALL_DESTROYCARET,
    CALL_DESTROYCURSOR,
    CALL_DESTROYICON,
    CALL_DESTROYMENU,
    CALL_DESTROYWINDOW,
    CALL_DIALOGBOXINDIRECTPARAMA,
    CALL_DIALOGBOXINDIRECTPARAMAORW,
    CALL_DIALOGBOXINDIRECTPARAMW,
    CALL_DIALOGBOXPARAMA,
    CALL_DIALOGBOXPARAMW,
    CALL_DISABLEPROCESSWINDOWSGHOSTING,
    CALL_DISPATCHMESSAGEA,
    CALL_DISPATCHMESSAGEW,
    CALL_DLGDIRLISTA,
    CALL_DLGDIRLISTCOMBOBOXA,
    CALL_DLGDIRLISTCOMBOBOXW,
    CALL_DLGDIRLISTW,
    CALL_DLGDIRSELECTCOMBOBOXEXA,
    CALL_DLGDIRSELECTCOMBOBOXEXW,
    CALL_DLGDIRSELECTEXA,
    CALL_DLGDIRSELECTEXW,
    CALL_DRAWANIMATEDRECTS,
    CALL_DRAWCAPTION,
    CALL_DRAWCAPTIONTEMPA,
    CALL_DRAWCAPTIONTEMPW,
    CALL_DRAWEDGE,
    CALL_DRAWFOCUSRECT,
    CALL_DRAWFRAMECONTROL,
    CALL_DRAWICON,
    CALL_DRAWICONEX,
    CALL_DRAWMENUBAR,
    CALL_DRAWMENUBARTEMP,
    CALL_DRAWSTATEA,
    CALL_DRAWSTATEW,
    CALL_DRAWTEXTA,
    CALL_DRAWTEXTEXA,
    CALL_DRAWTEXTEXW,
    CALL_DRAWTEXTW,
    CALL_EMPTYCLIPBOARD,
    CALL_ENABLEMENUITEM,
    CALL_ENABLESCROLLBAR,
    CALL_ENABLEWINDOW,
    CALL_ENDDEFERWINDOWPOS,
    CALL_ENDDIALOG,
    CALL_ENDMENU,
    CALL_ENDPAINT,
    CALL_ENUMCHILDWINDOWS,
    CALL_ENUMCLIPBOARDFORMATS,
    CALL_ENUMDESKTOPSA,
    CALL_ENUMDESKTOPSW,
    CALL_ENUMDESKTOPWINDOWS,
    CALL_ENUMDISPLAYDEVICESA,
    CALL_ENUMDISPLAYDEVICESW,
    CALL_ENUMDISPLAYMONITORS,
    CALL_ENUMDISPLAYSETTINGSA,
    CALL_ENUMDISPLAYSETTINGSEXA,
    CALL_ENUMDISPLAYSETTINGSEXW,
    CALL_ENUMDISPLAYSETTINGSW,
    CALL_ENUMPROPSA,
    CALL_ENUMPROPSEXA,
    CALL_ENUMPROPSEXW,
    CALL_ENUMPROPSW,
    CALL_ENUMTHREADWINDOWS,
    CALL_ENUMWINDOWS,
    CALL_ENUMWINDOWSTATIONSA,
    CALL_ENUMWINDOWSTATIONSW,
    CALL_EQUALRECT,
    CALL_EXCLUDEUPDATERGN,
    CALL_EXITWINDOWSEX,
    CALL_FILLRECT,
    CALL_FINDWINDOWA,
    CALL_FINDWINDOWEXA,
    CALL_FINDWINDOWEXW,
    CALL_FINDWINDOWW,
    CALL_FLASHWINDOW,
    CALL_FLASHWINDOWEX,
    CALL_FRAMERECT,
    CALL_FREEDDELPARAM,
    CALL_GETACTIVEWINDOW,
    CALL_GETALTTABINFOA,
    CALL_GETALTTABINFOW,
    CALL_GETANCESTOR,
    CALL_GETAPPCOMPATFLAGS,
    CALL_GETAPPCOMPATFLAGS2,
    CALL_GETASYNCKEYSTATE,
    CALL_GETCAPTURE,
    CALL_GETCARETBLINKTIME,
    CALL_GETCARETPOS,
    CALL_GETCLASSINFOA,
    CALL_GETCLASSINFOEXA,
    CALL_GETCLASSINFOEXW,
    CALL_GETCLASSINFOW,
    CALL_GETCLASSLONGA,
    CALL_GETCLASSLONGPTRA,
    CALL_GETCLASSLONGPTRW,
    CALL_GETCLASSLONGW,
    CALL_GETCLASSNAMEA,
    CALL_GETCLASSNAMEW,
    CALL_GETCLASSWORD,
    CALL_GETCLIENTRECT,
    CALL_GETCLIPBOARDDATA,
    CALL_GETCLIPBOARDFORMATNAMEA,
    CALL_GETCLIPBOARDFORMATNAMEW,
    CALL_GETCLIPBOARDOWNER,
    CALL_GETCLIPBOARDSEQUENCENUMBER,
    CALL_GETCLIPBOARDVIEWER,
    CALL_GETCLIPCURSOR,
    CALL_GETCOMBOBOXINFO,
    CALL_GETCURSOR,
    CALL_GETCURSORFRAMEINFO,
    CALL_GETCURSORINFO,
    CALL_GETCURSORPOS,
    CALL_GETDC,
    CALL_GETDCEX,
    CALL_GETDESKTOPWINDOW,
    CALL_GETDIALOGBASEUNITS,
    CALL_GETDISPLAYCONFIGBUFFERSIZES,
    CALL_GETDLGCTRLID,
    CALL_GETDLGITEM,
    CALL_GETDLGITEMINT,
    CALL_GETDLGITEMTEXTA,
    CALL_GETDLGITEMTEXTW,
    CALL_GETDOUBLECLICKTIME,
    CALL_GETFOCUS,
    CALL_GETFOREGROUNDWINDOW,
    CALL_GETGESTURECONFIG,
    CALL_GETGUIRESOURCES,
    CALL_GETGUITHREADINFO,
    CALL_GETICONINFO,
    CALL_GETICONINFOEXA,
    CALL_GETICONINFOEXW,
    CALL_GETINPUTSTATE,
    CALL_GETINTERNALWINDOWPOS,
    CALL_GETKBCODEPAGE,
    CALL_GETKEYBOARDLAYOUT,
    CALL_GETKEYBOARDLAYOUTLIST,
    CALL_GETKEYBOARDLAYOUTNAMEA,
    CALL_GETKEYBOARDLAYOUTNAMEW,
    CALL_GETKEYBOARDSTATE,
    CALL_GETKEYBOARDTYPE,
    CALL_GETKEYNAMETEXTA,
    CALL_GETKEYNAMETEXTW,
    CALL_GETKEYSTATE,
    CALL_GETLASTACTIVEPOPUP,
    CALL_GETLASTINPUTINFO,
    CALL_GETLAYEREDWINDOWATTRIBUTES,
    CALL_GETLISTBOXINFO,
    CALL_GETMENU,
    CALL_GETMENUBARINFO,
    CALL_GETMENUCONTEXTHELPID,
    CALL_GETMENUDEFAULTITEM,
    CALL_GETMENUINFO,
    CALL_GETMENUITEMCOUNT,
    CALL_GETMENUITEMID,
    CALL_GETMENUITEMINFOA,
    CALL_GETMENUITEMINFOW,
    CALL_GETMENUITEMRECT,
    CALL_GETMENUSTATE,
    CALL_GETMENUSTRINGA,
    CALL_GETMENUSTRINGW,
    CALL_GETMESSAGEA,
    CALL_GETMESSAGEEXTRAINFO,
    CALL_GETMESSAGEPOS,
    CALL_GETMESSAGETIME,
    CALL_GETMESSAGEW,
    CALL_GETMONITORINFOA,
    CALL_GETMONITORINFOW,
    CALL_GETMOUSEMOVEPOINTSEX,
    CALL_GETNEXTDLGGROUPITEM,
    CALL_GETNEXTDLGTABITEM,
    CALL_GETOPENCLIPBOARDWINDOW,
    CALL_GETPARENT,
    CALL_GETPHYSICALCURSORPOS,
    CALL_GETPRIORITYCLIPBOARDFORMAT,
    CALL_GETPROCESSDEFAULTLAYOUT,
    CALL_GETPROCESSWINDOWSTATION,
    CALL_GETPROGMANWINDOW,
    CALL_GETPROPA,
    CALL_GETPROPW,
    CALL_GETQUEUESTATUS,
    CALL_GETRAWINPUTBUFFER,
    CALL_GETRAWINPUTDATA,
    CALL_GETRAWINPUTDEVICEINFOA,
    CALL_GETRAWINPUTDEVICEINFOW,
    CALL_GETRAWINPUTDEVICELIST,
    CALL_GETREGISTEREDRAWINPUTDEVICES,
    CALL_GETSCROLLBARINFO,
    CALL_GETSCROLLINFO,
    CALL_GETSCROLLPOS,
    CALL_GETSCROLLRANGE,
    CALL_GETSHELLWINDOW,
    CALL_GETSUBMENU,
    CALL_GETSYSCOLOR,
    CALL_GETSYSCOLORBRUSH,
    CALL_GETSYSTEMMENU,
    CALL_GETSYSTEMMETRICS,
    CALL_GETTABBEDTEXTEXTENTA,
    CALL_GETTABBEDTEXTEXTENTW,
    CALL_GETTASKMANWINDOW,
    CALL_GETTHREADDESKTOP,
    CALL_GETTITLEBARINFO,
    CALL_GETTOPWINDOW,
    CALL_GETUPDATEDCLIPBOARDFORMATS,
    CALL_GETUPDATERECT,
    CALL_GETUPDATERGN,
    CALL_GETUSEROBJECTINFORMATIONA,
    CALL_GETUSEROBJECTINFORMATIONW,
    CALL_GETUSEROBJECTSECURITY,
    CALL_GETWINDOW,
    CALL_GETWINDOWCONTEXTHELPID,
    CALL_GETWINDOWDC,
    CALL_GETWINDOWINFO,
    CALL_GETWINDOWLONGA,
    CALL_GETWINDOWLONGPTRA,
    CALL_GETWINDOWLONGPTRW,
    CALL_GETWINDOWLONGW,
    CALL_GETWINDOWMODULEFILENAMEA,
    CALL_GETWINDOWMODULEFILENAMEW,
    CALL_GETWINDOWPLACEMENT,
    CALL_GETWINDOWRECT,
    CALL_GETWINDOWRGN,
    CALL_GETWINDOWRGNBOX,
    CALL_GETWINDOWTEXTA,
    CALL_GETWINDOWTEXTLENGTHA,
    CALL_GETWINDOWTEXTLENGTHW,
    CALL_GETWINDOWTEXTW,
    CALL_GETWINDOWTHREADPROCESSID,
    CALL_GETWINDOWWORD,
    CALL_GRAYSTRINGA,
    CALL_GRAYSTRINGW,
    CALL_HIDECARET,
    CALL_HILITEMENUITEM,
    CALL_IMPERSONATEDDECLIENTWINDOW,
    CALL_INFLATERECT,
    CALL_INSENDMESSAGE,
    CALL_INSENDMESSAGEEX,
    CALL_INSERTMENUA,
    CALL_INSERTMENUITEMA,
    CALL_INSERTMENUITEMW,
    CALL_INSERTMENUW,
    CALL_INTERNALGETWINDOWTEXT,
    CALL_INTERSECTRECT,
    CALL_INVALIDATERECT,
    CALL_INVALIDATERGN,
    CALL_INVERTRECT,
    CALL_ISCHARALPHAA,
    CALL_ISCHARALPHANUMERICA,
    CALL_ISCHARALPHANUMERICW,
    CALL_ISCHARALPHAW,
    CALL_ISCHARLOWERA,
    CALL_ISCHARLOWERW,
    CALL_ISCHARUPPERA,
    CALL_ISCHARUPPERW,
    CALL_ISCHILD,
    CALL_ISCLIPBOARDFORMATAVAILABLE,
    CALL_ISDIALOGMESSAGEA,
    CALL_ISDIALOGMESSAGEW,
    CALL_ISDLGBUTTONCHECKED,
    CALL_ISGUITHREAD,
    CALL_ISHUNGAPPWINDOW,
    CALL_ISICONIC,
    CALL_ISMENU,
    CALL_ISPROCESSDPIAWARE,
    CALL_ISRECTEMPTY,
    CALL_ISTOUCHWINDOW,
    CALL_ISWINDOW,
    CALL_ISWINDOWENABLED,
    CALL_ISWINDOWREDIRECTEDFORPRINT,
    CALL_ISWINDOWUNICODE,
    CALL_ISWINDOWVISIBLE,
    CALL_ISWINEVENTHOOKINSTALLED,
    CALL_ISZOOMED,
    CALL_KEYBD_EVENT,
    CALL_KILLSYSTEMTIMER,
    CALL_KILLTIMER,
    CALL_LOADACCELERATORSA,
    CALL_LOADACCELERATORSW,
    CALL_LOADBITMAPA,
    CALL_LOADBITMAPW,
    CALL_LOADCURSORA,
    CALL_LOADCURSORFROMFILEA,
    CALL_LOADCURSORFROMFILEW,
    CALL_LOADCURSORW,
    CALL_LOADICONA,
    CALL_LOADICONW,
    CALL_LOADIMAGEA,
    CALL_LOADIMAGEW,
    CALL_LOADKEYBOARDLAYOUTA,
    CALL_LOADKEYBOARDLAYOUTW,
    CALL_LOADLOCALFONTS,
    CALL_LOADMENUA,
    CALL_LOADMENUINDIRECTA,
    CALL_LOADMENUINDIRECTW,
    CALL_LOADMENUW,
    CALL_LOADSTRINGA,
    CALL_LOADSTRINGW,
    CALL_LOCKSETFOREGROUNDWINDOW,
    CALL_LOCKWINDOWUPDATE,
    CALL_LOCKWORKSTATION,
    CALL_LOGICALTOPHYSICALPOINT,
    CALL_LOOKUPICONIDFROMDIRECTORY,
    CALL_LOOKUPICONIDFROMDIRECTORYEX,
    CALL_MAPDIALOGRECT,
    CALL_MAPVIRTUALKEYA,
    CALL_MAPVIRTUALKEYEXA,
    CALL_MAPVIRTUALKEYEXW,
    CALL_MAPVIRTUALKEYW,
    CALL_MAPWINDOWPOINTS,
    CALL_MESSAGEBEEP,
    CALL_MESSAGEBOXA,
    CALL_MESSAGEBOXEXA,
    CALL_MESSAGEBOXEXW,
    CALL_MESSAGEBOXINDIRECTA,
    CALL_MESSAGEBOXINDIRECTW,
    CALL_MESSAGEBOXTIMEOUTA,
    CALL_MESSAGEBOXTIMEOUTW,
    CALL_MESSAGEBOXW,
    CALL_MODIFYMENUA,
    CALL_MODIFYMENUW,
    CALL_MONITORFROMPOINT,
    CALL_MONITORFROMRECT,
    CALL_MONITORFROMWINDOW,
    CALL_MOUSE_EVENT,
    CALL_MOVEWINDOW,
    CALL_MSGWAITFORMULTIPLEOBJECTS,
    CALL_MSGWAITFORMULTIPLEOBJECTSEX,
    CALL_NOTIFYWINEVENT,
    CALL_OEMKEYSCAN,
    CALL_OEMTOCHARA,
    CALL_OEMTOCHARBUFFA,
    CALL_OEMTOCHARBUFFW,
    CALL_OEMTOCHARW,
    CALL_OFFSETRECT,
    CALL_OPENCLIPBOARD,
    CALL_OPENDESKTOPA,
    CALL_OPENDESKTOPW,
    CALL_OPENICON,
    CALL_OPENINPUTDESKTOP,
    CALL_OPENWINDOWSTATIONA,
    CALL_OPENWINDOWSTATIONW,
    CALL_PACKDDELPARAM,
    CALL_PAINTDESKTOP,
    CALL_PEEKMESSAGEA,
    CALL_PEEKMESSAGEW,
    CALL_PHYSICALTOLOGICALPOINT,
    CALL_POSTMESSAGEA,
    CALL_POSTMESSAGEW,
    CALL_POSTQUITMESSAGE,
    CALL_POSTTHREADMESSAGEA,
    CALL_POSTTHREADMESSAGEW,
    CALL_PRINTWINDOW,
    CALL_PRIVATEEXTRACTICONEXA,
    CALL_PRIVATEEXTRACTICONEXW,
    CALL_PRIVATEEXTRACTICONSA,
    CALL_PRIVATEEXTRACTICONSW,
    CALL_PTINRECT,
    CALL_QUERYDISPLAYCONFIG,
    CALL_REALCHILDWINDOWFROMPOINT,
    CALL_REALGETWINDOWCLASSA,
    CALL_REALGETWINDOWCLASSW,
    CALL_REDRAWWINDOW,
    CALL_REGISTERCLASSEXA,
    CALL_REGISTERCLASSEXW,
    CALL_REGISTERCLIPBOARDFORMATA,
    CALL_REGISTERCLIPBOARDFORMATW,
    CALL_REGISTERDEVICENOTIFICATIONA,
    CALL_REGISTERDEVICENOTIFICATIONW,
    CALL_REGISTERHOTKEY,
    CALL_REGISTERLOGONPROCESS,
    CALL_REGISTERPOWERSETTINGNOTIFICATION,
    CALL_REGISTERRAWINPUTDEVICES,
    CALL_REGISTERSERVICESPROCESS,
    CALL_REGISTERSHELLHOOKWINDOW,
    CALL_REGISTERSYSTEMTHREAD,
    CALL_REGISTERTASKLIST,
    CALL_REGISTERTOUCHWINDOW,
    CALL_REGISTERWINDOWMESSAGEA,
    CALL_REGISTERWINDOWMESSAGEW,
    CALL_RELEASECAPTURE,
    CALL_RELEASEDC,
    CALL_REMOVECLIPBOARDFORMATLISTENER,
    CALL_REMOVEMENU,
    CALL_REMOVEPROPA,
    CALL_REMOVEPROPW,
    CALL_REPLYMESSAGE,
    CALL_REUSEDDELPARAM,
    CALL_SCREENTOCLIENT,
    CALL_SCROLLCHILDREN,
    CALL_SCROLLDC,
    CALL_SCROLLWINDOW,
    CALL_SCROLLWINDOWEX,
    CALL_SENDDLGITEMMESSAGEA,
    CALL_SENDDLGITEMMESSAGEW,
    CALL_SENDIMEMESSAGEEXA,
    CALL_SENDIMEMESSAGEEXW,
    CALL_SENDINPUT,
    CALL_SENDMESSAGEA,
    CALL_SENDMESSAGECALLBACKA,
    CALL_SENDMESSAGECALLBACKW,
    CALL_SENDMESSAGETIMEOUTA,
    CALL_SENDMESSAGETIMEOUTW,
    CALL_SENDMESSAGEW,
    CALL_SENDNOTIFYMESSAGEA,
    CALL_SENDNOTIFYMESSAGEW,
    CALL_SET_CALLBACKS,
    CALL_SETACTIVEWINDOW,
    CALL_SETCAPTURE,
    CALL_SETCARETBLINKTIME,
    CALL_SETCARETPOS,
    CALL_SETCLASSLONGA,
    CALL_SETCLASSLONGPTRA,
    CALL_SETCLASSLONGPTRW,
    CALL_SETCLASSLONGW,
    CALL_SETCLASSWORD,
    CALL_SETCLIPBOARDDATA,
    CALL_SETCLIPBOARDVIEWER,
    CALL_SETCOALESCABLETIMER,
    CALL_SETCURSOR,
    CALL_SETCURSORPOS,
    CALL_SETDEBUGERRORLEVEL,
    CALL_SETDESKWALLPAPER,
    CALL_SETDLGITEMINT,
    CALL_SETDLGITEMTEXTA,
    CALL_SETDLGITEMTEXTW,
    CALL_SETDOUBLECLICKTIME,
    CALL_SETFOCUS,
    CALL_SETFOREGROUNDWINDOW,
    CALL_SETGESTURECONFIG,
    CALL_SETINTERNALWINDOWPOS,
    CALL_SETKEYBOARDSTATE,
    CALL_SETLASTERROREX,
    CALL_SETLAYEREDWINDOWATTRIBUTES,
    CALL_SETLOGONNOTIFYWINDOW,
    CALL_SETMENU,
    CALL_SETMENUCONTEXTHELPID,
    CALL_SETMENUDEFAULTITEM,
    CALL_SETMENUINFO,
    CALL_SETMENUITEMBITMAPS,
    CALL_SETMENUITEMINFOA,
    CALL_SETMENUITEMINFOW,
    CALL_SETMESSAGEEXTRAINFO,
    CALL_SETMESSAGEQUEUE,
    CALL_SETPARENT,
    CALL_SETPHYSICALCURSORPOS,
    CALL_SETPROCESSDEFAULTLAYOUT,
    CALL_SETPROCESSDPIAWARE,
    CALL_SETPROCESSWINDOWSTATION,
    CALL_SETPROGMANWINDOW,
    CALL_SETPROPA,
    CALL_SETPROPW,
    CALL_SETRECT,
    CALL_SETRECTEMPTY,
    CALL_SETSCROLLINFO,
    CALL_SETSCROLLPOS,
    CALL_SETSCROLLRANGE,
    CALL_SETSHELLWINDOW,
    CALL_SETSHELLWINDOWEX,
    CALL_SETSYSCOLORS,
    CALL_SETSYSCOLORSTEMP,
    CALL_SETSYSTEMCURSOR,
    CALL_SETSYSTEMMENU,
    CALL_SETSYSTEMTIMER,
    CALL_SETTASKMANWINDOW,
    CALL_SETTHREADDESKTOP,
    CALL_SETTIMER,
    CALL_SETUSEROBJECTINFORMATIONA,
    CALL_SETUSEROBJECTINFORMATIONW,
    CALL_SETUSEROBJECTSECURITY,
    CALL_SETWINDOWCONTEXTHELPID,
    CALL_SETWINDOWLONGA,
    CALL_SETWINDOWLONGPTRA,
    CALL_SETWINDOWLONGPTRW,
    CALL_SETWINDOWLONGW,
    CALL_SETWINDOWPLACEMENT,
    CALL_SETWINDOWPOS,
    CALL_SETWINDOWRGN,
    CALL_SETWINDOWSHOOKA,
    CALL_SETWINDOWSHOOKEXA,
    CALL_SETWINDOWSHOOKEXW,
    CALL_SETWINDOWSHOOKW,
    CALL_SETWINDOWSTATIONUSER,
    CALL_SETWINDOWTEXTA,
    CALL_SETWINDOWTEXTW,
    CALL_SETWINDOWWORD,
    CALL_SETWINEVENTHOOK,
    CALL_SHOWCARET,
    CALL_SHOWCURSOR,
    CALL_SHOWOWNEDPOPUPS,
    CALL_SHOWSCROLLBAR,
    CALL_SHOWWINDOW,
    CALL_SHOWWINDOWASYNC,
    CALL_SHUTDOWNBLOCKREASONCREATE,
    CALL_SHUTDOWNBLOCKREASONDESTROY,
    CALL_SUBTRACTRECT,
    CALL_SWAPMOUSEBUTTON,
    CALL_SWITCHDESKTOP,
    CALL_SWITCHTOTHISWINDOW,
    CALL_SYSTEMPARAMETERSINFOA,
    CALL_SYSTEMPARAMETERSINFOW,
    CALL_TABBEDTEXTOUTA,
    CALL_TABBEDTEXTOUTW,
    CALL_TILECHILDWINDOWS,
    CALL_TILEWINDOWS,
    CALL_TOASCII,
    CALL_TOASCIIEX,
    CALL_TOUNICODE,
    CALL_TOUNICODEEX,
    CALL_TRACKMOUSEEVENT,
    CALL_TRACKPOPUPMENU,
    CALL_TRACKPOPUPMENUEX,
    CALL_TRANSLATEACCELERATORA,
    CALL_TRANSLATEACCELERATORW,
    CALL_TRANSLATEMDISYSACCEL,
    CALL_TRANSLATEMESSAGE,
    CALL_UNHOOKWINDOWSHOOK,
    CALL_UNHOOKWINDOWSHOOKEX,
    CALL_UNHOOKWINEVENT,
    CALL_UNIONRECT,
    CALL_UNLOADKEYBOARDLAYOUT,
    CALL_UNPACKDDELPARAM,
    CALL_UNREGISTERCLASSA,
    CALL_UNREGISTERCLASSW,
    CALL_UNREGISTERDEVICENOTIFICATION,
    CALL_UNREGISTERHOTKEY,
    CALL_UNREGISTERPOWERSETTINGNOTIFICATION,
    CALL_UPDATELAYEREDWINDOW,
    CALL_UPDATELAYEREDWINDOWINDIRECT,
    CALL_UPDATEWINDOW,
    CALL_USER32INITIALIZEIMMENTRYTABLE,
    CALL_USERHANDLEGRANTACCESS,
    CALL_USERREALIZEPALETTE,
    CALL_USERSIGNALPROC,
    CALL_VALIDATERECT,
    CALL_VALIDATERGN,
    CALL_VKKEYSCANA,
    CALL_VKKEYSCANEXA,
    CALL_VKKEYSCANEXW,
    CALL_VKKEYSCANW,
    CALL_WAITFORINPUTIDLE,
    CALL_WAITMESSAGE,
    CALL_WINDOWFROMDC,
    CALL_WINDOWFROMPOINT,
    CALL_WINHELPA,
    CALL_WINHELPW,
    CALL_WINNLSENABLEIME,
    CALL_WINNLSGETENABLESTATUS,
    CALL_WINNLSGETIMEHOTKEY,
};

struct qemu_SetWinEventHook_cb;

static inline BOOL wndproc_is_handle(LONG_PTR proc)
{
    /* This is not exactly right, Wine's user32 also keeps track of how many
     * wndprocs it remembered. We don't know for sure as we only see the ones
     * we pass in and not e.g. those of Wine's controls. */
#define WINPROC_HANDLE (~0u >> 16)
    return (proc >> 16 == WINPROC_HANDLE);
}

#ifdef QEMU_DLL_GUEST

LRESULT CALLBACK reverse_wndproc_func(HWND win, UINT msg, WPARAM wp, LPARAM lp, void *data);
void guest_win_event_wrapper(struct qemu_SetWinEventHook_cb *data);

#else

#include <wine/rbtree.h>

extern const struct qemu_ops *qemu_ops;

void qemu_ActivateKeyboardLayout(struct qemu_syscall *call);
void qemu_AddClipboardFormatListener(struct qemu_syscall *call);
void qemu_AdjustWindowRect(struct qemu_syscall *call);
void qemu_AdjustWindowRectEx(struct qemu_syscall *call);
void qemu_AlignRects(struct qemu_syscall *call);
void qemu_AllowSetForegroundWindow(struct qemu_syscall *call);
void qemu_AnimateWindow(struct qemu_syscall *call);
void qemu_AnyPopup(struct qemu_syscall *call);
void qemu_AppendMenuA(struct qemu_syscall *call);
void qemu_AppendMenuW(struct qemu_syscall *call);
void qemu_ArrangeIconicWindows(struct qemu_syscall *call);
void qemu_AttachThreadInput(struct qemu_syscall *call);
void qemu_BeginDeferWindowPos(struct qemu_syscall *call);
void qemu_BeginPaint(struct qemu_syscall *call);
void qemu_BlockInput(struct qemu_syscall *call);
void qemu_BringWindowToTop(struct qemu_syscall *call);
void qemu_BroadcastSystemMessageA(struct qemu_syscall *call);
void qemu_BroadcastSystemMessageExA(struct qemu_syscall *call);
void qemu_BroadcastSystemMessageExW(struct qemu_syscall *call);
void qemu_BroadcastSystemMessageW(struct qemu_syscall *call);
void qemu_CalcChildScroll(struct qemu_syscall *call);
void qemu_call_wndproc(struct qemu_syscall *call);
void qemu_CallMsgFilterA(struct qemu_syscall *call);
void qemu_CallMsgFilterW(struct qemu_syscall *call);
void qemu_CallNextHookEx(struct qemu_syscall *call);
void qemu_CallWindowProcA(struct qemu_syscall *call);
void qemu_CallWindowProcW(struct qemu_syscall *call);
void qemu_CascadeChildWindows(struct qemu_syscall *call);
void qemu_CascadeWindows(struct qemu_syscall *call);
void qemu_ChangeClipboardChain(struct qemu_syscall *call);
void qemu_ChangeDisplaySettingsA(struct qemu_syscall *call);
void qemu_ChangeDisplaySettingsExA(struct qemu_syscall *call);
void qemu_ChangeDisplaySettingsExW(struct qemu_syscall *call);
void qemu_ChangeDisplaySettingsW(struct qemu_syscall *call);
void qemu_ChangeMenuA(struct qemu_syscall *call);
void qemu_ChangeMenuW(struct qemu_syscall *call);
void qemu_ChangeWindowMessageFilter(struct qemu_syscall *call);
void qemu_CharLowerA(struct qemu_syscall *call);
void qemu_CharLowerBuffA(struct qemu_syscall *call);
void qemu_CharLowerBuffW(struct qemu_syscall *call);
void qemu_CharLowerW(struct qemu_syscall *call);
void qemu_CharNextA(struct qemu_syscall *call);
void qemu_CharNextExA(struct qemu_syscall *call);
void qemu_CharNextExW(struct qemu_syscall *call);
void qemu_CharNextW(struct qemu_syscall *call);
void qemu_CharPrevA(struct qemu_syscall *call);
void qemu_CharPrevExA(struct qemu_syscall *call);
void qemu_CharPrevExW(struct qemu_syscall *call);
void qemu_CharPrevW(struct qemu_syscall *call);
void qemu_CharToOemA(struct qemu_syscall *call);
void qemu_CharToOemBuffA(struct qemu_syscall *call);
void qemu_CharToOemBuffW(struct qemu_syscall *call);
void qemu_CharToOemW(struct qemu_syscall *call);
void qemu_CharUpperA(struct qemu_syscall *call);
void qemu_CharUpperBuffA(struct qemu_syscall *call);
void qemu_CharUpperBuffW(struct qemu_syscall *call);
void qemu_CharUpperW(struct qemu_syscall *call);
void qemu_CheckDlgButton(struct qemu_syscall *call);
void qemu_CheckMenuItem(struct qemu_syscall *call);
void qemu_CheckMenuRadioItem(struct qemu_syscall *call);
void qemu_CheckRadioButton(struct qemu_syscall *call);
void qemu_ChildWindowFromPoint(struct qemu_syscall *call);
void qemu_ChildWindowFromPointEx(struct qemu_syscall *call);
void qemu_ClientToScreen(struct qemu_syscall *call);
void qemu_ClipCursor(struct qemu_syscall *call);
void qemu_CloseClipboard(struct qemu_syscall *call);
void qemu_CloseDesktop(struct qemu_syscall *call);
void qemu_CloseWindow(struct qemu_syscall *call);
void qemu_CloseWindowStation(struct qemu_syscall *call);
void qemu_CopyAcceleratorTableA(struct qemu_syscall *call);
void qemu_CopyAcceleratorTableW(struct qemu_syscall *call);
void qemu_CopyIcon(struct qemu_syscall *call);
void qemu_CopyImage(struct qemu_syscall *call);
void qemu_CopyRect(struct qemu_syscall *call);
void qemu_CountClipboardFormats(struct qemu_syscall *call);
void qemu_CreateAcceleratorTableA(struct qemu_syscall *call);
void qemu_CreateAcceleratorTableW(struct qemu_syscall *call);
void qemu_CreateCaret(struct qemu_syscall *call);
void qemu_CreateCursor(struct qemu_syscall *call);
void qemu_CreateDesktopA(struct qemu_syscall *call);
void qemu_CreateDesktopW(struct qemu_syscall *call);
void qemu_CreateDialogIndirectParamA(struct qemu_syscall *call);
void qemu_CreateDialogIndirectParamAorW(struct qemu_syscall *call);
void qemu_CreateDialogIndirectParamW(struct qemu_syscall *call);
void qemu_CreateDialogParamA(struct qemu_syscall *call);
void qemu_CreateDialogParamW(struct qemu_syscall *call);
void qemu_CreateIcon(struct qemu_syscall *call);
void qemu_CreateIconFromResource(struct qemu_syscall *call);
void qemu_CreateIconFromResourceEx(struct qemu_syscall *call);
void qemu_CreateIconIndirect(struct qemu_syscall *call);
void qemu_CreateMDIWindowA(struct qemu_syscall *call);
void qemu_CreateMDIWindowW(struct qemu_syscall *call);
void qemu_CreateMenu(struct qemu_syscall *call);
void qemu_CreatePopupMenu(struct qemu_syscall *call);
void qemu_CreateWindowExA(struct qemu_syscall *call);
void qemu_CreateWindowExW(struct qemu_syscall *call);
void qemu_CreateWindowStationA(struct qemu_syscall *call);
void qemu_CreateWindowStationW(struct qemu_syscall *call);
void qemu_DdeAbandonTransaction(struct qemu_syscall *call);
void qemu_DdeAccessData(struct qemu_syscall *call);
void qemu_DdeAddData(struct qemu_syscall *call);
void qemu_DdeClientTransaction(struct qemu_syscall *call);
void qemu_DdeCmpStringHandles(struct qemu_syscall *call);
void qemu_DdeConnect(struct qemu_syscall *call);
void qemu_DdeConnectList(struct qemu_syscall *call);
void qemu_DdeCreateDataHandle(struct qemu_syscall *call);
void qemu_DdeCreateStringHandleA(struct qemu_syscall *call);
void qemu_DdeCreateStringHandleW(struct qemu_syscall *call);
void qemu_DdeDisconnect(struct qemu_syscall *call);
void qemu_DdeDisconnectList(struct qemu_syscall *call);
void qemu_DdeEnableCallback(struct qemu_syscall *call);
void qemu_DdeFreeDataHandle(struct qemu_syscall *call);
void qemu_DdeFreeStringHandle(struct qemu_syscall *call);
void qemu_DdeGetData(struct qemu_syscall *call);
void qemu_DdeGetLastError(struct qemu_syscall *call);
void qemu_DdeImpersonateClient(struct qemu_syscall *call);
void qemu_DdeInitializeA(struct qemu_syscall *call);
void qemu_DdeInitializeW(struct qemu_syscall *call);
void qemu_DdeKeepStringHandle(struct qemu_syscall *call);
void qemu_DdeNameService(struct qemu_syscall *call);
void qemu_DdePostAdvise(struct qemu_syscall *call);
void qemu_DdeQueryConvInfo(struct qemu_syscall *call);
void qemu_DdeQueryNextServer(struct qemu_syscall *call);
void qemu_DdeQueryStringA(struct qemu_syscall *call);
void qemu_DdeQueryStringW(struct qemu_syscall *call);
void qemu_DdeReconnect(struct qemu_syscall *call);
void qemu_DdeSetQualityOfService(struct qemu_syscall *call);
void qemu_DdeUnaccessData(struct qemu_syscall *call);
void qemu_DdeUninitialize(struct qemu_syscall *call);
void qemu_DefDlgProcA(struct qemu_syscall *call);
void qemu_DefDlgProcW(struct qemu_syscall *call);
void qemu_DeferWindowPos(struct qemu_syscall *call);
void qemu_DefFrameProcA(struct qemu_syscall *call);
void qemu_DefFrameProcW(struct qemu_syscall *call);
void qemu_DefMDIChildProcA(struct qemu_syscall *call);
void qemu_DefMDIChildProcW(struct qemu_syscall *call);
void qemu_DefRawInputProc(struct qemu_syscall *call);
void qemu_DefWindowProcA(struct qemu_syscall *call);
void qemu_DefWindowProcW(struct qemu_syscall *call);
void qemu_DeleteMenu(struct qemu_syscall *call);
void qemu_DeregisterShellHookWindow(struct qemu_syscall *call);
void qemu_DestroyAcceleratorTable(struct qemu_syscall *call);
void qemu_DestroyCaret(struct qemu_syscall *call);
void qemu_DestroyCursor(struct qemu_syscall *call);
void qemu_DestroyIcon(struct qemu_syscall *call);
void qemu_DestroyMenu(struct qemu_syscall *call);
void qemu_DestroyWindow(struct qemu_syscall *call);
void qemu_DialogBoxIndirectParam(struct qemu_syscall *call);
void qemu_DialogBoxIndirectParamAorW(struct qemu_syscall *call);
void qemu_DialogBoxParam(struct qemu_syscall *call);
void qemu_DialogBoxParam(struct qemu_syscall *call);
void qemu_DisableProcessWindowsGhosting(struct qemu_syscall *call);
void qemu_DispatchMessageA(struct qemu_syscall *call);
void qemu_DispatchMessageW(struct qemu_syscall *call);
void qemu_DlgDirListA(struct qemu_syscall *call);
void qemu_DlgDirListComboBoxA(struct qemu_syscall *call);
void qemu_DlgDirListComboBoxW(struct qemu_syscall *call);
void qemu_DlgDirListW(struct qemu_syscall *call);
void qemu_DlgDirSelectComboBoxExA(struct qemu_syscall *call);
void qemu_DlgDirSelectComboBoxExW(struct qemu_syscall *call);
void qemu_DlgDirSelectExA(struct qemu_syscall *call);
void qemu_DlgDirSelectExW(struct qemu_syscall *call);
void qemu_DrawAnimatedRects(struct qemu_syscall *call);
void qemu_DrawCaption(struct qemu_syscall *call);
void qemu_DrawCaptionTempA(struct qemu_syscall *call);
void qemu_DrawCaptionTempW(struct qemu_syscall *call);
void qemu_DrawEdge(struct qemu_syscall *call);
void qemu_DrawFocusRect(struct qemu_syscall *call);
void qemu_DrawFrameControl(struct qemu_syscall *call);
void qemu_DrawIcon(struct qemu_syscall *call);
void qemu_DrawIconEx(struct qemu_syscall *call);
void qemu_DrawMenuBar(struct qemu_syscall *call);
void qemu_DrawMenuBarTemp(struct qemu_syscall *call);
void qemu_DrawStateA(struct qemu_syscall *call);
void qemu_DrawStateW(struct qemu_syscall *call);
void qemu_DrawTextA(struct qemu_syscall *call);
void qemu_DrawTextExA(struct qemu_syscall *call);
void qemu_DrawTextExW(struct qemu_syscall *call);
void qemu_DrawTextW(struct qemu_syscall *call);
void qemu_EmptyClipboard(struct qemu_syscall *call);
void qemu_EnableMenuItem(struct qemu_syscall *call);
void qemu_EnableScrollBar(struct qemu_syscall *call);
void qemu_EnableWindow(struct qemu_syscall *call);
void qemu_EndDeferWindowPos(struct qemu_syscall *call);
void qemu_EndDialog(struct qemu_syscall *call);
void qemu_EndMenu(struct qemu_syscall *call);
void qemu_EndPaint(struct qemu_syscall *call);
void qemu_EnumChildWindows(struct qemu_syscall *call);
void qemu_EnumClipboardFormats(struct qemu_syscall *call);
void qemu_EnumDesktopsA(struct qemu_syscall *call);
void qemu_EnumDesktopsW(struct qemu_syscall *call);
void qemu_EnumDesktopWindows(struct qemu_syscall *call);
void qemu_EnumDisplayDevicesA(struct qemu_syscall *call);
void qemu_EnumDisplayDevicesW(struct qemu_syscall *call);
void qemu_EnumDisplayMonitors(struct qemu_syscall *call);
void qemu_EnumDisplaySettingsA(struct qemu_syscall *call);
void qemu_EnumDisplaySettingsExA(struct qemu_syscall *call);
void qemu_EnumDisplaySettingsExW(struct qemu_syscall *call);
void qemu_EnumDisplaySettingsW(struct qemu_syscall *call);
void qemu_EnumPropsA(struct qemu_syscall *call);
void qemu_EnumPropsExA(struct qemu_syscall *call);
void qemu_EnumPropsExW(struct qemu_syscall *call);
void qemu_EnumPropsW(struct qemu_syscall *call);
void qemu_EnumThreadWindows(struct qemu_syscall *call);
void qemu_EnumWindows(struct qemu_syscall *call);
void qemu_EnumWindowStationsA(struct qemu_syscall *call);
void qemu_EnumWindowStationsW(struct qemu_syscall *call);
void qemu_EqualRect(struct qemu_syscall *call);
void qemu_ExcludeUpdateRgn(struct qemu_syscall *call);
void qemu_ExitWindowsEx(struct qemu_syscall *call);
void qemu_FillRect(struct qemu_syscall *call);
void qemu_FindWindowA(struct qemu_syscall *call);
void qemu_FindWindowExA(struct qemu_syscall *call);
void qemu_FindWindowExW(struct qemu_syscall *call);
void qemu_FindWindowW(struct qemu_syscall *call);
void qemu_FlashWindow(struct qemu_syscall *call);
void qemu_FlashWindowEx(struct qemu_syscall *call);
void qemu_FrameRect(struct qemu_syscall *call);
void qemu_FreeDDElParam(struct qemu_syscall *call);
void qemu_GetActiveWindow(struct qemu_syscall *call);
void qemu_GetAltTabInfoA(struct qemu_syscall *call);
void qemu_GetAltTabInfoW(struct qemu_syscall *call);
void qemu_GetAncestor(struct qemu_syscall *call);
void qemu_GetAppCompatFlags(struct qemu_syscall *call);
void qemu_GetAppCompatFlags2(struct qemu_syscall *call);
void qemu_GetAsyncKeyState(struct qemu_syscall *call);
void qemu_GetCapture(struct qemu_syscall *call);
void qemu_GetCaretBlinkTime(struct qemu_syscall *call);
void qemu_GetCaretPos(struct qemu_syscall *call);
void qemu_GetClassInfoA(struct qemu_syscall *call);
void qemu_GetClassInfoExA(struct qemu_syscall *call);
void qemu_GetClassInfoExW(struct qemu_syscall *call);
void qemu_GetClassInfoW(struct qemu_syscall *call);
void qemu_GetClassLongA(struct qemu_syscall *call);
void qemu_GetClassLongPtrA(struct qemu_syscall *call);
void qemu_GetClassLongPtrW(struct qemu_syscall *call);
void qemu_GetClassLongW(struct qemu_syscall *call);
void qemu_GetClassNameA(struct qemu_syscall *call);
void qemu_GetClassNameW(struct qemu_syscall *call);
void qemu_GetClassWord(struct qemu_syscall *call);
void qemu_GetClientRect(struct qemu_syscall *call);
void qemu_GetClipboardData(struct qemu_syscall *call);
void qemu_GetClipboardFormatNameA(struct qemu_syscall *call);
void qemu_GetClipboardFormatNameW(struct qemu_syscall *call);
void qemu_GetClipboardOwner(struct qemu_syscall *call);
void qemu_GetClipboardSequenceNumber(struct qemu_syscall *call);
void qemu_GetClipboardViewer(struct qemu_syscall *call);
void qemu_GetClipCursor(struct qemu_syscall *call);
void qemu_GetComboBoxInfo(struct qemu_syscall *call);
void qemu_GetCursor(struct qemu_syscall *call);
void qemu_GetCursorFrameInfo(struct qemu_syscall *call);
void qemu_GetCursorInfo(struct qemu_syscall *call);
void qemu_GetCursorPos(struct qemu_syscall *call);
void qemu_GetDC(struct qemu_syscall *call);
void qemu_GetDCEx(struct qemu_syscall *call);
void qemu_GetDesktopWindow(struct qemu_syscall *call);
void qemu_GetDialogBaseUnits(struct qemu_syscall *call);
void qemu_GetDisplayConfigBufferSizes(struct qemu_syscall *call);
void qemu_GetDlgCtrlID(struct qemu_syscall *call);
void qemu_GetDlgItem(struct qemu_syscall *call);
void qemu_GetDlgItemInt(struct qemu_syscall *call);
void qemu_GetDlgItemTextA(struct qemu_syscall *call);
void qemu_GetDlgItemTextW(struct qemu_syscall *call);
void qemu_GetDoubleClickTime(struct qemu_syscall *call);
void qemu_GetFocus(struct qemu_syscall *call);
void qemu_GetForegroundWindow(struct qemu_syscall *call);
void qemu_GetGestureConfig(struct qemu_syscall *call);
void qemu_GetGuiResources(struct qemu_syscall *call);
void qemu_GetGUIThreadInfo(struct qemu_syscall *call);
void qemu_GetIconInfo(struct qemu_syscall *call);
void qemu_GetIconInfoExA(struct qemu_syscall *call);
void qemu_GetIconInfoExW(struct qemu_syscall *call);
void qemu_GetInputState(struct qemu_syscall *call);
void qemu_GetInternalWindowPos(struct qemu_syscall *call);
void qemu_GetKBCodePage(struct qemu_syscall *call);
void qemu_GetKeyboardLayout(struct qemu_syscall *call);
void qemu_GetKeyboardLayoutList(struct qemu_syscall *call);
void qemu_GetKeyboardLayoutNameA(struct qemu_syscall *call);
void qemu_GetKeyboardLayoutNameW(struct qemu_syscall *call);
void qemu_GetKeyboardState(struct qemu_syscall *call);
void qemu_GetKeyboardType(struct qemu_syscall *call);
void qemu_GetKeyNameTextA(struct qemu_syscall *call);
void qemu_GetKeyNameTextW(struct qemu_syscall *call);
void qemu_GetKeyState(struct qemu_syscall *call);
void qemu_GetLastActivePopup(struct qemu_syscall *call);
void qemu_GetLastInputInfo(struct qemu_syscall *call);
void qemu_GetLayeredWindowAttributes(struct qemu_syscall *call);
void qemu_GetListBoxInfo(struct qemu_syscall *call);
void qemu_GetMenu(struct qemu_syscall *call);
void qemu_GetMenuBarInfo(struct qemu_syscall *call);
void qemu_GetMenuContextHelpId(struct qemu_syscall *call);
void qemu_GetMenuDefaultItem(struct qemu_syscall *call);
void qemu_GetMenuInfo(struct qemu_syscall *call);
void qemu_GetMenuItemCount(struct qemu_syscall *call);
void qemu_GetMenuItemID(struct qemu_syscall *call);
void qemu_GetMenuItemInfoA(struct qemu_syscall *call);
void qemu_GetMenuItemInfoW(struct qemu_syscall *call);
void qemu_GetMenuItemRect(struct qemu_syscall *call);
void qemu_GetMenuState(struct qemu_syscall *call);
void qemu_GetMenuStringA(struct qemu_syscall *call);
void qemu_GetMenuStringW(struct qemu_syscall *call);
void qemu_GetMessageA(struct qemu_syscall *call);
void qemu_GetMessageExtraInfo(struct qemu_syscall *call);
void qemu_GetMessagePos(struct qemu_syscall *call);
void qemu_GetMessageTime(struct qemu_syscall *call);
void qemu_GetMessageW(struct qemu_syscall *call);
void qemu_GetMonitorInfoA(struct qemu_syscall *call);
void qemu_GetMonitorInfoW(struct qemu_syscall *call);
void qemu_GetMouseMovePointsEx(struct qemu_syscall *call);
void qemu_GetNextDlgGroupItem(struct qemu_syscall *call);
void qemu_GetNextDlgTabItem(struct qemu_syscall *call);
void qemu_GetOpenClipboardWindow(struct qemu_syscall *call);
void qemu_GetParent(struct qemu_syscall *call);
void qemu_GetPhysicalCursorPos(struct qemu_syscall *call);
void qemu_GetPriorityClipboardFormat(struct qemu_syscall *call);
void qemu_GetProcessDefaultLayout(struct qemu_syscall *call);
void qemu_GetProcessWindowStation(struct qemu_syscall *call);
void qemu_GetProgmanWindow(struct qemu_syscall *call);
void qemu_GetPropA(struct qemu_syscall *call);
void qemu_GetPropW(struct qemu_syscall *call);
void qemu_GetQueueStatus(struct qemu_syscall *call);
void qemu_GetRawInputBuffer(struct qemu_syscall *call);
void qemu_GetRawInputData(struct qemu_syscall *call);
void qemu_GetRawInputDeviceInfoA(struct qemu_syscall *call);
void qemu_GetRawInputDeviceInfoW(struct qemu_syscall *call);
void qemu_GetRawInputDeviceList(struct qemu_syscall *call);
void qemu_GetRegisteredRawInputDevices(struct qemu_syscall *call);
void qemu_GetScrollBarInfo(struct qemu_syscall *call);
void qemu_GetScrollInfo(struct qemu_syscall *call);
void qemu_GetScrollPos(struct qemu_syscall *call);
void qemu_GetScrollRange(struct qemu_syscall *call);
void qemu_GetShellWindow(struct qemu_syscall *call);
void qemu_GetSubMenu(struct qemu_syscall *call);
void qemu_GetSysColor(struct qemu_syscall *call);
void qemu_GetSysColorBrush(struct qemu_syscall *call);
void qemu_GetSystemMenu(struct qemu_syscall *call);
void qemu_GetSystemMetrics(struct qemu_syscall *call);
void qemu_GetTabbedTextExtentA(struct qemu_syscall *call);
void qemu_GetTabbedTextExtentW(struct qemu_syscall *call);
void qemu_GetTaskmanWindow(struct qemu_syscall *call);
void qemu_GetThreadDesktop(struct qemu_syscall *call);
void qemu_GetTitleBarInfo(struct qemu_syscall *call);
void qemu_GetTopWindow(struct qemu_syscall *call);
void qemu_GetUpdatedClipboardFormats(struct qemu_syscall *call);
void qemu_GetUpdateRect(struct qemu_syscall *call);
void qemu_GetUpdateRgn(struct qemu_syscall *call);
void qemu_GetUserObjectInformationA(struct qemu_syscall *call);
void qemu_GetUserObjectInformationW(struct qemu_syscall *call);
void qemu_GetUserObjectSecurity(struct qemu_syscall *call);
void qemu_GetWindow(struct qemu_syscall *call);
void qemu_GetWindowContextHelpId(struct qemu_syscall *call);
void qemu_GetWindowDC(struct qemu_syscall *call);
void qemu_GetWindowInfo(struct qemu_syscall *call);
void qemu_GetWindowLongA(struct qemu_syscall *call);
void qemu_GetWindowLongPtrA(struct qemu_syscall *call);
void qemu_GetWindowLongPtrW(struct qemu_syscall *call);
void qemu_GetWindowLongW(struct qemu_syscall *call);
void qemu_GetWindowModuleFileNameA(struct qemu_syscall *call);
void qemu_GetWindowModuleFileNameW(struct qemu_syscall *call);
void qemu_GetWindowPlacement(struct qemu_syscall *call);
void qemu_GetWindowRect(struct qemu_syscall *call);
void qemu_GetWindowRgn(struct qemu_syscall *call);
void qemu_GetWindowRgnBox(struct qemu_syscall *call);
void qemu_GetWindowTextA(struct qemu_syscall *call);
void qemu_GetWindowTextLengthA(struct qemu_syscall *call);
void qemu_GetWindowTextLengthW(struct qemu_syscall *call);
void qemu_GetWindowTextW(struct qemu_syscall *call);
void qemu_GetWindowThreadProcessId(struct qemu_syscall *call);
void qemu_GetWindowWord(struct qemu_syscall *call);
void qemu_GrayStringA(struct qemu_syscall *call);
void qemu_GrayStringW(struct qemu_syscall *call);
void qemu_HideCaret(struct qemu_syscall *call);
void qemu_HiliteMenuItem(struct qemu_syscall *call);
void qemu_ImpersonateDdeClientWindow(struct qemu_syscall *call);
void qemu_InflateRect(struct qemu_syscall *call);
void qemu_InSendMessage(struct qemu_syscall *call);
void qemu_InSendMessageEx(struct qemu_syscall *call);
void qemu_InsertMenuA(struct qemu_syscall *call);
void qemu_InsertMenuItemA(struct qemu_syscall *call);
void qemu_InsertMenuItemW(struct qemu_syscall *call);
void qemu_InsertMenuW(struct qemu_syscall *call);
void qemu_InternalGetWindowText(struct qemu_syscall *call);
void qemu_IntersectRect(struct qemu_syscall *call);
void qemu_InvalidateRect(struct qemu_syscall *call);
void qemu_InvalidateRgn(struct qemu_syscall *call);
void qemu_InvertRect(struct qemu_syscall *call);
void qemu_IsCharAlphaA(struct qemu_syscall *call);
void qemu_IsCharAlphaNumericA(struct qemu_syscall *call);
void qemu_IsCharAlphaNumericW(struct qemu_syscall *call);
void qemu_IsCharAlphaW(struct qemu_syscall *call);
void qemu_IsCharLowerA(struct qemu_syscall *call);
void qemu_IsCharLowerW(struct qemu_syscall *call);
void qemu_IsCharUpperA(struct qemu_syscall *call);
void qemu_IsCharUpperW(struct qemu_syscall *call);
void qemu_IsChild(struct qemu_syscall *call);
void qemu_IsClipboardFormatAvailable(struct qemu_syscall *call);
void qemu_IsDialogMessageA(struct qemu_syscall *call);
void qemu_IsDialogMessageW(struct qemu_syscall *call);
void qemu_IsDlgButtonChecked(struct qemu_syscall *call);
void qemu_IsGUIThread(struct qemu_syscall *call);
void qemu_IsHungAppWindow(struct qemu_syscall *call);
void qemu_IsIconic(struct qemu_syscall *call);
void qemu_IsMenu(struct qemu_syscall *call);
void qemu_IsProcessDPIAware(struct qemu_syscall *call);
void qemu_IsRectEmpty(struct qemu_syscall *call);
void qemu_IsTouchWindow(struct qemu_syscall *call);
void qemu_IsWindow(struct qemu_syscall *call);
void qemu_IsWindowEnabled(struct qemu_syscall *call);
void qemu_IsWindowRedirectedForPrint(struct qemu_syscall *call);
void qemu_IsWindowUnicode(struct qemu_syscall *call);
void qemu_IsWindowVisible(struct qemu_syscall *call);
void qemu_IsWinEventHookInstalled(struct qemu_syscall *call);
void qemu_IsZoomed(struct qemu_syscall *call);
void qemu_keybd_event(struct qemu_syscall *call);
void qemu_KillSystemTimer(struct qemu_syscall *call);
void qemu_KillTimer(struct qemu_syscall *call);
void qemu_LoadAcceleratorsA(struct qemu_syscall *call);
void qemu_LoadAcceleratorsW(struct qemu_syscall *call);
void qemu_LoadBitmapA(struct qemu_syscall *call);
void qemu_LoadBitmapW(struct qemu_syscall *call);
void qemu_LoadCursorA(struct qemu_syscall *call);
void qemu_LoadCursorFromFileA(struct qemu_syscall *call);
void qemu_LoadCursorFromFileW(struct qemu_syscall *call);
void qemu_LoadCursorW(struct qemu_syscall *call);
void qemu_LoadIconA(struct qemu_syscall *call);
void qemu_LoadIconW(struct qemu_syscall *call);
void qemu_LoadImageA(struct qemu_syscall *call);
void qemu_LoadImageW(struct qemu_syscall *call);
void qemu_LoadKeyboardLayoutA(struct qemu_syscall *call);
void qemu_LoadKeyboardLayoutW(struct qemu_syscall *call);
void qemu_LoadLocalFonts(struct qemu_syscall *call);
void qemu_LoadMenuA(struct qemu_syscall *call);
void qemu_LoadMenuIndirectA(struct qemu_syscall *call);
void qemu_LoadMenuIndirectW(struct qemu_syscall *call);
void qemu_LoadMenuW(struct qemu_syscall *call);
void qemu_LoadStringA(struct qemu_syscall *call);
void qemu_LoadStringW(struct qemu_syscall *call);
void qemu_LockSetForegroundWindow(struct qemu_syscall *call);
void qemu_LockWindowUpdate(struct qemu_syscall *call);
void qemu_LockWorkStation(struct qemu_syscall *call);
void qemu_LogicalToPhysicalPoint(struct qemu_syscall *call);
void qemu_LookupIconIdFromDirectory(struct qemu_syscall *call);
void qemu_LookupIconIdFromDirectoryEx(struct qemu_syscall *call);
void qemu_MapDialogRect(struct qemu_syscall *call);
void qemu_MapVirtualKeyA(struct qemu_syscall *call);
void qemu_MapVirtualKeyExA(struct qemu_syscall *call);
void qemu_MapVirtualKeyExW(struct qemu_syscall *call);
void qemu_MapVirtualKeyW(struct qemu_syscall *call);
void qemu_MapWindowPoints(struct qemu_syscall *call);
void qemu_MessageBeep(struct qemu_syscall *call);
void qemu_MessageBoxA(struct qemu_syscall *call);
void qemu_MessageBoxExA(struct qemu_syscall *call);
void qemu_MessageBoxExW(struct qemu_syscall *call);
void qemu_MessageBoxIndirectA(struct qemu_syscall *call);
void qemu_MessageBoxIndirectW(struct qemu_syscall *call);
void qemu_MessageBoxTimeoutA(struct qemu_syscall *call);
void qemu_MessageBoxTimeoutW(struct qemu_syscall *call);
void qemu_MessageBoxW(struct qemu_syscall *call);
void qemu_ModifyMenuA(struct qemu_syscall *call);
void qemu_ModifyMenuW(struct qemu_syscall *call);
void qemu_MonitorFromPoint(struct qemu_syscall *call);
void qemu_MonitorFromRect(struct qemu_syscall *call);
void qemu_MonitorFromWindow(struct qemu_syscall *call);
void qemu_mouse_event(struct qemu_syscall *call);
void qemu_MoveWindow(struct qemu_syscall *call);
void qemu_MsgWaitForMultipleObjects(struct qemu_syscall *call);
void qemu_MsgWaitForMultipleObjectsEx(struct qemu_syscall *call);
void qemu_NotifyWinEvent(struct qemu_syscall *call);
void qemu_OemKeyScan(struct qemu_syscall *call);
void qemu_OemToCharA(struct qemu_syscall *call);
void qemu_OemToCharBuffA(struct qemu_syscall *call);
void qemu_OemToCharBuffW(struct qemu_syscall *call);
void qemu_OemToCharW(struct qemu_syscall *call);
void qemu_OffsetRect(struct qemu_syscall *call);
void qemu_OpenClipboard(struct qemu_syscall *call);
void qemu_OpenDesktopA(struct qemu_syscall *call);
void qemu_OpenDesktopW(struct qemu_syscall *call);
void qemu_OpenIcon(struct qemu_syscall *call);
void qemu_OpenInputDesktop(struct qemu_syscall *call);
void qemu_OpenWindowStationA(struct qemu_syscall *call);
void qemu_OpenWindowStationW(struct qemu_syscall *call);
void qemu_PackDDElParam(struct qemu_syscall *call);
void qemu_PaintDesktop(struct qemu_syscall *call);
void qemu_PeekMessageA(struct qemu_syscall *call);
void qemu_PeekMessageW(struct qemu_syscall *call);
void qemu_PhysicalToLogicalPoint(struct qemu_syscall *call);
void qemu_PostMessageA(struct qemu_syscall *call);
void qemu_PostMessageW(struct qemu_syscall *call);
void qemu_PostQuitMessage(struct qemu_syscall *call);
void qemu_PostThreadMessageA(struct qemu_syscall *call);
void qemu_PostThreadMessageW(struct qemu_syscall *call);
void qemu_PrintWindow(struct qemu_syscall *call);
void qemu_PrivateExtractIconExA(struct qemu_syscall *call);
void qemu_PrivateExtractIconExW(struct qemu_syscall *call);
void qemu_PrivateExtractIconsA(struct qemu_syscall *call);
void qemu_PrivateExtractIconsW(struct qemu_syscall *call);
void qemu_PtInRect(struct qemu_syscall *call);
void qemu_QueryDisplayConfig(struct qemu_syscall *call);
void qemu_RealChildWindowFromPoint(struct qemu_syscall *call);
void qemu_RealGetWindowClassA(struct qemu_syscall *call);
void qemu_RealGetWindowClassW(struct qemu_syscall *call);
void qemu_RedrawWindow(struct qemu_syscall *call);
void qemu_RegisterClassEx(struct qemu_syscall *call);
void qemu_RegisterClipboardFormatA(struct qemu_syscall *call);
void qemu_RegisterClipboardFormatW(struct qemu_syscall *call);
void qemu_RegisterDeviceNotificationA(struct qemu_syscall *call);
void qemu_RegisterDeviceNotificationW(struct qemu_syscall *call);
void qemu_RegisterHotKey(struct qemu_syscall *call);
void qemu_RegisterLogonProcess(struct qemu_syscall *call);
void qemu_RegisterPowerSettingNotification(struct qemu_syscall *call);
void qemu_RegisterRawInputDevices(struct qemu_syscall *call);
void qemu_RegisterServicesProcess(struct qemu_syscall *call);
void qemu_RegisterShellHookWindow(struct qemu_syscall *call);
void qemu_RegisterSystemThread(struct qemu_syscall *call);
void qemu_RegisterTasklist(struct qemu_syscall *call);
void qemu_RegisterTouchWindow(struct qemu_syscall *call);
void qemu_RegisterWindowMessageA(struct qemu_syscall *call);
void qemu_RegisterWindowMessageW(struct qemu_syscall *call);
void qemu_ReleaseCapture(struct qemu_syscall *call);
void qemu_ReleaseDC(struct qemu_syscall *call);
void qemu_RemoveClipboardFormatListener(struct qemu_syscall *call);
void qemu_RemoveMenu(struct qemu_syscall *call);
void qemu_RemovePropA(struct qemu_syscall *call);
void qemu_RemovePropW(struct qemu_syscall *call);
void qemu_ReplyMessage(struct qemu_syscall *call);
void qemu_ReuseDDElParam(struct qemu_syscall *call);
void qemu_ScreenToClient(struct qemu_syscall *call);
void qemu_ScrollChildren(struct qemu_syscall *call);
void qemu_ScrollDC(struct qemu_syscall *call);
void qemu_ScrollWindow(struct qemu_syscall *call);
void qemu_ScrollWindowEx(struct qemu_syscall *call);
void qemu_SendDlgItemMessageA(struct qemu_syscall *call);
void qemu_SendDlgItemMessageW(struct qemu_syscall *call);
void qemu_SendIMEMessageExA(struct qemu_syscall *call);
void qemu_SendIMEMessageExW(struct qemu_syscall *call);
void qemu_SendInput(struct qemu_syscall *call);
void qemu_SendMessageA(struct qemu_syscall *call);
void qemu_SendMessageCallbackA(struct qemu_syscall *call);
void qemu_SendMessageCallbackW(struct qemu_syscall *call);
void qemu_SendMessageTimeoutA(struct qemu_syscall *call);
void qemu_SendMessageTimeoutW(struct qemu_syscall *call);
void qemu_SendMessageW(struct qemu_syscall *call);
void qemu_SendNotifyMessageA(struct qemu_syscall *call);
void qemu_SendNotifyMessageW(struct qemu_syscall *call);
void qemu_SetActiveWindow(struct qemu_syscall *call);
void qemu_SetCapture(struct qemu_syscall *call);
void qemu_SetCaretBlinkTime(struct qemu_syscall *call);
void qemu_SetCaretPos(struct qemu_syscall *call);
void qemu_SetClassLongA(struct qemu_syscall *call);
void qemu_SetClassLongPtrA(struct qemu_syscall *call);
void qemu_SetClassLongPtrW(struct qemu_syscall *call);
void qemu_SetClassLongW(struct qemu_syscall *call);
void qemu_SetClassWord(struct qemu_syscall *call);
void qemu_SetClipboardData(struct qemu_syscall *call);
void qemu_SetClipboardViewer(struct qemu_syscall *call);
void qemu_SetCoalescableTimer(struct qemu_syscall *call);
void qemu_SetCursor(struct qemu_syscall *call);
void qemu_SetCursorPos(struct qemu_syscall *call);
void qemu_SetDebugErrorLevel(struct qemu_syscall *call);
void qemu_SetDeskWallPaper(struct qemu_syscall *call);
void qemu_SetDlgItemInt(struct qemu_syscall *call);
void qemu_SetDlgItemTextA(struct qemu_syscall *call);
void qemu_SetDlgItemTextW(struct qemu_syscall *call);
void qemu_SetDoubleClickTime(struct qemu_syscall *call);
void qemu_SetFocus(struct qemu_syscall *call);
void qemu_SetForegroundWindow(struct qemu_syscall *call);
void qemu_SetGestureConfig(struct qemu_syscall *call);
void qemu_SetInternalWindowPos(struct qemu_syscall *call);
void qemu_SetKeyboardState(struct qemu_syscall *call);
void qemu_SetLastErrorEx(struct qemu_syscall *call);
void qemu_SetLayeredWindowAttributes(struct qemu_syscall *call);
void qemu_SetLogonNotifyWindow(struct qemu_syscall *call);
void qemu_SetMenu(struct qemu_syscall *call);
void qemu_SetMenuContextHelpId(struct qemu_syscall *call);
void qemu_SetMenuDefaultItem(struct qemu_syscall *call);
void qemu_SetMenuInfo(struct qemu_syscall *call);
void qemu_SetMenuItemBitmaps(struct qemu_syscall *call);
void qemu_SetMenuItemInfoA(struct qemu_syscall *call);
void qemu_SetMenuItemInfoW(struct qemu_syscall *call);
void qemu_SetMessageExtraInfo(struct qemu_syscall *call);
void qemu_SetMessageQueue(struct qemu_syscall *call);
void qemu_SetParent(struct qemu_syscall *call);
void qemu_SetPhysicalCursorPos(struct qemu_syscall *call);
void qemu_SetProcessDefaultLayout(struct qemu_syscall *call);
void qemu_SetProcessDPIAware(struct qemu_syscall *call);
void qemu_SetProcessWindowStation(struct qemu_syscall *call);
void qemu_SetProgmanWindow(struct qemu_syscall *call);
void qemu_SetPropA(struct qemu_syscall *call);
void qemu_SetPropW(struct qemu_syscall *call);
void qemu_SetRect(struct qemu_syscall *call);
void qemu_SetRectEmpty(struct qemu_syscall *call);
void qemu_SetScrollInfo(struct qemu_syscall *call);
void qemu_SetScrollPos(struct qemu_syscall *call);
void qemu_SetScrollRange(struct qemu_syscall *call);
void qemu_SetShellWindow(struct qemu_syscall *call);
void qemu_SetShellWindowEx(struct qemu_syscall *call);
void qemu_SetSysColors(struct qemu_syscall *call);
void qemu_SetSysColorsTemp(struct qemu_syscall *call);
void qemu_SetSystemCursor(struct qemu_syscall *call);
void qemu_SetSystemMenu(struct qemu_syscall *call);
void qemu_SetSystemTimer(struct qemu_syscall *call);
void qemu_SetTaskmanWindow(struct qemu_syscall *call);
void qemu_SetThreadDesktop(struct qemu_syscall *call);
void qemu_SetTimer(struct qemu_syscall *call);
void qemu_SetUserObjectInformationA(struct qemu_syscall *call);
void qemu_SetUserObjectInformationW(struct qemu_syscall *call);
void qemu_SetUserObjectSecurity(struct qemu_syscall *call);
void qemu_SetWindowContextHelpId(struct qemu_syscall *call);
void qemu_SetWindowLongA(struct qemu_syscall *call);
void qemu_SetWindowLongPtrA(struct qemu_syscall *call);
void qemu_SetWindowLongPtrW(struct qemu_syscall *call);
void qemu_SetWindowLongW(struct qemu_syscall *call);
void qemu_SetWindowPlacement(struct qemu_syscall *call);
void qemu_SetWindowPos(struct qemu_syscall *call);
void qemu_SetWindowRgn(struct qemu_syscall *call);
void qemu_SetWindowsHookA(struct qemu_syscall *call);
void qemu_SetWindowsHookExA(struct qemu_syscall *call);
void qemu_SetWindowsHookExW(struct qemu_syscall *call);
void qemu_SetWindowsHookW(struct qemu_syscall *call);
void qemu_SetWindowStationUser(struct qemu_syscall *call);
void qemu_SetWindowTextA(struct qemu_syscall *call);
void qemu_SetWindowTextW(struct qemu_syscall *call);
void qemu_SetWindowWord(struct qemu_syscall *call);
void qemu_SetWinEventHook(struct qemu_syscall *call);
void qemu_ShowCaret(struct qemu_syscall *call);
void qemu_ShowCursor(struct qemu_syscall *call);
void qemu_ShowOwnedPopups(struct qemu_syscall *call);
void qemu_ShowScrollBar(struct qemu_syscall *call);
void qemu_ShowWindow(struct qemu_syscall *call);
void qemu_ShowWindowAsync(struct qemu_syscall *call);
void qemu_ShutdownBlockReasonCreate(struct qemu_syscall *call);
void qemu_ShutdownBlockReasonDestroy(struct qemu_syscall *call);
void qemu_SubtractRect(struct qemu_syscall *call);
void qemu_SwapMouseButton(struct qemu_syscall *call);
void qemu_SwitchDesktop(struct qemu_syscall *call);
void qemu_SwitchToThisWindow(struct qemu_syscall *call);
void qemu_SystemParametersInfoA(struct qemu_syscall *call);
void qemu_SystemParametersInfoW(struct qemu_syscall *call);
void qemu_TabbedTextOutA(struct qemu_syscall *call);
void qemu_TabbedTextOutW(struct qemu_syscall *call);
void qemu_TileChildWindows(struct qemu_syscall *call);
void qemu_TileWindows(struct qemu_syscall *call);
void qemu_ToAscii(struct qemu_syscall *call);
void qemu_ToAsciiEx(struct qemu_syscall *call);
void qemu_ToUnicode(struct qemu_syscall *call);
void qemu_ToUnicodeEx(struct qemu_syscall *call);
void qemu_TrackMouseEvent(struct qemu_syscall *call);
void qemu_TrackPopupMenu(struct qemu_syscall *call);
void qemu_TrackPopupMenuEx(struct qemu_syscall *call);
void qemu_TranslateAcceleratorA(struct qemu_syscall *call);
void qemu_TranslateAcceleratorW(struct qemu_syscall *call);
void qemu_TranslateMDISysAccel(struct qemu_syscall *call);
void qemu_TranslateMessage(struct qemu_syscall *call);
void qemu_UnhookWindowsHook(struct qemu_syscall *call);
void qemu_UnhookWindowsHookEx(struct qemu_syscall *call);
void qemu_UnhookWinEvent(struct qemu_syscall *call);
void qemu_UnionRect(struct qemu_syscall *call);
void qemu_UnloadKeyboardLayout(struct qemu_syscall *call);
void qemu_UnpackDDElParam(struct qemu_syscall *call);
void qemu_UnregisterClass(struct qemu_syscall *call);
void qemu_UnregisterClass(struct qemu_syscall *call);
void qemu_UnregisterDeviceNotification(struct qemu_syscall *call);
void qemu_UnregisterHotKey(struct qemu_syscall *call);
void qemu_UnregisterPowerSettingNotification(struct qemu_syscall *call);
void qemu_UpdateLayeredWindow(struct qemu_syscall *call);
void qemu_UpdateLayeredWindowIndirect(struct qemu_syscall *call);
void qemu_UpdateWindow(struct qemu_syscall *call);
void qemu_User32InitializeImmEntryTable(struct qemu_syscall *call);
void qemu_UserHandleGrantAccess(struct qemu_syscall *call);
void qemu_UserRealizePalette(struct qemu_syscall *call);
void qemu_UserSignalProc(struct qemu_syscall *call);
void qemu_ValidateRect(struct qemu_syscall *call);
void qemu_ValidateRgn(struct qemu_syscall *call);
void qemu_VkKeyScanA(struct qemu_syscall *call);
void qemu_VkKeyScanExA(struct qemu_syscall *call);
void qemu_VkKeyScanExW(struct qemu_syscall *call);
void qemu_VkKeyScanW(struct qemu_syscall *call);
void qemu_WaitForInputIdle(struct qemu_syscall *call);
void qemu_WaitMessage(struct qemu_syscall *call);
void qemu_WindowFromDC(struct qemu_syscall *call);
void qemu_WindowFromPoint(struct qemu_syscall *call);
void qemu_WinHelpA(struct qemu_syscall *call);
void qemu_WinHelpW(struct qemu_syscall *call);
void qemu_WINNLSEnableIME(struct qemu_syscall *call);
void qemu_WINNLSGetEnableStatus(struct qemu_syscall *call);
void qemu_WINNLSGetIMEHotkey(struct qemu_syscall *call);

extern uint64_t reverse_wndproc_func;

struct wndproc_wrapper
{
    int32_t ldrx4;
    int32_t ldrx5;
    int32_t br;
    void *selfptr;
    void *host_proc;
    uint64_t guest_proc;
};

extern struct wndproc_wrapper *wndproc_wrappers;
extern unsigned int wndproc_wrapper_count;

/* Reverse wrapper for Wine's wndprocs. */
extern uint64_t guest_wndproc_wrapper;

struct reverse_wndproc_wrapper
{
    char code[0x20];
    uint64_t guest_proc;
    void *host_proc;
};

#define REVERSE_WNDPROC_WRAPPER_COUNT 1024
extern struct reverse_wndproc_wrapper
        reverse_wndproc_wrappers[REVERSE_WNDPROC_WRAPPER_COUNT];

WNDPROC wndproc_guest_to_host(uint64_t guest_func);
uint64_t wndproc_host_to_guest(WNDPROC host_func);

DWORD user32_tls;

HMODULE wrapper_mod, host_mod, guest_mod;

extern struct wine_rb_tree win_event_tree;
int win_event_compare(const void *key, const struct wine_rb_entry *entry);
extern uint64_t guest_win_event_wrapper;

#endif

#endif
