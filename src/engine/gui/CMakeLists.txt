find_package(Boost COMPONENTS log log_setup thread date_time filesystem system REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../../lib/glew/include ../../../lib/assimp-3.3.1/include ../../../lib/soil/src ../../../lib/freetype-2.10.0/include)
include_directories(../)

add_library(gui STATIC Primitives/PrimitiveRenderer.cpp Primitives/PrimitiveRenderer.h UIRenderer.cpp UIRenderer.h Primitives/Rectangle.h UIComponent.cpp UIComponent.h UIComposite.cpp UIComposite.h UIButton.cpp UIButton.h UIFrame.cpp UIFrame.h UIFrameDecorator.cpp UIFrameDecorator.h UIStage.cpp UIStage.h UIStageManager.cpp UIStageManager.h MenuStage.cpp MenuStage.h MeshStage.cpp MeshStage.h ParticlesStage.cpp ParticlesStage.h LightStage.cpp LightStage.h)

set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(gui ${Boost_LIBRARIES})
target_link_libraries(gui assimp SOIL freetype glfw libglew_shared)
target_link_libraries(gui math core)

#
#set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
##install(FILES gui.h DESTINATION ../../include/engine/core)