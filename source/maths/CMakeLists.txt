set (PROJECT_NAME Amber-Sun.Maths)
file(GLOB SRC_FILES
	"*.h"
	"*.cpp"
)

add_library(${PROJECT_NAME} ${SRC_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
