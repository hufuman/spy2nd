#pragma once


#include "WndLayout.h"


class CWndPropertyGeneralDlg : public CDialogImpl<CWndPropertyGeneralDlg>
{
public:
	enum { IDD = IDD_WNDPROPERTY_GENERAL };

	BEGIN_MSG_MAP(CWndPropertyGeneralDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
	END_MSG_MAP()

    CWndPropertyGeneralDlg()
    {
        m_hTargetWnd = NULL;
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlById(IDC_EDIT_CAPTION, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_HANDLE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_PROCEDURE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_RCWND, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_RCRESTORE, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_RCCLIENT, Layout_HFill);
        m_WndLayout.AddControlById(IDC_EDIT_INST, Layout_HFill);
		return TRUE;
	}

    void RefreshProperty(HWND hTargetWnd)
    {
        m_hTargetWnd = hTargetWnd;

        CWindow wnd;
        wnd.Attach(m_hTargetWnd);

        CString strTemp;

        // Caption
        wnd.GetWindowText(strTemp);
        SetDlgItemText(IDC_EDIT_CAPTION, strTemp);

        // Handle
        strTemp.Format(_T("0x%08x"), m_hTargetWnd);
        SetDlgItemText(IDC_EDIT_HANDLE, strTemp);

        // Procedure
        LONG_PTR nWndProc = wnd.GetWindowLongPtr(GWLP_WNDPROC);
        BOOL bInvalid = (::GetLastError() != ERROR_SUCCESS);
        BOOL bIsUnicode = wnd.IsWindowUnicode();
        if(bInvalid)
            strTemp.Format(_T("%s (%s)"), _T("Invalid"), bIsUnicode ? _T("Unicode") : _T("NonUnicode"));
        else
            strTemp.Format(_T("0x%08x (%s)"), nWndProc, bIsUnicode ? _T("Unicode") : _T("NonUnicode"));
        SetDlgItemText(IDC_EDIT_PROCEDURE, strTemp);

        // Rectangle
        CRect rcWnd;
        wnd.GetWindowRect(&rcWnd);
        strTemp.Format(_T("(%d, %d) - (%d, %d)  %d * %d"),
            rcWnd.left, rcWnd.top,
            rcWnd.right, rcWnd.bottom,
            rcWnd.Width(), rcWnd.Height());
        SetDlgItemText(IDC_EDIT_RCWND, strTemp);

        // Restored Rect
        WINDOWPLACEMENT placement = {sizeof(placement)};
        wnd.GetWindowPlacement(&placement);
        CRect rcRestore(placement.rcNormalPosition);
        strTemp.Format(_T("(%d, %d) - (%d, %d)  %d * %d"),
            rcRestore.left, rcRestore.top,
            rcRestore.right, rcRestore.bottom,
            rcRestore.Width(), rcRestore.Height());
        SetDlgItemText(IDC_EDIT_RCRESTORE, strTemp);

        // Client Rect
        CRect rcClient;
        wnd.GetClientRect(&rcClient);
        strTemp.Format(_T("(%d, %d) - (%d, %d)  %d * %d"),
            rcClient.left, rcClient.top,
            rcClient.right, rcClient.bottom,
            rcClient.Width(), rcClient.Height());
        SetDlgItemText(IDC_EDIT_RCCLIENT, strTemp);

        // Instance Handle
        LONG_PTR nInstance = wnd.GetWindowLongPtr(GWLP_HINSTANCE);
        strTemp.Format(_T("0x%08x"), nInstance);
        SetDlgItemText(IDC_EDIT_INST, strTemp);
    }

private:
    HWND        m_hTargetWnd;
    HBRUSH      m_hBrush;
    CWndLayout  m_WndLayout;
};

