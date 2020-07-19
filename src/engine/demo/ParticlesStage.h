#ifndef PARTICLESTAGE_H
#define PARTICLESTAGE_H

#include <memory>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"

class ParticleStage : public UIStage {
private:
    ParticleGenerator particleGenerator;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<ParticleStage> instance;
    ParticleStage();

public:
    static const std::shared_ptr<ParticleStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;
};

#endif // PARTICLESTAGE_H