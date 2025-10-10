#pragma once


#include "MemoryPoolBase.hpp"

namespace Appout
{
	class Win32MemoryPool : public MemoryPoolBase
	{
	private:

	public:

		Win32MemoryPool();
		void AllocateBlock() override;

		friend class x86Assembler;
	};
}