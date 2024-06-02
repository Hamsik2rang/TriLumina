#ifndef __MVR_SYSTEM_CONTEXT__
#define __MVR_SYSTEM_CONTEXT__

#include "MVRBase.h"

#if defined(__MVR_PLATFORM_MACOS)
#include "system/platform/cocoa/MVRPlatformCocoa.h"
#elif defined(__MVR_PLATFORM__WINDOWS)
#include "system/platform/windows/MVRPlatformWindows.h"
#endif

MVR_NS_BEGIN

class MVRWindow;

class MVRSystemContext
{
public:
    MVRSystemContext();
    
    ~MVRSystemContext();
    
    
private:
    bool _resizable;
};

MVR_NS_END

#endif /* __MVR_SYSTEM_CONTEXT */

