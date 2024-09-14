#ifndef __TL_SYSTEM_CONTEXT__
#define __TL_SYSTEM_CONTEXT__

#include "TLBase.h"
#include "system/platform/TLPlatformDefinition.h"

#include <string>

TL_NS_BEGIN

struct WindowConfig
{
	bool resizable;
	bool decorated;
	bool focused;
	const char* title;
};

struct FramebufferConfig
{

};

struct GraphicsConfig
{
	const char* name;
	uint8 major;
	uint8 minor;
};

class SystemContext
{
public:
	static SystemContext* Create();
	static SystemContext* Get();

    void PollEvents();
    struct
    {
        WindowConfig window;
        FramebufferConfig framebuffer;
        GraphicsConfig graphics;
    } configs;

    bool isInitialized;
    bool isDebug;
    bool shouldQuit = false;
    std::string executablePath;
    std::string executableDirectoryPath;

private:
	static SystemContext* s_instance;
};


TL_NS_END

#endif /* __TL_SYSTEM_CONTEXT */

