#include "StdAfx.h"
#include "WndStyles.h"

#include <CommCtrl.h>

namespace WndStyles
{
    namespace
    {
#define DEF_STYLE(style)    {style, L#style},
        struct stStyleInfo
        {
            DWORD   dwStyle;
            LPCTSTR szName;
        };

        // Window Styles
        const stStyleInfo g_WindowStylesData[] =
        {
            // Common
            // DEF_STYLE(WS_OVERLAPPEDWINDOW)
            // DEF_STYLE(WS_POPUPWINDOW)

            DEF_STYLE(WS_OVERLAPPED)
            DEF_STYLE(WS_POPUP)
            DEF_STYLE(WS_CHILD)
            DEF_STYLE(WS_MINIMIZE)
            DEF_STYLE(WS_VISIBLE)
            DEF_STYLE(WS_DISABLED)
            DEF_STYLE(WS_CLIPSIBLINGS)
            DEF_STYLE(WS_CLIPCHILDREN)
            DEF_STYLE(WS_MAXIMIZE)
            DEF_STYLE(WS_CAPTION)
            DEF_STYLE(WS_BORDER)
            DEF_STYLE(WS_DLGFRAME)
            DEF_STYLE(WS_VSCROLL)
            DEF_STYLE(WS_HSCROLL)
            DEF_STYLE(WS_SYSMENU)
            DEF_STYLE(WS_THICKFRAME)
            DEF_STYLE(WS_GROUP)
            DEF_STYLE(WS_TABSTOP)

            DEF_STYLE(WS_MINIMIZEBOX)
            DEF_STYLE(WS_MAXIMIZEBOX)
        };

        // Windows Extended Styles
        const stStyleInfo g_WindowExtendedStylesData[] =
        {
            // Common
            // DEF_STYLE(WS_EX_OVERLAPPEDWINDOW)
            // DEF_STYLE(WS_EX_PALETTEWINDOW)

            DEF_STYLE(WS_EX_DLGMODALFRAME)
            DEF_STYLE(WS_EX_NOPARENTNOTIFY)
            DEF_STYLE(WS_EX_TOPMOST)
            DEF_STYLE(WS_EX_ACCEPTFILES)
            DEF_STYLE(WS_EX_TRANSPARENT)
            DEF_STYLE(WS_EX_MDICHILD)
            DEF_STYLE(WS_EX_TOOLWINDOW)
            DEF_STYLE(WS_EX_WINDOWEDGE)
            DEF_STYLE(WS_EX_CLIENTEDGE)
            DEF_STYLE(WS_EX_CONTEXTHELP)

            DEF_STYLE(WS_EX_RIGHT)
            DEF_STYLE(WS_EX_LEFT)
            DEF_STYLE(WS_EX_RTLREADING)
            DEF_STYLE(WS_EX_LTRREADING)
            DEF_STYLE(WS_EX_LEFTSCROLLBAR)
            DEF_STYLE(WS_EX_RIGHTSCROLLBAR)

            DEF_STYLE(WS_EX_CONTROLPARENT)
            DEF_STYLE(WS_EX_STATICEDGE)
            DEF_STYLE(WS_EX_APPWINDOW)

            DEF_STYLE(WS_EX_LAYERED)

            DEF_STYLE(WS_EX_NOINHERITLAYOUT)
            DEF_STYLE(WS_EX_LAYOUTRTL)

            DEF_STYLE(WS_EX_COMPOSITED)

            DEF_STYLE(WS_EX_NOACTIVATE)
        };

        // Button
        const stStyleInfo g_ButtonStylesData[] =
        {
            DEF_STYLE(BS_PUSHBUTTON)
            DEF_STYLE(BS_DEFPUSHBUTTON)
            DEF_STYLE(BS_CHECKBOX)
            DEF_STYLE(BS_AUTOCHECKBOX)
            DEF_STYLE(BS_RADIOBUTTON)
            DEF_STYLE(BS_3STATE)
            DEF_STYLE(BS_AUTO3STATE)
            DEF_STYLE(BS_GROUPBOX)
            DEF_STYLE(BS_USERBUTTON)
            DEF_STYLE(BS_AUTORADIOBUTTON)
            DEF_STYLE(BS_PUSHBOX)
            DEF_STYLE(BS_OWNERDRAW)
            DEF_STYLE(BS_TYPEMASK)
            DEF_STYLE(BS_LEFTTEXT)

            DEF_STYLE(BS_TEXT)
            DEF_STYLE(BS_ICON)
            DEF_STYLE(BS_BITMAP)
            DEF_STYLE(BS_LEFT)
            DEF_STYLE(BS_RIGHT)
            DEF_STYLE(BS_CENTER)
            DEF_STYLE(BS_TOP)
            DEF_STYLE(BS_BOTTOM)
            DEF_STYLE(BS_VCENTER)
            DEF_STYLE(BS_PUSHLIKE)
            DEF_STYLE(BS_MULTILINE)
            DEF_STYLE(BS_NOTIFY)
            DEF_STYLE(BS_FLAT)
            DEF_STYLE(BS_RIGHTBUTTON)

#if _WIN32_WINNT < 0x0600
#define BS_SPLITBUTTON          0x0000000CL
#define BS_DEFSPLITBUTTON       0x0000000DL
#define BS_COMMANDLINK          0x0000000EL
#define BS_DEFCOMMANDLINK       0x0000000FL
#endif

            DEF_STYLE(BS_SPLITBUTTON)
            DEF_STYLE(BS_DEFSPLITBUTTON)
            DEF_STYLE(BS_COMMANDLINK)
            DEF_STYLE(BS_DEFCOMMANDLINK)
        };

