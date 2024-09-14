#ifndef __TL_SWAPCHAIN_VK__
#define __TL_SWAPCHAIN_VK__

#include "TLBase.h"
#include "graphics/TLSwapchain.h"

#include <vulkan/vulkan.h>

TL_NS_GRAPHICS_BEGIN


class SwapchainVK : public Swapchain
{
public:
	SwapchainVK() = delete;
	SwapchainVK(Window* window, VkInstance instance, VkDevice deviceVK);
	virtual ~SwapchainVK();

	VkSurfaceKHR surfaceVK;
	std::vector<VkImage> swapchainImages;
	VkSwapchainKHR swapchainVK;

	VkInstance instanceVK;
	VkDevice deviceVK;

	std::vector<VkSemaphore> presentCompleteSemaphores;
	std::vector<VkSemaphore> renderCompleteSemaphores;
	std::vector<VkFence> fences;

	uint32 imageIndex = 0;
	uint32 submitIndex = 0;

	static const uint32 MAX_SUBMIT_INDEX;
};

TL_NS_GRAPHICS_END

#endif
