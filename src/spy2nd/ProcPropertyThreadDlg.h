#pragma once


#include "WndLayout.h"
#include "ProcessInfo.h"
#include "resource.h"

#include "ProcUtil.h"

class CProcPropertyThreadDlg : public CDialogImpl<CProcPropertyThreadDlg>
{
public:
	enum { IDD = IDD_PROCPROPERTY_THREAD };

	BEGIN_MSG_MAP(CProcPropertyThreadDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
	END_MSG_MAP()

    CProcPropertyThreadDlg()
    {
        m_hBrush = ::GetSysColorBrush(COLOR_WINDOW);
    }

    LRESULT OnCtlColor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        return reinterpret_cast<LRESULT>(m_hBrush);
    }

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return TRUE;
	}

    void RefreshProperty(DWORD dwProcId, DWORD dwThreadId, HANDLE hProc)
    {
        CString strTemp;
        DWORD dwTemp = 0;

        Invalidate();
    }

    CString NumToString(ULONGLONG uData)
    {
        CString strResult;
        if(uData == 0)
            return CString(_T("0"));

        CString strTemp;
        while(uData > 0)
        {
            strTemp.Format(_T("%03u,"), uData % 1000);
            strResult = strTemp + strResult;
            uData /= 1000;
        }
        strResult.TrimLeft(_T(",0"));
        strResult.TrimRight(_T(","));
        return strResult;
    }

    CString GetFileSizeString(ULONGLONG size)
    {
        double bytes = size;
        DWORD index = 0;
        LPCTSTR szUnits[] = {_T("B"), _T("KB"), _T("MB"), _T("GB"), _T("TB"), _T("PB")};
        while(bytes >= 1024 && index < _countof(szUnits))
        {
            bytes /= 1024;
            ++ index;
        }
        CString strResult;
        strResult.Format(_T("%.2lf %s"), bytes, szUnits[index]);
        return strResult;
    }

private:
    HBRUSH  m_hBrush;
};

