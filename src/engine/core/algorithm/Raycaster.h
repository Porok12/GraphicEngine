#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <math/Vec3.h>
#include <math/Mat4.h>
#include <core/models/ModelRenderer.h>

class Raycaster {
public:
    static bool raycastPlane(const fVec3 &rayOrigin, const fVec3 &rayDirection, const fVec3 &normal, const fVec3 &center,
                             fVec3 &hit);
};

#endif // RAYCASTER_H