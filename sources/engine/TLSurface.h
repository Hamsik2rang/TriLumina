#ifndef __TL_SURFACE__
#define __TL_SURFACE__

#include "TLBase.h"

#include "graphics/TLSwapchain.h"

TL_NS_ENGINE_BEGIN

class TL_API TLSurface
{
public:
    TLSurface();
    ~TLSurface();
    
    inline void SetSwapchain(Graphics::TLISwapchain* swapchain) { _swapchain = swapchain; }
    inline Graphics::TLISwapchain* GetSwapchain() { return _swapchain; }
    
private:
    Graphics::TLISwapchain* _swapchain;
    
};




TL_NS_ENGINE_END

#endif
