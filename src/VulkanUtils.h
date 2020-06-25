#pragma once

#ifndef VULKAN_UTILS_H
#define VULKAN_UTILS_H

#include <vulkan/vulkan.h>
#include <vector>
#include <list>

#ifdef _DEBUG
	#define VK_VERIFY_RESULT(call) VulkanVerifyResult((call), #call, __FILE__, __LINE__)
	inline void VulkanVerifyResult(VkResult result, const char *call, const char *file, int line)
	{
		if (result != VK_SUCCESS)
		{
			fprintf(stderr, "Vulkan call '%s' in file '%s' on line %d failed with result code %d.\n", call, file, line, result);
			abort();
		}

		return;
	}
#else
	#define VK_VERIFY_RESULT(call) call
#endif

#define X_MOVE_CTOR_ASSIGN(x, name) \
	name(name &&) = x; \
	name & operator=(name &&) = x;

#define X_COPY_CTOR_ASSIGN(x, name) \
	name(const name &) = x; \
	name & operator=(const name &) = x;

#define DEFAULT_COPY_CTOR_ASSIGN(name) X_COPY_CTOR_ASSIGN(default, name)
#define DEFAULT_MOVE_CTOR_ASSIGN(name) X_MOVE_CTOR_ASSIGN(default, name)
#define DELETE_COPY_CTOR_ASSIGN(name) X_COPY_CTOR_ASSIGN(delete, name)
#define DELETE_MOVE_CTOR_ASSIGN(name) X_MOVE_CTOR_ASSIGN(delete, name)

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
	macro(vkGetPhysicalDeviceMemoryProperties) \
	macro(vkGetPhysicalDeviceSparseImageFormatProperties)

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
	macro(vkGetImageSparseMemoryRequirements) \
	macro(vkGetImageSparseMemoryRequirements2) \
	macro(vkQueueBindSparse)

#define VK_DECLARE_FUNCTION(name) \
	extern PFN_##name name;

VK_GENERAL_FUNCTIONS(VK_DECLARE_FUNCTION)
VK_INSTANCE_FUNCTIONS(VK_DECLARE_FUNCTION)
VK_DEVICE_FUNCTIONS(VK_DECLARE_FUNCTION)

class VulkanShaderModule;

///////////////////////////////////////////////////////////////////////////////////////

