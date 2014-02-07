// ProcessesView.h : interface of the CProcessesView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once


#include "ViewOptions.h"
#include "ProcPropertyDlg.h"
#include <TlHelp32.h>

class CProcessesView : public CWindowImpl<CProcessesView, CTreeViewCtrl>, public IProcessView
{
    typedef ATL::CSimpleArray<HWND> HWNDArray;
    struct stThreadInfo
    {
        BOOL bHasVisibleWindow;
        DWORD dwThreadId;
        HWNDArray vctWindows;
    };
    typedef ATL::CSimpleArray<stThreadInfo> ThreadInfoArray;
    struct stProcessInfo
    {
        BOOL bHasVisibleWindow;
        DWORD dwProcessId;
        CString strProcName;
        ThreadInfoArray vctThreads;
    };
    typedef ATL::CSimpleArray<stProcessInfo> ProcessInfoArray;

    enum ItemType
    {
        ItemProc,
        ItemThread,
        ItemHwnd,
    };
    struct stItemInfo
    {
        stItemInfo(DWORD procId)
        {
            type = ItemProc;
            dwProcId = procId;
            dwThreadId = 0;
            hWnd = 0;
        }
        stItemInfo(DWORD procId, DWORD threadId)
        {
            type = ItemThread;
            dwProcId = procId;
            dwThreadId = threadId;
            hWnd = 0;
        }
        stItemInfo(DWORD procId, HWND wnd)
        {
            type = ItemHwnd;
            dwProcId = procId;
            dwThreadId = 0;
            hWnd = wnd;
        }
        ItemType type;
        DWORD dwProcId;
        DWORD dwThreadId;
        HWND  hWnd;
    };
    typedef ATL::CSimpleMap<HTREEITEM, stItemInfo> ItemInfoMap;

public:
	DECLARE_WND_SUPERCLASS(_T("SpyProcessesView"), CTreeViewCtrl::GetWndClassName())

    BEGIN_MSG_MAP(CProcessesView)
        MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)

        COMMAND_ID_HANDLER(ID_PROCESSMENU_MESSAGE,  OnProcessMenuMessage)
        COMMAND_ID_HANDLER(ID_PROCESSMENU_REFRESH,  OnProcessMenuRefresh)
        COMMAND_ID_HANDLER(ID_PROCESSMENU_PROPERTY, OnProcessMenuProperty)

        REFLECTED_NOTIFY_CODE_HANDLER(NM_RCLICK, OnRClicked)
        REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnItemSelChanged)
	END_MSG_MAP()

    CProcessesView()
    {
        m_pHolder = NULL;
    }

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnProcessMenuMessage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        return 0;
    }

    LRESULT OnProcessMenuRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        Refresh(m_pHolder->GetViewOptions());
        return 0;
    }

    LRESULT OnProcessMenuProperty(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        ShowProperty();
        return 0;
    }

    LRESULT OnContextMenu(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        ShowContextMenu();
        return 0;
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
        if(pView->itemNew.hItem == NULL)
            return 0;

        BOOL bProcShow = (m_ProcPropertyDlg.m_hWnd != NULL && m_ProcPropertyDlg.IsWindowVisible());
        BOOL bWndShow = (m_WndPropertyDlg.m_hWnd != NULL && m_WndPropertyDlg.IsWindowVisible());
        if(bProcShow || bWndShow)
            ShowPropertyImpl(pView->itemNew.hItem);
        return 0;
    }

    void ShowContextMenu()
    {
        HTREEITEM hItem = GetSelectedItem();
        if(hItem == NULL)
            return;

        CMenu menu;
        menu.LoadMenu(IDR_MENU_PROCESS);

        POINT Pt;
        ::GetCursorPos(&Pt);

        menu.GetSubMenu(0).TrackPopupMenu(TPM_LEFTBUTTON | TPM_RIGHTBUTTON, Pt.x, Pt.y, m_hWnd);
    }

