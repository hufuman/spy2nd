#include "StdAfx.h"
#include "WctWrapper.h"


namespace
{
typedef HWCT (WINAPI *PFN_OpenThreadWaitChainSession)(
                            __in DWORD Flags,
                            __in_opt PWAITCHAINCALLBACK callback
                            );

typedef VOID (WINAPI *PFN_CloseThreadWaitChainSession)(
                             __in HWCT WctHandle
                             );

typedef BOOL (WINAPI *PFN_GetThreadWaitChain)(
                    __in HWCT WctHandle,
                    __in_opt DWORD_PTR Context,
                    __in DWORD Flags,
                    __in DWORD ThreadId,
                    __inout LPDWORD NodeCount,
                    __out_ecount(*NodeCount) PWAITCHAIN_NODE_INFO NodeInfoArray,
                    __out LPBOOL IsCycle
                    );

typedef VOID (WINAPI *PFN_RegisterWaitChainCOMCallback)(
                              __in PCOGETCALLSTATE CallStateCallback,
                              __in PCOGETACTIVATIONSTATE ActivationStateCallback
                              );


HWCT WINAPI StubOpenThreadWaitChainSession(
    __in DWORD Flags,
    __in_opt PWAITCHAINCALLBACK callback
    )
{
    static PFN_OpenThreadWaitChainSession pfnOpenThreadWaitChainSession =
        (PFN_OpenThreadWaitChainSession)::GetProcAddress(::GetModuleHandle(_T("ADVAPI32.dll")), "OpenThreadWaitChainSession");
    if(pfnOpenThreadWaitChainSession == NULL)
        return NULL;
    else
        return pfnOpenThreadWaitChainSession(Flags, callback);
}

VOID WINAPI StubCloseThreadWaitChainSession(
    __in HWCT WctHandle
    )
{
    static PFN_CloseThreadWaitChainSession pfnCloseThreadWaitChainSession =
        (PFN_CloseThreadWaitChainSession)::GetProcAddress(::GetModuleHandle(_T("ADVAPI32.dll")), "CloseThreadWaitChainSession");

    if(pfnCloseThreadWaitChainSession == NULL)
        return;

    pfnCloseThreadWaitChainSession(WctHandle);
}

BOOL WINAPI StubGetThreadWaitChain(
    __in HWCT WctHandle,
    __in_opt DWORD_PTR Context,
    __in DWORD Flags,
    __in DWORD ThreadId,
    __inout LPDWORD NodeCount,
    __out_ecount(*NodeCount) PWAITCHAIN_NODE_INFO NodeInfoArray,
    __out LPBOOL IsCycle
    )
{
    static PFN_GetThreadWaitChain pfnGetThreadWaitChain =
        (PFN_GetThreadWaitChain)::GetProcAddress(::GetModuleHandle(_T("ADVAPI32.dll")), "GetThreadWaitChain");
    if(pfnGetThreadWaitChain == NULL)
        return NULL;
    else
        return pfnGetThreadWaitChain(WctHandle, Context, Flags, ThreadId, NodeCount, NodeInfoArray, IsCycle);
}

VOID WINAPI StubRegisterWaitChainCOMCallback(
    __in PCOGETCALLSTATE CallStateCallback,
    __in PCOGETACTIVATIONSTATE ActivationStateCallback
    )
{
    static PFN_RegisterWaitChainCOMCallback pfnRegisterWaitChainCOMCallback =
        (PFN_RegisterWaitChainCOMCallback)::GetProcAddress(::GetModuleHandle(_T("ADVAPI32.dll")), "RegisterWaitChainCOMCallback");
    if(pfnRegisterWaitChainCOMCallback == NULL)
        return;

    pfnRegisterWaitChainCOMCallback(CallStateCallback, ActivationStateCallback);
}

}

CWctWrapper::CWctWrapper(void)
{
    m_hOLE32DLL = LoadLibrary(TEXT("OLE32.DLL"));
}

CWctWrapper::~CWctWrapper(void)
{
    if(m_hOLE32DLL)
        ::FreeLibrary(m_hOLE32DLL);
}

