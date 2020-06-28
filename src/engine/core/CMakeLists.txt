add_library(core STATIC window.cpp window.h)
set_target_properties(core PROPERTIES VERSION ${PROJECT_VERSION})
#install(FILES window.h DESTINATION ../../include/engine/core)