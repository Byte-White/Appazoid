#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace az 
{

	class Log
	{
	public:
		static void Init(std::string pattern = "%^[%T] %n: %v%$");

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
//define AZ_NO_LOGGING to disable all logging macros

#ifdef AZ_NO_LOGGING
	#define AZ_NO_CORE_LOGGING
	#define AZ_NO_CLIENT_LOGGING
#endif
#ifndef AZ_NO_CORE_LOGGING
	// Core log macros
	#define APPAZOID_CORE_TRACE(...)		::az::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define APPAZOID_CORE_INFO(...)			::az::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define APPAZOID_CORE_WARN(...)			::az::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define APPAZOID_CORE_ERROR(...)		::az::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define APPAZOID_CORE_CRITICAL(...)		::az::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
	#define APPAZOID_CORE_TRACE(...)
	#define APPAZOID_CORE_INFO(...)
	#define APPAZOID_CORE_WARN(...)
	#define APPAZOID_CORE_ERROR(...)
	#define APPAZOID_CORE_CRITICAL(...)
#endif

#ifndef AZ_NO_CLIENT_LOGGING
	// Client log macros
	#define APPAZOID_TRACE(...)				::az::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define APPAZOID_INFO(...)				::az::Log::GetClientLogger()->info(__VA_ARGS__)
	#define APPAZOID_WARN(...)				::az::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define APPAZOID_ERROR(...)				::az::Log::GetClientLogger()->error(__VA_ARGS__)
	#define APPAZOID_CRITICAL(...)			::az::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define APPAZOID_TRACE(...)
	#define APPAZOID_INFO(...)
	#define APPAZOID_WARN(...)
	#define APPAZOID_ERROR(...)
	#define APPAZOID_CRITICAL(...)
#endif