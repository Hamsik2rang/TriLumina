#include "graphics/private/metal/TLSwapchainMTL.h"
#include "system/platform/TLPlatformDefinition.h"

#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

TL_NS_GRAPHICS_BEGIN


TLSwapchainMTL::TLSwapchainMTL(TLIWindow* window)
: TLISwapchain(window)
{
    _metalLayer = window->GetNativeHandle()._layer;
    CAMetalLayer* layer = (__bridge CAMetalLayer*)_metalLayer;
    const id<MTLDevice> device = layer.device;
    _cmdQueue = (__bridge_retained void*)[device newCommandQueue];
    
}

TLSwapchainMTL::~TLSwapchainMTL()
{
    
}


TL_NS_GRAPHICS_END
