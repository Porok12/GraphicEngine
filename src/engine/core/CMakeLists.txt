find_package(Boost COMPONENTS log log_setup thread date_time filesystem system REQUIRED)

add_definitions(-DBOOST_LOG_DYN_LINK)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../../lib/glew/include ../../../lib/assimp-3.3.1/include ../../../lib/soil/src ../../../lib/freetype-2.10.0/include)
include_directories(../)

add_library(core STATIC
        window.cpp window.h
        exception/InitException.h
        shaders/Shader.cpp shaders/Shader.h shaders/ShaderLoader.cpp shaders/ShaderLoader.h shaders/ShaderProgram.cpp shaders/ShaderProgram.h utils/ResourceLoader.cpp utils/ResourceLoader.h models/Mesh.cpp models/Mesh.h models/Model.cpp models/Model.h text/FontLoader.cpp text/FontLoader.h text/FontRenderer.cpp text/FontRenderer.h text/Character.h text/Font.cpp text/Font.h InputHandler.cpp InputHandler.h particles/Particle.h particles/ParticleGenerator.cpp particles/ParticleGenerator.h particles/ParticleRenderer.cpp particles/ParticleRenderer.h Camera.cpp Camera.h models/ModelRenderer.cpp models/ModelRenderer.h light/PointLight.cpp light/PointLight.h light/DirectionalLight.cpp light/DirectionalLight.h light/SpotLight.cpp light/SpotLight.h light/Light.cpp light/Light.h light/Materials.h  effects/Bloom.cpp effects/Bloom.h algorithm/palette/PaletteAlghorithm.h algorithm/palette/MedianCut.cpp algorithm/palette/MedianCut.h algorithm/palette/Octree.cpp algorithm/palette/Octree.h algorithm/palette/FixedPalette.cpp algorithm/palette/FixedPalette.h)

set_target_properties(core PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(core ${Boost_LIBRARIES})
target_link_libraries(core assimp SOIL freetype glfw libglew_shared)
target_link_libraries(core math)
#install(FILES window.h DESTINATION ../../include/engine/core)