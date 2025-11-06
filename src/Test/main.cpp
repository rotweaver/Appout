#ifdef APPOUT_BUILD_TESTS

#include <Appout.hpp>

#include <iostream>
#include <string>

#include "TestEnviroment.hpp"

#include "Platform/x86Test.hpp"

void traceCallback(Appout::Log& log, std::string_view caller, std::string_view message, void* userdata)
{
	std::cout << std::format("TRACE [{}] {}", caller, message) << std::endl;
}
void debugCallback(Appout::Log& log, std::string_view caller, std::string_view message, void* userdata)
{
	std::cout << std::format("DEBUG [{}] {}", caller, message) << std::endl;
}
void infoCallback(Appout::Log& log, std::string_view caller, std::string_view message, void* userdata)
{
	std::cout << std::format("INFO  [{}] {}", caller, message) << std::endl;
}
void warnCallback(Appout::Log& log, std::string_view caller, std::string_view message, void* userdata)
{
	std::cout << std::format("WARN  [{}] {}", caller, message) << std::endl;
}
void errorCallback(Appout::Log& log, std::string_view caller, std::string_view message, void* userdata)
{
	std::cout << std::format("ERROR [{}] {}", caller, message) << std::endl;
}


int __cdecl CDECLFUNC(int a, int b)
{
	return 1;
}

int __stdcall STDCALLFUNC(int a, int b)
{
	return CDECLFUNC(a, b);
}

int main(int argc, char* argv[])
{
	auto testEnviroment = Appout::TestEnviroment::Instance(argc, argv);
	auto log = Appout::Log::Instance();

	log->SetCallback(Appout::Log::Severity::Trace, traceCallback);
	log->SetCallback(Appout::Log::Severity::Debug, debugCallback);
	log->SetCallback(Appout::Log::Severity::Info, infoCallback);
	log->SetCallback(Appout::Log::Severity::Warn, warnCallback);
	log->SetCallback(Appout::Log::Severity::Error, errorCallback);


	if (!Appout::x86Tests::TestCDeclHook())
	{
		std::cout << "CDECL HOOK FAILED!" << std::endl;
	}
	else
		std::cout << "CDECL HOOK SUCCESS" << std::endl;

	std::cout << "Hello Cmake" << std::endl;
	std::cin;
}

#endif // APPOUT_BUILD_TESTS
