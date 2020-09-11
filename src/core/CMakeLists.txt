set(CORE_PATH ${GRAPHIC_ENGINE_SOURCE_DIR}/src)

set(CORE_SRCS
        ${CORE_PATH}/core/window.cpp
        ${CORE_PATH}/core/Camera.cpp
        ${CORE_PATH}/core/FreeCamera.cpp
        ${CORE_PATH}/core/InputHandler.cpp

        ${CORE_PATH}/core/utils/ResourceLoader.cpp

        ${CORE_PATH}/core/text/Font.cpp
        ${CORE_PATH}/core/text/FontLoader.cpp
        ${CORE_PATH}/core/text/FontRenderer.cpp

        ${CORE_PATH}/core/shaders/Shader.h
        ${CORE_PATH}/core/shaders/Shader.cpp
        ${CORE_PATH}/core/shaders/ShaderLoader.cpp
        ${CORE_PATH}/core/shaders/ShaderProgram.cpp

        ${CORE_PATH}/core/particles/ParticleRenderer.cpp
        ${CORE_PATH}/core/particles/ParticleGenerator.cpp

        ${CORE_PATH}/core/models/Mesh.cpp
        ${CORE_PATH}/core/models/Model.cpp
        ${CORE_PATH}/core/models/ModelRenderer.cpp

        ${CORE_PATH}/core/light/Light.cpp
        ${CORE_PATH}/core/light/DirectionalLight.cpp
        ${CORE_PATH}/core/light/PointLight.cpp
        ${CORE_PATH}/core/light/SpotLight.cpp

        ${CORE_PATH}/core/effects/Bloom.cpp

        ${CORE_PATH}/core/algorithm/AreaFill.cpp
        ${CORE_PATH}/core/algorithm/Raycaster.cpp

        ${CORE_PATH}/core/algorithm/palette/FixedPalette.cpp
        ${CORE_PATH}/core/algorithm/palette/MedianCut.cpp
        ${CORE_PATH}/core/algorithm/palette/Octree.cpp

        ${CORE_PATH}/core/algorithm/Rasterisation/Bresenham.cpp

        ${CORE_PATH}/core/algorithm/VertexGenerator.cpp
        ${CORE_PATH}/core/models/InstancedMesh.cpp
        ${CORE_PATH}/core/models/InstancedModel.cpp)