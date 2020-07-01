add_subdirectory(engine/math)
add_subdirectory(engine/core)
add_subdirectory(engine/gui)

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



## Compilation step for static resources
#FUNCTION(ADD_RESOURCES out_var)
#    SET(result)
#    FOREACH(in_f ${ARGN})
#        FILE(RELATIVE_PATH src_f ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${in_f})
#        SET(out_f "${PROJECT_BINARY_DIR}/${in_f}.o")
#        ADD_CUSTOM_COMMAND(OUTPUT ${out_f}
#                COMMAND ld -r -b binary -o ${out_f} ${src_f}
#                DEPENDS ${in_f}
#                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#                COMMENT "Building GLSL object ${out_f}"
#                VERBATIM
#                )
#        LIST(APPEND result ${out_f})
#    ENDFOREACH()
#    SET(${out_var} "${result}" PARENT_SCOPE)
#ENDFUNCTION()
#
## A simple program that uses resources
#ADD_RESOURCES(someResources ../res/shaders/basic.frag)


add_executable(GraphicEngine main.cpp ${someResources})

target_link_libraries(GraphicEngine ${OPENGL_LIBRARIES})
target_link_libraries(GraphicEngine ${Boost_LIBRARIES})# pthread)
target_link_libraries(GraphicEngine glfw assimp freetype SOIL libglew_shared)
target_link_libraries(GraphicEngine math core gui)

#add_custom_command(
#        OUTPUT res
#        COMMAND embedfile foo foo.rsrc
#        DEPENDS foo.rsrc)

add_custom_command(TARGET GraphicEngine PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:GraphicEngine>/../res)

#add_custom_command(TARGET foo POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#        ${CMAKE_SOURCE_DIR}/test/input.txt
#        ${CMAKE_CURRENT_BINARY_DIR}/input.txt)

#file(GLOB MY_FILES "*.frag")
#file(COPY ${MY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
