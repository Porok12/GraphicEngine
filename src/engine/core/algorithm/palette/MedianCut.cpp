#include "MedianCut.h"

void MedianCut::getPalette(int paletteSize,
                           std::vector<fVec3> &palette,
                           std::vector<fVec3> &colors) {
    if (paletteSize > 0) {
        fVec3 min = colors[0];
        fVec3 max = colors[0];

        for (int i = 1; i < colors.size(); i++) {
            for (int j = 0; j < 3 ; j++) {
                if (min[j] > colors[i][j]) {
                    min[j] = colors[i][j];
                }

                if (max[j] < colors[i][j]) {
                    max[j] = colors[i][j];
                }
            }
        }

        fVec3 delta = max - min;

        if(delta.x > delta.y && delta.x > delta.z) {
            std::sort(colors.begin(), colors.end(), [](const fVec3 &a, const fVec3 &b) -> bool{return a.x < b.x;});

        } else if (delta.y > delta.x && delta.y > delta.z) {
            std::sort(colors.begin(), colors.end(), [](const fVec3 &a, const fVec3 &b) -> bool{return a.y < b.y;});

        } else {
            std::sort(colors.begin(), colors.end(), [](const fVec3 &a, const fVec3 &b) -> bool{return a.z < b.z;});
        }


        std::size_t half_size = colors.size() / 2;
        std::vector<fVec3> rgb_lo(colors.begin(), colors.begin() + half_size);
        std::vector<fVec3> rgb_hi(colors.begin() + half_size, colors.end());

        getPalette(paletteSize-1, palette, rgb_lo);
        getPalette(paletteSize-1, palette, rgb_hi);

    } else {
        palette.push_back(average(colors));
    }
}

fVec3 MedianCut::average(std::vector<fVec3> &vec) {
    fVec3 sum;
    for (const auto &i : vec) {
        sum += i;
    }

    sum *= 1.0 / vec.size();
    return sum;
}
