#ifndef UICOMPOSITE_H
#define UICOMPOSITE_H

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "UIComponent.h"
#include "Utils/Utils.h"

class UIComposite : public UIComponent {
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
    void update(int w, int h) override;
};

#endif // UICOMPOSITE_H