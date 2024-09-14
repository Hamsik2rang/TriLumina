#include "graphics/TLGraphicsContext.h"
#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "graphics/private/metal/GraphicsContextMTL.h"

TL_NS_GRAPHICS_BEGIN

GraphicsContext* GraphicsContext::Create(GraphicsInterface interface)
{
    GraphicsContext* context = nullptr;
    
    switch (interface)
    {

#ifdef TL_PLATFORM_MACOS
        case TLEGraphicsInterface::METAL:
        {
            context = new GraphicsContextMTL();
            break;
        }
#else
        case GraphicsInterface::VULKAN:
        {
            context = new GraphicsContextVK();
            break;
        }
        case GraphicsInterface::DIRECTX_11:
        case GraphicsInterface::DIRECTX_12:
#endif
        case GraphicsInterface::NONE:
        case GraphicsInterface::VIRTUAL:
        default:
        {
            TL_LOG_ERROR("this Graphics Interface is not supported yet.");
        }
            break;
    }
    
    return context;
}



TL_NS_GRAPHICS_END
