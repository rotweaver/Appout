#include <Appout/Process.hpp>

#include <Windows.h>

HANDLE s_currentProcess = nullptr;

bool Appout::Process::WriteMemory(uintptr_t address, const void* buffer, size_t len)
{
	if (s_currentProcess == nullptr)
		s_currentProcess = GetCurrentProcess();

	return WriteProcessMemory(
		s_currentProcess,
		reinterpret_cast<LPVOID>(address),
		buffer,
		len,
		nullptr);
}
