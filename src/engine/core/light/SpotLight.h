#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <math/Vec3.h>
#include "Light.h"

class SpotLight : public Light {
private:
    fVec3 position;
    fVec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;

public:
    SpotLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &position,
              const fVec3 &direction, float cutOff, float outerCutOff, float constant, float linear, float quadratic);

    const fVec3 &getPosition() const;
    void setPosition(const fVec3 &position);
    const fVec3 &getDirection() const;
    void setDirection(const fVec3 &direction);
    float getCutOff() const;
    void setCutOff(float cutOff);

    float getOuterCutOff() const;

    void setOuterCutOff(float outerCutOff);

    float getConstant() const;

    void setConstant(float constant);

    float getLinear() const;

    void setLinear(float linear);

    float getQuadratic() const;

    void setQuadratic(float quadratic);
};

#endif // SPOTLIGHT_H