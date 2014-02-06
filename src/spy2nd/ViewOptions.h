#pragma once




enum ViewOptions
{
    ViewOptionOnlyVisible   = 0x01,
    ViewOptionAll           = 0x02,
};

class IViewHolder
{
public:
    virtual ~IViewHolder(){}

    virtual HWND GetHwnd() = 0;
    virtual void Refresh() = 0;
    virtual DWORD GetViewOptions() = 0;
};

class IView
{
public:
    virtual ~IView(){}

    virtual void Refresh(DWORD dwOptions) = 0;
    virtual void Create(IViewHolder* pHolder) = 0;
    virtual void Show(BOOL bShow) = 0;
    virtual BOOL IsCreated() = 0;
    virtual HWND GetHwnd() = 0;
    virtual void ShowProperty() = 0;
};
