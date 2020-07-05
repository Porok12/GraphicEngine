#ifndef FONTLOADER_H
#define FONTLOADER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <boost/log/trivial.hpp>
#include <math/Vec2.h>
#include <math/Vec3.h>
#include <core/shaders/ShaderProgram.h>
#include <utility>
#include <map>
#include "Character.h"
#include "Font.h"

class FontLoader {
private:
    FontLoader();

    void init();

    FT_Library lib;
    FT_Face face;
    std::map<char, Character> characters;
    static std::unique_ptr<FontLoader> loader;

public:
    virtual ~FontLoader();

    static Font * loadFont(std::string name);
    static void destroy();
    void load(std::string string);
    void loadCharacters();
};

#endif // FONTLOADER_H