#include <Appout/Debug.hpp>

std::string Appout::CurrentSourceLocation(const std::source_location& location)
{
	return std::format("{}({}:{})", location.function_name(), location.line(), location.column());
}