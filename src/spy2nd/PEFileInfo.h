#pragma once

class CPEFileInfo
{
public:
    CPEFileInfo(void);
    ~CPEFileInfo(void);

    BOOL Open(LPCTSTR szImagePath);
    void Close();

    CString GetVersion();
    CString GetDesc();

private:
    LPCTSTR GetDescFromFile(LPCTSTR szVerName, DWORD* pdwDescLen);

private:
    LPVOID  m_pBlock;
    DWORD   m_dwSize;

    CString m_strVersion;
    CString m_strDesc;
};
