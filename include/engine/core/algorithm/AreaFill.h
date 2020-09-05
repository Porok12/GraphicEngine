#ifndef AREAFILL_H
#define AREAFILL_H

#include <engine/math/Vec2.h>
#include <engine/math/Vec3.h>
#include <GL/glew.h>
#include <array>
#include <iostream>
#include <queue>

class AreaFill {
public:
//    template <std::size_t N>
//    static void floodFill(std::array<GLubyte, N> &points, const int width, const int height, iVec2 point, iVec3 color, iVec3 bg) {
//        if (point.x < 0 || point.x >= width) {
//            return;
//        } else if (point.y < 0 || point.y >= height) {
//            return;
//        }
//
////        std::cout << "x: " << point.x << ", y: " << point.y << "\n";
//
//        int offset = (point.x+width*point.y) * 3;
//        if (bg.x == color.x &&
//            bg.y == color.y &&
//            bg.z == color.z) {
//            return;
//        } else if (points[offset+0] != bg.x ||
//                   points[offset+1] != bg.y ||
//                   points[offset+2] != bg.z) {
//            return;
//        } else {
//            points[offset+0] = color.x;
//            points[offset+1] = color.y;
//            points[offset+2] = color.z;
//        }
//
//        floodFill(points, width, height, iVec2(point.x+1, point.y+0), color, bg);
//        floodFill(points, width, height, iVec2(point.x-1, point.y+0), color, bg);
//        floodFill(points, width, height, iVec2(point.x+0, point.y+1), color, bg);
//        floodFill(points, width, height, iVec2(point.x+0, point.y-1), color, bg);
//    }
    template <std::size_t N>
    static void floodFill(std::array<GLubyte, N> &points, const int width, const int height, iVec2 point, iVec3 color, iVec3 bg) {
        if (point.x < 0 || point.x >= width) {
            return;
        } else if (point.y < 0 || point.y >= height) {
            return;
        }

        int offset = (point.x+width*point.y) * 3;
        if (bg.x == color.x &&
            bg.y == color.y &&
            bg.z == color.z) {
            return;
        } else if (points[offset+0] != bg.x ||
                   points[offset+1] != bg.y ||
                   points[offset+2] != bg.z) {
            return;
        } else {
            points[offset+0] = color.x;
            points[offset+1] = color.y;
            points[offset+2] = color.z;

            std::queue<iVec2> Q {};
            Q.push(point);

            while (!Q.empty()) {
                iVec2 n = Q.front();
                Q.pop();

                iVec2 tmp = iVec2(n.x+1, n.y);
                if (tmp.x >= 0 && tmp.x < width &&
                    tmp.y >= 0 && tmp.y < height) {
                    offset = (tmp.x+width*tmp.y) * 3;
                    if (points[offset+0] == bg.x &&
                        points[offset+1] == bg.y &&
                        points[offset+2] == bg.z) {
                        points[offset+0] = color.x;
                        points[offset+1] = color.y;
                        points[offset+2] = color.z;
                        Q.push(tmp);
                    }
                }

                tmp = iVec2(n.x-1, n.y);
                if (tmp.x >= 0 && tmp.x < width &&
                    tmp.y >= 0 && tmp.y < height) {
                    offset = (tmp.x+width*tmp.y) * 3;
                    if (points[offset+0] == bg.x &&
                        points[offset+1] == bg.y &&
                        points[offset+2] == bg.z) {
                        points[offset+0] = color.x;
                        points[offset+1] = color.y;
                        points[offset+2] = color.z;
                        Q.push(tmp);
                    }
                }

                tmp = iVec2(n.x, n.y+1);
                if (tmp.x >= 0 && tmp.x < width &&
                    tmp.y >= 0 && tmp.y < height) {
                    offset = (tmp.x+width*tmp.y) * 3;
                    if (points[offset+0] == bg.x &&
                        points[offset+1] == bg.y &&
                        points[offset+2] == bg.z) {
                        points[offset+0] = color.x;
                        points[offset+1] = color.y;
                        points[offset+2] = color.z;
                        Q.push(tmp);
                    }
                }

                tmp = iVec2(n.x, n.y-1);
                if (tmp.x >= 0 && tmp.x < width &&
                    tmp.y >= 0 && tmp.y < height) {
                    offset = (tmp.x+width*tmp.y) * 3;
                    if (points[offset+0] == bg.x &&
                        points[offset+1] == bg.y &&
                        points[offset+2] == bg.z) {
                        points[offset+0] = color.x;
                        points[offset+1] = color.y;
                        points[offset+2] = color.z;
                        Q.push(tmp);
                    }
                }
            }
        }
    }
};

#endif // AREAFILL_H