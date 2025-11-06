#pragma once

#include <vector>
#include <string>
#include <memory>

namespace Appout
{
	class TestEnviroment
	{
	public:
		static std::shared_ptr<TestEnviroment>& Instance(int argc = 0, char* argv[] = nullptr);

		TestEnviroment(int argc, char* argv[]);
		~TestEnviroment();
	private:
		static std::shared_ptr<TestEnviroment> s_instance;

		std::vector<std::string> m_programArguments = {};
	};

#ifdef APPOUT_ARCH_X86
	void RunX86Tests();
#endif // APPOUT_ARCH_X86

}