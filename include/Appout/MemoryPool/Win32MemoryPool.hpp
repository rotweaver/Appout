#pragma once

#include "../Predef.hpp"
#include "MemoryPoolBase.hpp"

#if defined(APPOUT_WIN32)
namespace Appout
{
	class Win32MemoryPool : public MemoryPoolBase
	{
	private:


	public:
		bool init(size_t defaultAllocSize = 0);

		~Win32MemoryPool();

		void AllocateBlock() override;

		friend class x86Assembler;
		friend class Instance;
	};
}

#endif