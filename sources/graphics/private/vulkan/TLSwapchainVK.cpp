#include "TLSwapchainVK.h"
#include "TLVulkanUtility.h"

TL_NS_GRAPHICS_BEGIN

TLSwapchainVK::TLSwapchainVK(TLIWindow* window, VkInstance instanceVK, VkDevice deviceVK)
	: TLISwapchain(window)
	, instanceVK{ instanceVK }
	, deviceVK{ deviceVK }
	, swapchainVK{ VK_NULL_HANDLE }
	, surfaceVK{ VK_NULL_HANDLE }
{
	bool result = tl_platform_create_surface_vulkan(window->GetNativeHandle(), instanceVK, &surfaceVK);

	if (false == result)
	{
		TL_LOG_CRASH("Cannot Create VkSurface");
	}

	static uint32 minImageCount = 3;

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.surface = surfaceVK;
	createInfo.minImageCount = minImageCount;
	createInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
	createInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	
	VkExtent2D extent;
	extent.width = window->GetWidth();
	extent.height = window->GetHeight();

	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

	vkCreateSwapchainKHR(deviceVK, &createInfo, nullptr, &swapchainVK);

	uint32 swapchainImageCount;
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(deviceVK, swapchainVK, &swapchainImageCount, nullptr));

	swapchainImages.resize(swapchainImageCount);
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(deviceVK, swapchainVK, &swapchainImageCount, swapchainImages.data()));

	imageAcquireSemaphores.resize(minImageCount);
	renderCompleteSemaphores.resize(minImageCount);
	fences.resize(minImageCount);

	VkSemaphoreCreateInfo semaphoreCreateInfo{};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = nullptr;
	semaphoreCreateInfo.flags = 0;

	VkFenceCreateInfo fenceCreateInfo{};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.pNext = nullptr;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (int i = 0; i < minImageCount; i++)
	{
		vkCreateSemaphore(deviceVK, &semaphoreCreateInfo, nullptr, &imageAcquireSemaphores[i]);
		vkCreateSemaphore(deviceVK, &semaphoreCreateInfo, nullptr, &renderCompleteSemaphores[i]);

		vkCreateFence(deviceVK, &fenceCreateInfo, nullptr, &fences[i]);
	}
}

TLSwapchainVK::~TLSwapchainVK()
{
	vkDestroySwapchainKHR(deviceVK, swapchainVK, nullptr);
	vkDestroySurfaceKHR(instanceVK, surfaceVK, nullptr);
}


TL_NS_GRAPHICS_END
