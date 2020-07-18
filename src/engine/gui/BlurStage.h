#ifndef BLURSTAGE_H
#define BLURSTAGE_H

#include <memory>
#include <core/light/Materials.h>
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

class BlurStage : public UIStage {
private:
    float a = 0, b = 0;
    GLuint textureID;
    GLuint pingpongFBO[2];
    GLuint pingpongColorbuffers[2];
    GLuint quadVAO = 0;
    GLuint quadVBO;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program, blur;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<BlurStage> instance;
    BlurStage();

public:
    static const std::shared_ptr<BlurStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;

    void drawQuad();
};

#endif // BLURSTAGE_H
