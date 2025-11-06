#pragma once

#include "../MemoryPool/MemoryPoolBase.hpp"

#include <iterator>
#include <cstddef>


namespace Appout
{
	class AssemblerBase
	{
	protected:
		MemoryPoolBase* m_memoryPool = nullptr;
		uintptr_t m_address = 0;

		size_t m_currentWriteSize = 0;

		void checkFitsInBlock();


		template<typename T>
		void writePrimitive(T value);

	public:

		AssemblerBase(uintptr_t address);
		AssemblerBase(MemoryPoolBase& memoryPool);
	};


	template<typename T>
	void Appout::AssemblerBase::writePrimitive(T value)
	{
		if (m_memoryPool != nullptr)
		{
			m_memoryPool->CurrentBlock().Write(value); // TODO: will fail for non primitives!
		}
		else
		{
			std::memcpy(m_address + m_currentWriteSize, &value, sizeof(T));
		}
		m_currentWriteSize += sizeof(T);
	}

}