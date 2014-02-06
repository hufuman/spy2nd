#pragma once



class IWndPropertyView
{
public:
    virtual ~IWndPropertyView(){}

    virtual void Show(BOOL bShow) = 0;
    virtual void SetInfo(HWND hWnd) = 0;
    virtual void Destroy() = 0;

    virtual void RefreshProperty(ULONG uUpdateTick) = 0;
};


template < typename Base >
class IWndPropertyViewImpl : public IWndPropertyView
{
public:
    IWndPropertyViewImpl()
    {
        m_uViewTick = -1;
        m_hTargetWnd = NULL;
    }

    virtual ~IWndPropertyViewImpl(){}

    virtual void Show(BOOL bShow)
    {
        ::ShowWindow(dynamic_cast<Base*>(this)->m_hWnd, bShow ? SW_SHOW : SW_HIDE);
    }

    virtual void SetInfo(HWND hWnd)
    {
        m_hTargetWnd = hWnd;
    }

    virtual void Destroy()
    {
        m_hTargetWnd = NULL;
        dynamic_cast<Base*>(this)->m_hWnd = NULL;
    }

    virtual void RefreshProperty(ULONG uUpdateTick)
    {
        if(uUpdateTick != m_uViewTick)
        {
            m_uViewTick = uUpdateTick;
            dynamic_cast<Base*>(this)->RefreshPropertyImpl();
        }
    }

protected:
    HWND    m_hTargetWnd;
    ULONG   m_uViewTick;
};
