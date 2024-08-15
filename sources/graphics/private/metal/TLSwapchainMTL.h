#ifndef __TL_SWAPCHAIN_MTL__
#define __TL_SWAPCHAIN_MTL__

#include "TLBase.h"

#include "graphics/TLSwapchain.h"

TL_NS_GRAPHICS_BEGIN

class TLSwapchainMTL : public TLISwapchain
{
public:
    TLSwapchainMTL() = delete;
    TLSwapchainMTL(TLIWindow* window);
    ~TLSwapchainMTL();
    
    void* _metalLayer;
    void* _cmdQueue;
};


TL_NS_GRAPHICS_END


#endif
