set(ENGINE_DEMO_SRC
        main.cpp
        MenuStage.cpp MenuStage.h
        MeshStage.cpp MeshStage.h
        ParticlesStage.cpp ParticlesStage.h
        LightStage.cpp LightStage.h
        ShadingStage.cpp ShadingStage.h
        TextureStage.cpp TextureStage.h
        DitheringStage.cpp DitheringStage.h
        BlurStage.cpp BlurStage.h
        BresenhamStage.cpp BresenhamStage.h
        UIStageManager.cpp UIStageManager.h
        SierpinskiStage.cpp SierpinskiStage.h
        ComboStage.cpp ComboStage.h)

add_executable(engine_demo ${ENGINE_DEMO_SRC})

set_target_properties(engine_demo PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(engine_demo GraphicEngine)

install(TARGETS engine_demo DESTINATION demo)

add_custom_command(TARGET engine_demo PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res)
