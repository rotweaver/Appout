#include <Appout/Log.hpp>

using namespace Appout;

Log::Severity::Severity(type value)
{
	Value = value;
}

Log::Severity::operator int() const
{
	return Value;
}
Log::Severity& Log::Severity::operator=(type t)
{
	Value = t;

	return *this;
}
bool Log::Severity::operator==(int other) const
{
	return Value == other;
}
bool Log::Severity::operator==(const Severity& other) const
{
	return Value == other.Value;
}
const char* Log::Severity::ToString() const
{
	switch (Value)
	{
	case Trace:
		return "Trace";
	case Debug:
		return "Debug";
	case Info:
		return "Info";
	case Warn:
		return "Warn";
	case Error:
		return "Error";
	default:
		return "UNDOCUMENTED!!! REPORT THIS";
	}
}



std::shared_ptr<Log> Log::s_instance = nullptr;

std::shared_ptr<Log>& Log::Instance()
{
	if (!s_instance)
		s_instance = std::make_shared<Log>();

	return s_instance;
}

void Log::SetCallback(const Severity& severity, Callback callback)
{
	switch (severity)
	{
	case Severity::Trace:
		m_traceCallback = callback;
		break;
	case Severity::Debug:
		m_debugCallback = callback;
		break;
	case Severity::Info:
		m_infoCallback = callback;
		break;
	case Severity::Warn:
		m_warnCallback = callback;
		break;
	case Severity::Error:
		m_errorCallback = callback;
		break;
	}
}
Log::Callback Log::GetCallback(const Severity& severity) const
{
	switch (severity)
	{
	case Severity::Trace:
		return m_traceCallback;
	case Severity::Debug:
		return m_debugCallback;
	case Severity::Info:
		return m_infoCallback;
	case Severity::Warn:
		return m_warnCallback;
	case Severity::Error:
		return m_errorCallback;
	default:
		return nullptr;
	}
}

void Log::SetUserData(void* value)
{
	m_userData = value;
}
void* Log::GetUserData() const
{
	return m_userData;
}

void Log::Write(const Severity& severity, std::string_view caller, std::string_view message)
{
	switch (severity)
	{
	case Severity::Trace:
		if (m_traceCallback == nullptr)
			return;
		m_traceCallback(*this, caller, message, m_userData);
		break;
	case Severity::Debug:
		if (m_debugCallback == nullptr)
			return;
		m_debugCallback(*this, caller, message, m_userData);
		break;
	case Severity::Info:
		if (m_infoCallback == nullptr)
			return;
		m_infoCallback(*this, caller, message, m_userData);
		break;
	case Severity::Warn:
		if (m_warnCallback == nullptr)
			return;
		m_warnCallback(*this, caller, message, m_userData);
		break;
	case Severity::Error:
		if (m_errorCallback == nullptr)
			return;
		m_errorCallback(*this, caller, message, m_userData);
		break;
	}

}
void Log::WriteTrace(std::string_view caller, std::string_view message)
{
	if (m_traceCallback == nullptr)
		return;
	m_traceCallback(*this, caller, message, m_userData);
}
void Log::WriteDebug(std::string_view caller, std::string_view message)
{
	if (m_debugCallback == nullptr)
		return;
	m_debugCallback(*this, caller, message, m_userData);
}
void Log::WriteInfo(std::string_view caller, std::string_view message)
{
	if (m_infoCallback == nullptr)
		return;
	m_infoCallback(*this, caller, message, m_userData);
}
void Log::WriteWarn(std::string_view caller, std::string_view message)
{
	if (m_warnCallback == nullptr)
		return;
	m_warnCallback(*this, caller, message, m_userData);
}
void Log::WriteError(std::string_view caller, std::string_view message)
{
	if (m_errorCallback == nullptr)
		return;
	m_errorCallback(*this, caller, message, m_userData);
}