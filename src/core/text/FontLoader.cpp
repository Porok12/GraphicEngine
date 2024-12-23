#include <engine/core/utils/ResourceLoader.h>
#include "engine/core/text/FontLoader.h"


std::unique_ptr<FontLoader> FontLoader::loader;

FontLoader::FontLoader() : characters() {
    init();
}

FontLoader::~FontLoader() {
    FT_Done_FreeType(lib);
}

void FontLoader::init() {
    if (FT_Init_FreeType(&lib)) {
        std::cerr << "Failed to initialize FreeType" << std::endl;
        return;
    }
    std::cout << "Font loader initialized" << std::endl;
}

void FontLoader::load(std::string name) {
    std::string path = ResourceLoader::getPath(name, FONT);
    if (FT_New_Face(lib, path.c_str(), 0, &face)) {
        std::cerr << "Failed to load font at path: " << path.c_str() << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    loadCharacters();

    std::cout << "Font loaded: " << name.c_str() << std::endl;
}

Font * FontLoader::loadFont(std::string name) {
    if (!loader) {
        loader.reset(new FontLoader);
    }
    loader->load(std::move(name));
    return new Font(loader->characters);
}

void FontLoader::loadCharacters() {
    std::cout << "Loading characters..." << std::endl;

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
    FT_Done_Face(face);
}

void FontLoader::destroy() {
    loader = nullptr;
}
