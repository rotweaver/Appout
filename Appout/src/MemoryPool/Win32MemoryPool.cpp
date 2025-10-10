#include <Appout/MemoryPool/Win32MemoryPool.hpp>

#include <Windows.h>

#include <assert.h>

using namespace Appout;

Win32MemoryPool::Win32MemoryPool()
{
	SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);

	m_defaultAllocationSize = system_info.dwPageSize;

	AllocateBlock();
	m_currentBlock--;
}

void Win32MemoryPool::AllocateBlock()
{
	uintptr_t block = reinterpret_cast<uintptr_t>(VirtualAlloc(NULL, m_defaultAllocationSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

	if (block == 0)
	{
		// TODO: report error
		throw new std::exception("Block was null!");
	}

	assert(block != 0);

	DWORD dummy;
	if (!VirtualProtect(reinterpret_cast<void*>(block), m_defaultAllocationSize, PAGE_EXECUTE_READWRITE, &dummy))
	{
		// TODO: report error
	}

	std::memset(reinterpret_cast<void*>(block), 0xCC, m_defaultAllocationSize);


	m_memoryBlocks.push_back(MemoryBlock(block, m_defaultAllocationSize));
	m_currentBlock++;
}