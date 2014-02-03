// LogMsgView.h : interface of the CLogMsgView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CLogMsgView : public CWindowImpl<CLogMsgView, CListViewCtrl>
{
public:
	DECLARE_WND_SUPERCLASS(_T("SpyLogMsgView"), CListViewCtrl::GetWndClassName())

	BEGIN_MSG_MAP(CLogMsgView)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
};
