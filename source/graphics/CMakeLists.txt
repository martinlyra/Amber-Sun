set (PROJECT_NAME Amber-Sun.Graphics)
file(GLOB SRC_FILES
	"*.h"
	"*.c"
	"*.cpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} dl)
target_link_libraries(${PROJECT_NAME} Amber-Sun.Maths)

target_include_directories(${PROJECT_NAME} PRIVATE ..)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})

if (${USE_CONAN})
	target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
endif()
if (${USE_VULKAN})
	target_link_libraries(${PROJECT_NAME} vulkan-1)
	target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VK_SDK_PATH}/include)
endif()
