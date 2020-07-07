#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <memory>
#include <core/shaders/ShaderProgram.h>
#include "UIElement.h"
#include "UIComponent.h"

class GUIRenderer {
    Mat4 projection;
    std::weak_ptr<ShaderProgram> program;
public:
    GUIRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
    GUIRenderer& setProjection(Mat4 &projection);

    void render(UIElement *elem);
    void render(UIComponent *elem);
};

#endif // GUIRENDERER_H