/*++

Module Name:

    NtApiDef.h

Abstract:

    Common structures and functions declaration.


Revision History:

    --------    --------    ----------------------------------------------
    gz1X        2010.4      Create

Notes:

--*/

#ifndef _DMBASE_NTAPIDEF_H
#define _DMBASE_NTAPIDEF_H

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _KERNEL_IN
    #include <stdarg.h>
    #include <winbase.h>
    #include <windef.h>
#else
    #include <ntifs.h>
    #include <ntddk.h>    
#endif

//#pragma pack(push,4)

typedef double DOUBLE;
typedef LONG KPRIORITY;
typedef PVOID PLANGID;

typedef LONG KAI_STATUS;

typedef __success(return >= 0) LONG NT_STATUS;

//////////////////////////////////////////////////////////////////////////

#define Ulong64ToULong(h) ((ULONG)(ULONG_PTR)(h))
#define UlongToULong64(h) ((ULONG_PTR)(ULONG)(h))

//////////////////////////////////////////////////////////////////////////

#ifndef NtCurrentProcess
#define NtCurrentProcess() (ULongToHandle(0xFFFFFFFF))
#endif /* NtCurrentProcess */
#ifndef NtCurrentThread
#define NtCurrentThread() (ULongToHandle(0xFFFFFFFE))
#endif /* NtCurrentThread */

#ifndef DECL_IMPORT
#define DECL_IMPORT __declspec(dllimport)
#endif

#ifndef NTOSAPI
#define NTOSAPI DECL_IMPORT
#endif
#define DECLARE_INTERNAL_OBJECT(x) struct _##x; typedef struct _##x *P##x;
#define DECLARE_INTERNAL_OBJECT2(x,y) struct _##x; typedef struct _##x *P##y;

//////////////////////////////////////////////////////////////////////////

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifndef NOTHING
#define NOTHING
#endif

#ifndef CRITICAL
#define CRITICAL
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifndef MAX_NAME
#define MAX_NAME 64
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef __INTERFACE_NO_DERIVED 
#define __INTERFACE_NO_DERIVED // 外部接口，不允许重载
#endif

#ifndef __INTERFACE_DERIVED 
#define __INTERFACE_DERIVED // 外部接口，必须重载
#endif

#ifndef __SINGLE_THREAD
#define __SINGLE_THREAD // 只允许单线程操作
#endif

#ifndef __INVOKE_MUST // 接口调用次序等级，最高等级
#define __INVOKE_MUST // 必须调用, 只有调用了此接口，才可以调用其他的接口
#endif

#ifndef __INVOKE_1 // 接口调用次序等级，1等级
#define __INVOKE_1 // 只有调用了此等级的接口，才可以调用次一级的接口
#endif

#ifndef __INVOKE_2 // 接口调用次序等级，2等级
#define __INVOKE_2
#endif

#ifndef __INVOKE_3 // 接口调用次序等级，3等级
#define __INVOKE_3
#endif

#ifndef __INVOKE_4 // 接口调用次序等级，4等级
#define __INVOKE_4
#endif

#ifndef __INVOKE_NA // 接口调用次序等级，未分级，随时可以调用
#define __INVOKE_NA
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef __NameSpace_Begin
#define __NameSpace_Begin(_X_) namespace _X_ {
#endif

#ifndef __NameSpace_End
#define __NameSpace_End(_X_) };
#endif

#ifndef __NameSpace_Use
#define __NameSpace_Use(_X_) using namespace _X_;
#endif

#ifndef __DeclareNS_Use
#define __DeclareNS_Use(_X_) using _X_;
#endif

#ifndef __AnonymousNS_Begin
#define __AnonymousNS_Begin() namespace {
#endif

#ifndef __AnonymousNS_End
#define __AnonymousNS_End() };
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef NT_SUCCESS
#define NT_SUCCESS(_Status_) (((NT_STATUS)(_Status_)) >= 0)
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NT_STATUS)0)
#endif

#ifndef STATUS_NO_ALERT
#define STATUS_NO_ALERT ((NT_STATUS)0x80070000)
#endif

#ifndef STATUS_UNSUCCESSFUL
#define STATUS_UNSUCCESSFUL ((NT_STATUS)0xC0000001L)
#endif

#ifndef STATUS_NOT_IMPLEMENTED
#define STATUS_NOT_IMPLEMENTED ((NT_STATUS)0xC0000002L)
#endif

#ifndef STATUS_INFO_LENGTH_MISMATCH
#define STATUS_INFO_LENGTH_MISMATCH ((NT_STATUS)0xC0000004L)
#endif

#ifndef STATUS_BUFFER_OVERFLOW
#define STATUS_BUFFER_OVERFLOW ((NT_STATUS)0x80000005L)
#endif

#ifndef STATUS_BUFFER_TOO_SMALL
#define STATUS_BUFFER_TOO_SMALL ((NT_STATUS)0xC0000023L)
#endif

#ifndef STATUS_CANT_TERMINATE_SELF
#define STATUS_CANT_TERMINATE_SELF ((NT_STATUS)0xC00000DBL)
#endif

#ifndef STATUS_PROCESS_IS_TERMINATING
#define STATUS_PROCESS_IS_TERMINATING ((NT_STATUS)0xC000010AL)
#endif

#ifndef STATUS_INSUFFICIENT_RESOURCES
#define STATUS_INSUFFICIENT_RESOURCES ((NT_STATUS)0xC000009AL) 
#endif

#ifndef STATUS_INVALID_PARAMETER
#define STATUS_INVALID_PARAMETER ((NT_STATUS)0xC000000DL)
#endif

#ifndef STATUS_NO_SUCH_DEVICE
#define STATUS_NO_SUCH_DEVICE ((NT_STATUS)0xC000000EL)
#endif

#ifndef STATUS_NO_SUCH_FILE
#define STATUS_NO_SUCH_FILE ((NT_STATUS)0xC000000FL)
#endif

#ifndef STATUS_INVALID_DEVICE_REQUEST
#define STATUS_INVALID_DEVICE_REQUEST ((NTSTATUS)0xC0000010L)
#endif

#ifndef STATUS_ALREADY_COMMITTED
#define STATUS_ALREADY_COMMITTED ((NTSTATUS)0xC0000021L)
#endif

#ifndef STATUS_OBJECT_NAME_NOT_FOUND
#define STATUS_OBJECT_NAME_NOT_FOUND ((NT_STATUS)0xC0000034L)
#endif

#ifndef STATUS_OBJECT_PATH_NOT_FOUND
#define STATUS_OBJECT_PATH_NOT_FOUND ((NT_STATUS)0xC000003AL)
#endif

#ifndef STATUS_CONNECTION_INVALID
#define STATUS_CONNECTION_INVALID ((NT_STATUS)0xC000023AL)
#endif

#ifndef STATUS_NOT_FOUND
#define STATUS_NOT_FOUND ((NT_STATUS)0xC0000225L)
#endif

#ifndef STATUS_CRC_ERROR
#define STATUS_CRC_ERROR ((NT_STATUS)0xC000003FL)
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef STATUS_ALREADY_EXISTED
#define STATUS_ALREADY_EXISTED ((NT_STATUS)0xFEB0E001L)
#endif

#ifndef STATUS_ALREADY_COMPLETE
#define STATUS_ALREADY_COMPLETE ((NT_STATUS)0xFEB0E002L)
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef KCB_SUCCESS
#define KCB_SUCCESS(_Status_) (((NT_STATUS)(_Status_)) >= KCB_STATUS_SUCCESS)
#endif

#ifndef KCB_STATUS_ERROR
#define KCB_STATUS_ERROR ((NT_STATUS)0xFEC01001L)
#endif

#ifndef KCB_STATUS_SUCCESS
#define KCB_STATUS_SUCCESS ((NT_STATUS)0xFED00001L)
#endif

#ifndef KCB_STATUS_CONTINUE
#define KCB_STATUS_CONTINUE ((NT_STATUS)0xFED00002L)
#endif

//////////////////////////////////////////////////////////////////////////

#define ABS_TIME(Time) (Time)
#define RAV_TIME(Time) (-(Time))

#define DIV_TIME(Time) (Time)/(10 * 1000)

#define NANOSECONDS(Time) (((signed __int64)(Time)) / 100L)
#define MICROSECONDS(Time) (((signed __int64)(Time)) * NANOSECONDS(1000L))
#define MILLISECONDS(Time) (((signed __int64)(Time)) * MICROSECONDS(1000L))
#define SECONDS(Time) (((signed __int64)(Time)) * MILLISECONDS(1000L))

#ifndef _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifndef getTableIndexbyField
#define getTableIndexbyField(_Table_, _Field_, _Value_, _outIndex_) \
{ \
    ULONG _i_ = 0; \
    \
    for (_i_ = 0; _i_ < _countof(_Table_); _i_ ++) \
    { \
        if (_Table_[_i_]._Field_ == _Value_) \
        { \
            break; \
        } \
    } \
    if (_i_ != _countof(_Table_)) \
    { \
        _outIndex_ = _i_; \
    } \
}
#endif

//////////////////////////////////////////////////////////////////////////

#ifndef _KERNEL_IN

#define FACILITY_NTWIN32 0x7
#define ERROR_SEVERITY_ERROR 0xC0000000

#ifndef __NTSTATUS_FROM_WIN32
#define __NTSTATUS_FROM_WIN32(x) \
    ((LONG)(x) <= 0 ? ((LONG)(x)) : ((LONG) (((x) & 0x0000FFFF) | (FACILITY_NTWIN32 << 16) | ERROR_SEVERITY_ERROR)))
#endif // __NTSTATUS_FROM_WIN32

#define NTSTATUS_FROM_WIN32(x) __NTSTATUS_FROM_WIN32(x)

#if defined(_AMD64_)
#define PAGE_SIZE 0x1000
#endif

#if defined(_X86_)
#define PAGE_SIZE 0x1000
#endif

#if defined(_IA64_)
#define PAGE_SIZE 0x2000
#endif

#endif

//////////////////////////////////////////////////////////////////////////

// Valid values for the Attributes field
//

#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_FORCE_ACCESS_CHECK  0x00000400L
#define OBJ_VALID_ATTRIBUTES    0x000007F2L

#define FOREGROUND_BASE_PRIORITY  9
#define NORMAL_BASE_PRIORITY      8

#define DELAYED_WORK_QUEUE_PRIORITY         (12 - NORMAL_BASE_PRIORITY)
#define CRITICAL_WORK_QUEUE_PRIORITY        (13 - NORMAL_BASE_PRIORITY)
#define HYPER_CRITICAL_WORK_QUEUE_PRIORITY  (15 - NORMAL_BASE_PRIORITY)

//////////////////////////////////////////////////////////////////////////

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

//////////////////////////////////////////////////////////////////////////

#ifdef _WIN64

#define ObpInterlockedExchange InterlockedExchange64
#define ObpInterlockedExchangeAdd InterlockedExchangeAdd64
#define ObpInterlockedIncrement InterlockedIncrement64
#define ObpInterlockedDecrement InterlockedDecrement64
#define ObpInterlockedCompareExchange InterlockedCompareExchange64
#define ObpInterlockedOr InterlockedOr64
#define ObpInterlockedAnd InterlockedAnd64

#else 

#define ObpInterlockedExchange InterlockedExchange
#define ObpInterlockedExchangeAdd InterlockedExchangeAdd
#define ObpInterlockedIncrement InterlockedIncrement
#define ObpInterlockedDecrement InterlockedDecrement
#define ObpInterlockedCompareExchange InterlockedCompareExchange
#define ObpInterlockedOr InterlockedOr
#define ObpInterlockedAnd InterlockedAnd

#endif

//////////////////////////////////////////////////////////////////////////

#define KAI_SET_VALUE(PFlags, Flag) \
    ObpInterlockedExchange((PLONG_PTR)PFlags, (LONG_PTR)Flag)

#define KAI_SET_VALUE32(PFlags, Flag) \
    InterlockedExchange((PLONG)PFlags, (LONG)Flag)

#define KAI_SET_VALUE64(PFlags, Flag) \
    InterlockedExchange64((PLONGLONG)PFlags, (LONGLONG)Flag)

#define KAI_SET_BITS(PFlags, Flag) \
    ObpInterlockedOr((PLONG_PTR)(PFlags), Flag)

#define KAI_MASK_BITS(PFlags, Flag) \
    ObpInterlockedAnd((PLONG_PTR)PFlags, Flag)

#define KAI_CLEAR_BITS(PFlags, Flag) \
    ObpInterlockedAnd((PLONG_PTR)PFlags, ~(Flag))

#define KAI_TEST_BITS(Flags, Bits) \
    ((Flags & (Bits)) == (Bits))

#define KAI_REF_VALUE(PFlags) \
    ObpInterlockedIncrement((PLONG_PTR)PFlags)

#define KAI_REF_VALUE32(PFlags) \
    InterlockedIncrement((PLONG_PTR)PFlags)

#define KAI_REF_VALUE64(PFlags) \
    InterlockedIncrement64((PLONGLONG)PFlags)

#define KAI_DEREF_VALUE(PFlags) \
    ObpInterlockedDecrement((PLONG_PTR)PFlags)

#define KAI_DEREF_VALUE32(PFlags) \
    InterlockedDecrement((PLONG_PTR)PFlags)

#define KAI_DEREF_VALUE64(PFlags) \
    InterlockedDecrement64((PLONGLONG)PFlags)

#define KAI_EXCHANGE_VALUE(PFlags, Flag, Comprand) \
    ObpInterlockedCompareExchange((PLONG_PTR)PFlags, (LONG_PTR)Flag, (LONG_PTR)Comprand)

#define KAI_EXCHANGE_VALUE32(PFlags, Flag, Comprand) \
    InterlockedCompareExchange((PLONG)PFlags, (LONG)Flag, (LONG)Comprand)

#define KAI_EXCHANGE_VALUE64(PFlags, Flag, Comprand) \
    InterlockedCompareExchange64((PLONGLONG)PFlags, (LONGLONG)Flag, (LONGLONG)Comprand)

//////////////////////////////////////////////////////////////////////////

#ifndef _KERNEL_IN

FORCEINLINE
VOID
InitializeListHead(
    __out PLIST_ENTRY ListHead
    )
{
    ListHead->Flink = ListHead->Blink = ListHead;
}

BOOLEAN
FORCEINLINE
IsListEmpty(
    __in const LIST_ENTRY * ListHead
    )
{
    return (BOOLEAN)(ListHead->Flink == ListHead);
}

FORCEINLINE
BOOLEAN
RemoveEntryList(
    __in PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;
    return (BOOLEAN)(Flink == Blink);
}

FORCEINLINE
PLIST_ENTRY
RemoveHeadList(
    __in __out PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Flink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;
    return Entry;
}

FORCEINLINE
PLIST_ENTRY
RemoveTailList(
    __in __out PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Entry;

    Entry = ListHead->Blink;
    Blink = Entry->Blink;
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;
    return Entry;
}

FORCEINLINE
VOID
InsertTailList(
    __in __out PLIST_ENTRY ListHead,
    __in __out PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;

    Blink = ListHead->Blink;
    Entry->Flink = ListHead;
    Entry->Blink = Blink;
    Blink->Flink = Entry;
    ListHead->Blink = Entry;
}

FORCEINLINE
VOID
InsertHeadList(
    __in __out PLIST_ENTRY ListHead,
    __in __out PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Flink;

    Flink = ListHead->Flink;
    Entry->Flink = Flink;
    Entry->Blink = ListHead;
    Flink->Blink = Entry;
    ListHead->Flink = Entry;
}

FORCEINLINE
VOID
AppendTailList(
    __in __out PLIST_ENTRY ListHead,
    __in __out PLIST_ENTRY ListToAppend
    )
{
    PLIST_ENTRY ListEnd = ListHead->Blink;

    ListHead->Blink->Flink = ListToAppend;
    ListHead->Blink = ListToAppend->Blink;
    ListToAppend->Blink->Flink = ListHead;
    ListToAppend->Blink = ListEnd;
}

//////////////////////////////////////////////////////////////////////////

typedef struct _CLIENT_ID
{
    HANDLE UniqueProcess;
    HANDLE UniqueThread;

}CLIENT_ID, *PCLIENT_ID;

typedef enum _KWAIT_REASON 
{
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    WrKeyedEvent,
    WrTerminated,
    WrProcessInSwap,
    WrCpuRateControl,
    WrCalloutStack,
    WrKernel,
    WrResource,
    WrPushLock,
    WrMutex,
    WrQuantumEnd,
    WrDispatchInt,
    WrPreempted,
    WrYieldExecution,
    WrFastMutex,
    WrGuardedMutex,
    WrRundown,
    MaximumWaitReason

} KWAIT_REASON;


typedef struct _STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PCHAR Buffer;

} STRING;

typedef STRING *PSTRING;

typedef STRING ANSI_STRING;
typedef PSTRING PANSI_STRING;
typedef PSTRING PCANSI_STRING;

typedef STRING OEM_STRING;
typedef PSTRING POEM_STRING;
typedef CONST STRING* PCOEM_STRING;
typedef CONST char *PCSZ;

typedef struct _WSTRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWCHAR Buffer;

} WSTRING;

typedef WSTRING *PWSTRING;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;

} UNICODE_STRING;

typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _UNICODE_STRING64 
{
    SHORT Length;
    SHORT MaximumLength;
    ULONG Fill;
    PVOID64 Buffer;

} UNICODE_STRING64;

typedef UNICODE_STRING64 *PUNICODE_STRING64;

typedef enum _POOL_TYPE 
{
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PagedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS,
    MaxPoolType,
    NonPagedPoolSession = 32,
    PagedPoolSession,
    NonPagedPoolMustSucceedSession,
    DontUseThisTypeSession,
    NonPagedPoolCacheAlignedSession,
    PagedPoolCacheAlignedSession,
    NonPagedPoolCacheAlignedMustSSession

} POOL_TYPE;

typedef struct _OBJECT_ATTRIBUTES 
{
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;

} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

#define InitializeObjectAttributes( p, n, a, r, s ) \
{ \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES ); \
    (p)->RootDirectory = r; \
    (p)->Attributes = a; \
    (p)->ObjectName = n; \
    (p)->SecurityDescriptor = s; \
    (p)->SecurityQualityOfService = NULL; \
}

typedef struct _FILE_NETWORK_OPEN_INFORMATION 
{ 
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime; 
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile; 
    ULONG FileAttributes;     

} FILE_NETWORK_OPEN_INFORMATION, *PFILE_NETWORK_OPEN_INFORMATION; 

typedef struct _IO_STATUS_BLOCK 
{
    union 
    {
        ULONG Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;

} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PKNORMAL_ROUTINE)(
  __in PVOID  NormalContext,
  __in PVOID  SystemArgument1,
  __in PVOID  SystemArgument2);

// Process Information Classes
//

typedef enum _PROCESSINFOCLASS {
    ProcessBasicInformation,
    ProcessQuotaLimits,
    ProcessIoCounters,
    ProcessVmCounters,
    ProcessTimes,
    ProcessBasePriority,
    ProcessRaisePriority,
    ProcessDebugPort,
    ProcessExceptionPort,
    ProcessAccessToken,
    ProcessLdtInformation,
    ProcessLdtSize,
    ProcessDefaultHardErrorMode,
    ProcessIoPortHandlers,          // Note: this is kernel mode only
    ProcessPooledUsageAndLimits,
    ProcessWorkingSetWatch,
    ProcessUserModeIOPL,
    ProcessEnableAlignmentFaultFixup,
    ProcessPriorityClass,
    ProcessWx86Information,
    ProcessHandleCount,
    ProcessAffinityMask,
    ProcessPriorityBoost,
    ProcessDeviceMap,
    ProcessSessionInformation,
    ProcessForegroundInformation,
    ProcessWow64Information,
    ProcessImageFileName,
    ProcessLUIDDeviceMapsEnabled,
    ProcessBreakOnTermination,
    ProcessDebugObjectHandle,
    ProcessDebugFlags,
    ProcessHandleTracing,
    ProcessIoPriority,      // The followings -> Vista or later
    ProcessExecuteFlags,
    ProcessTlsInformation,
    ProcessCookie,
    ProcessImageInformation,
    ProcessCycleTime,
    ProcessPagePriority,
    ProcessInstrumentationCallback,
    ProcessThreadStackAllocation,
    ProcessWorkingSetWatchEx,
    ProcessImageFileNameWin32,
    ProcessImageFileMapping,
    ProcessAffinityUpdateMode,
    ProcessMemoryAllocationMode,
    ProcessGroupInformation,
    ProcessTokenVirtualizationEnabled,
    ProcessConsoleHostProcess,
    ProcessWindowInformation,
    MaxProcessInfoClass             // MaxProcessInfoClass should always be the last enum
} PROCESSINFOCLASS;

//
// Thread Information Classes
//

typedef enum _THREADINFOCLASS {
    ThreadBasicInformation,
    ThreadTimes,
    ThreadPriority,
    ThreadBasePriority,
    ThreadAffinityMask,
    ThreadImpersonationToken,
    ThreadDescriptorTableEntry,
    ThreadEnableAlignmentFaultFixup,
    ThreadEventPair_Reusable,
    ThreadQuerySetWin32StartAddress,
    ThreadZeroTlsCell,
    ThreadPerformanceCount,
    ThreadAmILastThread,
    ThreadIdealProcessor,
    ThreadPriorityBoost,
    ThreadSetTlsArrayAddress,   // Obsolete
    ThreadIsIoPending,
    ThreadHideFromDebugger,
    ThreadBreakOnTermination,
    ThreadSwitchLegacyState,
    ThreadIsTerminated,
    ThreadLastSystemCall,
    ThreadIoPriority,
    ThreadCycleTime,
    ThreadPagePriority,
    ThreadActualBasePriority,
    ThreadTebInformation,
    ThreadCSwitchMon,          // Obsolete
    ThreadCSwitchPmu,
    ThreadWow64Context,
    ThreadGroupInformation,
    ThreadUmsInformation,      // UMS
    ThreadCounterProfiling,
    ThreadIdealProcessorEx,
    MaxThreadInfoClass
} THREADINFOCLASS;

