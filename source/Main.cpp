#ifdef USE_VULKAN
//#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan.hpp>
#endif

#ifdef USE_GLM
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif

#include <iostream>

#include "graphics/Graphics.h"
#include "graphics/GraphicsManager.h"
#include "utils/Timer.h"

#include "maths/Matrix4.h"

bool quit = false;
GraphicsManager* gmanager;

void Initialize()
{
    TIMER("Initialize");

    //gmanager = new GraphicsManager();
    //gmanager->Initialize();


	if (! Graphics::Initialize())
	{
		std::printf("You broke it, fam\n");
		exit(1);
	}
}

void Frame()
{
	// Update time here

	//gmanager->DrawFrame();
	Graphics::DrawFrame();
}

void RunOrDie()
{
	while (!quit)
	{
		Frame();
	}
}

int main()
{
#ifdef USE_VULKAN
	vk::ApplicationInfo appInfo = {};
	vk::InstanceCreateInfo createInfo = {};

	appInfo.setSType( vk::StructureType::eApplicationInfo );
	appInfo.setPNext( nullptr );
	appInfo.setPApplicationName( "Amber-Sun" );
	appInfo.setPEngineName( nullptr );
	appInfo.setEngineVersion( 1 );
	appInfo.setApiVersion( VK_MAKE_VERSION(1,0,33) );

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

#endif
#ifdef USE_GLM
	auto pers = glm::perspectiveRH<float>(glm::radians(60.0f), 1024/768, 0.1f, 100.0f);
	auto view = glm::lookAtRH(glm::vec3(4,3,3), glm::vec3(0, 0, 0),  glm::vec3(0, 1, 0));
	auto model = glm::mat4(1.0f);
	
	auto vm = view * model;
	auto mvp = pers * vm;

	auto v1 = mvp * glm::vec4(-1.0f, -1.0f, 0.0f, 1);
	auto v2 = mvp * glm::vec4(1.0f, -1.0f, 0.0f,  1);
	auto v3 = mvp * glm::vec4(0.0f, 1.0f, 0.0f,  1);

	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", pers[i][j]);
		std::printf("\n");
	}
	
	std::printf("-----------\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", view[i][j]);
		std::printf("\n");
	}
	std::printf("-----------\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", model[i][j]);
		std::printf("\n");
	}
	std::printf("VP Matrix:\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", vm[i][j]);
		std::printf("\n");
	}*/
	std::printf("-----------\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::printf("%f:", mvp[i][j]);
		std::printf("\n");
	}
	
	std::printf("-----------\n");
	std::printf("%f:%f:%f:%f\n", v1[0], v1[1], v1[2], v1[3]);
	std::printf("%f:%f:%f:%f\n", v2[0], v2[1], v2[2], v2[3]);
	std::printf("%f:%f:%f:%f\n", v3[0], v3[1], v3[2], v3[3]);
# endif
		
	Initialize();
	RunOrDie();
	
	return 0;
}