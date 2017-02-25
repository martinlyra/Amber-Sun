#define GLFW_INCLUDE_VULKAN
//#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan\vulkan.hpp>
#include <GLFW\glfw3.h>

#include <iostream>

int main()
{
	vk::ApplicationInfo appInfo = {};
	vk::InstanceCreateInfo createInfo = {};

	appInfo.setSType( vk::StructureType::eApplicationInfo );
	appInfo.setPNext( nullptr );
	appInfo.setPApplicationName( "Amber-Sun" );
	appInfo.setPEngineName( nullptr );
	appInfo.setEngineVersion( 1 );
	appInfo.setApiVersion( VK_VERSION_1_0 );

	createInfo.setSType( vk::StructureType::eInstanceCreateInfo );
	createInfo.setPNext( nullptr );
	createInfo.setFlags( vk::InstanceCreateFlags() );
	createInfo.setPApplicationInfo( &appInfo );
	createInfo.setEnabledExtensionCount( 0 );
	createInfo.setPpEnabledExtensionNames( nullptr );
	createInfo.setEnabledLayerCount( 0 );
	createInfo.setPpEnabledLayerNames( nullptr );

	auto instance = vk::createInstance( createInfo );

	auto device = instance.enumeratePhysicalDevices();

	std::printf( "%u device(s) found\n", device.size() );
	for ( int i = 0; i < device.size(); i++ )
		std::printf( "%s\n", device[i].getProperties().deviceName );

	uint32_t extensionCount;

	vk::enumerateInstanceExtensionProperties( nullptr, &extensionCount, nullptr );

	std::printf("%u extensions supported\n", extensionCount);

	instance.destroy();

	return 0;
}