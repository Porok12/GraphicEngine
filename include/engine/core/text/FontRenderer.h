#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>
#include <engine/math/Vec4.h>
#include <engine/math/Vec3.h>
#include <engine/math/Vec2.h>
#include <engine/core/shaders/ShaderProgram.h>
#include "Font.h"

class FontRenderer {
private:
    GLuint VAO, VBO;
    float r, g, b;
    float x, y;
    float scale;
    Mat4 projection;
    std::weak_ptr<ShaderProgram> program;
    std::weak_ptr<Font> font;
    static std::shared_ptr<FontRenderer> instance;

    float textWidth(std::string text);
    fVec4 textBox;

    FontRenderer();
public:

    FontRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
    FontRenderer& setFont(std::shared_ptr<Font>& font);
    FontRenderer& setScale(const float& scale);
    FontRenderer& setColor(const iVec3& color);
    FontRenderer& setColor(const float& r, const float& g, const float& b);
    FontRenderer& setPosition(const iVec2& pos);
    FontRenderer& setPosition(const float& x, const float& y);
    FontRenderer& setProjection(const Mat4& projection);
    FontRenderer& setTextBox(const fVec4& box);

    static std::shared_ptr<FontRenderer> getInstance();

    float getWidth(std::string text);
    void render(std::string text);
};

#endif // FONTRENDERER_H
