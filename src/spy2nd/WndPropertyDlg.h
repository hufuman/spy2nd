#pragma once


#include "WndPropertyGeneralDlg.h"
#include "WndPropertyStylesDlg.h"
#include "WndPropertyWindowsDlg.h"
#include "WndPropertyClassDlg.h"
#include "WndPropertyMiscDlg.h"

#include "WndLayout.h"


class CWndPropertyDlg : public CDialogImpl<CWndPropertyDlg>
{
public:
	enum { IDD = IDD_WND_PROPERTY };

	BEGIN_MSG_MAP(CWndPropertyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		COMMAND_ID_HANDLER(IDOK, OnBtnRefresh)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)

        NOTIFY_HANDLER(IDC_TAB_PROPERTY, TCN_SELCHANGE, OnTabSelChanged)

        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    CWndPropertyDlg()
    {
        m_hCurrentPage = NULL;
        m_hTargetWnd = NULL;
    }

    void ShowProperty(HWND hWnd)
    {
        m_hTargetWnd = hWnd;

        m_GeneralDlg.RefreshProperty(m_hTargetWnd);
        m_StylesDlg.RefreshProperty(m_hTargetWnd);
        m_WindowsDlg.RefreshProperty(m_hTargetWnd);
        m_ClassDlg.RefreshProperty(m_hTargetWnd);
        m_MiscDlg.RefreshProperty(m_hTargetWnd);
    }

    LRESULT OnTabSelChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
    {
        SelectPage(m_Tab.GetCurSel());
        return 0;
    }

    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;

        m_WndLayout.UnInit();
        m_Tab.m_hWnd = NULL;
        m_GeneralDlg.m_hWnd = NULL;
        m_StylesDlg.m_hWnd = NULL;
        m_WindowsDlg.m_hWnd = NULL;
        m_ClassDlg.m_hWnd = NULL;
        m_MiscDlg.m_hWnd = NULL;
        m_hCurrentPage = NULL;

        return 0;
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        m_Tab.Attach(GetDlgItem(IDC_TAB_PROPERTY));

        m_GeneralDlg.Create(m_hWnd);
        m_StylesDlg.Create(m_hWnd);
        m_WindowsDlg.Create(m_hWnd);
        m_ClassDlg.Create(m_hWnd);
        m_MiscDlg.Create(m_hWnd);

        AddPage(_T("General"),  m_GeneralDlg);
        AddPage(_T("Styles"),   m_StylesDlg);
        AddPage(_T("Windows"),  m_WindowsDlg);
        AddPage(_T("Class"),    m_ClassDlg);
        AddPage(_T("Misc"),     m_MiscDlg);

        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlByHwnd(m_Tab,         Layout_HFill);
        m_WndLayout.AddControlByHwnd(m_GeneralDlg,  Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_StylesDlg,   Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_WindowsDlg,  Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_ClassDlg,    Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_MiscDlg,     Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlById(IDOK, Layout_Right | Layout_Bottom);
        m_WndLayout.AddControlById(IDCANCEL, Layout_Right | Layout_Bottom);

        SelectPage(0);

		CenterWindow(GetParent());
		return TRUE;
	}

    LRESULT OnBtnRefresh(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowProperty(m_hTargetWnd);
        return 0;
    }

	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DestroyWindow();
		return 0;
	}

    void AddPage(LPCTSTR szTitle, HWND hWndPage)
    {
        int nIndex = m_Tab.InsertItem(m_Tab.GetItemCount(), TCIF_TEXT | TCIF_PARAM, szTitle, 0, reinterpret_cast<LPARAM>(hWndPage));

        CRect rcPage;
        m_Tab.GetWindowRect(&rcPage);
        ScreenToClient(&rcPage);
        rcPage.top = rcPage.bottom;
        rcPage.bottom = rcPage.top + 225;

        ::MoveWindow(hWndPage, rcPage.left, rcPage.top, rcPage.Width(), rcPage.Height(), TRUE);
    }

    void SelectPage(int nIndex)
    {
        if(m_hCurrentPage != NULL)
        {
            ::ShowWindow(m_hCurrentPage, SW_HIDE);
            m_hCurrentPage = NULL;
        }

        TCITEM item = {TCIF_PARAM};
        m_Tab.GetItem(nIndex, &item);
        m_hCurrentPage = reinterpret_cast<HWND>(item.lParam);

        ::ShowWindow(m_hCurrentPage, SW_SHOW);
    }

private:
    CWndLayout  m_WndLayout;

    CTabCtrl    m_Tab;

    CWndPropertyGeneralDlg m_GeneralDlg;
    CWndPropertyStylesDlg  m_StylesDlg;
    CWndPropertyWindowsDlg m_WindowsDlg;
    CWndPropertyClassDlg   m_ClassDlg;
    CWndPropertyMiscDlg    m_MiscDlg;

    HWND    m_hTargetWnd;
    HWND    m_hCurrentPage;
};

