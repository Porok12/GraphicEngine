#ifndef UITEXTBOX_H
#define UITEXTBOX_H

#include "engine/gui/UIComponent.h"
#include <engine/gui/Primitives/Rectangle.h>
#include <engine/gui/Primitives/PrimitiveRenderer.h>
#include <engine/core/text/FontRenderer.h>
#include "engine/core/InputHandler.h"

class UITextBox : public UIComponent {
    using onchange = std::function<void (std::string)>;
private:
    bool active = false;
    int maxSize = 10;
    std::string text = "TextBox";
    fVec3 backgroundColor = fVec3(0.5f);
    onchange onchangeFun;
public:
    UITextBox(const std::shared_ptr<Shape> &shape);
    UITextBox(int x, int y, int w, int h);

    bool click(const double &x, const double &y) override;

    void cursor(const double &x, const double &y) override;

    void draw() override;

    std::string getText() const;
    void setText(std::string text);
    void addListener(onchange fun);
};

#endif // UITEXTBOX_H