class VulkanBuffer
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanBuffer)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanBuffer)
	
	VulkanBuffer();
	~VulkanBuffer();

	VkBuffer mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanBufferView
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanBufferView)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanBufferView)
	
	VulkanBufferView();
	~VulkanBufferView();

	VkBufferView mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanCommandBuffer
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanCommandBuffer)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanCommandBuffer)
	
	VulkanCommandBuffer();
	~VulkanCommandBuffer();

	VkCommandBuffer mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDescriptorPool
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDescriptorPool)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanDescriptorPool)
	
	VulkanDescriptorPool();
	~VulkanDescriptorPool();

	VkDescriptorPool mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDescriptorSet
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDescriptorSet)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanDescriptorSet)
	
	VulkanDescriptorSet();
	~VulkanDescriptorSet();

	VkDescriptorSet mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDescriptorSetLayout
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDescriptorSetLayout)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanDescriptorSetLayout)
	
	VulkanDescriptorSetLayout();
	~VulkanDescriptorSetLayout();

	VkDescriptorSetLayout mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDevice
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDevice)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanDevice)
	
	VulkanDevice();
	~VulkanDevice();

	VkDevice mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanEvent
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanEvent)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanEvent)
	
	VulkanEvent();
	~VulkanEvent();

	VkEvent mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanFence
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanFence)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanFence)
	
	VulkanFence();
	~VulkanFence();

	VkFence mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanFramebuffer
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanFramebuffer)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanFramebuffer)
	
	VulkanFramebuffer();
	~VulkanFramebuffer();

	VkFramebuffer mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanImage
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanImage)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanImage)
	
	VulkanImage();
	~VulkanImage();

	VkImage mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanImageView
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanImageView)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanImageView)
	
	VulkanImageView();
	~VulkanImageView();

	VkImageView mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanRenderPass
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanRenderPass)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanRenderPass)
	
	VulkanRenderPass();
	~VulkanRenderPass();

	VkRenderPass mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSurface
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSurface)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanSurface)
	
	VulkanSurface();
	~VulkanSurface();

	VkSurfaceKHR mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanPhysicalDevice
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanPhysicalDevice)
	
	VulkanPhysicalDevice();
	~VulkanPhysicalDevice();

	VulkanPhysicalDevice(VulkanPhysicalDevice &&other);
	VulkanPhysicalDevice & operator=(VulkanPhysicalDevice &&other);

	std::vector<VkExtensionProperties> getExtensions();
	std::vector<VkLayerProperties> getLayers();
	std::vector<VkQueueFamilyProperties> getQueueFamilies();

	std::vector<VkSurfaceFormatKHR> getSupportedSurfaceFormats(const VulkanSurface &surface);
	std::vector<VkPresentModeKHR> getSupportedPresentModes(const VulkanSurface &surface);

	VkPhysicalDevice mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanInstance
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanInstance)
	
	VulkanInstance();
	~VulkanInstance();

	VulkanInstance(VulkanInstance &&other);
	VulkanInstance & operator=(VulkanInstance &&other);

	static std::vector<VkExtensionProperties> getExtensions(void);
	static std::vector<VkLayerProperties> getLayers(void);
	std::vector<VulkanPhysicalDevice> getPhysicalDevices();

	VkInstance mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanPipeline
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanPipeline)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanPipeline)
	
	VulkanPipeline();
	~VulkanPipeline();

	VkPipeline mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanPipelineLayout
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanPipelineLayout)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanPipelineLayout)
	
	VulkanPipelineLayout();
	~VulkanPipelineLayout();

	VkPipelineLayout mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanQueue
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanQueue)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanQueue)
	
	VulkanQueue();
	~VulkanQueue();

	VkQueue mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSampler
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSampler)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanSampler)
	
	VulkanSampler();
	~VulkanSampler();

	VkSampler mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSemaphore
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSemaphore)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanSemaphore)
	
	VulkanSemaphore();
	~VulkanSemaphore();

	VkSemaphore mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSwapchain
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSwapchain)
	DEFAULT_MOVE_CTOR_ASSIGN(VulkanSwapchain)
	
	VulkanSwapchain();
	~VulkanSwapchain();

	VkSwapchainKHR mHandle;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanInstanceCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanInstanceCreator)
	
	VulkanInstanceCreator();

	VulkanInstanceCreator & setApplication(const char *name, uint32_t version);
	VulkanInstanceCreator & setEngine(const char *name, uint32_t version);
	VulkanInstanceCreator & setApiVersion(uint32_t version);

	VulkanInstanceCreator & addEnabledLayer(const char *name);
	VulkanInstanceCreator & addEnabledExtension(const char *name);

	VulkanInstance create();

private:

	VkApplicationInfo mApplicationInfo;
	VkInstanceCreateInfo mInstanceCI;

	std::vector<const char *> mEnabledLayers;
	std::vector<const char *> mEnabledExtensions;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDeviceCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDeviceCreator)

	VulkanDeviceCreator();

	VulkanDeviceCreator & addQueueFamily(uint32_t familyIndex);
	VulkanDeviceCreator & addQueueFamilyQueue(float priority);

	VulkanDeviceCreator & addEnabledLayer(const char *name);
	VulkanDeviceCreator & addEnabledExtension(const char *name);

	VulkanDevice create(const VulkanPhysicalDevice &physicalDevice);

private:

	std::list<std::vector<float>> mPriorities;
	std::vector<VkDeviceQueueCreateInfo> mDeviceQueueCIs;
	std::vector<const char *> mEnabledLayers;
	std::vector<const char *> mEnabledExtensions;
	VkDeviceCreateInfo mDeviceCI;
	VkPhysicalDeviceFeatures mEnabledFeatures;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanBarrier
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanBarrier);

	VulkanBarrier();

	VulkanBarrier & setSrcStageMask(VkPipelineStageFlags stageMask);
	VulkanBarrier & setDstStageMask(VkPipelineStageFlags stageMask);
	
	VulkanBarrier & setDependencyFlags(VkDependencyFlags dependencyFlags);
	VulkanBarrier & addEvent(const VulkanEvent &event);

	VulkanBarrier & addMemoryBarrier(VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask);
	VulkanBarrier & addBufferMemoryBarrier(const VulkanBuffer &buffer, VkDeviceSize size, VkDeviceSize offset, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex);
	VulkanBarrier & addImageMemoryBarrier(const VulkanImage &image, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex);

	void executePipelineBarrierCommand(VulkanCommandBuffer &commandBuffer);
	void executeWaitEventsCommand(VulkanCommandBuffer &commandBuffer);

