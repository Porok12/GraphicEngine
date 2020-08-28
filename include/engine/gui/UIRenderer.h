#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include <memory>
#include <engine/core/shaders/ShaderProgram.h>
#include "engine/core/window.h"
#include "engine/gui/UIComponent.h"

class GUIRenderer {
private:
    Mat4 projection;
    std::weak_ptr<ShaderProgram> program;
    int w = 800, h = 600;
    bool _update;

    static std::unique_ptr<GUIRenderer> instance;
    GUIRenderer();

public:
    static GUIRenderer* getInstance();

    GUIRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
    GUIRenderer& setProjection(Mat4 &projection);

    void render(UIComponent *elem);
    void update(int w, int h) {
        this->w = w;
        this->h = h;
        _update = true;
    }
    void requestUpdate() {
        _update = true;
    }
};

#endif // GUIRENDERER_H