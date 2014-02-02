#include "StdAfx.h"
#include "WndLayout.h"

#include <cassert>

#define WND_LAYOUT_OBJ_NAME         _T("WLON12306")
#define WND_LAYOUT_OLD_WND_NAME     _T("WLOWN12306")

void GetChildRect(HWND hWndParent, HWND hWnd, LPRECT prcChild)
{
    ::GetWindowRect(hWnd, prcChild);
    // ::ClientToScreen(hWnd, (POINT*)prcChild);
    // ::ClientToScreen(hWnd, ((POINT*)prcChild) + 1);
    ::ScreenToClient(hWndParent, (POINT*)prcChild);
    ::ScreenToClient(hWndParent, ((POINT*)prcChild) + 1);
}

CWndLayout::CWndLayout(void)
{
    m_hWndParent = NULL;
}

CWndLayout::~CWndLayout(void)
{
}

void CWndLayout::Init(HWND hWndParent)
{
    UnInit();
    assert(::IsWindow(hWndParent));

    m_hWndParent = hWndParent;
    m_WndInfoMap.clear();

    LONG_PTR lOldWndProc = ::SetWindowLongPtr(m_hWndParent, GWLP_WNDPROC, (LONG_PTR)&CWndLayout::AutoLayoutProc);
    ::SetProp(m_hWndParent, WND_LAYOUT_OBJ_NAME, (HANDLE)this);
    ::SetProp(m_hWndParent, WND_LAYOUT_OLD_WND_NAME, (HANDLE)lOldWndProc);
}

void CWndLayout::UnInit()
{
    if(m_hWndParent == NULL)
        return;

    if(::IsWindow(m_hWndParent))
    {
        LONG_PTR lOldProc = (LONG_PTR)::GetProp(m_hWndParent, WND_LAYOUT_OLD_WND_NAME);
        ::SetWindowLongPtr(m_hWndParent, GWLP_WNDPROC, lOldProc);
        ::SetProp(m_hWndParent, WND_LAYOUT_OBJ_NAME, (HANDLE)NULL);
    }
    m_hWndParent = NULL;
}

void CWndLayout::AddControlByHwnd(HWND hWnd, DWORD dwLayout)
{
    RECT rcParent;
    RECT rcControl;
    ::GetClientRect(m_hWndParent, &rcParent);
    ::GetChildRect(m_hWndParent, hWnd, &rcControl);
    RECT rcMargin = {rcControl.left, rcControl.top, rcParent.right - rcControl.right, rcParent.bottom - rcControl.bottom};
    AddControl(hWnd, dwLayout, rcMargin);
}

void CWndLayout::AddControlById(int nId, DWORD dwLayout)
{
    HWND hWnd = ::GetDlgItem(m_hWndParent, nId);

    AddControlByHwnd(hWnd, dwLayout);
}

void CWndLayout::AddControlByIdM(int nId, DWORD dwLayout, int nLeft, int nTop, int nRight, int nBottom)
{
    HWND hWnd = ::GetDlgItem(m_hWndParent, nId);
    RECT rcMargin = {nLeft, nTop, nRight, nBottom};
    AddControl(hWnd, dwLayout, rcMargin);
}

void CWndLayout::RemoveControlByHwnd(HWND hWnd)
{
    WndInfoMap::iterator ite = m_WndInfoMap.find(hWnd);
    if(ite == m_WndInfoMap.end())
        return;

    m_WndInfoMap.erase(ite);
    Adjust();
}

void CWndLayout::Adjust()
{
    RECT rcParent;
    ::GetClientRect(m_hWndParent, &rcParent);

    HDWP hDWP = ::BeginDeferWindowPos(m_WndInfoMap.size());

    WndInfoMap::const_iterator ite = m_WndInfoMap.begin();
    for(; ite != m_WndInfoMap.end(); ++ ite)
    {
        AdjustControl(hDWP, rcParent, ite->second);
    }

    ::EndDeferWindowPos(hDWP);
}

void CWndLayout::AddControl(HWND hWnd, DWORD dwLayout, const RECT& rcMargin)
{
    stWndInfo info;
    info.hWnd = hWnd;
    assert(::IsWindow(hWnd));
    info.dwLayout = dwLayout;
    memcpy(&info.rcMargin, &rcMargin, sizeof(info.rcMargin));
    m_WndInfoMap[info.hWnd] = info;
}

void CWndLayout::AdjustControl(HDWP hDWP, RECT rcParent, const stWndInfo& info)
{
    RECT rcControl;
    ::GetChildRect(m_hWndParent, info.hWnd, &rcControl);

    int nWidth = rcControl.right - rcControl.left;
    int nHeight = rcControl.bottom - rcControl.top;

    // Horz
    if(info.dwLayout & Layout_Left)
    {
        rcControl.left = info.rcMargin.left;
        rcControl.right = rcControl.left + nWidth;
    }
    else if(info.dwLayout & Layout_Right)
    {
        rcControl.right = rcParent.right - info.rcMargin.right;
        rcControl.left = rcControl.right - nWidth;
    }
    else if(info.dwLayout & Layout_HCenter)
    {
        rcControl.left = (rcParent.right - rcParent.left - info.rcMargin.right - info.rcMargin.left - nWidth) / 2;
        rcControl.right = rcControl.left + nWidth;
    }
    else if(info.dwLayout & Layout_HFill)
    {
        rcControl.left = info.rcMargin.left;
        rcControl.right = rcParent.right - info.rcMargin.right;
    }

    // Vert
    if(info.dwLayout & Layout_Top)
    {
        rcControl.top = info.rcMargin.top;
        rcControl.bottom = rcControl.top + nHeight;
    }
    else if(info.dwLayout & Layout_Bottom)
    {
        rcControl.bottom = rcParent.bottom - info.rcMargin.bottom;
        rcControl.top = rcControl.bottom - nHeight;
    }
    else if(info.dwLayout & Layout_VCenter)
    {
        int nHeight = rcControl.bottom - rcControl.top;
        rcControl.top = (rcParent.bottom - rcParent.top - info.rcMargin.bottom - info.rcMargin.top - nHeight) / 2;
        rcControl.bottom = rcControl.top + nHeight;
    }
    else if(info.dwLayout & Layout_VFill)
    {
        rcControl.top = info.rcMargin.top;
        rcControl.bottom = rcParent.bottom - info.rcMargin.bottom;
    }

    ::DeferWindowPos(hDWP,
        info.hWnd,
        NULL, 
        rcControl.left, rcControl.top,
        rcControl.right - rcControl.left, rcControl.bottom - rcControl.top,
        SWP_NOZORDER
        );
}

LRESULT CWndLayout::AutoLayoutProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WNDPROC pfnOldProc = (WNDPROC)::GetProp(hWnd, WND_LAYOUT_OLD_WND_NAME);
    if(pfnOldProc == NULL)
        return ::DefWindowProc(hWnd, message, wParam, lParam);

    if(message == WM_SIZE)
    {
        CWndLayout* pLayout = (CWndLayout*)::GetProp(hWnd, WND_LAYOUT_OBJ_NAME);
        if(pLayout != NULL)
        {
            pLayout->Adjust();
        }
    }

    return pfnOldProc(hWnd, message, wParam, lParam);
}
