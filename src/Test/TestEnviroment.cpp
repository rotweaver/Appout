#include "TestEnviroment.hpp"

#include <iostream>
#include <format>

using namespace Appout;

std::shared_ptr<TestEnviroment> TestEnviroment::s_instance = nullptr;

std::shared_ptr<TestEnviroment>& TestEnviroment::Instance(int argc, char* argv[])
{
	if (!s_instance)
	{
		s_instance = std::make_shared<TestEnviroment>(argc, argv);
	}

	return s_instance;
}

TestEnviroment::TestEnviroment(int argc, char* argv[])
{
	if (s_instance != nullptr)
		return; // Nothing to do

	std::cout << std::format("Creating test enviroment with {} args.", argc) << std::endl;

	m_programArguments.reserve(argc);

	for (int i = 0; i < argc; i++)
		m_programArguments.push_back(std::string(argv[i]));

}

TestEnviroment::~TestEnviroment()
{
	std::cout << "Test Enviroment DTOR" << std::endl;
}