#ifndef CHARACTER_H
#define CHARACTER_H

#include <math/Vec2.h>

struct Character {
    unsigned int TextureID;
    iVec2 Size;
    iVec2 Bearing;
    unsigned int Advance;
};

#endif // CHARACTER_H