#include "SpotLight.h"

SpotLight::SpotLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &position,
                     const fVec3 &direction, float cutOff)
        : Light(ambient, diffuse, specular), position(position), direction(direction), cutOff(cutOff) {

}

const fVec3 &SpotLight::getPosition() const {
    return position;
}

void SpotLight::setPosition(const fVec3 &position) {
    SpotLight::position = position;
}

const fVec3 &SpotLight::getDirection() const {
    return direction;
}

void SpotLight::setDirection(const fVec3 &direction) {
    SpotLight::direction = direction;
}

float SpotLight::getCutOff() const {
    return cutOff;
}

void SpotLight::setCutOff(float cutOff) {
    SpotLight::cutOff = cutOff;
}
