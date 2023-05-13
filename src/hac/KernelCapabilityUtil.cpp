#include <pietendo/hac/KernelCapabilityUtil.h>
#include <fmt/format.h>

std::string pie::hac::KernelCapabilityUtil::getMiscFlagsBitAsString(pie::hac::kc::MiscFlagsBit flag)
{
	std::string str;

	switch(flag)
	{
	case (pie::hac::kc::MiscFlagsBit_EnableDebug):
		str = "EnableDebug";
		break;
	case (pie::hac::kc::MiscFlagsBit_ForceDebug):
		str = "ForceDebug";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)flag);
		break;
	}

	return str;
}

std::string pie::hac::KernelCapabilityUtil::getProgramTypeAsString(pie::hac::kc::ProgramType type)
{
	std::string str;

	switch(type)
	{
	case (pie::hac::kc::ProgramType_System):
		str = "System";
		break;
	case (pie::hac::kc::ProgramType_Application):
		str = "Application";
		break;
	case (pie::hac::kc::ProgramType_Applet):
		str = "Applet";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)type);
		break;
	}

	return str;
}

std::string pie::hac::KernelCapabilityUtil::getMemoryPermissionAsString(pie::hac::kc::MemoryPermission type)
{
	std::string str;

	switch(type)
	{
	case (pie::hac::kc::MemoryPermission_Rw):
		str = "Rw";
		break;
	case (pie::hac::kc::MemoryPermission_Ro):
		str = "Ro";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)type);
		break;
	}

	return str;
}

std::string pie::hac::KernelCapabilityUtil::getMappingTypeAsString(pie::hac::kc::MappingType type)
{
	std::string str;

	switch(type)
	{
	case (pie::hac::kc::MappingType_Io):
		str = "Io";
		break;
	case (pie::hac::kc::MappingType_Static):
		str = "Static";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)type);
		break;
	}

	return str;
}

