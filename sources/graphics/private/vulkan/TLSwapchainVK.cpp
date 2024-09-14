#include "TLSwapchainVK.h"
#include "TLVulkanUtility.h"

TL_NS_GRAPHICS_BEGIN

// TODO: 정확히 타겟 디바이스에 맞게 세팅해주어야 함.
const uint32 SwapchainVK::MAX_SUBMIT_INDEX = 3;

SwapchainVK::SwapchainVK(Window* window, VkInstance instanceVK, VkDevice deviceVK)
	: Swapchain(window)
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

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.surface = surfaceVK;
	createInfo.minImageCount = MAX_SUBMIT_INDEX;
	createInfo.imageFormat = VK_FORMAT_R8G8B8A8_UNORM;
	createInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;

	VkExtent2D extent;
	extent.width = window->GetWidth();
	extent.height = window->GetHeight();

	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
	createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

	vkCreateSwapchainKHR(deviceVK, &createInfo, nullptr, &swapchainVK);

	uint32 swapchainImageCount;
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(deviceVK, swapchainVK, &swapchainImageCount, nullptr));

	swapchainImages.resize(swapchainImageCount);
	VK_CHECK_RESULT(vkGetSwapchainImagesKHR(deviceVK, swapchainVK, &swapchainImageCount, swapchainImages.data()));

	presentCompleteSemaphores.resize(MAX_SUBMIT_INDEX);
	renderCompleteSemaphores.resize(MAX_SUBMIT_INDEX);
	fences.resize(MAX_SUBMIT_INDEX);

	VkSemaphoreCreateInfo semaphoreCreateInfo{};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = nullptr;
	semaphoreCreateInfo.flags = 0;

	VkFenceCreateInfo fenceCreateInfo{};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.pNext = nullptr;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (int i = 0; i < MAX_SUBMIT_INDEX; i++)
	{
		vkCreateSemaphore(deviceVK, &semaphoreCreateInfo, nullptr, &presentCompleteSemaphores[i]);
		vkCreateSemaphore(deviceVK, &semaphoreCreateInfo, nullptr, &renderCompleteSemaphores[i]);

		vkCreateFence(deviceVK, &fenceCreateInfo, nullptr, &fences[i]);
	}
}

SwapchainVK::~SwapchainVK()
{
	vkDestroySwapchainKHR(deviceVK, swapchainVK, nullptr);
	vkDestroySurfaceKHR(instanceVK, surfaceVK, nullptr);
}


TL_NS_GRAPHICS_END
