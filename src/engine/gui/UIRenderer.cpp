#include "UIRenderer.h"

std::unique_ptr<GUIRenderer> GUIRenderer::instance;

GUIRenderer::GUIRenderer() {

}

GUIRenderer *GUIRenderer::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<GUIRenderer>(new GUIRenderer);
    }

    return instance.get();
}

GUIRenderer & GUIRenderer::setProgram(std::shared_ptr<ShaderProgram> &program) {
    this->program = program;
    return *this;
}

GUIRenderer &GUIRenderer::setProjection(Mat4 &projection) {
    this->projection = projection;
    return *this;
}

void GUIRenderer::render(UIComponent *elem) {
    if (auto p = program.lock()) {
        p->use().setMatrix4("ortho", projection);
    }

    if (_update) {
        _update = false;
        elem->update(w, h);
    }

    elem->draw();
}
