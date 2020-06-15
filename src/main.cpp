
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <array>
#include <assert.h>

#include "vk_mem_alloc.h"
#include "shaderc/shaderc.h"

namespace vk
{
	#define VK_GENERAL_FUNCTIONS(macro) \
		macro(vkCreateInstance) \
		macro(vkEnumerateInstanceExtensionProperties) \
		macro(vkEnumerateInstanceLayerProperties)

	#define VK_INSTANCE_FUNCTIONS(macro) \
		macro(vkCreateDebugUtilsMessengerEXT) \
		macro(vkDestroyDebugUtilsMessengerEXT) \
		macro(vkDestroyInstance) \
		macro(vkGetDeviceProcAddr) \
		macro(vkEnumeratePhysicalDevices) \
		macro(vkEnumerateDeviceLayerProperties) \
		macro(vkEnumerateDeviceExtensionProperties) \
		macro(vkGetPhysicalDeviceProperties) \
		macro(vkGetPhysicalDeviceQueueFamilyProperties) \
		macro(vkCreateDevice) \
		macro(vkGetPhysicalDeviceImageFormatProperties) \
		macro(vkGetPhysicalDeviceSurfaceCapabilitiesKHR) \
		macro(vkGetPhysicalDeviceSurfaceFormatsKHR) \
		macro(vkGetPhysicalDeviceSurfacePresentModesKHR) \
		

	#define VK_DEVICE_FUNCTIONS(macro) \
		macro(vkDestroyDevice) \
		macro(vkGetDeviceQueue) \
		macro(vkCreateSwapchainKHR) \
		macro(vkDestroySwapchainKHR) \
		macro(vkGetSwapchainImagesKHR) \
		macro(vkAcquireNextImageKHR) \
		macro(vkQueuePresentKHR) \
		macro(vkCreateCommandPool) \
		macro(vkTrimCommandPool) \
		macro(vkResetCommandPool) \
		macro(vkDestroyCommandPool) \
		macro(vkAllocateCommandBuffers) \
		macro(vkResetCommandBuffer) \
		macro(vkFreeCommandBuffers) \
		macro(vkBeginCommandBuffer) \
		macro(vkEndCommandBuffer) \
		macro(vkQueueSubmit) \
		macro(vkCmdExecuteCommands) \
		macro(vkCreateFence) \
		macro(vkDestroyFence) \
		macro(vkGetFenceStatus) \
		macro(vkResetFences) \
		macro(vkWaitForFences) \
		macro(vkCreateSemaphore) \
		macro(vkDestroySemaphore) \
		macro(vkCreateEvent) \
		macro(vkDestroyEvent) \
		macro(vkGetEventStatus) \
		macro(vkSetEvent) \
		macro(vkResetEvent) \
		macro(vkCmdSetEvent) \
		macro(vkCmdResetEvent) \
		macro(vkCmdWaitEvents) \
		macro(vkCmdPipelineBarrier) \
		macro(vkQueueWaitIdle) \
		macro(vkDeviceWaitIdle) \
		macro(vkCreateRenderPass) \
		macro(vkDestroyRenderPass) \
		macro(vkCreateFramebuffer) \
		macro(vkDestroyFramebuffer) \
		macro(vkCmdBeginRenderPass) \
		macro(vkGetRenderAreaGranularity) \
		macro(vkCmdNextSubpass) \
		macro(vkCmdEndRenderPass) \
		macro(vkCreateShaderModule) \
		macro(vkDestroyShaderModule) \
		macro(vkCreateComputePipelines) \
		macro(vkCreateGraphicsPipelines) \
		macro(vkDestroyPipeline) \
		macro(vkCreatePipelineCache) \
		macro(vkMergePipelineCaches) \
		macro(vkGetPipelineCacheData) \
		macro(vkDestroyPipelineCache) \
		macro(vkCmdBindPipeline) \
		macro(vkGetPhysicalDeviceMemoryProperties) \
		macro(vkGetPhysicalDeviceMemoryProperties2) \
		macro(vkAllocateMemory) \
		macro(vkFreeMemory) \
		macro(vkMapMemory) \
		macro(vkFlushMappedMemoryRanges) \
		macro(vkInvalidateMappedMemoryRanges) \
		macro(vkUnmapMemory) \
		macro(vkGetDeviceMemoryCommitment) \
		macro(vkCreateBuffer) \
		macro(vkDestroyBuffer) \
		macro(vkCreateBufferView) \
		macro(vkDestroyBufferView) \
		macro(vkCreateImage) \
		macro(vkGetImageSubresourceLayout) \
		macro(vkDestroyImage) \
		macro(vkCreateImageView) \
		macro(vkDestroyImageView) \
		macro(vkGetBufferMemoryRequirements) \
		macro(vkGetBufferMemoryRequirements2) \
		macro(vkGetImageMemoryRequirements) \
		macro(vkGetImageMemoryRequirements2) \
		macro(vkBindBufferMemory) \
		macro(vkBindBufferMemory2) \
		macro(vkBindImageMemory) \
		macro(vkBindImageMemory2) \
		macro(vkCreateSampler) \
		macro(vkDestroySampler) \
		macro(vkCreateDescriptorSetLayout) \
		macro(vkGetDescriptorSetLayoutSupport) \
		macro(vkDestroyDescriptorSetLayout) \
		macro(vkCreatePipelineLayout) \
		macro(vkDestroyPipelineLayout) \
		macro(vkCreateDescriptorPool) \
		macro(vkDestroyDescriptorPool) \
		macro(vkAllocateDescriptorSets) \
		macro(vkFreeDescriptorSets) \
		macro(vkResetDescriptorPool) \
		macro(vkUpdateDescriptorSets) \
		macro(vkCreateDescriptorUpdateTemplate) \
		macro(vkDestroyDescriptorUpdateTemplate) \
		macro(vkUpdateDescriptorSetWithTemplate) \
		macro(vkCmdBindDescriptorSets) \
		macro(vkCmdPushConstants) \
		macro(vkCreateQueryPool) \
		macro(vkDestroyQueryPool) \
		macro(vkCmdResetQueryPool) \
		macro(vkCmdBeginQuery) \
		macro(vkCmdEndQuery) \
		macro(vkGetQueryPoolResults) \
		macro(vkCmdCopyQueryPoolResults) \
		macro(vkCmdWriteTimestamp) \
		macro(vkCmdClearColorImage) \
		macro(vkCmdClearDepthStencilImage) \
		macro(vkCmdClearAttachments) \
		macro(vkCmdFillBuffer) \
		macro(vkCmdUpdateBuffer) \
		macro(vkCmdBindIndexBuffer) \
		macro(vkCmdDraw) \
		macro(vkCmdDrawIndexed) \
		macro(vkCmdDrawIndirect) \
		macro(vkCmdDrawIndexedIndirect) \
		macro(vkCmdCopyBuffer) \
		macro(vkCmdCopyImage) \
		macro(vkCmdCopyBufferToImage) \
		macro(vkCmdCopyImageToBuffer) \
		macro(vkCmdBlitImage) \
		macro(vkCmdResolveImage) \
		macro(vkCmdSetViewport) \
		macro(vkCmdSetLineWidth) \
		macro(vkCmdSetDepthBias) \
		macro(vkCmdSetBlendConstants) \
		macro(vkCmdSetScissor) \
		macro(vkCmdSetDepthBounds) \
		macro(vkCmdSetStencilCompareMask) \
		macro(vkCmdSetStencilWriteMask) \
		macro(vkCmdSetStencilReference) \
		macro(vkCmdDispatch) \
		macro(vkCmdDispatchIndirect) \
		macro(vkCmdDispatchBase) \
		macro(vkGetPhysicalDeviceSparseImageFormatProperties) \
		macro(vkGetPhysicalDeviceSparseImageFormatProperties2) \
		macro(vkGetImageSparseMemoryRequirements) \
		macro(vkGetImageSparseMemoryRequirements2) \
		macro(vkQueueBindSparse)

