#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <math/Vec3.h>
#include <math/Mat4.h>
#include <core/models/ModelRenderer.h>

class Raycaster {
private:
    static GLint data[];
    static double x, y, z;
public:
    static bool raycastPlane(const fVec3 &rayOrigin, const fVec3 &rayDirection, const fVec3 &normal, const fVec3 &center,
                             fVec3 &hit);

    static fVec3 cursorToWorld(const double &mouse_x, const double &mouse_y);
};

#endif // RAYCASTER_H