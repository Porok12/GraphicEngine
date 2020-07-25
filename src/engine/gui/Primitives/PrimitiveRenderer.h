#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <GL/glew.h>
#include <array>

#include <math/Mat4.h>
#include <core/shaders/ShaderProgram.h>
#include <math/Vec2.h>

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"

class PrimitiveRenderer {
private:
    GLuint VAO, VBO;
    fVec3 color;
    float x, y;
    float transparency = 0.9f;
    std::weak_ptr<ShaderProgram> program;
    fVec3 offset;

    static std::unique_ptr<PrimitiveRenderer> renderer;
    PrimitiveRenderer();
public:

    virtual ~PrimitiveRenderer();
    static PrimitiveRenderer* getInstance();

    PrimitiveRenderer* setProgram(std::shared_ptr<ShaderProgram> &program);
    PrimitiveRenderer* setTransparency(const float &transparency);
    PrimitiveRenderer* setColor(const fVec3& color);
    PrimitiveRenderer* setColor(const float r, const float g, const float b);
    PrimitiveRenderer* setPosition(const iVec2& pos);
    PrimitiveRenderer* setPosition(const float& x, const float& y);
    PrimitiveRenderer* setOffset(const fVec3& offset);

    void render(const std::shared_ptr<Shape> &shape);

private:
    void render(const Rectangle* rectangle);
    void render(const Circle* circle, float fact);
};

#endif // PRIMITIVERENDERER_H