std::string pie::hac::KernelCapabilityUtil::getSystemCallIdAsString(pie::hac::kc::SystemCallId syscall_id)
{
	std::string str;

	switch(syscall_id)
	{
	case (pie::hac::kc::SystemCallId_Unknown0):
		str = "Unknown0";
		break;
	case (pie::hac::kc::SystemCallId_SetHeapSize):
		str = "SetHeapSize";
		break;
	case (pie::hac::kc::SystemCallId_SetMemoryPermission):
		str = "SetMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId_SetMemoryAttribute):
		str = "SetMemoryAttribute";
		break;
	case (pie::hac::kc::SystemCallId_MapMemory):
		str = "MapMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapMemory):
		str = "UnmapMemory";
		break;
	case (pie::hac::kc::SystemCallId_QueryMemory):
		str = "QueryMemory";
		break;
	case (pie::hac::kc::SystemCallId_ExitProcess):
		str = "ExitProcess";
		break;
	case (pie::hac::kc::SystemCallId_CreateThread):
		str = "CreateThread";
		break;
	case (pie::hac::kc::SystemCallId_StartThread):
		str = "StartThread";
		break;
	case (pie::hac::kc::SystemCallId_ExitThread):
		str = "ExitThread";
		break;
	case (pie::hac::kc::SystemCallId_SleepThread):
		str = "SleepThread";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadPriority):
		str = "GetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadPriority):
		str = "SetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadCoreMask):
		str = "GetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadCoreMask):
		str = "SetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId_GetCurrentProcessorNumber):
		str = "GetCurrentProcessorNumber";
		break;
	case (pie::hac::kc::SystemCallId_SignalEvent):
		str = "SignalEvent";
		break;
	case (pie::hac::kc::SystemCallId_ClearEvent):
		str = "ClearEvent";
		break;
	case (pie::hac::kc::SystemCallId_MapSharedMemory):
		str = "MapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapSharedMemory):
		str = "UnmapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateTransferMemory):
		str = "CreateTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_CloseHandle):
		str = "CloseHandle";
		break;
	case (pie::hac::kc::SystemCallId_ResetSignal):
		str = "ResetSignal";
		break;
	case (pie::hac::kc::SystemCallId_WaitSynchronization):
		str = "WaitSynchronization";
		break;
	case (pie::hac::kc::SystemCallId_CancelSynchronization):
		str = "CancelSynchronization";
		break;
	case (pie::hac::kc::SystemCallId_ArbitrateLock):
		str = "ArbitrateLock";
		break;
	case (pie::hac::kc::SystemCallId_ArbitrateUnlock):
		str = "ArbitrateUnlock";
		break;
	case (pie::hac::kc::SystemCallId_WaitProcessWideKeyAtomic):
		str = "WaitProcessWideKeyAtomic";
		break;
	case (pie::hac::kc::SystemCallId_SignalProcessWideKey):
		str = "SignalProcessWideKey";
		break;
	case (pie::hac::kc::SystemCallId_GetSystemTick):
		str = "GetSystemTick";
		break;
	case (pie::hac::kc::SystemCallId_ConnectToNamedPort):
		str = "ConnectToNamedPort";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequestLight):
		str = "SendSyncRequestLight";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequest):
		str = "SendSyncRequest";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequestWithUserBuffer):
		str = "SendSyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_SendAsyncRequestWithUserBuffer):
		str = "SendAsyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessId):
		str = "GetProcessId";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadId):
		str = "GetThreadId";
		break;
	case (pie::hac::kc::SystemCallId_Break):
		str = "Break";
		break;
	case (pie::hac::kc::SystemCallId_OutputDebugString):
		str = "OutputDebugString";
		break;
	case (pie::hac::kc::SystemCallId_ReturnFromException):
		str = "ReturnFromException";
		break;
	case (pie::hac::kc::SystemCallId_GetInfo):
		str = "GetInfo";
		break;
	case (pie::hac::kc::SystemCallId_FlushEntireDataCache):
		str = "FlushEntireDataCache";
		break;
	case (pie::hac::kc::SystemCallId_FlushDataCache):
		str = "FlushDataCache";
		break;
	case (pie::hac::kc::SystemCallId_MapPhysicalMemory):
		str = "MapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapPhysicalMemory):
		str = "UnmapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugFutureThreadInfo):
		str = "GetDebugFutureThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId_GetLastThreadInfo):
		str = "GetLastThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId_GetResourceLimitLimitValue):
		str = "GetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId_GetResourceLimitCurrentValue):
		str = "GetResourceLimitCurrentValue";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadActivity):
		str = "SetThreadActivity";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadContext3):
		str = "GetThreadContext3";
		break;
	case (pie::hac::kc::SystemCallId_WaitForAddress):
		str = "WaitForAddress";
		break;
	case (pie::hac::kc::SystemCallId_SignalToAddress):
		str = "SignalToAddress";
		break;
	case (pie::hac::kc::SystemCallId_SynchronizePreemptionState):
		str = "SynchronizePreemptionState";
		break;
	case (pie::hac::kc::SystemCallId_Unknown55):
		str = "Unknown55";
		break;
	case (pie::hac::kc::SystemCallId_Unknown56):
		str = "Unknown56";
		break;
	case (pie::hac::kc::SystemCallId_Unknown57):
		str = "Unknown57";
		break;
	case (pie::hac::kc::SystemCallId_Unknown58):
		str = "Unknown58";
		break;
	case (pie::hac::kc::SystemCallId_Unknown59):
		str = "Unknown59";
		break;
	case (pie::hac::kc::SystemCallId_KernelDebug):
		str = "KernelDebug";
		break;
	case (pie::hac::kc::SystemCallId_ChangeKernelTraceState):
		str = "ChangeKernelTraceState";
		break;
	case (pie::hac::kc::SystemCallId_Unknown62):
		str = "Unknown62";
		break;
	case (pie::hac::kc::SystemCallId_Unknown63):
		str = "Unknown63";
		break;
	case (pie::hac::kc::SystemCallId_CreateSession):
		str = "CreateSession";
		break;
	case (pie::hac::kc::SystemCallId_AcceptSession):
		str = "AcceptSession";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceiveLight):
		str = "ReplyAndReceiveLight";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceive):
		str = "ReplyAndReceive";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceiveWithUserBuffer):
		str = "ReplyAndReceiveWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_CreateEvent):
		str = "CreateEvent";
		break;
	case (pie::hac::kc::SystemCallId_Unknown70):
		str = "Unknown70";
		break;
	case (pie::hac::kc::SystemCallId_Unknown71):
		str = "Unknown71";
		break;
	case (pie::hac::kc::SystemCallId_MapPhysicalMemoryUnsafe):
		str = "MapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId_UnmapPhysicalMemoryUnsafe):
		str = "UnmapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId_SetUnsafeLimit):
		str = "SetUnsafeLimit";
		break;
	case (pie::hac::kc::SystemCallId_CreateCodeMemory):
		str = "CreateCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_ControlCodeMemory):
		str = "ControlCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_SleepSystem):
		str = "SleepSystem";
		break;
	case (pie::hac::kc::SystemCallId_ReadWriteRegister):
		str = "ReadWriteRegister";
		break;
	case (pie::hac::kc::SystemCallId_SetProcessActivity):
		str = "SetProcessActivity";
		break;
	case (pie::hac::kc::SystemCallId_CreateSharedMemory):
		str = "CreateSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_MapTransferMemory):
		str = "MapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapTransferMemory):
		str = "UnmapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateInterruptEvent):
		str = "CreateInterruptEvent";
		break;
	case (pie::hac::kc::SystemCallId_QueryPhysicalAddress):
		str = "QueryPhysicalAddress";
		break;
	case (pie::hac::kc::SystemCallId_QueryIoMapping):
		str = "QueryIoMapping";
		break;
	case (pie::hac::kc::SystemCallId_CreateDeviceAddressSpace):
		str = "CreateDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_AttachDeviceAddressSpace):
		str = "AttachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_DetachDeviceAddressSpace):
		str = "DetachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpaceByForce):
		str = "MapDeviceAddressSpaceByForce";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpaceAligned):
		str = "MapDeviceAddressSpaceAligned";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpace):
		str = "MapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_UnmapDeviceAddressSpace):
		str = "UnmapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_InvalidateProcessDataCache):
		str = "InvalidateProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_StoreProcessDataCache):
		str = "StoreProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_FlushProcessDataCache):
		str = "FlushProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_DebugActiveProcess):
		str = "DebugActiveProcess";
		break;
	case (pie::hac::kc::SystemCallId_BreakDebugProcess):
		str = "BreakDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId_TerminateDebugProcess):
		str = "TerminateDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugEvent):
		str = "GetDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId_ContinueDebugEvent):
		str = "ContinueDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessList):
		str = "GetProcessList";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadList):
		str = "GetThreadList";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugThreadContext):
		str = "GetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId_SetDebugThreadContext):
		str = "SetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId_QueryDebugProcessMemory):
		str = "QueryDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_ReadDebugProcessMemory):
		str = "ReadDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_WriteDebugProcessMemory):
		str = "WriteDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_SetHardwareBreakPoint):
		str = "SetHardwareBreakPoint";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugThreadParam):
		str = "GetDebugThreadParam";
		break;
	case (pie::hac::kc::SystemCallId_Unknown110):
		str = "Unknown110";
		break;
	case (pie::hac::kc::SystemCallId_GetSystemInfo):
		str = "GetSystemInfo";
		break;
	case (pie::hac::kc::SystemCallId_CreatePort):
		str = "CreatePort";
		break;
	case (pie::hac::kc::SystemCallId_ManageNamedPort):
		str = "ManageNamedPort";
		break;
	case (pie::hac::kc::SystemCallId_ConnectToPort):
		str = "ConnectToPort";
		break;
	case (pie::hac::kc::SystemCallId_SetProcessMemoryPermission):
		str = "SetProcessMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId_MapProcessMemory):
		str = "MapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapProcessMemory):
		str = "UnmapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_QueryProcessMemory):
		str = "QueryProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_MapProcessCodeMemory):
		str = "MapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapProcessCodeMemory):
		str = "UnmapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateProcess):
		str = "CreateProcess";
		break;
	case (pie::hac::kc::SystemCallId_StartProcess):
		str = "StartProcess";
		break;
	case (pie::hac::kc::SystemCallId_TerminateProcess):
		str = "TerminateProcess";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessInfo):
		str = "GetProcessInfo";
		break;
	case (pie::hac::kc::SystemCallId_CreateResourceLimit):
		str = "CreateResourceLimit";
		break;
	case (pie::hac::kc::SystemCallId_SetResourceLimitLimitValue):
		str = "SetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId_CallSecureMonitor):
		str = "CallSecureMonitor";
		break;
	default:
		str = fmt::format("syscall_id_{:02x}", (uint32_t)syscall_id);
		break;
	}

	return str;
}