#include <Appout/Instance.hpp>

using namespace Appout;

Instance* Instance::Get()
{
	static Instance* s_singleton = new Instance();
	return s_singleton;
}

bool Instance::Initialize()
{
	m_pool = new Win32MemoryPool();

	m_initialized = true;
	return true;
}
void Instance::SetLogCallback(LogCallback callback, void* userData)
{
	m_logCallback = callback;
	m_logUserData = userData;
}
const LogCallback Instance::GetLogCallback() const
{
	return m_logCallback;
}

Win32MemoryPool& Instance::MemoryPool() const
{
	return *m_pool;
}
void Instance::WriteLog(std::string_view caller, std::string_view message)
{
	if (m_logCallback != nullptr)
		m_logCallback(caller, message, m_logUserData);
}