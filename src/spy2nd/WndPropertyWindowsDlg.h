#pragma once


#include "WndLayout.h"


class CWndPropertyWindowsDlg : public CDialogImpl<CWndPropertyWindowsDlg>
{
public:
    enum { IDD = IDD_WNDPROPERTY_WINDOWS };

    BEGIN_MSG_MAP(CWndPropertyWindowsDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORBTN,     OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
    END_MSG_MAP()

    CWndPropertyWindowsDlg()
    {
        m_hTargetWnd = NULL;
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
        m_LinkOwnerHandle.m_tip.m_hWnd = NULL;
        m_LinkOwnerProcess.m_tip.m_hWnd = NULL;

        m_LinkParentHandle.SubclassWindow(GetDlgItem(IDC_LABEL_PARENT_HANDLE));
        m_LinkParentProcess.SubclassWindow(GetDlgItem(IDC_LABEL_PARENT_PROCESS));

        m_LinkOwnerHandle.SubclassWindow(GetDlgItem(IDC_LABEL_OWNER_HANDLE));
        m_LinkOwnerProcess.SubclassWindow(GetDlgItem(IDC_LABEL_OWNER_PROCESS));

        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlById(IDC_LABEL_PARENT_HANDLE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_PARENT_CAPTION, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_PARENT_PROCESS, Layout_HFill);

        m_WndLayout.AddControlById(IDC_LABEL_OWNER_HANDLE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_OWNER_CAPTION, Layout_HFill);
        m_WndLayout.AddControlById(IDC_LABEL_OWNER_PROCESS, Layout_HFill);

        m_WndLayout.AddControlById(IDC_GROUP_PARENT, Layout_HFill);
        m_WndLayout.AddControlById(IDC_GROUP_OWNER, Layout_HFill);

        return TRUE;
    }

    void RefreshProperty(HWND hTargetWnd)
    {
        m_hTargetWnd = hTargetWnd;

        CString strTemp;
        HWND hWndParent = ::GetParent(m_hTargetWnd);
        HWND hWndOwner = ::GetWindow(m_hTargetWnd, GW_OWNER);

        if(hWndParent == NULL)
        {
            m_LinkParentHandle.SetLabel(_T("NULL"));
            m_LinkParentProcess.SetLabel(_T(""));
            SetDlgItemText(IDC_LABEL_PARENT_CAPTION, _T(""));
        }
        else
        {
            CWindow wndParent;
            wndParent.Attach(hWndParent);

            strTemp.Format(_T("0x%08x"), hWndParent);
            m_LinkParentHandle.SetLabel(strTemp);

            DWORD dwProcId = 0;
            GetWindowThreadProcessId(hWndParent, &dwProcId);
            strTemp.Format(_T("%u"), dwProcId);
            m_LinkParentProcess.SetLabel(strTemp);

            wndParent.GetWindowText(strTemp);
            SetDlgItemText(IDC_LABEL_PARENT_CAPTION, strTemp);
        }

        if(hWndOwner == NULL)
        {
            m_LinkOwnerHandle.SetLabel(_T("NULL"));
            m_LinkOwnerProcess.SetLabel(_T(""));
            SetDlgItemText(IDC_LABEL_OWNER_CAPTION, _T(""));
        }
        else
        {
            CWindow wndOwner;
            wndOwner.Attach(hWndOwner);

            strTemp.Format(_T("0x%08x"), hWndOwner);
            m_LinkOwnerHandle.SetLabel(strTemp);

            DWORD dwProcId = 0;
            GetWindowThreadProcessId(hWndOwner, &dwProcId);
            strTemp.Format(_T("%u"), dwProcId);
            m_LinkOwnerProcess.SetLabel(strTemp);

            wndOwner.GetWindowText(strTemp);
            SetDlgItemText(IDC_LABEL_OWNER_CAPTION, strTemp);
        }

        m_LinkParentHandle.Invalidate();
        m_LinkParentProcess.Invalidate();
        m_LinkOwnerHandle.Invalidate();
        m_LinkOwnerProcess.Invalidate();
    }

private:
    HWND    m_hTargetWnd;
    HBRUSH  m_hBrush;

    CWndLayout  m_WndLayout;

    CHyperLink  m_LinkParentHandle;
    CHyperLink  m_LinkParentProcess;

    CHyperLink  m_LinkOwnerHandle;
    CHyperLink  m_LinkOwnerProcess;
};