private:

	VkPipelineStageFlags mSrcStageMask;
	VkPipelineStageFlags mDstStageMask;
	VkDependencyFlags mDependencyFlags;
	std::vector<VkMemoryBarrier> mMemoryBarriers;
	std::vector<VkBufferMemoryBarrier> mBufferMemoryBarriers;
	std::vector<VkImageMemoryBarrier> mImageMemoryBarriers;
	std::vector<VkEvent> mEvents;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanRenderPassCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanRenderPassCreator)

	VulkanRenderPassCreator();

	VulkanRenderPassCreator & addAttachment(VkFormat format, VkSampleCountFlagBits samples, VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp, VkImageLayout initialLayout, VkImageLayout finalLayout);
	
	VulkanRenderPassCreator & addSubpass();
	VulkanRenderPassCreator & addSubpassInputAttachment(uint32_t attachment, VkImageLayout layout);
	VulkanRenderPassCreator & addSubpassColorAttachment(uint32_t attachment, VkImageLayout layout);
	VulkanRenderPassCreator & addSubpassColorResolveAttachment(uint32_t colorAttachment, VkImageLayout colorLayout, uint32_t resolveAttachment = VK_ATTACHMENT_UNUSED, VkImageLayout resolveLayout = VK_IMAGE_LAYOUT_UNDEFINED);
	VulkanRenderPassCreator & addSubpassPreserveAttachment(uint32_t attachment);

	VulkanRenderPassCreator & setSubpassDepthStencilAttachment(uint32_t attachment, VkImageLayout layout);

	VulkanRenderPassCreator & addDependency(uint32_t srcSubpass, uint32_t dstSubpass, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags);

	VulkanRenderPass create(const VulkanDevice &device); 

