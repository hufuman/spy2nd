// WindowsView.h : interface of the CWindowsView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


#include "ViewOptions.h"
#include "HighlightDlg.h"

class CWindowsView : public CWindowImpl<CWindowsView, CTreeViewCtrl>, public IView
{
public:
	DECLARE_WND_SUPERCLASS(_T("SpyWindowsView"), CTreeViewCtrl::GetWndClassName())

	BEGIN_MSG_MAP(CWindowsView)
        MESSAGE_HANDLER(WM_CREATE, OnCreate)
        MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)

        COMMAND_ID_HANDLER(ID_WINDOWMENU_HIGHLIGHT, OnWindowMenuHighlight)
        COMMAND_ID_HANDLER(ID_WINDOWMENU_REFRESH, OnWindowMenuRefresh)
        COMMAND_ID_HANDLER(ID_WINDOWMENU_MESSAGE, OnWindowMenuMessage)
        COMMAND_ID_HANDLER(ID_WINDOWMENU_PROPERTY, OnWindowMenuProperty)

        REFLECTED_NOTIFY_CODE_HANDLER(NM_RCLICK, OnRClicked)

        DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

    CWindowsView()
    {
        m_pHolder = NULL;
    }

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

private:
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;
        return 0;
    }

    LRESULT OnWindowMenuHighlight(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        HTREEITEM hItem = GetSelectedItem();
        if(hItem == NULL)
            return 0;

        HWND hWnd = reinterpret_cast<HWND>(this->GetItemData(hItem));

        CHighlightDlg* pHighlightDlg = new CHighlightDlg(hWnd);
        pHighlightDlg->Create(NULL, 0);
        pHighlightDlg->ShowWindow(SW_SHOWNOACTIVATE);
        pHighlightDlg->UpdateWindow();
        return 0;
    }

    LRESULT OnWindowMenuRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        RefreshWindows(m_pHolder->GetViewOptions());
        return 0;
    }

    LRESULT OnWindowMenuMessage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

    LRESULT OnWindowMenuProperty(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

    void ShowContextMenu()
    {
        CMenu menu;
        menu.LoadMenu(IDR_MENU_WINDOW);

        POINT Pt;
        ::GetCursorPos(&Pt);

        menu.GetSubMenu(0).TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON, Pt.x, Pt.y, m_hWnd);
    }

    LRESULT OnRClicked(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
    {
        POINT Pt;
        ::GetCursorPos(&Pt);
        ScreenToClient(&Pt);

        UINT uFlags = 0;
        HTREEITEM hItem = this->HitTest(Pt, &uFlags);
        if(hItem == NULL)
            return 0;

        this->Select(hItem, TVGN_CARET);
        ShowContextMenu();
        return 0;
    }

    LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        ShowContextMenu();
        return 0;
    }

    void RefreshWindows(DWORD options)
    {
        if(m_ImageList.m_hImageList == NULL)
        {
            m_ImageList.Create(IDB_BITMAP_WINDOWS, 16, 1, RGB(0, 255, 0));
            SetImageList(m_ImageList, TVSIL_NORMAL);
            SetImageList(m_ImageList, TVSIL_STATE);
        }

        this->DeleteAllItems();

        HWND hWnd = ::GetDesktopWindow();
        HTREEITEM hItem = AddWindow(TVI_ROOT, hWnd, options);

        this->Expand(hItem);
    }

    HTREEITEM AddWindow(HTREEITEM hParent, HWND hWnd, DWORD options)
    {
        CWindow wnd(hWnd);
        if((options & ViewOptionOnlyVisible) && !wnd.IsWindowVisible())
            return NULL;

        CString strText;
        wnd.GetWindowText(strText);

        CString strClass;
        ::GetClassName(hWnd, strClass.GetBuffer(1024), 1024);

        CString strTitle;
        strTitle.Format(_T("Window 0x%08x %s \"%s\""),
            hWnd,
            strClass,
            strText);
        BOOL bVisible = wnd.IsWindowVisible();
        SetLastError(0);
        HTREEITEM hItem = this->InsertItem(strTitle, bVisible ? 0 : 1, bVisible ? 0 : 1, hParent, TVI_LAST);
        this->SetItemData(hItem, reinterpret_cast<DWORD_PTR>(hWnd));

        HWND hWndChild = ::GetWindow(hWnd, GW_CHILD);
        while(hWndChild != NULL)
        {
            AddWindow(hItem, hWndChild, options);
            hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
        }

        return hItem;
    }

public:
    //////////////////////////////////////////////////////////////////////////
    // IView
    virtual void Refresh(DWORD dwOptions)
    {
        RefreshWindows(dwOptions);
    }

    virtual void Create(IViewHolder* pHolder)
    {
        m_pHolder = pHolder;

        CWindowImpl<CWindowsView, CTreeViewCtrl>::Create(m_pHolder->GetHwnd(),
            rcDefault,
            NULL,
            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_DISABLEDRAGDROP | TVS_FULLROWSELECT | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
            WS_EX_CLIENTEDGE);
        this->SetFont(AtlGetDefaultGuiFont());
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

private:
    CImageList      m_ImageList;
    IViewHolder*    m_pHolder;
};
