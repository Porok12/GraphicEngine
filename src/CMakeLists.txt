cmake_minimum_required(VERSION 3.10)

include(core/CMakeLists.txt)
include(gui/CMakeLists.txt)
include(math/CMakeLists.txt)

set( HEADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/engine )
set( PUBLIC_HEADERS
        ${HEADER_PATH}/math/Matrix.h
        ${HEADER_PATH}/math/Mat4.h
        ${HEADER_PATH}/math/Vector.h
        ${HEADER_PATH}/math/Vec2.h
        ${HEADER_PATH}/math/Vec3.h
        ${HEADER_PATH}/math/Vec4.h
        ${HEADER_PATH}/math/NotImplementedException.h

        ${HEADER_PATH}/gui/UIButton.h
        ${HEADER_PATH}/gui/UICheckBox.h
        ${HEADER_PATH}/gui/UIComponent.h
        ${HEADER_PATH}/gui/UIComposite.h
        ${HEADER_PATH}/gui/UIFrame.h
        ${HEADER_PATH}/gui/UIFrameDecorator.h
        ${HEADER_PATH}/gui/UILabel.h
        ${HEADER_PATH}/gui/UIRenderer.h
        ${HEADER_PATH}/gui/UISelectBox.h
        ${HEADER_PATH}/gui/UISlider.h
        ${HEADER_PATH}/gui/UIStage.h
        ${HEADER_PATH}/gui/UITextBox.h
        ${HEADER_PATH}/gui/Utils/Constraint.h
        ${HEADER_PATH}/gui/Utils/Utils.h

        ${HEADER_PATH}/gui/Primitives/Circle.h
        ${HEADER_PATH}/gui/Primitives/Rectangle.h
        ${HEADER_PATH}/gui/Primitives/Shape.h
        ${HEADER_PATH}/gui/Primitives/PrimitiveRenderer.h

        ${HEADER_PATH}/core/Camera.h
        ${HEADER_PATH}/core/FreeCamera.h
        ${HEADER_PATH}/core/InputHandler.h
        ${HEADER_PATH}/core/window.h
        ${HEADER_PATH}/core/utils/ResourceLoader.h
        ${HEADER_PATH}/core/text/Character.h
        ${HEADER_PATH}/core/text/Font.h
        ${HEADER_PATH}/core/text/FontLoader.h
        ${HEADER_PATH}/core/text/FontRenderer.h
        ${HEADER_PATH}/core/shaders/ShaderLoader.h
        ${HEADER_PATH}/core/shaders/ShaderProgram.h
        ${HEADER_PATH}/core/particles/Particle.h
        ${HEADER_PATH}/core/particles/ParticleGenerator.h
        ${HEADER_PATH}/core/particles/ParticleRenderer.h
        ${HEADER_PATH}/core/models/Model.h
        ${HEADER_PATH}/core/models/ModelRenderer.h
        ${HEADER_PATH}/core/light/Materials.h
        ${HEADER_PATH}/core/light/Light.h
        ${HEADER_PATH}/core/light/DirectionalLight.h
        ${HEADER_PATH}/core/light/PointLight.h
        ${HEADER_PATH}/core/light/SpotLight.h
        ${HEADER_PATH}/core/exception/InitException.h
        ${HEADER_PATH}/core/effects/Bloom.h
        ${HEADER_PATH}/core/algorithm/AreaFill.h
        ${HEADER_PATH}/core/algorithm/Raycaster.h
        ${HEADER_PATH}/core/algorithm/palette/FixedPalette.h
        ${HEADER_PATH}/core/algorithm/palette/MedianCut.h
        ${HEADER_PATH}/core/algorithm/palette/Octree.h
        ${HEADER_PATH}/core/algorithm/palette/PaletteAlghorithm.h
        ${HEADER_PATH}/core/algorithm/Rasterisation/Bresenham.h
        ${HEADER_PATH}/core/algorithm/VertexGenerator.h

        ${HEADER_PATH}/core/models/Mesh.h
        ${HEADER_PATH}/core/models/InstancedMesh.h
        ${HEADER_PATH}/core/models/InstancedModel.h
        ${HEADER_PATH}/core/models/InstancedRenderer.h
        )

#source_group(Common FILES ${Common_SRCS}) //TODO:

set(ENGINE_SRC
        ${CORE_SRCS}
        ${GUI_SRCS}
        ${MATH_SRCS}
        ${PUBLIC_HEADERS})

add_library(GraphicEngine ${ENGINE_SRC})
#add_library(Foo::Foo ALIAS "${PROJECT_NAME}")

target_include_directories(GraphicEngine PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:include>" #${CMAKE_INSTALL_PREFIX}/include
        )

target_link_libraries(GraphicEngine
        PUBLIC
            ${OPENGL_LIBRARIES}
            ${Boost_LIBRARIES}
            freetype
            assimp
            SOIL
            libglew_static
            glfw
        )

set_target_properties(GraphicEngine PROPERTIES
        VERSION ${PROJECT_VERSION})

install(TARGETS GraphicEngine
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
        COMPONENT headers)
