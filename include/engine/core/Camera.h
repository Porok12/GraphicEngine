#ifndef CAMERA_H
#define CAMERA_H

#include <engine/math/Vec3.h>
#include <engine/math/Mat4.h>

class Camera {
protected:
    fVec3 Up;
    fVec3 Position;
    fVec3 Front;
    fVec3 Right;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;

    virtual void update() = 0;
public:

    const fVec3 &getPos() const;
    const fVec3 &getFront() const;
    const fVec3 &getUp() const;
    const fVec3 &getRight() const;
};

#endif // CAMERA_H