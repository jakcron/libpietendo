#include <pietendo/hac/KernelCapabilityUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::KernelCapabilityUtil::getMiscFlagsBitAsString(pie::hac::kc::MiscFlagsBit flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (pie::hac::kc::MiscFlagsBit_EnableDebug):
		ss << "EnableDebug";
		break;
	case (pie::hac::kc::MiscFlagsBit_ForceDebug):
		ss << "ForceDebug";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string pie::hac::KernelCapabilityUtil::getProgramTypeAsString(pie::hac::kc::ProgramType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (pie::hac::kc::ProgramType_System):
		ss << "System";
		break;
	case (pie::hac::kc::ProgramType_Application):
		ss << "Application";
		break;
	case (pie::hac::kc::ProgramType_Applet):
		ss << "Applet";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string pie::hac::KernelCapabilityUtil::getMemoryPermissionAsString(pie::hac::kc::MemoryPermission type)
{
	std::stringstream ss;

	switch(type)
	{
	case (pie::hac::kc::MemoryPermission_Rw):
		ss << "Rw";
		break;
	case (pie::hac::kc::MemoryPermission_Ro):
		ss << "Ro";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string pie::hac::KernelCapabilityUtil::getMappingTypeAsString(pie::hac::kc::MappingType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (pie::hac::kc::MappingType_Io):
		ss << "Io";
		break;
	case (pie::hac::kc::MappingType_Static):
		ss << "Static";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string pie::hac::KernelCapabilityUtil::getSystemCallIdAsString(pie::hac::kc::SystemCallId syscall_id)
{
	std::stringstream ss;

	switch(syscall_id)
	{
	case (pie::hac::kc::SystemCallId_Unknown0):
		ss << "Unknown0";
		break;
	case (pie::hac::kc::SystemCallId_SetHeapSize):
		ss << "SetHeapSize";
		break;
	case (pie::hac::kc::SystemCallId_SetMemoryPermission):
		ss << "SetMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId_SetMemoryAttribute):
		ss << "SetMemoryAttribute";
		break;
	case (pie::hac::kc::SystemCallId_MapMemory):
		ss << "MapMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapMemory):
		ss << "UnmapMemory";
		break;
	case (pie::hac::kc::SystemCallId_QueryMemory):
		ss << "QueryMemory";
		break;
	case (pie::hac::kc::SystemCallId_ExitProcess):
		ss << "ExitProcess";
		break;
	case (pie::hac::kc::SystemCallId_CreateThread):
		ss << "CreateThread";
		break;
	case (pie::hac::kc::SystemCallId_StartThread):
		ss << "StartThread";
		break;
	case (pie::hac::kc::SystemCallId_ExitThread):
		ss << "ExitThread";
		break;
	case (pie::hac::kc::SystemCallId_SleepThread):
		ss << "SleepThread";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadPriority):
		ss << "GetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadPriority):
		ss << "SetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadCoreMask):
		ss << "GetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadCoreMask):
		ss << "SetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId_GetCurrentProcessorNumber):
		ss << "GetCurrentProcessorNumber";
		break;
	case (pie::hac::kc::SystemCallId_SignalEvent):
		ss << "SignalEvent";
		break;
	case (pie::hac::kc::SystemCallId_ClearEvent):
		ss << "ClearEvent";
		break;
	case (pie::hac::kc::SystemCallId_MapSharedMemory):
		ss << "MapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapSharedMemory):
		ss << "UnmapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateTransferMemory):
		ss << "CreateTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_CloseHandle):
		ss << "CloseHandle";
		break;
	case (pie::hac::kc::SystemCallId_ResetSignal):
		ss << "ResetSignal";
		break;
	case (pie::hac::kc::SystemCallId_WaitSynchronization):
		ss << "WaitSynchronization";
		break;
	case (pie::hac::kc::SystemCallId_CancelSynchronization):
		ss << "CancelSynchronization";
		break;
	case (pie::hac::kc::SystemCallId_ArbitrateLock):
		ss << "ArbitrateLock";
		break;
	case (pie::hac::kc::SystemCallId_ArbitrateUnlock):
		ss << "ArbitrateUnlock";
		break;
	case (pie::hac::kc::SystemCallId_WaitProcessWideKeyAtomic):
		ss << "WaitProcessWideKeyAtomic";
		break;
	case (pie::hac::kc::SystemCallId_SignalProcessWideKey):
		ss << "SignalProcessWideKey";
		break;
	case (pie::hac::kc::SystemCallId_GetSystemTick):
		ss << "GetSystemTick";
		break;
	case (pie::hac::kc::SystemCallId_ConnectToNamedPort):
		ss << "ConnectToNamedPort";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequestLight):
		ss << "SendSyncRequestLight";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequest):
		ss << "SendSyncRequest";
		break;
	case (pie::hac::kc::SystemCallId_SendSyncRequestWithUserBuffer):
		ss << "SendSyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_SendAsyncRequestWithUserBuffer):
		ss << "SendAsyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessId):
		ss << "GetProcessId";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadId):
		ss << "GetThreadId";
		break;
	case (pie::hac::kc::SystemCallId_Break):
		ss << "Break";
		break;
	case (pie::hac::kc::SystemCallId_OutputDebugString):
		ss << "OutputDebugString";
		break;
	case (pie::hac::kc::SystemCallId_ReturnFromException):
		ss << "ReturnFromException";
		break;
	case (pie::hac::kc::SystemCallId_GetInfo):
		ss << "GetInfo";
		break;
	case (pie::hac::kc::SystemCallId_FlushEntireDataCache):
		ss << "FlushEntireDataCache";
		break;
	case (pie::hac::kc::SystemCallId_FlushDataCache):
		ss << "FlushDataCache";
		break;
	case (pie::hac::kc::SystemCallId_MapPhysicalMemory):
		ss << "MapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapPhysicalMemory):
		ss << "UnmapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugFutureThreadInfo):
		ss << "GetDebugFutureThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId_GetLastThreadInfo):
		ss << "GetLastThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId_GetResourceLimitLimitValue):
		ss << "GetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId_GetResourceLimitCurrentValue):
		ss << "GetResourceLimitCurrentValue";
		break;
	case (pie::hac::kc::SystemCallId_SetThreadActivity):
		ss << "SetThreadActivity";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadContext3):
		ss << "GetThreadContext3";
		break;
	case (pie::hac::kc::SystemCallId_WaitForAddress):
		ss << "WaitForAddress";
		break;
	case (pie::hac::kc::SystemCallId_SignalToAddress):
		ss << "SignalToAddress";
		break;
	case (pie::hac::kc::SystemCallId_SynchronizePreemptionState):
		ss << "SynchronizePreemptionState";
		break;
	case (pie::hac::kc::SystemCallId_Unknown55):
		ss << "Unknown55";
		break;
	case (pie::hac::kc::SystemCallId_Unknown56):
		ss << "Unknown56";
		break;
	case (pie::hac::kc::SystemCallId_Unknown57):
		ss << "Unknown57";
		break;
	case (pie::hac::kc::SystemCallId_Unknown58):
		ss << "Unknown58";
		break;
	case (pie::hac::kc::SystemCallId_Unknown59):
		ss << "Unknown59";
		break;
	case (pie::hac::kc::SystemCallId_KernelDebug):
		ss << "KernelDebug";
		break;
	case (pie::hac::kc::SystemCallId_ChangeKernelTraceState):
		ss << "ChangeKernelTraceState";
		break;
	case (pie::hac::kc::SystemCallId_Unknown62):
		ss << "Unknown62";
		break;
	case (pie::hac::kc::SystemCallId_Unknown63):
		ss << "Unknown63";
		break;
	case (pie::hac::kc::SystemCallId_CreateSession):
		ss << "CreateSession";
		break;
	case (pie::hac::kc::SystemCallId_AcceptSession):
		ss << "AcceptSession";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceiveLight):
		ss << "ReplyAndReceiveLight";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceive):
		ss << "ReplyAndReceive";
		break;
	case (pie::hac::kc::SystemCallId_ReplyAndReceiveWithUserBuffer):
		ss << "ReplyAndReceiveWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId_CreateEvent):
		ss << "CreateEvent";
		break;
	case (pie::hac::kc::SystemCallId_Unknown70):
		ss << "Unknown70";
		break;
	case (pie::hac::kc::SystemCallId_Unknown71):
		ss << "Unknown71";
		break;
	case (pie::hac::kc::SystemCallId_MapPhysicalMemoryUnsafe):
		ss << "MapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId_UnmapPhysicalMemoryUnsafe):
		ss << "UnmapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId_SetUnsafeLimit):
		ss << "SetUnsafeLimit";
		break;
	case (pie::hac::kc::SystemCallId_CreateCodeMemory):
		ss << "CreateCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_ControlCodeMemory):
		ss << "ControlCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_SleepSystem):
		ss << "SleepSystem";
		break;
	case (pie::hac::kc::SystemCallId_ReadWriteRegister):
		ss << "ReadWriteRegister";
		break;
	case (pie::hac::kc::SystemCallId_SetProcessActivity):
		ss << "SetProcessActivity";
		break;
	case (pie::hac::kc::SystemCallId_CreateSharedMemory):
		ss << "CreateSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId_MapTransferMemory):
		ss << "MapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapTransferMemory):
		ss << "UnmapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateInterruptEvent):
		ss << "CreateInterruptEvent";
		break;
	case (pie::hac::kc::SystemCallId_QueryPhysicalAddress):
		ss << "QueryPhysicalAddress";
		break;
	case (pie::hac::kc::SystemCallId_QueryIoMapping):
		ss << "QueryIoMapping";
		break;
	case (pie::hac::kc::SystemCallId_CreateDeviceAddressSpace):
		ss << "CreateDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_AttachDeviceAddressSpace):
		ss << "AttachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_DetachDeviceAddressSpace):
		ss << "DetachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpaceByForce):
		ss << "MapDeviceAddressSpaceByForce";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpaceAligned):
		ss << "MapDeviceAddressSpaceAligned";
		break;
	case (pie::hac::kc::SystemCallId_MapDeviceAddressSpace):
		ss << "MapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_UnmapDeviceAddressSpace):
		ss << "UnmapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId_InvalidateProcessDataCache):
		ss << "InvalidateProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_StoreProcessDataCache):
		ss << "StoreProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_FlushProcessDataCache):
		ss << "FlushProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId_DebugActiveProcess):
		ss << "DebugActiveProcess";
		break;
	case (pie::hac::kc::SystemCallId_BreakDebugProcess):
		ss << "BreakDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId_TerminateDebugProcess):
		ss << "TerminateDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugEvent):
		ss << "GetDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId_ContinueDebugEvent):
		ss << "ContinueDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessList):
		ss << "GetProcessList";
		break;
	case (pie::hac::kc::SystemCallId_GetThreadList):
		ss << "GetThreadList";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugThreadContext):
		ss << "GetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId_SetDebugThreadContext):
		ss << "SetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId_QueryDebugProcessMemory):
		ss << "QueryDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_ReadDebugProcessMemory):
		ss << "ReadDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_WriteDebugProcessMemory):
		ss << "WriteDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_SetHardwareBreakPoint):
		ss << "SetHardwareBreakPoint";
		break;
	case (pie::hac::kc::SystemCallId_GetDebugThreadParam):
		ss << "GetDebugThreadParam";
		break;
	case (pie::hac::kc::SystemCallId_Unknown110):
		ss << "Unknown110";
		break;
	case (pie::hac::kc::SystemCallId_GetSystemInfo):
		ss << "GetSystemInfo";
		break;
	case (pie::hac::kc::SystemCallId_CreatePort):
		ss << "CreatePort";
		break;
	case (pie::hac::kc::SystemCallId_ManageNamedPort):
		ss << "ManageNamedPort";
		break;
	case (pie::hac::kc::SystemCallId_ConnectToPort):
		ss << "ConnectToPort";
		break;
	case (pie::hac::kc::SystemCallId_SetProcessMemoryPermission):
		ss << "SetProcessMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId_MapProcessMemory):
		ss << "MapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapProcessMemory):
		ss << "UnmapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_QueryProcessMemory):
		ss << "QueryProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId_MapProcessCodeMemory):
		ss << "MapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_UnmapProcessCodeMemory):
		ss << "UnmapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId_CreateProcess):
		ss << "CreateProcess";
		break;
	case (pie::hac::kc::SystemCallId_StartProcess):
		ss << "StartProcess";
		break;
	case (pie::hac::kc::SystemCallId_TerminateProcess):
		ss << "TerminateProcess";
		break;
	case (pie::hac::kc::SystemCallId_GetProcessInfo):
		ss << "GetProcessInfo";
		break;
	case (pie::hac::kc::SystemCallId_CreateResourceLimit):
		ss << "CreateResourceLimit";
		break;
	case (pie::hac::kc::SystemCallId_SetResourceLimitLimitValue):
		ss << "SetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId_CallSecureMonitor):
		ss << "CallSecureMonitor";
		break;
	default:
		ss << "syscall_id_" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)syscall_id;
		break;
	}

	return ss.str();
}