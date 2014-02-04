#pragma once


#include "WndStyles.h"


class CPropertyStylesDlg : public CDialogImpl<CPropertyStylesDlg>
{
public:
    enum { IDD = IDD_PROPERTY_STYLES };

    BEGIN_MSG_MAP(CPropertyStylesDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
    END_MSG_MAP()

    CPropertyStylesDlg()
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
        return TRUE;
    }

    void RefreshProperty(HWND hTargetWnd)
    {
        m_hTargetWnd = hTargetWnd;

        DWORD dwStyles = ::GetWindowLongPtr(hTargetWnd, GWL_STYLE);
        DWORD dwExtendedStyles = ::GetWindowLongPtr(hTargetWnd, GWL_EXSTYLE);

        StringArray arrStyles, arrExtendedStyles;
        WndStyles::GetStylesTitle(hTargetWnd, dwStyles, arrStyles);
        WndStyles::GetExtendedStylesTitle(hTargetWnd, dwExtendedStyles, arrExtendedStyles);

        CString strTemp;

        // styles
        strTemp.Format(_T("0x%08x"), dwStyles);
        SetDlgItemText(IDC_EDIT_WINDOW_STYLES, strTemp);

        CListBox listStyles;
        listStyles.Attach(GetDlgItem(IDC_LIST_WINDOW_STYLES));
        listStyles.ResetContent();
        int nStylesCount = arrStyles.GetSize();
        for(int i=0; i<nStylesCount; ++ i)
        {
            listStyles.AddString(arrStyles[i]);
        }

        // extended styles
        strTemp.Format(_T("0x%08x"), dwExtendedStyles);
        SetDlgItemText(IDC_EDIT_EXSTYLES, strTemp);

        CListBox listExStyles;
        listExStyles.Attach(GetDlgItem(IDC_LIST_EXSTYLES));
        listExStyles.ResetContent();
        int nExStylesCount = arrExtendedStyles.GetSize();
        for(int i=0; i<nExStylesCount; ++ i)
        {
            listExStyles.AddString(arrExtendedStyles[i]);
        }
    }

private:
    HWND    m_hTargetWnd;
    HBRUSH  m_hBrush;
};

