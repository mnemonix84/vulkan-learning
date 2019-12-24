
#ifdef _DEBUG
#define DEBUG_BUILD 1
#else
#define DEBUG_BUILD 0
#endif

#ifdef _WIN32
#define PLATFORM_WINDOWS 1
#else
#define PLATFORM_WINDOWS 0
#endif

#define VK_NO_PROTOTYPES
#if PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cstdio>
#include <cassert>
#include <cstring>

#define BYTES(Count) (Count)
#define KIBIBYTES(Count) (Count*1024*BYTES(1))
#define MEBIBYTES(Count) (Count*1024*KIBIBYTES(1))
#define GIBIBYTES(Count) (Count*1024*MEBIBYTES(1))

#define ARRAY_SIZE(Array) \
	sizeof(Array) / sizeof((Array)[0])

#if DEBUG_BUILD
#define ASSERT(Condition) \
	assert(Condition)
#else
#define ASSERT(Condition)
#endif

#define ASSERT_ALWAYS(Condition) \
	assert(Condition)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

struct memory_arena
{
	void *Memory;
	u32 ReservedSize;
	u32 CommitSize;
};

void MemoryArena_Init(memory_arena *Arena, void *Memory, u32 Size)
{
	Arena->Memory = Memory;
	Arena->ReservedSize = Size;
	Arena->CommitSize = 0;
}

void *MemoryArena_PushSize(memory_arena *Arena, u32 Size)
{
	ASSERT((Arena->CommitSize + Size) <= Arena->ReservedSize);
	void *Result = (u8 *)Arena->Memory + Arena->CommitSize;
	Arena->CommitSize += Size;
	return Result;
}

struct memory_arena_temporary
{
	memory_arena *MemoryArena;
	u32 CommitSize;
};

memory_arena_temporary MemoryArena_BeginTemporary(memory_arena *Arena)
{
	memory_arena_temporary Result;
	Result.MemoryArena = Arena;
	Result.CommitSize = Arena->CommitSize;
	return Result;
}

void MemoryArena_EndTemporary(memory_arena_temporary *Marker)
{
	memory_arena *Arena = Marker->MemoryArena;
	Arena->CommitSize = Marker->CommitSize;
}

#define VULKAN_CHECK(Result) \
	ASSERT_ALWAYS(Result == VK_SUCCESS)

#define VULKAN_CORE_FUNCTIONS(Macro) \
	Macro(vkEnumerateInstanceLayerProperties) \
	Macro(vkEnumerateInstanceExtensionProperties) \
	Macro(vkCreateInstance)

