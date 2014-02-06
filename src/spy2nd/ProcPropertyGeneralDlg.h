#pragma once


#include "WndLayout.h"
#include "ProcessInfo.h"
#include "resource.h"

#include "ProcUtil.h"
#include "ProcessInfo.h"

class CProcPropertyGeneralDlg : public CDialogImpl<CProcPropertyGeneralDlg>, public IProcPropertyViewImpl<CProcPropertyGeneralDlg>
{
public:
	enum { IDD = IDD_PROCPROPERTY_GENERAL };

	BEGIN_MSG_MAP(CProcPropertyGeneralDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)

        COMMAND_ID_HANDLER(IDC_BTN_SELF_LOCATION, OnBtnSelfLocation)
        COMMAND_ID_HANDLER(IDC_BTN_PARENT_LOCATION, OnBtnParentLocation)
	END_MSG_MAP()

    CProcPropertyGeneralDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnBtnSelfLocation(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CString strImagePath = m_ProcInfo.GetImagePath();
        if(!strImagePath.IsEmpty())
        {
            ProcUtil::FsRedirection redirection;
            CString strCmdLine;
            strCmdLine.Format(_T("/select,\"%s\""), strImagePath);
            ::ShellExecute(m_hWnd, _T("open"), _T("Explorer.exe"), strCmdLine, NULL, SW_SHOWNORMAL);
        }
        return 0;
    }

    LRESULT OnBtnParentLocation(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        CString strImagePath = m_ProcInfo.GetParentImagePath();
        if(!strImagePath.IsEmpty())
        {
            ProcUtil::FsRedirection redirection;
            CString strCmdLine;
            strCmdLine.Format(_T("/select,\"%s\""), strImagePath);
            ::ShellExecute(m_hWnd, _T("open"), _T("Explorer.exe"), strCmdLine, NULL, SW_SHOWNORMAL);
        }
        return 0;
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlById(IDC_LABEL_PROC_DESC, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_CMDLINE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_PARENT_CMDLINE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_BTN_SELF_LOCATION, Layout_Right);
        m_WndLayout.AddControlById(IDC_BTN_PARENT_LOCATION, Layout_Right);
		return TRUE;
	}

    // IProcPropertyView
    void RefreshPropertyImpl()
    {
        CString strTemp;

        m_ProcInfo.OpenProcess(m_dwProcId);

        // Icon
        {
            CStatic icon;
            icon.Attach(GetDlgItem(IDC_PROC_ICON));
            icon.SetIcon(m_ProcInfo.GetIcon());
        }

        // Name
        strTemp.Format(_T("%s\tPID: %u"), m_ProcInfo.GetName(), m_ProcInfo.GetPid());
        SetDlgItemText(IDC_LABEL_PROC_NAME, strTemp);

        // Version
        SetDlgItemText(IDC_LABEL_PROC_VERSION, m_ProcInfo.GetVersion());

        // Desc
        SetDlgItemText(IDC_LABEL_PROC_DESC, m_ProcInfo.GetDescption());

        // Command Line
        SetDlgItemText(IDC_EDIT_CMDLINE, m_ProcInfo.GetCommandline());

        // Parent Proc Name
        {
            DWORD dwPid = m_ProcInfo.GetParentPid();
            CString strName = m_ProcInfo.GetParentName();
            if(dwPid == -1)
                strTemp = _T("Failed to retrieve parent pid");
            else if(strName.IsEmpty())
                strTemp = _T("N/A");
            else
                strTemp.Format(_T("%s\tPID:%u"), m_ProcInfo.GetParentName(), m_ProcInfo.GetParentPid());
        }
        SetDlgItemText(IDC_LABEL_PARENT_PROC_NAME, strTemp);

        // Parent CmdLine
        SetDlgItemText(IDC_EDIT_PARENT_CMDLINE, m_ProcInfo.GetParentCommandLine());

        // Chks
        CheckDlgButton(IDC_CHK_ELEVATED, m_ProcInfo.IsElevated() ? BST_CHECKED : BST_UNCHECKED);
        CheckDlgButton(IDC_CHK_INWOW64, m_ProcInfo.IsInWow64() ? BST_CHECKED : BST_UNCHECKED);
        CheckDlgButton(IDC_CHK_INJOB, m_ProcInfo.IsInJob() ? BST_CHECKED : BST_UNCHECKED);

        Invalidate();
    }

private:
    CProcessInfo    m_ProcInfo;
    HBRUSH          m_hBrush;
    CWndLayout      m_WndLayout;
};

