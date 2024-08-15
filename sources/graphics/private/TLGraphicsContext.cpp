#include "graphics/TLGraphicsContext.h"
#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "graphics/private/metal/TLGraphicsContextMTL.h"

TL_NS_GRAPHICS_BEGIN

TLIGraphicsContext* TLIGraphicsContext::Create(TLEGraphicsInterface interface)
{
    TLIGraphicsContext* context = nullptr;
    
    switch (interface)
    {

#ifdef TL_PLATFORM_MACOS
        case TLEGraphicsInterface::METAL:
        {
            context = new TLGraphicsContextMTL();
            break;
        }
#else
        case TLEGraphicsInterface::VULKAN:
        {
            context = new TLGraphicsContextVK();
            break;
        }
        case TLEGraphicsInterface::DIRECTX_11:
        case TLEGraphicsInterface::DIRECTX_12:
#endif
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
