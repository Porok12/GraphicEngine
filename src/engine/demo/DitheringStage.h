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
#include <core/algorithm/palette/MedianCut.h>
#include <core/light/SpotLight.h>
#include "gui/UIStage.h"
#include "gui/UIFrameDecorator.h"
#include "gui/UIButton.h"
#include "gui/UISelectBox.h"
#include <core/algorithm/palette/Octree.h>
#include <core/algorithm/palette/FixedPalette.h>

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
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // DITHERINGSTAGE_H
