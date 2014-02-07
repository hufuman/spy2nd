#pragma once




enum ViewOptions
{
    ViewOptionOnlyVisible   = 0x01,
    ViewOptionAll           = 0x02,
};



enum SpyViewType
{
    ViewNone        = -1,
    ViewWindows     = 0,
    ViewProcesses   = 1,
    ViewLogMsg      = 2,
    ViewMax         = 3,
};


class IViewHolder
{
public:
    virtual ~IViewHolder(){}

    virtual HWND GetHwnd() = 0;
    virtual void Refresh() = 0;
    virtual DWORD GetViewOptions() = 0;
    virtual void ShowView(SpyViewType type) = 0;
};

class IBaseView
{
public:
    virtual ~IBaseView(){}

    virtual void Refresh(DWORD dwOptions) = 0;
    virtual void Create(IViewHolder* pHolder) = 0;
    virtual void Show(BOOL bShow) = 0;
    virtual BOOL IsCreated() = 0;
    virtual HWND GetHwnd() = 0;
    virtual void ShowProperty() = 0;
    virtual SpyViewType GetViewType() = 0;

    virtual HTREEITEM SearchAndSelectItem(HWND& hWnd, BOOL bDownSearch, CString strCaption, CString strClass) = 0;
};

class IProcessView : public IBaseView
{
public:
    virtual ~IProcessView(){}

    virtual HTREEITEM SearchAndSelectProcItem(DWORD dwPid) = 0;
    virtual HTREEITEM SearchAndSelectThreadItem(DWORD dwThreadId) = 0;
};

typedef std::tr1::function<IViewHolder* ()> ViewHolderGetter;
__declspec(selectany) ViewHolderGetter    g_ViewHolderGetter;

typedef std::tr1::function<IBaseView* ()>    BaseViewGetter;

__declspec(selectany) BaseViewGetter        g_WndViewGetter;
__declspec(selectany) BaseViewGetter        g_CurrentViewGetter;

typedef std::tr1::function<IProcessView* ()> ProcessesViewGetter;
__declspec(selectany) ProcessesViewGetter   g_ProcViewGetter;
