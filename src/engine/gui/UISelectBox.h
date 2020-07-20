#ifndef UISELECTBOX_H
#define UISELECTBOX_H

#include <gui/Primitives/Rectangle.h>
#include <gui/Primitives/PrimitiveRenderer.h>
#include <core/text/FontRenderer.h>
#include <math/Vec3.h>
#include <functional>
#include <memory>
#include <utility>
#include "UIComponent.h"
#include "UIButton.h"
#include "UIComposite.h"


class UISelectBox : public UIComponent { //};, public std::enable_shared_from_this<UISelectBox> {
private:
    fVec3 backgroundColor;
    std::function<void ()> onClick;
    std::function<void(UISelectBox*)> onCursor;

    std::vector<std::shared_ptr<UIComponent>> buttons;
//protected:
//    std::shared_ptr<UIComponent> shared_from_this() override {
//        std::cerr << std::enable_shared_from_this<UISelectBox>::shared_from_this().use_count() << std::endl;
//        return std::enable_shared_from_this<UISelectBox>::shared_from_this();
//    };
public:
    UISelectBox(const std::shared_ptr<Shape> &shape) : UIComponent(shape), buttons() {
        this->backgroundColor = fVec3(0.5f, 0.5f, 0.5f);
    }

    UISelectBox(const int &x, const int &y, const int &w, const int &h)
            : UISelectBox(std::make_shared<Rectangle>(x, y, w, h)) {
    }

    void init() {
        buttons.push_back(std::make_shared<UIButton>("1", 0, 0, shape->x, 40));
        buttons.push_back(std::make_shared<UIButton>("2", 0, 0, shape->x, 40));
        buttons.push_back(std::make_shared<UIButton>("3", 0, 0, shape->x, 40));
        for (auto &btn: buttons) {
            btn->setParent(shared_from_this());
        }
    }

    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UISelectBox*)> &onCoursor);

    void draw() override;
    void click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;

    void setBackgroundColor(const fVec3 &backgroundColor);



};

#endif // UISELECTBOX_H