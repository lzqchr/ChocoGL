#pragma once

#include <memory>
#ifdef CL_PLATFORM_WINDOWS
#if CL_DYNAMIC_LINK
	#ifdef CL_BUILD_DLL
		#define ChocoGL_API __declspec(dllexport)
	#else // CL_BUILD_DLL
		#define ChocoGL_API __declspec(dllimport)
	#endif
#else
#define ChocoGL_API
#endif
#else
	#error ChocoGL only supports Windows!
#endif


#ifdef CL_DEBUG
#define CL_ENABLE_ASSERTS
#endif

#ifdef CL_ENABLE_ASSERTS
#define CL_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CL_ERROR("Assertion Failed!"); __debugbreak(); } }
#define CL_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define CL_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro

#define CL_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
#define CL_CORE_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
#else
#define CL_ASSERT(...)
#define CL_CORE_ASSERT(...)
#endif

#define BIT(x) (1 << x)

#define CL_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

// Pointer wrappers
namespace ChocoGL {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	using byte = unsigned char;

}