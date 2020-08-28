#ifndef UISTAGEMANAGER_H
#define UISTAGEMANAGER_H

#include <memory>
#include <engine/core/FreeCamera.h>
#include "engine/gui/UIRenderer.h"
#include "MeshStage.h"
#include "MenuStage.h"
#include "ParticlesStage.h"
#include "LightStage.h"
#include "ShadingStage.h"
#include "TextureStage.h"
#include "BlurStage.h"
#include "DitheringStage.h"
#include "BresenhamStage.h"
#include "SierpinskiStage.h"

enum Stages {
    MENU,
    MESH,
    PARTICLES,
    LIGHT,
    SHADING,
    TEXTURE_MAPS,
    BLUR,
    DITHERING,
    BRESENHAM,
    SIERPINSKI
};

class UIStageManager {
private:
    double deltaTime;
    std::shared_ptr<UIStage> rootUI;
    std::shared_ptr<FreeCamera> camera;
    bool disabled = false;

public:
    UIStageManager(const std::shared_ptr<FreeCamera> &camera);

    void setStage(Stages stage);
    void update(double dt);
    void render();

    void click(const double &x, const double &y);
    void cursor(const double &x, const double &y);

    void setDisabled(bool disabled);
    bool isDisabled() const;
};

#endif // UISTAGEMANAGER_H