typedef enum _KPROFILE_SOURCE
{
    ProfileTime,
    ProfileAlignmentFixup,
    ProfileTotalIssues,
    ProfilePipelineDry,
    ProfileLoadInstructions,
    ProfilePipelineFrozen,
    ProfileBranchInstructions,
    ProfileTotalNonissues,
    ProfileDcacheMisses,
    ProfileIcacheMisses,
    ProfileCacheMisses,
    ProfileBranchMispredictions,
    ProfileStoreInstructions,
    ProfileFpInstructions,
    ProfileIntegerInstructions,
    Profile2Issue,
    Profile3Issue,
    Profile4Issue,
    ProfileSpecialInstructions,
    ProfileTotalCycles,
    ProfileIcacheIssues,
    ProfileDcacheAccesses,
    ProfileMemoryBarrierCycles,
    ProfileLoadLinkedIssues,
    ProfileMaximum

} KPROFILE_SOURCE;

typedef 
VOID 
(NTAPI *PIO_APC_ROUTINE)(
    __in PVOID ApcContext,
    __in PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG Reserved
    );

typedef struct _KEY_VALUE_ENTRY 
{
    PUNICODE_STRING ValueName;
    ULONG           DataLength;
    ULONG           DataOffset;
    ULONG           Type;

} KEY_VALUE_ENTRY, *PKEY_VALUE_ENTRY;

#define PROCESS_PRIORITY_SEPARATION_MASK    0x00000003
#define PROCESS_PRIORITY_SEPARATION_MAX     0x00000002
#define PROCESS_QUANTUM_VARIABLE_MASK       0x0000000c
#define PROCESS_QUANTUM_VARIABLE_DEF        0x00000000
#define PROCESS_QUANTUM_VARIABLE_VALUE      0x00000004
#define PROCESS_QUANTUM_FIXED_VALUE         0x00000008
#define PROCESS_QUANTUM_LONG_MASK           0x00000030
#define PROCESS_QUANTUM_LONG_DEF            0x00000000
#define PROCESS_QUANTUM_LONG_VALUE          0x00000010
#define PROCESS_QUANTUM_SHORT_VALUE         0x00000020

#define PROCESS_HARDERROR_ALIGNMENT_BIT 0x0004
#if defined(_AMD64_)
#define PROCESS_HARDERROR_DEFAULT (1 | PROCESS_HARDERROR_ALIGNMENT_BIT)
#else
#define PROCESS_HARDERROR_DEFAULT 1
#endif


// Process Information Structures
//

// PageFaultHistory Information
//  NtQueryInformationProcess using ProcessWorkingSetWatch
//
typedef 
struct _PROCESS_WS_WATCH_INFORMATION 
{
    PVOID FaultingPc;
    PVOID FaultingVa;

} PROCESS_WS_WATCH_INFORMATION, *PPROCESS_WS_WATCH_INFORMATION;

// Basic Process Information
//  NtQueryInformationProcess using ProcessBasicInfo
//
typedef
struct _PROCESS_BASIC_INFORMATION 
{
    NT_STATUS ExitStatus;
    PVOID PebBaseAddress;
    ULONG_PTR AffinityMask;
    KPRIORITY BasePriority;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION;

typedef PROCESS_BASIC_INFORMATION *PPROCESS_BASIC_INFORMATION;

typedef 
struct _PROCESS_BASIC_INFORMATION64 
{
    NT_STATUS ExitStatus;
    ULONG32 Pad1;
    PVOID64 PebBaseAddress;
    ULONG64 AffinityMask;
    KPRIORITY BasePriority;
    ULONG32 Pad2;
    ULONG64 UniqueProcessId;
    ULONG64 InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION64;

typedef PROCESS_BASIC_INFORMATION64 *PPROCESS_BASIC_INFORMATION64;

#if !defined(SORTPP_PASS) && !defined(MIDL_PASS) && !defined(RC_INVOKED) && defined(_WIN64) && !defined(_X86AMD64_)
C_ASSERT(sizeof(PROCESS_BASIC_INFORMATION) == sizeof(PROCESS_BASIC_INFORMATION64));
#endif

// begin_ntddk begin_ntifs

// Process Device Map information
//  NtQueryInformationProcess using ProcessDeviceMap
//  NtSetInformationProcess using ProcessDeviceMap
//

typedef
struct _PROCESS_DEVICEMAP_INFORMATION 
{
    union {
        struct {
            HANDLE DirectoryHandle;
        } Set;
        struct {
            ULONG DriveMap;
            UCHAR DriveType[ 32 ];
        } Query;
    };

} PROCESS_DEVICEMAP_INFORMATION, *PPROCESS_DEVICEMAP_INFORMATION;

typedef
struct _PROCESS_DEVICEMAP_INFORMATION_EX
{
    union {
        struct {
            HANDLE DirectoryHandle;
        } Set;
        struct {
            ULONG DriveMap;
            UCHAR DriveType[ 32 ];
        } Query;
    };
    ULONG Flags;    // specifies that the query type

} PROCESS_DEVICEMAP_INFORMATION_EX, *PPROCESS_DEVICEMAP_INFORMATION_EX;

// PROCESS_DEVICEMAP_INFORMATION_EX flags
//
#define PROCESS_LUID_DOSDEVICES_ONLY 0x00000001

// Multi-User Session specific Process Information
//  NtQueryInformationProcess using ProcessSessionInformation
//

typedef 
struct _PROCESS_SESSION_INFORMATION 
{
    ULONG SessionId;

} PROCESS_SESSION_INFORMATION, *PPROCESS_SESSION_INFORMATION;


typedef 
struct _PROCESS_HANDLE_TRACING_ENABLE 
{
    ULONG Flags;

} PROCESS_HANDLE_TRACING_ENABLE, *PPROCESS_HANDLE_TRACING_ENABLE;

typedef 
struct _PROCESS_HANDLE_TRACING_ENABLE_EX 
{
    ULONG Flags;
    ULONG TotalSlots;
} PROCESS_HANDLE_TRACING_ENABLE_EX, *PPROCESS_HANDLE_TRACING_ENABLE_EX;


#define PROCESS_HANDLE_TRACING_MAX_STACKS 16

typedef 
struct _PROCESS_HANDLE_TRACING_ENTRY 
{
    HANDLE Handle;
    CLIENT_ID ClientId;
    ULONG Type;
    PVOID Stacks[PROCESS_HANDLE_TRACING_MAX_STACKS];

} PROCESS_HANDLE_TRACING_ENTRY, *PPROCESS_HANDLE_TRACING_ENTRY;

typedef struct _PROCESS_HANDLE_TRACING_QUERY 
{
    HANDLE Handle;
    ULONG  TotalTraces;
    PROCESS_HANDLE_TRACING_ENTRY HandleTrace[1];

} PROCESS_HANDLE_TRACING_QUERY, *PPROCESS_HANDLE_TRACING_QUERY;

// Process Virtual Memory Counters
//  NtQueryInformationProcess using ProcessVmCounters
//

typedef 
struct _VM_COUNTERS 
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;

} VM_COUNTERS;

typedef VM_COUNTERS *PVM_COUNTERS;

typedef 
struct _VM_COUNTERS_EX 
{
    SIZE_T PeakVirtualSize;
    SIZE_T VirtualSize;
    ULONG PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivateUsage;

} VM_COUNTERS_EX;

typedef VM_COUNTERS_EX *PVM_COUNTERS_EX;

// Process Pooled Quota Usage and Limits
//  NtQueryInformationProcess using ProcessPooledUsageAndLimits
//

typedef
struct _POOLED_USAGE_AND_LIMITS
{
    SIZE_T PeakPagedPoolUsage;
    SIZE_T PagedPoolUsage;
    SIZE_T PagedPoolLimit;
    SIZE_T PeakNonPagedPoolUsage;
    SIZE_T NonPagedPoolUsage;
    SIZE_T NonPagedPoolLimit;
    SIZE_T PeakPagefileUsage;
    SIZE_T PagefileUsage;
    SIZE_T PagefileLimit;

} POOLED_USAGE_AND_LIMITS;

typedef POOLED_USAGE_AND_LIMITS *PPOOLED_USAGE_AND_LIMITS;

// Process Security Context Information
//  NtSetInformationProcess using ProcessAccessToken
// PROCESS_SET_ACCESS_TOKEN access to the process is needed
// to use this info level.
//

typedef
struct _PROCESS_ACCESS_TOKEN 
{
    // Handle to Primary token to assign to the process.
    // TOKEN_ASSIGN_PRIMARY access to this token is needed.
    //
    HANDLE Token;

    // Handle to the initial thread of the process.
    // A process's access token can only be changed if the process has
    // no threads or one thread.  If the process has no threads, this
    // field must be set to NULL.  Otherwise, it must contain a handle
    // open to the process's only thread.  THREAD_QUERY_INFORMATION access
    // is needed via this handle.

    HANDLE Thread;

} PROCESS_ACCESS_TOKEN, *PPROCESS_ACCESS_TOKEN;

// Process/Thread System and User Time
//  NtQueryInformationProcess using ProcessTimes
//  NtQueryInformationThread using ThreadTimes
//
typedef 
struct _KERNEL_USER_TIMES 
{
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER ExitTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;

} KERNEL_USER_TIMES;

typedef KERNEL_USER_TIMES *PKERNEL_USER_TIMES;


// Thread Information Structures
//

//
// Basic Thread Information
//  NtQueryInformationThread using ThreadBasicInfo
//

typedef 
struct _THREAD_BASIC_INFORMATION 
{
    NT_STATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    ULONG_PTR AffinityMask;
    KPRIORITY Priority;
    LONG BasePriority;

} THREAD_BASIC_INFORMATION;

typedef THREAD_BASIC_INFORMATION *PTHREAD_BASIC_INFORMATION;

//////////////////////////////////////////////////////////////////////////

// Object Information Types for NtQueryInformationObject
//
typedef struct _OBJECT_NAME_INFORMATION
{
    UNICODE_STRING Name;

} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef enum _INTERFACE_TYPE
{
    InterfaceTypeUndefined = -1,
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    PCIBus,
    VMEBus,
    NuBus,
    PCMCIABus,
    CBus,
    MPIBus,
    MPSABus,
    ProcessorInternal,
    InternalPowerBus,
    PNPISABus,
    PNPBus,
    MaximumInterfaceType

}INTERFACE_TYPE, *PINTERFACE_TYPE;

typedef enum _BUS_DATA_TYPE 
{
    ConfigurationSpaceUndefined = -1,
    Cmos,
    EisaConfiguration,
    Pos,
    CbusConfiguration,
    PCIConfiguration,
    VMEConfiguration,
    NuBusConfiguration,
    PCMCIAConfiguration,
    MPIConfiguration,
    MPSAConfiguration,
    PNPISAConfiguration,
    SgiInternalConfiguration,
    MaximumBusDataType

} BUS_DATA_TYPE, *PBUS_DATA_TYPE;

#endif

//////////////////////////////////////////////////////////////////////////

#ifdef _KERNEL_IN

typedef struct _SERVICE_DESCRIPTOR_TABLE 
{
    PVOID ServiceTableBase;
    PVOID ServiceCounterTableBase; //Used only __in checked build
    ULONG_PTR NumberOfServices;
    PVOID ParamTableBase;

} SERVICE_DESCRIPTOR_TABLE, *PSERVICE_DESCRIPTOR_TABLE;

// "MOV EAX,IMM32" opcode
//
#define	OPCODE_MOV 0xB8

// "MOV R10,RCX" opcode
//
#define OPCODE_MOV64 0x4C

#define	SERVICE_TABLE_INDEX_BITS	2
#define	NUMBER_SERVICE_TABLES		(1 << SERVICE_TABLE_INDEX_BITS)

#define	SERVICE_ID_NUMBER_BITS		12
#define	SERVICE_ID_NUMBER_MASK		((1 << SERVICE_ID_NUMBER_BITS) - 1)

extern POBJECT_TYPE* IoDriverObjectType;
extern POBJECT_TYPE* IoDeviceObjectType;

POBJECT_TYPE 
ObGetObjectType(
    PVOID Object
    );

NTSYSAPI
NTSTATUS
NTAPI
ObReferenceObjectByName( 
    __in PUNICODE_STRING ObjectName,
    __in ULONG Attributes,
    __in_opt PACCESS_STATE AccessState,
    __in_opt ACCESS_MASK DesiredAccess,
    __in POBJECT_TYPE ObjectType,
    __in KPROCESSOR_MODE AccessMode,
    __inout_opt PVOID ParseContext,
    __out PVOID* Object
    );

NTSYSAPI
UCHAR *
NTAPI
PsGetProcessImageFileName(
    PEPROCESS Process
    );

NTKERNELAPI
NTSTATUS
KeUserModeCallback(
    __in ULONG ApiNumber,
    __in PVOID InputBuffer,
    __in ULONG InputLength,
    __out PVOID *OutputBuffer,
    __in PULONG OutputLength
    );

#endif

//////////////////////////////////////////////////////////////////////////

/* System information and control */

typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemInformationClassMin = 0,
	SystemBasicInformation = 0,
	SystemProcessorInformation = 1,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemPathInformation = 4,
	SystemNotImplemented1 = 4,
	SystemProcessInformation = 5,
	SystemProcessesAndThreadsInformation = 5,
	SystemCallCountInfoInformation = 6,
	SystemCallCounts = 6,
	SystemDeviceInformation = 7,
	SystemConfigurationInformation = 7,
	SystemProcessorPerformanceInformation = 8,
	SystemProcessorTimes = 8,
	SystemFlagsInformation = 9,
	SystemGlobalFlag = 9,
	SystemCallTimeInformation = 10,
	SystemNotImplemented2 = 10,
	SystemModuleInformation = 11,
	SystemLocksInformation = 12,
	SystemLockInformation = 12,
	SystemStackTraceInformation = 13,
	SystemNotImplemented3 = 13,
	SystemPagedPoolInformation = 14,
	SystemNotImplemented4 = 14,
	SystemNonPagedPoolInformation = 15,
	SystemNotImplemented5 = 15,
	SystemHandleInformation = 16,
	SystemObjectInformation = 17,
	SystemPageFileInformation = 18,
	SystemVdmInstemulInformation = 19,
	SystemInstructionEmulationCounts = 19,
	SystemVdmBopInformation = 20,
	SystemInvalidInfoClass1 = 20,	
	SystemFileCacheInformation = 21,
	SystemCacheInformation = 21,
	SystemPoolTagInformation = 22,
	SystemInterruptInformation = 23,
	SystemProcessorStatistics = 23,
	SystemDpcBehaviourInformation = 24,
	SystemDpcInformation = 24,
	SystemFullMemoryInformation = 25,
	SystemNotImplemented6 = 25,
	SystemLoadImage = 26,
	SystemUnloadImage = 27,
	SystemTimeAdjustmentInformation = 28,
	SystemTimeAdjustment = 28,
	SystemSummaryMemoryInformation = 29,
	SystemNotImplemented7 = 29,
	SystemNextEventIdInformation = 30,
	SystemNotImplemented8 = 30,
	SystemEventIdsInformation = 31,
	SystemNotImplemented9 = 31,
	SystemCrashDumpInformation = 32,
	SystemExceptionInformation = 33,
	SystemCrashDumpStateInformation = 34,
	SystemKernelDebuggerInformation = 35,
	SystemContextSwitchInformation = 36,
	SystemRegistryQuotaInformation = 37,
	SystemLoadAndCallImage = 38,
	SystemPrioritySeparation = 39,
	SystemPlugPlayBusInformation = 40,
	SystemNotImplemented10 = 40,
	SystemDockInformation = 41,
	SystemNotImplemented11 = 41,
	SystemInvalidInfoClass2 = 42,
	SystemProcessorSpeedInformation = 43,
	SystemInvalidInfoClass3 = 43,
	SystemCurrentTimeZoneInformation = 44,
	SystemTimeZoneInformation = 44,
	SystemLookasideInformation = 45,
	SystemSetTimeSlipEvent = 46,
	SystemCreateSession = 47,
	SystemDeleteSession = 48,
	SystemInvalidInfoClass4 = 49,
	SystemRangeStartInformation = 50,
	SystemVerifierInformation = 51,
	SystemAddVerifier = 52,
	SystemSessionProcessesInformation	= 53,
	SystemInformationClassMax

} SYSTEM_INFORMATION_CLASS;

// Information Structures for NtQuerySystemInformation
//
typedef struct _SYSTEM_BASIC_INFORMATION
{
    ULONG Reserved;
    ULONG TimerResolution;
    ULONG PageSize;
    ULONG NumberOfPhysicalPages;
    ULONG LowestPhysicalPageNumber;
    ULONG HighestPhysicalPageNumber;
    ULONG AllocationGranularity;
    ULONG_PTR MinimumUserModeAddress;
    ULONG_PTR MaximumUserModeAddress;
    ULONG_PTR ActiveProcessorsAffinityMask;
    CCHAR NumberOfProcessors;

} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

// Class 1
typedef struct _SYSTEM_PROCESSOR_INFORMATION
{
    USHORT ProcessorArchitecture;
    USHORT ProcessorLevel;
    USHORT ProcessorRevision;
    USHORT Reserved;
    ULONG ProcessorFeatureBits;

} SYSTEM_PROCESSOR_INFORMATION, *PSYSTEM_PROCESSOR_INFORMATION;

// Class 2
typedef struct _SYSTEM_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleProcessTime;
    LARGE_INTEGER IoReadTransferCount;
    LARGE_INTEGER IoWriteTransferCount;
    LARGE_INTEGER IoOtherTransferCount;
    ULONG IoReadOperationCount;
    ULONG IoWriteOperationCount;
    ULONG IoOtherOperationCount;
    ULONG AvailablePages;
    ULONG CommittedPages;
    ULONG CommitLimit;
    ULONG PeakCommitment;
    ULONG PageFaultCount;
    ULONG CopyOnWriteCount;
    ULONG TransitionCount;
    ULONG CacheTransitionCount;
    ULONG DemandZeroCount;
    ULONG PageReadCount;
    ULONG PageReadIoCount;
    ULONG CacheReadCount;
    ULONG CacheIoCount;
    ULONG DirtyPagesWriteCount;
    ULONG DirtyWriteIoCount;
    ULONG MappedPagesWriteCount;
    ULONG MappedWriteIoCount;
    ULONG PagedPoolPages;
    ULONG NonPagedPoolPages;
    ULONG PagedPoolAllocs;
    ULONG PagedPoolFrees;
    ULONG NonPagedPoolAllocs;
    ULONG NonPagedPoolFrees;
    ULONG FreeSystemPtes;
    ULONG ResidentSystemCodePage;
    ULONG TotalSystemDriverPages;
    ULONG TotalSystemCodePages;
    ULONG NonPagedPoolLookasideHits;
    ULONG PagedPoolLookasideHits;
    ULONG Spare3Count;
    ULONG ResidentSystemCachePage;
    ULONG ResidentPagedPoolPage;
    ULONG ResidentSystemDriverPage;
    ULONG CcFastReadNoWait;
    ULONG CcFastReadWait;
    ULONG CcFastReadResourceMiss;
    ULONG CcFastReadNotPossible;
    ULONG CcFastMdlReadNoWait;
    ULONG CcFastMdlReadWait;
    ULONG CcFastMdlReadResourceMiss;
    ULONG CcFastMdlReadNotPossible;
    ULONG CcMapDataNoWait;
    ULONG CcMapDataWait;
    ULONG CcMapDataNoWaitMiss;
    ULONG CcMapDataWaitMiss;
    ULONG CcPinMappedDataCount;
    ULONG CcPinReadNoWait;
    ULONG CcPinReadWait;
    ULONG CcPinReadNoWaitMiss;
    ULONG CcPinReadWaitMiss;
    ULONG CcCopyReadNoWait;
    ULONG CcCopyReadWait;
    ULONG CcCopyReadNoWaitMiss;
    ULONG CcCopyReadWaitMiss;
    ULONG CcMdlReadNoWait;
    ULONG CcMdlReadWait;
    ULONG CcMdlReadNoWaitMiss;
    ULONG CcMdlReadWaitMiss;
    ULONG CcReadAheadIos;
    ULONG CcLazyWriteIos;
    ULONG CcLazyWritePages;
    ULONG CcDataFlushes;
    ULONG CcDataPages;
    ULONG ContextSwitches;
    ULONG FirstLevelTbFills;
    ULONG SecondLevelTbFills;
    ULONG SystemCalls;

    // For Win7
    //
    ULONG Reserved1[4];

} SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

// Class 3
typedef struct _SYSTEM_TIMEOFDAY_INFORMATION
{
    LARGE_INTEGER BootTime;
    LARGE_INTEGER CurrentTime;
    LARGE_INTEGER TimeZoneBias;
    ULONG TimeZoneId;
    ULONG Reserved;
#if (NTDDI_VERSION >= NTDDI_WIN2K)
    ULONGLONG BootTimeBias;
    ULONGLONG SleepTimeBias;
#endif

} SYSTEM_TIMEOFDAY_INFORMATION, *PSYSTEM_TIMEOFDAY_INFORMATION;

//#pragma pack(pop)

// Class 4
// This class is obsolete, please use KUSER_SHARED_DATA instead

