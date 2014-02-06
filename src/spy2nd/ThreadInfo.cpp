#include "StdAfx.h"
#include "ThreadInfo.h"

CThreadInfo::CThreadInfo(void)
{
    m_hThread = NULL;
    m_dwThreadId = 0;
}

CThreadInfo::~CThreadInfo(void)
{
    Close();
}

BOOL CThreadInfo::Open(DWORD dwThreadId)
{
    Close();

    m_dwThreadId = dwThreadId;
    m_hThread = ::OpenThread(THREAD_QUERY_INFORMATION | THREAD_QUERY_LIMITED_INFORMATION ,
        FALSE, dwThreadId);
    return (m_hThread != NULL);
}

void CThreadInfo::Close()
{
    if(m_hThread)
    {
        CloseHandle(m_hThread);
        m_hThread = NULL;
        m_dwThreadId = 0;
    }
}

CString CThreadInfo::GetPriority()
{
    int nPriority = ::GetThreadPriority(m_hThread);
    static struct
    {
        int priority;
        LPCTSTR szPriority;
    } data[] =
    {
        {THREAD_PRIORITY_IDLE,          _T("Idle")},
        {THREAD_PRIORITY_LOWEST,        _T("Lowest")},
        {THREAD_PRIORITY_BELOW_NORMAL,  _T("BelowNormal")},
        {THREAD_PRIORITY_NORMAL,        _T("Normal")},
        {THREAD_PRIORITY_ABOVE_NORMAL,  _T("AboveNormal")},
        {THREAD_PRIORITY_HIGHEST,       _T("Highest")},
        {THREAD_PRIORITY_TIME_CRITICAL, _T("Critical")},
    };
    LPCTSTR szPriority = NULL;
    for(int i=0; i<_countof(data); ++ i)
    {
        if(nPriority < data[i].priority)
        {
            szPriority = data[i].szPriority;
            break;
        }
    }
    if(szPriority == NULL)
        szPriority = _T("Above Critical");

    CString strPriority;
    strPriority.Format(_T("%s (%d)"), szPriority, nPriority);
    return strPriority;
}

CString CThreadInfo::GetDesktop()
{
    CString strDesk;
    HDESK hDesk = ::GetThreadDesktop(m_dwThreadId);
    if(hDesk != NULL)
    {
        TCHAR szDesk[1024];
        DWORD dwLength = sizeof(szDesk);
        if(::GetUserObjectInformation(hDesk, UOI_NAME, szDesk, sizeof(szDesk), &dwLength))
        {
            strDesk = szDesk;
        }
    }
    if(strDesk.IsEmpty())
        strDesk = _T("N/A");
    return strDesk;
}

BOOL CThreadInfo::IsIoPending()
{
    BOOL bIoPending = FALSE;
    if(!::GetThreadIOPendingFlag(m_hThread, &bIoPending))
        bIoPending = FALSE;
    return bIoPending;
}

BOOL CThreadInfo::IsSuspended()
{
    DWORD dwCount = ::SuspendThread(m_hThread);
    ::ResumeThread(m_hThread);
    return (dwCount > 0);
}

BOOL CThreadInfo::IsRunning()
{
    return (::WaitForSingleObject(m_hThread, 0) != WAIT_OBJECT_0);
}
