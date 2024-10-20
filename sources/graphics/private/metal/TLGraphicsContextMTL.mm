#include "graphics/private/metal/TLGraphicsContextMTL.h"
#include "graphics/private/metal/TLSwapchainMTL.h"

#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>


TL_NS_GRAPHICS_BEGIN

static id<MTLDevice> s_device = nil;


bool GraphicsContextMTL::Init()
{
    s_device = MTLCreateSystemDefaultDevice();
}

bool GraphicsContextMTL::Load()
{
    return false;
}

Swapchain* GraphicsContextMTL::CreateSwapchain(Window* window)
{
    Swapchain* swapchain = new SwapchainMTL(window);
//    swapchain->_swapchainRenderer = SDL_CreateRenderer(static_cast<SDL_Window*>(window->GetHandle()), -1, )
    
    
    return swapchain;
}

uint32 GraphicsContextMTL::AcquireNextImageIndex(Swapchain* swapchain)
{
    return 0;
}

uint32 GraphicsContextMTL::GetCurrentImageIndex(Swapchain* swapchain)
{
    return 0;
}

void GraphicsContextMTL::Present(Swapchain* swapchain)
{
    SwapchainMTL* swMTL = static_cast<SwapchainMTL*>(swapchain);
    @autoreleasepool {
        
        CAMetalLayer* layer = (__bridge CAMetalLayer*)swMTL->_metalLayer;
        id<CAMetalDrawable> surface = [layer nextDrawable];
        
        static MTLClearColor color = MTLClearColorMake(0, 0, 0, 1);
        
        color.red = (color.red > 1.0) ? 0.0 : color.red + 0.01;
        color.green = (color.green > 1.0) ? 0.0 : color.green + 0.02;
        color.blue = (color.blue > 1.0) ? 0.0 : color.blue + 0.03;
        
        MTLRenderPassDescriptor* pass  = [MTLRenderPassDescriptor renderPassDescriptor];
        pass.colorAttachments[0].clearColor = color;
        pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
        pass.colorAttachments[0].storeAction = MTLStoreActionStore;
        pass.colorAttachments[0].texture = surface.texture;

        id<MTLCommandQueue> cmdQueue = (__bridge id<MTLCommandQueue>)swMTL->_cmdQueue;
        id<MTLCommandBuffer> buffer = [cmdQueue commandBuffer];
        id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];
        [encoder endEncoding];
        [buffer presentDrawable:surface];
        [buffer commit];
        
    }
}

void GraphicsContextMTL::Shutdown()
{
    return;
}

TL_NS_GRAPHICS_END
