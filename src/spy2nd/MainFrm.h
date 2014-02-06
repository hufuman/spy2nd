// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

enum SpyViewType
{
    ViewNone        = -1,
    ViewWindows     = 0,
    ViewProcesses   = 1,
    ViewLogMsg      = 2,
    ViewMax         = 3,
};

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler, public IViewHolder
{
public:
	DECLARE_FRAME_WND_CLASS(_T("Spy2nd"), IDR_MAINFRAME)

    CMainFrame()
    {
        m_SpyViewType = ViewNone;
        GetWndClassInfo().m_uCommonResourceID = IDR_MAINFRAME;
    }

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
			return TRUE;
        else
            return FALSE;
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)

        UPDATE_ELEMENT(ID_FILE_WINDOWS, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
        UPDATE_ELEMENT(ID_FILE_PROCESSES, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
        UPDATE_ELEMENT(ID_FILE_LOG_MSG, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)

        UPDATE_ELEMENT(ID_VIEW_SHOWVISIBLE, UPDUI_MENUPOPUP | UPDUI_CHECKED)
        UPDATE_ELEMENT(ID_VIEW_SHOWALL, UPDUI_MENUPOPUP | UPDUI_CHECKED)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)

		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

        COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)

        COMMAND_ID_HANDLER(ID_FILE_WINDOWS, OnFileWindows)
        COMMAND_ID_HANDLER(ID_FILE_PROCESSES, OnFileProcesses)
        COMMAND_ID_HANDLER(ID_FILE_LOG_MSG, OnFileLogMsg)

		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
        COMMAND_ID_HANDLER(ID_VIEW_SHOWVISIBLE, OnViewShowVisible)
        COMMAND_ID_HANDLER(ID_VIEW_SHOWALL, OnViewShowAll)
        COMMAND_ID_HANDLER(ID_VIEW_REFRESH, OnViewRefresh)
        COMMAND_ID_HANDLER(ID_VIEW_PROPERTY, OnViewProperty)
        COMMAND_ID_HANDLER(ID_CHANGE_VIEW, OnChangeView)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
        REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

public:
//////////////////////////////////////////////////////////////////////////
// IViewHolder
    virtual HWND GetHwnd()
    {
        return m_hWnd;
    }

    virtual void Refresh()
    {
        DWORD dwOptions = GetViewOptions();
        CWindow wnd(m_hWndClient);
        wnd.SetRedraw(FALSE);
        m_pView[m_SpyViewType]->Refresh(dwOptions);
        wnd.SetRedraw(TRUE);
        wnd.Invalidate();
        wnd.UpdateWindow();
    }

    virtual DWORD GetViewOptions()
    {
        DWORD dwState = UIGetState(ID_VIEW_SHOWVISIBLE);
        bool bOnlyVisible = ((dwState & UPDUI_CHECKED) == UPDUI_CHECKED);
        DWORD dwOptions = bOnlyVisible ? ViewOptionOnlyVisible : ViewOptionAll;

        return dwOptions;
    }

private:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CreateSimpleToolBar();

		CreateSimpleStatusBar();

        UISetCheck(ID_VIEW_SHOWALL, true);

        m_pView[ViewWindows] = dynamic_cast<IView*>(&m_WindowsView);
        m_pView[ViewProcesses] = dynamic_cast<IView*>(&m_ProcessView);
        m_pView[ViewLogMsg] = dynamic_cast<IView*>(&m_LogMsgView);

        ShowView(ViewWindows);

		UIAddToolBar(m_hWndToolBar);
		UISetCheck(ID_VIEW_TOOLBAR, 1);
		UISetCheck(ID_VIEW_STATUS_BAR, 1);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		return 0;
	}


    void ShowView(SpyViewType type)
    {
        if(type == m_SpyViewType)
            return;

        if(m_SpyViewType != ViewNone)
            m_pView[m_SpyViewType]->Show(FALSE);

        if(!m_pView[type]->IsCreated())
        {
            m_pView[type]->Create(this);
            m_pView[type]->Refresh(GetViewOptions());
        }
        m_pView[type]->Show(TRUE);
        ::SetFocus(m_pView[type]->GetHwnd());
        m_SpyViewType = type;
        m_hWndClient = m_pView[type]->GetHwnd();

        UISetCheck(ID_FILE_WINDOWS, type == ViewWindows);
        UISetCheck(ID_FILE_LOG_MSG, type == ViewLogMsg);
        UISetCheck(ID_FILE_PROCESSES, type == ViewProcesses);

        UpdateLayout();
    }

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		bHandled = FALSE;
		return 1;
	}

    // File Menu
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		PostMessage(WM_CLOSE);
		return 0;
    }

    LRESULT OnFileWindows(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowView(ViewWindows);
        return 0;
    }

    LRESULT OnFileProcesses(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowView(ViewProcesses);
        return 0;
    }

    LRESULT OnFileLogMsg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowView(ViewLogMsg);
        return 0;
    }

	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bVisible = !::IsWindowVisible(m_hWndToolBar);
		::ShowWindow(m_hWndToolBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_TOOLBAR, bVisible);
		UpdateLayout();
		return 0;
	}

	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
		::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
		UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
		UpdateLayout();
		return 0;
	}

    LRESULT OnViewShowVisible(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        UISetCheck(ID_VIEW_SHOWVISIBLE, true);
        UISetCheck(ID_VIEW_SHOWALL, false);

        Refresh();
        return 0;
    }

    LRESULT OnViewShowAll(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        UISetCheck(ID_VIEW_SHOWVISIBLE, false);
        UISetCheck(ID_VIEW_SHOWALL, true);

        Refresh();
        return 0;
    }

    LRESULT OnViewRefresh(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        Refresh();
        return 0;
    }

    LRESULT OnViewProperty(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        m_pView[m_SpyViewType]->ShowProperty();
        return 0;
    }

    LRESULT OnChangeView(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        SpyViewType type = ViewNone;
        if(m_SpyViewType == ViewWindows)
        {
            type = ViewProcesses;
        }
        else if(m_SpyViewType == ViewProcesses)
        {
            if(m_pView[ViewLogMsg]->IsCreated())
                type = ViewLogMsg;
            else
                type = ViewWindows;
        }
        else if(m_SpyViewType == ViewLogMsg)
        {
            type = ViewWindows;
        }
        if(type != ViewNone)
            ShowView(type);
        return 0;
    }

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}

private:
    CWindowsView    m_WindowsView;
    CLogMsgView     m_LogMsgView;
    CProcessesView  m_ProcessView;

    IView*          m_pView[ViewMax];

    SpyViewType     m_SpyViewType;
};
