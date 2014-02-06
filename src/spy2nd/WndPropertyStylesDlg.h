#pragma once


#include "WndStyles.h"


class CWndPropertyStylesDlg : public CDialogImpl<CWndPropertyStylesDlg>, public IWndPropertyViewImpl<CWndPropertyStylesDlg>
{
public:
    enum { IDD = IDD_WNDPROPERTY_STYLES };

    BEGIN_MSG_MAP(CWndPropertyStylesDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
    END_MSG_MAP()

    CWndPropertyStylesDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

    LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        bHandled = FALSE;
        if(wParam != SIZE_MAXIMIZED && wParam != SIZE_RESTORED)
            return 0;

        int nWidth = LOWORD(lParam);
        int nHeight = HIWORD(lParam);

        const int nVertInterval = 6;
        const int nHorzInterval = 6;
        int nListHeight = (nHeight - 5 * nVertInterval - m_rcEdit.Height() * 2) / 2;
        int nListWidth = nWidth - nHorzInterval * 2;

        int nEditWidth = nWidth - m_rcEdit.left - nHorzInterval;

        HDWP hDWP = BeginDeferWindowPos(4);
        // Styles Label
        GetDlgItem(IDC_LABEL_STYLES).DeferWindowPos(hDWP,
            NULL,
            nHorzInterval, nVertInterval + 4,
            m_rcLabel.Width(), m_rcLabel.Height(),
            SWP_NOZORDER);

        // Styles Edit
        GetDlgItem(IDC_EDIT_WINDOW_STYLES).DeferWindowPos(hDWP,
            NULL,
            m_rcEdit.left, nVertInterval,
            nEditWidth, m_rcEdit.Height(),
            SWP_NOZORDER);

        // Styles List
        GetDlgItem(IDC_LIST_WINDOW_STYLES).DeferWindowPos(hDWP,
            NULL,
            nHorzInterval, nVertInterval * 2 + m_rcEdit.Height(),
            nListWidth, nListHeight,
            SWP_NOZORDER);

        // ExStyles Label
        GetDlgItem(IDC_LABEL_EXSTYLES).DeferWindowPos(hDWP,
            NULL,
            nHorzInterval, nVertInterval * 3 + m_rcEdit.Height() + nListHeight + 4,
            m_rcLabel.Width(), m_rcLabel.Height(),
            SWP_NOZORDER);

        // ExStyles Edit
        GetDlgItem(IDC_EDIT_EXSTYLES).DeferWindowPos(hDWP,
            NULL,
            m_rcEdit.left, nVertInterval * 3 + m_rcEdit.Height() + nListHeight,
            nEditWidth, m_rcEdit.Height(),
            SWP_NOZORDER);

        // ExStyles List
        GetDlgItem(IDC_LIST_EXSTYLES).DeferWindowPos(hDWP,
            NULL,
            nHorzInterval, nVertInterval * 4 + m_rcEdit.Height() * 2 + nListHeight,
            nListWidth, nListHeight,
            SWP_NOZORDER);

        EndDeferWindowPos(hDWP);

        return 0;
    }

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        GetDlgItem(IDC_EDIT_WINDOW_STYLES).GetWindowRect(&m_rcEdit);
        ScreenToClient(&m_rcEdit);
        GetDlgItem(IDC_LABEL_EXSTYLES).GetWindowRect(&m_rcLabel);
        ScreenToClient(&m_rcLabel);

        return TRUE;
    }

    void RefreshPropertyImpl()
    {
        DWORD dwStyles = ::GetWindowLongPtr(m_hTargetWnd, GWL_STYLE);
        DWORD dwExtendedStyles = ::GetWindowLongPtr(m_hTargetWnd, GWL_EXSTYLE);

        StringArray arrStyles, arrExtendedStyles;
        WndStyles::GetStylesTitle(m_hTargetWnd, dwStyles, arrStyles);
        WndStyles::GetExtendedStylesTitle(m_hTargetWnd, dwExtendedStyles, arrExtendedStyles);

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
    HBRUSH  m_hBrush;
    CRect   m_rcEdit;
    CRect   m_rcLabel;
};