private:
    void RefreshProcesses(DWORD options)
    {
        if(m_ImageList.m_hImageList == NULL)
        {
            m_ImageList.Create(IDB_BITMAP_WINDOWS, 16, 1, RGB(0, 255, 0));
            SetImageList(m_ImageList, TVSIL_NORMAL);
            SetImageList(m_ImageList, TVSIL_STATE);
        }

        this->DeleteAllItems();
        m_ItemInfoMap.RemoveAll();

        HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD, 0);
        if(INVALID_HANDLE_VALUE == hSnap)
        {
            MessageBox(_T("Failed to enum processes"));
            return;
        }

        ProcessInfoArray vctProcesses;
        RefreshProcess(hSnap, vctProcesses);
        RefreshThreads(hSnap, vctProcesses);

        int nProcCount = vctProcesses.GetSize();
        for(int i=0; i<nProcCount; ++ i)
        {
            stProcessInfo& process = vctProcesses[i];
            int nThreadCount = process.vctThreads.GetSize();
            for(int j=0; j<nThreadCount; ++ j)
            {
                stThreadInfo& thread = process.vctThreads[j];
                if(thread.dwThreadId == 0)
                    continue;
                RefreshWindows(process, thread);
            }
        }

        GenerateTree(vctProcesses, options);

        ::CloseHandle(hSnap);
    }