private:

	struct SubpassRefs
	{
		std::vector<VkAttachmentReference> inputRefs;
		std::vector<VkAttachmentReference> colorRefs;
		std::vector<VkAttachmentReference> resolveRefs;
		VkAttachmentReference depthStencilRef;
		std::vector<uint32_t> preserveRefs;
	};

	VkRenderPassCreateInfo mRenderPassCI;
	std::vector<VkAttachmentDescription> mAttachements;
	std::vector<VkSubpassDescription> mSubpasses;
	std::list<SubpassRefs> mSubpassesRefs;
	std::vector<VkSubpassDependency> mDependencies;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanGraphicsPipelineCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanGraphicsPipelineCreator)

	VulkanGraphicsPipelineCreator();

	VulkanGraphicsPipelineCreator & addShader(const VulkanShaderModule &shaderModule);
	VulkanGraphicsPipelineCreator & setSpecialization(size_t dataSize, const void *pData);
	VulkanGraphicsPipelineCreator & addSpecializationMapEntry(uint32_t constantID, uint32_t offset, size_t size);

	VulkanGraphicsPipelineCreator & addVertexInputBinding(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate);
	VulkanGraphicsPipelineCreator & addVertexInputAttribute(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset);

	VulkanGraphicsPipelineCreator & setPrimitiveTopology(VkPrimitiveTopology primitiveTopology);
	VulkanGraphicsPipelineCreator & setPrimitiveRestartEnable(VkBool32 primitiveRestartEnable);

	VulkanGraphicsPipelineCreator & setPatchControlPoints(uint32_t patchControlPoints);

	VulkanGraphicsPipelineCreator & addViewport(float x, float y, float width, float height, float minDepth, float maxDepth);
	VulkanGraphicsPipelineCreator & addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height);

	VulkanGraphicsPipelineCreator & setDepthClampEnable(VkBool32 depthClampEnable);
	VulkanGraphicsPipelineCreator & setRasterizerDiscardEnable(VkBool32 rasterizerDiscardEnable);
	VulkanGraphicsPipelineCreator & setPolygonMode(VkPolygonMode polygonMode);
	VulkanGraphicsPipelineCreator & setCullMode(VkCullModeFlags cullMode);
	VulkanGraphicsPipelineCreator & setFrontFace(VkFrontFace frontFace);
	VulkanGraphicsPipelineCreator & setDepthBiasEnable(VkBool32 depthBiasEnable);
	VulkanGraphicsPipelineCreator & setDepthBias(float constantFactor, float clamp, float slopeFactor);
	VulkanGraphicsPipelineCreator & setLineWidth(float lineWidth);

	VulkanGraphicsPipelineCreator & setDepthTestEnable(VkBool32 depthTestEnable);
	VulkanGraphicsPipelineCreator & setDepthWriteEnable(VkBool32 depthWriteEnable);
	VulkanGraphicsPipelineCreator & setDepthCompareOp(VkCompareOp depthCompareOp);
	VulkanGraphicsPipelineCreator & setDepthBoundsTestEnable(VkBool32 depthBoundsTestEnable);
	VulkanGraphicsPipelineCreator & setStencilTestEnable(VkBool32 stencilTestEnable);
	VulkanGraphicsPipelineCreator & setStencilFrontOps(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp);
	VulkanGraphicsPipelineCreator & setStencilFrontCompare(VkCompareOp compareOp, uint32_t reference, uint32_t compareMask);
	VulkanGraphicsPipelineCreator & setStencilFrontMask(uint32_t writeMask);
	VulkanGraphicsPipelineCreator & setStencilBackOps(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp);
	VulkanGraphicsPipelineCreator & setStencilBackCompare(VkCompareOp compareOp, uint32_t reference, uint32_t compareMask);
	VulkanGraphicsPipelineCreator & setStencilBackMask(uint32_t writeMask);

	VulkanGraphicsPipelineCreator & setLogicOpEnable(VkBool32 logicOpEnable);
	VulkanGraphicsPipelineCreator & setLogicOp(VkLogicOp logicOp);
	VulkanGraphicsPipelineCreator & setBlendConstants(float red, float green, float blue, float alpha);
	VulkanGraphicsPipelineCreator & addColorBlendAttachmentState();
	VulkanGraphicsPipelineCreator & setBlendEnable(VkBool32 blendEnable);
	VulkanGraphicsPipelineCreator & setBlendOps(VkBlendOp colorBlendOp, VkBlendOp alphaBlendOp);
	VulkanGraphicsPipelineCreator & setBlendFactors(VkBlendFactor srcColorBlendFactor, VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendFactor dstAlphaBlendFactor);
	VulkanGraphicsPipelineCreator & setColorWriteMask(VkColorComponentFlags colorWriteMask);

	VulkanGraphicsPipelineCreator & addDynamicState(VkDynamicState dynamicState);

	VulkanGraphicsPipelineCreator & setPipelineLayout(const VulkanPipelineLayout &pipelineLayout);
	VulkanGraphicsPipelineCreator & setRenderPass(const VulkanRenderPass &renderPass, uint32_t subpass);

	VulkanPipeline create(const VulkanDevice &device);

private:

	struct Specialization
	{
		VkSpecializationInfo mInfo;
		std::vector<VkSpecializationMapEntry> mMapEntries;
	};

	VkGraphicsPipelineCreateInfo mGraphicsPipelineCI;
	std::vector<VkPipelineShaderStageCreateInfo> mShaderStages;
	std::list<Specialization> mSpecializations;
	VkPipelineVertexInputStateCreateInfo mVertexInputStateCI;
	std::vector<VkVertexInputBindingDescription> mVertexInputBindings;
	std::vector<VkVertexInputAttributeDescription> mVertexInputAttributes;
	VkPipelineInputAssemblyStateCreateInfo mInputAssemblyStateCI;
	VkPipelineTessellationStateCreateInfo mTessellationStateCI;
	VkPipelineViewportStateCreateInfo mViewportStateCI;
	std::vector<VkViewport> mViewports;
	std::vector<VkRect2D> mScissors;
	VkPipelineRasterizationStateCreateInfo mRasterizationStateCI;
	VkPipelineMultisampleStateCreateInfo mMultisampleCI;
	VkPipelineDepthStencilStateCreateInfo mDepthStencilStateCI;
	VkPipelineColorBlendStateCreateInfo mColorBlendStateCI;
	std::vector<VkPipelineColorBlendAttachmentState> mColorBlendAttachmentStates;
	VkPipelineDynamicStateCreateInfo mDynamicStateCI;
	std::vector<VkDynamicState> mDynamicStates;

};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanBufferCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanBufferCreator)

	VulkanBufferCreator();

	VulkanBufferCreator & setFlags(VkBufferCreateFlags flags);
	VulkanBufferCreator & setSize(VkDeviceSize size);
	VulkanBufferCreator & setUsage(VkBufferUsageFlags usage);
	VulkanBufferCreator & setSharingMode(VkSharingMode sharingMode);
	VulkanBufferCreator & addQueueFamily(uint32_t queueFamily);

	VulkanBuffer create(const VulkanDevice &device);

