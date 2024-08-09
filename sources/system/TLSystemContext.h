#ifndef __TL_SYSTEM_CONTEXT__
#define __TL_SYSTEM_CONTEXT__

#include "TLBase.h"

#include <string>

#if defined(TL_PLATFORM_MACOS)
#include "system/platform/cocoa/TLPlatformCocoa.h"
#elif defined(TL_PLATFORM_WINDOWS)
#include "system/platform/windows/TLPlatformWindows.h"
#endif

TL_NS_BEGIN

struct TLWindowConfig
{
	bool resizable;
	bool decorated;
	bool focused;
	const char* title;
};

struct TLFramebufferConfig
{

};

struct TLGraphicsConfig
{
	const char* name;
	uint8 major;
	uint8 minor;
};

class TLSystemContext
{
public:
	static TLSystemContext* Create();
	static TLSystemContext* Get();

private:
	struct
	{
		TLWindowConfig window;
		TLFramebufferConfig framebuffer;
		TLGraphicsConfig graphics;
	} configs;

	bool isInitialized;
	bool isDebug;
	std::string executablePath;
	std::string executableDirectoryPath;

	static TLSystemContext* _instance;
};

TLSystemContext* tl_create_system_context();

TL_NS_END

#endif /* __TL_SYSTEM_CONTEXT */

