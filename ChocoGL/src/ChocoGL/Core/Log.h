#pragma once


#include "clpch.h"

#include"Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
//#include "spdlog/sinks/stdout_sinks.h"



namespace ChocoGL {
	class  Log
	{
	public :
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


		

	};
}


#define CL_CORE_TRACE(...) ::ChocoGL::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CL_CORE_INFO(...) ::ChocoGL::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CL_CORE_WARN(...) ::ChocoGL::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CL_CORE_ERROR(...) ::ChocoGL::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CL_CORE_FATAL(...) ::ChocoGL::Log::GetCoreLogger()->fatal(__VA_ARGS__)


#define CL_TRACE(...) ::ChocoGL::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CL_INFO(...)  ::ChocoGL::Log::GetClientLogger()->info(__VA_ARGS__)
#define CL_WARN(...)  ::ChocoGL::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CL_ERROR(...) ::ChocoGL::Log::GetClientLogger()->error(__VA_ARGS__)
#define CL_FATAL(...) ::ChocoGL::Log::GetClientLogger()->fatal(__VA_ARGS__)