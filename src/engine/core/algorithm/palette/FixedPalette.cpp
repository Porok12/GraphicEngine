#include "FixedPalette.h"

void FixedPalette::getRandom(int s, std::vector <fVec3> &palette) {
    static std::time_t now = std::time(0);
    static boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};
    static boost::random::uniform_int_distribution<> dist{0, 255};

    palette.clear();
    for (int j = 0; j < s; ++j) {
        palette.push_back(fVec3(dist(gen), dist(gen), dist(gen)));
    }
}

void FixedPalette::getFixed(int s, std::vector <fVec3> &palette) {
    palette.clear();
    for (int i = 1; i <= s; ++i) {
        for (int j = 0; j < 8 && (i-1)*8+j < s; j++) {
            palette.push_back(fVec3(255.0/i * (j/4), 255.0/i * ((j/2)%2), 255.0/i *(j%2)));
        }
    }
}
