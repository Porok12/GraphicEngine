#ifndef UICHECKBOX_H
#define UICHECKBOX_H

#include "UIButton.h"

class UICheckBox : public UIComponent {
private:
    std::function<void ()> onClick;
    std::function<void(UICheckBox*)> onCursor;
    fVec3 backgroundColor = fVec3(0.5);
    bool checked = false;
public:
    UICheckBox(const int &x, const int &y, const int &w, const int &h);

    void addClickCallback(std::function<void()> onClick);
    void addCursorCallback(std::function<void(UICheckBox*)> &onCoursor);

    void draw() override;
    void click(const double &x, const double &y) override;
    void cursor(const double &x, const double &y) override;

    void setBackgroundColor(const fVec3 &backgroundColor);

};

#endif // UICHECKBOX_H