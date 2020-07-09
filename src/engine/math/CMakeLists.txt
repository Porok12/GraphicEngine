add_library(math STATIC Vec2.cpp Vec2.h Vec3.cpp Vec3.h Vec4.cpp Vec4.h Mat4.cpp Mat4.h Vector.cpp Vector.h Matrix.cpp Matrix.h)
set_target_properties(math PROPERTIES VERSION ${PROJECT_VERSION})
#install(FILES vector.h DESTINATION ../../include/engine/math)