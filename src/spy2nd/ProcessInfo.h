#pragma once


#include "ProcessHandle.h"

class CProcessInfo
{
public:
    CProcessInfo();
    ~CProcessInfo();

    BOOL OpenProcess(DWORD dwPid);
    void Close();

    DWORD   GetPid();
    HICON   GetIcon();
    CString GetName();
    CString GetCommandline();
    CString GetVersion();
    CString GetDescption();
    CString GetImagePath();

    DWORD GetParentPid();
    CString GetParentName();
    CString GetParentImagePath();
    CString GetParentCommandLine();

    BOOL IsElevated();
    BOOL IsInWow64();
    BOOL IsInJob();

private:
    void Empty();
    BOOL InitInfo();
    BOOL InitSystemInfo();

private:
    DWORD   m_dwProcId;
    CProcessHandle  m_Proc;

    HICON   m_hIcon;
    CString m_strImagePath;
    CString m_strCmdLine;
    CString m_strVersion;
    CString m_strDesc;

    DWORD   m_dwParentPid;
    CString m_strParentImagePath;
    CString m_strParentCmdLine;

    BOOL    m_bElevated;
    BOOL    m_bInWow64;
    BOOL    m_bInJob;
};
