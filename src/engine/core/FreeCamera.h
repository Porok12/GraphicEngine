#ifndef FREECAMERA_H
#define FREECAMERA_H

#include <GL/glew.h>
#include "Camera.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class FreeCamera : public Camera {
private:
    bool enabled;
    void update() override;

public:
    explicit FreeCamera(const fVec3 &Position);

    Mat4 getViewMatrix();
    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(const double &x, const double &y);

    void toggle();
    void reset();

    bool isEnabled() const;
};

#endif // FREECAMERA_H
