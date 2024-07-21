#ifndef __TL_BASE__
#define __TL_BASE__

#include <cassert>

#if !defined(_WIN32) && !defined(__APPLE__)
	#error TL is only support Windows and Mac!
#endif

#if defined(__i386__) || defined(_M_IX86)
	#define TL_PROCESSOR_X86_32
#endif

#if defined(__x86_64__) || defined(__ia64__) || defined(_M_X64)
	#define TL_PROCESSOR_X86_64
#endif

#if defined(__arm__) || defined(__arm64__) || defined(_M_ARM) || defined(__aarch64__)
	#if !defined(__LINUX__) && !defined(__arm64__) && !defined(__aarch64__)
		#define TL_PROCESSOR_ARM32
	#else
		#define TL_PROCESSOR_ARM64
	#endif
#endif

#ifdef _WIN32
	#define TL_PLATFORM_WINDOWS
#else
	#define TL_PLATFORM_MACOS
#endif

#if defined(_DEBUG) || defined(DEBUG)
	#define TL_PROFILE_DEBUG
#else
	#define TL_PROFILE_RELEASE
#endif

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
#ifdef TL_PLATFORM_WINDOWS
	typedef long long int64;
	typedef unsigned long long uint64;
#else // TL_PLATFORM_MACOS
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
	#define TL_DEBUG_BREAK() __debugbreak()
#elif defined(__APPLE__)
	#define TL_DEBUG_BREAK() __builtin_trap()
#endif

#ifdef _DEBUG
	#ifndef TL_ASSERTION_ENABLED
		#define TL_ASSERTION_ENABLED
	#endif
#else
	#ifdef TL_ASSERTION_ENABLED
		#undef TL_ASSERTION_ENABLED
	#endif
#endif

#if defined(TL_ENGINE)
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_API __declspec(dllexport)
	#else
		#define TL_API __attribute__(( __visibility__("default") ))
	#endif
#else
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_API __declspec(dllimport)
	#else
		#define TL_API
	#endif
#endif

#if defined(TL_EDITOR)
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_EDITOR_API __declspec(dllexport)
	#else
		#define TL_EDITOR_API __attribute__(( __visibility__("default") ))
	#endif
#else
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_EDITOR_API __declspec(dllimport)
	#else
		#define TL_EDITOR_API
	#endif
#endif

#if defined(TL_PLATFORM_WINDOWS)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define TL_CHECK_MEMORY_START() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
	#define TL_CHECK_MEMORY_END() _CrtCheckMemory()
	#define TL_ALIGN_BEGIN(size) alignas(size)
	#define TL_ALIGN_END(size)
#else
	#define TL_CHECK_MEMORY_START()
	#define TL_CHECK_MEMORY_END()
	#define TL_ALIGN_BEGIN(size) 
	#define TL_ALIGN_END(size) __attribute__ ((aligned (size)))
#endif

#define TL_NS_BEGIN				namespace TL {
#define TL_NS_GRAPHICS_BEGIN 	namespace TL { namespace Graphics {
#define TL_NS_ENGINE_BEGIN 		namespace TL { namespace Engine {
#define TL_NS_EDITOR_BEGIN 		namespace TL { namespace Editor {

#define TL_NS_END				}
#define TL_NS_GRAPHICS_END		} }
#define TL_NS_ENGINE_END		} }
#define TL_NS_EDITOR_END		} }

#endif
