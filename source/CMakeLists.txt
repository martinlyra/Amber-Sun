set(PROJECT_NAME Amber-Sun)

file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ..)

target_link_libraries(Amber-Sun Amber-Sun.Graphics)

if (${USE_CONAN})
	target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
endif()
if (${USE_VULKAN})
	target_link_libraries(${PROJECT_NAME} vulkan-1)
	target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VK_SDK_PATH}/include)
endif()