#pragma once


#include "WndStyles.h"


class CPropertyClassDlg : public CDialogImpl<CPropertyClassDlg>
{
public:
    enum { IDD = IDD_PROPERTY_CLASS };

    BEGIN_MSG_MAP(CPropertyClassDlg)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
        MESSAGE_HANDLER(WM_DESTROY,         OnDestroy)
        MESSAGE_HANDLER(WM_DRAWITEM,        OnDrawItem)
    END_MSG_MAP()

    CPropertyClassDlg()
    {
        m_hBkgBrush = NULL;
        m_bCreateBkgBrush = FALSE;
        m_hTargetWnd = NULL;
        m_hBkgLabel = NULL;
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
        m_hBkgPen = ::CreatePen(PS_SOLID, 2, RGB(255, 0, 255));
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
    {
        if(reinterpret_cast<HWND>(lParam) == m_hBkgLabel)
            return reinterpret_cast<LRESULT>(::GetStockObject(NULL_BRUSH));
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

    LRESULT OnDrawItem(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        DRAWITEMSTRUCT* pItem = reinterpret_cast<DRAWITEMSTRUCT*>(lParam);
        if(pItem->hwndItem != m_hBkgLabel)
        {
            bHandled = FALSE;
            return 0;
        }

        HDC hDC = pItem->hDC;

        HGDIOBJ hOldPen = ::SelectObject(hDC, m_hBkgPen);
        HGDIOBJ hOldBrush = ::SelectObject(hDC, m_hBkgBrush);
        ::Rectangle(hDC, pItem->rcItem.left, pItem->rcItem.top, pItem->rcItem.right, pItem->rcItem.bottom);
        ::SelectObject(hDC, hOldBrush);
        ::SelectObject(hDC, hOldPen);
        return 1;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;
        if(m_bCreateBkgBrush)
            ::DeleteObject(m_hBkgBrush);
        if(m_hBkgPen)
            ::DeleteObject(m_hBkgPen);
        return 0;
    }

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        m_hBkgLabel = GetDlgItem(IDC_CLASS_BACKGROUND);
        return TRUE;
    }

    void RefreshProperty(HWND hTargetWnd)
    {
        CString strTemp;
        m_hTargetWnd = hTargetWnd;

        // Instance
        HINSTANCE hInst = reinterpret_cast<HINSTANCE>(::GetWindowLongPtr(m_hTargetWnd, GWLP_HINSTANCE));

        // Class Name
        TCHAR szClassName[1024] = {0};
        if(::GetClassName(m_hTargetWnd, szClassName, 1024) == 0)
        {
            MessageBox(_T("Failed to get class name of window"));
            return;
        }

        SetDlgItemText(IDC_EDIT_CLASS_NAME, szClassName);

        // Class Style
        DWORD dwStyle = ::GetClassLongPtr(m_hTargetWnd, GCL_STYLE);
        strTemp.Format(_T("0x%08x"), dwStyle);
        SetDlgItemText(IDC_EDIT_CLASS_STYLES, strTemp);

        StringArray arrTitles;
        if(!WndStyles::GetClassStylesTitle(dwStyle, arrTitles))
        {
            MessageBox(_T("Failed to get class style of window"));
            return;
        }
        CListBox listStyles;
        listStyles.Attach(GetDlgItem(IDC_LIST_CLASS_STYLES));
        listStyles.ResetContent();
        int nTitleCount = arrTitles.GetSize();
        for(int i=0; i<nTitleCount; ++ i)
        {
            listStyles.AddString(arrTitles[i]);
        }

        // Icon
        HICON hIcon = reinterpret_cast<HICON>(::GetClassLongPtr(m_hTargetWnd, GCL_HICON));
        CStatic iconClass;
        iconClass.Attach(GetDlgItem(IDC_CLASS_ICON));
        iconClass.SetIcon(hIcon);

        // Cursor
        HCURSOR hCursor = reinterpret_cast<HCURSOR>(::GetClassLongPtr(m_hTargetWnd, GCL_HCURSOR));
        CStatic cursorClass;
        cursorClass.Attach(GetDlgItem(IDC_CLASS_CURSOR));
        cursorClass.SetCursor(hCursor);

        // 
        CStatic bkgClass;
        bkgClass.Attach(GetDlgItem(IDC_CLASS_BACKGROUND));
        if(m_bCreateBkgBrush)
        {
            ::DeleteObject(m_hBkgBrush);
            m_hBkgBrush = NULL;
        }

        HBRUSH hBkgBrush = reinterpret_cast<HBRUSH>(::GetClassLongPtr(m_hTargetWnd, GCL_HBRBACKGROUND));
        LOGBRUSH LogBrush = {0};
        m_bCreateBkgBrush = (::GetObject(hBkgBrush, sizeof(LogBrush), &LogBrush) == 0);
        if(m_bCreateBkgBrush)
        {
            m_hBkgBrush = hBkgBrush;
        }
        else
        {
            m_hBkgBrush = ::GetSysColorBrush(reinterpret_cast<int>(hBkgBrush) + 1);
        }
        bkgClass.Invalidate();
    }

private:
    HWND    m_hTargetWnd;
    HBRUSH  m_hBrush;
    BOOL    m_bCreateBkgBrush;
    HBRUSH  m_hBkgBrush;
    HPEN    m_hBkgPen;
    HWND    m_hBkgLabel;
};

