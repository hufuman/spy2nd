#include "StdAfx.h"
#include "PEFileInfo.h"

CPEFileInfo::CPEFileInfo(void)
{
    m_pBlock = NULL;
    m_dwSize = 0;
}

CPEFileInfo::~CPEFileInfo(void)
{
    Close();
}

BOOL CPEFileInfo::Open(LPCTSTR szImagePath)
{
    Close();

    DWORD dwSize = ::GetFileVersionInfoSize(szImagePath, NULL);
    if(dwSize == 0)
        return FALSE;

    LPVOID pBlock = malloc(dwSize);
    if(pBlock == NULL)
        return FALSE;

    if(!::GetFileVersionInfo(szImagePath, 0, dwSize, pBlock))
    {
        free(pBlock);
        return FALSE;
    }

    m_pBlock = pBlock;
    m_dwSize = dwSize;
    return TRUE;
}

void CPEFileInfo::Close()
{
    if(m_pBlock)
    {
        m_pBlock = NULL;
        m_dwSize = 0;
        m_strVersion = _T("");
        m_strDesc = _T("");
    }
}

CString CPEFileInfo::GetVersion()
{
    if(!m_strVersion.IsEmpty())
        return m_strVersion;

    DWORD dwVersionLength = 0;
    LPCTSTR szVersion = GetDescFromFile(_T("FileVersion"), &dwVersionLength);
    if(szVersion != NULL)
    {
        CString strVersion(szVersion, dwVersionLength);
        m_strVersion = strVersion;
    }
    return m_strVersion;
}

CString CPEFileInfo::GetDesc()
{
    if(!m_strDesc.IsEmpty())
        return m_strDesc;

    DWORD dwVersionLength = 0;
    LPCTSTR szVersion = GetDescFromFile(_T("FileDescription"), &dwVersionLength);
    if(szVersion != NULL)
    {
        CString strVersion(szVersion, dwVersionLength);
        m_strDesc = strVersion;
    }
    return m_strDesc;
}

LPCTSTR CPEFileInfo::GetDescFromFile(LPCTSTR szVerName, DWORD* pdwDescLen)
{
    UINT    nSize = 0;
    TCHAR  *pVerValue = NULL;

    if(!::VerQueryValue(m_pBlock, _T("\\VarFileInfo\\Translation"), (LPVOID*)&pVerValue, &nSize))
        return NULL;

    TCHAR szSubBlock[MAX_PATH];

    _sntprintf(szSubBlock, MAX_PATH,
        _T("\\StringFileInfo\\%04x%04x\\%s"),
        *((unsigned short int *)pVerValue),
#ifdef _UNICODE
        *((unsigned short int *)&pVerValue[1]),
#else
        *((unsigned short int *)&pVerValue[2]),
#endif //_UNICODE
        szVerName
        );

    if(!::VerQueryValue(m_pBlock, szSubBlock, (LPVOID*)&pVerValue, &nSize))
        return NULL;

    *pdwDescLen = nSize;
    return pVerValue;
}