        // Dialog
        const stStyleInfo g_DialogStylesData[] =
        {
            DEF_STYLE(DS_ABSALIGN)
            DEF_STYLE(DS_SYSMODAL)
            DEF_STYLE(DS_LOCALEDIT)
            DEF_STYLE(DS_SETFONT)
            DEF_STYLE(DS_MODALFRAME)
            DEF_STYLE(DS_NOIDLEMSG)
            DEF_STYLE(DS_SETFOREGROUND)

            DEF_STYLE(DS_3DLOOK)
            DEF_STYLE(DS_FIXEDSYS)
            DEF_STYLE(DS_NOFAILCREATE)
            DEF_STYLE(DS_CONTROL)
            DEF_STYLE(DS_CENTER)
            DEF_STYLE(DS_CENTERMOUSE)
            DEF_STYLE(DS_CONTEXTHELP)
        };

        // Edit
        const stStyleInfo g_EditStylesData[] =
        {
            DEF_STYLE(ES_LEFT)
            DEF_STYLE(ES_CENTER)
            DEF_STYLE(ES_RIGHT)
            DEF_STYLE(ES_MULTILINE)
            DEF_STYLE(ES_UPPERCASE)
            DEF_STYLE(ES_LOWERCASE)
            DEF_STYLE(ES_PASSWORD)
            DEF_STYLE(ES_AUTOVSCROLL)
            DEF_STYLE(ES_AUTOHSCROLL)
            DEF_STYLE(ES_NOHIDESEL)
            DEF_STYLE(ES_OEMCONVERT)
            DEF_STYLE(ES_READONLY)
            DEF_STYLE(ES_WANTRETURN)
            DEF_STYLE(ES_NUMBER)

            // RichEdit Only
            DEF_STYLE(ES_DISABLENOSCROLL)
            DEF_STYLE(ES_EX_NOCALLOLEINIT)
            DEF_STYLE(ES_NOIME)
            DEF_STYLE(ES_NOOLEDRAGDROP)
            DEF_STYLE(ES_SAVESEL)
            DEF_STYLE(ES_SELECTIONBAR)
            DEF_STYLE(ES_SELFIME)
            DEF_STYLE(ES_SUNKEN)
            DEF_STYLE(ES_VERTICAL)
        };

        // ComboBox 
        const stStyleInfo g_ComboBoxStylesData[] =
        {
            DEF_STYLE(CBS_SIMPLE)
            DEF_STYLE(CBS_DROPDOWN)
            DEF_STYLE(CBS_DROPDOWNLIST)
            DEF_STYLE(CBS_OWNERDRAWFIXED)
            DEF_STYLE(CBS_OWNERDRAWVARIABLE)
            DEF_STYLE(CBS_AUTOHSCROLL)
            DEF_STYLE(CBS_OEMCONVERT)
            DEF_STYLE(CBS_SORT)
            DEF_STYLE(CBS_HASSTRINGS)
            DEF_STYLE(CBS_NOINTEGRALHEIGHT)
            DEF_STYLE(CBS_DISABLENOSCROLL)

            DEF_STYLE(CBS_UPPERCASE)
            DEF_STYLE(CBS_LOWERCASE)
        };

        // ComboBox Extended
        const stStyleInfo g_ComboBoxExtendedStylesData[] =
        {
            DEF_STYLE(CBES_EX_CASESENSITIVE)
            DEF_STYLE(CBES_EX_NOEDITIMAGE)
            DEF_STYLE(CBES_EX_NOEDITIMAGE)
            DEF_STYLE(CBES_EX_NOSIZELIMIT)
            DEF_STYLE(CBES_EX_PATHWORDBREAKPROC)

#if (_WIN32_WINNT < 0x0600)
#define CBES_EX_TEXTENDELLIPSIS      0x00000020
#endif
            DEF_STYLE(CBES_EX_TEXTENDELLIPSIS)
        };

