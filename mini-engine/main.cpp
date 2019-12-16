
#define VK_NO_PROTOTYPES
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdio>
#include <cassert>

#define VULKAN_ASSERT(Condition) \
	assert(Condition)

#define VULKAN_CHECK(Result) \
	VULKAN_ASSERT(Result == VK_SUCCESS)

#define VULKAN_CORE_FUNCTIONS(Macro) \
	Macro(vkCreateInstance)

#define VULKAN_INSTANCE_FUNCTIONS(Macro) \
	Macro(vkDestroyInstance)

#define VULKAN_DEVICE_FUNCTIONS(Macro)

#define VULKAN_DEFINE_FUNCTION(Name) \
	PFN_##Name Name;

#define VULKAN_LOAD_CORE_FUNCTION(Name) \
	Context->Name = (PFN_##Name)Context->vkGetInstanceProcAddr(nullptr, #Name); \
	VULKAN_ASSERT(Context->Name);

#define VULKAN_LOAD_INSTANCE_FUNCTION(Name) \
	Context->Name = (PFN_##Name)Context->vkGetInstanceProcAddr(Context->Instance, #Name); \
	VULKAN_ASSERT(Context->Name);

struct vulkan_context
{
	HMODULE VulkanDLL;

	PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
	
	VULKAN_CORE_FUNCTIONS(VULKAN_DEFINE_FUNCTION)
	VULKAN_INSTANCE_FUNCTIONS(VULKAN_DEFINE_FUNCTION)

	VkInstance Instance;
};

vulkan_context *CreateVulkanContext()
{
	vulkan_context *Context = (vulkan_context *)calloc(1, sizeof(vulkan_context));
	Context->VulkanDLL = LoadLibraryA("vulkan-1.dll");
	Context->vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(Context->VulkanDLL, "vkGetInstanceProcAddr");

	VULKAN_CORE_FUNCTIONS(VULKAN_LOAD_CORE_FUNCTION);

	VkApplicationInfo ApplicationInfo{};
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.pApplicationName = "Vulkan Learning";
	ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
	ApplicationInfo.pEngineName = "Vulkan Learning";
	ApplicationInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
	ApplicationInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo InstanceCI{};
	InstanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCI.pApplicationInfo = &ApplicationInfo;
	InstanceCI.enabledLayerCount = 0;
	InstanceCI.ppEnabledLayerNames = nullptr;
	InstanceCI.enabledExtensionCount = 0;
	InstanceCI.ppEnabledExtensionNames = nullptr;

	VULKAN_CHECK(Context->vkCreateInstance(&InstanceCI, nullptr, &Context->Instance));

	VULKAN_INSTANCE_FUNCTIONS(VULKAN_LOAD_INSTANCE_FUNCTION)

	return Context;
}

void DestroyVulkanContext(vulkan_context *Context)
{
	Context->vkDestroyInstance(Context->Instance, nullptr);

	free(Context);
}

int main(int argc, char *argv[])
{
	vulkan_context *Context = CreateVulkanContext();

	DestroyVulkanContext(Context);

	return 0;
}
