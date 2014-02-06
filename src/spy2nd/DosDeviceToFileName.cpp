#include "StdAfx.h"
#include "DosDeviceToFileName.h"

CDosDeviceToFileName::CDosDeviceToFileName(void)
{
    Init();
}

CDosDeviceToFileName::~CDosDeviceToFileName(void)
{
}

CString CDosDeviceToFileName::Translate(LPCTSTR szDosDevicePath)
{
    static CDosDeviceToFileName inst;
    return inst.TranslateImpl(szDosDevicePath);
}

CString CDosDeviceToFileName::TranslateImpl(LPCTSTR szDosDevicePath)
{
    CString strDosDevicePath(szDosDevicePath);
    CString strName, strTemp;
    int nSize = m_StringMap.GetSize();
    for(int i=0; i<nSize; ++ i)
    {
        CString& strDeviceName = m_StringMap.GetKeyAt(i);
        CString& strDriveName = m_StringMap.GetValueAt(i);

        if(strDeviceName.GetLength() > strDosDevicePath.GetLength())
            continue;

        strTemp = strDosDevicePath.Mid(0, strDeviceName.GetLength());
        if(strTemp.CompareNoCase(strDeviceName) == 0)
        {
            strName = strDriveName;
            strName += strDosDevicePath.Mid(strDeviceName.GetLength());
            break;
        }
    }
    return strName;
}

void CDosDeviceToFileName::Init()
{
    TCHAR szTemp[512];
    if(!::GetLogicalDriveStrings(_countof(szTemp) - 1, szTemp))
        return;

    TCHAR szName[MAX_PATH];
    TCHAR szDevice[3] = _T(" :");
    BOOL bFound = FALSE;
    TCHAR* p = szTemp;

    do 
    {
        *szDevice = *p;

        if(::QueryDosDevice(szDevice, szName, MAX_PATH))
        {
            m_StringMap.Add(szName, szDevice);
        }

        while(*p++);

    } while (*p);
}
