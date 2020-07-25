#include <iostream>
#include "Octree.h"

octreenode* createOctree(const std::vector<fVec3> &colors) {
//    octreenode octree;
//
//    for (const auto &c: colors) {
//        addNode(octree, c);
//    }

    octreenode* octree = new octreenode;

    octreenode* root = octree;
    int r, g, b, id, ch;
    for (const auto &c: colors) {
        root = octree;
        for (int i = 0; i < 8; i++) {
//            std::cout << c.x << " " << c.y << " " << c.z << std::endl;
            r = c.x;
            g = c.y;
            b = c.z;
            ch = 0;
            id = (r >> (7-i)) & 1;
            ch |= (id << 2);
            root->red += id;
//            std::cout << root->red << " " << ch << std::endl;

            id = (g >> (7-i)) & 1;
            ch |= (id << 1);
            root->green += id;
//            std::cout << id << " " << ch << std::endl;

            id = (b >> (7-i)) & 1;
            ch |= (id << 0);
            root->blue += id;
//            std::cout << id << " " << ch << std::endl;

            root->references += 1;

            if (i == 7) {
                continue;
            }

            if (root->childs == nullptr) {
                root->childs = new octreenode[8];
            }
//            std::cout << root->red << " " << root->green << " " << root->blue << " " << root->references << "\n";
            root = &root->childs[ch];
//            std::cout << i << " " << ch << std::endl;
//            std::cout << (root == nullptr) << std::endl;
        }
    }

    root = octree;

//    int min;
//    for (int i = 0; i < 8; i++) {
//        min = 0;
//        if (root->childs != nullptr) {
//            for (int j = 1; j < 8; j++) {
//                std:: cout << root->childs[min].references << " " << root->childs[j].references << std::endl;
//                min = root->childs[min].references < root->childs[j].references ? min : j;
//            }
//            root = &root->childs[min];
//            std:: cout << min << std::endl;
//        }
//    }

    root = octree;

    r = 0;
    g = 0;
    b = 0;

    unsigned int max;
    for (int i = 0; i < 8; i++) {
        max = 0;
        if (root->childs != nullptr) {
            for (int j = 1; j < 8; j++) {
//                std::cout << root->childs[max].references << " " << root->childs[j].references << std::endl;
                max = root->childs[max].references > root->childs[j].references ? max : j;
            }
            root = &root->childs[max];
//            std:: cout << max << std::endl;
            r |= ((max >> 2) & 1) << (7-i);
            g |= ((max >> 1) & 1) << (7-i);
            b |= ((max >> 0) & 1) << (7-i);
//            std::cout << ((max >> 2) & 1) << " " << ((max >> 1) & 1) << " " << ((max >> 0) & 1) << std::endl;
        }
    }

//    std::cout << r << " " << g << " " << b << std::endl;

    root = octree;
    std::cout << (float)root->red/root->references << " " << (float)root->green/root->references << " " << (float)root->blue/root->references << std::endl;

    for (int i = 0; i < 8; i++) {
//        std::cout << i << std::endl;
        r = root->childs[i].references > 0 ? 255*root->childs[i].red/root->childs[i].references : 0;
        g = root->childs[i].references > 0 ? 255*root->childs[i].green/root->childs[i].references : 0;
        b = root->childs[i].references > 0 ? 255*root->childs[i].blue/root->childs[i].references : 0;

        std::cout << " " << r
                  << " " << g
                  << " " << b << std::endl;
    }

//    octreenode* node = root;
//    for (int n = 0; n < 8; n++) {
//        if (&root->childs[n] != nullptr) {
//            root->references += root->childs[n].references;
//            root->red        += root->childs[n].red;
//            root->green      += root->childs[n].green;
//            root->blue       += root->childs[n].blue;
//
////            delete &root->childs[n];
////            root->childs[n] = nullptr;
//        }
//    }
//
//    std::cout << root->red << " " << root->green << " " << root->blue << " " << root->references << "\n";

    std::cout << octree->red << " " << octree->green << " " << octree->blue << " " << octree->references << "\n";
    return octree;
}

void OctreePalete::getPalette(int s, std::vector<fVec3> &colors, std::vector<fVec3> &palette) {
    octreenode* octree = new octreenode;

    octreenode* root = octree;
    int r, g, b, id, ch;
    for (const auto &c: colors) {
        root = octree;
        r = c.x;
        g = c.y;
        b = c.z;
        for (int i = 0; i < 8; i++) {
            ch = 0;
            id = (r >> (7-i)) & 1;
            ch |= (id << 2);
            root->red += id;

            id = (g >> (7-i)) & 1;
            ch |= (id << 1);
            root->green += id;

            id = (b >> (7-i)) & 1;
            ch |= (id << 0);
            root->blue += id;

            root->references += 1;
            if (root->childs == nullptr) {
                root->childs = new octreenode[8];
            }
            root = &root->childs[ch];
        }
    }

    root = octree;

    for (int i = 0; i < 8; i++) {
        r = root->childs[i].references > 0 ? 255*root->childs[i].red/root->childs[i].references : 0;
        g = root->childs[i].references > 0 ? 255*root->childs[i].green/root->childs[i].references : 0;
        b = root->childs[i].references > 0 ? 255*root->childs[i].blue/root->childs[i].references : 0;
        palette.push_back(fVec3(r, g, b));
    }
}