private:
    void GenerateTree(ProcessInfoArray& vctProcesses, DWORD options)
    {
        bool bOnlyVisible = ((options & ViewOptionOnlyVisible) == ViewOptionOnlyVisible);
        CString strTitle;
        int nProcCount = vctProcesses.GetSize();
        for(int i=0; i<nProcCount; ++ i)
        {
            stProcessInfo& process = vctProcesses[i];
            if(!process.bHasVisibleWindow && bOnlyVisible)
                continue;

            strTitle.Format(_T("Process %08u %s"), process.dwProcessId, process.strProcName);
            HTREEITEM hProcItem = this->InsertItem(strTitle, 3, 3, TVI_ROOT, TVI_LAST);

            {
                stItemInfo procInfo(process.dwProcessId);
                m_ItemInfoMap.Add(hProcItem, procInfo);
            }

            int nThreadCount = process.vctThreads.GetSize();
            for(int j=0; j<nThreadCount; ++ j)
            {
                stThreadInfo& thread = process.vctThreads[j];
                if(!thread.bHasVisibleWindow && bOnlyVisible)
                    continue;

                strTitle.Format(_T("Thread %08u"), thread.dwThreadId);
                HTREEITEM hThreadItem = this->InsertItem(strTitle, 2, 2, hProcItem, TVI_LAST);

                {
                    stItemInfo procInfo(process.dwProcessId, thread.dwThreadId);
                    m_ItemInfoMap.Add(hThreadItem, procInfo);
                }

                int nWindowCount = thread.vctWindows.GetSize();
                for(int k=0; k<nWindowCount; ++ k)
                {
                    HWND& hWnd = thread.vctWindows[k];
                    HTREEITEM hWndItem = AddWindow(hThreadItem, hWnd, options);
                }
            }
        }
    }

    void RefreshProcess(HANDLE hSnap, ProcessInfoArray& vctProcesses)
    {
        PROCESSENTRY32 entry = {sizeof(entry)};
        if(::Process32First(hSnap, &entry))
        {
            do 
            {
                if(entry.th32ProcessID == ::GetCurrentProcessId())
                    continue;

                stProcessInfo proc;
                proc.bHasVisibleWindow = FALSE;
                proc.dwProcessId = entry.th32ProcessID;
                proc.strProcName = entry.szExeFile;
                vctProcesses.Add(proc);
            } while (::Process32Next(hSnap, &entry));
        }
    }

    void RefreshThreads(HANDLE hSnap, ProcessInfoArray& vctProcesses)
    {
        THREADENTRY32 entry = {sizeof(entry)};
        if(::Thread32First(hSnap, &entry))
        {
            do 
            {
                stProcessInfo* pProcess = GetProcInfo(vctProcesses, entry.th32OwnerProcessID);
                if(!pProcess)
                    continue;

                stThreadInfo thread;
                thread.bHasVisibleWindow = FALSE;
                thread.dwThreadId = entry.th32ThreadID;
                pProcess->vctThreads.Add(thread);
            } while (::Thread32Next(hSnap, &entry));
        }
    }

    stProcessInfo* GetProcInfo(ProcessInfoArray& vctProcesses, DWORD dwProcId)
    {
        int nCount = vctProcesses.GetSize();
        for(int i=0; i<nCount; ++ i)
        {
            stProcessInfo& process = vctProcesses[i];
            if(process.dwProcessId == dwProcId)
                return &process;
        }
        return NULL;
    }

    static BOOL CALLBACK EnumWindowCallback(HWND hWnd, LPARAM lParam)
    {
        ATL::CSimpleArray<HWND>* pVecor = reinterpret_cast<ATL::CSimpleArray<HWND>*>(lParam);
        pVecor->Add(hWnd);
        return TRUE;
    }

    void RefreshWindows(stProcessInfo& process, stThreadInfo& thread)
    {
        ::EnumThreadWindows(thread.dwThreadId, &CProcessesView::EnumWindowCallback, reinterpret_cast<LPARAM>(&thread.vctWindows));

        BOOL bHasVisibleWindows = FALSE;
        int nCount = thread.vctWindows.GetSize();
        for(int i=0; i<nCount; ++ i)
        {
            if(::IsWindowVisible(thread.vctWindows[i]))
            {
                bHasVisibleWindows = TRUE;
                break;
            }
        }
        thread.bHasVisibleWindow = bHasVisibleWindows;
        process.bHasVisibleWindow = process.bHasVisibleWindow || bHasVisibleWindows;
    }

    HTREEITEM AddWindow(HTREEITEM hParent, HWND hWnd, DWORD options)
    {
        CWindow wnd(hWnd);
        if(!wnd.IsWindow())
            return NULL;

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

        if(hItem != NULL)
        {
            DWORD dwProcId = 0;
            ::GetWindowThreadProcessId(hWnd, &dwProcId);
            stItemInfo procInfo(dwProcId, hWnd);
            m_ItemInfoMap.Add(hItem, procInfo);
        }

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
    // IProcessView
    virtual void Refresh(DWORD dwOptions)
    {
        if(m_ProcPropertyDlg.m_hWnd != NULL)
            m_ProcPropertyDlg.ShowWindow(SW_HIDE);
        if(m_WndPropertyDlg.m_hWnd != NULL)
            m_WndPropertyDlg.ShowWindow(SW_HIDE);

        RefreshProcesses(dwOptions);
    }

    virtual void Create(IViewHolder* pHolder)
    {
        m_pHolder = pHolder;

        CWindowImpl<CProcessesView, CTreeViewCtrl>::Create(m_pHolder->GetHwnd(),
            rcDefault,
            NULL,
            WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TVS_DISABLEDRAGDROP | TVS_FULLROWSELECT | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS,
            WS_EX_CLIENTEDGE);
        this->SetFont(AtlGetDefaultGuiFont());
    }

    virtual void Show(BOOL bShow)
    {
        if(!bShow && m_ProcPropertyDlg.m_hWnd != NULL)
            m_ProcPropertyDlg.ShowWindow(SW_HIDE);
        if(!bShow && m_WndPropertyDlg.m_hWnd != NULL)
            m_WndPropertyDlg.ShowWindow(SW_HIDE);
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
        HTREEITEM hItem = GetSelectedItem();
        if(hItem == NULL)
            return;

        if(m_ProcPropertyDlg.m_hWnd != NULL)
            m_ProcPropertyDlg.ShowWindow(SW_SHOW);
        if(m_WndPropertyDlg.m_hWnd != NULL)
            m_WndPropertyDlg.ShowWindow(SW_SHOW);

        ShowPropertyImpl(hItem);
    }

    virtual SpyViewType GetViewType()
    {
        return ViewProcesses;
    }

    BOOL MatchWindow(HTREEITEM hItem, HWND hWnd)
    {
        int nIndex = m_ItemInfoMap.FindKey(hItem);
        if(nIndex == -1)
            return FALSE;

        const stItemInfo& item = m_ItemInfoMap.GetValueAt(nIndex);
        if(item.type != ItemHwnd)
            return FALSE;

        return (item.hWnd == hWnd);
    }

    BOOL MatchCaptionAndClass(HTREEITEM hItem, HWND* phTargetWnd, const CString& strCaption, const CString& strClass)
    {
        int nIndex = m_ItemInfoMap.FindKey(hItem);
        if(nIndex == -1)
            return FALSE;

        const stItemInfo& item = m_ItemInfoMap.GetValueAt(nIndex);
        if(item.type != ItemHwnd)
            return FALSE;

        if(!strCaption.IsEmpty())
        {
            if(::GetWindowTextLength(item.hWnd) != strCaption.GetLength())
                return FALSE;
            CString strTemp;
            DWORD dwLength = strCaption.GetLength();
            ::GetWindowText(item.hWnd, strTemp.GetBuffer(dwLength + 1), dwLength + 1);
            strTemp.ReleaseBuffer();
            if(_tcsicmp(strCaption, strTemp) != 0)
                return FALSE;
        }

        if(!strClass.IsEmpty())
        {
            TCHAR szClassName[MAX_PATH];
            ::GetClassName(item.hWnd, szClassName, MAX_PATH);
            if(_tcsicmp(strClass, szClassName) != 0)
                return FALSE;
        }

        if(phTargetWnd)
            *phTargetWnd = item.hWnd;
        return TRUE;
    }

    virtual HTREEITEM SearchAndSelectItem(HWND& hWnd, BOOL bDownSearch, CString strCaption, CString strClass)
    {
        HTREEITEM hItem = this->GetSelectedItem();
        HWND hTargetWnd = hWnd;
        BOOL bMatched = (hTargetWnd != NULL ) ? MatchWindow(hItem, hTargetWnd)
            : MatchCaptionAndClass(hItem, &hTargetWnd, strCaption, strClass);
        if(hWnd != NULL)
        {
            std::tr1::function<BOOL (HTREEITEM)> comparer = std::tr1::bind(&CProcessesView::MatchWindow, this, std::tr1::placeholders::_1, hWnd);
            if(bDownSearch)
                hItem = TreeViewUtil::TraversalItemsDown(m_hWnd, hItem, comparer);
            else
                hItem = TreeViewUtil::TraversalItemsUp(m_hWnd, hItem, comparer);
            if(hItem != NULL)
            {
                this->SelectItem(hItem);
                return hItem;
            }
        }
        else
        {
            std::tr1::function<BOOL (HTREEITEM)> comparer = std::tr1::bind(&CProcessesView::MatchCaptionAndClass, this, std::tr1::placeholders::_1, &hWnd, strCaption, strClass);
            if(bDownSearch)
                hItem = TreeViewUtil::TraversalItemsDown(m_hWnd, hItem, comparer);
            else
                hItem = TreeViewUtil::TraversalItemsUp(m_hWnd, hItem, comparer);
            if(hItem != NULL)
            {
                this->SelectItem(hItem);
                return hItem;
            }
        }

        if(!bMatched)
            return NULL;

        hItem = this->GetSelectedItem();
        MatchCaptionAndClass(hItem, &hWnd, strCaption, strClass);

        this->SelectItem(hItem);
        return hItem;
    }

    BOOL MatchPid(HTREEITEM hItem, DWORD dwPid)
    {
        int nIndex = m_ItemInfoMap.FindKey(hItem);
        if(nIndex == -1)
            return FALSE;

        const stItemInfo& item = m_ItemInfoMap.GetValueAt(nIndex);
        return (item.type == ItemProc && item.dwProcId == dwPid);
    }

    virtual HTREEITEM SearchAndSelectProcItem(DWORD dwPid)
    {
        std::tr1::function<BOOL (HTREEITEM)> comparer = std::tr1::bind(&CProcessesView::MatchPid, this, std::tr1::placeholders::_1, dwPid);
        HTREEITEM hItem = this->GetSelectedItem();
        if(!MatchPid(hItem, dwPid))
        {
            hItem = TreeViewUtil::TraversalItemsDown(m_hWnd, hItem, comparer);
        }
        if(hItem != NULL)
        {
            this->SelectItem(hItem);
        }
        return hItem;
    }

    BOOL MatchThreadId(HTREEITEM hItem, DWORD dwThreadId)
    {
        int nIndex = m_ItemInfoMap.FindKey(hItem);
        if(nIndex == -1)
            return FALSE;

        const stItemInfo& item = m_ItemInfoMap.GetValueAt(nIndex);
        return (item.type == ItemThread && item.dwThreadId == dwThreadId);
    }

    virtual HTREEITEM SearchAndSelectThreadItem(DWORD dwThreadId)
    {
        std::tr1::function<BOOL (HTREEITEM)> comparer = std::tr1::bind(&CProcessesView::MatchThreadId, this, std::tr1::placeholders::_1, dwThreadId);
        HTREEITEM hItem = this->GetSelectedItem();
        if(!MatchThreadId(hItem, dwThreadId))
        {
            hItem = TreeViewUtil::TraversalItemsDown(m_hWnd, hItem, comparer);
        }
        if(hItem != NULL)
        {
            this->SelectItem(hItem);
        }
        return hItem;
    }

    void ShowPropertyImpl(HTREEITEM hItem)
    {
        int nIndex = m_ItemInfoMap.FindKey(hItem);
        if(nIndex == -1)
            return;

        stItemInfo& itemInfo = m_ItemInfoMap.GetValueAt(nIndex);
        if(itemInfo.type == ItemProc || itemInfo.type == ItemThread)
        {
            BOOL bWndShow = (m_WndPropertyDlg.m_hWnd != NULL && m_WndPropertyDlg.IsWindowVisible());
            if(bWndShow)
                m_WndPropertyDlg.ShowWindow(SW_HIDE);

            if(m_ProcPropertyDlg.m_hWnd == NULL)
                m_ProcPropertyDlg.Create(m_hWnd);

            if(!m_ProcPropertyDlg.IsWindowVisible())
                m_ProcPropertyDlg.ShowWindow(SW_SHOWNOACTIVATE);
            m_ProcPropertyDlg.ShowProperty(itemInfo.dwProcId, itemInfo.dwThreadId);
        }
        else
        {
            BOOL bProcShow = (m_ProcPropertyDlg.m_hWnd != NULL && m_ProcPropertyDlg.IsWindowVisible());
            if(bProcShow)
                m_ProcPropertyDlg.ShowWindow(SW_HIDE);

            if(m_WndPropertyDlg.m_hWnd == NULL)
                m_WndPropertyDlg.Create(m_hWnd);

            if(!m_WndPropertyDlg.IsWindowVisible())
                m_WndPropertyDlg.ShowWindow(SW_SHOWNOACTIVATE);
            m_WndPropertyDlg.ShowProperty(itemInfo.hWnd);
        }
    }

private:
    CImageList          m_ImageList;
    IViewHolder*        m_pHolder;
    CProcPropertyDlg    m_ProcPropertyDlg;
    CWndPropertyDlg     m_WndPropertyDlg;

    ItemInfoMap         m_ItemInfoMap;
};
