set(CORE_SRCS
        ${CMAKE_SOURCE_DIR}/src/core/window.cpp
        ${CMAKE_SOURCE_DIR}/src/core/Camera.cpp
        ${CMAKE_SOURCE_DIR}/src/core/FreeCamera.cpp
        ${CMAKE_SOURCE_DIR}/src/core/InputHandler.cpp

        ${CMAKE_SOURCE_DIR}/src/core/utils/ResourceLoader.cpp

#        ${CMAKE_SOURCE_DIR}/src/core/text/Character.h
        ${CMAKE_SOURCE_DIR}/src/core/text/Font.cpp
        ${CMAKE_SOURCE_DIR}/src/core/text/FontLoader.cpp
        ${CMAKE_SOURCE_DIR}/src/core/text/FontRenderer.cpp

        ${CMAKE_SOURCE_DIR}/src/core/shaders/Shader.h
        ${CMAKE_SOURCE_DIR}/src/core/shaders/Shader.cpp
        ${CMAKE_SOURCE_DIR}/src/core/shaders/ShaderLoader.cpp
        ${CMAKE_SOURCE_DIR}/src/core/shaders/ShaderProgram.cpp

        ${CMAKE_SOURCE_DIR}/src/core/particles/ParticleRenderer.cpp
        ${CMAKE_SOURCE_DIR}/src/core/particles/ParticleGenerator.cpp

#        ${CMAKE_SOURCE_DIR}/src/core/models/Mesh.h
        ${CMAKE_SOURCE_DIR}/src/core/models/Mesh.cpp
        ${CMAKE_SOURCE_DIR}/src/core/models/Model.cpp
        ${CMAKE_SOURCE_DIR}/src/core/models/ModelRenderer.cpp

        ${CMAKE_SOURCE_DIR}/src/core/light/Light.cpp
        ${CMAKE_SOURCE_DIR}/src/core/light/DirectionalLight.cpp
        ${CMAKE_SOURCE_DIR}/src/core/light/PointLight.cpp
        ${CMAKE_SOURCE_DIR}/src/core/light/SpotLight.cpp

        ${CMAKE_SOURCE_DIR}/src/core/effects/Bloom.cpp

        ${CMAKE_SOURCE_DIR}/src/core/algorithm/AreaFill.cpp
        ${CMAKE_SOURCE_DIR}/src/core/algorithm/Raycaster.cpp

        ${CMAKE_SOURCE_DIR}/src/core/algorithm/palette/FixedPalette.cpp
        ${CMAKE_SOURCE_DIR}/src/core/algorithm/palette/MedianCut.cpp
        ${CMAKE_SOURCE_DIR}/src/core/algorithm/palette/Octree.cpp

        ${CMAKE_SOURCE_DIR}/src/core/algorithm/Rasterisation/Bresenham.cpp

#        ${CMAKE_SOURCE_DIR}/src/core/definitions.h
#        ${CMAKE_SOURCE_DIR}/src/core/definitions.cpp
#        ${CMAKE_SOURCE_DIR}/src/core/InputHandler.h
#        ${CMAKE_SOURCE_DIR}/src/core/window.h

        ${CMAKE_SOURCE_DIR}/src/core/algorithm/VertexGenerator.cpp
        ${CMAKE_SOURCE_DIR}/src/core/models/InstancedMesh.cpp
        ${CMAKE_SOURCE_DIR}/src/core/models/InstancedModel.cpp
#        ${CMAKE_SOURCE_DIR}/src/core/models/InstancedRenderer.cpp
        )