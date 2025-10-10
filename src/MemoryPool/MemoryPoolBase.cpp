#include <Appout/MemoryPool/MemoryPoolBase.hpp>

using namespace Appout;

#pragma region Iterator
MemoryPoolBase::Iterator::Iterator(pointer pointer) : m_pointer(pointer)
{

}

MemoryPoolBase::Iterator::reference MemoryPoolBase::Iterator::operator*()
{
	return *m_pointer;
}
MemoryPoolBase::Iterator::pointer MemoryPoolBase::Iterator::operator->()
{
	return m_pointer;
}

MemoryPoolBase::Iterator& MemoryPoolBase::Iterator::operator++()
{
	m_pointer++;
	return *this;
}
MemoryPoolBase::Iterator MemoryPoolBase::Iterator::operator++(int)
{
	auto temp = *this;
	++(*this);
	return temp;
}

#pragma endregion

MemoryPoolBase::Iterator MemoryPoolBase::begin()
{
	return Iterator(&(*m_memoryBlocks.begin()));
}
MemoryPoolBase::Iterator MemoryPoolBase::end()
{
	return Iterator(&(*m_memoryBlocks.end()));
}

MemoryBlock& MemoryPoolBase::CurrentBlock()
{
	return m_memoryBlocks[m_currentBlock];
}

size_t MemoryPoolBase::GetBlockCount() const
{
	return m_memoryBlocks.size();
}
size_t MemoryPoolBase::GetDefaultAllocationSize() const
{
	return m_defaultAllocationSize;
}


size_t MemoryPoolBase::GetFreeBlockSpace(size_t blockID) const
{
	return m_memoryBlocks[blockID].GetFreeSpace();
}

size_t MemoryPoolBase::GetFreeSpace() const
{
	//size_t size = 0;

	//for (auto it = m_memoryBlocks.begin(); it != m_memoryBlocks.end(); it++)
	//{
	//	size += it->FreeSpace;
	//}

	//return size;

	return m_memoryBlocks[m_currentBlock].GetFreeSpace();
}

size_t MemoryPoolBase::GetTotalFreeSpace() const
{
	size_t size = 0;

	for (auto it = m_memoryBlocks.begin(); it != m_memoryBlocks.end(); it++)
		size += it->GetFreeSpace();

	return size;
}