	#define VK_DECLARE_FUNCTION(name) \
		PFN_##name name;

	#define VK_GET_GENERAL_FUNCTION(name) \
		name = (PFN_##name)glfwGetInstanceProcAddress(nullptr, #name); \
		if (!name) { fprintf(stderr, "Failed to load Vulkan general function '%s'.\n", #name); abort(); }

	#define VK_GET_INSTANCE_FUNCTION(name) \
		name = (PFN_##name)glfwGetInstanceProcAddress(context->instance, #name); \
		if (!name) { fprintf(stderr, "Failed to load Vulkan instance function '%s'.\n", #name); abort(); }

	#define VK_GET_DEVICE_FUNCTION(name) \
		name = (PFN_##name)vkGetDeviceProcAddr(context->logicalDevice, #name); \
		if (!name) { fprintf(stderr, "Failed to load Vulkan device function '%s'.\n", #name); abort(); }

	VK_GENERAL_FUNCTIONS(VK_DECLARE_FUNCTION)
	VK_INSTANCE_FUNCTIONS(VK_DECLARE_FUNCTION)
	VK_DEVICE_FUNCTIONS(VK_DECLARE_FUNCTION)

	struct Queue
	{
		int familyIndex;
		VkQueue handle;
	};

	struct CommandBuffer
	{
		VkCommandBuffer handle;
		int commandPool;
	};

	struct CommandPool
	{
		VkCommandPool handle;
		std::vector<int> commandBuffers;
	};

	struct Image
	{
		VkImage handle;
		VmaAllocation allocation;
		std::vector<int> imageViews;
		bool swapchain;
	};

	struct ImageView
	{
		VkImageView handle;
		int image;
	};

	struct Buffer
	{
		VkBuffer handle;
		VmaAllocation allocation;
		std::vector<int> bufferViews;
	};

	struct BufferView
	{
		VkBufferView handle;
		int buffer;
	};

	struct ShaderModule
	{
		VkShaderModule handle;
	};

	struct Framebuffer
	{
		VkFramebuffer handle;
	};

	struct RenderPass
	{
		VkRenderPass handle;
	};

	struct Pipeline
	{
		VkPipeline handle;
	};

	struct DescriptorSetLayout
	{
		VkDescriptorSetLayout handle;
	};

	struct PipelineLayout
	{
		VkPipelineLayout handle;
	};

	struct Context
	{
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugUtilsMessenger;
		VkSurfaceKHR surface;
		VkPhysicalDevice physicalDevice;
		VkSurfaceCapabilitiesKHR surfaceCaps;
		VkPhysicalDeviceProperties deviceProperties;
		VkDevice logicalDevice;
		VmaVulkanFunctions vmaVulkanFunctions;
		VmaAllocator vmaAllocator;
		Queue graphicsQueue;
		Queue presentationQueue;
		Queue transferQueue;
		VkSwapchainKHR swapchain;
		std::vector<CommandPool> commandPools;
		std::vector<CommandBuffer> commandBuffers;
		std::vector<ShaderModule> shaderModules;
		std::vector<Image> images;
		std::vector<ImageView> imageViews;
		std::vector<Buffer> buffers;
		std::vector<BufferView> bufferViews;
		std::vector<Framebuffer> framebuffers;
		std::vector<RenderPass> renderPasses;
		std::vector<Pipeline> pipelines;
		std::vector<DescriptorSetLayout> descriptorSetLayouts;
		std::vector<PipelineLayout> pipelineLayouts;
	};

	int createImage2DView(Context *context, int image, VkFormat format, VkImageAspectFlags aspectFlags);

	#define VK_VERIFY_CALL(call) verifyCall((call), #call, __FILE__, __LINE__)
	inline void verifyCall(VkResult result, const char *call, const char *file, int line)
	{
		if (result != VK_SUCCESS)
		{
			fprintf(stderr, "Vulkan call '%s' in file '%s' on line %d failed with result code %d.\n", call, file, line, result);
			abort();
		}

		return;
	}

	std::vector<VkExtensionProperties> getInstanceExtensions(void)
	{
		uint32_t extensionCount = 0;
		VK_VERIFY_CALL(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
		std::vector<VkExtensionProperties> extensions;
		extensions.resize(extensionCount);
		VK_VERIFY_CALL(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()));
		return extensions;
	}

	std::vector<VkLayerProperties> getInstanceLayers(void)
	{
		uint32_t layerCount = 0;
		VK_VERIFY_CALL(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));
		std::vector<VkLayerProperties> layers;
		layers.resize(layerCount);
		VK_VERIFY_CALL(vkEnumerateInstanceLayerProperties(&layerCount, layers.data()));
		return layers;
	}

	std::vector<VkExtensionProperties> getDeviceExtensions(VkPhysicalDevice physicalDevice)
	{
		uint32_t extensionCount = 0;
		VK_VERIFY_CALL(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr));
		std::vector<VkExtensionProperties> extensions;
		extensions.resize(extensionCount);
		VK_VERIFY_CALL(vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, extensions.data()));
		return extensions;
	}

	std::vector<VkLayerProperties> getDeviceLayers(VkPhysicalDevice physicalDevice)
	{
		uint32_t layerCount = 0;
		VK_VERIFY_CALL(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, nullptr));
		std::vector<VkLayerProperties> layers;
		layers.resize(layerCount);
		VK_VERIFY_CALL(vkEnumerateDeviceLayerProperties(physicalDevice, &layerCount, layers.data()));
		return layers;
	}

	std::vector<VkPhysicalDevice> getPhysicalDevices(VkInstance instance)
	{
		uint32_t physicalDeviceCount = 0;
		VK_VERIFY_CALL(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr));
		std::vector<VkPhysicalDevice> physicalDevices;
		physicalDevices.resize(physicalDeviceCount);
		VK_VERIFY_CALL(vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data()));
		return physicalDevices;
	}

	std::vector<VkQueueFamilyProperties> getQueueFamilies(VkPhysicalDevice physicalDevice)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies;
		queueFamilies.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
		return queueFamilies;
	}

	std::vector<VkSurfaceFormatKHR> getSupportedSurfaceFormats(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
	{
		uint32_t surfaceFormatCount = 0;
		VK_VERIFY_CALL(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, nullptr));
		std::vector<VkSurfaceFormatKHR> surfaceFormats;
		surfaceFormats.resize(surfaceFormatCount);
		VK_VERIFY_CALL(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, surfaceFormats.data()));
		return surfaceFormats;
	}
	
	std::vector<VkPresentModeKHR> getSupportedPresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
	{
		uint32_t presentModeCount = 0;
		VK_VERIFY_CALL(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr));
		std::vector<VkPresentModeKHR> presentModes;
		presentModes.resize(presentModeCount);
		VK_VERIFY_CALL(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data()));
		return presentModes;
	}

	void printQueueFamily(VkQueueFamilyProperties queueFamily)
	{
		fprintf(stdout, "Queue family\n");
		fprintf(stdout, "  Queue count: %d\n", queueFamily.queueCount);
		fprintf(stdout, "  Valid timestamp bits: %d\n", queueFamily.timestampValidBits);
		fprintf(stdout, "  Min. image transfer granularity: %dx%dx%d\n", queueFamily.minImageTransferGranularity.width,
			                                                               queueFamily.minImageTransferGranularity.height,
																															       queueFamily.minImageTransferGranularity.depth);
		fprintf(stdout, "  Supported operations:\n");
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			fprintf(stdout, "    Graphics\n");
		if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
			fprintf(stdout, "    Compute\n");
		if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT )
			fprintf(stdout, "    Transfer\n");

		return;
	}

	template <typename T>
	int getFreeSlotForResource(std::vector<T> &resources)
	{
		int freeResourceSlot = -1;
		int resourceCount = (int)resources.size();

		for (int i = 0; i < resourceCount; i++)
		{
			if (!resources[i].handle)
			{
				freeResourceSlot = i;
				break;
			}
		}

		if (freeResourceSlot == -1)
		{
			resources.resize(resourceCount + 1);
			freeResourceSlot = resourceCount;
		}

		return freeResourceSlot;
	}

	void trackResource(std::vector<int> &list, int slot)
	{
		for (int i = 0, n = (int)list.size(); i < n; i++)
		{
			if (list[i] == -1)
			{
				list[i] = slot;
				return;
			}
		}

		list.push_back(slot);
	}

	std::vector<char> loadFromFile(const char *filename)
	{
		std::vector<char> content;
		FILE *f = fopen(filename, "rb");
		assert(f);
		fseek(f, 0, SEEK_END);
		long size = ftell(f);
		rewind(f);
		content.resize(size);
		if (fread(content.data(), 1, size, f) != size)
			content.clear();
		fclose(f);
		return content;
	}

	std::vector<char> compileGlslFileToSpirvBinary(const char *filename)
	{
		shaderc_shader_kind shaderKind;
		const char *fileExtension = strrchr(filename, '.');
		assert(fileExtension);

		if (fileExtension)
		{
			if (strcmp(fileExtension, ".vs") == 0)
			{
				shaderKind = shaderc_glsl_vertex_shader;
			}
			else if (strcmp(fileExtension, ".gs") == 0)
			{
				shaderKind = shaderc_glsl_geometry_shader;
			}
			else if (strcmp(fileExtension, ".tcs") == 0)
			{
				shaderKind = shaderc_glsl_tess_control_shader;
			}
			else if (strcmp(fileExtension, ".tes") == 0)
			{
				shaderKind = shaderc_glsl_tess_evaluation_shader;
			}
			else if (strcmp(fileExtension, ".fs") == 0)
			{
				shaderKind = shaderc_glsl_fragment_shader;
			}
			else if (strcmp(fileExtension, ".cs") == 0)
			{
				shaderKind = shaderc_glsl_compute_shader;
			}
			else
			{
				assert(!"GLSL shader file has no supported extension.");
			}
		}

		shaderc_compiler_t compiler = shaderc_compiler_initialize();
		shaderc_compile_options_t options = shaderc_compile_options_initialize();
		shaderc_compile_options_set_warnings_as_errors(options);
		
		#ifdef _DEBUG
		shaderc_compile_options_set_generate_debug_info(options);
		shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_zero);
		#else
		shaderc_compile_options_set_optimization_level(options, shaderc_optimization_level_performance);
		#endif

		auto source = loadFromFile(filename);
		shaderc_compilation_result_t result = shaderc_compile_into_spv(compiler, source.data(), source.size(), shaderKind, filename, "main", options);
    shaderc_compilation_status status = shaderc_result_get_compilation_status(result);

		std::vector<char> byteCode;

		if (status == shaderc_compilation_status_success)
		{
			size_t length = shaderc_result_get_length(result);
			const char *bytes = shaderc_result_get_bytes(result);
			byteCode.resize(length);
			memcpy(byteCode.data(), bytes, length);
		}
		else
		{
			const char *errorMessage = shaderc_result_get_error_message(result);
			fprintf(stderr, "Failed to compile shader from file '%s'. Error:\n%s\n", filename, errorMessage);
		}

    shaderc_result_release(result);
		shaderc_compile_options_release(options);
    shaderc_compiler_release(compiler);

		return byteCode;
	}

	int getFreeShaderModuleSlot(Context *context)
	{
		int freeShaderModuleSlot = -1;
		int shaderModuleCount = (int)context->shaderModules.size();

		for (int i = 0; i < shaderModuleCount; i++)
		{
			if (!context->shaderModules[i].handle)
			{
				freeShaderModuleSlot = i;
				break;
			}
		}

		if (freeShaderModuleSlot == -1)
		{
			context->shaderModules.resize(shaderModuleCount + 1);
			freeShaderModuleSlot = shaderModuleCount;
		}

		return freeShaderModuleSlot;
	}

	void createShaderModuleFromSpirvFile(Context *context, const char *filename)
	{
		int freeShaderModuleSlot = getFreeShaderModuleSlot(context);

		auto byteCode = loadFromFile(filename);

		VkShaderModuleCreateInfo shaderModuleCI = {};
		shaderModuleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCI.codeSize = byteCode.size();
		shaderModuleCI.pCode = (uint32_t *)byteCode.data();

		ShaderModule &shaderModule = context->shaderModules[freeShaderModuleSlot];

		VK_VERIFY_CALL(vkCreateShaderModule(context->logicalDevice, &shaderModuleCI, nullptr, &shaderModule.handle));
	}

	void createShaderModuleFromGlslFile(Context *context, const char *filename)
	{
		int freeShaderModuleSlot = getFreeShaderModuleSlot(context);

		auto byteCode = compileGlslFileToSpirvBinary(filename);

		VkShaderModuleCreateInfo shaderModuleCI = {};
		shaderModuleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCI.codeSize = byteCode.size();
		shaderModuleCI.pCode = (uint32_t *)byteCode.data();

		ShaderModule &shaderModule = context->shaderModules[freeShaderModuleSlot];

		VK_VERIFY_CALL(vkCreateShaderModule(context->logicalDevice, &shaderModuleCI, nullptr, &shaderModule.handle));
	}

	VkBool32 VKAPI_PTR vkDebugUtilsMessengerCallbackEXT(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                      VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                                      const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                                                      void *userData)
	{
		fprintf(stderr, "Vulkan Debug Utils: %s\n", callbackData->pMessage);
		return VK_FALSE;
	}

	std::unique_ptr<Context> createContext(const char *applicationName)
	{
		VK_GENERAL_FUNCTIONS(VK_GET_GENERAL_FUNCTION)

		std::vector<VkLayerProperties> layers = getInstanceLayers();
		std::vector<VkExtensionProperties> extensions = getInstanceExtensions();

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = applicationName;
		appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.pEngineName = applicationName;
		appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
		appInfo.apiVersion = VK_API_VERSION_1_2;

		std::array<const char *, 1> enabledLayers;
		enabledLayers[0] = "VK_LAYER_LUNARG_standard_validation";

		uint32_t requiredGLFWExtensionCount;
		const char **requiredGLFWExtensions = glfwGetRequiredInstanceExtensions(&requiredGLFWExtensionCount);

		std::vector<const char *> enabledExtensions;

		for (int i = 0; i < (int)requiredGLFWExtensionCount; i++)
			enabledExtensions.push_back(requiredGLFWExtensions[i]);

		bool hasDebugUtilsExtension = false;
		for (const char *extension : enabledExtensions)
		{
			if (strcmp(extension, "VK_EXT_debug_utils") == 0)
			{
				hasDebugUtilsExtension = true;
				break;
			}
		}
				
		if (!hasDebugUtilsExtension)
			enabledExtensions.push_back("VK_EXT_debug_utils");

		VkInstanceCreateInfo instanceCI = {};
		instanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCI.pApplicationInfo = &appInfo;
		instanceCI.enabledLayerCount = (uint32_t)enabledLayers.size();
		instanceCI.ppEnabledLayerNames = enabledLayers.data();
		instanceCI.enabledExtensionCount = (uint32_t)enabledExtensions.size();
		instanceCI.ppEnabledExtensionNames = enabledExtensions.data();

		auto context = std::make_unique<Context>();
		VK_VERIFY_CALL(vkCreateInstance(&instanceCI, nullptr, &context->instance));

		VK_INSTANCE_FUNCTIONS(VK_GET_INSTANCE_FUNCTION)

		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCI = {};
		debugUtilsMessengerCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugUtilsMessengerCI.messageSeverity = 0 |
		                                        //VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		                                        //VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
																						VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
																						VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
																						;
		debugUtilsMessengerCI.messageType = 0 |
		                                    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		                                    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
																				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
																				;
		debugUtilsMessengerCI.pfnUserCallback = vkDebugUtilsMessengerCallbackEXT;
		debugUtilsMessengerCI.pUserData = nullptr;

		VK_VERIFY_CALL(vkCreateDebugUtilsMessengerEXT(context->instance, &debugUtilsMessengerCI, nullptr, &context->debugUtilsMessenger));

		return context;
	}

	// spezifisch für Nvidia GTX 780
	void createDevice(Context *context)
	{
		std::vector<VkPhysicalDevice> physicalDevices = getPhysicalDevices(context->instance);

		context->physicalDevice = physicalDevices[0];
		vkGetPhysicalDeviceProperties(context->physicalDevice, &context->deviceProperties);

		VK_VERIFY_CALL(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context->physicalDevice, context->surface, &context->surfaceCaps));

		if (!glfwGetPhysicalDevicePresentationSupport(context->instance, context->physicalDevice, 0))
		{
			fprintf(stderr, "Queue family 0 does not support presentation.");
			abort();
		}

		std::array<VkDeviceQueueCreateInfo, 2> deviceQueueCIs = {};
		float queuePriorities[1] = { 1.0f };

		for (int i = 0; i < 2; i++)
		{
			VkDeviceQueueCreateInfo &deviceQueueCI = deviceQueueCIs[i];
			deviceQueueCI.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCI.queueFamilyIndex = i;
			deviceQueueCI.queueCount = 1;
			deviceQueueCI.pQueuePriorities = queuePriorities;
		}

		std::array<const char *, 1> enabledExtensions;
		enabledExtensions[0] = "VK_KHR_swapchain";

		VkDeviceCreateInfo deviceCI = {};
		deviceCI.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;	
		deviceCI.queueCreateInfoCount = (uint32_t)deviceQueueCIs.size();
		deviceCI.pQueueCreateInfos = deviceQueueCIs.data();
		deviceCI.enabledLayerCount = 0;
		deviceCI.ppEnabledLayerNames = nullptr;
		deviceCI.enabledExtensionCount = (uint32_t)enabledExtensions.size();
		deviceCI.ppEnabledExtensionNames = enabledExtensions.data();
		deviceCI.pEnabledFeatures = nullptr;

		VK_VERIFY_CALL(vkCreateDevice(context->physicalDevice, &deviceCI, nullptr, &context->logicalDevice));

		VK_DEVICE_FUNCTIONS(VK_GET_DEVICE_FUNCTION)

		context->vmaVulkanFunctions.vkAllocateMemory = vkAllocateMemory;
		context->vmaVulkanFunctions.vkBindBufferMemory = vkBindBufferMemory;
		context->vmaVulkanFunctions.vkBindBufferMemory2KHR = vkBindBufferMemory2;
		context->vmaVulkanFunctions.vkBindImageMemory = vkBindImageMemory;
		context->vmaVulkanFunctions.vkBindImageMemory2KHR = vkBindImageMemory2;
		context->vmaVulkanFunctions.vkCmdCopyBuffer = vkCmdCopyBuffer;
		context->vmaVulkanFunctions.vkCreateBuffer = vkCreateBuffer;
		context->vmaVulkanFunctions.vkCreateImage = vkCreateImage;
		context->vmaVulkanFunctions.vkDestroyBuffer = vkDestroyBuffer;
		context->vmaVulkanFunctions.vkDestroyImage = vkDestroyImage;
		context->vmaVulkanFunctions.vkFlushMappedMemoryRanges = vkFlushMappedMemoryRanges;
		context->vmaVulkanFunctions.vkFreeMemory = vkFreeMemory;
		context->vmaVulkanFunctions.vkGetBufferMemoryRequirements = vkGetBufferMemoryRequirements;
		context->vmaVulkanFunctions.vkGetBufferMemoryRequirements2KHR = vkGetBufferMemoryRequirements2;
		context->vmaVulkanFunctions.vkGetImageMemoryRequirements = vkGetImageMemoryRequirements;
		context->vmaVulkanFunctions.vkGetImageMemoryRequirements2KHR = vkGetImageMemoryRequirements2;
		context->vmaVulkanFunctions.vkGetPhysicalDeviceMemoryProperties = vkGetPhysicalDeviceMemoryProperties;
		context->vmaVulkanFunctions.vkGetPhysicalDeviceMemoryProperties2KHR = vkGetPhysicalDeviceMemoryProperties2;
		context->vmaVulkanFunctions.vkGetPhysicalDeviceProperties = vkGetPhysicalDeviceProperties;
		context->vmaVulkanFunctions.vkInvalidateMappedMemoryRanges = vkInvalidateMappedMemoryRanges;
		context->vmaVulkanFunctions.vkMapMemory = vkMapMemory;
		context->vmaVulkanFunctions.vkUnmapMemory = vkUnmapMemory;

		VmaAllocatorCreateInfo allocatorCI = {};
		allocatorCI.physicalDevice = context->physicalDevice;
		allocatorCI.device = context->logicalDevice;
		allocatorCI.pVulkanFunctions = &context->vmaVulkanFunctions;

		VK_VERIFY_CALL(vmaCreateAllocator(&allocatorCI, &context->vmaAllocator));

		context->graphicsQueue.familyIndex = 0;
		context->presentationQueue.familyIndex = 0;
		context->transferQueue.familyIndex = 1;

		vkGetDeviceQueue(context->logicalDevice, 0, 0,  &context->graphicsQueue.handle);
		vkGetDeviceQueue(context->logicalDevice, 0, 0,  &context->presentationQueue.handle);
		vkGetDeviceQueue(context->logicalDevice, 1, 0,  &context->transferQueue.handle);

		return;
	}

	void createSwapchain(Context *context, uint32_t width, uint32_t height, uint32_t imageCount)
	{
		if (imageCount < context->surfaceCaps.minImageCount)
			imageCount = context->surfaceCaps.minImageCount;
		if (context->surfaceCaps.maxImageCount != 0 && imageCount > context->surfaceCaps.maxImageCount)
			imageCount = context->surfaceCaps.maxImageCount;

		if (context->surfaceCaps.currentExtent.width == 0xFFFFFFFF)
		{ 
			if (width < context->surfaceCaps.minImageExtent.width)
				width = context->surfaceCaps.minImageExtent.width;
			if (width > context->surfaceCaps.maxImageExtent.width)
				width = context->surfaceCaps.maxImageExtent.width;

			if (height < context->surfaceCaps.minImageExtent.height)
				height = context->surfaceCaps.minImageExtent.height;
			if (height > context->surfaceCaps.maxImageExtent.height)
				height = context->surfaceCaps.maxImageExtent.height;
		}
		else
		{
			width = context->surfaceCaps.currentExtent.width;
			height = context->surfaceCaps.currentExtent.height;
		}

		VkSwapchainCreateInfoKHR swapchainCI = {};
		swapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCI.surface = context->surface;
		swapchainCI.minImageCount = 0;
		swapchainCI.imageFormat = VK_FORMAT_B8G8R8A8_SRGB;
		swapchainCI.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		swapchainCI.imageExtent.width = width;
		swapchainCI.imageExtent.height = height;
		swapchainCI.imageArrayLayers = 1;
		swapchainCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCI.queueFamilyIndexCount = 0;
		swapchainCI.pQueueFamilyIndices = nullptr;
		swapchainCI.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		swapchainCI.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCI.presentMode = VK_PRESENT_MODE_FIFO_KHR;
		swapchainCI.clipped = VK_FALSE;
		swapchainCI.oldSwapchain = VK_NULL_HANDLE;

		VK_VERIFY_CALL(vkCreateSwapchainKHR(context->logicalDevice, &swapchainCI, nullptr, &context->swapchain));

		uint32_t swapchainImageCount = 0;
		VK_VERIFY_CALL(vkGetSwapchainImagesKHR(context->logicalDevice, context->swapchain, &swapchainImageCount, nullptr));
		std::vector<VkImage> swapchainImages;
		swapchainImages.resize(swapchainImageCount);
		VK_VERIFY_CALL(vkGetSwapchainImagesKHR(context->logicalDevice, context->swapchain, &swapchainImageCount, swapchainImages.data()));

		for (int i = 0; i < (int)swapchainImageCount; i++)
		{
			int freeImageSlot = getFreeSlotForResource(context->images);
			VkImage swapchainImage = swapchainImages[i];
			Image &image = context->images[freeImageSlot];
			image.handle = swapchainImage;
			image.swapchain = true;
			createImage2DView(context, freeImageSlot, VK_FORMAT_B8G8R8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);
		}

		return;
	}

	void createSurface(Context *context, GLFWwindow *window)
	{
		VK_VERIFY_CALL(glfwCreateWindowSurface(context->instance, window, NULL, &context->surface));

		return;
	}

	int createCommandPool(Context *context, int queueFamily, VkCommandPoolCreateFlags createFlags)
	{
		int freeCommandPoolSlot = getFreeSlotForResource(context->commandPools);
		
		CommandPool &commandPool = context->commandPools[freeCommandPoolSlot];

		VkCommandPoolCreateInfo commandPoolCI = {};
		commandPoolCI.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCI.flags = createFlags;
		commandPoolCI.queueFamilyIndex = queueFamily;

		VK_VERIFY_CALL(vkCreateCommandPool(context->logicalDevice, &commandPoolCI, nullptr, &commandPool.handle));

		return freeCommandPoolSlot;
	}

	int allocateCommandBuffer(Context *context, int commandPool, VkCommandBufferLevel level)
	{
		int freeCommandBufferSlot = getFreeSlotForResource(context->commandBuffers);
		
		CommandBuffer &commandBuffer = context->commandBuffers[freeCommandBufferSlot];
		commandBuffer.commandPool = commandPool;

		trackResource(context->commandPools[commandPool].commandBuffers, freeCommandBufferSlot);

		VkCommandBufferAllocateInfo commandBufferAI = {};
		commandBufferAI.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAI.commandPool = context->commandPools[commandPool].handle;
		commandBufferAI.level = level;
		commandBufferAI.commandBufferCount = 1;

		VK_VERIFY_CALL(vkAllocateCommandBuffers(context->logicalDevice, &commandBufferAI, &commandBuffer.handle));

		return freeCommandBufferSlot;
	}

	int createImage2D(Context *context, int width, int height, VkFormat format, VkImageUsageFlags usage, VkImageLayout initialLayout, VkImageTiling tiling)
	{
		int freeImageSlot = getFreeSlotForResource(context->images);
		
		Image &image = context->images[freeImageSlot];

		VkImageCreateInfo imageCI = {};
		imageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		imageCI.flags = 0;
		imageCI.imageType = VK_IMAGE_TYPE_2D;
		imageCI.format = format;
		imageCI.extent.width = width;
		imageCI.extent.height = height;
		imageCI.extent.depth = 1;
		imageCI.mipLevels = 1;
		imageCI.arrayLayers = 1;
		imageCI.samples = VK_SAMPLE_COUNT_1_BIT;
		imageCI.tiling = tiling;
		imageCI.usage = usage;
		imageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		imageCI.queueFamilyIndexCount = 0;
		imageCI.pQueueFamilyIndices = nullptr;
		imageCI.initialLayout = initialLayout;

		VK_VERIFY_CALL(vkCreateImage(context->logicalDevice, &imageCI, nullptr, &image.handle));

		VmaAllocationCreateInfo allocationCI = {};
		allocationCI.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VK_VERIFY_CALL(vmaAllocateMemoryForImage(context->vmaAllocator, image.handle, &allocationCI, &image.allocation, nullptr));

		VK_VERIFY_CALL(vmaBindImageMemory(context->vmaAllocator, image.allocation, image.handle));

		return freeImageSlot;
	}

	int createImage2DView(Context *context, int image, VkFormat format, VkImageAspectFlags aspectFlags)
	{
		int freeImageViewSlot = getFreeSlotForResource(context->imageViews);
		
		ImageView &imageView = context->imageViews[freeImageViewSlot];
		imageView.image = image;

		trackResource(context->images[image].imageViews, freeImageViewSlot);

		VkImageViewCreateInfo imageViewCI = {};
		imageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageViewCI.image = context->images[image].handle;
		imageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageViewCI.format = format;
		imageViewCI.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCI.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCI.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCI.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageViewCI.subresourceRange.aspectMask = aspectFlags;
		imageViewCI.subresourceRange.baseMipLevel = 0;
		imageViewCI.subresourceRange.levelCount = 1;
		imageViewCI.subresourceRange.baseArrayLayer = 0;
		imageViewCI.subresourceRange.layerCount = 1;

		VK_VERIFY_CALL(vkCreateImageView(context->logicalDevice, &imageViewCI, nullptr, &imageView.handle));

		return freeImageViewSlot;
	}

	int createBuffer(Context *context, VkDeviceSize size, VkBufferUsageFlags usage)
	{
		int freeBufferSlot = getFreeSlotForResource(context->buffers);
		
		Buffer &buffer = context->buffers[freeBufferSlot];

		VkBufferCreateInfo bufferCI = {};
		bufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCI.size = size;
		bufferCI.usage = usage;
		bufferCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		bufferCI.queueFamilyIndexCount = 0;
		bufferCI.pQueueFamilyIndices = nullptr;

		VK_VERIFY_CALL(vkCreateBuffer(context->logicalDevice, &bufferCI, nullptr, &buffer.handle));

		VmaAllocationCreateInfo allocationCI = {};
		allocationCI.usage = VMA_MEMORY_USAGE_GPU_ONLY;

		VK_VERIFY_CALL(vmaAllocateMemoryForBuffer(context->vmaAllocator, buffer.handle, &allocationCI, &buffer.allocation, nullptr));

		VK_VERIFY_CALL(vmaBindBufferMemory(context->vmaAllocator, buffer.allocation, buffer.handle));

		return freeBufferSlot;
	}

	int createBufferView(Context *context, int buffer, VkFormat format, VkDeviceSize offset, VkDeviceSize range)
	{
		int freeBufferViewSlot = getFreeSlotForResource(context->bufferViews);
		
		BufferView &bufferView = context->bufferViews[freeBufferViewSlot];
		bufferView.buffer = buffer;

		trackResource(context->buffers[buffer].bufferViews, freeBufferViewSlot);

		VkBufferViewCreateInfo bufferViewCI = {};
		bufferViewCI.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
		bufferViewCI.buffer = context->buffers[buffer].handle;
		bufferViewCI.format = format;
		bufferViewCI.offset = offset;
		bufferViewCI.range = range;

		VK_VERIFY_CALL(vkCreateBufferView(context->logicalDevice, &bufferViewCI, nullptr, &bufferView.handle));

		return freeBufferViewSlot;
	}

	int createFramebuffer(Context *context, int renderPass, int width, int height, const std::vector<int> &attachments)
	{
		int freeFramebufferSlot = getFreeSlotForResource(context->framebuffers);

		Framebuffer &framebuffer = context->framebuffers[freeFramebufferSlot];

		std::vector<VkImageView> imageViews;
		imageViews.resize(attachments.size());
		for (int attachment : attachments)
			imageViews.push_back(context->imageViews[attachment].handle);

		VkFramebufferCreateInfo framebufferCI = {};
		framebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferCI.renderPass = context->renderPasses[renderPass].handle;
		framebufferCI.attachmentCount = (uint32_t)imageViews.size();
		framebufferCI.pAttachments = imageViews.data();
		framebufferCI.width = width;
		framebufferCI.height = height;
		framebufferCI.layers = 1;

		VK_VERIFY_CALL(vkCreateFramebuffer(context->logicalDevice, &framebufferCI, nullptr, &framebuffer.handle));

		return freeFramebufferSlot;
	}

	int createDescriptorSetLayout(Context *context)
	{
		int freeDescriptSetSlot = getFreeSlotForResource(context->descriptorSetLayouts);

		DescriptorSetLayout &descriptorSetLayout = context->descriptorSetLayouts[freeDescriptSetSlot];

		VkDescriptorSetLayoutBinding binding = {};
		binding.binding = 0;
		binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		binding.descriptorCount = 1;
		binding.stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS;
		binding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCI = {};
		descriptorSetLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorSetLayoutCI.flags = 0;
		descriptorSetLayoutCI.bindingCount = 1;
		descriptorSetLayoutCI.pBindings = &binding;

		VK_VERIFY_CALL(vkCreateDescriptorSetLayout(context->logicalDevice, &descriptorSetLayoutCI, nullptr, &descriptorSetLayout.handle));

		return freeDescriptSetSlot;
	}

	int createPipelineLayout(Context *context)
	{
		int freePipelineLayoutSlot = getFreeSlotForResource(context->pipelineLayouts);

		PipelineLayout &pipelineLayout = context->pipelineLayouts[freePipelineLayoutSlot];

		VkPipelineLayoutCreateInfo pipelineLayoutCI = {};
		pipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCI.setLayoutCount = 1;
		pipelineLayoutCI.pSetLayouts = nullptr;
		pipelineLayoutCI.pushConstantRangeCount = 0;
		pipelineLayoutCI.pPushConstantRanges = nullptr;

		VK_VERIFY_CALL(vkCreatePipelineLayout(context->logicalDevice, &pipelineLayoutCI, nullptr, &pipelineLayout.handle));

		return freePipelineLayoutSlot;
	}

	int createRenderPass(Context *context)
	{
		int freeRenderPassSlot = getFreeSlotForResource(context->renderPasses);

		RenderPass &renderPass = context->renderPasses[freeRenderPassSlot];

		VkAttachmentDescription attachmentDesc = {};
		attachmentDesc.format = VK_FORMAT_D24_UNORM_S8_UINT;
		attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
		attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE; // color and depth
		attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE; // stencil
		attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
		attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

		VkAttachmentReference attachmentRef = {};
		attachmentRef.attachment = 0; // index into renderPassCI.pAttachments or VK_ATTACHMENT_UNUSED
		attachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpassDesc = {};
		subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDesc.inputAttachmentCount = 0;
		subpassDesc.pInputAttachments = nullptr;
		subpassDesc.colorAttachmentCount = 0;
		subpassDesc.pColorAttachments = nullptr;
		subpassDesc.pResolveAttachments = nullptr; // colorAttachmentCount
		subpassDesc.pDepthStencilAttachment = &attachmentRef;
		subpassDesc.preserveAttachmentCount = 0;
		subpassDesc.pPreserveAttachments = nullptr;

		VkSubpassDependency subpassDependency = {};
		subpassDependency.srcSubpass = 0; // subpass index or VK_SUBPASS_EXTERNAL
		subpassDependency.dstSubpass = 0;
		subpassDependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
		subpassDependency.dstStageMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		subpassDependency.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
		subpassDependency.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
		subpassDependency.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		VkRenderPassCreateInfo renderPassCI = {};
		renderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCI.attachmentCount = 1;
		renderPassCI.pAttachments = &attachmentDesc;
		renderPassCI.subpassCount = 1;
		renderPassCI.pSubpasses = &subpassDesc;
		renderPassCI.dependencyCount = 1;
		renderPassCI.pDependencies = &subpassDependency;

		VK_VERIFY_CALL(vkCreateRenderPass(context->logicalDevice, &renderPassCI, nullptr, &renderPass.handle));

		return freeRenderPassSlot;
	}

	int createGraphicsPipeline(Context *context)
	{
		int freePipelineSlot = getFreeSlotForResource(context->pipelines);

		Pipeline &pipeline = context->pipelines[freePipelineSlot];

		VkPipelineShaderStageCreateInfo shaderStageCI = {};
		shaderStageCI.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		shaderStageCI.stage = VK_SHADER_STAGE_VERTEX_BIT;
		shaderStageCI.module = VK_NULL_HANDLE;
		shaderStageCI.pName = "main";
		shaderStageCI.pSpecializationInfo = nullptr;

		VkVertexInputBindingDescription inputBindingDesc = {};
		inputBindingDesc.binding = 0;
		inputBindingDesc.stride = 0;
		inputBindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		VkVertexInputAttributeDescription inputAttributeDesc = {};
		inputAttributeDesc.location = 0;
		inputAttributeDesc.binding = 0;
		inputAttributeDesc.format = VK_FORMAT_R32G32B32A32_SFLOAT;
		inputAttributeDesc.offset = 0;

		VkPipelineVertexInputStateCreateInfo vertexInputStateCI = {};
		vertexInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputStateCI.vertexBindingDescriptionCount = 1;
		vertexInputStateCI.pVertexBindingDescriptions = &inputBindingDesc;
		vertexInputStateCI.vertexAttributeDescriptionCount = 1;
		vertexInputStateCI.pVertexAttributeDescriptions = &inputAttributeDesc;

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCI = {};
		inputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCI.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssemblyStateCI.primitiveRestartEnable = VK_FALSE;

		VkPipelineTessellationStateCreateInfo tesselationStateCI = {};
		tesselationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		tesselationStateCI.patchControlPoints = 0;

		VkViewport viewport = {};
		viewport.x = 0;
		viewport.y = 0;
		viewport.width = 640;
		viewport.height = 480;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		VkRect2D scissor = {};
		scissor.offset.x = 0;
		scissor.offset.y = 0;
		scissor.extent.width = 640;
		scissor.extent.height = 480;

		VkPipelineViewportStateCreateInfo viewportStateCI = {};
		viewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportStateCI.viewportCount = 1;
		viewportStateCI.pViewports = &viewport;
		viewportStateCI.scissorCount = 1;
		viewportStateCI.pScissors = &scissor;

		VkPipelineRasterizationStateCreateInfo rasterizationStateCI = {};
		rasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateCI.depthClampEnable = VK_FALSE;
		rasterizationStateCI.rasterizerDiscardEnable = VK_FALSE;
		rasterizationStateCI.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizationStateCI.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizationStateCI.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizationStateCI.depthBiasEnable = VK_FALSE;
		rasterizationStateCI.depthBiasConstantFactor = 0.0f;
		rasterizationStateCI.depthBiasClamp = 0.0f;
		rasterizationStateCI.depthBiasSlopeFactor = 0.0f;
		rasterizationStateCI.lineWidth = 1.0f;

		VkPipelineMultisampleStateCreateInfo multisampleStateCI = {};
		multisampleStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleStateCI.sampleShadingEnable = VK_FALSE;
		multisampleStateCI.minSampleShading = 0.0f;
		multisampleStateCI.pSampleMask = nullptr;
		multisampleStateCI.alphaToCoverageEnable = VK_FALSE;
		multisampleStateCI.alphaToOneEnable = VK_FALSE;

		VkStencilOpState stencilOpState = {};
		stencilOpState.failOp = VK_STENCIL_OP_KEEP;
		stencilOpState.passOp = VK_STENCIL_OP_KEEP;
		stencilOpState.depthFailOp = VK_STENCIL_OP_KEEP;
		stencilOpState.compareOp = VK_COMPARE_OP_NEVER;
		stencilOpState.compareMask = 0xFFFFFFFF;
		stencilOpState.writeMask = 0xFFFFFFFF;
		stencilOpState.reference = 0xFFFFFFFF;

		VkPipelineDepthStencilStateCreateInfo depthStencilStateCI = {};
		depthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencilStateCI.depthTestEnable = VK_TRUE;
		depthStencilStateCI.depthWriteEnable = VK_TRUE;
		depthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencilStateCI.depthBoundsTestEnable = VK_TRUE;
		depthStencilStateCI.stencilTestEnable = VK_TRUE;
		depthStencilStateCI.front = stencilOpState;
		depthStencilStateCI.back = stencilOpState;
		depthStencilStateCI.minDepthBounds = 0.0f;
		depthStencilStateCI.maxDepthBounds = 1.0f;

		VkPipelineColorBlendAttachmentState colorBlendAttachmentState = {};
		colorBlendAttachmentState.blendEnable = VK_FALSE;
		colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD ;
		colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD ;
		colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT ;

		VkPipelineColorBlendStateCreateInfo colorBlendstateCI = {};
		colorBlendstateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendstateCI.logicOpEnable = VK_FALSE;
		colorBlendstateCI.logicOp = VK_LOGIC_OP_CLEAR;
		colorBlendstateCI.attachmentCount = 1; // must be equal to colorAttachmentCount of subpass
		colorBlendstateCI.pAttachments = &colorBlendAttachmentState;
		colorBlendstateCI.blendConstants[0] = 0.0f;
		colorBlendstateCI.blendConstants[1] = 0.0f;
		colorBlendstateCI.blendConstants[2] = 0.0f;
		colorBlendstateCI.blendConstants[3] = 0.0f;

		VkDynamicState dynamicState = VK_DYNAMIC_STATE_VIEWPORT;

		VkPipelineDynamicStateCreateInfo dynamicStateCI = {};
		dynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCI.dynamicStateCount = 1;
		dynamicStateCI.pDynamicStates = &dynamicState;

		VkPipelineCreateFlags pipelineCreateFlags = 0;
		
		#ifdef _DEBUG
		pipelineCreateFlags |= VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT;
		#endif

		VkGraphicsPipelineCreateInfo graphicsPipelineCI = {};
		graphicsPipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		graphicsPipelineCI.flags = pipelineCreateFlags;
		graphicsPipelineCI.stageCount = 1;
		graphicsPipelineCI.pStages = &shaderStageCI;
		graphicsPipelineCI.pVertexInputState = &vertexInputStateCI;
		graphicsPipelineCI.pInputAssemblyState = &inputAssemblyStateCI;
		graphicsPipelineCI.pTessellationState = &tesselationStateCI;
		graphicsPipelineCI.pViewportState = &viewportStateCI;
		graphicsPipelineCI.pRasterizationState = &rasterizationStateCI;
		graphicsPipelineCI.pMultisampleState = &multisampleStateCI;
		graphicsPipelineCI.pDepthStencilState = &depthStencilStateCI;
		graphicsPipelineCI.pColorBlendState = &colorBlendstateCI;
		graphicsPipelineCI.pDynamicState = &dynamicStateCI;
		//graphicsPipelineCI.layout = ;
		//graphicsPipelineCI.renderPass = ;
		graphicsPipelineCI.subpass = 0;
		graphicsPipelineCI.basePipelineHandle = VK_NULL_HANDLE;
		graphicsPipelineCI.basePipelineIndex = -1;

		VK_VERIFY_CALL(vkCreateGraphicsPipelines(context->logicalDevice, VK_NULL_HANDLE, 1, &graphicsPipelineCI, nullptr, &pipeline.handle));

		return freePipelineSlot;
	}
}

