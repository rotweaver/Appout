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

		Win32MemoryPool();
		void AllocateBlock() override;

		friend class x86Assembler;
	};
}

#endif