typedef enum _THREAD_STATE
{
    StateInitialized,
    StateReady,
    StateRunning,
    StateStandby,
    StateTerminated,
    StateWait,
    StateTransition,
    StateUnknown

} THREAD_STATE;

// Class 5
typedef struct _SYSTEM_THREAD_INFORMATION
{
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER CreateTime;
    ULONG WaitTime;
    PVOID StartAddress;
    CLIENT_ID ClientId;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
    ULONG ContextSwitches;
    THREAD_STATE ThreadState;
    KWAIT_REASON WaitReason;

#ifdef _WIN64
    ULONG Reserved;
#endif

} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    ULONG Reserved1[6];
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    HANDLE InheritedFromUniqueProcessId;
    ULONG HandleCount;
    ULONG SessionId;
    ULONG_PTR PageDirectoryBase;

    VM_COUNTERS VmCounters;
    IO_COUNTERS IoCounters;

    SYSTEM_THREAD_INFORMATION Threads[1];

} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

//#pragma pack(push,4)

// Class 6
typedef struct _SYSTEM_CALL_COUNT_INFORMATION
{
    ULONG Length;
    ULONG NumberOfTables;

} SYSTEM_CALL_COUNT_INFORMATION, *PSYSTEM_CALL_COUNT_INFORMATION;

// Class 7
typedef struct _SYSTEM_DEVICE_INFORMATION
{
    ULONG NumberOfDisks;
    ULONG NumberOfFloppies;
    ULONG NumberOfCdRoms;
    ULONG NumberOfTapes;
    ULONG NumberOfSerialPorts;
    ULONG NumberOfParallelPorts;

} SYSTEM_DEVICE_INFORMATION, *PSYSTEM_DEVICE_INFORMATION;

// Class 8
typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
{
    LARGE_INTEGER IdleTime;
    LARGE_INTEGER KernelTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER DpcTime;
    LARGE_INTEGER InterruptTime;
    ULONG InterruptCount;

} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

// Class 9
typedef struct _SYSTEM_FLAGS_INFORMATION
{
    ULONG Flags;

} SYSTEM_FLAGS_INFORMATION, *PSYSTEM_FLAGS_INFORMATION;

// Class 10
typedef struct _SYSTEM_CALL_TIME_INFORMATION
{
    ULONG Length;
    ULONG TotalCalls;
    LARGE_INTEGER TimeOfCalls[1];

} SYSTEM_CALL_TIME_INFORMATION, *PSYSTEM_CALL_TIME_INFORMATION;

// Class 11 - See RTL_PROCESS_MODULES

typedef struct _RTL_PROCESS_MODULE_INFORMATION 
{
    PVOID Section;                // Not filled __in
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR FullPathName[256];

} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
    ULONG NumberOfModules;
    RTL_PROCESS_MODULE_INFORMATION Modules[1];

} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

// Class 12 - See RTL_PROCESS_LOCKS

// Class 13 - See RTL_PROCESS_BACKTRACES

// Class 14 - 15
typedef struct _SYSTEM_POOL_ENTRY
{
    BOOLEAN Allocated;
    BOOLEAN Spare0;
    USHORT AllocatorBackTraceIndex;
    ULONG Size;
    union
    {
        UCHAR Tag[4];
        ULONG TagUlong;
        PVOID ProcessChargedQuota;
    };

} SYSTEM_POOL_ENTRY, *PSYSTEM_POOL_ENTRY;

typedef struct _SYSTEM_POOL_INFORMATION
{
    ULONG TotalSize;
    PVOID FirstEntry;
    USHORT EntryOverhead;
    BOOLEAN PoolTagPresent;
    BOOLEAN Spare0;
    ULONG NumberOfEntries;
    SYSTEM_POOL_ENTRY Entries[1];

} SYSTEM_POOL_INFORMATION, *PSYSTEM_POOL_INFORMATION;

typedef enum _SYSTEM_HANDLE_TYPE
{
    OB_TYPE_UNKNOWN,	//0
    OB_TYPE_TYPE,		//1
    OB_TYPE_DIRECTORY,	//2
    OB_TYPE_SYMBOLIC_LINK,//3
    OB_TYPE_TOKEN,		//4
    OB_TYPE_PROCESS,	//5
    OB_TYPE_THREAD,		//6
    OB_TYPE_UNKNOWN_7,	//7
    OB_TYPE_EVENT,		//8
    OB_TYPE_EVENT_PAIR,	//9
    OB_TYPE_MUTANT,		//10
    OB_TYPE_UNKNOWN_11,	//11
    OB_TYPE_SEMAPHORE,	//12
    OB_TYPE_TIMER,		//13
    OB_TYPE_PROFILE,	//14
    OB_TYPE_WINDOW_STATION,//15
    OB_TYPE_DESKTOP,	//16
    OB_TYPE_SECTION,	//17
    OB_TYPE_KEY,		//18
    OB_TYPE_PORT,		//19
    OB_TYPE_WAITABLE_PORT,//20
    OB_TYPE_UNKNOWN_21,	
    OB_TYPE_UNKNOWN_22,
    OB_TYPE_UNKNOWN_23,
    OB_TYPE_UNKNOWN_24,
    OB_TYPE_IO_COMPLETION,//25
    OB_TYPE_FILE		//26

}SYSTEM_HANDLE_TYPE;

// Class 16
typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
    USHORT UniqueProcessId;
    USHORT CreatorBackTraceIndex;
    UCHAR ObjectTypeIndex;
    UCHAR HandleAttributes;
    USHORT HandleValue;
    PVOID Object;
    ULONG GrantedAccess;

} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
    ULONG NumberOfHandles;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];

} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

// Class 17
typedef struct _SYSTEM_OBJECTTYPE_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG NumberOfObjects;
    ULONG NumberOfHandles;
    ULONG TypeIndex;
    ULONG InvalidAttributes;
    GENERIC_MAPPING GenericMapping;
    ULONG ValidAccessMask;
    ULONG PoolType;
    BOOLEAN SecurityRequired;
    BOOLEAN WaitableObject;
    UNICODE_STRING TypeName;

} SYSTEM_OBJECTTYPE_INFORMATION, *PSYSTEM_OBJECTTYPE_INFORMATION;

typedef struct _SYSTEM_OBJECT_INFORMATION
{
    ULONG NextEntryOffset;
    PVOID Object;
    HANDLE CreatorUniqueProcess;
    USHORT CreatorBackTraceIndex;
    USHORT Flags;
    LONG PointerCount;
    LONG HandleCount;
    ULONG PagedPoolCharge;
    ULONG NonPagedPoolCharge;
    HANDLE ExclusiveProcessId;
    PVOID SecurityDescriptor;
    OBJECT_NAME_INFORMATION NameInfo;

} SYSTEM_OBJECT_INFORMATION, *PSYSTEM_OBJECT_INFORMATION;

// Class 18
typedef struct _SYSTEM_PAGEFILE_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG TotalSize;
    ULONG TotalInUse;
    ULONG PeakUsage;
    UNICODE_STRING PageFileName;

} SYSTEM_PAGEFILE_INFORMATION, *PSYSTEM_PAGEFILE_INFORMATION;

// Class 19
typedef struct _SYSTEM_VDM_INSTEMUL_INFO
{
    ULONG SegmentNotPresent;
    ULONG VdmOpcode0F;
    ULONG OpcodeESPrefix;
    ULONG OpcodeCSPrefix;
    ULONG OpcodeSSPrefix;
    ULONG OpcodeDSPrefix;
    ULONG OpcodeFSPrefix;
    ULONG OpcodeGSPrefix;
    ULONG OpcodeOPER32Prefix;
    ULONG OpcodeADDR32Prefix;
    ULONG OpcodeINSB;
    ULONG OpcodeINSW;
    ULONG OpcodeOUTSB;
    ULONG OpcodeOUTSW;
    ULONG OpcodePUSHF;
    ULONG OpcodePOPF;
    ULONG OpcodeINTnn;
    ULONG OpcodeINTO;
    ULONG OpcodeIRET;
    ULONG OpcodeINBimm;
    ULONG OpcodeINWimm;
    ULONG OpcodeOUTBimm;
    ULONG OpcodeOUTWimm ;
    ULONG OpcodeINB;
    ULONG OpcodeINW;
    ULONG OpcodeOUTB;
    ULONG OpcodeOUTW;
    ULONG OpcodeLOCKPrefix;
    ULONG OpcodeREPNEPrefix;
    ULONG OpcodeREPPrefix;
    ULONG OpcodeHLT;
    ULONG OpcodeCLI;
    ULONG OpcodeSTI;
    ULONG BopCount;

} SYSTEM_VDM_INSTEMUL_INFO, *PSYSTEM_VDM_INSTEMUL_INFO;

// Class 20 - ULONG VDMBOPINFO

// Class 21
typedef struct _SYSTEM_FILECACHE_INFORMATION
{
    ULONG CurrentSize;
    ULONG PeakSize;
    ULONG PageFaultCount;
    ULONG MinimumWorkingSet;
    ULONG MaximumWorkingSet;
    ULONG CurrentSizeIncludingTransitionInPages;
    ULONG PeakSizeIncludingTransitionInPages;
    ULONG TransitionRePurposeCount;
    ULONG Flags;

} SYSTEM_FILECACHE_INFORMATION, *PSYSTEM_FILECACHE_INFORMATION;

// Class 22
typedef struct _SYSTEM_POOLTAG
{
    union
    {
        UCHAR Tag[4];
        ULONG TagUlong;
    };
    ULONG PagedAllocs;
    ULONG PagedFrees;
    ULONG PagedUsed;
    ULONG NonPagedAllocs;
    ULONG NonPagedFrees;
    ULONG NonPagedUsed;

} SYSTEM_POOLTAG, *PSYSTEM_POOLTAG;

typedef struct _SYSTEM_POOLTAG_INFORMATION
{
    ULONG Count;
    SYSTEM_POOLTAG TagInfo[1];

} SYSTEM_POOLTAG_INFORMATION, *PSYSTEM_POOLTAG_INFORMATION;

// Class 23
typedef struct _SYSTEM_INTERRUPT_INFORMATION
{
    ULONG ContextSwitches;
    ULONG DpcCount;
    ULONG DpcRate;
    ULONG TimeIncrement;
    ULONG DpcBypassCount;
    ULONG ApcBypassCount;

} SYSTEM_INTERRUPT_INFORMATION, *PSYSTEM_INTERRUPT_INFORMATION;

// Class 24
typedef struct _SYSTEM_DPC_BEHAVIOR_INFORMATION
{
    ULONG Spare;
    ULONG DpcQueueDepth;
    ULONG MinimumDpcRate;
    ULONG AdjustDpcThreshold;
    ULONG IdealDpcRate;

} SYSTEM_DPC_BEHAVIOR_INFORMATION, *PSYSTEM_DPC_BEHAVIOR_INFORMATION;

// Class 25
typedef struct _SYSTEM_MEMORY_INFO
{
    PUCHAR StringOffset;
    USHORT ValidCount;
    USHORT TransitionCount;
    USHORT ModifiedCount;
    USHORT PageTableCount;

} SYSTEM_MEMORY_INFO, *PSYSTEM_MEMORY_INFO;

typedef struct _SYSTEM_MEMORY_INFORMATION
{
    ULONG InfoSize;
    ULONG StringStart;
    SYSTEM_MEMORY_INFO Memory[1];

} SYSTEM_MEMORY_INFORMATION, *PSYSTEM_MEMORY_INFORMATION;

// Class 26
typedef struct _SYSTEM_GDI_DRIVER_INFORMATION
{
    UNICODE_STRING DriverName;
    PVOID ImageAddress;
    PVOID SectionPointer;
    PVOID EntryPoint;
    //PIMAGE_EXPORT_DIRECTORY ExportSectionPointer;
    PVOID ExportSectionPointer;
    ULONG ImageLength;

} SYSTEM_GDI_DRIVER_INFORMATION, *PSYSTEM_GDI_DRIVER_INFORMATION;

// Class 27
// Not an actually class, simply a PVOID to the ImageAddress

// Class 28
typedef struct _SYSTEM_QUERY_TIME_ADJUST_INFORMATION
{
    ULONG TimeAdjustment;
    ULONG TimeIncrement;
    BOOLEAN Enable;

} SYSTEM_QUERY_TIME_ADJUST_INFORMATION, *PSYSTEM_QUERY_TIME_ADJUST_INFORMATION;

typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION
{
    ULONG TimeAdjustment;
    BOOLEAN Enable;

} SYSTEM_SET_TIME_ADJUST_INFORMATION, *PSYSTEM_SET_TIME_ADJUST_INFORMATION;

// Class 29 - Same as 25

// FixMe: Class 30

// Class 31
typedef struct _SYSTEM_REF_TRACE_INFORMATION
{
    UCHAR TraceEnable;
    UCHAR TracePermanent;
    UNICODE_STRING TraceProcessName;
    UNICODE_STRING TracePoolTags;

} SYSTEM_REF_TRACE_INFORMATION, *PSYSTEM_REF_TRACE_INFORMATION;

// Class 32 - OBSOLETE

// Class 33
typedef struct _SYSTEM_EXCEPTION_INFORMATION
{
    ULONG AlignmentFixupCount;
    ULONG ExceptionDispatchCount;
    ULONG FloatingEmulationCount;
    ULONG ByteWordEmulationCount;

} SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

// Class 34
typedef struct _SYSTEM_CRASH_STATE_INFORMATION
{
    ULONG ValidCrashDump;

} SYSTEM_CRASH_STATE_INFORMATION, *PSYSTEM_CRASH_STATE_INFORMATION;

// Class 35
typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
    BOOLEAN KernelDebuggerEnabled;
    BOOLEAN KernelDebuggerNotPresent;

} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

// Class 36
typedef struct _SYSTEM_CONTEXT_SWITCH_INFORMATION
{
    ULONG ContextSwitches;
    ULONG FindAny;
    ULONG FindLast;
    ULONG FindIdeal;
    ULONG IdleAny;
    ULONG IdleCurrent;
    ULONG IdleLast;
    ULONG IdleIdeal;
    ULONG PreemptAny;
    ULONG PreemptCurrent;
    ULONG PreemptLast;
    ULONG SwitchToIdle;

} SYSTEM_CONTEXT_SWITCH_INFORMATION, *PSYSTEM_CONTEXT_SWITCH_INFORMATION;

// Class 37
typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION
{
    ULONG RegistryQuotaAllowed;
    ULONG RegistryQuotaUsed;
    ULONG PagedPoolSize;

} SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

// Class 38
// Not a structure, simply send the UNICODE_STRING

// Class 39
// Not a structure, simply send a ULONG containing the new separation

typedef enum _PLUGPLAY_BUS_CLASS
{
    SystemBus,
    PlugPlayVirtualBus,
    MaxPlugPlayBusClass

} PLUGPLAY_BUS_CLASS, *PPLUGPLAY_BUS_CLASS;

//
// Plag and Play Bus Types
//
typedef enum _PLUGPLAY_VIRTUAL_BUS_TYPE
{
    Root,
    MaxPlugPlayVirtualBusType

} PLUGPLAY_VIRTUAL_BUS_TYPE, *PPLUGPLAY_VIRTUAL_BUS_TYPE;

typedef enum _SYSDBG_COMMAND
{
    SysDbgQueryModuleInformation=0,
    SysDbgQueryTraceInformation,
    SysDbgSetTracepoint,
    SysDbgSetSpecialCall,
    SysDbgClearSpecialCalls,
    SysDbgQuerySpecialCalls,
    SysDbgBreakPoint,
    SysDbgQueryVersion,
    SysDbgReadVirtual,
    SysDbgWriteVirtual,
    SysDbgReadPhysical,
    SysDbgWritePhysical,
    SysDbgReadControlSpace,
    SysDbgWriteControlSpace,
    SysDbgReadIoSpace,
    SysDbgWriteIoSpace,
    SysDbgReadMsr,
    SysDbgWriteMsr,
    SysDbgReadBusData,
    SysDbgWriteBusData,
    SysDbgCheckLowMemory,
    SysDbgEnableKernelDebugger,
    SysDbgDisableKernelDebugger,
    SysDbgGetAutoKdEnable,
    SysDbgSetAutoKdEnable,
    SysDbgGetPrintBufferSize,
    SysDbgSetPrintBufferSize,
    SysDbgGetKdUmExceptionEnable,
    SysDbgSetKdUmExceptionEnable,
    SysDbgGetTriageDump,
    SysDbgGetKdBlockEnable,
    SysDbgSetKdBlockEnable,

} SYSDBG_COMMAND, *PSYSDBG_COMMAND;

// used by SysDbgQueryVersion=7
typedef struct _DBGKD_GET_VERSION
{
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    USHORT  ProtocolVersion;
    USHORT  Flags;
    USHORT  MachineType;
    UCHAR   MaxPacketType;
    UCHAR   MaxStateChange;
    UCHAR   MaxManipulate;
    UCHAR   Simulation;
    USHORT  Unused[1];
    ULONG64 KernBase;
    ULONG64 PsLoadedModuleList;
    ULONG64 DebuggerDataList;

} DBGKD_GET_VERSION, *PDBGKD_GET_VERSION;

typedef struct _SYSDBG_VIRTUAL
{
    PVOID Address;
    PVOID Buffer;
    ULONG Request;

} SYSDBG_VIRTUAL, *PSYSDBG_VIRTUAL;

typedef LARGE_INTEGER PHYSICAL_ADDRESS;

typedef struct _SYSDBG_PHYSICAL
{
    PHYSICAL_ADDRESS Address;
    PVOID Buffer;
    ULONG Request;

} SYSDBG_PHYSICAL, *PSYSDBG_PHYSICAL;

typedef struct _SYSDBG_CONTROL_SPACE
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    ULONG Processor;

} SYSDBG_CONTROL_SPACE, *PSYSDBG_CONTROL_SPACE;

typedef struct _SYSDBG_IO_SPACE 
{
    ULONG64 Address;
    PVOID Buffer;
    ULONG Request;
    INTERFACE_TYPE InterfaceType;
    ULONG BusNumber;
    ULONG AddressSpace;

} SYSDBG_IO_SPACE, *PSYSDBG_IO_SPACE;

typedef struct _SYSDBG_MSR 
{
    ULONG Msr;
    ULONG64 Data;

} SYSDBG_MSR, *PSYSDBG_MSR;

typedef struct _SYSDBG_BUS_DATA
{
    ULONG Address;
    PVOID Buffer;
    ULONG Request;
    BUS_DATA_TYPE BusDataType;
    ULONG BusNumber;
    ULONG SlotNumber;

} SYSDBG_BUS_DATA, *PSYSDBG_BUS_DATA;

// Plug and Play Bus Type Definition
//
typedef struct _PLUGPLAY_BUS_TYPE
{
    PLUGPLAY_BUS_CLASS BusClass;
    union
    {
        INTERFACE_TYPE SystemBusType;
        PLUGPLAY_VIRTUAL_BUS_TYPE PlugPlayVirtualBusType;
    };

} PLUGPLAY_BUS_TYPE, *PPLUGPLAY_BUS_TYPE;

#define MAX_BUS_NAME 24

//
// Plug and Play Bus Instance Definition
//
typedef struct _PLUGPLAY_BUS_INSTANCE
{
    PLUGPLAY_BUS_TYPE BusType;
    ULONG BusNumber;
    WCHAR BusName[MAX_BUS_NAME];

} PLUGPLAY_BUS_INSTANCE, *PPLUGPLAY_BUS_INSTANCE;

// Class 40
typedef struct _SYSTEM_PLUGPLAY_BUS_INFORMATION
{
    ULONG BusCount;
    PLUGPLAY_BUS_INSTANCE BusInstance[1];

} SYSTEM_PLUGPLAY_BUS_INFORMATION, *PSYSTEM_PLUGPLAY_BUS_INFORMATION;

typedef enum _SYSTEM_DOCK_STATE
{
    SystemDockStateUnknown,
    SystemUndocked,
    SystemDocked

} SYSTEM_DOCK_STATE, *PSYSTEM_DOCK_STATE;

// Class 41
typedef struct _SYSTEM_DOCK_INFORMATION
{
    SYSTEM_DOCK_STATE DockState;
    INTERFACE_TYPE DeviceBusType;
    ULONG DeviceBusNumber;
    ULONG SlotNumber;

} SYSTEM_DOCK_INFORMATION, *PSYSTEM_DOCK_INFORMATION;

// Class 42
typedef struct _SYSTEM_POWER_INFORMATION_NATIVE
{
    BOOLEAN SystemSuspendSupported;
    BOOLEAN SystemHibernateSupported;
    BOOLEAN ResumeTimerSupportsSuspend;
    BOOLEAN ResumeTimerSupportsHibernate;
    BOOLEAN LidSupported;
    BOOLEAN TurboSettingSupported;
    BOOLEAN TurboMode;
    BOOLEAN SystemAcOrDc;
    BOOLEAN PowerDownDisabled;
    LARGE_INTEGER SpindownDrives;

} SYSTEM_POWER_INFORMATION_NATIVE, *PSYSTEM_POWER_INFORMATION_NATIVE;

// Class 43
typedef struct _SYSTEM_LEGACY_DRIVER_INFORMATION
{
    ULONG VetoType;
    UNICODE_STRING VetoDriver;
    // CHAR Buffer[0];

} SYSTEM_LEGACY_DRIVER_INFORMATION, *PSYSTEM_LEGACY_DRIVER_INFORMATION;

// Class 44
//typedef struct _TIME_ZONE_INFORMATION RTL_TIME_ZONE_INFORMATION;