        // ListBox
        const stStyleInfo g_ListBoxStylesData[] =
        {
            DEF_STYLE(LBS_STANDARD)

            DEF_STYLE(LBS_NOTIFY)
            DEF_STYLE(LBS_SORT)
            DEF_STYLE(LBS_NOREDRAW)
            DEF_STYLE(LBS_MULTIPLESEL)
            DEF_STYLE(LBS_OWNERDRAWFIXED)
            DEF_STYLE(LBS_OWNERDRAWVARIABLE)
            DEF_STYLE(LBS_HASSTRINGS)
            DEF_STYLE(LBS_USETABSTOPS)
            DEF_STYLE(LBS_NOINTEGRALHEIGHT)
            DEF_STYLE(LBS_MULTICOLUMN)
            DEF_STYLE(LBS_WANTKEYBOARDINPUT)
            DEF_STYLE(LBS_EXTENDEDSEL)
            DEF_STYLE(LBS_DISABLENOSCROLL)
            DEF_STYLE(LBS_NODATA)

            DEF_STYLE(LBS_NOSEL)

            DEF_STYLE(LBS_COMBOBOX)
        };

        // Static
        const stStyleInfo g_StaticStylesData[] =
        {
            DEF_STYLE(SS_LEFT)
            DEF_STYLE(SS_CENTER)
            DEF_STYLE(SS_RIGHT)
            DEF_STYLE(SS_ICON)
            DEF_STYLE(SS_BLACKRECT)
            DEF_STYLE(SS_GRAYRECT)
            DEF_STYLE(SS_WHITERECT)
            DEF_STYLE(SS_BLACKFRAME)
            DEF_STYLE(SS_GRAYFRAME)
            DEF_STYLE(SS_WHITEFRAME)
            DEF_STYLE(SS_USERITEM)
            DEF_STYLE(SS_SIMPLE)
            DEF_STYLE(SS_LEFTNOWORDWRAP)

            DEF_STYLE(SS_OWNERDRAW)
            DEF_STYLE(SS_BITMAP)
            DEF_STYLE(SS_ENHMETAFILE)
            DEF_STYLE(SS_ETCHEDHORZ)
            DEF_STYLE(SS_ETCHEDVERT)
            DEF_STYLE(SS_ETCHEDFRAME)
            DEF_STYLE(SS_TYPEMASK)

#if(WINVER < 0x0501)
#define SS_REALSIZECONTROL  0x00000040L
#endif /* WINVER < 0x0501 */
            DEF_STYLE(SS_REALSIZECONTROL)

            DEF_STYLE(SS_NOPREFIX)

            DEF_STYLE(SS_NOTIFY)
            DEF_STYLE(SS_CENTERIMAGE)
            DEF_STYLE(SS_RIGHTJUST)
            DEF_STYLE(SS_REALSIZEIMAGE)
            DEF_STYLE(SS_SUNKEN)
            DEF_STYLE(SS_EDITCONTROL)
            DEF_STYLE(SS_ENDELLIPSIS)
            DEF_STYLE(SS_PATHELLIPSIS)
            DEF_STYLE(SS_WORDELLIPSIS)
            DEF_STYLE(SS_ELLIPSISMASK)
        };

        // ScrollBar
        const stStyleInfo g_ScrollBarStylesData[] =
        {
            DEF_STYLE(SBS_HORZ)
            DEF_STYLE(SBS_VERT)
            DEF_STYLE(SBS_TOPALIGN)
            DEF_STYLE(SBS_LEFTALIGN)
            DEF_STYLE(SBS_BOTTOMALIGN)
            DEF_STYLE(SBS_RIGHTALIGN)
            DEF_STYLE(SBS_SIZEBOXTOPLEFTALIGN)
            DEF_STYLE(SBS_SIZEBOXBOTTOMRIGHTALIGN)
            DEF_STYLE(SBS_SIZEBOX)

            DEF_STYLE(SBS_SIZEGRIP)
        };

        // Slider
        const stStyleInfo g_SliderStylesData[] =
        {
            DEF_STYLE(TBS_AUTOTICKS)
            DEF_STYLE(TBS_VERT)
            DEF_STYLE(TBS_HORZ)
            DEF_STYLE(TBS_TOP)
            DEF_STYLE(TBS_BOTTOM)
            DEF_STYLE(TBS_LEFT)
            DEF_STYLE(TBS_RIGHT)
            DEF_STYLE(TBS_BOTH)
            DEF_STYLE(TBS_NOTICKS)
            DEF_STYLE(TBS_ENABLESELRANGE)
            DEF_STYLE(TBS_FIXEDLENGTH)
            DEF_STYLE(TBS_NOTHUMB)

            DEF_STYLE(TBS_TOOLTIPS)

            DEF_STYLE(TBS_REVERSED)

            DEF_STYLE(TBS_DOWNISLEFT)

#if (_WIN32_IE < 0x0600)
#define TBS_NOTIFYBEFOREMOVE    0x0800  // Trackbar should notify parent before repositioning the slider due to user action (enables snapping)
#endif
            DEF_STYLE(TBS_NOTIFYBEFOREMOVE)

#if (NTDDI_VERSION < NTDDI_LONGHORN)
#define TBS_TRANSPARENTBKGND    0x1000  // Background is painted by the parent via WM_PRINTCLIENT
#endif
            DEF_STYLE(TBS_TRANSPARENTBKGND)
        };

