#include "UIRenderer.h"

GUIRenderer & GUIRenderer::setProgram(std::shared_ptr<ShaderProgram> &program) {
    this->program = program;
    return *this;
}

GUIRenderer &GUIRenderer::setProjection(Mat4 &projection) {
    this->projection = projection;
    return *this;
}

void GUIRenderer::render(UIComponent *elem) {
    elem->draw();
}
