add_library(math STATIC vector.cpp vector.h)
set_target_properties(math PROPERTIES VERSION ${PROJECT_VERSION})
#install(FILES vector.h DESTINATION ../../include/engine/math)