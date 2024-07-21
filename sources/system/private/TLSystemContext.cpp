#include "system/TLSystemContext.h"

TL_NS_BEGIN


TLSystemContext* tl_create_system_context()
{
    TLSystemContext* systemContext = new TLSystemContext;

    return systemContext;
}

TL_NS_END