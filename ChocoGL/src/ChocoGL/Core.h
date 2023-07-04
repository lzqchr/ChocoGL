#pragma once

#ifdef CL_PLATFORM_WINDOWS
	#ifdef CL_BUILD_DLL
		#define ChocoGL_API __declspec(dllexport)
	#else // CL_BUILD_DLL
		#define ChocoGL_API __declspec(dllimport)
	#endif
#endif

#define BIT(x) (1<<x)