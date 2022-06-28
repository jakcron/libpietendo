	/**
	 * @file kc.h
	 * @brief Declaration of KernelCap structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <bitset>

namespace pie { namespace hac {
	
namespace kc
{
	enum KernelCapId
	{
		KernelCapId_Invalid = 0,
		KernelCapId_ThreadInfo = 3,
		KernelCapId_EnableSystemCalls = 4,
		KernelCapId_MemoryMap = 6,
		KernelCapId_IoMemoryMap = 7,
		KernelCapId_MemoryRegionMap = 10,
		KernelCapId_EnableInterrupts = 11,
		KernelCapId_MiscParams = 13,
		KernelCapId_KernelVersion = 14,
		KernelCapId_HandleTableSize = 15,
		KernelCapId_MiscFlags = 16,
		KernelCapId_Stubbed = 32
	};

	enum ProgramType
	{
		ProgramType_System = 0,
		ProgramType_Application = 1,
		ProgramType_Applet = 2
	};

	enum MiscFlagsBit
	{
		MiscFlagsBit_EnableDebug = 0,
		MiscFlagsBit_ForceDebug = 1
	};

	using MiscFlags = std::bitset<16>;

	enum MemoryPermission : bool
	{
		MemoryPermission_Rw = false,
		MemoryPermission_Ro = true
	};

	enum MappingType : bool
	{
		MappingType_Io = false,
		MappingType_Static = true
	};

	enum RegionType : byte_t
	{
		RegionType_NoMapping = 0,
		RegionType_KernelTraceBuffer = 1,
		RegionType_OnMemoryBootImage = 2,
		RegionType_DTB = 3
	};

	enum SystemCallId : byte_t
	{
		SystemCallId_Unknown0                       = 0,
		SystemCallId_SetHeapSize                    = 1,
		SystemCallId_SetMemoryPermission            = 2,
		SystemCallId_SetMemoryAttribute             = 3,
		SystemCallId_MapMemory                      = 4,
		SystemCallId_UnmapMemory                    = 5,
		SystemCallId_QueryMemory                    = 6,
		SystemCallId_ExitProcess                    = 7,
		SystemCallId_CreateThread                   = 8,
		SystemCallId_StartThread                    = 9,
		SystemCallId_ExitThread                     = 10,
		SystemCallId_SleepThread                    = 11,
		SystemCallId_GetThreadPriority              = 12,
		SystemCallId_SetThreadPriority              = 13,
		SystemCallId_GetThreadCoreMask              = 14,
		SystemCallId_SetThreadCoreMask              = 15,
		SystemCallId_GetCurrentProcessorNumber      = 16,
		SystemCallId_SignalEvent                    = 17,
		SystemCallId_ClearEvent                     = 18,
		SystemCallId_MapSharedMemory                = 19,
		SystemCallId_UnmapSharedMemory              = 20,
		SystemCallId_CreateTransferMemory           = 21,
		SystemCallId_CloseHandle                    = 22,
		SystemCallId_ResetSignal                    = 23,
		SystemCallId_WaitSynchronization            = 24,
		SystemCallId_CancelSynchronization          = 25,
		SystemCallId_ArbitrateLock                  = 26,
		SystemCallId_ArbitrateUnlock                = 27,
		SystemCallId_WaitProcessWideKeyAtomic       = 28,
		SystemCallId_SignalProcessWideKey           = 29,
		SystemCallId_GetSystemTick                  = 30,
		SystemCallId_ConnectToNamedPort             = 31,
		SystemCallId_SendSyncRequestLight           = 32,
		SystemCallId_SendSyncRequest                = 33,
		SystemCallId_SendSyncRequestWithUserBuffer  = 34,
		SystemCallId_SendAsyncRequestWithUserBuffer = 35,
		SystemCallId_GetProcessId                   = 36,
		SystemCallId_GetThreadId                    = 37,
		SystemCallId_Break                          = 38,
		SystemCallId_OutputDebugString              = 39,
		SystemCallId_ReturnFromException            = 40,
		SystemCallId_GetInfo                        = 41,
		SystemCallId_FlushEntireDataCache           = 42,
		SystemCallId_FlushDataCache                 = 43,
		SystemCallId_MapPhysicalMemory              = 44,
		SystemCallId_UnmapPhysicalMemory            = 45,
		SystemCallId_GetDebugFutureThreadInfo       = 46,
		SystemCallId_GetLastThreadInfo              = 47,
		SystemCallId_GetResourceLimitLimitValue     = 48,
		SystemCallId_GetResourceLimitCurrentValue   = 49,
		SystemCallId_SetThreadActivity              = 50,
		SystemCallId_GetThreadContext3              = 51,
		SystemCallId_WaitForAddress                 = 52,
		SystemCallId_SignalToAddress                = 53,
		SystemCallId_SynchronizePreemptionState     = 54,
		SystemCallId_Unknown55                      = 55,
		SystemCallId_Unknown56                      = 56,
		SystemCallId_Unknown57                      = 57,
		SystemCallId_Unknown58                      = 58,
		SystemCallId_Unknown59                      = 59,
		SystemCallId_KernelDebug                    = 60,
		SystemCallId_ChangeKernelTraceState         = 61, /* DumpInfo [1.0.0-3.0.2] */
		SystemCallId_Unknown62                      = 62,
		SystemCallId_Unknown63                      = 63,
		SystemCallId_CreateSession                  = 64,
		SystemCallId_AcceptSession                  = 65,
		SystemCallId_ReplyAndReceiveLight           = 66,
		SystemCallId_ReplyAndReceive                = 67,
		SystemCallId_ReplyAndReceiveWithUserBuffer  = 68,
		SystemCallId_CreateEvent                    = 69,
		SystemCallId_Unknown70                      = 70,
		SystemCallId_Unknown71                      = 71,
		SystemCallId_MapPhysicalMemoryUnsafe        = 72,
		SystemCallId_UnmapPhysicalMemoryUnsafe      = 73,
		SystemCallId_SetUnsafeLimit                 = 74,
		SystemCallId_CreateCodeMemory               = 75,
		SystemCallId_ControlCodeMemory              = 76,
		SystemCallId_SleepSystem                    = 77,
		SystemCallId_ReadWriteRegister              = 78,
		SystemCallId_SetProcessActivity             = 79,
		SystemCallId_CreateSharedMemory             = 80,
		SystemCallId_MapTransferMemory              = 81,
		SystemCallId_UnmapTransferMemory            = 82,
		SystemCallId_CreateInterruptEvent           = 83,
		SystemCallId_QueryPhysicalAddress           = 84,
		SystemCallId_QueryIoMapping                 = 85,
		SystemCallId_CreateDeviceAddressSpace       = 86,
		SystemCallId_AttachDeviceAddressSpace       = 87,
		SystemCallId_DetachDeviceAddressSpace       = 88,
		SystemCallId_MapDeviceAddressSpaceByForce   = 89,
		SystemCallId_MapDeviceAddressSpaceAligned   = 90,
		SystemCallId_MapDeviceAddressSpace          = 91,
		SystemCallId_UnmapDeviceAddressSpace        = 92,
		SystemCallId_InvalidateProcessDataCache     = 93,
		SystemCallId_StoreProcessDataCache          = 94,
		SystemCallId_FlushProcessDataCache          = 95,
		SystemCallId_DebugActiveProcess             = 96,
		SystemCallId_BreakDebugProcess              = 97,
		SystemCallId_TerminateDebugProcess          = 98,
		SystemCallId_GetDebugEvent                  = 99,
		SystemCallId_ContinueDebugEvent             = 100,
		SystemCallId_GetProcessList                 = 101,
		SystemCallId_GetThreadList                  = 102,
		SystemCallId_GetDebugThreadContext          = 103,
		SystemCallId_SetDebugThreadContext          = 104,
		SystemCallId_QueryDebugProcessMemory        = 105,
		SystemCallId_ReadDebugProcessMemory         = 106,
		SystemCallId_WriteDebugProcessMemory        = 107,
		SystemCallId_SetHardwareBreakPoint          = 108,
		SystemCallId_GetDebugThreadParam            = 109,
		SystemCallId_Unknown110                     = 110,
		SystemCallId_GetSystemInfo                  = 111,
		SystemCallId_CreatePort                     = 112,
		SystemCallId_ManageNamedPort                = 113,
		SystemCallId_ConnectToPort                  = 114,
		SystemCallId_SetProcessMemoryPermission     = 115,
		SystemCallId_MapProcessMemory               = 116,
		SystemCallId_UnmapProcessMemory             = 117,
		SystemCallId_QueryProcessMemory             = 118,
		SystemCallId_MapProcessCodeMemory           = 119,
		SystemCallId_UnmapProcessCodeMemory         = 120,
		SystemCallId_CreateProcess                  = 121,
		SystemCallId_StartProcess                   = 122,
		SystemCallId_TerminateProcess               = 123,
		SystemCallId_GetProcessInfo                 = 124,
		SystemCallId_CreateResourceLimit            = 125,
		SystemCallId_SetResourceLimitLimitValue     = 126,
		SystemCallId_CallSecureMonitor              = 127
	};

	static const uint32_t kMaxSystemCallNum = ((1 << 3) * 24);
	static const uint32_t kMaxSystemCallId = kMaxSystemCallNum - 1;
	using SystemCallIds = std::bitset<kMaxSystemCallNum>;
}

}} // namespace pie::hac