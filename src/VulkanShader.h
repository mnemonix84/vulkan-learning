#pragma once

#ifndef VULKAN_SHADER_H
#define VULKAN_SHADER_H

#include "VulkanUtils.h"

class VulkanDevice;

class VulkanShaderModule
{
public:

	DELETE_COPY_CTOR_ASSIGN(VulkanShaderModule)
	
	VulkanShaderModule();
	~VulkanShaderModule();

	VulkanShaderModule(VulkanShaderModule &&other);
	VulkanShaderModule & operator=(VulkanShaderModule &&other);

	static VulkanShaderModule createFromSpirvFile(const VulkanDevice &device, const char *filename);
	static VulkanShaderModule createFromGlslFile(const VulkanDevice &device, const char *filename);

	VkShaderModule mHandle;
	VkShaderStageFlagBits mStage;
};

#endif
