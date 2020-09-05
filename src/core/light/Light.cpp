#include "engine/core/light/Light.h"

Light::Light(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular)
        : ambient(ambient), diffuse(diffuse), specular(specular) {

}

const fVec3 &Light::getAmbient() const {
    return ambient;
}

void Light::setAmbient(const fVec3 &ambient) {
    Light::ambient = ambient;
}

const fVec3 &Light::getDiffuse() const {
    return diffuse;
}

void Light::setDiffuse(const fVec3 &diffuse) {
    Light::diffuse = diffuse;
}

const fVec3 &Light::getSpecular() const {
    return specular;
}

void Light::setSpecular(const fVec3 &specular) {
    Light::specular = specular;
}
