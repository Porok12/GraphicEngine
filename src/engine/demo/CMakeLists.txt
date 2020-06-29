add_library(demo STATIC demo.cpp)
set_target_properties(demo PROPERTIES VERSION ${PROJECT_VERSION})
#install(FILES demo.h DESTINATION ../../include/engine/core)