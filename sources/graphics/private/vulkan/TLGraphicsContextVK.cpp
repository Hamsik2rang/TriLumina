#include "graphics/private/vulkan/TLGraphicsContextVK.h"
#include "graphics/private/vulkan/TLVulkanUtility.h"
#include "graphics/private/vulkan/TLSwapchainVK.h"

#include <vector>
#include <cstring>

TL_NS_GRAPHICS_BEGIN


#ifdef TL_PROFILE_DEBUG
static const std::vector<const char*> validationLayers
{
	"VK_LAYER_KHRONOS_validation"
};

static const bool enable_validation_layers = true;
#else
static const bool enable_validation_layers = false;

#endif

bool tl_vk_check_validation_layer_support()
{
	uint32 layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;
	}
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
	createInstance();
	createDevice();

	//TODO: ���� �ۼ� �Ϸ� �� true �����ϵ��� ����.
	return false;
}

bool TLGraphicsContextVK::Load()
{
	//TODO: ���� �ۼ� �Ϸ� �� true �����ϵ��� ����.
	return false;
}

TLISwapchain* TLGraphicsContextVK::CreateSwapchain(TLIWindow* window)
{
	TLSwapchainVK* swapchainVK = new TLSwapchainVK(window);

	VkSurfaceKHR surface = nullptr;

	bool result = tl_platform_create_surface_vulkan(window->GetNativeHandle(), _instance, &surface);
	
	if (false == result)
	{
		TL_LOG_CRASH("Cannot Create VkSurface");
		return nullptr;
	}

	return static_cast<TLISwapchain*>(swapchainVK);
}

void TLGraphicsContextVK::Present(TLISwapchain* swapchain)
{
	TLSwapchainVK* swapchainVK = static_cast<TLSwapchainVK*>(swapchain);

	
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
	VK_CHECK_ERROR(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));

	std::vector<VkLayerProperties> layerProps(layerCount);
	VK_CHECK_ERROR(vkEnumerateInstanceLayerProperties(&layerCount, layerProps.data()));

	std::vector<const char*> enabledLayerNames;
	for (int i = 0; i < layerCount; i++)
	{
		enabledLayerNames.push_back(layerProps[i].layerName);
	}

	uint32 extensionCount;
	VK_CHECK_ERROR(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
	
	std::vector<VkExtensionProperties> extensionProps(extensionCount);
	VK_CHECK_ERROR(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProps.data()));

	std::vector<const char*> supportedExtensionNames;
	for (int i = 0; i < extensionCount; i++)
	{
		supportedExtensionNames.push_back(extensionProps[i].extensionName);
	}
	
	std::vector<const char*> enabledExtensionNames;
	for (const char* extension : supportedExtensionNames)
	{
		if (std::string("VK_KHR_Surface") == std::string(extension) ||
			std::string("VK_KHR_win32_surface") == std::string(extension))
		{
			enabledExtensionNames.push_back(extension);
		}
	}

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = enabledLayerNames.size();
	createInfo.ppEnabledLayerNames = enabledLayerNames.data();
	createInfo.enabledExtensionCount = enabledExtensionNames.size();
	createInfo.ppEnabledExtensionNames = enabledExtensionNames.data();

	VK_CHECK_ERROR(vkCreateInstance(&createInfo, nullptr, &_instance));

	return true;
}

// TODO: Queue Family�� VkQueue���� ������ �и��ϴ� �� ���� ���δ�.
bool TLGraphicsContextVK::createDevice()
{
	TL_CHECK(_instance != nullptr, "VkInstance isn't created yet.");

	uint32 physicalDeviceCount = 0;
	VK_CHECK_ERROR(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	VK_CHECK_ERROR(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, physicalDevices.data()));

	_physicalDevice = physicalDevices[0];

	// TODO: Physical Device ���� ���� �߰��ϱ�.
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
	VK_CHECK_ERROR(vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &deviceExtensionCount, nullptr));

	std::vector<VkExtensionProperties> deviceExtensionProps(deviceExtensionCount);
	VK_CHECK_ERROR(vkEnumerateDeviceExtensionProperties(_physicalDevice, nullptr, &deviceExtensionCount, deviceExtensionProps.data()));

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

	VK_CHECK_ERROR(vkCreateDevice(_physicalDevice, &deviceCreateInfo, nullptr, &_logicalDevice));

	vkGetDeviceQueue(_logicalDevice, queueFamilyIndex, 0, &_queue);
	
	
	return true;
}

void TLGraphicsContextVK::Shutdown()
{
	//Not implemented yet;
}

TL_NS_GRAPHICS_END