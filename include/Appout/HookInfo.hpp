#pragma once

#include <cstdint>


namespace Appout
{
	class HookInfo
	{
	private:
		uintptr_t m_origAddress = 0;
	public:
		HookInfo(uintptr_t address);

		uintptr_t GetAddress() const;
	};
}