// Class 45
typedef struct _SYSTEM_LOOKASIDE_INFORMATION
{
    USHORT CurrentDepth;
    USHORT MaximumDepth;
    ULONG TotalAllocates;
    ULONG AllocateMisses;
    ULONG TotalFrees;
    ULONG FreeMisses;
    ULONG Type;
    ULONG Tag;
    ULONG Size;

} SYSTEM_LOOKASIDE_INFORMATION, *PSYSTEM_LOOKASIDE_INFORMATION;

// Class 46
// Not a structure. Only a HANDLE for the SlipEvent;

// Class 47
// Not a structure. Only a ULONG for the SessionId;

// Class 48
// Not a structure. Only a ULONG for the SessionId;

// FixMe: Class 49

// Class 50
// Not a structure. Only a ULONG_PTR for the SystemRangeStart

// Class 51
typedef struct _SYSTEM_VERIFIER_INFORMATION
{
    ULONG NextEntryOffset;
    ULONG Level;
    UNICODE_STRING DriverName;
    ULONG RaiseIrqls;
    ULONG AcquireSpinLocks;
    ULONG SynchronizeExecutions;
    ULONG AllocationsAttempted;
    ULONG AllocationsSucceeded;
    ULONG AllocationsSucceededSpecialPool;
    ULONG AllocationsWithNoTag;
    ULONG TrimRequests;
    ULONG Trims;
    ULONG AllocationsFailed;
    ULONG AllocationsFailedDeliberately;
    ULONG Loads;
    ULONG Unloads;
    ULONG UnTrackedPool;
    ULONG CurrentPagedPoolAllocations;
    ULONG CurrentNonPagedPoolAllocations;
    ULONG PeakPagedPoolAllocations;
    ULONG PeakNonPagedPoolAllocations;
    ULONG PagedPoolUsageInBytes;
    ULONG NonPagedPoolUsageInBytes;
    ULONG PeakPagedPoolUsageInBytes;
    ULONG PeakNonPagedPoolUsageInBytes;

} SYSTEM_VERIFIER_INFORMATION, *PSYSTEM_VERIFIER_INFORMATION;

// FixMe: Class 52

// Class 53
typedef struct _SYSTEM_SESSION_PROCESS_INFORMATION
{
    ULONG SessionId;
    ULONG SizeOfBuf;
    PVOID Buffer; // Same format as __in SystemProcessInformation

} SYSTEM_SESSION_PROCESS_INFORMATION, *PSYSTEM_SESSION_PROCESS_INFORMATION;

// FixMe: Class 54-97

//
// Hotpatch flags
//
#define RTL_HOTPATCH_SUPPORTED_FLAG         0x01
#define RTL_HOTPATCH_SWAP_OBJECT_NAMES      0x08 << 24
#define RTL_HOTPATCH_SYNC_RENAME_FILES      0x10 << 24
#define RTL_HOTPATCH_PATCH_USER_MODE        0x20 << 24
#define RTL_HOTPATCH_REMAP_SYSTEM_DLL       0x40 << 24
#define RTL_HOTPATCH_PATCH_KERNEL_MODE      0x80 << 24


// Class 69
typedef struct _SYSTEM_HOTPATCH_CODE_INFORMATION
{
    ULONG Flags;
    ULONG InfoSize;
    union
    {
        struct
        {
            ULONG Foo;
        } CodeInfo;
        struct
        {
            USHORT NameOffset;
            USHORT NameLength;
        } KernelInfo;
        struct
        {
            USHORT NameOffset;
            USHORT NameLength;
            USHORT TargetNameOffset;
            USHORT TargetNameLength;
            UCHAR PatchingFinished;
        } UserModeInfo;
        struct
        {
            USHORT NameOffset;
            USHORT NameLength;
            USHORT TargetNameOffset;
            USHORT TargetNameLength;
            UCHAR PatchingFinished;
            ULONG ReturnCode;
            HANDLE TargetProcess;
        } InjectionInfo;
        struct
        {
            HANDLE FileHandle1;
            PIO_STATUS_BLOCK IoStatusBlock1;
            PVOID RenameInformation1;
            PVOID RenameInformationLength1;
            HANDLE FileHandle2;
            PIO_STATUS_BLOCK IoStatusBlock2;
            PVOID RenameInformation2;
            PVOID RenameInformationLength2;
        } RenameInfo;
        struct
        {
            HANDLE ParentDirectory;
            HANDLE ObjectHandle1;
            HANDLE ObjectHandle2;
        } AtomicSwap;
    };

} SYSTEM_HOTPATCH_CODE_INFORMATION, *PSYSTEM_HOTPATCH_CODE_INFORMATION;

#ifndef _KERNEL_IN

typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION 
{
    SystemFirmwareTable_Enumerate,
    SystemFirmwareTable_Get

} SYSTEM_FIRMWARE_TABLE_ACTION;

//
// Class 76
//
typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION
{
    ULONG ProviderSignature;
    SYSTEM_FIRMWARE_TABLE_ACTION Action;
    ULONG TableID;
    ULONG TableBufferLength;
    UCHAR TableBuffer[1];

} SYSTEM_FIRMWARE_TABLE_INFORMATION, *PSYSTEM_FIRMWARE_TABLE_INFORMATION;

typedef
ULONG
(__cdecl *PFNFTH)(
    __inout PSYSTEM_FIRMWARE_TABLE_INFORMATION SystemFirmwareTableInfo
    );

//
// Class 75
//
typedef struct _SYSTEM_FIRMWARE_TABLE_HANDLER
{
    ULONG ProviderSignature;
    BOOLEAN Register;
    PFNFTH FirmwareTableHandler;
    PVOID DriverObject;

} SYSTEM_FIRMWARE_TABLE_HANDLER, *PSYSTEM_FIRMWARE_TABLE_HANDLER;

#endif

//
// Class 81
//
typedef struct _SYSTEM_MEMORY_LIST_INFORMATION
{
    SIZE_T ZeroPageCount;
    SIZE_T FreePageCount;
    SIZE_T ModifiedPageCount;
    SIZE_T ModifiedNoWritePageCount;
    SIZE_T BadPageCount;
    SIZE_T PageCountByPriority[8];
    SIZE_T RepurposedPagesByPriority[8];

} SYSTEM_MEMORY_LIST_INFORMATION, *PSYSTEM_MEMORY_LIST_INFORMATION;

//////////////////////////////////////////////////////////////////////////

#define MAP_PROCESS 1L
#define MAP_SYSTEM  2L

NTOSAPI
NT_STATUS
NTAPI
NtLockVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in __out PULONG LockSize,
    __in ULONG LockType
    );

NTOSAPI
NT_STATUS
NTAPI
NtUnlockVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in __out PULONG LockSize,
    __in ULONG LockType
    );

//////////////////////////////////////////////////////////////////////////

#ifndef _KERNEL_IN

