#ifndef LIGHT_H
#define LIGHT_H

#include <math/Vec3.h>

class Light {
protected:
    fVec3 ambient;
    fVec3 diffuse;
    fVec3 specular;

public:
    Light(const fVec3 &ambient, const fVec3 &diffuse, const fVec3 &specular);

    const fVec3 &getAmbient() const;
    void setAmbient(const fVec3 &ambient);
    const fVec3 &getDiffuse() const;
    void setDiffuse(const fVec3 &diffuse);
    const fVec3 &getSpecular() const;
    void setSpecular(const fVec3 &specular);
};

#endif // LIGHT_H
