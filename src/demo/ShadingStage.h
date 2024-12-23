#ifndef SHADINGSTAGE_H
#define SHADINGSTAGE_H

#include <memory>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"

class ShadingStage : public UIStage {
private:
    enum Shading {
        FLAT,
        GOURAUD,
        PHONG,
        BLINN
    };

    float a = 0;
    Model model, plane;
    std::shared_ptr<ShaderProgram> program, phong, gouraud;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<ShadingStage> instance;
    ShadingStage();
    void updateShading(Shading shading);

public:
    static const std::shared_ptr<ShadingStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // SHADINGSTAGE_H
