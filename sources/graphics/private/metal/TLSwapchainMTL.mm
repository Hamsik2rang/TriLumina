#include "graphics/private/metal/SwapchainMTL.h"
#include "system/platform/TLPlatformDefinition.h"

#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

TL_NS_GRAPHICS_BEGIN


SwapchainMTL::SwapchainMTL(TLIWindow* window)
: TLISwapchain(window)
{
    _metalLayer = window->GetNativeHandle()._layer;
    CAMetalLayer* layer = (__bridge CAMetalLayer*)_metalLayer;
    const id<MTLDevice> device = layer.device;
    _cmdQueue = (__bridge_retained void*)[device newCommandQueue];
    
}

SwapchainMTL::~SwapchainMTL()
{
    
}


TL_NS_GRAPHICS_END
