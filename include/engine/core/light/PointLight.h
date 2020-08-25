#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <engine/math/Vec3.h>
#include "Light.h"

class PointLight : public Light {
private:
    fVec3 position;
    float constant;
    float linear;
    float quadratic;

public:
    PointLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &position,
               float constant, float linear, float quadratic);

    const fVec3 &getPosition() const;
    void setPosition(const fVec3 &position);
    float getConstant() const;
    void setConstant(float constant);
    float getLinear() const;
    void setLinear(float linear);
    float getQuadratic() const;
    void setQuadratic(float quadratic);
};

#endif // POINTLIGHT_H