NTOSAPI
NT_STATUS
NTAPI
NtClose(
	__in HANDLE Handle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwClose(
	__in HANDLE Handle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQueryFullAttributesFile(
	__in POBJECT_ATTRIBUTES ObjectAttributes,
 	__out PFILE_NETWORK_OPEN_INFORMATION FileInformation
    );

#endif

NTOSAPI
NT_STATUS
NTAPI
NtQuerySystemInformation(
    __in SYSTEM_INFORMATION_CLASS SystemInformationClass,
    __inout PVOID SystemInformation,
    __in ULONG SystemInformationLength,
    __out_opt PULONG ReturnLength 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQuerySystemInformation(
    __in SYSTEM_INFORMATION_CLASS SystemInformationClass,
    __inout PVOID SystemInformation,
    __in ULONG SystemInformationLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryFullAttributesFile(
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__out PFILE_NETWORK_OPEN_INFORMATION FileInformation
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetSystemInformation(
	__in SYSTEM_INFORMATION_CLASS SystemInformationClass,
	__in __out PVOID SystemInformation,
	__in ULONG SystemInformationLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwSetSystemInformation(
	__in SYSTEM_INFORMATION_CLASS SystemInformationClass,
	__in __out PVOID SystemInformation,
	__in ULONG SystemInformationLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtQuerySystemEnvironmentValue(
	__in PUNICODE_STRING Name,
	__out PVOID Value,
	__in ULONG ValueLength,
	__out_opt PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetSystemEnvironmentValue(
	__in PUNICODE_STRING Name,
	__in PUNICODE_STRING Value
    );

typedef enum _SHUTDOWN_ACTION
{
	ShutdownNoReboot,
	ShutdownReboot,
	ShutdownPowerOff

} SHUTDOWN_ACTION;

NTOSAPI
NT_STATUS
NTAPI
NtShutdownSystem(
  __in SHUTDOWN_ACTION Action
  );

NTOSAPI
NT_STATUS
NTAPI
NtSystemDebugControl(
	__in SYSDBG_COMMAND ControlCode,
	__in_opt PVOID InputBuffer,
	__in ULONG InputBufferLength,
	__out_opt PVOID OutputBuffer,
	__in ULONG OutputBufferLength,
	__out_opt PULONG ReturnLength 
    );

typedef
struct _OBJECT_HANDLE_FLAG_INFORMATION
{
    BOOLEAN Inherit;
    BOOLEAN ProtectFromClose;

} OBJECT_HANDLE_FLAG_INFORMATION, *POBJECT_HANDLE_FLAG_INFORMATION;

#ifndef _KERNEL_IN

typedef 
enum _OBJECT_INFORMATION_CLASS
{
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectTypesInformation,
    ObjectHandleFlagInformation,
    ObjectSessionInformation,
    MaxObjectInfoClass

} OBJECT_INFORMATION_CLASS;

NTOSAPI
NT_STATUS
NTAPI
NtQueryObject(
	__in HANDLE ObjectHandle,
	__in OBJECT_INFORMATION_CLASS ObjectInformationClass,
	__out PVOID ObjectInformation,
	__in ULONG ObjectInformationLength,
	__out_opt PULONG ReturnLength 
    );

#endif



NTOSAPI
NT_STATUS
NTAPI
NtSetInformationObject(
	__in HANDLE ObjectHandle,
	__in OBJECT_INFORMATION_CLASS ObjectInformationClass,
	__in PVOID ObjectInformation,
	__in ULONG ObjectInformationLength
    );

/* OBJECT_BASIC_INFORMATION.Attributes constants */
/* also __in winbase.h */
//#define HANDLE_FLAG_INHERIT               0x01
//#define HANDLE_FLAG_PROTECT_FROM_CLOSE    0x02
/* end winbase.h */
#define PERMANENT                         0x10
#define EXCLUSIVE                         0x20

typedef struct _OBJECT_BASIC_INFORMATION 
{
	ULONG Attributes;
	ACCESS_MASK GrantedAccess;
	ULONG HandleCount;
	ULONG PointerCount;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
	ULONG Reserved[3];
	ULONG NameInformationLength;
	ULONG TypeInformationLength;
	ULONG SecurityDescriptorLength;
	LARGE_INTEGER CreateTime;

} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION 
{
	UNICODE_STRING Name;
	ULONG ObjectCount;
	ULONG HandleCount;
	ULONG Reserved1[4];
	ULONG PeakObjectCount;
	ULONG PeakHandleCount;
	ULONG Reserved2[4];
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccess;
	UCHAR Unknown;
	BOOLEAN MaintainHandleDatabase;
	POOL_TYPE PoolType;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;

} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

typedef struct _OBJECT_ALL_TYPES_INFORMATION 
{
  ULONG  NumberOfTypes;
  OBJECT_TYPE_INFORMATION  TypeInformation;

} OBJECT_ALL_TYPES_INFORMATION, *POBJECT_ALL_TYPES_INFORMATION;

typedef struct _OBJECT_HANDLE_ATTRIBUTE_INFORMATION 
{
  BOOLEAN  Inherit;
  BOOLEAN  ProtectFromClose;

} OBJECT_HANDLE_ATTRIBUTE_INFORMATION, *POBJECT_HANDLE_ATTRIBUTE_INFORMATION;

/*
typedef enum _SE_OBJECT_TYPE
{
    SE_UNKNOWN_OBJECT_TYPE = 0,
    SE_FILE_OBJECT,
    SE_SERVICE,
    SE_PRINTER,
    SE_REGISTRY_KEY,
    SE_LMSHARE,
    SE_KERNEL_OBJECT,
    SE_WINDOW_OBJECT,
    SE_DS_OBJECT,
    SE_DS_OBJECT_ALL,
    SE_PROVIDER_DEFINED_OBJECT,
    SE_WMIGUID_OBJECT,
    SE_REGISTRY_WOW64_32KEY
} SE_OBJECT_TYPE;
*/

#define DUPLICATE_CLOSE_SOURCE      0x00000001  
#define DUPLICATE_SAME_ACCESS       0x00000002  
#define DUPLICATE_SAME_ATTRIBUTES   0x00000004

NTOSAPI
NT_STATUS
NTAPI
NtDuplicateObject(
    __in HANDLE SourceProcessHandle,
    __in HANDLE SourceHandle,
    __in HANDLE TargetProcessHandle,
    __out_opt PHANDLE TargetHandle,
    __in ACCESS_MASK DesiredAccess,
    __in ULONG Attributes,
    __in ULONG Options
    );

#ifndef _KERNEL_IN

NTOSAPI
NT_STATUS
NTAPI
ZwDuplicateObject(
    __in HANDLE SourceProcessHandle,
    __in HANDLE SourceHandle,
    __in HANDLE TargetProcessHandle,
    __out_opt PHANDLE TargetHandle,
    __in ACCESS_MASK DesiredAccess,
    __in ULONG Attributes,
    __in ULONG Options
    );

NTOSAPI
NT_STATUS
NTAPI
NtQuerySecurityObject(
    __in HANDLE Handle,
    __in SECURITY_INFORMATION SecurityInformation,
    __out PSECURITY_DESCRIPTOR SecurityDescriptor,
    __in ULONG SecurityDescriptorLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQuerySecurityObject(
    __in HANDLE Handle,
    __in SECURITY_INFORMATION SecurityInformation,
    __out PSECURITY_DESCRIPTOR SecurityDescriptor,
    __in ULONG SecurityDescriptorLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetSecurityObject(
    __in HANDLE Handle,
    __in SECURITY_INFORMATION SecurityInformation,
    __in PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTOSAPI
NT_STATUS
NTAPI
ZwSetSecurityObject(
    __in HANDLE Handle,
    __in SECURITY_INFORMATION SecurityInformation,
    __in PSECURITY_DESCRIPTOR SecurityDescriptor
    );

NTOSAPI
NT_STATUS
NTAPI
ZwOpenDirectoryObject(
    __out PHANDLE DirectoryHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes
    );

#endif

NTOSAPI
NT_STATUS
NTAPI
ZwQueryDirectoryObject(
    __in HANDLE DirectoryHandle,
    __out PVOID Buffer,
    __in ULONG BufferLength,
    __in BOOLEAN ReturnSingleEntry,
    __in BOOLEAN RestartScan,
    __in __out PULONG Context,
    __out_opt PULONG ReturnLength 
    );

typedef struct _DIRECTORY_BASIC_INFORMATION 
{
  UNICODE_STRING ObjectName;
  UNICODE_STRING ObjectTypeName;

} DIRECTORY_BASIC_INFORMATION, *PDIRECTORY_BASIC_INFORMATION;

NTOSAPI
NT_STATUS
NTAPI
ZwCreateSymbolicLinkObject(
    __out PHANDLE SymbolicLinkHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in PUNICODE_STRING TargetName
    );


/* Virtual memory */

typedef enum _MEMORY_INFORMATION_CLASS 
{
    MemoryBasicInformation,
    MemoryWorkingSetList,
    MemorySectionName,
    MemoryBasicVlmInformation

} MEMORY_INFORMATION_CLASS;

#ifndef _KERNEL_IN

NTOSAPI
NT_STATUS
NTAPI
NtAllocateVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in ULONG ZeroBits,
    __in __out PULONG AllocationSize,
    __in ULONG AllocationType,
    __in ULONG Protect
    );

NTOSAPI
NT_STATUS
NTAPI
ZwAllocateVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in ULONG_PTR ZeroBits,
    __in __out PSIZE_T RegionSize,
    __in ULONG AllocationType,
    __in ULONG Protect
    );

NTOSAPI
NT_STATUS
NTAPI
NtFreeVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in __out PULONG FreeSize,
    __in ULONG FreeType
    );

NTOSAPI
NT_STATUS
NTAPI
ZwFreeVirtualMemory(
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in __out PULONG FreeSize,
    __in ULONG FreeType
    );

NTOSAPI
NT_STATUS
NTAPI
ZwFlushVirtualMemory(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG FlushSize,
	__out PIO_STATUS_BLOCK IoStatusBlock
    );

#endif

NTOSAPI
NT_STATUS
NTAPI
ZwQueryVirtualMemory(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__in MEMORY_INFORMATION_CLASS MemoryInformationClass,
	__out PVOID MemoryInformation,
	__in ULONG MemoryInformationLength,
	__out_opt PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryVirtualMemory(
    __in HANDLE ProcessHandle,
    __in PVOID BaseAddress,
    __in MEMORY_INFORMATION_CLASS MemoryInformationClass,
    __out PVOID MemoryInformation,
    __in ULONG MemoryInformationLength,
    __out_opt PULONG ReturnLength
    );

/* MEMORY_WORKING_SET_LIST.WorkingSetList constants */
#define WSLE_PAGE_READONLY                0x001
#define WSLE_PAGE_EXECUTE                 0x002
#define WSLE_PAGE_READWRITE               0x004
#define WSLE_PAGE_EXECUTE_READ            0x003
#define WSLE_PAGE_WRITECOPY               0x005
#define WSLE_PAGE_EXECUTE_READWRITE       0x006
#define WSLE_PAGE_EXECUTE_WRITECOPY       0x007
#define WSLE_PAGE_SHARE_COUNT_MASK        0x0E0
#define WSLE_PAGE_SHAREABLE               0x100

typedef struct _MEMORY_WORKING_SET_LIST
{
    ULONG NumberOfPages;
    ULONG WorkingSetList[1];

} MEMORY_WORKING_SET_LIST, *PMEMORY_WORKING_SET_LIST;

typedef struct _MEMORY_SECTION_NAME
{
    UNICODE_STRING SectionFileName;

} MEMORY_SECTION_NAME, *PMEMORY_SECTION_NAME;

/* Zw[Lock|Unlock]VirtualMemory.LockType constants */
#define LOCK_VM_IN_WSL                    0x01
#define LOCK_VM_IN_RAM                    0x02

typedef
NT_STATUS
(NTAPI* _ZwLockVirtualMemory)(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG LockSize,
	__in ULONG LockType
    );

typedef
NT_STATUS
(NTAPI* _ZwUnlockVirtualMemory)(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG LockSize,
	__in ULONG LockType
    );

NTOSAPI
NT_STATUS
NTAPI
ZwLockVirtualMemory(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG LockSize,
	__in ULONG LockType
    );

NTOSAPI
NT_STATUS
NTAPI
ZwUnlockVirtualMemory(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG LockSize,
	__in ULONG LockType
    );

typedef
NT_STATUS
(NTAPI* _NtReadVirtualMemory)(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__out PVOID Buffer,
	__in ULONG BufferLength,
	__out_opt PULONG ReturnLength 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwReadVirtualMemory(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__out PVOID Buffer,
	__in ULONG BufferLength,
	__out_opt PULONG ReturnLength 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwWriteVirtualMemory(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__in PVOID Buffer,
	__in ULONG BufferLength,
	__out_opt PULONG ReturnLength 
    );

typedef
NT_STATUS
(NTAPI* _ZwProtectVirtualMemory)(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG ProtectSize,
	__in ULONG NewProtect,
	__out PULONG OldProtect
    );

NTOSAPI
NT_STATUS
NTAPI
ZwProtectVirtualMemory(
	__in HANDLE ProcessHandle,
	__in __out PVOID *BaseAddress,
	__in __out PULONG ProtectSize,
	__in ULONG NewProtect,
	__out PULONG OldProtect
    );

NTOSAPI
NT_STATUS
NTAPI
ZwAllocateUserPhysicalPages(
	__in HANDLE ProcessHandle,
	__in PULONG NumberOfPages,
	__out PULONG PageFrameNumbers
    );

NTOSAPI
NT_STATUS
NTAPI
ZwFreeUserPhysicalPages(
	__in HANDLE ProcessHandle,
	__in __out PULONG NumberOfPages,
	__in PULONG PageFrameNumbers
    );

NTOSAPI
NT_STATUS
NTAPI
ZwMapUserPhysicalPages(
	__in PVOID BaseAddress,
	__in PULONG NumberOfPages,
	__in PULONG PageFrameNumbers
    );

NTOSAPI
NT_STATUS
NTAPI
ZwMapUserPhysicalPagesScatter(
	__in PVOID *BaseAddresses,
	__in PULONG NumberOfPages,
	__in PULONG PageFrameNumbers
    );

NTOSAPI
NT_STATUS
NTAPI
ZwGetWriteWatch(
	__in HANDLE ProcessHandle,
	__in ULONG Flags,
	__in PVOID BaseAddress,
	__in ULONG RegionSize,
	__out PULONG Buffer,
	__in __out PULONG BufferEntries,
	__out PULONG Granularity
    );

NTOSAPI
NT_STATUS
NTAPI
ZwResetWriteWatch(
	__in HANDLE ProcessHandle,
	__in PVOID BaseAddress,
	__in ULONG RegionSize
    );

/* Sections */

typedef enum _SECTION_INFORMATION_CLASS {
    SectionBasicInformation,
    SectionImageInformation
} SECTION_INFORMATION_CLASS;

typedef 
struct _SECTION_BASIC_INFORMATION
{
    PVOID BaseAddress;
    ULONG AllocationAttributes;
    LARGE_INTEGER MaximumSize;

} SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning(disable:4201)       // unnamed struct

typedef 
struct _SECTION_IMAGE_INFORMATION32
{
    PVOID TransferAddress;
    ULONG ZeroBits;
    SIZE_T MaximumStackSize;
    SIZE_T CommittedStackSize;
    ULONG SubSystemType;
    union
    {
        struct 
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    ULONG GpValue;
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    BOOLEAN Spare1;
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG CheckSum;

} SECTION_IMAGE_INFORMATION32, *PSECTION_IMAGE_INFORMATION32;

//
// This structure is used only by Wow64 processes. The offsets
// of structure elements should the same as viewed by a native Win64 application.
//
typedef 
struct _SECTION_IMAGE_INFORMATION64 
{
    ULONGLONG TransferAddress;
    ULONG ZeroBits;
    ULONGLONG MaximumStackSize;
    ULONGLONG CommittedStackSize;
    ULONG SubSystemType;
    union 
    {
        struct 
        {
            USHORT SubSystemMinorVersion;
            USHORT SubSystemMajorVersion;
        };
        ULONG SubSystemVersion;
    };
    ULONG GpValue;
    USHORT ImageCharacteristics;
    USHORT DllCharacteristics;
    USHORT Machine;
    BOOLEAN ImageContainsCode;
    BOOLEAN Spare1;
    ULONG LoaderFlags;
    ULONG ImageFileSize;
    ULONG Reserved[1];

} SECTION_IMAGE_INFORMATION64, *PSECTION_IMAGE_INFORMATION64;

#if defined(_WIN64)
typedef SECTION_IMAGE_INFORMATION64 SECTION_IMAGE_INFORMATION;
#else
typedef SECTION_IMAGE_INFORMATION32 SECTION_IMAGE_INFORMATION;
#endif

typedef SECTION_IMAGE_INFORMATION *PSECTION_IMAGE_INFORMATION;

#if !defined(SORTPP_PASS) && !defined(MIDL_PASS) && !defined(RC_INVOKED) && defined(_WIN64) && !defined(_X86AMD64_)
C_ASSERT(sizeof(SECTION_IMAGE_INFORMATION) == sizeof(SECTION_IMAGE_INFORMATION64));
#endif

#if _MSC_VER >= 1200
#pragma warning(pop)
#else
#pragma warning( default : 4201 )
#endif

typedef
NT_STATUS
(NTAPI* _ZwCreateSection)(
    __out PHANDLE SectionHandle,
    __in ACCESS_MASK DesiredAccess,
    __in_opt POBJECT_ATTRIBUTES ObjectAttributes,
    __in_opt PLARGE_INTEGER MaximumSize,
    __in ULONG Protect,
    __in ULONG Attributes,
    __in_opt HANDLE FileHandle
    );

#ifndef _KERNEL_IN

typedef enum _SECTION_INHERIT {
    ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;

NTOSAPI
NT_STATUS
NTAPI
NtCreateSection(
    __out PHANDLE SectionHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in_opt PLARGE_INTEGER SectionSize,
    __in ULONG Protect,
    __in ULONG Attributes,
    __in HANDLE FileHandle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwCreateSection(
    __out PHANDLE SectionHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in_opt PLARGE_INTEGER SectionSize,
    __in ULONG Protect,
    __in ULONG Attributes,
    __in HANDLE FileHandle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwMapViewOfSection(
    __in HANDLE SectionHandle,
    __in HANDLE ProcessHandle,
    __in __out PVOID *BaseAddress,
    __in ULONG_PTR ZeroBits,
    __in SIZE_T CommitSize,
    __inout_opt PLARGE_INTEGER SectionOffset,
    __inout PSIZE_T ViewSize,
    __in SECTION_INHERIT InheritDisposition,
    __in ULONG AllocationType,
    __in ULONG Win32Protect
    );

NTOSAPI
NT_STATUS
NTAPI
ZwUnmapViewOfSection (
    __in HANDLE ProcessHandle,
    __in PVOID BaseAddress
    );

#endif

NTOSAPI
NT_STATUS
NTAPI
ZwQuerySection(
	__in HANDLE SectionHandle,
	__in SECTION_INFORMATION_CLASS SectionInformationClass,
	__out PVOID SectionInformation,
	__in ULONG SectionInformationLength,
    __out_opt PULONG ResultLength 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwExtendSection(
	__in HANDLE SectionHandle,
	__in PLARGE_INTEGER SectionSize
    );

NTOSAPI
NT_STATUS
NTAPI
ZwAreMappedFilesTheSame(
	__in PVOID Address1,
	__in PVOID Address2
    );


/* Threads */

#define PS_CROSS_THREAD_FLAGS_SYSTEM 0x00000010UL

typedef struct _USER_STACK 
{
	PVOID  FixedStackBase;
	PVOID  FixedStackLimit;
	PVOID  ExpandableStackBase;
	PVOID  ExpandableStackLimit;
	PVOID  ExpandableStackBottom;

} USER_STACK, *PUSER_STACK;

typedef 
NT_STATUS 
(NTAPI* _ZwSuspendProcess)(
    __in HANDLE Process
    );

typedef 
NT_STATUS 
(NTAPI* _ZwResumeProcess)(
    __in HANDLE Process
    );

typedef 
NT_STATUS 
(NTAPI* _ZwSuspendThread)(
    __in HANDLE ThreadHandle,
    __out_opt PULONG PreviousSuspendCount
    );

typedef 
NT_STATUS 
(NTAPI* _ZwResumeThread)(
    __in HANDLE ThreadHandle,
    __out_opt PULONG PreviousSuspendCount
    );

typedef 
NT_STATUS
(NTAPI *_NtClose)(
    __in HANDLE Handle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwCreateThread(
	__out PHANDLE ThreadHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in HANDLE ProcessHandle,
	__out PCLIENT_ID ClientId,
	__in PCONTEXT ThreadContext,
	__in PUSER_STACK UserStack,
	__in BOOLEAN CreateSuspended
    );

NTOSAPI
NT_STATUS
NTAPI
NtOpenThread(
    __out PHANDLE ThreadHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in PCLIENT_ID ClientId
    );

NTOSAPI
NT_STATUS
NTAPI
ZwOpenThread(
    __out PHANDLE ThreadHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in PCLIENT_ID ClientId
    );

NTOSAPI
NT_STATUS
NTAPI
NtTerminateThread(
    __in_opt HANDLE ThreadHandle,
    __in NT_STATUS ExitStatus
    );

typedef
NTOSAPI
NT_STATUS
(NTAPI* _ZwTerminateThread)(
	__in_opt HANDLE ThreadHandle,
	__in NT_STATUS ExitStatus
    );

NTOSAPI
NT_STATUS
NTAPI
ZwTerminateThread(
	__in_opt HANDLE ThreadHandle,
	__in NT_STATUS  ExitStatus
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationThread(
    __in HANDLE ThreadHandle,
    __in THREADINFOCLASS ThreadInformationClass,
    __out PVOID ThreadInformation,
    __in ULONG ThreadInformationLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQueryInformationThread(
    __in HANDLE ThreadHandle,
    __in THREADINFOCLASS ThreadInformationClass,
    __out PVOID ThreadInformation,
    __in ULONG ThreadInformationLength,
    __out PULONG ReturnLength
    );

#ifndef _KERNEL_IN
NTOSAPI
NT_STATUS
NTAPI
NtSetInformationThread(
    __in HANDLE ThreadHandle,
    __in THREADINFOCLASS ThreadInformationClass,
    __in PVOID ThreadInformation,
    __in ULONG ThreadInformationLength
    );
#endif

NTOSAPI
NT_STATUS
NTAPI
NtSuspendThread(
    __in HANDLE ThreadHandle,
    __out PULONG PreviousSuspendCount
    );

NTOSAPI
NT_STATUS
NTAPI
NtResumeThread(
    __in HANDLE ThreadHandle,
    __out PULONG PreviousSuspendCount 
    );

NTOSAPI
NT_STATUS
NTAPI
NtSuspendProcess(
    __in HANDLE ProcessHandle    
    );

NTOSAPI
NT_STATUS
NTAPI
NtResumeProcess(
    __in HANDLE ProcessHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtGetContextThread(
    __in HANDLE ThreadHandle,
    __out PCONTEXT Context
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetContextThread(
	__in HANDLE ThreadHandle,
	__in PCONTEXT Context
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueueApcThread(
	__in HANDLE ThreadHandle,
	__in PKNORMAL_ROUTINE ApcRoutine,
	__in_opt PVOID ApcContext,
	__in_opt PVOID Argument1,
	__in_opt PVOID Argument2
    );

NTOSAPI
NT_STATUS
NTAPI
NtTestAlert(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtAlertThread(
    __in HANDLE ThreadHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtAlertResumeThread(
    __in HANDLE ThreadHandle,
    __out PULONG PreviousSuspendCount
    );

NTOSAPI
NT_STATUS
NTAPI
NtRegisterThreadTerminatePort(
    __in HANDLE PortHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtImpersonateThread(
	__in HANDLE ThreadHandle,
	__in HANDLE TargetThreadHandle,
	__in PSECURITY_QUALITY_OF_SERVICE SecurityQos
    );

#ifndef _KERNEL_IN
NTOSAPI
NT_STATUS
NTAPI
NtImpersonateAnonymousToken(
    __in HANDLE ThreadHandle
    );
#endif

/* Processes */

typedef
NT_STATUS
(NTAPI* _ZwCreateProcess)(
	__out PHANDLE ProcessHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in HANDLE InheritFromProcessHandle,
	__in BOOLEAN InheritHandles,
	__in_opt HANDLE SectionHandle,
	__in_opt HANDLE DebugPort,
	__in_opt HANDLE ExceptionPort
    );

typedef
NT_STATUS
(NTAPI* _ZwCreateProcessEx)(
    __out PHANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __in_opt POBJECT_ATTRIBUTES ObjectAttributes,
    __in HANDLE ParentProcess,
    __in ULONG Flags,
    __in_opt HANDLE SectionHandle,
    __in_opt HANDLE DebugPort,
    __in_opt HANDLE ExceptionPort,
    __in ULONG JobMemberLevel
    );


NT_STATUS
NtCreateProcessEx(
    __out PHANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __in_opt POBJECT_ATTRIBUTES ObjectAttributes,
    __in HANDLE ParentProcess,
    __in ULONG Flags,
    __in_opt HANDLE SectionHandle,
    __in_opt HANDLE DebugPort,
    __in_opt HANDLE ExceptionPort,
    __in ULONG JobMemberLevel
    );

NTOSAPI
NT_STATUS
NTAPI
NtCreateProcess(
	__out PHANDLE ProcessHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__in HANDLE InheritFromProcessHandle,
	__in BOOLEAN InheritHandles,
	__in_opt HANDLE SectionHandle,
	__in_opt HANDLE DebugPort,
	__in_opt HANDLE ExceptionPort
    );

NTOSAPI
NT_STATUS
NTAPI
NtTerminateProcess(
	__in_opt HANDLE ProcessHandle,
	__in ULONG ExitStatus
    );

#ifndef _KERNEL_IN
NTSYSAPI
NT_STATUS
NTAPI
NtOpenProcess(
    __out PHANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in PCLIENT_ID ClientId
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwOpenProcess(
    __out PHANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in PCLIENT_ID ClientId
    );

typedef
NT_STATUS
(NTAPI* _NtQueryInformationProcess)(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __out PVOID ProcessInformation,
    __in ULONG ProcessInformationLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationProcess(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __out PVOID ProcessInformation,
    __in ULONG ProcessInformationLength,
    __out PULONG ReturnLength
    );
#endif

NTOSAPI
NT_STATUS
NTAPI
ZwQueryInformationProcess(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __out PVOID ProcessInformation,
    __in ULONG ProcessInformationLength,
    __out PULONG ReturnLength 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwSetInformationProcess(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __in PVOID ProcessInformation,
    __in ULONG ProcessInformationLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetInformationProcess(
    __in HANDLE ProcessHandle,
    __in PROCESSINFOCLASS ProcessInformationClass,
    __in PVOID ProcessInformation,
    __in ULONG ProcessInformationLength
    );

typedef struct _PEB_FREE_BLOCK
{                                                                   
    struct _PEB_FREE_BLOCK* Next;                                   
    ULONG32 Size;      

}PEB_FREE_BLOCK, *PPEB_FREE_BLOCK;  

#define DOS_MAX_COMPONENT_LENGTH 255
#define DOS_MAX_PATH_LENGTH (DOS_MAX_COMPONENT_LENGTH + 5)

typedef struct _CURDIR
{
    UNICODE_STRING DosPath;
    HANDLE Handle;

} CURDIR, *PCURDIR;

#define RTL_USER_PROC_CURDIR_CLOSE 0x00000002
#define RTL_USER_PROC_CURDIR_INHERIT 0x00000003

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
    USHORT Flags;
    USHORT Length;
    ULONG TimeStamp;
    STRING DosPath;

} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;

    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    PVOID Environment;

    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;

    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

    ULONG EnvironmentSize;
    ULONG EnvironmentVersion;

} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _RTL_USER_PROCESS_PARAMETERS64
{
    ULONG MaximumLength;
    ULONG Length;

    ULONG Flags;
    ULONG DebugFlags;

    PVOID64 ConsoleHandle;
    ULONG ConsoleFlags;
    PVOID64 StandardInput;
    PVOID64 StandardOutput;
    PVOID64 StandardError;

    UNICODE_STRING64 DosPath;
    HANDLE Handle;

    UNICODE_STRING64 DllPath;
    UNICODE_STRING64 ImagePathName;
    UNICODE_STRING64 CommandLine;
    
    //...

} RTL_USER_PROCESS_PARAMETERS64, *PRTL_USER_PROCESS_PARAMETERS64;

typedef struct _LDR_DATA_TABLE_ENTRY 
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    USHORT LoadCount;
    USHORT TlsIndex;

    union
    {
        LIST_ENTRY HashLinks;
        struct 
        {
            PVOID SectionPointer;
            ULONG CheckSum;
        };
    };

    union 
    {
        struct
        {
            ULONG TimeDateStamp;
        };
        struct 
        {
            PVOID LoadedImports;
        };
    };

    PVOID EntryPointActivationContext;
    PVOID PatchInformation;

    // [Win7]
    //
    // +0x050 ForwarderLinks   : _LIST_ENTRY
    // +0x058 ServiceTagLinks  : _LIST_ENTRY
    // +0x060 StaticLinks      : _LIST_ENTRY
    // +0x068 ContextInformation : Ptr32 Void
    // +0x06c OriginalBase     : Uint4B
    // +0x070 LoadTime         : _LARGE_INTEGER

} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

#define FLS_MAXIMUM_AVAILABLE 128
#define TLS_MINIMUM_AVAILABLE 64
#define TLS_EXPANSION_SLOTS 1024

// symbols
typedef struct _PEB_LDR_DATA
{
    ULONG Length;
    BOOLEAN Initialized;
    HANDLE SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
    BOOLEAN ShutdownInProgress;
    HANDLE ShutdownThreadId;

} PEB_LDR_DATA, *PPEB_LDR_DATA;

#ifdef _KERNEL_IN
#pragma pack(push, 8)

typedef struct _RTL_CRITICAL_SECTION_DEBUG
{
    USHORT Type;
    USHORT CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    ULONG EntryCount;
    ULONG ContentionCount;
    ULONG Flags;
    USHORT CreatorBackTraceIndexHigh;
    USHORT SpareWORD;

} RTL_CRITICAL_SECTION_DEBUG, *PRTL_CRITICAL_SECTION_DEBUG, RTL_RESOURCE_DEBUG, *PRTL_RESOURCE_DEBUG;

typedef struct _RTL_CRITICAL_SECTION 
{
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;        // force size on 64-bit systems when packed

} RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#pragma pack(pop)
#endif

typedef struct _PEB
{
    BOOLEAN InheritedAddressSpace;
    BOOLEAN ReadImageFileExecOptions;
    BOOLEAN BeingDebugged;
    union
    {
        BOOLEAN BitField;
        struct
        {
            BOOLEAN ImageUsesLargePages : 1;
            BOOLEAN IsProtectedProcess : 1;
            BOOLEAN IsLegacyProcess : 1;
            BOOLEAN IsImageDynamicallyRelocated : 1;
            BOOLEAN SkipPatchingUser32Forwarders : 1;
            BOOLEAN SpareBits : 3;
        };
    };
    HANDLE Mutant;

    PVOID ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    PVOID ProcessHeap;
    PRTL_CRITICAL_SECTION FastPebLock;
    PVOID AtlThunkSListPtr;
    PVOID IFEOKey;
    union
    {
        ULONG CrossProcessFlags;
        struct
        {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ReservedBits0 : 27;
        };
        ULONG EnvironmentUpdateCount;
    };
    union
    {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    ULONG SystemReserved[1];
    ULONG AtlThunkSListPtr32;
    PVOID ApiSetMap;
    ULONG TlsExpansionCounter;
    PVOID TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID HotpatchInformation;
    PVOID* ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;

    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;

    LARGE_INTEGER CriticalSectionTimeout;
    SIZE_T HeapSegmentReserve;
    SIZE_T HeapSegmentCommit;
    SIZE_T HeapDeCommitTotalFreeThreshold;
    SIZE_T HeapDeCommitFreeBlockThreshold;

    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID* ProcessHeaps;

    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    ULONG GdiDCAttributeList;

    PRTL_CRITICAL_SECTION LoaderLock;

    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    ULONG_PTR ImageProcessAffinityMask;
    GDI_HANDLE_BUFFER GdiHandleBuffer;
    PVOID PostProcessInitRoutine;

    PVOID TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];

    ULONG SessionId;

    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID pShimData;
    PVOID AppCompatInfo;

    UNICODE_STRING CSDVersion;

    PVOID ActivationContextData;
    PVOID ProcessAssemblyStorageMap;
    PVOID SystemDefaultActivationContextData;
    PVOID SystemAssemblyStorageMap;

    SIZE_T MinimumStackCommit;

    PVOID* FlsCallback;
    LIST_ENTRY FlsListHead;
    PVOID FlsBitmap;
    ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
    ULONG FlsHighIndex;

    PVOID WerRegistrationData;
    PVOID WerShipAssertPtr;
    PVOID pContextData;
    PVOID pImageHeaderHash;
    union
    {
        ULONG TracingFlags;
        struct
        {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG SpareTracingBits : 30;
        };
    };

} PEB, *PPEB;

typedef unsigned char BYTE;

// typedef struct _PEB64
// {
//     BYTE Reserved1[2];
//     BYTE BeingDebugged;
//     BYTE Reserved2[21];
//     PPEB_LDR_DATA LoaderData;
//     PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
//     BYTE Reserved3[520];
//     PVOID PostProcessInitRoutine;
//     BYTE Reserved4[136];
//     ULONG SessionId;
// 
// } PEB64, *PPEB64;

typedef struct _PEB64
{
    PVOID64 Filler[4];
    PVOID64 ProcessParameters;

} PEB64, *PPEB64;

#define CREATE_PROCESS_BREAKAWAY_FROM_JOB   0x0001
#define CREATE_PROCESS_INHERIT_HANDLES      0x0004
#define CREATE_PROCESS_PROTECTED            0x0040

#define CREATE_THREAD_SUSPENDED             0x0001

typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY 
{
    ULONG Attribute;    // UpdateProcThreadAttribute
    SIZE_T Size;        // Value Size
    ULONG_PTR Value;    
    ULONG Unknown;      // 0

} NT_PROC_THREAD_ATTRIBUTE_ENTRY, *PNT_PROC_THREAD_ATTRIBUTE_ENTRY;

typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST
{
    ULONG Length;
    NT_PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];

} NT_PROC_THREAD_ATTRIBUTE_LIST, *PNT_PROC_THREAD_ATTRIBUTE_LIST;

typedef
NT_STATUS 
(NTAPI* _ZwCreateUserProcess)(
    __out PHANDLE ProcessHandle,
    __out PHANDLE ThreadHandle,
    __in ACCESS_MASK ProcessDesiredAccess,
    __in ACCESS_MASK ThreadDesiredAccess,
    __in_opt POBJECT_ATTRIBUTES ProcessObjectAttributes,
    __in_opt POBJECT_ATTRIBUTES ThreadObjectAttributes,
    __in ULONG CreateProcessFlags,
    __in ULONG CreateThreadFlags,
    __in PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    __in PVOID Parameter9,
    __in PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList
    );

NT_STATUS
NTAPI
NtCreateUserProcess(
    __out PHANDLE ProcessHandle,
    __out PHANDLE ThreadHandle,
    __in ACCESS_MASK ProcessDesiredAccess,
    __in ACCESS_MASK ThreadDesiredAccess,
    __in_opt POBJECT_ATTRIBUTES ProcessObjectAttributes,
    __in_opt POBJECT_ATTRIBUTES ThreadObjectAttributes,
    __in ULONG CreateProcessFlags,
    __in ULONG CreateThreadFlags,
    __in PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
    __in PVOID Parameter9,
    __in PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList
    );

NT_STATUS
NTAPI
RtlCreateProcessParameters(
	__out PRTL_USER_PROCESS_PARAMETERS  *ProcessParameters,
	__in PUNICODE_STRING ImageFile,
	__in_opt PUNICODE_STRING DllPath,
	__in_opt PUNICODE_STRING CurrentDirectory,
	__in_opt PUNICODE_STRING CommandLine,
	__in_opt PWSTR Environment,
	__in_opt PUNICODE_STRING WindowTitle,
	__in_opt PUNICODE_STRING DesktopInfo,
	__in_opt PUNICODE_STRING ShellInfo,
	__in_opt PUNICODE_STRING RuntimeInfo 
    );

NT_STATUS
NTAPI
RtlDestroyProcessParameters(
    __in PRTL_USER_PROCESS_PARAMETERS ProcessParameters
    );

typedef struct _DEBUG_BUFFER
{
	HANDLE  SectionHandle;
	PVOID  SectionBase;
	PVOID  RemoteSectionBase;
	ULONG  SectionBaseDelta;
	HANDLE  EventPairHandle;
	ULONG  Unknown[2];
	HANDLE  RemoteThreadHandle;
	ULONG  InfoClassMask;
	ULONG  SizeOfInfo;
	ULONG  AllocatedSize;
	ULONG  SectionSize;
	PVOID  ModuleInformation;
	PVOID  BackTraceInformation;
	PVOID  HeapInformation;
	PVOID  LockInformation;
	PVOID  Reserved[8];

} DEBUG_BUFFER, *PDEBUG_BUFFER;

PDEBUG_BUFFER
NTAPI
RtlCreateQueryDebugBuffer(
	__in ULONG  Size,
	__in BOOLEAN  EventPair
    );

/* RtlQueryProcessDebugInformation.DebugInfoClassMask constants */
#define PDI_MODULES                       0x01
#define PDI_BACKTRACE                     0x02
#define PDI_HEAPS                         0x04
#define PDI_HEAP_TAGS                     0x08
#define PDI_HEAP_BLOCKS                   0x10
#define PDI_LOCKS                         0x20

NT_STATUS
NTAPI
RtlQueryProcessDebugInformation(
	__in ULONG ProcessId,
	__in ULONG DebugInfoClassMask,
	__in __out PDEBUG_BUFFER DebugBuffer
    );

NT_STATUS
NTAPI
RtlDestroyQueryDebugBuffer(
    __in PDEBUG_BUFFER DebugBuffer
    );

/* DEBUG_MODULE_INFORMATION.Flags constants */
#define LDRP_STATIC_LINK                  0x00000002
#define LDRP_IMAGE_DLL                    0x00000004
#define LDRP_LOAD_IN_PROGRESS             0x00001000
#define LDRP_UNLOAD_IN_PROGRESS           0x00002000
#define LDRP_ENTRY_PROCESSED              0x00004000
#define LDRP_ENTRY_INSERTED               0x00008000
#define LDRP_CURRENT_LOAD                 0x00010000
#define LDRP_FAILED_BUILTIN_LOAD          0x00020000
#define LDRP_DONT_CALL_FOR_THREADS        0x00040000
#define LDRP_PROCESS_ATTACH_CALLED        0x00080000
#define LDRP_DEBUG_SYMBOLS_LOADED         0x00100000
#define LDRP_IMAGE_NOT_AT_BASE            0x00200000
#define LDRP_WX86_IGNORE_MACHINETYPE      0x00400000

typedef struct _DEBUG_MODULE_INFORMATION 
{
	ULONG  Reserved[2];
	ULONG  Base;
	ULONG  Size;
	ULONG  Flags;
	USHORT  Index;
	USHORT  Unknown;
	USHORT  LoadCount;
	USHORT  ModuleNameOffset;
	CHAR  ImageName[256];

} DEBUG_MODULE_INFORMATION, *PDEBUG_MODULE_INFORMATION;

typedef struct _DEBUG_HEAP_INFORMATION 
{
	ULONG  Base;
	ULONG  Flags;
	USHORT  Granularity;
	USHORT  Unknown;
	ULONG  Allocated;
	ULONG  Committed;
	ULONG  TagCount;
	ULONG  BlockCount;
	ULONG  Reserved[7];
	PVOID  Tags;
	PVOID  Blocks;

} DEBUG_HEAP_INFORMATION, *PDEBUG_HEAP_INFORMATION;

typedef struct _DEBUG_LOCK_INFORMATION 
{
	PVOID  Address;
	USHORT  Type;
	USHORT  CreatorBackTraceIndex;
	ULONG  OwnerThreadId;
	ULONG  ActiveCount;
	ULONG  ContentionCount;
	ULONG  EntryCount;
	ULONG  RecursionCount;
	ULONG  NumberOfSharedWaiters;
	ULONG  NumberOfExclusiveWaiters;

} DEBUG_LOCK_INFORMATION, *PDEBUG_LOCK_INFORMATION;



/* Jobs */

NTOSAPI
NT_STATUS
NTAPI
NtCreateJobObject(
	__out PHANDLE JobHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes
    );

NTOSAPI
NT_STATUS
NTAPI
NtOpenJobObject(
	__out PHANDLE JobHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes
    );

NTOSAPI
NT_STATUS
NTAPI
NtTerminateJobObject(
	__in HANDLE JobHandle,
	__in ULONG ExitStatus
    );

NTOSAPI
NT_STATUS
NTAPI
NtAssignProcessToJobObject(
	__in HANDLE JobHandle,
	__in HANDLE ProcessHandle
    );

#ifdef _KERNEL_IN

typedef enum _JOBOBJECTINFOCLASS 
{
    JobObjectBasicAccountingInformation = 1,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,  // deprecated
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    JobObjectGroupInformation,
    MaxJobObjectInfoClass

} JOBOBJECTINFOCLASS;

#endif

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationJobObject(
	__in HANDLE JobHandle,
	__in JOBOBJECTINFOCLASS JobInformationClass,
	__out PVOID JobInformation,
	__in ULONG JobInformationLength,
	__out_opt PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetInformationJobObject(
	__in HANDLE JobHandle,
	__in JOBOBJECTINFOCLASS JobInformationClass,
	__in PVOID JobInformation,
	__in ULONG JobInformationLength
    );


/* Tokens */

NTOSAPI
NT_STATUS
NTAPI
NtCreateToken(
    __out PHANDLE TokenHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in TOKEN_TYPE Type,
    __in PLUID AuthenticationId,
    __in PLARGE_INTEGER ExpirationTime,
    __in PTOKEN_USER User,
    __in PTOKEN_GROUPS Groups,
    __in PTOKEN_PRIVILEGES Privileges,
    __in PTOKEN_OWNER Owner,
    __in PTOKEN_PRIMARY_GROUP PrimaryGroup,
    __in PTOKEN_DEFAULT_DACL DefaultDacl,
    __in PTOKEN_SOURCE Source
    );

NTOSAPI
NT_STATUS
NTAPI
ZwOpenProcessToken(
    __in HANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __out PHANDLE TokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwOpenThreadToken(
    __in HANDLE ThreadHandle,
    __in ACCESS_MASK DesiredAccess,
    __in BOOLEAN OpenAsSelf,
    __out PHANDLE TokenHandle
    );

#ifndef _KERNEL_IN
NTOSAPI
NT_STATUS
NTAPI
NtOpenProcessToken(
    __in HANDLE ProcessHandle,
    __in ACCESS_MASK DesiredAccess,
    __out PHANDLE TokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtOpenThreadToken(
    __in HANDLE ThreadHandle,
    __in ACCESS_MASK DesiredAccess,
    __in BOOLEAN OpenAsSelf,
    __out PHANDLE TokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
ZwDuplicateToken(
    __in HANDLE ExistingTokenHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in BOOLEAN EffectiveOnly,
    __in TOKEN_TYPE TokenType,
    __out PHANDLE NewTokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtDuplicateToken(
    __in HANDLE ExistingTokenHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in BOOLEAN EffectiveOnly,
    __in TOKEN_TYPE TokenType,
    __out PHANDLE NewTokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtFilterToken(
	__in HANDLE ExistingTokenHandle,
	__in ULONG Flags,
	__in PTOKEN_GROUPS SidsToDisable,
	__in PTOKEN_PRIVILEGES PrivilegesToDelete,
	__in PTOKEN_GROUPS SidsToRestricted,
	__out PHANDLE NewTokenHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtAdjustPrivilegesToken(
    __in HANDLE TokenHandle,
    __in BOOLEAN DisableAllPrivileges,
    __in PTOKEN_PRIVILEGES NewState,
    __in ULONG BufferLength,
    __out_opt PTOKEN_PRIVILEGES PreviousState,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtAdjustPrivilegesToken(
    __in HANDLE TokenHandle,
    __in BOOLEAN DisableAllPrivileges,
    __in PTOKEN_PRIVILEGES NewState,
    __in ULONG BufferLength,
    __out_opt PTOKEN_PRIVILEGES PreviousState,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtAdjustGroupsToken(
	__in HANDLE TokenHandle,
	__in BOOLEAN ResetToDefault,
	__in PTOKEN_GROUPS NewState,
	__in ULONG BufferLength,
	__out_opt PTOKEN_GROUPS PreviousState,
	__out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationToken(
    __in HANDLE TokenHandle,
    __in TOKEN_INFORMATION_CLASS TokenInformationClass,
    __out PVOID TokenInformation,
    __in ULONG TokenInformationLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQueryInformationToken(
    __in HANDLE TokenHandle,
    __in TOKEN_INFORMATION_CLASS TokenInformationClass,
    __out PVOID TokenInformation,
    __in ULONG TokenInformationLength,
    __out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetInformationToken(
	__in HANDLE TokenHandle,
	__in TOKEN_INFORMATION_CLASS TokenInformationClass,
	__in PVOID TokenInformation,
    __in ULONG TokenInformationLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwSetInformationToken(
	__in HANDLE TokenHandle,
	__in TOKEN_INFORMATION_CLASS TokenInformationClass,
	__in PVOID TokenInformation,
    __in ULONG TokenInformationLength
    );
#endif


/* Time */

NTOSAPI
NT_STATUS
NTAPI
NtQuerySystemTime(
    __out PLARGE_INTEGER CurrentTime
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetSystemTime(
    __in PLARGE_INTEGER NewTime,
    __out_opt PLARGE_INTEGER OldTime 
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryPerformanceCounter(
    __out PLARGE_INTEGER PerformanceCount,
    __out_opt PLARGE_INTEGER PerformanceFrequency 
    );

NTOSAPI
NT_STATUS
NTAPI
ZwQueryPerformanceCounter(
    __out PLARGE_INTEGER PerformanceCount,
    __out_opt PLARGE_INTEGER PerformanceFrequency 
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryTimerResolution(
	__out PULONG CoarsestResolution,
	__out PULONG FinestResolution,
	__out PULONG ActualResolution
    );

NTOSAPI
NT_STATUS
NTAPI
NtDelayExecution(
    __in BOOLEAN Alertable,
    __in PLARGE_INTEGER Interval
    );

NTOSAPI
NT_STATUS
NTAPI
NtYieldExecution(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtGetTickCount(
    VOID
    );

/* Execution profiling */

NTOSAPI
NT_STATUS
NTAPI
NtCreateProfile(
	__out PHANDLE ProfileHandle,
	__in HANDLE ProcessHandle,
	__in PVOID Base,
	__in ULONG Size,
	__in ULONG BucketShift,
	__in PULONG Buffer,
	__in ULONG BufferLength,
	__in KPROFILE_SOURCE Source,
	__in ULONG ProcessorMask
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetIntervalProfile(
    __in ULONG Interval,
    __in KPROFILE_SOURCE Source
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryIntervalProfile(
	__in KPROFILE_SOURCE Source,
	__out PULONG Interval
    );

NTOSAPI
NT_STATUS
NTAPI
NtStartProfile(
    __in HANDLE ProfileHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtStopProfile(
    __in HANDLE ProfileHandle
    );

/* Local Procedure Call (LPC) */

#define LPC_MESSAGE_BASE_SIZE	24

typedef enum _LPC_TYPE
{
    LPC_NEW_MESSAGE,
    LPC_REQUEST,
    LPC_REPLY,
    LPC_DATAGRAM,
    LPC_LOST_REPLY,
    LPC_PORT_CLOSED,
    LPC_CLIENT_DIED,
    LPC_EXCEPTION,
    LPC_DEBUG_EVENT,
    LPC_ERROR_EVENT,
    LPC_CONNECTION_REQUEST,
    LPC_CONNECTION_REFUSED,
    LPC_MAXIMUM

} LPC_TYPE;

typedef struct _PORT_MESSAGE
{
    union
    {
        struct
        {
            USHORT DataLength;          // Length of data following the header (bytes)
            USHORT TotalLength;         // Length of data + sizeof(PORT_MESSAGE)
        } s1;
        ULONG Length;
    } u1;

    union
    {
        struct
        {
            USHORT Type;
            USHORT DataInfoOffset;
        } s2;
        ULONG ZeroInit;
    } u2;

    union
    {
        CLIENT_ID ClientId;
        double DoNotUseThisField;     // Force quadword alignment
    };

    ULONG MessageId;                   // Identifier of the particular message instance

    union
    {
        ULONG_PTR ClientViewSize;       // Size of section created by the sender (__in bytes)
        ULONG CallbackId;              // 
    };

} PORT_MESSAGE, *PPORT_MESSAGE;

// Define structure for initializing shared memory on the caller's side of the port
//
typedef struct _PORT_VIEW 
{
    ULONG Length;                      // Size of this structure
    HANDLE SectionHandle;               // Handle to section object with SECTION_MAP_WRITE and SECTION_MAP_READ
    ULONG SectionOffset;               // The offset __in the section
    ULONG ViewSize;                    // The size of the view (__in bytes)
    PVOID ViewBase;                    // The base address of the view __in the creator
    PVOID ViewRemoteBase;              // The base address of the view __in the process connected to the port.

} PORT_VIEW, *PPORT_VIEW;

// Define structure for shared memory coming from remote side of the port
//
typedef struct _REMOTE_PORT_VIEW 
{
    ULONG Length;                       // Size of this structure
    ULONG ViewSize;                     // The size of the view (bytes)
    PVOID ViewBase;                     // Base address of the view

} REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;

#ifndef InitializePortHeader
#define InitializeMessageHeader( ph, l, t ) {                        \
    (ph)->u1.s1.TotalLength    = (USHORT)(l);                        \
    (ph)->u1.s1.DataLength     = (USHORT)(l - sizeof(PORT_MESSAGE)); \
    (ph)->u2.s2.Type           = (USHORT)(t);                        \
    (ph)->u2.s2.DataInfoOffset = 0;                                  \
}
#endif

NTSYSAPI
NT_STATUS
NTAPI
NtCreatePort(
    __out PHANDLE PortHandle,                     
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG MaxConnectionInfoLength,
    __in ULONG MaxMessageLength,
    __in ULONG MaxPoolUsage
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwCreatePort(
    __out PHANDLE PortHandle,                     
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in ULONG MaxConnectionInfoLength,
    __in ULONG MaxMessageLength,
    __in ULONG MaxPoolUsage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtConnectPort(
    __out PHANDLE PortHandle,
    __in PUNICODE_STRING PortName,
    __in PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    __inout_opt PPORT_VIEW ClientView,
    __out_opt PREMOTE_PORT_VIEW ServerView,
    __out_opt PULONG MaxMessageLength,
    __inout_opt PVOID ConnectionInformation,
    __inout_opt PULONG ConnectionInformationLength
    );


NTSYSAPI
NT_STATUS
NTAPI
ZwConnectPort(
    __out PHANDLE PortHandle,
    __in PUNICODE_STRING PortName,
    __in PSECURITY_QUALITY_OF_SERVICE SecurityQos,
    __inout_opt PPORT_VIEW ClientView,
    __out_opt PREMOTE_PORT_VIEW ServerView,
    __out_opt PULONG MaxMessageLength,
    __inout_opt PVOID ConnectionInformation,
    __inout_opt PULONG ConnectionInformationLength
    );

NTSYSAPI
NT_STATUS
NTAPI
NtListenPort(
    __in HANDLE PortHandle,
    __out PPORT_MESSAGE RequestMessage
    );
 
NTSYSAPI
NT_STATUS
NTAPI
ZwListenPort(
    __in HANDLE PortHandle,
    __out PPORT_MESSAGE RequestMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtAcceptConnectPort(
    __out PHANDLE PortHandle,
    __in_opt PVOID PortContext,
    __in PPORT_MESSAGE ConnectionRequest,
    __in BOOLEAN AcceptConnection,
    __inout_opt PPORT_VIEW ServerView,
    __out_opt PREMOTE_PORT_VIEW ClientView
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwAcceptConnectPort(
    __out PHANDLE PortHandle,
    __in_opt PVOID PortContext,
    __in PPORT_MESSAGE ConnectionRequest,
    __in BOOLEAN AcceptConnection,
    __inout_opt PPORT_VIEW ServerView,
    __out_opt PREMOTE_PORT_VIEW ClientView
    );

NTSYSAPI
NT_STATUS
NTAPI
NtCompleteConnectPort(
    __in HANDLE PortHandle
    );


NTSYSAPI
NT_STATUS
NTAPI
ZwCompleteConnectPort(
    __in HANDLE PortHandle
    );

NTSYSAPI
NT_STATUS
NTAPI
NtRequestPort (
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE RequestMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwRequestPort (
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE RequestMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtRequestWaitReplyPort(
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE RequestMessage,
    __out PPORT_MESSAGE ReplyMessage
    );


NTSYSAPI
NT_STATUS
NTAPI
ZwRequestWaitReplyPort(
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE RequestMessage,
    __out PPORT_MESSAGE ReplyMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtReplyPort(
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE ReplyMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwReplyPort(
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE ReplyMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtReplyWaitReplyPort(
    __in HANDLE PortHandle,
    __in __out PPORT_MESSAGE ReplyMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwReplyWaitReplyPort(
    __in HANDLE PortHandle,
    __in __out PPORT_MESSAGE ReplyMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
NtReplyWaitReceivePort(
    __in HANDLE PortHandle,
    __out_opt PVOID *PortContext,
    __in_opt PPORT_MESSAGE ReplyMessage,
    __out PPORT_MESSAGE ReceiveMessage
    );

NTSYSAPI
NT_STATUS
NTAPI
ZwReplyWaitReceivePort(
    __in HANDLE PortHandle,
    __out_opt PVOID *PortContext,
    __in_opt PPORT_MESSAGE ReplyMessage,
    __out PPORT_MESSAGE ReceiveMessage
    );


typedef enum _PORT_INFORMATION_CLASS {
    PortBasicInformation
} PORT_INFORMATION_CLASS;

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationPort(
	__in HANDLE PortHandle,
	__in PORT_INFORMATION_CLASS PortInformationClass,
	__out PVOID PortInformation,
	__in ULONG PortInformationLength,
    __out_opt PULONG ReturnLength 
    );

NTOSAPI
NT_STATUS
NTAPI
NtImpersonateClientOfPort(
    __in HANDLE PortHandle,
    __in PPORT_MESSAGE Message
    );


/* Files */

//
// Define the create disposition values
//

#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

NTOSAPI
NT_STATUS
NTAPI
NtDeleteFile(
    __in POBJECT_ATTRIBUTES ObjectAttributes
    );

#ifndef _KERNEL_IN

// Define the create/open option flags
//

#define FILE_DIRECTORY_FILE                     0x00000001
#define FILE_WRITE_THROUGH                      0x00000002
#define FILE_SEQUENTIAL_ONLY                    0x00000004
#define FILE_NO_INTERMEDIATE_BUFFERING          0x00000008

#define FILE_SYNCHRONOUS_IO_ALERT               0x00000010
#define FILE_SYNCHRONOUS_IO_NONALERT            0x00000020
#define FILE_NON_DIRECTORY_FILE                 0x00000040
#define FILE_CREATE_TREE_CONNECTION             0x00000080

#define FILE_COMPLETE_IF_OPLOCKED               0x00000100
#define FILE_NO_EA_KNOWLEDGE                    0x00000200
#define FILE_OPEN_REMOTE_INSTANCE               0x00000400
#define FILE_RANDOM_ACCESS                      0x00000800

#define FILE_DELETE_ON_CLOSE                    0x00001000
#define FILE_OPEN_BY_FILE_ID                    0x00002000
#define FILE_OPEN_FOR_BACKUP_INTENT             0x00004000
#define FILE_NO_COMPRESSION                     0x00008000

#if (NTDDI_VERSION >= NTDDI_WIN7)
#define FILE_OPEN_REQUIRING_OPLOCK              0x00010000
#define FILE_DISALLOW_EXCLUSIVE                 0x00020000
#endif /* NTDDI_VERSION >= NTDDI_WIN7 */

#define FILE_RESERVE_OPFILTER                   0x00100000
#define FILE_OPEN_REPARSE_POINT                 0x00200000
#define FILE_OPEN_NO_RECALL                     0x00400000
#define FILE_OPEN_FOR_FREE_SPACE_QUERY          0x00800000


#define FILE_VALID_OPTION_FLAGS                 0x00ffffff
#define FILE_VALID_PIPE_OPTION_FLAGS            0x00000032
#define FILE_VALID_MAILSLOT_OPTION_FLAGS        0x00000032
#define FILE_VALID_SET_FLAGS                    0x00000036

//
// Define the I/O Status information return values for NtCreateFile/NtOpenFile
//

#define FILE_SUPERSEDED                 0x00000000
#define FILE_OPENED                     0x00000001
#define FILE_CREATED                    0x00000002
#define FILE_OVERWRITTEN                0x00000003
#define FILE_EXISTS                     0x00000004
#define FILE_DOES_NOT_EXIST             0x00000005

NTOSAPI
NT_STATUS
NTAPI 
NtCreateFile(
	__out PHANDLE FileHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_ATTRIBUTES ObjectAttributes,
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in_opt PLARGE_INTEGER AllocationSize,
	__in ULONG FileAttributes,
	__in ULONG ShareAccess,
	__in ULONG CreateDisposition,
	__in ULONG CreateOptions,
	__in_opt PVOID EaBuffer,
	__in ULONG EaLength
    );

NTOSAPI
NT_STATUS
NTAPI
ZwDeleteFile(
    __in POBJECT_ATTRIBUTES ObjectAttributes
    );

NT_STATUS
NTAPI
NtOpenFile(
    __out PHANDLE FileHandle,
    __in ACCESS_MASK DesiredAccess,
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG ShareAccess,
    __in ULONG OpenOptions
    );

NT_STATUS
NTAPI
NtDeviceIoControlFile (
    __in HANDLE FileHandle,
    __in_opt HANDLE Event,
    __in_opt PIO_APC_ROUTINE ApcRoutine,
    __in_opt PVOID ApcContext,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG IoControlCode,
    __in_bcount_opt(InputBufferLength) PVOID InputBuffer,
    __in ULONG InputBufferLength,
    __out_bcount_opt(OutputBufferLength) PVOID OutputBuffer,
    __in ULONG OutputBufferLength
    );

// NT_STATUS 
// NtFsControlFile(
//     __in HANDLE FileHandle,
//     __in_opt HANDLE Event,
//     __in_opt PIO_APC_ROUTINE ApcRoutine,
//     __in_opt PVOID ApcContext,
//     __out PIO_STATUS_BLOCK IoStatusBlock,
//     __in ULONG FsControlCode,
//     __in_opt PVOID InputBuffer,
//     __in ULONG InputBufferLength,
//     __out_opt PVOID OutputBuffer,
//     __in ULONG OutputBufferLength
//     );

#endif

typedef
NT_STATUS
(NTAPI* _NtDeviceIoControlFile)(
    __in HANDLE FileHandle,
    __in_opt HANDLE Event,
    __in_opt PIO_APC_ROUTINE ApcRoutine,
    __in_opt PVOID ApcContext,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG IoControlCode,
    __in_bcount_opt(InputBufferLength) PVOID InputBuffer,
    __in ULONG InputBufferLength,
    __out_bcount_opt(OutputBufferLength) PVOID OutputBuffer,
    __in ULONG OutputBufferLength
    );

typedef
NT_STATUS
(NTAPI* _NtFsControlFile)(
    __in HANDLE FileHandle,
    __in_opt HANDLE Event,
    __in_opt PIO_APC_ROUTINE ApcRoutine,
    __in_opt PVOID ApcContext,
    __out PIO_STATUS_BLOCK IoStatusBlock,
    __in ULONG FsControlCode,
    __in_opt PVOID InputBuffer,
    __in ULONG InputBufferLength,
    __out_opt PVOID OutputBuffer,
    __in ULONG OutputBufferLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtFlushBuffersFile(
	__in HANDLE FileHandle,
	__out PIO_STATUS_BLOCK IoStatusBlock
    );

NTOSAPI
NT_STATUS
NTAPI
NtCancelIoFile(
	__in HANDLE FileHandle,
	__out PIO_STATUS_BLOCK IoStatusBlock
    );

NTOSAPI
NT_STATUS
NTAPI
NtReadFileScatter(
	__in HANDLE FileHandle,
	__in_opt HANDLE Event,
	__in_opt PIO_APC_ROUTINE ApcRoutine,
	__in_opt PVOID ApcContext,
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in PFILE_SEGMENT_ELEMENT Buffer,
	__in ULONG Length,
	__in_opt PLARGE_INTEGER ByteOffset,
	__in_opt PULONG Key 
    );

NTOSAPI
NT_STATUS
NTAPI
NtWriteFileGather(
	__in HANDLE FileHandle,
	__in_opt HANDLE Event,
	__in_opt PIO_APC_ROUTINE ApcRoutine,
	__in_opt PVOID ApcContext,
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in PFILE_SEGMENT_ELEMENT Buffer,
	__in ULONG Length,
	__in_opt PLARGE_INTEGER ByteOffset,
	__in_opt PULONG Key 
    );


/* Registry keys */

NTOSAPI
NT_STATUS
NTAPI
NtSaveKey(
	__in HANDLE KeyHandle,
	__in HANDLE FileHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtSaveMergedKeys(
	__in HANDLE KeyHandle1,
	__in HANDLE KeyHandle2,
	__in HANDLE FileHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtRestoreKey(
    __in HANDLE KeyHandle,
    __in HANDLE FileHandle,
    __in ULONG Flags
    );

NTOSAPI
NT_STATUS
NTAPI
NtLoadKey(
    __in POBJECT_ATTRIBUTES KeyObjectAttributes,
    __in POBJECT_ATTRIBUTES FileObjectAttributes
    );

NTOSAPI
NT_STATUS
NTAPI
NtLoadKey2(
	__in POBJECT_ATTRIBUTES KeyObjectAttributes,
	__in POBJECT_ATTRIBUTES FileObjectAttributes,
	__in ULONG Flags
    );

NTOSAPI
NT_STATUS
NTAPI
NtUnloadKey(
    __in POBJECT_ATTRIBUTES KeyObjectAttributes
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryOpenSubKeys(
	__in POBJECT_ATTRIBUTES KeyObjectAttributes,
	__out PULONG NumberOfKeys
    );

NTOSAPI
NT_STATUS
NTAPI
NtReplaceKey(
	__in POBJECT_ATTRIBUTES NewFileObjectAttributes,
	__in HANDLE KeyHandle,
	__in POBJECT_ATTRIBUTES OldFileObjectAttributes
    );

#ifndef _KERNEL_IN
typedef enum _KEY_SET_INFORMATION_CLASS 
{
    KeyLastWriteTimeInformation

} KEY_SET_INFORMATION_CLASS;

typedef struct _KEY_NAME_INFORMATION 
{
    ULONG NameLength;
    WCHAR Name[1];

} KEY_NAME_INFORMATION, *PKEY_NAME_INFORMATION;
#endif

NTOSAPI
NT_STATUS
NTAPI
NtSetInformationKey(
	__in HANDLE KeyHandle,
	__in KEY_SET_INFORMATION_CLASS KeyInformationClass,
	__in PVOID KeyInformation,
	__in ULONG KeyInformationLength
    );

typedef struct _KEY_LAST_WRITE_TIME_INFORMATION
{
    LARGE_INTEGER LastWriteTime;

} KEY_LAST_WRITE_TIME_INFORMATION, *PKEY_LAST_WRITE_TIME_INFORMATION;

NTOSAPI
NT_STATUS
NTAPI
NtNotifyChangeKey(
	__in HANDLE KeyHandle,
	__in_opt HANDLE EventHandle,
	__in_opt PIO_APC_ROUTINE ApcRoutine,
	__in_opt PVOID ApcContext,
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in ULONG NotifyFilter,
	__in BOOLEAN WatchSubtree,
	__in PVOID Buffer,
	__in ULONG BufferLength,
	__in BOOLEAN Asynchronous
    );

/* ZwNotifyChangeMultipleKeys.Flags constants */
#define REG_MONITOR_SINGLE_KEY            0x00
#define REG_MONITOR_SECOND_KEY            0x01

NTOSAPI
NT_STATUS
NTAPI
NtNotifyChangeMultipleKeys(
	__in HANDLE KeyHandle,
	__in ULONG Flags,
	__in POBJECT_ATTRIBUTES KeyObjectAttributes,
	__in_opt HANDLE EventHandle,
	__in_opt PIO_APC_ROUTINE ApcRoutine,
	__in_opt PVOID ApcContext,
	__out PIO_STATUS_BLOCK IoStatusBlock,
	__in ULONG NotifyFilter,
	__in BOOLEAN WatchSubtree,
	__in PVOID Buffer,
	__in ULONG BufferLength,
	__in BOOLEAN Asynchronous
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryMultipleValueKey(
	__in HANDLE KeyHandle,
	__in __out  PKEY_VALUE_ENTRY ValueList,
	__in ULONG NumberOfValues,
	__out PVOID Buffer,
	__in __out PULONG Length,
	__out PULONG ReturnLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtInitializeRegistry(
    __in BOOLEAN Setup
    );


/* Security and auditing */

#ifndef _KERNEL_IN
NTOSAPI
NT_STATUS
NTAPI
NtPrivilegeCheck(
	__in HANDLE TokenHandle,
	__in PPRIVILEGE_SET RequiredPrivileges,
	__out PBOOLEAN Result
    );

NTOSAPI
NT_STATUS
NTAPI
NtPrivilegeObjectAuditAlarm(
	__in PUNICODE_STRING SubsystemName,
	__in PVOID HandleId,
	__in HANDLE TokenHandle,
	__in ACCESS_MASK DesiredAccess,
	__in PPRIVILEGE_SET Privileges,
	__in BOOLEAN AccessGranted
    );
#endif

NTOSAPI
NT_STATUS
NTAPI
ZwPrivilegeObjectAuditAlarm(
	__in PUNICODE_STRING SubsystemName,
	__in PVOID HandleId,
	__in HANDLE TokenHandle,
	__in ACCESS_MASK DesiredAccess,
	__in PPRIVILEGE_SET Privileges,
	__in BOOLEAN AccessGranted
    );

NTOSAPI
NT_STATUS
NTAPI
NtAccessCheck(
	__in PSECURITY_DESCRIPTOR SecurityDescriptor,
	__in HANDLE TokenHandle,
	__in ACCESS_MASK DesiredAccess,
	__in PGENERIC_MAPPING GenericMapping,
	__in PPRIVILEGE_SET PrivilegeSet,
	__in PULONG PrivilegeSetLength,
	__out PACCESS_MASK GrantedAccess,
	__out PBOOLEAN AccessStatus
    );

NTOSAPI
NT_STATUS
NTAPI
NtAccessCheckByType(
	__in PSECURITY_DESCRIPTOR SecurityDescriptor,
	__in PSID PrincipalSelfSid,
	__in HANDLE TokenHandle,
	__in ULONG DesiredAccess,
	__in POBJECT_TYPE_LIST ObjectTypeList,
	__in ULONG ObjectTypeListLength,
	__in PGENERIC_MAPPING GenericMapping,
	__in PPRIVILEGE_SET PrivilegeSet,
	__in PULONG PrivilegeSetLength,
	__out PACCESS_MASK GrantedAccess,
	__out PULONG AccessStatus
    );

NTOSAPI
NT_STATUS
NTAPI
NtAccessCheckByTypeResultList(
	__in PSECURITY_DESCRIPTOR SecurityDescriptor,
	__in PSID PrincipalSelfSid,
	__in HANDLE TokenHandle,
	__in ACCESS_MASK DesiredAccess,
	__in POBJECT_TYPE_LIST ObjectTypeList,
	__in ULONG ObjectTypeListLength,
	__in PGENERIC_MAPPING GenericMapping,
	__in PPRIVILEGE_SET PrivilegeSet,
	__in PULONG PrivilegeSetLength,
	__out PACCESS_MASK GrantedAccessList,
	__out PULONG AccessStatusList
    );

/* Plug and play and power management */

NTOSAPI
NT_STATUS
NTAPI
NtRequestWakeupLatency(
    __in LATENCY_TIME Latency
    );

NTOSAPI
NT_STATUS
NTAPI
NtRequestDeviceWakeup(
    __in HANDLE DeviceHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtCancelDeviceWakeupRequest(
    __in HANDLE DeviceHandle
    );

NTOSAPI
BOOLEAN
NTAPI
NtIsSystemResumeAutomatic(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetThreadExecutionState(
	__in EXECUTION_STATE ExecutionState,
	__out EXECUTION_STATE* PreviousExecutionState
    );

NTOSAPI
NT_STATUS
NTAPI
NtGetDevicePowerState(
    __in HANDLE DeviceHandle,
    __out PDEVICE_POWER_STATE DevicePowerState
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetSystemPowerState(
	__in POWER_ACTION SystemAction,
	__in SYSTEM_POWER_STATE MinSystemState,
	__in ULONG Flags
    );

NTOSAPI
NT_STATUS
NTAPI
NtInitiatePowerAction(
	__in POWER_ACTION SystemAction,
	__in SYSTEM_POWER_STATE MinSystemState,
	__in ULONG Flags,
	__in BOOLEAN Asynchronous
    );

NTOSAPI
NT_STATUS
NTAPI
NtPowerInformation(
	__in POWER_INFORMATION_LEVEL PowerInformationLevel,
	__in_opt PVOID InputBuffer,
	__in ULONG InputBufferLength,
	__out_opt PVOID OutputBuffer,
	__in ULONG OutputBufferLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtPlugPlayControl(
    __in ULONG ControlCode,
    __in __out PVOID Buffer,
    __in ULONG BufferLength
    );

NTOSAPI
NT_STATUS
NTAPI
NtGetPlugPlayEvent(
	__in ULONG Reserved1,
	__in ULONG Reserved2,
	__out PVOID Buffer,
	__in ULONG BufferLength
    );


/* Miscellany */

NTOSAPI
NT_STATUS
NTAPI
NtRaiseException(
    __in PEXCEPTION_RECORD ExceptionRecord,
    __in PCONTEXT Context,
    __in BOOLEAN SearchFrames
    );

NTOSAPI
NT_STATUS
NTAPI
NtContinue(
    __in PCONTEXT Context,
    __in BOOLEAN TestAlert
    );

NTOSAPI
NT_STATUS
NTAPI
NtW32Call(
	__in ULONG RoutineIndex,
	__in PVOID Argument,
	__in ULONG ArgumentLength,
	__out_opt PVOID *Result,
	__out_opt PULONG ResultLength 
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetLowWaitHighThread(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetHighWaitLowThread(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtLoadDriver(
    __in PUNICODE_STRING DriverServiceName
    );

NTOSAPI
NT_STATUS
NTAPI
NtUnloadDriver(
    __in PUNICODE_STRING DriverServiceName
    );

NTOSAPI
NT_STATUS
NTAPI
NtFlushInstructionCache(
	__in HANDLE ProcessHandle,
	__in_opt PVOID BaseAddress,
	__in ULONG FlushSize
    );

NTOSAPI
NT_STATUS
NTAPI
NtFlushWriteBuffer(
    VOID
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryDefaultLocale(
	__in BOOLEAN ThreadOrSystem,
	__out PLCID Locale
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetDefaultLocale(
    __in BOOLEAN ThreadOrSystem,
    __in LCID Locale
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryDefaultUILanguage(
    __out PLANGID LanguageId
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetDefaultUILanguage(
    __in LANGID LanguageId
    );

NTOSAPI
NT_STATUS
NTAPI
NtQueryInstallUILanguage(
    __out PLANGID LanguageId
    );

NTOSAPI
NT_STATUS
NTAPI
NtAllocateLocallyUniqueId(
    __out PLUID Luid
    );

NTOSAPI
NT_STATUS
NTAPI
NtAllocateUuids(
    __out PLARGE_INTEGER UuidLastTimeAllocated,
    __out PULONG UuidDeltaTime,
    __out PULONG UuidSequenceNumber,
    __out PUCHAR UuidSeed
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetUuidSeed(
    __in PUCHAR UuidSeed
    );

typedef enum _HARDERROR_RESPONSE_OPTION
{
	OptionAbortRetryIgnore,
	OptionOk,
	OptionOkCancel,
	OptionRetryCancel,
	OptionYesNo,
	OptionYesNoCancel,
	OptionShutdownSystem

} HARDERROR_RESPONSE_OPTION, *PHARDERROR_RESPONSE_OPTION;

typedef enum _HARDERROR_RESPONSE 
{
	ResponseReturnToCaller,
	ResponseNotHandled,
	ResponseAbort,
	ResponseCancel,
	ResponseIgnore,
	ResponseNo,
	ResponseOk,
	ResponseRetry,
	ResponseYes

} HARDERROR_RESPONSE, *PHARDERROR_RESPONSE;

NTOSAPI
NT_STATUS
NTAPI
NtRaiseHardError(
	__in ULONG Status,
	__in ULONG NumberOfArguments,
	__in ULONG StringArgumentsMask,
	__in PULONG Arguments,
	__in HARDERROR_RESPONSE_OPTION ResponseOption,
	__out PHARDERROR_RESPONSE Response
    );

NTOSAPI
NT_STATUS
NTAPI
NtSetDefaultHardErrorPort(
    __in HANDLE PortHandle
    );

NTOSAPI
NT_STATUS
NTAPI
NtDisplayString(
    __in PUNICODE_STRING String
    );

NTOSAPI
NT_STATUS
NTAPI
NtCreatePagingFile(
    __in PUNICODE_STRING FileName,
    __in PULARGE_INTEGER InitialSize,
    __in PULARGE_INTEGER MaximumSize,
    __in ULONG Reserved
    );

#define DIM(_array)     (sizeof(_array) / sizeof(_array[0]))

#ifdef  _UNICODE
#define SUFFIX  "W"
#else
#define SUFFIX  "A"
#endif

#define BACK_SLASH _T('\\')

// These are __out Disposition values.
//
#define RTL_NT_PATH_NAME_TO_DOS_PATH_NAME_AMBIGUOUS   (0x00000001)
#define RTL_NT_PATH_NAME_TO_DOS_PATH_NAME_UNC         (0x00000002)
#define RTL_NT_PATH_NAME_TO_DOS_PATH_NAME_DRIVE       (0x00000003)
#define RTL_NT_PATH_NAME_TO_DOS_PATH_NAME_ALREADY_DOS (0x00000004)

typedef struct _RTL_BUFFER 
{
    PUCHAR Buffer;
    PUCHAR StaticBuffer;
    SIZE_T Size;
    SIZE_T StaticSize;
    SIZE_T ReservedForAllocatedSize; // for future doubling
    PVOID ReservedForIMalloc; // for future pluggable growth

} RTL_BUFFER, *PRTL_BUFFER;

typedef struct _RTL_UNICODE_STRING_BUFFER 
{
    UNICODE_STRING String;
    RTL_BUFFER ByteBuffer;
    UCHAR MinimumStaticBufferForTerminalNul[sizeof(WCHAR)];

} RTL_UNICODE_STRING_BUFFER, *PRTL_UNICODE_STRING_BUFFER;

NTSYSAPI
NT_STATUS
NTAPI
RtlNtPathNameToDosPathName(
    __in ULONG Flags,
    __inout PRTL_UNICODE_STRING_BUFFER Path,
    __out_opt PULONG Disposition,
    __inout_opt PWSTR* FilePart
    );


typedef USHORT RTL_ATOM, *PRTL_ATOM;

NTOSAPI
NT_STATUS
NTAPI
NtAddAtom(
    __in PWSTR AtomName,
    __in ULONG AtomNameLength,
    __out PRTL_ATOM Atom
    );

NTOSAPI
NT_STATUS
NTAPI
NtFindAtom(
    __in PWSTR AtomName,
    __in ULONG AtomNameLength,
    __out PRTL_ATOM Atom
    );

NTOSAPI
NT_STATUS
NTAPI
NtDeleteAtom(
    __in RTL_ATOM Atom
    );

typedef enum _ATOM_INFORMATION_CLASS
{
	AtomBasicInformation,
	AtomListInformation

} ATOM_INFORMATION_CLASS;

NTOSAPI
NT_STATUS
NTAPI
NtQueryInformationAtom(
    __in RTL_ATOM Atom,
    __in ATOM_INFORMATION_CLASS AtomInformationClass,
    __out PVOID AtomInformation,
    __in ULONG AtomInformationLength,
    __out_opt PULONG ReturnLength 
    );

typedef struct _ATOM_BASIC_INFORMATION 
{
	USHORT  ReferenceCount;
	USHORT  Pinned;
	USHORT  NameLength;
	WCHAR  Name[1];

} ATOM_BASIC_INFORMATION, *PATOM_BASIC_INFORMATION;

typedef struct _ATOM_LIST_INFORMATION 
{
    ULONG  NumberOfAtoms;
    USHORT Atoms[1];

} ATOM_LIST_INFORMATION, *PATOM_LIST_INFORMATION;

#ifdef _KERNEL_IN

#ifndef _LDT_ENTRY_DEFINED
#define _LDT_ENTRY_DEFINED

typedef struct _LDT_ENTRY 
{
    USHORT    LimitLow;
    USHORT    BaseLow;
    union {
        struct {
            UINT8    BaseMid;
            UINT8    Flags1;     // Declare as bytes to avoid alignment
            UINT8    Flags2;     // Problems.
            UINT8    BaseHi;
        } Bytes;
        struct {
            ULONG   BaseMid : 8;
            ULONG   Type : 5;
            ULONG   Dpl : 2;
            ULONG   Pres : 1;
            ULONG   LimitHi : 4;
            ULONG   Sys : 1;
            ULONG   Reserved_0 : 1;
            ULONG   Default_Big : 1;
            ULONG   Granularity : 1;
            ULONG   BaseHi : 8;
        } Bits;
    } HighWord;
} LDT_ENTRY, *PLDT_ENTRY;

#endif
#endif

NTOSAPI
NT_STATUS
NTAPI
NtSetLdtEntries(
	__in ULONG Selector1,
	__in LDT_ENTRY LdtEntry1,
	__in ULONG Selector2,
	__in LDT_ENTRY LdtEntry2
    );

NTOSAPI
NT_STATUS
NTAPI
NtVdmControl(
  __in ULONG ControlCode,
  __in PVOID ControlData
  );

#ifndef _KERNEL_IN

NTSYSAPI
VOID
NTAPI
RtlInitUnicodeString(
    __out PUNICODE_STRING DestinationString,
    __in PCWSTR SourceString
    );

NTSYSAPI
VOID
NTAPI
RtlInitString(
    PSTRING DestinationString,
    PCSZ SourceString
    );

NTSYSAPI
VOID
NTAPI
RtlInitAnsiString(
    PANSI_STRING DestinationString,
    PCSZ SourceString
    );

NTSYSAPI
VOID
NTAPI
RtlInitUnicodeString(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString
    );

#define RtlInitEmptyUnicodeString(_ucStr,_buf,_bufSize) \
    ((_ucStr)->Buffer = (_buf), \
     (_ucStr)->Length = 0, \
     (_ucStr)->MaximumLength = (USHORT)(_bufSize))

NTSYSAPI
LONG
NTAPI
RtlCompareUnicodeString(
    PCUNICODE_STRING String1,
    PCUNICODE_STRING String2,
    BOOLEAN CaseInSensitive
    );

NTSYSAPI
BOOLEAN
NTAPI
RtlEqualUnicodeString(
    const UNICODE_STRING *String1,
    const UNICODE_STRING *String2,
    BOOLEAN CaseInSensitive
    );

#define HASH_STRING_ALGORITHM_DEFAULT   (0)
#define HASH_STRING_ALGORITHM_X65599    (1)
#define HASH_STRING_ALGORITHM_INVALID   (0xffffffff)

NTSYSAPI
VOID
NTAPI
RtlCopyUnicodeString(
    PUNICODE_STRING DestinationString,
    PCUNICODE_STRING SourceString
    );

NTSYSAPI
NT_STATUS
NTAPI
RtlAnsiStringToUnicodeString(
    PUNICODE_STRING DestinationString,
    PCANSI_STRING SourceString,
    BOOLEAN AllocateDestinationString
    );


NTSYSAPI
NT_STATUS
NTAPI
RtlUnicodeStringToAnsiString(
    PANSI_STRING DestinationString,
    PCUNICODE_STRING SourceString,
    BOOLEAN AllocateDestinationString
    );

NTSYSAPI
NT_STATUS
NTAPI
RtlAppendUnicodeStringToString (
    PUNICODE_STRING Destination,
    PCUNICODE_STRING Source
    );

NTSYSAPI
NT_STATUS
NTAPI
RtlAppendUnicodeToString (
    PUNICODE_STRING Destination,
    PCWSTR Source
    );

NTSYSAPI
NT_STATUS
NTAPI
RtlHashUnicodeString(
    __in const UNICODE_STRING *String,
    __in BOOLEAN CaseInSensitive,
    __in ULONG HashAlgorithm,
    __out PULONG HashValue
    );

NTSYSAPI
VOID
NTAPI
RtlFreeUnicodeString(
    PUNICODE_STRING UnicodeString
    );

NTSYSAPI
VOID
NTAPI
RtlFreeAnsiString(
    PANSI_STRING AnsiString
    );

NTSYSAPI
ULONG
NTAPI
RtlxUnicodeStringToAnsiSize(
    PCUNICODE_STRING UnicodeString
    );

NTSYSAPI
ULONG 
WINAPI 
RtlNtStatusToDosError(
    __in NT_STATUS Status
    );

NTSYSAPI
NT_STATUS
NTAPI
RtlGetVersion(
    __inout PRTL_OSVERSIONINFOW lpVersionInformation
    );

#endif

//Privilege defination

#define SE_MIN_WELL_KNOWN_PRIVILEGE       (2L)
#define SE_CREATE_TOKEN_PRIVILEGE         (2L)
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE   (3L)
#define SE_LOCK_MEMORY_PRIVILEGE          (4L)
#define SE_INCREASE_QUOTA_PRIVILEGE       (5L)

// end_wdm
//
// Unsolicited Input is obsolete and unused.
//

#define SE_UNSOLICITED_INPUT_PRIVILEGE    (6L)

// begin_wdm
#define SE_MACHINE_ACCOUNT_PRIVILEGE      (6L)
#define SE_TCB_PRIVILEGE                  (7L)
#define SE_SECURITY_PRIVILEGE             (8L)
#define SE_TAKE_OWNERSHIP_PRIVILEGE       (9L)
#define SE_LOAD_DRIVER_PRIVILEGE          (10L)
#define SE_SYSTEM_PROFILE_PRIVILEGE       (11L)
#define SE_SYSTEMTIME_PRIVILEGE           (12L)
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE  (13L)
#define SE_INC_BASE_PRIORITY_PRIVILEGE    (14L)
#define SE_CREATE_PAGEFILE_PRIVILEGE      (15L)
#define SE_CREATE_PERMANENT_PRIVILEGE     (16L)
#define SE_BACKUP_PRIVILEGE               (17L)
#define SE_RESTORE_PRIVILEGE              (18L)
#define SE_SHUTDOWN_PRIVILEGE             (19L)
#define SE_DEBUG_PRIVILEGE                (20L)
#define SE_AUDIT_PRIVILEGE                (21L)
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE   (22L)
#define SE_CHANGE_NOTIFY_PRIVILEGE        (23L)
#define SE_REMOTE_SHUTDOWN_PRIVILEGE      (24L)
#define SE_UNDOCK_PRIVILEGE               (25L)
#define SE_SYNC_AGENT_PRIVILEGE           (26L)
#define SE_ENABLE_DELEGATION_PRIVILEGE    (27L)
#define SE_MANAGE_VOLUME_PRIVILEGE        (28L)
#define SE_IMPERSONATE_PRIVILEGE          (29L)
#define SE_CREATE_GLOBAL_PRIVILEGE        (30L)

#ifndef _KERNEL_IN
#define SE_MAX_WELL_KNOWN_PRIVILEGE       (SE_CREATE_GLOBAL_PRIVILEGE)
#endif

NTSYSAPI
NT_STATUS
NTAPI
RtlAdjustPrivilege(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN Client,
    PBOOLEAN WasEnabled
    );

//////////////////////////////////////////////////////////////////////////

#ifdef _KERNEL_IN

/* APCs */

// Enumerated kernel types
//
// Kernel object types.
//
//  N.B. There are really two types of event objects; NotificationEvent and
//       SynchronizationEvent. The type value for a notification event is 0,
//       and that for a synchronization event 1.
//
//  N.B. There are two types of new timer objects; NotificationTimer and
//       SynchronizationTimer. The type value for a notification timer is
//       8, and that for a synchronization timer is 9. These values are
//       very carefully chosen so that the dispatcher object type AND'ed
//       with 0x7 yields 0 or 1 for event objects and the timer objects.
//

#define DISPATCHER_OBJECT_TYPE_MASK 0x7

typedef enum _KOBJECTS {
    EventNotificationObject = 0,
    EventSynchronizationObject = 1,
    MutantObject = 2,
    ProcessObject = 3,
    QueueObject = 4,
    SemaphoreObject = 5,
    ThreadObject = 6,
    GateObject = 7,
    TimerNotificationObject = 8,
    TimerSynchronizationObject = 9,
    Spare2Object = 10,
    Spare3Object = 11,
    Spare4Object = 12,
    Spare5Object = 13,
    Spare6Object = 14,
    Spare7Object = 15,
    Spare8Object = 16,
    Spare9Object = 17,
    ApcObject,
    DpcObject,
    DeviceQueueObject,
    EventPairObject,
    InterruptObject,
    ProfileObject,
    ThreadedDpcObject,
    MaximumKernelObject
} KOBJECTS;

#define KOBJECT_LOCK_BIT 0x80
#define KOBJECT_LOCK_BIT_NUMBER 7
#define KOBJECT_TYPE_MASK 0x7f

C_ASSERT((MaximumKernelObject & KOBJECT_LOCK_BIT) == 0);

typedef 
enum _KAPC_ENVIRONMENT
{
    OriginalApcEnvironment,
    AttachedApcEnvironment,
    CurrentApcEnvironment,
    InsertApcEnvironment
} KAPC_ENVIRONMENT, *PKAPC_ENVIRONMENT;

NTKERNELAPI 
VOID 
NTAPI
KeInitializeApc(
    PKAPC Apc,
    PKTHREAD Thread,
    KAPC_ENVIRONMENT Environment,
    PKKERNEL_ROUTINE KernelRoutine,
    PKRUNDOWN_ROUTINE RundownRoutine,
    PKNORMAL_ROUTINE NormalRoutine,
    KPROCESSOR_MODE ProcessorMode,
    PVOID NormalContext
    );

NTKERNELAPI
BOOLEAN 
NTAPI
KeInsertQueueApc(
    PRKAPC Apc,
    PVOID SystemArgument1,
    PVOID SystemArgument2,
    KPRIORITY Increment
    );

//////////////////////////////////////////////////////////////////////////

#define PROCESS_TERMINATE (0x0001)
#define PROCESS_CREATE_THREAD (0x0002)
#define PROCESS_SET_SESSIONID (0x0004)
#define PROCESS_VM_OPERATION (0x0008)
#define PROCESS_VM_READ (0x0010)
#define PROCESS_VM_WRITE (0x0020)
#define PROCESS_DUP_HANDLE (0x0040)
#define PROCESS_CREATE_PROCESS (0x0080)
#define PROCESS_SET_QUOTA (0x0100)
#define PROCESS_SET_INFORMATION (0x0200)
#define PROCESS_QUERY_INFORMATION (0x0400)
#define PROCESS_SUSPEND_RESUME (0x0800)
#define PROCESS_QUERY_LIMITED_INFORMATION (0x1000)
#ifndef PROCESS_ALL_ACCESS
#define PROCESS_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xffff)
#endif

#define THREAD_TERMINATE (0x0001)
#define THREAD_SUSPEND_RESUME (0x0002)
#define THREAD_ALERT (0x0004)
#define THREAD_GET_CONTEXT (0x0008)
#define THREAD_SET_CONTEXT (0x0010)
#define THREAD_SET_INFORMATION (0x0020)
#define THREAD_QUERY_INFORMATION (0x0040)
#define THREAD_SET_THREAD_TOKEN (0x0080)
#define THREAD_IMPERSONATE (0x0100)
#define THREAD_DIRECT_IMPERSONATION (0x0200)
#ifndef THREAD_ALL_ACCESS
#define THREAD_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3ff)
#endif

#define MAX_STACK_DEPTH 64

#define RTL_WALK_USER_MODE_STACK 0x00000001
#define RTL_WALK_VALID_FLAGS 0x00000001

//////////////////////////////////////////////////////////////////////////

typedef 
struct _PROCESS_HANDLE
{
    HANDLE Handle;
    PVOID Object;
    ACCESS_MASK GrantedAccess;
    USHORT ObjectTypeIndex;
    USHORT Reserved1;
    ULONG HandleAttributes;
    ULONG Reserved2;

} PROCESS_HANDLE, *PPROCESS_HANDLE;

typedef 
struct _PROCESS_HANDLE_INFORMATION
{
    ULONG HandleCount;
    PROCESS_HANDLE Handles[1];

} PROCESS_HANDLE_INFORMATION, *PPROCESS_HANDLE_INFORMATION;

typedef struct _CAPTURE_BACKTRACE_THREAD_CONTEXT
{
    BOOLEAN Local;
    KAPC Apc;
    KEVENT CompletedEvent;
    ULONG FramesToSkip;
    ULONG FramesToCapture;
    PVOID *BackTrace;
    ULONG CapturedFrames;
    ULONG BackTraceHash;

} CAPTURE_BACKTRACE_THREAD_CONTEXT, *PCAPTURE_BACKTRACE_THREAD_CONTEXT;

typedef struct _EXIT_THREAD_CONTEXT
{
    KAPC Apc;
    KEVENT CompletedEvent;
    NTSTATUS ExitStatus;

} EXIT_THREAD_CONTEXT, *PEXIT_THREAD_CONTEXT;

//////////////////////////////////////////////////////////////////////////

typedef 
NTSTATUS
(NTAPI *_PsResumeProcess)(
    __in PEPROCESS Process
    );

typedef 
NTSTATUS
(NTAPI *_PsSuspendProcess)(
    __in PEPROCESS Process
    );

PVOID 
NTAPI
PsGetThreadWin32Thread(
    __in PETHREAD Thread
    );

NTSTATUS 
NTAPI 
PsLookupProcessThreadByCid(
    __in PCLIENT_ID ClientId,
    __out_opt PEPROCESS *Process,
    __out PETHREAD *Thread
    );

PPEB
NTAPI
PsGetProcessPeb( 
     __in PEPROCESS Process 
     );

//////////////////////////////////////////////////////////////////////////

#define OBJECT_TO_OBJECT_HEADER(o) \
    CONTAINING_RECORD((o), OBJECT_HEADER, Body)

#define OBJ_PROTECT_CLOSE 0x00000001L
#define OBJ_INHERIT 0x00000002L
#define OBJ_AUDIT_OBJECT_CLOSE 0x00000004L
#define OBJ_HANDLE_ATTRIBUTES (OBJ_PROTECT_CLOSE | OBJ_INHERIT | OBJ_AUDIT_OBJECT_CLOSE)

#define ObpDecodeGrantedAccess(Access) \
    ((Access) & ~ObpAccessProtectCloseBit)

#define ObpDecodeObject(Object) \
    ((PVOID)((ULONG_PTR)(Object) & ~OBJ_HANDLE_ATTRIBUTES))

#define ObpGetHandleAttributes(HandleTableEntry) \
    (((HandleTableEntry)->GrantedAccess & ObpAccessProtectCloseBit) ? \
    (((HandleTableEntry)->Value & OBJ_HANDLE_ATTRIBUTES) | OBJ_PROTECT_CLOSE) : \
    ((HandleTableEntry)->Value & (OBJ_INHERIT | OBJ_AUDIT_OBJECT_CLOSE)))

//////////////////////////////////////////////////////////////////////////

typedef struct _OBJECT_TYPE_INITIALIZER OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;

enum _OB_OPEN_REASON;

typedef struct _HANDLE_TABLE HANDLE_TABLE, *PHANDLE_TABLE;

typedef 
enum _OB_OPEN_REASON
{
    ObCreateHandle,
    ObOpenHandle,
    ObDuplicateHandle,
    ObInheritHandle,
    ObMaxOpenReason

} OB_OPEN_REASON, *POB_OPEN_REASON;

typedef 
struct _OBP_QUERY_PROCESS_HANDLES_DATA
{
    PVOID Buffer;
    ULONG BufferLength;
    ULONG CurrentIndex;
    NTSTATUS Status;

} OBP_QUERY_PROCESS_HANDLES_DATA, *POBP_QUERY_PROCESS_HANDLES_DATA;

typedef 
struct _OBP_SET_HANDLE_GRANTED_ACCESS_DATA
{
    HANDLE Handle;
    ACCESS_MASK GrantedAccess;

} OBP_SET_HANDLE_GRANTED_ACCESS_DATA, *POBP_SET_HANDLE_GRANTED_ACCESS_DATA;

typedef OBJECT_HANDLE_FLAG_INFORMATION \
    OBJECT_CREATE_INFORMATION, *POBJECT_CREATE_INFORMATION;

typedef 
struct _OBJECT_HEADER
{
    LONG PointerCount;
    union
    {
        LONG HandleCount;
        PVOID NextToFree;
    };
    POBJECT_TYPE Type;
    UCHAR NameInfoOffset;
    UCHAR HandleInfoOffset;
    UCHAR QuotaInfoOffset;
    UCHAR Flags;
    union
    {
        POBJECT_CREATE_INFORMATION ObjectCreateInfo;
        PVOID QuotaBlockCharged;
    };
    PVOID SecurityDescriptor;
    QUAD Body;

} OBJECT_HEADER, *POBJECT_HEADER;

typedef 
struct _HANDLE_TABLE_ENTRY
{
    union
    {
        PVOID Object;
        ULONG Value;
    };
    ULONG GrantedAccess;

} HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY;


//  Object attributes only for internal use
//

#define OBJ_KERNEL_EXCLUSIVE           0x00010000L
#define OBJ_VALID_PRIVATE_ATTRIBUTES   0x00010000L
#define OBJ_ALL_VALID_ATTRIBUTES (OBJ_VALID_PRIVATE_ATTRIBUTES | OBJ_VALID_ATTRIBUTES)

//////////////////////////////////////////////////////////////////////////

#define MAX_HANDLES (1<<24)

#define TABLE_PAGE_SIZE PAGE_SIZE

#define LOWLEVEL_COUNT (TABLE_PAGE_SIZE / sizeof(HANDLE_TABLE_ENTRY))
#define MIDLEVEL_COUNT (PAGE_SIZE / sizeof(PHANDLE_TABLE_ENTRY))
#define HIGHLEVEL_COUNT  MAX_HANDLES / (LOWLEVEL_COUNT * MIDLEVEL_COUNT)

#define LOWLEVEL_THRESHOLD LOWLEVEL_COUNT
#define MIDLEVEL_THRESHOLD (MIDLEVEL_COUNT * LOWLEVEL_COUNT)
#define HIGHLEVEL_THRESHOLD (MIDLEVEL_COUNT * MIDLEVEL_COUNT * LOWLEVEL_COUNT)

#define HIGHLEVEL_SIZE (HIGHLEVEL_COUNT * sizeof (PHANDLE_TABLE_ENTRY))

//////////////////////////////////////////////////////////////////////////

typedef 
BOOLEAN 
(*EX_ENUMERATE_HANDLE_ROUTINE)(
    __in PHANDLE_TABLE_ENTRY HandleTableEntry,
    __in HANDLE Handle,
    __in PVOID EnumParameter
    );

typedef
BOOLEAN
(NTAPI *_ExEnumHandleTable)(
    __in PHANDLE_TABLE HandleTable,
    __in EX_ENUMERATE_HANDLE_ROUTINE EnumHandleProcedure,
    __in PVOID EnumParameter,
    __out_opt PHANDLE Handle
    );

//////////////////////////////////////////////////////////////////////////

NTSTATUS 
NTAPI
ObCreateObjectType(
    __in PUNICODE_STRING TypeName,
    __in POBJECT_TYPE_INITIALIZER ObjectTypeInitializer,
    __in PSECURITY_DESCRIPTOR SecurityDescriptor,
    __out_opt POBJECT_TYPE *ObjectType
    );

NTSTATUS 
NTAPI
ObOpenObjectByName(
    __in POBJECT_ATTRIBUTES ObjectAttributes,
    __in POBJECT_TYPE ObjectType,
    __in KPROCESSOR_MODE PreviousMode,
    __in_opt PACCESS_STATE AccessState,
    __in_opt ACCESS_MASK DesiredAccess,
    __in_opt PVOID ParseContext,
    __out PHANDLE Handle
    );

NTSTATUS
NTAPI 
ObSetHandleAttributes(
    __in HANDLE Handle,
    __in struct _OBJECT_HANDLE_FLAG_INFORMATION *HandleFlags,
    __in KPROCESSOR_MODE PreviousMode
    );

NTSTATUS 
ObDuplicateObject(
    __in PEPROCESS SourceProcess,
    __in_opt PEPROCESS TargetProcess,
    __in HANDLE SourceHandle,
    __out_opt PHANDLE TargetHandle,
    __in ACCESS_MASK DesiredAccess,
    __in ULONG HandleAttributes,
    __in ULONG Options,
    __in KPROCESSOR_MODE AccessMode
    );

PHANDLE_TABLE 
ObReferenceProcessHandleTable(
    __in PEPROCESS Process
    );

VOID 
ObDereferenceProcessHandleTable(
    __in PEPROCESS Process
    );

FORCEINLINE
ULONG
ObSanitizeHandleAttributes (
    __in ULONG HandleAttributes,
    __in KPROCESSOR_MODE Mode
    )
{
    if (Mode == KernelMode) 
    {
        return HandleAttributes & OBJ_ALL_VALID_ATTRIBUTES;
    } 
    else
    {
        return HandleAttributes & (OBJ_ALL_VALID_ATTRIBUTES &
            ~(OBJ_KERNEL_HANDLE | OBJ_KERNEL_EXCLUSIVE));
    }
}

//////////////////////////////////////////////////////////////////////////

extern POBJECT_TYPE *SeTokenObjectType;

#ifdef _X86_
#define AUX_ACCESS_DATA_SIZE (0xc8)
#else
#define AUX_ACCESS_DATA_SIZE (0xe0)
#endif

typedef PVOID PAUX_ACCESS_DATA;

typedef 
struct _SE_AUDIT_PROCESS_CREATION_INFO
{
    POBJECT_NAME_INFORMATION ImageFileName;

} SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;

//////////////////////////////////////////////////////////////////////////

NTKERNELAPI
NTSTATUS 
NTAPI 
SeCreateAccessState(
    __out PACCESS_STATE AccessState,
    __out PAUX_ACCESS_DATA AuxData,
    __in ACCESS_MASK DesiredAccess,
    __in_opt PGENERIC_MAPPING Mapping
    );

NTKERNELAPI 
VOID
NTAPI
SeDeleteAccessState(
    __in PACCESS_STATE AccessState
    );

KPROCESSOR_MODE
KeGetPreviousMode (
    VOID
    );

#endif

//////////////////////////////////////////////////////////////////////////

typedef struct
{
    ULONGLONG Vcn;
    ULONGLONG Lcn;

} MAPPING_PAIR, *PMAPPING_PAIR;

typedef struct 
{
    HANDLE FileHandle; 
    ULONG Reserved;   
    LARGE_INTEGER StartVcn; 
    LARGE_INTEGER TargetLcn;
    ULONG NumVcns; 
    ULONG Reserved1;

} MOVEFILE_DESCRIPTOR, *PMOVEFILE_DESCRIPTOR;

typedef struct 
{
    ULONGLONG StartLcn;
    ULONGLONG ClustersToEndOfVol;
    UCHAR Map[1];

} BITMAP_DESCRIPTOR, *PBITMAP_DESCRIPTOR; 

typedef struct
{
    ULONG NumberOfPairs;
    ULONGLONG StartVcn;
    MAPPING_PAIR Pair[1];

} GET_RETRIEVAL_DESCRIPTOR, *PGET_RETRIEVAL_DESCRIPTOR;

//////////////////////////////////////////////////////////////////////////

//#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __NTAPI_H */
