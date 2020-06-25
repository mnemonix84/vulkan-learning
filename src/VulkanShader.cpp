
#include "VulkanShader.h"

#include "shaderc/shaderc.h"

#include <vector>
#include <cassert>

static std::vector<char> loadFromFile(const char *filename)
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

static std::vector<char> compileGlslFileToSpirvBinary(const char *filename)
{
	shaderc_shader_kind shaderKind;
	const char *fileExtension = strrchr(filename, '.');
	assert(fileExtension);

	if (fileExtension)
	{
		if (strcmp(fileExtension, ".vs") == 0)
			shaderKind = shaderc_glsl_vertex_shader;
		else if (strcmp(fileExtension, ".gs") == 0)
			shaderKind = shaderc_glsl_geometry_shader;
		else if (strcmp(fileExtension, ".tcs") == 0)
			shaderKind = shaderc_glsl_tess_control_shader;
		else if (strcmp(fileExtension, ".tes") == 0)
			shaderKind = shaderc_glsl_tess_evaluation_shader;
		else if (strcmp(fileExtension, ".fs") == 0)
			shaderKind = shaderc_glsl_fragment_shader;
		else if (strcmp(fileExtension, ".cs") == 0)
			shaderKind = shaderc_glsl_compute_shader;
		else
			assert(!"GLSL shader file has no supported extension.");
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

static VulkanShaderModule createShaderModule(const VulkanDevice &device, uint32_t *code, size_t size)
{
	VkShaderModuleCreateInfo shaderModuleCI = {};
	shaderModuleCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCI.codeSize = size;
	shaderModuleCI.pCode = code;

	VulkanShaderModule shaderModule;
	VK_VERIFY_RESULT(vkCreateShaderModule(device.mHandle, &shaderModuleCI, nullptr, &shaderModule.mHandle));
	return shaderModule;
}

VulkanShaderModule::VulkanShaderModule()
	: mHandle(VK_NULL_HANDLE)
{
}

VulkanShaderModule::~VulkanShaderModule()
{
}

VulkanShaderModule::VulkanShaderModule(VulkanShaderModule &&other)
	: mHandle(other.mHandle)
{
	other.mHandle = VK_NULL_HANDLE;
}

VulkanShaderModule & VulkanShaderModule::operator=(VulkanShaderModule &&other)
{
	std::swap(mHandle, other.mHandle);
	return *this;
}

VulkanShaderModule VulkanShaderModule::createFromSpirvFile(const VulkanDevice &device, const char *filename)
{
	auto byteCode = loadFromFile(filename);
	return createShaderModule(device, (uint32_t *)byteCode.data(), byteCode.size());
}

VulkanShaderModule VulkanShaderModule::createFromGlslFile(const VulkanDevice &device, const char *filename)
{
	auto byteCode = compileGlslFileToSpirvBinary(filename);
	return createShaderModule(device, (uint32_t *)byteCode.data(), byteCode.size());
}
