#include "graphics/TLGraphicsContext.h"

#if defined(TL_PLATFORM_WINDOWS)
    #include "graphics/private/vulkan/TLGraphicsContextVK.h"
#elif defined(TL_PLATFORM_MACOS)
    #include "graphics/private/metal/TLGraphicsContextMTL.h"
#endif

TL_NS_GRAPHICS_BEGIN

TLIGraphicsContext* TLIGraphicsContext::Create(TLEGraphicsInterface interface)
{
    TLIGraphicsContext* context = nullptr;
    
    switch (interface)
    {
        case TLEGraphicsInterface::VULKAN:
        {
            
        }
            break;
        case TLEGraphicsInterface::METAL:
        {
            context = new TLGraphicsContextMTL();
        }
            break;
        case TLEGraphicsInterface::NONE:
        case TLEGraphicsInterface::VIRTUAL:
        default:
        {
            TL_LOG_ERROR("this Graphics Interface is not supported yet.");
        }
            break;
    }
    
    return context;
}



TL_NS_GRAPHICS_END
