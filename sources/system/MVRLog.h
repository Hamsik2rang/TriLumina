#ifndef __MVR_LOG__
#define __MVR_LOG__

#include "MVRBase.h"

#include <cstdarg>

MVR_NS_BEGIN

class MVRLog
{
public:
	enum class LogType
	{
		LOG_INFO,
		LOG_DEBUG,
		LOG_TRACE,
		LOG_WARNING,
		LOG_ERROR,
		LOG_CRASH,

		LOG_ASSERT
	};

	static void Log(const char* file, const uint32 line, const LogType type, const char* fmt, ...);

private:
	static void print(const char* file, const uint32 line, const char* start, const char* tag, const char* end, const char* fmt, va_list ptr);
};

MVR_NS_END

#define MVR_LOG_INFO(fmt, ...)		do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_INFO, fmt, ##__VA_ARGS__); } while(0)
#define MVR_LOG_DEBUG(fmt, ...)		do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_DEBUG, fmt, ##__VA_ARGS__); } while(0)
#define MVR_LOG_TRACE(fmt, ...)		do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_TRACE, fmt, ##__VA_ARGS__); } while(0)
#define MVR_LOG_WARNING(fmt, ...)	do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_WARNING, fmt, ##__VA_ARGS__); } while(0)
#define MVR_LOG_ERROR(fmt, ...)		do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_ERROR, fmt, ##__VA_ARGS__); } while(0)
#define MVR_LOG_CRASH(fmt, ...)		do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_CRASH, fmt, ##__VA_ARGS__); abort(); } while(0)

#ifdef MVR_ASSERTION_ENABLED
#define MVR_LOG_ASSERT(fmt, ...)		    do { MVR::MVRLog::Log(__FILE__, __LINE__, MVR::MVRLog::LogType::LOG_ASSERT, fmt, ##__VA_ARGS__); } while(0)
#define MVR_ASSERT(x, fmt, ...)			    do { const volatile bool b = (x); if (!b) { MVR_LOG_ASSERT(fmt, ##__VA_ARGS__); abort(); } } while(0)
#define MVR_NEVER_HAPPEN()				assert(0)
#define MVR_CHECK(x, msg) do { const volatile bool b = (x); if (!b) { MVR_DEBUG_BREAK(); } } while(0)
#else
#define MVR_ASSERT(b, fmt, ...)
#define MVR_NEVER_HAPPEN()
#define MVR_CHECK(x, msg)
#endif

#endif


//#ifdef MVR_ASSERTION_ENABLED
//// TODO: Implement after create Log System.
//#define MVR_ASSERT(x, ...)
//#define MVR_ASSERT_WITHOUT_MESSAGE(x)
//#define MVR_ASSERT_WITH_ERROR_CODE(x)
//#define MVR_NEVER_HAPPEN				assert(0)
//#else
//#define HS_ASSERT(x, ...) 
//#define HS_ASSERT_WITHOUT_MESSAGE(x) 
//#define HS_ASSERT_WITH_ERROR_CODE(x)
//#define HS_NEVER_HAPPEN
//#endif
