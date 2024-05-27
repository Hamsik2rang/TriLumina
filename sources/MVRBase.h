#ifndef __MVR_BASE__
#define __MVR_BASE__

#include <cassert>

#if !defined(_WIN32) && !defined(__APPLE__)
	#error MVR is only support Windows and Mac!
#endif

#if defined(__i386__) || defined(_M_IX86)
	#define MVR_PROCESSOR_X86_32
#endif

#if defined(__x86_64__) || defined(__ia64__) || defined(_M_X64)
	#define MVR_PROCESSOR_X86_64
#endif

#if defined(__arm__) || defined(__arm64__) || defined(_M_ARM) || defined(__aarch64__)
	#if !defined(__LINUX__) && !defined(__arm64__) && !defined(__aarch64__)
		#define MVR_PROCESSOR_ARM32
	#else
		#define MVR_PROCESSOR_ARM64
	#endif
#endif

#ifdef _WIN32
	#define MVR_PLATFORM_WINDOWS
#else
	#define MVR_PLATFORM_MACOS
#endif

#if defined(_DEBUG) || defined(DEBUG)
	#define MVR_PROFILE_DEBUG
#else
	#define MVR_PROFILE_RELEASE
#endif

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
#ifdef MVR_PLATFORM_WINDOWS
typedef long long int64;
typedef unsigned long long uint64;
#else // MVR_PLATFORM_MACOS
typedef long int64;
typedef unsigned long uint64;
#endif

#define BIT_INT8(x)     (static_cast<int8>(1) << (x))
#define BIT_UINT8(x)    (static_cast<uint8>(1u) << (x))
#define BIT_INT16(x)    (static_cast<int16>(1) << (x))
#define BIT_UINT16(x)   (static_cast<uint16>(1u) << (x))
#define BIT_INT32(x)    (static_cast<int32>(1) << (x))
#define BIT_UINT32(x)   (static_cast<uint32>(1u) << (x))
#define BIT_INT64(x)    (static_cast<int64>(1) << (x))
#define BIT_UINT64(x)   (static_cast<uint64>(1u) << (x))

#define BIT(x)          BIT_UINT32(x)

#if defined(_WIN32)
	#define MVR_DEBUG_BREAK __debugbreak
#elif defined(__APPLE__)
	#define MVR_DEBUG_BREAK __builtin_trap
#endif

#ifdef _DEBUG
	#ifndef MVR_ASSERTION_ENABLED
		#define MVR_ASSERTION_ENABLED
	#endif
#else
	#ifdef MVR_ASSERTION_ENABLED
		#undef MVR_ASSERTION_ENABLED
	#endif
#endif

#if defined(MVR_ENGINE)
	#ifdef MVR_PLATFORM_WINDOWS
		#define MVR_API __declspec(dllexport)
	#else
		#define MVR_API __attribute__(( __visibility__("default") ))
	#endif
#else
	#ifdef MVR_PLATFORM_WINDOWS
		#define MVR_API __declspec(dllimport)
	#else
		#define MVR_API
	#endif
#endif

#if defined(MVR_EDITOR)
	#ifdef MVR_PLATFORM_WINDOWS
		#define MVR_EDITOR_API __declspec(dllexport)
	#else
		#define MVR_EDITOR_API __attribute__(( __visibility__("default") ))
	#endif
#else
	#ifdef MVR_PLATFORM_WINDOWS
		#define MVR_EDITOR_API __declspec(dllimport)
	#else
		#define MVR_EDITOR_API
	#endif
#endif

#define MVR_NS_BEGIN		namespace MVR {
#define MVR_NS_RENDER_BEGIN namespace MVR { namespace Render {
#define MVR_NS_ENGINE_BEGIN namespace MVR { namespace Engine {
#define MVR_NS_EDITOR_BEGIN namespace MVR { namespace Editor {

#define MVR_NS_END				}
#define MVR_NS_RENDER_END		} }
#define MVR_NS_ENGINE_END		} }
#define MVR_NS_EDITOR_END		} }

#endif