private:

	VkBufferCreateInfo mBufferCI;
	std::vector<uint32_t> mQueueFamily;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanBufferViewCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanBufferViewCreator)

	VulkanBufferViewCreator();

	VulkanBufferViewCreator & setBuffer(const VulkanBuffer &buffer);
	VulkanBufferViewCreator & setFormat(VkFormat format);
	VulkanBufferViewCreator & setOffset(VkDeviceSize offset);
	VulkanBufferViewCreator & setRange(VkDeviceSize range);

	VulkanBufferView create(const VulkanDevice &device);

private:

	VkBufferViewCreateInfo mBufferViewCI;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanImageCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanImageCreator)

	VulkanImageCreator();

	VulkanImageCreator & setFlags(VkImageCreateFlags flags);
	VulkanImageCreator & setType(VkImageType type);
	VulkanImageCreator & setFormat(VkFormat format);
	VulkanImageCreator & setExtent(uint32_t width, uint32_t height, uint32_t depth);
	VulkanImageCreator & setMipLevels(uint32_t mipLevels);
	VulkanImageCreator & setArrayLayers(uint32_t arrayLayers);
	VulkanImageCreator & setSamples(VkSampleCountFlagBits samples);
	VulkanImageCreator & setTiling(VkImageTiling tiling);
	VulkanImageCreator & setUsage(VkImageUsageFlags usage);
	VulkanImageCreator & setSharingMode(VkSharingMode sharingMode);
	VulkanImageCreator & setInitialLayout(VkImageLayout initialLayout);

	VulkanImageCreator & addQueueFamily(uint32_t queueFamily);

	VulkanImage create(const VulkanDevice &device);

private:

	VkImageCreateInfo mImageCI;
	std::vector<uint32_t> mQueueFamily;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanImageViewCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanImageViewCreator)

	VulkanImageViewCreator();

	VulkanImageViewCreator & setImage(const VulkanImage &image);
	VulkanImageViewCreator & setType(VkImageViewType type);
	VulkanImageViewCreator & setFormat(VkFormat format);
	VulkanImageViewCreator & setComponentMapping(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a);
	VulkanImageViewCreator & setAspectMask(VkImageAspectFlags aspectMask);
	VulkanImageViewCreator & setMip(uint32_t baseMipLevel, uint32_t levelCount = VK_REMAINING_MIP_LEVELS );
	VulkanImageViewCreator & setArrayLayer(uint32_t baseArrayLayer, uint32_t layerCount = VK_REMAINING_ARRAY_LAYERS);

	VulkanImageView create(const VulkanDevice &device);

private:

	VkImageViewCreateInfo mImageViewCI;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanQueueSubmit
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanQueueSubmit)

	VulkanQueueSubmit();

	VulkanQueueSubmit & addSubmit();
	VulkanQueueSubmit & addWaitSemaphore(const VulkanSemaphore &waitSemaphore, VkPipelineStageFlags waitDstStageMask);
	VulkanQueueSubmit & addCommandBuffer(const VulkanCommandBuffer &commandBuffer);
	VulkanQueueSubmit & addSignalSemaphore(const VulkanSemaphore &signalSemaphore);

	void submit(const VulkanQueue &queue, const VulkanFence &fence);

