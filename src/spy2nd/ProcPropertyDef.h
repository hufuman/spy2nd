#pragma once



class IProcPropertyView
{
public:
    virtual ~IProcPropertyView(){}

    virtual void Show(BOOL bShow) = 0;
    virtual void SetInfo(DWORD dwProcId, DWORD dwThreadId, HANDLE hProc) = 0;
    virtual void Destroy() = 0;

    virtual void RefreshProperty(ULONG uUpdateTick) = 0;
};


template < typename Base >
class IProcPropertyViewImpl : public IProcPropertyView
{
public:
    IProcPropertyViewImpl()
    {
        m_dwProcId = 0;
        m_dwThreadId = 0;
        m_hProc = NULL;
        m_uViewTick = -1;
    }

    virtual ~IProcPropertyViewImpl(){}

    virtual void Show(BOOL bShow)
    {
        ::ShowWindow(dynamic_cast<Base*>(this)->m_hWnd, bShow ? SW_SHOW : SW_HIDE);
    }

    virtual void SetInfo(DWORD dwProcId, DWORD dwThreadId, HANDLE hProc)
    {
        m_dwProcId = dwProcId;
        m_dwThreadId = dwThreadId;
        m_hProc = hProc;
    }

    virtual void Destroy()
    {
        m_dwProcId = 0;
        m_dwThreadId = 0;
        m_hProc = NULL;
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
    DWORD   m_dwProcId;
    DWORD   m_dwThreadId;
    HANDLE  m_hProc;
    ULONG   m_uViewTick;
};
