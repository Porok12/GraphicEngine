#ifndef DITHERINGSTAGE_H
#define DITHERINGSTAGE_H

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

class DitheringStage : public UIStage {
private:
    float a = 0, b = 0;
    bool enableNormalMap = false;
    bool enableSpecularMap = false;
    GLuint textureID;
    int size = 0;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;
    PointLight pointLight;
    DirectionalLight dirLight;

    static std::shared_ptr<DitheringStage> instance;
    DitheringStage();

public:
    static const std::shared_ptr<DitheringStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;
};

#endif // DITHERINGSTAGE_H
