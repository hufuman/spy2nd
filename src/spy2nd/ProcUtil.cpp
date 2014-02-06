#include "stdafx.h"
#include "ProcUtil.h"

#include "NtApiDef.h"
#include "DosDeviceToFileName.h"

namespace ProcUtil
{
#ifndef NT_SUCCESS
#define NT_SUCCESS(value) ((value) >= 0)
#endif  // NT_SUCCESS

    namespace
    {
        NT_STATUS
            NTAPI
            MyNtQueryInformationProcess(
            __in HANDLE ProcessHandle,
            __in PROCESSINFOCLASS ProcessInformationClass,
            __out PVOID ProcessInformation,
            __in ULONG ProcessInformationLength,
            __out PULONG ReturnLength
            )
        {
            static _NtQueryInformationProcess pNtQueryInformationProcess = 
                (_NtQueryInformationProcess)GetProcAddress(
                GetModuleHandle(_T("ntdll.dll")),
                "NtQueryInformationProcess"
                );

            if (!pNtQueryInformationProcess)
            {
                ATLASSERT(FALSE);
                return STATUS_UNSUCCESSFUL;
            }

            return pNtQueryInformationProcess(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
        }

        NT_STATUS
            NTAPI
            MyNtQueryInformationProcess64(
            __in HANDLE ProcessHandle,
            __in PROCESSINFOCLASS ProcessInformationClass,
            __out PVOID ProcessInformation,
            __in ULONG ProcessInformationLength,
            __out PULONG ReturnLength
            )
        {
            static _NtQueryInformationProcess pNtQueryInformationProcess = 
                (_NtQueryInformationProcess)GetProcAddress(
                GetModuleHandle(_T("ntdll.dll")),
                "NtWow64QueryInformationProcess64"
                );

            if (!pNtQueryInformationProcess)
            {
                ATLASSERT(FALSE);
                return STATUS_UNSUCCESSFUL;
            }

            return pNtQueryInformationProcess(ProcessHandle, ProcessInformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
        }

        LONG
            NTAPI
            MyNtReadVirtualMemory64(
            HANDLE ProcessHandle,
            PVOID64 BaseAddress,
            PVOID Buffer,
            UINT64 NumberOfBytesToRead,
            PUINT64 NumberOfBytesReaded
            )
        {
            typedef LONG64 (WINAPI *_NtReadVirtualMemory64)(HANDLE ProcessHandle, PVOID64 BaseAddress, PVOID Buffer, UINT64 NumberOfBytesToRead, PUINT64 NumberOfBytesReaded);
            static _NtReadVirtualMemory64 pNtReadVirtualMemory64 = 
                (_NtReadVirtualMemory64)GetProcAddress(
                GetModuleHandle(_T("ntdll.dll")),
                "NtWow64ReadVirtualMemory64"
                );

            if (!pNtReadVirtualMemory64)
            {
                ATLASSERT(FALSE);
                return STATUS_UNSUCCESSFUL;
            }

            return (LONG)pNtReadVirtualMemory64(ProcessHandle, BaseAddress, Buffer, NumberOfBytesToRead, NumberOfBytesReaded);
        }

        LPWSTR GetProcessCommandLine32(HANDLE hProc)
        {
            NTSTATUS Status = STATUS_UNSUCCESSFUL;
            PVOID pPebAddress = NULL;
            PVOID pProcessParameters = NULL;
            UNICODE_STRING CommandLine = {0};

            LPWSTR szCmdLine = NULL;

            do 
            {
                PROCESS_BASIC_INFORMATION pbi;

                __try
                {

                    Status = MyNtQueryInformationProcess(
                        hProc, 
                        ProcessBasicInformation, 
                        &pbi, 
                        sizeof(pbi), 
                        NULL
                        );
                    if (Status != STATUS_SUCCESS)
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    pPebAddress = pbi.PebBaseAddress;

                    if(!ReadProcessMemory(
                        hProc,
                        (PCHAR)pPebAddress + 
                        FIELD_OFFSET(PEB, ProcessParameters),
                        &pProcessParameters,
                        sizeof(PVOID),
                        NULL
                        ))
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    if(!ReadProcessMemory(
                        hProc,
                        (PCHAR)pProcessParameters + 
                        FIELD_OFFSET(RTL_USER_PROCESS_PARAMETERS, CommandLine),
                        &CommandLine,
                        sizeof(CommandLine),
                        NULL
                        ))
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    DWORD dwLength = CommandLine.Length * sizeof(WCHAR) + sizeof(WCHAR);
                    szCmdLine = (LPWSTR)malloc(dwLength);
                    memset(szCmdLine, 0, dwLength);
                    if(!ReadProcessMemory(
                        hProc,
                        (LPVOID)CommandLine.Buffer,
                        szCmdLine,
                        CommandLine.Length,
                        NULL
                        ))
                    {
                        free(szCmdLine);
                        szCmdLine = NULL;
                        ATLASSERT(FALSE);
                        break;
                    }

                    szCmdLine[CommandLine.Length / 2] = 0;
                }
                __except(EXCEPTION_EXECUTE_HANDLER)
                {
                    free(szCmdLine);
                    szCmdLine = NULL;

                    ATLASSERT(FALSE);
                    break;
                }

            } while (FALSE);

            return szCmdLine;
        }

        LPWSTR GetProcessCommandLine64(HANDLE hProc)
        {
            NT_STATUS Status = STATUS_UNSUCCESSFUL;
            PEB64 pPebAddress = {0};
            RTL_USER_PROCESS_PARAMETERS64 pProcessParameters = {0};
            UNICODE_STRING64 CommandLine = {0};

            LPWSTR szCmdLine = NULL;

            do 
            {
                PROCESS_BASIC_INFORMATION64 pbi;

                __try
                {
                    Status = MyNtQueryInformationProcess64(
                        hProc, 
                        ProcessBasicInformation, 
                        &pbi, 
                        sizeof(pbi), 
                        NULL
                        );
                    if (Status != STATUS_SUCCESS)
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    if(ERROR_SUCCESS != MyNtReadVirtualMemory64(
                        hProc,
                        pbi.PebBaseAddress,
                        &pPebAddress,
                        sizeof(PEB64),
                        NULL
                        ))
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    if(ERROR_SUCCESS != MyNtReadVirtualMemory64(
                        hProc,
                        (PVOID64)((ULONG64)pPebAddress.ProcessParameters + 
                        FIELD_OFFSET(RTL_USER_PROCESS_PARAMETERS64, CommandLine)),
                        &CommandLine,
                        sizeof(CommandLine),
                        NULL
                        ))
                    {
                        ATLASSERT(FALSE);
                        break;
                    }

                    DWORD dwLength = CommandLine.Length * sizeof(WCHAR) + sizeof(WCHAR);
                    szCmdLine = (LPWSTR)malloc(dwLength);
                    memset(szCmdLine, 0, dwLength);
                    if(ERROR_SUCCESS != MyNtReadVirtualMemory64(
                        hProc,
                        CommandLine.Buffer,
                        szCmdLine,
                        CommandLine.Length,
                        NULL
                        ))
                    {
                        free(szCmdLine);
                        szCmdLine = NULL;

                        ATLASSERT(FALSE);
                        break;
                    }

                    szCmdLine[CommandLine.Length / 2] = 0;
                }
                __except(EXCEPTION_EXECUTE_HANDLER)
                {
                    free(szCmdLine);
                    szCmdLine = NULL;

                    ATLASSERT(FALSE);
                    break;
                }        

            } while (FALSE);

            return szCmdLine;
        }
    }

    BOOL    IsProcElevated(HANDLE hProc)
    {
        HANDLE hToken = NULL;

        if(!::OpenProcessToken(hProc, TOKEN_QUERY, &hToken))
        {
            ATLASSERT(FALSE);
            return FALSE;
        }

        TOKEN_ELEVATION te = {0};
        DWORD dwReturnLength = 0;

        BOOL bElevated = FALSE;
        if(::GetTokenInformation(hToken, TokenElevation, &te, sizeof(te), &dwReturnLength))
        {
            ATLASSERT(dwReturnLength == sizeof( te ));
            bElevated= (te.TokenIsElevated != 0);
        }

        ::CloseHandle(hToken);
        return bElevated;
    }

    BOOL    IsProcInWow64(HANDLE hProc)
    {
        BOOL bIsWow64 = TRUE;

        typedef BOOL (WINAPI *PFN_IsWow64Process)(_In_ HANDLE, _Out_ PBOOL);
        static PFN_IsWow64Process pfnIsWow64Process = (PFN_IsWow64Process)GetProcAddress(
            GetModuleHandle(TEXT("kernel32")),
            "IsWow64Process"
            );

        if (NULL != pfnIsWow64Process)
            pfnIsWow64Process(hProc, &bIsWow64);

        return bIsWow64;
    }

    CString GetProcCommandLine(HANDLE hProc)
    {
        LPWSTR szCmdLine = NULL;
        if (IsProcInWow64(hProc))
            szCmdLine = GetProcessCommandLine32(hProc);
        else
            szCmdLine = GetProcessCommandLine64(hProc);

        CString strCmdLine;
        if(szCmdLine)
        {
            strCmdLine = szCmdLine;
            free(szCmdLine);
        }
        return strCmdLine;
    }

    DWORD GetProcParentPid(HANDLE hProc)
    {
        ULONG uRetLength = 0;
        NTSTATUS Status = 0;
        DWORD dwParentPid = -1;

        if(IsProcInWow64(hProc))
        {
            PROCESS_BASIC_INFORMATION basicInfo = {0};
            Status = MyNtQueryInformationProcess( 
                hProc, 
                ProcessBasicInformation,
                &basicInfo,
                sizeof(PROCESS_BASIC_INFORMATION),
                &uRetLength
                );
            if(NT_SUCCESS(Status))
                dwParentPid = basicInfo.InheritedFromUniqueProcessId;
        }
        else
        {
            PROCESS_BASIC_INFORMATION64 basicInfo = {0};
            Status = MyNtQueryInformationProcess64( 
                hProc, 
                ProcessBasicInformation,
                &basicInfo,
                sizeof(PROCESS_BASIC_INFORMATION64),
                &uRetLength
                );
            if(NT_SUCCESS(Status))
                dwParentPid = static_cast<DWORD>(basicInfo.InheritedFromUniqueProcessId);
        }

        return dwParentPid;
    }

    CString GetProcessImagePath(HANDLE hProc)
    {
        TCHAR szImagePath[1024];
        CString strImagePath;

        ULONG uRetLength = 0;
        NTSTATUS Status = MyNtQueryInformationProcess( 
            hProc, 
            ProcessImageFileName,
            szImagePath,
            sizeof(szImagePath),
            &uRetLength
            );
        if(NT_SUCCESS(Status))
        {
            PUNICODE_STRING pImageName = (PUNICODE_STRING)szImagePath;
            CString strTmp(pImageName->Buffer, pImageName->Length / 2);
            strImagePath = CDosDeviceToFileName::Translate(strTmp);
        }
        else if(::GetModuleFileNameEx(hProc, NULL, szImagePath, _countof(szImagePath)) > 0)
        {
            strImagePath = szImagePath;
        }

        return strImagePath;
    }

    BOOL EnablePrivilege(
        LPTSTR lpName,
        BOOL bEnable
        )
    {
        BOOL bResult = FALSE;
        HANDLE hToken = NULL;
        TOKEN_PRIVILEGES TokenPrivileges;
        TOKEN_PRIVILEGES tpPrev;
        ULONG cbPrev = sizeof(TOKEN_PRIVILEGES);

        do
        {
            bResult = OpenProcessToken(
                GetCurrentProcess(), 
                TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, 
                &hToken
                );
            if(!bResult)
            {
                ATLASSERT(FALSE);
                break;
            }

            TokenPrivileges.PrivilegeCount  = 1;
            TokenPrivileges.Privileges[0].Attributes = 0;

            bResult = LookupPrivilegeValue(
                NULL,
                lpName,
                &TokenPrivileges.Privileges[0].Luid
                );
            if(!bResult)
            {
                ATLASSERT(FALSE);
                break;
            }

            bResult = AdjustTokenPrivileges(
                hToken,
                FALSE,
                &TokenPrivileges,
                sizeof(TOKEN_PRIVILEGES),
                &tpPrev, 
                &cbPrev
                );
            if(GetLastError() != ERROR_SUCCESS || !bResult)
            {
                ATLASSERT(FALSE);
                break;
            }

            tpPrev.PrivilegeCount = 1;
            tpPrev.Privileges[0].Luid = TokenPrivileges.Privileges[0].Luid;

            if(bEnable)
            {
                tpPrev.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;
            }
            else
            {
                tpPrev.Privileges[0].Attributes &= ~SE_PRIVILEGE_ENABLED;
            }

            AdjustTokenPrivileges( 
                hToken, 
                FALSE, 
                &tpPrev, 
                cbPrev, 
                NULL, 
                NULL 
                );
            if (GetLastError() != ERROR_SUCCESS)
            {
                bResult = FALSE;
            }

        } while (0);

        CloseHandle(hToken);

        return bResult;
    }

    BOOL Execute(LPCTSTR szExePath, LPCTSTR szParam)
    {
        CString strTemp(szExePath);
        strTemp += _T("  ");
        strTemp += szParam;

        STARTUPINFO si = {sizeof(si)};
        PROCESS_INFORMATION pi = {0};
        BOOL bResult = ::CreateProcess(NULL, strTemp.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        strTemp.ReleaseBuffer();
        if(!bResult)
            return FALSE;
        ::CloseHandle(pi.hThread);
        ::CloseHandle(pi.hProcess);
        return TRUE;
    }
}
