// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

enum SpyViewType
{
    ViewNone,
    ViewWindows,
    ViewThreads,
    ViewProcesses,
    ViewLogMsg,
};

class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

    CWindowsView    m_WindowsView;
	CLogMsgView     m_LogMsgView;
    CThreadsView    m_ThreadsView;
    CProcessesView  m_ProcessView;

    SpyViewType     m_SpyViewType;

    CMainFrame()
    {
        m_SpyViewType = ViewNone;
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
        UPDATE_ELEMENT(ID_FILE_THREADS, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
        UPDATE_ELEMENT(ID_FILE_PROCESSES, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
        UPDATE_ELEMENT(ID_FILE_LOG_MSG, UPDUI_MENUPOPUP | UPDUI_TOOLBAR)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

        COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)

        COMMAND_ID_HANDLER(ID_FILE_WINDOWS, OnFileWindows)
        COMMAND_ID_HANDLER(ID_FILE_THREADS, OnFileThreads)
        COMMAND_ID_HANDLER(ID_FILE_PROCESSES, OnFileProcesses)
        COMMAND_ID_HANDLER(ID_FILE_LOG_MSG, OnFileLogMsg)

		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(CFrameWindowImpl<CMainFrame>)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CreateSimpleToolBar();

		CreateSimpleStatusBar();

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

        if(type == ViewWindows)
        {
            if(m_WindowsView.m_hWnd == NULL)
            {
                m_hWndClient = m_WindowsView.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
                m_WindowsView.SetFont(AtlGetDefaultGuiFont());
            }
            else
            {
                m_hWndClient = m_WindowsView.m_hWnd;
            }
        }
        else if(type == ViewLogMsg)
        {
            if(m_LogMsgView.m_hWnd == NULL)
            {
                m_hWndClient = m_LogMsgView.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
                m_LogMsgView.SetFont(AtlGetDefaultGuiFont());
            }
            else
            {
                m_hWndClient = m_LogMsgView.m_hWnd;
            }
        }
        else if(type == ViewThreads)
        {
            if(m_ThreadsView.m_hWnd == NULL)
            {
                m_hWndClient = m_ThreadsView.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
                m_ThreadsView.SetFont(AtlGetDefaultGuiFont());
            }
            else
            {
                m_hWndClient = m_ThreadsView.m_hWnd;
            }
        }
        else if(type == ViewProcesses)
        {
            if(m_ProcessView.m_hWnd == NULL)
            {
                m_hWndClient = m_ProcessView.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | LVS_REPORT | LVS_SHOWSELALWAYS, WS_EX_CLIENTEDGE);
                m_ProcessView.SetFont(AtlGetDefaultGuiFont());
            }
            else
            {
                m_hWndClient = m_ProcessView.m_hWnd;
            }
        }
        if(m_WindowsView.m_hWnd != NULL)
            m_WindowsView.ShowWindow(type == ViewWindows ? SW_SHOW : SW_HIDE);
        if(m_LogMsgView.m_hWnd != NULL)
            m_LogMsgView.ShowWindow(type == ViewLogMsg ? SW_SHOW : SW_HIDE);
        if(m_ThreadsView.m_hWnd != NULL)
            m_ThreadsView.ShowWindow(type == ViewThreads ? SW_SHOW : SW_HIDE);
        if(m_ProcessView.m_hWnd != NULL)
            m_ProcessView.ShowWindow(type == ViewProcesses ? SW_SHOW : SW_HIDE);

        UISetCheck(ID_FILE_WINDOWS, type == ViewWindows);
        UISetCheck(ID_FILE_LOG_MSG, type == ViewLogMsg);
        UISetCheck(ID_FILE_THREADS, type == ViewThreads);
        UISetCheck(ID_FILE_PROCESSES, type == ViewProcesses);

        m_SpyViewType = type;

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

    LRESULT OnFileThreads(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowView(ViewThreads);
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

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
		return 0;
	}
};
