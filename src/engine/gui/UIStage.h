#ifndef UISTAGE_H
#define UISTAGE_H

#include <memory>
//#include <core/particles/ParticleGenerator.h>
//#include <core/particles/ParticleRenderer.h>
//#include <core/Camera.h>
#include "UIComponent.h"
#include "UIButton.h"
#include "UIFrameDecorator.h"
#include "UIRenderer.h"
#include "../core/particles/ParticleGenerator.h"
#include "../core/particles/ParticleRenderer.h"
#include "../core/Camera.h"

class UIStage {
protected:
//    std::weak_ptr<UIStageManager> stageManager;
    std::shared_ptr<UIComponent> rootComponent;
public:
    UIStage();

    UIStage(const std::shared_ptr<UIComponent> &rootComponent);

    virtual void click(const double &x, const double &y);
    virtual void cursor(const double &x, const double &y);
//    virtual void setManager(const std::shared_ptr<UIStageManager> &manager);
    virtual void renderUI();
    virtual void renderContent(Camera camera, double dt) = 0;
};

class MenuStage : public UIStage {
private:
    std::shared_ptr<UIComponent> temp;
    static std::shared_ptr<MenuStage> instance;
public:
    MenuStage();
    std::function<void ()> fun;

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
        this->fun = fun;
    }

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;

    static std::shared_ptr<UIStage> getInstance();
//    static MenuStage* getInstance();
};

class MeshStage : public UIStage {
private:
    ParticleGenerator pg;
    static std::shared_ptr<MeshStage> instance;
public:
    MeshStage();
    std::function<void ()> fun;

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;

    static std::shared_ptr<UIStage> getInstance();
};

#endif // UISTAGE_H
