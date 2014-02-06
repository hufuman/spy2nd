#pragma once


#include "HighlightDlg.h"


class CHighlightFlasher
{
public:
    CHighlightFlasher(HWND hWndHighlight)
    {
        m_uTimer = 0;
        m_nCount = 0;
        m_bHighlight = true;
        s_Flasher = this;
        m_hWndHighlight = hWndHighlight;
    }

    ~CHighlightFlasher()
    {
        if(s_Flasher == this)
            s_Flasher = NULL;
    }

    void Flash()
    {
        m_HighlightDlg.Create(NULL, 0);
        m_HighlightDlg.SetHwnd(m_hWndHighlight);
        m_HighlightDlg.ShowWindow(SW_SHOWNOACTIVATE);
        m_HighlightDlg.UpdateWindow();

        m_uTimer = ::SetTimer(m_HighlightDlg, 1234, 200, FlashTimerProc);
    }

private:

    static void WINAPI FlashTimerProc(HWND, UINT, UINT_PTR, DWORD)
    {
        HBRUSH hBrush = s_Flasher->m_bHighlight ?
            reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH))
            : reinterpret_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH));
        s_Flasher->m_HighlightDlg.SetBrush(hBrush);
        s_Flasher->m_HighlightDlg.Invalidate();
        s_Flasher->m_HighlightDlg.UpdateWindow();
        s_Flasher->m_bHighlight = !s_Flasher->m_bHighlight;

        if((++ s_Flasher->m_nCount) > 8)
        {
            ::KillTimer(s_Flasher->m_HighlightDlg, s_Flasher->m_uTimer);
            s_Flasher->m_HighlightDlg.DestroyWindow();
            delete s_Flasher;
        }
    }

private:
    CHighlightDlg   m_HighlightDlg;

    UINT_PTR    m_uTimer;
    bool        m_bHighlight;
    UINT        m_nCount;
    HWND        m_hWndHighlight;

    static CHighlightFlasher* s_Flasher;
};

__declspec(selectany) CHighlightFlasher* CHighlightFlasher::s_Flasher = NULL;

