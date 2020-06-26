cmake_minimum_required(VERSION 3.10)
project(GraphicEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX bin)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} glfw)

add_executable(GraphicEngine main.cpp)

target_link_libraries(GraphicEngine ${Boost_LIBRARIES} ${OPENGL_LIBRARIES} glfw)

install(TARGETS GraphicEngine DESTINATION lib)