        // Spin
        const stStyleInfo g_SpinStylesData[] =
        {
            DEF_STYLE(UDS_WRAP)
            DEF_STYLE(UDS_SETBUDDYINT)
            DEF_STYLE(UDS_ALIGNRIGHT)
            DEF_STYLE(UDS_ALIGNLEFT)
            DEF_STYLE(UDS_AUTOBUDDY)
            DEF_STYLE(UDS_ARROWKEYS)
            DEF_STYLE(UDS_HORZ)
            DEF_STYLE(UDS_NOTHOUSANDS)

            DEF_STYLE(UDS_HOTTRACK)
        };

        // Progress
        const stStyleInfo g_ProgressStylesData[] =
        {
            DEF_STYLE(PBS_MARQUEE)
            DEF_STYLE(PBS_SMOOTH)

#if _WIN32_WINNT < 0x0600
#define PBS_SMOOTHREVERSE       0x10
#endif       // _WIN32_WINNT < 0x0600
            DEF_STYLE(PBS_SMOOTHREVERSE)
            DEF_STYLE(PBS_VERTICAL)
        };

        // HotKey
        // const stStyleInfo g_HotKeyStylesData[] = 
        // {
        // };

        // ListCtrl
        const stStyleInfo g_ListCtrlStylesData[] =
        {
            DEF_STYLE(LVS_ICON)
            DEF_STYLE(LVS_REPORT)
            DEF_STYLE(LVS_SMALLICON)
            DEF_STYLE(LVS_LIST)
            DEF_STYLE(LVS_TYPEMASK)
            DEF_STYLE(LVS_SINGLESEL)
            DEF_STYLE(LVS_SHOWSELALWAYS)
            DEF_STYLE(LVS_SORTASCENDING)
            DEF_STYLE(LVS_SORTDESCENDING)
            DEF_STYLE(LVS_SHAREIMAGELISTS)
            DEF_STYLE(LVS_NOLABELWRAP)
            DEF_STYLE(LVS_AUTOARRANGE)
            DEF_STYLE(LVS_EDITLABELS)

            DEF_STYLE(LVS_OWNERDATA)

            DEF_STYLE(LVS_NOSCROLL)

            DEF_STYLE(LVS_TYPESTYLEMASK)

            DEF_STYLE(LVS_ALIGNTOP)
            DEF_STYLE(LVS_ALIGNLEFT)
            DEF_STYLE(LVS_ALIGNMASK)

            DEF_STYLE(LVS_OWNERDRAWFIXED)
            DEF_STYLE(LVS_NOCOLUMNHEADER)
            DEF_STYLE(LVS_NOSORTHEADER)
        };

        // ListCtrl Extended
        const stStyleInfo g_ListCtrlExtendedStylesData[] =
        {
#if _WIN32_WINNT < 0x0600
#define LVS_EX_JUSTIFYCOLUMNS   0x00200000  // Icons are lined up in columns that use up the whole view area.
#define LVS_EX_TRANSPARENTBKGND 0x00400000  // Background is painted by the parent via WM_PRINTCLIENT
#define LVS_EX_TRANSPARENTSHADOWTEXT 0x00800000  // Enable shadow text on transparent backgrounds only (useful with bitmaps)
#define LVS_EX_AUTOAUTOARRANGE  0x01000000  // Icons automatically arrange if no icon positions have been set
#define LVS_EX_HEADERINALLVIEWS 0x02000000  // Display column header in all view modes
#define LVS_EX_AUTOCHECKSELECT  0x08000000
#define LVS_EX_AUTOSIZECOLUMNS  0x10000000
#define LVS_EX_COLUMNSNAPPOINTS 0x40000000
#define LVS_EX_COLUMNOVERFLOW   0x80000000
#endif
            DEF_STYLE(LVS_EX_AUTOAUTOARRANGE)
            DEF_STYLE(LVS_EX_AUTOCHECKSELECT)
            DEF_STYLE(LVS_EX_AUTOSIZECOLUMNS)
            DEF_STYLE(LVS_EX_BORDERSELECT)
            DEF_STYLE(LVS_EX_CHECKBOXES)
            DEF_STYLE(LVS_EX_COLUMNOVERFLOW)
            DEF_STYLE(LVS_EX_COLUMNSNAPPOINTS)
            DEF_STYLE(LVS_EX_DOUBLEBUFFER)
            DEF_STYLE(LVS_EX_FLATSB)
            DEF_STYLE(LVS_EX_FULLROWSELECT)
            DEF_STYLE(LVS_EX_GRIDLINES)
            DEF_STYLE(LVS_EX_HEADERDRAGDROP)
            DEF_STYLE(LVS_EX_HEADERINALLVIEWS)
            DEF_STYLE(LVS_EX_HIDELABELS)
            DEF_STYLE(LVS_EX_INFOTIP)
            DEF_STYLE(LVS_EX_JUSTIFYCOLUMNS)
            DEF_STYLE(LVS_EX_LABELTIP)
            DEF_STYLE(LVS_EX_MULTIWORKAREAS)
            DEF_STYLE(LVS_EX_ONECLICKACTIVATE)
            DEF_STYLE(LVS_EX_REGIONAL)
            DEF_STYLE(LVS_EX_SIMPLESELECT)
            DEF_STYLE(LVS_EX_SINGLEROW)
            DEF_STYLE(LVS_EX_SNAPTOGRID)
            DEF_STYLE(LVS_EX_SUBITEMIMAGES)
            DEF_STYLE(LVS_EX_TRACKSELECT)
            DEF_STYLE(LVS_EX_TRANSPARENTBKGND)
            DEF_STYLE(LVS_EX_TRANSPARENTSHADOWTEXT)
            DEF_STYLE(LVS_EX_TWOCLICKACTIVATE)
            DEF_STYLE(LVS_EX_UNDERLINECOLD)
            DEF_STYLE(LVS_EX_UNDERLINEHOT)
        };

