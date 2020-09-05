#ifndef LIGHTSTAGE_H
#define LIGHTSTAGE_H

#include <memory>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include <engine/core/light/PointLight.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/light/SpotLight.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"

class LightStage : public UIStage {
private:
    float a = 0;
    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;
    PointLight pointLight;
    DirectionalLight dirLight;
    SpotLight spotLight;
    bool dir, point, spot;

    void light(ShaderProgram *program, std::string name, PointLight pointLight);
    void light(ShaderProgram *program, std::string name, DirectionalLight dirLight);
    void light(ShaderProgram *program, std::string name, SpotLight spotLight);

    static std::shared_ptr<LightStage> instance;
    LightStage();

public:
    static const std::shared_ptr<LightStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // LIGHTSTAGE_H