BOOL CWctWrapper::InitThreadChain(DWORD dwThreadId)
{
    if(m_hOLE32DLL == NULL)
        return FALSE;

    HWCT hWct = StubOpenThreadWaitChainSession(0, 0);
    if(hWct == NULL)
        return FALSE;

    //两个COM的函数指针
    PCOGETCALLSTATE CallStateCallback;
    PCOGETACTIVATIONSTATE ActivationStateCallback;

    //从ole32.dll中取得两个函数的地址
    CallStateCallback = (PCOGETCALLSTATE)
        ::GetProcAddress(m_hOLE32DLL, "CoGetCallState");
    ActivationStateCallback = (PCOGETACTIVATIONSTATE)
        ::GetProcAddress(m_hOLE32DLL, "CoGetActivationState");

    //注册COM函数，使得WCT可以报告COM相关事件
    ::StubRegisterWaitChainCOMCallback(CallStateCallback, ActivationStateCallback);

    BOOL bIsChain = FALSE;
    DWORD dwCount = WCT_MAX_NODE_COUNT;
    WAITCHAIN_NODE_INFO info[WCT_MAX_NODE_COUNT];

    BOOL bResult = FALSE;
    for(;;)
    {
        if(!::StubGetThreadWaitChain(hWct,
            0,
            WCTP_GETINFO_ALL_FLAGS,
            ::GetCurrentThreadId(),
            &dwCount,
            info,
            &bIsChain))
        {
            break;
        }

        stThreadWctInfo stubInfo;
        if(!m_arrThreadInfo.Add(stubInfo))
            break;

        stThreadWctInfo& threadInfo = m_arrThreadInfo[m_arrThreadInfo.GetSize() - 1];
        threadInfo.dwThreadId = dwThreadId;
        threadInfo.bIsCycle = bIsChain;

        for(DWORD i=0; i<dwCount; ++ i)
        {
            threadInfo.arrWaitChain.Add(info[i]);
        }

        bResult = TRUE;
        break;
    }

    StubCloseThreadWaitChainSession(hWct);
    return bResult;
}

BOOL CWctWrapper::InitProcessChain(DWORD dwProcId)
{
    if(m_hOLE32DLL == NULL)
        return FALSE;

    HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if(hSnap == NULL)
        return FALSE;

    BOOL bResult = FALSE;
    THREADENTRY32 entry = {sizeof(entry)};
    for(;;)
    {
        if(!::Thread32First(hSnap, &entry))
            break;

        bResult = TRUE;
        do 
        {
            if(entry.th32OwnerProcessID != dwProcId)
                continue;

            bResult = InitThreadChain(entry.th32ThreadID);

        } while (bResult && ::Thread32Next(hSnap, &entry));

        break;
    }

    ::CloseHandle(hSnap);
    return bResult;
}

const CWctWrapper::ThreadWctInfoArray& CWctWrapper::GetThreadWctInfo() const
{
    return m_arrThreadInfo;
}

BOOL IsWctAvailable()
{
    DWORD dwVersion = ::GetVersion();
    DWORD dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    return (dwMajorVersion >= 6);
}

LPCTSTR WctGetObjectTypeName(WCT_OBJECT_TYPE type)
{
    static struct
    {
        WCT_OBJECT_TYPE type;
        LPCTSTR szType;
    } data[] =
    {
        {WctCriticalSectionType,    L"CriticalSection"},
        {WctSendMessageType,        L"SendMessage"},
        {WctMutexType,              L"Mutex"},
        {WctAlpcType,               L"Alpc"},
        {WctComType,                L"Com"},
        {WctThreadWaitType,         L"ThreadWait"},
        {WctProcessWaitType,        L"ProcessWait"},
        {WctThreadType,             L"Thread"},
        {WctComActivationType,      L"ComActivation"},
        {WctUnknownType,            L"Unknown"},
    };

    if(type < WctCriticalSectionType || type > WctUnknownType)
    {
        return _T("WrongType");
    }
    return data[type - 1].szType;
}

LPCTSTR WctGetObjectStatusName(WCT_OBJECT_STATUS status)
{
    static struct
    {
        WCT_OBJECT_STATUS status;
        LPCTSTR szStatus;
    } data[] =
    {
        {WctStatusNoAccess,     L"NoAccess"},
        {WctStatusRunning,      L"Running"},
        {WctStatusBlocked,      L"Blocked"},
        {WctStatusPidOnly,      L"PidOnly"},
        {WctStatusPidOnlyRpcss, L"PidOnlyRpcss"},
        {WctStatusOwned,        L"Owned"},
        {WctStatusNotOwned,     L"NotOwned"},
        {WctStatusAbandoned,    L"Abandoned"},
        {WctStatusUnknown,      L"Unknown"},
        {WctStatusError,        L"Error"},
    };

    if(status < WctStatusNoAccess || status > WctStatusError)
    {
        return _T("WrongStatus");
    }
    return data[status - 1].szStatus;
}
