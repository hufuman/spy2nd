#pragma once


#include "WndLayout.h"
#include "ProcessInfo.h"
#include "resource.h"

#include "ProcUtil.h"

class CProcPropertyCountersDlg : public CDialogImpl<CProcPropertyCountersDlg>, public IProcPropertyViewImpl<CProcPropertyCountersDlg>
{
public:
	enum { IDD = IDD_PROCPROPERTY_COUNTERS };

	BEGIN_MSG_MAP(CProcPropertyCountersDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(WM_CTLCOLOREDIT,    OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORSTATIC,  OnCtlColor)
        MESSAGE_HANDLER(WM_CTLCOLORDLG,     OnCtlColor)
	END_MSG_MAP()

    CProcPropertyCountersDlg()
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

    // IProcPropertyView
    void RefreshPropertyImpl()
    {
        CString strTemp;
        DWORD dwTemp = 0;

        // Gdi Objects
        strTemp.Format(_T("%u"), ::GetGuiResources(m_hProc, GR_GDIOBJECTS));
        SetDlgItemText(IDC_LABEL_GDI, strTemp);

        // User Objects
        strTemp.Format(_T("%u"), ::GetGuiResources(m_hProc, GR_USEROBJECTS));
        SetDlgItemText(IDC_LABEL_USER, strTemp);

        // IO Counters
        IO_COUNTERS ioCounters = {0};
        ::GetProcessIoCounters(m_hProc, &ioCounters);
        SetDlgItemText(IDC_LABEL_READ_TIMES, NumToString(ioCounters.ReadOperationCount));
        SetDlgItemText(IDC_LABEL_WRITE_TIMES, NumToString(ioCounters.WriteOperationCount));
        SetDlgItemText(IDC_LABEL_OTHER_TIMES, NumToString(ioCounters.OtherOperationCount));

        SetDlgItemText(IDC_LABEL_READ_BYTES, GetFileSizeString(ioCounters.ReadTransferCount));
        SetDlgItemText(IDC_LABEL_WRITE_BYTES, GetFileSizeString(ioCounters.WriteTransferCount));
        SetDlgItemText(IDC_LABEL_OTHER_BYTES, GetFileSizeString(ioCounters.OtherTransferCount));

        // Memory
        PROCESS_MEMORY_COUNTERS procMem = {sizeof(procMem)};
        ::GetProcessMemoryInfo(m_hProc, &procMem, sizeof(procMem));
        SetDlgItemText(IDC_LABEL_WORKING_SET, GetFileSizeString(procMem.WorkingSetSize));
        SetDlgItemText(IDC_LABEL_PEEK_WORKING_SET, GetFileSizeString(procMem.PeakWorkingSetSize));
        SetDlgItemText(IDC_LABEL_PAGEFILE, GetFileSizeString(procMem.PagefileUsage));
        SetDlgItemText(IDC_LABEL_PEEK_PAGEFILE, GetFileSizeString(procMem.PeakPagefileUsage));

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
        double bytes = (double)size;
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

