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
	public:

		AssemblerBase(MemoryPoolBase& memoryPool);
	};

}