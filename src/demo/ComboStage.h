#ifndef COMBOTAGE_H
#define COMBOTAGE_H

#include <memory>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/gui/UIStage.h>
#include <engine/gui/UIFrameDecorator.h>
#include <engine/gui/UIButton.h>
#include <engine/gui/UISelectBox.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/models/Model.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/light/PointLight.h>

class ComboStage : public UIStage {
private:
    std::unique_ptr<ParticleGenerator> particleGenerator;
    std::shared_ptr<UIComponent> temp;
    GLuint texSnowFlakes;

    DirectionalLight dirLight;
    PointLight pointLight;
    std::shared_ptr<ShaderProgram> program;
    Model model, plane;

    float a, b;

    static std::shared_ptr<ComboStage> instance;
    ComboStage();
    void changeGenerator(int i);
    void light(ShaderProgram *program, std::string name, DirectionalLight dirLight);
    void light(ShaderProgram *program, std::string name, PointLight pointLight);

public:
    static const std::shared_ptr<ComboStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // COMBOTAGE_H