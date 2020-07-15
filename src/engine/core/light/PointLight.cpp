#include "PointLight.h"

PointLight::PointLight(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular, const fVec3 &position,
                       float constant, float linear, float quadratic)
        : Light(ambient, diffuse, specular), position(position), constant(constant), linear(linear), quadratic(quadratic) {

}

const fVec3 &PointLight::getPosition() const {
    return position;
}

void PointLight::setPosition(const fVec3 &position) {
    PointLight::position = position;
}

float PointLight::getConstant() const {
    return constant;
}

void PointLight::setConstant(float constant) {
    PointLight::constant = constant;
}

float PointLight::getLinear() const {
    return linear;
}

void PointLight::setLinear(float linear) {
    PointLight::linear = linear;
}

float PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::setQuadratic(float quadratic) {
    PointLight::quadratic = quadratic;
}
