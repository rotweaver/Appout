#ifdef APPOUT_TEST_ARCH_X86
#include "x86Test.hpp"

#include <Appout.hpp>
#include <format>

using namespace Appout;

void __cdecl cdeclFunction(int a)
{
	auto log = Appout::Log::Instance();

	log->WriteInfo(CurrentSourceLocation(), "Hello!");
}

void __cdecl HookFunctionA(FunctionBinding<void, int> binding, int a)
{
	auto log = Appout::Log::Instance();

	log->WriteInfo(CurrentSourceLocation(), std::format("a: {} hooks: {}", a, binding.GetHookCount()));

	binding(a); // calls next hook
}
void __cdecl HookFunctionB(FunctionBinding<void, int> binding, int a)
{
	auto log = Appout::Log::Instance();

	log->WriteInfo(CurrentSourceLocation(), std::format("a: {} hooks: {}", a, binding.GetHookCount()));

	binding(a); // calls next hook
}

bool x86Tests::TestCDeclHook()
{
	auto log = Appout::Log::Instance();

	Win32MemoryPool memPool = Win32MemoryPool();


	if (!memPool.init())
	{
		log->WriteError(CurrentSourceLocation(), "Unable to initialize Win32MemoryPool");
		return false;
	}
	log->WriteInfo(CurrentSourceLocation(), "Initialized Win32MemoryPool");


	FunctionBinding<void, int> binding = { cdeclFunction }; // Will be some function addr in the exe


	binding.createWrapper();

	binding += HookFunctionA;
	binding += HookFunctionB;

	binding(3); // calls all hooks and the orig


	return true;
}


bool x86Tests::TestSTDCallHook()
{
	auto log = Appout::Log::Instance();

	Win32MemoryPool memPool = Win32MemoryPool();


	if (!memPool.init())
	{
		log->WriteError(CurrentSourceLocation(), "Unable to initialize Win32MemoryPool");
		return false;
	}
	log->WriteInfo(CurrentSourceLocation(), "Initialized Win32MemoryPool");


	FunctionBinding<void, int> binding = { cdeclFunction }; // Will be some function addr in the exe

	binding += HookFunctionA;
	binding += HookFunctionB;

	binding(3);


	return true;
}

#endif // APPOUT_TEST_ARCH_X86