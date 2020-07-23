#include "FontRenderer.h"

std::shared_ptr<FontRenderer> FontRenderer::instance;

FontRenderer::FontRenderer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void FontRenderer::render(std::string text) {
    float x = this->x;
    float y = this->y;
    program.lock()->use().set3f("color", r, g, b).setMatrix4("ortho", projection);
    float width = this->textWidth(text);
    float height = font.lock()->getCharacters().at('X').Size.y * scale;

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = font.lock()->getCharacters().at(*c);

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        for (auto &v : vertices) {
            v[0] += (textBox.z - textBox.x - width)/2;
            v[1] += (textBox.w - textBox.y - height)/2;
        }

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

FontRenderer &FontRenderer::setColor(const float &r, const float &g, const float &b) {
    this->r = r;
    this->g = g;
    this->b = b;
    return *this;
}

FontRenderer &FontRenderer::setColor(const iVec3 &color) {
    return setColor((float)color.x, (float)color.y, (float)color.z);
}

FontRenderer &FontRenderer::setPosition(const float &x, const float &y) {
    this->x = x;
    this->y = y;
    return *this;
}

FontRenderer &FontRenderer::setPosition(const iVec2 &pos) {
    return setPosition((float)pos.x, (float)pos.y);
}

FontRenderer &FontRenderer::setProgram(std::shared_ptr<ShaderProgram> &program) {
    this->program = program;
    return *this;
}

FontRenderer &FontRenderer::setScale(const float &scale) {
    this->scale = scale;
    return *this;
}

FontRenderer &FontRenderer::setFont(std::shared_ptr<Font>& font) {
    this->font = font;
    return *this;
}

FontRenderer &FontRenderer::setProjection(const Mat4 &projection) {
    this->projection = projection;
    return *this;
}

std::shared_ptr<FontRenderer> FontRenderer::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<FontRenderer>(new FontRenderer());
    }

    return instance;
}

float FontRenderer::textWidth(std::string text) {
    float width = 0.0f;
    for (char &c : text) {
        if (auto f = font.lock()) {
            width += (f->getCharacters().at(c).Advance >> 6) * scale;
        }
    }
    return width;
}

FontRenderer &FontRenderer::setTextBox(const fVec4& box) {
    this->textBox = box;
    return *this;
}

float FontRenderer::getWidth(std::string text) {
    return textWidth(text);
}


