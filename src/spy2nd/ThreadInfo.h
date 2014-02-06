#pragma once

class CThreadInfo
{
public:
    CThreadInfo(void);
    ~CThreadInfo(void);

    BOOL Open(DWORD dwThreadId);
    void Close();

    CString GetPriority();
    CString GetDesktop();

    BOOL IsIoPending();
    BOOL IsSuspended();
    BOOL IsRunning();

private:
    DWORD   m_dwThreadId;
    HANDLE  m_hThread;
};
