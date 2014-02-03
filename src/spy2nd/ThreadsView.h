// ThreadsView.h : interface of the CThreadsView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CThreadsView : public CWindowImpl<CThreadsView, CTreeViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("SpyThreadsView"), CTreeViewCtrl::GetWndClassName())

	BEGIN_MSG_MAP(CThreadsView)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};
