#ifndef __TL_SWAPCHAIN_MTL__
#define __TL_SWAPCHAIN_MTL__

#include "TLBase.h"

#include "graphics/TLSwapchain.h"

TL_NS_GRAPHICS_BEGIN

class SwapchainMTL : public TLISwapchain
{
public:
    SwapchainMTL() = delete;
    SwapchainMTL(TLIWindow* window);
    ~SwapchainMTL();
    
    void* _metalLayer;
    void* _cmdQueue;
};


TL_NS_GRAPHICS_END


#endif
