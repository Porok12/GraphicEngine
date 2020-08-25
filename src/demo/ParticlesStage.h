#ifndef PARTICLESTAGE_H
#define PARTICLESTAGE_H

#include <memory>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"
#include "engine/gui/UISelectBox.h"

class ParticleStage : public UIStage {
private:
    std::unique_ptr<ParticleGenerator> particleGenerator;
    std::shared_ptr<UIComponent> temp;
    GLuint texFire, texCloud, texExplosion, texCandleSmoke, texSnowFlakes;

    static std::shared_ptr<ParticleStage> instance;
    ParticleStage();
    void changeGenerator(int i);

public:
    static const std::shared_ptr<ParticleStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // PARTICLESTAGE_H