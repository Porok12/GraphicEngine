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

add_library(gui STATIC Primitives/PrimitiveRenderer.cpp Primitives/PrimitiveRenderer.h UIRenderer.cpp UIRenderer.h Primitives/Rectangle.h UIComponent.h UIComposite.cpp UIComposite.h UIButton.cpp UIButton.h UIFrame.cpp UIFrame.h UIFrameDecorator.cpp UIFrameDecorator.h UIStage.cpp UIStage.h ../demo/UIStageManager.cpp ../demo/UIStageManager.h UISlider.cpp UISlider.h UISelectBox.cpp UISelectBox.h UICheckBox.cpp UICheckBox.h UITextBox.cpp UITextBox.h Utils/Utils.h UILabel.cpp UILabel.h Utils/Constraint.cpp Utils/Constraint.h)

set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(gui ${Boost_LIBRARIES})
target_link_libraries(gui assimp SOIL freetype glfw ${GLEW_LIB_NAME})
target_link_libraries(gui math core)

#
#set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
##install(FILES gui.h DESTINATION ../../include/engine/core)