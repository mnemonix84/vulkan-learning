
#include "VulkanUtils.h"
#include "VulkanShader.h"

#include <cassert>

#include "vk_mem_alloc.h"
#include <GLFW/glfw3.h>

#define VK_GET_DEVICE_FUNCTION(name) \
	name = (PFN_##name)vkGetDeviceProcAddr(context->logicalDevice, #name); \
	if (!name) { fprintf(stderr, "Failed to load Vulkan device function '%s'.\n", #name); abort(); }

#define VK_DEFINE_FUNCTION(name) \
	PFN_##name name;

VK_GENERAL_FUNCTIONS(VK_DEFINE_FUNCTION)
VK_INSTANCE_FUNCTIONS(VK_DEFINE_FUNCTION)
VK_DEVICE_FUNCTIONS(VK_DEFINE_FUNCTION)

VulkanInstance::VulkanInstance()
	: mHandle(VK_NULL_HANDLE)
{
}

VulkanInstance::~VulkanInstance()
{
	if (mHandle)
		vkDestroyInstance(mHandle, nullptr);
}

VulkanInstance::VulkanInstance(VulkanInstance &&other)
	: mHandle(other.mHandle)
{
	other.mHandle = VK_NULL_HANDLE;
}

VulkanInstance & VulkanInstance::operator=(VulkanInstance &&other)
{
	std::swap(mHandle, other.mHandle);
	return *this;
}

std::vector<VkLayerProperties> VulkanInstance::getLayers(void)
{
	uint32_t layerCount = 0;
	VK_VERIFY_RESULT(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));

	std::vector<VkLayerProperties> layers;
	layers.resize(layerCount);
	VK_VERIFY_RESULT(vkEnumerateInstanceLayerProperties(&layerCount, layers.data()));

	return layers;
}

std::vector<VkExtensionProperties> VulkanInstance::getExtensions(void)
{
	uint32_t extensionCount = 0;
	VK_VERIFY_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));

	std::vector<VkExtensionProperties> extensions;
	extensions.resize(extensionCount);
	VK_VERIFY_RESULT(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()));

	return extensions;
}

std::vector<VulkanPhysicalDevice> VulkanInstance::getPhysicalDevices()
{
	uint32_t physicalDeviceCount = 0;
	VK_VERIFY_RESULT(vkEnumeratePhysicalDevices(mHandle, &physicalDeviceCount, nullptr));

	std::vector<VkPhysicalDevice> physicalDevices;
	physicalDevices.resize(physicalDeviceCount);
	VK_VERIFY_RESULT(vkEnumeratePhysicalDevices(mHandle, &physicalDeviceCount, physicalDevices.data()));

	std::vector<VulkanPhysicalDevice> result;
	result.resize(physicalDeviceCount);
	for (int i = 0; i < (int)physicalDeviceCount; i++)
		result[i].mHandle = physicalDevices[i];

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanPhysicalDevice::VulkanPhysicalDevice()
	: mHandle(VK_NULL_HANDLE)
{
}

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanPhysicalDevice &&other)
	: mHandle(other.mHandle)
{
	other.mHandle = VK_NULL_HANDLE;
}

VulkanPhysicalDevice & VulkanPhysicalDevice::operator=(VulkanPhysicalDevice &&other)
{
	std::swap(mHandle, other.mHandle);
	return *this;
}

std::vector<VkLayerProperties> VulkanPhysicalDevice::getLayers()
{
	uint32_t layerCount = 0;
	VK_VERIFY_RESULT(vkEnumerateDeviceLayerProperties(mHandle, &layerCount, nullptr));

	std::vector<VkLayerProperties> layers;
	layers.resize(layerCount);
	VK_VERIFY_RESULT(vkEnumerateDeviceLayerProperties(mHandle, &layerCount, layers.data()));

	return layers;
}

std::vector<VkExtensionProperties> VulkanPhysicalDevice::getExtensions()
{
	uint32_t extensionCount = 0;
	VK_VERIFY_RESULT(vkEnumerateDeviceExtensionProperties(mHandle, nullptr, &extensionCount, nullptr));

	std::vector<VkExtensionProperties> extensions;
	extensions.resize(extensionCount);
	VK_VERIFY_RESULT(vkEnumerateDeviceExtensionProperties(mHandle, nullptr, &extensionCount, extensions.data()));

	return extensions;
}

std::vector<VkQueueFamilyProperties> VulkanPhysicalDevice::getQueueFamilies()
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(mHandle, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies;
	queueFamilies.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(mHandle, &queueFamilyCount, queueFamilies.data());

	return queueFamilies;
}

std::vector<VkSurfaceFormatKHR> VulkanPhysicalDevice::getSupportedSurfaceFormats(const VulkanSurface &surface)
{
	uint32_t surfaceFormatCount = 0;
	VK_VERIFY_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(mHandle, surface.mHandle, &surfaceFormatCount, nullptr));

	std::vector<VkSurfaceFormatKHR> surfaceFormats;
	surfaceFormats.resize(surfaceFormatCount);
	VK_VERIFY_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(mHandle, surface.mHandle, &surfaceFormatCount, surfaceFormats.data()));

	return surfaceFormats;
}
	
std::vector<VkPresentModeKHR> VulkanPhysicalDevice::getSupportedPresentModes(const VulkanSurface &surface)
{
	uint32_t presentModeCount = 0;
	VK_VERIFY_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(mHandle, surface.mHandle, &presentModeCount, nullptr));

	std::vector<VkPresentModeKHR> presentModes;
	presentModes.resize(presentModeCount);
	VK_VERIFY_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(mHandle, surface.mHandle, &presentModeCount, presentModes.data()));

	return presentModes;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanBuffer::VulkanBuffer()
{
}

VulkanBuffer::~VulkanBuffer()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanBufferView::VulkanBufferView()
{
}

VulkanBufferView::~VulkanBufferView()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanCommandBuffer::VulkanCommandBuffer()
{
}

VulkanCommandBuffer::~VulkanCommandBuffer()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDescriptorPool::VulkanDescriptorPool()
{
}

VulkanDescriptorPool::~VulkanDescriptorPool()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDescriptorSet::VulkanDescriptorSet()
{
}

VulkanDescriptorSet::~VulkanDescriptorSet()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDescriptorSetLayout::VulkanDescriptorSetLayout()
{
}

VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDevice::VulkanDevice()
{
}

VulkanDevice::~VulkanDevice()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanEvent::VulkanEvent()
{
}

VulkanEvent::~VulkanEvent()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanFence::VulkanFence()
{
}

VulkanFence::~VulkanFence()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanFramebuffer::VulkanFramebuffer()
{
}

VulkanFramebuffer::~VulkanFramebuffer()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanImage::VulkanImage()
{
}

VulkanImage::~VulkanImage()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanImageView::VulkanImageView()
{
}

VulkanImageView::~VulkanImageView()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanRenderPass::VulkanRenderPass()
{
}

VulkanRenderPass::~VulkanRenderPass()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanSurface::VulkanSurface()
{
}

VulkanSurface::~VulkanSurface()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanPipeline::VulkanPipeline()
{
}

VulkanPipeline::~VulkanPipeline()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanPipelineLayout::VulkanPipelineLayout()
{
}

VulkanPipelineLayout::~VulkanPipelineLayout()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanQueue::VulkanQueue()
{
}

VulkanQueue::~VulkanQueue()
{
}

///////////////////////////////////////////////////////////////////////////////////////
	
VulkanSampler::VulkanSampler()
{
}

VulkanSampler::~VulkanSampler()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanSemaphore::VulkanSemaphore()
{
}

VulkanSemaphore::~VulkanSemaphore()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanSwapchain::VulkanSwapchain()
{
}

