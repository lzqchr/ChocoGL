#pragma once

//#ifdef CL_DEBUG
//#define CL_ENABLE_ASSERTS
//#endif
//
//#ifdef CL_ENABLE_ASSERTS
//#define CL_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CL_ERROR("Assertion Failed!"); __debugbreak(); } }
//#define CL_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
//
//#define CL_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
//
//#define CL_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
//#define CL_CORE_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
//#else
//#define CL_ASSERT(...)
//#define CL_CORE_ASSERT(...)
//#endif


#ifdef CL_DEBUG
#define CL_ENABLE_ASSERTS
#endif

#ifdef CL_ENABLE_ASSERTS
#define CL_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CL_ERROR("Assertion Failed"); __debugbreak(); } }
#define CL_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define CL_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define CL_GET_ASSERT_MACRO(...) CL_EXPAND_VARGS(CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE))

#define CL_ASSERT(...) CL_EXPAND_VARGS( CL_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#define CL_CORE_ASSERT(...) CL_EXPAND_VARGS( CL_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
#define CL_ASSERT(...)
#define CL_CORE_ASSERT(...)
#endif


// old maloc 
/*
#define CL_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CL_ERROR("Assertion Failed!"); __debugbreak(); } }
#define CL_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define CL_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro

#define CL_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
#define CL_CORE_ASSERT(...) CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE)(__VA_ARGS__)
*/



// new maloc 
/*
#define CL_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { CL_ERROR("Assertion Failed"); __debugbreak(); } }
#define CL_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { CL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define CL_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
#define CL_GET_ASSERT_MACRO(...) CL_EXPAND_VARGS(CL_ASSERT_RESOLVE(__VA_ARGS__, CL_ASSERT_MESSAGE, CL_ASSERT_NO_MESSAGE))

#define CL_ASSERT(...) CL_EXPAND_VARGS( CL_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#define CL_CORE_ASSERT(...) CL_EXPAND_VARGS( CL_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
*/