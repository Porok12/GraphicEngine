#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include <math/Vec3.h>
#include "Light.h"

class SpotLight : public Light {
private:
    fVec3 position;
    fVec3 direction;
    float cutOff;

public:
    SpotLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular,
              const fVec3 &position, const fVec3 &direction, float cutOff);

    const fVec3 &getPosition() const;
    void setPosition(const fVec3 &position);
    const fVec3 &getDirection() const;
    void setDirection(const fVec3 &direction);
    float getCutOff() const;
    void setCutOff(float cutOff);
};

#endif // SPOTLIGHT_H