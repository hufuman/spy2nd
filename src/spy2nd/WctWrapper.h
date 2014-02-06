#pragma once

#include <wct.h>


class CWctWrapper
{
public:
    CWctWrapper(void);
    ~CWctWrapper(void);

    BOOL InitThreadChain(DWORD dwThreadId);
    BOOL InitProcessChain(DWORD dwProcId);

public:
    typedef ATL::CSimpleArray<WAITCHAIN_NODE_INFO> WaitChainArray;

    struct stThreadWctInfo
    {
        DWORD           dwThreadId;
        BOOL            bIsCycle;
        WaitChainArray  arrWaitChain;
    };
    typedef ATL::CSimpleArray<stThreadWctInfo> ThreadWctInfoArray;

    const ThreadWctInfoArray& GetThreadWctInfo() const;

private:
    HMODULE         m_hOLE32DLL;

    ThreadWctInfoArray m_arrThreadInfo;
};


BOOL IsWctAvailable();

LPCTSTR WctGetObjectTypeName(WCT_OBJECT_TYPE type);
LPCTSTR WctGetObjectStatusName(WCT_OBJECT_STATUS status);
