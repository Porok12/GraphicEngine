#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <memory>
#include <core/shaders/ShaderProgram.h>
#include "UIComponent.h"

class GUIRenderer {
private:
    Mat4 projection;
    std::weak_ptr<ShaderProgram> program;

    static std::unique_ptr<GUIRenderer> instance;
    GUIRenderer();

public:
    static GUIRenderer* getInstance();

    GUIRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
    GUIRenderer& setProjection(Mat4 &projection);

    void render(UIComponent *elem);
};

#endif // GUIRENDERER_H