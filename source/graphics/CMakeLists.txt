set (PROJECT_NAME Amber-Sun.Graphics)
file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} vulkan-1)
target_include_directories(${PROJECT_NAME} PRIVATE $ENV{VK_SDK_PATH}/include)
