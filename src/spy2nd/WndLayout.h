#pragma once

#include <map>

enum
{
    Layout_None     = 0x0000,
    Layout_Left     = 0x0001,
    Layout_Top      = 0x0002,
    Layout_Right    = 0x0004,
    Layout_Bottom   = 0x0008,

    Layout_HFill    = 0x0010,
    Layout_VFill    = 0x0020,

    Layout_HCenter  = 0x0040,
    Layout_VCenter  = 0x0080,
};

class CWndLayout
{
    struct stWndInfo
    {
        HWND    hWnd;
        DWORD   dwLayout;
        RECT    rcMargin;
    };
    typedef std::map<HWND, stWndInfo> WndInfoMap;

public:
    CWndLayout(void);
    ~CWndLayout(void);

    void Init(HWND hWndParent);
    void UnInit();

    void AddControlByHwnd(HWND hWnd, DWORD dwLayout);
    void AddControlById(int nId, DWORD dwLayout);
    void AddControlByIdM(int nId, DWORD dwLayout, int nLeft, int nTop, int nRight, int nBottom);

    void RemoveControlByHwnd(HWND hWnd);

    void Adjust();

protected:
    void AddControl(HWND hWnd, DWORD dwLayout, const RECT& rcMargin);
    void AdjustControl(HDWP hDWP, RECT rcParent, const stWndInfo& info);

    static LRESULT WINAPI AutoLayoutProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
    HWND    m_hWndParent;
    WndInfoMap  m_WndInfoMap;
};
