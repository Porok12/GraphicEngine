#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &direction)
        : Light(ambient, diffuse, specular), direction(direction) {

}

const fVec3 &DirectionalLight::getDirection() const {
    return direction;
}

void DirectionalLight::setDirection(const fVec3 &direction) {
    DirectionalLight::direction = direction;
}
