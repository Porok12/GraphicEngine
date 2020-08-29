#ifndef SIERPINSKI_STAGE_H
#define SIERPINSKI_STAGE_H

#include <memory>
#include <functional>
#include <engine/core/FreeCamera.h>
#include <engine/gui/UIButton.h>
#include <engine/gui/UIStage.h>
#include <engine/core/light/DirectionalLight.h>

class SierpinskiStage : public UIStage {
private:
    static std::shared_ptr<SierpinskiStage> instance;
    SierpinskiStage();

    std::shared_ptr<UIComponent> temp;
    std::shared_ptr<ShaderProgram> program;
    Model cube;
    DirectionalLight dirLight;

public:
    static const std::shared_ptr<SierpinskiStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // SIERPINSKI_STAGE_H