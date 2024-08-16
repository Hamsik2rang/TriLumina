#ifndef __TL_SWAPCHAIN_VK__
#define __TL_SWAPCHAIN_VK__

#include "TLBase.h"
#include "graphics/TLSwapchain.h"

#include <vulkan/vulkan.h>

TL_NS_GRAPHICS_BEGIN


class TLSwapchainVK : public TLISwapchain
{
public:
    TLSwapchainVK() = delete;
    TLSwapchainVK(TLIWindow* window);
    ~TLSwapchainVK();
    
private:
    VkSwapchainKHR _vkSwapchain;
};

TL_NS_GRAPHICS_END

#endif
