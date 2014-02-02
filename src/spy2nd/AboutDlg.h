#pragma once


#include "LinkStatic.h"



class CAboutDlg : public CDialogImpl<CAboutDlg>
{
public:
	enum { IDD = IDD_ABOUTBOX };

	BEGIN_MSG_MAP(CAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()


	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        // m_Link.SubclassDlgItem(IDC_LABEL_AUTHOR, this);
        // m_Link.AttachToWindow(GetDlgItem(IDC_LABEL_AUTHOR).m_hWnd);
        // m_Link.Init();
        m_LinkAuthor.SubclassWindow(GetDlgItem(IDC_LABEL_AUTHOR).m_hWnd);
        m_LinkAuthor.SetHyperLink(_T("https://github.com/hufuman"));

		CenterWindow(GetParent());
		return TRUE;
	}

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}

private:
    CHyperLink m_LinkAuthor;
};

