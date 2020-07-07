#ifndef UICOMPOSITE_H
#define UICOMPOSITE_H

#include <vector>
#include <memory>
#include "UIComponent.h"

class UIComposite : public UIComponent {
private:
    std::vector<std::shared_ptr<UIComponent>> children;
public:
    UIComposite(const std::shared_ptr<Shape> &shape);

    void add(std::shared_ptr<UIComponent> &child);
//    bool remove(std::shared_ptr<UIComponent> &child);
    std::vector<std::shared_ptr<UIComponent>> &getChildren();

    void draw(float offsetX, float offsetY) override;
    void click(const double &x, const double &y) override {
        if (shape->contains(x, y)) {
            for(const auto& ch: children) {
                ch->click(x, y);
            }
        }
    }

    void cursor(const double &x, const double &y) override {
        if (shape->contains(x, y)) {
            for(const auto& ch: children) {
                ch->cursor(x, y);
            }
        }
    }
};

#endif // UICOMPOSITE_H