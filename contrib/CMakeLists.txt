set(CONTRIB_PATH ${GRAPHIC_ENGINE_SOURCE_DIR}/contrib)

# glew
execute_process(COMMAND git submodule update --init -- contrib/glew-cmake
        WORKING_DIRECTORY ${GRAPHIC_ENGINE_SOURCE_DIR})

add_subdirectory(${CONTRIB_PATH}/glew-cmake)
message("glew subdirectory added")

# glfw
execute_process(COMMAND git submodule update --init -- contrib/glfw
        WORKING_DIRECTORY ${GRAPHIC_ENGINE_SOURCE_DIR})

add_subdirectory(${CONTRIB_PATH}/glfw)
message("glfw subdirectory added")


# assimp
execute_process(COMMAND git submodule update --init -- contrib/assimp
        WORKING_DIRECTORY ${GRAPHIC_ENGINE_SOURCE_DIR})

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)
#set(BUILD_SHARED_LIBS ON)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT FALSE CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)
set(ASSIMP_LIBRARY_DIRS "${GRAPHIC_ENGINE_SOURCE_DIR}/contrib/assimp/code" "${GRAPHIC_ENGINE_BINARY_DIR}/contrib/assimp/code")
set(ASSIMP_INCLUDE_DIRS "${GRAPHIC_ENGINE_SOURCE_DIR}/contrib/assimp/include" "${GRAPHIC_ENGINE_BINARY_DIR}/contrib/assimp/include")
include_directories(${ASSIMP_INCLUDE_DIRS})
add_subdirectory(${CONTRIB_PATH}/assimp)
message("assimp subdirectory added")


# freetype
execute_process(COMMAND git submodule update --init -- contrib/freetype
        WORKING_DIRECTORY ${GRAPHIC_ENGINE_SOURCE_DIR})

add_subdirectory(${CONTRIB_PATH}/freetype)
include_directories(${CONTRIB_PATH}/freetype/include) #TODO: fix this
message("freetype subdirectory added")


# soil
execute_process(COMMAND git submodule update --init -- contrib/soil
        WORKING_DIRECTORY ${GRAPHIC_ENGINE_SOURCE_DIR})

add_subdirectory(${CONTRIB_PATH}/soil)
message("soil subdirectory added")