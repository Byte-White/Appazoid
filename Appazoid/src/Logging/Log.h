#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace az 
{

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define APPAZOID_CORE_TRACE(...)    ::az::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define APPAZOID_CORE_INFO(...)     ::az::Log::GetCoreLogger()->info(__VA_ARGS__)
#define APPAZOID_CORE_WARN(...)     ::az::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define APPAZOID_CORE_ERROR(...)    ::az::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define APPAZOID_TRACE(...)	      ::az::Log::GetClientLogger()->trace(__VA_ARGS__)
#define APPAZOID_INFO(...)	      ::az::Log::GetClientLogger()->info(__VA_ARGS__)
#define APPAZOID_WARN(...)	      ::az::Log::GetClientLogger()->warn(__VA_ARGS__)
#define APPAZOID_ERROR(...)	      ::az::Log::GetClientLogger()->error(__VA_ARGS__)