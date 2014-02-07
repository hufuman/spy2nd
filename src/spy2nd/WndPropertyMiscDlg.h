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

        m_LinkProcId.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkThreadId.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);

        m_LinkProcId.SubclassWindow(GetDlgItem(IDC_LINK_PROCID));
        m_LinkThreadId.SubclassWindow(GetDlgItem(IDC_LINK_THREADID));
        return TRUE;
    }

    LRESULT OnProcIdClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LINK_PROCID));
        DWORD dwProcId = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        if(!g_ProcViewGetter)
        {
            MessageBox(_T("Processes View hasn't be initialized"));
        }
        else
        {
            IProcessView* pProcView = g_ProcViewGetter();
            g_ViewHolderGetter()->ShowView(ViewProcesses);
            if(pProcView->SearchAndSelectProcItem(dwProcId) == NULL)
            {
                MessageBox(_T("No Item Found"));
            }
        }

        return 0;
    }

    LRESULT OnThreadIdClicked(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LINK_THREADID));
        DWORD dwThreadId = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        if(!g_ProcViewGetter)
        {
            MessageBox(_T("Processes View hasn't be initialized"));
        }
        else
        {
            IProcessView* pProcView = g_ProcViewGetter();
            g_ViewHolderGetter()->ShowView(ViewProcesses);
            if(pProcView->SearchAndSelectThreadItem(dwThreadId) == NULL)
            {
                MessageBox(_T("No Item Found"));
            }
        }

        return 0;
    }

    void RefreshPropertyImpl()
    {
        DWORD dwProcId = 0;
        DWORD dwThreadId = ::GetWindowThreadProcessId(m_hTargetWnd, &dwProcId);

        CString strTemp;

        strTemp.Format(_T("%08u"), dwProcId);
        m_LinkProcId.SetLabel(strTemp);
        m_LinkProcId.SetWindowLongPtr(GWLP_USERDATA, dwProcId);
        m_LinkProcId.Invalidate();

        strTemp.Format(_T("%08u"), dwThreadId);
        m_LinkThreadId.SetLabel(strTemp);
        m_LinkThreadId.SetWindowLongPtr(GWLP_USERDATA, dwThreadId);
        m_LinkThreadId.Invalidate();
    }

private:
    HBRUSH  m_hBrush;

    CHyperLink  m_LinkProcId;
    CHyperLink  m_LinkThreadId;
};

