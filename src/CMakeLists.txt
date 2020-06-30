add_subdirectory(engine/math)
add_subdirectory(engine/core)
add_subdirectory(engine/demo)

if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

#    set(Boost_USE_STATIC_LIBS ON)
    add_definitions(-DBOOST_LOG_DYN_LINK)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(engine)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(../lib/glfw-3.3.2 ../lib/assimp-3.3.1/include ../lib/freetype-2.10.0/include ../lib/soil/src)
include_directories(../lib/glew/include)


#set(FOO_SOURCE_DIR /glew-2.1.0/src)
#set(FOO_BINARY_DIR /glew-2.1.0/bin)
#set(FOO_INSTALL_DIR /glew-2.1.0/install)
#message(">${FOO_SOURCE_DIR}<")
#message(">${FOO_BINARY_DIR}<")
##
#include(ExternalProject)
#include(GNUInstallDirs)
#ExternalProject_Add(GLEW_EXTERNAL
#        SOURCE_DIR "${FOO_SOURCE_DIR}"
#        BINARY_DIR "${FOO_BINARY_DIR}"
#        INSTALL_DIR "${FOO_INSTALL_DIR}"
#        CMAKE_ARGS "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}"
#        "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}"
#        "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
#        "-DCMAKE_INSTALL_PREFIX=${FOO_INSTALL_DIR}"
#        )
#
#add_dependencies(foo GLEW_EXTERNAL)
#set(foo_LIBRARY
#        "${FOO_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}foo${CMAKE_STATIC_LIBRARY_SUFFIX}")
#set(foo_INCLUDE_DIR "${FOO_INSTALL_DIR}/include")
#


add_executable(GraphicEngine main.cpp)

#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/res)
#message("${OPENGL_LIBRARIES}")
#message(">${GLEW_LIBRARIES}<")
#message("${PROJECT_SOURCE_DIR}")

target_link_libraries(GraphicEngine ${OPENGL_LIBRARIES})
target_link_libraries(GraphicEngine ${Boost_LIBRARIES} pthread)
target_link_libraries(GraphicEngine glfw assimp freetype SOIL libglew_shared)
target_link_libraries(GraphicEngine math core demo)
