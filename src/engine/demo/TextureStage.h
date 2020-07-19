#ifndef TEXTURESTAGE_H
#define TEXTURESTAGE_H

#include <memory>
#include <core/light/Materials.h>
#include <core/models/ModelRenderer.h>
#include <core/particles/ParticleGenerator.h>
#include <core/particles/ParticleRenderer.h>
#include <core/models/Model.h>
#include <core/light/PointLight.h>
#include <core/light/DirectionalLight.h>
#include <core/light/SpotLight.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"

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
    void renderContent(Camera camera, double dt) override;
};

#endif // TEXTURESTAGE_H
