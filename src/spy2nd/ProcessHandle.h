#pragma once


class CProcessHandle
{
    CProcessHandle(const CProcessHandle&);
    CProcessHandle& operator = (const CProcessHandle&);
public:
    CProcessHandle();
    ~CProcessHandle();

    BOOL Open(DWORD dwPid, DWORD dwAccess);
    void Close();

    operator HANDLE();

private:
    HANDLE  m_hProc;
};
