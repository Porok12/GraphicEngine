#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * (3+3), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    srand (time(NULL));
}

PrimitiveRenderer::~PrimitiveRenderer() {
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
}

PrimitiveRenderer &PrimitiveRenderer::setProgram(std::shared_ptr<ShaderProgram> &program) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setScale(const float &scale) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setColor(const iVec3 &color) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setColor(const float &r, const float &g, const float &b) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setPosition(const iVec2 &pos) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setPosition(const float &x, const float &y) {
    return *this;
}

PrimitiveRenderer &PrimitiveRenderer::setProjection(const Mat4 &projection) {
    return *this;
}

void PrimitiveRenderer::render(std::string text, double xx, double yy) {
    float xpos = 200;
    float ypos = 100;
    float w = 200;
    float h = 100;
    float r = (isIn(xx, yy)) ? 0.0f : 1.0f;
    if (isIn(xx, yy)) {
        xpos -= 5;
        ypos -= 5;
        w += 10;
        h += 10;
    }
    float vertices[6][6] = {
            { xpos,     ypos + h, 0.0f,   1.0f, 0.0f, 1.0f },
            { xpos,     ypos,     0.0f,   0.0f, 1.0f, 1.0f },
            { xpos + w, ypos,     0.0f,   1.0f, 1.0f, 0.0f },
            { xpos,     ypos + h, 0.0f,   1.0f, 1.0f, 1.0f },
            { xpos + w, ypos,     0.0f,   1.0f, 1.0f, 1.0f },
            { xpos + w, ypos + h, 0.0f,   r*1.0f, 1.0f, 1.0f }
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

bool PrimitiveRenderer::isIn(double d, double d1) {
    float xpos = 200;
    float ypos = 100;
    float w = 200;
    float h = 100;

    d1 = 600 - d1;

    if (d >= xpos && d <= xpos + w) {
        if (d1 >= ypos && d1 <= ypos + h) {
            return true;
        }
    }

    return false;
}

void PrimitiveRenderer::render(Rectangle rect) {
    float vertices[6][6] = {
            { rect.x,     rect.y + rect.h, 0.0f,   1.0f, 0.0f, 1.0f },
            { rect.x,     rect.y,     0.0f,   0.0f, 1.0f, 1.0f },
            { rect.x + rect.w, rect.y,     0.0f,   1.0f, 1.0f, 0.0f },
            { rect.x,     rect.y + rect.h, 0.0f,   1.0f, 1.0f, 1.0f },
            { rect.x + rect.w, rect.y,     0.0f,   1.0f, 1.0f, 1.0f },
            { rect.x + rect.w, rect.y + rect.h, 0.0f,   r*1.0f, 1.0f, 1.0f }
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
