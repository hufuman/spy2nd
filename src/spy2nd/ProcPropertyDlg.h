#pragma once

#include "ProcessInfo.h"
#include "ProcPropertyGeneralDlg.h"
#include "ProcPropertyCountersDlg.h"
#include "ProcPropertyThreadDlg.h"
#include "ProcPropertyWaitChainDlg.h"

#include "WndLayout.h"


class CProcPropertyDlg : public CDialogImpl<CProcPropertyDlg>
{
public:
	enum { IDD = IDD_PROC_PROPERTY };

	BEGIN_MSG_MAP(CProcPropertyDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		COMMAND_ID_HANDLER(IDOK, OnBtnRefresh)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)

        NOTIFY_HANDLER(IDC_TAB_PROPERTY, TCN_SELCHANGE, OnTabSelChanged)

        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

    CProcPropertyDlg()
    {
        m_hCurrentPage = NULL;
        m_dwProcId = 0;
        m_dwThreadId = 0;
        m_pWaitChainDlg = NULL;
    }

    void ShowProperty(DWORD dwProcId, DWORD dwThreadId)
    {
        m_dwProcId = dwProcId;
        m_dwThreadId = dwThreadId;

        if(!m_Proc.Open(m_dwProcId, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ))
        {
            m_GeneralDlg.ShowWindow(SW_HIDE);
            m_CountersDlg.ShowWindow(SW_HIDE);
            m_ThreadDlg.ShowWindow(SW_HIDE);
            if(m_pWaitChainDlg)
                m_pWaitChainDlg->ShowWindow(SW_HIDE);

            CString strTemp;
            strTemp.Format(_T("Failed to open process: %u"), dwProcId);
            MessageBox(strTemp);
            return;
        }

        m_GeneralDlg.RefreshProperty(m_dwProcId, m_Proc);
        m_CountersDlg.RefreshProperty(m_dwProcId, m_Proc);
        if(dwThreadId == 0)
        {
            if(m_bThreadInfoAdded)
            {
                m_Tab.DeleteItem(m_Tab.GetItemCount() - 1);
                m_bThreadInfoAdded = FALSE;
            }
        }
        else
        {
            if(!m_bThreadInfoAdded)
            {
                AddPage(_T("Thread"),   m_ThreadDlg);
                m_bThreadInfoAdded = TRUE;
            }
            m_ThreadDlg.RefreshProperty(m_dwProcId, dwThreadId, m_Proc);
        }
        if(m_pWaitChainDlg)
            m_pWaitChainDlg->RefreshProperty(dwProcId, dwThreadId, m_Proc);

        SelectPage(m_Tab.GetCurSel());
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
        m_CountersDlg.m_hWnd = NULL;
        m_ThreadDlg.m_hWnd = NULL;
        if(m_pWaitChainDlg)
            m_pWaitChainDlg->m_hWnd = NULL;
        m_hCurrentPage = NULL;
        m_bThreadInfoAdded = FALSE;

        return 0;
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        m_Tab.Attach(GetDlgItem(IDC_TAB_PROPERTY));

        m_GeneralDlg.Create(m_hWnd);
        m_CountersDlg.Create(m_hWnd);
        m_ThreadDlg.Create(m_hWnd);

        AddPage(_T("General"),  m_GeneralDlg);
        AddPage(_T("Counters"), m_CountersDlg);

        if(IsWctAvailable())
        {
            m_pWaitChainDlg = new CProcPropertyWaitChainDlg;
            m_pWaitChainDlg->Create(m_hWnd);
            AddPage(_T("WaitChain"), *m_pWaitChainDlg);
        }

        m_bThreadInfoAdded = FALSE;

        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlByHwnd(m_Tab,         Layout_HFill);
        m_WndLayout.AddControlByHwnd(m_GeneralDlg,  Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_CountersDlg,  Layout_HFill | Layout_VFill);
        m_WndLayout.AddControlByHwnd(m_ThreadDlg,  Layout_HFill | Layout_VFill);

        if(m_pWaitChainDlg)
            m_WndLayout.AddControlByHwnd(*m_pWaitChainDlg,  Layout_HFill | Layout_VFill);

        m_WndLayout.AddControlById(IDOK, Layout_Right | Layout_Bottom);
        m_WndLayout.AddControlById(IDCANCEL, Layout_Right | Layout_Bottom);

        SelectPage(0);

		CenterWindow(GetParent());
		return TRUE;
	}

    LRESULT OnBtnRefresh(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowProperty(m_dwProcId, m_dwThreadId);
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

        if(m_Proc != NULL)
            ::ShowWindow(m_hCurrentPage, SW_SHOW);
    }

private:
    CTabCtrl    m_Tab;
    CWndLayout  m_WndLayout;

    CProcessHandle  m_Proc;
    CProcPropertyGeneralDlg     m_GeneralDlg;
    CProcPropertyCountersDlg    m_CountersDlg;
    CProcPropertyThreadDlg      m_ThreadDlg;
    CProcPropertyWaitChainDlg*  m_pWaitChainDlg;

    BOOL        m_bThreadInfoAdded;

    DWORD   m_dwProcId;
    DWORD   m_dwThreadId;
    HWND    m_hCurrentPage;
};