VulkanSwapchain::~VulkanSwapchain()
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanInstanceCreator::VulkanInstanceCreator()
	: mApplicationInfo{}
	, mInstanceCI{}
{
	mApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

	mInstanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	mInstanceCI.pApplicationInfo = &mApplicationInfo;
}

VulkanInstanceCreator & VulkanInstanceCreator::setApplication(const char *name, uint32_t version)
{
	mApplicationInfo.pApplicationName = name;
	mApplicationInfo.applicationVersion = version;

	return *this;
}

VulkanInstanceCreator & VulkanInstanceCreator::setEngine(const char *name, uint32_t version)
{
	mApplicationInfo.pEngineName = name;
	mApplicationInfo.engineVersion = version;

	return *this;
}

VulkanInstanceCreator & VulkanInstanceCreator::setApiVersion(uint32_t version)
{
	mApplicationInfo.apiVersion = version;

	return *this;
}

VulkanInstanceCreator & VulkanInstanceCreator::addEnabledLayer(const char *name)
{
	mEnabledLayers.push_back(name);
	mInstanceCI.ppEnabledLayerNames = mEnabledLayers.data();
	mInstanceCI.enabledLayerCount = (uint32_t)mEnabledLayers.size();

	return *this;
}

VulkanInstanceCreator & VulkanInstanceCreator::addEnabledExtension(const char *name)
{
	mEnabledExtensions.push_back(name);
	mInstanceCI.ppEnabledExtensionNames = mEnabledExtensions.data();
	mInstanceCI.enabledExtensionCount = (uint32_t)mEnabledExtensions.size();

	return *this;
}

