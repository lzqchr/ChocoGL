#include "clpch.h"
#include "Log.h"


namespace ChocoGL {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//spdlog::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
	//	spdlog::set_pattern("%^[%T]%n:%v%$");
		spdlog::set_pattern("[multi_sink_example] [%^%l%$] %v");
		s_CoreLogger = spdlog::stdout_color_mt("ChocoGL");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}