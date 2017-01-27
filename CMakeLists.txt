project (Amber-Sun C CXX)
cmake_minimum_required (VERSION 2.6)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

link_directories($ENV{VK_SDK_PATH}/bin)

add_subdirectory(source)
add_subdirectory(source/sim)
add_subdirectory(source/utils)
