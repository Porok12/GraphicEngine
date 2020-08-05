#ifndef PARTICLESTAGE_H
#define PARTICLESTAGE_H

#include <memory>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"
#include "gui/UISelectBox.h"

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