#include <Appout/HookInfo.hpp>

using namespace Appout;

HookInfo::HookInfo(uintptr_t address)
{
	m_origAddress = address;
}
uintptr_t HookInfo::GetAddress() const
{
	return m_origAddress;
}