#pragma once

#include <memory>
#include <string>

namespace Appout
{
	class Log
	{
	public:
		struct Severity
		{
		public:
			enum
			{
				/// <summary>
				/// Used for documenting control flow
				/// </summary>
				Trace,
				/// <summary>
				/// Used for documenting variable states
				/// </summary>
				Debug,
				/// <summary>
				/// Used for documenting normal behavior
				/// </summary>
				Info,
				/// <summary>
				/// Used for documenting unwanted process state but the given process can continue execution  
				/// </summary>
				Warn,
				/// <summary>
				/// Used for documenting unwanted process state but the given process can not continue execution  
				/// </summary>
				Error
			};

			using type = decltype(Trace);

			type Value;

			Severity(type value);
			operator int() const;
			Severity& operator=(type t);
			bool operator==(int other) const;
			bool operator==(const Severity& other) const;
			const char* ToString() const;
		};
		using Callback = void(*)(Log& log, std::string_view caller, std::string_view message, void* userdata);

		static std::shared_ptr<Log>& Instance();

		void SetCallback(const Severity& severity, Callback callback);
		Callback GetCallback(const Severity& severity) const;

		void SetUserData(void* value);
		void* GetUserData() const;

		void Write(const Severity& severity, std::string_view caller, std::string_view message);
		void WriteTrace(std::string_view caller, std::string_view message);
		void WriteDebug(std::string_view caller, std::string_view message);
		void WriteInfo(std::string_view caller, std::string_view message);
		void WriteWarn(std::string_view caller, std::string_view message);
		void WriteError(std::string_view caller, std::string_view message);

	private:
		static std::shared_ptr<Log> s_instance;
		Callback m_traceCallback = nullptr;
		Callback m_debugCallback = nullptr;
		Callback m_infoCallback = nullptr;
		Callback m_warnCallback = nullptr;
		Callback m_errorCallback = nullptr;

		void* m_userData = nullptr;
	};
}