#ifndef CAMERA_H
#define CAMERA_H

#include <math/Mat4.h>
#include <GL/glew.h>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
private:
    bool enabled;
    fVec3 Position;
    fVec3 Front;
    fVec3 Up;
    fVec3 Right;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    volatile bool test = false;

    void updateCameraVectors();

public:
    explicit Camera(const fVec3 &Position);


    Mat4 getViewMatrix();
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(const double &x, const double &y);
    const fVec3 &getPos() const;
    const fVec3 &getFront() const;
    const fVec3 &getUp() const;
    const fVec3 &getRight() const;

    void toggle();

    bool isEnabled() const;
};

#endif // CAMERA_H