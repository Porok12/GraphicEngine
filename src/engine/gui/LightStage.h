#ifndef LIGHTSTAGE_H
#define LIGHTSTAGE_H

#include <memory>
#include <core/models/ModelRenderer.h>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/Model.h>
#include <core/light/PointLight.h>
#include <core/light/DirectionalLight.h>
#include <core/light/SpotLight.h>
#include "UIStage.h"
#include "UIFrameDecorator.h"
#include "UIButton.h"

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
    void renderContent(Camera camera, double dt) override;
};

#endif // LIGHTSTAGE_H
