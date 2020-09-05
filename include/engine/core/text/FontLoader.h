#ifndef FONTLOADER_H
#define FONTLOADER_H

//#include <GL/glew.h>
#include <engine/math/Vec2.h>
#include <engine/math/Vec3.h>
#include <engine/core/shaders/ShaderProgram.h>
#include <utility>
#include <map>
#include "Character.h"
#include "Font.h"
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H

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