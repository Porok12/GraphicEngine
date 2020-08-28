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
        UIStageManager.cpp UIStageManager.h)

add_executable(engine_demo ${ENGINE_DEMO_SRC})

set_target_properties(engine_demo PROPERTIES VERSION ${PROJECT_VERSION})
target_link_libraries(engine_demo GraphicEngine)

install(TARGETS engine_demo DESTINATION demo)