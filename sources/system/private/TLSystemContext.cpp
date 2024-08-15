#include "system/TLSystemContext.h"
#include "system/TLLog.h"

TL_NS_BEGIN

TLSystemContext* TLSystemContext::s_instance;

TLSystemContext* TLSystemContext::Create()
{
    if (nullptr != s_instance)
    {
        TL_LOG_CRASH("TLSystemContext is already created!");
        return nullptr;
    }
    TLSystemContext* systemContext = new TLSystemContext();
    systemContext->isInitialized = true;
#ifdef TL_PROFILE_DEBUG
    systemContext->isDebug = true;
#else
    systemContext->isDebug = false;
#endif
    systemContext->shouldQuit = false;

    s_instance = systemContext;
    
    return s_instance;
}

TLSystemContext* TLSystemContext::Get()
{
    if (s_instance)
    {
        return s_instance;
    }

    TL_LOG_CRASH("TLSystemContext doesn't create yet. you should craete first");
    return nullptr;
}

void TLSystemContext::PollEvents()
{
    tl_platform_poll_events();
}

TL_NS_END
