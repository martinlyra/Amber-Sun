cmake_minimum_required (VERSION 3.4)

#Enable support for more modern C/C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(USE_VULKAN false)
set(USE_CONAN false)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

message(STATUS "${GLFW_FOUND}")

if (NOT ${GLFW_FOUND})
	message(FATAL_ERROR "GLFW3 was not found! Do you have it installed?")
endif()

#find_package(glfw3 3.2 REQUIRED)

project (Amber-Sun C CXX)

if (${USE_CONAN})
	include(utilities/conan/conanbuildinfo.cmake)
	conan_basic_setup()
endif()
	
if (${USE_VULKAN})
	link_directories($ENV{VK_SDK_PATH}/bin)
endif()
	
add_subdirectory(source/shared)
add_subdirectory(source/maths)
add_subdirectory(source/utils)

add_subdirectory(source/renderer)
add_subdirectory(source/graphics)

add_subdirectory(source/sim)

add_subdirectory(source/core)

add_subdirectory(source)