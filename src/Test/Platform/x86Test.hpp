#pragma once

#ifdef APPOUT_TEST_ARCH_X86

#include <Appout.hpp>

namespace Appout::x86Tests
{
	bool TestCDeclHook();

	bool TestSTDCallHook();

}
#endif // APPOUT_TEST_ARCH_X86