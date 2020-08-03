#ifndef BRESENHAMSTAGE_H
#define BRESENHAMSTAGE_H

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
#include <gui/UIStage.h>
#include <gui/UIFrameDecorator.h>
#include <gui/UIButton.h>
#include <gui/UISelectBox.h>
#include <core/algorithm/palette/Octree.h>
#include <core/algorithm/palette/FixedPalette.h>
#include <core/algorithm/Rasterisation/Bresenham.h>
#include <core/algorithm/Raycaster.h>
#include <GL/glew.h>

class BresenhamStage : public UIStage {
private:
    const GLuint CANVAS_WIDTH = 256;
    const GLuint CANVAS_HEIGHT = 256;

    GLuint textureID;
    std::shared_ptr<FreeCamera> cam;
    std::array<GLubyte, 256 * 256 * 3> pixels;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;
    PointLight pointLight;
    DirectionalLight dirLight;

    static std::shared_ptr<BresenhamStage> instance;
    BresenhamStage();

public:
    static const std::shared_ptr<BresenhamStage> &getInstance();

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // BRESENHAMSTAGE_H
