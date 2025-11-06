#pragma once

#include <string_view>

#include <Appout/MemoryPool/Win32MemoryPool.hpp>

namespace Appout
{
	using LogCallback = void(*)(std::string_view caller, std::string_view message, void* userdata);

	class Instance
	{
	public:
		static Instance* Get();
		
		bool Initialize();

		void SetLogCallback(LogCallback callback, void* userData = nullptr);
		const LogCallback GetLogCallback() const;

		Win32MemoryPool& MemoryPool() const;

		void WriteLog(std::string_view caller, std::string_view message);
	private:
		LogCallback m_logCallback = nullptr;
		void* m_logUserData = nullptr;
		bool m_initialized = false;

		Win32MemoryPool* m_pool;
	};
}