#ifndef TEXTURESTAGE_H
#define TEXTURESTAGE_H

#include <memory>
#include <engine/core/light/Materials.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include <engine/core/light/PointLight.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/light/SpotLight.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"

class TextureStage : public UIStage {
private:
    float a = 0, b = 0;
    bool enableNormalMap = false;
    bool enableSpecularMap = false;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;
    PointLight pointLight;
    DirectionalLight dirLight;

    void light(ShaderProgram *program, std::string name, PointLight pointLight);
    void light(ShaderProgram *program, std::string name, DirectionalLight dirLight);

    static std::shared_ptr<TextureStage> instance;
    TextureStage();

public:
    static const std::shared_ptr<TextureStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // TEXTURESTAGE_H