        // TreeCtrl
        const stStyleInfo g_TreeCtrlStylesData[] =
        {
            DEF_STYLE(TVS_HASBUTTONS)
            DEF_STYLE(TVS_HASLINES)
            DEF_STYLE(TVS_LINESATROOT)
            DEF_STYLE(TVS_EDITLABELS)
            DEF_STYLE(TVS_DISABLEDRAGDROP)
            DEF_STYLE(TVS_SHOWSELALWAYS)

            DEF_STYLE(TVS_RTLREADING)

            DEF_STYLE(TVS_NOTOOLTIPS)
            DEF_STYLE(TVS_CHECKBOXES)
            DEF_STYLE(TVS_TRACKSELECT)

            DEF_STYLE(TVS_SINGLEEXPAND)
            DEF_STYLE(TVS_INFOTIP)
            DEF_STYLE(TVS_FULLROWSELECT)
            DEF_STYLE(TVS_NOSCROLL)
            DEF_STYLE(TVS_NONEVENHEIGHT)

            DEF_STYLE(TVS_NOHSCROLL)
        };

        // TreeCtrl Extended
        const stStyleInfo g_TreeCtrlExtendedStylesData[] =
        {
#if (_WIN32_WINNT < 0x0600)
#define TVS_EX_MULTISELECT          0x0002
#define TVS_EX_DOUBLEBUFFER         0x0004
#define TVS_EX_NOINDENTSTATE        0x0008
#define TVS_EX_RICHTOOLTIP          0x0010
#define TVS_EX_AUTOHSCROLL          0x0020
#define TVS_EX_FADEINOUTEXPANDOS    0x0040
#define TVS_EX_PARTIALCHECKBOXES    0x0080
#define TVS_EX_EXCLUSIONCHECKBOXES  0x0100
#define TVS_EX_DIMMEDCHECKBOXES     0x0200
#define TVS_EX_DRAWIMAGEASYNC       0x0400
#endif
            DEF_STYLE(TVS_EX_AUTOHSCROLL)
            DEF_STYLE(TVS_EX_DIMMEDCHECKBOXES)
            DEF_STYLE(TVS_EX_DOUBLEBUFFER)
            DEF_STYLE(TVS_EX_DRAWIMAGEASYNC)
            DEF_STYLE(TVS_EX_EXCLUSIONCHECKBOXES)
            DEF_STYLE(TVS_EX_FADEINOUTEXPANDOS)
            DEF_STYLE(TVS_EX_MULTISELECT)
            DEF_STYLE(TVS_EX_NOINDENTSTATE)
            DEF_STYLE(TVS_EX_PARTIALCHECKBOXES)
            DEF_STYLE(TVS_EX_RICHTOOLTIP)
        };

        // Tab
        const stStyleInfo g_TabStylesData[] =
        {
            DEF_STYLE(TCS_SCROLLOPPOSITE)
            DEF_STYLE(TCS_BOTTOM)
            DEF_STYLE(TCS_RIGHT)
            DEF_STYLE(TCS_MULTISELECT)

            DEF_STYLE(TCS_FLATBUTTONS)

            DEF_STYLE(TCS_FORCEICONLEFT)
            DEF_STYLE(TCS_FORCELABELLEFT)

            DEF_STYLE(TCS_HOTTRACK)
            DEF_STYLE(TCS_VERTICAL)

            DEF_STYLE(TCS_TABS)
            DEF_STYLE(TCS_BUTTONS)
            DEF_STYLE(TCS_SINGLELINE)
            DEF_STYLE(TCS_MULTILINE)
            DEF_STYLE(TCS_RIGHTJUSTIFY)
            DEF_STYLE(TCS_FIXEDWIDTH)
            DEF_STYLE(TCS_RAGGEDRIGHT)
            DEF_STYLE(TCS_FOCUSONBUTTONDOWN)
            DEF_STYLE(TCS_OWNERDRAWFIXED)
            DEF_STYLE(TCS_TOOLTIPS)
            DEF_STYLE(TCS_FOCUSNEVER)
        };

