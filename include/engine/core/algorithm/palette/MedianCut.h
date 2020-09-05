#ifndef MEDIANCUT_H
#define MEDIANCUT_H

#include <array>
#include <engine/math/Vec3.h>
#include "PaletteAlghorithm.h"

class MedianCut : public PaletteAlgortihm {
private:
    fVec3 average(std::vector<fVec3> &vec);
public:
    void getPalette(int paletteSize,
                    std::vector<fVec3> &palette,
                    std::vector<fVec3> &colors) override;
};

#endif // MEDIANCUT_H