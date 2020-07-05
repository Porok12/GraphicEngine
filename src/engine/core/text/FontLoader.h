#ifndef FONTLOADER_H
#define FONTLOADER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <boost/log/trivial.hpp>
#include <math/Vec2.h>
#include <map>
#include <math/Vec3.h>
#include <core/shaders/ShaderProgram.h>

struct Character {
    unsigned int TextureID;
    iVec2 Size;
    iVec2 Bearing;
    unsigned int Advance;
};

class FontLoader {
private:
    GLuint VAO, VBO;
    std::map<char, Character> characters {};
    void init();
public:
    FontLoader();

    void RenderText(ShaderProgram &sp, std::string text);
//    FontLoader(const std::map<char, Character> &characters);
};

#endif // FONTLOADER_H