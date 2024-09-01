#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "graphics/private/vulkan/TLVulkanUtility.h"
#include "graphics/private/vulkan/TLSwapchainVK.h"

#include <vector>
#include <cstring>

TL_NS_GRAPHICS_BEGIN


#ifdef TL_PROFILE_DEBUG
static const std::vector<const char*> validation_layers
{
	"VK_LAYER_KHRONOS_validation"
};

static const bool enable_validation_layers = true;
static VkDebugUtilsMessengerEXT debug_messenger;
static PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
static PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;

#else
static const bool enable_validation_layers = false;

#endif


static VKAPI_ATTR VkBool32 VKAPI_CALL tl_vk_debug_callback
(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
)
{
	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
	{
		TL_LOG_CRASH("[Vulkan Validation Layer] [ID: %s] [Number: %d] Message: %s", pCallbackData->pMessageIdName, pCallbackData->messageIdNumber, pCallbackData->pMessage);
	}
	else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
	{
		TL_LOG_WARNING("[Vulkan Validation Layer] [ID: %s] [Number: %d] Message: %s", pCallbackData->pMessageIdName, pCallbackData->messageIdNumber, pCallbackData->pMessage);
	}
	else 
	{
		TL_LOG_DEBUG("[Vulkan Validation Layer] [ID: %s] [Number: %d] Message: %s", pCallbackData->pMessageIdName, pCallbackData->messageIdNumber, pCallbackData->pMessage);
	}

	return VK_FALSE;
}

bool tl_vk_check_validation_layer_support()
{
	uint32 layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validation_layers)
	{
		bool layerFound = false;

		for (const VkLayerProperties& layerProps : availableLayers)
		{
			// ...
		}
	}

	return false;
}

TLGraphicsContextVK::TLGraphicsContextVK()
{

}

TLGraphicsContextVK::~TLGraphicsContextVK()
{
	Shutdown();
}

bool TLGraphicsContextVK::Init()
{
	//TODO: 로직 작성 완료 후 true 리턴하도록 변경.
	return false;
}

bool TLGraphicsContextVK::Load()
{
	createInstance();
	if (enable_validation_layers)
	{
		vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
		if (nullptr == vkCreateDebugUtilsMessengerEXT)
		{
			return false;
		}
		vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
		if (nullptr == vkDestroyDebugUtilsMessengerEXT)
		{
			return false;
		}
	}

	//TODO: 필요한 함수 로드 추가할 것...
	setupDebugMessenger();
	createDevice();

	return true;
}

TLISwapchain* TLGraphicsContextVK::CreateSwapchain(TLIWindow* window)
{
	TLSwapchainVK* swapchainVK = new TLSwapchainVK(window, _instance, _logicalDevice);


	return static_cast<TLISwapchain*>(swapchainVK);
}

uint32 TLGraphicsContextVK::AcquireNextImageIndex(TLISwapchain* swapchain)
{
	return 0;
}

uint32 TLGraphicsContextVK::GetCurrentImageIndex(TLISwapchain* swapchain)
{
	return 0;
}

