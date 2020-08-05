#ifndef SHADINGSTAGE_H
#define SHADINGSTAGE_H

#include <memory>
#include <core/models/ModelRenderer.h>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/Model.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"

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
