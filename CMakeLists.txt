macro(get_source_files TARGET_VAR PATH)
	file(GLOB_RECURSE ${TARGET_VAR}
			RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
			#"${CMAKE_CURRENT_SOURCE_DIR}/${PATH}/*.h"
			"${CMAKE_CURRENT_SOURCE_DIR}/${PATH}/*.c"
			"${CMAKE_CURRENT_SOURCE_DIR}/${PATH}/*.cpp")
endmacro(get_source_files)

cmake_minimum_required (VERSION 3.4)

#Enable support for more modern C/C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_STANDARD 17)

set(USE_VULKAN false)
set(USE_CONAN false)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW glfw3)

message(STATUS "Source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Binary directory: ${CMAKE_BINARY_DIR}")

#message(STATUS "${GLFW_INCLUDE_DIRS}")
#message(STATUS "${GLFW_LIBRARY_DIRS}")

# Somehow, either it is CMAKE or/and Pkgconfig who is/are kinda retarded
# when handling paths that contain spaces, seeing them a list of entries, inserting
# semicolons in between. Currently limited to Windows, change the condition
# if it would appear on Linux (or Mac) as well.
if (WIN32)
	STRING(REPLACE ";" " " GLFW_INCLUDE_DIRS "${GLFW_INCLUDE_DIRS}")
	STRING(REPLACE ";" " " GLFW_LIBRARY_DIRS "${GLFW_LIBRARY_DIRS}")
endif()
message(STATUS "${GLFW_INCLUDE_DIRS}")
message(STATUS "${GLFW_INCLUDE_DIRS}")

if (NOT GLFW_FOUND)
	message(FATAL_ERROR "GLFW3 was not found! Do you have it installed?")
endif()

#find_package(glfw3 3.2 REQUIRED)

project (Amber-Sun C CXX)

get_source_files(MAIN "source")
#get_source_files(CORE "source/core")
#get_source_files(GRAPHICS "source/graphics")
#get_source_files(MATHS "source/maths")
#get_source_files(RENDERER "source/renderer")
#get_source_files(SHARED "source/shared")
#get_source_files(SIM "source/sim")
#get_source_files(UTILS "source/utils")

source_group(main FILES ${MAIN})
#source_group(core FILES ${CORE})
#source_group(graphics FILES ${GRAPHICS})
#source_group(maths FILES ${MATHS})

set(PROJECT_NAME Amber-Sun)
add_executable(${PROJECT_NAME} ${MAIN})

target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)

target_include_directories(${PROJECT_NAME} PRIVATE source)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY_DIRS}/libglfw3.a)

# Copy non-source binary files from template folder to binary folder
add_custom_target(copy_directory
		TARGET ${PROJECT_NAME}
		COMMENT "Copying template files to ${CMAKE_BINARY_DIR}")
add_custom_command(
		TARGET ${PROJECT_NAME}
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_CURRENT_SOURCE_DIR}/template/
				${CMAKE_BINARY_DIR}/
)

#if (${USE_CONAN})
#	include(utilities/conan/conanbuildinfo.cmake)
#	conan_basic_setup()
#endif()
	
#if (${USE_VULKAN})
#	link_directories($ENV{VK_SDK_PATH}/bin)
#endif()
	
#add_subdirectory(source/shared)
#add_subdirectory(source/maths)
#add_subdirectory(source/utils)

#add_subdirectory(source/renderer)
#add_subdirectory(source/graphics)

#add_subdirectory(source/sim)

#add_subdirectory(source/core)

#add_subdirectory(source)