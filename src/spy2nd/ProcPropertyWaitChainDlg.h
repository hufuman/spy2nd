#pragma once


#include "WndLayout.h"
#include "ProcessInfo.h"
#include "resource.h"

#include "WctWrapper.h"

class CProcPropertyWaitChainDlg : public CDialogImpl<CProcPropertyWaitChainDlg>
{
public:
	enum { IDD = IDD_PROCPROPERTY_WAIT_CHAIN };

	BEGIN_MSG_MAP(CProcPropertyWaitChainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
	END_MSG_MAP()

    CProcPropertyWaitChainDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
        m_WndLayout.Init(m_hWnd);
        m_WndLayout.AddControlById(IDC_TREE_WAIT_CHAIN, Layout_HFill | Layout_VFill);

        m_ImageList.Create(IDB_BITMAP_WINDOWS, 16, 1, RGB(0, 255, 0));

        CTreeViewCtrl treeChain;
        treeChain.Attach(GetDlgItem(IDC_TREE_WAIT_CHAIN));
        treeChain.SetImageList(m_ImageList, TVSIL_NORMAL);
        treeChain.SetImageList(m_ImageList, TVSIL_STATE);

		return TRUE;
	}

    void RefreshProperty(DWORD dwProcId, DWORD dwThreadId, HANDLE hProc)
    {
        CString strTemp;
        DWORD dwTemp = 0;

        CTreeViewCtrl treeChain;
        treeChain.Attach(GetDlgItem(IDC_TREE_WAIT_CHAIN));
        treeChain.DeleteAllItems();

        std::auto_ptr<CWctWrapper> pWctWrapper(new CWctWrapper);

        BOOL bResult = FALSE;
        if(dwThreadId == 0)
            bResult = pWctWrapper->InitProcessChain(dwProcId);
        else
            bResult = pWctWrapper->InitThreadChain(dwThreadId);

        if(!bResult)
        {
            CString strTemp;
            if(dwThreadId == 0)
                strTemp.Format(_T("Failed to get wait chain for process: %u"), dwProcId);
            else
                strTemp.Format(_T("Failed to get wait chain for thread: %u"), dwThreadId);
            MessageBox(strTemp);
            return;
        }

        treeChain.SetRedraw(FALSE);
        const CWctWrapper::ThreadWctInfoArray& arrThreadInfo = pWctWrapper->GetThreadWctInfo();
        int nSize = arrThreadInfo.GetSize();
        for(int i=0; i<nSize; ++ i)
        {
            const CWctWrapper::stThreadWctInfo& wctInfo = arrThreadInfo[i];

            // Insert Thread Root
            if(wctInfo.bIsCycle)
                strTemp.Format(_T("Thread: %u, DeadLock !!!"), wctInfo.dwThreadId);
            else
                strTemp.Format(_T("Thread: %u"), wctInfo.dwThreadId);

            HTREEITEM hThreadItem = treeChain.InsertItem(strTemp, 2, 2, TVI_ROOT, TVI_LAST);

            // Wait Chain
            int nChainSize = wctInfo.arrWaitChain.GetSize();
            for(int j=0; j<nChainSize; ++ j)
            {
                const WAITCHAIN_NODE_INFO& node = wctInfo.arrWaitChain[j];
                HTREEITEM hObjectItem = treeChain.InsertItem(WctGetObjectTypeName(node.ObjectType), 0, 0, hThreadItem, TVI_LAST);
                if(node.ObjectType == WctThreadType)
                {
                    strTemp.Format(_T("Process Id: %u"), node.ThreadObject.ProcessId);
                    treeChain.InsertItem(strTemp, 3, 3, hObjectItem, TVI_LAST);

                    strTemp.Format(_T("Thread Id: %u"), node.ThreadObject.ThreadId);
                    treeChain.InsertItem(strTemp, 2, 2, hObjectItem, TVI_LAST);

                    strTemp = WctGetObjectStatusName(node.ObjectStatus);
                    treeChain.InsertItem(strTemp, -1, -1, hObjectItem, TVI_LAST);
                }
                else
                {
                    if(node.LockObject.ObjectName[0] == _T('\0'))
                    {
                        treeChain.InsertItem(node.LockObject.ObjectName, -1, -1, hObjectItem, TVI_LAST);
                    }
                }
                treeChain.Expand(hObjectItem);
            }

            treeChain.Expand(hThreadItem);
        }

        treeChain.SetRedraw(TRUE);
        treeChain.Invalidate();
    }

private:
    HBRUSH      m_hBrush;
    CWndLayout  m_WndLayout;
    CImageList  m_ImageList;
};

