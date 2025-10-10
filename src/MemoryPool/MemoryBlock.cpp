#include <Appout/MemoryPool/MemoryBlock.hpp>

using namespace Appout;


MemoryBlock::MemoryBlock(uintptr_t baseAddress, size_t freeSpace)
{
	m_baseAddress = baseAddress;
	m_freeSpace = freeSpace;
	m_stackPointer = baseAddress;
}

uintptr_t MemoryBlock::GetCurrentAddress() const
{
	return m_stackPointer;
}
uintptr_t MemoryBlock::GetBaseAddress() const
{
	return m_baseAddress;
}
size_t MemoryBlock::GetFreeSpace() const
{
	return m_freeSpace;
}

void MemoryBlock::Transfer(MemoryBlock& dst, size_t size)
{
	if (dst.m_freeSpace < size)
	{
		throw new std::exception("dst doesn't have enough memory to support the operation");
	}

	std::memcpy(reinterpret_cast<void*>(dst.m_stackPointer), reinterpret_cast<void*>(m_stackPointer), size);

	m_stackPointer -= size;
	m_freeSpace += size;

	dst.m_stackPointer += size;
	dst.m_freeSpace -= size;
}

void MemoryBlock::Write(std::uint8_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::int8_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::uint16_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::int16_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::uint32_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::int32_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::uint64_t value) { writePrimitive(value); }
void MemoryBlock::Write(std::int64_t value) { writePrimitive(value); }
void MemoryBlock::Write(float value) { writePrimitive(value); }