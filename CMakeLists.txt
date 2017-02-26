project (Amber-Sun C CXX)
cmake_minimum_required (VERSION 2.6)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

link_directories($ENV{VK_SDK_PATH}/bin)

add_subdirectory(source/shared)
add_subdirectory(source/maths)
add_subdirectory(source/utils)

add_subdirectory(source/renderer)
add_subdirectory(source/graphics)

add_subdirectory(source/sim)

add_subdirectory(source/core)

add_subdirectory(source)
