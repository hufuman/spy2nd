#pragma once





class CHighlightDlg : public CDialogImpl<CHighlightDlg>
{
public:
	enum { IDD = IDD_HIGHLIGHT };

	BEGIN_MSG_MAP(CHighlightDlg)

		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnErasebkgnd)

        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    CHighlightDlg()
    {
        m_hBkgBrush = reinterpret_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH));
        m_hWndHighlight = NULL;
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return TRUE;
	}

    void SetBrush(HBRUSH hBrush)
    {
        m_hBkgBrush = hBrush;
    }

    void SetHwnd(HWND hWnd)
    {
        m_hWndHighlight = hWnd;
        if(m_hWnd)
        {
            Prepare();
            Invalidate();
            UpdateWindow();
        }
    }

private:
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

        ::FillRect(reinterpret_cast<HDC>(wParam), &rcWnd, m_hBkgBrush);

        return 1;
    }

private:
    HWND        m_hWndHighlight;
    HBRUSH      m_hBkgBrush;
};

