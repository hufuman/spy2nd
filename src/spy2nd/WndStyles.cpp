#include "StdAfx.h"
#include "WndStyles.h"


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


        BOOL GetTitleImpl(DWORD dwStyles, const stStyleInfo styleInfo[], int nInfoCount, StringArray& arrTitles)
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
            if(dwStyles != 0)
            {
                CString strTemp;
                strTemp.Format(_T("0x%08x"), dwStyles);
                arrTitles.Add(strTemp);
            }
            return TRUE;
        }
    }

    BOOL GetStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles)
    {
        return GetTitleImpl(dwStyles, g_WindowStylesData, _countof(g_WindowStylesData), arrTitles);
    }

    BOOL GetExtendedStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles)
    {
        return GetTitleImpl(dwStyles, g_WindowExtendedStylesData, _countof(g_WindowExtendedStylesData), arrTitles);
    }


    BOOL GetClassStylesTitle(DWORD dwStyles, StringArray& arrTitles)
    {
        return GetTitleImpl(dwStyles, g_WindowClassStylesData, _countof(g_WindowClassStylesData), arrTitles);
    }
};
