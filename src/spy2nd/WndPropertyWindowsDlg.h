#pragma once


#include "WndLayout.h"
#include "ProcUtil.h"

class CWndPropertyWindowsDlg : public CDialogImpl<CWndPropertyWindowsDlg>, public IWndPropertyViewImpl<CWndPropertyWindowsDlg>
{
public:
    enum { IDD = IDD_WNDPROPERTY_WINDOWS };

    BEGIN_MSG_MAP(CWndPropertyWindowsDlg)

        MESSAGE_HANDLER(WM_INITDIALOG,      OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORBTN,     OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)

        COMMAND_ID_HANDLER(IDC_LABEL_PARENT_HANDLE, OnParentHandle)
        COMMAND_ID_HANDLER(IDC_LABEL_PARENT_THREAD, OnParentThread)
        COMMAND_ID_HANDLER(IDC_LABEL_PARENT_PROCESS, OnParentProcess)

        COMMAND_ID_HANDLER(IDC_LABEL_OWNER_HANDLE, OnOwnerHandle)
        COMMAND_ID_HANDLER(IDC_LABEL_OWNER_THREAD, OnOwnerThread)
        COMMAND_ID_HANDLER(IDC_LABEL_OWNER_PROCESS, OnOwnerProcess)

    END_MSG_MAP()

    CWndPropertyWindowsDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }


    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_LinkParentHandle.m_tip.m_hWnd = NULL;
        m_LinkParentProcess.m_tip.m_hWnd = NULL;
        m_LinkParentThread.m_tip.m_hWnd = NULL;
        m_LinkOwnerHandle.m_tip.m_hWnd = NULL;
        m_LinkOwnerProcess.m_tip.m_hWnd = NULL;
        m_LinkOwnerThread.m_tip.m_hWnd = NULL;

        m_LinkParentHandle.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkParentProcess.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkParentThread.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkOwnerHandle.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkOwnerProcess.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);
        m_LinkOwnerThread.SetHyperLinkExtendedStyle(HLINK_COMMANDBUTTON | HLINK_UNDERLINEHOVER);

        m_LinkParentHandle.SubclassWindow(GetDlgItem(IDC_LABEL_PARENT_HANDLE));
        m_LinkParentThread.SubclassWindow(GetDlgItem(IDC_LABEL_PARENT_THREAD));
        m_LinkParentProcess.SubclassWindow(GetDlgItem(IDC_LABEL_PARENT_PROCESS));

        m_LinkOwnerHandle.SubclassWindow(GetDlgItem(IDC_LABEL_OWNER_HANDLE));
        m_LinkOwnerThread.SubclassWindow(GetDlgItem(IDC_LABEL_OWNER_THREAD));
        m_LinkOwnerProcess.SubclassWindow(GetDlgItem(IDC_LABEL_OWNER_PROCESS));

        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlById(IDC_LABEL_PARENT_CAPTION, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_PARENT_PROCESS, Layout_HFill);

        m_WndLayout.AddControlById(IDC_LABEL_OWNER_CAPTION, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_OWNER_PROCESS, Layout_HFill);

        m_WndLayout.AddControlById(IDC_GROUP_PARENT, Layout_HFill);
        m_WndLayout.AddControlById(IDC_GROUP_OWNER, Layout_HFill);

        return TRUE;
    }

    LRESULT OnParentHandle(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_PARENT_HANDLE));
        HWND hParentWnd = reinterpret_cast<HWND>(wnd.GetWindowLongPtr(GWLP_USERDATA));
        if(hParentWnd == NULL)
        {
            MessageBox(_T("No Parent Window"));
            return 0;
        }

        IBaseView* pView = g_CurrentViewGetter();
        SpyViewType viewType = pView->GetViewType();
        if(viewType != ViewProcesses && viewType != ViewWindows)
            pView = g_WndViewGetter();
        CString strStub;
        g_ViewHolderGetter()->ShowView(pView->GetViewType());
        if(pView->SearchAndSelectItem(hParentWnd, TRUE, strStub, strStub) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    LRESULT OnParentThread(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_PARENT_THREAD));
        DWORD dwThreadId = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        IProcessView* pProcView = g_ProcViewGetter();
        g_ViewHolderGetter()->ShowView(ViewProcesses);
        if(pProcView->SearchAndSelectThreadItem(dwThreadId) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    LRESULT OnParentProcess(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_PARENT_PROCESS));
        DWORD dwParentPid = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        IProcessView* pProcView = g_ProcViewGetter();
        g_ViewHolderGetter()->ShowView(ViewProcesses);
        if(pProcView->SearchAndSelectProcItem(dwParentPid) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    LRESULT OnOwnerHandle(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_OWNER_HANDLE));
        HWND hOwnerWnd = reinterpret_cast<HWND>(wnd.GetWindowLongPtr(GWLP_USERDATA));
        if(hOwnerWnd == NULL)
        {
            MessageBox(_T("No Owner Window"));
            return 0;
        }

        IBaseView* pView = g_CurrentViewGetter();
        SpyViewType viewType = pView->GetViewType();
        if(viewType != ViewProcesses && viewType != ViewWindows)
            pView = g_WndViewGetter();
        CString strStub;
        g_ViewHolderGetter()->ShowView(pView->GetViewType());
        if(pView->SearchAndSelectItem(hOwnerWnd, TRUE, strStub, strStub) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    LRESULT OnOwnerThread(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_OWNER_THREAD));
        DWORD dwThreadId = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        IProcessView* pProcView = g_ProcViewGetter();
        g_ViewHolderGetter()->ShowView(ViewProcesses);
        if(pProcView->SearchAndSelectThreadItem(dwThreadId) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    LRESULT OnOwnerProcess(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CWindow wnd(GetDlgItem(IDC_LABEL_OWNER_PROCESS));
        DWORD dwOwnerPid = (DWORD)wnd.GetWindowLongPtr(GWLP_USERDATA);

        IProcessView* pProcView = g_ProcViewGetter();
        g_ViewHolderGetter()->ShowView(ViewProcesses);
        if(pProcView->SearchAndSelectProcItem(dwOwnerPid) == NULL)
        {
            MessageBox(_T("No Item Found"));
        }

        return 0;
    }

    void RefreshPropertyImpl()
    {
        CString strTemp;
        HWND hWndParent = ::GetParent(m_hTargetWnd);
        HWND hWndOwner = ::GetWindow(m_hTargetWnd, GW_OWNER);

        DWORD dwParentPid = 0;
        DWORD dwOwnerPid = 0;
        DWORD dwParentThreadId = 0;
        DWORD dwOwnerThreadId = 0;

        if(hWndParent == NULL)
        {
            m_LinkParentHandle.SetLabel(_T("NULL"));
            m_LinkParentProcess.SetLabel(_T(""));
            m_LinkParentThread.SetLabel(_T(""));
            SetDlgItemText(IDC_LABEL_PARENT_CAPTION, _T(""));
        }
        else
        {
            CWindow wndParent;
            wndParent.Attach(hWndParent);

            strTemp.Format(_T("0x%08x"), hWndParent);
            m_LinkParentHandle.SetLabel(strTemp);

            dwParentThreadId = GetWindowThreadProcessId(hWndParent, &dwParentPid);
            strTemp.Format(_T("%s (%u)"), ProcUtil::GetProcName(dwParentPid), dwParentPid);
            m_LinkParentProcess.SetLabel(strTemp);

            strTemp.Format(_T("%u"), dwParentThreadId);
            m_LinkParentThread.SetLabel(strTemp);

            wndParent.GetWindowText(strTemp);
            SetDlgItemText(IDC_LABEL_PARENT_CAPTION, strTemp);
        }

        if(hWndOwner == NULL)
        {
            m_LinkOwnerHandle.SetLabel(_T("NULL"));
            m_LinkOwnerProcess.SetLabel(_T(""));
            m_LinkOwnerThread.SetLabel(_T(""));
            SetDlgItemText(IDC_LABEL_OWNER_CAPTION, _T(""));
        }
        else
        {
            CWindow wndOwner;
            wndOwner.Attach(hWndOwner);

            strTemp.Format(_T("0x%08x"), hWndOwner);
            m_LinkOwnerHandle.SetLabel(strTemp);

            dwOwnerThreadId = GetWindowThreadProcessId(hWndOwner, &dwOwnerPid);
            strTemp.Format(_T("%s (%u)"), ProcUtil::GetProcName(dwOwnerPid), dwOwnerPid);
            m_LinkOwnerProcess.SetLabel(strTemp);

            strTemp.Format(_T("%u"), dwOwnerThreadId);
            m_LinkOwnerThread.SetLabel(strTemp);

            wndOwner.GetWindowText(strTemp);
            SetDlgItemText(IDC_LABEL_OWNER_CAPTION, strTemp);
        }

        {
            CWindow wnd;
            wnd.Attach(GetDlgItem(IDC_LABEL_PARENT_HANDLE));
            wnd.SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)hWndParent);

            wnd.Detach();
            wnd.Attach(GetDlgItem(IDC_LABEL_PARENT_THREAD));
            wnd.SetWindowLongPtr(GWL_USERDATA, dwParentThreadId);

            wnd.Detach();
            wnd.Attach(GetDlgItem(IDC_LABEL_PARENT_PROCESS));
            wnd.SetWindowLongPtr(GWL_USERDATA, dwParentPid);

            wnd.Detach();
            wnd.Attach(GetDlgItem(IDC_LABEL_OWNER_HANDLE));
            wnd.SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)hWndOwner);

            wnd.Detach();
            wnd.Attach(GetDlgItem(IDC_LABEL_OWNER_THREAD));
            wnd.SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)dwOwnerThreadId);

            wnd.Detach();
            wnd.Attach(GetDlgItem(IDC_LABEL_OWNER_PROCESS));
            wnd.SetWindowLongPtr(GWL_USERDATA, (LONG_PTR)dwOwnerPid);
        }

        m_LinkParentHandle.Invalidate();
        m_LinkParentProcess.Invalidate();
        m_LinkParentThread.Invalidate();
        m_LinkOwnerHandle.Invalidate();
        m_LinkOwnerProcess.Invalidate();
        m_LinkOwnerThread.Invalidate();
    }

private:
    HBRUSH  m_hBrush;

    CWndLayout  m_WndLayout;

    CHyperLink  m_LinkParentHandle;
    CHyperLink  m_LinkParentThread;
    CHyperLink  m_LinkParentProcess;

    CHyperLink  m_LinkOwnerHandle;
    CHyperLink  m_LinkOwnerThread;
    CHyperLink  m_LinkOwnerProcess;
};

