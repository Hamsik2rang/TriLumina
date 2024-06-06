#ifndef __TL_SYSTEM_CONTEXT__
#define __TL_SYSTEM_CONTEXT__

#include "TLBase.h"

#if defined(TL_PLATFORM_MACOS)
#include "system/platform/cocoa/TLPlatformCocoa.h"
#elif defined(TL_PLATFORM_WINDOWS)
#include "system/platform/windows/TLPlatformWindows.h"
#endif

TL_NS_BEGIN

class TLWindow;

struct TLSystemConfig
{

};

class TLSystemContext
{
public:
    TLSystemContext();
    
    ~TLSystemContext();
    
    void SetConfig(const TLSystemConfig& config) { _config = config; }
    TLSystemConfig GetConfig() const { return _config; }
private:
    TLSystemConfig _config;
    bool _resizable;
};

TL_NS_END

#endif /* __TL_SYSTEM_CONTEXT */

