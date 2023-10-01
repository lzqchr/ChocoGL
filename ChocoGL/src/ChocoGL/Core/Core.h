#pragma once

#pragma once

#include <memory>

namespace ChocoGL {

	void InitializeCore();
	void ShutdownCore();

}
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


// __VA_ARGS__ expansion to get past MSVC "bug"
#define CL_EXPAND_VARGS(x) x

#define BIT(x) (1 << x)

#define CL_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

#include "Assert.h"

// Pointer wrappers
namespace ChocoGL {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;

}



//#include <memory>
//
//#ifdef CL_PLATFORM_WINDOWS
//#if CL_DYNAMIC_LINK
//#ifdef CL_BUILD_DLL
//#define ChocoGL_API __declspec(dllexport)
//#else // CL_BUILD_DLL
//#define ChocoGL_API __declspec(dllimport)
//#endif
//#else
//#define ChocoGL_API
//#endif
//#else
//#error ChocoGL only supports Windows!
//#endif
//
//#define CL_EXPAND_VARGS(x) x
//
//#define BIT(x) (1 << x)
//
//#define CL_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)
//
//#include "Assert.h"
//// Pointer wrappers
//namespace ChocoGL {
//
//	template<typename T>
//	using Scope = std::unique_ptr<T>;
//
//	template<typename T>
//	using Ref = std::shared_ptr<T>;
//
//	using byte = unsigned char;
//
//}