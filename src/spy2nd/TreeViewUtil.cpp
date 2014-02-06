#include "StdAfx.h"
#include "TreeViewUtil.h"




namespace TreeViewUtil
{
    namespace details
    {
        void GetAllChildItems(HWND hTreeView, HTREEITEM hParent, HTREEITEM hItem, ATL::CSimpleArray<HTREEITEM>& arrItems, int& nIndex)
        {
            HTREEITEM hTempItem = TreeView_GetChild(hTreeView, hParent);

            while(hTempItem != NULL)
            {
                if(hTempItem == hItem)
                    nIndex = arrItems.GetSize();
                arrItems.Add(hTempItem);

                GetAllChildItems(hTreeView, hTempItem, hItem, arrItems, nIndex);

                hTempItem = TreeView_GetNextSibling(hTreeView, hTempItem);
            }
        }

        void GetAllTreeItems(HWND hTreeView, HTREEITEM hItem, ATL::CSimpleArray<HTREEITEM>& arrItems, int& nIndex)
        {
            int nSize = TreeView_GetCount(hTreeView);
            arrItems.RemoveAll();

            GetAllChildItems(hTreeView, TVI_ROOT, hItem, arrItems, nIndex);
        }
    }

    HTREEITEM TraversalItemsDown(HWND hTreeView, HTREEITEM hStartItem, std::tr1::function<BOOL (HTREEITEM)> comparer)
    {
        int nIndex = 0;
        ATL::CSimpleArray<HTREEITEM> arrItems;
        details::GetAllTreeItems(hTreeView, hStartItem, arrItems, nIndex);

        int nSize = arrItems.GetSize();
        for(int i=nIndex+1; i < nSize; ++ i)
        {
            if(comparer(arrItems[i]))
                return arrItems[i];
        }

        for(int i=0; i < nIndex; ++ i)
        {
            if(comparer(arrItems[i]))
                return arrItems[i];
        }

        return NULL;
    }

    HTREEITEM TraversalItemsUp(HWND hTreeView, HTREEITEM hStartItem, std::tr1::function<BOOL (HTREEITEM)> comparer)
    {
        int nIndex = 0;
        ATL::CSimpleArray<HTREEITEM> arrItems;
        details::GetAllTreeItems(hTreeView, hStartItem, arrItems, nIndex);

        int nSize = arrItems.GetSize();
        for(int i=nIndex-1; i >= 0; -- i)
        {
            if(comparer(arrItems[i]))
                return arrItems[i];
        }

        for(int i=nSize-1; i > nIndex; -- i)
        {
            if(comparer(arrItems[i]))
                return arrItems[i];
        }

        return NULL;
    }
};
