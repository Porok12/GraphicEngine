#ifndef MESHSTAGE_H
#define MESHSTAGE_H

#include <memory>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/Model.h>
#include <core/models/ModelRenderer.h>
#include <gui/UISlider.h>
#include <gui/UILabel.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"
#include <gui/UISelectBox.h>

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
    void renderContent(Camera camera, double dt) override;
};

#endif // MESHSTAGE_H