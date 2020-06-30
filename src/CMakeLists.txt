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

add_executable(GraphicEngine main.cpp)

target_link_libraries(GraphicEngine ${OPENGL_LIBRARIES})
target_link_libraries(GraphicEngine ${Boost_LIBRARIES})# pthread)
target_link_libraries(GraphicEngine glfw assimp freetype SOIL libglew_shared)
target_link_libraries(GraphicEngine math core demo)
