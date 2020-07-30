set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost COMPONENTS log_setup log thread date_time filesystem system REQUIRED)

#add_definitions(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(
        ../../../lib/glew/include
        ../../../lib/assimp-3.3.1/include
        ../../../lib/soil/src
        ../../../lib/freetype-2.10.0/include)
include_directories(../)

add_library(demo STATIC MenuStage.cpp MenuStage.h MeshStage.cpp MeshStage.h ParticlesStage.cpp ParticlesStage.h LightStage.cpp LightStage.h ShadingStage.cpp ShadingStage.h TextureStage.cpp TextureStage.h DitheringStage.cpp DitheringStage.h BlurStage.cpp BlurStage.h)

set_target_properties(demo PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(demo ${Boost_LIBRARIES})
target_link_libraries(demo assimp SOIL freetype glfw)
target_link_libraries(demo math core gui)

#
#set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
##install(FILES gui.h DESTINATION ../../include/engine/core)