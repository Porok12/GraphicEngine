#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <math/Vec3.h>
#include "Light.h"

class DirectionalLight : public Light {
protected:
    fVec3 direction;

public:
    DirectionalLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &direction);

    const fVec3 &getDirection() const;
    void setDirection(const fVec3 &direction);
};

#endif // DIRECTIONALLIGHT_H