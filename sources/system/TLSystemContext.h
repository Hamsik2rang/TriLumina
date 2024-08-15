#ifndef __TL_SYSTEM_CONTEXT__
#define __TL_SYSTEM_CONTEXT__

#include "TLBase.h"
#include "system/platform/TLPlatformDefinition.h"

#include <string>

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

    void PollEvents();
    struct
    {
        TLWindowConfig window;
        TLFramebufferConfig framebuffer;
        TLGraphicsConfig graphics;
    } configs;

    bool isInitialized;
    bool isDebug;
    bool shouldQuit = false;
    std::string executablePath;
    std::string executableDirectoryPath;

private:
	static TLSystemContext* s_instance;
};


TL_NS_END

#endif /* __TL_SYSTEM_CONTEXT */

