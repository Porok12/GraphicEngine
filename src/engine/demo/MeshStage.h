#ifndef MESHSTAGE_H
#define MESHSTAGE_H

#include <memory>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/Model.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"

class MeshStage : public UIStage {
private:
    float rotationSpeed = 0, tmp = 0;
    float rotationX, rotationY, rotationZ;
    Model model;
    std::shared_ptr<UIComponent> temp;

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