#ifndef DITHERINGSTAGE_H
#define DITHERINGSTAGE_H

#include <memory>
#include <engine/core/light/Materials.h>
#include <engine/core/models/ModelRenderer.h>
#include <engine/core/particles/ParticleGenerator.h>
#include <engine/core/particles/ParticleRenderer.h>
#include <engine/core/models/Model.h>
#include <engine/core/light/PointLight.h>
#include <engine/core/light/DirectionalLight.h>
#include <engine/core/algorithm/palette/MedianCut.h>
#include <engine/core/light/SpotLight.h>
#include "engine/gui/UIStage.h"
#include "engine/gui/UIFrameDecorator.h"
#include "engine/gui/UIButton.h"
#include "engine/gui/UISelectBox.h"
#include <engine/core/algorithm/palette/Octree.h>
#include <engine/core/algorithm/palette/FixedPalette.h>

#define MAX_PALETTE 64

class DitheringStage : public UIStage {
private:
    float a = 0, b = 0;
    GLuint textureID;
    int size = 0;
    int paletteColors = 0;
    int paletteId = 0;
    std::vector<fVec3> colors, palette;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<DitheringStage> instance;
    DitheringStage();

public:
    static const std::shared_ptr<DitheringStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // DITHERINGSTAGE_H
