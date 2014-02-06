#pragma once


enum FindWindowOption
{
    FindWindowByCapture,    // 
    FindWindowByMove,       // 
};

class CFindWindowDlg : public CDialogImpl<CFindWindowDlg>
{
public:
	enum { IDD = IDD_FIND_WINDOW };

	BEGIN_MSG_MAP(CFindWindowDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

        MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
        MESSAGE_HANDLER(WM_MOUSEMOVE,   OnMouseMove)
        MESSAGE_HANDLER(WM_LBUTTONUP,   OnLButtonUp)
        MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)

        COMMAND_ID_HANDLER(IDC_CHK_HIDE_SPY2ND, OnHideSpy2nd)

        COMMAND_ID_HANDLER(IDC_BTN_SEARCH,  OnBtnSearch)
		COMMAND_ID_HANDLER(IDOK,            OnBtnAction)
		COMMAND_ID_HANDLER(IDCANCEL,        OnCloseCmd)
    END_MSG_MAP()

    CFindWindowDlg(IView *pView)
    {
        m_pView = pView;
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_hOldCursor = NULL;
        m_hDragCursor = NULL;
        m_hLastWnd = NULL;
        m_bDownAtSearchIcon = FALSE;

        GetDlgItem(IDC_ICON_SEARCH).GetWindowRect(&m_rcSearchIcon);
        ScreenToClient(&m_rcSearchIcon);

        CheckDlgButton(IDC_RADIO_DOWN, BST_CHECKED);
        CheckDlgButton(IDC_RADIO_PROPERTY, BST_CHECKED);

		CenterWindow(GetParent());
		return TRUE;
    }

    void StartDrag()
    {
        if(m_hDragCursor == NULL)
            m_hDragCursor = LoadCursor(::GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR_SEARCH_WINDOW));
        m_hOldCursor = SetCursor(m_hDragCursor);
        if(m_HighlightDlg.m_hWnd == NULL)
        {
            m_HighlightDlg.Create(m_hWnd);
        }

        POINT Pt;
        ::GetCursorPos(&Pt);
        HWND hWnd = ::WindowFromPoint(Pt);

