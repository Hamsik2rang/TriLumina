#include "TLBase.h"
#include "system/TLLog.h"
#include <cstdio>

#include <cstdio>
#include <cstdarg>

TL_NS_BEGIN

#define LOG_COLOR_RED		"\033[31m"
#define LOG_COLOR_GREEN		"\033[32m"
#define LOG_COLOR_YELLOW	"\033[33m"
#define LOG_COLOR_CYAN		"\033[36m"
#define LOG_COLOR_WHITE		"\033[39m"
#define LOG_COLOR_MAGENTA	"\033[35m"
#define LOG_COLOR_RESET		"\033[0m"

#ifdef _WIN32
static const char* log_color_red = LOG_COLOR_RED;
static const char* log_color_green = LOG_COLOR_GREEN;
static const char* log_color_yellow = LOG_COLOR_YELLOW;
static const char* log_color_cyan = LOG_COLOR_CYAN;
static const char* log_color_white = LOG_COLOR_WHITE;
static const char* log_color_magenta = LOG_COLOR_MAGENTA;
static const char* log_color_reset = LOG_COLOR_RESET;

#else
static const char* log_color_red = "🔴";
static const char* log_color_green = "🟢";
static const char* log_color_yellow = "🟡";
static const char* log_color_cyan = "🔵";
static const char* log_color_white = "⚪️";
static const char* log_color_magenta = "🟣";
static const char* log_color_reset = "";

#endif

static const char* log_tag_info = "[INFO]";
static const char* log_tag_debug = "[DEBUG]";
static const char* log_tag_trace = "[TRACE]";
static const char* log_tag_warning = "[WARNING]";
static const char* log_tag_error = "[ERROR]";
static const char* log_tag_crash = "[CRASH]";
static const char* log_tag_assert = "[ASSERT]";
static const char* log_tag_invalid = "[??????]";


void TLLog::Log(const char* file, const uint32 line, const LogType type, const char* fmt, ...)
{
	const char* start = nullptr;
	const char* end = log_color_reset;
	const char* tag = nullptr;

	switch (type)
	{
    case LogType::LOG_INFO:
	{
		start = log_color_white;
		tag = log_tag_info;
		break;
	}
	case LogType::LOG_DEBUG:
	{
		start = log_color_white;
		tag = log_tag_debug;
		break;
	}
	case LogType::LOG_TRACE:
	{
		start = log_color_cyan;
		tag = log_tag_trace;
		break;
	}
	case LogType::LOG_WARNING:
	{
		start = log_color_yellow;
		tag = log_tag_warning;
		break;
	}
	case LogType::LOG_ERROR:
	{
		start = log_color_red;
		tag = log_tag_error;
		break;
	}
	case LogType::LOG_CRASH:
	{
		start = log_color_red;
		tag = log_tag_crash;
		break;
	}
	case LogType::LOG_ASSERT:
	{
		start = log_color_magenta;
		tag = log_tag_assert;
		break;
	}
	default:	// Invalid Type
	{
		start = log_color_green;
		tag = log_tag_invalid;
		break;
	}
	}
	va_list ptr;
	va_start(ptr, fmt);

	print(file, line, start, tag, end, fmt, ptr);

	va_end(ptr);
}

void TLLog::print(const char* file, const uint32 line, const char* start, const char* tag, const char* end, const char* fmt, va_list ptr)
{
	fprintf(stdout, "%s%s ", start, tag);
	vfprintf(stdout, fmt, ptr);
	fprintf(stdout, " (%s:%u)%s\n", file, line, end);
}

TL_NS_END
