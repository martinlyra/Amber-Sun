#define GLFW_INCLUDE_VULKAN
#include <vulkan\vulkan.hpp>
#include <GLFW\glfw3.h>

#include <iostream>

int main()
{
	vk::InstanceCreateInfo createInfo = {};

	uint32_t extensionCount;

	vk::enumerateInstanceExtensionProperties( nullptr, &extensionCount, nullptr );

	std::printf("%u extensions supported\n", extensionCount);

	return 0;
}