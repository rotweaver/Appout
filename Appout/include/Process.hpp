#pragma once

#include <cstdint>

namespace Appout::Process
{
	bool WriteMemory(uintptr_t address, const void* buffer, size_t len);
}