        // Animation
        const stStyleInfo g_AnimationStylesData[] =
        {
            DEF_STYLE(ACS_AUTOPLAY)
            DEF_STYLE(ACS_CENTER)
            DEF_STYLE(ACS_TIMER)
            DEF_STYLE(ACS_TRANSPARENT)
        };

        // DateTime
        const stStyleInfo g_DateTimeStylesData[] =
        {
            DEF_STYLE(DTS_APPCANPARSE)
            DEF_STYLE(DTS_LONGDATEFORMAT)
            DEF_STYLE(DTS_RIGHTALIGN)
            DEF_STYLE(DTS_SHOWNONE)
            DEF_STYLE(DTS_SHORTDATEFORMAT)
            DEF_STYLE(DTS_SHORTDATECENTURYFORMAT)
            DEF_STYLE(DTS_TIMEFORMAT)
            DEF_STYLE(DTS_UPDOWN)
        };

        // Calendar
        const stStyleInfo g_CalendarStylesData[] =
        {
            DEF_STYLE(MCS_DAYSTATE)
            DEF_STYLE(MCS_MULTISELECT)
            DEF_STYLE(MCS_WEEKNUMBERS)
            DEF_STYLE(MCS_NOTODAYCIRCLE)
            DEF_STYLE(MCS_NOTODAY)

#if (NTDDI_VERSION < NTDDI_LONGHORN)
#define MCS_NOTRAILINGDATES  0x0040
#define MCS_SHORTDAYSOFWEEK  0x0080
#define MCS_NOSELCHANGEONNAV 0x0100
#endif
            DEF_STYLE(MCS_NOTRAILINGDATES)
            DEF_STYLE(MCS_SHORTDAYSOFWEEK)
            DEF_STYLE(MCS_NOSELCHANGEONNAV)
        };

        // IPAddress
        // const stStyleInfo g_IPAddressStylesData[] =
        // {
        // };

        // SysLink
        const stStyleInfo g_SysLinkStylesData[] =
        {
            DEF_STYLE(LWS_TRANSPARENT)
            DEF_STYLE(LWS_IGNORERETURN)

#if _WIN32_WINNT < 0x0600
#define LWS_NOPREFIX        0x0004
#define LWS_USEVISUALSTYLE  0x0008
#define LWS_USECUSTOMTEXT   0x0010
#define LWS_RIGHT           0x0020
#endif // _WIN32_WINNT < 0x600
            DEF_STYLE(LWS_NOPREFIX)
            DEF_STYLE(LWS_USEVISUALSTYLE)
            DEF_STYLE(LWS_USECUSTOMTEXT)
            DEF_STYLE(LWS_RIGHT)
        };

        // SplitButton
        // const stStyleInfo g_SplitButtonStylesData[] =
        // {
        // };

        // NetworkAddress

        // CommandButton

        // Rebar
        const stStyleInfo g_RebarStylesData[] =
        {
            DEF_STYLE(RBS_AUTOSIZE)
            DEF_STYLE(RBS_BANDBORDERS)
            DEF_STYLE(RBS_DBLCLKTOGGLE)
            DEF_STYLE(RBS_FIXEDORDER)
            DEF_STYLE(RBS_REGISTERDROP)
            DEF_STYLE(RBS_TOOLTIPS)
            DEF_STYLE(RBS_VERTICALGRIPPER)
            DEF_STYLE(RBS_VARHEIGHT)
        };

        // Header
        const stStyleInfo g_HeaderStylesData[] =
        {
            DEF_STYLE(HDS_BUTTONS)
            DEF_STYLE(HDS_DRAGDROP)
            DEF_STYLE(HDS_FILTERBAR)
            DEF_STYLE(HDS_FLAT)
            DEF_STYLE(HDS_FULLDRAG)
            DEF_STYLE(HDS_HIDDEN)
            DEF_STYLE(HDS_HORZ)
            DEF_STYLE(HDS_HOTTRACK)

#if _WIN32_WINNT < 0x0600
#define HDS_CHECKBOXES          0x0400
#define HDS_NOSIZING            0x0800
#define HDS_OVERFLOW            0x1000
#endif
            DEF_STYLE(HDS_CHECKBOXES)
            DEF_STYLE(HDS_NOSIZING)
            DEF_STYLE(HDS_OVERFLOW)
        };

