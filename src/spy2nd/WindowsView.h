// WindowsView.h : interface of the CWindowsView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


#include "ViewOptions.h"
#include "HighlightDlg.h"
#include "WndPropertyDlg.h"

#include "TreeViewUtil.h"

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
        REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnItemSelChanged)

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
        ShowProperty();
        return 0;
    }

    void ShowContextMenu()
    {
        HTREEITEM hItem = GetSelectedItem();
        if(hItem == NULL)
            return;

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

    LRESULT OnItemSelChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
    {
        NMTREEVIEW* pView = reinterpret_cast<NMTREEVIEW*>(pnmh);
        if(pView->itemNew.hItem != NULL && m_PropertyDlg.m_hWnd != NULL && m_PropertyDlg.IsWindowVisible())
        {
            HWND hWnd = reinterpret_cast<HWND>(this->GetItemData(pView->itemNew.hItem));
            m_PropertyDlg.ShowProperty(hWnd);
        }
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
        if(!bShow && m_PropertyDlg.m_hWnd != NULL)
            m_PropertyDlg.ShowWindow(SW_HIDE);
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
        if(m_PropertyDlg.m_hWnd == NULL)
        {
            m_PropertyDlg.Create(m_hWnd);
        }

        HTREEITEM hItem = GetSelectedItem();
        if(hItem == NULL)
            return;

        HWND hWnd = reinterpret_cast<HWND>(this->GetItemData(hItem));
        m_PropertyDlg.ShowProperty(hWnd);
    }

    BOOL MatchWindow(HTREEITEM hItem, HWND* phWnd, const CString& strCaption, const CString& strClass)
    {
        HWND hItemWnd = reinterpret_cast<HWND>(this->GetItemData(hItem));
        if(phWnd != NULL && hItemWnd == *phWnd)
            return TRUE;

        if(strCaption.IsEmpty() && strClass.IsEmpty())
            return FALSE;

        if(!strCaption.IsEmpty())
        {
            if(::GetWindowTextLength(hItemWnd) != strCaption.GetLength())
                return FALSE;
            CString strTemp;
            DWORD dwLength = strCaption.GetLength();
            ::GetWindowText(hItemWnd, strTemp.GetBuffer(dwLength + 1), dwLength + 1);
            strTemp.ReleaseBuffer();
            if(_tcsicmp(strCaption, strTemp) != 0)
                return FALSE;
        }

        if(!strClass.IsEmpty())
        {
            TCHAR szClassName[MAX_PATH];
            ::GetClassName(hItemWnd, szClassName, MAX_PATH);
            if(_tcsicmp(strClass, szClassName) != 0)
                return FALSE;
        }

        if(phWnd)
            *phWnd = hItemWnd;
        return TRUE;
    }

    virtual HTREEITEM SearchAndSelectItem(HWND& hWnd, BOOL bDownSearch, CString strCaption, CString strClass)
    {
        std::tr1::function<BOOL (HTREEITEM)> comparer = std::tr1::bind(&CWindowsView::MatchWindow, this, std::tr1::placeholders::_1, &hWnd, strCaption, strClass);
        HTREEITEM hItem = this->GetSelectedItem();

        HWND hTargetWnd = NULL;
        BOOL bItemMatched = MatchWindow(hItem, NULL, strCaption, strClass);

        if(bDownSearch)
            hItem = TreeViewUtil::TraversalItemsDown(m_hWnd, hItem, comparer);
        else
            hItem = TreeViewUtil::TraversalItemsUp(m_hWnd, hItem, comparer);
        if(hItem == NULL && !bItemMatched)
            return NULL;

        if(hItem == NULL && bItemMatched)
        {
            hItem = this->GetSelectedItem();
            hWnd = reinterpret_cast<HWND>(this->GetItemData(hItem));
        }
        this->SelectItem(hItem);
        return hItem;
    }

private:
    CImageList      m_ImageList;
    IViewHolder*    m_pHolder;
    CWndPropertyDlg m_PropertyDlg;
};
