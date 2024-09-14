#include "system/TLSystemContext.h"
#include "system/TLLog.h"

TL_NS_BEGIN

SystemContext* SystemContext::s_instance;

SystemContext* SystemContext::Create()
{
    if (nullptr != s_instance)
    {
        TL_LOG_CRASH("SystemContext is already created!");
        return nullptr;
    }
    SystemContext* systemContext = new SystemContext();
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

SystemContext* SystemContext::Get()
{
    if (s_instance)
    {
        return s_instance;
    }

    TL_LOG_CRASH("SystemContext doesn't create yet. you should craete first");
    return nullptr;
}

void SystemContext::PollEvents()
{
    tl_platform_poll_events();
}

TL_NS_END
