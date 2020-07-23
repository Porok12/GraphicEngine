#ifndef UIBUILDER_H
#define UIBUILDER_H

#include "UIButton.h"

template <class T>
class UIBuilder {
private:
public:
    virtual std::shared_ptr<T> build() = 0;
};

class ButtonBuilder : public UIBuilder<UIButton> {
public:
    std::shared_ptr<UIButton> build() override {


//        PrimitiveRenderer::getInstance()->setPosition()->render();



    };
};

#endif // UIBUILDER_H