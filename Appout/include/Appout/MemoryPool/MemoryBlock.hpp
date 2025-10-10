#pragma once

#include <cstdint>
#include <exception>
#include <memory>

namespace Appout
{
	class MemoryBlock
	{
	private:
		template<typename T>
		void writePrimitive(T value);

		uintptr_t m_baseAddress;
		uintptr_t m_stackPointer;
		size_t m_freeSpace;

	public:
		MemoryBlock(uintptr_t baseAddress, size_t freeSpace);



		uintptr_t GetCurrentAddress() const;
		uintptr_t GetBaseAddress() const;
		size_t GetFreeSpace() const;

		void Transfer(MemoryBlock& dst, size_t size);

		void Write(std::uint8_t value);
		void Write(std::int8_t value);
		void Write(std::uint16_t value);
		void Write(std::int16_t value);
		void Write(std::uint32_t value);
		void Write(std::int32_t value);
		void Write(std::uint64_t value);
		void Write(std::int64_t value);
		void Write(float value);
	};
}




template<typename T>
void Appout::MemoryBlock::writePrimitive(T value)
{
	if (sizeof(value) > m_freeSpace)
	{
		throw new std::exception("Memory Block is out of memory!!");
	}

	// maybe look into intrinsics later? depending on speed

	std::memcpy(reinterpret_cast<void*>(m_stackPointer), &value, sizeof(value));

	m_stackPointer += sizeof(value);
	m_freeSpace -= sizeof(value);

}