private:

	struct SubmitInfo
	{
		std::vector<VkSemaphore> waitSemaphores;
		std::vector<VkPipelineStageFlags> waitDstStageMasks;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector<VkSemaphore> signalSemaphores;
	};

	std::vector<VkSubmitInfo> mSubmitInfos;
	std::list<SubmitInfo> mSubmitInfoData;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanFramebufferCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanFramebufferCreator)

	VulkanFramebufferCreator();

	VulkanFramebufferCreator & setRenderPass(const VulkanRenderPass &renderPass);
	VulkanFramebufferCreator & addAttachment(const VulkanImageView &attachment);
	VulkanFramebufferCreator & setExtent(uint32_t width, uint32_t height, uint32_t layers = 1);

	VulkanFramebuffer create(const VulkanDevice &device);

private:

	VkFramebufferCreateInfo mFramebufferCI;
	std::vector<VkImageView> mAttachments;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSamplerCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSamplerCreator)

	VulkanSamplerCreator();

	VulkanSamplerCreator & setFilter(VkFilter minFilter, VkFilter magFilter);
	VulkanSamplerCreator & setMipmapMode(VkSamplerMipmapMode mipmapMode);
	VulkanSamplerCreator & setAddressMode(VkSamplerAddressMode u, VkSamplerAddressMode v, VkSamplerAddressMode w);
	VulkanSamplerCreator & setLod(float minLod, float maxLod);
	VulkanSamplerCreator & setMipLodBias(float mipLoadBias);
	VulkanSamplerCreator & setAnisotropyEnable(VkBool32 anisotropyEnable);
	VulkanSamplerCreator & setMaxAnisotropy(float maxAnisotropy);
	VulkanSamplerCreator & setCompareEnable(VkBool32 compareEnable);
	VulkanSamplerCreator & setCompareOp(VkCompareOp compareOp);
	VulkanSamplerCreator & setBorderColor(VkBorderColor borderColor);
	VulkanSamplerCreator & setUnnormalizedCoordinates(VkBool32 unnormalizedCoordinates);

	VulkanSampler create(const VulkanDevice &device);

private:

	VkSamplerCreateInfo mSamplerCI;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDescriptorSetLayoutCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDescriptorSetLayoutCreator)

	VulkanDescriptorSetLayoutCreator();

	VulkanDescriptorSetLayoutCreator & setFlags(VkDescriptorSetLayoutCreateFlags flags);
	VulkanDescriptorSetLayoutCreator & addBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags shaderStages);
	VulkanDescriptorSetLayoutCreator & addImmutableSamplerBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags shaderStages);
	VulkanDescriptorSetLayoutCreator & addImmutableSampler(const VulkanSampler &sampler);

	VulkanDescriptorSetLayout create(const VulkanDevice &device);

private:

	VkDescriptorSetLayoutCreateInfo mDescriptorSetLayoutCI;
	std::vector<VkDescriptorSetLayoutBinding> mBindings;
	std::list<std::vector<VkSampler>> mImmutableSamplers;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanPipelineLayoutCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanPipelineLayoutCreator)

	VulkanPipelineLayoutCreator();

	VulkanPipelineLayoutCreator & addSetLayout(VkDescriptorSetLayout setLayout);
	VulkanPipelineLayoutCreator & addPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size);

	VulkanPipelineLayout create(const VulkanDevice &device);

private:

	VkPipelineLayoutCreateInfo mPipelineLayoutCI;
	std::vector<VkDescriptorSetLayout> mSetLayouts;
	std::vector<VkPushConstantRange> mPushConstantRanges;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanDescriptorPoolCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanDescriptorPoolCreator)

	VulkanDescriptorPoolCreator();

	VulkanDescriptorPoolCreator & setFlags(VkDescriptorPoolCreateFlags flags);
	VulkanDescriptorPoolCreator & setMaxSets(uint32_t maxSets);
	VulkanDescriptorPoolCreator & addPoolSize(VkDescriptorType type, uint32_t descriptorCount);

	VulkanDescriptorPool create(const VulkanDevice &device);