#define VULKAN_INSTANCE_FUNCTIONS(Macro) \
	Macro(vkDestroyInstance) \
	Macro(vkGetDeviceProcAddr) \
	Macro(vkEnumeratePhysicalDevices) \
	Macro(vkGetPhysicalDeviceProperties) \
	Macro(vkGetPhysicalDeviceQueueFamilyProperties) \
	Macro(vkGetPhysicalDeviceWin32PresentationSupportKHR) \
	Macro(vkCreateDevice) \
	Macro(vkEnumerateDeviceLayerProperties) \
	Macro(vkEnumerateDeviceExtensionProperties) \
	Macro(vkDestroySurfaceKHR) \
	Macro(vkGetPhysicalDeviceSurfaceSupportKHR) \
	Macro(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
	Macro(vkGetPhysicalDeviceSurfaceFormatsKHR) \
	Macro(vkGetPhysicalDeviceSurfacePresentModesKHR)

#define VULKAN_DEBUG_FUNCTIONS(Macro) \
	Macro(vkCreateDebugReportCallbackEXT) \
	Macro(vkDestroyDebugReportCallbackEXT)

#define VULKAN_WIN32_INSTANCE_FUNCTIONS(Macro) \
	Macro(vkCreateWin32SurfaceKHR)

#define VULKAN_DEVICE_FUNCTIONS(Macro)

#define VULKAN_DEFINE_FUNCTION(Name) \
	PFN_##Name Name;

#define VULKAN_LOAD_CORE_FUNCTION(Name) \
	Context->Name = (PFN_##Name)Context->vkGetInstanceProcAddr(nullptr, #Name); \
	ASSERT_ALWAYS(Context->Name);

#define VULKAN_LOAD_INSTANCE_FUNCTION(Name) \
	Context->Name = (PFN_##Name)Context->vkGetInstanceProcAddr(Context->Instance, #Name); \
	ASSERT_ALWAYS(Context->Name);

struct vulkan_context
{
	memory_arena PersistentMemory;
	memory_arena TransientMemory;

	HMODULE VulkanDLL;

	PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
	
	VULKAN_CORE_FUNCTIONS(VULKAN_DEFINE_FUNCTION)
	VULKAN_INSTANCE_FUNCTIONS(VULKAN_DEFINE_FUNCTION)
	VULKAN_DEBUG_FUNCTIONS(VULKAN_DEFINE_FUNCTION)
	VULKAN_WIN32_INSTANCE_FUNCTIONS(VULKAN_DEFINE_FUNCTION)

	HINSTANCE Win32Instance;
	HWND Win32Window;

	VkInstance Instance;
	VkSurfaceKHR Surface;
	VkDebugReportCallbackEXT DebugReportCallback;
	VkPhysicalDevice PhysicalDevice;
	VkDevice Device;
	u32 GraphicsQueue;
	u32 TransferQueue;
};

void DebugPrintf(const char *Format, ...)
{
	va_list ArgList;
	va_start(ArgList, Format);
	char Buffer[1024];
	vsnprintf(Buffer, sizeof(Buffer), Format, ArgList);
	OutputDebugStringA(Buffer);
	va_end(ArgList);
}

VkBool32 Vulkan_DebugReport(VkDebugReportFlagsEXT Flags, VkDebugReportObjectTypeEXT ObjectType,
	uint64_t Object, size_t Location, int32_t MessageCode, const char* LayerPrefix,
	const char* Message, void* UserData)
{
	const char *Type = nullptr;

	switch (Flags)
	{
	case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
		Type = "INFO";
		break;
	case VK_DEBUG_REPORT_WARNING_BIT_EXT:
		Type = "WARN";
		break;
	case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
		Type = "PERF-WARN";
		break;
	case VK_DEBUG_REPORT_ERROR_BIT_EXT:
		Type = "ERROR";
		break;
	case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
		Type = "DEBUG";
		break;
	default:
		ASSERT(!"invalid code path");
	}

	DebugPrintf("[%s] %s\n", Type, Message);
	return VK_FALSE;
}

void Vulkan_Initialize(vulkan_context *Context)
{
	memory_arena_temporary Marker = MemoryArena_BeginTemporary(&Context->TransientMemory);

	Context->VulkanDLL = LoadLibraryA("vulkan-1.dll");
	Context->vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(Context->VulkanDLL, "vkGetInstanceProcAddr");

	VULKAN_CORE_FUNCTIONS(VULKAN_LOAD_CORE_FUNCTION);

	u32 InstanceLayerPropsCount = 0;
	VkLayerProperties *InstanceLayerProps = nullptr;

	VULKAN_CHECK(Context->vkEnumerateInstanceLayerProperties(&InstanceLayerPropsCount, nullptr));
	InstanceLayerProps = (VkLayerProperties *)MemoryArena_PushSize(&Context->TransientMemory, InstanceLayerPropsCount*sizeof(VkLayerProperties));
	VULKAN_CHECK(Context->vkEnumerateInstanceLayerProperties(&InstanceLayerPropsCount, InstanceLayerProps));

	u32 InstanceExtensionPropsCount = 0;
	VkExtensionProperties *InstanceExtensionProps = nullptr;

	VULKAN_CHECK(Context->vkEnumerateInstanceExtensionProperties(nullptr, &InstanceExtensionPropsCount, nullptr));
	InstanceExtensionProps = (VkExtensionProperties *)MemoryArena_PushSize(&Context->TransientMemory, InstanceExtensionPropsCount*sizeof(VkExtensionProperties));
	VULKAN_CHECK(Context->vkEnumerateInstanceExtensionProperties(nullptr, &InstanceExtensionPropsCount, InstanceExtensionProps));
	
	int LayerCount = 0;
	const char *Layers[128] = {};

	bool StandardValidationLayerSupported = false;

	for (int Index = 0;
	     Index != InstanceLayerPropsCount;
			 Index++)
	{
		if (DEBUG_BUILD && strcmp(InstanceLayerProps[Index].layerName, "VK_LAYER_LUNARG_standard_validation") == 0)
		{
			Layers[LayerCount++] = "VK_LAYER_LUNARG_standard_validation";
			StandardValidationLayerSupported = true;
		}
	}

#if DEBUG_BUILD
	if (!StandardValidationLayerSupported)
	{
		// Error
	}
#endif

	int ExtensionCount = 0;
	const char *Extensions[128] = {};

	bool SurfaceExtensionSupported = false;
	bool Win32SurfaceExtensionSupported = false;
	bool DebugReportSupported = false;

	for (int Index = 0;
	     Index != InstanceExtensionPropsCount;
			 Index++)
	{
		if (strcmp(InstanceExtensionProps[Index].extensionName, "VK_KHR_surface") == 0)
		{
			Extensions[ExtensionCount++] = "VK_KHR_surface";
			SurfaceExtensionSupported = true;
		}
		if (strcmp(InstanceExtensionProps[Index].extensionName, "VK_KHR_win32_surface") == 0)
		{
			Extensions[ExtensionCount++] = "VK_KHR_win32_surface";
			Win32SurfaceExtensionSupported = true;
		}
		if (DEBUG_BUILD && strcmp(InstanceExtensionProps[Index].extensionName, "VK_EXT_debug_report") == 0)
		{
			Extensions[ExtensionCount++] = "VK_EXT_debug_report";
			DebugReportSupported = true;
		}
	}

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
	InstanceCI.enabledLayerCount = LayerCount;
	InstanceCI.ppEnabledLayerNames = Layers;
	InstanceCI.enabledExtensionCount = ExtensionCount;
	InstanceCI.ppEnabledExtensionNames = Extensions;

	VULKAN_CHECK(Context->vkCreateInstance(&InstanceCI, nullptr, &Context->Instance));

	VULKAN_INSTANCE_FUNCTIONS(VULKAN_LOAD_INSTANCE_FUNCTION)

	if (DebugReportSupported)
	{
		VULKAN_DEBUG_FUNCTIONS(VULKAN_LOAD_INSTANCE_FUNCTION)

		VkDebugReportCallbackCreateInfoEXT DebugReportCallbackCI = {};
		DebugReportCallbackCI.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		DebugReportCallbackCI.flags =
			//VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
			VK_DEBUG_REPORT_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
			VK_DEBUG_REPORT_ERROR_BIT_EXT |
			//VK_DEBUG_REPORT_DEBUG_BIT_EXT |
			0;
		DebugReportCallbackCI.pfnCallback = Vulkan_DebugReport;
		DebugReportCallbackCI.pUserData = nullptr;

		VULKAN_CHECK(Context->vkCreateDebugReportCallbackEXT(Context->Instance, &DebugReportCallbackCI, nullptr, &Context->DebugReportCallback));
	}

	if (!SurfaceExtensionSupported)
	{
		// Error
	}

#if PLATFORM_WINDOWS
	if (Win32SurfaceExtensionSupported)
	{
		VULKAN_WIN32_INSTANCE_FUNCTIONS(VULKAN_LOAD_INSTANCE_FUNCTION)			

		VkWin32SurfaceCreateInfoKHR SurfaceCI = {};
		SurfaceCI.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		SurfaceCI.hinstance = Context->Win32Instance;
		SurfaceCI.hwnd = Context->Win32Window;

		VULKAN_CHECK(Context->vkCreateWin32SurfaceKHR(Context->Instance, &SurfaceCI, nullptr, &Context->Surface));
	}
	else
	{
		// Error
	}
#endif

	MemoryArena_EndTemporary(&Marker);
}

void Vulkan_Shutdown(vulkan_context *Context)
{
	Context->vkDestroyDebugReportCallbackEXT(Context->Instance, Context->DebugReportCallback, nullptr);
	Context->vkDestroyInstance(Context->Instance, nullptr);
}

void Vulkan_SelectDevice(vulkan_context *Context)
{
	memory_arena_temporary TemporaryMemory = MemoryArena_BeginTemporary(&Context->TransientMemory);

	u32 PhysicalDeviceCount = 0;
	VkPhysicalDevice *PhysicalDevices = nullptr;

	VULKAN_CHECK(Context->vkEnumeratePhysicalDevices(Context->Instance, &PhysicalDeviceCount, nullptr));
	PhysicalDevices = (VkPhysicalDevice *)MemoryArena_PushSize(&Context->TransientMemory, PhysicalDeviceCount*sizeof(VkPhysicalDevice));
	VULKAN_CHECK(Context->vkEnumeratePhysicalDevices(Context->Instance, &PhysicalDeviceCount, PhysicalDevices));

	VkPhysicalDevice SelectedPhysicalDevice = VK_NULL_HANDLE; 

	for (int PhysicalDeviceIndex = 0;
	     PhysicalDeviceIndex != PhysicalDeviceCount;
			 PhysicalDeviceIndex++)
	{
		VkPhysicalDevice CurrentPhysicalDevice = PhysicalDevices[PhysicalDeviceIndex];

		VkPhysicalDeviceProperties PhysicalDeviceProps;
		Context->vkGetPhysicalDeviceProperties(CurrentPhysicalDevice, &PhysicalDeviceProps);

		if (PhysicalDeviceProps.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			continue;

		u32 QueueFamilyCount = 0;
		VkQueueFamilyProperties *QueueFamilies = nullptr;

		Context->vkGetPhysicalDeviceQueueFamilyProperties(CurrentPhysicalDevice, &QueueFamilyCount, nullptr);
		QueueFamilies = (VkQueueFamilyProperties *)MemoryArena_PushSize(&Context->TransientMemory, QueueFamilyCount*sizeof(VkQueueFamilyProperties));
		Context->vkGetPhysicalDeviceQueueFamilyProperties(CurrentPhysicalDevice, &QueueFamilyCount, QueueFamilies);

		for (int QueueFamilyIndex = 0;
		     QueueFamilyIndex != QueueFamilyCount;
				 QueueFamilyIndex++)
		{
			VkQueueFamilyProperties *QueueFamily = QueueFamilies + QueueFamilyIndex;

			if (QueueFamily->queueCount == 0)
				continue;

			printf("queue family: %d\n", QueueFamilyIndex);

			bool HasPresentation = Context->vkGetPhysicalDeviceWin32PresentationSupportKHR(CurrentPhysicalDevice, QueueFamilyIndex);

			if (QueueFamily->queueFlags & VK_QUEUE_GRAPHICS_BIT)
				puts("  VK_QUEUE_GRAPHICS_BIT");
			if (QueueFamily->queueFlags & VK_QUEUE_COMPUTE_BIT)
				puts("  VK_QUEUE_COMPUTE_BIT");
			if (QueueFamily->queueFlags & VK_QUEUE_TRANSFER_BIT)
				puts("  VK_QUEUE_TRANSFER_BIT");
			if (QueueFamily->queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
				puts("  VK_QUEUE_SPARSE_BINDING_BIT");
			if (QueueFamily->queueFlags & VK_QUEUE_PROTECTED_BIT)
				puts("  VK_QUEUE_PROTECTED_BIT");
			if (HasPresentation)
				puts("  HasPresentation");
		}

		int GraphicsQueue = -1;
		int TransferQueue = -1;

		for (int QueueFamilyIndex = 0;
		     QueueFamilyIndex != QueueFamilyCount;
				 QueueFamilyIndex++)
		{
			VkQueueFamilyProperties *QueueFamily = QueueFamilies + QueueFamilyIndex;

			if (QueueFamily->queueCount == 0)
				continue;

			bool HasPresentation = Context->vkGetPhysicalDeviceWin32PresentationSupportKHR(CurrentPhysicalDevice, QueueFamilyIndex);

			// NOTE: graphics queue should have both presentation and graphics support
			if (HasPresentation && QueueFamily->queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				GraphicsQueue = QueueFamilyIndex;
				break;
			}
		}

		for (int QueueFamilyIndex = 0;
		     QueueFamilyIndex != QueueFamilyCount;
				 QueueFamilyIndex++)
		{
			VkQueueFamilyProperties *CurrQueueFamilyProps = QueueFamilies + QueueFamilyIndex;

			if (CurrQueueFamilyProps->queueCount == 0)
				continue;

			// NOTE: we want DMA transfer queue for async transfers (CPU <-> GPU)
			if (CurrQueueFamilyProps->queueFlags & VK_QUEUE_TRANSFER_BIT &&
			    !(CurrQueueFamilyProps->queueFlags & VK_QUEUE_GRAPHICS_BIT) &&
					!(CurrQueueFamilyProps->queueFlags & VK_QUEUE_COMPUTE_BIT))
			{
				TransferQueue = QueueFamilyIndex;
				break;
			}
		}

		if (GraphicsQueue != -1)
		{
			Context->PhysicalDevice = CurrentPhysicalDevice;

			Context->GraphicsQueue = GraphicsQueue;
			Context->TransferQueue = TransferQueue;

			u32 DeviceLayerPropsCount = 0;
			VULKAN_CHECK(Context->vkEnumerateDeviceLayerProperties(Context->PhysicalDevice, &DeviceLayerPropsCount, nullptr));
			VkLayerProperties *DeviceLayerProps = (VkLayerProperties *)MemoryArena_PushSize(&Context->TransientMemory, DeviceLayerPropsCount*sizeof(VkLayerProperties));
			VULKAN_CHECK(Context->vkEnumerateDeviceLayerProperties(Context->PhysicalDevice, &DeviceLayerPropsCount, DeviceLayerProps));

			u32 DeviceExtensionPropsCount = 0;
			VULKAN_CHECK(Context->vkEnumerateDeviceExtensionProperties(Context->PhysicalDevice, nullptr, &DeviceExtensionPropsCount, nullptr));
			VkExtensionProperties *DeviceExtensionProps = (VkExtensionProperties *)MemoryArena_PushSize(&Context->TransientMemory, DeviceExtensionPropsCount*sizeof(VkExtensionProperties));
			VULKAN_CHECK(Context->vkEnumerateDeviceExtensionProperties(Context->PhysicalDevice, nullptr, &DeviceExtensionPropsCount, DeviceExtensionProps));

			VkBool32 SurfaceSupported = false;
			VULKAN_CHECK(Context->vkGetPhysicalDeviceSurfaceSupportKHR(Context->PhysicalDevice, Context->GraphicsQueue, Context->Surface, &SurfaceSupported));

			ASSERT_ALWAYS(SurfaceSupported);

			u32 SurfaceFormatCount = 0;
			VULKAN_CHECK(Context->vkGetPhysicalDeviceSurfaceFormatsKHR(Context->PhysicalDevice, Context->Surface, &SurfaceFormatCount, nullptr));
			VkSurfaceFormatKHR *SurfaceFormats = (VkSurfaceFormatKHR *)MemoryArena_PushSize(&Context->TransientMemory, SurfaceFormatCount*sizeof(VkSurfaceFormatKHR));


			VkDevice Device;
			VkDeviceCreateInfo DeviceCI = {};
			DeviceCI.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			
			VULKAN_CHECK(Context->vkCreateDevice(SelectedPhysicalDevice, &DeviceCI, nullptr, &Device));

			// KK_KHR_swapchain

			break;
		}	
	}

	MemoryArena_EndTemporary(&TemporaryMemory);
}

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_ERASEBKGND:
		return 1; // indicates erased
	}

	return DefWindowProcA(Window, Message, WParam, LParam);
}

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PSTR CmdLine, int CmdShow)
{
	memory_arena PersistentMemory;
	memory_arena TransientMemory;

	{
		u32 Size = MEBIBYTES(256);
		void *Memory = calloc(1, Size);
		ASSERT(Memory);
		MemoryArena_Init(&PersistentMemory, Memory, Size);
	}

	{
		u32 Size = MEBIBYTES(256);
		void *Memory = calloc(1, Size);
		ASSERT(Memory);
		MemoryArena_Init(&TransientMemory, Memory, Size);
	}

	vulkan_context *Context = (vulkan_context *)MemoryArena_PushSize(&PersistentMemory, sizeof(vulkan_context));
	Context->PersistentMemory = PersistentMemory;
	Context->TransientMemory = TransientMemory;

	WNDCLASSEXA WindowClass = {};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpszClassName = "VulkanWindowClass";
	WindowClass.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	WindowClass.hIcon = WindowClass.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);
	WindowClass.lpfnWndProc = WindowProc;

	if (!RegisterClassExA(&WindowClass))
	{	
		// Error
	}

	Context->Win32Window = CreateWindowExA(WS_EX_OVERLAPPEDWINDOW, "VulkanWindowClass", "Vulkan",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, Instance, nullptr);

	if (!Context->Win32Window)
	{
		// Error
	}

	ShowWindow(Context->Win32Window, SW_SHOW);

	Context->Win32Instance = Instance;

	Vulkan_Initialize(Context);
	Vulkan_SelectDevice(Context);

	bool Running = true;

	while (Running)
	{
		MSG Message;
		while (PeekMessageA(&Message, nullptr, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				Running = false;

			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}

		// Render
	}

	Vulkan_Shutdown(Context);

	free(PersistentMemory.Memory);
	free(TransientMemory.Memory);

	return 0;
}
