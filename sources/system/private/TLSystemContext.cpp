#include "system/TLSystemContext.h"
#include "system/TLLog.h"

TL_NS_BEGIN


TLSystemContext* tl_create_system_context()
{
    TLSystemContext* systemContext = new TLSystemContext;

    return systemContext;
}


TLSystemContext* TLSystemContext::Create()
{
    return nullptr;
}

TLSystemContext* TLSystemContext::Get()
{
    if (_instance)
    {
        return _instance;
    }

    TL_LOG_CRASH("TLSystemContext doesn't create yet. you should craete first");
    return nullptr;
}

TL_NS_END