        // Pager
        const stStyleInfo g_PagerStylesData[] =
        {
            DEF_STYLE(PGS_AUTOSCROLL)
            DEF_STYLE(PGS_DRAGNDROP)
            DEF_STYLE(PGS_HORZ)
            DEF_STYLE(PGS_VERT)
        };

        // StatusBar
        const stStyleInfo g_StatusBarStylesData[] =
        {
            DEF_STYLE(SBARS_SIZEGRIP)
            DEF_STYLE(SBT_TOOLTIPS)
            DEF_STYLE(SBARS_TOOLTIPS)
        };

        // Toolbar
        const stStyleInfo g_ToolbarStylesData[] =
        {
            DEF_STYLE(BTNS_AUTOSIZE)
            DEF_STYLE(BTNS_BUTTON)
            DEF_STYLE(BTNS_CHECK)
            DEF_STYLE(BTNS_CHECKGROUP)
            DEF_STYLE(BTNS_DROPDOWN)
            DEF_STYLE(BTNS_GROUP)
            DEF_STYLE(BTNS_NOPREFIX)
            DEF_STYLE(BTNS_SEP)
            DEF_STYLE(BTNS_SHOWTEXT)
            DEF_STYLE(BTNS_WHOLEDROPDOWN)
        };

        // Toolbar Extended
        const stStyleInfo g_ToolbarExtendedStylesData[] =
        {
            DEF_STYLE(TBSTYLE_EX_DRAWDDARROWS)
            DEF_STYLE(TBSTYLE_EX_HIDECLIPPEDBUTTONS)
            DEF_STYLE(TBSTYLE_EX_DOUBLEBUFFER)
            DEF_STYLE(TBSTYLE_EX_MIXEDBUTTONS)
        };

        // Tooltip
        const stStyleInfo g_TooltipStylesData[] =
        {
            DEF_STYLE(TTS_ALWAYSTIP)
            DEF_STYLE(TTS_BALLOON)
            DEF_STYLE(TTS_CLOSE)
            DEF_STYLE(TTS_NOANIMATE)
            DEF_STYLE(TTS_NOFADE)
            DEF_STYLE(TTS_NOPREFIX)
#if _WIN32_WINNT < 0x0600
#define TTS_USEVISUALSTYLE      0x100  // Use themed hyperlinks
#endif
            DEF_STYLE(TTS_USEVISUALSTYLE)
        };

        // Class Style
        const stStyleInfo g_WindowClassStylesData[] =
        {
            DEF_STYLE(CS_VREDRAW)
            DEF_STYLE(CS_HREDRAW)
            DEF_STYLE(CS_DBLCLKS)
            DEF_STYLE(CS_OWNDC)
            DEF_STYLE(CS_CLASSDC)
            DEF_STYLE(CS_PARENTDC)
            DEF_STYLE(CS_NOCLOSE)
            DEF_STYLE(CS_SAVEBITS)
            DEF_STYLE(CS_BYTEALIGNCLIENT)
            DEF_STYLE(CS_BYTEALIGNWINDOW)
            DEF_STYLE(CS_GLOBALCLASS)

            DEF_STYLE(CS_IME)
            DEF_STYLE(CS_DROPSHADOW)
        };


        void GetTitleImpl(DWORD& dwStyles, const stStyleInfo styleInfo[], int nInfoCount, StringArray& arrTitles)
        {
            for(int i=0; i<nInfoCount; ++ i)
            {
                const stStyleInfo& style = styleInfo[i];
                if((style.dwStyle & dwStyles) == style.dwStyle)
                {
                    arrTitles.Add(style.szName);
                    dwStyles = (dwStyles & (~style.dwStyle));
                }
            }
        }
    }