void initializeRenderer(GLFWwindow *window)
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);

	int swapchainImageCount = 2;

	auto context = vk::createContext("Vulkan");
	vk::createSurface(context.get(), window);
	vk::createDevice(context.get());
	vk::createSwapchain(context.get(), w, h, swapchainImageCount);
	int commandPool = vk::createCommandPool(context.get(), context->graphicsQueue.familyIndex, 0);
	int commandBuffer = vk::allocateCommandBuffer(context.get(), commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY);
	int depthStencilImage = vk::createImage2D(context.get(), w, h, VK_FORMAT_D24_UNORM_S8_UINT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_TILING_OPTIMAL);
	int depthStencilView = vk::createImage2DView(context.get(), depthStencilImage, VK_FORMAT_D24_UNORM_S8_UINT, VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT);
	int buffer = vk::createBuffer(context.get(), 1024, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
	int bufferView = vk::createBufferView(context.get(), buffer, VK_FORMAT_R32G32B32A32_SFLOAT, 0, VK_WHOLE_SIZE);

	vk::compileGlslFileToSpirvBinary("D:/Projects/cpp/vulkan/flat.fs");

	return;
}

int main(int argc, char *argv[])
{
	if (!glfwInit())
		return EXIT_FAILURE;

	if (!glfwVulkanSupported())
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow *window = glfwCreateWindow(640, 480, "Vulkan", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	initializeRenderer(window);

	return 0;
}