void TLGraphicsContextVK::Present(TLISwapchain* swapchain)
{
	TLSwapchainVK* sw = static_cast<TLSwapchainVK*>(swapchain);

	sw->submitIndex = (sw->submitIndex + 1) % TLSwapchainVK::MAX_SUBMIT_INDEX;

	if (VK_SUCCESS != vkGetFenceStatus(_logicalDevice, sw->fences[sw->submitIndex]))
	{
		vkWaitForFences(_logicalDevice, 1, &sw->fences[sw->submitIndex], VK_TRUE, UINT64_MAX);
	}
	VK_CHECK_RESULT(vkResetFences(_logicalDevice, 1, &sw->fences[sw->submitIndex]));

	VK_CHECK_RESULT(vkAcquireNextImageKHR(_logicalDevice, sw->swapchainVK, UINT64_MAX, sw->presentCompleteSemaphores[sw->submitIndex], VK_NULL_HANDLE, &sw->imageIndex));

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	VK_CHECK_RESULT(vkBeginCommandBuffer(_tempCommandBuffer[sw->submitIndex], &beginInfo));

	VkImageSubresourceRange range{};
	range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	range.baseArrayLayer = 0;
	range.layerCount = 1;
	range.baseMipLevel = 0;
	range.levelCount = 1;

	VkImageMemoryBarrier swClearBarrier{};
	swClearBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	swClearBarrier.srcAccessMask = VK_ACCESS_NONE;
	swClearBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	swClearBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	swClearBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	swClearBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	swClearBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	swClearBarrier.image = sw->swapchainImages[sw->imageIndex];
	swClearBarrier.subresourceRange = range;

	vkCmdPipelineBarrier(
		_tempCommandBuffer[sw->submitIndex],
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		0,
		0,
		nullptr,
		0,
		nullptr,
		1,
		&swClearBarrier
	);

	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;
	r += 0.03f;
	g += 0.02f;
	b += 0.01f;

	if (r > 1.0f) r = 0.0f;
	if (g > 1.0f) g = 0.0f;
	if (b > 1.0f) b = 0.0f;

	VkClearColorValue clearColorValue = { r, g, b, 1.0f };
	
	vkCmdClearColorImage(_tempCommandBuffer[sw->submitIndex], sw->swapchainImages[sw->imageIndex], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColorValue, 1, &range);

	VkImageMemoryBarrier swPresentBarrier{};
	swPresentBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	swPresentBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	swPresentBarrier.dstAccessMask = VK_ACCESS_NONE;
	swPresentBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	swPresentBarrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	swPresentBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	swPresentBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	swPresentBarrier.image = sw->swapchainImages[sw->imageIndex];
	swPresentBarrier.subresourceRange = range;

	vkCmdPipelineBarrier(
		_tempCommandBuffer[sw->submitIndex],
		VK_PIPELINE_STAGE_TRANSFER_BIT,
		VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		0,
		0,
		nullptr,
		0,
		nullptr,
		1,
		&swPresentBarrier
	);


	VK_CHECK_RESULT(vkEndCommandBuffer(_tempCommandBuffer[sw->submitIndex]));

	VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pWaitDstStageMask = &waitStageMask;
	submitInfo.pCommandBuffers = &_tempCommandBuffer[sw->submitIndex];
	submitInfo.commandBufferCount = 1;
	submitInfo.pWaitSemaphores = &sw->presentCompleteSemaphores[sw->submitIndex];
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &sw->renderCompleteSemaphores[sw->submitIndex];
	submitInfo.signalSemaphoreCount = 1;

	VK_CHECK_RESULT(vkQueueSubmit(_queue, 1, &submitInfo, sw->fences[sw->submitIndex]));

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pSwapchains = &sw->swapchainVK;
	presentInfo.swapchainCount = 1;
	presentInfo.pImageIndices = &sw->imageIndex;
	presentInfo.pWaitSemaphores = &sw->renderCompleteSemaphores[sw->submitIndex];
	presentInfo.waitSemaphoreCount = 1;

	VK_CHECK_RESULT(vkQueuePresentKHR(_queue, &presentInfo));

	//VK_CHECK_RESULT(vkQueueWaitIdle(_queue));

	//...
}

bool TLGraphicsContextVK::createInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = "TriLumina";
	appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
	appInfo.pEngineName = "TriLumina";
	appInfo.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
	appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 0);

	uint32 layerCount;
	VK_CHECK_RESULT(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));

	std::vector<VkLayerProperties> layerProps(layerCount);
	VK_CHECK_RESULT(vkEnumerateInstanceLayerProperties(&layerCount, layerProps.data()));

	std::vector<const char*> enabledLayerNames;

	// TODO: 필요한 instance layer만 추가해야 한다.. 어떻게?
	//for (int i = 0; i < layerCount; i++)
	//{
	//	enabledLayerNames.push_back(layerProps[i].layerName);
	//}
	//

	// Validatoin Layer 추가
	if (enable_validation_layers)
	{
		enabledLayerNames.push_back(validation_layers[0]);
	}

	uint32 extensionCount;
	VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));

	std::vector<VkExtensionProperties> extensionProps(extensionCount);
	VK_CHECK_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProps.data()));

	std::vector<const char*> supportedExtensionNames;
	for (int i = 0; i < extensionCount; i++)
	{
		supportedExtensionNames.push_back(extensionProps[i].extensionName);
	}

	std::vector<const char*> enabledExtensionNames;
	for (const char* extension : supportedExtensionNames)
	{
		if (std::string("VK_KHR_surface") == std::string(extension) ||
			std::string("VK_KHR_win32_surface") == std::string(extension))
		{
			enabledExtensionNames.push_back(extension);
		}
	}
	if (enable_validation_layers)
	{
		enabledExtensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	if (enable_validation_layers)
	{
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
		debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugMessengerCreateInfo.messageSeverity = 
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugMessengerCreateInfo.messageType = 
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | 
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | 
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugMessengerCreateInfo.pfnUserCallback = tl_vk_debug_callback;

		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerCreateInfo;

	}
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = validation_layers.size();
	createInfo.ppEnabledLayerNames = validation_layers.data();
	createInfo.enabledExtensionCount = enabledExtensionNames.size();
	createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();

	VK_CHECK_RESULT(vkCreateInstance(&createInfo, nullptr, &_instance));

	return true;
}

