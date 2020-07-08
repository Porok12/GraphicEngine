#include "PrimitiveRenderer.h"

std::unique_ptr<PrimitiveRenderer> PrimitiveRenderer::renderer = nullptr;

PrimitiveRenderer::PrimitiveRenderer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 64 * (3+4), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->color = fVec3(1.0f);
}

PrimitiveRenderer::~PrimitiveRenderer() {
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
}

PrimitiveRenderer *PrimitiveRenderer::setColor(const fVec3& color) {
    this->color = color;
    return this;
}

PrimitiveRenderer *PrimitiveRenderer::setColor(const float r, const float g, const float b) {
    return setColor(fVec3(r, g, b));
}

PrimitiveRenderer *PrimitiveRenderer::setPosition(const iVec2 &pos) {
    return setPosition((float)pos.x, (float)pos.y);
}

PrimitiveRenderer *PrimitiveRenderer::setPosition(const float &x, const float &y) {
    this->x = x;
    this->y = y;
    return this;
}

void PrimitiveRenderer::render(Rectangle rect) {
    //TODO:
    float vertices[6][7] = {
            { rect.x,          rect.y + rect.h, 0.0f,   color.x, color.y, color.z, transparency },
            { rect.x,          rect.y,          0.0f,   color.x, color.y, color.z, transparency },
            { rect.x + rect.w, rect.y,          0.0f,   color.x, color.y, color.z, transparency },
            { rect.x,          rect.y + rect.h, 0.0f,   color.x, color.y, color.z, transparency },
            { rect.x + rect.w, rect.y,          0.0f,   color.x, color.y, color.z, transparency },
            { rect.x + rect.w, rect.y + rect.h, 0.0f,   color.x, color.y, color.z, transparency }
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void PrimitiveRenderer::render(const Rectangle* rect) {
    //TODO:
    program.lock()->use();

    float vertices[6][7] = {
            { rect->x,           rect->y + rect->h, 0.0f,   color.x, color.y, color.z, transparency },
            { rect->x,           rect->y,           0.0f,   color.x, color.y, color.z, transparency },
            { rect->x + rect->w, rect->y,           0.0f,   color.x, color.y, color.z, transparency },
            { rect->x,           rect->y + rect->h, 0.0f,   color.x, color.y, color.z, transparency },
            { rect->x + rect->w, rect->y,           0.0f,   color.x, color.y, color.z, transparency },
            { rect->x + rect->w, rect->y + rect->h, 0.0f,   color.x, color.y, color.z, transparency }
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

PrimitiveRenderer* PrimitiveRenderer::getInstance() {
    if (!renderer) {
        renderer = std::unique_ptr<PrimitiveRenderer>(new PrimitiveRenderer);
    }

    return renderer.get();
}

PrimitiveRenderer* PrimitiveRenderer::setTransparency(const float &transparency) {
    PrimitiveRenderer::transparency = transparency;
    return this;
}

PrimitiveRenderer *PrimitiveRenderer::setProgram(std::shared_ptr<ShaderProgram> &program) {
    this->program = program;
    return this;
}

void PrimitiveRenderer::render(const Circle *circle, int fact) {
    program.lock()->use();

    fact = 16;
    float f = (360.0f / fact);
    fact += 2;

    auto D2R = static_cast<float>(M_PI / 180.0f);
    float step = f * D2R;
    float angle = 0.0f;

    std::array<std::array<float, 7>, 64> vertices = {};

    this->x = circle->x;
    this->y = circle->y;

    vertices.at(0) = {this->x, this->y, 0.0f, color.x, color.y, color.z, transparency};
    for (unsigned int i = 1; i < fact; i++) {
        vertices.at(i) = {this->x + circle->radius*std::sin(angle),
                          this->y + circle->radius*std::cos(angle),
                          0.0f, color.x, color.y, color.z, transparency};
        angle -= step;
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 7*4*fact, vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, fact);
    glBindVertexArray(0);
}
