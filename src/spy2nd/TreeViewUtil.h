#pragma once




namespace TreeViewUtil
{
    HTREEITEM TraversalItemsDown(HWND hTreeView, HTREEITEM hStartItem, std::tr1::function<BOOL (HTREEITEM)> comparer);
    HTREEITEM TraversalItemsUp(HWND hTreeView, HTREEITEM hStartItem, std::tr1::function<BOOL (HTREEITEM)> comparer);
};
