#ifndef UISELECTBOX_H
#define UISELECTBOX_H

#include <engine/gui/Primitives/Rectangle.h>
#include <engine/gui/Primitives/PrimitiveRenderer.h>
#include <engine/core/text/FontRenderer.h>
#include <engine/math/Vec3.h>
#include <functional>
#include <memory>
#include <utility>
#include "engine/gui/UIComponent.h"
#include "engine/gui/UIButton.h"
#include "engine/gui/UIComposite.h"
#include <boost/range/adaptor/reversed.hpp>
#include <boost/foreach.hpp>
#include <string>

class UISelectBox : public UIComponent {
    struct Option {
        std::shared_ptr<Shape> shape;
        bool over;
        std::string text;

        Option(float x, float y, float w, float h)
                : shape(std::make_shared<Rectangle>(x, y, w, h)), text("none"), over(0) { };
        Option(float x, float y, float w, float h, std::string text)
                : shape(std::make_shared<Rectangle>(x, y, w, h)), text(std::move(text)), over(0) { };
    };
private:
    bool opened = false;
    fVec3 backgroundColor;
    std::function<void ()> onClick;
    std::function<void (int)> onChanged;
    std::function<void(UISelectBox*)> onCursor;

    std::vector<std::shared_ptr<Option>> options;
    std::shared_ptr<Option> option;
public:
    UISelectBox(const std::shared_ptr<Shape> &shape) : UIComponent(shape), options() {
        this->backgroundColor = fVec3(0.5f);
    }

    UISelectBox(const int &x, const int &y, const int &w, const int &h)
            : UISelectBox(std::make_shared<Rectangle>(x, y, w, h)) {
    }

    void init() {
        options.push_back(std::make_shared<Option>(shape->x, shape->y - 1*shape->h, shape->w, shape->h));
        options.push_back(std::make_shared<Option>(shape->x, shape->y - 2*shape->h, shape->w, shape->h));
        options.push_back(std::make_shared<Option>(shape->x, shape->y - 3*shape->h, shape->w, shape->h));
    }

    void setOptions(const std::vector<std::string> &options);

    void addChangedCallback(std::function<void(int)> onChanged);
    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UISelectBox*)> &onCoursor);

    int getOption();

    void draw() override;
    bool click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;
    void setBackgroundColor(const fVec3 &backgroundColor);
};

#endif // UISELECTBOX_H