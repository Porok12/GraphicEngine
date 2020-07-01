add_library(gui STATIC demo.cpp)
set_target_properties(gui PROPERTIES VERSION ${PROJECT_VERSION})
#install(FILES gui.h DESTINATION ../../include/engine/core)