private:

	VkDescriptorPoolCreateInfo mDescriptorPoolCI;
	std::vector<VkDescriptorPoolSize> mPoolSizes;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanSwapchainCreator
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanSwapchainCreator)

	VulkanSwapchainCreator();

	VulkanSwapchainCreator & setFlags(VkSwapchainCreateFlagsKHR flags);
	VulkanSwapchainCreator & setSurface(const VulkanSurface &surface);
	VulkanSwapchainCreator & setMinImageCount(uint32_t minImageCount);
	VulkanSwapchainCreator & setFormat(VkFormat format, VkColorSpaceKHR colorSpace);
	VulkanSwapchainCreator & setExtent(uint32_t width, uint32_t height, uint32_t layers = 1);
	VulkanSwapchainCreator & setUsage(VkImageUsageFlags usage);
	VulkanSwapchainCreator & setSharingMode(VkSharingMode sharingMode);
	VulkanSwapchainCreator & setPreTransform(VkSurfaceTransformFlagBitsKHR preTransform);
	VulkanSwapchainCreator & setCompositeAlpha(VkCompositeAlphaFlagBitsKHR compositeAlpha);
	VulkanSwapchainCreator & setPresentMode(VkPresentModeKHR presentMode);
	VulkanSwapchainCreator & setClipped(VkBool32 clipped);
	VulkanSwapchainCreator & setOldSwapchain(const VulkanSwapchain &oldSwapchain);

	VulkanSwapchainCreator & addQueueFamily(uint32_t queueFamily);

	VulkanSwapchain create(const VulkanDevice &device);

private:

	VkSwapchainCreateInfoKHR mSwapchainCI;
	std::vector<uint32_t> mQueueFamilies;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanUpdateDescriptorSets
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanUpdateDescriptorSets)

	VulkanUpdateDescriptorSets();

	VulkanUpdateDescriptorSets & addDescriptorSetWrite(const VulkanDescriptorSet &set, uint32_t binding, uint32_t arrayOffset, VkDescriptorType type);
	VulkanUpdateDescriptorSets & writeImageDescriptor(const VulkanSampler &sampler, const VulkanImageView &imageView, VkImageLayout imageLayout);
	VulkanUpdateDescriptorSets & writeBufferDescriptor(const VulkanBuffer &buffer, VkDeviceSize offset, VkDeviceSize range);
	VulkanUpdateDescriptorSets & writeTexelBufferViewDescriptor(const VulkanBufferView &texelBufferView);

	VulkanUpdateDescriptorSets & addDescriptorSetCopy(const VulkanDescriptorSet &srcSet, uint32_t srcBinding, uint32_t srcArrayOffset, const VulkanDescriptorSet &dstSet, uint32_t dstBinding, uint32_t dstArrayOffset, uint32_t descriptorCount);

	void execute(const VulkanDevice &device);

private:

	std::vector<VkWriteDescriptorSet> mWriteDescriptorSets;
	std::list<std::vector<VkDescriptorImageInfo>> mDescriptorImageInfoCollection;
	std::list<std::vector<VkDescriptorBufferInfo>> mDescriptorBufferInfoCollection;
	std::list<std::vector<VkBufferView>> mTexelBufferViewCollection;
	std::vector<VkCopyDescriptorSet> mCopyDescriptorSets;
};

///////////////////////////////////////////////////////////////////////////////////////

class VulkanRenderPassBeginInfo
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanRenderPassBeginInfo)

	VulkanRenderPassBeginInfo();

	VulkanRenderPassBeginInfo & setRenderPass(const VulkanRenderPass &renderPass);
	VulkanRenderPassBeginInfo & setFramebuffer(const VulkanFramebuffer &framebuffer);
	VulkanRenderPassBeginInfo & setRenderArea(int32_t x, int32_t y, uint32_t width, uint32_t height);
	VulkanRenderPassBeginInfo & addClearColorF(float r, float g, float b, float a);
	VulkanRenderPassBeginInfo & addClearColorI(int32_t r, int32_t g, int32_t b, int32_t a);
	VulkanRenderPassBeginInfo & addClearColorU(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
	VulkanRenderPassBeginInfo & addClearDepthStencil(float depth, uint32_t stencil);

	void execute(VulkanCommandBuffer &commandBuffer, VkSubpassContents contents);

private:

	VkRenderPassBeginInfo mRenderPassBeginInfo;
	std::vector<VkClearValue> mClearValues;
};

#endif