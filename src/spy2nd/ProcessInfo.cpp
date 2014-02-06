#include "StdAfx.h"
#include "ProcessInfo.h"

#include "ProcUtil.h"
#include "PEFileInfo.h"

CProcessInfo::CProcessInfo()
{
    Empty();
}

CProcessInfo::~CProcessInfo()
{
    Close();
}

BOOL CProcessInfo::OpenProcess(DWORD dwPid)
{
    Close();

    if(dwPid == 0 || dwPid == 4)
    {
        m_dwProcId = dwPid;
        return InitSystemInfo();
    }

    if(!m_Proc.Open(dwPid, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ))
    {
        ATLASSERT(FALSE);
        return FALSE;
    }

    m_dwProcId = dwPid;
    return InitInfo();
}

void CProcessInfo::Close()
{
    if(m_Proc != NULL)
    {
        m_Proc.Close();
        if(m_hIcon)
            ::DestroyIcon(m_hIcon);

        Empty();
    }
}

DWORD CProcessInfo::GetPid()
{
    return m_dwProcId;
}

HICON CProcessInfo::GetIcon()
{
    return m_hIcon;
}

CString CProcessInfo::GetName()
{
    CString strName;
    if(m_strImagePath.IsEmpty())
        return strName;

    int pos = m_strImagePath.ReverseFind(_T('\\'));
    if(pos == -1)
        strName = m_strImagePath;
    else
        strName = m_strImagePath.Mid(pos + 1);
    return strName;
}

CString CProcessInfo::GetCommandline()
{
    return m_strCmdLine;
}

CString CProcessInfo::GetVersion()
{
    return m_strVersion;
}

CString CProcessInfo::GetDescption()
{
    return m_strDesc;
}

CString CProcessInfo::GetImagePath()
{
    return m_strImagePath;
}

DWORD CProcessInfo::GetParentPid()
{
    return m_dwParentPid;
}

CString CProcessInfo::GetParentName()
{
    CString strName;
    if(m_strParentImagePath.IsEmpty())
        return strName;

    int pos = m_strParentImagePath.ReverseFind(_T('\\'));
    if(pos == -1)
        strName = m_strParentImagePath;
    else
        strName = m_strParentImagePath.Mid(pos + 1);
    return strName;
}

CString CProcessInfo::GetParentImagePath()
{
    return m_strParentImagePath;
}

CString CProcessInfo::GetParentCommandLine()
{
    return m_strParentCmdLine;
}

BOOL CProcessInfo::IsElevated()
{
    return m_bElevated;
}

BOOL CProcessInfo::IsInWow64()
{
    return m_bInWow64;
}

BOOL CProcessInfo::IsInJob()
{
    return m_bInJob;
}

void CProcessInfo::Empty()
{
    m_dwProcId = 0;

    m_hIcon = NULL;

    m_strImagePath = _T("");
    m_strCmdLine = _T("");
    m_strVersion = _T("");
    m_strDesc = _T("");

    m_dwParentPid = 0;
    m_strParentImagePath = _T("");
    m_strParentCmdLine = _T("");

    m_bElevated = FALSE;
    m_bInWow64 = FALSE;
    m_bInJob = FALSE;
}

BOOL CProcessInfo::InitSystemInfo()
{
    m_hIcon = ::LoadIcon(NULL, IDI_APPLICATION);

    m_strImagePath = (m_dwProcId == 0) ? _T("[System]") : _T("[System Idle Process]");
    m_strCmdLine = _T("");
    m_strVersion = _T("");
    m_strDesc = _T("");

    m_dwParentPid = 0;
    m_strParentImagePath = _T("");
    m_strParentCmdLine = _T("");

    m_bElevated = TRUE;
    m_bInWow64 = FALSE;
    m_bInJob = FALSE;
    return TRUE;
}

BOOL CProcessInfo::InitInfo()
{
    // ImagePath
    m_strImagePath = ProcUtil::GetProcessImagePath(m_Proc);
    if(m_strImagePath.IsEmpty())
    {
        ATLASSERT(FALSE);
        return FALSE;
    }

    // hIcon
    if(::ExtractIconEx(m_strImagePath, 0, &m_hIcon, NULL, 1) != 1)
    {
        m_hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
    }

    // CmdLine
    m_strCmdLine = ProcUtil::GetProcCommandLine(m_Proc);

    // Version
    CPEFileInfo pefile;
    if(pefile.Open(m_strImagePath))
    {
        m_strVersion = pefile.GetVersion();
        m_strDesc = pefile.GetDesc();
    }

    // Parent Process
    m_dwParentPid = ProcUtil::GetProcParentPid(m_Proc);
    if(m_dwParentPid != -1 && m_dwParentPid != 0)
    {
        CProcessHandle procParent;
        if(procParent.Open(m_dwParentPid, PROCESS_QUERY_INFORMATION | PROCESS_VM_READ))
        {
            m_strParentCmdLine = ProcUtil::GetProcCommandLine(procParent);
            m_strParentImagePath = ProcUtil::GetProcessImagePath(procParent);
        }
    }

    // Elevated
    m_bElevated = ProcUtil::IsProcElevated(m_Proc);

    // In Wow64
    m_bInWow64 = ProcUtil::IsProcInWow64(m_Proc);

    // InJob
    if(!::IsProcessInJob(m_Proc, NULL, &m_bInJob))
        m_bInJob = FALSE;

    return TRUE;
}


