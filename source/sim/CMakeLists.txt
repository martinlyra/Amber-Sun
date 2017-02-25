set (PROJECT_NAME Amber-Sun.Simulated)
file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} Amber-Sun.Shared)
target_include_directories(${PROJECT_NAME} PRIVATE ..)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
