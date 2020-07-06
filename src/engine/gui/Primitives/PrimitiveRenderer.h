#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <GL/glew.h>

#include <math/Mat4.h>
#include <core/shaders/ShaderProgram.h>
#include <math/Vec2.h>

#include "Shape.h"
#include "Rectangle.h"

class PrimitiveRenderer {
private:
    GLuint VAO, VBO;
    float r, g, b;
    float x, y;
    float scale;
    Mat4 projection;
    std::weak_ptr<ShaderProgram> ptr;

    bool isIn(double d, double d1);
public:
    PrimitiveRenderer();

    virtual ~PrimitiveRenderer();

    PrimitiveRenderer& setProgram(std::shared_ptr<ShaderProgram> &program);
//    PrimitiveRenderer& setFont(std::shared_ptr<Font>& font);
    PrimitiveRenderer& setScale(const float& scale);
    PrimitiveRenderer& setColor(const iVec3& color);
    PrimitiveRenderer& setColor(const float& r, const float& g, const float& b);
    PrimitiveRenderer& setPosition(const iVec2& pos);
    PrimitiveRenderer& setPosition(const float& x, const float& y);
    PrimitiveRenderer& setProjection(const Mat4& projection);

    void render(std::string text, double xx, double yy);
    void render(Rectangle shape);
};

#endif // PRIMITIVERENDERER_H