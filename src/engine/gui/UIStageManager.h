#ifndef UISTAGEMANAGER_H
#define UISTAGEMANAGER_H

#include <memory>
#include <core/Camera.h>
#include "UIRenderer.h"
#include "demo/MeshStage.h"
#include "demo/MenuStage.h"
#include "demo/ParticlesStage.h"
#include "demo/LightStage.h"
#include "demo/ShadingStage.h"
#include "demo/TextureStage.h"
#include "demo/BlurStage.h"
#include "demo/DitheringStage.h"

enum Stages {
    MENU,
    MESH,
    PARTICLES,
    LIGHT,
    SHADING,
    TEXTURE_MAPS,
    BLUR,
    DITHERING
};

class UIStageManager {
private:
    double deltaTime;
    std::shared_ptr<UIStage> rootUI;
    std::shared_ptr<Camera> camera;
    bool disabled = false;

public:
    UIStageManager(const std::shared_ptr<Camera> &camera);

    void setStage(Stages stage);
    void update(double dt);
    void render();

    void click(const double &x, const double &y);
    void cursor(const double &x, const double &y);

    void setDisabled(bool disabled);
    bool isDisabled() const;
};

#endif // UISTAGEMANAGER_H