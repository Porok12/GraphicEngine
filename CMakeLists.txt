set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_minimum_required(VERSION 3.10)

project(GraphicEngine
        VERSION 1.1.0
        DESCRIPTION "Graphic engine library"
#        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_THREAD_PREFER_PTHREAD True)
set(CMAKE_INSTALL_PREFIX bin)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")

option(ENGINE_BUILD_TESTS "Build test programs" ON)
option(ENGINE_BUILD_DEMO "Build demo" ON)
option(RNGINE_BUILD_SHARED_LIBS ON)

set(Boost_USE_STATIC_LIBS   ON)

find_package(Boost 1.55.0 REQUIRED COMPONENTS thread date_time filesystem system REQUIRED)
find_package(OpenGL REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

if(OpenGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
endif()

include(contrib/CMakeLists.txt)

add_subdirectory(src)

if(ENGINE_BUILD_TESTS)
    add_subdirectory(test)
endif()

if(ENGINE_BUILD_DEMO)
    add_subdirectory(src/demo)
endif()
