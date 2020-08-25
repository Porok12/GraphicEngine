#ifndef FONT_H
#define FONT_H

#include <map>
#include "../../../../src/core/text/Character.h"
#include <utility>

class Font {
private:
    std::map<char, Character> characters;
public:
    explicit Font(std::map<char, Character> characters);
    virtual ~Font();

    const std::map<char, Character> &getCharacters() const;
};

#endif // FONT_H