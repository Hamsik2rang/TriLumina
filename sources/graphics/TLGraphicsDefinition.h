#ifndef __TL_GRAPHICS_DEFINITION__
#define __TL_GRAPHICS_DEFINITION__

#include "TLBase.h"
#include "system/TLLog.h"

TL_NS_GRAPHICS_BEGIN

enum class GraphicsInterface
{
    NONE = 0,
    VULKAN = 1,
    METAL = 2,
    DIRECTX_11 = 3,
    DIRECTX_12 = 4,
    VIRTUAL = 5,
};

enum class PixelFormat : uint8
{
    NONE = 0,
    R8G8B8A8_UNORM = 37,
    R8G8B8A8_SNORM = 38,
    
};




TL_NS_GRAPHICS_END

#endif __TL_GRAPHICS_DEFINITION__

