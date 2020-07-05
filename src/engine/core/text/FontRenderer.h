#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <GL/glew.h>
#include <string>
#include <math/Vec3.h>
#include <math/Vec2.h>
#include <memory>
#include "../shaders/ShaderProgram.h"
#include "Character.h"
#include "Font.h"

class FontRenderer {
private:
    GLuint VAO, VBO;
    float r, g, b;
    float x, y;
    float scale;
    Mat4 projection;
    std::weak_ptr<ShaderProgram> ptr;
    std::weak_ptr<Font> font;
public:
    FontRenderer();

    FontRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
    FontRenderer& setFont(std::shared_ptr<Font>& font);
    FontRenderer& setScale(const float& scale);
    FontRenderer& setColor(const iVec3& color);
    FontRenderer& setColor(const float& r, const float& g, const float& b);
    FontRenderer& setPosition(const iVec2& pos);
    FontRenderer& setPosition(const float& x, const float& y);
    FontRenderer& setProjection(const Mat4& projection);


    void render(std::string text);
};

#endif // FONTRENDERER_H
