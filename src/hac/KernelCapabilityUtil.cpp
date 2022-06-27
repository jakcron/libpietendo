#include <nn/hac/KernelCapabilityUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::KernelCapabilityUtil::getMiscFlagsBitAsString(nn::hac::kc::MiscFlagsBit flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::kc::MiscFlagsBit::EnableDebug):
		ss << "EnableDebug";
		break;
	case (nn::hac::kc::MiscFlagsBit::ForceDebug):
		ss << "ForceDebug";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getProgramTypeAsString(nn::hac::kc::ProgramType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::kc::ProgramType::System):
		ss << "System";
		break;
	case (nn::hac::kc::ProgramType::Application):
		ss << "Application";
		break;
	case (nn::hac::kc::ProgramType::Applet):
		ss << "Applet";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getMemoryPermissionAsString(nn::hac::kc::MemoryPermission type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::kc::MemoryPermission::Rw):
		ss << "Rw";
		break;
	case (nn::hac::kc::MemoryPermission::Ro):
		ss << "Ro";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getMappingTypeAsString(nn::hac::kc::MappingType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::kc::MappingType::Io):
		ss << "Io";
		break;
	case (nn::hac::kc::MappingType::Static):
		ss << "Static";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}

std::string nn::hac::KernelCapabilityUtil::getSystemCallIdAsString(nn::hac::kc::SystemCallId syscall_id)
{
	std::stringstream ss;

	switch(syscall_id)
	{
	case (nn::hac::kc::SystemCallId::Unknown0):
		ss << "Unknown0";
		break;
	case (nn::hac::kc::SystemCallId::SetHeapSize):
		ss << "SetHeapSize";
		break;
	case (nn::hac::kc::SystemCallId::SetMemoryPermission):
		ss << "SetMemoryPermission";
		break;
	case (nn::hac::kc::SystemCallId::SetMemoryAttribute):
		ss << "SetMemoryAttribute";
		break;
	case (nn::hac::kc::SystemCallId::MapMemory):
		ss << "MapMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapMemory):
		ss << "UnmapMemory";
		break;
	case (nn::hac::kc::SystemCallId::QueryMemory):
		ss << "QueryMemory";
		break;
	case (nn::hac::kc::SystemCallId::ExitProcess):
		ss << "ExitProcess";
		break;
	case (nn::hac::kc::SystemCallId::CreateThread):
		ss << "CreateThread";
		break;
	case (nn::hac::kc::SystemCallId::StartThread):
		ss << "StartThread";
		break;
	case (nn::hac::kc::SystemCallId::ExitThread):
		ss << "ExitThread";
		break;
	case (nn::hac::kc::SystemCallId::SleepThread):
		ss << "SleepThread";
		break;
	case (nn::hac::kc::SystemCallId::GetThreadPriority):
		ss << "GetThreadPriority";
		break;
	case (nn::hac::kc::SystemCallId::SetThreadPriority):
		ss << "SetThreadPriority";
		break;
	case (nn::hac::kc::SystemCallId::GetThreadCoreMask):
		ss << "GetThreadCoreMask";
		break;
	case (nn::hac::kc::SystemCallId::SetThreadCoreMask):
		ss << "SetThreadCoreMask";
		break;
	case (nn::hac::kc::SystemCallId::GetCurrentProcessorNumber):
		ss << "GetCurrentProcessorNumber";
		break;
	case (nn::hac::kc::SystemCallId::SignalEvent):
		ss << "SignalEvent";
		break;
	case (nn::hac::kc::SystemCallId::ClearEvent):
		ss << "ClearEvent";
		break;
	case (nn::hac::kc::SystemCallId::MapSharedMemory):
		ss << "MapSharedMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapSharedMemory):
		ss << "UnmapSharedMemory";
		break;
	case (nn::hac::kc::SystemCallId::CreateTransferMemory):
		ss << "CreateTransferMemory";
		break;
	case (nn::hac::kc::SystemCallId::CloseHandle):
		ss << "CloseHandle";
		break;
	case (nn::hac::kc::SystemCallId::ResetSignal):
		ss << "ResetSignal";
		break;
	case (nn::hac::kc::SystemCallId::WaitSynchronization):
		ss << "WaitSynchronization";
		break;
	case (nn::hac::kc::SystemCallId::CancelSynchronization):
		ss << "CancelSynchronization";
		break;
	case (nn::hac::kc::SystemCallId::ArbitrateLock):
		ss << "ArbitrateLock";
		break;
	case (nn::hac::kc::SystemCallId::ArbitrateUnlock):
		ss << "ArbitrateUnlock";
		break;
	case (nn::hac::kc::SystemCallId::WaitProcessWideKeyAtomic):
		ss << "WaitProcessWideKeyAtomic";
		break;
	case (nn::hac::kc::SystemCallId::SignalProcessWideKey):
		ss << "SignalProcessWideKey";
		break;
	case (nn::hac::kc::SystemCallId::GetSystemTick):
		ss << "GetSystemTick";
		break;
	case (nn::hac::kc::SystemCallId::ConnectToNamedPort):
		ss << "ConnectToNamedPort";
		break;
	case (nn::hac::kc::SystemCallId::SendSyncRequestLight):
		ss << "SendSyncRequestLight";
		break;
	case (nn::hac::kc::SystemCallId::SendSyncRequest):
		ss << "SendSyncRequest";
		break;
	case (nn::hac::kc::SystemCallId::SendSyncRequestWithUserBuffer):
		ss << "SendSyncRequestWithUserBuffer";
		break;
	case (nn::hac::kc::SystemCallId::SendAsyncRequestWithUserBuffer):
		ss << "SendAsyncRequestWithUserBuffer";
		break;
	case (nn::hac::kc::SystemCallId::GetProcessId):
		ss << "GetProcessId";
		break;
	case (nn::hac::kc::SystemCallId::GetThreadId):
		ss << "GetThreadId";
		break;
	case (nn::hac::kc::SystemCallId::Break):
		ss << "Break";
		break;
	case (nn::hac::kc::SystemCallId::OutputDebugString):
		ss << "OutputDebugString";
		break;
	case (nn::hac::kc::SystemCallId::ReturnFromException):
		ss << "ReturnFromException";
		break;
	case (nn::hac::kc::SystemCallId::GetInfo):
		ss << "GetInfo";
		break;
	case (nn::hac::kc::SystemCallId::FlushEntireDataCache):
		ss << "FlushEntireDataCache";
		break;
	case (nn::hac::kc::SystemCallId::FlushDataCache):
		ss << "FlushDataCache";
		break;
	case (nn::hac::kc::SystemCallId::MapPhysicalMemory):
		ss << "MapPhysicalMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapPhysicalMemory):
		ss << "UnmapPhysicalMemory";
		break;
	case (nn::hac::kc::SystemCallId::GetDebugFutureThreadInfo):
		ss << "GetDebugFutureThreadInfo";
		break;
	case (nn::hac::kc::SystemCallId::GetLastThreadInfo):
		ss << "GetLastThreadInfo";
		break;
	case (nn::hac::kc::SystemCallId::GetResourceLimitLimitValue):
		ss << "GetResourceLimitLimitValue";
		break;
	case (nn::hac::kc::SystemCallId::GetResourceLimitCurrentValue):
		ss << "GetResourceLimitCurrentValue";
		break;
	case (nn::hac::kc::SystemCallId::SetThreadActivity):
		ss << "SetThreadActivity";
		break;
	case (nn::hac::kc::SystemCallId::GetThreadContext3):
		ss << "GetThreadContext3";
		break;
	case (nn::hac::kc::SystemCallId::WaitForAddress):
		ss << "WaitForAddress";
		break;
	case (nn::hac::kc::SystemCallId::SignalToAddress):
		ss << "SignalToAddress";
		break;
	case (nn::hac::kc::SystemCallId::SynchronizePreemptionState):
		ss << "SynchronizePreemptionState";
		break;
	case (nn::hac::kc::SystemCallId::Unknown55):
		ss << "Unknown55";
		break;
	case (nn::hac::kc::SystemCallId::Unknown56):
		ss << "Unknown56";
		break;
	case (nn::hac::kc::SystemCallId::Unknown57):
		ss << "Unknown57";
		break;
	case (nn::hac::kc::SystemCallId::Unknown58):
		ss << "Unknown58";
		break;
	case (nn::hac::kc::SystemCallId::Unknown59):
		ss << "Unknown59";
		break;
	case (nn::hac::kc::SystemCallId::KernelDebug):
		ss << "KernelDebug";
		break;
	case (nn::hac::kc::SystemCallId::ChangeKernelTraceState):
		ss << "ChangeKernelTraceState";
		break;
	case (nn::hac::kc::SystemCallId::Unknown62):
		ss << "Unknown62";
		break;
	case (nn::hac::kc::SystemCallId::Unknown63):
		ss << "Unknown63";
		break;
	case (nn::hac::kc::SystemCallId::CreateSession):
		ss << "CreateSession";
		break;
	case (nn::hac::kc::SystemCallId::AcceptSession):
		ss << "AcceptSession";
		break;
	case (nn::hac::kc::SystemCallId::ReplyAndReceiveLight):
		ss << "ReplyAndReceiveLight";
		break;
	case (nn::hac::kc::SystemCallId::ReplyAndReceive):
		ss << "ReplyAndReceive";
		break;
	case (nn::hac::kc::SystemCallId::ReplyAndReceiveWithUserBuffer):
		ss << "ReplyAndReceiveWithUserBuffer";
		break;
	case (nn::hac::kc::SystemCallId::CreateEvent):
		ss << "CreateEvent";
		break;
	case (nn::hac::kc::SystemCallId::Unknown70):
		ss << "Unknown70";
		break;
	case (nn::hac::kc::SystemCallId::Unknown71):
		ss << "Unknown71";
		break;
	case (nn::hac::kc::SystemCallId::MapPhysicalMemoryUnsafe):
		ss << "MapPhysicalMemoryUnsafe";
		break;
	case (nn::hac::kc::SystemCallId::UnmapPhysicalMemoryUnsafe):
		ss << "UnmapPhysicalMemoryUnsafe";
		break;
	case (nn::hac::kc::SystemCallId::SetUnsafeLimit):
		ss << "SetUnsafeLimit";
		break;
	case (nn::hac::kc::SystemCallId::CreateCodeMemory):
		ss << "CreateCodeMemory";
		break;
	case (nn::hac::kc::SystemCallId::ControlCodeMemory):
		ss << "ControlCodeMemory";
		break;
	case (nn::hac::kc::SystemCallId::SleepSystem):
		ss << "SleepSystem";
		break;
	case (nn::hac::kc::SystemCallId::ReadWriteRegister):
		ss << "ReadWriteRegister";
		break;
	case (nn::hac::kc::SystemCallId::SetProcessActivity):
		ss << "SetProcessActivity";
		break;
	case (nn::hac::kc::SystemCallId::CreateSharedMemory):
		ss << "CreateSharedMemory";
		break;
	case (nn::hac::kc::SystemCallId::MapTransferMemory):
		ss << "MapTransferMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapTransferMemory):
		ss << "UnmapTransferMemory";
		break;
	case (nn::hac::kc::SystemCallId::CreateInterruptEvent):
		ss << "CreateInterruptEvent";
		break;
	case (nn::hac::kc::SystemCallId::QueryPhysicalAddress):
		ss << "QueryPhysicalAddress";
		break;
	case (nn::hac::kc::SystemCallId::QueryIoMapping):
		ss << "QueryIoMapping";
		break;
	case (nn::hac::kc::SystemCallId::CreateDeviceAddressSpace):
		ss << "CreateDeviceAddressSpace";
		break;
	case (nn::hac::kc::SystemCallId::AttachDeviceAddressSpace):
		ss << "AttachDeviceAddressSpace";
		break;
	case (nn::hac::kc::SystemCallId::DetachDeviceAddressSpace):
		ss << "DetachDeviceAddressSpace";
		break;
	case (nn::hac::kc::SystemCallId::MapDeviceAddressSpaceByForce):
		ss << "MapDeviceAddressSpaceByForce";
		break;
	case (nn::hac::kc::SystemCallId::MapDeviceAddressSpaceAligned):
		ss << "MapDeviceAddressSpaceAligned";
		break;
	case (nn::hac::kc::SystemCallId::MapDeviceAddressSpace):
		ss << "MapDeviceAddressSpace";
		break;
	case (nn::hac::kc::SystemCallId::UnmapDeviceAddressSpace):
		ss << "UnmapDeviceAddressSpace";
		break;
	case (nn::hac::kc::SystemCallId::InvalidateProcessDataCache):
		ss << "InvalidateProcessDataCache";
		break;
	case (nn::hac::kc::SystemCallId::StoreProcessDataCache):
		ss << "StoreProcessDataCache";
		break;
	case (nn::hac::kc::SystemCallId::FlushProcessDataCache):
		ss << "FlushProcessDataCache";
		break;
	case (nn::hac::kc::SystemCallId::DebugActiveProcess):
		ss << "DebugActiveProcess";
		break;
	case (nn::hac::kc::SystemCallId::BreakDebugProcess):
		ss << "BreakDebugProcess";
		break;
	case (nn::hac::kc::SystemCallId::TerminateDebugProcess):
		ss << "TerminateDebugProcess";
		break;
	case (nn::hac::kc::SystemCallId::GetDebugEvent):
		ss << "GetDebugEvent";
		break;
	case (nn::hac::kc::SystemCallId::ContinueDebugEvent):
		ss << "ContinueDebugEvent";
		break;
	case (nn::hac::kc::SystemCallId::GetProcessList):
		ss << "GetProcessList";
		break;
	case (nn::hac::kc::SystemCallId::GetThreadList):
		ss << "GetThreadList";
		break;
	case (nn::hac::kc::SystemCallId::GetDebugThreadContext):
		ss << "GetDebugThreadContext";
		break;
	case (nn::hac::kc::SystemCallId::SetDebugThreadContext):
		ss << "SetDebugThreadContext";
		break;
	case (nn::hac::kc::SystemCallId::QueryDebugProcessMemory):
		ss << "QueryDebugProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::ReadDebugProcessMemory):
		ss << "ReadDebugProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::WriteDebugProcessMemory):
		ss << "WriteDebugProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::SetHardwareBreakPoint):
		ss << "SetHardwareBreakPoint";
		break;
	case (nn::hac::kc::SystemCallId::GetDebugThreadParam):
		ss << "GetDebugThreadParam";
		break;
	case (nn::hac::kc::SystemCallId::Unknown110):
		ss << "Unknown110";
		break;
	case (nn::hac::kc::SystemCallId::GetSystemInfo):
		ss << "GetSystemInfo";
		break;
	case (nn::hac::kc::SystemCallId::CreatePort):
		ss << "CreatePort";
		break;
	case (nn::hac::kc::SystemCallId::ManageNamedPort):
		ss << "ManageNamedPort";
		break;
	case (nn::hac::kc::SystemCallId::ConnectToPort):
		ss << "ConnectToPort";
		break;
	case (nn::hac::kc::SystemCallId::SetProcessMemoryPermission):
		ss << "SetProcessMemoryPermission";
		break;
	case (nn::hac::kc::SystemCallId::MapProcessMemory):
		ss << "MapProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapProcessMemory):
		ss << "UnmapProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::QueryProcessMemory):
		ss << "QueryProcessMemory";
		break;
	case (nn::hac::kc::SystemCallId::MapProcessCodeMemory):
		ss << "MapProcessCodeMemory";
		break;
	case (nn::hac::kc::SystemCallId::UnmapProcessCodeMemory):
		ss << "UnmapProcessCodeMemory";
		break;
	case (nn::hac::kc::SystemCallId::CreateProcess):
		ss << "CreateProcess";
		break;
	case (nn::hac::kc::SystemCallId::StartProcess):
		ss << "StartProcess";
		break;
	case (nn::hac::kc::SystemCallId::TerminateProcess):
		ss << "TerminateProcess";
		break;
	case (nn::hac::kc::SystemCallId::GetProcessInfo):
		ss << "GetProcessInfo";
		break;
	case (nn::hac::kc::SystemCallId::CreateResourceLimit):
		ss << "CreateResourceLimit";
		break;
	case (nn::hac::kc::SystemCallId::SetResourceLimitLimitValue):
		ss << "SetResourceLimitLimitValue";
		break;
	case (nn::hac::kc::SystemCallId::CallSecureMonitor):
		ss << "CallSecureMonitor";
		break;
	default:
		ss << "syscall_id_" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)syscall_id;
		break;
	}

	return ss.str();
}