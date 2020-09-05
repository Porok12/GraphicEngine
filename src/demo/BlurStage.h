#ifndef BLURSTAGE_H
#define BLURSTAGE_H

#include <memory>
#include <engine/core/light/Materials.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include <engine/core/light/PointLight.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/light/SpotLight.h>
#include <engine/core/effects/Bloom.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UISlider.h>
#include <engine/gui/UILabel.h>

class BlurStage : public UIStage {
private:
    float a = 0, b = 0;
    GLuint textureID;
    Bloom bloom;
    Model plane;

    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<BlurStage> instance;
    BlurStage();

public:
    static const std::shared_ptr<BlurStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }


    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // BLURSTAGE_H
