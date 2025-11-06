#pragma once

#include "Predef.hpp"

#include <string>
#include <format>
#include <source_location>

namespace Appout
{
#ifdef __cpp_lib_source_location
	std::string CurrentSourceLocation(const std::source_location& location = std::source_location::current());
#endif
}