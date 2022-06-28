#include <pietendo/hac/KernelCapabilityUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::KernelCapabilityUtil::getMiscFlagsBitAsString(pie::hac::kc::MiscFlagsBit flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (pie::hac::kc::MiscFlagsBit::EnableDebug):
		ss << "EnableDebug";
		break;
	case (pie::hac::kc::MiscFlagsBit::ForceDebug):
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
	case (pie::hac::kc::ProgramType::System):
		ss << "System";
		break;
	case (pie::hac::kc::ProgramType::Application):
		ss << "Application";
		break;
	case (pie::hac::kc::ProgramType::Applet):
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
	case (pie::hac::kc::MemoryPermission::Rw):
		ss << "Rw";
		break;
	case (pie::hac::kc::MemoryPermission::Ro):
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
	case (pie::hac::kc::MappingType::Io):
		ss << "Io";
		break;
	case (pie::hac::kc::MappingType::Static):
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
	case (pie::hac::kc::SystemCallId::Unknown0):
		ss << "Unknown0";
		break;
	case (pie::hac::kc::SystemCallId::SetHeapSize):
		ss << "SetHeapSize";
		break;
	case (pie::hac::kc::SystemCallId::SetMemoryPermission):
		ss << "SetMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId::SetMemoryAttribute):
		ss << "SetMemoryAttribute";
		break;
	case (pie::hac::kc::SystemCallId::MapMemory):
		ss << "MapMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapMemory):
		ss << "UnmapMemory";
		break;
	case (pie::hac::kc::SystemCallId::QueryMemory):
		ss << "QueryMemory";
		break;
	case (pie::hac::kc::SystemCallId::ExitProcess):
		ss << "ExitProcess";
		break;
	case (pie::hac::kc::SystemCallId::CreateThread):
		ss << "CreateThread";
		break;
	case (pie::hac::kc::SystemCallId::StartThread):
		ss << "StartThread";
		break;
	case (pie::hac::kc::SystemCallId::ExitThread):
		ss << "ExitThread";
		break;
	case (pie::hac::kc::SystemCallId::SleepThread):
		ss << "SleepThread";
		break;
	case (pie::hac::kc::SystemCallId::GetThreadPriority):
		ss << "GetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId::SetThreadPriority):
		ss << "SetThreadPriority";
		break;
	case (pie::hac::kc::SystemCallId::GetThreadCoreMask):
		ss << "GetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId::SetThreadCoreMask):
		ss << "SetThreadCoreMask";
		break;
	case (pie::hac::kc::SystemCallId::GetCurrentProcessorNumber):
		ss << "GetCurrentProcessorNumber";
		break;
	case (pie::hac::kc::SystemCallId::SignalEvent):
		ss << "SignalEvent";
		break;
	case (pie::hac::kc::SystemCallId::ClearEvent):
		ss << "ClearEvent";
		break;
	case (pie::hac::kc::SystemCallId::MapSharedMemory):
		ss << "MapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapSharedMemory):
		ss << "UnmapSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId::CreateTransferMemory):
		ss << "CreateTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId::CloseHandle):
		ss << "CloseHandle";
		break;
	case (pie::hac::kc::SystemCallId::ResetSignal):
		ss << "ResetSignal";
		break;
	case (pie::hac::kc::SystemCallId::WaitSynchronization):
		ss << "WaitSynchronization";
		break;
	case (pie::hac::kc::SystemCallId::CancelSynchronization):
		ss << "CancelSynchronization";
		break;
	case (pie::hac::kc::SystemCallId::ArbitrateLock):
		ss << "ArbitrateLock";
		break;
	case (pie::hac::kc::SystemCallId::ArbitrateUnlock):
		ss << "ArbitrateUnlock";
		break;
	case (pie::hac::kc::SystemCallId::WaitProcessWideKeyAtomic):
		ss << "WaitProcessWideKeyAtomic";
		break;
	case (pie::hac::kc::SystemCallId::SignalProcessWideKey):
		ss << "SignalProcessWideKey";
		break;
	case (pie::hac::kc::SystemCallId::GetSystemTick):
		ss << "GetSystemTick";
		break;
	case (pie::hac::kc::SystemCallId::ConnectToNamedPort):
		ss << "ConnectToNamedPort";
		break;
	case (pie::hac::kc::SystemCallId::SendSyncRequestLight):
		ss << "SendSyncRequestLight";
		break;
	case (pie::hac::kc::SystemCallId::SendSyncRequest):
		ss << "SendSyncRequest";
		break;
	case (pie::hac::kc::SystemCallId::SendSyncRequestWithUserBuffer):
		ss << "SendSyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId::SendAsyncRequestWithUserBuffer):
		ss << "SendAsyncRequestWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId::GetProcessId):
		ss << "GetProcessId";
		break;
	case (pie::hac::kc::SystemCallId::GetThreadId):
		ss << "GetThreadId";
		break;
	case (pie::hac::kc::SystemCallId::Break):
		ss << "Break";
		break;
	case (pie::hac::kc::SystemCallId::OutputDebugString):
		ss << "OutputDebugString";
		break;
	case (pie::hac::kc::SystemCallId::ReturnFromException):
		ss << "ReturnFromException";
		break;
	case (pie::hac::kc::SystemCallId::GetInfo):
		ss << "GetInfo";
		break;
	case (pie::hac::kc::SystemCallId::FlushEntireDataCache):
		ss << "FlushEntireDataCache";
		break;
	case (pie::hac::kc::SystemCallId::FlushDataCache):
		ss << "FlushDataCache";
		break;
	case (pie::hac::kc::SystemCallId::MapPhysicalMemory):
		ss << "MapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapPhysicalMemory):
		ss << "UnmapPhysicalMemory";
		break;
	case (pie::hac::kc::SystemCallId::GetDebugFutureThreadInfo):
		ss << "GetDebugFutureThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId::GetLastThreadInfo):
		ss << "GetLastThreadInfo";
		break;
	case (pie::hac::kc::SystemCallId::GetResourceLimitLimitValue):
		ss << "GetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId::GetResourceLimitCurrentValue):
		ss << "GetResourceLimitCurrentValue";
		break;
	case (pie::hac::kc::SystemCallId::SetThreadActivity):
		ss << "SetThreadActivity";
		break;
	case (pie::hac::kc::SystemCallId::GetThreadContext3):
		ss << "GetThreadContext3";
		break;
	case (pie::hac::kc::SystemCallId::WaitForAddress):
		ss << "WaitForAddress";
		break;
	case (pie::hac::kc::SystemCallId::SignalToAddress):
		ss << "SignalToAddress";
		break;
	case (pie::hac::kc::SystemCallId::SynchronizePreemptionState):
		ss << "SynchronizePreemptionState";
		break;
	case (pie::hac::kc::SystemCallId::Unknown55):
		ss << "Unknown55";
		break;
	case (pie::hac::kc::SystemCallId::Unknown56):
		ss << "Unknown56";
		break;
	case (pie::hac::kc::SystemCallId::Unknown57):
		ss << "Unknown57";
		break;
	case (pie::hac::kc::SystemCallId::Unknown58):
		ss << "Unknown58";
		break;
	case (pie::hac::kc::SystemCallId::Unknown59):
		ss << "Unknown59";
		break;
	case (pie::hac::kc::SystemCallId::KernelDebug):
		ss << "KernelDebug";
		break;
	case (pie::hac::kc::SystemCallId::ChangeKernelTraceState):
		ss << "ChangeKernelTraceState";
		break;
	case (pie::hac::kc::SystemCallId::Unknown62):
		ss << "Unknown62";
		break;
	case (pie::hac::kc::SystemCallId::Unknown63):
		ss << "Unknown63";
		break;
	case (pie::hac::kc::SystemCallId::CreateSession):
		ss << "CreateSession";
		break;
	case (pie::hac::kc::SystemCallId::AcceptSession):
		ss << "AcceptSession";
		break;
	case (pie::hac::kc::SystemCallId::ReplyAndReceiveLight):
		ss << "ReplyAndReceiveLight";
		break;
	case (pie::hac::kc::SystemCallId::ReplyAndReceive):
		ss << "ReplyAndReceive";
		break;
	case (pie::hac::kc::SystemCallId::ReplyAndReceiveWithUserBuffer):
		ss << "ReplyAndReceiveWithUserBuffer";
		break;
	case (pie::hac::kc::SystemCallId::CreateEvent):
		ss << "CreateEvent";
		break;
	case (pie::hac::kc::SystemCallId::Unknown70):
		ss << "Unknown70";
		break;
	case (pie::hac::kc::SystemCallId::Unknown71):
		ss << "Unknown71";
		break;
	case (pie::hac::kc::SystemCallId::MapPhysicalMemoryUnsafe):
		ss << "MapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId::UnmapPhysicalMemoryUnsafe):
		ss << "UnmapPhysicalMemoryUnsafe";
		break;
	case (pie::hac::kc::SystemCallId::SetUnsafeLimit):
		ss << "SetUnsafeLimit";
		break;
	case (pie::hac::kc::SystemCallId::CreateCodeMemory):
		ss << "CreateCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId::ControlCodeMemory):
		ss << "ControlCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId::SleepSystem):
		ss << "SleepSystem";
		break;
	case (pie::hac::kc::SystemCallId::ReadWriteRegister):
		ss << "ReadWriteRegister";
		break;
	case (pie::hac::kc::SystemCallId::SetProcessActivity):
		ss << "SetProcessActivity";
		break;
	case (pie::hac::kc::SystemCallId::CreateSharedMemory):
		ss << "CreateSharedMemory";
		break;
	case (pie::hac::kc::SystemCallId::MapTransferMemory):
		ss << "MapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapTransferMemory):
		ss << "UnmapTransferMemory";
		break;
	case (pie::hac::kc::SystemCallId::CreateInterruptEvent):
		ss << "CreateInterruptEvent";
		break;
	case (pie::hac::kc::SystemCallId::QueryPhysicalAddress):
		ss << "QueryPhysicalAddress";
		break;
	case (pie::hac::kc::SystemCallId::QueryIoMapping):
		ss << "QueryIoMapping";
		break;
	case (pie::hac::kc::SystemCallId::CreateDeviceAddressSpace):
		ss << "CreateDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId::AttachDeviceAddressSpace):
		ss << "AttachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId::DetachDeviceAddressSpace):
		ss << "DetachDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId::MapDeviceAddressSpaceByForce):
		ss << "MapDeviceAddressSpaceByForce";
		break;
	case (pie::hac::kc::SystemCallId::MapDeviceAddressSpaceAligned):
		ss << "MapDeviceAddressSpaceAligned";
		break;
	case (pie::hac::kc::SystemCallId::MapDeviceAddressSpace):
		ss << "MapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId::UnmapDeviceAddressSpace):
		ss << "UnmapDeviceAddressSpace";
		break;
	case (pie::hac::kc::SystemCallId::InvalidateProcessDataCache):
		ss << "InvalidateProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId::StoreProcessDataCache):
		ss << "StoreProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId::FlushProcessDataCache):
		ss << "FlushProcessDataCache";
		break;
	case (pie::hac::kc::SystemCallId::DebugActiveProcess):
		ss << "DebugActiveProcess";
		break;
	case (pie::hac::kc::SystemCallId::BreakDebugProcess):
		ss << "BreakDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId::TerminateDebugProcess):
		ss << "TerminateDebugProcess";
		break;
	case (pie::hac::kc::SystemCallId::GetDebugEvent):
		ss << "GetDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId::ContinueDebugEvent):
		ss << "ContinueDebugEvent";
		break;
	case (pie::hac::kc::SystemCallId::GetProcessList):
		ss << "GetProcessList";
		break;
	case (pie::hac::kc::SystemCallId::GetThreadList):
		ss << "GetThreadList";
		break;
	case (pie::hac::kc::SystemCallId::GetDebugThreadContext):
		ss << "GetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId::SetDebugThreadContext):
		ss << "SetDebugThreadContext";
		break;
	case (pie::hac::kc::SystemCallId::QueryDebugProcessMemory):
		ss << "QueryDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::ReadDebugProcessMemory):
		ss << "ReadDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::WriteDebugProcessMemory):
		ss << "WriteDebugProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::SetHardwareBreakPoint):
		ss << "SetHardwareBreakPoint";
		break;
	case (pie::hac::kc::SystemCallId::GetDebugThreadParam):
		ss << "GetDebugThreadParam";
		break;
	case (pie::hac::kc::SystemCallId::Unknown110):
		ss << "Unknown110";
		break;
	case (pie::hac::kc::SystemCallId::GetSystemInfo):
		ss << "GetSystemInfo";
		break;
	case (pie::hac::kc::SystemCallId::CreatePort):
		ss << "CreatePort";
		break;
	case (pie::hac::kc::SystemCallId::ManageNamedPort):
		ss << "ManageNamedPort";
		break;
	case (pie::hac::kc::SystemCallId::ConnectToPort):
		ss << "ConnectToPort";
		break;
	case (pie::hac::kc::SystemCallId::SetProcessMemoryPermission):
		ss << "SetProcessMemoryPermission";
		break;
	case (pie::hac::kc::SystemCallId::MapProcessMemory):
		ss << "MapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapProcessMemory):
		ss << "UnmapProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::QueryProcessMemory):
		ss << "QueryProcessMemory";
		break;
	case (pie::hac::kc::SystemCallId::MapProcessCodeMemory):
		ss << "MapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId::UnmapProcessCodeMemory):
		ss << "UnmapProcessCodeMemory";
		break;
	case (pie::hac::kc::SystemCallId::CreateProcess):
		ss << "CreateProcess";
		break;
	case (pie::hac::kc::SystemCallId::StartProcess):
		ss << "StartProcess";
		break;
	case (pie::hac::kc::SystemCallId::TerminateProcess):
		ss << "TerminateProcess";
		break;
	case (pie::hac::kc::SystemCallId::GetProcessInfo):
		ss << "GetProcessInfo";
		break;
	case (pie::hac::kc::SystemCallId::CreateResourceLimit):
		ss << "CreateResourceLimit";
		break;
	case (pie::hac::kc::SystemCallId::SetResourceLimitLimitValue):
		ss << "SetResourceLimitLimitValue";
		break;
	case (pie::hac::kc::SystemCallId::CallSecureMonitor):
		ss << "CallSecureMonitor";
		break;
	default:
		ss << "syscall_id_" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)syscall_id;
		break;
	}

	return ss.str();
}