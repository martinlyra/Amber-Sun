set (PROJECT_NAME Amber-Sun.Simulated)
file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
