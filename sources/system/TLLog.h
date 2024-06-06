#ifndef __TL_LOG__
#define __TL_LOG__

#include "TLBase.h"

#include <cstdarg>

TL_NS_BEGIN

class TLLog
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

TL_NS_END

#define TL_LOG_INFO(fmt, ...)		do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_INFO, fmt, ##__VA_ARGS__); } while(0)
#define TL_LOG_DEBUG(fmt, ...)		do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_DEBUG, fmt, ##__VA_ARGS__); } while(0)
#define TL_LOG_TRACE(fmt, ...)		do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_TRACE, fmt, ##__VA_ARGS__); } while(0)
#define TL_LOG_WARNING(fmt, ...)	do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_WARNING, fmt, ##__VA_ARGS__); } while(0)
#define TL_LOG_ERROR(fmt, ...)		do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_ERROR, fmt, ##__VA_ARGS__); } while(0)
#define TL_LOG_CRASH(fmt, ...)		do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_CRASH, fmt, ##__VA_ARGS__); TL_DEBUG_BREAK(); } while(0)

#ifdef TL_ASSERTION_ENABLED
#define TL_LOG_ASSERT(fmt, ...)    do { TL::TLLog::Log(__FILE__, __LINE__, TL::TLLog::LogType::LOG_ASSERT, fmt, ##__VA_ARGS__); } while(0)
#define TL_ASSERT(x, fmt, ...)	    do { const volatile bool b = (x); if (!b) { TL_LOG_ASSERT(fmt, ##__VA_ARGS__); TL_DEBUG_BREAK(); } } while(0)
#define TL_NEVER_HAPPEN()		    assert(0)
#define TL_CHECK(x, fmt, ...)      do { const volatile bool b = (x); if (!b) { TL_LOG_CRASH(fmt, ##__VA_ARGS__); } } while(0)
#else
#define TL_ASSERT(b, fmt, ...)
#define TL_NEVER_HAPPEN()
#define TL_CHECK(x, msg)
#endif

#endif


//#ifdef TL_ASSERTION_ENABLED
//// TODO: Implement after create Log System.
//#define TL_ASSERT(x, ...)
//#define TL_ASSERT_WITHOUT_MESSAGE(x)
//#define TL_ASSERT_WITH_ERROR_CODE(x)
//#define TL_NEVER_HAPPEN				assert(0)
//#else
//#define HS_ASSERT(x, ...) 
//#define HS_ASSERT_WITHOUT_MESSAGE(x) 
//#define HS_ASSERT_WITH_ERROR_CODE(x)
//#define HS_NEVER_HAPPEN
//#endif
