#include "PrimitiveRenderer.h"

std::unique_ptr<PrimitiveRenderer> PrimitiveRenderer::renderer = nullptr;

PrimitiveRenderer::PrimitiveRenderer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * (3+4), nullptr, GL_DYNAMIC_DRAW);

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

//void PrimitiveRenderer::render(Rectangle rect) {
//    //TODO:
//    float vertices[6][6] = {
//            { rect.x,          rect.y + rect.h, 0.0f,   color.x, color.y, color.z },
//            { rect.x,          rect.y,          0.0f,   color.x, color.y, color.z },
//            { rect.x + rect.w, rect.y,          0.0f,   color.x, color.y, color.z },
//            { rect.x,          rect.y + rect.h, 0.0f,   color.x, color.y, color.z },
//            { rect.x + rect.w, rect.y,          0.0f,   color.x, color.y, color.z },
//            { rect.x + rect.w, rect.y + rect.h, 0.0f,   color.x, color.y, color.z }
//    };
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glBindVertexArray(0);
//}

void PrimitiveRenderer::render(Rectangle rect) {
    //TODO:
//    std::cout << color.x << ", " << color.y << ", " << color.z << std::endl;
//    std::cout << color[0] << ", " << color[1] << ", " << color[2] << std::endl;
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
//    std::cout << color.x << ", " << color.y << ", " << color.z << std::endl;
//    std::cout << color[0] << ", " << color[1] << ", " << color[2] << std::endl;

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
