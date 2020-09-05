#ifndef FIXEDPALETTE_H
#define FIXEDPALETTE_H

#include <ctime>
#include <iostream>
#include <boost/random.hpp>
#include <engine/math/Vec3.h>

class FixedPalette {
public:
    static void getRandom(int s, std::vector<fVec3> &palette);
    static void getFixed(int s, std::vector<fVec3> &palette);
};

#endif // FIXEDPALETTE_H