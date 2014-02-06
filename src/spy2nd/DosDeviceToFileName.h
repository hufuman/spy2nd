#pragma once

class CDosDeviceToFileName
{
    CDosDeviceToFileName(void);
public:
    ~CDosDeviceToFileName(void);

    static CString Translate(LPCTSTR szDosDevicePath);

private:
    CString TranslateImpl(LPCTSTR szDosDevicePath);
    void Init();

private:
    typedef ATL::CSimpleMap<CString, CString> StringMap;
    StringMap   m_StringMap;
};
