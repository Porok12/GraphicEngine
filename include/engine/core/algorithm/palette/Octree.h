#ifndef OCTREE_H
#define OCTREE_H

#include <engine/math/Vec3.h>

#define OCTREE_DEPTH 8

struct octreenode {
    unsigned long references = 0;
    unsigned long red = 0;
    unsigned long green = 0;
    unsigned long blue = 0;
    octreenode *childs = nullptr;
};

octreenode* createOctree(const std::vector<fVec3> &colors);
//void addNode(const octreenode &node, const fVec3 &color);

class OctreePalete {
public:
    static void getPalette(int s, std::vector<fVec3> &colors, std::vector<fVec3> &palette);
};

#endif // OCTREE_H