#include <Appout/MemoryPool/Win32MemoryPool.hpp>

#if defined(APPOUT_WIN32)

#include <Appout/Debug.hpp>
#include <Appout/Instance.hpp>
#include <Appout/Log.hpp>

#include <Windows.h>

#include <assert.h>
#include <format>
#include <iostream>


using namespace Appout;


bool Win32MemoryPool::init(size_t defaultAllocSize)
{
	auto log = Log::Instance();

	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	if (defaultAllocSize != system_info.dwPageSize)
	{
		//Instance::Get()->WriteLog("Win32MemoryPool", std::format("defaultAllocSize {:X4} does not match system_info.dwPageSize {:X4}", defaultAllocSize, system_info.dwPageSize));
	}

	m_defaultAllocationSize = system_info.dwPageSize;

	AllocateBlock();
	m_currentBlock = 0;

	return (m_initialized = true);
}

Win32MemoryPool::~Win32MemoryPool()
{
	auto log = Log::Instance();

	for (auto it = m_memoryBlocks.begin(); it != m_memoryBlocks.end(); it++)
	{
		uintptr_t baseAddress = 0;
		size_t size = 0;
		try
		{
			baseAddress = it->GetBaseAddress();
			size = it->GetSize();

			auto result = VirtualFree(reinterpret_cast<LPVOID>(baseAddress), 0, MEM_RELEASE);

			if (!result)
				log->WriteWarn(CurrentSourceLocation(), std::format("Unable to free Win32 block @ {:#04x} size: {:#04x}! This will result in memory leakage!", baseAddress, size));
			else
				log->WriteInfo(CurrentSourceLocation(), std::format("Freed Win32 block @ {:#04x} size: {:#04x}", baseAddress, size));
		}
		catch(...)
		{
			try
			{
				std::rethrow_exception(std::current_exception());
			}
			catch (const std::exception& e)
			{
				log->WriteError(CurrentSourceLocation(), e.what());
			}
		}
	}
}

void Win32MemoryPool::AllocateBlock()
{
	auto log = Log::Instance();

	uintptr_t block = reinterpret_cast<uintptr_t>(VirtualAlloc(NULL, m_defaultAllocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

	if (block == 0)
	{
		log->WriteError(CurrentSourceLocation(), std::format("Unable to VirtualAlloc page with size: {:#04x}", m_defaultAllocationSize));
		return;
	}

	log->WriteInfo(CurrentSourceLocation(), std::format("Created VirtualAlloc page @ {:#04x}with size: {:#04x}", block, m_defaultAllocationSize));

	assert(block != 0);

	DWORD dummy;
	if (!VirtualProtect(reinterpret_cast<void*>(block), m_defaultAllocationSize, PAGE_EXECUTE_READWRITE, &dummy))
	{
		log->WriteError(CurrentSourceLocation(), std::format("Unable to change page protection to PAGE_EXECUTE_READWRITE", m_defaultAllocationSize));
		VirtualFree(reinterpret_cast<LPVOID>(block), 0, MEM_FREE);
		return;
	}

	std::memset(reinterpret_cast<void*>(block), 0xCC, m_defaultAllocationSize);

	m_memoryBlocks.push_back(MemoryBlock(block, m_defaultAllocationSize));
	m_currentBlock++;
}

#endif