        m_HighlightDlg.SetHwnd(hWnd);
        m_HighlightDlg.ShowWindow(SW_SHOWNOACTIVATE);
    }

    void UpdateDrag()
    {
        POINT Pt;
        ::GetCursorPos(&Pt);
        HWND hWnd = ::WindowFromPoint(Pt);
        HWND hRealWnd = hWnd;
        POINT Ppt;
        do 
        {
            hWnd = hRealWnd;
            Ppt = Pt;
            ::ScreenToClient(hWnd, &Ppt);
            hRealWnd = ::RealChildWindowFromPoint(hWnd, Ppt);
        } while (hRealWnd != NULL && hRealWnd != hWnd);
        UpdateInfo(hWnd);
    }

    void CancelDrag()
    {
        if(!m_bDownAtSearchIcon)
            return;

        SetCursor(m_hOldCursor);
        m_bDownAtSearchIcon = FALSE;

        if(m_HighlightDlg.m_hWnd)
            m_HighlightDlg.ShowWindow(SW_HIDE);
    }

    void UpdateInfo(HWND hWnd)
    {
        if(m_hLastWnd == hWnd)
            return;

        m_hLastWnd = hWnd;

        CString strTemp;

        if(hWnd == NULL)
        {
            SetDlgItemText(IDC_EDIT_HANDLE, _T("0x00000000"));
            SetDlgItemText(IDC_EDIT_CAPTION, _T(""));
            SetDlgItemText(IDC_EDIT_CLASS, _T(""));
            SetDlgItemText(IDC_LABEL_RECT, _T(""));
        }
        else
        {
            CWindow wnd;
            wnd.Attach(hWnd);

            // Handle
            strTemp.Format(_T("0x%08x"), hWnd);
            SetDlgItemText(IDC_EDIT_HANDLE, strTemp);

            // Caption
            wnd.GetWindowText(strTemp);
            SetDlgItemText(IDC_EDIT_CAPTION, strTemp);

            // Class
            TCHAR szTemp[MAX_PATH];
            ::GetClassName(hWnd, szTemp, MAX_PATH);
            SetDlgItemText(IDC_EDIT_CLASS, szTemp);

            CRect rcWnd;
            wnd.GetWindowRect(&rcWnd);
            strTemp.Format(_T("(%d, %d) - (%d, %d) %d * %d"),
                rcWnd.left, rcWnd.top,
                rcWnd.right, rcWnd.bottom,
                rcWnd.Width(), rcWnd.Height());
            SetDlgItemText(IDC_LABEL_RECT, strTemp);

            m_HighlightDlg.SetHwnd(hWnd);
        }
    }

    HTREEITEM SearchAndSelectItem(HWND &hTargetWnd)
    {
        HTREEITEM hItem = NULL;

        CString strHandle, strCaption, strClass;
        GetDlgItemText(IDC_EDIT_HANDLE, strHandle);

        BOOL bDownSearch = IsDlgButtonChecked(IDC_RADIO_DOWN) == BST_CHECKED;

        // Only hWnd
        if(!strHandle.IsEmpty())
        {
            _sntscanf(strHandle, strHandle.GetLength(), _T("0x%08x"), &hTargetWnd);
            if(::IsWindow(hTargetWnd))
            {
                hItem = m_pView->SearchAndSelectItem(hTargetWnd, bDownSearch, strCaption, strClass);
                if(hItem != NULL)
                    return hItem;
            }
            else
            {
                MessageBox(_T("Found one valid hWnd, views need to be refresh to show this hWnd"));
                return NULL;
            }
        }

        // 
        GetDlgItemText(IDC_EDIT_CAPTION, strCaption);
        GetDlgItemText(IDC_EDIT_CLASS, strClass);

        hItem = m_pView->SearchAndSelectItem(hTargetWnd, bDownSearch, strCaption, strClass);
        if(hItem != NULL)
            return hItem;

        hTargetWnd = NULL;
        MessageBox(_T("Found one valid hWnd, views need to be refresh to show this hWnd"));
        return NULL;
    }

    LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        POINT Pt = {LOWORD(lParam), HIWORD(lParam)};
        m_bDownAtSearchIcon = (PtInRect(&m_rcSearchIcon, Pt));
        if(m_bDownAtSearchIcon)
        {
            StartDrag();
            SetCapture();
        }
        return 0;
    }

    LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        POINT Pt = {LOWORD(lParam), HIWORD(lParam)};
        if(m_bDownAtSearchIcon)
            UpdateDrag();
        return 0;
    }

    LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        POINT Pt = {LOWORD(lParam), HIWORD(lParam)};

        if(m_bDownAtSearchIcon)
        {
            ReleaseCapture();
            CancelDrag();
        }
        return 0;
    }

    LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        CancelDrag();
        return 0;
    }

    LRESULT OnHideSpy2nd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        BOOL bHide = IsDlgButtonChecked(IDC_CHK_HIDE_SPY2ND);
        ::ShowWindow(GetParent(), bHide ? SW_HIDE : SW_SHOW);
        return 0;
    }

    LRESULT OnBtnSearch(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        HWND hTargetWnd = NULL;
        HTREEITEM hTargetItem = SearchAndSelectItem(hTargetWnd);
        if(hTargetItem == NULL)
        {
            MessageBox(_T("Can't search window which matched all options"));
            return 0;
        }

        m_hLastWnd = HWND_TOPMOST;
        UpdateInfo(hTargetWnd);
        return 0;
    }

    LRESULT OnBtnAction(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        HWND hTargetWnd = NULL;
        HTREEITEM hTargetItem = SearchAndSelectItem(hTargetWnd);
        if(hTargetItem == NULL)
        {
            MessageBox(_T("Can't search window which matched all options"));
            return 0;
        }

        EndDialog(IDOK);
        if(BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_LOCATE))
        {
        }
        else if(BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_PROPERTY))
        {
            ::PostMessage(GetParent(), WM_COMMAND, MAKEWPARAM(ID_VIEW_PROPERTY, 0), 0);
        }
        else if(BST_CHECKED == IsDlgButtonChecked(IDC_RADIO_MESSAGE))
        {
            ::PostMessage(GetParent(), WM_COMMAND, MAKEWPARAM(ID_FILE_LOG_MSG, 0), 0);
        }
        return 0;
    }

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

private:
    CRect   m_rcSearchIcon;

    HCURSOR m_hDragCursor;
    HCURSOR m_hOldCursor;
    BOOL    m_bDownAtSearchIcon;

    HWND    m_hLastWnd;

    IView*  m_pView;
    CHighlightDlg   m_HighlightDlg;
};

