
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdlib>

#include "VulkanUtils.h"

void initializeVulkan()
{
	auto instance = VulkanInstanceCreator()
		.setApplication("Vulkan Learning", VK_MAKE_VERSION(1,0,0))
		.setEngine("Vulkan Learning", VK_MAKE_VERSION(1,0,0))
		.setApiVersion(VK_MAKE_VERSION(1,1,0))
		.addEnabledLayer("VK_LAYER_LUNARG_standard_validation")
		.addEnabledExtension("VK_EXT_debug_utils")
		.create();

	auto physicalDevices = instance.getPhysicalDevices();
	auto extensions = physicalDevices[0].getExtensions();

	auto device = VulkanDeviceCreator()
		.addQueueFamily(0)
			.addQueueFamilyQueue(1.f)
		.create(physicalDevices[0]);

	auto swapchain = VulkanSwapchainCreator();

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

	initializeVulkan();

	return 0;
}