VulkanInstance VulkanInstanceCreator::create()
{
	#define VK_GET_GENERAL_FUNCTION(name) \
		name = (PFN_##name)glfwGetInstanceProcAddress(nullptr, #name); \
		if (!name) { fprintf(stderr, "Failed to load Vulkan general function '%s'.\n", #name); abort(); }

	VK_GENERAL_FUNCTIONS(VK_GET_GENERAL_FUNCTION)

	VulkanInstance result;
	VK_VERIFY_RESULT(vkCreateInstance(&mInstanceCI, nullptr, &result.mHandle));

	#define VK_GET_INSTANCE_FUNCTION(name) \
		name = (PFN_##name)glfwGetInstanceProcAddress(result.mHandle, #name); \
		if (!name) { fprintf(stderr, "Failed to load Vulkan instance function '%s'.\n", #name); abort(); }

	VK_INSTANCE_FUNCTIONS(VK_GET_INSTANCE_FUNCTION)

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDeviceCreator::VulkanDeviceCreator()
	: mEnabledFeatures{}
	, mDeviceCI{}
{
	mDeviceCI.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	mDeviceCI.pEnabledFeatures = &mEnabledFeatures;
}

VulkanDeviceCreator & VulkanDeviceCreator::addQueueFamily(uint32_t familyIndex)
{
	mDeviceQueueCIs.resize(mDeviceQueueCIs.size() + 1);
	mDeviceQueueCIs.back().sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

	mDeviceCI.queueCreateInfoCount = (uint32_t)mDeviceQueueCIs.size();
	mDeviceCI.pQueueCreateInfos = mDeviceQueueCIs.data();

	mPriorities.resize(mPriorities.size() + 1);

	return *this;
}

VulkanDeviceCreator & VulkanDeviceCreator::addQueueFamilyQueue(float priority)
{
	auto &priorities = mPriorities.back();
	auto &deviceQueueCI = mDeviceQueueCIs.back();

	priorities.push_back(priority);

	deviceQueueCI.queueCount = (uint32_t)priorities.size();
	deviceQueueCI.pQueuePriorities = priorities.data();

	return *this;
}

VulkanDeviceCreator & VulkanDeviceCreator::addEnabledLayer(const char *name)
{
	mEnabledLayers.push_back(name);

	mDeviceCI.enabledLayerCount = (uint32_t)mEnabledLayers.size();
	mDeviceCI.ppEnabledLayerNames = mEnabledLayers.data();

	return *this;
}

VulkanDeviceCreator & VulkanDeviceCreator::addEnabledExtension(const char *name)
{
	mEnabledExtensions.push_back(name);

	mDeviceCI.enabledExtensionCount = (uint32_t)mEnabledExtensions.size();
	mDeviceCI.ppEnabledExtensionNames = mEnabledExtensions.data();

	return *this;
}

VulkanDevice VulkanDeviceCreator::create(const VulkanPhysicalDevice &physicalDevice)
{
	VulkanDevice result;
	VK_VERIFY_RESULT(vkCreateDevice(physicalDevice.mHandle, &mDeviceCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanBarrier::VulkanBarrier()
{
}

VulkanBarrier & VulkanBarrier::setSrcStageMask(VkPipelineStageFlags stageMask)
{
	mSrcStageMask = stageMask;

	return *this;
}

VulkanBarrier & VulkanBarrier::setDstStageMask(VkPipelineStageFlags stageMask)
{
	mDstStageMask = stageMask;

	return *this;
}

VulkanBarrier & VulkanBarrier::setDependencyFlags(VkDependencyFlags dependencyFlags)
{
	mDependencyFlags = dependencyFlags;

	return *this;
}

VulkanBarrier & VulkanBarrier::addEvent(const VulkanEvent &event)
{
	mEvents.push_back(event.mHandle);

	return *this;
}

VulkanBarrier & VulkanBarrier::addMemoryBarrier(VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask)
{
	VkMemoryBarrier memoryBarrier = {};
	memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
	memoryBarrier.srcAccessMask = srcAccessMask;
	memoryBarrier.dstAccessMask = dstAccessMask;

	mMemoryBarriers.push_back(memoryBarrier);

	return *this;
}

VulkanBarrier & VulkanBarrier::addBufferMemoryBarrier(const VulkanBuffer &buffer, VkDeviceSize size, VkDeviceSize offset, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex)
{
	VkBufferMemoryBarrier bufferMemoryBarrier = {};
	bufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
	bufferMemoryBarrier.srcAccessMask = srcAccessMask;
	bufferMemoryBarrier.dstAccessMask = dstAccessMask;
	bufferMemoryBarrier.srcQueueFamilyIndex = srcQueueFamilyIndex;
	bufferMemoryBarrier.dstQueueFamilyIndex = dstQueueFamilyIndex;
	bufferMemoryBarrier.buffer = buffer.mHandle;
	bufferMemoryBarrier.offset = offset;
	bufferMemoryBarrier.size = size;

	mBufferMemoryBarriers.push_back(bufferMemoryBarrier);

	return *this;
}

VulkanBarrier & VulkanBarrier::addImageMemoryBarrier(const VulkanImage &image, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t srcQueueFamilyIndex, uint32_t dstQueueFamilyIndex)
{
	VkImageMemoryBarrier imageMemoryBarrier = {};
	imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	/*
	imageMemoryBarrier.srcAccessMask = srcAccessMask;
  imageMemoryBarrier.dstAccessMask = dstAccessMask;
  imageMemoryBarrier.oldLayout = oldLayout;
  imageMemoryBarrier.newLayout = newLayout;
  imageMemoryBarrier.srcQueueFamilyIndex = srcQueueFamilyIndex;
  imageMemoryBarrier.dstQueueFamilyIndex = dstQueueFamilyIndex;
  imageMemoryBarrier.image = image.mHandle;
  imageMemoryBarrier.subresourceRange.aspectMask = aspectMask;
	imageMemoryBarrier.subresourceRange.baseMipLevel = baseMipLevel;
	imageMemoryBarrier.subresourceRange.levelCount = levelCount;
	imageMemoryBarrier.subresourceRange.baseArrayLayer = baseArrayLayer;
	imageMemoryBarrier.subresourceRange.layerCount = layerCount;
	*/
	mImageMemoryBarriers.push_back(imageMemoryBarrier);

	return *this;
}

void VulkanBarrier::executePipelineBarrierCommand(VulkanCommandBuffer &commandBuffer)
{
}

void VulkanBarrier::executeWaitEventsCommand(VulkanCommandBuffer &commandBuffer)
{
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanRenderPassCreator::VulkanRenderPassCreator()
	: mRenderPassCI{}
{
	mRenderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addAttachment(VkFormat format, VkSampleCountFlagBits samples, VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp, VkImageLayout initialLayout, VkImageLayout finalLayout)
{
	VkAttachmentDescription attachment = {};
	attachment.format = format;
	attachment.samples = samples;
	attachment.loadOp = loadOp;
	attachment.storeOp = storeOp;
	attachment.stencilLoadOp = stencilLoadOp;
	attachment.stencilStoreOp = stencilStoreOp;
	attachment.initialLayout = initialLayout;
	attachment.finalLayout = finalLayout;

	mAttachements.push_back(attachment);

	mRenderPassCI.attachmentCount = (uint32_t)mAttachements.size();
	mRenderPassCI.pAttachments = mAttachements.data();

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addSubpass()
{
	mSubpasses.resize(mSubpasses.size() + 1);
	mSubpassesRefs.resize(mSubpassesRefs.size() + 1);

	mRenderPassCI.subpassCount = (uint32_t)mSubpasses.size();
	mRenderPassCI.pSubpasses = mSubpasses.data();

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addSubpassInputAttachment(uint32_t attachment, VkImageLayout layout)
{
	auto &inputRefs = mSubpassesRefs.back().inputRefs;
	auto &subpass = mSubpasses.back();

	VkAttachmentReference attachmentRef;
	attachmentRef.attachment = attachment;
	attachmentRef.layout = layout;

	inputRefs.push_back(attachmentRef);

	subpass.inputAttachmentCount = (uint32_t)inputRefs.size();
	subpass.pInputAttachments = inputRefs.data();

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addSubpassColorResolveAttachment(uint32_t colorAttachment, VkImageLayout colorLayout, uint32_t resolveAttachment, VkImageLayout resolveLayout)
{
	auto &colorRefs = mSubpassesRefs.back().colorRefs;
	auto &resolveRefs = mSubpassesRefs.back().resolveRefs;
	auto &subpass = mSubpasses.back();

	VkAttachmentReference attachmentRef;
	attachmentRef.attachment = colorAttachment;
	attachmentRef.layout = colorLayout;

	colorRefs.push_back(attachmentRef);

	attachmentRef.attachment = resolveAttachment;
	attachmentRef.layout = resolveLayout;

	resolveRefs.push_back(attachmentRef);

	subpass.colorAttachmentCount = (uint32_t)colorRefs.size();
	subpass.pColorAttachments = colorRefs.data();
	subpass.pResolveAttachments = resolveRefs.data();

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::setSubpassDepthStencilAttachment(uint32_t attachment, VkImageLayout layout)
{
	auto &depthStencilRef = mSubpassesRefs.back().depthStencilRef;

	depthStencilRef.attachment = attachment;
	depthStencilRef.layout = layout;

	mSubpasses.back().pDepthStencilAttachment = &depthStencilRef;

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addSubpassPreserveAttachment(uint32_t attachment)
{
	auto &preserveRefs = mSubpassesRefs.back().preserveRefs;
	auto &subpass = mSubpasses.back();

	preserveRefs.push_back(attachment);

	subpass.preserveAttachmentCount = (uint32_t)preserveRefs.size();
	subpass.pPreserveAttachments = preserveRefs.data();

	return *this;
}

VulkanRenderPassCreator & VulkanRenderPassCreator::addDependency(uint32_t srcSubpass, uint32_t dstSubpass, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask, VkDependencyFlags dependencyFlags)
{
	VkSubpassDependency dependency = {};
	dependency.srcSubpass = srcSubpass;
	dependency.dstSubpass = dstSubpass;
	dependency.srcStageMask = srcStageMask;
	dependency.dstStageMask = dstStageMask;
	dependency.srcAccessMask = srcAccessMask;
	dependency.dstAccessMask = dstAccessMask;
	dependency.dependencyFlags = dependencyFlags;

	mDependencies.push_back(dependency);

	mRenderPassCI.dependencyCount = (uint32_t)mDependencies.size();
	mRenderPassCI.pDependencies = mDependencies.data();

	return *this;
}

VulkanRenderPass VulkanRenderPassCreator::create(const VulkanDevice &device)
{
	VulkanRenderPass result;
	VK_VERIFY_RESULT(vkCreateRenderPass(device.mHandle, &mRenderPassCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanGraphicsPipelineCreator::VulkanGraphicsPipelineCreator()
{
	mVertexInputStateCI = {};
	mVertexInputStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	mInputAssemblyStateCI = {};
	mInputAssemblyStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	mInputAssemblyStateCI.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	mInputAssemblyStateCI.primitiveRestartEnable = VK_FALSE;

	mTessellationStateCI = {};
	mTessellationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	mTessellationStateCI.patchControlPoints = 0;

	mViewportStateCI = {};
	mViewportStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

	mRasterizationStateCI = {};
	mRasterizationStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	mRasterizationStateCI.depthClampEnable = VK_FALSE;
	mRasterizationStateCI.rasterizerDiscardEnable = VK_FALSE;
	mRasterizationStateCI.polygonMode = VK_POLYGON_MODE_FILL;
	mRasterizationStateCI.cullMode = VK_CULL_MODE_BACK_BIT;
	mRasterizationStateCI.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	mRasterizationStateCI.depthBiasEnable = VK_FALSE;
	mRasterizationStateCI.lineWidth = 1.f;

	mMultisampleCI = {};
	mMultisampleCI.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	mMultisampleCI.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	mMultisampleCI.sampleShadingEnable = VK_FALSE;
	mMultisampleCI.alphaToCoverageEnable = VK_FALSE;
	mMultisampleCI.alphaToOneEnable = VK_FALSE;

	mDepthStencilStateCI = {};
	mDepthStencilStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	mDepthStencilStateCI.depthTestEnable = VK_TRUE;
	mDepthStencilStateCI.depthWriteEnable = VK_TRUE;
	mDepthStencilStateCI.depthCompareOp = VK_COMPARE_OP_LESS;
	mDepthStencilStateCI.depthBoundsTestEnable = VK_TRUE;
	mDepthStencilStateCI.stencilTestEnable = VK_FALSE;
	mDepthStencilStateCI.minDepthBounds = 0.f;
	mDepthStencilStateCI.maxDepthBounds = 1.f;

	mColorBlendStateCI = {};
	mColorBlendStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	mColorBlendStateCI.logicOpEnable = VK_FALSE;

	mDynamicStateCI = {};
	mDynamicStateCI.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

	mGraphicsPipelineCI = {};
	mGraphicsPipelineCI.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	mGraphicsPipelineCI.pVertexInputState = &mVertexInputStateCI;
	mGraphicsPipelineCI.pInputAssemblyState = &mInputAssemblyStateCI;
	mGraphicsPipelineCI.pTessellationState = &mTessellationStateCI;
	mGraphicsPipelineCI.pViewportState = &mViewportStateCI;
	mGraphicsPipelineCI.pRasterizationState = &mRasterizationStateCI;
	mGraphicsPipelineCI.pMultisampleState = &mMultisampleCI;
	mGraphicsPipelineCI.pDepthStencilState = &mDepthStencilStateCI;
	mGraphicsPipelineCI.pColorBlendState = &mColorBlendStateCI;
	mGraphicsPipelineCI.pDynamicState = &mDynamicStateCI;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addShader(const VulkanShaderModule &shaderModule)
{
	mSpecializations.resize(mSpecializations.size() + 1);

	VkPipelineShaderStageCreateInfo shaderStageCI = {};
	shaderStageCI.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCI.stage = shaderModule.mStage;
	shaderStageCI.module = shaderModule.mHandle;
	shaderStageCI.pName = "main";
	shaderStageCI.pSpecializationInfo = &mSpecializations.back().mInfo;

	mShaderStages.push_back(shaderStageCI);

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setSpecialization(size_t dataSize, const void *pData)
{
	auto &specializationInfo = mSpecializations.back().mInfo;

	specializationInfo.dataSize = dataSize;
	specializationInfo.pData = pData;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addSpecializationMapEntry(uint32_t constantID, uint32_t offset, size_t size)
{
	auto &mapEntries = mSpecializations.back().mMapEntries;

	VkSpecializationMapEntry mapEntry;
	mapEntry.constantID = constantID;
	mapEntry.offset = offset;
	mapEntry.size = size;

	mapEntries.push_back(mapEntry);

	auto &specializationInfo = mSpecializations.back().mInfo;
	specializationInfo.mapEntryCount = (uint32_t)mapEntries.size();
	specializationInfo.pMapEntries = mapEntries.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addVertexInputBinding(uint32_t binding, uint32_t stride, VkVertexInputRate inputRate)
{
	VkVertexInputBindingDescription vertexInputBinding;
	vertexInputBinding.binding = binding;
	vertexInputBinding.stride = stride;
	vertexInputBinding.inputRate = inputRate;

	mVertexInputBindings.push_back(vertexInputBinding);

	mVertexInputStateCI.vertexBindingDescriptionCount = (uint32_t)mVertexInputBindings.size();
	mVertexInputStateCI.pVertexBindingDescriptions = mVertexInputBindings.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addVertexInputAttribute(uint32_t location, uint32_t binding, VkFormat format, uint32_t offset)
{
	VkVertexInputAttributeDescription vertexInputAttribute;
	vertexInputAttribute.location = location;
	vertexInputAttribute.binding = binding;
	vertexInputAttribute.format = format;
	vertexInputAttribute.offset = offset;

	mVertexInputAttributes.push_back(vertexInputAttribute);

	mVertexInputStateCI.vertexAttributeDescriptionCount = (uint32_t)mVertexInputAttributes.size();
	mVertexInputStateCI.pVertexAttributeDescriptions = mVertexInputAttributes.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setPrimitiveTopology(VkPrimitiveTopology primitiveTopology)
{
	mInputAssemblyStateCI.topology = primitiveTopology;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setPrimitiveRestartEnable(VkBool32 primitiveRestartEnable)
{
	mInputAssemblyStateCI.primitiveRestartEnable = primitiveRestartEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setPatchControlPoints(uint32_t patchControlPoints)
{
	mTessellationStateCI.patchControlPoints = patchControlPoints;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
{
	VkViewport viewport;
	viewport.x = x;
	viewport.y = y;
	viewport.width = width;
	viewport.height = height;
	viewport.minDepth = minDepth;
	viewport.maxDepth = maxDepth;

	mViewports.push_back(viewport);

	mViewportStateCI.viewportCount = (uint32_t)mViewports.size();
	mViewportStateCI.pViewports = mViewports.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addScissor(int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	VkRect2D scissor;
	scissor.offset.x = x;
	scissor.offset.y = y;
	scissor.extent.width = width;
	scissor.extent.height = height;

	mScissors.push_back(scissor);

	mViewportStateCI.scissorCount = (uint32_t)mScissors.size();
	mViewportStateCI.pScissors = mScissors.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthClampEnable(VkBool32 depthClampEnable)
{
	mRasterizationStateCI.depthClampEnable = depthClampEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setRasterizerDiscardEnable(VkBool32 rasterizerDiscardEnable)
{
	mRasterizationStateCI.rasterizerDiscardEnable = rasterizerDiscardEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setPolygonMode(VkPolygonMode polygonMode)
{
	mRasterizationStateCI.polygonMode = polygonMode;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setCullMode(VkCullModeFlags cullMode)
{
	mRasterizationStateCI.cullMode = cullMode;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setFrontFace(VkFrontFace frontFace)
{
	mRasterizationStateCI.frontFace = frontFace;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthBiasEnable(VkBool32 depthBiasEnable)
{
	mRasterizationStateCI.depthBiasEnable = depthBiasEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthBias(float constantFactor, float clamp, float slopeFactor)
{
	mRasterizationStateCI.depthBiasConstantFactor = constantFactor;
	mRasterizationStateCI.depthBiasClamp = clamp;
	mRasterizationStateCI.depthBiasSlopeFactor = slopeFactor;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setLineWidth(float lineWidth)
{
	mRasterizationStateCI.lineWidth = lineWidth;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthTestEnable(VkBool32 depthTestEnable)
{
	mDepthStencilStateCI.depthTestEnable = depthTestEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthWriteEnable(VkBool32 depthWriteEnable)
{
	mDepthStencilStateCI.depthWriteEnable = depthWriteEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthCompareOp(VkCompareOp depthCompareOp)
{
	mDepthStencilStateCI.depthCompareOp = depthCompareOp;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setDepthBoundsTestEnable(VkBool32 depthBoundsTestEnable)
{
	mDepthStencilStateCI.depthBoundsTestEnable = depthBoundsTestEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilTestEnable(VkBool32 stencilTestEnable)
{
	mDepthStencilStateCI.stencilTestEnable = stencilTestEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilFrontOps(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp)
{
	mDepthStencilStateCI.front.failOp = failOp;
	mDepthStencilStateCI.front.passOp = passOp;
	mDepthStencilStateCI.front.depthFailOp = depthFailOp;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilFrontCompare(VkCompareOp compareOp, uint32_t reference, uint32_t compareMask)
{
	mDepthStencilStateCI.front.compareOp = compareOp;
	mDepthStencilStateCI.front.reference = reference;
	mDepthStencilStateCI.front.compareMask = compareMask;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilFrontMask(uint32_t writeMask)
{
	mDepthStencilStateCI.front.writeMask = writeMask;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilBackOps(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp)
{
	mDepthStencilStateCI.back.failOp = failOp;
	mDepthStencilStateCI.back.passOp = passOp;
	mDepthStencilStateCI.back.depthFailOp = depthFailOp;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilBackCompare(VkCompareOp compareOp, uint32_t reference, uint32_t compareMask)
{
	mDepthStencilStateCI.back.compareOp = compareOp;
	mDepthStencilStateCI.back.reference = reference;
	mDepthStencilStateCI.back.compareMask = compareMask;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setStencilBackMask(uint32_t writeMask)
{
	mDepthStencilStateCI.back.writeMask = writeMask;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setLogicOpEnable(VkBool32 logicOpEnable)
{
	mColorBlendStateCI.logicOpEnable = logicOpEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setLogicOp(VkLogicOp logicOp)
{
	mColorBlendStateCI.logicOp = logicOp;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setBlendConstants(float red, float green, float blue, float alpha)
{
	mColorBlendStateCI.blendConstants[0] = red;
	mColorBlendStateCI.blendConstants[1] = green;
	mColorBlendStateCI.blendConstants[2] = blue;
	mColorBlendStateCI.blendConstants[3] = alpha;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addColorBlendAttachmentState()
{
	mColorBlendAttachmentStates.resize(mColorBlendAttachmentStates.size() + 1);

	mColorBlendStateCI.attachmentCount = (uint32_t)mColorBlendAttachmentStates.size();
	mColorBlendStateCI.pAttachments = mColorBlendAttachmentStates.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setBlendEnable(VkBool32 blendEnable)
{
	mColorBlendAttachmentStates.back().blendEnable = blendEnable;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setBlendOps(VkBlendOp colorBlendOp, VkBlendOp alphaBlendOp)
{
	auto &colorBlendAttachmentState = mColorBlendAttachmentStates.back();
	colorBlendAttachmentState.colorBlendOp = colorBlendOp;
	colorBlendAttachmentState.alphaBlendOp = alphaBlendOp;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setBlendFactors(VkBlendFactor srcColorBlendFactor, VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendFactor dstAlphaBlendFactor)
{
	auto &colorBlendAttachmentState = mColorBlendAttachmentStates.back();
	colorBlendAttachmentState.srcColorBlendFactor = srcColorBlendFactor;
	colorBlendAttachmentState.srcAlphaBlendFactor = srcAlphaBlendFactor;
	colorBlendAttachmentState.dstColorBlendFactor = dstColorBlendFactor;
	colorBlendAttachmentState.dstAlphaBlendFactor = dstAlphaBlendFactor;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setColorWriteMask(VkColorComponentFlags colorWriteMask)
{
	mColorBlendAttachmentStates.back().colorWriteMask = colorWriteMask;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::addDynamicState(VkDynamicState dynamicState)
{
	mDynamicStates.push_back(dynamicState);

	mDynamicStateCI.dynamicStateCount = (uint32_t)mDynamicStates.size();
	mDynamicStateCI.pDynamicStates = mDynamicStates.data();

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setPipelineLayout(const VulkanPipelineLayout &pipelineLayout)
{
	mGraphicsPipelineCI.layout = pipelineLayout.mHandle;

	return *this;
}

VulkanGraphicsPipelineCreator & VulkanGraphicsPipelineCreator::setRenderPass(const VulkanRenderPass &renderPass, uint32_t subpass)
{
	mGraphicsPipelineCI.renderPass = renderPass.mHandle;
	mGraphicsPipelineCI.subpass = subpass;

	return *this;
}

VulkanPipeline VulkanGraphicsPipelineCreator::create(const VulkanDevice &device)
{
	VulkanPipeline result;
	VK_VERIFY_RESULT(vkCreateGraphicsPipelines(device.mHandle, VK_NULL_HANDLE, 1, &mGraphicsPipelineCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanBufferCreator::VulkanBufferCreator()
	: mBufferCI{}
{
	mBufferCI.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
}

VulkanBufferCreator & VulkanBufferCreator::setFlags(VkBufferCreateFlags flags)
{
	mBufferCI.flags = flags;

	return *this;
}

VulkanBufferCreator & VulkanBufferCreator::setSize(VkDeviceSize size)
{
	mBufferCI.size = size;

	return *this;
}

VulkanBufferCreator & VulkanBufferCreator::setUsage(VkBufferUsageFlags usage)
{
	mBufferCI.usage = usage;

	return *this;
}

VulkanBufferCreator & VulkanBufferCreator::setSharingMode(VkSharingMode sharingMode)
{
	mBufferCI.sharingMode = sharingMode;

	return *this;
}

VulkanBufferCreator & VulkanBufferCreator::addQueueFamily(uint32_t queueFamily)
{
	mQueueFamily.push_back(queueFamily);

	mBufferCI.queueFamilyIndexCount = (uint32_t)mQueueFamily.size();
	mBufferCI.pQueueFamilyIndices = mQueueFamily.data();

	return *this;
}

VulkanBuffer VulkanBufferCreator::create(const VulkanDevice &device)
{
	VulkanBuffer result;
	VK_VERIFY_RESULT(vkCreateBuffer(device.mHandle, &mBufferCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanBufferViewCreator::VulkanBufferViewCreator()
	: mBufferViewCI{}
{
	mBufferViewCI.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	mBufferViewCI.range = VK_WHOLE_SIZE;
}

VulkanBufferViewCreator & VulkanBufferViewCreator::setBuffer(const VulkanBuffer &buffer)
{
	mBufferViewCI.buffer = buffer.mHandle;

	return *this;
}

VulkanBufferViewCreator & VulkanBufferViewCreator::setFormat(VkFormat format)
{
	mBufferViewCI.format = format;

	return *this;
}

VulkanBufferViewCreator & VulkanBufferViewCreator::setOffset(VkDeviceSize offset)
{
	mBufferViewCI.offset = offset;

	return *this;
}

VulkanBufferViewCreator & VulkanBufferViewCreator::setRange(VkDeviceSize range)
{
	mBufferViewCI.range = range;

	return *this;
}

VulkanBufferView VulkanBufferViewCreator::create(const VulkanDevice &device)
{
	VulkanBufferView bufferView;
	VK_VERIFY_RESULT(vkCreateBufferView(device.mHandle, &mBufferViewCI, nullptr, &bufferView.mHandle));
	return bufferView;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanImageCreator::VulkanImageCreator()
	: mImageCI{}
{
	mImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	mImageCI.imageType = VK_IMAGE_TYPE_2D; 
	mImageCI.format = VK_FORMAT_R8G8B8A8_SRGB;
	mImageCI.mipLevels = 1;
	mImageCI.arrayLayers = 1;
	mImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
	mImageCI.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
}

VulkanImageCreator & VulkanImageCreator::setFlags(VkImageCreateFlags flags)
{
	mImageCI.flags = flags;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setType(VkImageType type)
{
	mImageCI.imageType = type;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setFormat(VkFormat format)
{
	mImageCI.format = format;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setExtent(uint32_t width, uint32_t height, uint32_t depth)
{
	mImageCI.extent.width = width;
	mImageCI.extent.height = height;
	mImageCI.extent.depth = depth;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setMipLevels(uint32_t mipLevels)
{
	mImageCI.mipLevels = mipLevels;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setArrayLayers(uint32_t arrayLayers)
{
	mImageCI.arrayLayers = arrayLayers;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setSamples(VkSampleCountFlagBits samples)
{
	mImageCI.samples = samples;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setTiling(VkImageTiling tiling)
{
	mImageCI.tiling = tiling;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setUsage(VkImageUsageFlags usage)
{
	mImageCI.usage = usage;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setSharingMode(VkSharingMode sharingMode)
{
	mImageCI.sharingMode = sharingMode;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::setInitialLayout(VkImageLayout initialLayout)
{
	mImageCI.initialLayout = initialLayout;

	return *this;
}

VulkanImageCreator & VulkanImageCreator::addQueueFamily(uint32_t queueFamily)
{
	mQueueFamily.push_back(queueFamily);

	mImageCI.queueFamilyIndexCount = (uint32_t)mQueueFamily.size();
	mImageCI.pQueueFamilyIndices = mQueueFamily.data();

	return *this;
}

VulkanImage VulkanImageCreator::create(const VulkanDevice &device)
{
	VulkanImage result;
	VK_VERIFY_RESULT(vkCreateImage(device.mHandle, &mImageCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanImageViewCreator::VulkanImageViewCreator()
	: mImageViewCI{}
{
	mImageViewCI.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	mImageViewCI.viewType = VK_IMAGE_VIEW_TYPE_2D;
	mImageViewCI.format = VK_FORMAT_R8G8B8A8_SRGB;
	mImageViewCI.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	mImageViewCI.subresourceRange.baseMipLevel = 0;
	mImageViewCI.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
	mImageViewCI.subresourceRange.baseArrayLayer = 0;
	mImageViewCI.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;
}

VulkanImageViewCreator & VulkanImageViewCreator::setImage(const VulkanImage &image)
{
	mImageViewCI.image = image.mHandle;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setType(VkImageViewType type)
{
	mImageViewCI.viewType = type;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setFormat(VkFormat format)
{
	mImageViewCI.format = format;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setComponentMapping(VkComponentSwizzle r, VkComponentSwizzle g, VkComponentSwizzle b, VkComponentSwizzle a)
{
	mImageViewCI.components.r = r;
	mImageViewCI.components.g = g;
	mImageViewCI.components.b = b;
	mImageViewCI.components.a = a;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setAspectMask(VkImageAspectFlags aspectMask)
{
	mImageViewCI.subresourceRange.aspectMask = aspectMask;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setMip(uint32_t baseMipLevel, uint32_t levelCount)
{
	mImageViewCI.subresourceRange.baseMipLevel = baseMipLevel;
	mImageViewCI.subresourceRange.levelCount = levelCount;

	return *this;
}

VulkanImageViewCreator & VulkanImageViewCreator::setArrayLayer(uint32_t baseArrayLayer, uint32_t layerCount)
{
	mImageViewCI.subresourceRange.baseArrayLayer = baseArrayLayer;
	mImageViewCI.subresourceRange.layerCount = layerCount;

	return *this;
}

VulkanImageView VulkanImageViewCreator::create(const VulkanDevice &device)
{
	VulkanImageView result;
	VK_VERIFY_RESULT(vkCreateImageView(device.mHandle, &mImageViewCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanQueueSubmit::VulkanQueueSubmit()
{
}

VulkanQueueSubmit & VulkanQueueSubmit::addSubmit()
{
	mSubmitInfos.resize(mSubmitInfos.size() + 1);
	mSubmitInfoData.resize(mSubmitInfoData.size() + 1);

	return *this;
}

VulkanQueueSubmit & VulkanQueueSubmit::addWaitSemaphore(const VulkanSemaphore &waitSemaphore, VkPipelineStageFlags waitDstStageMask)
{
	auto &submitInfo = mSubmitInfos.back();
	auto &submitInfoData = mSubmitInfoData.back();

	submitInfoData.waitSemaphores.push_back(waitSemaphore.mHandle);
	submitInfoData.waitDstStageMasks.push_back(waitDstStageMask);

	submitInfo.waitSemaphoreCount = (uint32_t)submitInfoData.waitSemaphores.size();
	submitInfo.pWaitSemaphores = submitInfoData.waitSemaphores.data();
	submitInfo.pWaitDstStageMask = submitInfoData.waitDstStageMasks.data();

	return *this;
}

VulkanQueueSubmit & VulkanQueueSubmit::addCommandBuffer(const VulkanCommandBuffer &commandBuffer)
{
	auto &submitInfo = mSubmitInfos.back();
	auto &submitInfoData = mSubmitInfoData.back();

	submitInfoData.commandBuffers.push_back(commandBuffer.mHandle);

	submitInfo.commandBufferCount = (uint32_t)submitInfoData.commandBuffers.size();
	submitInfo.pCommandBuffers = submitInfoData.commandBuffers.data();

	return *this;
}

VulkanQueueSubmit & VulkanQueueSubmit::addSignalSemaphore(const VulkanSemaphore &signalSemaphore)
{
	auto &submitInfo = mSubmitInfos.back();
	auto &submitInfoData = mSubmitInfoData.back();

	submitInfoData.signalSemaphores.push_back(signalSemaphore.mHandle);

	submitInfo.signalSemaphoreCount = (uint32_t)submitInfoData.signalSemaphores.size();
	submitInfo.pSignalSemaphores = submitInfoData.signalSemaphores.data();

	return *this;
}

void VulkanQueueSubmit::submit(const VulkanQueue &queue, const VulkanFence &fence)
{
	VK_VERIFY_RESULT(vkQueueSubmit(queue.mHandle, (uint32_t)mSubmitInfos.size(), mSubmitInfos.data(), fence.mHandle));
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanFramebufferCreator::VulkanFramebufferCreator()
	: mFramebufferCI{}
{
	mFramebufferCI.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
}

VulkanFramebufferCreator & VulkanFramebufferCreator::setRenderPass(const VulkanRenderPass &renderPass)
{
	mFramebufferCI.renderPass = renderPass.mHandle;

	return *this;
}

VulkanFramebufferCreator & VulkanFramebufferCreator::addAttachment(const VulkanImageView &attachment)
{
	mAttachments.push_back(attachment.mHandle);

	mFramebufferCI.attachmentCount = (uint32_t)mAttachments.size();
	mFramebufferCI.pAttachments = mAttachments.data();

	return *this;
}

VulkanFramebufferCreator & VulkanFramebufferCreator::setExtent(uint32_t width, uint32_t height, uint32_t layers)
{
	mFramebufferCI.width = width;
	mFramebufferCI.height = height;
	mFramebufferCI.layers = layers;

	return *this;
}

VulkanFramebuffer VulkanFramebufferCreator::create(const VulkanDevice &device)
{
	VulkanFramebuffer result;
	VK_VERIFY_RESULT(vkCreateFramebuffer(device.mHandle, &mFramebufferCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanSamplerCreator::VulkanSamplerCreator()
	: mSamplerCI{}
{
	mSamplerCI.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	mSamplerCI.magFilter = VK_FILTER_LINEAR;
	mSamplerCI.minFilter = VK_FILTER_LINEAR;
	mSamplerCI.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	mSamplerCI.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	mSamplerCI.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	mSamplerCI.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	mSamplerCI.mipLodBias = 0.f;
	mSamplerCI.anisotropyEnable = VK_TRUE;
	mSamplerCI.maxAnisotropy = 16.f;
	mSamplerCI.compareEnable = VK_FALSE;
	mSamplerCI.compareOp = VK_COMPARE_OP_NEVER;
	mSamplerCI.minLod = 0.f;
	mSamplerCI.maxLod = FLT_MAX;
	mSamplerCI.borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
	mSamplerCI.unnormalizedCoordinates = VK_FALSE;
}

VulkanSamplerCreator & VulkanSamplerCreator::setFilter(VkFilter minFilter, VkFilter magFilter)
{
	mSamplerCI.minFilter = minFilter;
	mSamplerCI.magFilter = magFilter;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setMipmapMode(VkSamplerMipmapMode mipmapMode)
{
	mSamplerCI.mipmapMode = mipmapMode;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setAddressMode(VkSamplerAddressMode u, VkSamplerAddressMode v, VkSamplerAddressMode w)
{
	mSamplerCI.addressModeU = u;
	mSamplerCI.addressModeV = v;
	mSamplerCI.addressModeW = w;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setLod(float minLod, float maxLod)
{
	mSamplerCI.minLod = minLod;
	mSamplerCI.maxLod = maxLod;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setMipLodBias(float mipLoadBias)
{
	mSamplerCI.mipLodBias = mipLoadBias;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setAnisotropyEnable(VkBool32 anisotropyEnable)
{
	mSamplerCI.anisotropyEnable = anisotropyEnable;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setMaxAnisotropy(float maxAnisotropy)
{
	mSamplerCI.maxAnisotropy = maxAnisotropy;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setCompareEnable(VkBool32 compareEnable)
{
	mSamplerCI.compareEnable = compareEnable;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setCompareOp(VkCompareOp compareOp)
{
	mSamplerCI.compareOp = compareOp;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setBorderColor(VkBorderColor borderColor)
{
	mSamplerCI.borderColor = borderColor;

	return *this;
}

VulkanSamplerCreator & VulkanSamplerCreator::setUnnormalizedCoordinates(VkBool32 unnormalizedCoordinates)
{
	mSamplerCI.unnormalizedCoordinates = unnormalizedCoordinates;

	return *this;
}

VulkanSampler VulkanSamplerCreator::create(const VulkanDevice &device)
{
	VulkanSampler result;
	VK_VERIFY_RESULT(vkCreateSampler(device.mHandle, &mSamplerCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDescriptorSetLayoutCreator::VulkanDescriptorSetLayoutCreator()
	: mDescriptorSetLayoutCI{}
{
	mDescriptorSetLayoutCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
}

VulkanDescriptorSetLayoutCreator & VulkanDescriptorSetLayoutCreator::setFlags(VkDescriptorSetLayoutCreateFlags flags)
{
	mDescriptorSetLayoutCI.flags = flags;

	return *this;
}

VulkanDescriptorSetLayoutCreator & VulkanDescriptorSetLayoutCreator::addBinding(uint32_t binding, VkDescriptorType descriptorType, uint32_t descriptorCount, VkShaderStageFlags shaderStages)
{
	VkDescriptorSetLayoutBinding desciptorSetLayoutBinding = {};
	desciptorSetLayoutBinding.binding = binding;
	desciptorSetLayoutBinding.descriptorType = descriptorType;
	desciptorSetLayoutBinding.descriptorCount = descriptorCount;
	desciptorSetLayoutBinding.stageFlags = shaderStages;

	mBindings.push_back(desciptorSetLayoutBinding);

	mDescriptorSetLayoutCI.bindingCount = (uint32_t)mBindings.size();
	mDescriptorSetLayoutCI.pBindings = mBindings.data();

	return *this;
}

VulkanDescriptorSetLayoutCreator & VulkanDescriptorSetLayoutCreator::addImmutableSamplerBinding(uint32_t binding, VkDescriptorType descriptorType, VkShaderStageFlags shaderStages)
{
	VkDescriptorSetLayoutBinding desciptorSetLayoutBinding = {};
	desciptorSetLayoutBinding.binding = binding;
	desciptorSetLayoutBinding.descriptorType = descriptorType;
	desciptorSetLayoutBinding.descriptorCount = 0;
	desciptorSetLayoutBinding.stageFlags = shaderStages;

	mBindings.push_back(desciptorSetLayoutBinding);

	mImmutableSamplers.resize(mImmutableSamplers.size() + 1);

	mDescriptorSetLayoutCI.bindingCount = (uint32_t)mBindings.size();
	mDescriptorSetLayoutCI.pBindings = mBindings.data();

	return *this;
}

VulkanDescriptorSetLayoutCreator & VulkanDescriptorSetLayoutCreator::addImmutableSampler(const VulkanSampler &sampler)
{
	auto &immutableSampler = mImmutableSamplers.back();

	immutableSampler.push_back(sampler.mHandle);

	mBindings.back().pImmutableSamplers = immutableSampler.data();

	return *this;
}

VulkanDescriptorSetLayout VulkanDescriptorSetLayoutCreator::create(const VulkanDevice &device)
{
	VulkanDescriptorSetLayout result;
	VK_VERIFY_RESULT(vkCreateDescriptorSetLayout(device.mHandle, &mDescriptorSetLayoutCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanPipelineLayoutCreator::VulkanPipelineLayoutCreator()
	: mPipelineLayoutCI{}
{
	mPipelineLayoutCI.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
}

VulkanPipelineLayoutCreator & VulkanPipelineLayoutCreator::addSetLayout(VkDescriptorSetLayout setLayout)
{
	mSetLayouts.push_back(setLayout);

	mPipelineLayoutCI.setLayoutCount = (uint32_t)mSetLayouts.size();
	mPipelineLayoutCI.pSetLayouts = mSetLayouts.data();

	return *this;
}

VulkanPipelineLayoutCreator & VulkanPipelineLayoutCreator::addPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size)
{
	VkPushConstantRange pushConstantRange;
	pushConstantRange.stageFlags = stageFlags;
	pushConstantRange.offset = offset;
	pushConstantRange.size = size;

	mPushConstantRanges.push_back(pushConstantRange);

	mPipelineLayoutCI.pushConstantRangeCount = (uint32_t)mPushConstantRanges.size();
	mPipelineLayoutCI.pPushConstantRanges = mPushConstantRanges.data();

	return *this;
}

VulkanPipelineLayout VulkanPipelineLayoutCreator::create(const VulkanDevice &device)
{
	VulkanPipelineLayout result;
	VK_VERIFY_RESULT(vkCreatePipelineLayout(device.mHandle, &mPipelineLayoutCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanDescriptorPoolCreator::VulkanDescriptorPoolCreator()
	: mDescriptorPoolCI{}
{
	mDescriptorPoolCI.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
}

VulkanDescriptorPoolCreator & VulkanDescriptorPoolCreator::setFlags(VkDescriptorPoolCreateFlags flags)
{
	mDescriptorPoolCI.flags = flags;

	return *this;
}

VulkanDescriptorPoolCreator & VulkanDescriptorPoolCreator::setMaxSets(uint32_t maxSets)
{
	mDescriptorPoolCI.maxSets = maxSets;

	return *this;
}

VulkanDescriptorPoolCreator & VulkanDescriptorPoolCreator::addPoolSize(VkDescriptorType type, uint32_t descriptorCount)
{
	VkDescriptorPoolSize poolSize;
	poolSize.type = type;
	poolSize.descriptorCount = descriptorCount;

	mPoolSizes.push_back(poolSize);

	mDescriptorPoolCI.poolSizeCount = (uint32_t)mPoolSizes.size();
	mDescriptorPoolCI.pPoolSizes = mPoolSizes.data();

	return *this;
}

VulkanDescriptorPool VulkanDescriptorPoolCreator::create(const VulkanDevice &device)
{
	VulkanDescriptorPool result;
	VK_VERIFY_RESULT(vkCreateDescriptorPool(device.mHandle, &mDescriptorPoolCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanSwapchainCreator::VulkanSwapchainCreator()
	: mSwapchainCI{}
{
	mSwapchainCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setFlags(VkSwapchainCreateFlagsKHR flags)
{
	mSwapchainCI.flags = flags;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setSurface(const VulkanSurface &surface)
{
	mSwapchainCI.surface = surface.mHandle;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setMinImageCount(uint32_t minImageCount)
{
	mSwapchainCI.minImageCount = minImageCount;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setFormat(VkFormat format, VkColorSpaceKHR colorSpace)
{
	mSwapchainCI.imageFormat = format;
	mSwapchainCI.imageColorSpace = colorSpace;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setExtent(uint32_t width, uint32_t height, uint32_t layers)
{
	mSwapchainCI.imageExtent.width = width;
	mSwapchainCI.imageExtent.height = height;
	mSwapchainCI.imageArrayLayers = layers;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setUsage(VkImageUsageFlags usage)
{
	mSwapchainCI.imageUsage = usage;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setSharingMode(VkSharingMode sharingMode)
{
	mSwapchainCI.imageSharingMode;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setPreTransform(VkSurfaceTransformFlagBitsKHR preTransform)
{
	mSwapchainCI.preTransform = preTransform;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setCompositeAlpha(VkCompositeAlphaFlagBitsKHR compositeAlpha)
{
	mSwapchainCI.compositeAlpha = compositeAlpha;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setPresentMode(VkPresentModeKHR presentMode)
{
	mSwapchainCI.presentMode = presentMode;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setClipped(VkBool32 clipped)
{
	mSwapchainCI.clipped = clipped;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::setOldSwapchain(const VulkanSwapchain &oldSwapchain)
{
	mSwapchainCI.oldSwapchain = oldSwapchain.mHandle;

	return *this;
}

VulkanSwapchainCreator & VulkanSwapchainCreator::addQueueFamily(uint32_t queueFamily)
{
	mQueueFamilies.push_back(queueFamily);

	mSwapchainCI.queueFamilyIndexCount = (uint32_t)mQueueFamilies.size();
	mSwapchainCI.pQueueFamilyIndices = mQueueFamilies.data();

	return *this;
}

VulkanSwapchain VulkanSwapchainCreator::create(const VulkanDevice &device)
{
	VulkanSwapchain result;
	VK_VERIFY_RESULT(vkCreateSwapchainKHR(device.mHandle, &mSwapchainCI, nullptr, &result.mHandle));
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanUpdateDescriptorSets::VulkanUpdateDescriptorSets()
{
}

VulkanUpdateDescriptorSets & VulkanUpdateDescriptorSets::addDescriptorSetWrite(const VulkanDescriptorSet &set, uint32_t binding, uint32_t arrayOffset, VkDescriptorType type)
{
	VkWriteDescriptorSet writeDescriptorSet = {};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.dstSet = set.mHandle;
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.dstArrayElement = arrayOffset;
	writeDescriptorSet.descriptorType = type;

	mWriteDescriptorSets.push_back(writeDescriptorSet);

	switch (type)
	{
	case VK_DESCRIPTOR_TYPE_SAMPLER:
	case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
	case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
	case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
	case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
		mDescriptorBufferInfoCollection.resize(mDescriptorBufferInfoCollection.size() + 1);
		break;
	case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
	case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
	case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
	case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
		mDescriptorBufferInfoCollection.resize(mDescriptorBufferInfoCollection.size() + 1);
		break;
	case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
	case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
		mTexelBufferViewCollection.resize(mTexelBufferViewCollection.size() + 1);
		break;
	}

	return *this;
}

VulkanUpdateDescriptorSets & VulkanUpdateDescriptorSets::writeImageDescriptor(const VulkanSampler &sampler, const VulkanImageView &imageView, VkImageLayout imageLayout)
{
	auto &writeDescriptorSet = mWriteDescriptorSets.back();

	assert(writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLER ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_IMAGE ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT);

	auto &descriptorImageInfos = mDescriptorImageInfoCollection.back();

	VkDescriptorImageInfo descriptorImageInfo;
	descriptorImageInfo.sampler = sampler.mHandle;
	descriptorImageInfo.imageView = imageView.mHandle;
	descriptorImageInfo.imageLayout = imageLayout;

	descriptorImageInfos.push_back(descriptorImageInfo);

	writeDescriptorSet.descriptorCount = (uint32_t)descriptorImageInfos.size();
	writeDescriptorSet.pImageInfo = descriptorImageInfos.data();

	return *this;
}

VulkanUpdateDescriptorSets & VulkanUpdateDescriptorSets::writeBufferDescriptor(const VulkanBuffer &buffer, VkDeviceSize offset, VkDeviceSize range)
{
	auto &writeDescriptorSet = mWriteDescriptorSets.back();

	assert(writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC);

	auto &descriptorBufferInfos = mDescriptorBufferInfoCollection.back();

	VkDescriptorBufferInfo descriptorBufferInfo;
	descriptorBufferInfo.buffer = buffer.mHandle;
	descriptorBufferInfo.offset = offset;
	descriptorBufferInfo.range = range;

	descriptorBufferInfos.push_back(descriptorBufferInfo);

	writeDescriptorSet.descriptorCount = (uint32_t)descriptorBufferInfos.size();
	writeDescriptorSet.pBufferInfo = descriptorBufferInfos.data();

	return *this;
}

VulkanUpdateDescriptorSets & VulkanUpdateDescriptorSets::writeTexelBufferViewDescriptor(const VulkanBufferView &texelBufferView)
{
	auto &writeDescriptorSet = mWriteDescriptorSets.back();

	assert(writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER ||
	       writeDescriptorSet.descriptorType == VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER);

	auto &texelBufferViews = mTexelBufferViewCollection.back();

	texelBufferViews.push_back(texelBufferView.mHandle);

	writeDescriptorSet.descriptorCount = (uint32_t)texelBufferViews.size();
	writeDescriptorSet.pTexelBufferView = texelBufferViews.data();

	return *this;
}

VulkanUpdateDescriptorSets & VulkanUpdateDescriptorSets::addDescriptorSetCopy(const VulkanDescriptorSet &srcSet, uint32_t srcBinding, uint32_t srcArrayOffset, const VulkanDescriptorSet &dstSet, uint32_t dstBinding, uint32_t dstArrayOffset, uint32_t descriptorCount)
{
	VkCopyDescriptorSet copyDescriptorSet = {};
	copyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
	copyDescriptorSet.srcSet = srcSet.mHandle;
	copyDescriptorSet.srcBinding = srcBinding;
	copyDescriptorSet.srcArrayElement = srcArrayOffset;
	copyDescriptorSet.dstSet = dstSet.mHandle;
	copyDescriptorSet.dstBinding = dstBinding;
	copyDescriptorSet.dstArrayElement = dstArrayOffset;
	copyDescriptorSet.descriptorCount = descriptorCount;

	return *this;
}

void VulkanUpdateDescriptorSets::execute(const VulkanDevice &device)
{
	vkUpdateDescriptorSets(device.mHandle, (uint32_t)mWriteDescriptorSets.size(), mWriteDescriptorSets.data(), (uint32_t)mCopyDescriptorSets.size(), mCopyDescriptorSets.data());
}

///////////////////////////////////////////////////////////////////////////////////////

VulkanRenderPassBeginInfo::VulkanRenderPassBeginInfo()
	: mRenderPassBeginInfo{}
{
	mRenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::setRenderPass(const VulkanRenderPass &renderPass)
{
	mRenderPassBeginInfo.renderPass = renderPass.mHandle;

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::setFramebuffer(const VulkanFramebuffer &framebuffer)
{
	mRenderPassBeginInfo.framebuffer = framebuffer.mHandle;

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::setRenderArea(int32_t x, int32_t y, uint32_t width, uint32_t height)
{
	mRenderPassBeginInfo.renderArea.offset.x = x;
	mRenderPassBeginInfo.renderArea.offset.y = y;
	mRenderPassBeginInfo.renderArea.extent.width = width;
	mRenderPassBeginInfo.renderArea.extent.height = height;

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::addClearColorF(float r, float g, float b, float a)
{
	VkClearValue clearValue = {};
	clearValue.color.float32[0] = r;
	clearValue.color.float32[1] = g;
	clearValue.color.float32[2] = b;
	clearValue.color.float32[3] = a;

	mClearValues.push_back(clearValue);

	mRenderPassBeginInfo.clearValueCount = (uint32_t)mClearValues.size();
	mRenderPassBeginInfo.pClearValues = mClearValues.data();

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::addClearColorI(int32_t r, int32_t g, int32_t b, int32_t a)
{
	VkClearValue clearValue = {};
	clearValue.color.int32[0] = r;
	clearValue.color.int32[1] = g;
	clearValue.color.int32[2] = b;
	clearValue.color.int32[3] = a;

	mClearValues.push_back(clearValue);

	mRenderPassBeginInfo.clearValueCount = (uint32_t)mClearValues.size();
	mRenderPassBeginInfo.pClearValues = mClearValues.data();

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::addClearColorU(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	VkClearValue clearValue = {};
	clearValue.color.uint32[0] = r;
	clearValue.color.uint32[1] = g;
	clearValue.color.uint32[2] = b;
	clearValue.color.uint32[3] = a;

	mClearValues.push_back(clearValue);

	mRenderPassBeginInfo.clearValueCount = (uint32_t)mClearValues.size();
	mRenderPassBeginInfo.pClearValues = mClearValues.data();

	return *this;
}

VulkanRenderPassBeginInfo & VulkanRenderPassBeginInfo::addClearDepthStencil(float depth, uint32_t stencil)
{
	VkClearValue clearValue = {};
	clearValue.depthStencil.depth = depth;
	clearValue.depthStencil.stencil = stencil;

	mClearValues.push_back(clearValue);

	mRenderPassBeginInfo.clearValueCount = (uint32_t)mClearValues.size();
	mRenderPassBeginInfo.pClearValues = mClearValues.data();

	return *this;
}

void VulkanRenderPassBeginInfo::execute(VulkanCommandBuffer &commandBuffer, VkSubpassContents contents)
{
	vkCmdBeginRenderPass(commandBuffer.mHandle, &mRenderPassBeginInfo, contents);
}
