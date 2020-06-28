add_subdirectory(engine/math)
add_subdirectory(engine/core)

include_directories(engine)
include_directories(${Boost_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
include_directories(../lib/glfw-3.3.2 ../lib/assimp-3.3.1/include ../lib/freetype-2.10.0/include ../lib/soil/src)

add_executable(GraphicEngine main.cpp)

target_link_libraries(GraphicEngine ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})
target_link_libraries(GraphicEngine glfw assimp freetype SOIL)
target_link_libraries(GraphicEngine math core)