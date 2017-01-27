file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_executable(Amber-Sun ${SRC_FILES})

target_link_libraries(Amber-Sun ${CONAN_LIBS})
target_link_libraries(Amber-Sun vulkan-1)
target_include_directories(Amber-Sun PRIVATE $ENV{VK_SDK_PATH}/include)