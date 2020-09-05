#ifndef MESHSTAGE_H
#define MESHSTAGE_H

#include <memory>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/gui/UISlider.h>
#include <engine/gui/UILabel.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UICheckBox.h>

class MeshStage : public UIStage {
private:
    float rotationSpeed = 0, tmp = 0;
    float rotationX = 0.01, rotationY = 0.01, rotationZ = 0.01;
    Model model;
    std::shared_ptr<UIComponent> temp;
    int colorTarget = 0;

    static std::shared_ptr<MeshStage> instance;
    MeshStage();

public:
    static const std::shared_ptr<MeshStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // MESHSTAGE_H