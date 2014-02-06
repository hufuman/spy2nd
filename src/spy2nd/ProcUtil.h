#pragma once



namespace ProcUtil
{
    // TOKEN_QUERY
    BOOL    IsProcElevated(HANDLE hProc);

    // PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION
    BOOL    IsProcInWow64(HANDLE hProc);

    // PROCESS_QUERY_INFORMATION | PROCESS_VM_READ
    CString GetProcCommandLine(HANDLE hProc);

    // PROCESS_QUERY_INFORMATION | PROCESS_VM_READ
    // return -1 if error
    DWORD   GetProcParentPid(HANDLE hProc);

    // PROCESS_QUERY_INFORMATION | PROCESS_VM_READ
    CString GetProcessImagePath(HANDLE hProc);

    BOOL EnablePrivilege(LPTSTR lpName, BOOL bEnable);

    BOOL Execute(LPCTSTR szExePath, LPCTSTR szParam);

    class FsRedirection
    {
    public:
        FsRedirection()
        {
            typedef BOOL (WINAPI *PFN_Wow64DisableWow64FsRedirection)(PVOID *);

            static PFN_Wow64DisableWow64FsRedirection pfnWow64DisableWow64FsRedirection = 
                (PFN_Wow64DisableWow64FsRedirection)GetProcAddress(
                GetModuleHandle(_T("kernel32.dll")),
                "Wow64DisableWow64FsRedirection"
                );

            if(pfnWow64DisableWow64FsRedirection)
                pfnWow64DisableWow64FsRedirection(&m_Value);
        }
        ~FsRedirection()
        {
            typedef BOOL (WINAPI *PFN_Wow64RevertWow64FsRedirection)(PVOID);

            static PFN_Wow64RevertWow64FsRedirection pfnWow64RevertWow64FsRedirection = 
                (PFN_Wow64RevertWow64FsRedirection)GetProcAddress(
                GetModuleHandle(_T("kernel32.dll")),
                "Wow64RevertWow64FsRedirection"
                );

            pfnWow64RevertWow64FsRedirection(m_Value);
        }
    private:
        PVOID   m_Value;
    };
}
