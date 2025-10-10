#pragma once

#include "../MemoryPool/MemoryPoolBase.hpp"

#include <iterator>
#include <cstddef>


namespace Appout
{
	class AssemblerBase
	{
	protected:
		MemoryPoolBase& m_memoryPool;

		size_t m_currentWriteSize = 0;

		void checkFitsInBlock();

		template <typename T>
		void writePrimitive(T value);
	public:

		AssemblerBase(MemoryPoolBase& memoryPool);

		void Write(std::uint8_t value);
		void Write(std::int8_t value);
		void Write(std::uint16_t value);
		void Write(std::int8_t value);
		void Write(std::uint32_t value);
		void Write(std::int32_t value);
		void Write(std::uint64_t value);
		void Write(std::int64_t value);
		void Write(float value);
	};

}



template <typename T>
void Appout::AssemblerBase::writePrimitive(T value)
{
	m_currentWriteSize += sizeof(value);

	checkFitsInBlock();

	m_memoryPool.CurrentBlock().Write(value);
}