#include <engine/core/text/Font.h>

Font::Font(std::map<char, Character> characters)
        : characters(std::move(characters)) {

}

const std::map<char, Character> &Font::getCharacters() const {
    return characters;
}

Font::~Font() {

}
