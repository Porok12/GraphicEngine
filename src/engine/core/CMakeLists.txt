include_directories(../../../lib/glew/include)
add_library(core STATIC
        window.cpp window.h
        exception/InitException.h
        shaders/Shader.cpp shaders/Shader.h shaders/ShaderLoader.cpp shaders/ShaderLoader.h)
set_target_properties(core PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(core GLEW)
#install(FILES window.h DESTINATION ../../include/engine/core)