#ifndef MENUSTAGE_H
#define MENUSTAGE_H

#include <memory>
#include "UIStage.h"
#include "UIButton.h"
#include "UIFrameDecorator.h"

class MenuStage : public UIStage {
private:
    std::shared_ptr<UIComponent> temp, temp2;
    static std::shared_ptr<MenuStage> instance;
    MenuStage();

public:
    static const std::shared_ptr<MenuStage> & getInstance();

    void renderUI() override;
    void renderContent(Camera camera, double dt) override;

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void setYyy(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp2)->addClickCallback(fun);
    }
};

#endif // MENUSTAGE_H