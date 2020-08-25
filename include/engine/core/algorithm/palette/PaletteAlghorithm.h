#ifndef PALETTEALGORITHM_H
#define PALETTEALGORITHM_H

#include <array>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <engine/math/Vec3.h>

class PaletteAlgortihm {
public:
    virtual void getPalette(int paletteSize,
                            std::vector<fVec3> &palette,
                            std::vector<fVec3> &colors) = 0;
};

/*
 * Uniform
 * Popularity
 * Median Cut
 * Octree
 * K-means
 */

#endif // PALETTEALGORITHM_H