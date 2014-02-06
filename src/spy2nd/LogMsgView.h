// LogMsgView.h : interface of the CLogMsgView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


#include "ViewOptions.h"

class CLogMsgView : public CWindowImpl<CLogMsgView, CListViewCtrl>, public IView
{
public:
	DECLARE_WND_SUPERCLASS(_T("SpyLogMsgView"), CListViewCtrl::GetWndClassName())

	BEGIN_MSG_MAP(CLogMsgView)
	END_MSG_MAP()

    CLogMsgView()
    {
        m_pHolder = NULL;
    }

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)


public:
    //////////////////////////////////////////////////////////////////////////
    // IView
    virtual void Refresh(DWORD dwOptions)
    {
    }

    virtual void Create(IViewHolder* pHolder)
    {
        m_pHolder = pHolder;
    }

    virtual void Show(BOOL bShow)
    {
        ShowWindow(bShow ? SW_SHOW : SW_HIDE);
    }

    virtual BOOL IsCreated()
    {
        return (m_hWnd != NULL);
    }

    virtual HWND GetHwnd()
    {
        return m_hWnd;
    }

    virtual void ShowProperty()
    {
        ;
    }

private:
    IViewHolder*    m_pHolder;
};
