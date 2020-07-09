#ifndef UICOMPOSITE_H
#define UICOMPOSITE_H

#include <vector>
#include <memory>
#include "UIComponent.h"

class UIComposite : public UIComponent, public std::enable_shared_from_this<UIComposite> {
private:
    std::vector<std::shared_ptr<UIComponent>> children;
public:
    UIComposite(const std::shared_ptr<Shape> &shape);

    void add(std::shared_ptr<UIComponent> &child);
    void remove(std::shared_ptr<UIComponent> &child);
    std::vector<std::shared_ptr<UIComponent>> &getChildren();

    void draw() override;
    void click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;
};

#endif // UICOMPOSITE_H