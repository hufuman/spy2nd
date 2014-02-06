#pragma once





class CWndPropertyMiscDlg : public CDialogImpl<CWndPropertyMiscDlg>, public IWndPropertyViewImpl<CWndPropertyMiscDlg>
{
public:
    enum { IDD = IDD_WNDPROPERTY_MISC };

    BEGIN_MSG_MAP(CWndPropertyMiscDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)

        COMMAND_ID_HANDLER(IDC_LINK_PROCID, OnProcIdClicked)
        COMMAND_ID_HANDLER(IDC_LINK_THREADID, OnThreadIdClicked)
    END_MSG_MAP()

    CWndPropertyMiscDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_LinkProcId.m_tip.m_hWnd = NULL;
        m_LinkThreadId.m_tip.m_hWnd = NULL;

        m_LinkProcId.SubclassWindow(GetDlgItem(IDC_LINK_PROCID));
        m_LinkThreadId.SubclassWindow(GetDlgItem(IDC_LINK_THREADID));
        return TRUE;
    }

    LRESULT OnProcIdClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // not impl
        return 0;
    }

    LRESULT OnThreadIdClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        // not impl
        return 0;
    }

    void RefreshPropertyImpl()
    {
        DWORD dwProcId = 0;
        DWORD dwThreadId = ::GetWindowThreadProcessId(m_hTargetWnd, &dwProcId);

        CString strTemp;

        strTemp.Format(_T("%08u"), dwProcId);
        m_LinkProcId.SetLabel(strTemp);
        m_LinkProcId.Invalidate();

        strTemp.Format(_T("%08u"), dwThreadId);
        m_LinkThreadId.SetLabel(strTemp);
        m_LinkThreadId.Invalidate();
    }

private:
    HBRUSH  m_hBrush;

    CHyperLink  m_LinkProcId;
    CHyperLink  m_LinkThreadId;
};

