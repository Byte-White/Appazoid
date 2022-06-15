#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace az 
{

	class Log
	{
	public:
		static void Init(const std::string& pattern = "%^[%T] %n: %v%$");

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
		
		//CORE LOG FNS

		template<typename... Args>
		inline static void CoreTrace(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			
			GetCoreLogger()->trace(fmt, args...);
		}

		template<typename... Args>
		inline static void CoreInfo(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetCoreLogger()->info(fmt, args...);
		}
		template<typename... Args>
		inline static void CoreWarn(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetCoreLogger()->warn(fmt, args...);
		}
		template<typename... Args>
		inline static void CoreError(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetCoreLogger()->error(fmt, args...);
		}
		template<typename... Args>
		inline static void CoreCritical(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetCoreLogger()->critical(fmt, args...);
		}

		template<typename... Args>
		inline static void CoreDebug(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetCoreLogger()->debug(fmt, args...);
		}


		//CLIENT LOG FNS
		template<typename... Args>
		inline static void Trace(spdlog::format_string_t<Args...> fmt, Args &&... args) 
		{ GetClientLogger()->trace(fmt,args...); }

		template<typename... Args>
		inline static void Info(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetClientLogger()->info(fmt, args...);
		}
		template<typename... Args>
		inline static void Warn(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetClientLogger()->warn(fmt, args...);
		}
		template<typename... Args>
		inline static void Error(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetClientLogger()->error(fmt, args...);
		}
		template<typename... Args>
		inline static void Critical(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetClientLogger()->critical(fmt, args...);
		}

		template<typename... Args>
		inline static void Debug(spdlog::format_string_t<Args...> fmt, Args &&... args)
		{
			GetClientLogger()->debug(fmt, args...);
		}

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
	#define APPAZOID_CORE_TRACE(...)		az::Log::CoreTrace(__VA_ARGS__)
	#define APPAZOID_CORE_INFO(...)			az::Log::CoreInfo(__VA_ARGS__)
	#define APPAZOID_CORE_WARN(...)			az::Log::CoreWarn(__VA_ARGS__)
	#define APPAZOID_CORE_ERROR(...)		az::Log::CoreError(__VA_ARGS__)
	#define APPAZOID_CORE_CRITICAL(...)		az::Log::CoreCritical(__VA_ARGS__)
	#define APPAZOID_CORE_DEBUG(...)		az::Log::CoreDebug(__VA_ARGS__)
#else
	#define APPAZOID_CORE_TRACE(...)
	#define APPAZOID_CORE_INFO(...)
	#define APPAZOID_CORE_WARN(...)
	#define APPAZOID_CORE_ERROR(...)
	#define APPAZOID_CORE_CRITICAL(...)
	#define APPAZOID_CORE_DEBUG(...)		
#endif

#ifndef AZ_NO_CLIENT_LOGGING
	// Client log macros
	#define APPAZOID_TRACE(...)				az::Log::Trace(__VA_ARGS__)
	#define APPAZOID_INFO(...)				az::Log::Info(__VA_ARGS__)
	#define APPAZOID_WARN(...)				az::Log::Warn(__VA_ARGS__)
	#define APPAZOID_ERROR(...)				az::Log::Error(__VA_ARGS__)
	#define APPAZOID_CRITICAL(...)			az::Log::Critical(__VA_ARGS__)
	#define APPAZOID_DEBUG(...)				az::Log::Debug(__VA_ARGS__)
#else
	#define APPAZOID_TRACE(...)
	#define APPAZOID_INFO(...)
	#define APPAZOID_WARN(...)
	#define APPAZOID_ERROR(...)
	#define APPAZOID_CRITICAL(...)
	#define APPAZOID_DEBUG(...)			
#endif