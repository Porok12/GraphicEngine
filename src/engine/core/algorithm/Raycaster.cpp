#include "Raycaster.h"

bool Raycaster::raycastPlane(const fVec3 &rayOrigin, const fVec3 &rayDirection, const fVec3 &normal, const fVec3 &center, fVec3 &hit) {
    float denom = normal.dot(rayDirection);

    if (abs(denom) > 0.0001f) {
        float t = (center - rayOrigin).dot(normal) / denom;
        if (t > 0) { // 0 - behind
            fVec3 tmp = rayOrigin + rayDirection * t;
            hit.x = tmp.x; hit.y = tmp.y; hit.z = tmp.z;

            return true;
        }
    }

    return false;
}
