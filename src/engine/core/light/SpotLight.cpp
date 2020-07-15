#include "SpotLight.h"

SpotLight::SpotLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &position, const fVec3 &direction,
                     float cutOff, float outerCutOff, float constant, float linear, float quadratic)
        : Light(ambient, diffuse, specular), position(position), direction(direction),
          cutOff(cutOff), outerCutOff(outerCutOff),
          constant(constant), linear(linear), quadratic(quadratic) {

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

float SpotLight::getOuterCutOff() const {
    return outerCutOff;
}

void SpotLight::setOuterCutOff(float outerCutOff) {
    SpotLight::outerCutOff = outerCutOff;
}

float SpotLight::getConstant() const {
    return constant;
}

void SpotLight::setConstant(float constant) {
    SpotLight::constant = constant;
}

float SpotLight::getLinear() const {
    return linear;
}

void SpotLight::setLinear(float linear) {
    SpotLight::linear = linear;
}

float SpotLight::getQuadratic() const {
    return quadratic;
}

void SpotLight::setQuadratic(float quadratic) {
    SpotLight::quadratic = quadratic;
}
