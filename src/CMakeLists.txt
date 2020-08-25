cmake_minimum_required(VERSION 3.10)

#file(GLOB PUBLIC_HEADERS "include/ft2build.h" "include/freetype/*.h")
#file(GLOB PUBLIC_CONFIG_HEADERS "include/freetype/config/*.h")
#file(GLOB PRIVATE_HEADERS "include/freetype/internal/*.h")

include(core/CMakeLists.txt)
include(gui/CMakeLists.txt)
include(math/CMakeLists.txt)

set( HEADER_PATH ${CMAKE_SOURCE_DIR}/include/engine )
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
        )

#source_group(Common FILES ${Common_SRCS})
#source_group( include\\assimp    FILES ${PUBLIC_HEADERS} )

set( engine_src
        ${CORE_SRCS}
        ${GUI_SRCS}
        ${MATH_SRCS}
        ${PUBLIC_HEADERS})

#if(${BUILD_SHARED_LIBS})
#    set(BUILD_LIB_TYPE SHARED)
#else()
#    set(BUILD_LIB_TYPE STATIC)
#endif()

add_library(GraphicEngine ${engine_src})

target_include_directories(
        GraphicEngine PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>")

#target_include_directories(mylib PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mylib>
#        $<INSTALL_INTERFACE:include/mylib>  # <prefix>/include/mylib
#        )

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/engine
        COMPONENT headers)

#set(HEADER_FILES ${YOUR_DIRECTORY}/file1.h ${YOUR_DIRECTORY}/file2.h)

#add_library(mylib libsrc.cpp ${HEADER_FILES})
#target_include_directories(mylib PRIVATE ${YOUR_DIRECTORY})
#add_executable(myexec execfile.cpp ${HEADER_FILES})
#target_include_directories(myexec PRIVATE ${YOUR_DIRECTORY})

target_link_libraries(GraphicEngine PUBLIC
        ${OPENGL_LIBRARIES}
        ${Boost_LIBRARIES}
        libglew_static
        glfw
        assimp
        freetype
        SOIL)

target_include_directories(GraphicEngine PUBLIC
        "${PROJECT_SOURCE_DIR}/include")

#set_target_properties( GraphicEngine PROPERTIES
#        VERSION ${PROJECT_VERSION}
#        )

#set_target_properties( GraphicEngine PROPERTIES
#        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#        )


#target_include_directories(GraphicEngine PUBLIC
#        $<INSTALL_INTERFACE:include>)

#add_custom_command(TARGET GraphicEngine PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/res
#        $<TARGET_FILE_DIR:GraphicEngine>/../res)

#install( FILES ${PUBLIC_HEADERS} DESTINATION xxx COMPONENT headers)

#target_include_directories(${tgt}
#        PUBLIC
#        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
#        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
#        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
#        PRIVATE
#        ${PostgreSQL_INCLUDE_DIRS}
#        )
#target_link_libraries(${tgt} PRIVATE ${PostgreSQL_LIBRARIES})
#if(WIN32)
#    target_link_libraries(${tgt} PUBLIC wsock32 ws2_32)
#endif()

#install(TARGETS ${tgt} EXPORT libpqxx-targets
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        )