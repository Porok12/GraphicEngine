cmake_minimum_required(VERSION 3.10)
project(GraphicEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX bin)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(test)
add_subdirectory(src)

add_subdirectory(lib/glfw-3.3.2)
add_subdirectory(lib/assimp-3.3.1)
add_subdirectory(lib/freetype-2.10.0)
add_subdirectory(lib/soil)

include_directories(${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} glfw)
include_directories(lib/glfw-3.3.2 lib/assimp-3.3.1/include lib/freetype-2.10.0/include lib/soil/src)
#include_directories(src/math src/core)

add_executable(GraphicEngine main.cpp)

target_link_libraries(GraphicEngine ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(GraphicEngine glfw assimp freetype SOIL)

install(TARGETS GraphicEngine DESTINATION lib)