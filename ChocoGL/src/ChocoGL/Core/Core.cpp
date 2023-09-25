#include "clpch.h"
#include "Core.h"

#include "Log.h"

#define ChocoGL_BUILD_ID "v0.2a"

namespace ChocoGL {

	void InitializeCore()
	{
		ChocoGL::Log::Init();

		CL_CORE_TRACE("ChocoGL Engine {}", ChocoGL_BUILD_ID);
		CL_CORE_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		CL_CORE_TRACE("Shutting down...");
	}

}