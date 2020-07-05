#include "FontLoader.h"

void FontLoader::init() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        BOOST_LOG_TRIVIAL(error) << "Failed to initialize FreeType";
        return;
    }

    std::string path = ResourceLoader::getPath("Ubuntu.ttf", FONT);
    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face)) {
        BOOST_LOG_TRIVIAL(error) << "Failed to load font at path: " << path.c_str();
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

//    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
//        BOOST_LOG_TRIVIAL(error) << "Failed to load character";
//        return;
//    }

    //

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width, face->glyph->bitmap.rows,
        0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
                texture, iVec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                iVec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x
        };

        characters.insert(std::make_pair(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

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

void FontLoader::RenderText(ShaderProgram &sp, std::string text) {
    float x = 0.9, y = 0.9, scale = 1.0;
    iVec3 color(200, 200, 0);

    sp.set3f("color", color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;

    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        for (int i = 0; i < 6; ++i) {
            vertices[i][0] /= 800.0f;
            vertices[i][1] /= 600.0f;
        }

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

FontLoader::FontLoader() {
    init();
}

//FontLoader::FontLoader(const std::map<char, Character> &characters) : characters(characters) {
//
//}
