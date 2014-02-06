#include "StdAfx.h"
#include "ProcessHandle.h"

CProcessHandle::CProcessHandle()
{
    m_hProc = NULL;
}

CProcessHandle::~CProcessHandle()
{
    Close();
}

BOOL CProcessHandle::Open(DWORD dwPid, DWORD dwAccess)
{
    Close();
    m_hProc = ::OpenProcess(dwAccess, FALSE, dwPid);
    return (m_hProc != NULL);
}

void CProcessHandle::Close()
{
    if(m_hProc)
    {
        ::CloseHandle(m_hProc);
        m_hProc = NULL;
    }
}

CProcessHandle::operator HANDLE()
{
    return m_hProc;
}
