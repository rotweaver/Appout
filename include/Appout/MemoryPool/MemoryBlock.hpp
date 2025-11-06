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
		size_t m_size;
	public:
		MemoryBlock(uintptr_t baseAddress, size_t freeSpace);

		/// <summary>
		/// The Size of the block
		/// </summary>
		/// <returns>The size in bytes of the block</returns>
		size_t GetSize() const;

		/// <summary>
		/// The current offset into the block
		/// </summary>
		/// <returns>An absolute address of the next free byte in the block</returns>
		uintptr_t GetCurrentAddress() const;
		/// <summary>
		/// The underlying pointer
		/// </summary>
		/// <returns>The start of the memory block's address space</returns>
		uintptr_t GetBaseAddress() const;

		/// <summary>
		/// How many bytes are in the memory block
		/// </summary>
		/// <returns>The number of empty bytes left in the block</returns>
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

	std::memcpy(reinterpret_cast<void*>(m_stackPointer), &value, sizeof(T));

	m_stackPointer += sizeof(value);
	m_freeSpace -= sizeof(value);
}