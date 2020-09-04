#ifndef MENUSTAGE_H
#define MENUSTAGE_H

#include <memory>
#include <engine/gui/UIStage.h>
#include <engine/gui/UIButton.h>
#include <engine/gui/UIFrameDecorator.h>
#include <engine/gui/UISlider.h>
#include <engine/gui/UISelectBox.h>
#include <engine/gui/UILabel.h>
#include <engine/gui/UICheckBox.h>
#include <engine/gui/UITextBox.h>

class MenuStage : public UIStage {
private:
    std::shared_ptr<UIComponent> temp, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10;
    static std::shared_ptr<MenuStage> instance;
    MenuStage();

public:
    static const std::shared_ptr<MenuStage> & getInstance();

    void renderUI() override;
    void renderContent(FreeCamera &camera, double dt) override;

    void setXxx(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp)->addClickCallback(fun);
    }

    void setYyy(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp2)->addClickCallback(fun);
    }

    void setZzz(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp3)->addClickCallback(fun);
    }

    void setAaa(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp4)->addClickCallback(fun);
    }

    void setBbb(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp5)->addClickCallback(fun);
    }

    void setCcc(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp6)->addClickCallback(fun);
    }

    void setDdd(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp7)->addClickCallback(fun);
    }

    void setEee(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp8)->addClickCallback(fun);
    }

    void setFff(std::function<void ()> fun) {
        std::dynamic_pointer_cast<UIButton>(temp9)->addClickCallback(fun);
    }

    void setGgg(std::function<void (std::string)> fun) {
        std::dynamic_pointer_cast<UITextBox>(temp10)->addListener(fun);
    }
};

#endif // MENUSTAGE_H