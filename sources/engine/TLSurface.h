#ifndef __TL_SURFACE__
#define __TL_SURFACE__

#include "TLBase.h"

#include "graphics/TLSwapchain.h"

TL_NS_ENGINE_BEGIN

class TL_API Surface
{
public:
    Surface();
    ~Surface();
    
    inline void SetSwapchain(Graphics::Swapchain* swapchain) { _swapchain = swapchain; }
    inline Graphics::Swapchain* GetSwapchain() { return _swapchain; }

    
private:
    Graphics::Swapchain* _swapchain;
};




TL_NS_ENGINE_END

#endif
