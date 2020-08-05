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
#include <core/algorithm/AreaFill.h>
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
#include <random>

class BresenhamStage : public UIStage {
private:
    const GLuint CANVAS_WIDTH = 256;
    const GLuint CANVAS_HEIGHT = 256;

    GLuint textureID;
    std::shared_ptr<FreeCamera> cam;
    std::array<GLubyte, 256 * 256 * 3> pixels;
    std::array<GLubyte, 256 * 256 * 3> tmpPixels;
    iVec2 startPoint;
    bool enable;
    bool active;
    bool abort;
    int option;
    bool fill;
    iVec2 fillPoint;
    iVec3 fillColor;
    bool focus = false;

    Model model, plane;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<UIComponent> temp;

    static std::shared_ptr<BresenhamStage> instance;
    BresenhamStage();
    void fillArea(iVec2 start);

public:
    static const std::shared_ptr<BresenhamStage> &getInstance();

    void setFocus(bool focus);
    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;
};

#endif // BRESENHAMSTAGE_H
