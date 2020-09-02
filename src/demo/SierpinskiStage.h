#ifndef SIERPINSKI_STAGE_H
#define SIERPINSKI_STAGE_H

#include <memory>
#include <functional>
#include <engine/core/FreeCamera.h>
#include <engine/gui/UIButton.h>
#include <engine/gui/UIStage.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/models/InstancedModel.h>
#include <engine/core/light/PointLight.h>
#include <engine/core/light/SpotLight.h>

class SierpinskiStage : public UIStage {
private:
    static std::shared_ptr<SierpinskiStage> instance;
    SierpinskiStage();

    std::shared_ptr<UIComponent> temp;
    std::shared_ptr<ShaderProgram> program;
    Model cube;
    InstancedModel iCube;
    DirectionalLight dirLight;
    PointLight pointLight;
    SpotLight spotLight;
    fVec3 tmp;
    float tmpLoad = 0;
    float fps;
    float fpsMax = 0;
    float fpsMin = 100;
    int iter = 0, algorithmIterations = 0, algorithmSelect = 0, maxIterations;
    float buffer[128]{};

    std::shared_ptr<UIComponent> minLabel, maxLabel, fpsLabel, iterLabel;
    void updateMesh();

public:
    static const std::shared_ptr<SierpinskiStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // SIERPINSKI_STAGE_H