    BOOL GetStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles)
    {
        GetTitleImpl(dwStyles, g_WindowStylesData, _countof(g_WindowStylesData), arrTitles);

        TCHAR szClassName[1024];
        if(::GetClassName(hWnd, szClassName, 1024) == 0)
        {
            if(dwStyles != 0)
            {
                CString strTemp;
                strTemp.Format(_T("0x%08x"), dwStyles);
                arrTitles.Add(strTemp);
            }
            return FALSE;
        }

        struct
        {
            LPCTSTR szClassName;
            const stStyleInfo* pStyle;
            int nStyleCount;
        } styleDatas[] =
        {
            {WC_BUTTON,                 g_ButtonStylesData,        _countof(g_ButtonStylesData)},
            {_T("#32770"),              g_DialogStylesData,        _countof(g_DialogStylesData)},
            {WC_EDIT,                   g_EditStylesData,          _countof(g_EditStylesData)},
            {WC_COMBOBOX,               g_ComboBoxStylesData,      _countof(g_ComboBoxStylesData)},
            {WC_COMBOBOXEX,             g_ComboBoxStylesData,      _countof(g_ComboBoxStylesData)},
            {WC_LISTBOX,                g_ListBoxStylesData,       _countof(g_ListBoxStylesData)},
            {WC_STATIC,                 g_StaticStylesData,        _countof(g_StaticStylesData)},
            {WC_SCROLLBAR,              g_ScrollBarStylesData,     _countof(g_ScrollBarStylesData)},
            {UPDOWN_CLASS,              g_SliderStylesData,        _countof(g_SliderStylesData)},
            {TRACKBAR_CLASS,            g_SpinStylesData,          _countof(g_SpinStylesData)},
            {PROGRESS_CLASS,            g_ProgressStylesData,      _countof(g_ProgressStylesData)},
            {WC_LISTVIEW,               g_ListCtrlStylesData,      _countof(g_ListCtrlStylesData)},
            {WC_TREEVIEW,               g_TreeCtrlStylesData,      _countof(g_TreeCtrlStylesData)},
            {WC_TABCONTROL,             g_TabStylesData,           _countof(g_TabStylesData)},
            {ANIMATE_CLASS,             g_AnimationStylesData,     _countof(g_AnimationStylesData)},
            {DATETIMEPICK_CLASS,        g_DateTimeStylesData,      _countof(g_DateTimeStylesData)},
            {MONTHCAL_CLASS,            g_CalendarStylesData,      _countof(g_CalendarStylesData)},
            {WC_LINK,                   g_SysLinkStylesData,       _countof(g_SysLinkStylesData)},
            {REBARCLASSNAME,            g_RebarStylesData,         _countof(g_RebarStylesData)},
            {WC_HEADER,                 g_HeaderStylesData,        _countof(g_HeaderStylesData)},
            {WC_PAGESCROLLER,           g_PagerStylesData,         _countof(g_PagerStylesData)},
            {STATUSCLASSNAME,           g_StatusBarStylesData,     _countof(g_StatusBarStylesData)},
            {TOOLBARCLASSNAME,          g_ToolbarStylesData,       _countof(g_ToolbarStylesData)},
            {TOOLTIPS_CLASS,            g_TooltipStylesData,       _countof(g_TooltipStylesData)},
        };

        // 
        for(int i=0; i<_countof(styleDatas); ++ i)
        {
            if(_tcsicmp(styleDatas[i].szClassName, szClassName) == 0)
            {
                GetTitleImpl(dwStyles, styleDatas[i].pStyle, styleDatas[i].nStyleCount, arrTitles);
                break;
            }
        }

        if(dwStyles != 0)
        {
            CString strTemp;
            strTemp.Format(_T("0x%08x"), dwStyles);
            arrTitles.Add(strTemp);
        }
        return TRUE;
    }

    BOOL GetExtendedStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles)
    {
        GetTitleImpl(dwStyles, g_WindowExtendedStylesData, _countof(g_WindowExtendedStylesData), arrTitles);

        TCHAR szClassName[1024];
        if(::GetClassName(hWnd, szClassName, 1024) == 0)
        {
            if(dwStyles != 0)
            {
                CString strTemp;
                strTemp.Format(_T("0x%08x"), dwStyles);
                arrTitles.Add(strTemp);
            }
            return FALSE;
        }

        struct
        {
            LPCTSTR szClassName;
            const stStyleInfo* pStyle;
            int nStyleCount;
        } styleDatas[] =
        {
            {WC_COMBOBOXEX,                 g_ComboBoxExtendedStylesData,      _countof(g_ComboBoxExtendedStylesData)},
            {WC_LISTVIEW,                   g_ListCtrlExtendedStylesData,      _countof(g_ListCtrlExtendedStylesData)},
            {WC_TREEVIEW,                   g_TreeCtrlExtendedStylesData,      _countof(g_TreeCtrlExtendedStylesData)},
            {TOOLBARCLASSNAME,              g_ToolbarExtendedStylesData,       _countof(g_ToolbarExtendedStylesData)},
        };

        // 
        for(int i=0; i<_countof(styleDatas); ++ i)
        {
            if(_tcsicmp(styleDatas[i].szClassName, szClassName) == 0)
            {
                GetTitleImpl(dwStyles, styleDatas[i].pStyle, styleDatas[i].nStyleCount, arrTitles);
                break;
            }
        }

        if(dwStyles != 0)
        {
            CString strTemp;
            strTemp.Format(_T("0x%08x"), dwStyles);
            arrTitles.Add(strTemp);
        }

        return TRUE;
    }


    BOOL GetClassStylesTitle(DWORD dwStyles, StringArray& arrTitles)
    {
        GetTitleImpl(dwStyles, g_WindowClassStylesData, _countof(g_WindowClassStylesData), arrTitles);

        if(dwStyles != 0)
        {
            CString strTemp;
            strTemp.Format(_T("0x%08x"), dwStyles);
            arrTitles.Add(strTemp);
        }

        return TRUE;
    }
};