// TODO: Queue Family나 VkQueue관련 로직은 분리하는 게 좋아 보인다.
bool TLGraphicsContextVK::createDevice()
{
	TL_CHECK(_instance != nullptr, "VkInstance isn't created yet.");

	uint32 physicalDeviceCount = 0;
	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	VK_CHECK_RESULT(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, physicalDevices.data()));

	_physicalDevice = physicalDevices[0];

	// TODO: Physical Device 선택 로직 추가하기.
	//for (uint32 i = 0; i < physicalDeviceCount; i++)
	//{
	//	VkPhysicalDevice physicalDevice = physicalDevices[i];
	//	VkPhysicalDeviceProperties physicalDeviceProps{};
	//	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProps);

		// Select logic...
	//}

	VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProps{};
	vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &physicalDeviceMemoryProps);

	uint32 queueFamilyPropsCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyPropsCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyPropsCount);
	vkGetPhysicalDeviceQueueFamilyProperties(_physicalDevice, &queueFamilyPropsCount, queueFamilyProps.data());

	uint32 queueFamilyIndex = 0;
	for (; queueFamilyIndex != queueFamilyPropsCount; queueFamilyIndex++)
	{
		if (queueFamilyProps[queueFamilyIndex].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			break;
		}
	}

	float priority = 1.0f;

	VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndex;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &priority;

	uint32 deviceExtensionCount;
	VK_CHECK_RESULT(vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &deviceExtensionCount, nullptr));

	std::vector<VkExtensionProperties> deviceExtensionProps(deviceExtensionCount);
	VK_CHECK_RESULT(vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &deviceExtensionCount, deviceExtensionProps.data()));

	std::vector<const char*> deviceExtensionNames;
	for (const VkExtensionProperties& extensionProps : deviceExtensionProps)
	{
		if (::strcmp(extensionProps.extensionName, "VK_KHR_swapchain") == 0)
		{
			deviceExtensionNames.push_back(extensionProps.extensionName);
		}
	}

	TL_CHECK(deviceExtensionNames.size() == 1, "Extension size is not expected.");

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
	deviceCreateInfo.enabledExtensionCount = static_cast<uint32>(deviceExtensionNames.size());
	deviceCreateInfo.ppEnabledExtensionNames = deviceExtensionNames.data();

	VK_CHECK_RESULT(vkCreateDevice(_physicalDevice, &deviceCreateInfo, nullptr, &_logicalDevice));

	vkGetDeviceQueue(_logicalDevice, queueFamilyIndex, 0, &_queue);

	// TODO: 별도 객체로 분리될 예정.
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndex;

	VK_CHECK_RESULT(vkCreateCommandPool(_logicalDevice, &poolInfo, nullptr, &_tempCommandPool));

	VkCommandBufferAllocateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	bufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	bufferInfo.commandPool = _tempCommandPool;
	bufferInfo.commandBufferCount = 3; // minImageCount만큼

	VK_CHECK_RESULT(vkAllocateCommandBuffers(_logicalDevice, &bufferInfo, _tempCommandBuffer));

	return true;
}

void TLGraphicsContextVK::setupDebugMessenger()
{
	if (false == enable_validation_layers)
	{
		return;
	}

	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = tl_vk_debug_callback;
	createInfo.pUserData = nullptr;

	VK_CHECK_RESULT(vkCreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &debug_messenger));
}


void TLGraphicsContextVK::Shutdown()
{
	vkDestroyDevice(_logicalDevice, nullptr);

	//...

	if (nullptr != debug_messenger)
	{
		//vkDestroyDebugUtilsMessengerEXT(_instance, debug_messenger, nullptr);
	}
	vkDestroyInstance(_instance, nullptr);
}

TL_NS_GRAPHICS_END