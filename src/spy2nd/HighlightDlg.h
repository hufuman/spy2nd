#pragma once





class CHighlightDlg : public CDialogImpl<CHighlightDlg>
{
public:
	enum { IDD = IDD_HIGHLIGHT };

	BEGIN_MSG_MAP(CHighlightDlg)

		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)

        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    CHighlightDlg(HWND hWndHighlight)
    {
        m_uTimer = 0;
        m_nCount = 0;
        m_bHighlight = true;
        m_hWndHighlight = hWndHighlight;
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        if(m_hWndHighlight == NULL || !::IsWindow(m_hWndHighlight))
        {
            DestroyWindow();
            delete this;
            return TRUE;
        }

        m_uTimer = SetTimer(1234, 200, NULL);

        Prepare();
		return TRUE;
	}

    void Prepare()
    {
        CRect rcWnd;
        ::GetWindowRect(m_hWndHighlight, &rcWnd);

        SetWindowPos(HWND_TOPMOST, rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), SWP_NOACTIVATE);

        const int offset = 4;
        HRGN hRgn = ::CreateRectRgn(0, 0, rcWnd.Width(), rcWnd.Height());
        HRGN hInnerRgn = ::CreateRectRgn(offset, offset, rcWnd.Width() - offset, rcWnd.Height() - offset);
        ::CombineRgn(hRgn, hRgn, hInnerRgn, RGN_DIFF);
        SetWindowRgn(hRgn);
        ::DeleteObject(hInnerRgn);
    }

    LRESULT OnErasebkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        CRect rcWnd;
        GetClientRect(&rcWnd);

        if(m_bHighlight)
            ::FillRect(reinterpret_cast<HDC>(wParam), &rcWnd, reinterpret_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH)));
        else
            ::FillRect(reinterpret_cast<HDC>(wParam), &rcWnd, reinterpret_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH)));

        m_bHighlight = !m_bHighlight;
        return 1;
    }

    LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(m_uTimer != wParam)
        {
            bHandled = FALSE;
            return 0;
        }

        Invalidate();
        UpdateWindow();

        if((++ m_nCount) > 8)
        {
            DestroyWindow();
        }

        return 0;
    }

    virtual void OnFinalMessage(HWND /*hWnd*/)
    {
        delete this;
    }

private:
    HWND        m_hWndHighlight;
    UINT_PTR    m_uTimer;
    bool        m_bHighlight;
    UINT        m_nCount;
};

