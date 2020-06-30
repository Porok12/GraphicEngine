cmake_minimum_required(VERSION 3.10)
project(GraphicEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_THREAD_PREFER_PTHREAD True)
set(CMAKE_INSTALL_PREFIX bin)

option(BUILD_TESTS "Build test programs" ON)

find_package(Boost COMPONENTS log log_setup thread date_time filesystem system REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(lib/glfw-3.3.2)
add_subdirectory(lib/assimp-3.3.1)
add_subdirectory(lib/freetype-2.10.0)
add_subdirectory(lib/soil)
add_subdirectory(lib/glew)
add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(test)
endif(BUILD_TESTS)
